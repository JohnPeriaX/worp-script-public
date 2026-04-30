#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetPlayerAirDrop(playerid){
    PlayerIsCheckpointAirDrop[playerid] = -1;
    PlayerCarryAirDrop[playerid] = -1;

    PlayerTrackAirDropPlayerID[playerid] = INVALID_PLAYER_ID;
    for(new i=0; i<MAX_AIR_DROPS; i++){
        PlayerGetTrackAirDropList[playerid][i] = -1;
        PlayerGetAirDropList[playerid][i] = -1;
    }

    PlayerStartTimeAirDrop[playerid] = false;
    PlayerGetModelRewardAirDrop[playerid] = false;
    return 1;
}

hook OnPlayerEnterCheckpoint(playerid){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerIsCheckpointAirDrop[playerid] != -1){
        DisablePlayerCheckpoint(playerid);
        ClearGPS(playerid);
    }
    return 1;
}

hook OnPlayerDisconnect(playerid){
    if(LoggedIn[playerid]){
        if(PlayerCarryAirDrop[playerid] != -1 && !IsPlayerNPC(playerid)){
            AirDrop_Spawn(playerid, PlayerCarryAirDrop[playerid]);
            SendClientMessageToAllEx(COLOR_ORANGE, "| ขณะนี้ AirDrop กล่องที่ %d ได้ตกแล้ว...", PlayerCarryAirDrop[playerid]);
            RemoveAttachedObject(playerid, 9);
            PlayerStartTimeAirDrop[playerid] = false;
            PlayerTextDrawHide(playerid, AirDropTimeTextDraw[playerid][0]);
            PlayerTextDrawDestroy(playerid, AirDropTimeTextDraw[playerid][0]);
            foreach(new i : Player) if(LoggedIn[i]){
                if(PlayerTrackAirDropPlayerID[i] == playerid){
                    DisablePlayerCheckpoint(i);
                    SendClientMessageEx(i, COLOR_ORANGERED, "| ผู้เล่น %s(%d) ที่ถือกล่อง AirDrop กล่องที่ %d อยู่ ได้ออกจากเกมเรียบร้อยแล้ว", ReturnRoleplayName(playerid), playerid, PlayerCarryAirDrop[playerid]);
                    PlayerTrackAirDropPlayerID[i] = INVALID_PLAYER_ID;
                }
            }
            PlayerCarryAirDrop[playerid] = -1;
        }
    }   
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(!LoggedIn[playerid]) return 1;
    new airdropid = -1;
    if(newkeys & KEY_YES){
        if(!PlayerStartProgressbar[playerid]){
            if(( airdropid = IsPlayerNearAirDrop(playerid)) != -1 && PlayerCarryAirDrop[playerid] == -1){
                if(!strcmp(AirDropData[airdropid][AirDropState], "Ready", true) && AirDropData[airdropid][AirDropCoolDown] == 0 && AirDropData[airdropid][AirDropPlayerGet] == INVALID_PLAYER_ID){
                    if(airdropid != -1 && Iter_Contains(Iter_Airdrop, airdropid)){

                        ClearAnimations(playerid);
                        ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);

                        LoadPlayerAirDropTimeTextDraw(playerid);
                        PlayerTextDrawShow(playerid, AirDropTimeTextDraw[playerid][0]);
                        PlayerStartTimeAirDrop[playerid] = true;

                        PlayerCarryAirDrop[playerid] = airdropid;
                        AirDrop_Refresh(PlayerCarryAirDrop[playerid]);
                        SetPlayerAttachedObject(playerid,9,11745,1,0.034999,-0.200000,0.054999,22.499992,42.400039,-112.600021,0.957999,1.380999,1.442000);
                        SendClientMessageToAllEx(COLOR_ORANGE, "| ขณะนี้ผู้เล่น %s(%d) ได้เก็บ AirDrop กล่องที่ %d ไปแล้ว...", ReturnRoleplayName(playerid), playerid, PlayerCarryAirDrop[playerid]);
                        SendClientMessageToAllEx(COLOR_ORANGE, "| [คำแนะนำ] ใช้คำสั่ง '/tad' เพื่อค้นหา AirDrop ที่คุณจะไล่ล่า", ReturnRoleplayName(playerid), playerid, PlayerCarryAirDrop[playerid]);
                        SendClientMessage(playerid, COLOR_RED, "| จุดของคุณจะถูกเปิดเผยบน Minimap รีบหนีไปก่อนที่คนอื่นจะตามมา...");
                        SetPlayerProgressbarV2_Hide(playerid);
                        PlayerProgressbar_ResetMaxPoint(playerid);
                        ResetPlayerProgressbarV2(playerid);
                        ClearAnimations(playerid);
                        AirDropData[PlayerCarryAirDrop[playerid]][AirDropPlayerGet] = playerid;
                    }
                }
            }
        }
    }
    return 1;
}

ShowPlayerTrackAirDrop(playerid){
    new count = 0, string[1024];
    foreach(new i : Iter_Airdrop) if(Iter_Contains(Iter_Airdrop, i)){
        if(AirDropData[i][AirDropPlayerGet] == INVALID_PLAYER_ID) continue;
        if(playerid == AirDropData[i][AirDropPlayerGet]) continue;
        if(PlayerCarryAirDrop[AirDropData[i][AirDropPlayerGet]] != -1){
            format(string, sizeof string, "%s| ผู้เล่น %s(%d) กำลังถือ AirDrop กล่องที่ %d [กด 'เลือก' เพื่อตามไล่ล่า]\n", string, ReturnRoleplayName(AirDropData[i][AirDropPlayerGet]), AirDropData[i][AirDropPlayerGet], i);
            PlayerGetTrackAirDropList[playerid][count++] = i;
        }
    }

    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "เลือกคนที่ต้องการไล่ล่า", "ไม่พบคนที่ได้ AirDrop!", "เลือก", "ยกเลิก");
    else Dialog_ShowEasy(playerid, TrackAirDrop, DIALOG_STYLE_LIST, "เลือกคนที่ต้องการไล่ล่า", string, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:TrackAirDrop(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem >= 0 && listitem <= MAX_AIR_DROPS){
            new airdropid = PlayerGetTrackAirDropList[playerid][listitem];
            if(airdropid != -1 && Iter_Contains(Iter_Airdrop, airdropid)){
                PlayerTrackAirDropPlayerID[playerid] = AirDropData[airdropid][AirDropPlayerGet];
                SendClientMessageEx(playerid, COLOR_ORANGERED, "| คุณได้เปิดการไล่ล่า %s(%d) ที่กำลังถือกล่อง AirDrop กล่องที่ %d อยู่ เรียบร้อยแล้ว", ReturnRoleplayName(PlayerTrackAirDropPlayerID[playerid]), PlayerTrackAirDropPlayerID[playerid], airdropid);
            }
        }
    }
    return 1;
}

