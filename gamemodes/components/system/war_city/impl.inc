#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetPlayerWarCity(playerid){
    PlayerEnterWarCity[playerid] = 0;
    PlayerLastPositionWarCity[playerid][0] = 0.0;
    PlayerLastPositionWarCity[playerid][1] = 0.0;
    PlayerLastPositionWarCity[playerid][2] = 0.0;
    PlayerLastPositionWarCity[playerid][3] = 0.0;
    PlayerLastIntWarCity[playerid] = 0;
    PlayerLastWorldWarCity[playerid] = 0;
    PlayerDelayWarCity[playerid] = 0;
    PlayerIsHoldingWarCity[playerid] = false;
    return 1;
}

ResetWarCity(){
    foreach(new i : Player) if(LoggedIn[i]){
        if(PlayerEnterWarCity[i] > 0){
            SetPlayerPosEx(i, PlayerLastPositionWarCity[i][0], PlayerLastPositionWarCity[i][1], PlayerLastPositionWarCity[i][2], PlayerLastIntWarCity[i], PlayerLastWorldWarCity[i]);
            SetPlayerFacingAngle(i, PlayerLastPositionWarCity[i][3]);
            PlayerEnterWarCity[i] = 0;
            PlayerIsHoldingWarCity[i] = false;
            DisablePlayerCheckpoint(i);
        }
    }

    if(openWarLS){
        openWarLS = false;
        gangHoldingWarLS = -1;
        gangHoldingWarLSBy = INVALID_PLAYER_ID;
        gangHoldingWarLS_Time = 0;
    }

    if(openWarSF){
        openWarSF = false;
        gangHoldingWarSF = -1;
        gangHoldingWarSFBy = INVALID_PLAYER_ID;
        gangHoldingWarSF_Time = 0;
    }
    return 1;
}

hook OnGameModeInit(){
    openWarText3D = CreateDynamic3DTextLabel("[จุดยึดวอเมือง]\nกด 'Y' เพื่อทำการยึด", COLOR_RED, -1420.6829,1619.2101,1052.5313, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, WAR_CITY_INT, WAR_CITY_INT);
    CreateDynamicPickup(19132, 23, -1420.6829,1619.2101,1052.5313, WAR_CITY_INT, WAR_CITY_INT);
    return 1;
}

hook OnPlayerDeath(playerid){
    if(PlayerEnterWarCity[playerid] > 0){
        if(gangHoldingWarLSBy == playerid){
            SendClientMessageToAllEx(COLOR_RED, "[WAR-LS]: '%s' จากแก๊ง '%s' ที่กำลังยึดวอเมือง 'LS' อยู่ได้ตายแล้วทำให้การยึดวอเมืองถูกยกเลิก", ReturnRoleplayName(playerid), GetGroupName(PlayerData[playerid][pGroup]));
            gangHoldingWarLSBy = INVALID_PLAYER_ID;
            gangHoldingWarLS_Time = 0;
            gangHoldingWarLS = -1;
        }

        if(gangHoldingWarSFBy == playerid){
            SendClientMessageToAllEx(COLOR_RED, "[WAR-SF]: '%s' จากแก๊ง '%s' ที่กำลังยึดวอเมือง 'SF' อยู่ได้ตายแล้วทำให้การยึดวอเมืองถูกยกเลิก", ReturnRoleplayName(playerid), GetGroupName(PlayerData[playerid][pGroup]));
            gangHoldingWarSFBy = INVALID_PLAYER_ID;
            gangHoldingWarSF_Time = 0;
            gangHoldingWarSF = -1;
        }
        PlayerIsHoldingWarCity[playerid] = false;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(LoggedIn[playerid]){
        if(newkeys & KEY_YES){
            if(PlayerEnterWarCity[playerid] > 0 && PlayerData[playerid][pGroup] != -1){
                if(GetGroupType(playerid) == GROUP_GANG && !PlayerIsHoldingWarCity[playerid] && PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]-1){
                    if(IsPlayerInRangeOfPoint(playerid, 3.5, -1420.6829,1619.2101,1052.5313)){
                        if(PlayerEnterWarCity[playerid] == 1){
                            if(gangHoldingWarLS == -1 && gangHoldingWarLSBy == INVALID_PLAYER_ID){
                                gangHoldingWarLS = PlayerData[playerid][pGroup];
                                gangHoldingWarLSBy = playerid;
                                SendClientMessageToAllEx(COLOR_RED, "[WAR-LS]: แก๊ง '%s' กำลังทำการยึดวอเมือง 'LS' นำโดย '%s'", GetGroupName(PlayerData[playerid][pGroup]), ReturnRoleplayName(playerid));
                                gangHoldingWarLS_Time = 0;
                                SetPlayerHoldingWarCity(playerid);
                            }
                        } else if(PlayerEnterWarCity[playerid] == 2){
                            if(gangHoldingWarSF == -1 && gangHoldingWarSFBy == INVALID_PLAYER_ID){
                                gangHoldingWarSF = PlayerData[playerid][pGroup];
                                gangHoldingWarSFBy = playerid;
                                SendClientMessageToAllEx(COLOR_RED, "[WAR-SF]: แก๊ง '%s' กำลังทำการยึดวอเมือง 'SF' นำโดย '%s'", GetGroupName(PlayerData[playerid][pGroup]), ReturnRoleplayName(playerid));
                                gangHoldingWarSF_Time = 0;
                                SetPlayerHoldingWarCity(playerid);
                            }
                        }   
                    }
                }
            }
        }
    }
    return 1;
}

