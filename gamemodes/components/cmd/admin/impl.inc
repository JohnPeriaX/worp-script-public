#if defined _inc_impl
	#undef _inc_impl
#endif

CMD:acmds(playerid, params[]){

    if(LoggedIn[playerid] == false)
		return 0;

    if(PlayerData[playerid][pAdmin] < 1)
        return ErrorMsg(playerid, "คุณไม่ใช่ผู้ดูแล");

    SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
    if(PlayerData[playerid][pAdmin] >= 1){
        SendClientMessage(playerid, COLOR_GRAY, "[ADMIN LEVEL 1]: /goto, /get, /a, /an, /aduty, /checkplayer, /ban, /kick, /warn, /unwarn, /checkafk, /aslap, /auncuff");
        SendClientMessage(playerid, COLOR_GRAY, "[ADMIN LEVEL 1]: /reports, /apm");
    }
    if(PlayerData[playerid][pAdmin] >= 2){
        SendClientMessage(playerid, COLOR_GRAY, "[ADMIN LEVEL 2]: /setweather, /setweatherall, /tod, /resetplayer");
    }
    if(PlayerData[playerid][pAdmin] >= 3){
        SendClientMessage(playerid, COLOR_GRAY, "[ADMIN LEVEL 3]: /gotocar, /getcar, /togooc, /togtw, /tognewbie, /togvad, /listcars, /entercar");
    }
    if(PlayerData[playerid][pAdmin] >= 4){
        SendClientMessage(playerid, COLOR_GRAY, "[ADMIN LEVEL 4]: /sethp, /setam, /checkinv, /carvars, /checkgroup, /playerspawn, /jailtime, /unjail");
    }
    if(PlayerData[playerid][pAdmin] >= 5){
        SendClientMessage(playerid, COLOR_GRAY, "[ADMIN LEVEL 5]: /veh, /dv, /dvs, /near, /int, /recar, /acpr, /unban, /refuelall, /mute, /aunjail, /sendjail");
        SendClientMessage(playerid, COLOR_GRAY, "[ADMIN LEVEL 5]: /setint, /setworld, /mutemic, /unmutemic");
    }
    if(PlayerData[playerid][pAdmin] >= 1337){
        SendClientMessage(playerid, COLOR_GRAY, "[ADMIN LEVEL 1337]: /setplayer /savedata, /rehour, /restart, /setnewname, /addpc");
        SendClientMessage(playerid, COLOR_GRAY, "[ADMIN LEVEL 1337]: /spawnitem, /destroyitem, /destroyitemall, /itemlist, /sendmarket");
    }
    if(PlayerData[playerid][pAdmin] >= 1338){
        SendClientMessage(playerid, COLOR_GRAY, "[ADMIN LEVEL 1338]: /givemoney, /givevip, /randomprice, /spawnweapon, /removeweapon, /setadminname");
        SendClientMessage(playerid, COLOR_GRAY, "[DYNAMIC CMDS]: /jobcmds, /carcmds, /craftcmds, /sidejobcmds, /garagecmds, /doorcmds, /carsellcmds, /safezonecmds");
        SendClientMessage(playerid, COLOR_GRAY, "[DYNAMIC CMDS]: /groupcmds, /drugcmds, /arrestcmds, /pumpcmds, /gatecmds, /viewweapons, /homecmds, /atmcmds, /zonecmds, /accshopcmds");
        SendClientMessage(playerid, COLOR_GRAY, "[DYNAMIC CMDS]: /upgradeweaponcmds, /casinocmds, /bizcmds, /showercmds");
    }
    if(PlayerData[playerid][pAdmin] >= 1339){
        SendClientMessage(playerid, COLOR_GRAY, "[ADMIN LEVEL 1339]: /giveadmin");
    }
    SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
    return 1;
}

CMD:refreshnametag(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new userid;
    if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/refreshnametag [playerid]");
    if(userid == INVALID_PLAYER_ID) return 1;
    if(!LoggedIn[userid]) return 1;
    SetPlayerNameTag(userid, userid);
    return 1;
}

CMD:aboombox(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new string[128];

    if(AllSoundPlayerd == 1){
        foreach (new i : Player) if(LoggedIn[i]){
            if(IsPlayerInRangeOfPoint(playerid, 150.0, AllSoundPosition[0], AllSoundPosition[1], AllSoundPosition[2])){
                StopAudioStreamForPlayer(i);
            }
        }
        AllSoundPlayerd = 0;
    }
    else if(AllSoundPlayerd == 0){
        if(sscanf(params, "s[128]", string)) return SystemMsg(playerid, "/aboombox [url]");
        if(isnull(string)) return SystemMsg(playerid, "/aboombox [url]");
        GetPlayerPos(playerid, AllSoundPosition[0], AllSoundPosition[1], AllSoundPosition[2]);
        foreach (new i : Player) if(LoggedIn[i]){
            StopAudioStreamForPlayer(i);
            PlayAudioStreamForPlayer(i, string, AllSoundPosition[0], AllSoundPosition[1], AllSoundPosition[2], 150.0, 1);
        }
        AllSoundPlayerd = 1;
    }
    return 1;
}

CMD:checklogin(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    foreach(new i : Player) if(!LoggedIn[i]){
        SendClientMessageEx(playerid, -1, "[%d] %s ยังไม่ได้เข้าสู่ระบบ", i, ReturnName(i));
    }
    return 1;
}

CMD:checkpro(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    foreach(new i : Player) if(LoggedIn[i]){
        if(PlayerData[i][pPlayerhour] < 5){
            SendClientMessageEx(playerid, -1, "[%d] %s ชั่วโมงออนไลน์ต่ำกว่า 5", i, ReturnRoleplayName(i));
        }
    }
    return 1;
}

CMD:adestroybox(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 3)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	foreach (new i : Player) if (BoomboxData[i][boomboxPlaced] && IsPlayerInRangeOfPoint(playerid, 3.0, BoomboxData[i][boomboxPos][0], BoomboxData[i][boomboxPos][1], BoomboxData[i][boomboxPos][2])) {
		Boombox_Destroy(i);

		SendClientMessageEx(playerid, -1, "คุณได้ทำลาย Boombox ของ %s", ReturnRoleplayName(i));
		return SendClientMessageEx(i, -1, "%s ได้ทำลาย Boombox ของคุณ", ReturnRoleplayName(playerid));
	}
	ErrorMsg(playerid, "คุณไม่ได้อยู่ในขอบเขตของ Boombox ใด ๆ");
	return 1;
}


CMD:removeallchar(playerid){
    if(!LoggedIn[playerid]) return 1;
    
    if(PlayerData[playerid][pAdmin] < 1339) return ErrorMsg(playerid, "คุณไม่ใช่แอดมิน");
    mysql_tquery(dbCon, "SELECT * FROM `characters` WHERE `ActiveChar` < '4'", "RemoveCharAndOther", "");
    mysql_tquery(dbCon, "SELECT * FROM `accounts` WHERE `Active` < '4'", "RemoveAccount", "");
    SendClientMessage(playerid, -1, "คุณได้ลบตัวละครที่ไม่ได้เข้ามาทำการออนไลน์สำเร็จ");
    return 1;
}

forward RemoveAccount();
public RemoveAccount(){
	static
	    rows,
        string[128];

    new A_ID;
	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++){

        cache_get_value_name_int(i, "SQLID", A_ID);
        format(string, sizeof(string), "DELETE FROM `accounts` WHERE `Active` < '%d' AND `SQLID` = '%d'", 4, A_ID);
        mysql_tquery(dbCon, string);
	}
	printf("Remove Finish");
	return 1;
}

forward RemoveItemHome();
public RemoveItemHome()
{
	static
	    rows,
        string[128];

    new hID;
	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++){
        cache_get_value_name_int(i, "ID", hID);
        format(string, sizeof(string), "DELETE FROM `homestorage` WHERE `ID` = '%d'", hID);
        mysql_tquery(dbCon, string);
	}
	printf("Remove HomeItem Finish");
	return 1;
}

forward RemoveHome();
public RemoveHome()
{
	static
	    rows,
        string[128];

    new hID, CID;
	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++){
        cache_get_value_name_int(i, "homeID", hID);
        cache_get_value_name_int(i, "homeOwner", CID);

        format(string, sizeof(string), "SELECT ID FROM `homestorage` WHERE `ID` = '%d'", hID);
        mysql_tquery(dbCon, string, "RemoveItemHome");

        format(string, sizeof(string), "DELETE FROM `homes` WHERE `homeID` = '%d' AND `homeOwner` = '%d'", hID, CID);
        mysql_tquery(dbCon, string);
	}
	printf("Remove Home Finish");
	return 1;
}

forward RemoveCharAndOther();
public RemoveCharAndOther()
{
	static
	    rows,
        string[128];

    new CID, A_ID;
	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++){

        cache_get_value_name_int(i, "ID", CID);
        cache_get_value_name_int(i, "A_ID", A_ID);

        format(string, sizeof(string), "DELETE FROM `characters` WHERE `ActiveChar` < '%d' AND `ID` = '%d'", 4, CID);
        mysql_tquery(dbCon, string);

        format(string, sizeof(string), "DELETE FROM `accounts` WHERE `Active` < '%d' AND `SQLID` = '%d'", 4, A_ID);
        mysql_tquery(dbCon, string);

        format(string, sizeof(string), "DELETE FROM `inventory` WHERE `invOwner` = '%d'", CID);
        mysql_tquery(dbCon, string);

        format(string, sizeof(string), "DELETE FROM `cars` WHERE `carOwner` = '%d'", CID);
        mysql_tquery(dbCon, string);

        format(string, sizeof(string), "SELECT homeID, homeOwner FROM `homes` WHERE `homeOwner` = '%d'", CID);
        mysql_tquery(dbCon, string, "RemoveHome");
	}
	printf("Remove All Finish");
	return 1;
}

CMD:cdb(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new userid;
    if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/cdb [playerid]");
    if(userid == INVALID_PLAYER_ID) return 1;
    if(!LoggedIn[userid]) return 1;
    SendClientMessageEx(playerid, COLOR_RED, "- ผู้เล่น %s เปิดกล่องไปแล้วจำนวน %s กล่อง", ReturnRoleplayName(userid), FormatNumberNotMoney(PlayerData[userid][pTotalOpenBox]));
    return 1;
}

