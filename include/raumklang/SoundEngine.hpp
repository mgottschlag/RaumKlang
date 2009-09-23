/*
Copyright (c) 2009, Mathias Gottschlag

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef _RAUMKLANG_SOUNDENGINE_HPP_INCLUDED_
#define _RAUMKLANG_SOUNDENGINE_HPP_INCLUDED_

#include "SoundDriver.hpp"
#include "SoundDevice.hpp"
#include "Logger.hpp"

#include <vector>

namespace rk
{
	class Listener;
	class Sound;
	class SoundSource;
	class StreamLoader;
	class SoundStream;
	class SoundRecorder;
	class DataSource;
	class SoundFormat;

	/**
	 * Central sound engine class.
	 */
	class SoundEngine
	{
		public:
			/**
			 * Returns a list with the supported drivers.
			 */
			static std::vector<SoundDriver> getSupportedDrivers();
			/**
			 * Returns a list with the available devices for a driver.
			 */
			static std::vector<SoundDevice> getDevices(SoundDriver driver = ESD_AutoDetect);
			/**
			 * Initializes the sound engine.
			 * @param driver Driver to use. The available drivers can be
			 * listed up with getSupportedDrivers().
			 * @param device Device to use. Can be an empty string for the
			 * default device.
			 */
			static SoundEngine *create(SoundDriver driver = ESD_AutoDetect,
				std::string device = "");

			/**
			 * Destroys the sound engine, stops playback and deletes all sounds
			 * and resources.
			 *
			 * Note that resources to which the user still has references are
			 * not deleted, but cannot be used any more after this.
			 */
			virtual void destroy() = 0;

			/**
			 * Returns the name of the currently used driver as a string. Can
			  for example be "OpenAL" for the OpenAL driver.
			 */
			virtual const char *getDriverName() = 0;

			/**
			 * Returns the listener of the sound engine.
			 */
			virtual Listener *getListener() = 0;

			/**
			 * Loads a sound source from a file.
			 */
			virtual SoundSource *getSource(std::string filename,
				bool reuse = true) = 0;
			/**
			 * Loads a sound source from a file with raw PCM sound data.
			 */
			virtual SoundSource *getSourcePCM(std::string filename,
				const SoundFormat &format) = 0;
			/**
			 * Loads a sound source from memory.
			 * @param name Name of the sound source. Has to contain the
			 * extension (e.g. .wav) for the sound format at the end of the
			 * string.
			 * @param data Data buffer to be used for the sound source.
			 * @param size Size of the data buffer.
			 */
			virtual SoundSource *getSource(std::string name, void *data,
				unsigned int size, bool reuse = true) = 0;
			/**
			 * Loads a sound source from raw PCM sound data.
			 * @param name Name of the sound source.
			 * @param data Data buffer to be used for the sound source.
			 * @param size Size of the data buffer.
			 * @param format Format of the PCM sound data
			 */
			virtual SoundSource *getSourcePCM(std::string name, void *data,
				unsigned int size, const SoundFormat &format) = 0;
			/**
			 * Loads a sound source from an arbitrary data source.
			 * @param name Name of the sound source. Has to contain the
			 * extension (e.g. .wav) for the sound format at the end of the
			 * string.
			 * @param source Data source to load the sound from.
			 */
			virtual SoundSource *getSource(std::string name,
				DataSource *source, bool reuse = true) = 0;
			/**
			 * Loads a sound source from raw PCM sound data.
			 * @param name Name of the sound source.
			 * @param source Data source to load the sound from.
			 * @param format Format of the PCM sound data
			 */
			virtual SoundSource *getSourcePCM(std::string name,
				DataSource *source, const SoundFormat &format) = 0;

			/**
			 * Plays a sound from an already loaded sound source in 2D. For
			 * memory management, reference counting is used: If the used does
			 * not add references by calling ReferenceCounted::grab() or using
			 * SharedPointer, the sound instance is deleted after the song has
			 * finished playing or the user has called Sound::stop().
			 *
			 * @param source Sound source to use for playback.
			 * @param looped Of set to true, the sound will be repeated until
			 * the user calls Sound::stop().
			 * @param paused If set to true, the sound starts paused and will
			 * not be played until the user calls Sound::setPaused(false).
			 * @return Pointer to the sound. 0, if the sound could not be
			 * played.
			 */
			virtual Sound *play2D(SoundSource *source, bool looped = false,
				bool paused = false) = 0;
			/**
			 * Plays a sound from a file in 2D. For memory management, reference
			 * counting is used: If the used does not add references by calling
			 * ReferenceCounted::grab() or using SharedPointer, the sound
			 * instance is deleted after the song has finished playing or the
			 * user has called Sound::stop().
			 *
			 * @param file Path to the sound file to be loaded.
			 * @param looped Of set to true, the sound will be repeated until
			 * the user calls Sound::stop().
			 * @param paused If set to true, the sound starts paused and will
			 * not be played until the user calls Sound::setPaused(false).
			 * @return Pointer to the sound. 0, if the sound could not be
			 * played.
			 */
			virtual Sound *play2D(std::string file, bool looped = false,
				bool paused = false) = 0;
			/**
			 * Plays a sound from an already loaded sound source in 3D. For
			 * memory management, reference counting is used: If the used does
			 * not add references by calling ReferenceCounted::grab() or using
			 * SharedPointer, the sound instance is deleted after the song has
			 * finished playing or the user has called Sound::stop().
			 *
			 * @param source Sound source to use for playback.
			 * @param looped Of set to true, the sound will be repeated until
			 * the user calls Sound::stop().
			 * @param paused If set to true, the sound starts paused and will
			 * not be played until the user calls Sound::setPaused(false).
			 * @return Pointer to the sound. 0, if the sound could not be
			 * played.
			 */
			virtual Sound *play3D(SoundSource *source, bool looped = false,
				bool paused = false) = 0;
			/**
			 * Plays a sound from a file in 3D. For memory management, reference
			 * counting is used: If the used does not add references by calling
			 * ReferenceCounted::grab() or using SharedPointer, the sound
			 * instance is deleted after the song has finished playing or the
			 * user has called Sound::stop().
			 *
			 * @param file Path to the sound file to be loaded.
			 * @param looped Of set to true, the sound will be repeated until
			 * the user calls Sound::stop().
			 * @param paused If set to true, the sound starts paused and will
			 * not be played until the user calls Sound::setPaused(false).
			 * @return Pointer to the sound. 0, if the sound could not be
			 * played.
			 */
			virtual Sound *play3D(std::string file, bool looped = false,
				bool paused = false) = 0;

			/**
			 * Sets the master volume of the sound engine.
			 */
			virtual void setVolume(float volume) = 0;
			/**
			 * Returns the master volume.
			 */
			virtual float getVolume() = 0;

			/**
			 * Pauses/resumes all currently active sounds.
			 */
			virtual void setAllPaused(bool paused) = 0;
			/**
			 * Stops all currently active (playing or paused) sounds.
			 */
			virtual void stopAll() = 0;

			/**
			 * Sets the logger used for all output from the sound engine. By
			 * default, a file logger logging to "RaumKlang.htm" is created,
			 * or text is logged to stdout if that file could not be opened.
			 */
			virtual void setLogger(Logger *logger);
			/**
			 * Returns the logger of the sound engine.
			 */
			virtual LoggerPointer getLogger();

			/**
			 * Returns a list with the devices which can be used to create a
			 * sound recorder with createSoundRecorder().
			 */
			virtual std::vector<SoundDevice> getRecorderDevices() = 0;
			/**
			 * Creates a sound recorder.
			 * @param device Device to be used for recording sound. Can be an
			 * empty string for the default device, or any id from the list
			 * returned by getRecorderDevices().
			 */
			virtual SoundRecorder *createSoundRecorder(std::string device = "") = 0;

			/**
			 * Registers a custom stream loader. This can be used to make the
			 * engine support more sound file formats.
			 */
			void registerStreamLoader(StreamLoader *loader);

			/**
			 * Function to update all sound streams and refill buffers. This
			 * must not be called by the user, instead it is called from a
			 * different thread running in the background.
			 */
			virtual bool update() = 0;

			virtual ~SoundEngine()
			{
			}
		protected:
			void startUpdateThread();

			void initStreamLoaders();
			SoundStream *getStream(std::string name, DataSource *source);

			LoggerPointer logger;
		private:
			std::vector<StreamLoader*> loaders;
	};
}

#endif
