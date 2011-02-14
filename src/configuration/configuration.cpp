#include "configuration/configuration.h"

Configuration::Configuration()
{
    //ctor
}

Configuration::~Configuration()
{
    //dtor
}

bool Configuration::readConfiguration( std::string filepath )
{
    std::ifstream configFile( filepath.c_str() );
    std::string line;
    int linenum = 1;

    if( !configFile.is_open() )
    {
        std::cerr << "Couldn't open configuration file: "
                  << filepath << std::endl;
        return false;
    }

    while( configFile.good() )
    {
        std::string name;
        std::string value;

        getline( configFile, line );

        // omit comments and empty lines
        if( line[0] == '#' || line[0] == ' ' || line.length() == 0 )
            continue;

        size_t separatorIndex = line.find('=');

        if( separatorIndex == std::string::npos )
        {
            std::cout << "Error while parsing line: " << linenum << std::endl;
            continue;
        }

        name = line.substr( 0, separatorIndex );
        value = line.substr( separatorIndex+1, line.length() );

        // trim both the name and the value from whitespace
        name = trim(name);
        value = trim(value);

        std::pair<std::string, std::string> property;
        property.first = name;
        property.second = value;

        properties.insert(property);
        linenum++;
    }

    configFile.close();
    return true;
}

bool Configuration::saveConfiguration( std::string filepath )
{
    std::ofstream outputFile( filepath.c_str() );

    if( !outputFile.is_open() )
    {
        std::cerr << "Error while opening file: " << filepath << std::endl;
        return false;
    }

    std::map<std::string, std::string>::iterator iter;

    for( iter=properties.begin(); iter != properties.end(); iter++ )
    {
        std::string name = iter->first;
        std::string value = iter->second;

        name = trim(name);
        value = trim(value);

        outputFile << name << "=" << value << std::endl;
    }

    outputFile.close();
    return true;
}

std::map<std::string, std::string>& Configuration::getProperties()
{
    return properties;
}