CMD:checkweapons(playerid, params[]){

    if(!LoggedIn[playerid]) return 0;

    if(PlayerData[playerid][pAdmin] >= 4){
        new userid;
        if(sscanf(params, "u", userid))
            return SystemMsg(playerid, "/checkweapons [playerid]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

        if(userid != INVALID_PLAYER_ID){
            if(LoggedIn[userid]){
                SendClientMessage(playerid, -1, "-------------------------------------------------------------");
                SendClientMessageEx(playerid, COLOR_DARKGREEN, "- อาวุธของ %s(%d)", ReturnRoleplayName(userid), userid);
                SendClientMessageEx(playerid, -1, "อาวุธปืนหนัก: %s [กระสุน: %d]", ReturnWeaponName(PlayerData[userid][pMyWeapon][0]), PlayerData[userid][pMyAmmo][0], PlayerData[userid][pMyWeaponLevel][0]);
                SendClientMessageEx(playerid, -1, "อาวุธปืนเบา: %s [กระสุน: %d]", ReturnWeaponName(PlayerData[userid][pMyWeapon][1]), PlayerData[userid][pMyAmmo][1], PlayerData[userid][pMyWeaponLevel][1]);
                SendClientMessageEx(playerid, -1, "อาวุธประชิด: %s [กระสุน: %d]", ReturnWeaponName(PlayerData[userid][pMyWeapon][2]), PlayerData[userid][pMyAmmo][2], PlayerData[userid][pMyWeaponLevel][2]);
                for(new i=0; i<MAX_INVENTORYPLAYERS; i++){
                    if(Inventory_Player[userid][i][itemHave]){
                        if(CheckItemIsWeaponMelee(userid, i) != -1){
                            SendClientMessageEx(playerid, -1, "- [%d] %s(%d) (ระดับตีบวก: %d) จำนวน %d", i, Inventory_Player[userid][i][itemName], Inventory_Player[userid][i][itemKey], Inventory_Player[userid][i][itemLevel], Inventory_Player[userid][i][itemQuantity]);
                        }

                        if(CheckItemIsWeaponPistol(userid, i) != -1){
                            SendClientMessageEx(playerid, -1, "- [%d] %s(%d) (ระดับตีบวก: %d) จำนวน %d", i, Inventory_Player[userid][i][itemName], Inventory_Player[userid][i][itemKey], Inventory_Player[userid][i][itemLevel], Inventory_Player[userid][i][itemQuantity]);
                        }

                        if(CheckItemIsWeaponAssaultRifle(userid, i) != -1){
                            SendClientMessageEx(playerid, -1, "- [%d] %s(%d) (ระดับตีบวก: %d) จำนวน %d", i, Inventory_Player[userid][i][itemName], Inventory_Player[userid][i][itemKey], Inventory_Player[userid][i][itemLevel], Inventory_Player[userid][i][itemQuantity]);
                        }
                    }
                    if(i >= 107) break;
                }
                SendClientMessage(playerid, -1, "-------------------------------------------------------------");
            }
        }
    }
    return 1;
}

CMD:checkinv(playerid, params[]){

    if(!LoggedIn[playerid]) return 0;

    if(PlayerData[playerid][pAdmin] >= 4){
        new userid;
        if(sscanf(params, "u", userid))
            return SystemMsg(playerid, "/checkinv [playerid]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

        if(userid != INVALID_PLAYER_ID){
            if(LoggedIn[userid]){
                SendClientMessage(playerid, -1, "-------------------------------------------------------------");
                SendClientMessageEx(playerid, COLOR_DARKGREEN, "- กระเป๋าของ %s(%d)", ReturnRoleplayName(userid), userid);
                for(new i=0; i<MAX_INVENTORYPLAYERS; i++){
                    if(Inventory_Player[userid][i][itemHave]){
                        SendClientMessageEx(playerid, -1, "- [%d] %s(%d) จำนวน %d", i, Inventory_Player[userid][i][itemName], Inventory_Player[userid][i][itemKey], Inventory_Player[userid][i][itemQuantity]);
                    }
                    if(i >= 107) break;
                }
                SendClientMessage(playerid, -1, "-------------------------------------------------------------");
            }
        }
    }
    return 1;
}

CMD:givewallet(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    new string[128];
    if(PlayerData[playerid][pAdmin] >= 1339){
        new userid, wallet;
        if(sscanf(params, "ud", userid, wallet))
            return SystemMsg(playerid, "/givewallet [playerid] [wallet]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

        if(userid != INVALID_PLAYER_ID){
            if(LoggedIn[userid]){
                AccountData[userid][uWallet] += wallet;
                SendClientMessageEx(userid, COLOR_ORANGE, "- Wallet ของคุณถูกเซตเป็น จำนวน %d จาก ผู้ดูแล", wallet);
                format(string, sizeof(string), "ผู้ดูแล %s ได้เซต Wallet กับ Username: %s จำนวน %d", ReturnRoleplayName(playerid), AccountData[userid][uName], wallet);
		        SendAdminsMessage(1, COLOR_GRAY, string);
                UpdatePlayerWallet(userid);
            }
        }
    }
    return 1;
}

CMD:changepass(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        new userid;
        if(sscanf(params, "d", userid))
            return SystemMsg(playerid, "/changepass [userid]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

        if(userid != INVALID_PLAYER_ID){
            if(LoggedIn[userid]){
                SetUserChangePass(playerid, userid);
            }
        }
    }
	return 1;
}

CMD:kick(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1){
        new userid, reason[128];
        if(sscanf(params, "uS(Not specified)[128]", userid, reason))
            return SystemMsg(playerid, "/kick [playerid] [สาเหตุ]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
        if(userid != INVALID_PLAYER_ID){

            SendClientMessageToAllEx(0xFF6100AA, "ผู้ดูแลระบบ ได้ทำการ 'เตะ' ผู้เล่น '%s(%d)' สาเหตุ: %s", ReturnRoleplayName(userid), userid, reason);
            SetTimerEx("FixKick", 500, false, "d", userid);
        }
    }
    return 1;
}

CMD:ban(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1){
        new userid, reason[128];
        if(sscanf(params, "uS(Not specified)[128]", userid, reason))
            return SystemMsg(playerid, "/ban [playerid] [สาเหตุ]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
        if(userid != INVALID_PLAYER_ID){

            PlayerData[userid][pBan] = 1;

            if(!IsAndroidPlayer(userid)) Blacklist_Add(PlayerData[userid][pLastIP], AccountData[userid][uName], AccountData[playerid][uName], reason);

            SendClientMessageToAllEx(0xFF6100AA, "ผู้ดูแลระบบ ได้ทำการ 'แบน' ผู้เล่น '%s(%d)' สาเหตุ: %s", ReturnRoleplayName(userid), userid, reason);
            SetTimerEx("FixKick", 500, false, "d", userid);
        }
    }
    return 1;
}

CMD:unban(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    new string[128];
    if(PlayerData[playerid][pAdmin] >= 5){
        if (isnull(params) || strlen(params) > 64)
            return SystemMsg(playerid, "/addpc [ชื่อตัวละคร]");

        UnbanCharacter(params);

        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ปลดแบน \"%s\" สำเร็จ", params);
        format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปลดแบน \"%s\" เรียบร้อยแล้ว", ReturnRoleplayName(playerid), params);
        SendAdminsMessage(1, COLOR_YELLOW, string);
    }
    return 1;
}

CMD:unwarn(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1){
        new userid, reason[128];
        if(sscanf(params, "uS(Not specified)[128]", userid, reason))
            return SystemMsg(playerid, "/unwarn [playerid]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
        if(userid != INVALID_PLAYER_ID){
            if(LoggedIn[userid]){
                PlayerData[userid][pWarn] -= 1;
                SendClientMessageEx(playerid, COLOR_RED, "- คุณได้ลดการเตือน %s เรียบร้อยแล้ว (%d/3)", PlayerData[userid][pWarn]);
                SendClientMessageEx(userid, COLOR_RED, "- คุณถูกลดการเตือนจากผู้ดูแล ตอนนี้คุณมี Warn อยู่ (%d/3)", PlayerData[userid][pWarn]);
            }
        }
    }
    return 1;
}

CMD:sendjail(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 5) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");
    new userid;
    if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/sendjail [userid]");
    if(userid == INVALID_PLAYER_ID) return 1;
    if(userid != INVALID_PLAYER_ID){
        if(LoggedIn[userid]){
            if(PlayerData[userid][pJail] == 0) return ErrorMsg(playerid, "ผู้เล่นนั้นไม่ได้ติดคุก");
            SendPlayerToPrisonNow(userid);
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ส่ง %s กลับเข้าคุกแล้ว", ReturnRoleplayName(userid));
        }
    }
    return 1;
}

CMD:setint(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 5) return 1;
    new userid, int;
    if(sscanf(params, "ud", userid, int)) return SystemMsg(playerid, "/setint [playerid] [intid]");
    if(userid == INVALID_PLAYER_ID) return 1;
    if(!LoggedIn[userid]) return 1;
    SetPlayerInterior(userid, int);
    return 1;
}

CMD:setworld(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 5) return 1;
    new userid, world;
    if(sscanf(params, "ud", userid, world)) return SystemMsg(playerid, "/setworld [playerid] [worldid]");
    if(userid == INVALID_PLAYER_ID) return 1;
    if(!LoggedIn[userid]) return 1;
    SetPlayerVirtualWorld(userid, world);
    return 1;
}

CMD:warn(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1){
        new userid, reason[128];
        if(sscanf(params, "uS(Not specified)[128]", userid, reason))
            return SystemMsg(playerid, "/warn [playerid] [reason]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
        if(userid != INVALID_PLAYER_ID){
            if(LoggedIn[userid]){
                PlayerData[userid][pWarn] += 1;
                SendClientMessageEx(userid, COLOR_RED, "- คุณได้รับการเตือนจากผู้ดูแล ตอนนี้คุณมี Warn อยู่ (%d/3)", PlayerData[userid][pWarn]);
                SendClientMessageToAllEx(0xFF0000AA, "ผู้ดูแลระบบ ได้ทำการ 'เตือน' ผู้เล่น '%s(%d)' สาเหตุ: %s", ReturnRoleplayName(userid), userid, reason);
                if(PlayerData[userid][pWarn] >= 3){
                    PlayerData[userid][pBan] = 1;
                    SendClientMessageToAllEx(0xFF6100AA, "ระบบ ได้ทำการ 'แบน' ผู้เล่น '%s(%d)' สาเหตุ: Warn ครบ 3 ครั้ง", ReturnRoleplayName(userid), userid);
                    SetTimerEx("FixKick", 500, false, "d", userid);
                }
            }
        }
    }
    return 1;
}

CMD:resetplayer(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 2){
        new userid;
        if(sscanf(params, "u", userid))
            return SystemMsg(playerid, "/resetplayer [playerid]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

        if(userid != INVALID_PLAYER_ID){
             ResetPlayer(playerid);
        }
    }
    return 1;
}

CMD:acpr(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 5){
        new userid;
        if(sscanf(params, "u", userid))
            return SystemMsg(playerid, "/acpr [playerid]");

        if(userid == INVALID_PLAYER_ID)
            return 1;

        PlayerData[userid][pInjured] = 0;
        PlayerData[userid][pInjuredTime] = 0;
        TimeInjuredStart[userid] = 0;
        PlayerData[userid][pInHospital] = 0;
        PlayerData[userid][pHospitalType] = 0;
        TogglePlayerControllable(userid, 1);
        ClearAnimations(userid);
        SetPlayerColor(userid, 0xFFFFFF00);
        ResetDamages(userid);
    }
    return 1;
}

CMD:randomprice(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        RandomPriceJob();
    }
    return 1;
}

CMD:givevip(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        Dialog_ShowEasy(playerid, DIALOGVIPMEMBER, DIALOG_STYLE_INPUT, "จัดการระดับผู้บริจาค", "กรอก ID ผู้เล่นที่ต้องการจะให้ Vip", "ตกลง", "ยกเลิก");
    }
    return 1;
}

CMD:checkplayer(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1){
        new userid;
        if(sscanf(params, "u", userid))
            return SystemMsg(playerid, "/checkplayer [playerid]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

        if(userid != INVALID_PLAYER_ID){
            ShowStatsForPlayer(playerid, userid);
        }
    }
    return 1;
}

CMD:setadminname(playerid, params[]){
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pAdmin] >= 1338){
            new userid, adminname[64], string[128];
            if(sscanf(params, "us[64]", userid, adminname)) return SystemMsg(playerid, "/setadminname [userid] [nameadmin]");
            if(userid == INVALID_PLAYER_ID) return 1;
            if(userid != INVALID_PLAYER_ID){
                if(LoggedIn[userid]){
                    format(PlayerData[userid][pAdminName], 64, adminname);
                    format(string, sizeof(string), "ผู้ดูแล %s ได้เปลี่ยนชื่อแอดมินของ %s เป็น %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), adminname);
		            SendAdminsMessage(1, COLOR_GRAY, string);
                }
            }
        }
    }
    return 1;
}

CMD:aduty(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1){
        if(AdminDuty[playerid] == 0){
            AdminDuty[playerid] = 1;
            SetPlayerName(playerid, PlayerData[playerid][pAdminName]);
            SetPlayerNameTag(playerid, playerid);
            foreach(new x : Player){
                if(!LoggedIn[x]) continue;
                if(PlayerData[x][pAdmin] > 1)
                    SendClientMessageEx(x, 0xFFA200AA, "[AdminDuty] ผู้ดูแลระบบ %s(%d) ได้เริ่มปฏิบัติงานแล้ว", PlayerData[playerid][pAdminName], playerid);
            }
        }
        else{
            AdminDuty[playerid] = 0;
            SetPlayerName(playerid, PlayerData[playerid][pUsername]);
            SetPlayerNameTag(playerid, playerid);
            foreach(new x : Player) {
                if(!LoggedIn[x]) continue;
                if(PlayerData[x][pAdmin] > 1)
                    SendClientMessageEx(x, 0xFFA200AA, "[AdminDuty] ผู้ดูแลระบบ %s(%d) ได้ยกเลิกปฏิบัติงานแล้ว", PlayerData[playerid][pAdminName], playerid);
            }
        }
    }
    return 1;
}

CMD:an(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    
    if(PlayerData[playerid][pAdmin] == 0) return 1;

    if(isnull(params)) return SystemMsg(playerid, "/an [message]");

    if(PlayerData[playerid][pAdmin] >= 1){
        if (strlen(params) > 80){
            SendClientMessageToAllEx(0xFF1F00AA, "[Administrator] {FFBD00}%s: {FFFFFF}%.80s", PlayerData[playerid][pAdminName], params);
            SendClientMessageToAllEx(0xFF1F00AA, "{FFFFFF}...%s", params[80]);
        }
        else{
            SendClientMessageToAllEx(0xFF1F00AA, "[Administrator] {FFBD00}%s: {FFFFFF}%s", PlayerData[playerid][pAdminName], params);
        }
    }
    return 1;
}

CMD:a(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1){
        if(isnull(params))
            return SystemMsg(playerid, "/a [message]");
            
        foreach(new x : Player) if(LoggedIn[x]){
            if(PlayerData[x][pAdmin] <= 0) continue;
            if (strlen(params) > 80){
                SendClientMessageEx(x, 0xFFFD68AA, "[%d] %s: %.80s", PlayerData[playerid][pAdmin], PlayerData[playerid][pAdminName], params);
                SendClientMessageEx(x, 0xFFFD68AA, "...%s", params[80]);
            }
            else{
                SendClientMessageEx(x, 0xFFFD68AA, "[%d] %s: %s", PlayerData[playerid][pAdmin], PlayerData[playerid][pAdminName], params);
            }
        }
    }
    return 1;
}

CMD:mute(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] >= 5){
        new userid, seconds;
        if(sscanf(params, "uI(1)", userid, seconds)) return SystemMsg(playerid, "/mute [playerid] [วินาที]");
        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
        if(userid != INVALID_PLAYER_ID && LoggedIn[userid]){
            TimeMute[userid] = seconds;
            SendClientMessageToAllEx(0xFF0000AA, "ผู้ดูแลระบบ ได้ทำการ 'ใบ้' ผู้เล่น '%s(%d)' จำนวน %d วินาที", ReturnRoleplayName(userid), userid, seconds);
        }
    }
    return 1;
}

CMD:rehour(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1337){
        HourTime();
    }
    return 1;
}

CMD:specveh(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] > 1){
        new vehicleid;
        if(sscanf(params, "d", vehicleid)) return SystemMsg(playerid, "/specveh [vehicleid]");
        PlayerSpectateVehicle(playerid, vehicleid);
    }
    return 1;
}

alias:spec("ส่อง")
CMD:spec(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1) {
        new
            userID;

        if(sscanf(params, "u", userID))
            return SystemMsg(playerid, "/spec [ไอดีผู้เล่น]");
        
        if(userID == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

        if(!IsPlayerConnected(userID))
            return ErrorMsg(playerid, "ไอดีผู้เล่นที่คุณระบุ ไม่ได้เชื่อต่อกับเซิฟเวอร์");
        
        if(PlayerData[playerid][pSpec] == INVALID_PLAYER_ID) {
            GetPlayerPos(playerid, PlayerData[playerid][pPosX], PlayerData[playerid][pPosY], PlayerData[playerid][pPosZ]);
            Character_Save(playerid);
            PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);
            PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
            //PlayerData[playerid][pSkin] = GetPlayerSkin(playerid);
            GetPlayerHealth(playerid, PlayerData[playerid][pHP]);
            GetPlayerArmour(playerid, PlayerData[playerid][pAM]);
        }
        PlayerData[playerid][pSpec] = userID;
        TogglePlayerSpectating(playerid, true);
        SetPlayerColor(playerid, 0xFFFFFF00);
        SetPlayerInterior(playerid, GetPlayerInterior(userID));
        SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(userID));

        if(IsPlayerInAnyVehicle(userID)) {
            PlayerSpectateVehicle(playerid, GetPlayerVehicleID(userID));
        }
        else {
            PlayerSpectatePlayer(playerid, userID);
        }
    }
    return 1;
}