SetPlayerHoldingWarCity(playerid){
    TogglePlayerControllable(playerid, 0);
    CreatePlayerProgressbar_Job(playerid, 0xFF2828AA, ServerData[ServerWarCityTime]);
    PlayerIsHoldingWarCity[playerid] = true;
    ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.1,1,0,0,0,0,1);
    return 1;
}

SetPlayerHoldingWarCity_Finish(playerid){
    TogglePlayerControllable(playerid, 1);
    PlayerIsHoldingWarCity[playerid] = false;
    ClearAnimations(playerid);
    DestroyPlayerProgressbar_Job(playerid);
    return 1;
}

task ShowGangHoldWar[1800000](){
    if(gangHoldLS > -1){
        SendClientMessageToAllEx(0xFFA728FF, "[WAR-LS]: ขณะนี้แก๊ง '%s' กำลังยึดเมือง LS อยู่ในขณะนี้...", GetGroupName(gangHoldLS));
    }

    if(gangHoldSF > -1){
        SendClientMessageToAllEx(0xCAFF31FF, "[WAR-SF]: ขณะนี้แก๊ง '%s' กำลังยึดเมือง SF อยู่ในขณะนี้...", GetGroupName(gangHoldSF));
    }
}

task UpdateWarCity[1000](){
    new string[128];
    if(gangHoldingWarLS != -1 && gangHoldingWarLSBy != INVALID_PLAYER_ID){
        if(gangHoldingWarLS_Time < ServerData[ServerWarCityTime]){
            gangHoldingWarLS_Time++;
            SetPlayerProgressBarValue(gangHoldingWarLSBy, ProgressbarJob[gangHoldingWarLSBy], gangHoldingWarLS_Time);
            format(string,sizeof(string),"Holding War City (LS)... (%d)", gangHoldingWarLS_Time);
            PlayerTextDrawSetString(gangHoldingWarLSBy, PlayerTextDrawJob[gangHoldingWarLSBy], string);
        } else if(gangHoldingWarLS_Time >= ServerData[ServerWarCityTime]){
            gangHoldLS = gangHoldingWarLSBy;
            SendClientMessageToAllEx(COLOR_RED, "[WAR-LS]: แก๊ง '%s' ได้ทำการยึดวอเมือง 'LS' สำเร็จ นำโดย '%s'", GetGroupName(gangHoldingWarLS), ReturnRoleplayName(gangHoldingWarLSBy));
            SetPlayerHoldingWarCity_Finish(gangHoldingWarLSBy);
            ResetWarCity();
        }
    }

    if(gangHoldingWarSF != -1 && gangHoldingWarSFBy != INVALID_PLAYER_ID){
        if(gangHoldingWarSF_Time < ServerData[ServerWarCityTime]){
            gangHoldingWarSF_Time++;
            SetPlayerProgressBarValue(gangHoldingWarSFBy, ProgressbarJob[gangHoldingWarSFBy], gangHoldingWarSF_Time);
            format(string,sizeof(string),"Holding War City (SF)... (%d)", gangHoldingWarSF_Time);
            PlayerTextDrawSetString(gangHoldingWarSFBy, PlayerTextDrawJob[gangHoldingWarSFBy], string);
        } else if(gangHoldingWarSF_Time >= ServerData[ServerWarCityTime]){
            gangHoldSF = gangHoldingWarSF;
            SendClientMessageToAllEx(COLOR_RED, "[WAR-SF]: แก๊ง '%s' ได้ทำการยึดวอเมือง 'SF' สำเร็จ นำโดย '%s'", GetGroupName(gangHoldingWarSF), ReturnRoleplayName(gangHoldingWarSFBy));
            SetPlayerHoldingWarCity_Finish(gangHoldingWarLSBy);
            ResetWarCity();
        }
    }
}

