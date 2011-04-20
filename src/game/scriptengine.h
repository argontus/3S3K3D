#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <string>

#define LUA_BUILD_AS_DLL

extern "C"
{
#ifdef WIN32
#   include <lua/lua.h>
#   include <lua/lualib.h>
#   include <lua/lauxlib.h>
#else
#   include "lua.h"
#   include "lualib.h"
#   include "lauxlib.h"
#endif
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