CMD:near(playerid)
{
    if(!LoggedIn[playerid]) return 0;
    new
        id = -1,
        string[128];

    if(PlayerData[playerid][pAdmin] < 5)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    if ((id = Job_Nearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้งานไอดี : %d (SQLID: %d)", id, JobData[id][jobID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Entrance_Nearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ทางเข้าไอดี : %d (SQLID: %d)", id, EntranceData[id][entranceID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Craft_Nearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้จุดคราฟไอดี : %d (SQLID: %d)", id, CraftData[id][craftID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Garage_GetNearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้จุดการาจไอดี : %d (SQLID: %d)", id, CraftData[id][craftID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Garage_StoreNearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้จุดการาจไอดี : %d (SQLID: %d)", id, CraftData[id][craftID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Garage_StoreNearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้จุดการาจไอดี : %d (SQLID: %d)", id, CraftData[id][craftID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Sidejob_Nearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้จุดอาชีพเสริมไอดี : %d (SQLID: %d)", id, CraftData[id][craftID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Drug_Nearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้เก็บยาไอดี : %d (SQLID: %d)", id, DrugData[id][drugID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Drug_ProcessNearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ Process ยา ไอดี : %d (SQLID: %d)", id, DrugData[id][drugID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Drug_DeliverNearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ Deliver ยา ไอดี : %d (SQLID: %d)", id, DrugData[id][drugID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Home_Nearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ Home ไอดี : %d (SQLID: %d)", id, HomeData[id][homeID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Home_Inside(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ ภายใน Home ไอดี : %d (SQLID: %d)", id, HomeData[id][homeID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = SafeZone_Nearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ SafeZone ไอดี : %d (SQLID: %d)", id, HomeData[id][homeID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Gate_Nearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ Gate ไอดี : %d (SQLID: %d)", id, GateData[id][gateID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = AccShop_Nearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ AccShop ไอดี : %d (SQLID: %d)", id, AccDataShop[id][accShopID]);
        SendClientMessage(playerid, -1, string);
    }

    if ((id = Casino_Nearest(playerid)) != -1)
    {
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ Casino ไอดี : %d (SQLID: %d)", id, CasinoData[id][casinoID]);
        SendClientMessage(playerid, -1, string);
    }

    if((id = Shower_Nearest(playerid)) != -1){
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ จุดอาบน้ำ ไอดี : %d (SQLID: %d)", id, ShowerData[id][showerID]);
        SendClientMessage(playerid, -1, string);
    } 

    if((id = NewCow_Nearest(playerid, 1)) != -1){
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ วัว ไอดี : %d (SQLID: %d)", id, NewCowData[id][newcowID]);
        SendClientMessage(playerid, -1, string);
    } 

    if((id = NewCow_Nearest(playerid, 2)) != -1){
        format(string, sizeof(string), "คุณกำลังยืนอยู่ใกล้ วัว ไอดี : %d (SQLID: %d)", id, NewCowData[id][newcowID]);
        SendClientMessage(playerid, -1, string);
    }    
    return 1;
}

CMD:setskintemp(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1337) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");
    new userid, skinid, string[128];
    if(sscanf(params, "ud", userid, skinid)) return SystemMsg(playerid, "/setskintemp [playerid] [skinid]");
    if(userid == INVALID_PLAYER_ID) return 1;
    if(!LoggedIn[userid]) return 1;
    SetPlayerSkin(playerid, skinid);
    format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'สกินชั่วคราว' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), skinid);
    SendAdminsMessage(1, COLOR_GRAY, string);
    return 1;
}

CMD:setplayer(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1337)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    new userid, type, amount;
    new string[128];
    if(sscanf(params, "udI(1)", userid, type, amount)){
        SystemMsg(playerid, "/setplayer [playerid] [OPTION] [Amount]");
        SystemMsg(playerid, "[OPTION]: [1]:Level, [2]:Skin, [3]:Hunger, [4]:Water, [5]:Energy, [6]:MaxItem, [7]:ItemAmount, [8]:RedMoney");
        SystemMsg(playerid, "[OPTION]: [9]:NumberPhone, [10]:WeaponDealerSkills, [11]:WeaponDealerExp, [12]:PlayerHour, [13]: InvWeight");
        SystemMsg(playerid, "[OPTION]: [14]:Shower, [15]:Stress");
        return 1;
    }

    if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

    if(userid != INVALID_PLAYER_ID){
        if(type == 1){
            PlayerData[userid][pLevel] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'เลเวล' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'เลเวล' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 2){
            PlayerData[userid][pSkin] = amount;
            SetPlayerSkin(userid, amount);
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'สกิน' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'สกิน' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 3){
            PlayerData[userid][pHunger] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'ความหิว' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'ความหิว' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 4){
            PlayerData[userid][pWater] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'ความกระหาย' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'ความกระหาย' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 5){
            PlayerData[userid][pEnergy] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'พละกำลัง' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'พละกำลัง' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 6){
            PlayerData[userid][pMaxItem] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'จำนวนช่องกระเป๋า' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'จำนวนช่องกระเป๋า' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 7){
            PlayerData[userid][pItemAmount] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'จำนวนไอเท็มแต่ละชนิด' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'จำนวนไอเท็มแต่ละชนิด' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 8){
            PlayerData[userid][pRedMoney] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'เงินแดง' ของคุณ เป็น %s", FormatNumber(amount));
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'เงินแดง' ของ %s เป็น %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), FormatNumber(amount));
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 9){
            PlayerData[userid][pNumberPhone] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'เบอร์โทรศัพท์' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'เบอร์โทรศัพท์' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 10){
            PlayerData[userid][pWeaponDealerSkills] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'สกิลการคราฟอาวุธ' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'สกิลการคราฟอาวุธ' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 11){
            PlayerData[userid][pWeaponDealerExp] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'Exp ของสกิลการคราฟอาวุธ' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'Exp ของสกิลการคราฟอาวุธ' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 12){
            PlayerData[userid][pPlayerhour] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'ชั่วโมงออนไลน์' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'ชั่วโมงออนไลน์' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 13){
            PlayerData[userid][pInvMaxWeight] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'น้ำหนักกระเป๋า' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'น้ำหนักกระเป๋า' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 14){
            PlayerData[userid][pShower] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'ความสะอาด' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'ความสะอาด' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
        if(type == 15){
            PlayerData[userid][pStress] = amount;
            SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปรับ 'ความเครียด' ของคุณ เป็น %d", amount);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ 'ความเครียด' ของ %s เป็น %d", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), amount);
		    SendAdminsMessage(1, COLOR_GRAY, string);
            return 1;
        }
    }
    return 1;
}

CMD:aslap(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	new
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "u", userid))
	    return SystemMsg(playerid, "/aslap [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return ErrorMsg(playerid, "ผู้เล่นที่ระบุไม่ถูกต้อง");

	new
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(userid, x, y, z);
	SetPlayerPosEx(userid, x, y, z + 5, PlayerData[userid][pInterior], PlayerData[userid][pWorld]);

	PlayerPlaySound(userid, 1130, 0.0, 0.0, 0.0);
	return 1;
}

CMD:get(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	new
		userid;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendClientMessage(playerid,-1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "u", userid)){
	 	SendClientMessage(playerid,-1, "/get [player or name]");
		return 1;
	}

	if (userid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, -1, "ไอดีผู้เล่นไม่ถูกต้อง");

	SendPlayerToPlayer(userid, playerid);
	return 1;
}

CMD:setweather(playerid, params[]){
    new weatherid;

	if (PlayerData[playerid][pAdmin] < 2)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", weatherid))
	    return SystemMsg(playerid, "/setweather [weather ID]");

	foreach(new i : Player){
        if(LoggedIn[i]){
            SetPlayerWeather(i, weatherid);
        }
    }
	g_serverWeather = weatherid;
    SetWeather(g_serverWeather);
    SendClientMessageEx(playerid, -1, "คุณได้เปลี่ยนสภาพอากาศเป็น: %d", weatherid);
    return 1;
}

CMD:tod(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 2)
    {
        new time,str[128];
        if(sscanf(params, "d",time)) return SendClientMessage(playerid, COLOR_GRAY, "/tod [hour]");
        if(time < 0 || time >24)return SendClientMessage(playerid, COLOR_GRAY, "/tod [0-24]");
            else if(time <= 24 && time >= 0)
            {
                ghour = time;
                SetWorldTime(time);
                format(str, sizeof(str), "%s ได้ปรับเวลาเป็น %d!", ReturnName(playerid), time);
                SendAdminsMessage(1, COLOR_GRAY, str);
            }
    }
    return 1;
}

CMD:atod(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 2)
    {
        new time;
        if(sscanf(params, "d",time)) return SendClientMessage(playerid, COLOR_GRAY, "/tod [hour]");
        if(time < 0 || time >24)return SendClientMessage(playerid, COLOR_GRAY, "/tod [0-24]");
        else if(time <= 24 && time >= 0){
            SetWorldTime(time);
        }
    }
    return 1;
}

alias:sendmarket("sm")
CMD:sendmarket(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 5) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");
    new userid, string[64];
    if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/sendmarket [playerid]");
    if(userid == INVALID_PLAYER_ID) return 0;
    if(!LoggedIn[userid]) return 0;
    if(PlayerData[userid][pFirstTime] == 1) return ErrorMsg(playerid, "ผู้เล่นนั้นยังทำข้อสอบไม่เรียบร้อย");
    PlayerIsDropMap[userid] = false;
    SetPlayerPosEx(userid,1120.4299,-1378.5870,14.2879, 0, 0);
    SendClientMessageEx(playerid, -1, "- คุณได้ส่ง %s(%d) ไปยังหน้าตลาดกลางเรียบร้อยแล้ว", ReturnRoleplayName(userid), userid);
    format(string, sizeof(string), "ผู้ดูแล %s ได้ส่ง %s ไปยังหน้าตลาดแล้ว", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
    SendAdminsMessage(1, COLOR_GRAY, string);
    return 1;
}

CMD:gotopos(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1337)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    if(IsPlayerConnected(playerid))
    {
        new
            interiorID, world,
            Float: coordinates[3];

        if(sscanf(params, "fffdd", coordinates[0], coordinates[1], coordinates[2], interiorID, world)) {
            return SendClientMessage(playerid, COLOR_GREY, "การใช้งาน : /gotopos [x] [y] [z] [interior id] [world]");
        }
        else {
            SetPlayerInterior(playerid, interiorID);
            SetPlayerVirtualWorld(playerid, world);
            SetPlayerPos(playerid, coordinates[0], coordinates[1], coordinates[2]);
        }
    }
    return 1;
}

alias:goto("tp")
CMD:goto(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	new
	    id;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendClientMessage(playerid,-1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "u", id))
 	{
	 	SendClientMessage(playerid,-1, "/goto [player or name]");
		return 1;
	}

    if (id == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, -1, "ไอดีผู้เล่นไม่ถูกต้อง");

	SendPlayerToPlayer(playerid, id);
	return 1;
}

CMD:gotocar(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	new vehicleid;

    if (PlayerData[playerid][pAdmin] < 3)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", vehicleid))
	    return SystemMsg(playerid, "/gotocar [veh]");

	if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
		return SendClientMessage(playerid, -1, "คุณระบุไอดียานพาหนะไม่ถูกต้อง");

	new
	    Float:x,
	    Float:y,
	    Float:z;

	GetVehiclePos(vehicleid, x, y, z);
	SetPlayerPosEx(playerid, x, y - 2, z + 2, GetPlayerInterior(playerid),GetPlayerVirtualWorld(playerid));

	return 1;
}

CMD:getcar(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	new vehicleid;

    if (PlayerData[playerid][pAdmin] < 3)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", vehicleid))
	    return SystemMsg(playerid, "/getcar [veh]");

	if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
		return SendClientMessage(playerid, -1, "คุณระบุไอดียานพาหนะไม่ถูกต้อง");

	new
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(playerid, x, y, z);
	SetVehiclePosEx(vehicleid, x + 2, y - 2, z);

 	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
	LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));

	return 1;
}

CMD:veh(playerid, params[]){
	new
	    model[32],
		color1,
		color2;

    if (PlayerData[playerid][pAdmin] < 5)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "s[32]I(-1)I(-1)", model, color1, color2))
	    return SystemMsg(playerid, "/veh [model id/name] <color 1> <color 2>");

	if ((model[0] = GetVehicleModelByName(model)) == 0)
	    return ErrorMsg(playerid, "ไอดีรุ่นไม่ถูกต้อง");

	new
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:a,
		vehicleid;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	vehicleid = CreateVehicle(model[0], x, y + 2, z, a, color1, color2, 0);
	if (GetPlayerInterior(playerid) != 0)
	    LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));

	if (GetPlayerVirtualWorld(playerid) != 0)
		SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));

	if (IsABoat(vehicleid) || IsAPlane(vehicleid) || IsAHelicopter(vehicleid))
	    PutPlayerInVehicleEx(playerid, vehicleid, 0);

    ResetVehicle(vehicleid);
	CoreVehicles[vehicleid][vehTemporary] = true;
    SetEngineStatus(vehicleid, true);
    SetLightStatus(vehicleid, true);
	PutPlayerInVehicleEx(playerid, vehicleid, 0);
	SendClientMessageEx(playerid, -1, "คุณได้สร้างยานพาหนะชั่วคราว %s (%d, %d)", ReturnVehicleModelName(model[0]), color1, color2);
	return 1;
}

CMD:entercar(playerid, params[])
{
	new vehicleid, seatid;

    if (PlayerData[playerid][pAdmin] < 3)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", vehicleid))
	    return SystemMsg(playerid, "/entercar [veh]");

	if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
		return ErrorMsg(playerid, "คุณระบุไอดียานพาหนะไม่ถูกต้อง");

	seatid = GetAvailableSeat(vehicleid, 0);

	if (seatid == -1)
	    return ErrorMsg(playerid, "ไม่มีที่นั่งเหลือที่จะเข้าไป");

	PutPlayerInVehicleEx(playerid, vehicleid, seatid);
	return 1;
}

alias:desvehicles("dvs")
CMD:desvehicles(playerid, params[]){
    if (PlayerData[playerid][pAdmin] < 5)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

    for (new i = 1; i != MAX_VEHICLES; i ++) if (IsValidVehicle(i) && CoreVehicles[i][vehTemporary]){
        ResetVehicle(i);
		TRP_DestroyVehicle(i);
    }
   	SendClientMessage(playerid, -1, "คุณได้ทำลายยานพาหนะผู้ดูแลทั้งหมด");
    return 1;
}

alias:desvehicle("dv")
CMD:desvehicle(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 5)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (IsPlayerInAnyVehicle(playerid))
	{
	    new vehicleid = GetPlayerVehicleID(playerid);

	    if (CoreVehicles[vehicleid][vehTemporary]){
            ResetVehicle(vehicleid);
	        TRP_DestroyVehicle(vehicleid);
	        SendClientMessage(playerid, -1, "คุณได้ทำลายยานพาหนะผู้ดูแล");
		}
		else{
		    ErrorMsg(playerid, "คุณไม่สามารถทำลายยานพาหนะที่ไม่ชั่วคราวได้");
		}
	}
	return 1;
}

