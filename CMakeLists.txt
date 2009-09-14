
cmake_minimum_required(VERSION 2.6)
project(RaumKlang)

find_package(OpenAL)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter")

include_directories(include  ${OPENAL_INCLUDE_DIR})

# RaumKlang library

set(SRC
	src/OggVorbisLoader.cpp
	src/OggVorbisStream.cpp
	src/SoundEngine.cpp
	src/SoundRecorder.cpp
	src/SoundSource.cpp
	src/openal/ListenerOpenAL.cpp
	src/openal/SoundOpenAL.cpp
	src/openal/SoundEngineOpenAL.cpp
	src/openal/SoundSourceOpenAL.cpp
)

add_library(RaumKlang SHARED ${SRC})
target_link_libraries(RaumKlang openal alut ogg vorbis vorbisfile pthread)

# Simple test

add_executable(test1 tests/test1.cpp)
target_link_libraries(test1 RaumKlang)
