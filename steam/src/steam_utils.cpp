#if defined(DM_PLATFORM_OSX) || defined(DM_PLATFORM_WINDOWS) || defined(DM_PLATFORM_LINUX)

#include <dmsdk/sdk.h>
#include "steam_api.h"

static ISteamUtils* g_SteamUtils;

extern "C" void __cdecl SteamAPIDebugTextHook(int nSeverity, const char *pchDebugText)
{
	if (nSeverity == 0)
	{
		dmLogInfo("%s", pchDebugText);
	}
	else
	{
		dmLogWarning("%s", pchDebugText);
	}
}

int SteamUtils_Init(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 0);
	g_SteamUtils = SteamUtils();
	g_SteamUtils->SetWarningMessageHook(&SteamAPIDebugTextHook);
	return 0;
}

/** Returns the appID of the current process.
 * @treturn Number app_id
 */
int SteamUtils_GetAppId(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 1);

	lua_pushnumber(L, g_SteamUtils->GetAppID());
	return 1;
}

/** Return the number of seconds since the user.
 * @treturn Number seconds
 */
int SteamUtils_GetSecondsSinceAppActive(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 1);

	lua_pushnumber(L, g_SteamUtils->GetSecondsSinceAppActive());
	return 1;
}

/** Returns true if currently running on the Steam Deck device.
 * @treturn Boolean running_on_steamdeck
 */
int SteamUtils_IsSteamRunningOnSteamDeck(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 1);

	lua_pushboolean(L, g_SteamUtils->IsSteamRunningOnSteamDeck());
	return 1;
}

#endif