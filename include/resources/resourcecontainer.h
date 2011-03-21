#ifndef RESOURCECONTAINER_H
#define RESOURCECONTAINER_H

#include <string>

/**
 * @file resources/resourcecontainer.h
 * @author Juha Sinkkonen
 *
 * Container for resources
 */

class Resourcecontainer
{
    public:
        Resourcecontainer();
        virtual ~Resourcecontainer();

        /**
         * Sets ID tag for resource
         *
         * @param newid ID of the resource
         */
        void setID(std::string newid);
        /**
         * Sets Type for resource
         *
         * @param newid Type of the resource
         */
        void setType(int newtype);
        /**
         * Sets Filename for resource
         *
         * @param newid Filename of the resource
         */
        void setFilename(std::string newname);

        /**
         * Getter for ID tag
         *
         * @return std::string ID tag of the resource
         */
        std::string getID();
        /**
         * Getter for Type
         *
         * @return int Type of the resource (0=Texture,1=Mesh,2=Sound)
         */
        int getType();
        /**
         * Getter for Filename
         *
         * @return std::string Filename of the resource
         */
        std::string getFilename();

    protected:
    private:
        std::string id;
        int type;
        std::string filename;
};

#endif // RESOURCECONTAINER_H
