solution "rana"
    configurations { "debug", "release" }
    platforms { "x64" }
    location ("./" .. _ACTION)
    configuration "debug"
        flags { "Symbols" }
		optimize "Off"
    configuration "release"
        optimize "Full"

project "rana.test"
    kind "ConsoleApp"
    language "C++"
    targetname "rana.test"
    includedirs { 
       "../include/rana",
       "/usr/local/Cellar/cxxtest/4.3"
    }
    files { 
       "../tests/*.hpp",
       "../tests/runner-autogen.cpp",
        "../include/rana/rana.hpp"
    }
    prebuildcommands { "/usr/local/Cellar/cxxtest/4.3/bin/cxxtestgen --runner=ErrorPrinter -o ../../tests/runner-autogen.cpp ../../tests/*.hpp" }
    flags { 
       "Unicode",
       "NoEditAndContinue",
       "NoManifest",
       "NoPCH",
       "NoBufferSecurityCheck"       
    }
    configuration "debug"
	targetdir "../bin"
    configuration "release"
        flags { "LinkTimeOptimization" }
        optimize "Full"
	targetdir "../bin"
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
    includedirs { 
       "../include/rana"
    }
    files { 
        "../benchmark/main.cpp",
        "../include/rana/rana.hpp"
    }
    flags { 
       "Unicode",
       "NoEditAndContinue",
       "NoManifest",
       "NoPCH",
       "NoBufferSecurityCheck"
    }
    configuration "debug"
	targetdir "../bin"
    configuration "release"
        flags { "LinkTimeOptimization" }
        optimize "Full"
	targetdir "../bin"
    configuration "not windows"
        buildoptions { 
            "-std=c++11",
            "-Wno-unknown-pragmas"
        }
    configuration { "not windows", "debug" }
        buildoptions { "-ggdb" }
