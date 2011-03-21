#ifndef RESOURCE_H
#define RESOURCE_H

#include<string>

/**
 * @file resources/resource.h
 * @author Juha Sinkkonen
 *
 */


class Resource
{
    public:
        Resource();
        virtual ~Resource();

        virtual void setNeeded(bool need) = 0;
        virtual bool getNeeded() = 0;
        virtual void release() = 0;
        virtual void load(std::string fileName) = 0;

    protected:
        bool needed;
    private:
};

#endif // RESOURCE_H
