#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

PlayerResetBoxing(playerid){
    PlayerEnterBoxing[playerid] = false;
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(newkeys & KEY_YES){
        if(IsPlayerInRangeOfPoint(playerid, 3.0, -2051.5498,-481.3043,38.7344)){
            new Float:hp;
            GetPlayerHealth(playerid, hp);
            if(hp >= 100){
                PlayerEnterBoxing[playerid] = true;
                SetPlayerPos(playerid, -1424.1720,929.5659,1036.4000);
                SetPlayerFacingAngle(playerid, 355.3697);
                SetPlayerInterior(playerid, 15);
                SetPlayerVirtualWorld(playerid, 1);
                SendClientMessage(playerid, -1, "- คุณได้เข้ามาในสนาม Boxing เรียบร้อยแล้ว");
            }
        }
        else if(IsPlayerInRangeOfPoint(playerid, 3.0, -1424.1720,929.5659,1036.4000)){
            PlayerEnterBoxing[playerid] = false;
            SetPlayerPos(playerid, -2051.5498,-481.3043,38.7344);
            SetPlayerFacingAngle(playerid, 355.3697);
            SetPlayerInterior(playerid, 0);
            SetPlayerVirtualWorld(playerid, 0);
            SendClientMessage(playerid, -1, "- คุณได้ออกจากสนาม Boxing แล้ว");
        }
    }
    return 1;
}

SetPlayerSpawnBoxing(playerid){
    new type = jdzrandom(1,3);
    if(type == 1){
        PlayerEnterBoxing[playerid] = true;
        SetSpawnInfo(playerid, NO_TEAM, PlayerData[playerid][pSkin], -1430.8342,936.7032,1036.5114, 356.0874, 0, 0, 0, 0, 0, 0);
        SetPlayerPos(playerid, -1430.8342,936.7032,1036.5114);
        SetPlayerFacingAngle(playerid, 356.0874);
        SetPlayerInterior(playerid, 15);
        SetPlayerVirtualWorld(playerid, 1);
    }
    if(type == 2){
        PlayerEnterBoxing[playerid] = true;
        SetSpawnInfo(playerid, NO_TEAM, PlayerData[playerid][pSkin], -1448.1876,939.1326,1036.5829, 345.0580, 0, 0, 0, 0, 0, 0);
        SetPlayerPos(playerid, -1448.1876,939.1326,1036.5829);
        SetPlayerFacingAngle(playerid, 345.0580);
        SetPlayerInterior(playerid, 15);
        SetPlayerVirtualWorld(playerid, 1);
    }
    if(type == 3){
        PlayerEnterBoxing[playerid] = true;
        SetSpawnInfo(playerid, NO_TEAM, PlayerData[playerid][pSkin], -1470.8572,946.7859,1036.7600, 335.6580, 0, 0, 0, 0, 0, 0);
        SetPlayerPos(playerid, -1470.8572,946.7859,1036.7600);
        SetPlayerFacingAngle(playerid, 335.6580);
        SetPlayerInterior(playerid, 15);
        SetPlayerVirtualWorld(playerid, 1);
    }
    return 1;
}