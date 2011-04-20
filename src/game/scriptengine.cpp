#include "scriptengine.h"

#include <iostream>

ScriptEngine::ScriptEngine()
{
    // initialize lua
    L = lua_open();
    luaL_openlibs(L);
}

ScriptEngine::~ScriptEngine()
{
    lua_close(L);
}

void ScriptEngine::reportErrors( lua_State* L, int status )
{
    if( status != 0 )
    {
        std::cerr << "ERROR: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
}

void ScriptEngine::executeScript( std::string pathToScript )
{
    std::cerr << "Executing script: " << pathToScript << std::endl;
    int status = luaL_loadfile( L, pathToScript.c_str() );

    if( status == 0 )
    {
        status = lua_pcall( L, 0, LUA_MULTRET, 0 );
    }

    reportErrors(L, status);
}

void ScriptEngine::registerFunctions()
{
    lua_register( L, "testFunction", testFunction );
}

int ScriptEngine::testFunction( lua_State* L )
{
    std::cout << "in test function called from lua" << std::endl;

    int argc = lua_gettop(L);

    for( int i=0; i<argc; i++ )
    {
        std::cout << lua_tostring( L, i ) << std::endl;
    }
}
