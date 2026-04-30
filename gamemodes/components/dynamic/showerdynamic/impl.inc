#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

forward Shower_Load();
public Shower_Load(){
    new rows;
    cache_get_row_count(rows);
    for (new i = 0; i < rows; i ++) if (i < MAX_SHOWER){
        cache_get_value_name_int(i, "showerID", ShowerData[i][showerID]);
        cache_get_value_name_float(i, "showerPosX", ShowerData[i][showerPos][0]);
        cache_get_value_name_float(i, "showerPosY", ShowerData[i][showerPos][1]);
        cache_get_value_name_float(i, "showerPosZ", ShowerData[i][showerPos][2]);
        cache_get_value_name_int(i, "showerInterior", ShowerData[i][showerInterior]);
        cache_get_value_name_int(i, "showerWorld", ShowerData[i][showerWorld]);

        Iter_Add(Iter_Shower, i);

        ShowerData[i][showerPickup] = CreateDynamicPickup(1275, 23, ShowerData[i][showerPos][0], ShowerData[i][showerPos][1], ShowerData[i][showerPos][2], ShowerData[i][showerWorld], ShowerData[i][showerInterior]);
        ShowerData[i][showerText3D] = CreateDynamic3DTextLabel("[จุดอาบน้ำ]\nกด 'Y' เพื่ออาบน้ำ", COLOR_YELLOW, ShowerData[i][showerPos][0], ShowerData[i][showerPos][1], ShowerData[i][showerPos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, ShowerData[i][showerWorld], ShowerData[i][showerInterior]);
    }
    printf("(( [MYSQL]: Load %d Showers Successfully ))", Iter_Count(Iter_Shower));
    return 1;
}

Shower_Create(playerid){
    new showerid = -1;
    if(( showerid = Iter_Free(Iter_Shower)) != -1){
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        ShowerData[showerid][showerPos][0] = x;
        ShowerData[showerid][showerPos][1] = y;
        ShowerData[showerid][showerPos][2] = z;
        ShowerData[showerid][showerInterior] = GetPlayerInterior(playerid);
        ShowerData[showerid][showerWorld] = GetPlayerVirtualWorld(playerid);

        ShowerData[showerid][showerPickup] = CreateDynamicPickup(1275, 23, ShowerData[showerid][showerPos][0], ShowerData[showerid][showerPos][1], ShowerData[showerid][showerPos][2], ShowerData[showerid][showerWorld], ShowerData[showerid][showerInterior]);
        ShowerData[showerid][showerText3D] = CreateDynamic3DTextLabel("[จุดอาบน้ำ]\nกด 'Y' เพื่ออาบน้ำ", COLOR_YELLOW, ShowerData[showerid][showerPos][0], ShowerData[showerid][showerPos][1], ShowerData[showerid][showerPos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, ShowerData[showerid][showerWorld], ShowerData[showerid][showerInterior]);
    
        new query[256];
        mysql_format(dbCon, query, sizeof query, "INSERT INTO `showers` (`showerPosX`, `showerPosY`, `showerPosZ`, `showerInterior`, `showerWorld`) VALUES(%f, %f, %f, %d, %d)", x, y, z, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
		mysql_tquery(dbCon, query, "OnShowerCreated", "ii", playerid, showerid);
        return showerid;
    }
    return -1;
}

forward OnShowerCreated(playerid, showerid);
public OnShowerCreated(playerid, showerid){
	new insert_id = cache_insert_id();
	if(insert_id) {
        new string[128];
		Iter_Add(Iter_Shower, showerid);
		ShowerData[showerid][showerID] = insert_id;
		format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการสร้างจุดอาบน้ำไอดี %d (ShowerID: %d) เรียบร้อยแล้ว", ReturnRoleplayName(playerid), showerid, ShowerData[showerid][showerID]);
        SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else {
		if(IsValidDynamicPickup(ShowerData[showerid][showerPickup]))
			DestroyDynamicPickup(ShowerData[showerid][showerPickup]);

        if(IsValidDynamic3DTextLabel(ShowerData[showerid][showerText3D]))
            DestroyDynamic3DTextLabel(ShowerData[showerid][showerText3D]);

		SendClientMessage(playerid, -1, "[!] ไม่สามารถสร้างจุดอาบน้ำได้โปรดติดต่อผู้ดูแลระบบ");
	}
	return 1;
}

Shower_Remove(showerid){
    if(showerid != -1 && Iter_Contains(Iter_Shower, showerid)){
        new query[128];
        format(query, sizeof(query), "DELETE FROM `showers` WHERE `showerID` = '%d' LIMIT 1", ShowerData[showerid][showerID]);
		mysql_tquery(dbCon, query);

        ShowerData[showerid][showerID] = 0;
        ShowerData[showerid][showerPos][0] = 0;
        ShowerData[showerid][showerPos][1] = 0;
        ShowerData[showerid][showerPos][2] = 0;
        ShowerData[showerid][showerInterior] = 0;
        ShowerData[showerid][showerWorld] = 0;

        if(IsValidDynamic3DTextLabel(ShowerData[showerid][showerText3D]))
            DestroyDynamic3DTextLabel(ShowerData[showerid][showerText3D]);

        if(IsValidDynamicPickup(ShowerData[showerid][showerPickup]))
            DestroyDynamicPickup(ShowerData[showerid][showerPickup]);

        Iter_Remove(Iter_Shower, showerid);

        return showerid;
    }
    return -1;
}

Shower_Refresh(showerid){
    if(showerid != -1 && Iter_Contains(Iter_Shower, showerid)){
        if(IsValidDynamic3DTextLabel(ShowerData[showerid][showerText3D]))
            DestroyDynamic3DTextLabel(ShowerData[showerid][showerText3D]);

        if(IsValidDynamicPickup(ShowerData[showerid][showerPickup]))
            DestroyDynamicPickup(ShowerData[showerid][showerPickup]);

        ShowerData[showerid][showerPickup] = CreateDynamicPickup(1275, 23, ShowerData[showerid][showerPos][0], ShowerData[showerid][showerPos][1], ShowerData[showerid][showerPos][2], ShowerData[showerid][showerWorld], ShowerData[showerid][showerInterior]);
        ShowerData[showerid][showerText3D] = CreateDynamic3DTextLabel("[จุดอาบน้ำ]\nกด 'Y' เพื่ออาบน้ำ", COLOR_YELLOW, ShowerData[showerid][showerPos][0], ShowerData[showerid][showerPos][1], ShowerData[showerid][showerPos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, ShowerData[showerid][showerWorld], ShowerData[showerid][showerInterior]);
    }   
    return 1;
}

Shower_Save(showerid){
    if(showerid != -1 && Iter_Contains(Iter_Shower, showerid)){
        new query[1024];
        format(query, sizeof(query), "UPDATE `showers` SET `showerPosX` = '%.4f', `showerPosY` = '%.4f', `showerPosZ` = '%.4f', `showerInterior` = '%d', `showerWorld` = '%d' WHERE `showerID` = '%d'",
            ShowerData[showerid][showerPos][0],
            ShowerData[showerid][showerPos][1],
            ShowerData[showerid][showerPos][2],
            ShowerData[showerid][showerInterior],
            ShowerData[showerid][showerWorld],
            ShowerData[showerid][showerID]
        );
        return mysql_tquery(dbCon, query);
    }
    return 1;
}

Shower_Nearest(playerid, Float:radius = 3.5)
{
    for (new i = 0; i != MAX_SHOWER; i ++) if (Iter_Contains(Iter_Shower, i) && IsPlayerInRangeOfPoint(playerid, radius, ShowerData[i][showerPos][0], ShowerData[i][showerPos][1], ShowerData[i][showerPos][2]) && GetPlayerInterior(playerid) == ShowerData[i][showerInterior] && GetPlayerVirtualWorld(playerid) == ShowerData[i][showerWorld]) {
		return i;
	}
	return -1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(!LoggedIn[playerid]) return 1;

    if(newkeys & KEY_YES){
        if(Shower_Nearest(playerid) != -1){
            SetPlayerShower(playerid);
        }
    }

    return 1;
}

ResetPlayerShow(playerid){
    stop PlayerShower[playerid];
    PlayerStartShower[playerid] = false;
    return 1;
}

timer UpdateShower[100](playerid){
    if(PlayerStartShower[playerid]){
        new Float:currentValueMine = GetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0]);
        if(currentValueMine < 100.0){
            currentValueMine++;
            SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], currentValueMine);
        }
        else{
            Shower_Finish(playerid);
        }
    }
    return 1;
}

Shower_Finish(playerid){
    stop PlayerShower[playerid];
    PlayerStartShower[playerid] = false;
    TogglePlayerControllable(playerid, 1);
    ClearAnimations(playerid);
    SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], 0.0);
    HidePlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    PlayerTextDrawHide(playerid, NewProgressText[playerid][0]);
    DestroyPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    PlayerTextDrawDestroy(playerid, NewProgressText[playerid][0]);
    RemoveAttachedObject(playerid, 9);
    PlayerData[playerid][pShower] = 0;
    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การอาบน้ำ", "คุณได้อาบน้ำทำความสะอาดตัวเรียบร้อยแล้ว", "ตกลง", "");
    return 1;
}