ShowPlayerAirDropList(playerid){
    new count = 0, string[1024];
    foreach(new i : Iter_Airdrop) if(Iter_Contains(Iter_Airdrop, i)){
        if(AirDropData[i][AirDropPlayerGet] != INVALID_PLAYER_ID) continue;
        if(AirDropData[i][AirDropItemModel][0] == MODEL_NULL) continue;
        if(AirDropData[i][AirDropItemModel][1] == MODEL_NULL) continue;
        if(AirDropData[i][AirDropItemModel][2] == MODEL_NULL) continue;
        new status[64];
        if(!strcmp(AirDropData[i][AirDropState], "Ready", true) && AirDropData[i][AirDropCoolDown] == 0) status = "พร้อมเก็บ";
        else if(AirDropData[i][AirDropCoolDown] != 0 && !strcmp(AirDropData[i][AirDropState], "Ready", true)) status = "อยู่ในช่วง CoolDown";
        else if(!strcmp(AirDropData[i][AirDropState], "Waiting", true)) status = "กำลังตกลงจากน่านฟ้า";
        format(string, sizeof string, "%s| กล่อง AirDrop ที่ %d - สถานะ: %s\n", string, i, status);
        PlayerGetAirDropList[playerid][count++] = i;
    }
    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "ค้นหา AirDrop", "ไม่พบกล่อง AirDrop ใดๆ", "ตกลง", "");
    Dialog_ShowEasy(playerid, FindAirDrop, DIALOG_STYLE_LIST, "ค้นหา AirDrop", string, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:FindAirDrop(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem >= 0 && listitem <= MAX_AIR_DROPS){
            new airdropid = PlayerGetAirDropList[playerid][listitem];
            if(airdropid != -1 && Iter_Contains(Iter_Airdrop, airdropid)){
                PlayerIsCheckpointAirDrop[playerid] = airdropid;
                SendClientMessageEx(playerid, COLOR_ORANGERED, "| คุณได้ค้นหาตำแหน่งของกล่อง AirDrop กล่องที่ %d เรียบร้อยแล้ว...", airdropid);
                DisablePlayerCheckpoint(playerid);
                ClearGPS(playerid);
                SetPlayerCheckpoint(playerid, AirDropData[airdropid][AirDropPos][0], AirDropData[airdropid][AirDropPos][1], AirDropData[airdropid][AirDropPos][2], 30.0);
                GPSNavigateToPoint(playerid, AirDropData[airdropid][AirDropPos][0], AirDropData[airdropid][AirDropPos][1], AirDropData[airdropid][AirDropPos][2]);
            }
        }
    }
    return 1;
}

ptask UpdateTrackAirDrop[1000](playerid){
    if(!IsPlayerNPC(playerid) && LoggedIn[playerid]){
        new aid = -1;
        if(( aid = IsPlayerNearAirDrop(playerid)) != -1 && !strcmp(AirDropData[aid][AirDropState], "Ready", true)){
            if(AirDropData[aid][AirDropItemModel][0] != MODEL_NULL && AirDropData[aid][AirDropItemModel][1] != MODEL_NULL 
            && AirDropData[aid][AirDropItemModel][2] != MODEL_NULL && AirDropData[aid][AirDropItemAmount][0] != 0 && AirDropData[aid][AirDropItemAmount][1] != 0
            && AirDropData[aid][AirDropItemAmount][2] != 0){
                if(!PlayerGetModelRewardAirDrop[playerid]){
                    PlayerGetModelRewardAirDrop[playerid] = true;
                    PlayerLoadModelAirDrop(playerid);

                    new string[128];

                    PlayerTextDrawSetPreviewModel(playerid, ModelItemAirDrop[playerid][1], AirDropData[aid][AirDropItemModel][0]);
                    PlayerTextDrawSetPreviewModel(playerid, ModelItemAirDrop[playerid][2], AirDropData[aid][AirDropItemModel][1]);
                    PlayerTextDrawSetPreviewModel(playerid, ModelItemAirDrop[playerid][3], AirDropData[aid][AirDropItemModel][2]);

                    format(string, sizeof string, "AIRDROP BOX #%d", aid);
                    PlayerTextDrawSetString(playerid, ModelItemAirDrop[playerid][4], string);

                    format(string, sizeof string, "%d EA", AirDropData[aid][AirDropItemAmount][0]);
                    PlayerTextDrawSetString(playerid, ModelItemAirDrop[playerid][5], string);
                    format(string, sizeof string, "%d EA", AirDropData[aid][AirDropItemAmount][1]);
                    PlayerTextDrawSetString(playerid, ModelItemAirDrop[playerid][6], string);
                    format(string, sizeof string, "%d EA", AirDropData[aid][AirDropItemAmount][2]);
                    PlayerTextDrawSetString(playerid, ModelItemAirDrop[playerid][7], string);

                    for(new i=0; i<8; i++){
                        PlayerTextDrawShow(playerid, ModelItemAirDrop[playerid][i]);
                    }
                }
            }
        }
        else{
            if(PlayerGetModelRewardAirDrop[playerid]){
                PlayerGetModelRewardAirDrop[playerid] = false;
                for(new i=0; i<8; i++){
                    PlayerTextDrawHide(playerid, ModelItemAirDrop[playerid][i]);
                    PlayerTextDrawDestroy(playerid, ModelItemAirDrop[playerid][i]);
                }
            }
        }

        if(PlayerCarryAirDrop[playerid] != -1 && PlayerStartTimeAirDrop[playerid]){
            if(AirDropData[PlayerCarryAirDrop[playerid]][AirDropMaxTime] > 0 && AirDropData[PlayerCarryAirDrop[playerid]][AirDropPlayerGet] != INVALID_PLAYER_ID) {
                AirDropData[PlayerCarryAirDrop[playerid]][AirDropMaxTime]--;
                new string[128];
                if(AirDropData[PlayerCarryAirDrop[playerid]][AirDropMaxTime] / 60 < 1){
                    format(string, sizeof string, "AIRDROP TIMEOUT: %d SECONDS", AirDropData[PlayerCarryAirDrop[playerid]][AirDropMaxTime]);
                }   
                else if(AirDropData[PlayerCarryAirDrop[playerid]][AirDropMaxTime] / 60 >= 1 && AirDropData[PlayerCarryAirDrop[playerid]][AirDropMaxTime] / 60 <= 60){
                    format(string, sizeof string, "AIRDROP TIMEOUT: %d MINUTES", AirDropData[PlayerCarryAirDrop[playerid]][AirDropMaxTime] / 60);
                }
                PlayerTextDrawSetString(playerid, AirDropTimeTextDraw[playerid][0], string);

                if(AirDropData[PlayerCarryAirDrop[playerid]][AirDropMaxTime] == 0){

                    if(PlayerStartTimeAirDrop[playerid]){
                        PlayerStartTimeAirDrop[playerid] = false;
                        PlayerTextDrawHide(playerid, AirDropTimeTextDraw[playerid][0]);
                        PlayerTextDrawDestroy(playerid, AirDropTimeTextDraw[playerid][0]);
                    }

                    foreach(new i : Player) if(LoggedIn[i]){
                        if(PlayerTrackAirDropPlayerID[i] == playerid){
                            DisablePlayerCheckpoint(i);
                            SendClientMessageEx(i, COLOR_ORANGERED, "| ผู้เล่น %s(%d) ได้ถือกล่อง AirDrop ที่ %d จนครบเวลาและเขาได้รับรางวัลไปแล้ว", ReturnRoleplayName(playerid), playerid, PlayerCarryAirDrop[playerid]);
                            PlayerTrackAirDropPlayerID[i] = INVALID_PLAYER_ID;
                        }
                    }

                    new itemid1 = PlayerInventory_AddItem(playerid, AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemName1], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemModel][0], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemAmount][0]);
                    new itemid2 = PlayerInventory_AddItem(playerid, AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemName2], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemModel][1], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemAmount][1]);
                    new itemid3 = PlayerInventory_AddItem(playerid, AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemName3], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemModel][2], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemAmount][2]);

                    if(itemid1 == -1) SendClientMessageEx(playerid, COLOR_RED, "| กระเป๋าของคุณเต็มไม่สามารถเก็บ %s จำนวน %d ชิ้นได้", AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemName1], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemAmount][0]);
                    else SendClientMessageEx(playerid, COLOR_YELLOW, "| คุณได้รับ %s จำนวน %d ชิ้น", AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemName1], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemAmount][0]);
                    
                    if(itemid2 == -1) SendClientMessageEx(playerid, COLOR_RED, "| กระเป๋าของคุณเต็มไม่สามารถเก็บ %s จำนวน %d ชิ้นได้", AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemName2], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemAmount][1]);
                    else SendClientMessageEx(playerid, COLOR_YELLOW, "| คุณได้รับ %s จำนวน %d ชิ้น", AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemName2], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemAmount][1]);

                    if(itemid3 == -1) SendClientMessageEx(playerid, COLOR_RED, "| กระเป๋าของคุณเต็มไม่สามารถเก็บ %s จำนวน %d ชิ้นได้", AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemName3], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemAmount][2]);
                    else SendClientMessageEx(playerid, COLOR_YELLOW, "| คุณได้รับ %s จำนวน %d ชิ้น", AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemName3], AirDropData[PlayerCarryAirDrop[playerid]][AirDropItemAmount][2]);

                    AirDrop_Remove(PlayerCarryAirDrop[playerid]);
                    RemoveAttachedObject(playerid, 9);
                    ResetPlayerAirDrop(playerid);
                }
            }
        }

        if(PlayerTrackAirDropPlayerID[playerid] != INVALID_PLAYER_ID){
            new Float:x, Float:y, Float:z;
            GetPlayerPos(PlayerTrackAirDropPlayerID[playerid], x, y, z);
            SetPlayerCheckpoint(playerid, x, y, z, 8.0);
        }
    }
}

