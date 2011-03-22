#include "resources/resourcemanager.h"


Resourcemanager::Resourcemanager()
{
    //ctor
}

Resourcemanager::~Resourcemanager()
{
    //dtor
}

bool Resourcemanager::loadResources(std::vector<Resourceinfo> resources)
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

    tLoader.loadtextures(textures);

    return true;
}

Texture* Resourcemanager::gettexture(std::string id)
{
    return tLoader.gettexture(id);
}
