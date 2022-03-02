#pragma once

namespace Main {
    //const int EXIT_SUCCESS = 0;   // Already part of C standard
    const int EXIT_ERROR_NO_ARGS = 1;
    const int EXIT_ERROR_FILE_NOT_FOUND = 2;

    const char* const TESTDATA_DIR = "Debug/TestData/";

    int CommandLine(int, char**);
}