CMD:fad(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    ShowPlayerAirDropList(playerid);
    return 1;
}

CMD:tad(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    ShowPlayerTrackAirDrop(playerid);
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason){
    if(LoggedIn[playerid]){
        if(PlayerCarryAirDrop[playerid] != -1 && !IsPlayerNPC(playerid)){
            AirDrop_Spawn(playerid, PlayerCarryAirDrop[playerid]);
            SendClientMessageToAllEx(COLOR_ORANGE, "| ขณะนี้ AirDrop กล่องที่ %d ได้ตกแล้ว...", PlayerCarryAirDrop[playerid]);
            RemoveAttachedObject(playerid, 9);
            PlayerStartTimeAirDrop[playerid] = false;
            PlayerTextDrawHide(playerid, AirDropTimeTextDraw[playerid][0]);
            PlayerTextDrawDestroy(playerid, AirDropTimeTextDraw[playerid][0]);
            foreach(new i : Player) if(LoggedIn[i]){
                if(PlayerTrackAirDropPlayerID[i] == playerid){
                    DisablePlayerCheckpoint(i);
                    SendClientMessageEx(i, COLOR_ORANGERED, "| ผู้เล่น %s(%d) ที่ถือกล่อง AirDrop กล่องที่ %d อยู่ ได้ตายแล้วทำกล่องตก...", ReturnRoleplayName(playerid), playerid, PlayerCarryAirDrop[playerid]);
                    PlayerTrackAirDropPlayerID[i] = INVALID_PLAYER_ID;
                }
            }
            PlayerCarryAirDrop[playerid] = -1;
        }
    }   
    return 1;
}

task UpdateAirDrop[1000](){
    foreach(new i : Iter_Airdrop) if(Iter_Contains(Iter_Airdrop, i)){
        if(AirDropData[i][AirDropCoolDown] > 0 && !strcmp(AirDropData[i][AirDropState], "Ready", true)){
            AirDropData[i][AirDropCoolDown]--;
            new string[128];
            if(AirDropData[i][AirDropCoolDown] / 60 < 1){
                format(string, sizeof string, "[Air Drop]\n(( เหลือเวลาอีก %d วินาที เพื่อจะเก็บ AirDrop นี้ได้อีกครั้ง ))\nกด 'Y' เพื่อเก็บ", AirDropData[i][AirDropCoolDown]);
            }   
            else if(AirDropData[i][AirDropCoolDown] / 60 >= 1 && AirDropData[i][AirDropCoolDown] / 60 <= 60){
                format(string, sizeof string, "[Air Drop]\n(( เหลือเวลาอีก %d นาที เพื่อจะเก็บ AirDrop นี้ได้อีกครั้ง ))\nกด 'Y' เพื่อเก็บ", AirDropData[i][AirDropCoolDown] / 60);
            }

            if(AirDropData[i][AirDropCoolDown] == 0){
                format(string, sizeof string, "[Air Drop]\n(( สามารถเก็บได้แล้ว ))\nกด 'Y' เพื่อเก็บ");
            }

            UpdateDynamic3DTextLabelText(AirDropData[i][TextAirDrop], 0xC9FF00FF, string);
        }
    }
}

AirDrop_Create(playerid){
    new id = -1;
    if(( id = Iter_Free(Iter_Airdrop)) != -1){
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        AirDropData[id][AirDropPos][0] = x;
        AirDropData[id][AirDropPos][1] = y;
        AirDropData[id][AirDropPos][2] = z;
        AirDropData[id][AirDropInt] = GetPlayerInterior(playerid);
        AirDropData[id][AirDropWorld] = GetPlayerVirtualWorld(playerid);
        AirDropData[id][AirDropCoolDown] = 0;
        AirDropData[id][AirDropPlayerGet] = INVALID_PLAYER_ID;
        format(AirDropData[id][AirDropState], 64, "Waiting");
        
        format(AirDropData[id][AirDropItemName1], 64, "NULL");
        format(AirDropData[id][AirDropItemName2], 64, "NULL");
        format(AirDropData[id][AirDropItemName3], 64, "NULL");

        for(new i=0; i<3; i++){
            AirDropData[id][AirDropItemModel][i] = MODEL_NULL;
            AirDropData[id][AirDropItemAmount][i] = 0;
        }

        new time = jdzrandom(1,3);
        if(time == 1) AirDropData[id][AirDropMaxTime] = 600;
        else if(time == 2) AirDropData[id][AirDropMaxTime] = 780;
        else if(time == 3) AirDropData[id][AirDropMaxTime] = 900;
        
        AirDropData[id][ObjectBox] = CreateDynamicObject(18849, AirDropData[id][AirDropPos][0], AirDropData[id][AirDropPos][1], AirDropData[id][AirDropPos][2]+90.0, 0.0, 0.0, 0.0, AirDropData[id][AirDropWorld], AirDropData[id][AirDropInt]);
        AirDropData[id][ObjectFlash] = CreateDynamicObject(18728, AirDropData[id][AirDropPos][0], AirDropData[id][AirDropPos][1], AirDropData[id][AirDropPos][2]+85.0, 0.0, 0.0, 0.0, AirDropData[id][AirDropWorld], AirDropData[id][AirDropInt]);

        AirDropData[id][TextAirDrop] = CreateDynamic3DTextLabel("[Air Drop]\n(( กำลังตกลงจากน่านฟ้า ))\nกด 'Y' เพื่อเก็บ", 0xC9FF00FF, AirDropData[id][AirDropPos][0], AirDropData[id][AirDropPos][1], AirDropData[id][AirDropPos][2]+0.8, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, AirDropData[id][AirDropWorld], AirDropData[id][AirDropInt]);
        Iter_Add(Iter_Airdrop, id);

        ShowPlayerSetItemAirDrop(playerid, id);
        return id;
    }
    return -1;
}

