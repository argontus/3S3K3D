#include "graphics/texture.h"
#include <algorithm> // needed for transform

Texture::Texture()
{
    glGenTextures( 1, &textureHandle );
    filtersSetManually = false;
}

Texture::~Texture()
{
    glDeleteTextures( 1, &textureHandle );
}

bool Texture::loadImage( std::string imagepath )
{
    SDL_Surface* tmp = NULL;

    tmp = IMG_Load( imagepath.c_str() );

    if( tmp  == NULL )
    {
        std::cerr << "Error while loading image: " << imagepath << std::endl;
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        return false;
    }

    GLint colorChannels = tmp->format->BytesPerPixel;
    GLenum textureFormat;

    switch( colorChannels )
    {
        case 4: // alpha channel
            if( tmp->format->Rmask == 0x000000ff )
                textureFormat = GL_RGBA;
            else
                textureFormat = GL_BGRA;
        break;

        case 3: // no alpha channel
            if( tmp->format->Rmask == 0x000000ff )
                textureFormat = GL_RGB;
            else
                textureFormat = GL_BGR;
        break;

        default:
            std::cerr << "Not a true color image... something will go wrong"
                      << std::endl;
        break;
    }

    bindTexture();
    /**
     * if filters aren't set yet, use linear filtering for minification and
     * magnificiation.
     */
    if( !filtersSetManually )
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }

    // copy the texture to the GPU
    glTexImage2D( GL_TEXTURE_2D, 0, colorChannels, tmp->w, tmp->h, 0,
                  textureFormat, GL_UNSIGNED_BYTE, tmp->pixels );

    // release the surface
    SDL_FreeSurface( tmp );

    return true;
}

void Texture::bindTexture()
{
    glBindTexture( GL_TEXTURE_2D, textureHandle );
}

void Texture::setTextureFilters( Texture::TextureFilter minfilter,
                                 Texture::TextureFilter magfilter )
{
    bindTexture();

    GLenum min = resolveFilter(minfilter);
    GLenum mag = resolveFilter(magfilter);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag );

    filtersSetManually = true;
}

GLenum Texture::resolveFilter( Texture::TextureFilter filter )
{
    switch( filter )
    {
        case FILTER_NEAREST:
            return GL_NEAREST;

        case FILTER_LINEAR:
            return GL_LINEAR;

        case FILTER_NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;

        case FILTER_NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;

        case FILTER_LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;

        case FILTER_LINEAR_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;

        default:
            return FILTER_NEAREST;
    }
}

