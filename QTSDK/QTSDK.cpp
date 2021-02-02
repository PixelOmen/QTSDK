// QTSDK.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <Movies.h>
#include <QTML.h>
#include <CoreAudioTypes.h>


int main()
{
    std::string mystring2 = "D:\\CodingProjects\\_ffmpeg\\resolve_OG.mov";
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


    long trackcount = GetMovieTrackCount(myMovie);
	Track firsttrack = GetMovieTrack(myMovie, 3);
    long trackcount2 = GetMovieTrackCount(myMovie);
    AudioChannelLayout* layout = nil;
    UInt32 layoutsize;
    UInt32 layoutsizeused;
    QTPropertyValueType proptype;


    OSErr gettrackinfoerr = QTGetTrackPropertyInfo(firsttrack, kQTPropertyClass_Audio,
        kQTAudioPropertyID_ChannelLayout, &proptype, &layoutsize, nil);
    
    layout = (AudioChannelLayout*)malloc(layoutsize);

    OSErr gettrackproperr = QTGetTrackProperty(firsttrack, kQTPropertyClass_Audio,
        kQTAudioPropertyID_ChannelLayout, layoutsize, &layout, &layoutsizeused);

    firsttrack;


    std::cout << 'test';






        
 //   // Extraction Technique -------

 //   MovieAudioExtractionRef extractionSessionRef = nil;
 //   SoundDescriptionHandle mySound = nil;
 //   AudioStreamBasicDescription asbd;

 //   OSStatus extracterr = MovieAudioExtractionBegin(myMovie, 0, &extractionSessionRef);

 //   OSStatus extractasbderr = MovieAudioExtractionGetProperty(extractionSessionRef, 
 //       kQTPropertyClass_MovieAudioExtraction_Audio,
 //       kQTMovieAudioExtractionAudioPropertyID_AudioStreamBasicDescription,
 //       sizeof(asbd), &asbd, nil);

 //   AudioChannelLayout* layout = NULL;
 //   UInt32             size = 0;

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

}