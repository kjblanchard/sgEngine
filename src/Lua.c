#include <Supergoon/Log.hpp>
#include <Supergoon/Lua.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

static lua_State *_luaState;

void sgInitializeLua(void) {
  _luaState = luaL_newstate();
  if (_luaState == NULL) {
    sgLogCritical("Could not initialize Lua");
    return;
  }
  luaL_openlibs(_luaState);
  const char *script = "print('Hello from Lua!')";
  luaL_dostring(_luaState, script);
  //  if (luaL_dostring(_luaState, script) != 0) {
  //    fprintf(stderr, "Error running Lua script: %s\n", lua_tostring(_luaState, -1));
  //    lua_pop(_luaState, 1); // Pop the error message from the stack
  //  }

  // Step 4: Close the Lua state
  lua_close(_luaState);
}
