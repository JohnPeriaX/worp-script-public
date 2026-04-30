#if defined _inc_impl
	#undef _inc_impl
#endif

LoadTextSleepOnBed(){
    TextDrawBed[0] = CreateDynamic3DTextLabel("[เตียงนอน $500]\nกด 'Y' เพื่อใช้งาน", 0xFF73FBFF, 1393.7346,-4.9261,1001.0047, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);

    TextDrawBed[1] = CreateDynamic3DTextLabel("[เตียงนอน $500]\nกด 'Y' เพื่อใช้งาน", 0xFF73FBFF, 1383.1830,-5.0377,1001.0047, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);

    TextDrawBed[2] = CreateDynamic3DTextLabel("[เตียงนอน $500]\nกด 'Y' เพื่อใช้งาน", 0xFF73FBFF, 1372.1964,-5.0009,1001.0047, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
    return 1;
}

ResetDamages(playerid)
{
	for(new i = 0; i < MAX_DAMAGES; i++)
	{
	    DamageData[playerid][i][dExists] = false;
		DamageData[playerid][i][dSec] = 0;
		DamageData[playerid][i][dDamage] = 0.0;
		DamageData[playerid][i][dShotType] = 0;
		DamageData[playerid][i][dWeaponid] = 0;
		DamageData[playerid][i][dArmour] = 0;
	}
	return 1;
}

AddPlayerDamage(playerid, weaponid, Float:damage, armour, bodypart){

	new issuccess;

	for(new i = 0; i < MAX_DAMAGES; i++)
	{
	    if(!DamageData[playerid][i][dExists])
	    {
	        DamageData[playerid][i][dExists] = true;
	        DamageData[playerid][i][dSec] = gettime();
	        DamageData[playerid][i][dDamage] = damage;
	        DamageData[playerid][i][dShotType] = bodypart;
	        DamageData[playerid][i][dArmour] = armour;
	        DamageData[playerid][i][dWeaponid] = weaponid;

            issuccess = 1;
	    	break;
	    }
	}
	if(!issuccess)
	{
	    new emptyslot;

		for(new i = 0; i < MAX_DAMAGES; i++)
		{
		    new moretime;
		    if(DamageData[playerid][i][dExists])
		    {
		        if(moretime < gettime()-DamageData[playerid][i][dSec])
		        {
		            moretime = gettime()-DamageData[playerid][i][dSec];
		            emptyslot = i;
		        }
		    }
		}


	  	DamageData[playerid][emptyslot][dExists] = true;
	 	DamageData[playerid][emptyslot][dSec] = gettime();
	  	DamageData[playerid][emptyslot][dDamage] = damage;
	  	DamageData[playerid][emptyslot][dShotType] = bodypart;
	   	DamageData[playerid][emptyslot][dArmour] = armour;
	  	DamageData[playerid][emptyslot][dWeaponid] = weaponid;

	}
	return 1;
}

GetBodyPartName(bodypart)
{
	new name[16];
	switch(bodypart)
	{
		case 3: name = "ลำตัว";
		case 4: name = "ขาหนีบ";
		case 5: name = "แขนซ้าย";
		case 6: name = "แขนขวา";
		case 7: name = "ขาซ้าย";
		case 8: name = "ขาขวา";
		case 9: name = "หัว";
	}
	return name;
}

ShowPlayerLockerMedic(playerid, id){
	new caption[128], string[128];
	format(caption, sizeof(caption), "Locker ของ %s", GroupData[id][groupName]);
	format(string, sizeof(string), "- เริ่มปฏิบัติงาน/เลิกทำงาน\n- เปลี่ยนชุด\n- อุปกรณ์เสริม\n- เบิกอุปกรณ์แพทย์\n- คลังเงิน");
	Dialog_ShowEasy(playerid, LockerMedic, DIALOG_STYLE_LIST, caption, string, "เลือก", "ยกเลิก");
	return 1;
}

Dialog:LockerMedic(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(listitem == 0){
            if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_ONDUTY)){
                BitFlag_On(g_PlayerFlags[playerid], PLAYER_ONDUTY);
                SetGroupColor(playerid);
                PlayerData[playerid][pOnPlayerDuty] = 1;
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
            new groupid = PlayerData[playerid][pGroup];
            new string[256];
            for (new i = 0; i < 10; i ++){
                if (GroupData[groupid][groupWeapons][i])
                    format(string, sizeof(string), "%sอาวุธ %d: %s (%d)\n", string, i + 1, ReturnWeaponName(GroupData[groupid][groupWeapons][i]), GroupData[groupid][groupAmmo][i]);

                else format(string, sizeof(string), "%sว่าง\n", string);
            }
            Dialog_ShowEasy(playerid, LockerWeaponsMedic, DIALOG_STYLE_LIST, "คลังอาวุธ", string, "เลือก", "ยกเลิก");
        }
        if(listitem == 3){
            if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_ONDUTY))
                return ErrorMsg(playerid, "คุณจำเป็นต้องปฏิบัติหน้าที่ก่อน");

            Dialog_ShowEasy(playerid, MedicToolMenu, DIALOG_STYLE_LIST, "อุปกรณ์แพทย์", "- กล่องพยาบาล (Medkit)\n- ถุงเลือด (Blood bag)", "เลือก", "ยกเลิก");
        }
        if(listitem == 4){
            new string[128];
            if(GetGroupType(playerid) == GROUP_MEDIC){
                if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                    format(string, sizeof(string), "เงินในคลัง: %s", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
                    Dialog_ShowEasy(playerid, MoneyLockerMedicShow, DIALOG_STYLE_LIST, "คลังเงิน", string, "ตกลง", "");
                }
                else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                    format(string, sizeof(string), "เงินในคลัง: %s", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
                    Dialog_ShowEasy(playerid, MoneyLockerMedic, DIALOG_STYLE_LIST, "คลังเงิน", string, "ตกลง", "");
                }
            }
        }
    }
    return 1;
}

