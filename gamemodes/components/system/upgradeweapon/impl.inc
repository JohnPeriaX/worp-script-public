#if defined _inc_impl
	#undef _inc_impl
#endif

Reset_PlayerUpgradeWeapon(playerid){
    Open_UpgradeMenu[playerid] = 0;
    Open_UpgradeMenuFinish[playerid] = 0;
    Can_CloseUpgradeFinish[playerid] = 0;
    format(WeaponNameData[playerid][weaponMainName], 32, "Empty");
    Weapon_MainModel[playerid] = 18631;
    Weapon_MainLevel[playerid] = 0;

    format(WeaponNameData[playerid][weaponSecondName], 32, "Empty");
    Weapon_SecondModel[playerid] = 18631;

    format(UpgradeWeapon_GetStatus[playerid], 32, "Not Ready");

    Weapon_MainIndex[playerid] = -1;
    Weapon_SecondIndex[playerid] = -1;

    PlayerStart_UpgradeWeapon[playerid] = 0;
    PlayerUpgradeWeapon_Point[playerid] = 0;

    Weapon_UpgradeStats[playerid] = false;

    KillTimer(PlayerUpgradeWeaponTimer[playerid]);

    UnBorkenCardIndex[playerid] = -1;
    UnBorkenCardModel[playerid] = 18631;
    return 1;
}

CMD:upgradeweaponcmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1338)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[UPGRADEWEAPONCMDS]: /makeupgradeweapon, /removeupgradeweapon, /editupgradeweapon");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
    return 1;
}

CMD:makeupgradeweapon(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new id = UpgradeWeapon_Create(playerid);
    if(id == -1) return ErrorMsg(playerid, "เซิฟเวอร์ได้สร้างจุดตีบวกอาวุธเต็มแล้ว");
	SendClientMessageEx(playerid, -1, "คุณประสบความสำเร็จสร้างจุดตีบวกอาวุธไอดี: %d", id);
    return 1;
}

CMD:removeupgradeweapon(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;

	new
		id = -1;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/removeupgradeweapon [craft id]");

	if ((id < 0 || id >= MAX_UPGRADEWEAPON) || !UpgradeWeaponData[id][upgradeweaponEx])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีจุดตีบวกอาวุธผิดพลาด");

	UpgradeWeapon_Delete(id);
    SendClientMessageEx(playerid, -1, "คุณประสบความสำเร็จในการทำลายจุดตีบวกอาวุธไอดี: %d", id);
	return 1;
}

CMD:editupgradeweapon(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	new
		id = -1,
		type[24],
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
	{
		SystemMsg(playerid, "/editupgradeweapon [id] [name]");
		SystemMsg(playerid, "[ตัวเลือก]:{FFFFFF} location");
		return 1;
	}

	if ((id < 0 || id >= MAX_UPGRADEWEAPON) || !UpgradeWeaponData[id][upgradeweaponEx])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีจุดตีบวกอาวุธผิดพลาด");

	if (!strcmp(type, "location", true))
	{
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);

		UpgradeWeaponData[id][upgradeweaponPos][0] = x;
		UpgradeWeaponData[id][upgradeweaponPos][1] = y;
		UpgradeWeaponData[id][upgradeweaponPos][2] = z;

		UpgradeWeaponData[id][upgradeweaponInt] = GetPlayerInterior(playerid);
		UpgradeWeaponData[id][upgradeweaponWorld] = GetPlayerVirtualWorld(playerid);

		UpgradeWeapon_Refresh(id);
		UpgradeWeapon_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่งของจุดตีบวกอาวุธ ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	return 1;
}

forward UpgradeWeapon_Load();
public UpgradeWeapon_Load(){
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_UPGRADEWEAPON){
	    UpgradeWeaponData[i][upgradeweaponEx] = true;

	    cache_get_value_name_int(i, "upgradeweaponID", UpgradeWeaponData[i][upgradeweaponID]);
	    cache_get_value_name_float(i, "upgradeweaponPosX", UpgradeWeaponData[i][upgradeweaponPos][0]);
	    cache_get_value_name_float(i, "upgradeweaponPosY", UpgradeWeaponData[i][upgradeweaponPos][1]);
	    cache_get_value_name_float(i, "upgradeweaponPosZ", UpgradeWeaponData[i][upgradeweaponPos][2]);
	    cache_get_value_name_int(i, "upgradeweaponInt", UpgradeWeaponData[i][upgradeweaponInt]);
	    cache_get_value_name_int(i, "upgradeweaponWorld", UpgradeWeaponData[i][upgradeweaponWorld]);

        Count_UpgradeWeapon++;

 	    UpgradeWeapon_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d UpgradeWeapon Successfully ))", Count_UpgradeWeapon);
	return 1;
}

UpgradeWeapon_Create(playerid){
	new
	    Float:x,
	    Float:y,
	    Float:z;

	if (GetPlayerPos(playerid, x, y, z)){
		for (new i = 0; i != MAX_UPGRADEWEAPON; i ++)
		{
	    	if (!UpgradeWeaponData[i][upgradeweaponEx])
	    	{
	        	UpgradeWeaponData[i][upgradeweaponEx] = true;

				UpgradeWeaponData[i][upgradeweaponPos][0] = x;
	        	UpgradeWeaponData[i][upgradeweaponPos][1] = y;
	        	UpgradeWeaponData[i][upgradeweaponPos][2] = z;

	        	UpgradeWeaponData[i][upgradeweaponInt] = GetPlayerInterior(playerid);
	        	UpgradeWeaponData[i][upgradeweaponWorld] = GetPlayerVirtualWorld(playerid);

	        	UpgradeWeapon_Refresh(i);
	        	mysql_tquery(dbCon, "INSERT INTO `upgradeweapons` (`upgradeweaponInt`) VALUES(0)", "OnUpgradeWeaponCreated", "d", i);
	        	return i;
	        }
	    }
	}
	return -1;
}

forward OnUpgradeWeaponCreated(upgradeweaponid);
public OnUpgradeWeaponCreated(upgradeweaponid)
{
	if (upgradeweaponid == -1 || !UpgradeWeaponData[upgradeweaponid][upgradeweaponEx])
	    return 0;

	UpgradeWeaponData[upgradeweaponid][upgradeweaponID] = cache_insert_id();
	UpgradeWeapon_Save(upgradeweaponid);

	return 1;
}

UpgradeWeapon_Save(upgradeweaponid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `upgradeweapons` SET `upgradeweaponPosX` = '%.4f', `upgradeweaponPosY` = '%.4f', `upgradeweaponPosZ` = '%.4f', `upgradeweaponInt` = '%d', `upgradeweaponWorld` = '%d' WHERE `upgradeweaponID` = '%d'",
		UpgradeWeaponData[upgradeweaponid][upgradeweaponPos][0],
	    UpgradeWeaponData[upgradeweaponid][upgradeweaponPos][1],
	    UpgradeWeaponData[upgradeweaponid][upgradeweaponPos][2],
	    UpgradeWeaponData[upgradeweaponid][upgradeweaponInt],
	    UpgradeWeaponData[upgradeweaponid][upgradeweaponWorld],
        UpgradeWeaponData[upgradeweaponid][upgradeweaponID]
	);

	return mysql_tquery(dbCon, query);
}

