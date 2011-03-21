#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <resources/textureloader.h>
#include <resources/resourcecontainer.h>

#include <SDL/SDL.h> // needed for SDL_Surface
#include <SDL/SDL_image.h> // needed to load raw image data to a SDL_Surface

/**
 * @file resources/resourcemanager.h
 * @author Juha Sinkkonen
 *
 * Handles the resource lists from the game
 */


class Resourcemanager
{
    public:
        Resourcemanager();
        virtual ~Resourcemanager();

        /**
         * Setter for textures needed tag
         *
         * @param resources List of resources that are needed
         */
        bool loadResources(std::vector<Resourcecontainer> resources);

        /**
         * Returns pointer to texture file
         *
         */
        SDL_Surface* getTexture(std::string id);

    protected:
    private:
        Textureloader tLoader;

        std::vector<Resourcecontainer> textures;
};

#endif // RESOURCEMANAGER_H
