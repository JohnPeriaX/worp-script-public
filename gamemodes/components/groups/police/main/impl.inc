#if defined _inc_impl
	#undef _inc_impl
#endif

ResetPoliceVar(playerid){
    GetPlayerPrisonID[playerid] = -1;
    GetPlayerSuspectID[playerid] = -1;
    GetPlayerFriskID[playerid] = -1;
    PoliceGetSupID[playerid] = -1;
    LastShotgunWeapon[playerid] = 0;
    LastShotgunAmmo[playerid] = 0;
    CanFriskHome[playerid] = 0;
    CanFriskHomeTime[playerid] = 0;
    return 1;
}

forward Arrest_Load();
public Arrest_Load(){
    new rows;

    cache_get_row_count(rows);

    for(new i=0; i<rows; i++) if(!ArrestData[i][arrestEx]){
        ArrestData[i][arrestEx] = true;
        cache_get_value_name_int(i, "arrestID", ArrestData[i][arrestID]);
        cache_get_value_name_float(i, "arrestPosX", ArrestData[i][arrestPos][0]);
        cache_get_value_name_float(i, "arrestPosY", ArrestData[i][arrestPos][1]);
        cache_get_value_name_float(i, "arrestPosZ", ArrestData[i][arrestPos][2]);
        cache_get_value_name_int(i, "arrestInt", ArrestData[i][arrestInt]);
        cache_get_value_name_int(i, "arrestWorld", ArrestData[i][arrestWorld]);

        count_arrest++;

 	    Arrest_Refresh(i);
    }
    printf("(( [MYSQL]: Load %d Arrests Successfully ))", count_arrest);
    return 1;
}

Arrest_Save(arrestid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `arrests` SET `arrestPosX` = '%.4f', `arrestPosY` = '%.4f', `arrestPosZ` = '%.4f', `arrestInt` = '%d', `arrestWorld` = '%d' WHERE `arrestID` = '%d'",
		ArrestData[arrestid][arrestPos][0],
	    ArrestData[arrestid][arrestPos][1],
	    ArrestData[arrestid][arrestPos][2],
	    ArrestData[arrestid][arrestInt],
	    ArrestData[arrestid][arrestWorld],
        ArrestData[arrestid][arrestID]
	);
	return mysql_tquery(dbCon, query);
}

Arrest_Refresh(arrestid){
    if(arrestid != -1 && ArrestData[arrestid][arrestEx]){
        if (IsValidDynamic3DTextLabel(ArrestData[arrestid][arrestText3D]))
            DestroyDynamic3DTextLabel(ArrestData[arrestid][arrestText3D]);

        if (IsValidDynamicPickup(ArrestData[arrestid][arrestPickup]))
            DestroyDynamicPickup(ArrestData[arrestid][arrestPickup]);

        new string[40];

        format(string, sizeof(string), "[จุดส่งเข้าเรือนจำ]\n กด 'Y'");
        ArrestData[arrestid][arrestText3D] = CreateDynamic3DTextLabel(string, 0xFF0000FF, ArrestData[arrestid][arrestPos][0], ArrestData[arrestid][arrestPos][1], ArrestData[arrestid][arrestPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, ArrestData[arrestid][arrestWorld], ArrestData[arrestid][arrestInt]);
	    ArrestData[arrestid][arrestPickup] = CreateDynamicPickup(1239, 23, ArrestData[arrestid][arrestPos][0], ArrestData[arrestid][arrestPos][1], ArrestData[arrestid][arrestPos][2], ArrestData[arrestid][arrestWorld], ArrestData[arrestid][arrestInt]);
    }
    return 1;
}

Arrest_Create(playerid){
    new Float:x, Float:y, Float:z;
    if (GetPlayerPos(playerid, x, y, z)){
        for(new i=0; i<MAX_ARRESTS; i++) if(!ArrestData[i][arrestEx]){
            ArrestData[i][arrestEx] = true;
            ArrestData[i][arrestPos][0] = x;
            ArrestData[i][arrestPos][1] = y;
            ArrestData[i][arrestPos][2] = z;
            ArrestData[i][arrestInt] = GetPlayerInterior(playerid);
            ArrestData[i][arrestWorld] = GetPlayerVirtualWorld(playerid);

            Arrest_Refresh(i);
            mysql_tquery(dbCon, "INSERT INTO `arrests` (`arrestInt`) VALUES(0)", "OnArrestCreated", "d", i);
            return i;
        }
    }
    return -1;
}

stock Arrest_Remove(arrestid)
{
	if (arrestid != -1 && ArrestData[arrestid][arrestEx])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `arrest` WHERE `arrestID` = '%d' LIMIT 1", ArrestData[arrestid][arrestID]);
		mysql_tquery(dbCon, string);

        if (IsValidDynamic3DTextLabel(ArrestData[arrestid][arrestText3D]))
            DestroyDynamic3DTextLabel(ArrestData[arrestid][arrestText3D]);

        if (IsValidDynamicPickup(ArrestData[arrestid][arrestPickup]))
            DestroyDynamicPickup(ArrestData[arrestid][arrestPickup]);

	    ArrestData[arrestid][arrestEx] = false;
	    ArrestData[arrestid][arrestID] = 0;
	}
	return 1;
}

forward OnArrestCreated(arrestid);
public OnArrestCreated(arrestid)
{
	if (arrestid == -1 || !ArrestData[arrestid][arrestEx])
	    return 0;

	ArrestData[arrestid][arrestID] = cache_insert_id();
	Arrest_Save(arrestid);

	return 1;
}

Arrest_Nearest(playerid)
{
    for (new i = 0; i != MAX_ARRESTS; i ++) if (ArrestData[i][arrestEx] && IsPlayerInRangeOfPoint(playerid, 2.5, ArrestData[i][arrestPos][0], ArrestData[i][arrestPos][1], ArrestData[i][arrestPos][2]))
	{
		if (GetPlayerInterior(playerid) == ArrestData[i][arrestInt] && GetPlayerVirtualWorld(playerid) == ArrestData[i][arrestWorld])
			return i;
	}
	return -1;
}

ShowPlayerLockerPolice(playerid, id){
	new caption[128], string[128];
	format(caption, sizeof(caption), "Locker ของ %s", GroupData[id][groupName]);
	format(string, sizeof(string), "- เริ่มปฏิบัติงาน/เลิกทำงาน\n- เปลี่ยนชุด\n- เบิกอุปกรณ์\n- คลังเงิน");
	Dialog_ShowEasy(playerid, LockerPolice, DIALOG_STYLE_LIST, caption, string, "เลือก", "ยกเลิก");
	return 1;
}

Dialog:LockerPolice(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    new string[128];
    if(response){
        if(listitem == 0){
            if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_ONDUTY)){
                BitFlag_On(g_PlayerFlags[playerid], PLAYER_ONDUTY);
                SetGroupColor(playerid);
                PlayerData[playerid][pOnPlayerDuty] = 1;

                if(PlayerData[playerid][pMyWeapon][0] != 0){
                    PlayerData[playerid][pDelayWeapon][0] = 0; 
                    OnPlayerStoreWeapon1(playerid, PlayerData[playerid][pMyWeapon][0]);
                }

                if(PlayerData[playerid][pMyWeapon][1] != 0){
                    PlayerData[playerid][pDelayWeapon][1] = 0; 
                    OnPlayerStoreWeapon2(playerid, PlayerData[playerid][pMyWeapon][1]);
                }

                if(PlayerData[playerid][pMyWeapon][2] != 0){
                    PlayerData[playerid][pDelayWeapon][2] = 0; 
                    OnPlayerStoreWeapon3(playerid, PlayerData[playerid][pMyWeapon][2]);
                }

                SendFactionMessage(PlayerData[playerid][pGroup], COLOR_RADIO, "(( [HQ] %s %s: ได้เริ่มปฏิบัติหน้าที่แล้วในขณะนี้ ))", Group_GetRank(playerid), ReturnRoleplayName(playerid));
                /*if(PlayerInParty[playerid] && PlayerPartyGetID[playerid] != -1){
                    UpdatePartyTextDrawForPlayer(playerid, PlayerPartyGetID[playerid]);
                }*/
            }
            else{
                BitFlag_Off(g_PlayerFlags[playerid], PLAYER_ONDUTY);
                SetPlayerColor(playerid, 0xFFFFFF00);
                SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
                PlayerData[playerid][pOnPlayerDuty] = 0;
                SetPlayerArmour(playerid, 0);
                SendFactionMessage(PlayerData[playerid][pGroup], COLOR_RADIO, "(( [HQ] %s %s: ได้เลิกปฏิบัติหน้าที่แล้วในขณะนี้ ))", Group_GetRank(playerid), ReturnRoleplayName(playerid));
                /*if(PlayerInParty[playerid] && PlayerPartyGetID[playerid] != -1){
                    UpdatePartyTextDrawForPlayer(playerid, PlayerPartyGetID[playerid]);
                }*/
            }
        }
        if(listitem == 1){
            if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_ONDUTY))
                return ErrorMsg(playerid, "คุณจำเป็นต้องปฏิบัติหน้าที่ก่อน");

            ShowGroupSkin(playerid, PlayerData[playerid][pGroup]);
        }
        if(listitem == 2){
            
            if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_ONDUTY))
                return ErrorMsg(playerid, "คุณจำเป็นต้องปฏิบัติหน้าที่ก่อน");

            Dialog_ShowEasy(playerid, PoliceToolMenu, DIALOG_STYLE_LIST, "อุปกรณ์เจ้าหน้าที่ตำรวจ", "- เสื้อเกราะ\n- อาวุธต่างๆ", "เลือก", "ยกเลิก");
        }
        if(listitem == 3){
            if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_NATIONAL){
                if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                    format(string, sizeof(string), "เงินในคลัง: %s", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
                    Dialog_ShowEasy(playerid, MoneyLockerPoliceShow, DIALOG_STYLE_LIST, "คลังเงิน", string, "ตกลง", "");
                }
                else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                    format(string, sizeof(string), "เงินในคลัง: %s", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
                    Dialog_ShowEasy(playerid, MoneyLockerPolice, DIALOG_STYLE_LIST, "คลังเงิน", string, "ตกลง", "ยกเลิก");
                }
            }
        }
    }
    return 1;
}

Dialog:MoneyLockerPolice(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new string[128];
            format(string, sizeof(string), "เงินในคลัง: %s\nกรอกจำนวนที่คุณต้องการจะเบิก:", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
            Dialog_ShowEasy(playerid, WithDrawMoneyLocker, DIALOG_STYLE_INPUT, "คลังเงิน > เบิก", string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:WithDrawMoneyLocker(playerid, response, listitem, inputtext[]){
    if(!response)   return 1;
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนเงินมากกว่า 0");

        if(amount > GroupData[PlayerData[playerid][pGroup]][groupMoney])
            return ErrorMsg(playerid, "จำนวนเงินในคลังมีไม่เพียงพอ");

        GiveMoney(playerid, amount, "withdraw locker");
        GroupData[PlayerData[playerid][pGroup]][groupMoney] -= amount;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], COLOR_RADIO, "(( [%s] %s(%d) ได้ทำการเบิกเงินคลังของกลุ่มออกมาจำนวน: %s ))", Group_GetRank(playerid), ReturnRoleplayName(playerid), playerid, FormatNumber(amount));
        new string[256];
        format(string, sizeof(string), "```> [%s] (%d) %s(%d) Withdraw Money from Storage Group [%s]```", ReturnDate(), PlayerData[playerid][pGroupRank], ReturnRoleplayName(playerid), playerid, FormatNumber(amount));
		DCC_SendChannelMessage(WithdrawPolice, string);
    }
    return 1;
}

