#include <iostream>
#include <map>
#include <string>
#include <Movies.h>
#include <QTML.h>
#include <CoreAudioTypes.h>
#include <QuickTimeComponents.h>
#include "general.h"

using namespace std;

typedef std::map<std::string, OSErr> errorDict;

errorDict initQT()
{
    errorDict errors;
    errors["init"] = InitializeQTML(0L);
    errors["enter"] = EnterMovies();
    return errors;
}

Track* getTracks(Movie& movie, int* range)
{
    const int numOfTracks = (range[1] - range[0]) + 1;
    Track* allTracks = new Track[numOfTracks];
    for (int i = 0; i < numOfTracks; i++)
    {
        allTracks[i] = GetMovieTrack(movie, (range[0] + i));
    }
    return allTracks;
}

AudioChannelLayout* buildLayouts(int num)
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

void FlagQT(Movie& myMovie, int* channels, int& numberOfTracks, errorDict& converterrors, short& myRefNum, short& myResID)
{
    Track* workingTracks = getTracks(myMovie, channels);
    AudioChannelLayout* layouts = buildLayouts(numberOfTracks);

    for (int i = 0; i < numberOfTracks; i++)
    {
        converterrors["SetTrack"] = QTSetTrackProperty(workingTracks[i], kQTPropertyClass_Audio, kQTAudioPropertyID_ChannelLayout,
            sizeof(layouts[i]), &layouts[i]);
    }

    converterrors["UpdateResource"] = UpdateMovieResource(myMovie, myRefNum, myResID, (ConstStr255Param)"ChannelLayoutUpdate");
    converterrors["CloseMovie"] = CloseMovieFile(myRefNum);

    for (auto i : converterrors)
    {
        if (i.second != 0)
        {
            cout << "Error from " << i.first << endl;
            exit(1);
        }
    }

    print("Success");
    exit(0);
}

int main(int argc, char* argv[])
{
    int numberOfTracks;
    int* channels;
    //channels = parseargs(argc, argv, numberOfTracks);

    //if ((string)argv[2] == "debug")
    //{
    //    print("Exited");
    //    exit(1);
    //}

    errorDict initerrors = initQT();

    for (auto item : initerrors)
    {
        if (item.second != 0)
        {
            cout << "Init QT error in " << "'" << item.first << "'" << endl;
            exit(1);
        }
    }

    //const char* fileURL = argv[2];
    const char* fileURL = "C://Users//cagef//projects//_testfiles//TC_Testing.mov";

    Movie myMovie;
    FSSpec myFileSpec;
    const FSSpec* myFSptr = &myFileSpec;
    short myRefNum;
    short myResID;
    StringPtr myStringPtr = (StringPtr)"WorkingFile";
    Boolean wasChanged;
    errorDict converterrors;

    converterrors["PathToSpec"] = NativePathNameToFSSpec((char*)fileURL, (FSSpec*)myFSptr, 0);
    converterrors["OpenMovie"] = OpenMovieFile(myFSptr, &myRefNum, 0);
    converterrors["NewMovie"] = NewMovieFromFile(&myMovie, myRefNum, &myResID, myStringPtr, 0, &wasChanged);

    //FlagQT(myMovie, channels, numberOfTracks, converterrors, myRefNum, myResID);

    Track tctrack = GetMovieTrack(myMovie, 8);
    Track videotrack = GetMovieTrack(myMovie, 1);

    TimeValue myMovieDur = GetMovieDuration(myMovie);
    TimeScale myTS = GetMovieTimeScale(myMovie);

    TimeCodeTime myTC;
    myTC.hours = 0;
    myTC.minutes = 10;
    myTC.seconds = 1;
    myTC.frames = 0;

    TimeCodeRecord myTRR;
    myTRR.t = myTC;

    long mySize = sizeof(TimeCodeDescription);
    TimeCodeDescriptionHandle myDesc = (TimeCodeDescriptionHandle)NewHandle(mySize);
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

    long framenum;
    HandlerError TCtoFrameErr = TCTimeCodeToFrameNumber(GetMediaHandler(newTCmedia), &myTCDef, &myTRR, &framenum);
    //framenum = EndianS32_NtoB(framenum);
    long* framenumptr = &framenum;
    Handle frameH = NewHandle(sizeof(long));
    frameH = (Handle)&framenumptr;


    OSErr setdefaulterr = SetMediaDefaultDataRefIndex(newTCmedia, 1);
    OSErr beginEditsErr = BeginMediaEdits(newTCmedia);
    OSErr addSampleErr = AddMediaSample(newTCmedia, frameH, 0, GetHandleSize(frameH), myMovieDur,
        SampleDescriptionHandle(myDesc), 1, 0, 0);
    OSErr endEditsErr = EndMediaEdits(newTCmedia);

    OSErr insertErr = InsertMediaIntoTrack(newTCtrack, 0, 0, myMovieDur, 1);
    OSErr myErr = AddTrackReference(videotrack, newTCtrack, TimeCodeMediaType, NULL);

    OSErr generalErr = GetMoviesError();


    converterrors["UpdateResource"] = UpdateMovieResource(myMovie, myRefNum, myResID, (ConstStr255Param)"TCUpdate");
    converterrors["CloseMovie"] = CloseMovieFile(myRefNum);

    for (auto i : converterrors)
    {
        if (i.second != 0)
        {
            cout << "Error from " << i.first << endl;
        }
    };
    
    // ----- Media Sample DESCRIPTION -----------
    //TimeCodeDef TCdef23976{0, 24000, 1001, 24};
    //TimeCodeDescription myTCdesc {0, TimeCodeMediaType, 0, 0, 1, 0, TCdef23976, 0};
    //myTCdesc.descSize = sizeof(myTCdesc);
    //TimeCodeDescriptionHandle myTChandle = (TimeCodeDescriptionHandle)NewHandle(myTCdesc.descSize);
    //OSErr setMediaDescErr = SetMediaSampleDescription(tctrackmedia, 1, (SampleDescriptionHandle)myTChandle);
    //OSErr generalErr = GetMoviesError();
    //Media newtctrackmedia = NewTrackMedia(tctrack, TimeCodeMediaType, 24000, nil, MovieMediaType);
}