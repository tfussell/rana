solution "rana"
    configurations { "debug", "release" }
    platforms { "x64" }
    location ("./" .. _ACTION)
    configuration "debug"
        flags { "Symbols" }

project "rana.test"
    kind "ConsoleApp"
    language "C++"
    targetname "rana.test"
    targetdir "../bin"
    includedirs { 
       "../include/rana",
       "/usr/local/Cellar/cxxtest/4.3"
    }
    files {
       "../tests/*.hpp",
       "../tests/runner-autogen.cpp",
       "../include/rana/*.hpp"
    }
    prebuildcommands { "/usr/local/Cellar/cxxtest/4.3/bin/cxxtestgen --runner=ErrorPrinter -o ../../tests/runner-autogen.cpp ../../tests/*.hpp" }
    flags { 
       "Unicode",
       "NoEditAndContinue",
       "NoPCH"
    }
    configuration "debug"
        targetsuffix "d"
    configuration "release"
        flags { "Optimize" }
    configuration "not windows"
        buildoptions { 
            "-std=c++11",
            "-Wno-unknown-pragmas"
        }
    configuration { "not windows", "debug" }
        buildoptions { "-ggdb" }

project "rana.benchmark"
    kind "ConsoleApp"
    language "C++"
    targetname "rana.benchmark"
    targetdir "../bin"
    includedirs { 
       "../include/rana"
    }
    files {
       "../benchmark/main.cpp",
       "../include/rana/*.hpp"
    }
    flags { 
       "Unicode",
       "NoEditAndContinue",
       "NoPCH"
    }
    configuration "debug"
        targetsuffix "d"
    configuration "release"
        flags { "Optimize" }
    configuration "not windows"
        buildoptions { 
            "-std=c++11",
            "-Wno-unknown-pragmas"
        }
    configuration { "not windows", "debug" }
        buildoptions { "-ggdb" }