Dialog:PoliceToolMenu(playerid, response, listitem, inputtext[]){
    new groupid = PlayerData[playerid][pGroup];
    new string[256];
    if(response){
        if(listitem == 0){
            SetPlayerArmour(playerid, 100);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้หยิบเสื้อเกราะออกมาแล้วใส่มัน", ReturnRoleplayName(playerid));
        }
        if(listitem == 1){
            for (new i = 0; i < 10; i ++)
            {
                if (GroupData[groupid][groupWeapons][i])
                    format(string, sizeof(string), "%sอาวุธ %d: %s (%d)\n", string, i + 1, ReturnWeaponName(GroupData[groupid][groupWeapons][i]), GroupData[groupid][groupAmmo][i]);

                else format(string, sizeof(string), "%sว่าง\n", string);
            }
            Dialog_ShowEasy(playerid, LockerWeapons, DIALOG_STYLE_LIST, "คลังอาวุธ", string, "เลือก", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:LockerWeapons(playerid, response, listitem, inputtext[]){
	new groupid = PlayerData[playerid][pGroup];
	if (groupid == -1)
		return 0;

	if (response)
	{
		if(listitem < 0 || listitem >= 10) { SecurityAC_Report(playerid, "bad-police-weapon-listitem", false); return 0; }
	    new
	        weaponid = GroupData[groupid][groupWeapons][listitem],
	        ammo = GroupData[groupid][groupAmmo][listitem];

	    if (weaponid != 0){
            
            if(weaponid == 31){
                if(PlayerData[playerid][pGroupRank] < 2) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติให้เบิกอาวุธชนิดนี้");
            }

            GivePlayerWeapon(playerid, weaponid, ammo);
	        SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s เอื้อมมือเข้าไปในตู้เก็บของและหยิบ %s", ReturnRoleplayName(playerid), ReturnWeaponName(weaponid));
		}
	}
	return 1;
}

//AdminCMDS

CMD:arrestcmds(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[ARRESTCMDS]: /makearrest, /removearrest, /editarrest, /arrestrefresh");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
    return 1;
}

CMD:friskhome(playerid, params[]){
    if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้คำสั่งนี้ได้ในขณะนี้");

	if (GetGroupType(playerid) != GROUP_POLICE)
		return ErrorMsg(playerid, "คุณต้องเป็นเจ้าหน้าที่ตำรวจ");

    new id = Home_Inside(playerid);
    if(id == -1) return ErrorMsg(playerid, "คุณต้องอยู่ภายในบ้านเท่านั้น");

    new userid, string[128];
    if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/friskhome [playerid]");
    if(userid == playerid) return 1;
    if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
    if(!LoggedIn[userid]) return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
    if(!IsPlayerNearPlayer(playerid, userid, 5.0)) return ErrorMsg(playerid, "ผู้เล่นนั้นไม่ได้อยู่ใกล้คุณ");

    if(HomeData[id][homeOwner] != PlayerData[userid][pID]) return ErrorMsg(playerid, "คุณต้องอยู่ในบ้านของคนที่จะค้นเท่านั้น");

    SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ส่งคำขอค้นบ้านไปยัง %s(%d) เรียบร้อยแล้ว รอการตอบกลับ...", ReturnRoleplayName(userid), userid);
    format(string, sizeof string, "เจ้าหน้าที่ %s(%d) ได้ยื่นคำขอในการค้นบ้านของคุณ", ReturnRoleplayName(playerid), playerid);
    SetPVarInt(userid, "PlayerIDFriskHome", playerid);
    Dialog_ShowEasy(userid, RequestFriskHome, DIALOG_STYLE_MSGBOX, "การขอค้นบ้าน", string, "ตกลง", "ปฏิเสธ");
    return 1;
}

Dialog:RequestFriskHome(playerid, response, listitem, inputtext[]){
    new string[128];
    if(!response){
        new userid = GetPVarInt(playerid, "PlayerIDFriskHome");
        SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้ปฏิเสธการขอค้นบ้านเรียบร้อยแล้ว");
        format(string, sizeof string, "ผู้เล่น %s(%d) ได้ทำการปฏิเสธการขอค้นบ้านของคุณ", ReturnRoleplayName(playerid), playerid);
        Dialog_ShowEasy(userid, ShowOnly, DIALOG_STYLE_MSGBOX, "การปฏิเสธ", string, "ตกลง", "");
        DeletePVar(playerid, "PlayerIDFriskHome");
        return 1;
    }
    if(response){
        new userid = GetPVarInt(playerid, "PlayerIDFriskHome");
        format(string, sizeof string, "ผู้เล่น %s(%d) ได้ทำการยอมรับการขอค้นบ้านของคุณแล้ว\
        \nคุณมีสิทธ์ในการค้นบ้านเป็นเวลา 5 นาทีหรือจนกว่าคุณจะออกเกม", ReturnRoleplayName(playerid), playerid);
        Dialog_ShowEasy(userid, ShowOnly, DIALOG_STYLE_MSGBOX, "การขอถูกยอมรับ", string, "ตกลง", "");

        CanFriskHomeTime[userid] = 300;
        CanFriskHome[userid] = PlayerData[playerid][pID];

        DeletePVar(playerid, "PlayerIDFriskHome");
    }
    return 1;
}

CMD:breakhome(playerid, params[]){
    if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้คำสั่งนี้ได้ในขณะนี้");

	if (GetGroupType(playerid) != GROUP_POLICE)
		return ErrorMsg(playerid, "คุณต้องเป็นเจ้าหน้าที่ตำรวจ");

    if(PlayerData[playerid][pGroupRank] < 10) return ErrorMsg(playerid, "ตำแหน่งของคุณไม่ได้รับอนุญาติในการใช้คำสั่งนี้");
    new id = -1;
    if((id = Home_Nearest(playerid)) != -1){
        if(!HomeData[id][homeLocked]) return ErrorMsg(playerid, "บ้านหลังนี้ไม่ได้ถูกล็อคอยู่");

        new bool:checked = false;

        foreach(new i : Player){
            if(!LoggedIn[i]) continue;
            if(PlayerData[i][pID] == HomeData[id][homeOwner]){
                checked = true;
                break;
            }
        }

        if(checked){
            ApplyAnimation(playerid, "POLICE", "Door_Kick", 4.0, 0, 0, 0, 0, 0);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s พยายามที่จะถีบประตูของบ้านให้ล้มลง", ReturnRoleplayName(playerid));
	        SetTimerEx("KickHouse", 1500, false, "dd", playerid, id);
        }
        else return ErrorMsg(playerid, "เจ้าของบ้านไม่ออนไลน์คุณไม่สามารถพังประตูบ้านนี้ได้");
    }
    return 1;
}

forward KickHouse(playerid, id);
public KickHouse(playerid, id){
	if (GetGroupType(playerid) != GROUP_POLICE || Home_Nearest(playerid) != id)
	    return 0;

	switch (random(6)){
	    case 0..2:{
	        SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ล้มเหลวในการถีบประตูให้ล้มลง", ReturnRoleplayName(playerid));
		}
		default:{
		    HomeData[id][homeLocked] = 0;
		    Home_Save(id);

		    SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้ประสบความสำเร็จในการถีบประตูให้ล้มลง", ReturnRoleplayName(playerid));
		}
	}
	return 1;
}

CMD:makearrest(playerid, params[]){
    if(!LoggedIn[playerid])
        return 0;

    if(PlayerData[playerid][pAdmin] >= 1338){
        new id = -1;

        id = Arrest_Create(playerid);

        if(id == -1)
            return ErrorMsg(playerid, "เซิฟเวอร์ได้สร้างจุดส่งคุกเกินขีดจำกัดแล้ว");

        SendClientMessageEx(playerid, -1, "- คุณได้ประสบความสำเร็จในการสร้าง จุดส่งคุก ไอดี: %d", id);
    }
    return 1;
}

CMD:removearrest(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	new id = -1;

	if (sscanf(params, "d", id))
		return SendClientMessage(playerid, -1, "/removearrest [arrest id]");

	if ((id < 0 || id >= MAX_ARRESTS) || !ArrestData[id][arrestEx])
		return SendClientMessage(playerid, -1, "คุณระบุไอดี Arrest ไม่ถูกต้อง");

	Arrest_Remove(id);
	SendClientMessageEx(playerid, -1, "คุณประสบความสำเร็จในการทำลาย Arrest ไอดี: %d", id);
	return 1;
}
//--------------------------------------------------//

ShowSendPlayerToPrisonDialog(playerid){
    new stringplayer[1024];
    new count;
    new menu[20];
    foreach(new x : Player){
        if(!LoggedIn[x]) continue;
        if(x == playerid) continue;
        if(IsPlayerNearPlayer(playerid, x, 5.0)){
            format(menu, 20, "menu%d", count++);
            SetPVarInt(playerid, menu, x);
            format(stringplayer, sizeof(stringplayer), "%s %s(%d)\n", stringplayer, ReturnRoleplayName(x), x);
        }
        if(count >= 20) break;
    }
    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "เลือกผู้เล่นที่จะส่งเข้าเรือนจำ", "ไม่มีใครอยู่ใกล้คุณเลย", "ตกลง", "ยกเลิก");
    else Dialog_ShowEasy(playerid, SendPlayerToPrison, DIALOG_STYLE_LIST, "เลือกผู้เล่นที่จะส่งเข้าเรือนจำ", stringplayer, "เลือก", "ยกเลิก");
    /*format(string, sizeof(string), "กรอกชื่อไอดีผู้เล่นที่ต้องการจะส่งเข้าเรือนจำ");
    Dialog_ShowEasy(playerid, SendPlayerToPrison, DIALOG_STYLE_INPUT, "การส่งเข้าเรือนจำ", string, "ตกลง", "ยกเลิก");*/
    return 1;
}

Dialog:SendPlayerToPrison(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "playerID", GetPVarInt(playerid, str_biz));
			SendPlayerTargetToPrison(playerid);
			return 1;
		}
    }
    return 1;
}

SendPlayerTargetToPrison(playerid){
    new targetid = GetPVarInt(playerid, "playerID");
	new string[128];
    if(targetid == INVALID_PLAYER_ID){
        ErrorMsg(playerid, "ไอดีผู้เล่นผิดพลาด");
        return ShowSendPlayerToPrisonDialog(playerid);
    }

    if(!LoggedIn[targetid]){
        ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        return ShowSendPlayerToPrisonDialog(playerid);
    }

    if (!IsPlayerNearPlayer(playerid, targetid, 5.0)){
        ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้นหรือผู้เล่นนั้นห่างคุณออกไป");
        return ShowSendPlayerToPrisonDialog(playerid);
    }

    GetPlayerPrisonID[playerid] = targetid;
    format(string, sizeof(string), "%s", ReturnPlayerName(targetid));
    Dialog_ShowEasy(playerid, SendPrisonTime, DIALOG_STYLE_INPUT, string, "กรอกจำนวนเวลาที่ต้องการจะส่งเข้าเรือนจำ (วินาที):", "ตกลง", "ยกเลิก");
    return 1;
}

/*Dialog:SendPlayerToPrison(playerid, response, listitem, inputtext[]){
    if(!response)  return GetPlayerPrisonID[playerid] = -1;
    if(response){
        new userid = strval(inputtext);
        new string[128];

        if(userid == INVALID_PLAYER_ID){
            format(string, sizeof(string), "* กรอกไอดีผู้เล่นไม่ถูกต้อง *\nกรอกชื่อไอดีผู้เล่นที่ต้องการจะส่งเข้าเรือนจำ");
            return Dialog_ShowEasy(playerid, SendPlayerToPrison, DIALOG_STYLE_INPUT, "การส่งเข้าเรือนจำ", string, "ตกลง", "ยกเลิก");
        }

        if(!LoggedIn[userid]){
            format(string, sizeof(string), "* ผู้เล่นนั้นยังไม่ได้ล็อคอิน *\nกรอกชื่อไอดีผู้เล่นที่ต้องการจะส่งเข้าเรือนจำ");
            return Dialog_ShowEasy(playerid, SendPlayerToPrison, DIALOG_STYLE_INPUT, "การส่งเข้าเรือนจำ", string, "ตกลง", "ยกเลิก");
        }

        if (!IsPlayerNearPlayer(playerid, userid, 5.0)){
            format(string, sizeof(string), "* ผู้เล่นนั้นไม่ได้อยู่ใกล้คุณ *\nกรอกชื่อไอดีผู้เล่นที่ต้องการจะส่งเข้าเรือนจำ");
            return Dialog_ShowEasy(playerid, SendPlayerToPrison, DIALOG_STYLE_INPUT, "การส่งเข้าเรือนจำ", string, "ตกลง", "ยกเลิก");
        }

        GetPlayerPrisonID[playerid] = userid;
        format(string, sizeof(string), "%s", ReturnPlayerName(userid));
        Dialog_ShowEasy(playerid, SendPrisonTime, DIALOG_STYLE_INPUT, string, "กรอกจำนวนเวลาที่ต้องการจะส่งเข้าเรือนจำ (วินาที):", "ตกลง", "ยกเลิก");
    }
    return 1;
}*/

