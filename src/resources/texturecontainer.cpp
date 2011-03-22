#include "resources/texturecontainer.h"

Texturecontainer::Texturecontainer()
{
}

Texturecontainer::~Texturecontainer()
{
}

void Texturecontainer::setNeeded(bool need)
{
    needed = need;
}

bool Texturecontainer::getNeeded()
{
    return needed;
}

void Texturecontainer::release()
{
}

void Texturecontainer::load(std::string fileName)
{
    texture.loadImage(fileName);
}

Texture* Texturecontainer::gettexture()
{
    return &texture;
}
