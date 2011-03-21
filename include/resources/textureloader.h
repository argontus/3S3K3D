#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <resources/texture.h>
#include <resources/resourcecontainer.h>

#include <map>
#include <string>

#include<vector>
#include <SDL/SDL.h> // needed for SDL_Surface
#include <SDL/SDL_image.h> // needed to load raw image data to a SDL_Surface

/**
 * @file input/textureloader.h
 * @author Juha Sinkkonen
 *
 */

class Textureloader
{
    public:
        Textureloader();
        virtual ~Textureloader();

        /**
         * Load given textures to loaded textures map
         *
         * @param textures List of textures to be loaded
         */
        bool loadTextures(std::vector<Resourcecontainer> textures);

        /**
         * Returns pointer to wanted texture
         *
         * @param id ID tag of the wanted texture
         */
        SDL_Surface* getTexture(std::string id);

    protected:
    private:
        std::map<std::string, Texture> loadedTextures;
};

#endif // TEXTURELOADER_H
