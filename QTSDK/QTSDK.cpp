#include <iostream>
#include <map>
#include <string>
#include <Movies.h>
#include <QTML.h>
#include <CoreAudioTypes.h>
#include "general.h"

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
        if (i > 6)
        {
            currentch = i + 31;
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


int main(int argc, char* argv[])
{
    int numberOfTracks;
    int* channels;
    channels = parseargs(argc, argv, numberOfTracks);

    if ((string)argv[2] == "debug")
    {
        print("Exited");
        exit(1);
    }

    errorDict initerrors = initQT();

    for (auto item : initerrors)
    {
        if (item.second != 0)
        {
            cout << "Init QT error in " << "'" << item.first << "'" << endl;
            exit(1);
        }
    }

    const char* fileURL = argv[2];

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
}