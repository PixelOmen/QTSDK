#include "general.h"
#include <QTML.h>
#include <Movies.h>
#include <CoreAudioTypes.h>
#include <QuickTimeComponents.h>

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

AudioChannelLayout* buildLayouts(int& num)
{
    AudioChannelLabel currentch;
    AudioChannelLayout* totalLayouts = new AudioChannelLayout[num];
    for (int i = 0; i < num; i++)
    {
        if (i > 5)
        {
            currentch = i + 32;
        }
        else
        {
			currentch = i + 1;
        }
        totalLayouts[i] = {kAudioChannelLayoutTag_UseChannelDescriptions,
            NULL, 1, {currentch, NULL, NULL}};
    }
    return totalLayouts;
}

void FlagQT(Movie& myMovie, array<int, 2>& channels, int& numberOfTracks, errorDict& converterrors)
{
    Track* workingTracks = getTracks(myMovie, channels);
    AudioChannelLayout* layouts = buildLayouts(numberOfTracks);

    for (int i = 0; i < numberOfTracks; i++)
    {
        converterrors["SetTrack"] = QTSetTrackProperty(workingTracks[i], kQTPropertyClass_Audio, kQTAudioPropertyID_ChannelLayout,
            sizeof(layouts[i]), &layouts[i]);
    }
}

void SetTC(const Movie& myMovie, errorDict& converterrors)
{
    Track videotrack = GetMovieIndTrackType(myMovie, 1, VideoMediaType, movieTrackMediaType);
    TimeValue myMovieDur = GetMovieDuration(myMovie);
    TimeScale myTS = GetMovieTimeScale(myMovie);

    TimeCodeRecord myTRR;
    myTRR.t.hours = (UInt8)0;
    myTRR.t.minutes = (UInt8)59;
    myTRR.t.seconds = (UInt8)50;
    myTRR.t.frames = (UInt8)00;

    long mySize = sizeof(TimeCodeDescription);
    TimeCodeDescriptionHandle myDesc = (TimeCodeDescriptionHandle)NewHandleClear(mySize);
    TimeCodeDef myTCDef{ 0, 24000, 1001, 24 };
    (**myDesc).descSize = mySize;
    (**myDesc).dataFormat = TimeCodeMediaType;
    (**myDesc).resvd1 = 0;
    (**myDesc).resvd2 = 0;
    (**myDesc).dataRefIndex = 1;
    (**myDesc).flags = 0;
    (**myDesc).timeCodeDef = myTCDef;

    Track oldTrack = GetMovieIndTrackType(myMovie, 1, TimeCodeMediaType, movieTrackMediaType);
    while (oldTrack != NULL) {
        DisposeMovieTrack(oldTrack);
        oldTrack = GetMovieIndTrackType(myMovie, 1, TimeCodeMediaType, movieTrackMediaType);
    }

    Track newTCtrack = NewMovieTrack(myMovie, 0, 0, 0);
    Media newTCmedia = NewTrackMedia(newTCtrack, TimeCodeMediaType, myTS, NULL, 0);

    long** framenum = (long**)NewHandle(sizeof(long));
    Handle frameH = (Handle)framenum;
    HandlerError TCtoFrameErr = TCTimeCodeToFrameNumber(GetMediaHandler(newTCmedia), &myTCDef, &myTRR, *framenum);
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
    int numOfTracks = NULL;
    array<int, 2> channels{};
    char* fileURL = nullptr;
    vector<string> tasks;
    commands argcmds = parseargs(argc, argv, &numOfTracks, &channels, &fileURL, &tasks);

    for (auto i : argcmds)
    {
        cout << i.first << " with " << i.second << "\n";
    }

    if (!tasks.empty())
    {
        for (auto i : tasks)
        {
            cout << "Task: " << i << "\n";
        }
    }

    exit(0);

    errorDict initerrors;
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

    converterrors["PathToSpec"] = NativePathNameToFSSpec(fileURL, (FSSpec*)myFSptr, 0);
    converterrors["OpenMovie"] = OpenMovieFile(myFSptr, &myRefNum, 0);
    converterrors["NewMovie"] = NewMovieFromFile(&myMovie, myRefNum, &myResID, myStringPtr, 0, &wasChanged);

    FlagQT(myMovie, channels, numOfTracks, converterrors);

    SetTC(myMovie, converterrors);

    converterrors["General"] = GetMoviesError();
    converterrors["UpdateResource"] = UpdateMovieResource(myMovie, myRefNum, myResID, (ConstStr255Param)"TCUpdate");
    converterrors["CloseMovie"] = CloseMovieFile(myRefNum);

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