ShowPlayerSetItemAirDrop(playerid, id){
    new string[1024];
    format(string, sizeof string, "| #1 : ไอเท็ม: %s (Model: %d) จำนวน %d ชิ้น\
    \n| #2 : ไอเท็ม: %s (Model: %d) จำนวน %d ชิ้น\
    \n| #3 : ไอเท็ม: %s (Model: %d) จำนวน %d ชิ้น\
    \n| ยืนยันการปล่อย AirDrop |", AirDropData[id][AirDropItemName1], AirDropData[id][AirDropItemModel][0], AirDropData[id][AirDropItemAmount][0],
    AirDropData[id][AirDropItemName2], AirDropData[id][AirDropItemModel][1], AirDropData[id][AirDropItemAmount][1],
    AirDropData[id][AirDropItemName3], AirDropData[id][AirDropItemModel][2], AirDropData[id][AirDropItemAmount][2]);
    new caption[128];
    SetPVarInt(playerid, "EditAirDropID", id);
    format(caption, sizeof caption, "ไอเท็มกล่อง AirDrop ที่ %d", id);
    Dialog_ShowEasy(playerid, EditItemAirDrop, DIALOG_STYLE_LIST, caption, string, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:EditItemAmountAirDrop3(playerid, response, listitem, inputtext[]){
    new aid = GetPVarInt(playerid, "EditAirDropID");
    if(aid != -1){
        new string[1024], caption[128];
        if(!response){
            format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
            \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName3], AirDropData[aid][AirDropItemModel][2], AirDropData[aid][AirDropItemAmount][2]);
            format(caption, sizeof caption, "ไอเท็มชิ้นที่ 3 (AID: %d)", aid);
            Dialog_ShowEasy(playerid, EditItemAirDrop3, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
        }
        if(response){
            new amount = strval(inputtext);
            if(amount <= 0){
                format(string, sizeof string, "[!] คุณต้องกรอกจำนวนมากกว่า 0\nไอเท็ม: %s (%d) จำนวน %d EA\nกรุณาใส่จำนวนไอเท็มที่ต้องการ:", AirDropData[aid][AirDropItemName3], AirDropData[aid][AirDropItemModel][2], AirDropData[aid][AirDropItemAmount][2]);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 3 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, EditItemAmountAirDrop3, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "กลับ");
                return 1;
            }

            AirDropData[aid][AirDropItemAmount][2] = amount;
            SendClientMessageEx(playerid, COLOR_ORANGERED, "| คุณได้ปรับจำนวน ไอเท็ม: %s (%d) เป็น %d EA แล้ว", AirDropData[aid][AirDropItemName3], AirDropData[aid][AirDropItemModel][2], AirDropData[aid][AirDropItemAmount][2]);
        
            ShowPlayerSetItemAirDrop(playerid, aid);
        }
    }
    return 1;
}

Dialog:EditItemAmountAirDrop2(playerid, response, listitem, inputtext[]){
    new aid = GetPVarInt(playerid, "EditAirDropID");
    if(aid != -1){
        new string[1024], caption[128];
        if(!response){
            format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
            \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName2], AirDropData[aid][AirDropItemModel][1], AirDropData[aid][AirDropItemAmount][1]);
            format(caption, sizeof caption, "ไอเท็มชิ้นที่ 2 (AID: %d)", aid);
            Dialog_ShowEasy(playerid, EditItemAirDrop2, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
        }
        if(response){
            new amount = strval(inputtext);
            if(amount <= 0){
                format(string, sizeof string, "[!] คุณต้องกรอกจำนวนมากกว่า 0\nไอเท็ม: %s (%d) จำนวน %d EA\nกรุณาใส่จำนวนไอเท็มที่ต้องการ:", AirDropData[aid][AirDropItemName2], AirDropData[aid][AirDropItemModel][1], AirDropData[aid][AirDropItemAmount][1]);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 2 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, EditItemAmountAirDrop2, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "กลับ");
                return 1;
            }

            AirDropData[aid][AirDropItemAmount][1] = amount;
            SendClientMessageEx(playerid, COLOR_ORANGERED, "| คุณได้ปรับจำนวน ไอเท็ม: %s (%d) เป็น %d EA แล้ว", AirDropData[aid][AirDropItemName2], AirDropData[aid][AirDropItemModel][1], AirDropData[aid][AirDropItemAmount][1]);
        
            ShowPlayerSetItemAirDrop(playerid, aid);
        }
    }
    return 1;
}

Dialog:EditItemAmountAirDrop1(playerid, response, listitem, inputtext[]){
    new aid = GetPVarInt(playerid, "EditAirDropID");
    if(aid != -1){
        new string[1024], caption[128];
        if(!response){
            format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
            \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName1], AirDropData[aid][AirDropItemModel][0], AirDropData[aid][AirDropItemAmount][0]);
            format(caption, sizeof caption, "ไอเท็มชิ้นที่ 1 (AID: %d)", aid);
            Dialog_ShowEasy(playerid, EditItemAirDrop1, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
        }
        if(response){
            new amount = strval(inputtext);
            if(amount <= 0){
                format(string, sizeof string, "[!] คุณต้องกรอกจำนวนมากกว่า 0\nไอเท็ม: %s (%d) จำนวน %d EA\nกรุณาใส่จำนวนไอเท็มที่ต้องการ:", AirDropData[aid][AirDropItemName1], AirDropData[aid][AirDropItemModel][0], AirDropData[aid][AirDropItemAmount][0]);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 1 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, EditItemAmountAirDrop1, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "กลับ");
                return 1;
            }

            AirDropData[aid][AirDropItemAmount][0] = amount;
            SendClientMessageEx(playerid, COLOR_ORANGERED, "| คุณได้ปรับจำนวน ไอเท็ม: %s (%d) เป็น %d EA แล้ว", AirDropData[aid][AirDropItemName1], AirDropData[aid][AirDropItemModel][0], AirDropData[aid][AirDropItemAmount][0]);
        
            ShowPlayerSetItemAirDrop(playerid, aid);
        }
    }
    return 1;
}

Dialog:SelectItemAirDrop3(playerid, response, listitem, inputtext[]){
    new aid = GetPVarInt(playerid, "EditAirDropID");
    if(aid != -1){
        new string[1024], caption[128];
        if(!response){
            format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
            \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName3], AirDropData[aid][AirDropItemModel][2], AirDropData[aid][AirDropItemAmount][2]);
            format(caption, sizeof caption, "ไอเท็มชิ้นที่ 3 (AID: %d)", aid);
            Dialog_ShowEasy(playerid, EditItemAirDrop3, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
        }
        if(response){

            if(isnull(inputtext)){
                format(string, sizeof string, "ใส่ชื่อไอเท็มที่ต้องการจะเพิ่มเข้าไอเท็มช่องที่ 3: ");
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 3 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, SelectItemAirDrop3, DIALOG_STYLE_INPUT, caption, string, "เลือก", "กลับ");
                return 1;
            }

            new found = false;

            for (new i = 0; i < sizeof(Item_Data); i ++) {
                if (!strcmp(Item_Data[i][itemName], inputtext, true)){
                    format(AirDropData[aid][AirDropItemName3], 64, Item_Data[i][itemName]);
                    AirDropData[aid][AirDropItemModel][2] = Item_Data[i][itemModel];

                    SendClientMessageEx(playerid, COLOR_ORANGERED, "| คุณได้เลือกไอเท็ม %s (%d) ใส่ในไอเท็มช่องที่ 3 ของ AirDrop กล่องที่ %d", AirDropData[aid][AirDropItemName3], AirDropData[aid][AirDropItemModel][2], aid);

                    format(string, sizeof string, "ไอเท็ม: %s (%d) จำนวน %d EA\nกรุณาใส่จำนวนไอเท็มที่ต้องการ:", AirDropData[aid][AirDropItemName3], AirDropData[aid][AirDropItemModel][2], AirDropData[aid][AirDropItemAmount][2]);
                    format(caption, sizeof caption, "ไอเท็มชิ้นที่ 3 (AID: %d)", aid);
                    Dialog_ShowEasy(playerid, EditItemAmountAirDrop3, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "กลับ");
                    found = true;
                    return 1;
                }
            }

            if(!found){
                format(string, sizeof string, "! ไม่พบไอเท็ม %s โปรดลองใหม่ !\nใส่ชื่อไอเท็มที่ต้องการจะเพิ่มเข้าไอเท็มช่องที่ 2: ", inputtext);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 2 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, SelectItemAirDrop2, DIALOG_STYLE_INPUT, caption, string, "เลือก", "กลับ");
            }
            
            return 1;
        }
    }
    return 1;
}