CMD:checkneon(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
        new vehicleid = GetPlayerVehicleID(playerid);
        if(vehicleid != INVALID_VEHICLE_ID){
            for(new i=0; i<4; i++){
                SendClientMessageEx(playerid, -1, "Neon [slot %d] = %d", i, NeonVehicle[vehicleid][i]);
            }
        }
    }
    return 1;
}

CMD:giveadmin(playerid, params[]) 
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1339)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติให้ใช้คำสั่งนี้");

    new userid, level;
    if(sscanf(params, "ud", userid, level))
        return SystemMsg(playerid, "/ให้แอดมิน [ไอดีผู้เล่น/ชื่อผู้เล่น] [ระดับ]");

    if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

    if(userid != INVALID_PLAYER_ID)
    {
        PlayerData[userid][pAdmin] = level;
        SendClientMessageEx(playerid, -1, "{FE0000}คุณได้ให้ยศแอดมินกับ {FECC00}%s {FE0000}ระดับ {FECC00}%d", ReturnRoleplayName(userid), level);
        SendClientMessageEx(userid, -1, "{FE0000}ผู้ดูแล {FECC00}%s {FE0000}ได้ให้ยศแอดมินระดับ {FECC00}%d {FE0000}กับคุณ", ReturnRoleplayName(playerid), level);
    }
    else
        return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");

    return 1;
}

CMD:sethp(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 4)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติให้ใช้คำสั่งนี้");

    new userid, Float:amount;
    if(sscanf(params, "uf", userid, amount))
        return SystemMsg(playerid, "/sethp [ไอดีผู้เล่น/ชื่อผู้เล่น] [จำนวน]");

    if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

    if(userid != INVALID_PLAYER_ID){
        SetPlayerHealth(userid, amount);
        SendClientMessageEx(playerid, -1, "{FE0000}คุณได้เซ็ต 'เลือด' ของ {FECC00}%s {FE0000}เป็น %.2f", ReturnRoleplayName(userid), amount);
    }
    else return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
    return 1;
}

CMD:setam(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 4)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติให้ใช้คำสั่งนี้");

    new userid, Float:amount;
    if(sscanf(params, "uf", userid, amount))
        return SystemMsg(playerid, "/setam [ไอดีผู้เล่น/ชื่อผู้เล่น] [จำนวน]");

    if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

    if(userid != INVALID_PLAYER_ID)
    {
        SetPlayerArmour(userid, amount);
        SendClientMessageEx(playerid, -1, "{FE0000}คุณได้เซ็ต 'เกราะ' ของ {FECC00}%s {FE0000}เป็น %.2f", ReturnRoleplayName(userid), amount);
    }
    else
        return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
    return 1;
}

CMD:checkwallet(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "5 อันดับ Wallet สูงสุด", TopRankWallet, "ตกลง", "");
    return 1;
}

StorePlayerWeapon(playerid){
    if(PlayerData[playerid][pMyWeapon][1] != 0){
        PlayerData[playerid][pDelayWeapon][1] = 0;
        OnPlayerStoreWeapon2(playerid, PlayerData[playerid][pMyWeapon][1]);
    }

    if(PlayerData[playerid][pMyWeapon][2] != 0){
        PlayerData[playerid][pDelayWeapon][2] = 0;
        OnPlayerStoreWeapon3(playerid, PlayerData[playerid][pMyWeapon][2]);
    }
    return 1;
}

CMD:savedata(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;

    if(PlayerData[playerid][pAdmin] < 1337)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    foreach (new i : Player) if(LoggedIn[playerid]){
        if(PlayerData[playerid][pFirstTime]) continue;
        if(Character_Save(i)){
            printf("[SaveData]: %s SaveData Successfully", ReturnRoleplayName(i));
            continue;
        }
	}

    foreach(new i : Iter_Biz) Biz_Save(i);

    printf("Successfully Save");
    SendClientMessage(playerid, -1, "คุณได้เซฟข้อมูลผู้เล่นทั้งหมดเรียบร้อยแล้ว");
    return 1;
}

CMD:givemoney(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1338)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติให้ใช้คำสั่งนี้");

    new userid, amount;
    if(sscanf(params, "ud", userid, amount))
        return SystemMsg(playerid, "/givemoney [ไอดีผู้เล่น/ชื่อผู้เล่น] [จำนวน]");

    if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

    if(userid != INVALID_PLAYER_ID)
    {
        new string[128];

        GiveMoney(userid, amount, "Get From Admin %s", ReturnRoleplayName(playerid));
        format(string, sizeof(string), "ผู้ดูแล %s ได้เสกเงินให้กับ %s จำนวน %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), FormatNumber(amount));
        SendAdminsMessage(1, COLOR_YELLOW, string);
        format(string, sizeof(string), "ผู้ดูแล %s ได้เสกเงินให้กับคุณ จำนวน %s", ReturnRoleplayName(playerid), FormatNumber(amount));
        SendClientMessage(userid, -1, string);
        Log_Write("logs/setmoney.txt", "[%s] %s Give Money to %s amount %s", ReturnDate(), ReturnRoleplayName(playerid), ReturnRoleplayName(userid), FormatNumber(amount));
    }
    else
        return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
    return 1;
}

forward CheckChangeName(playerid, userid);
public CheckChangeName(playerid, userid)
{
 	if(cache_num_rows()) {
         format(PlayerData[playerid][pNameChangeTemp], 64, "");
         ErrorMsg(playerid, "ชื่อนี้มีผู้ใช้งานแล้ว!");
    }
    else{

        if(!IsValidRpName(PlayerData[playerid][pNameChangeTemp])){
            return ErrorMsg(playerid, "ชื่อไม่ถูกต้องตามหลัก Roleplay");
        }

        new string[128];
        new query[400];
        format(string, sizeof(string), "ผู้ดูแล ได้เปลี่ยนชื่อให้คุณเป็น %s", PlayerData[playerid][pNameChangeTemp]);
        SendClientMessage(userid, -1, string);
        format(string, sizeof(string), "ผู้ดูแล %s ได้เปลี่ยนชื่อให้ %s เป็น %s", ReturnRoleplayName(playerid), ReturnName(userid), PlayerData[playerid][pNameChangeTemp]);
        SendAdminsMessage(1, COLOR_YELLOW, string);
        SetPlayerName(userid, PlayerData[playerid][pNameChangeTemp]);
        format(PlayerData[userid][pUsername], 64, PlayerData[playerid][pNameChangeTemp]);
        mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET Username = '%e' WHERE ID = %d LIMIT 1", PlayerData[userid][pUsername], PlayerData[userid][pID]);
        mysql_tquery(dbCon, query);
    }
	return 1;
}

CMD:setnewname(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1337){
        new userid, newname[64];
        new query[400];
        if(sscanf(params, "us[64]", userid, newname))
            return SystemMsg(playerid, "/setnewname [playerid] [newname]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

        if(userid != INVALID_PLAYER_ID){
            if(LoggedIn[userid]){
                mysql_format(dbCon, query, sizeof(query), "SELECT * FROM `characters` WHERE `Username` = '%e' LIMIT 1", newname);
                mysql_tquery(dbCon, query, "CheckChangeName", "ii", playerid, userid);

                format(PlayerData[playerid][pNameChangeTemp], 64, newname);
            }
        }
    }
    return 1;
}

CMD:playerspawn(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 4){
        new userid;
        if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/spawnplayer [playerid]");

        if(!LoggedIn[userid]) return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");

        SpawnPlayer(userid);
    }
    return 1;
}

CMD:togooc(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 3)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    if(TogOOC == 0){
        TogOOC = 1;
        SendClientMessageToAll(0xFF8A9EAA, "(( ผู้ดูแลได้ปิด OOC แล้ว ))");
    }
    else if(TogOOC == 1){
        TogOOC = 0;
        SendClientMessageToAll(0xFF8A9EAA, "(( ผู้ดูแลได้เปิด OOC แล้ว ))");
    }
    return 1;
}

CMD:togvad(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 3)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    if(TogVad == 0){
        TogVad = 1;
        SendClientMessageToAll(0x42CBFFAA, "(( ผู้ดูแลได้ปิด VAD แล้ว ))");
    }
    else if(TogVad == 1){
        TogVad = 0;
        SendClientMessageToAll(0x42CBFFAA, "(( ผู้ดูแลได้เปิด VAD แล้ว ))");
    }
    return 1;
}

CMD:tognewbie(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 3)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    if(TogNewbie == 0){
        TogNewbie = 1;
        SendClientMessageToAll(0xFFECA1AA, "(( ผู้ดูแลได้ปิด Newbie แล้ว ))");
    }
    else if(TogNewbie == 1){
        TogNewbie = 0;
        SendClientMessageToAll(0xFFECA1AA, "(( ผู้ดูแลได้เปิด Newbie แล้ว ))");
    }
    return 1;
}

CMD:togtw(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 3)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    if(TogTwitter == 0){
        TogTwitter = 1;
        SendClientMessageToAll(0x42CBFFAA, "(( ผู้ดูแลได้ปิด Twitter แล้ว ))");
    }
    else if(TogTwitter == 1){
        TogTwitter = 0;
        SendClientMessageToAll(0x42CBFFAA, "(( ผู้ดูแลได้เปิด Twitter แล้ว ))");
    }
    return 1;
}

CMD:togalert(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1){
        if(CheckToggleAlert[playerid] == 0){
            CheckToggleAlert[playerid] = 1;
            SendClientMessage(playerid, COLOR_YELLOW, ">> คุณได้ ปิด การแจ้งเตือนแอดมินเรียบร้อยแล้ว <<");
        }
        else if(CheckToggleAlert[playerid] == 1){
            CheckToggleAlert[playerid] = 0;
            SendClientMessage(playerid, COLOR_YELLOW, ">> คุณได้ เปิด การแจ้งเตือนแอดมินเรียบร้อยแล้ว <<");
        }
    }
    return 1;
}

CMD:testrecar(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 5){
        StartRespawnCar = 1;
	    TimerRespawnCar = 60;
        SendClientMessageToAll(COLOR_ORANGE, "[รียานพาหนะ]: อีก 1 นาที ระบบจะทำการรียานพาหนะภายในเซิฟเวอร์กลับจุดเดิม, หากยานพาหนะที่มีผู้ใช้อยู่จะไม่ถูกรีกลับจุดเดิม");
    }
    return 1;
}

CMD:freegetcar(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new userid, amount;
    new string[128];
    if(sscanf(params, "ud", userid, amount)) return SystemMsg(playerid, "/freegetcar [playerid] [จำนวน]");
    if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
    if(!LoggedIn[userid]) return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้ทำการล็อคอิน");
    if(amount == 0) return ErrorMsg(playerid, "ต้องกรอกจำนวนมากกว่า 0");
    PlayerData[userid][pPlayerFreeGetCar] += amount;
    format(string, sizeof(string), "ผู้ดูแล %s ได้ให้ใบกู้ยานพาหนะฟรี กับ \"%s(%d)\" จำนวน %d ใบ", PlayerData[playerid][pAdminName], ReturnRoleplayName(userid), userid, amount);
    SendAdminsMessage(1, COLOR_YELLOW, string);
    SendClientMessageEx(userid, COLOR_YELLOW, "| คุณได้รับใบกู้ยานพาหนะฟรีจำนวน %d ใบจาก ผู้ดูแล %s", amount, PlayerData[playerid][pAdminName]);
    return 1;
}

CMD:checkfreegetcar(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new userid;
    if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/checkfreegetcar [playerid]");
    if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
    if(!LoggedIn[userid]) return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้ทำการล็อคอิน");
    SendClientMessageEx(playerid, COLOR_ORANGE, "| ใบกู้ยานพาหนะฟรีของ %s(%d) เหลืออยู่ %d ใบ", ReturnRoleplayName(userid), userid, PlayerData[userid][pPlayerFreeGetCar]);
    return 1;
}

CMD:restart(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new second, string[64];
    if(!ServerRestart){
        if(sscanf(params, "d", second)) return SystemMsg(playerid, "/restart [seconds]");
        if(second <= 0) return ErrorMsg(playerid, "คุณต้องกรอกมากกว่า 0");
        LoadRestartServerText();
        ServerRestart = true;
        TextDrawShowForAll(RestartServer);
        ServerSeconds = second;
        if(second / 60 < 1){
            SendClientMessageToAllEx(COLOR_SERVER, "| [Restart Server]: {FFBD00}เซิฟเวอร์ได้ถูกทำการตั้งเวลารีในอีก %d วินาที!", second);
            format(string, sizeof string, "Restart Server In: %d seconds", ServerSeconds);
        }   
        else if(second / 60 >= 1 && second / 60 <= 60){
            SendClientMessageToAllEx(COLOR_SERVER, "| [Restart Server]: {FFBD00}เซิฟเวอร์ได้ถูกทำการตั้งเวลารีในอีก %d นาที!", second / 60);
            format(string, sizeof string, "Restart Server In: %d minutes", ServerSeconds / 60);
        }
        else if((second / 60) / 60 >= 1){
            SendClientMessageToAllEx(COLOR_SERVER, "| [Restart Server]: {FFBD00}เซิฟเวอร์ได้ถูกทำการตั้งเวลารีในอีก %d ชั่วโมง!", (second / 60) / 60);
            format(string, sizeof string, "Restart Server In: %d hours", (ServerSeconds / 60) / 60);
        }
        TextDrawSetString(RestartServer, string);
    }
    else{
        ServerRestart = false;
        ServerSeconds = 0;
        SendClientMessageToAll(COLOR_SERVER, "| [Restart Server]: {FFBD00}การรีเซิฟเวอร์ได้ถูกยกเลิก!");
        TextDrawHideForAll(RestartServer);
        TextDrawDestroy(RestartServer);
    }
    return 1;
}

task UpdateRestartServer[1000](){
    if(ServerRestart && ServerSeconds > 0){
        new string[128];
        ServerSeconds--;
        //printf("%d", ServerSeconds);
        if(ServerSeconds / 60 < 1){
            format(string, sizeof string, "Restart Server In: %d seconds", ServerSeconds);
        }
        else if(ServerSeconds / 60 >= 1 && ServerSeconds / 60 <= 60){
            format(string, sizeof string, "Restart Server In: %d minutes", ServerSeconds / 60);
        }
        else if((ServerSeconds / 60) / 60 >= 1){
            format(string, sizeof string, "Restart Server In: %d hours", (ServerSeconds / 60) / 60);
        }
        TextDrawSetString(RestartServer, string);
    }
    else if(ServerRestart && ServerSeconds <= 0){
        ServerRestart = false;
        ServerSeconds = 0;
        TextDrawHideForAll(RestartServer);
        TextDrawDestroy(RestartServer);
        foreach(new i : Player){
            if(PlayerData[i][pAdmin] != 0) continue;
            Kick(i);
        }
        ServerData[ServerLocked] = true;
        SendRconCommand("password 0");
        new str[64];
        format(str, sizeof(str), "password %s", ServerData[ServerPassword]);
        SendRconCommand(str);
    }
}

