// QTSDK.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <Movies.h>
#include <QTML.h>
#include <CoreAudioTypes.h>


int main()
{
    std::string mystring3 = "D:\\CodingProjects\\_ffmpeg\\resolve_OG.mov";
    std::string mystring2 = "D:\\CodingProjects\\_ffmpeg\\resolve_51.mov";
    std::string mystring = "C:\\Users\\cagef\\projects\\_QT\\resolve_51.mov";
    OSErr initerr = InitializeQTML(0L);
    OSErr entererr = EnterMovies();

    CFStringRef inPath = CFStringCreateWithCString(CFAllocatorGetDefault(), mystring.c_str(), CFStringGetSystemEncoding());    

    Movie myMovie;
    short myResID;
    Size mySize = (Size)strlen(mystring.c_str()) + 1;
    Handle myHandle = NewHandle(mySize);
    OSType myDataRefType = NULL;

    OSErr datareferr = QTNewDataReferenceFromFullPathCFString(inPath, kQTWindowsPathStyle, 0, &myHandle, &myDataRefType);
    OSErr newmovieerr = NewMovieFromDataRef(&myMovie, 0, &myResID, myHandle, myDataRefType);

	AudioChannelLayout* layout = nil;
	ByteCount layoutsize;
	ByteCount layoutsizeused;
	UInt32 outprop;
	QTPropertyValueType proptype;
	UInt32 size = 0;
    SoundDescriptionHandle mySD;

	MovieAudioExtractionRef extractionSessionRef = nil;
	SoundDescriptionHandle mySound = nil;
	AudioStreamBasicDescription asbd;

	OSStatus extracterr = MovieAudioExtractionBegin(myMovie, 0, &extractionSessionRef);

	OSStatus extractasbderr = MovieAudioExtractionGetProperty(extractionSessionRef,
		kQTPropertyClass_MovieAudioExtraction_Audio,
		kQTMovieAudioExtractionAudioPropertyID_AudioStreamBasicDescription,
		sizeof(asbd), &asbd, nil);

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
    
    OSStatus sdcreateerr = QTSoundDescriptionCreate(&asbd, &mylayout, layoutsize, nil, nil, FOUR_CHAR_CODE('mvv2'), &mySD);


	std::cout << "test" << std::endl;


    
 //    //Extraction Technique -------

	//AudioChannelLayout* layout = nil;
	//ByteCount layoutsize;
	//ByteCount layoutsizeused;
	//UInt32 outprop;
	//QTPropertyValueType proptype;
 //   UInt32 size = 0;

 //   MovieAudioExtractionRef extractionSessionRef = nil;
 //   SoundDescriptionHandle mySound = nil;
 //   AudioStreamBasicDescription asbd;

 //   OSStatus extracterr = MovieAudioExtractionBegin(myMovie, 0, &extractionSessionRef);

 //   OSStatus extractasbderr = MovieAudioExtractionGetProperty(extractionSessionRef, 
 //       kQTPropertyClass_MovieAudioExtraction_Audio,
 //       kQTMovieAudioExtractionAudioPropertyID_AudioStreamBasicDescription,
 //       sizeof(asbd), &asbd, nil);

 //   // First get the size of the extraction output layout
 //   OSStatus extractlayoutsizeerr = MovieAudioExtractionGetPropertyInfo(extractionSessionRef,
 //       kQTPropertyClass_MovieAudioExtraction_Audio,
 //       kQTMovieAudioExtractionAudioPropertyID_AudioChannelLayout,
 //       NULL, &size, NULL);

	//// Allocate memory for the channel layout
	//layout = (AudioChannelLayout*)calloc(1, size);

	//// Get the layout for the current extraction configuration.
	//// This will have already been expanded into channel descriptions.
 //   OSStatus extractlayouterr = MovieAudioExtractionGetProperty(extractionSessionRef,
	//	kQTPropertyClass_MovieAudioExtraction_Audio,
	//	kQTMovieAudioExtractionAudioPropertyID_AudioChannelLayout,
	//	size, layout, nil);  

 //   
 //   std::cout << "test" << std::endl;
    
    
     //Track Technique ------

    //long trackcount = GetMovieTrackCount(myMovie);
    //Track firsttrack = GetMovieTrack(myMovie, 3);
    //AudioChannelLayout* layout;
    //UInt32 layoutsize;
    //UInt32 layoutsizeused;


    //OSErr gettrackinfoerr = QTGetTrackPropertyInfo(firsttrack, kQTPropertyClass_Audio,
    //    kQTAudioPropertyID_ChannelLayout, nil, &layoutsize, nil);

    //layout = (AudioChannelLayout*)calloc(1, layoutsize);

    //OSErr gettrackproperr = QTGetTrackProperty(firsttrack, kQTPropertyClass_Audio,
    //    kQTAudioPropertyID_ChannelLayout, layoutsize, &layout, &layoutsizeused);

    //std::cout << "test" << std::endl;


}