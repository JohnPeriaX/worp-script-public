#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetPlayer_WarFlag(playerid){
    PlayerEnterWarFlag[playerid] = false;
    GetPositionBeforeFlagWar[playerid][0] = 0.0;
    GetPositionBeforeFlagWar[playerid][1] = 0.0;
    GetPositionBeforeFlagWar[playerid][2] = 0.0;
    GetPositionBeforeFlagWar[playerid][3] = 0.0;
    GetIntBeforeFlagWar[playerid] = 0;
    GetWorldBeforeFlagWar[playerid] = 0;
    PlayerDelayFlagWar[playerid] = 0;
    PlayerGetFlag[playerid] = false;
    return 1;
}

hook OnGameModeInit(){
    WarFlagOpen = false;
    WarFlagTime = 0;
    return 1;
}

hook OnPlayerPickUpPickup(playerid, pickupid){
    if(!FlagDrill && IsValidPickup(FlagPickup) && FlagPickup != -1 && FlagPickup != -1){
        if(PlayerEnterWarFlag[playerid] && !PlayerGetFlag[playerid]){
            if(pickupid == FlagPickup){
                FlagDrill = true;
                if(IsValidPickup(FlagPickup) && FlagPickup != -1 && FlagPickup != -1) DestroyPickup(FlagPickup);
                FlagPickup = -1;
                PlayerGetFlag[playerid] = true;
                ClearAnimations(playerid);
                SetPlayerFlagObject(playerid);

                foreach(new i : Player){
                    if(!LoggedIn[i]) continue;
                    if(!PlayerEnterWarFlag[i]) continue;
                    SendClientMessageEx(i, 0xFF8300FF, "[วอชิงธง]: ผู้เล่น %s ได้ทำการยึดธงไปแล้วในขณะนี้...", ReturnRoleplayName(playerid));
                }   
            }
        }
    }
    return 1;    
}

SetPlayerFlagObject(playerid){
    SetPlayerAttachedObject(playerid,8,2614,1,0.083999,-0.120999,0.000000,0.000000,86.200065,0.000000,1.000000,1.000000,1.000000);
    return 1;
}

CMD:checkflag(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    foreach(new i : Player){
        if(!LoggedIn[i]) continue;
        if(!PlayerEnterWarFlag[i]) continue;
        if(PlayerGetFlag[i]){
            SendClientMessageEx(playerid, -1, "- ผู้เล่น %s(%d) กำลังถือธงอยู่ในขณะนี้", ReturnRoleplayName(i), i);
        }
    }
    return 1;
}

CMD:reflag(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    foreach(new i : Player){
        if(!LoggedIn[i]) continue;
        if(!PlayerEnterWarFlag[i]) continue;
        if(PlayerGetFlag[i]) PlayerGetFlag[i] = false;
    }
    FlagDrill = false;
    if(IsValidPickup(FlagPickup) && FlagPickup != -1) DestroyPickup(FlagPickup);
    FlagPickup = -1;
    FlagPickup = CreatePickup(2614, 2, -1053.6649,1058.2955,1341.3516, 1);
    return 1;
}

CMD:flagwar(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    if(!WarFlagOpen){
        OpenFlagWar();
    }
    else{
        CloseFlagWar();
    }
    return 1;
}

CloseFlagWar(){
    if(IsValidPickup(FlagPickup) && FlagPickup != -1) DestroyPickup(FlagPickup);
    FlagPickup = -1;
    WarFlagOpen = false;
    FlagDrill = false;
    WarFinish = false;
    WarFlagTime = 0;
    SendClientMessageToAll(0xFF7400FF, "[วอชิงธง]: {FFFFFF}ขณะนี้ 'วอชิงธง' ได้ทำการ 'ปิด' แล้ว");
    foreach(new i : Player){
        if(!LoggedIn[i]) continue;
        if(!PlayerEnterWarFlag[i]) continue;
        SetPlayerPos(i, GetPositionBeforeFlagWar[i][0], GetPositionBeforeFlagWar[i][1], GetPositionBeforeFlagWar[i][2]);
        SetPlayerFacingAngle(i, GetPositionBeforeFlagWar[i][3]);
        SetPlayerInterior(i, GetIntBeforeFlagWar[i]);
        SetPlayerVirtualWorld(i, GetWorldBeforeFlagWar[i]);

        if(PlayerGetFlag[i]){
            RemoveAttachedObject(i, 8);
        }

        ResetPlayer_WarFlag(i);
    }
    return 1;
}