ptask UpdateFindHoldingWarCity[1000](playerid){
    if(PlayerDelayWarCity[playerid] > 0) PlayerDelayWarCity[playerid]--;
    if(gangHoldingWarLS != -1 && gangHoldingWarLSBy != INVALID_PLAYER_ID){
        if(gangHoldingWarLS_Time < ServerData[ServerWarCityTime]){
            new Float:x, Float:y, Float:z;
            GetPlayerPos(gangHoldingWarLSBy, x, y, z);
            SetPlayerCheckpoint(playerid, x, y, z, 5.0);
        }
        else{
            DisablePlayerCheckpoint(playerid);
        }
    }

    if(gangHoldingWarSF != -1 && gangHoldingWarSFBy != INVALID_PLAYER_ID){
        if(gangHoldingWarSF_Time < ServerData[ServerWarCityTime]){
            new Float:x, Float:y, Float:z;
            GetPlayerPos(gangHoldingWarSFBy, x, y, z);
            SetPlayerCheckpoint(playerid, x, y, z, 5.0);
        }
        else{
            DisablePlayerCheckpoint(playerid);
        }
    }
}

CMD:openwarls(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new string[128];
    if(!openWarLS){
        openWarLS = true;
        format(string, sizeof string, "[จุดยึดวอเมือง 'LS']\nกด 'Y' เพื่อทำการยึด");
        UpdateDynamic3DTextLabelText(openWarText3D, COLOR_RED, string);
        SendClientMessageToAll(COLOR_RED, "[WAR-LS]: วอเมือง 'LS' ได้ทำการเปิดแล้ว ('/warls [1-4]')");
    } else {
        ResetWarCity();
        SendClientMessageToAll(COLOR_RED, "[WAR-LS]: วอเมือง 'LS' ได้ทำการปิดแล้ว");
    }
    return 1;
}

CMD:openwarsf(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new string[128];
    if(!openWarSF){
        openWarSF = true;
        format(string, sizeof string, "[จุดยึดวอเมือง 'SF']\nกด 'Y' เพื่อทำการยึด");
        UpdateDynamic3DTextLabelText(openWarText3D, COLOR_RED, string);
        SendClientMessageToAll(COLOR_RED, "[WAR-SF]: วอเมือง 'SF' ได้ทำการเปิดแล้ว ('/warsf [1-4]')");
    } else {
        ResetWarCity();
        SendClientMessageToAll(COLOR_RED, "[WAR-SF]: วอเมือง 'SF' ได้ทำการปิดแล้ว");
    }
    return 1;
}

CMD:warls(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    new spawnpoint;
    if(sscanf(params, "d", spawnpoint)) return SystemMsg(playerid, "/warls [1-4]");
    if(spawnpoint < 1 || spawnpoint > 4) return ErrorMsg(playerid, "กรุณาเลือกจุดเกิดเฉพาะ 1-4 เท่านั้น");
    if(!openWarLS) return ErrorMsg(playerid, "วอเมือง LS ยังไม่เปิด");
    if(GetGroupType(playerid) != GROUP_GANG) return ErrorMsg(playerid, "เล่นได้เฉพาะกลุ่มแก๊งเท่านั้น");
    if(PlayerDelayWarCity[playerid] > 0) return SendClientMessageEx(playerid, COLOR_RED, "คุณต้องรออีก %d วินาทีเพื่อที่จะเข้าเล่นได้อีกครั้ง", PlayerDelayWarCity[playerid]);
    if(PlayerEnterWarCity[playerid] == 0){

        new Float:x, Float:y, Float:z, Float:a;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);

        PlayerLastPositionWarCity[playerid][0] = x;
        PlayerLastPositionWarCity[playerid][1] = y;
        PlayerLastPositionWarCity[playerid][2] = z;
        PlayerLastPositionWarCity[playerid][3] = a;
        PlayerLastIntWarCity[playerid] = GetPlayerInterior(playerid);
        PlayerLastWorldWarCity[playerid] = GetPlayerVirtualWorld(playerid);

        if(spawnpoint == 1) {
            SetPlayerPosEx(playerid, PlayerSpawnPointWarCity[0][0], PlayerSpawnPointWarCity[0][1], PlayerSpawnPointWarCity[0][2], WAR_CITY_INT, WAR_CITY_INT);
            SetPlayerFacingAngle(playerid, PlayerSpawnPointWarCity[0][3]);
        } else if(spawnpoint == 2) {
            SetPlayerPosEx(playerid, PlayerSpawnPointWarCity[1][0], PlayerSpawnPointWarCity[1][1], PlayerSpawnPointWarCity[1][2], WAR_CITY_INT, WAR_CITY_INT);
            SetPlayerFacingAngle(playerid, PlayerSpawnPointWarCity[1][3]);
        } else if(spawnpoint == 3) {
            SetPlayerPosEx(playerid, PlayerSpawnPointWarCity[2][0], PlayerSpawnPointWarCity[2][1], PlayerSpawnPointWarCity[2][2], WAR_CITY_INT, WAR_CITY_INT);
            SetPlayerFacingAngle(playerid, PlayerSpawnPointWarCity[2][3]);
        } else if(spawnpoint == 4) {
            SetPlayerPosEx(playerid, PlayerSpawnPointWarCity[3][0], PlayerSpawnPointWarCity[3][1], PlayerSpawnPointWarCity[3][2], WAR_CITY_INT, WAR_CITY_INT);
            SetPlayerFacingAngle(playerid, PlayerSpawnPointWarCity[3][3]);
        }
        PlayerEnterWarCity[playerid] = 1;
    }
    return 1;
}