Dialog:SelectItemAirDrop2(playerid, response, listitem, inputtext[]){
    new aid = GetPVarInt(playerid, "EditAirDropID");
    if(aid != -1){
        new string[1024], caption[128];
        if(!response){
            format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
            \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName2], AirDropData[aid][AirDropItemModel][1], AirDropData[aid][AirDropItemAmount][1]);
            format(caption, sizeof caption, "ไอเท็มชิ้นที่ 2 (AID: %d)", aid);
            Dialog_ShowEasy(playerid, EditItemAirDrop2, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
        }
        if(response){

            if(isnull(inputtext)){
                format(string, sizeof string, "ใส่ชื่อไอเท็มที่ต้องการจะเพิ่มเข้าไอเท็มช่องที่ 2: ");
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 2 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, SelectItemAirDrop2, DIALOG_STYLE_INPUT, caption, string, "เลือก", "กลับ");
                return 1;
            }

            new found = false;

            for (new i = 0; i < sizeof(Item_Data); i ++) {
                if (!strcmp(Item_Data[i][itemName], inputtext, true)){
                    format(AirDropData[aid][AirDropItemName2], 64, Item_Data[i][itemName]);
                    AirDropData[aid][AirDropItemModel][1] = Item_Data[i][itemModel];

                    SendClientMessageEx(playerid, COLOR_ORANGERED, "| คุณได้เลือกไอเท็ม %s (%d) ใส่ในไอเท็มช่องที่ 2 ของ AirDrop กล่องที่ %d", AirDropData[aid][AirDropItemName2], AirDropData[aid][AirDropItemModel][1], aid);

                    format(string, sizeof string, "ไอเท็ม: %s (%d) จำนวน %d EA\nกรุณาใส่จำนวนไอเท็มที่ต้องการ:", AirDropData[aid][AirDropItemName2], AirDropData[aid][AirDropItemModel][1], AirDropData[aid][AirDropItemAmount][1]);
                    format(caption, sizeof caption, "ไอเท็มชิ้นที่ 2 (AID: %d)", aid);
                    Dialog_ShowEasy(playerid, EditItemAmountAirDrop2, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "กลับ");
                    found = true;
                    return 1;
                }
            }

            if(!found){
                format(string, sizeof string, "! ไม่พบไอเท็ม %s โปรดลองใหม่ !\nใส่ชื่อไอเท็มที่ต้องการจะเพิ่มเข้าไอเท็มช่องที่ 2: ", inputtext);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 2 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, SelectItemAirDrop2, DIALOG_STYLE_INPUT, caption, string, "เลือก", "กลับ");
            }
            
            return 1;
        }
    }
    return 1;
}

Dialog:SelectItemAirDrop1(playerid, response, listitem, inputtext[]){
    new aid = GetPVarInt(playerid, "EditAirDropID");
    if(aid != -1){
        new string[1024], caption[128];
        if(!response){
            format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
            \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName1], AirDropData[aid][AirDropItemModel][0], AirDropData[aid][AirDropItemAmount][0]);
            format(caption, sizeof caption, "ไอเท็มชิ้นที่ 1 (AID: %d)", aid);
            Dialog_ShowEasy(playerid, EditItemAirDrop1, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
        }
        if(response){

            if(isnull(inputtext)){
                format(string, sizeof string, "ใส่ชื่อไอเท็มที่ต้องการจะเพิ่มเข้าไอเท็มช่องที่ 1: ");
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 1 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, SelectItemAirDrop1, DIALOG_STYLE_INPUT, caption, string, "เลือก", "กลับ");
                return 1;
            }

            new found = false;

            for (new i = 0; i < sizeof(Item_Data); i ++) {
                if (!strcmp(Item_Data[i][itemName], inputtext, true)){
                    format(AirDropData[aid][AirDropItemName1], 64, Item_Data[i][itemName]);
                    AirDropData[aid][AirDropItemModel][0] = Item_Data[i][itemModel];

                    SendClientMessageEx(playerid, COLOR_ORANGERED, "| คุณได้เลือกไอเท็ม %s (%d) ใส่ในไอเท็มช่องที่ 1 ของ AirDrop กล่องที่ %d", AirDropData[aid][AirDropItemName1], AirDropData[aid][AirDropItemModel][0], aid);

                    format(string, sizeof string, "ไอเท็ม: %s (%d) จำนวน %d EA\nกรุณาใส่จำนวนไอเท็มที่ต้องการ:", AirDropData[aid][AirDropItemName1], AirDropData[aid][AirDropItemModel][0], AirDropData[aid][AirDropItemAmount][0]);
                    format(caption, sizeof caption, "ไอเท็มชิ้นที่ 1 (AID: %d)", aid);
                    Dialog_ShowEasy(playerid, EditItemAmountAirDrop1, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "กลับ");
                    found = true;
                    return 1;
                }
            }

            if(!found){
                format(string, sizeof string, "! ไม่พบไอเท็ม %s โปรดลองใหม่ !\nใส่ชื่อไอเท็มที่ต้องการจะเพิ่มเข้าไอเท็มช่องที่ 1: ", inputtext);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 1 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, SelectItemAirDrop1, DIALOG_STYLE_INPUT, caption, string, "เลือก", "กลับ");
            }
            
            return 1;
        }
    }
    return 1;
}

Dialog:EditItemAirDrop3(playerid, response, listitem, inputtext[]){
    new aid = GetPVarInt(playerid, "EditAirDropID");
    if(aid != -1){
        new string[1024], caption[128];
        if(!response){
            ShowPlayerSetItemAirDrop(playerid, aid);
            return 1;
        }
        if(response){
            if(listitem == 0){
                format(string, sizeof string, "ใส่ชื่อไอเท็มที่ต้องการจะเพิ่มเข้าไอเท็มช่องที่ 3: ");
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 3 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, SelectItemAirDrop3, DIALOG_STYLE_INPUT, caption, string, "เลือก", "กลับ");
            }
            if(listitem == 1){
                if(!strcmp(AirDropData[aid][AirDropItemName3], "NULL", true)){
                    format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
                    \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName3], AirDropData[aid][AirDropItemModel][2], AirDropData[aid][AirDropItemAmount][2]);
                    format(caption, sizeof caption, "ไอเท็มชิ้นที่ 3 (AID: %d)", aid);
                    Dialog_ShowEasy(playerid, EditItemAirDrop3, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
                    return 1;
                }

                format(string, sizeof string, "ไอเท็ม: %s (%d) จำนวน %d EA\nกรุณาใส่จำนวนไอเท็มที่ต้องการ:", AirDropData[aid][AirDropItemName3], AirDropData[aid][AirDropItemModel][2], AirDropData[aid][AirDropItemAmount][2]);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 3 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, EditItemAmountAirDrop3, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "กลับ");
            }
        }
    }
    return 1;
}

Dialog:EditItemAirDrop2(playerid, response, listitem, inputtext[]){
    new aid = GetPVarInt(playerid, "EditAirDropID");
    if(aid != -1){
        new string[1024], caption[128];
        if(!response){
            ShowPlayerSetItemAirDrop(playerid, aid);
            return 1;
        }
        if(response){
            if(listitem == 0){
                format(string, sizeof string, "ใส่ชื่อไอเท็มที่ต้องการจะเพิ่มเข้าไอเท็มช่องที่ 2: ");
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 2 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, SelectItemAirDrop2, DIALOG_STYLE_INPUT, caption, string, "เลือก", "กลับ");
            }
            if(listitem == 1){
                if(!strcmp(AirDropData[aid][AirDropItemName2], "NULL", true)){
                    format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
                    \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName2], AirDropData[aid][AirDropItemModel][1], AirDropData[aid][AirDropItemAmount][1]);
                    format(caption, sizeof caption, "ไอเท็มชิ้นที่ 2 (AID: %d)", aid);
                    Dialog_ShowEasy(playerid, EditItemAirDrop2, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
                    return 1;
                }

                format(string, sizeof string, "ไอเท็ม: %s (%d) จำนวน %d EA\nกรุณาใส่จำนวนไอเท็มที่ต้องการ:", AirDropData[aid][AirDropItemName2], AirDropData[aid][AirDropItemModel][1], AirDropData[aid][AirDropItemAmount][1]);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 2 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, EditItemAmountAirDrop2, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "กลับ");
            }
        }
    }
    return 1;
}

