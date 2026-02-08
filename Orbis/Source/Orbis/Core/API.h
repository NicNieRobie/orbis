#pragma once

#ifdef _WIN64
    #ifdef ORBIS_BUILD_DLL
        #define ORBIS_API __declspec(dllexport)
    #else
        #define ORBIS_API __declspec(dllimport)
    #endif
#else
    #define ORBIS_API
#endif