UpgradeWeapon_Delete(upgradeweaponid)
{
	if (upgradeweaponid != -1 && UpgradeWeaponData[upgradeweaponid][upgradeweaponEx])
	{
	    new
	        string[64];

        Count_UpgradeWeapon--;

		format(string, sizeof(string), "DELETE FROM `upgradeweapons` WHERE `upgradeweaponID` = '%d'", UpgradeWeaponData[upgradeweaponid][upgradeweaponID]);
		mysql_tquery(dbCon, string);

        if (IsValidDynamic3DTextLabel(UpgradeWeaponData[upgradeweaponid][upgradeweaponText]))
            DestroyDynamic3DTextLabel(UpgradeWeaponData[upgradeweaponid][upgradeweaponText]);

        if (IsValidDynamicPickup(UpgradeWeaponData[upgradeweaponid][upgradeweaponPickup]))
            DestroyDynamicPickup(UpgradeWeaponData[upgradeweaponid][upgradeweaponPickup]);

		UpgradeWeaponData[upgradeweaponid][upgradeweaponEx] = false;
	    UpgradeWeaponData[upgradeweaponid][upgradeweaponID] = 0;
	}
	return 1;
}

UpgradeWeapon_Refresh(upgradeweaponid){
    if (upgradeweaponid != -1 && UpgradeWeaponData[upgradeweaponid][upgradeweaponEx])
	{
        if (IsValidDynamic3DTextLabel(UpgradeWeaponData[upgradeweaponid][upgradeweaponText]))
            DestroyDynamic3DTextLabel(UpgradeWeaponData[upgradeweaponid][upgradeweaponText]);

        if (IsValidDynamicPickup(UpgradeWeaponData[upgradeweaponid][upgradeweaponPickup]))
            DestroyDynamicPickup(UpgradeWeaponData[upgradeweaponid][upgradeweaponPickup]);

		new
		    string[128];

		format(string, sizeof(string), "[ตีบวกอาวุธ]\nกดปุ่ม 'Y' เพื่อใช้งาน");

		UpgradeWeaponData[upgradeweaponid][upgradeweaponText] = CreateDynamic3DTextLabel(string, 0x33FFACDD, UpgradeWeaponData[upgradeweaponid][upgradeweaponPos][0], UpgradeWeaponData[upgradeweaponid][upgradeweaponPos][1], UpgradeWeaponData[upgradeweaponid][upgradeweaponPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, UpgradeWeaponData[upgradeweaponid][upgradeweaponWorld], UpgradeWeaponData[upgradeweaponid][upgradeweaponInt]);
	    UpgradeWeaponData[upgradeweaponid][upgradeweaponPickup] = CreateDynamicPickup(19132, 23, UpgradeWeaponData[upgradeweaponid][upgradeweaponPos][0], UpgradeWeaponData[upgradeweaponid][upgradeweaponPos][1], UpgradeWeaponData[upgradeweaponid][upgradeweaponPos][2], UpgradeWeaponData[upgradeweaponid][upgradeweaponWorld], UpgradeWeaponData[upgradeweaponid][upgradeweaponInt]);
	}
    return 1;
}

UpgradeWeapon_Nearest(playerid)
{
    for (new i = 0; i != MAX_UPGRADEWEAPON; i ++) if (UpgradeWeaponData[i][upgradeweaponEx] && IsPlayerInRangeOfPoint(playerid, 3.0, UpgradeWeaponData[i][upgradeweaponPos][0], UpgradeWeaponData[i][upgradeweaponPos][1], UpgradeWeaponData[i][upgradeweaponPos][2]))
	{
		if (GetPlayerInterior(playerid) == UpgradeWeaponData[i][upgradeweaponInt] && GetPlayerVirtualWorld(playerid) == UpgradeWeaponData[i][upgradeweaponWorld])
			return i;
	}
	return -1;
}

OnPlayer_UpgradeWeaponShow(playerid){
    LoadTextDraw_UpgradeWeapon(playerid);

    for(new i=0; i<max_upgradetextdraw; i++){
        PlayerTextDrawShow(playerid, UpgradeWeapon_TextDraw[playerid][i]);
    }

    ShowPlayerProgressBar(playerid, UpgradeWeapon_Bar[playerid][0]);
    SetPlayerProgressBarValue(playerid, UpgradeWeapon_Bar[playerid][0], 0.0);

    OnPlayerUpdate_UpgradeWeapon(playerid);

    SelectTextDraw(playerid, 0x33FFACAA);
    TogglePlayerControllable(playerid, 0);
    Open_UpgradeMenu[playerid] = 1;
    return 1;
}

OnPlayer_UpgradeWeaponHide(playerid){
    for(new i=0; i<max_upgradetextdraw; i++){
        PlayerTextDrawHide(playerid, UpgradeWeapon_TextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, UpgradeWeapon_TextDraw[playerid][i]);
    }

    HidePlayerProgressBar(playerid, UpgradeWeapon_Bar[playerid][0]);
    DestroyPlayerProgressBar(playerid, UpgradeWeapon_Bar[playerid][0]);

    CancelSelectTextDraw(playerid);
    TogglePlayerControllable(playerid, 1);
    Open_UpgradeMenu[playerid] = 0;
    if(Open_UpgradeMenuFinish[playerid] == 0)
        Reset_PlayerUpgradeWeapon(playerid);
    return 1;
}

OnPlayerUpdate_UpgradeWeapon(playerid){
    new string[128];

    format(string, sizeof(string), "Fail Stack: %d", PlayerData[playerid][pFailStack]);
    PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDraw[playerid][14], string);

    PlayerTextDrawHide(playerid, UpgradeWeapon_TextDraw[playerid][5]);
    PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDraw[playerid][5], Weapon_MainModel[playerid]);
    PlayerTextDrawShow(playerid, UpgradeWeapon_TextDraw[playerid][5]);

    format(string, sizeof(string), "%s", WeaponNameData[playerid][weaponMainName]);
    PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDraw[playerid][6], string);

    format(string, sizeof(string), "Level: %d", Weapon_MainLevel[playerid]);
    PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDraw[playerid][7], string);

    PlayerTextDrawHide(playerid, UpgradeWeapon_TextDraw[playerid][9]);
    PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDraw[playerid][9], Weapon_SecondModel[playerid]);
    PlayerTextDrawShow(playerid, UpgradeWeapon_TextDraw[playerid][9]);

    PlayerTextDrawHide(playerid, UpgradeWeapon_TextDraw[playerid][12]);
    PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDraw[playerid][12], UnBorkenCardModel[playerid]);
    PlayerTextDrawShow(playerid, UpgradeWeapon_TextDraw[playerid][12]);

    format(string, sizeof(string), "%s", WeaponNameData[playerid][weaponSecondName]);
    PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDraw[playerid][10], string);

    format(string, sizeof(string), "Level: 0");
    PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDraw[playerid][11], string);

    PlayerTextDrawHide(playerid, UpgradeWeapon_TextDraw[playerid][15]);
    if(Weapon_MainModel[playerid] != 18631 && Weapon_SecondModel[playerid] != 18631){

        new Fail_Stack = PlayerData[playerid][pFailStack];
        new Persent = 0;
        if(Fail_Stack < 5){
            if(Weapon_MainLevel[playerid] == 0) Persent = 50;
            else if(Weapon_MainLevel[playerid] == 1) Persent = 45;
            else if(Weapon_MainLevel[playerid] == 2) Persent = 35;
            else if(Weapon_MainLevel[playerid] == 3) Persent = 25;
            else if(Weapon_MainLevel[playerid] == 4) Persent = 15;
        }
        else if(Fail_Stack >= 5 && Fail_Stack <= 9){
            if(Weapon_MainLevel[playerid] == 0) Persent = 55;
            else if(Weapon_MainLevel[playerid] == 1) Persent = 50;
            else if(Weapon_MainLevel[playerid] == 2) Persent = 40;
            else if(Weapon_MainLevel[playerid] == 3) Persent = 30;
            else if(Weapon_MainLevel[playerid] == 4) Persent = 20;
        }
        else if(Fail_Stack >= 10 && Fail_Stack <= 14){
            if(Weapon_MainLevel[playerid] == 0) Persent = 57;
            else if(Weapon_MainLevel[playerid] == 1) Persent = 52;
            else if(Weapon_MainLevel[playerid] == 2) Persent = 42;
            else if(Weapon_MainLevel[playerid] == 3) Persent = 32;
            else if(Weapon_MainLevel[playerid] == 4) Persent = 22;
        }
        else if(Fail_Stack >= 15){
            if(Weapon_MainLevel[playerid] == 0) Persent = 60;
            else if(Weapon_MainLevel[playerid] == 1) Persent = 55;
            else if(Weapon_MainLevel[playerid] == 2) Persent = 45;
            else if(Weapon_MainLevel[playerid] == 3) Persent = 35;
            else if(Weapon_MainLevel[playerid] == 4) Persent = 25;
        }

        format(UpgradeWeapon_GetStatus[playerid], 32, "Ready (%d Percent)", Persent);
        PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][15], 0x24FF27AA);
    }
    else{
        format(UpgradeWeapon_GetStatus[playerid], 32, "Not Ready");
        PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][15], 0xFF2424AA);
    }
    PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDraw[playerid][15], UpgradeWeapon_GetStatus[playerid]);
    PlayerTextDrawShow(playerid, UpgradeWeapon_TextDraw[playerid][15]);
    return 1;
}

