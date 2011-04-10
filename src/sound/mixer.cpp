/**
 * @file sound/mixer.cpp
 * @author Juhani Alanko
 */

#include "sound/mixer.h"

#include <SDL/SDL.h>


Mixer::Mixer()
:   lastPlayed("")
{
    //ctor
}


Mixer::~Mixer()
{
    //dtor
}


bool Mixer::init( int frequency, Uint16 format, int channels, int chunksize )
{
    SDL_InitSubSystem( SDL_INIT_AUDIO );

    Mix_Init( MIX_INIT_OGG );

    if( Mix_OpenAudio(  frequency,
                        format,
                        channels,
                        chunksize) < 0 )
    {
        return false;
    }

    return true;
}


void Mixer::close()
{
    stopMusic();

    freeSounds();
    Mix_CloseAudio();
    Mix_Quit();
}


int Mixer::loadChunk( const char* filename, std::string friendlyname )
{
    Mix_Chunk* chunk = Mix_LoadWAV( filename );
    if( chunk == NULL )
    {
        return -1;
    }

    AudioData* data;
    data = new AudioData();
    data->filename       = filename;
    data->friendlyname   = friendlyname;
    data->data_p         = chunk;

    soundList_.push_back(data);
    return 0;
}


int Mixer::loadMusic( const char* filename, std::string friendlyname )
{
    Mix_Music* music = Mix_LoadMUS( filename );
    if( music == NULL )
    {
        return -1;
    }

    AudioData* data;
    data = new AudioData();
    data->filename          = filename;
    data->friendlyname      = friendlyname;
    data->data_p            = music;
    data->type              = MIXER_SOUNDTYPE_MUSIC;

    soundList_.push_back(data);
    return 0;
}


void Mixer::playChunk( std::string name, int loops=0 )
{
    if( soundList_.size() < 1 )
    {
        return;
    }

    AudioData* data = NULL;
    bool foundData = false;

    for ( size_t i = 0; i < soundList_.size(); ++i )
    {
    	if( soundList_[i]->friendlyname.compare( name ) == 0 )
    	{
    	    data = soundList_[i];

    	    // check if the data exists
    	    if( data->data_p == NULL ) return;
            foundData = true;
    	}
    }

    if( !foundData ) return;

    // convert void pointer to more useful type
    Mix_PlayChannel( -1, (Mix_Chunk*)data->data_p, loops );
}


void Mixer::playMusic( std::string name )
{
    if( soundList_.size() < 1 )
    {
        return;
    }

    AudioData* data = NULL;
    bool foundData = false;

    for ( size_t i = 0; i < soundList_.size(); ++i )
    {
    	if( soundList_[i]->friendlyname.compare( name ) == 0 )
    	{
    	    data = soundList_[i];

    	    // check if the data exists
    	    if( data->data_p == NULL ) return;
    	    foundData = true;
    	}
    }

    if( !foundData ) return;

    Mix_Music* music = (Mix_Music*)data->data_p;

    // check if there already is music playing
    // if this is the case, fade out & in
    // else just start playing
    // TODO: real crossfading needs implementation of a multi-channel music mixer
    if( Mix_PlayingMusic() )
    {
        Mix_FadeOutMusic( 500 );
        while( Mix_FadingMusic() ) {}
        Mix_FadeInMusic( music, -1, 500 );
    }
    else
    {
        Mix_PlayMusic( music, -1 );
    }

    lastPlayed = name;
}


void Mixer::stopMusic()
{
    if( Mix_PlayingMusic() )
    {
        Mix_HaltMusic();
    }
}


void Mixer::freeSounds()
{
    for ( size_t i=0; i < soundList_.size(); ++i )
    {
        AudioData* data = soundList_[i];

        if( data->type == MIXER_SOUNDTYPE_MUSIC )
        {
            Mix_FreeMusic( (Mix_Music*)data->data_p );
        }
        else
        {
            Mix_FreeChunk( (Mix_Chunk*)data->data_p );
        }
    }

    soundList_.clear();
}

void Mixer::toggleMusic()
{
    if( Mix_PlayingMusic() )
    {
        stopMusic();
    }
    else
    {
        playMusic( lastPlayed );
    }
}