SetPlayerShower(playerid){
    if(PlayerStartShower[playerid]) return 1;
    if(PlayerData[playerid][pShower] <= 20) return ErrorMsg(playerid, "คุณยังไม่จำเป็นต้องอาบน้ำ");
    TogglePlayerControllable(playerid, 0);
    LoadPlayerNewProgress(playerid);
    ShowPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    SetPlayerProgressBarColour(playerid, NewProgressBar[playerid][0], 0x009BFFAA);
    SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], 0.0);
    PlayerTextDrawShow(playerid, NewProgressText[playerid][0]);
    PlayerTextDrawSetString(playerid, NewProgressText[playerid][0], "Showering...");
    SetPlayerAttachedObject(playerid,9,18720,1,0.716000,0.000000,-1.504000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
    PlayerStartShower[playerid] = true;
    PlayerShower[playerid] = repeat UpdateShower(playerid);
    return 1;
}

CMD:showercmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1338)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[SHOWERCMDS]: /makeshower, /removeshower, /editshower");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
    return 1;
}

CMD:makeshower(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new id = Shower_Create(playerid);
    if(id == -1) return ErrorMsg(playerid, "เซิฟเวอร์ได้สร้างจุดอาบน้ำเกินขีดจำกัดแล้ว");
    return 1;
}

