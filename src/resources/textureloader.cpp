#include "resources/textureloader.h"

Textureloader::Textureloader()
{
}

Textureloader::~Textureloader()
{
}

Texture* Textureloader::gettexture(std::string id)
{
    return loadedtextures.find(id)->second.gettexture();
}

bool Textureloader::loadtextures(std::vector<Resourceinfo> textures)
{
    for(std::map<std::string, Texturecontainer>::iterator ii=loadedtextures.begin(); ii!=loadedtextures.end(); ++ii)
   {
       (*ii).second.setNeeded(false);
   }

    unsigned int i;
    std::map<std::string, Texturecontainer>::iterator it;

    for(i=0;i<textures.size();i++)
    {
        it=loadedtextures.find(textures[i].getID());
        if(it!=loadedtextures.end())
        {
            (*it).second.setNeeded(true);
        }
        else if (it==loadedtextures.end())
        {
            Texturecontainer tmp;
            tmp.load(textures[i].getFilename());
            tmp.setNeeded(true);

            loadedtextures.insert ( std::pair<std::string, Texturecontainer>(textures[i].getID(),tmp));
        }
    }

   for(std::map<std::string, Texturecontainer>::iterator ii=loadedtextures.begin(); ii!=loadedtextures.end(); ++ii)
   {
       if(!(*ii).second.getNeeded())
       {
         (*ii).second.release();
         loadedtextures.erase(ii);
       }
   }


    return true;
}
