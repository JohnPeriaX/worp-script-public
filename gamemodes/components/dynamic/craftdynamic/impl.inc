#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
	if(LoggedIn[playerid]){
		if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
			new id = -1;
			if ((id = Craft_Nearest(playerid)) != -1){
				//คราฟเมนู
				OnPlayerCreateCraftMenu(playerid, CraftData[id][craftType]);
			}
		}
	}
	return true;
}



forward Craft_Load();
public Craft_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_CRAFT_DYNAMIC){
	    CraftData[i][craftExists] = true;

	    cache_get_value_name_int(i, "craftID", CraftData[i][craftID]);
	    cache_get_value_name_float(i, "craftPosX", CraftData[i][craftPos][0]);
	    cache_get_value_name_float(i, "craftPosY", CraftData[i][craftPos][1]);
	    cache_get_value_name_float(i, "craftPosZ", CraftData[i][craftPos][2]);
	    cache_get_value_name_int(i, "craftInt", CraftData[i][craftInt]);
	    cache_get_value_name_int(i, "craftWorld", CraftData[i][craftWorld]);
		cache_get_value_name_int(i, "craftType", CraftData[i][craftType]);

        Craft_Count++;

 	    Craft_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d Craft Successfully ))", Craft_Count);
	return 1;
}

Craft_Refresh(craftid)
{
	if (craftid != -1 && CraftData[craftid][craftExists])
	{
        if (IsValidDynamic3DTextLabel(CraftData[craftid][craftText3D]))
            DestroyDynamic3DTextLabel(CraftData[craftid][craftText3D]);

        if (IsValidDynamicPickup(CraftData[craftid][craftPickup]))
            DestroyDynamicPickup(CraftData[craftid][craftPickup]);

		new
		    string[128];

		format(string, sizeof(string), "[จุดสำหรับคราฟไอเท็ม]\nกดปุ่ม 'Y' เพื่อใช้งาน");

		CraftData[craftid][craftText3D] = CreateDynamic3DTextLabel(string, 0xFF9B00FF, CraftData[craftid][craftPos][0], CraftData[craftid][craftPos][1], CraftData[craftid][craftPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, CraftData[craftid][craftWorld], CraftData[craftid][craftInt]);
	    CraftData[craftid][craftPickup] = CreateDynamicPickup(1318, 23, CraftData[craftid][craftPos][0], CraftData[craftid][craftPos][1], CraftData[craftid][craftPos][2], CraftData[craftid][craftWorld], CraftData[craftid][craftInt]);
	}
	return 1;
}

Craft_Delete(craftid)
{
	if (craftid != -1 && CraftData[craftid][craftExists])
	{
	    new
	        string[64];

        Craft_Count--;

		format(string, sizeof(string), "DELETE FROM `crafts` WHERE `craftID` = '%d' LIMIT 1", CraftData[craftid][craftID]);
		mysql_tquery(dbCon, string);

        if (IsValidDynamic3DTextLabel(CraftData[craftid][craftText3D]))
            DestroyDynamic3DTextLabel(CraftData[craftid][craftText3D]);

        if (IsValidDynamicPickup(CraftData[craftid][craftPickup]))
            DestroyDynamicPickup(CraftData[craftid][craftPickup]);

		CraftData[craftid][craftExists] = false;
	    CraftData[craftid][craftID] = 0;
	}
	return 1;
}

Craft_Save(craftid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `crafts` SET `craftPosX` = '%.4f', `craftPosY` = '%.4f', `craftPosZ` = '%.4f', `craftInt` = '%d', `craftWorld` = '%d', `craftType` = '%d' WHERE `craftID` = '%d'",
		CraftData[craftid][craftPos][0],
	    CraftData[craftid][craftPos][1],
	    CraftData[craftid][craftPos][2],
	    CraftData[craftid][craftInt],
	    CraftData[craftid][craftWorld],
		CraftData[craftid][craftType],
        CraftData[craftid][craftID]
	);

	return mysql_tquery(dbCon, query);
}