alias:recar("รีรถ")
CMD:recar(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if (PlayerData[playerid][pAdmin] < 5)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

    new count;

    for (new i = 1; i != MAX_VEHICLES; i ++){
        if(i == INVALID_VEHICLE_ID) continue;
        if(i == BusRed) continue;
        if(i == BusYellow) continue;
        if(!IsVehicleEmpty(i)){
            RespawnVehicle(i);
            count++;
        }
    }
    if (!count)
        return ErrorMsg(playerid, "ไม่มียานพาหนะคันไหนถูกส่งกลับจุดเกิด");

    new string[128];

    SendClientMessageEx(playerid, -1, "คุณได้ส่งยานพาหนะที่ไม่มีใครอยู่กลับจุดเกิดจำนวน %d คัน", count);
    format(string, sizeof(string), "[Respawncars]: ผู้ดูแล ได้ทำการรีรถของเซิฟเวอร์แล้ว");
    SendClientMessageToAll(-1, string);
    return 1;
}

alias:addpc("ให้ไวริสคอม")
CMD:addpc(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    new string[128];
    if (PlayerData[playerid][pAdmin] < 1337)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

    if (isnull(params) || strlen(params) > 64)
        return SystemMsg(playerid, "/addpc [ชื่อตัวละคร]");

    AddWhitelistPC(params);

    SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ให้ Whitelist สำหรับคอมพิวเตอร์ กับ \"%s\" สำเร็จ", params);
    format(string, sizeof(string), "ผู้ดูแล %s ได้ให้ไวริส สำหรับคอมพิวเตอร์ กับ \"%s\"", ReturnRoleplayName(playerid), params);
    SendAdminsMessage(1, COLOR_YELLOW, string);
    return 1;
}

CMD:reports(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] >= 1)
	{
		new
			tool[16];

		if(sscanf(params, "s[16] ", tool))
		{
		    SendClientMessage(playerid, COLOR_GREY, "/reports [tool]");
		    SendClientMessage(playerid, COLOR_GREY, "Tools: List(l), Accept(a), Disregard(d), Status, Clear");
		}
		else
		{
		    if(strcmp(tool, "list", true) == 0)
			{
				SendClientMessage(playerid, COLOR_WHITE, "------------------------------------------------------------------------------------");

		        new
					string[128],
					reportCount;

		        foreach(new i: Player) if(LoggedIn[i]){
		            if(PlayerData[i][pReport] >= 1)
					{
		                format(string, sizeof(string), "[ACTIVE] %s [%d] รายงานว่า: %s", ReturnRoleplayName(i), i, PlayerData[i][pReportMessage]);
		                SendClientMessage(playerid, 0xFF0066AA , string);
		                reportCount++;
		            }
		        }

		        format(string, sizeof(string), "ACTIVE REPORTS: %d (ใช้ /reports ยืนยัน)", reportCount);
		        SendClientMessage(playerid, -1 , string);

				SendClientMessage(playerid, COLOR_WHITE, "------------------------------------------------------------------------------------");
		    }
		    else if(strcmp(tool, "l", true) == 0){
				SendClientMessage(playerid, COLOR_WHITE, "------------------------------------------------------------------------------------");

		        new
					string[128],
					reportCount;

		        foreach(new i: Player) if(LoggedIn[i]){
		            if(PlayerData[i][pReport] >= 1)
					{
		                format(string, sizeof(string), "[ACTIVE] %s [%d] รายงานว่า: %s", ReturnRoleplayName(i), i, PlayerData[i][pReportMessage]);
		                SendClientMessage(playerid, 0xFF0066AA , string);
		                reportCount++;
		            }
		        }

		        format(string, sizeof(string), "ACTIVE REPORTS: %d (ใช้ /reports ยืนยัน)", reportCount);
		        SendClientMessage(playerid, -1 , string);

				SendClientMessage(playerid, COLOR_WHITE, "------------------------------------------------------------------------------------");
		    }
            else if(strcmp(tool, "clear", true) == 0){
                new string[128];
                foreach(new i : Player) if(LoggedIn[i]){
                    if(PlayerData[i][pReport] >= 1){
                        PlayerData[i][pReport] = 0;
                    }
                }
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการล้าง Report ทั้งหมดแล้ว", PlayerData[playerid][pAdminName]);
                SendAdminsMessage(1, 0xFF0066AA, string);
            }
		    else if(strcmp(tool, "accept", true) == 0)
		    {
		        new
					userID;

		        if(sscanf(params, "s[16]u", tool, userID))
				{
		            SendClientMessage(playerid, COLOR_GREY, "/reports accept [playerid]");
		        }
		        else
				{
		            if(!IsPlayerConnected(userID))
					{
		                SendClientMessage(playerid, COLOR_GREY, "The specified player ID is either not connected or has not authenticated.");
		            }
		            else
		            {
		                if(PlayerData[userID][pReport] >= 1)
						{
		                    new

								string[128];

		                    format(string, sizeof(string), "คุณยืนยันรายงานของ %s (%s)", ReturnRoleplayName(userID), PlayerData[userID][pReportMessage]);
		                    SendClientMessage(playerid, COLOR_WHITE, string);

		                    PlayerData[userID][pReport] = 0;
		                    format(PlayerData[userID][pReportMessage], 64, "(null)");

                            format(string, sizeof(string), "ขอบคุณสำหรับรายงาน! ผู้ดูแล ได้ยืนยันรายงานของคุณแล้ว");
							SendClientMessage(userID, 0xFF0066AA , string);

		                    SetPVarInt(playerid, "aR", 1);
		                    SetPVarInt(playerid, "aRf", userID);

                            format(string, sizeof(string), "ผู้ดูแล %s ได้ยืนยันรายงานของ %s เรียบร้อยแล้ว!", PlayerData[playerid][pAdminName], ReturnRoleplayName(userID));
		                    SendAdminsMessage(1, 0xFF0066AA, string);

                            new caption[128];
                            format(caption, sizeof(caption), "ผู้เล่น %s", ReturnRoleplayName(userID));
                            format(string, sizeof(string), "- วาปไปหา\n- ดึงมาหา\n- ส่อง\n- ส่งไปตลาดกลาง");
                            AdminManagePlayerID[playerid] = userID;
                            Dialog_ShowEasy(playerid, AdminManagePlayer, DIALOG_STYLE_LIST, caption, string, "เลือก", "ยกเลิก");
		                }
		                else {
		                    SendClientMessage(playerid, COLOR_GREY, "That player doesn't have an active report.");
		                }
		            }
		        }
		    }
		    else if(strcmp(tool, "a", true) == 0)
		    {
		        new
					userID;

		        if(sscanf(params, "s[16]u", tool, userID))
				{
		            SendClientMessage(playerid, COLOR_GREY, "/reports accept [playerid]");
		        }
		        else
				{
		            if(!IsPlayerConnected(userID))
					{
		                SendClientMessage(playerid, COLOR_GREY, "The specified player ID is either not connected or has not authenticated.");
		            }
		            else
		            {
		                if(PlayerData[userID][pReport] >= 1)
						{
		                    new

								string[128];

		                    format(string, sizeof(string), "คุณยืนยันรายงานของ %s (%s)", ReturnRoleplayName(userID), PlayerData[userID][pReportMessage]);
		                    SendClientMessage(playerid, COLOR_WHITE, string);

		                    PlayerData[userID][pReport] = 0;
		                    format(PlayerData[userID][pReportMessage], 64, "(null)");

                            format(string, sizeof(string), "ขอบคุณสำหรับรายงาน! ผู้ดูแล ได้ยืนยันรายงานของคุณแล้ว");
							SendClientMessage(userID, 0xFF0066AA , string);

		                    SetPVarInt(playerid, "aR", 1);
		                    SetPVarInt(playerid, "aRf", userID);

                            format(string, sizeof(string), "%s ได้ยืนยันรายงานของ %s เรียบร้อยแล้ว!", PlayerData[playerid][pAdminName], ReturnRoleplayName(userID));
		                    SendAdminsMessage(1, 0xFF0066AA, string);

                            new caption[128];
                            format(caption, sizeof(caption), "ผู้เล่น %s", ReturnRoleplayName(userID));
                            format(string, sizeof(string), "- วาปไปหา\n- ดึงมาหา\n- ส่อง\n- ส่งไปตลาดกลาง");
                            AdminManagePlayerID[playerid] = userID;
                            Dialog_ShowEasy(playerid, AdminManagePlayer, DIALOG_STYLE_LIST, caption, string, "เลือก", "ยกเลิก");
		                }
		                else {
		                    SendClientMessage(playerid, COLOR_GREY, "That player doesn't have an active report.");
		                }
		            }
		        }
		    }
		    else if(strcmp(tool, "disregard", true) == 0)
			{
		        new
					userID,
					string[128];

		        if(sscanf(params, "s[16]u", tool, userID))
				{
		            SendClientMessage(playerid, COLOR_GREY, "/reports disregard [playerid]");
		        }
		        else
				{
		            if(!IsPlayerConnected(userID)) {
		                SendClientMessage(playerid, COLOR_GREY, "The specified player ID is either not connected or has not authenticated.");
		            }
		            else
					{
		                if(PlayerData[userID][pReport] != 0)
						{
		                    PlayerData[userID][pReport] = 0;
		                    format(PlayerData[userID][pReportMessage], 64, "(null)");


		                    format(string, sizeof(string), "ผู้ดูแล ได้ปฏิเสธรายงานของคุณ");
							SendClientMessage(userID, 0xFF0066AA , string);

		                    format(string, sizeof(string), "คุณปฏิเสธรายงานของ %s", ReturnRoleplayName(userID));
		                    SendClientMessage(playerid, 0xFF0066AA , string);

                            format(string, sizeof(string), "ผู้ดูแล %s ได้ปฏิเสธรายงานของ %s เรียบร้อยแล้ว!", PlayerData[playerid][pAdminName], ReturnRoleplayName(userID));
		                    SendAdminsMessage(1, 0xFF0066AA, string);
		                }
		                else
						{
		                    SendClientMessage(playerid, COLOR_GREY, "That player doesn't have an active report.");
		                }
		            }
		        }
		    }
		    else if(strcmp(tool, "d", true) == 0)
			{
		        new
					userID,
					string[128];

		        if(sscanf(params, "s[16]u", tool, userID))
				{
		            SendClientMessage(playerid, COLOR_GREY, "/reports disregard [playerid]");
		        }
		        else
				{
		            if(!IsPlayerConnected(userID)) {
		                SendClientMessage(playerid, COLOR_GREY, "The specified player ID is either not connected or has not authenticated.");
		            }
		            else
					{
		                if(PlayerData[userID][pReport] != 0)
						{
		                    PlayerData[userID][pReport] = 0;
		                    format(PlayerData[userID][pReportMessage], 64, "(null)");

                            format(string, sizeof(string), "ผู้ดูแล ได้ปฏิเสธรายงานของคุณ");
							SendClientMessage(userID, 0xFF0066AA , string);

		                    format(string, sizeof(string), "คุณปฏิเสธรายงานของ %s", ReturnRoleplayName(userID));
		                    SendClientMessage(playerid, 0xFF0066AA , string);

                            format(string, sizeof(string), "%s ได้ปฏิเสธรายงานของ %s เรียบร้อยแล้ว!", ReturnRoleplayName(playerid), ReturnRoleplayName(userID));
		                    SendAdminsMessage(1, 0xFF0066AA, string);
		                }
		                else
						{
		                    SendClientMessage(playerid, COLOR_GREY, "That player doesn't have an active report.");
		                }
		            }
		        }
		    }
		    else if(strcmp(tool, "status", true) == 0) {
		        if(PlayerData[playerid][pAdmin] >= 1300) {
			        if(systemVariables[reportSystem] == 0) {
			            systemVariables[reportSystem] = 1;
			            SendClientMessageToAll(COLOR_YELLOW, "ระบบ Report ถูกยกเลิก");
			        }
			        else {
			            systemVariables[reportSystem] = 0;
			            SendClientMessageToAll(COLOR_YELLOW, "ระบบ Report ถูกเปิดใช้อีกครั้ง");
			        }
		        }
		        else {
					return SendClientMessage(playerid, COLOR_GREY, "You need to be a Head Administrator or above to use this command.");
				}
 		    }
		    else {
			    SendClientMessage(playerid, COLOR_GREY, "/reports [tool]");
			    SendClientMessage(playerid, COLOR_GREY, "TOOLS: List, Accept, Disregard, Status");
		    }
		}
	}

	return 1;
}

CMD:apm(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1){
        new userid, message[80];

        if(sscanf(params, "uS[80]", userid, message))
            return SystemMsg(playerid, "/apm [playerid] [message]");

        if(isnull(message))
            return SystemMsg(playerid, "/apm [playerid] [message]");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
        if(LoggedIn[userid]){
            SendClientMessageEx(userid, COLOR_YELLOW, "(( ข้อความจากผู้ดูแลระบบถึงคุณ: %s ))", message);
            SendClientMessageEx(playerid, COLOR_YELLOW, "(( คุณส่งไปหา %s(%d) : %s ))", ReturnRoleplayName(userid), userid, message);
        }
    }
    return 1;
}

CMD:freeze(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1300)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    new userid;
    if(sscanf(params, "u", userid)) 
        return SystemMsg(playerid, "/freeze [ID/Name]");

    if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

    TogglePlayerControllable(userid, 0);
    return 1;
}

CMD:unfreeze(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1300)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    new userid;
    if(sscanf(params, "u", userid)) 
        return SystemMsg(playerid, "/unfreeze [ID/Name]");

    if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

    TogglePlayerControllable(userid, 1);
    return 1;
}

