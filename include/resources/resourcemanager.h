#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <resources/textureloader.h>
#include <resources/resourceinfo.h>

#include <graphics/texture.h>

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
         * Setter for texturecontainers needed tag
         *
         * @param resources List of resources that are needed
         */
        bool loadResources(std::vector<Resourceinfo> resources);

        /**
         * Returns pointer to texturecontainer file
         *
         */
        Texture* gettexture(std::string id);

    protected:
    private:
        Textureloader tLoader;

        std::vector<Resourceinfo> textures;
};

#endif // RESOURCEMANAGER_H