Dialog:LockerWeaponsMedic(playerid, response, listitem, inputtext[]){
	new groupid = PlayerData[playerid][pGroup];
	if (groupid == -1)
		return 0;

	if (response)
	{
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

Dialog:MoneyLockerMedic(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new string[128];
            format(string, sizeof(string), "เงินในคลัง: %s\nกรอกจำนวนที่คุณต้องการจะเบิก:", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
            Dialog_ShowEasy(playerid, WithDrawMoneyLockerMedic, DIALOG_STYLE_INPUT, "คลังเงิน > เบิก", string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:WithDrawMoneyLockerMedic(playerid, response, listitem, inputtext[]){
    if(!response)   return 1;
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนเงินมากกว่า 0");

        if(amount > GroupData[PlayerData[playerid][pGroup]][groupMoney])
            return ErrorMsg(playerid, "จำนวนเงินในคลังมีไม่เพียงพอ");

        GiveMoney(playerid, amount, "withdraw medic");
        GroupData[PlayerData[playerid][pGroup]][groupMoney] -= amount;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], COLOR_RADIO, "(( [%s] %s(%d) ได้ทำการเบิกเงินคลังของกลุ่มออกมาจำนวน: %s ))", Group_GetRank(playerid), ReturnRoleplayName(playerid), playerid, FormatNumber(amount));
        new string[256];
        format(string, sizeof(string), "```> [%s] (%d) %s(%d) Withdraw Money from Storage Group [%s]```", ReturnDate(), PlayerData[playerid][pGroupRank], ReturnRoleplayName(playerid), playerid, FormatNumber(amount));
		DCC_SendChannelMessage(WithdrawMedic, string);
    }
    return 1;
}

Dialog:MedicToolMenu(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(listitem == 0){
            new id = PlayerInventory_AddItem(playerid, "Medkit", 11738, 10);

			if (id == -1)
				return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เบิก 'Medkit' จำนวน 10 ชิ้น เรียบร้อยแล้ว");
            Log_Write("logs/medics.txt", "[%s] %s Take Medkit", ReturnDate(), ReturnRoleplayName(playerid));
        }
        if(listitem == 1){
            new id = PlayerInventory_AddItem(playerid, "Blood bag", 11736, 10);

			if (id == -1)
				return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เบิก 'Blood bag' จำนวน 10 ชิ้น เรียบร้อยแล้ว");
            Log_Write("logs/medics.txt", "[%s] %s Take Blood bag", ReturnDate(), ReturnRoleplayName(playerid));
        }
    }
    return 1;
}

Dialog:CprPlayer(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "playerID", GetPVarInt(playerid, str_biz));
			SetPlayerCprTargetPlayer(playerid);
			return 1;
		}
    }
    return 1;
}

SetPlayerCprTargetPlayer(playerid){
    new targetid = GetPVarInt(playerid, "playerID");

    if(PlayerInventory_AllCount(playerid, "Medkit") <= 0)
        return ErrorMsg(playerid, "คุณไม่มี Medkit");

    if(PlayerData[targetid][pInjured] == 1){
        if(IsPlayerNearPlayer(playerid, targetid, 3.0)){
            PlayerData[targetid][pInjured] = 0;
            PlayerData[targetid][pInjuredTime] = 0;
            SetPlayerColor(targetid, 0xFFFFFF00);
            ClearAnimations(targetid);
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "MEDIC", "CPR", 4.1, 0, 0, 0, 0, 0, 1);
            PlayerInventory_Remove(playerid, "Medkit", 1);
            TogglePlayerControllable(targetid, 1);
            ResetDamages(targetid);
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ทำการรักษา %s(%d) เรียบร้อยแล้ว", ReturnRoleplayName(targetid), targetid);
            SendClientMessageEx(targetid, COLOR_YELLOW, "- คุณได้รับการรักษาจาก %s(%d) เรียบร้อยแล้ว", ReturnRoleplayName(playerid), playerid);
        }
    }
    return 1;
}

