#pragma once

#include "Config.h"

class ArgsParser {
public:
    void Parse(
        // argc - кол-во адресов
        // argv[] - массив из указателей на них
        int argc, char* argv[],
        Config& config
    );
};
