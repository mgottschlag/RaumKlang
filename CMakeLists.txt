
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