Show_PlayerSelectWeaponMain(playerid){
    new string[720], count = 0, menu[20];
    new weaponid = Weapon_MainIndex[playerid];
    new weaponsecondid = Weapon_SecondIndex[playerid];
    for(new i=0; i<MAX_INVENTORYPLAYERS; i++) if(Inventory_Player[playerid][i][itemHave]){
        if(Inventory_Player[playerid][i][itemLevel] < 5){
            if(weaponid == i) continue;
            if(weaponsecondid == i) continue;
            if(CheckItemIsWeapon(Inventory_Player[playerid][i][itemName]) != -1){
                format(menu, 20, "menu%d", count++);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s อาวุธ: %s (ระดับตีบวก: %d) จำนวน %d ชิ้น\n", string, Inventory_Player[playerid][i][itemName], Inventory_Player[playerid][i][itemLevel], Inventory_Player[playerid][i][itemQuantity]);
            }
        }
        if(count >= 20) break;
        if(i >= 107) break;
    }
    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "เลือกอาวุธทีต้องการจะตีบวก", "คุณไม่มีอาวุธใดๆอยู่กระเป๋าเลย", "ตกลง", "ยกเลิก");
    else Dialog_ShowEasy(playerid, Dialog_UpgradeWeapons, DIALOG_STYLE_LIST, "เลือกอาวุธทีต้องการจะตีบวก", string, "ตกลง", "ยกเลิก");
    return 1;
}

Dialog:Dialog_UpgradeWeapons(playerid, response, listitem, inputtext[]){
    if(!response){
        Weapon_MainIndex[playerid] = -1;
        format(WeaponNameData[playerid][weaponMainName], 32, "Empty");
        Weapon_MainModel[playerid] = 18631;
        Weapon_MainLevel[playerid] = 0;
        OnPlayerUpdate_UpgradeWeapon(playerid);
        return 1;
    }
    if(response){

        if(Open_UpgradeMenu[playerid] == 0) return 1;

        if(listitem >= 0 && listitem <= 20) {

            Weapon_SecondIndex[playerid] = -1;
            format(WeaponNameData[playerid][weaponSecondName], 32, "Empty");
            Weapon_SecondModel[playerid] = 18631;
            OnPlayerUpdate_UpgradeWeapon(playerid);

			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);
			Weapon_MainIndex[playerid] = GetPVarInt(playerid, str_biz);
			SetUpgradeWeaponMainSelect(playerid);
			return 1;
		}
    }
    return 1;
}

SetUpgradeWeaponMainSelect(playerid){
    new weaponid = Weapon_MainIndex[playerid];
    format(WeaponNameData[playerid][weaponMainName], 32, Inventory_Player[playerid][weaponid][itemName]);
    Weapon_MainModel[playerid] = Inventory_Player[playerid][weaponid][itemKey];
    Weapon_MainLevel[playerid] = Inventory_Player[playerid][weaponid][itemLevel];
    SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เลือกอาวุธ '%s' (ระดับตีบวก: %d) ไว้ช่องตีบวกอาวุธที่ 1 เรียบร้อยแล้ว", WeaponNameData[playerid][weaponMainName], Weapon_MainLevel[playerid]);
    OnPlayerUpdate_UpgradeWeapon(playerid);
    return 1;
}

Show_PlayerSelectWeaponSecond(playerid){
    new string[720], count = 0, menu[20];
    new weaponid = Weapon_MainIndex[playerid];

    for(new i=0; i<MAX_INVENTORYPLAYERS; i++) if(Inventory_Player[playerid][i][itemHave]){
        if (!strcmp(WeaponNameData[playerid][weaponMainName], Inventory_Player[playerid][i][itemName], true) && Inventory_Player[playerid][i][itemLevel] == 0){
            if(weaponid == i) continue;
            if(CheckItemIsWeapon(Inventory_Player[playerid][i][itemName]) != -1){
                format(menu, 20, "menu%d", count++);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s อาวุธ: %s จำนวน %d ชิ้น\n", string, Inventory_Player[playerid][i][itemName], Inventory_Player[playerid][i][itemQuantity]);
            }
        }   
        if(count >= 20) break;
        if(i >= 107) break;
    }
    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "เลือกอาวุธทีต้องการจะตีบวก", "คุณไม่มีอาวุธที่มีระดับตีบวก 0 อยู่ในกระเป๋าเลย", "ตกลง", "ยกเลิก");
    else Dialog_ShowEasy(playerid, Dialog_UpgradeSecond, DIALOG_STYLE_LIST, "เลือกอาวุธที่จะนำมาตีบวกกับอาวุธหลัก", string, "ตกลง", "ยกเลิก");
    return 1;
}