Dialog:EditItemAirDrop1(playerid, response, listitem, inputtext[]){
    new aid = GetPVarInt(playerid, "EditAirDropID");
    if(aid != -1){
        new string[1024], caption[128];
        if(!response){
            ShowPlayerSetItemAirDrop(playerid, aid);
            return 1;
        }
        if(response){
            if(listitem == 0){
                format(string, sizeof string, "ใส่ชื่อไอเท็มที่ต้องการจะเพิ่มเข้าไอเท็มช่องที่ 1: ");
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 1 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, SelectItemAirDrop1, DIALOG_STYLE_INPUT, caption, string, "เลือก", "กลับ");
            }
            if(listitem == 1){
                if(!strcmp(AirDropData[aid][AirDropItemName1], "NULL", true)){
                    format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
                    \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName1], AirDropData[aid][AirDropItemModel][0], AirDropData[aid][AirDropItemAmount][0]);
                    format(caption, sizeof caption, "ไอเท็มชิ้นที่ 1 (AID: %d)", aid);
                    Dialog_ShowEasy(playerid, EditItemAirDrop1, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
                    return 1;
                }

                format(string, sizeof string, "ไอเท็ม: %s (%d) จำนวน %d EA\nกรุณาใส่จำนวนไอเท็มที่ต้องการ:", AirDropData[aid][AirDropItemName1], AirDropData[aid][AirDropItemModel][0], AirDropData[aid][AirDropItemAmount][0]);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 1 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, EditItemAmountAirDrop1, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "กลับ");
            }
        }
    }
    return 1;
}

timer UpdateAirDropEx[8500](id){
    format(AirDropData[id][AirDropState], 64, "Ready");
    UpdateDynamic3DTextLabelText(AirDropData[id][TextAirDrop], 0xC9FF00FF, "[Air Drop]\n(( สามารถเก็บได้แล้ว ))\nกด 'Y' เพื่อเก็บ");
}

Dialog:EditItemAirDrop(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new aid = GetPVarInt(playerid, "EditAirDropID");
        if(aid != -1){
            new string[1024], caption[128];
            if(listitem == 0){
                format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
                \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName1], AirDropData[aid][AirDropItemModel][0], AirDropData[aid][AirDropItemAmount][0]);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 1 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, EditItemAirDrop1, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
            }
            if(listitem == 1){
                format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
                \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName2], AirDropData[aid][AirDropItemModel][1], AirDropData[aid][AirDropItemAmount][1]);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 2 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, EditItemAirDrop2, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
            }
            if(listitem == 2){
                format(string, sizeof string, "| เลือกไอเท็ม [%s (%d)]\
                \n| จำนวนไอเท็ม %d EA", AirDropData[aid][AirDropItemName3], AirDropData[aid][AirDropItemModel][2], AirDropData[aid][AirDropItemAmount][2]);
                format(caption, sizeof caption, "ไอเท็มชิ้นที่ 3 (AID: %d)", aid);
                Dialog_ShowEasy(playerid, EditItemAirDrop3, DIALOG_STYLE_LIST, caption, string, "เลือก", "กลับ");
            }
            if(listitem == 3){
                if(!strcmp(AirDropData[aid][AirDropState], "Ready", true)) return ErrorMsg(playerid, "AirDrop นี้ถูกปล่อยไปแล้ว");

                if(AirDropData[aid][AirDropItemModel][0] == MODEL_NULL){
                    ErrorMsg(playerid, "AirDrop นี้ยังไม่ได้ถูกตั้งค่า Item ชิ้นที่ 1");
                    return ShowPlayerSetItemAirDrop(playerid, aid);
                }

                if(AirDropData[aid][AirDropItemModel][1] == MODEL_NULL){
                    ErrorMsg(playerid, "AirDrop นี้ยังไม่ได้ถูกตั้งค่า Item ชิ้นที่ 2");
                    return ShowPlayerSetItemAirDrop(playerid, aid);
                }

                if(AirDropData[aid][AirDropItemModel][2] == MODEL_NULL){
                    ErrorMsg(playerid, "AirDrop นี้ยังไม่ได้ถูกตั้งค่า Item ชิ้นที่ 3");
                    return ShowPlayerSetItemAirDrop(playerid, aid);
                }

                MoveDynamicObject(AirDropData[aid][ObjectBox], AirDropData[aid][AirDropPos][0], AirDropData[aid][AirDropPos][1], AirDropData[aid][AirDropPos][2]+6.2, 10.0);
                MoveDynamicObject(AirDropData[aid][ObjectFlash], AirDropData[aid][AirDropPos][0], AirDropData[aid][AirDropPos][1], AirDropData[aid][AirDropPos][2]-3.0, 10.0);
                defer UpdateAirDropEx(aid);
                SendClientMessageToAll(COLOR_ORANGE, "| ขณะนี้ AirDrop กำลังตกลงจากน่านฟ้า...");
                SendClientMessageToAll(COLOR_ORANGE, "| [คำแนะนำ]: ใช้ '/fad' ในการค้นหากล่อง AirDrop ทั้งหมดที่กำลังตกลงมา...");
            }
        }
    }
    return 1;
}

AirDrop_Spawn(playerid, airdropid){
    if(airdropid != -1 && Iter_Contains(Iter_Airdrop, airdropid)){
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        AirDropData[airdropid][AirDropPos][0] = x;
        AirDropData[airdropid][AirDropPos][1] = y;
        AirDropData[airdropid][AirDropPos][2] = z;
        AirDropData[airdropid][AirDropInt] = GetPlayerInterior(playerid);
        AirDropData[airdropid][AirDropWorld] = GetPlayerVirtualWorld(playerid);

        AirDropData[airdropid][ObjectBox] = CreateDynamicObject(18849, AirDropData[airdropid][AirDropPos][0], AirDropData[airdropid][AirDropPos][1], AirDropData[airdropid][AirDropPos][2]+6.2, 0.0, 0.0, 0.0, AirDropData[airdropid][AirDropWorld], AirDropData[airdropid][AirDropInt]);
        AirDropData[airdropid][ObjectFlash] = CreateDynamicObject(18728, AirDropData[airdropid][AirDropPos][0], AirDropData[airdropid][AirDropPos][1], AirDropData[airdropid][AirDropPos][2]-3.0, 0.0, 0.0, 0.0, AirDropData[airdropid][AirDropWorld], AirDropData[airdropid][AirDropInt]);
        AirDropData[airdropid][TextAirDrop] = CreateDynamic3DTextLabel("[Air Drop]\n(( กำลังตกลงจากน่านฟ้า ))\nกด 'Y' เพื่อเก็บ", 0xC9FF00FF, AirDropData[airdropid][AirDropPos][0], AirDropData[airdropid][AirDropPos][1], AirDropData[airdropid][AirDropPos][2]+0.8, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, AirDropData[airdropid][AirDropWorld], AirDropData[airdropid][AirDropInt]);
        format(AirDropData[airdropid][AirDropState], 64, "Ready");
        AirDropData[airdropid][AirDropPlayerGet] = INVALID_PLAYER_ID;
    }
    return 1;
}

AirDrop_Refresh(airdropid){
    if(airdropid != -1 && Iter_Contains(Iter_Airdrop, airdropid)){
        if(IsValidDynamicObject(AirDropData[airdropid][ObjectBox]) && AirDropData[airdropid][ObjectBox] != -1){
            DestroyDynamicObject(AirDropData[airdropid][ObjectBox]);
            AirDropData[airdropid][ObjectBox] = -1;
        }

        if(IsValidDynamicObject(AirDropData[airdropid][ObjectFlash]) && AirDropData[airdropid][ObjectFlash] != -1){
            DestroyDynamicObject(AirDropData[airdropid][ObjectFlash]);
            AirDropData[airdropid][ObjectFlash] = -1;
        }

        if(IsValidDynamic3DTextLabel(AirDropData[airdropid][TextAirDrop]) && AirDropData[airdropid][TextAirDrop]) DestroyDynamic3DTextLabel(AirDropData[airdropid][TextAirDrop]);
    
        format(AirDropData[airdropid][AirDropState], 64, "Pickup");
        AirDropData[airdropid][AirDropCoolDown] = 60;
    }
    return 1;
}

