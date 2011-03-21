#include "resources/resourcecontainer.h"

Resourcecontainer::Resourcecontainer()
{
}

Resourcecontainer::~Resourcecontainer()
{
}

void Resourcecontainer::setID(std::string newid)
{
    id = newid;
}

void Resourcecontainer::setType(int newtype)
{
    type = newtype;
}

void Resourcecontainer::setFilename(std::string newname)
{
    filename = newname;
}

std::string Resourcecontainer::getID()
 {
     return id;
 }

int Resourcecontainer::getType()
 {
     return type;
 }

std::string Resourcecontainer::getFilename()
{
    return filename;
}
