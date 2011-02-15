#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL/SDL.h> // needed for SDL_Surface
#include <SDL/SDL_image.h> // needed to load raw image data to a SDL_Surface
#include <iostream>

#include "opengl.h"

/**
 * @file graphics/texture.h
 * @author Marko Silokunnas
 */
class Texture
{
    /**
     * Supported texture filters.
     */
    enum TextureFilter {
        FILTER_NEAREST,
        FILTER_LINEAR,
        FILTER_NEAREST_MIPMAP_NEAREST,
        FILTER_NEAREST_MIPMAP_LINEAR,
        FILTER_LINEAR_MIPMAP_NEAREST,
        FILTER_LINEAR_MIPMAP_LINEAR
    };

    public:
        Texture();
        virtual ~Texture();

        /**
         * Loads the texture from a file on disk to memory
         *
         * @param imagepath path to the file to load
         * @return bool returns true if the file was read succesfully, false
         *              otherwise
         */
        bool loadImage( std::string imagepath );

        /**
         * Calls glBindTexture with textureHandle.
         */
        void bindTexture();

        /**
         * Sets texture filters
         *
         * @param minfilter minification filter
         * @param magfilter magnification filter
         */
        void setTextureFilters( TextureFilter minfilter,
                                TextureFilter magfilter );

        /**
         * Getter for textureHandler
         *
         * @return GLuing texture handle for the texture
         */
        inline GLuint getTextureHandler() const { return textureHandle; }

    protected:
    private:
        GLuint textureHandle;
        bool filtersSetManually;

        GLenum resolveFilter( Texture::TextureFilter filter );

};

#endif // TEXTURE_H
