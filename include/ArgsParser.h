#pragma once
#include "FileSystemScanner.h"

class ArgsParser
{
public:
    FileSystemScanner::ScanConfig Parse(int argc, char* argv[]) const;
};
