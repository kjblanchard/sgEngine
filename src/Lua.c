#include "SDL3/SDL_filesystem.h"
#include <SDL3/SDL.h>
#include <Supergoon/Log.hpp>
#include <Supergoon/Lua.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>
#include <string.h>

static lua_State *_luaState;

void sgInitializeLua(void) {
  // _luaState = luaL_newstate();
  // if (_luaState == NULL) {
  //   sgLogCritical("Could not initialize Lua");
  //   return;
  // }
  // luaL_openlibs(_luaState);
  // const char *basePath = SDL_GetBasePath();
  // const char *path = "assets/lua/test.lua";
  // size_t size = strlen(basePath) + strlen(path) + 1;
  // char fullPath[size];
  // snprintf(fullPath, size, "%s%s", basePath, path);
  // if (luaL_dofile(_luaState, fullPath) != 0) {
  //   const char *luaError = lua_tostring(_luaState, -1);
  //   sgLogCritical("Lua error: %s", luaError);
  // }
  // lua_close(_luaState);
}
