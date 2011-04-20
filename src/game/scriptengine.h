#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <string>

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

class ScriptEngine
{
    public:
        ScriptEngine();
        virtual ~ScriptEngine();

        virtual void reportErrors( lua_State *L, int status );
        virtual void executeScript( std::string pathToScript );
        virtual void registerFunctions();

        static int testFunction( lua_State* L );
    protected:
        lua_State* L;

    private:
};

#endif // SCRIPTENGINE_H
