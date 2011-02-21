/**
 * @file sound/mixer.h
 * @author Juhani Alanko
 */

#ifndef MIXER_H
#define MIXER_H

#include <SDL/SDL_mixer.h>
#include <iostream>
#include <vector>

/**
 * Enumerations for chunk and music 'sound types', used internally
 */
enum
{
    MIXER_SOUNDTYPE_CHUNK,
    MIXER_SOUNDTYPE_MUSIC
};

/**
 * A struct for storing chunk and music data
 */
struct AudioData
{
    char*           filename;
    std::string     friendlyname;
    int             channel; // needed for chunks
    Uint16          type;
    void*           data_p;
};

/**
 * An interface class for sdl_mixer
 */
class Mixer
{
public:
    /**
     * Constructor.
     */
    Mixer();

    /**
     * Destructor.
     */
    virtual ~Mixer();

    /**
     * Initialises the audio engine with custom values
     * @param frequency sampling frequency in samples per second
     * @param format sample format
     * @param channels number of output channels, 1 = mono, 2 = stereo etc.
     * @param chunksize size of sample buffer
     * @return bool true if succeeded, false otherwise
     */
    bool init( int frequency, Uint16 format, int channels, int chunksize );

    /**
     * Close the audio engine and clean up.
     */
    void close();

    /**
     * Loads an audio chunk, in other words a sound effect, into the audio engine.
     * Supports multiple audio formats.
     * Avoid using large files, use loadMusic for music.
     * @param filename the name of the sound file
     * @param chunkname a name for the sound effect, needed for actual playback
     * @return int -1 if failed, 0 if succeeded
     */
    int loadChunk( char* filename, std::string friendlyname );

    /**
     * Loads a music file into the engine. Supports multiple audio formats.
     * @param filename the name of the music file
     * @param songname a name for the music piece, needed for actual playback
     * @return int -1 if failed, 0 if succeeded
     */
    int loadMusic( char* filename, std::string friendlyname );

    /**
     * Plays a sound effect.
     * @param name the user-specified name of the sound effect that is to be played, assigned in loadChunk()
     * @param loops the number of loops, -1 for infinite loop
     */
    void playChunk( std::string name, int loops );

    /**
     * Plays music.
     * @param name the user-specified name of the piece of music that is to be played, assigned in loadChunk()
     */
    void playMusic( std::string name );

    /**
     * Stops music playback.
     */
    void stopMusic();

    /**
     * Tells if music is playing or not.
     */
    inline bool isMusicPlaying() {  return (Mix_PlayingMusic() ? true : false); }

private:
    /**
     * Frees the loaded sounds and music
     */
    void freeSounds();

    /**
     * Contains both chunk and music data
     */
    std::vector<AudioData*>     soundList_;
};

#endif // MIXER_H
