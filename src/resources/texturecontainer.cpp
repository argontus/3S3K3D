#include "resources/texturecontainer.h"

texturecontainer::texturecontainer()
{
}

texturecontainer::~texturecontainer()
{
}

void texturecontainer::setNeeded(bool need)
{
    needed = need;
}

bool texturecontainer::getNeeded()
{
    return needed;
}

void texturecontainer::release()
{
    //TODO
}

void texturecontainer::load(std::string fileName)
{
    //TODO
}

texture* texturecontainer::gettexture()
{
    return &texture;
}
