// QTSDK.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <Movies.h>
#include <QTML.h>


int main()
{
    std::string mystring = "D:\\CodingProjects\\_ffmpeg\\resolve_OG.mov";
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

}