#ifndef TEXTURECONTAINER_H
#define TEXTURECONTAINER_H

#include <resources/resource.h>

#include <graphics/texture.h>

/**
 * @file resources/resourcecontainer.h
 * @author Juha Sinkkonen
 *
 * Container for  texturecontainer
 */


class Texturecontainer : public Resource
{
    public:
        Texturecontainer();
        virtual ~Texturecontainer();

        /**
         * Setter for texturecontainers needed tag
         *
         * @param need Is texturecontainer needed
         */
        virtual void setNeeded(bool need);

        /**
         * Returns texturecontainers needed tag
         *
         */
        virtual bool getNeeded();

        /**
         * Releases texturecontainer from memory
         *
         */
        virtual void release();

        /**
         * Load given texture file to memory
         *
         * @param fileName texturecontainer filename
         */
        virtual void load(std::string fileName);

        /**
         * Returns pointer to texture file
         *
         */
        Texture* gettexture();

    protected:
    private:
        Texture texture;

};

#endif // texturecontainer_H
