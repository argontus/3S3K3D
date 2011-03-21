#include "resources/resourcemanager.h"


Resourcemanager::Resourcemanager()
{
    //ctor
}

Resourcemanager::~Resourcemanager()
{
    //dtor
}

bool Resourcemanager::loadResources(std::vector<Resourcecontainer> resources)
{
    unsigned int i;

    for(i=0;i<resources.size();i++)
    {
        switch(resources[i].getType())
        {
        case 0:

            textures.push_back(resources[i]);
            break;
        default:
            break;
        }
    }

    tLoader.loadTextures(textures);

    return true;
}

SDL_Surface* Resourcemanager::getTexture(std::string id)
{
    return tLoader.getTexture(id);
}
