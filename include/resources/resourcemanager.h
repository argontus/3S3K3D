#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <resources/textureloader.h>
#include <resources/resourcecontainer.h>

#include <SDL/SDL.h> // needed for SDL_Surface
#include <SDL/SDL_image.h> // needed to load raw image data to a SDL_Surface

class Resourcemanager
{
    public:
        Resourcemanager();
        virtual ~Resourcemanager();

        bool loadResources(std::vector<Resourcecontainer> resources);

        SDL_Surface* getTexture(std::string id);

    protected:
    private:
        Textureloader tLoader;

        std::vector<Resourcecontainer> textures;
};

#endif // RESOURCEMANAGER_H
