#include "resources/resourceinfo.h"

Resourceinfo::Resourceinfo()
{
}

Resourceinfo::~Resourceinfo()
{
}

void Resourceinfo::setID(std::string newid)
{
    id = newid;
}

void Resourceinfo::setType(int newtype)
{
    type = newtype;
}

void Resourceinfo::setFilename(std::string newname)
{
    filename = newname;
}

std::string Resourceinfo::getID()
 {
     return id;
 }

int Resourceinfo::getType()
 {
     return type;
 }

std::string Resourceinfo::getFilename()
{
    return filename;
}
