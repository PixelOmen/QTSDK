#include "general.h"
#include <QTML.h>
#include <Movies.h>
#include <CoreAudioTypes.h>

using namespace std;

void initQT(errorDict* errors)
{
    (*errors)["init"] = InitializeQTML(0L);
    (*errors)["enter"] = EnterMovies();
}

Track* getTracks(Movie& movie, array<int, 2> range)
{
    const int numOfTracks = (range[1] - range[0]) + 1;
    Track* allTracks = new Track[numOfTracks];
    for (int i = 0; i < numOfTracks; i++)
    {
        allTracks[i] = GetMovieTrack(movie, (range[0] + i));
    }
    return allTracks;
}

AudioChannelLayout* buildLayouts(int& num, bool& me6ch)
{
    AudioChannelLabel currentch;
    AudioChannelLayout* totalLayouts = new AudioChannelLayout[num];
    for (int i = 0; i < num; i++)
    {
        if (me6ch)
        {
            if (i % 2 == 0)
            {
                currentch = 1;
            }
            else
            {
                currentch = 2;
            }
            totalLayouts[i] = { kAudioChannelLayoutTag_UseChannelDescriptions,
                NULL, 1, {currentch, NULL, NULL} };
        }
        else
        {
            if (i > 5)
            {
                currentch = i + 32;
            }
            else
            {
                currentch = i + 1;
            }
            totalLayouts[i] = { kAudioChannelLayoutTag_UseChannelDescriptions,
                NULL, 1, {currentch, NULL, NULL} };
        }
    }
    return totalLayouts;
}

void FlagQT(Movie& myMovie, array<int, 2>& channels, int& numberOfTracks, bool& me6ch, errorDict& converterrors)
{
    Track* workingTracks = getTracks(myMovie, channels);
    AudioChannelLayout* layouts = buildLayouts(numberOfTracks, me6ch);

    for (int i = 0; i < numberOfTracks; i++)
    {
        converterrors["SetTrack"] = QTSetTrackProperty(workingTracks[i], kQTPropertyClass_Audio, kQTAudioPropertyID_ChannelLayout,
            sizeof(layouts[i]), &layouts[i]);
    }
}



void SetTC(const Movie& myMovie, errorDict& converterrors, TimeCodeRecord& myTRR, TimeCodeDef& myTCD)
{
    Track videotrack = GetMovieIndTrackType(myMovie, 1, VideoMediaType, movieTrackMediaType);
    TimeValue myMovieDur = GetMovieDuration(myMovie);
    TimeScale myTS = GetMovieTimeScale(myMovie);

    long mySize = sizeof(TimeCodeDescription);
    TimeCodeDescriptionHandle myDesc = (TimeCodeDescriptionHandle)NewHandleClear(mySize);
    (**myDesc).descSize = mySize;
    (**myDesc).dataFormat = TimeCodeMediaType;
    (**myDesc).resvd1 = 0;
    (**myDesc).resvd2 = 0;
    (**myDesc).dataRefIndex = 1;
    (**myDesc).flags = 0;
    (**myDesc).timeCodeDef = myTCD;

    Track oldTrack = GetMovieIndTrackType(myMovie, 1, TimeCodeMediaType, movieTrackMediaType);
    while (oldTrack != NULL) {
        DisposeMovieTrack(oldTrack);
        oldTrack = GetMovieIndTrackType(myMovie, 1, TimeCodeMediaType, movieTrackMediaType);
    }

    Track newTCtrack = NewMovieTrack(myMovie, 0, 0, 0);
    Media newTCmedia = NewTrackMedia(newTCtrack, TimeCodeMediaType, myTS, NULL, 0);

    long** framenum = (long**)NewHandle(sizeof(long));
    Handle frameH = (Handle)framenum;
    HandlerError TCtoFrameErr = TCTimeCodeToFrameNumber(GetMediaHandler(newTCmedia), &myTCD, &myTRR, *framenum);
    **framenum = EndianS32_NtoB(**framenum);

    converterrors["BeginEdits"] = BeginMediaEdits(newTCmedia);
    converterrors["AddMediaSample"] = AddMediaSample(newTCmedia, frameH, 0, GetHandleSize(frameH), myMovieDur,
                                                                            SampleDescriptionHandle(myDesc), 1, 0, 0);
    converterrors["EndEdits"] = EndMediaEdits(newTCmedia);

    converterrors["InsertMedia"] = InsertMediaIntoTrack(newTCtrack, 0, 0, myMovieDur, fixed1);
    converterrors["AddTrackReference"] = AddTrackReference(videotrack, newTCtrack, TimeCodeMediaType, NULL);
}


int main(int argc, char* argv[])
{
    argHandler args{ argc, argv };

    // Debug only, checks incoming arguments
    //for (auto i : args.getparams())
    //{
    //    cout << i.first << " with " << i.second << "\n";
    //}

    //if (!args.tasks.empty())
    //{
    //    for (auto i : args.tasks)
    //    {
    //        cout << "Task: " << i << "\n";
    //    }
    //}
    // end of Debug only

    errorDict initerrors{};
    initQT(&initerrors);

    for (auto item : initerrors)
    {
        if (item.second != 0)
        {
            cout << "Init QT error in " << "'" << item.first << "'" << endl;
            exit(1);
        }
    }

    Movie myMovie;
    FSSpec myFileSpec;
    const FSSpec* myFSptr = &myFileSpec;
    short myRefNum;
    short myResID;
    StringPtr myStringPtr = (StringPtr)"WorkingFile";
    Boolean wasChanged;
    errorDict converterrors;

    converterrors["PathToSpec"] = NativePathNameToFSSpec(const_cast<char*>(args.fileURL.c_str()), (FSSpec*)myFSptr, 0);
    converterrors["OpenMovie"] = OpenMovieFile(myFSptr, &myRefNum, 0);
    converterrors["NewMovie"] = NewMovieFromFile(&myMovie, myRefNum, &myResID, myStringPtr, 0, &wasChanged);

    if (converterrors["NewMovie"] != 0)
    {
        cout << "Error opening QT. 'NewMovie' error code: " << converterrors["NewMovie"] << "\n";
        exit(1);
    }

    if (vectortools::contains(args.tasks, string("setTC")))
    {
		SetTC(myMovie, converterrors, args.TCR, args.TCD);
    }

    if (vectortools::contains(args.tasks, string("flagaudio")))
    {
        bool me6ch = vectortools::contains(args.tasks, string("me6ch"));
        {
            FlagQT(myMovie, args.channelRange, args.numOfTracks, me6ch, converterrors);
        }
    }

    if (wasChanged)
    {
		converterrors["UpdateResource"] = UpdateMovieResource(myMovie, myRefNum, myResID, (ConstStr255Param)"Update");
	}

    converterrors["CloseMovie"] = CloseMovieFile(myRefNum);
    converterrors["General"] = GetMoviesError();

    for (auto i : converterrors)
    {
        if (i.second != 0)
        {
            cout << "Error from " << i.first << ". Error: " << i.second << endl;
            exit(1);
        }
    }

    print("Success");
}