Dialog:Dialog_UpgradeSecond(playerid, response, listitem, inputtext[]){
    if(!response){
        Weapon_SecondIndex[playerid] = -1;
        format(WeaponNameData[playerid][weaponSecondName], 32, "Empty");
        Weapon_SecondModel[playerid] = 18631;
        OnPlayerUpdate_UpgradeWeapon(playerid);
        return 1;
    }
    if(response){

        if(Open_UpgradeMenu[playerid] == 0) return 1;

        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);
			Weapon_SecondIndex[playerid]  = GetPVarInt(playerid, str_biz);
			SetUpgradeWeaponSecondSelect(playerid);
			return 1;
		}
    }
    return 1;
}

SetUpgradeWeaponSecondSelect(playerid){
    new weaponid = Weapon_SecondIndex[playerid];

    format(WeaponNameData[playerid][weaponSecondName], 32, Inventory_Player[playerid][weaponid][itemName]);
    Weapon_SecondModel[playerid] = Inventory_Player[playerid][weaponid][itemKey];
    SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เลือกอาวุธ '%s' ไว้ช่องตีบวกอาวุธที่ 2 เรียบร้อยแล้ว", WeaponNameData[playerid][weaponSecondName]);
    OnPlayerUpdate_UpgradeWeapon(playerid);

    return 1;
}

OnPlayer_StartUpgradeWeapon(playerid){

    new string[128];
    format(string, sizeof(string), "คุณจะต้องใช้เงินจำนวน %s เพื่อใช้ในการอัพเกรดอาวุธของคุณ", FormatNumber(PRICE_UPGRADEWEAPON));
    Dialog_ShowEasy(playerid, ConfirmUpgradeWeapon, DIALOG_STYLE_MSGBOX, "เงื่อนไขการตีบวก", string, "ตกลง", "ยกเลิก");
    return 1;
}

Dialog:ConfirmUpgradeWeapon(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(GetMoney(playerid) < PRICE_UPGRADEWEAPON){
            new string[128];
            format(string, sizeof(string), "คุณมีเงินไม่เพียงพอกับ %s ที่จะใช้ในการตีบวก", FormatNumber(PRICE_UPGRADEWEAPON));
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", string, "ตกลง", "");
            return 1;
        }

        PlayerStart_UpgradeWeapon[playerid] = 1;
        PlayerUpgradeWeapon_Point[playerid] = 0;
        KillTimer(PlayerUpgradeWeaponTimer[playerid]);
        PlayerUpgradeWeaponTimer[playerid] = SetTimerEx("UpdateTimerUpgradeWeapon", 1000, false, "i", playerid);
    }
    return 1;
}

Show_PlayerSelectUnbrokenCard(playerid){
    new string[720], count = 0, menu[20];
    
    for(new i=0; i<MAX_INVENTORYPLAYERS; i++) if(Inventory_Player[playerid][i][itemHave]){
        if (!strcmp(Inventory_Player[playerid][i][itemName], "Unbroken Star", true)){
            format(menu, 20, "menu%d", count++);
            SetPVarInt(playerid, menu, i);
            format(string, sizeof(string), "%s %s จำนวน %d ชิ้น\n", string, Inventory_Player[playerid][i][itemName], Inventory_Player[playerid][i][itemQuantity]);
        }   
        if(count >= 20) break;
        if(i >= 107) break;
    }
    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "เลือกดาวกันแตก", "คุณไม่มีดาวกันแตกอยู่ในกระเป๋าเลย!", "ตกลง", "ยกเลิก");
    else Dialog_ShowEasy(playerid, Dialog_UnbrokenCard, DIALOG_STYLE_LIST, "เลือกดาวกันแตก", string, "ตกลง", "ยกเลิก");
    return 1;
}

Dialog:Dialog_UnbrokenCard(playerid, response, listitem, inputtext[]){
    if(!response){
        return 1;
    }
    if(response){

        if(Open_UpgradeMenu[playerid] == 0) return 1;

        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);
			UnBorkenCardIndex[playerid]  = GetPVarInt(playerid, str_biz);
			SetUnbrokenCarddSelect(playerid);
			return 1;
		}
    }
    return 1;
}

SetUnbrokenCarddSelect(playerid){
    new indexid = UnBorkenCardIndex[playerid];
    UnBorkenCardModel[playerid] = Inventory_Player[playerid][indexid][itemKey];
    SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้ใส่ดาวกันแตกจำนวน 1 ใบเรียบร้อยแล้ว");
    OnPlayerUpdate_UpgradeWeapon(playerid);
    return 1;
}

forward UpdateTimerUpgradeWeapon(playerid);
public UpdateTimerUpgradeWeapon(playerid){
    if(LoggedIn[playerid]){
        if(PlayerStart_UpgradeWeapon[playerid]){
            if(PlayerUpgradeWeapon_Point[playerid] < 100){
                PlayerUpgradeWeapon_Point[playerid] += 10;
                SetPlayerProgressBarValue(playerid, UpgradeWeapon_Bar[playerid][0], PlayerUpgradeWeapon_Point[playerid]);
                PlayerUpgradeWeaponTimer[playerid] = SetTimerEx("UpdateTimerUpgradeWeapon", 1000, false, "i", playerid);
            }
            else{
                KillTimer(PlayerUpgradeWeaponTimer[playerid]);
                Open_UpgradeMenuFinish[playerid] = 1;
                OnPlayer_UpgradeWeaponFinish(playerid);
                PlayerUpgradeWeapon_Point[playerid] = 0;
                PlayerStart_UpgradeWeapon[playerid] = 0;
                SetPlayerProgressBarValue(playerid, UpgradeWeapon_Bar[playerid][0], PlayerUpgradeWeapon_Point[playerid]);
            }
        }
    }
    return 1;
}