CMD:removeshower(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new string[128], showerid = -1;
    if(sscanf(params, "d", showerid)) return SystemMsg(playerid, "/removeshower [showerid]");
    if(showerid <= -1 || showerid > MAX_SHOWER) return ErrorMsg(playerid, "คุณกรอกไอดีจุดอาบน้ำไม่ถูกต้อง");
    if(!Iter_Contains(Iter_Shower, showerid)) return ErrorMsg(playerid, "ไอดีจุดอาบน้ำไม่ถูกต้อง");
    format(string, sizeof(string), "ผู้ดูแล %s ได้การทำลบจุดอาบน้ำ %d (ShowerID: %d) เรียบร้อยแล้ว", ReturnRoleplayName(playerid), showerid, ShowerData[showerid][showerID]);
    SendAdminsMessage(1, COLOR_GRAY, string);
    Shower_Remove(showerid);
    return 1;
}

CMD:editshower(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new string[128], showerid = -1, type[24];
    if (sscanf(params, "ds[24]S()[128]", showerid, type, string)){
		SystemMsg(playerid, "/editshower [id] [type]");
		SystemMsg(playerid, "[ตัวเลือก]:{FFFFFF} location");
		return 1;
	}
    if(showerid <= -1 || showerid > MAX_SHOWER) return ErrorMsg(playerid, "คุณกรอกไอดีจุดอาบน้ำไม่ถูกต้อง");
    if(!Iter_Contains(Iter_Shower, showerid)) return ErrorMsg(playerid, "ไอดีจุดอาบน้ำไม่ถูกต้อง");

    if(!strcmp(type, "location", true)){
		GetPlayerPos(playerid, ShowerData[showerid][showerPos][0], ShowerData[showerid][showerPos][1], ShowerData[showerid][showerPos][2]);

		ShowerData[showerid][showerInterior] = GetPlayerInterior(playerid);
		ShowerData[showerid][showerWorld] = GetPlayerVirtualWorld(playerid);

		Shower_Save(showerid);
        Shower_Refresh(showerid);

        format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับตำแหน่งจุดอาบน้ำไอดี %d (showerID: %d) เรียบร้อยแล้ว", ReturnRoleplayName(playerid), showerid, ShowerData[showerid][showerID]);
        SendAdminsMessage(1, COLOR_GRAY, string);
	}
    return 1;
}