Craft_Create(playerid, type){
	new
	    Float:x,
	    Float:y,
	    Float:z;

	if (GetPlayerPos(playerid, x, y, z)){
		for (new i = 0; i != MAX_CRAFT_DYNAMIC; i ++){
	    	if (!CraftData[i][craftExists]){
	        	CraftData[i][craftExists] = true;

				CraftData[i][craftPos][0] = x;
	        	CraftData[i][craftPos][1] = y;
	        	CraftData[i][craftPos][2] = z;
				CraftData[i][craftType] = type;

	        	CraftData[i][craftInt] = GetPlayerInterior(playerid);
	        	CraftData[i][craftWorld] = GetPlayerVirtualWorld(playerid);

	        	Craft_Refresh(i);
	        	mysql_tquery(dbCon, "INSERT INTO `crafts` (`craftInt`) VALUES(0)", "OnCraftCreated", "d", i);
	        	return i;
	        }
	    }
	}
	return -1;
}

forward OnCraftCreated(craftid);
public OnCraftCreated(craftid){
	if (craftid == -1 || !CraftData[craftid][craftExists])
	    return 0;

	CraftData[craftid][craftID] = cache_insert_id();
	Craft_Save(craftid);

	return 1;
}

Craft_Nearest(playerid){
    for (new i = 0; i != MAX_CRAFT_DYNAMIC; i ++) if (CraftData[i][craftExists] && IsPlayerInRangeOfPoint(playerid, 3.0, CraftData[i][craftPos][0], CraftData[i][craftPos][1], CraftData[i][craftPos][2]))
	{
		if (GetPlayerInterior(playerid) == CraftData[i][craftInt] && GetPlayerVirtualWorld(playerid) == CraftData[i][craftWorld])
			return i;
	}
	return -1;
}

CMD:craftcmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1338)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[CRAFTCMDS]: /makecraft, /removecraft, /editcraft");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
    return 1;
}

CMD:gotocraft(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	new
		id;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/gotocraft [craft ID]");

	if ((id < 0 || id >= MAX_CRAFT_DYNAMIC) || !CraftData[id][craftExists])
		return SendClientMessage(playerid, -1, "คุณระบุ Craft ID ไม่ถูกต้อง");

	SetPlayerPosEx(playerid, CraftData[id][craftPos][0], CraftData[id][craftPos][1], CraftData[id][craftPos][2], CraftData[id][craftInt], CraftData[id][craftWorld]);
	SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ Craft ID: %d", id);
	return 1;
}

CMD:makecraft(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
    new
		id = -1,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	new type;
	if(sscanf(params, "d", type)) {
		SystemMsg(playerid, "[Types]: 0: ไอเท็มทั่วไป");
		return SystemMsg(playerid, "/makecraft [type]");
	}

	id = Craft_Create(playerid, type);

	if (id == -1)
		return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างจุดคราฟเกินขีดจำกัดแล้ว");

	format(string, sizeof(string), "คุณประสบความสำเร็จสร้างจุดคราฟไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:removecraft(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	new
		id = 0,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/removecraft [craft id]");

	if ((id < 0 || id >= MAX_CRAFT_DYNAMIC) || !CraftData[id][craftExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีจุดคราฟผิดพลาด");

	Craft_Delete(id);
	format(string, sizeof(string), "คุณประสบความสำเร็จในการทำลายจุดคราฟไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:editcraft(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id,
		type[24],
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
	{
		SystemMsg(playerid, "/editcraft [id] [name]");
		SystemMsg(playerid, "[ตัวเลือก]:{FFFFFF} location");
		return 1;
	}
	if ((id < 0 || id >= MAX_CRAFT_DYNAMIC) || !CraftData[id][craftExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีจุดคราฟไม่ถูกต้อง");

	if (!strcmp(type, "location", true))
	{
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);

		CraftData[id][craftPos][0] = x;
		CraftData[id][craftPos][1] = y;
		CraftData[id][craftPos][2] = z;

		CraftData[id][craftInt] = GetPlayerInterior(playerid);
		CraftData[id][craftWorld] = GetPlayerVirtualWorld(playerid);

		Craft_Refresh(id);
		Craft_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่งของจุดคราฟ ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	return 1;
}