forward OnPlayerLoad_UpgradeFinish(playerid);
public OnPlayerLoad_UpgradeFinish(playerid){ //

    if(UnBorkenCardModel[playerid] != 18631){
        if(PlayerInventory_AllCount(playerid, "Unbroken Star") < 1) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
    }

    Can_CloseUpgradeFinish[playerid] = 1;

    new weaponmainid = Weapon_MainIndex[playerid];
    new weaponsecondid = Weapon_SecondIndex[playerid];

    LoadTextDraw_UpgradeWeaponSuc(playerid);
    for(new i=0; i<max_upgradetextdrawsuc; i++){
        PlayerTextDrawShow(playerid, UpgradeWeapon_TextDrawSuc[playerid][i]);
    }

    new string[128], query[128];

    //Fail
    if(Weapon_UpgradeStats[playerid] == 0){
        format(string, sizeof(string), "Upgrade Weapon > Fail");
        PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], string);

        PlayerTextDrawHide(playerid, UpgradeWeapon_TextDrawSuc[playerid][1]);
        PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 0xFF2424AA);
        PlayerTextDrawShow(playerid, UpgradeWeapon_TextDrawSuc[playerid][1]);

        PlayerTextDrawHide(playerid, UpgradeWeapon_TextDrawSuc[playerid][3]);
        PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], Weapon_MainModel[playerid]);
        PlayerTextDrawShow(playerid, UpgradeWeapon_TextDrawSuc[playerid][3]);

        format(string, sizeof(string), "%s", WeaponNameData[playerid][weaponMainName]);
        PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], string);

        format(string, sizeof(string), "Level: %d", Weapon_MainLevel[playerid]);
        PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], string);

        format(string, sizeof(string), "You're Fail Upgrade Weapon %s", WeaponNameData[playerid][weaponMainName]);
        PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], string);

        PlayerTextDrawHide(playerid, UpgradeWeapon_TextDrawSuc[playerid][7]);
        PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], Weapon_SecondModel[playerid]);
        PlayerTextDrawShow(playerid, UpgradeWeapon_TextDrawSuc[playerid][7]);

        if(UnBorkenCardModel[playerid] != 18631){
            if(UnBorkenCardIndex[playerid] != -1){    
                PlayerTextDrawHide(playerid, UpgradeWeapon_TextDrawSuc[playerid][9]);
                PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], UnBorkenCardModel[playerid]);
                PlayerTextDrawShow(playerid, UpgradeWeapon_TextDrawSuc[playerid][9]);

                format(string, sizeof(string), "UnBroken");
                PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], string);

                format(string, sizeof(string), "UnBroken Star (-1)");
                PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], string);
            }
        }
        else{
            format(string, sizeof(string), "%s Level: 0 (-1)", WeaponNameData[playerid][weaponSecondName]);
            PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], string);
        }

        PlayerData[playerid][pFailStack]++;
        SendClientMessageEx(playerid, COLOR_RED, "- คุณได้รับ FailStack + 1 รวมเป็น %d", PlayerData[playerid][pFailStack]);
    }
    //Successfully
    else if(Weapon_UpgradeStats[playerid] == 1){
        format(string, sizeof(string), "Upgrade Weapon > Successfully");
        PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], string);

        PlayerTextDrawHide(playerid, UpgradeWeapon_TextDrawSuc[playerid][1]);
        PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 0x4AFF29AA);
        PlayerTextDrawShow(playerid, UpgradeWeapon_TextDrawSuc[playerid][1]);

        PlayerTextDrawHide(playerid, UpgradeWeapon_TextDrawSuc[playerid][3]);
        PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], Weapon_MainModel[playerid]);
        PlayerTextDrawShow(playerid, UpgradeWeapon_TextDrawSuc[playerid][3]);

        format(string, sizeof(string), "%s", WeaponNameData[playerid][weaponMainName]);
        PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], string);

        Weapon_MainLevel[playerid] ++;

        format(string, sizeof(string), "ผู้เล่น %s ตีบวกอาวุธ '%s' ติด และมีระดับตีบวกเป็น: %d", ReturnRoleplayName(playerid), WeaponNameData[playerid][weaponMainName], Weapon_MainLevel[playerid]);
        SendAdminsMessage(1, COLOR_GRAY, string);

        format(string, sizeof(string), "Level: %d", Weapon_MainLevel[playerid]);
        PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], string);

        format(string, sizeof(string), "You got %s Level: %d", WeaponNameData[playerid][weaponMainName], Weapon_MainLevel[playerid]);
        PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], string);

        PlayerTextDrawHide(playerid, UpgradeWeapon_TextDrawSuc[playerid][7]);
        PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], Weapon_SecondModel[playerid]);
        PlayerTextDrawShow(playerid, UpgradeWeapon_TextDrawSuc[playerid][7]);

        format(string, sizeof(string), "%s Level: 0 (-1)", WeaponNameData[playerid][weaponSecondName]);
        PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], string);

        if(UnBorkenCardModel[playerid] != 18631){
            if(UnBorkenCardIndex[playerid] != -1){    
                PlayerTextDrawHide(playerid, UpgradeWeapon_TextDrawSuc[playerid][9]);
                PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], UnBorkenCardModel[playerid]);
                PlayerTextDrawShow(playerid, UpgradeWeapon_TextDrawSuc[playerid][9]);

                format(string, sizeof(string), "UnBroken Star (-1)");
                PlayerTextDrawSetString(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], string);
            }
        }

        PlayerData[playerid][pFailStack] = 0;

        //Add
        Inventory_Player[playerid][weaponmainid][itemLevel] = Weapon_MainLevel[playerid];
        mysql_format(dbCon, query, sizeof(query), "UPDATE `inventory` SET `itemLevel` = %d WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", Weapon_MainLevel[playerid], PlayerData[playerid][pID], Inventory_Player[playerid][weaponmainid][itemID]);
        mysql_tquery(dbCon, query);
        Log_Write("logs/addweaponupgrade.txt", "[%s] %s (Level: %d) Add to %s", ReturnDate(), Inventory_Player[playerid][weaponmainid][itemName], Weapon_MainLevel[playerid], ReturnRoleplayName(playerid));
    }

    if(Weapon_UpgradeStats[playerid] == 0){
        if(UnBorkenCardModel[playerid] != 18631){
            if(UnBorkenCardIndex[playerid] != -1){
                PlayerInventory_RemoveEx(playerid, UnBorkenCardIndex[playerid], 1);
                SendClientMessage(playerid, COLOR_RED, "- คุณได้เสีย 'ดาวกันแตก (Unbroken Star) -1");
                SendClientMessage(playerid, COLOR_YELLOW, "[การตีบวก]: เนื่องจากคุณใช้ดาวกันแตกทำให้อาวุธที่คุณนำมาตีไม่เสียหายหรือแตก");
            }
        }
        else{
            //Remove
            Inventory_Player[playerid][weaponsecondid][itemHave] = false;
            Inventory_Player[playerid][weaponsecondid][itemKey] = MODEL_NULL;
            Inventory_Player[playerid][weaponsecondid][itemQuantity] = 0;
            Inventory_Player[playerid][weaponsecondid][itemAmmo] = 0;
            Inventory_Player[playerid][weaponsecondid][itemLevel] = 0;
            format(Inventory_Player[playerid][weaponsecondid][itemName], 64, "NULL");

            mysql_format(dbCon, query, sizeof(query), "DELETE FROM `inventory` WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", PlayerData[playerid][pID], Inventory_Player[playerid][weaponsecondid][itemID]);
            mysql_tquery(dbCon, query);
            Log_Write("logs/removeweaponupgrade.txt", "[%s] %s Delete from %s", ReturnDate(), Inventory_Player[playerid][weaponsecondid][itemName], ReturnRoleplayName(playerid));
        }
    }
    else{

        if(UnBorkenCardModel[playerid] != 18631){
            if(UnBorkenCardIndex[playerid] != -1){
                PlayerInventory_RemoveEx(playerid, UnBorkenCardIndex[playerid], 1);
                SendClientMessage(playerid, COLOR_RED, "- คุณได้เสีย 'ดาวกันแตก (Unbroken Star) -1");
            }
        }

        //Remove
        Inventory_Player[playerid][weaponsecondid][itemHave] = false;
        Inventory_Player[playerid][weaponsecondid][itemKey] = MODEL_NULL;
        Inventory_Player[playerid][weaponsecondid][itemQuantity] = 0;
        Inventory_Player[playerid][weaponsecondid][itemAmmo] = 0;
        Inventory_Player[playerid][weaponsecondid][itemLevel] = 0;
        format(Inventory_Player[playerid][weaponsecondid][itemName], 64, "NULL");

        mysql_format(dbCon, query, sizeof(query), "DELETE FROM `inventory` WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", PlayerData[playerid][pID], Inventory_Player[playerid][weaponsecondid][itemID]);
        mysql_tquery(dbCon, query);
        Log_Write("logs/removeweaponupgrade.txt", "[%s] %s Delete from %s", ReturnDate(), Inventory_Player[playerid][weaponsecondid][itemName], ReturnRoleplayName(playerid));
    }

    SendClientMessageEx(playerid, COLOR_RED, "- คุณเสียเงิน %s ในการตีบวกครั้งนี้", FormatNumber(PRICE_UPGRADEWEAPON));
    GiveMoney(playerid, -PRICE_UPGRADEWEAPON, "upgrade weapon");

    SelectTextDraw(playerid, 0x33FFACAA);
    return 1;
}