AirDrop_Remove(airdropid){
    if(airdropid != -1 && Iter_Contains(Iter_Airdrop, airdropid)){
        if(IsValidDynamicObject(AirDropData[airdropid][ObjectBox]) && AirDropData[airdropid][ObjectBox] != -1){
            DestroyDynamicObject(AirDropData[airdropid][ObjectBox]);
            AirDropData[airdropid][ObjectBox] = -1;
        }

        if(IsValidDynamicObject(AirDropData[airdropid][ObjectFlash]) && AirDropData[airdropid][ObjectFlash] != -1){
            DestroyDynamicObject(AirDropData[airdropid][ObjectFlash]);
            AirDropData[airdropid][ObjectFlash] = -1;
        }

        if(IsValidDynamic3DTextLabel(AirDropData[airdropid][TextAirDrop]) && AirDropData[airdropid][TextAirDrop]) DestroyDynamic3DTextLabel(AirDropData[airdropid][TextAirDrop]);
    
        AirDropData[airdropid][AirDropPos][0] = 0.0;
        AirDropData[airdropid][AirDropPos][1] = 0.0;
        AirDropData[airdropid][AirDropPos][2] = 0.0;
        AirDropData[airdropid][AirDropInt] = 0;
        AirDropData[airdropid][AirDropWorld] = 0;
        AirDropData[airdropid][AirDropPlayerGet] = INVALID_PLAYER_ID;
        format(AirDropData[airdropid][AirDropState], 64, "Waiting");
        AirDropData[airdropid][AirDropCoolDown] = 0;
        AirDropData[airdropid][AirDropMaxTime] = 0;

        format(AirDropData[airdropid][AirDropItemName1], 64, "NULL");
        format(AirDropData[airdropid][AirDropItemName2], 64, "NULL");
        format(AirDropData[airdropid][AirDropItemName3], 64, "NULL");

        for(new i=0; i<3; i++){
            AirDropData[airdropid][AirDropItemModel][i] = MODEL_NULL;
            AirDropData[airdropid][AirDropItemAmount][i] = MODEL_NULL;
        }

        Iter_Remove(Iter_Airdrop, airdropid);
        SendClientMessageToAllEx(COLOR_ORANGE, "| ขณะนี้ AirDrop กล่องที่ %d ได้ถูกทำลายทิ้งแล้ว...", airdropid);
    }
    return 1;
}

IsPlayerNearAirDrop(playerid){
    foreach(new i : Iter_Airdrop) if(Iter_Contains(Iter_Airdrop, i)){
        if(IsPlayerInRangeOfPoint(playerid, 2.0, AirDropData[i][AirDropPos][0], AirDropData[i][AirDropPos][1], AirDropData[i][AirDropPos][2]) && GetPlayerInterior(playerid) == AirDropData[i][AirDropInt] && GetPlayerVirtualWorld(playerid) == AirDropData[i][AirDropWorld]){
            return i;
        }
    }
    return -1;
}

CMD:airdrop(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    
    new airdopid = AirDrop_Create(playerid);
    if(airdopid == -1) return ErrorMsg(playerid, "เซิฟเวอร์ได้สร้าง Airdrop จนเต็มแล้ว");
    return 1;
}

CMD:editairdrop(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new aid;
    if(sscanf(params, "d", aid)) return SystemMsg(playerid, "/editairdrop [airdropid]");
    if(aid != -1 && Iter_Contains(Iter_Airdrop, aid)){
        ShowPlayerSetItemAirDrop(playerid, aid);
    }
    return 1;
}

CMD:checkairdrop(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new aid;
    if(sscanf(params, "d", aid)) return SystemMsg(playerid, "/checkairdrop [airdropid]");
    if(aid != -1 && Iter_Contains(Iter_Airdrop, aid)){
        new string[128];
        if(AirDropData[aid][AirDropMaxTime] / 60 < 1){
            format(string, sizeof string, "| AIRDROP #%d AIRDROP TIMEOUT: %d SECONDS", aid, AirDropData[aid][AirDropMaxTime]);
            SendClientMessage(playerid, COLOR_ORANGERED, string);
            format(string, sizeof string, "| ถือโดย %s(%d)", ReturnRoleplayName(AirDropData[aid][AirDropPlayerGet]), AirDropData[aid][AirDropPlayerGet]);
            SendClientMessage(playerid, COLOR_ORANGERED, string);
        }   
        else if(AirDropData[aid][AirDropMaxTime] / 60 >= 1 && AirDropData[aid][AirDropMaxTime] / 60 <= 60){
            format(string, sizeof string, "| AIRDROP #%d AIRDROP TIMEOUT: %d MINUTES", aid, AirDropData[aid][AirDropMaxTime] / 60);
            SendClientMessage(playerid, COLOR_ORANGERED, string);
            format(string, sizeof string, "| ถือโดย %s(%d)", ReturnRoleplayName(AirDropData[aid][AirDropPlayerGet]), AirDropData[aid][AirDropPlayerGet]);
            SendClientMessage(playerid, COLOR_ORANGERED, string);
        }
    }
    return 1;
}

CMD:gotoairdrop(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new aid;
    if(sscanf(params, "d", aid)) return SystemMsg(playerid, "/gotoairdrop [airdropid]");
    if(aid != -1 && Iter_Contains(Iter_Airdrop, aid)){
        if(AirDropData[aid][AirDropPlayerGet] == INVALID_PLAYER_ID){
            SetPlayerPosEx(playerid, AirDropData[aid][AirDropPos][0], AirDropData[aid][AirDropPos][1], AirDropData[aid][AirDropPos][2], AirDropData[aid][AirDropInt], AirDropData[aid][AirDropWorld]);
        }
        else{
            new Float:x, Float:y, Float:z;
            GetPlayerPos(AirDropData[aid][AirDropPlayerGet], x, y, z);
            SetPlayerPosEx(playerid, x, y, z, GetPlayerInterior(AirDropData[aid][AirDropPlayerGet]), GetPlayerVirtualWorld(AirDropData[aid][AirDropPlayerGet]));
        }
    }
    return 1;
}

CMD:rmairdrop(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new aid;
    if(sscanf(params, "d", aid)) return SystemMsg(playerid, "/gotoairdrop [airdropid]");
    if(aid != -1 && Iter_Contains(Iter_Airdrop, aid)){
        if(AirDropData[aid][AirDropPlayerGet] != INVALID_PLAYER_ID) return ErrorMsg(playerid, "กล่อง AirDrop นั้นยังไม่ตกพื้น");
        AirDrop_Remove(aid);
    }
    return 1;
}