CMD:warsf(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    new spawnpoint;
    if(sscanf(params, "d", spawnpoint)) return SystemMsg(playerid, "/warsf [1-4]");
    if(spawnpoint < 1 || spawnpoint > 4) return ErrorMsg(playerid, "กรุณาเลือกจุดเกิดเฉพาะ 1-4 เท่านั้น");
    if(!openWarSF) return ErrorMsg(playerid, "วอเมือง SF ยังไม่เปิด");
    if(PlayerDelayWarCity[playerid] > 0) return SendClientMessageEx(playerid, COLOR_RED, "คุณต้องรออีก %d วินาทีเพื่อที่จะเข้าเล่นได้อีกครั้ง", PlayerDelayWarCity[playerid]);
    if(GetGroupType(playerid) != GROUP_GANG) return ErrorMsg(playerid, "เล่นได้เฉพาะกลุ่มแก๊งเท่านั้น");
    if(PlayerEnterWarCity[playerid] == 0){
        new Float:x, Float:y, Float:z, Float:a;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);

        PlayerLastPositionWarCity[playerid][0] = x;
        PlayerLastPositionWarCity[playerid][1] = y;
        PlayerLastPositionWarCity[playerid][2] = z;
        PlayerLastPositionWarCity[playerid][3] = a;
        PlayerLastIntWarCity[playerid] = GetPlayerInterior(playerid);
        PlayerLastWorldWarCity[playerid] = GetPlayerVirtualWorld(playerid);

        if(spawnpoint == 1) {
            SetPlayerPosEx(playerid, PlayerSpawnPointWarCity[0][0], PlayerSpawnPointWarCity[0][1], PlayerSpawnPointWarCity[0][2], WAR_CITY_INT, WAR_CITY_INT);
            SetPlayerFacingAngle(playerid, PlayerSpawnPointWarCity[0][3]);
        } else if(spawnpoint == 2) {
            SetPlayerPosEx(playerid, PlayerSpawnPointWarCity[1][0], PlayerSpawnPointWarCity[1][1], PlayerSpawnPointWarCity[1][2], WAR_CITY_INT, WAR_CITY_INT);
            SetPlayerFacingAngle(playerid, PlayerSpawnPointWarCity[1][3]);
        } else if(spawnpoint == 3) {
            SetPlayerPosEx(playerid, PlayerSpawnPointWarCity[2][0], PlayerSpawnPointWarCity[2][1], PlayerSpawnPointWarCity[2][2], WAR_CITY_INT, WAR_CITY_INT);
            SetPlayerFacingAngle(playerid, PlayerSpawnPointWarCity[2][3]);
        } else if(spawnpoint == 4) {
            SetPlayerPosEx(playerid, PlayerSpawnPointWarCity[3][0], PlayerSpawnPointWarCity[3][1], PlayerSpawnPointWarCity[3][2], WAR_CITY_INT, WAR_CITY_INT);
            SetPlayerFacingAngle(playerid, PlayerSpawnPointWarCity[3][3]);
        }
        PlayerEnterWarCity[playerid] = 2;
    }
    return 1;
}