#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(!LoggedIn[playerid]) return 1;
    if(newkeys & KEY_NO){
        if(PlayerData[playerid][pMyWeapon][2] != 0){
            if(GetPlayerWeapon(playerid) == PlayerData[playerid][pMyWeapon][2]){
                OnPlayerStoreWeapon3(playerid, PlayerData[playerid][pMyWeapon][2]);
            }
        }
    }
    return 1;
}