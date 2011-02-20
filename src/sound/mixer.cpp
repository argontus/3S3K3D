/**
 * @file sound/mixer.cpp
 * @author Juhani Alanko
 */

#include "sound/mixer.h"

#include <SDL/SDL.h>


Mixer::Mixer()
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
    // TODO: hardcoded for OGG, might be a good idea to change this
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


int Mixer::loadChunk( std::string filename )
{
    Mix_Chunk* chunk = Mix_LoadWAV( (char*)filename.c_str() );
    if( chunk == NULL )
    {
        return -1;
    }

    chunkList_.push_back(chunk);

    // return the index of the loaded chunk
    return ( chunkList_.size() - 1 );
}


int Mixer::loadMusic( std::string filename )
{
    Mix_Music* music = Mix_LoadMUS( (char*)filename.c_str() );
    if( music == NULL )
    {
        return -1;
    }

    musicList_.push_back(music);

    // return the index of the loaded music object
    return ( musicList_.size() - 1);
}


int Mixer::playChunk( int id, int loops=0 )
{
    // sanity checks
    if( id < 0 || id >= (int)chunkList_.size() )
    {
        return -1;
    }

    if( chunkList_[id] == NULL )
    {
        return -1;
    }

    return Mix_PlayChannel( -1, chunkList_[id], loops );
}


void Mixer::playMusic( int id )
{
    // sanity checks
    if( id < 0 || id >= (int)musicList_.size() )
    {
        return;
    }

    if( musicList_[id] == NULL )
    {
        return;
    }

    Mix_Music* music = musicList_[id];

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
    // free chunks...
    for ( int i=0; i < (int)chunkList_.size(); ++i )
    {
        Mix_FreeChunk( chunkList_[i] );
    }

    chunkList_.clear();

    // ...and music
    for ( int i=0; i < (int)musicList_.size(); ++i )
    {
        Mix_FreeMusic( musicList_[i] );
    }

    musicList_.clear();
}