Dialog:SendPrisonTime(playerid, response, listitem, inputtext[]){
    if(!response)   return GetPlayerPrisonID[playerid] = -1;
    if(response){
        new time = strval(inputtext);
        new userid = GetPlayerPrisonID[playerid];
        new string[128];

        if(userid == INVALID_PLAYER_ID)
            return ErrorMsg(playerid, "คุณกรอกไอดีผู้เล่นไม่ถูกต้อง");

        if(!LoggedIn[userid])
            return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้ล็อคอิน");

        if (!IsPlayerNearPlayer(playerid, userid, 5.0))
            return ErrorMsg(playerid, "ผู้เล่นนั้นไม่ได้อยู่ใกล้คุณ");

        if(time <= 0){
            format(string, sizeof(string), "%s", ReturnPlayerName(userid));
            return Dialog_ShowEasy(playerid, SendPrisonTime, DIALOG_STYLE_INPUT, string, "กรอกจำนวนเวลาที่ต้องการจะส่งเข้าเรือนจำ (วินาที):", "ตกลง", "ยกเลิก");
        }
            
        PlayerData[userid][pJail] = 1;
        PlayerData[userid][pJailTime] = time;
	    RemoveCharges(ReturnName(userid));
        ResetPlayerDrag(userid);
        ResetPlayerWeapons(userid);
        ResetPlayer(userid);
        BitFlag_Off(g_PlayerFlags[userid],PLAYER_CUFFED);
        SetPlayerSpecialAction(userid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(userid, 7);
        TogglePlayerControllable(userid, 1);
        GetPlayerPrisonID[playerid] = -1;
        SendPlayerToPrisonNow(userid);
        PlayerData[userid][pCuffed] = 0;
        SendClientMessageEx(playerid, COLOR_ORANGE, "- คุณถูกส่งเข้าเรือนจำเป็นเวลา %d วินาที โดย เจ้าหน้าที่ %s", time, ReturnRoleplayName(playerid));
        SendFactionMessage(PlayerData[playerid][pGroup], COLOR_RADIO, "(( %s ถูกส่งเข้าเรือนจำเป็นเวลา %d วินาที โดยเจ้าหน้าที่ [%s] %s(%d) ))", ReturnRoleplayName(userid), time, Group_GetRank(playerid), ReturnRoleplayName(playerid), playerid);
    }
    return 1;
}

SendPlayerToPrisonNow(playerid){
    SetPlayerPosEx(playerid, 201.6343,1424.2471,10.5930, 0, 0);
    SetPlayerFacingAngle(playerid, 275.2320);
    SetCameraBehindPlayer(playerid);
    SetPlayerSkin(playerid, 268);
    BitFlag_On(g_PlayerFlags[playerid], PLAYER_PHONE_OFF);
    return 1;
}

ShowPoliceMDC(playerid){
    new string[128];
    format(string, sizeof(string), "ค้นหาประวัติ\nเพิ่มข้อหา\nดูข้อหา\nค้นหาป้ายทะเบียนรถ");
    Dialog_ShowEasy(playerid, MDCPOLICE, DIALOG_STYLE_LIST, "MDC", string, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:MDCPOLICE(playerid, response, listitem, inputtext[]){
    if(!response)   return 1;
    if(response){
        if(listitem == 0){
            Dialog_ShowEasy(playerid, MdcPlayerInfo, DIALOG_STYLE_INPUT, "MDC > ค้นหาประวัติ", "กรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการค้นหาประวัติ: ", "ตกลง", "กลับ");
        }
        if(listitem == 1){
            Dialog_ShowEasy(playerid, InputSuspect, DIALOG_STYLE_INPUT, "MDC > เพิ่มข้อหา", "กรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการค้นเพิ่มข้อหา: ", "ตกลง", "ยกเลิก");
        }
        if(listitem == 2){
            Dialog_ShowEasy(playerid, SeeSuspect, DIALOG_STYLE_INPUT, "MDC > ดูข้อหา", "กรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการดูข้อหา: ", "ตกลง", "ยกเลิก");
        }
        if(listitem == 3){
            Dialog_ShowEasy(playerid, PlateVeh, DIALOG_STYLE_INPUT, "MDC > ค้นหาป้ายทะเบียน", "กรอกป้ายทะเบียน:", "ตกลง", "กลับ");
        }
    }
    return 1;
}

Dialog:PlateVeh(playerid, response, listitem, inputtext[]){
    if(!response)  return ShowPoliceMDC(playerid);
    if(response){
        if (isnull(inputtext) || strlen(inputtext) > 32)
		    return  Dialog_ShowEasy(playerid, PlateVeh, DIALOG_STYLE_INPUT, "MDC > ค้นหาป้ายทะเบียน", "กรอกป้ายทะเบียน:", "ตกลง", "กลับ");

        new
			str[128];

		mysql_format(dbCon, str,sizeof(str),"SELECT * FROM cars WHERE carPlate = '%e' LIMIT 1", inputtext);
		mysql_tquery(dbCon, str, "SearchPlate", "is", playerid, inputtext);

    }
    return 1;
}

static const g_arrSelectColors[256] = {
	0x000000FF, 0xF5F5F5FF, 0x2A77A1FF, 0x840410FF, 0x263739FF, 0x86446EFF, 0xD78E10FF, 0x4C75B7FF, 0xBDBEC6FF, 0x5E7072FF,
	0x46597AFF, 0x656A79FF, 0x5D7E8DFF, 0x58595AFF, 0xD6DAD6FF, 0x9CA1A3FF, 0x335F3FFF, 0x730E1AFF, 0x7B0A2AFF, 0x9F9D94FF,
	0x3B4E78FF, 0x732E3EFF, 0x691E3BFF, 0x96918CFF, 0x515459FF, 0x3F3E45FF, 0xA5A9A7FF, 0x635C5AFF, 0x3D4A68FF, 0x979592FF,
	0x421F21FF, 0x5F272BFF, 0x8494ABFF, 0x767B7CFF, 0x646464FF, 0x5A5752FF, 0x252527FF, 0x2D3A35FF, 0x93A396FF, 0x6D7A88FF,
	0x221918FF, 0x6F675FFF, 0x7C1C2AFF, 0x5F0A15FF, 0x193826FF, 0x5D1B20FF, 0x9D9872FF, 0x7A7560FF, 0x989586FF, 0xADB0B0FF,
	0x848988FF, 0x304F45FF, 0x4D6268FF, 0x162248FF, 0x272F4BFF, 0x7D6256FF, 0x9EA4ABFF, 0x9C8D71FF, 0x6D1822FF, 0x4E6881FF,
	0x9C9C98FF, 0x917347FF, 0x661C26FF, 0x949D9FFF, 0xA4A7A5FF, 0x8E8C46FF, 0x341A1EFF, 0x6A7A8CFF, 0xAAAD8EFF, 0xAB988FFF,
	0x851F2EFF, 0x6F8297FF, 0x585853FF, 0x9AA790FF, 0x601A23FF, 0x20202CFF, 0xA4A096FF, 0xAA9D84FF, 0x78222BFF, 0x0E316DFF,
	0x722A3FFF, 0x7B715EFF, 0x741D28FF, 0x1E2E32FF, 0x4D322FFF, 0x7C1B44FF, 0x2E5B20FF, 0x395A83FF, 0x6D2837FF, 0xA7A28FFF,
	0xAFB1B1FF, 0x364155FF, 0x6D6C6EFF, 0x0F6A89FF, 0x204B6BFF, 0x2B3E57FF, 0x9B9F9DFF, 0x6C8495FF, 0x4D8495FF, 0xAE9B7FFF,
	0x406C8FFF, 0x1F253BFF, 0xAB9276FF, 0x134573FF, 0x96816CFF, 0x64686AFF, 0x105082FF, 0xA19983FF, 0x385694FF, 0x525661FF,
	0x7F6956FF, 0x8C929AFF, 0x596E87FF, 0x473532FF, 0x44624FFF, 0x730A27FF, 0x223457FF, 0x640D1BFF, 0xA3ADC6FF, 0x695853FF,
	0x9B8B80FF, 0x620B1CFF, 0x5B5D5EFF, 0x624428FF, 0x731827FF, 0x1B376DFF, 0xEC6AAEFF, 0x000000FF, 0x177517FF, 0x210606FF,
	0x125478FF, 0x452A0DFF, 0x571E1EFF, 0x010701FF, 0x25225AFF, 0x2C89AAFF, 0x8A4DBDFF, 0x35963AFF, 0xB7B7B7FF, 0x464C8DFF,
	0x84888CFF, 0x817867FF, 0x817A26FF, 0x6A506FFF, 0x583E6FFF, 0x8CB972FF, 0x824F78FF, 0x6D276AFF, 0x1E1D13FF, 0x1E1306FF,
	0x1F2518FF, 0x2C4531FF, 0x1E4C99FF, 0x2E5F43FF, 0x1E9948FF, 0x1E9999FF, 0x999976FF, 0x7C8499FF, 0x992E1EFF, 0x2C1E08FF,
	0x142407FF, 0x993E4DFF, 0x1E4C99FF, 0x198181FF, 0x1A292AFF, 0x16616FFF, 0x1B6687FF, 0x6C3F99FF, 0x481A0EFF, 0x7A7399FF,
	0x746D99FF, 0x53387EFF, 0x222407FF, 0x3E190CFF, 0x46210EFF, 0x991E1EFF, 0x8D4C8DFF, 0x805B80FF, 0x7B3E7EFF, 0x3C1737FF,
	0x733517FF, 0x781818FF, 0x83341AFF, 0x8E2F1CFF, 0x7E3E53FF, 0x7C6D7CFF, 0x020C02FF, 0x072407FF, 0x163012FF, 0x16301BFF,
	0x642B4FFF, 0x368452FF, 0x999590FF, 0x818D96FF, 0x99991EFF, 0x7F994CFF, 0x839292FF, 0x788222FF, 0x2B3C99FF, 0x3A3A0BFF,
	0x8A794EFF, 0x0E1F49FF, 0x15371CFF, 0x15273AFF, 0x375775FF, 0x060820FF, 0x071326FF, 0x20394BFF, 0x2C5089FF, 0x15426CFF,
	0x103250FF, 0x241663FF, 0x692015FF, 0x8C8D94FF, 0x516013FF, 0x090F02FF, 0x8C573AFF, 0x52888EFF, 0x995C52FF, 0x99581EFF,
	0x993A63FF, 0x998F4EFF, 0x99311EFF, 0x0D1842FF, 0x521E1EFF, 0x42420DFF, 0x4C991EFF, 0x082A1DFF, 0x96821DFF, 0x197F19FF,
	0x3B141FFF, 0x745217FF, 0x893F8DFF, 0x7E1A6CFF, 0x0B370BFF, 0x27450DFF, 0x071F24FF, 0x784573FF, 0x8A653AFF, 0x732617FF,
	0x319490FF, 0x56941DFF, 0x59163DFF, 0x1B8A2FFF, 0x38160BFF, 0x041804FF, 0x355D8EFF, 0x2E3F5BFF, 0x561A28FF, 0x4E0E27FF,
	0x706C67FF, 0x3B3E42FF, 0x2E2D33FF, 0x7B7E7DFF, 0x4A4442FF, 0x28344EFF
};

forward SearchPlate(playerid, plate[]);
public SearchPlate(playerid, plate[])
{
    new
		rows;

    cache_get_row_count(rows);

    if(rows)
    {
        new
			query[160];

        new modelid, c1, c2, ownerid, jobid, facid;

        cache_get_value_name_int(0, "carOwner", ownerid);
        cache_get_value_name_int(0, "carGroup", facid);
        cache_get_value_name_int(0, "carJob", jobid);
        cache_get_value_name_int(0, "carModel", modelid);
        cache_get_value_name_int(0, "carColor1", c1);
        cache_get_value_name_int(0, "carColor2", c2);

        if(ownerid > 0)
        {
             format(query, sizeof(query), "%s", GetIDFromName(ownerid));
        }
        else if(facid > 0)
        {
            format(query, sizeof(query), "Group %s", Group_GetName(facid));
        }
        else if(jobid > 0)
        {
            format(query, sizeof(query), "%s Job", Job_GetName(jobid));
        }
        new Float:x, Float:y, Float:z;
        for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
            if(!strcmp(CarData[i][carPlate], plate, true)){
                GetVehiclePos(CarData[i][carVehicle], x, y, z);
                break;
            }
        }

        SetPlayerCheckpoint(playerid, x, y, z, 10.0);
        PlayerEnterCheckPoint[playerid] = 1;

		format(query, sizeof(query), "{FFFFFF}ชื่อยานพาหนะ: %s\nVehicle Color: {%06x}#COLOR1{FFFFFF}/{%06x}#COLOR2{FFFFFF}\nชื่อเจ้าของ: %s\nป้ายทะเบียน: %s", ReturnVehicleModelName(modelid), g_arrSelectColors[c1] >>> 8, g_arrSelectColors[c2] >>> 8, query, plate);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "MDC > ค้นหาป้ายทะเบียน", query, "ปิด","");
    }
    else
    {
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "MDC > ค้นหาป้ายทะเบียน", "ไม่พบป้ายทะเบียนหมายเลขนี้", "ปิด","");
    }
	return 1;
}

