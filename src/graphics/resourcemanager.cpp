#include "graphics/resourcemanager.h"
#include <utility> // needed for std::pair

template <class T>
ResourceManager<T>::ResourceManager()
{
    //ctor
}

template <class T>
bool ResourceManager<T>::loadResource( std::string resourceName,
                                       const T* resource )
{
    /* sanity check */
    if( resource == NULL || resourceName == "" )
        return false;

    std::pair<std::string, T*> tmp;
    tmp = resources.insert( std::pair<std::string, T*>( resourceName, resource) );

    /* check if resource by that name already exists */
    if( tmp.second == false )
        return false;

    return true;
}

template <class T>
bool ResourceManager<T>::releaseResource( const std::string resourceName )
{
    typename std::map<std::string, T*>::iterator it = resources.find( resourceName );

    if( it == resources.end() )
    {
        return false;
    }

    delete it->second;
    resources.erase( it );
}

template <class T>
T* ResourceManager<T>::getResource( const std::string resourceName )
{
    typename std::map<std::string, T*>::iterator it = resources.find( resourceName );
    if( it == resources.end() )
    {
         return NULL;
    }

    return it->second;
}

template <class T>
void ResourceManager<T>::releaseResources()
{
    typename std::map<std::string, T*>::iterator iter;

    for( iter = resources.begin(); iter != resources.end(); iter++ )
    {
        releaseResource( iter->first );
    }
}

template <class T>
ResourceManager<T>::~ResourceManager()
{
    releaseResources();
}
