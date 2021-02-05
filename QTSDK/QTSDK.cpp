#include <iostream>
#include <map>
#include <Movies.h>
#include <QTML.h>
#include <CoreAudioTypes.h>

typedef std::map<std::string, OSErr> errorDict;

template<typename T>
void print(T toprint)
{
    std::cout << toprint << std::endl;
}

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
        currentch = i+1;
        totalLayouts[i] = {kAudioChannelLayoutTag_UseChannelDescriptions,
            NULL, 1, {currentch, NULL, NULL}};
    }
    return totalLayouts;
}


int main()
{
    errorDict initerrors = initQT();

    for (auto item : initerrors)
    {
        if (item.second != 0)
            exit(1);
    }

    const char* fileURL = "C:\\Users\\cagef\\projects\\_testfiles\\Batman_Mono.mov";

    Movie myMovie;
    FSSpec myFileSpec;
    const FSSpec* myFSptr = &myFileSpec;
    short myRefNum;
    short myResID;
    const char* stringName = "WorkingFile";
    StringPtr myStringPtr = (StringPtr)stringName;
    Boolean wasChanged;
    int trackRange[2]{ 2,7 };
    int numberOfTracks = (trackRange[1] - trackRange[0]) + 1;

    OSErr pathtospecerr = NativePathNameToFSSpec((char*)fileURL, (FSSpec*)myFSptr, 0);
    OSErr openerr = OpenMovieFile(myFSptr, &myRefNum, 0);
    OSErr newmovieerr = NewMovieFromFile(&myMovie, myRefNum, &myResID, myStringPtr, 0, &wasChanged);

    Track* workingTracks = getTracks(myMovie, trackRange);
    AudioChannelLayout* layouts = buildLayouts(numberOfTracks);

    for (int i = 0; i < numberOfTracks; i++)
    {
        OSErr settrackerr = QTSetTrackProperty(workingTracks[i], kQTPropertyClass_Audio, kQTAudioPropertyID_ChannelLayout,
            sizeof(layouts[i]), &layouts[i]);
    }

    OSErr updateerr = UpdateMovieResource(myMovie, myRefNum, myResID, (ConstStr255Param)"ChannelLayoutUpdate");
    OSErr closeerr = CloseMovieFile(myRefNum);


    //print("test");

}