LoadPlayerAirDropTimeTextDraw(playerid){
    AirDropTimeTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 541.000000, 112.000000, "AIRDROP TIMEOUT: 15 MINTUES");
    PlayerTextDrawFont(playerid, AirDropTimeTextDraw[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, AirDropTimeTextDraw[playerid][0], 0.245833, 1.350003);
    PlayerTextDrawTextSize(playerid, AirDropTimeTextDraw[playerid][0], 301.000000, 136.500000);
    PlayerTextDrawSetOutline(playerid, AirDropTimeTextDraw[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, AirDropTimeTextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, AirDropTimeTextDraw[playerid][0], 2);
    PlayerTextDrawColor(playerid, AirDropTimeTextDraw[playerid][0], -16776961);
    PlayerTextDrawBackgroundColor(playerid, AirDropTimeTextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, AirDropTimeTextDraw[playerid][0], 135);
    PlayerTextDrawUseBox(playerid, AirDropTimeTextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, AirDropTimeTextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, AirDropTimeTextDraw[playerid][0], 0);
    return 1;
}

PlayerLoadModelAirDrop(playerid){
    ModelItemAirDrop[playerid][0] = CreatePlayerTextDraw(playerid, 320.000000, 157.000000, "AIRDROP REWARDS");
    PlayerTextDrawFont(playerid, ModelItemAirDrop[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, ModelItemAirDrop[playerid][0], 0.429166, 1.800000);
    PlayerTextDrawTextSize(playerid, ModelItemAirDrop[playerid][0], 400.000000, 224.000000);
    PlayerTextDrawSetOutline(playerid, ModelItemAirDrop[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, ModelItemAirDrop[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, ModelItemAirDrop[playerid][0], 2);
    PlayerTextDrawColor(playerid, ModelItemAirDrop[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, ModelItemAirDrop[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, ModelItemAirDrop[playerid][0], 130);
    PlayerTextDrawUseBox(playerid, ModelItemAirDrop[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, ModelItemAirDrop[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, ModelItemAirDrop[playerid][0], 0);

    ModelItemAirDrop[playerid][1] = CreatePlayerTextDraw(playerid, 206.500000, 175.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, ModelItemAirDrop[playerid][1], 5);
    PlayerTextDrawLetterSize(playerid, ModelItemAirDrop[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, ModelItemAirDrop[playerid][1], 76.000000, 87.500000);
    PlayerTextDrawSetOutline(playerid, ModelItemAirDrop[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, ModelItemAirDrop[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, ModelItemAirDrop[playerid][1], 1);
    PlayerTextDrawColor(playerid, ModelItemAirDrop[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, ModelItemAirDrop[playerid][1], -1962934147);
    PlayerTextDrawBoxColor(playerid, ModelItemAirDrop[playerid][1], 255);
    PlayerTextDrawUseBox(playerid, ModelItemAirDrop[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, ModelItemAirDrop[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, ModelItemAirDrop[playerid][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, ModelItemAirDrop[playerid][1], 19793);
    PlayerTextDrawSetPreviewRot(playerid, ModelItemAirDrop[playerid][1], -10.000000, 0.000000, -20.000000, 1.300000);
    PlayerTextDrawSetPreviewVehCol(playerid, ModelItemAirDrop[playerid][1], 1, 1);

    ModelItemAirDrop[playerid][2] = CreatePlayerTextDraw(playerid, 282.000000, 175.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, ModelItemAirDrop[playerid][2], 5);
    PlayerTextDrawLetterSize(playerid, ModelItemAirDrop[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, ModelItemAirDrop[playerid][2], 76.000000, 87.500000);
    PlayerTextDrawSetOutline(playerid, ModelItemAirDrop[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, ModelItemAirDrop[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, ModelItemAirDrop[playerid][2], 1);
    PlayerTextDrawColor(playerid, ModelItemAirDrop[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, ModelItemAirDrop[playerid][2], -1962934147);
    PlayerTextDrawBoxColor(playerid, ModelItemAirDrop[playerid][2], 255);
    PlayerTextDrawUseBox(playerid, ModelItemAirDrop[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, ModelItemAirDrop[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, ModelItemAirDrop[playerid][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, ModelItemAirDrop[playerid][2], 19793);
    PlayerTextDrawSetPreviewRot(playerid, ModelItemAirDrop[playerid][2], -10.000000, 0.000000, -20.000000, 1.300000);
    PlayerTextDrawSetPreviewVehCol(playerid, ModelItemAirDrop[playerid][2], 1, 1);

    ModelItemAirDrop[playerid][3] = CreatePlayerTextDraw(playerid, 357.500000, 175.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, ModelItemAirDrop[playerid][3], 5);
    PlayerTextDrawLetterSize(playerid, ModelItemAirDrop[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, ModelItemAirDrop[playerid][3], 76.000000, 87.500000);
    PlayerTextDrawSetOutline(playerid, ModelItemAirDrop[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, ModelItemAirDrop[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, ModelItemAirDrop[playerid][3], 1);
    PlayerTextDrawColor(playerid, ModelItemAirDrop[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, ModelItemAirDrop[playerid][3], -1962934147);
    PlayerTextDrawBoxColor(playerid, ModelItemAirDrop[playerid][3], 255);
    PlayerTextDrawUseBox(playerid, ModelItemAirDrop[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, ModelItemAirDrop[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, ModelItemAirDrop[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, ModelItemAirDrop[playerid][3], 19793);
    PlayerTextDrawSetPreviewRot(playerid, ModelItemAirDrop[playerid][3], -10.000000, 0.000000, -20.000000, 1.300000);
    PlayerTextDrawSetPreviewVehCol(playerid, ModelItemAirDrop[playerid][3], 1, 1);

    ModelItemAirDrop[playerid][4] = CreatePlayerTextDraw(playerid, 320.000000, 264.000000, "AIRDROP BOX #1");
    PlayerTextDrawFont(playerid, ModelItemAirDrop[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, ModelItemAirDrop[playerid][4], 0.429166, 1.800000);
    PlayerTextDrawTextSize(playerid, ModelItemAirDrop[playerid][4], 400.000000, 224.000000);
    PlayerTextDrawSetOutline(playerid, ModelItemAirDrop[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, ModelItemAirDrop[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, ModelItemAirDrop[playerid][4], 2);
    PlayerTextDrawColor(playerid, ModelItemAirDrop[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, ModelItemAirDrop[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, ModelItemAirDrop[playerid][4], 130);
    PlayerTextDrawUseBox(playerid, ModelItemAirDrop[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, ModelItemAirDrop[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, ModelItemAirDrop[playerid][4], 0);

    ModelItemAirDrop[playerid][5] = CreatePlayerTextDraw(playerid, 245.000000, 245.000000, "100 EA");
    PlayerTextDrawFont(playerid, ModelItemAirDrop[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, ModelItemAirDrop[playerid][5], 0.275000, 1.350000);
    PlayerTextDrawTextSize(playerid, ModelItemAirDrop[playerid][5], 400.000000, 57.000000);
    PlayerTextDrawSetOutline(playerid, ModelItemAirDrop[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, ModelItemAirDrop[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, ModelItemAirDrop[playerid][5], 2);
    PlayerTextDrawColor(playerid, ModelItemAirDrop[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, ModelItemAirDrop[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, ModelItemAirDrop[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, ModelItemAirDrop[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, ModelItemAirDrop[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, ModelItemAirDrop[playerid][5], 0);

    ModelItemAirDrop[playerid][6] = CreatePlayerTextDraw(playerid, 321.000000, 245.000000, "100 EA");
    PlayerTextDrawFont(playerid, ModelItemAirDrop[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, ModelItemAirDrop[playerid][6], 0.275000, 1.350000);
    PlayerTextDrawTextSize(playerid, ModelItemAirDrop[playerid][6], 400.000000, 57.000000);
    PlayerTextDrawSetOutline(playerid, ModelItemAirDrop[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, ModelItemAirDrop[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, ModelItemAirDrop[playerid][6], 2);
    PlayerTextDrawColor(playerid, ModelItemAirDrop[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, ModelItemAirDrop[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, ModelItemAirDrop[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, ModelItemAirDrop[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, ModelItemAirDrop[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, ModelItemAirDrop[playerid][6], 0);

    ModelItemAirDrop[playerid][7] = CreatePlayerTextDraw(playerid, 396.000000, 245.000000, "100 EA");
    PlayerTextDrawFont(playerid, ModelItemAirDrop[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, ModelItemAirDrop[playerid][7], 0.275000, 1.350000);
    PlayerTextDrawTextSize(playerid, ModelItemAirDrop[playerid][7], 400.000000, 57.000000);
    PlayerTextDrawSetOutline(playerid, ModelItemAirDrop[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, ModelItemAirDrop[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, ModelItemAirDrop[playerid][7], 2);
    PlayerTextDrawColor(playerid, ModelItemAirDrop[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, ModelItemAirDrop[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, ModelItemAirDrop[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, ModelItemAirDrop[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, ModelItemAirDrop[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, ModelItemAirDrop[playerid][7], 0);
    return 1;
}