CMD:listcars(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    new
	    Float:fX,
	    Float:fY,
	    Float:fZ,
		targetid,
		count = 1,
        status[64],
        lockstats[64],
        tracker[64];

    if (PlayerData[playerid][pAdmin] >= 3){

        if (sscanf(params, "u", targetid))
            return SystemMsg(playerid, "/listcars [playerid]");

        if (targetid == INVALID_PLAYER_ID)
            return ErrorMsg(playerid, "ผู้เล่นที่ระบุไม่ถูกต้อง");

        SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
        SendClientMessageEx(playerid, COLOR_YELLOW, "ยานพาหนะจดทะเบียนโดย %s (ID: %d):", ReturnRoleplayName(targetid), targetid);

        for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
            if (Car_IsOwner(targetid, i)) {
                GetVehiclePos(CarData[i][carVehicle], fX, fY, fZ);

                if(CarData[i][carLocked] == 0)
                    lockstats = "ปลดล็อค";
                else
                    lockstats = "ล็อค";

                if(CarData[i][carDestroyed] == 0){
                    if(CarData[i][carInsideGarage] == 1)
                        status = "อยู่ในการาจ";
                    else
                        status = "ไม่ได้อยู่ในการาจ";

                    if(CarData[i][carGPS] == 1) tracker = "มี";
                    else tracker = "ไม่มี";

                    SendClientMessageEx(playerid, COLOR_WHITE, "กุญแจยานพาหนะ: [%d] ช่อง #%d: ยานพาหนะ:[%s] สถานะล็อค:[%s] สถานที่รถ:[%s] | [%s]", CarData[i][carVehicle],count,ReturnVehicleModelName(CarData[i][carModel]),lockstats,GetLocation(fX, fY, fZ), status);
                    SendClientMessageEx(playerid, COLOR_WHITE, "ป้ายทะเบียน:[%s] ระบบติดตาม:[%s]", CarData[i][carPlate], tracker);
                }
                else if(CarData[i][carDestroyed] == 1){
                    if(CarData[i][carVehicle] == INVALID_VEHICLE_ID){
                        SendClientMessageEx(playerid, COLOR_WHITE, "[ถูกทำลาย] กุญแจยานพาหนะ: [#] ช่อง #%d: ยานพาหนะ:[%s] (สามารถไปกู้คืนได้โดยพิมพ์ '/gps > ค้นหา จุดกู้คืนยานพาหนะ)",count,ReturnVehicleModelName(CarData[i][carModel]));
                        SendClientMessageEx(playerid, COLOR_WHITE, "ป้ายทะเบียน:[%s] ระบบติดตาม:[%s]", CarData[i][carPlate], tracker);
                    }
                    else{
                        SendClientMessageEx(playerid, COLOR_WHITE, "[ถูกทำลาย] กุญแจยานพาหนะ: [%d] ช่อง #%d: ยานพาหนะ:[%s] (สามารถไปกู้คืนได้โดยพิมพ์ '/gps > ค้นหา จุดกู้คืนยานพาหนะ)",CarData[i][carVehicle],count,ReturnVehicleModelName(CarData[i][carModel]));
                        SendClientMessageEx(playerid, COLOR_WHITE, "ป้ายทะเบียน:[%s] ระบบติดตาม:[%s]", CarData[i][carPlate], tracker);
                    }
                }
                count++;
            }
        }

        if (count < 2)
            SendClientMessage(playerid, COLOR_WHITE, "ผู้เล่นนั้นไม่ได้เป็นเจ้าของยานพาหนะใด ๆ");

        SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
    }
	return 1;
}

CMD:removeweapon(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        new userid, weaponid;
        if(sscanf(params, "ud", userid, weaponid))
            return SystemMsg(playerid, "/removeweapon [playerid] [weaponid]");

        if (weaponid <= 0 || weaponid > 46 || (weaponid >= 19 && weaponid <= 21))
		    return SendClientMessage(playerid,-1, "คุณระบุอาวุธไม่ถูกต้อง");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

        if(userid != INVALID_PLAYER_ID && LoggedIn[userid]){
            GivePlayerWeapon(userid, weaponid, 0);

            if(weaponid == 34 || weaponid == 33 || weaponid == 32 || weaponid == 31 || weaponid == 30 || weaponid == 29 || weaponid == 28 || weaponid == 27 || weaponid == 26 || weaponid == 25)
            {
                PlayerData[userid][pMyWeapon][0] = 0;
                PlayerData[userid][pMyAmmo][0] = 0;
            }
            
            if(weaponid == 22 || weaponid == 23 || weaponid == 24)
            {
                PlayerData[userid][pMyWeapon][1] = 0;
                PlayerData[userid][pMyAmmo][1] = 0;
            }
            
            if(weaponid == 1 || weaponid == 2 || weaponid == 3 || weaponid == 4 || weaponid == 5 || weaponid == 6 || weaponid == 7 || weaponid == 8 || weaponid == 9 || weaponid == 10 || weaponid == 11 || weaponid == 12 || weaponid == 13 || weaponid == 14 || weaponid == 15)
            {
                PlayerData[userid][pMyWeapon][2] = 0;
                PlayerData[userid][pMyAmmo][2] = 0;
            }
        }
    }
    return 1;
}

CMD:giveguntemp(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        new userid, weaponid, ammo;
        if(sscanf(params, "udI(1)", userid, weaponid, ammo))
            return SystemMsg(playerid, "/giveguntemp [playerid] [weaponid] [ammo]");

        if (weaponid <= 0 || weaponid > 46 || (weaponid >= 19 && weaponid <= 21))
		    return SendClientMessage(playerid,-1, "คุณระบุอาวุธไม่ถูกต้อง");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

        if(userid != INVALID_PLAYER_ID && LoggedIn[userid]){
            GivePlayerWeapon(userid, weaponid, ammo);

            if(weaponid == 34 || weaponid == 33 || weaponid == 32 || weaponid == 31 || weaponid == 30 || weaponid == 29 || weaponid == 28 || weaponid == 27 || weaponid == 26 || weaponid == 25)
            {
                if(PlayerData[userid][pMyWeapon][0] != 0) return ErrorMsg(playerid, "ผู้เล่นนั้นมีอาวุธอยู่แล้ว");
                GivePlayerWeapon(userid, weaponid, ammo);
            }
            
            if(weaponid == 22 || weaponid == 23 || weaponid == 24)
            {
                if(PlayerData[userid][pMyWeapon][1] != 0) return ErrorMsg(playerid, "ผู้เล่นนั้นมีอาวุธอยู่แล้ว");
                GivePlayerWeapon(userid, weaponid, ammo);
            }
            
            if(weaponid == 1 || weaponid == 2 || weaponid == 3 || weaponid == 4 || weaponid == 5 || weaponid == 6 || weaponid == 7 || weaponid == 8 || weaponid == 9 || weaponid == 10 || weaponid == 11 || weaponid == 12 || weaponid == 13 || weaponid == 14 || weaponid == 15)
            {
                if(PlayerData[userid][pMyWeapon][2] != 0) return ErrorMsg(playerid, "ผู้เล่นนั้นมีอาวุธอยู่แล้ว");
                GivePlayerWeapon(userid, weaponid, ammo);
            }
        }
    }
    return 1;
}

CMD:givegun(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        new userid, weaponid, ammo;
        if(sscanf(params, "udI(1)", userid, weaponid, ammo))
            return SystemMsg(playerid, "/givegun [playerid] [weaponid] [ammo]");

        if (weaponid <= 0 || weaponid > 46 || (weaponid >= 19 && weaponid <= 21))
		    return SendClientMessage(playerid,-1, "คุณระบุอาวุธไม่ถูกต้อง");

        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

        if(userid != INVALID_PLAYER_ID && LoggedIn[userid]){
            GivePlayerWeapon(userid, weaponid, ammo);

            if(weaponid == 34 || weaponid == 33 || weaponid == 32 || weaponid == 31 || weaponid == 30 || weaponid == 29 || weaponid == 28 || weaponid == 27 || weaponid == 26 || weaponid == 25)
            {
                PlayerData[userid][pMyWeapon][0] = weaponid;
                PlayerData[userid][pMyAmmo][0] = ammo;
            }
            
            if(weaponid == 22 || weaponid == 23 || weaponid == 24)
            {
                PlayerData[userid][pMyWeapon][1] = weaponid;
                PlayerData[userid][pMyAmmo][1] = ammo;
            }
            
            if(weaponid == 1 || weaponid == 2 || weaponid == 3 || weaponid == 4 || weaponid == 5 || weaponid == 6 || weaponid == 7 || weaponid == 8 || weaponid == 9 || weaponid == 10 || weaponid == 11 || weaponid == 12 || weaponid == 13 || weaponid == 14 || weaponid == 15)
            {
                PlayerData[userid][pMyWeapon][2] = weaponid;
                PlayerData[userid][pMyAmmo][2] = 1;
            }
        }
    }
    return 1;
}

CMD:checkafk(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1){
        new count = 0;
        foreach(new x : Player){
            if(IsAFK{x} && LoggedIn[x]){
                count++;
                SendClientMessageEx(playerid, COLOR_ORANGE, "%s(%d) ได้ทำการ AFK", ReturnRoleplayName(x), x);
            }
        }

        if(count == 0){
            SendClientMessage(playerid, COLOR_ORANGE, "- ไม่มีผู้เล่น AFK อยู่เลย -");
        }
    }
    return 1;
}

CMD:gotobank(playerid, params[]){
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pAdmin] < 1) return 1;
        SetPlayerVirtualWorld(playerid, 1);
	    SetPlayerInterior(playerid, 1);
		SetPlayerPos(playerid, 1388.7264,-26.6971,1000.8729);
    }
    return 1;
}

