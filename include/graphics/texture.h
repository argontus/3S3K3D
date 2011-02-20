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
    public:
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

        enum WrapMode {
            WRAP_REPEAT,
            WRAP_CLAMP,
            WRAP_CLAMP_TO_EDGE,
            WRAP_CLAMP_TO_BORDER
        };

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
        void setFilters( TextureFilter minfilter,
                                TextureFilter magfilter );

        /**
         * Sets texture wrap modes
         */
        void setWrapModes( WrapMode wrap_s, WrapMode wrap_t );

        /**
         * Getter for textureHandle
         *
         * @return GLuing texture handle for the texture
         */
        inline GLuint getTextureHandle() const { return textureHandle; }

        /**
         * Generates mipmap for the texture
         */
        void generateMipmap();

        /**
         * Turns anisotropic filtering on for the texture.
         */
        void activateAnisotropicFiltering();

        /**
         * Disables anisotropic filtering ( sets anisotropy level to 1.0f ).
         */
        void disableAnisotropicFiltering();

    protected:
    private:
        GLuint textureHandle;
        bool filtersSetManually;
        bool wrapModesSetManually;

        GLenum resolveFilter( TextureFilter filter );
        GLenum resolveWrapMode( WrapMode wrapmode );
        /**
         * Checks whether or not anisotropic filtering is supported by the
         * driver.
         *
         * @return bool returns true if anisotropic filtering is supported,
         *              false otherwise.
         */
        bool isAnisotropicFilteringSupported();

        /**
         * Returns the maximum anisotropy supported by the driver.
         *
         * @return float maximum anisotropy supported by the driver. Returns a
         *               negative value if anisotropic filtering isn't supported
         */
        float getMaximumAnisotropy();

};

#endif // TEXTURE_H
