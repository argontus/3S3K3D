#include "resources/texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::setNeeded(bool need)
{
    needed = need;
}

bool Texture::getNeeded()
{
    return needed;
}

void Texture::release()
{
    SDL_FreeSurface( lTexture );
}

void Texture::load(std::string fileName)
{
    lTexture = IMG_Load( fileName.c_str() );
}

SDL_Surface* Texture::getTexture()
{
    return lTexture;
}
