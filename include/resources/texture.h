#ifndef TEXTURE_H
#define TEXTURE_H

#include <resources/resource.h>

#include <SDL/SDL.h> // needed for SDL_Surface
#include <SDL/SDL_image.h> // needed to load raw image data to a SDL_Surface

/**
 * @file resources/resourcecontainer.h
 * @author Juha Sinkkonen
 *
 * Container for  Texture
 */


class Texture : public Resource
{
    public:
        Texture();
        virtual ~Texture();

        /**
         * Setter for textures needed tag
         *
         * @param need Is texture needed
         */
        virtual void setNeeded(bool need);

        /**
         * Returns textures needed tag
         *
         */
        virtual bool getNeeded();

        /**
         * Releases texture from memory
         *
         */
        virtual void release();

        /**
         * Load given texture file to memory
         *
         * @param fileName Texture filename
         */
        virtual void load(std::string fileName);

        /**
         * Returns pointer to texture file
         *
         */
        SDL_Surface* getTexture();

    protected:
    private:
        SDL_Surface* lTexture;

};

#endif // TEXTURE_H