Dialog:SeeSuspect(playerid, response, listitem, inputtext[]){
    if(!response)  return 1;
    if(response){
        new userid = strval(inputtext);
        if(userid == INVALID_PLAYER_ID)
            return Dialog_ShowEasy(playerid, SeeSuspect, DIALOG_STYLE_INPUT, "MDC > ดูข้อหา", "* กรอกไอดีไม่ถูกต้อง *\nกรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการดูข้อหา: ", "ตกลง", "ยกเลิก");

        if(!LoggedIn[userid])
            return Dialog_ShowEasy(playerid, SeeSuspect, DIALOG_STYLE_INPUT, "MDC > ดูข้อหา", "* ผู้เล่นนั้นยังไม่ได้ล็อคอิน *\nกรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการดูข้อหา: ", "ตกลง", "ยกเลิก");

        if (IsNumeric(inputtext)) {
	        ViewCharges(playerid, ReturnName(strval(inputtext)));
		}
        else if (!IsNumeric(inputtext))
            ViewCharges(playerid, inputtext);
    }
    return 1;
}

forward OnViewCharges(extraid, const name[]);
public OnViewCharges(extraid, const name[])
{
	if (GetGroupType(extraid) != GROUP_POLICE && GetGroupType(extraid) != GROUP_NATIONAL)
	    return 0;

	new
	    rows;

	cache_get_row_count(rows);

	if (!rows)
	    return ErrorMsg(extraid, "ไม่พบคำตอบของผู้กล่าวหา \"%s\"", name);

	new
	    string[512],
		desc[128],
		date[36];

	string[0] = 0;

	for (new i = 0; i < rows; i ++) {
        cache_get_value_name(i, "Description", desc, 128);
        cache_get_value_name(i, "Date", date, 36);

	    format(string, sizeof(string), "%s%s (%s)\n", string, desc, date);
	}
	format(desc, sizeof(desc), "ผู้กล่าวหา: %s", name);
	Dialog_ShowEasy(extraid, ChargeList, DIALOG_STYLE_LIST, desc, string, "ปิด", "");
	return 1;
}

stock ViewCharges(playerid, const name[])
{
	new
	    string[128];

	mysql_format(dbCon, string, sizeof(string), "SELECT * FROM `warrants` WHERE `Suspect` = '%e' ORDER BY `ID` DESC", name);
	mysql_tquery(dbCon, string, "OnViewCharges", "ds", playerid, name);
	return 1;
}

stock RemoveCharges(const name[]){
    new
	    string[128];

	mysql_format(dbCon, string, sizeof(string), "DELETE FROM `warrants` WHERE `Suspect` = '%e' LIMIT 1", name);
    mysql_tquery(dbCon, string);
    return 1;
}

Dialog:InputSuspect(playerid, response, listitem, inputtext[]){
    if(!response)   return 1;
    if(response){
        new caption[128];
        new userid = strval(inputtext);
        if(userid == INVALID_PLAYER_ID)
            return Dialog_ShowEasy(playerid, InputSuspect, DIALOG_STYLE_INPUT, "MDC > เพิ่มข้อหา", "* กรอกไอดีไม่ถูกต้อง *\nกรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการค้นเพิ่มข้อหา: ", "ตกลง", "ยกเลิก");

        if(!LoggedIn[userid])
            return Dialog_ShowEasy(playerid, InputSuspect, DIALOG_STYLE_INPUT, "MDC > เพิ่มข้อหา", "* ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ *\nกรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการค้นเพิ่มข้อหา: ", "ตกลง", "ยกเลิก");

        GetPlayerSuspectID[playerid] = userid;
        format(caption, sizeof(caption), "เพิ่มข้อหา > %s(%d)", ReturnRoleplayName(userid), userid);
        Dialog_ShowEasy(playerid, InputPlayerSuspect, DIALOG_STYLE_INPUT, caption, "ใส่ข้อหาที่คุณต้องการเพิ่ม: ", "ตกลง", "กลับ");
    }
    return 1;
}

Dialog:InputPlayerSuspect(playerid, response, listitem, inputtext[]){
    if(!response){
        GetPlayerSuspectID[playerid] = -1;
        return Dialog_ShowEasy(playerid, InputSuspect, DIALOG_STYLE_INPUT, "MDC > เพิ่มข้อหา", "กรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการค้นหาประวัติ: ", "ตกลง", "ยกเลิก");
    }
    if(response){
        new caption[128];
        new userid = GetPlayerSuspectID[playerid];
        
        if(userid == INVALID_PLAYER_ID)
            return Dialog_ShowEasy(playerid, InputSuspect, DIALOG_STYLE_INPUT, "MDC > เพิ่มข้อหา", "* กรอกไอดีไม่ถูกต้อง *\nกรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการค้นเพิ่มข้อหา: ", "ตกลง", "ยกเลิก");

        if(!LoggedIn[userid])
            return Dialog_ShowEasy(playerid, InputSuspect, DIALOG_STYLE_INPUT, "MDC > เพิ่มข้อหา", "* ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ *\nกรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการค้นเพิ่มข้อหา: ", "ตกลง", "ยกเลิก");

        if(isnull(inputtext)){
            format(caption, sizeof(caption), "เพิ่มข้อหา > %s(%d)", ReturnRoleplayName(userid), userid);
            return Dialog_ShowEasy(playerid, InputPlayerSuspect, DIALOG_STYLE_INPUT, caption, "ใส่ข้อหาที่คุณต้องการเพิ่ม: ", "ตกลง", "กลับ");
        }

        if(strlen(inputtext) < 128){
            format(caption, sizeof(caption), "[!] ข้อหาต้องน้อยกว่า 128 ตัวอักษร\nเพิ่มข้อหา > %s(%d)", ReturnRoleplayName(userid), userid);
            return Dialog_ShowEasy(playerid, InputPlayerSuspect, DIALOG_STYLE_INPUT, caption, "ใส่ข้อหาที่คุณต้องการเพิ่ม: ", "ตกลง", "กลับ");
        }

        AddWarrant(userid, playerid, inputtext);
        SendClientMessageEx(userid, COLOR_ORANGE, "- คุณถูกตั้งข้อหาว่า: %s โดยเจ้าหน้าที่ %s", inputtext, ReturnRoleplayName(playerid));
        SendFactionMessage(PlayerData[playerid][pGroup], COLOR_RADIO, "(( %s ได้ถูกตั้งข้อหาว่า: %s โดยเจ้าหน้าที่ [%s] %s(%d) ))", ReturnRoleplayName(userid), inputtext, Group_GetRank(playerid), ReturnRoleplayName(playerid), playerid);
    }
    return 1;
}

stock AddWarrant(targetid, playerid, const description[])
{
	new
	    string[500];

	mysql_format(dbCon, string, sizeof(string), "INSERT INTO `warrants` (`Suspect`, `Username`, `Date`, `Description`) VALUES('%e', '%e', '%e', '%e')", ReturnName(targetid), ReturnName(playerid), ReturnDate(), description);
	mysql_tquery(dbCon, string);
}

Dialog:MdcPlayerInfo(playerid, response, listitem, inputtext[]){
    if(!response) return ShowPoliceMDC(playerid);
    if(response){
        new userid = strval(inputtext);
        if(userid == INVALID_PLAYER_ID)
            return Dialog_ShowEasy(playerid, MdcPlayerInfo, DIALOG_STYLE_INPUT, "MDC > ค้นหาประวัติ", "* ชื่อผู้ใช้งานไม่ถูกต้อง *\nกรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการค้นหาประวัติ: ", "ตกลง", "กลับ");

        if(!LoggedIn[userid])
            return Dialog_ShowEasy(playerid, MdcPlayerInfo, DIALOG_STYLE_INPUT, "MDC > ค้นหาประวัติ", "* ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ *\nกรอก ไอดี/ชื่อ ของผู้เล่นที่ต้องการค้นหาประวัติ: ", "ตกลง", "กลับ");
   
        new string[256], caption[128], gender[16];

        if(PlayerData[userid][pGender] == 1)
            gender = "ชาย";
        else if(PlayerData[userid][pGender] == 2)
            gender = "หญิง";

        format(caption, sizeof(caption), "ประวัติของ > %s(%d)", ReturnRoleplayName(userid), userid);
        format(string, sizeof(string), "ชื่อ: %s | อายุ: %d | เพศ: %s | อาชีพ: %s", ReturnRoleplayName(userid), PlayerData[userid][pAge], gender, Job_GetName(PlayerData[userid][pJob]));
        Dialog_ShowEasy(playerid, ShowPlayerInfoPolice, DIALOG_STYLE_MSGBOX, caption, string, "ตกลง", "ปิด");
    }
    return 1;
}

ShowMenuPoliceCommand(playerid, userid){
    new string[100], caption[100];
    PoliceGetSupID[playerid] = userid;
    format(caption, sizeof(caption), "จัดการกับ: %s(%d)", ReturnRoleplayName(userid), userid);
    format(string, sizeof(string), "ใส่กุญแจมือ/ปลดกุญแจมือ\nควบคุมตัว/หยุดควบคุมตัว\nดึงขึ้นรถ\nดึงลงจากรถ\nตรวจค้นสิ่งผิดกฏหมาย");
    Dialog_ShowEasy(playerid, PoliceMenuCommand, DIALOG_STYLE_LIST, caption, string, "ตกลง", "ยกเลิก");
    return 1;
}