OnPlayer_UpgradeWeaponFinish(playerid){
    new weaponmainid = Weapon_MainIndex[playerid];
    new weaponsecondid = Weapon_SecondIndex[playerid];

    if(weaponmainid > -1 && weaponsecondid > -1){
        for(new i=0; i<max_upgradetextdraw; i++){
            PlayerTextDrawHide(playerid, UpgradeWeapon_TextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, UpgradeWeapon_TextDraw[playerid][i]);
        }

        HidePlayerProgressBar(playerid, UpgradeWeapon_Bar[playerid][0]);
        DestroyPlayerProgressBar(playerid, UpgradeWeapon_Bar[playerid][0]);

        CancelSelectTextDraw(playerid);

        new Fail_Stack = PlayerData[playerid][pFailStack];

        new rands = random(1000);
        // 0 > 1

        if(Fail_Stack < 5){ // No Effect
            if(Weapon_MainLevel[playerid] == 0){ // 50%
                if(rands >= 50 && rands <= 150) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200 && rands <= 300) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 400 && rands <= 500) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 600 && rands <= 699) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 850 && rands <= 950) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 1 > 2
            if(Weapon_MainLevel[playerid] == 1){ // 45%
                if(rands >= 15 && rands <= 64) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 120 && rands <= 169) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 375 && rands <= 424) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 505 && rands <= 554) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 749 && rands <= 798) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 870 && rands <= 919) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 975 && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 2 > 3
            if(Weapon_MainLevel[playerid] == 2){ // 35%
                if(rands >= 0 && rands <= 34-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 110 && rands <= 129-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200 && rands <= 219-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 325 && rands <= 344-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 400 && rands <= 419-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 630 && rands <= 645-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 710 && rands <= 744-15-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 966+15+10 && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 3 > 4
            if(Weapon_MainLevel[playerid] == 3){ // 25%
                if(rands >= 0 && rands <= 24) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 75 && rands <= 99) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 170 && rands <= 194) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 300 && rands <= 324) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 460 && rands <= 479) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 563 && rands <= 584) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 700 && rands <= 724) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 976 && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 4 > 5
            if(Weapon_MainLevel[playerid] == 4){ // 15%
                if(rands >= 0 && rands <= 14) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 70 && rands <= 84) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200 && rands <= 214) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 265 && rands <= 279) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 380 && rands <= 394) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 470 && rands <= 484) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 700 && rands <= 714) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 850 && rands <= 864) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 986 && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }
        }
        else if(Fail_Stack >= 5 && Fail_Stack <= 9){ // + 5%
            new effectpersent = 10;
            if(Weapon_MainLevel[playerid] == 0){ // 50%
                if(rands >= 50-effectpersent && rands <= 150) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200-effectpersent && rands <= 300) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 400-effectpersent && rands <= 500) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 600-effectpersent && rands <= 699) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 850-effectpersent && rands <= 950) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 1 > 2
            if(Weapon_MainLevel[playerid] == 1){ // 45%
                if(rands >= 15-effectpersent && rands <= 64) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 120-effectpersent && rands <= 169) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 375-effectpersent && rands <= 424) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 505 && rands <= 554) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 749-effectpersent && rands <= 798) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 870 && rands <= 919) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 975-effectpersent && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 2 > 3
            if(Weapon_MainLevel[playerid] == 2){ // 35%
                if(rands >= 0 && rands <= 34-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 110-effectpersent && rands <= 129-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200-effectpersent && rands <= 219-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 325 && rands <= 344-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 400-effectpersent && rands <= 419-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 630 && rands <= 645-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 710-effectpersent && rands <= 744-15-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 966+15+10-effectpersent && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 3 > 4
            if(Weapon_MainLevel[playerid] == 3){ // 25%
                if(rands >= 0 && rands <= 24) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 75-effectpersent && rands <= 99) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 170-effectpersent && rands <= 194) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 300 && rands <= 324) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 460-effectpersent && rands <= 479) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 563 && rands <= 584) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 700-effectpersent && rands <= 724) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 976-effectpersent && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 4 > 5
            if(Weapon_MainLevel[playerid] == 4){ // 15%
                if(rands >= 0 && rands <= 14) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 70-effectpersent && rands <= 84) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200-effectpersent && rands <= 214) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 265 && rands <= 279) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 380-effectpersent && rands <= 394) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 470 && rands <= 484) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 700-effectpersent && rands <= 714) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 850 && rands <= 864) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 986-effectpersent && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }
        }
        else if(Fail_Stack >= 10 && Fail_Stack <= 14){ // + 7%
            new effectpersent = 35;
            if(Weapon_MainLevel[playerid] == 0){ // 50%
                if(rands >= 50 && rands <= 150) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200-effectpersent && rands <= 300) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 400 && rands <= 500) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 600-effectpersent && rands <= 699) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 850 && rands <= 950) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 1 > 2
            if(Weapon_MainLevel[playerid] == 1){ // 45%
                if(rands >= 15 && rands <= 64) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 120-effectpersent && rands <= 169) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 375 && rands <= 424) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 505 && rands <= 554) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 749 && rands <= 798) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 870 && rands <= 919) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 975-effectpersent && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 2 > 3
            if(Weapon_MainLevel[playerid] == 2){ // 35%
                if(rands >= 0 && rands <= 34-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 110-effectpersent && rands <= 129-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200 && rands <= 219-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 325 && rands <= 344-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 400 && rands <= 419-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 630-effectpersent && rands <= 645-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 710 && rands <= 744-15-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 966+15+10 && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 3 > 4
            if(Weapon_MainLevel[playerid] == 3){ // 25%
                if(rands >= 0 && rands <= 24) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 75 && rands <= 99) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 170 && rands <= 194) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 300 && rands <= 324) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 460-effectpersent && rands <= 479) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 563 && rands <= 584) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 700 && rands <= 724) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 976-effectpersent && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 4 > 5
            if(Weapon_MainLevel[playerid] == 4){ // 15%
                if(rands >= 0 && rands <= 14) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 70-effectpersent && rands <= 84) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200 && rands <= 214) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 265 && rands <= 279) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 380 && rands <= 394) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 470 && rands <= 484) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 700-effectpersent && rands <= 714) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 850 && rands <= 864) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 986 && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }
        }
        else if(Fail_Stack >= 15){ // + 10%
            new effectpersent = 20;
            if(Weapon_MainLevel[playerid] == 0){ // 50%
                if(rands >= 50-effectpersent && rands <= 150) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200-effectpersent && rands <= 300) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 400-effectpersent && rands <= 500) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 600-effectpersent && rands <= 699) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 850-effectpersent && rands <= 950) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 1 > 2
            if(Weapon_MainLevel[playerid] == 1){ // 45%
                if(rands >= 15 && rands <= 64) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 120-effectpersent && rands <= 169) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 375-effectpersent && rands <= 424) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 505-effectpersent && rands <= 554) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 749 && rands <= 798) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 870-effectpersent && rands <= 919) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 975-effectpersent && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 2 > 3
            if(Weapon_MainLevel[playerid] == 2){ // 35%
                if(rands >= 0 && rands <= 34-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 110-effectpersent && rands <= 129-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200-effectpersent && rands <= 219-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 325 && rands <= 344-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 400-effectpersent && rands <= 419-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 630-effectpersent && rands <= 645-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 710 && rands <= 744-15-10) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 966+15+10-effectpersent && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 3 > 4
            if(Weapon_MainLevel[playerid] == 3){ // 25%
                if(rands >= 0 && rands <= 24) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 75-effectpersent && rands <= 99) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 170 && rands <= 194) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 300-effectpersent && rands <= 324) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 460-effectpersent && rands <= 479) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 563-effectpersent && rands <= 584) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 700-effectpersent && rands <= 724) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 976 && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }

            // 4 > 5
            if(Weapon_MainLevel[playerid] == 4){ // 15%
                if(rands >= 0 && rands <= 14) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 70 && rands <= 84) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 200-effectpersent && rands <= 214) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 265-effectpersent && rands <= 279) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 380-effectpersent && rands <= 394) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 470 && rands <= 484) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 700-effectpersent && rands <= 714) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 850 && rands <= 864) Weapon_UpgradeStats[playerid] = true;
                else if(rands >= 986-effectpersent && rands <= 1000) Weapon_UpgradeStats[playerid] = true;
                else Weapon_UpgradeStats[playerid] = false;
            }
        }

        SetTimerEx("OnPlayerLoad_UpgradeFinish", 500, false, "i", playerid);
    }
    else{
        ErrorMsg(playerid, "เกิดข้อผิดพลาด");
        OnPlayer_UpgradeWeaponHide(playerid);
        return 1;
    }
    return 1;
}

