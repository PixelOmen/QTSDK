#include <iostream>
#include <Movies.h>
#include <QTML.h>
#include <CoreAudioTypes.h>

void initQT()
{

}


int main()
{
    OSErr initerr = InitializeQTML(0L);
    OSErr entererr = EnterMovies();

    std::string mystring2 = "D:\\CodingProjects\\_ffmpeg\\resolve_OG.mov";
    std::string mystring3 = "D:\\CodingProjects\\_ffmpeg\\resolve_51.mov";
    std::string mystring = "C:\\Users\\cagef\\projects\\_testfiles\\resolve_OG.mov";
    const char* mystringchar = "C:\\Users\\cagef\\projects\\_testfiles\\Batman_Mono.mov";

    Movie myMovie;
    Size mySize = (Size)strlen(mystring.c_str()) + 1;
    Handle myHandle = NewHandle(mySize);
    OSType myDataRefType = NULL;
	AudioChannelLayout* layout = nil;
	ByteCount layoutsize;
	UInt32 size = 0;
	MovieAudioExtractionRef extractionSessionRef = nil;
	SoundDescriptionHandle mySound = nil;

   AudioChannelDescription myDescriptions[6];
    myDescriptions[0] = {kAudioChannelLabel_Left, NULL, NULL};
    myDescriptions[1] = {kAudioChannelLabel_Right, NULL, NULL};
    myDescriptions[2] = {kAudioChannelLabel_Center, NULL, NULL};
    myDescriptions[3] = {kAudioChannelLabel_LFEScreen, NULL, NULL};
    myDescriptions[4] = {kAudioChannelLabel_LeftSurround, NULL, NULL};
    myDescriptions[5] = {kAudioChannelLabel_RightSurround, NULL, NULL};

    const int sizeofmyDesc = sizeof(myDescriptions) / sizeof(AudioChannelDescription);
    AudioChannelLayout mylayout = {kAudioChannelLayoutTag_UseChannelDescriptions,
        NULL, 6, NULL};

    for (int i = 0; i < sizeofmyDesc; i++)
    {
        mylayout.mChannelDescriptions[i] = myDescriptions[i];
    }
    layoutsize = sizeof(mylayout);

    FSSpec myFileSpec;
    short myRefNum;
    short myResID;
    const char* stringName = "MyFileName";
    StringPtr myStringPtr = (StringPtr)stringName;
    Boolean wasChanged;

    OSErr pathtospecerr = NativePathNameToFSSpec((char*)mystringchar, &myFileSpec, 0);
    const FSSpec* myFSptr = &myFileSpec;
    OSErr openerr = OpenMovieFile(myFSptr, &myRefNum, 0);
    OSErr newmovieerr = NewMovieFromFile(&myMovie, myRefNum, &myResID, myStringPtr, 0, &wasChanged);

	Track firsttrack = GetMovieTrack(myMovie, 2);
    AudioChannelLayout leftLayout = { kAudioChannelLayoutTag_UseChannelDescriptions,
    NULL, 1, {kAudioChannelLabel_Left, NULL, NULL}};
    ByteCount leftLayoutSize = sizeof(leftLayout);

    OSErr settrackerr = QTSetTrackProperty(firsttrack, kQTPropertyClass_Audio, kQTAudioPropertyID_ChannelLayout,
        leftLayoutSize, &leftLayout);

    OSErr updateerr = UpdateMovieResource(myMovie, myRefNum, myResID, (ConstStr255Param)"test.mov");

    OSErr closeerr = CloseMovieFile(myRefNum);


    std::cout << "test" << std::endl;


}