CMD:int(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(IsPlayerConnected(playerid))
    {
        if (PlayerData[playerid][pAdmin] >= 5)
        {
            new x_nr[32];
            if(sscanf(params, "s[32]", x_nr))
                return SendClientMessage(playerid, COLOR_WHITE, "การใช้: /int [1-119]");

            if(strcmp(x_nr,"1",true) == 0)
            {
                SetPlayerPos(playerid,-25.884498,-185.868988,1003.546875);
                SetPlayerInterior(playerid,17);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ 24/7 1");
            }
            else if(strcmp(x_nr,"2",true) == 0)
            {
                SetPlayerPos(playerid,6.091179,-29.271898,1003.549438);
                SetPlayerInterior(playerid,10);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ 24/7 2");
            }
            else if(strcmp(x_nr,"3",true) == 0)
            {
                SetPlayerPos(playerid,-30.946699,-89.609596,1003.546875);
                SetPlayerInterior(playerid,18);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ 24/7 3");
            }
            else if(strcmp(x_nr,"4",true) == 0)
            {
                SetPlayerPos(playerid,-25.132598,-139.066986,1003.546875);
                SetPlayerInterior(playerid,16);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ 24/7 4");
            }
            else if(strcmp(x_nr,"5",true) == 0)
            {
                SetPlayerPos(playerid,-27.312299,-29.277599,1003.557250);
                SetPlayerInterior(playerid,4);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ 24/7 5");
            }
            else if(strcmp(x_nr,"6",true) == 0)
            {
                SetPlayerPos(playerid,-26.691598,-55.714897,1003.546875);
                SetPlayerInterior(playerid,6);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ 24/7 6");
            }
            else if(strcmp(x_nr,"7",true) == 0)
            {
                SetPlayerPos(playerid,-1827.147338,7.207417,1061.143554);
                SetPlayerInterior(playerid,14);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Airport ticket desk");
            }
            else if(strcmp(x_nr,"8",true) == 0)
            {
                SetPlayerPos(playerid,-1861.936889,54.908092,1061.143554);
                SetPlayerInterior(playerid,14);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Airport baggage reclaim");
            }
            else if(strcmp(x_nr,"9",true) == 0)
            {
                SetPlayerPos(playerid,1.808619,32.384357,1199.593750);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Shamal");
            }
            else if(strcmp(x_nr,"10",true) == 0)
            {
                SetPlayerPos(playerid,315.745086,984.969299,1958.919067);
                SetPlayerInterior(playerid,9);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Andromada");
            }
            else if(strcmp(x_nr,"11",true) == 0)
            {
                SetPlayerPos(playerid,286.148986,-40.644397,1001.515625);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Ammunation 1");
            }
            else if(strcmp(x_nr,"12",true) == 0)
            {
                SetPlayerPos(playerid,286.800994,-82.547599,1001.515625);
                SetPlayerInterior(playerid,4);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Ammunation 2");
            }
            else if(strcmp(x_nr,"13",true) == 0)
            {
                SetPlayerPos(playerid,296.919982,-108.071998,1001.515625);
                SetPlayerInterior(playerid,6);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Ammunation 3");
            }
            else if(strcmp(x_nr,"14",true) == 0)
            {
                SetPlayerPos(playerid,314.820983,-141.431991,999.601562);
                SetPlayerInterior(playerid,7);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Ammunation 4");
            }
            else if(strcmp(x_nr,"15",true) == 0)
            {
                SetPlayerPos(playerid,316.524993,-167.706985,999.593750);
                SetPlayerInterior(playerid,6);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Ammunation 5");
            }
            else if(strcmp(x_nr,"16",true) == 0)
            {
                SetPlayerPos(playerid,302.292877,-143.139099,1004.062500);
                SetPlayerInterior(playerid,7);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Ammunation booths");
            }
            else if(strcmp(x_nr,"17",true) == 0)
            {
                SetPlayerPos(playerid,298.507934,-141.647048,1004.054748);
                SetPlayerInterior(playerid,7);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Ammunation range");
            }
            else if(strcmp(x_nr,"18",true) == 0)
            {
                SetPlayerPos(playerid,1038.531372,0.111030,1001.284484);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Blastin fools hallway");
            }
            else if(strcmp(x_nr,"19",true) == 0)
            {
                SetPlayerPos(playerid,444.646911,508.239044,1001.419494);
                SetPlayerInterior(playerid,12);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Budget inn motel room");
            }
            else if(strcmp(x_nr,"20",true) == 0)
            {
                SetPlayerPos(playerid,2215.454833,-1147.475585,1025.796875);
                SetPlayerInterior(playerid,15);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Jefferson motel");
            }
            else if(strcmp(x_nr,"21",true) == 0)
            {
                SetPlayerPos(playerid,833.269775,10.588416,1004.179687);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Off track betting shop");
            }
            else if(strcmp(x_nr,"22",true) == 0)
            {
                SetPlayerPos(playerid,-103.559165,-24.225606,1000.718750);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Sex shop");
            }
            else if(strcmp(x_nr,"23",true) == 0)
            {
                SetPlayerPos(playerid,963.418762,2108.292480,1011.030273);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Meat factory");
            }
            else if(strcmp(x_nr,"24",true) == 0)
            {
                SetPlayerPos(playerid,-2240.468505,137.060440,1035.414062);
                SetPlayerInterior(playerid,6);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Zero's RC shop");
            }
            else if(strcmp(x_nr,"25",true) == 0)
            {
                SetPlayerPos(playerid,663.836242,-575.605407,16.343263);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Dillimore gas station");
            }
            else if(strcmp(x_nr,"26",true) == 0)
            {
                SetPlayerPos(playerid,2169.461181,1618.798339,999.976562);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Catigula's basement");
            }
            else if(strcmp(x_nr,"27",true) == 0)
            {
                SetPlayerPos(playerid,1889.953369,1017.438293,31.882812);
                SetPlayerInterior(playerid,10);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ FDC Janitors room");
            }
            else if(strcmp(x_nr,"28",true) == 0)
            {
                SetPlayerPos(playerid,-2159.122802,641.517517,1052.381713);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Woozie's office");
            }
            else if(strcmp(x_nr,"29",true) == 0)
            {
                SetPlayerPos(playerid,207.737991,-109.019996,1005.132812);
                SetPlayerInterior(playerid,15);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Binco");
            }
            else if(strcmp(x_nr,"30",true) == 0)
            {
                SetPlayerPos(playerid,204.332992,-166.694992,1000.523437);
                SetPlayerInterior(playerid,14);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Didier sachs");
            }
            else if(strcmp(x_nr,"31",true) == 0)
            {
                SetPlayerPos(playerid,207.054992,-138.804992,1003.507812);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Prolaps");
            }
            else if(strcmp(x_nr,"32",true) == 0)
            {
                SetPlayerPos(playerid,203.777999,-48.492397,1001.804687);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Suburban");
            }
            else if(strcmp(x_nr,"33",true) == 0)
            {
                SetPlayerPos(playerid,226.293991,-7.431529,1002.210937);
                SetPlayerInterior(playerid,5);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Victim");
            }
            else if(strcmp(x_nr,"34",true) == 0)
            {
                SetPlayerPos(playerid,161.391006,-93.159156,1001.804687);
                SetPlayerInterior(playerid,18);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Zip");
            }
            else if(strcmp(x_nr,"35",true) == 0)
            {
                SetPlayerPos(playerid,493.390991,-22.722799,1000.679687);
                SetPlayerInterior(playerid,17);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Club");
            }
            else if(strcmp(x_nr,"36",true) == 0)
            {
                SetPlayerPos(playerid,501.980987,-69.150199,998.757812);
                SetPlayerInterior(playerid,11);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Bar");
            }
            else if(strcmp(x_nr,"37",true) == 0)
            {
                SetPlayerPos(playerid,-227.027999,1401.229980,27.765625);
                SetPlayerInterior(playerid,18);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Lil' probe inn");
            }
            else if(strcmp(x_nr,"38",true) == 0)
            {
                SetPlayerPos(playerid,457.304748,-88.428497,999.554687);
                SetPlayerInterior(playerid,4);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Jay's diner");
            }
            else if(strcmp(x_nr,"39",true) == 0)
            {
                SetPlayerPos(playerid,454.973937,-110.104995,1000.077209);
                SetPlayerInterior(playerid,5);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Gant bridge diner");
            }
            else if(strcmp(x_nr,"40",true) == 0)
            {
                SetPlayerPos(playerid,435.271331,-80.958938,999.554687);
                SetPlayerInterior(playerid,6);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Secret valley diner");
            }
            else if(strcmp(x_nr,"41",true) == 0)
            {
                SetPlayerPos(playerid,452.489990,-18.179698,1001.132812);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ World of coq");
            }
            else if(strcmp(x_nr,"42",true) == 0)
            {
                SetPlayerPos(playerid,681.557861,-455.680053,-25.609874);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Welcome pump");
            }
            else if(strcmp(x_nr,"43",true) == 0)
            {
                SetPlayerPos(playerid,375.962463,-65.816848,1001.507812);
                SetPlayerInterior(playerid,10);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Burger shot");
            }
            else if(strcmp(x_nr,"44",true) == 0)
            {
                SetPlayerPos(playerid,369.579528,-4.487294,1001.858886);
                SetPlayerInterior(playerid,9);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Cluckin' bell");
            }
            else if(strcmp(x_nr,"45",true) == 0)
            {
                SetPlayerPos(playerid,373.825653,-117.270904,1001.499511);
                SetPlayerInterior(playerid,5);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Well stacked pizza");
            }
            else if(strcmp(x_nr,"46",true) == 0)
            {
                SetPlayerPos(playerid,381.169189,-188.803024,1000.632812);
                SetPlayerInterior(playerid,17);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Rusty browns donuts");
            }
            else if(strcmp(x_nr,"47",true) == 0)
            {
                SetPlayerPos(playerid,244.411987,305.032989,999.148437);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Denise room");
            }
            else if(strcmp(x_nr,"48",true) == 0)
            {
                SetPlayerPos(playerid,271.884979,306.631988,999.148437);
                SetPlayerInterior(playerid,2);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Katie room");
            }
            else if(strcmp(x_nr,"49",true) == 0)
            {
                SetPlayerPos(playerid,291.282989,310.031982,999.14843);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Helena room");
            }
            else if(strcmp(x_nr,"50",true) == 0)
            {
                SetPlayerPos(playerid,302.180999,300.722991,999.148437);
                SetPlayerInterior(playerid,4);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Michelle room");
            }
            else if(strcmp(x_nr,"51",true) == 0)
            {
                SetPlayerPos(playerid,322.197998,302.497985,999.148437);
                SetPlayerInterior(playerid,5);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Barbara room");
            }
            else if(strcmp(x_nr,"52",true) == 0)
            {
                SetPlayerPos(playerid,346.870025,309.259033,999.155700);
                SetPlayerInterior(playerid,6);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Millie room");
            }
            else if(strcmp(x_nr,"53",true) == 0)
            {
                SetPlayerPos(playerid,-959.564392,1848.576782,9.000000);
                SetPlayerInterior(playerid,17);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Sherman dam");
            }
            else if(strcmp(x_nr,"54",true) == 0)
            {
                SetPlayerPos(playerid,384.808624,173.804992,1008.382812);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Planning dept.");
            }
            else if(strcmp(x_nr,"55",true) == 0)
            {
                SetPlayerPos(playerid,223.431976,1872.400268,13.734375);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Area 51");
            }
            else if(strcmp(x_nr,"56",true) == 0)
            {
                SetPlayerPos(playerid,772.111999,-3.898649,1000.728820);
                SetPlayerInterior(playerid,5);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ LS gym");
            }
            else if(strcmp(x_nr,"57",true) == 0)
            {
                SetPlayerPos(playerid,774.213989,-48.924297,1000.585937);
                SetPlayerInterior(playerid,6);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ SF gym");
            }
            else if(strcmp(x_nr,"58",true) == 0)
            {
                SetPlayerPos(playerid,773.579956,-77.096694,1000.655029);
                SetPlayerInterior(playerid,7);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ LV gym");
            }
            else if(strcmp(x_nr,"59",true) == 0)
            {
                SetPlayerPos(playerid,1527.229980,-11.574499,1002.097106);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ B Dup's house");
            }
            else if(strcmp(x_nr,"60",true) == 0)
            {
                SetPlayerPos(playerid,1523.509887,-47.821197,1002.130981);
                SetPlayerInterior(playerid,2);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ B Dup's crack pad");
            }
            else if(strcmp(x_nr,"61",true) == 0)
            {
                SetPlayerPos(playerid,2496.049804,-1695.238159,1014.742187);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Cj's house");
            }
            else if(strcmp(x_nr,"62",true) == 0)
            {
                SetPlayerPos(playerid,1267.663208,-781.323242,1091.906250);
                SetPlayerInterior(playerid,5);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Madd Doggs mansion");
            }
            else if(strcmp(x_nr,"63",true) == 0)
            {
                SetPlayerPos(playerid,513.882507,-11.269994,1001.565307);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Og Loc's house");
            }
            else if(strcmp(x_nr,"64",true) == 0)
            {
                SetPlayerPos(playerid,2454.717041,-1700.871582,1013.515197);
                SetPlayerInterior(playerid,2);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Ryders house");
            }
            else if(strcmp(x_nr,"65",true) == 0)
            {
                SetPlayerPos(playerid,2527.654052,-1679.388305,1015.498596);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Sweet's house");
            }
            else if(strcmp(x_nr,"66",true) == 0)
            {
                SetPlayerPos(playerid,2543.462646,-1308.379882,1026.728393);
                SetPlayerInterior(playerid,2);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Crack factory");
            }
            else if(strcmp(x_nr,"67",true) == 0)
            {
                SetPlayerPos(playerid,1212.019897,-28.663099,1000.953125);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Big spread ranch");
            }
            else if(strcmp(x_nr,"68",true) == 0)
            {
                SetPlayerPos(playerid,761.412963,1440.191650,1102.703125);
                SetPlayerInterior(playerid,6);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Fanny batters");
            }
            else if(strcmp(x_nr,"69",true) == 0)
            {
                SetPlayerPos(playerid,1204.809936,-11.586799,1000.921875);
                SetPlayerInterior(playerid,2);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Strip club");
            }
            else if(strcmp(x_nr,"70",true) == 0)
            {
                SetPlayerPos(playerid,1204.809936,13.897239,1000.921875);
                SetPlayerInterior(playerid,2);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Strip club private room");
            }
            else if(strcmp(x_nr,"71",true) == 0)
            {
                SetPlayerPos(playerid,942.171997,-16.542755,1000.929687);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Unnamed brothel");
            }
            else if(strcmp(x_nr,"72",true) == 0)
            {
                SetPlayerPos(playerid,964.106994,-53.205497,1001.124572);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Tiger skin brothel");
            }
            else if(strcmp(x_nr,"73",true) == 0)
            {
                SetPlayerPos(playerid,-2640.762939,1406.682006,906.460937);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Pleasure domes");
            }
            else if(strcmp(x_nr,"74",true) == 0)
            {
                SetPlayerPos(playerid,-729.276000,503.086944,1371.971801);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Liberty city outside");
            }
            else if(strcmp(x_nr,"75",true) == 0)
            {
                SetPlayerPos(playerid,-794.806396,497.738037,1376.195312);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Liberty city inside");
            }
            else if(strcmp(x_nr,"76",true) == 0)
            {
                SetPlayerPos(playerid,2350.339843,-1181.649902,1027.976562);
                SetPlayerInterior(playerid,5);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Gang house");
            }
            else if(strcmp(x_nr,"77",true) == 0)
            {
                SetPlayerPos(playerid,2807.619873,-1171.899902,1025.570312);
                SetPlayerInterior(playerid,8);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Colonel Furhberger's");
            }
            else if(strcmp(x_nr,"78",true) == 0)
            {
                SetPlayerPos(playerid,318.564971,1118.209960,1083.882812);
                SetPlayerInterior(playerid,5);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Crack den");
            }
            else if(strcmp(x_nr,"79",true) == 0)
            {
                SetPlayerPos(playerid,1412.639892,-1.787510,1000.924377);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Warehouse 1");
            }
            else if(strcmp(x_nr,"80",true) == 0)
            {
                SetPlayerPos(playerid,1302.519897,-1.787510,1001.028259);
                SetPlayerInterior(playerid,18);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Warehouse 2");
            }
            else if(strcmp(x_nr,"81",true) == 0)
            {
                SetPlayerPos(playerid,2522.000000,-1673.383911,14.866223);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Sweets garage");
            }
            else if(strcmp(x_nr,"82",true) == 0)
            {
                SetPlayerPos(playerid,-221.059051,1408.984008,27.773437);
                SetPlayerInterior(playerid,18);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Lil' probe inn toilet");
            }
            else if(strcmp(x_nr,"83",true) == 0)
            {
                SetPlayerPos(playerid,2324.419921,-1145.568359,1050.710083);
                SetPlayerInterior(playerid,12);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Unused safe house");
            }
            else if(strcmp(x_nr,"84",true) == 0)
            {
                SetPlayerPos(playerid,-975.975708,1060.983032,1345.671875);
                SetPlayerInterior(playerid,10);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ RC Battlefield");
            }
            else if(strcmp(x_nr,"85",true) == 0)
            {
                SetPlayerPos(playerid,411.625976,-21.433298,1001.804687);
                SetPlayerInterior(playerid,2);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Barber 1");
            }
            else if(strcmp(x_nr,"86",true) == 0)
            {
                SetPlayerPos(playerid,418.652984,-82.639793,1001.804687);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Barber 2");
            }
            else if(strcmp(x_nr,"87",true) == 0)
            {
                SetPlayerPos(playerid,412.021972,-52.649898,1001.898437);
                SetPlayerInterior(playerid,12);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Barber 3");
            }
            else if(strcmp(x_nr,"88",true) == 0)
            {
                SetPlayerPos(playerid,-204.439987,-26.453998,1002.273437);
                SetPlayerInterior(playerid,16);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Tatoo parlour 1");
            }
            else if(strcmp(x_nr,"89",true) == 0)
            {
                SetPlayerPos(playerid,-204.439987,-8.469599,1002.273437);
                SetPlayerInterior(playerid,17);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Tatoo parlour 2");
            }
            else if(strcmp(x_nr,"90",true) == 0)
            {
                SetPlayerPos(playerid,-204.439987,-43.652496,1002.273437);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Tatoo parlour 3");
            }
            else if(strcmp(x_nr,"91",true) == 0)
            {
                SetPlayerPos(playerid,246.783996,63.900199,1003.640625);
                SetPlayerInterior(playerid,6);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ LS police HQ");
            }
            else if(strcmp(x_nr,"92",true) == 0)
            {
                SetPlayerPos(playerid,246.375991,109.245994,1003.218750);
                SetPlayerInterior(playerid,10);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ SF police HQ");
            }
            else if(strcmp(x_nr,"93",true) == 0)
            {
                SetPlayerPos(playerid,288.745971,169.350997,1007.171875);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ LV police HQ");
            }
            else if(strcmp(x_nr,"94",true) == 0)
            {
                SetPlayerPos(playerid,-2029.798339,-106.675910,1035.171875);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Car school");
            }
            else if(strcmp(x_nr,"95",true) == 0)
            {
                SetPlayerPos(playerid,-1398.065307,-217.028900,1051.115844);
                SetPlayerInterior(playerid,7);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ 8-Track");
            }
            else if(strcmp(x_nr,"96",true) == 0)
            {
                SetPlayerPos(playerid,-1398.103515,937.631164,1036.479125);
                SetPlayerInterior(playerid,15);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Bloodbowl");
            }
            else if(strcmp(x_nr,"97",true) == 0)
            {
                SetPlayerPos(playerid,-1444.645507,-664.526000,1053.572998);
                SetPlayerInterior(playerid,4);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Dirt track");
            }
            else if(strcmp(x_nr,"98",true) == 0)
            {
                SetPlayerPos(playerid,-1465.268676,1557.868286,1052.531250);
                SetPlayerInterior(playerid,14);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Kickstart");
            }
            else if(strcmp(x_nr,"99",true) == 0)
            {
                SetPlayerPos(playerid,-1401.829956,107.051300,1032.273437);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Vice stadium");
            }
            else if(strcmp(x_nr,"100",true) == 0)
            {
                SetPlayerPos(playerid,-1790.378295,1436.949829,7.187500);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ SF Garage");
            }
            else if(strcmp(x_nr,"101",true) == 0)
            {
                SetPlayerPos(playerid,1643.839843,-1514.819580,13.566620);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ LS Garage");
            }
            else if(strcmp(x_nr,"102",true) == 0)
            {
                SetPlayerPos(playerid,-1685.636474,1035.476196,45.210937);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ SF Bomb shop");
            }
            else if(strcmp(x_nr,"103",true) == 0)
            {
                SetPlayerPos(playerid,76.632553,-301.156829,1.578125);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Blueberry warehouse");
            }
            else if(strcmp(x_nr,"104",true) == 0)
            {
                SetPlayerPos(playerid,1059.895996,2081.685791,10.820312);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ LV Warehouse 1");
            }
            else if(strcmp(x_nr,"105",true) == 0)
            {
                SetPlayerPos(playerid,1059.180175,2148.938720,10.820312);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ LV Warehouse 2 (hidden part)");
            }
            else if(strcmp(x_nr,"106",true) == 0)
            {
                SetPlayerPos(playerid,2131.507812,1600.818481,1008.359375);
                SetPlayerInterior(playerid,1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Catigula's hidden room");
            }
            else if(strcmp(x_nr,"107",true) == 0)
            {
                SetPlayerPos(playerid,2315.952880,-1.618174,26.742187);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Bank");
            }
            else if(strcmp(x_nr,"108",true) == 0)
            {
                SetPlayerPos(playerid,2319.714843,-14.838361,26.749565);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Bank (behind desk)");
            }
            else if(strcmp(x_nr,"109",true) == 0)
            {
                SetPlayerPos(playerid,1710.433715,-1669.379272,20.225049);
                SetPlayerInterior(playerid,18);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ LS Atruim");
            }
            else if(strcmp(x_nr,"110",true) == 0)
            {
                SetPlayerPos(playerid,1494.325195,1304.942871,1093.289062);
                SetPlayerInterior(playerid,3);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ Bike School");
            }
            else if(strcmp(x_nr,"111",true) == 0)
            {
                SetPlayerPos(playerid, 1549.6086,-32.9997,21.3286);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ แลกเงินแดง");
            }
            else if(strcmp(x_nr,"112",true) == 0)
            {
                SetPlayerPos(playerid, 888.1677,-23.6436,63.2566);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ เก็บวัชพืช");
            }
            else if(strcmp(x_nr,"113",true) == 0)
            {
                SetPlayerPos(playerid, -1423.6852,-1477.2373,105.0321);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ ขายกัญชา 1");
            }
            else if(strcmp(x_nr,"114",true) == 0)
            {
                SetPlayerPos(playerid, -1483.21924, 2651.37354, 55.74530);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ ขายกัญชา 2 (ยังไม่มี)");
            }
            else if(strcmp(x_nr,"115",true) == 0)
            {
                SetPlayerPos(playerid, -1863.0320,-1560.2201,21.7500);
                SetPlayerInterior(playerid,0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่ process วัชพืช");
            }
            else if(strcmp(x_nr,"116",true) == 0)
            {
                SetPlayerPos(playerid, 1676.8683,-1459.5503,3002.8413);
                SetPlayerVirtualWorld(playerid, 0);
			    SetPlayerInterior(playerid, 0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่  New House");
            }
            else if(strcmp(x_nr,"117", true) == 0){
                SetPlayerPos(playerid, 1406.1517,-4.3266,1001.0047);
                SetPlayerVirtualWorld(playerid, 0);
                SetPlayerInterior(playerid, 1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่  New Hospital");
            }
            else if(strcmp(x_nr,"118", true) == 0){
                SetPlayerPos(playerid, 1594.0793,-1687.1176,-58.2830);
                SetPlayerVirtualWorld(playerid, 897);
                SetPlayerInterior(playerid, 119);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่  สถานีตำรวจใหม่");
            }
            else if(strcmp(x_nr,"119", true) == 0){
                SetPlayerPos(playerid, -322.8066,1047.4307,-50.4840);
                SetPlayerVirtualWorld(playerid, 0);
                SetPlayerInterior(playerid, 0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่  โรงพยาบาล Fort Cason");
            }
            else if(strcmp(x_nr,"120", true) == 0){
                SetPlayerPos(playerid, -216.2649,981.8255,-12.7282);
                SetPlayerVirtualWorld(playerid, 0);
                SetPlayerInterior(playerid, 0);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่  สถานีตำรวจ Fort Cason");
            }
            else if(strcmp(x_nr,"121", true) == 0){
                SetPlayerPos(playerid, 2225.5403,2516.8298,-54.9877);
                SetPlayerVirtualWorld(playerid, 0);
                SetPlayerInterior(playerid, 1);
                SendClientMessage(playerid,COLOR_SUPERRED,"คุณได้วาปมาที่  โบสถ์");
            }
            else if(strcmp(x_nr, "122", true) == 0){
                SetPlayerPos(playerid, 597.6992,-1546.2081,-96.9725);
                SetPlayerVirtualWorld(playerid, 0);
                SetPlayerInterior(playerid, 1);
                SendClientMessage(playerid, COLOR_SUPERRED, " คุณได้วาปมาที่ สำนักข่าว");
            }
            else if(strcmp(x_nr, "123", true) == 0){
                SetPlayerPos(playerid, 2040.8159,1003.4343,3001.0859);
                SetPlayerVirtualWorld(playerid, 0);
                SetPlayerInterior(playerid, 0);
                SendClientMessage(playerid, COLOR_SUPERRED, " คุณได้วาปมาที่ คาสิโน");
            }
            else if(strcmp(x_nr, "124", true) == 0){
                SetPlayerPos(playerid, 2450.7180,2376.4055,-39.3672);
                SetPlayerVirtualWorld(playerid, 0);
                SetPlayerInterior(playerid, 0);
                SendClientMessage(playerid, COLOR_SUPERRED, " คุณได้วาปมาที่ ธนาคารใหม่");
            }
            else
            {
                SendClientMessage(playerid, COLOR_WHITE, "การใช้: /int [1-124] เท่านั้น");
                return 1;
            }
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREY, "คุณไม่ใช่แอดมิน");
            return 1;
        }
    }
    return 1;
}

CMD:auncuff(playerid, params[])
{
    if(!LoggedIn[playerid])
        return ErrorMsg(playerid, "คุณไม่ได้ล็อคอิน");

    if(PlayerData[playerid][pAdmin] < 1) return 1;

    new
        userid;

    if (sscanf(params, "u", userid))
        return SendClientMessage(playerid, -1, "/uncuff [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นได้ตัดการเชื่อมต่อแล้ว");

    if (!BitFlag_Get(g_PlayerFlags[userid],PLAYER_CUFFED))
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นไม่ได้ถูกใส่กุญแจมือในขณะนี้");


    BitFlag_Off(g_PlayerFlags[userid],PLAYER_CUFFED);
    SetPlayerSpecialAction(userid, SPECIAL_ACTION_NONE);
    RemovePlayerAttachedObject(userid, 7);
    TogglePlayerControllable(userid, 1);
    PlayerData[userid][pCuffed] = 0;
    SendClientMessageEx(userid, COLOR_YELLOW, "ผู้ดูแล ได้ปลดกุญแจมือให้คุณแล้ว");
    return 1;
}

CMD:jailtime(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] > 4 || GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_NATIONAL){
        new userid;
        if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/jailtime [playerid]");
        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
        if(userid != INVALID_PLAYER_ID){
            if(LoggedIn[userid]){
                if(PlayerData[userid][pJail] != 0)
                    SendClientMessageEx(playerid, COLOR_YELLOW, "- เวลาจำคุกของ %s คือ %d วินาที", ReturnRoleplayName(userid), PlayerData[userid][pJailTime]);
            }
        }
    }
    return 1;
}

CMD:aunjail(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] > 4){
        new userid;
        if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/aunjail [playerid]");
        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
        if(userid != INVALID_PLAYER_ID){
            if(LoggedIn[userid]){
                if(PlayerData[userid][pJail] != 0){
                    PlayerData[userid][pJailTime] = 0;
                }
            }
        }
    }
    return 1;
}