Dialog:BloodBagMenu(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(listitem == 0){
            if(PlayerInventory_AllCount(playerid, "Blood bag") <= 0) return ErrorMsg(playerid, "คุณไม่มี Blood bag");
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้ใช้ 'Blood bag (ถุงเลือด)'", ReturnRoleplayName(playerid));
            PlayerInventory_Remove(playerid, "Blood bag", 1);
            PlayerData[playerid][pFirstAid] = true;
            
            PlayerData[playerid][pAidTimer] = SetTimerEx("BloodbagUpdate", 1000, 0, "i", playerid);
        }
        if(listitem == 1){
            new stringplayer[1024];
            new count;
            new menu[20];
            foreach(new x : Player){
                if(!LoggedIn[x]) continue;
                if(x == playerid) continue;
                if(IsPlayerNearPlayer(playerid, x, 3.0)){
                    new Float:hp;
                    GetPlayerHealth(x, hp);

                    format(menu, 20, "menu%d", count++);
                    SetPVarInt(playerid, menu, x);
                    format(stringplayer, sizeof(stringplayer), "%s %s(%d) (เลือด: %.0f)\n", stringplayer, ReturnRoleplayName(x), x, hp);
                }
                if(count >= 20) break;
            }
            if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "เลือกผู้เล่นที่จะเพิ่มเลือด", "ไม่มีใครอยู่ใกล้คุณเลย", "ตกลง", "ยกเลิก");
            else Dialog_ShowEasy(playerid, BloodbagToPlayer, DIALOG_STYLE_LIST, "เลือกผู้เล่นที่จะเพิ่มเลือด", stringplayer, "เลือก", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:BloodbagToPlayer(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "playerID", GetPVarInt(playerid, str_biz));
			SetPlayerBloodbagToTargetplayer(playerid);
			return 1;
		}
    }
    return 1;
}

SetPlayerBloodbagToTargetplayer(playerid){
    new targetid = GetPVarInt(playerid, "playerID");

    new Float:hp;
    GetPlayerHealth(targetid, hp);

    if(PlayerInventory_AllCount(playerid, "Blood bag") <= 0)
        return ErrorMsg(playerid, "คุณไม่มี Blood bag");

    if(hp >= 100)
        return ErrorMsg(playerid, "ผู้เล่นนั้นเลือดเต็ม 100 แล้ว");

    if(IsPlayerNearPlayer(playerid, targetid, 3.0)){
        ClearAnimations(targetid);
        ClearAnimations(playerid);

        if (!IsPlayerInAnyVehicle(targetid) && GetPlayerAnimationIndex(targetid) != 1508)
    	    ApplyAnimation(targetid, "SWAT", "gnstwall_injurd", 4.0, 1, 0, 0, 0, 0);

        PlayerData[targetid][pFirstAid] = true;
        PlayerData[targetid][pAidTimer] = SetTimerEx("BloodbagUpdate", 1000, 0, "i", targetid);

        ApplyAnimation(playerid, "MEDIC", "CPR", 4.1, 0, 0, 0, 0, 0, 1);
        PlayerInventory_Remove(playerid, "Blood bag", 1);
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ทำการเพิ่มเลือดให้กับ %s(%d) เรียบร้อยแล้ว", ReturnRoleplayName(targetid), targetid);
        SendClientMessageEx(targetid, COLOR_YELLOW, "- คุณได้รับการเพิ่มเลือดจาก %s(%d) เรียบร้อยแล้ว", ReturnRoleplayName(playerid), playerid);
    }
    return 1;
}

CMD:damages(playerid, params[])
{
	new targetid, string[1046], count;

	if (sscanf(params, "u", targetid))
		return SystemMsg(playerid, "/damages [playerid/name]");

    if(GetGroupType(playerid) != GROUP_MEDIC) return 1;

	if (targetid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, targetid, 3.0))
	{
		ErrorMsg(playerid, "ผู้เล่นนั้นตัดการเชื่อมต่อหรือไม่ได้อยู่ใกล้คุณ");
		return 1;
	}

    new checkarmour[64];

	for(new i = 0; i < MAX_DAMAGES; i++)
	{
	    if(DamageData[targetid][i][dExists])
		{
            if(DamageData[targetid][i][dArmour] == 1) checkarmour = "โดนเกราะ";
            else checkarmour = "ไม่โดนเกราะ";

			format(string, sizeof(string), "%s%.2f ถูกทำดาเมจโดย %s ไปที่ %s (%s) %d วินาที ที่ผ่านมา\n", string, DamageData[targetid][i][dDamage], ReturnWeaponName(DamageData[targetid][i][dWeaponid]), GetBodyPartName(DamageData[targetid][i][dShotType]), checkarmour, gettime()-DamageData[targetid][i][dSec]);
			count++;
		}
	}
	return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, ReturnRoleplayName(targetid), (count) ? (string) : (" "), "Close", "");
}
