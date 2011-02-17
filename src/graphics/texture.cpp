#include "graphics/texture.h"
#include <algorithm> // needed for transform

Texture::Texture()
{
    glGenTextures( 1, &textureHandle );
    filtersSetManually = false;
    wrapModesSetManually = false;
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

    // TODO: put this in a separate function

    const size_t scanlineSize = tmp->pitch;
    const int numSwaps = tmp->h / 2;

    char* buffer = new char[scanlineSize];
    char* top = (char*)tmp->pixels;
    char* bottom = top + (tmp->h - 1) * scanlineSize;

    // swap scanlines vertically
    for (int i = 0; i < numSwaps; ++i)
    {
        ::memcpy(buffer, top, scanlineSize);
        ::memcpy(top, bottom, scanlineSize);
        ::memcpy(bottom, buffer, scanlineSize);

        top += scanlineSize;
        bottom -= scanlineSize;
    }

    delete [] buffer;

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
            SDL_FreeSurface(tmp);

            return false;
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

    /**
     * set GL_REPEAT as the default wrap mode
     */
    if( !wrapModesSetManually )
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
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

void Texture::setFilters( Texture::TextureFilter minfilter,
                                 Texture::TextureFilter magfilter )
{
    bindTexture();

    GLenum min = resolveFilter(minfilter);
    GLenum mag = resolveFilter(magfilter);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag );

    filtersSetManually = true;
}

void Texture::setWrapModes( Texture::WrapMode wrap_s, Texture::WrapMode wrap_t )
{
    bindTexture();

    GLenum s = resolveWrapMode( wrap_s );
    GLenum t = resolveWrapMode( wrap_t );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t );

    wrapModesSetManually = true;
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

GLenum Texture::resolveWrapMode( Texture::WrapMode wrapmode )
{
    switch( wrapmode )
    {
        case WRAP_REPEAT:
            return GL_REPEAT;
        break;

        case WRAP_CLAMP:
            return GL_CLAMP;
        break;

        case WRAP_CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        break;

        case WRAP_CLAMP_TO_BORDER:
            return GL_CLAMP_TO_BORDER;
        break;

        default:
            return GL_REPEAT;
        break;
    }
}