CMD:setattach(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1337)
	{
		new slot, bone, objecid;
		if(sscanf(params, "ddI(1)", slot, objecid, bone))
			return SendClientMessage(playerid, COLOR_GREY, "/setattach [slot] [objectid] [bone]");

	    SetPlayerAttachedObject(playerid, slot, objecid, bone);
	}
  	return 1;
}

CMD:editattach(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1337)
	{
		new slot;
		if(sscanf(params, "d", slot))
			return SendClientMessage(playerid, COLOR_GREY, "/editattach [slot]");


		SetPVarInt(playerid, "AttachEdit", 1);
	  	EditAttachedObject(playerid, slot);
	}

  	return 1;
}

CMD:admins(playerid, params[]){
	if(LoggedIn[playerid] == false) return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");
    if(PlayerData[playerid][pAdmin] <= 0) return 1;
	SendClientMessage(playerid, -1, "--------------------------------------------------");
    new count = 0;
    if(PlayerData[playerid][pAdmin] >= 1){
        foreach(new x : Player) if(LoggedIn[x]){
            if(PlayerData[x][pAdmin] > 0 && PlayerData[x][pAdmin] <= 1339){
                if(AdminDuty[x] == 0)
                    SendClientMessageEx(playerid, COLOR_GRAY, "[Admin Level: %d] %s (%s) (ยังไม่ได้ปฏิบัติงาน)", PlayerData[x][pAdmin], ReturnRoleplayName(x), PlayerData[x][pAdminName]);
                else if(AdminDuty[x] == 1)
                    SendClientMessageEx(playerid, COLOR_GREEN, "[Admin Level: %d] %s (เริ่มปฏิบัติงาน)", PlayerData[x][pAdmin], PlayerData[x][pAdminName]);
            
                count++;
            }
        }
    }
    if(!count) SendClientMessage(playerid, COLOR_GRAY, "ไม่มีแอดมินออไนลน์");
	SendClientMessage(playerid, -1, "--------------------------------------------------");
	return 1;
}

CMD:checkstate(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");
    new userid;
    if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/checkstate [playerid]");
    if(userid == INVALID_PLAYER_ID) return 1;
    if(!LoggedIn[userid]) return 1;
    SendClientMessageEx(playerid, COLOR_YELLOW, "สถานะของ %s", ReturnRoleplayName(userid));
    new inj[64], hospi[64];

    if(PlayerData[userid][pInjured] == 1) inj = "บาดเจ็บ";
    else if(PlayerData[playerid][pInjured] == 0) inj = "ไม่บาดเจ็บ";

    if(PlayerData[userid][pInHospital] == 1) hospi = "นอน";
    else if(PlayerData[userid][pInHospital] == 0) hospi = "ไม่ได้นอน";

    SendClientMessageEx(playerid, COLOR_YELLOW, "- อาการบาดเจ็บ: [%s] | นอนโรงพยาบาล: [%s]", inj, hospi);
    return 1;
}

CMD:rebus(playerid, params[]){
    if(PlayerData[playerid][pAdmin] < 1339) return 1;
    if(BusRed != 0){
        TRP_DestroyVehicle(BusRed);
    }
    if(BusYellow != 0){
        TRP_DestroyVehicle(BusYellow);
    }
    ConnectNPC("NPCBUSNO1", "BusRed");
    ConnectNPC("NPCBUSNO2", "BusYellow");
	BusRed = CreateVehicle(431, 0.0, 0.0, 5.0, 0.0, 3, 3, -1);
    BusYellow = CreateVehicle(431, 0.0, 0.0, 5.0, 0.0, 6, 6, -1);
    return 1;
}

CMD:renpc(playerid, params[]){
    if(PlayerData[playerid][pAdmin] < 1339) return 1;
	FCNPC_Spawn(NPCPUBLICGIRL,151 ,1129.0079,-1449.5337,15.7969);
	FCNPC_SetAngle(NPCPUBLICGIRL,359.7365);
	SetPlayerColor(NPCPUBLICGIRL,0xFFFFFFAA);
    FCNPC_Respawn(NPCPUBLICGIRL);
    return 1;
}

forward RemovePlayerExitGroup();
public RemovePlayerExitGroup(){
	static
	    rows,
        string[128];

    new CHARID;
	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++){
        cache_get_value_name_int(i, "ID", CHARID);
        format(string, sizeof(string), "UPDATE `characters` SET `GroupID` = '-1', `GroupRank` = '0' WHERE `ID` = '%d'", CHARID);
        mysql_tquery(dbCon, string);
	}
	return 1;
}

CMD:removemembers(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new groupid = -1;
    if(sscanf(params, "d", groupid)) return SystemMsg(playerid, "/removemembers [groupid]");
    if ((groupid < -1 || groupid >= MAX_GROUPS) || (groupid != -1 && !GroupData[groupid][groupExists]))
	    return ErrorMsg(playerid, "คุณระบุกลุ่มไม่ถูกต้อง");

    foreach(new i : Player){
        if(!LoggedIn[i]) continue;
        if(PlayerData[i][pGroup] == groupid){
            ResetGroup(i);
            SendClientMessage(i, -1, "ผู้ดูแล ได้ลบคุณออกจากกลุ่ม");
        }
    }    

    new query[256];

    format(query, sizeof(query), "SELECT ID, GroupID, GroupRank FROM `characters` WHERE `GroupID` = '%d'", GroupData[groupid][groupID]);
	mysql_tquery(dbCon, query, "RemovePlayerExitGroup");

    SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ทำการลบสมาชิกของกลุ่ม %s ทั้งหมดเรียบร้อยแล้ว", GroupData[groupid][groupName]);
    return 1;
}