OpenFlagWar(){
    if(IsValidPickup(FlagPickup) && FlagPickup != -1) DestroyPickup(FlagPickup);
    FlagPickup = -1;
    FlagPickup = CreatePickup(2614, 2, -1053.6649,1058.2955,1341.3516, 1);
    WarFlagTime = 1200;
    //WarFlagTime = 120;
    WarFlagOpen = true;
    SendClientMessageToAll(0xFF7400FF, "[วอชิงธง]: {FFFFFF}ขณะนี้ 'วอชิงธง' ได้ทำการ 'เปิด' แล้ว");
    SendClientMessageToAll(0xFF7400FF, "[วอชิงธง]: {FFFFFF}พิมพ์ '/warf' เพื่อเข้าเล่น");
    return 1;
}

CMD:checkwarflag(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    SendClientMessageEx(playerid, -1, "สถานะ: %d | เวลาวอ: %d", WarFlagOpen, WarFlagTime);
    return 1;
}

task TimerUpdateWar[1000](){
    if(WarFlagOpen && !WarFinish){
        if(WarFlagTime > 0) WarFlagTime--;
        else{
            WarFinish = true;
            foreach(new i : Player){
                if(!LoggedIn[i]) continue;
                if(!PlayerEnterWarFlag[i]) continue;
                if(PlayerGetFlag[i]){
                    GetPlayerRewardFlag(i);
                }
            }
            CloseFlagWar();
        }
    }
}

GetPlayerRewardFlag(playerid){
    new itemid = PlayerInventory_AddItem(playerid, "Wood", 19793, 100);
    new itemid2 = PlayerInventory_AddItem(playerid, "Ore", 19941, 100);
    new itemid3 = PlayerInventory_AddItem(playerid, "Gun Powder", 2057, 25);
    new itemid4 = PlayerInventory_AddItem(playerid, "Mixed Drug", 1577, 1);


    if(itemid == -1) ErrorMsg(playerid, "คุณมีช่องเก็บของไม่พอที่จะเก็บไม้");
    else SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้รับ ไม้ จำนวน 100 ชิ้น");
    if(itemid2 == -1) ErrorMsg(playerid, "คุณมีช่องเก็บของไม่พอที่จะเก็บเหล็ก");
    else SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้รับ เหล็ก จำนวน 100 ชิ้น");
    if(itemid3 == -1) ErrorMsg(playerid, "คุณมีช่องเก็บของไม่พอที่จะเก็บดินปืน");
    else SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้รับ ดินปืน จำนวน 25 ชิ้น");
    if(itemid4 == -1) ErrorMsg(playerid, "คุณมีช่องเก็บของไม่พอที่จะเก็บยาเกราะ");
    else SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้รับ ยาเกราะ จำนวน 1 ชิ้น");

    return 1;
}

