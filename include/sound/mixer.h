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
     * @return int -1 if failed, otherwise the index of the added chunk (needed for playback later)
     */
    int loadChunk( std::string filename );

    /**
     * Loads a music file into the engine. Supports multiple audio formats.
     * @param filename the name of the music file
     * @param songname a name for the music piece, needed for actual playback
     * @return int -1 if failed, otherwise the index of the added song (needed for playback later)
     */
    int loadMusic( std::string filename );

    /**
     * Plays a sound effect.
     * @param id the id of the sound effect that is to be played, returned by loadMusic()
     * @param loops the number of loops, -1 for infinite loop
     * @return int the channel number assigned to playing the chunk, -1 on error
     */
    int playChunk( int id, int loops );

    /**
     * Plays music.
     * @param id the id of the piece of music that is to be played, returned by loadChunk()
     */
    void playMusic( int id );

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

    std::vector<Mix_Chunk*>     chunkList_;
    std::vector<Mix_Music*>     musicList_;
};

#endif // MIXER_H
