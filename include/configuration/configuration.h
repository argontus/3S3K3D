#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

/**
 * @file configuration/configuration.h
 * @author Marko Silokunnas
 *
 * This class represents a set of properties that can read from a file or
 * saved to a file. The properties are saved to a std::map as strings. It is
 * up to the user of this class to perform needed type conversions before using
 * the properties.
 */
class Configuration
{
    public:
        Configuration();
        virtual ~Configuration();

        /**
         * Reads configuration from a file.
         *
         * @param filepath path to the configuration file
         * @return bool returns true if the file has been read succesfully.
         *              Returns false otherwise.
         */
        bool readConfiguration( std::string filepath );

        /**
         * Saves configuration to a file.
         *
         * @param filepath path to the file
         * @return bool Returns true if the the file has been written
         *              succesfully. Returns false otherwise.
         */
        bool saveConfiguration( std::string filepath );

        /**
         * Returns a reference to the std::map containing the properties.
         *
         * @return std::map& a reference to the property map.
         */
        std::map<std::string, std::string>& getProperties();

        // TODO: property query functions
        //
        // bool getBoolean(const std::string& name, bool default) const;
        //
        // int getInteger(const std::string& name, int default) const;
        //
        // const std::string getString(
        //     const std::string& name,
        //     const std::string& default) const;

    protected:

    private:
        std::map<std::string, std::string> properties;

        /**
         * A simple function to trim a string of whitespace
         */
        static inline std::string& trim( std::string &s )
        {
            return ltrim( rtrim(s) );
        }

        /**
         * Trim from the beginning of the string
         */
        static inline std::string& ltrim( std::string & s )
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
            return s;
        }

        /**
         * Trim from the end of the string
         */
        static inline std::string &rtrim(std::string &s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;
        }
};

#endif // CONFIGURATION_H
