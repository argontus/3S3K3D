/**
 * @file graphics/resourcemanager.h
 * @author Marko Silokunnas
 */
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

/**
 * Template class for resource management. Knows how to retrieve resources
 * from it's inner resource list and add resources to it. It can also release
 * all resources owned by it.
 */
template <class T> class ResourceManager
{
    public:
        ResourceManager() { }

        /**
         * Loads a resource by specified by the parameter resource to a slot
         * named by the parameter name
         *
         * @param resource resource to load
         * @param resourceName name of the resource will be used as an index
         *                     for the resource
         * @return returns true on succesfull loading of a resouce, false
         *         otherwise.
         */

         bool loadResource( const std::string resourceName , T* resource )
         {
                /* sanity check */
                if( resource == NULL || resourceName == "" )
                    return false;

                return resources.insert( std::pair<std::string, T*>( resourceName, resource) ).second;
         }

        /**
         * Releases resource specified by the parameter
         *
         * @param resourceName name of the resource to release
         * @return returns true if release of the resource is succesfull, false
         *         otherwise.
         */
        bool releaseResource( const std::string resourceName )
        {
                typename std::map<std::string, T*>::iterator it = resources.find( resourceName );

                if( it == resources.end() )
                {
                    return false;
                }

                delete it->second;
                resources.erase( it );

                return true;
        }

        /**
         * Returns a pointer to a resource specified by the parameter
         *
         * @param resourceName name of the resource
         * @return returns a pointer to the resource if found, returns NULL
         *         otherwise
         */
        T* getResource( const std::string resourceName )
        {
                typename std::map<std::string, T*>::iterator it = resources.find( resourceName );
                if( it == resources.end() )
                {
                     return NULL;
                }

                return it->second;
        }

        /**
         * Frees all resources that are currently owned by the manager
         */
        void releaseResources()
        {
            typename std::map<std::string, T*>::iterator iter;

            for( iter = resources.begin(); iter != resources.end(); ++iter )
            {
                delete iter->second;
            }

            resources.clear();
        }

        /**
         * Calls releaseResources()
         */
        virtual ~ResourceManager()
        {
            releaseResources();
        }

    protected:
        std::map<std::string, T*> resources;
    private:
};

#endif // RESOURCEMANAGER_H