Dialog:PoliceMenuCommand(playerid, response, listitem, inputtext[]){
    if(!response) return PoliceGetSupID[playerid] = -1;
    if(response){
        new userid = PoliceGetSupID[playerid];
        if(!IsPlayerNearPlayer(playerid, userid, 5.0)) return ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้กับผู้เล่นนั้น");

        new caption[128], string[128];

        if(listitem == 0){
            
            if (!BitFlag_Get(g_PlayerFlags[userid],PLAYER_CUFFED)){
                BitFlag_On(g_PlayerFlags[userid],PLAYER_CUFFED);
                SetPlayerSpecialAction(userid, SPECIAL_ACTION_CUFFED);
                TogglePlayerControllable(userid, 0);
                PlayerData[userid][pCuffed] = 1;
                SetPlayerAttachedObject(userid, 7, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
                SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้จับข้อมือคู่นั้นของ %s อย่างรัดกุมพร้อมใส่กุญแจมือ", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
            }
            else{
                BitFlag_Off(g_PlayerFlags[userid],PLAYER_CUFFED);
                SetPlayerSpecialAction(userid, SPECIAL_ACTION_NONE);
                RemovePlayerAttachedObject(userid, 7);
                TogglePlayerControllable(userid, 1);
                PlayerData[userid][pCuffed] = 0;
                SetPlayerDraging(playerid, userid);
                SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s แก้กุญแจมือให้กับข้อมือของ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
            }
        }
        if(listitem == 1){
            if (!BitFlag_Get(g_PlayerFlags[userid],PLAYER_CUFFED) && !PlayerData[userid][pInjured]) return ErrorMsg(playerid, "ผู้เล่นนั้นไม่ได้ถูกใส่กุญแจมือหรือบาดเจ็บในขณะนี้");
            return SetPlayerDraging(playerid, userid);
        }
        if(listitem == 2){
            if (!BitFlag_Get(g_PlayerFlags[userid],PLAYER_CUFFED) && !PlayerData[userid][pInjured])
                return ErrorMsg(playerid, "ผู้เล่นนั้นไม่ได้ถูกใส่กุญแจมือหรือบาดเจ็บในขณะนี้");

            new
                seat;

            if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณจะต้องเป็นคนขับก่อน");

            new vehicleid = GetPlayerVehicleID(playerid);

            if(IsPlayerNearPlayer(playerid, userid, 5.0)) {
                if(checkVehicleSeat(vehicleid, 3) == 0){
                    seat = 3;
                    PutPlayerInVehicle(userid, vehicleid, seat);
                }
                else{
                    if(checkVehicleSeat(vehicleid, 4) == 0){
                        seat = 4;
                        PutPlayerInVehicle(userid, vehicleid, seat);
                    }
                    else ErrorMsg(playerid, "รถคันนี้ไม่มีที่ว่างเหลือแล้ว");
                }
                SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s เปิดประตูและจับ %s นั่งในยานพาหนะ", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
            }
            else SendClientMessage(playerid, COLOR_GREY, "คุณและรถต้องอยู่ใกล้กับคนที่คุณจะควบคุมตัวขึ้นรถ");
        }
        if(listitem == 3){
            if(GetPlayerState(userid) == PLAYER_STATE_PASSENGER) {
                if(GetPlayerVehicleID(playerid) == GetPlayerVehicleID(userid)) {
                    SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้ผลัก %s ออกจากพาหนะรถยนต์", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
                    RemovePlayerFromVehicle(userid);
                }
                else ErrorMsg(playerid, "ผู้เล่นนี้ไม่ได้อยู่ภายในพาหนะ");
            }
        }
        if(listitem == 4){
            GetPlayerFriskID[playerid] = userid;
            format(caption, sizeof(caption), "กำลังค้นตัว >> %s", ReturnRoleplayName(userid));
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้ตรวจค้นตัวของ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
            format(string, sizeof(string), "เงินแดง: %s\nแพ็คกัญชา: %d\nดินปืน: %d\nแพ็คโคเคน: %d\nยาผสม: %d\nแพ็คปูน: %d", FormatNumber(PlayerData[userid][pRedMoney]), PlayerInventory_AllCount(userid, "Pack Weed"), PlayerInventory_AllCount(userid, "Gun Powder"), PlayerInventory_AllCount(userid, "Pack Cocain"), PlayerInventory_AllCount(userid, "Pack Cement"));
            Dialog_ShowEasy(playerid, ShowFriskTargetid, DIALOG_STYLE_LIST, caption, string, "ตกลง", "ปิด");
        }
    }
    return 1;
}

CMD:beanbag(playerid, params[]){
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้คำสั่งนี้ได้ในขณะนี้");

	if (GetGroupType(playerid) != GROUP_POLICE)
		return ErrorMsg(playerid, "คุณต้องเป็นเจ้าหน้าที่ตำรวจ");

    if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_ONDUTY))
        return ErrorMsg(playerid, "คุณจำเป็นต้อง ON-DUTY ก่อน");

    if(PlayerEnterWarFlag[playerid]) return 1;

	if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_BEANBAG)){
	    BitFlag_On(g_PlayerFlags[playerid], PLAYER_BEANBAG);
	    GetPlayerWeaponData(playerid, 3, LastShotgunWeapon[playerid], LastShotgunAmmo[playerid]);
        ResetPlayerWeapons(playerid);
		GivePlayerWeapon(playerid, 25, 20000);
	    SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s หยิบ Beanbag shotgun ออกมา", ReturnRoleplayName(playerid));
	}
	else
	{
	    BitFlag_Off(g_PlayerFlags[playerid], PLAYER_BEANBAG);
        GivePlayerWeapon(playerid, LastShotgunWeapon[playerid], LastShotgunAmmo[playerid]);
	    SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s เก็บ Beanbag shotgun ของเขา", ReturnRoleplayName(playerid));
	}
	return 1;
}

CMD:checkdv(playerid, params[]){
    if(!LoggedIn[playerid])
        return 0;

    if(GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_NATIONAL)
        return 0;

    new userid;
    if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/checkdv [playerid]");
    if(userid == INVALID_PLAYER_ID) return 1;
    if(!LoggedIn[userid]) return 1;
    new device[32];
    if(IsAndroidPlayer(userid)) device = "โทรศัพท์มือถือ";
    else device = "คอมพิวเตอร์";
    SendClientMessageEx(playerid, COLOR_YELLOW, "ผู้เล่น %s เล่นด้วย %s", ReturnRoleplayName(userid), device);
    return 1;
}

CMD:lspd(playerid, params[]){
    if(!LoggedIn[playerid])
        return 0;

    if(GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_NATIONAL)
        return 0;

    if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_ONDUTY))
        return SendClientMessage(playerid, -1, "คุณต้อง ON-DUTY ก่อน");

    ShowTargetidUseCommandPolice(playerid);
    //Dialog_ShowEasy(playerid, PoliceCommandInputID, DIALOG_STYLE_INPUT, "Computer Police", "กรอกไอดีหรือชื่อผู้เล่นที่คุณต้องการจะจัดการ:", "ตกลง", "ยกเลิก");
    return 1;
}

ShowTargetidUseCommandPolice(playerid){
    new stringplayer[1024];
    new count;
    new menu[20];
    foreach(new x : Player){
        if(!LoggedIn[x]) continue;
        if(x == playerid) continue;
        if(IsPlayerNearPlayer(playerid, x, 5.0)){
            format(menu, 20, "menu%d", count++);
            SetPVarInt(playerid, menu, x);
            format(stringplayer, sizeof(stringplayer), "%s %s(%d)\n", stringplayer, ReturnRoleplayName(x), x);
        }
        if(count >= 20) break;
    }
    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "[Police Commands]", "ไม่มีใครอยู่ใกล้คุณเลย", "ตกลง", "ยกเลิก");
    else Dialog_ShowEasy(playerid, SendTargetUsePolice, DIALOG_STYLE_LIST, "[Police Commands]", stringplayer, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:SendTargetUsePolice(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "playerID", GetPVarInt(playerid, str_biz));
			ShowPoliceCommand(playerid);
			return 1;
		}
    }
    return 1;
}

ShowPoliceCommand(playerid){
    new targetid = GetPVarInt(playerid, "playerID");
    if(targetid == INVALID_PLAYER_ID){
        ErrorMsg(playerid, "ไอดีผู้เล่นผิดพลาด");
        return ShowTargetidUseCommandPolice(playerid);
    }

    if(!LoggedIn[targetid]){
        ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        return ShowTargetidUseCommandPolice(playerid);
    }

    if (!IsPlayerNearPlayer(playerid, targetid, 5.0)){
        ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้นหรือผู้เล่นนั้นห่างคุณออกไป");
        return ShowTargetidUseCommandPolice(playerid);
    }

    ShowMenuPoliceCommand(playerid, targetid);
    return 1;
}

CMD:m(playerid, params[])
{
	if(LoggedIn[playerid] == false)
		return 0;
		
    if(GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_NATIONAL)
        return 0;

	if (isnull(params))
	    return SendClientMessage(playerid, -1, "/m [text]");

	if (strlen(params) > 64) {
	    SendNearbyMessage(playerid, 40.0, COLOR_YELLOW, "[โทรโข่ง]: %s >> %.64s", ReturnRoleplayName(playerid), params);
	    SendNearbyMessage(playerid, 40.0, COLOR_YELLOW, "...%s <<", params[64]);
	}
	else {
	    SendNearbyMessage(playerid, 40.0, COLOR_YELLOW, "[โทรโข่ง]: %s >> %s <<", ReturnRoleplayName(playerid), params);
	}
	return 1;
}

CMD:siren2(playerid, params[]){
	new veh, type[8];
	if(!LoggedIn[playerid]) return SendClientMessage(playerid, COLOR_GREY, "คุณต้องเข้าสู่ระบบก่อนที่จะใช้คำสั่งต่าง ๆ");
   	if(GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_NATIONAL && GetGroupType(playerid) != GROUP_MEDIC) return SendClientMessage(playerid, COLOR_GREY, "คุณไม่ใช่เจ้าหน้าที่ LSPD/FBI Agent");
   	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_GREY, "คุณต้องเป็นคนขับรถ");
	if(sscanf(params, "s[8]", type))
	{
		SendClientMessage(playerid, COLOR_WHITE, "[Usage]: /siren2 [ตำแหน่ง]");
		SendClientMessage(playerid, COLOR_WHITE, "ตำแหน่ง: ภายใน | หลังคา | ปิด");
		return 1;
	}
	if(Siren[veh]) return SendClientMessage(playerid, COLOR_GREY, "พาหนะคันนี้ติดไซเรนแล้ว");
	veh = GetPlayerVehicleID(playerid);
	if(!strcmp(type, "ภายใน"))
	{
		if(Siren[veh]) return SendClientMessage(playerid, COLOR_GREY, "พาหนะคันนี้ติดไซเรนแล้ว");
        Siren[veh] = 1;
        SirenObject[veh] = CreateDynamicObject(18646, 10.0, 10.0, 10.0, 0, 0, 0);
        AttachDynamicObjectToVehicle(SirenObject[veh],veh, 0.0, 0.75, 0.275, 0.0, 0.1, 0.0);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ติดไซเรนลงแผงความคุม", ReturnRoleplayName(playerid));
        return 1;
	}
	else if(!strcmp(type, "หลังคา"))
	{
	    if(Siren[veh]) return SendClientMessage(playerid, COLOR_GREY, "พาหนะคันนี้ติดไซเรนแล้ว");
		Siren[veh] = 2;
        SirenObject[veh] = CreateDynamicObject(18646, 10.0, 10.0, 10.0, 0, 0, 0);
        AttachDynamicObjectToVehicle(SirenObject[veh], veh, -0.43, 0.0, 0.785, 0.0, 0.1, 0.0);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ติดไซเรนลงไว้บนหลังคาพาหนะ", ReturnRoleplayName(playerid));
        return 1;
	}
	else if(!strcmp(type, "ปิด")){
        if(!Siren[veh] && SirenObject[veh] == -1) return ErrorMsg(playerid, "ยานพาหนะนี้ยังไม่ได้ติดไซเรน");
		Siren[veh] = 0;
		DestroyDynamicObject(SirenObject[veh]);
        SirenObject[veh] = -1;
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบไซเรนลง", ReturnRoleplayName(playerid));
		return 1;
	}
	return 1;
}