OnPlayerHide_TextDrawUpgradeSuc(playerid){
    for(new i=0; i<max_upgradetextdrawsuc; i++){
        PlayerTextDrawHide(playerid, UpgradeWeapon_TextDrawSuc[playerid][i]);
        PlayerTextDrawDestroy(playerid, UpgradeWeapon_TextDrawSuc[playerid][i]);
    }
    
    Reset_PlayerUpgradeWeapon(playerid);
    CancelSelectTextDraw(playerid);
    TogglePlayerControllable(playerid, 1);
    return 1;
}

LoadTextDraw_UpgradeWeaponSuc(playerid){
    UpgradeWeapon_TextDrawSuc[playerid][0] = CreatePlayerTextDraw(playerid, 320.000000, 122.000000, "_");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], 0.600000, 25.800003);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], 298.500000, 235.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], 200);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][0], 0);

    UpgradeWeapon_TextDrawSuc[playerid][1] = CreatePlayerTextDraw(playerid, 320.000000, 122.000000, "_");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 0.600000, 1.800003);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 298.500000, 235.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 9109704);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][1], 0);

    UpgradeWeapon_TextDrawSuc[playerid][2] = CreatePlayerTextDraw(playerid, 206.000000, 121.000000, "Upgrade Weapon Successfully");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], 0.287500, 1.900000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], 510.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], 1);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][2], 0);

    UpgradeWeapon_TextDrawSuc[playerid][3] = CreatePlayerTextDraw(playerid, 276.000000, 149.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 5);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 87.000000, 94.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 1);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], -1094795686);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 255);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 339);
    PlayerTextDrawSetPreviewRot(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 26.000000, 37.000000, 10.000000, 1.770000);
    PlayerTextDrawSetPreviewVehCol(playerid, UpgradeWeapon_TextDrawSuc[playerid][3], 1, 1);

    UpgradeWeapon_TextDrawSuc[playerid][4] = CreatePlayerTextDraw(playerid, 319.000000, 249.000000, "Katana");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], 0.312500, 1.550000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], 400.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], -1094795726);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][4], 0);

    UpgradeWeapon_TextDrawSuc[playerid][5] = CreatePlayerTextDraw(playerid, 319.000000, 270.000000, "LEVEL: 1");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], 0.312500, 1.550000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], 400.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], -1094795726);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][5], 0);

    UpgradeWeapon_TextDrawSuc[playerid][6] = CreatePlayerTextDraw(playerid, 320.000000, 291.000000, "You Got Katana +1");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], 0.183333, 1.250000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], 400.000000, 227.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], -1094795726);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][6], 0);

    UpgradeWeapon_TextDrawSuc[playerid][7] = CreatePlayerTextDraw(playerid, 384.000000, 149.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 5);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 33.500000, 36.500000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 1);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], -1094795686);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 255);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 0);
    PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 339);
    PlayerTextDrawSetPreviewRot(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 26.000000, 37.000000, 10.000000, 1.770000);
    PlayerTextDrawSetPreviewVehCol(playerid, UpgradeWeapon_TextDrawSuc[playerid][7], 1, 1);

    UpgradeWeapon_TextDrawSuc[playerid][8] = CreatePlayerTextDraw(playerid, 401.000000, 189.000000, "Baseball bat Level:0 (-1)");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], 0.116666, 0.800000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], 400.000000, 63.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], -1094795726);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][8], 0);

    UpgradeWeapon_TextDrawSuc[playerid][9] = CreatePlayerTextDraw(playerid, 221.000000, 149.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 5);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 33.500000, 36.500000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 1);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], -1094795686);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 255);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 0);
    PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 18631);
    PlayerTextDrawSetPreviewRot(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 26.000000, 37.000000, 10.000000, 1.770000);
    PlayerTextDrawSetPreviewVehCol(playerid, UpgradeWeapon_TextDrawSuc[playerid][9], 1, 1);

    UpgradeWeapon_TextDrawSuc[playerid][10] = CreatePlayerTextDraw(playerid, 238.000000, 189.000000, "UnBorken Card (0)");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], 0.116666, 0.800000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], 400.000000, 63.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], -1094795726);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][10], 0);

    UpgradeWeapon_TextDrawSuc[playerid][11] = CreatePlayerTextDraw(playerid, 319.000000, 323.000000, "Close");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], 0.258332, 1.750000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], 16.500000, 90.500000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], -1094795716);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDrawSuc[playerid][11], 1);
    return 1;
}

