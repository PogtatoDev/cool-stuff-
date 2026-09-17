#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>

#include <SDL2/SDL.h>
#include <shittyfb.h>

int main() {
    lua_State* lua = luaL_newstate();
    luaL_openlibs(lua);
    luaL_loadfile(lua, "test4.lua");
    luaL_call

    SDL_Init(SDL_INIT_VIDEO);
}
