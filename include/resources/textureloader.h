#ifndef texturecontainerLOADER_H
#define texturecontainerLOADER_H

#include <resources/texturecontainer.h>
#include <resources/resourceinfo.h>

#include <graphics/texture.h>

#include <map>
#include <string>

#include<vector>


/**
 * @file input/textureloader.h
 * @author Juha Sinkkonen
 *
 * Keppps tarck of the texturecontaineres in memory
 *
 */

class Textureloader
{
    public:
        Textureloader();
        virtual ~Textureloader();

        /**
         * Load given texturecontainers to loaded texturecontainers map
         *
         * @param texturecontainers List of texturecontainers to be loaded
         */
        bool loadtextures(std::vector<Resourceinfo> textures);

        /**
         * Returns pointer to wanted texturecontainer
         *
         * @param id ID tag of the wanted texturecontainer
         */
        Texture* gettexture(std::string id);

    protected:
    private:
        std::map<std::string, texturecontainer> loadedtextures;
};

#endif // texturecontainerLOADER_H
