#pragma once

 void* CreateDepthBufMapFile();
 int UnmapDepthBufFile(void* UnmapFileStruct);
 void* OpenDepthBufMapFileToRead(int x, int y);
 void* ReadDepthMapBufFile(void* InDataStruct);
 int CheckDMBFlag(void* InDataStruct);