CMD:warf(playerid, params[]){
    if(WarFlagOpen == false) {
        if(GetPlayerInterior(playerid) == 10 && GetPlayerVirtualWorld(playerid) >= 0 && GetPlayerVirtualWorld(playerid) <= 1){
            SetPlayerPosEx(playerid,1120.4299,-1378.5870,14.2879, 0, 0);
        }
        return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] วอชิงธงถูกปิดอยู่", "ตกลง", "");
    }
    if(IsPlayerInAnyVehicle(playerid)) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] คุณต้องไม่อยู่บนยานพาหนะใดๆ", "ตกลง", "");
    if(PlayerData[playerid][pInjured] || PlayerData[playerid][pInHospital]) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] คุณอยู่ในสถานะบาดเจ็บหรือกำลังนอนโรงพยาบาล", "ตกลง", "");
    if(PlayerDelayFlagWar[playerid] > 0) return SendClientMessageEx(playerid, COLOR_RED, "[!] คุณจะต้องรอเวลาอีก %d วินาที เพื่อที่จะเข้าเล่นอีกครั้ง", PlayerDelayFlagWar[playerid]);
    if(PlayerData[playerid][pMyWeapon][2] != 0) OnPlayerStoreWeapon3(playerid, PlayerData[playerid][pMyWeapon][2]);
    if(PlayerData[playerid][pMyWeapon][2] != 0) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] คุณจะต้องเก็บอาวุธของคุณก่อน", "ตกลง", "");
    if(PlayerData[playerid][pJail] != 0) return 1;
    if(PlayerData[playerid][pPlayerhour] < 5) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] คุณต้องมีชั่วโมงออนไลน์มากกว่า 5", "ตกลง", "");
    if(PlayerEnterBoxing[playerid]) return ErrorMsg(playerid, "คุณยังอยู่ในสนาม Boxing ออกจากสนามก่อน");

    if(!PlayerEnterWarFlag[playerid]){
        GetPlayerPos(playerid, GetPositionBeforeFlagWar[playerid][0], GetPositionBeforeFlagWar[playerid][1], GetPositionBeforeFlagWar[playerid][2]);
        GetIntBeforeFlagWar[playerid] = GetPlayerInterior(playerid);
        GetWorldBeforeFlagWar[playerid] = GetPlayerVirtualWorld(playerid);
        PlayerEnterWarFlag[playerid] = true;
        RandomSpawnWarFlag(playerid);
    }
    else{
        if(!PlayerGetFlag[playerid]){
            PlayerEnterWarFlag[playerid] = false;
            SetPlayerPos(playerid, GetPositionBeforeFlagWar[playerid][0], GetPositionBeforeFlagWar[playerid][1], GetPositionBeforeFlagWar[playerid][2]);
            SetPlayerFacingAngle(playerid, GetPositionBeforeFlagWar[playerid][3]);
            SetPlayerInterior(playerid, GetIntBeforeFlagWar[playerid]);
            SetPlayerVirtualWorld(playerid, GetWorldBeforeFlagWar[playerid]);
            ResetPlayer_WarFlag(playerid);
        }
    }
    return 1;
}

RandomSpawnWarFlag(playerid){
    new randomspawn = jdzrandom(1,2);
    if(randomspawn == 1){       
        SetPlayerPos(playerid, -973.9290,1061.1335,1345.6740);
        SetPlayerFacingAngle(playerid, 88.6447);
        SetPlayerInterior(playerid, 10);
        SetPlayerVirtualWorld(playerid, 1);
        SetCameraBehindPlayer(playerid);
        TogglePlayerControllable(playerid, 1);
    }
    else if(randomspawn == 2){
        SetPlayerPos(playerid, -1132.0879,1057.7367,1346.4127);
        SetPlayerFacingAngle(playerid, 269.6277);
        SetPlayerVirtualWorld(playerid, 1);
        SetPlayerInterior(playerid, 10);
        SetCameraBehindPlayer(playerid);
        TogglePlayerControllable(playerid, 1);
    }

    foreach(new i : Player){
        if(!LoggedIn[i]) continue;
        if(!PlayerEnterWarFlag[i]) continue;
        SendClientMessageEx(i, 0xFF8300FF, "[วอชิงธง]: ผู้เล่น %s ได้เข้าร่วมกิจกรรมวอชิงธงแล้ว...", ReturnRoleplayName(playerid));
    }
    return 1;
}