#if defined(DM_PLATFORM_OSX) || defined(DM_PLATFORM_WINDOWS) || defined(DM_PLATFORM_LINUX)

#include <dmsdk/sdk.h>
#include "steam_api.h"
#include "steam_types.h"


static dmScript::LuaCallbackInfo* g_SteamListener;

void SteamListener_Invoke(int (*fn)(lua_State*, void*), void* data)
{
	if (!g_SteamListener)
	{
		dmLogWarning("Steam callback is not set");
		return;
	}

	if (!dmScript::IsCallbackValid(g_SteamListener))
	{
		dmLogWarning("Steam callback is not valid");
		g_SteamListener = 0;
		return;
	}

	if (!dmScript::SetupCallback(g_SteamListener))
	{
		dmLogWarning("Steam callback setup failed");
		dmScript::DestroyCallback(g_SteamListener);
		g_SteamListener = 0;
		return;
	}

	lua_State* L = dmScript::GetCallbackLuaContext(g_SteamListener);
	int num = (*fn)(L, data);
	int ret = lua_pcall(L, 1 + num, 0, 0);
	if (ret != 0)
	{
		lua_pop(L, 1);
	}
	dmScript::TeardownCallback(g_SteamListener);
}

void SteamListener_Destroy()
{
	if (g_SteamListener)
	{
		dmScript::DestroyCallback(g_SteamListener);
		g_SteamListener = 0;
	}
}

int SteamListener_Set(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 0);
	if (g_SteamListener)
	{
		dmScript::DestroyCallback(g_SteamListener);
		g_SteamListener = 0;
	}
	g_SteamListener = dmScript::CreateCallback(L, 1);
	return 0;
}


#endif
