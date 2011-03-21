#include "resources/textureloader.h"

Textureloader::Textureloader()
{
}

Textureloader::~Textureloader()
{
}

SDL_Surface* Textureloader::getTexture(std::string id)
{
    return loadedTextures.find(id)->second.getTexture();
}

bool Textureloader::loadTextures(std::vector<Resourcecontainer> textures)
{
    for(std::map<std::string, Texture>::iterator ii=loadedTextures.begin(); ii!=loadedTextures.end(); ++ii)
   {
       (*ii).second.setNeeded(false);
   }

    unsigned int i;
    std::map<std::string, Texture>::iterator it;

    for(i=0;i<textures.size();i++)
    {
        it=loadedTextures.find(textures[i].getID());
        if(it!=loadedTextures.end())
        {
            (*it).second.setNeeded(true);
        }
        else if (it==loadedTextures.end())
        {
            Texture tmp;
            tmp.load(textures[i].getFilename());
            tmp.setNeeded(true);

            loadedTextures.insert ( std::pair<std::string, Texture>(textures[i].getID(),tmp));
        }
    }

   for(std::map<std::string, Texture>::iterator ii=loadedTextures.begin(); ii!=loadedTextures.end(); ++ii)
   {
       if(!(*ii).second.getNeeded())
       {
         (*ii).second.release();
         loadedTextures.erase(ii);
       }
   }


    return true;
}
