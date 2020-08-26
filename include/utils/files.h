#ifndef _UNIVERSAL_UPDATER_FILES_H
#define _UNIVERSAL_UPDATER_FILES_H

#include "common.hpp"

Result makeDirs(const char * path);
Result openFile(Handle* fileHandle, const char * path, bool write);
Result deleteFile(const char * path);
Result removeDir(const char * path);
Result removeDirRecursive(const char * path);

#endif