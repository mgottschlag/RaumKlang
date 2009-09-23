
cmake_minimum_required(VERSION 2.6)
project(RaumKlang)

find_package(OpenAL)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter")

include_directories(include src ${OPENAL_INCLUDE_DIR})

# RaumKlang library

set(SRC
	src/ConsoleLogger.cpp
	src/FileLogger.cpp
	src/FileSource.cpp
	src/Logger.cpp
	src/MemorySource.cpp
	src/Mutex.cpp
	src/OggVorbisLoader.cpp
	src/OggVorbisStream.cpp
	src/PCMStream.cpp
	src/ScopedLock.cpp
	src/SoundEngine.cpp
	src/SoundSource.cpp
	src/WavLoader.cpp
	src/WavStream.cpp
	src/c/Sound.cpp
	src/c/SoundEngine.cpp
	src/openal/ListenerOpenAL.cpp
	src/openal/SoundOpenAL.cpp
	src/openal/SoundEngineOpenAL.cpp
	src/openal/SoundRecorderOpenAL.cpp
	src/openal/SoundSourceOpenAL.cpp
)

add_library(RaumKlang SHARED ${SRC})
target_link_libraries(RaumKlang openal ogg vorbis vorbisfile pthread)

# Simple test

add_executable(test1 tests/test1.cpp)
target_link_libraries(test1 RaumKlang)

# Tutorials

add_executable(01.QuickStart tutorials/01.QuickStart/01.QuickStart.cpp)
target_link_libraries(01.QuickStart RaumKlang)

add_executable(02.3DSound tutorials/02.3DSound/02.3DSound.cpp)
target_link_libraries(02.3DSound RaumKlang)

add_executable(06.C tutorials/06.C/06.C.c)
target_link_libraries(06.C RaumKlang)