CMD:siren(playerid, params[]){
	new veh, type[8];
    new Float:temphealth;
	if(!LoggedIn[playerid]) return SendClientMessage(playerid, COLOR_GREY, "คุณต้องเข้าสู่ระบบก่อนที่จะใช้คำสั่งต่าง ๆ");
   	if(GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_NATIONAL && GetGroupType(playerid) != GROUP_MEDIC) return SendClientMessage(playerid, COLOR_GREY, "คุณไม่ใช่เจ้าหน้าที่ LSPD/FBI Agent");
   	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_GREY, "คุณต้องเป็นคนขับรถ");
	if(sscanf(params, "s[8]", type))
	{
		SystemMsg(playerid, "[Usage]: /siren [ตำแหน่ง]");
		SystemMsg(playerid, "ตำแหน่ง: เปิด | ปิด");
		return 1;
	}
	veh = GetPlayerVehicleID(playerid);
    new carid = Car_GetID(veh);
    if(!strcmp(type, "เปิด"))
	{
	    if(CoreVehicles[veh][vehSirenOn] == 0)
        {
            new
                Float:fSize[3],
                Float:fSeat[3];

            GetVehicleModelInfo(GetVehicleModel(veh), VEHICLE_MODEL_INFO_SIZE, fSize[0], fSize[1], fSize[2]); // need height (z)
            GetVehicleModelInfo(GetVehicleModel(veh), VEHICLE_MODEL_INFO_FRONTSEAT, fSeat[0], fSeat[1], fSeat[2]); // need pos (x, y)

            CoreVehicles[veh][vehSirenOn] = 1;

            if(carid == -1) return ErrorMsg(playerid, "ยานพาหนะไม่ถูกต้อง");

            GetVehicleHealth(CarData[carid][carVehicle], temphealth);

            CarData[carid][carRealSiren] = 1;
            TRP_DestroyVehicle(CarData[carid][carVehicle], true);
			CarData[carid][carVehicle] = INVALID_VEHICLE_ID;
            Car_Spawn(carid);
            SetTimerEx("SetVehicleHealthForSiren", 1000, false, "df", carid, temphealth);
            
            new
                Float:x,
                Float:y,
                Float:z;

            GetPlayerPos(playerid, x, y, z);
            SetVehiclePosEx(CarData[carid][carVehicle], x + 2, y - 2, z);

            SetVehicleVirtualWorld(CarData[carid][carVehicle], GetPlayerVirtualWorld(playerid));
            LinkVehicleToInterior(CarData[carid][carVehicle], GetPlayerInterior(playerid));
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ติดไซเรนแบบพกพาให้กับยานพาหนะ", ReturnRoleplayName(playerid));
        }
        return 1;
	}
	else if(!strcmp(type, "ปิด"))
	{
        if(CoreVehicles[veh][vehSirenOn] == 1){
            CoreVehicles[veh][vehSirenOn] = 0;
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ถอดไซเรนแบบพกพาจากยานพาหนะ", ReturnRoleplayName(playerid));
        }

        if(carid != -1){
            CarData[carid][carRealSiren] = 0;
            GetVehicleHealth(CarData[carid][carVehicle], temphealth);
            TRP_DestroyVehicle(CarData[carid][carVehicle], true);
			CarData[carid][carVehicle] = INVALID_VEHICLE_ID;
            Car_Spawn(carid);
            SetTimerEx("SetVehicleHealthForSiren", 1000, false, "df", carid, temphealth);

            new
                Float:x,
                Float:y,
                Float:z;

            GetPlayerPos(playerid, x, y, z);
            SetVehiclePosEx(CarData[carid][carVehicle], x + 2, y - 2, z);

            SetVehicleVirtualWorld(CarData[carid][carVehicle], GetPlayerVirtualWorld(playerid));
            LinkVehicleToInterior(CarData[carid][carVehicle], GetPlayerInterior(playerid));
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำนำไซเรนออกจากยานพาหนะ", ReturnRoleplayName(playerid));
        }
		return 1;
	}
	return 1;
}

forward SetVehicleHealthForSiren(carid, Float:health);
public SetVehicleHealthForSiren(carid, Float:health){
    if(carid != -1){
        SetVehicleHealth(CarData[carid][carVehicle], health);
    }
    return 1;
}

CMD:removenitro(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณต้องเป็นคนขับ");
    if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_NATIONAL){

        if(PlayerData[playerid][pGroupRank] < 3) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติให้ใช้งานคำสั่งนี้");

        new vehicleid = GetPlayerVehicleID(playerid);
        new carid = Car_GetID(vehicleid);
        RemoveVehicleComponent(CarData[carid][carVehicle], CarData[carid][carMods][5]);
        CarData[carid][carMods][5] = 0;
        Car_Save(carid);
    }else return ErrorMsg(playerid, "คุณไม่สามารถใช้งานคำสั่งนี้ได้");
    return 1;
}

CMD:frisk(playerid, params[]){
    if(LoggedIn[playerid]){
        if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_NATIONAL){
            new userid, string[256], caption[128];
            if(sscanf(params, "u", userid))
                return SystemMsg(playerid, "/frisk [playerid]");

            if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

            if(userid == playerid)
                return ErrorMsg(playerid, "คุณค้นตัวเองไม่ได้");


            if(userid != INVALID_PLAYER_ID){
                if(IsPlayerNearPlayer(playerid, userid, 5.0)){
                    if(LoggedIn[userid]){
                        GetPlayerFriskID[playerid] = userid;
                        SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้ตรวจค้นตัวของ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
                        format(caption, sizeof(caption), "กำลังค้นตัว >> %s", ReturnRoleplayName(userid));
                        format(string, sizeof(string), "เงินแดง: %s\nแพ็คกัญชา: %d\nดินปืน: %d\nแพ็คโคเคน: %d\nยาผสม: %d\nแพ็คปูน: %d\nสายไฟ: %d", FormatNumber(PlayerData[userid][pRedMoney]), PlayerInventory_AllCount(userid, "Pack Weed"), PlayerInventory_AllCount(userid, "Gun Powder"), PlayerInventory_AllCount(userid, "Pack Cocain"), PlayerInventory_AllCount(userid, "Mixed Drug"), PlayerInventory_AllCount(userid, "Pack Cement"), PlayerInventory_AllCount(userid, "Wire"));
                        Dialog_ShowEasy(playerid, ShowFriskTargetid, DIALOG_STYLE_LIST, caption, string, "ตกลง", "ปิด");
                    }
                }
            }
        }
    }
    return 1;
}