LoadTextDraw_UpgradeWeapon(playerid){
    UpgradeWeapon_TextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 315.000000, 106.000000, "_");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][0], 0.683333, 30.550014);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][0], 308.500000, 415.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][0], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][0], 190);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][0], 0);

    UpgradeWeapon_TextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 315.000000, 106.000000, "_");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][1], 0.683333, 1.850015);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][1], 308.500000, 415.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][1], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][1], -1962934082);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][1], 0);

    UpgradeWeapon_TextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 129.000000, 105.000000, "UPGRADE WEAPON");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][2], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][2], 0.275000, 1.750000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][2], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][2], 1);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][2], 0);

    UpgradeWeapon_TextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 112.000000, 108.000000, "HUD:radar_race");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][3], 4);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][3], 11.000000, 11.500000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][3], 1);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][3], 0);

    UpgradeWeapon_TextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 508.000000, 108.000000, "ld_chat:thumbdn");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][4], 4);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][4], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][4], 11.000000, 11.500000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][4], 1);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][4], 1);

    UpgradeWeapon_TextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 132.000000, 150.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][5], 5);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][5], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][5], 87.500000, 95.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][5], 1);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][5], -1094795731);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][5], 255);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][5], 1);
    PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDraw[playerid][5], 18631);
    PlayerTextDrawSetPreviewRot(playerid, UpgradeWeapon_TextDraw[playerid][5], 11.000000, 51.000000, -5.000000, 2.399999);
    PlayerTextDrawSetPreviewVehCol(playerid, UpgradeWeapon_TextDraw[playerid][5], 1, 1);

    UpgradeWeapon_TextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 175.000000, 250.000000, "Pool Cue");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][6], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][6], 0.200000, 1.300004);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][6], 298.500000, 84.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][6], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][6], -1094795731);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][6], 0);

    UpgradeWeapon_TextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 175.000000, 268.000000, "LEVEL: 5");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][7], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][7], 0.200000, 1.300004);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][7], 298.500000, 84.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][7], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][7], -1094795731);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][7], 0);

    UpgradeWeapon_TextDraw[playerid][8] = CreatePlayerTextDraw(playerid, 318.000000, 188.000000, "+");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][8], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][8], 0.650000, 2.800004);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][8], 298.500000, 84.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][8], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][8], -1094795731);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][8], 0);

    UpgradeWeapon_TextDraw[playerid][9] = CreatePlayerTextDraw(playerid, 411.000000, 150.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][9], 5);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][9], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][9], 87.500000, 95.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][9], 1);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][9], -1094795731);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][9], 255);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][9], 1);
    PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDraw[playerid][9], 18631);
    PlayerTextDrawSetPreviewRot(playerid, UpgradeWeapon_TextDraw[playerid][9], 11.000000, 51.000000, -5.000000, 2.399999);
    PlayerTextDrawSetPreviewVehCol(playerid, UpgradeWeapon_TextDraw[playerid][9], 1, 1);

    UpgradeWeapon_TextDraw[playerid][10] = CreatePlayerTextDraw(playerid, 455.000000, 250.000000, "Pool Cue");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][10], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][10], 0.200000, 1.300004);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][10], 298.500000, 84.500000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][10], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][10], -1094795731);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][10], 0);

    UpgradeWeapon_TextDraw[playerid][11] = CreatePlayerTextDraw(playerid, 455.000000, 268.000000, "LEVEL: 5");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][11], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][11], 0.200000, 1.300004);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][11], 298.500000, 84.500000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][11], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][11], -1094795731);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][11], 0);

    UpgradeWeapon_TextDraw[playerid][12] = CreatePlayerTextDraw(playerid, 301.000000, 218.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][12], 5);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][12], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][12], 32.000000, 33.500000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][12], 1);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][12], -1094795731);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][12], 255);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][12], 1);
    PlayerTextDrawSetPreviewModel(playerid, UpgradeWeapon_TextDraw[playerid][12], 18631);
    PlayerTextDrawSetPreviewRot(playerid, UpgradeWeapon_TextDraw[playerid][12], 11.000000, 51.000000, -5.000000, 1.300000);
    PlayerTextDrawSetPreviewVehCol(playerid, UpgradeWeapon_TextDraw[playerid][12], 1, 1);

    UpgradeWeapon_TextDraw[playerid][13] = CreatePlayerTextDraw(playerid, 317.000000, 256.000000, "Add-On");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][13], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][13], 0.187500, 1.100004);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][13], 298.500000, 59.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][13], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][13], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][13], -1094795731);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][13], 0);

    UpgradeWeapon_TextDraw[playerid][14] = CreatePlayerTextDraw(playerid, 315.000000, 152.000000, "Fail Stack: 10");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][14], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][14], 0.187500, 1.100004);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][14], 298.500000, 159.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][14], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][14], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][14], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][14], -1094795731);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][14], 0);

    UpgradeWeapon_TextDraw[playerid][15] = CreatePlayerTextDraw(playerid, 316.000000, 295.000000, "NOT READY");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][15], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][15], 0.350000, 2.200004);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][15], 298.500000, 159.000000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][15], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][15], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][15], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][15], -16776961);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][15], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][15], -1094795731);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][15], 0);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][15], 0);

    UpgradeWeapon_TextDraw[playerid][16] = CreatePlayerTextDraw(playerid, 315.000000, 348.000000, "START");
    PlayerTextDrawFont(playerid, UpgradeWeapon_TextDraw[playerid][16], 2);
    PlayerTextDrawLetterSize(playerid, UpgradeWeapon_TextDraw[playerid][16], 0.258332, 1.750000);
    PlayerTextDrawTextSize(playerid, UpgradeWeapon_TextDraw[playerid][16], 16.500000, 90.500000);
    PlayerTextDrawSetOutline(playerid, UpgradeWeapon_TextDraw[playerid][16], 0);
    PlayerTextDrawSetShadow(playerid, UpgradeWeapon_TextDraw[playerid][16], 0);
    PlayerTextDrawAlignment(playerid, UpgradeWeapon_TextDraw[playerid][16], 2);
    PlayerTextDrawColor(playerid, UpgradeWeapon_TextDraw[playerid][16], -1);
    PlayerTextDrawBackgroundColor(playerid, UpgradeWeapon_TextDraw[playerid][16], 255);
    PlayerTextDrawBoxColor(playerid, UpgradeWeapon_TextDraw[playerid][16], -1094795731);
    PlayerTextDrawUseBox(playerid, UpgradeWeapon_TextDraw[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, UpgradeWeapon_TextDraw[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, UpgradeWeapon_TextDraw[playerid][16], 1);

    UpgradeWeapon_Bar[playerid][0] = CreatePlayerProgressBar(playerid, 132.000000, 326.000000, 372.000000, 4.000000, -8388353, 100.000000, 0);
    return 1;
}