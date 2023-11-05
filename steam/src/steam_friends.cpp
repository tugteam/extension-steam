/** Interface to access information about individual users and interact with the
 * Steam Overlay.
 */

#if defined(DM_PLATFORM_OSX) || defined(DM_PLATFORM_WINDOWS) || defined(DM_PLATFORM_LINUX)

#include <dmsdk/sdk.h>
#include "steam_api.h"
#include "steam_types.h"

static ISteamFriends* g_SteamFriends;

int SteamFriends_Init(lua_State* L)
{
	g_SteamFriends = SteamFriends();
	return 0;
}

/** Returns the name of another user.
 * Same rules as GetFriendPersonaState() apply as to whether or not the user
 * knowns the name of the other user note that on first joining a lobby, chat
 * room or game server the local user will not known the name of the other users
 * automatically; that information will arrive asyncronously.
 * @name friends_get_friend_persona_name
 * @tparam friendId CSteamID
 * @treturn name String Name of user
 */
int SteamFriends_GetFriendPersonaName(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 1);
	CSteamID steamIDFriend = check_uint64(L, 1);
	const char* name = g_SteamFriends->GetFriendPersonaName(steamIDFriend);
	lua_pushstring(L, name);
	return 1;
}

/** Activates game overlay to store page for app.
 * @name friends_activate_game_overlay_to_store
 * @number app_id
 * @number flag EOverlayToStoreFlag
 */
int SteamFriends_ActivateGameOverlayToStore(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 0);
	AppId_t nAppID = luaL_checknumber(L, 1);
	EOverlayToStoreFlag eFlag;
	if (lua_isnil(L, 2)) {
		eFlag = k_EOverlayToStoreFlag_None;
	}
	else {
		eFlag = (EOverlayToStoreFlag)luaL_checknumber(L, 2);
	}
	g_SteamFriends->ActivateGameOverlayToStore(480, k_EOverlayToStoreFlag_None);
	//g_SteamFriends->ActivateGameOverlayToStore(nAppID, eFlag);
	return 0;
}

#endif