Dialog:ShowFriskTargetid(playerid, response, listitem, inputtext[]){
    if(!response) return GetPlayerFriskID[playerid] = -1;
    if(response){
        new userid = GetPlayerFriskID[playerid];
        new caption[80], string[80];
        if(listitem == 0){
            format(caption, sizeof(caption), "ยึดเงินแดง >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "กรอกจำนวนเงินแดงทีต้องการจะยึด, มีอยู่: %s", FormatNumber(PlayerData[userid][pRedMoney]));
            Dialog_ShowEasy(playerid, TakeRedMoneyAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            format(caption, sizeof(caption), "ยึดแพ็คกัญชา >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "กรอกจำนวนแพ็คกัญชาที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Pack Weed"));
            Dialog_ShowEasy(playerid, TakePackWeedAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }
        if(listitem == 2){
            format(caption, sizeof(caption), "ยึดดินปืน >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "กรอกจำนวนดินปืนที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Gun Powder"));
            Dialog_ShowEasy(playerid, TakeGunPowderAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }
        if(listitem == 3){
            format(caption, sizeof(caption), "ยึดแพ็คโคเคน >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "กรอกจำนวนแพ็คโคเคนที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Pack Cocain"));
            Dialog_ShowEasy(playerid, TakePackCocainAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }
        if(listitem == 4){
            format(caption, sizeof(caption), "ยึดยาผสม >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "กรอกจำนวนยาผสมที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Mix Drug"));
            Dialog_ShowEasy(playerid, TakeMixedDrugAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }
        if(listitem == 5){
            format(caption, sizeof(caption), "ยึดแพ็คปูน >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "กรอกจำนวนแพ็คปูนที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Pack Cement"));
            Dialog_ShowEasy(playerid, TakePackCementAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }
        if(listitem == 6){
            format(caption, sizeof(caption), "ยึดสายไฟ >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "กรอกจำนวนแพ็คปูนที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Wire"));
            Dialog_ShowEasy(playerid, TakePackWireAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:TakeGunPowderAmount(playerid, response, listitem, inputtext[]){
    if(!response) return GetPlayerFriskID[playerid] = -1;
    if(response){
        new amount = strval(inputtext);
        new userid = GetPlayerFriskID[playerid];
        new caption[128], string[128];

        if(amount <= 0){
            format(caption, sizeof(caption), "ยึดดินปืน >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* คุณจำเป็นต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนดินปืนที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Gun Powder"));
            return Dialog_ShowEasy(playerid, TakeGunPowderAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        if(amount > PlayerInventory_AllCount(userid, "Gun Powder")){
            format(caption, sizeof(caption), "ยึดดินปืน >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* ผู้เล่นนั้นมีแพ็คกัญชาไม่พอ *\nกรอกจำนวนดินปืนที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Gun Powder"));
            return Dialog_ShowEasy(playerid, TakeGunPowderAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        PlayerInventory_Remove(userid, "Gun Powder", amount);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ทำการยึดดินปืนของ %s(%d) จำนวน %d เรียบร้อยแล้ว", ReturnRoleplayName(userid), userid, amount);
        SendClientMessageEx(userid, COLOR_YELLOW, "คุณได้ถูกเจ้าหน้าที่ %s(%d) ทำการยึดดินปืนจำนวน %d", ReturnRoleplayName(playerid), playerid, amount);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำการยึด 'ดินปืน' ของ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
    }
    return 1;
}

Dialog:TakePackWeedAmount(playerid, response, listitem, inputtext[]){
    if(!response) return GetPlayerFriskID[playerid] = -1;
    if(response){
        new amount = strval(inputtext);
        new userid = GetPlayerFriskID[playerid];
        new caption[128], string[128];

        if(amount <= 0){
            format(caption, sizeof(caption), "ยึดแพ็คกัญชา >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* คุณจำเป็นต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนแพ็คกัญชาที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Pack Weed"));
            return Dialog_ShowEasy(playerid, TakePackWeedAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        if(amount > PlayerInventory_AllCount(userid, "Pack Weed")){
            format(caption, sizeof(caption), "ยึดแพ็คกัญชา >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* ผู้เล่นนั้นมีแพ็คกัญชาไม่พอ *\nกรอกจำนวนแพ็คกัญชาที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Pack Weed"));
            return Dialog_ShowEasy(playerid, TakePackWeedAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        PlayerInventory_Remove(userid, "Pack Weed", amount);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ทำการยึดแพ็คกัญชาของ %s(%d) จำนวน %d เรียบร้อยแล้ว", ReturnRoleplayName(userid), userid, amount);
        SendClientMessageEx(userid, COLOR_YELLOW, "คุณได้ถูกเจ้าหน้าที่ %s(%d) ทำการยึดแพ็คกัญชาจำนวน %d", ReturnRoleplayName(playerid), playerid, amount);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำการยึด 'แพ็คกัญชา' ของ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
    }
    return 1;
}

Dialog:TakePackCocainAmount(playerid, response, listitem, inputtext[]){
    if(!response) return GetPlayerFriskID[playerid] = -1;
    if(response){
        new amount = strval(inputtext);
        new userid = GetPlayerFriskID[playerid];
        new caption[128], string[128];

        if(amount <= 0){
            format(caption, sizeof(caption), "ยึดแพ็คโคเคน >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* คุณจำเป็นต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนแพ็คโคเคนที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Pack Cocain"));
            return Dialog_ShowEasy(playerid, TakePackCocainAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        if(amount > PlayerInventory_AllCount(userid, "Pack Cocain")){
            format(caption, sizeof(caption), "ยึดแพ็คโคเคน >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* ผู้เล่นนั้นมีแพ็คกัญชาไม่พอ *\nกรอกจำนวนแพ็คโคเคนที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Pack Cocain"));
            return Dialog_ShowEasy(playerid, TakePackCocainAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        PlayerInventory_Remove(userid, "Pack Cocain", amount);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ทำการยึดแพ็คโคเคนของ %s(%d) จำนวน %d เรียบร้อยแล้ว", ReturnRoleplayName(userid), userid, amount);
        SendClientMessageEx(userid, COLOR_YELLOW, "คุณได้ถูกเจ้าหน้าที่ %s(%d) ทำการยึดแพ็คโคเคนจำนวน %d", ReturnRoleplayName(playerid), playerid, amount);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำการยึด 'แพ็คโคเคน' ของ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
    }
    return 1;
}

Dialog:TakeMixedDrugAmount(playerid, response, listitem, inputtext[]){
    if(!response) return GetPlayerFriskID[playerid] = -1;
    if(response){
        new amount = strval(inputtext);
        new userid = GetPlayerFriskID[playerid];
        new caption[128], string[128];

        if(amount <= 0){
            format(caption, sizeof(caption), "ยึดยาผสม >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* คุณจำเป็นต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนยาผสมที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Mixed Drug"));
            return Dialog_ShowEasy(playerid, TakeMixedDrugAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        if(amount > PlayerInventory_AllCount(userid, "Mixed Drug")){
            format(caption, sizeof(caption), "ยึดยาผสม >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* ผู้เล่นนั้นมีแพ็คกัญชาไม่พอ *\nกรอกจำนวนยาผสมที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Mixed Drug"));
            return Dialog_ShowEasy(playerid, TakeMixedDrugAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        PlayerInventory_Remove(userid, "Mixed Drug", amount);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ทำการยึดยาผสมของ %s(%d) จำนวน %d เรียบร้อยแล้ว", ReturnRoleplayName(userid), userid, amount);
        SendClientMessageEx(userid, COLOR_YELLOW, "คุณได้ถูกเจ้าหน้าที่ %s(%d) ทำการยึดยาผสมจำนวน %d", ReturnRoleplayName(playerid), playerid, amount);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำการยึด 'ยาผสม' ของ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
    }
    return 1;
}

Dialog:TakePackCementAmount(playerid, response, listitem, inputtext[]){
    if(!response) return GetPlayerFriskID[playerid] = -1;
    if(response){
        new amount = strval(inputtext);
        new userid = GetPlayerFriskID[playerid];
        new caption[128], string[128];

        if(amount <= 0){
            format(caption, sizeof(caption), "ยึดแพ็คปูน >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* คุณจำเป็นต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนแพ็คปูนที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Pack Cement"));
            return Dialog_ShowEasy(playerid, TakePackCementAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        if(amount > PlayerInventory_AllCount(userid, "Pack Cement")){
            format(caption, sizeof(caption), "ยึดแพ็คปูน >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* ผู้เล่นนั้นมีแพ็คกัญชาไม่พอ *\nกรอกจำนวนแพ็คปูนที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Pack Cement"));
            return Dialog_ShowEasy(playerid, TakePackCementAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        PlayerInventory_Remove(userid, "Pack Cement", amount);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ทำการยึดแพ็คปูนของ %s(%d) จำนวน %d เรียบร้อยแล้ว", ReturnRoleplayName(userid), userid, amount);
        SendClientMessageEx(userid, COLOR_YELLOW, "คุณได้ถูกเจ้าหน้าที่ %s(%d) ทำการยึดแพ็คปูนจำนวน %d", ReturnRoleplayName(playerid), playerid, amount);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำการยึด 'แพ็คปูน' ของ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
    }
    return 1;
}

Dialog:TakePackWireAmount(playerid, response, listitem, inputtext[]){
    if(!response) return GetPlayerFriskID[playerid] = -1;
    if(response){
        new amount = strval(inputtext);
        new userid = GetPlayerFriskID[playerid];
        new caption[128], string[128];

        if(amount <= 0){
            format(caption, sizeof(caption), "ยึดสายไฟ >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* คุณจำเป็นต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนสายไฟที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Wire"));
            return Dialog_ShowEasy(playerid, TakePackWireAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        if(amount > PlayerInventory_AllCount(userid, "Wire")){
            format(caption, sizeof(caption), "ยึดสายไฟ >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* ผู้เล่นนั้นมีแพ็คกัญชาไม่พอ *\nกรอกจำนวนสายไฟที่ต้องการจะยึด, มีอยู่: %d", PlayerInventory_AllCount(userid, "Wire"));
            return Dialog_ShowEasy(playerid, TakePackWireAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        PlayerInventory_Remove(userid, "Wire", amount);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ทำการยึดสายไฟของ %s(%d) จำนวน %d เรียบร้อยแล้ว", ReturnRoleplayName(userid), userid, amount);
        SendClientMessageEx(userid, COLOR_YELLOW, "คุณได้ถูกเจ้าหน้าที่ %s(%d) ทำการยึดสายไฟจำนวน %d", ReturnRoleplayName(playerid), playerid, amount);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำการยึด 'สายไฟ' ของ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
    }
    return 1;
}

Dialog:TakeRedMoneyAmount(playerid, response, listitem, inputtext[]){
    if(!response) return GetPlayerFriskID[playerid] = -1;
    if(response){
        new amount = strval(inputtext);
        new userid = GetPlayerFriskID[playerid];
        new caption[128], string[128];

        if(amount <= 0){
            format(caption, sizeof(caption), "ยึดเงินแดง >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* คุณจำเป็นต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนเงินแดงทีต้องการจะยึด, มีอยู่: %s", FormatNumber(PlayerData[userid][pRedMoney]));
            return Dialog_ShowEasy(playerid, TakeRedMoneyAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        if(amount > PlayerData[userid][pRedMoney]){
            format(caption, sizeof(caption), "ยึดเงินแดง >> %s", ReturnRoleplayName(userid));
            format(string, sizeof(string), "* ผู้เล่นนั้นมีเงินแดงไม่พอ *\nกรอกจำนวนเงินแดงทีต้องการจะยึด, มีอยู่: %s", FormatNumber(PlayerData[userid][pRedMoney]));
            return Dialog_ShowEasy(playerid, TakeRedMoneyAmount, DIALOG_STYLE_INPUT, caption, string, "ตกลง", "ยกเลิก");
        }

        PlayerData[userid][pRedMoney] -= amount;
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ทำการยึดเงินแดงของ %s(%d) จำนวน %s เรียบร้อยแล้ว", ReturnRoleplayName(userid), userid, FormatNumber(amount));
        SendClientMessageEx(userid, COLOR_YELLOW, "คุณได้ถูกเจ้าหน้าที่ %s(%d) ทำการยึดเงินแดงจำนวน %s", ReturnRoleplayName(playerid), playerid, FormatNumber(amount));
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำการยึด 'เงินแดง' ของ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
    }
    return 1;
}

CMD:mdc(playerid, params[]){
    if(!LoggedIn[playerid])
        return 0;

    if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_NATIONAL){
        new vehicleid = GetPlayerVehicleID(playerid);
        if(GetVehicleModel(vehicleid) == 596 || GetVehicleModel(vehicleid) == 597 || GetVehicleModel(vehicleid) == 598 || GetVehicleModel(vehicleid) == 599){
            ShowPoliceMDC(playerid);
        }
    }
    return 1;
}

CMD:door(playerid, const params[]){
    if(!LoggedIn[playerid])
        return 0;

    new id = Gate_Nearest(playerid);

	if (id != -1)
	{
		if (strlen(GateData[id][gatePass]))
		{
		    Dialog_ShowEasy(playerid, GatePass, DIALOG_STYLE_INPUT, "Enter Password", "โปรดป้อนรหัสผ่านสำหรับประตูนี้ด้านล่าง:", "Submit", "Cancel");
		}
		else
		{
		    if (GateData[id][gateFaction] != -1 && PlayerData[playerid][pGroup] != GetGroupByID(GateData[id][gateFaction]))
				return ErrorMsg(playerid, "คุณไม่สามารถเปิดประตูนี้ได้");

			Gate_Operate(id);
		}
	}
    else if (IsPlayerNearDynamicObject(playerid, PrisonData[prisonDoors][0]))
	{
	    if (GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_NATIONAL)
	        return ErrorMsg(playerid, "คุณจะต้องเป็นเจ้าหน้าที่ตำรวจที่จะเปิดประตูนี้");

	    if (!PrisonData[prisonDoorOpened][0])
		{
			SetDynamicObjectRot(PrisonData[prisonDoors][0], 0.0, 0.0, -90.0);

			PrisonData[prisonDoorOpened][0] = true;
			SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ใช้กุญแจของเขาและเปิดประตูคุก", ReturnRoleplayName(playerid));
		}
		else
		{
		    SetDynamicObjectRot(PrisonData[prisonDoors][0], 0.0, 0.0, 0.0);

			PrisonData[prisonDoorOpened][0] = false;
			SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ใช้กุญแจของเขาและปิดประตูคุก", ReturnRoleplayName(playerid));
		}
	}
	else if (IsPlayerNearDynamicObject(playerid, PrisonData[prisonDoors][1]))
	{
	    if (GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_NATIONAL)
	        return ErrorMsg(playerid, "คุณจะต้องเป็นเจ้าหน้าที่ตำรวจที่จะเปิดประตูนี้");

	    if (!PrisonData[prisonDoorOpened][1])
		{
			SetDynamicObjectRot(PrisonData[prisonDoors][1], 0.0, 0.0, 0.0);

			PrisonData[prisonDoorOpened][1] = true;
			SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ใช้กุญแจของเขาและเปิดประตูคุก", ReturnRoleplayName(playerid));
		}
		else
		{
		    SetDynamicObjectRot(PrisonData[prisonDoors][1], 0.0, 0.0, 90.0);

			PrisonData[prisonDoorOpened][1] = false;
			SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ใช้กุญแจของเขาและปิดประตูคุก", ReturnRoleplayName(playerid));
		}
	}
	else if (IsPlayerNearDynamicObject(playerid, PrisonData[prisonDoors][2]))
	{
	    if (GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_NATIONAL)
	        return ErrorMsg(playerid, "คุณจะต้องเป็นเจ้าหน้าที่ตำรวจที่จะเปิดประตูนี้");

	    if (!PrisonData[prisonDoorOpened][2])
		{
			SetDynamicObjectRot(PrisonData[prisonDoors][2], 0.0, 0.0, -90.0);

			PrisonData[prisonDoorOpened][2] = true;
			SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ใช้กุญแจของเขาและเปิดประตูคุก", ReturnRoleplayName(playerid));
		}
		else
		{
		    SetDynamicObjectRot(PrisonData[prisonDoors][2], 0.0, 0.0, 0.0);

			PrisonData[prisonDoorOpened][2] = false;
			SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ใช้กุญแจของเขาและปิดประตูคุก", ReturnRoleplayName(playerid));
		}
	}
	for (new i = 0; i < 24; i ++) if (IsPlayerNearDynamicObject(playerid, PrisonData[prisonCells][i], 3.0))
	{
	    if (GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_NATIONAL)
	        return ErrorMsg(playerid, "คุณจะต้องเป็นเจ้าหน้าที่ตำรวจที่จะเปิดประตูห้องขังนี้");

		if (!PrisonData[prisonCellOpened][i])
		{
			MoveDynamicObject(PrisonData[prisonCells][i], PrisonCells[i][0], PrisonCells[i][1] + 1.6, PrisonCells[i][2], 3.0);

		    PrisonData[prisonCellOpened][i] = true;
		    SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ใช้กุญแจของเขาและเปิดประตูห้องขัง", ReturnRoleplayName(playerid));
		}
		else
		{
		    MoveDynamicObject(PrisonData[prisonCells][i], PrisonCells[i][0], PrisonCells[i][1], PrisonCells[i][2], 3.0);

		    PrisonData[prisonCellOpened][i] = false;
		    SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ใช้กุญแจของเขาและปิดประตูห้องขัง", ReturnRoleplayName(playerid));
		}
		break;
	}
    return 1;
}

CMD:cuff(playerid, params[])
{
    if(!LoggedIn[playerid])
        return ErrorMsg(playerid, "คุณไม่ได้ล็อคอิน");

    new
        userid;

    if (GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_GOV && GetGroupType(playerid) != GROUP_NATIONAL)
        return SendClientMessage(playerid, -1, "คุณต้องเป็นเจ้าหน้าที่ตำรวจ");

    if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_ONDUTY))
        return SendClientMessage(playerid, -1, "คุณต้อง ON-DUTY ก่อน");

    if (sscanf(params, "u", userid))
        return SendClientMessage(playerid, -1, "/cuff [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นได้ตัดการเชื่อมต่อแล้ว");

    if (userid == playerid)
        return SendClientMessage(playerid, -1, "คุณไม่สามารถใส่กุญแจมือตัวเองได้");

    if (!IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendClientMessage(playerid, -1, "คุณต้องอยู่ใกล้ผู้เล่นนั้น");

    if (BitFlag_Get(g_PlayerFlags[userid],PLAYER_CUFFED))
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นถูกใส่กุญแจมือแล้ว");

    BitFlag_On(g_PlayerFlags[userid],PLAYER_CUFFED);
    SetPlayerSpecialAction(userid, SPECIAL_ACTION_CUFFED);
    PlayerData[userid][pCuffed] = 1;
    SetPlayerAttachedObject(userid, 7, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
    TogglePlayerControllable(userid, 0);
    SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้จับข้อมือคู่นั้นของ %s อย่างรัดกุมพร้อมใส่กุญแจมือ", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
    return 1;
}

CMD:uncuff(playerid, params[])
{
    if(!LoggedIn[playerid])
        return ErrorMsg(playerid, "คุณไม่ได้ล็อคอิน");

    new
        userid;

    if (GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_GOV && GetGroupType(playerid) != GROUP_NATIONAL)
        return SendClientMessage(playerid, -1, "คุณต้องเป็นเจ้าหน้าที่ตำรวจ");

    if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_ONDUTY))
        return SendClientMessage(playerid, -1, "คุณต้อง ON-DUTY ก่อน");

    if (sscanf(params, "u", userid))
        return SendClientMessage(playerid, -1, "/uncuff [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นได้ตัดการเชื่อมต่อแล้ว");

    if (userid == playerid)
        return SendClientMessage(playerid, -1, "คุณไม่สามารถปลดกุญแจมือตัวเองได้");

    if (!IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendClientMessage(playerid, -1, "คุณต้องอยู่ใกล้ผู้เล่นนั้น");

    if (!BitFlag_Get(g_PlayerFlags[userid],PLAYER_CUFFED))
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นไม่ได้ถูกใส่กุญแจมือในขณะนี้");


    BitFlag_Off(g_PlayerFlags[userid],PLAYER_CUFFED);
    SetPlayerSpecialAction(userid, SPECIAL_ACTION_NONE);
    RemovePlayerAttachedObject(userid, 7);
    TogglePlayerControllable(userid, 1);
    PlayerData[userid][pCuffed] = 0;
    SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s แก้กุญแจมือให้กับข้อมือของ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
    return 1;
}

CMD:unjail(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    new string[128];
    if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_NATIONAL){
        if(PlayerData[playerid][pGroupRank] >= 10){
            new userid;
            if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/unjail [playerid]");
            if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
            if(userid != INVALID_PLAYER_ID){
                if(LoggedIn[userid]){
                    if(PlayerData[userid][pJail] != 0){
                        PlayerData[userid][pJailTime] = 0;
                        format(string, sizeof(string), "%s %s: ได้ทำการประกันตัว %s ออกจากเรือนจำเรียบร้อยแล้ว", Group_GetRank(playerid), ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
                        SendAdminsMessage(1, 0xFF0066AA, string);
                        SendFactionMessage(PlayerData[playerid][pGroup], COLOR_RADIO, "(( [HQ] %s %s: ได้ทำการประกันตัว %s ออกจากเรือนจำเรียบร้อยแล้ว ))", Group_GetRank(playerid), ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
                        Log_Write("logs/unjail.txt", "[%s] %s Unjail %s", ReturnDate(), ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
                    }
                }
            }
        }
        else return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");
    }
    return 1;
}

stock CreateRoadblock(Object,Float:x,Float:y,Float:z,Float:Angle){
    for(new i = 0; i < sizeof(Roadblocks); i++)
  	{
  	    if(Roadblocks[i][sCreated] == 0)
  	    {
            Roadblocks[i][sCreated] = 1;
            Roadblocks[i][sX] = x;
            Roadblocks[i][sY] = y;
            Roadblocks[i][sZ] = z-0.7;
            Roadblocks[i][sObject] = CreateDynamicObject(Object, x, y, z-0.9, 0, 0, Angle);
	        return 1;
  	    }
  	}
  	return 0;
}

stock DeleteAllRoadblocks(playerid){
    for(new i = 0; i < sizeof(Roadblocks); i++){
        if(Roadblocks[i][sCreated] == 1){
            if(IsPlayerInRangeOfPoint(playerid, 100, Roadblocks[i][sX], Roadblocks[i][sY], Roadblocks[i][sZ])){
	  	        Roadblocks[i][sCreated] = 0;
	            Roadblocks[i][sX] = 0.0;
	            Roadblocks[i][sY] = 0.0;
	            Roadblocks[i][sZ] = 0.0;
                if(IsValidDynamicObject(Roadblocks[i][sObject]) && Roadblocks[i][sObject] != -1) DestroyDynamicObject(Roadblocks[i][sObject]);
	            Roadblocks[i][sObject] = -1;
	  	    }
  	    }
	}
    return 0;
}

DeleteClosestRoadblock(playerid){
    for(new i = 0; i < sizeof(Roadblocks); i++){
        if(Roadblocks[i][sCreated] == 1){
  	        if(IsPlayerInRangeOfPoint(playerid, 5.0, Roadblocks[i][sX], Roadblocks[i][sY], Roadblocks[i][sZ])){
                Roadblocks[i][sCreated] = 0;
                Roadblocks[i][sX] = 0.0;
                Roadblocks[i][sY] = 0.0;
                Roadblocks[i][sZ] = 0.0;
                if(IsValidDynamicObject(Roadblocks[i][sObject]) && Roadblocks[i][sObject] != -1) DestroyDynamicObject(Roadblocks[i][sObject]);
                Roadblocks[i][sObject] =-1;
                return 1;
  	        }
  	    }
  	}
    return 0;
}

CMD:rb(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_NATIONAL){
        new rb, string[128];
        if(sscanf(params, "i", rb)){
            SendClientMessage(playerid, COLOR_WHITE, "{7DAEFF}USAGE: /rb [Roadblock ID]{7DAEFF}");
            SendClientMessage(playerid, COLOR_LIGHTBLUE, "Available Roadblocks:");
            SendClientMessage(playerid, COLOR_GREY, "| 1: Small Roadblock");
            SendClientMessage(playerid, COLOR_GREY, "| 2: Medium Roadblock");
            SendClientMessage(playerid, COLOR_GREY, "| 3: Big Roadblock");
            SendClientMessage(playerid, COLOR_GREY, "| 4: Cone");
            return 1;
        }

        new groupid = PlayerData[playerid][pGroup];

        if (rb == 1){
            PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
            new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
            GetPlayerPos(playerid, plocx, plocy, plocz);
            GetPlayerFacingAngle(playerid,ploca);
            CreateRoadblock(1459,plocx,plocy,plocz,ploca);

            SendFactionMessage(groupid, COLOR_RADIO, "(( (%d) %s %s: ได้ทำการว่างสิ่งกีดขวาง, เปลี่ยน ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid));
            format(string, sizeof(string), "*[Radio] %s ได้ทำการว่างสิ่งกีดขวาง", ReturnRoleplayName(playerid));
            SetPlayerChatBubble(playerid, string, COLOR_RP, 30.0, 10000);
            GameTextForPlayer(playerid,"~w~Roadblock ~b~Placed!",3000,1);
            return 1;
        }
        else if (rb == 2)
        {
            PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
            new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
            GetPlayerPos(playerid, plocx, plocy, plocz);
            GetPlayerFacingAngle(playerid,ploca);
            CreateRoadblock(978,plocx,plocy,plocz+0.6,ploca);

            SendFactionMessage(groupid, COLOR_RADIO, "(( (%d) %s %s: ได้ทำการว่างสิ่งกีดขวาง, เปลี่ยน ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid));
            format(string, sizeof(string), "*[Radio] %s ได้ทำการว่างสิ่งกีดขวาง", ReturnRoleplayName(playerid));
            SetPlayerChatBubble(playerid, string, COLOR_RP, 30.0, 10000);

            GameTextForPlayer(playerid,"~w~Roadblock ~b~Placed!",3000,1);
            return 1;
        }
        else if (rb == 3)
        {
            PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
            new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
            GetPlayerPos(playerid, plocx, plocy, plocz);
            GetPlayerFacingAngle(playerid,ploca);
            CreateRoadblock(981,plocx,plocy,plocz+0.9,ploca+180);

            SetPlayerPos(playerid, plocx+3, plocy, plocz);

            SendFactionMessage(groupid, COLOR_RADIO, "(( (%d) %s %s: ได้ทำการว่างสิ่งกีดขวาง, เปลี่ยน ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid));
            format(string, sizeof(string), "*[Radio] %s ได้ทำการว่างสิ่งกีดขวาง", ReturnRoleplayName(playerid));
            SetPlayerChatBubble(playerid, string, COLOR_RP, 30.0, 10000);

            GameTextForPlayer(playerid,"~w~Roadblock ~b~Placed!",3000,1);
            return 1;
        }
        else if (rb == 4)
        {
            PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
            new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
            GetPlayerPos(playerid, plocx, plocy, plocz);
            GetPlayerFacingAngle(playerid,ploca);
            CreateRoadblock(1238,plocx,plocy,plocz+0.2,ploca);

            SendFactionMessage(groupid, COLOR_RADIO, "(( (%d) %s %s: ได้ทำการว่างสิ่งกีดขวาง, เปลี่ยน ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid));
            format(string, sizeof(string), "*[Radio] %s ได้ทำการว่างสิ่งกีดขวาง", ReturnRoleplayName(playerid));
            SetPlayerChatBubble(playerid, string, COLOR_RP, 30.0, 10000);

            GameTextForPlayer(playerid,"~w~Roadblock ~b~Placed!",3000,1);
            GameTextForPlayer(playerid,"~w~Cone ~g~Placed!",3000,1);
            return 1;
        }
    }
    else return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");
    return 1;
}

CMD:rrb(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_NATIONAL){
        new string[128];
        new groupid = PlayerData[playerid][pGroup];
        if(DeleteClosestRoadblock(playerid) != 0){
            SendFactionMessage(groupid, COLOR_RADIO, "(( (%d) %s %s: ได้ลบวิ่งกีดขวาง, เปลี่ยน ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid));
            format(string, sizeof(string), "*[Radio] %s ได้ลบวิ่งกีดขวาง", ReturnRoleplayName(playerid));
            SetPlayerChatBubble(playerid, string, COLOR_RP, 30.0, 10000);

            GameTextForPlayer(playerid,"~w~Roadblock ~r~Removed!",3000,1);
        }
    }
    else return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");
    return 1;
}

CMD:rrball(playerid, params[]) {
	if(!LoggedIn[playerid]) return 0;
    if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_NATIONAL){
        new string[128];
        new groupid = PlayerData[playerid][pGroup];
		if(PlayerData[playerid][pGroupRank] >= 10){
 			DeleteAllRoadblocks(playerid);
 			SendFactionMessage(groupid, COLOR_RADIO, "(( (%d) %s %s: ได้ลบวิ่งกีดขวางในพื้นที่ทั้งหมด, เปลี่ยน ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid));
            format(string, sizeof(string), "*[Radio] %s ได้ลบวิ่งกีดขวางในพื้นที่ทั้งหมด", ReturnRoleplayName(playerid));
            SetPlayerChatBubble(playerid, string, COLOR_RP, 30.0, 10000);
  			GameTextForPlayer(playerid,"~b~All ~w~Roadblocks ~r~Removed!",3000,1);
		}
        else return ErrorMsg(playerid, "คุณต้องมีระดับยศมากกว่า 10");
	}
    else return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");
	return 1;
}

alias:summons("หมายเรียก")
CMD:summons(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(GetGroupType(playerid) != GROUP_POLICE) return ErrorMsg(playerid, "คุณไม่ใช่เจ้าหน้าที่ตำรวจ");
    if(PlayerData[playerid][pGroupRank] >= 2){
        if (isnull(params)) return SystemMsg(playerid, "/summons [text]");
        if (strlen(params) > 64){
            foreach (new i : Player){
                if(LoggedIn[i] && PlayerData[playerid][pFirstTime] == 0){
                    SendClientMessageEx(i, 0xFF2A00AA, "[หมายเรียกตัวจากกรมตำรวจ]: {FFFFFF}%.64s", params);
                    SendClientMessageEx(i, 0xFF2A00AA, "...%s", params[64]);
                }
            }
        }
        else{
            foreach (new i : Player){
                if(LoggedIn[i] && PlayerData[playerid][pFirstTime] == 0)
                    SendClientMessageEx(i, 0xFF2A00AA, "[หมายเรียกตัวจากกรมตำรวจ]: {FFFFFF}%s", params);
            }
        }
    }
    else return ErrorMsg(playerid, "ตำแหน่งของคุณไม่สามารถใช้ได้");
    return 1;
}