#if defined _inc_impl
	#undef _inc_impl
#endif

forward SafeZone_Load();
public SafeZone_Load()
{
    new
	    rows;

    cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if (i < MAX_SAFEZONES)
	{
	    SafeZoneData[i][safezoneExists] = true;
    	cache_get_value_name_int(i, "safezoneID", SafeZoneData[i][safezoneID]);

    	cache_get_value_name_float(i, "safezonePosX", SafeZoneData[i][safezonePos][0]);
     	cache_get_value_name_float(i, "safezonePosY", SafeZoneData[i][safezonePos][1]);
     	cache_get_value_name_float(i, "safezonePosZ", SafeZoneData[i][safezonePos][2]);
     	cache_get_value_name_int(i, "safezoneInterior", SafeZoneData[i][safezoneInterior]);
     	cache_get_value_name_int(i, "safezoneWorld", SafeZoneData[i][safezoneWorld]);
		cache_get_value_name_int(i, "safezoneRadius", SafeZoneData[i][safezoneRadius]);
		cache_get_value_name_int(i, "safezoneType", SafeZoneData[i][safezoneType]);

	    SafeZone_Refresh(i);

	    Total_Safezones_Created++;
	}
	printf("(( [MYSQL]: Load %d Safezones Successfully ))", Total_Safezones_Created);
	return 1;
}

SafeZone_Delete(safezoneid)
{
	if (safezoneid != -1 && SafeZoneData[safezoneid][safezoneExists])
	{
	    new
	        string[64];

        Total_Safezones_Created--;

		format(string, sizeof(string), "DELETE FROM `safezones` WHERE `safezoneID` = '%d' LIMIT 1", SafeZoneData[safezoneid][safezoneID]);
		mysql_tquery(dbCon, string);

        if (IsValidDynamic3DTextLabel(SafeZoneData[safezoneid][safezoneText3D]))
		    DestroyDynamic3DTextLabel(SafeZoneData[safezoneid][safezoneText3D]);

		if (IsValidDynamicPickup(SafeZoneData[safezoneid][safezonePickup]))
		    DestroyDynamicPickup(SafeZoneData[safezoneid][safezonePickup]);

	    SafeZoneData[safezoneid][safezoneExists] = false;
	    SafeZoneData[safezoneid][safezoneID] = 0;
	}
	return 1;
}

SafeZone_Save(safezoneid)
{
	new
	    query[1024];

	format(query, sizeof(query), "UPDATE `safezones` SET `safezonePosX` = '%.4f', `safezonePosY` = '%.4f', `safezonePosZ` = '%.4f', `safezoneInterior` = '%d', `safezoneWorld` = '%d', `safezoneRadius` = '%d', `safezoneType` = '%d' WHERE `safezoneID` = '%d'",
	    SafeZoneData[safezoneid][safezonePos][0],
	    SafeZoneData[safezoneid][safezonePos][1],
	    SafeZoneData[safezoneid][safezonePos][2],
	    SafeZoneData[safezoneid][safezoneInterior],
        SafeZoneData[safezoneid][safezoneWorld],
		SafeZoneData[safezoneid][safezoneRadius],
		SafeZoneData[safezoneid][safezoneType],
        SafeZoneData[safezoneid][safezoneID]
	);
	return mysql_tquery(dbCon, query);
}

SafeZone_Refresh(safezoneid)
{
	if (safezoneid != -1 && SafeZoneData[safezoneid][safezoneExists])
	{
		if (IsValidDynamic3DTextLabel(SafeZoneData[safezoneid][safezoneText3D]))
		    DestroyDynamic3DTextLabel(SafeZoneData[safezoneid][safezoneText3D]);

		if (IsValidDynamicPickup(SafeZoneData[safezoneid][safezonePickup]))
		    DestroyDynamicPickup(SafeZoneData[safezoneid][safezonePickup]);

		new string[128];

		if(SafeZoneData[safezoneid][safezoneType] == 1){
			format(string, sizeof(string), "[SafeZone]\n{FFFFFF}ห้ามทำดาเมจกันใน Safezone");
			SafeZoneData[safezoneid][safezoneText3D] = CreateDynamic3DTextLabel(string, COLOR_GREEN, SafeZoneData[safezoneid][safezonePos][0], SafeZoneData[safezoneid][safezonePos][1], SafeZoneData[safezoneid][safezonePos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, SafeZoneData[safezoneid][safezoneWorld], SafeZoneData[safezoneid][safezoneInterior]);
			SafeZoneData[safezoneid][safezonePickup] = CreateDynamicPickup(1254, 23, SafeZoneData[safezoneid][safezonePos][0], SafeZoneData[safezoneid][safezonePos][1], SafeZoneData[safezoneid][safezonePos][2], SafeZoneData[safezoneid][safezoneWorld], SafeZoneData[safezoneid][safezoneInterior]);
		}	
		else if(SafeZoneData[safezoneid][safezoneType] == 2){
			format(string, sizeof(string), "[RabelZone]\n{FFFFFF}พืนที่ที่สามารถทำดาเมจกันได้");
			SafeZoneData[safezoneid][safezoneText3D] = CreateDynamic3DTextLabel(string, COLOR_RED, SafeZoneData[safezoneid][safezonePos][0], SafeZoneData[safezoneid][safezonePos][1], SafeZoneData[safezoneid][safezonePos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, SafeZoneData[safezoneid][safezoneWorld], SafeZoneData[safezoneid][safezoneInterior]);
			SafeZoneData[safezoneid][safezonePickup] = CreateDynamicPickup(1254, 23, SafeZoneData[safezoneid][safezonePos][0], SafeZoneData[safezoneid][safezonePos][1], SafeZoneData[safezoneid][safezonePos][2], SafeZoneData[safezoneid][safezoneWorld], SafeZoneData[safezoneid][safezoneInterior]);
		}
        
	}
	return 1;
}

SafeZone_Nearest(playerid)
{
    for (new i = 0; i != MAX_SAFEZONES; i ++) if (SafeZoneData[i][safezoneExists] && IsPlayerInRangeOfPoint(playerid, SafeZoneData[i][safezoneRadius], SafeZoneData[i][safezonePos][0], SafeZoneData[i][safezonePos][1], SafeZoneData[i][safezonePos][2]))
	{
		if (GetPlayerInterior(playerid) == SafeZoneData[i][safezoneInterior] && GetPlayerVirtualWorld(playerid) == SafeZoneData[i][safezoneWorld])
			return i;
	}
	return -1;
}

SafeZone_Create(playerid, type, radius)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

    if (GetPlayerPos(playerid, x, y, z))
	{
		for (new i = 0; i != MAX_SAFEZONES; i ++)
		{
	    	if (!SafeZoneData[i][safezoneExists])
		    {
    	        SafeZoneData[i][safezoneExists] = true;


    	        SafeZoneData[i][safezonePos][0] = x;
    	        SafeZoneData[i][safezonePos][1] = y;
    	        SafeZoneData[i][safezonePos][2] = z;


				SafeZoneData[i][safezoneInterior] = GetPlayerInterior(playerid);
				SafeZoneData[i][safezoneWorld] = GetPlayerVirtualWorld(playerid);

				SafeZoneData[i][safezoneRadius] = radius;
				SafeZoneData[i][safezoneType] = type;

				SafeZone_Refresh(i);
				mysql_tquery(dbCon, "INSERT INTO `safezones` (`safezoneInterior`) VALUES(0)", "OnSafezoneCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

forward OnSafezoneCreated(safezoneid);
public OnSafezoneCreated(safezoneid)
{
	if (safezoneid == -1 || !SafeZoneData[safezoneid][safezoneExists])
	    return 0;

	SafeZoneData[safezoneid][safezoneID] = cache_insert_id();
	SafeZone_Save(safezoneid);

	return 1;
}

CMD:safezonecmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[SAFEZONECMDS]: /gotosafezone, /makesafezone, /editsafezone, /removesafezone");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

CMD:gotosafezone(playerid, params[])
{
	new
		id;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SendClientMessage(playerid, -1, "/gotosafezone [safezone ID]");

	if ((id < 0 || id >= MAX_SAFEZONES) || !SafeZoneData[id][safezoneExists])
		return SendClientMessage(playerid, -1, "คุณระบุ Safezone ID ไม่ถูกต้อง");

	SetPlayerPosEx(playerid, SafeZoneData[id][safezonePos][0], SafeZoneData[id][safezonePos][1], SafeZoneData[id][safezonePos][2], SafeZoneData[id][safezoneInterior], SafeZoneData[id][safezoneWorld]);
	SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ Safezone ID: %d", id);
	return 1;
}

CMD:makesafezone(playerid, params[])
{
	new
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	new type, radius;
	if(sscanf(params, "dd", type, radius)){
		SystemMsg(playerid, "/makesafezone [type] [radius]");
		SystemMsg(playerid, "[TYPE]: 1:Safezone, 2:Rabelzone");
		return 1;
	}	

	new id = SafeZone_Create(playerid, type, radius);

	if (id == -1)
		return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้ Safezone เกินขีดจำกัดแล้ว");

	format(string, sizeof(string), "คุณได้ประสบความสำเร็จในการสร้าง Safezone ไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:editsafezone(playerid, params[])
{
	new
		id,
		type[24],
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
	{
		SystemMsg(playerid, "/editsafezone [id] [name]");
		SystemMsg(playerid, "[NAMES]:{FFFFFF} location, type, radius");
		return 1;
	}
	if ((id < 0 || id >= MAX_SAFEZONES) || !SafeZoneData[id][safezoneExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดี safezone ไม่ถูกต้อง");

	if (!strcmp(type, "location", true))
	{
		GetPlayerPos(playerid, SafeZoneData[id][safezonePos][0], SafeZoneData[id][safezonePos][1], SafeZoneData[id][safezonePos][2]);

		SafeZoneData[id][safezoneInterior] = GetPlayerInterior(playerid);
		SafeZoneData[id][safezoneWorld] = GetPlayerVirtualWorld(playerid);

		SafeZone_Refresh(id);
		SafeZone_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่งของ Safezone ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if(!strcmp(type, "type", true)){
		new typeint;

		if (sscanf(string, "d", typeint))
			return SendClientMessage(playerid, -1, "/editsafezone [id] [type] [1:เซฟโซน, 2:เลเบลโซน]");

		if (typeint < 1 || typeint > 2)
			return SendClientMessage(playerid, -1, "ประเภทที่ระบุต้องอยู่ระหว่าง 1 ถึง 2");

		SafeZoneData[id][safezoneType] = typeint;

		SafeZone_Refresh(id);
		SafeZone_Save(id);

		format(string, sizeof(string), "%s ได้ปรับประเภทของ Safezone ไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if(!strcmp(type, "radius", true)){
		new radius;

		if (sscanf(string, "d", radius))
			return SendClientMessage(playerid, -1, "/editsafezone [id] [radius] [radius]");

		if (radius < 1)
			return SendClientMessage(playerid, -1, "ขอบเขตต้องมากกว่า 0");

		SafeZoneData[id][safezoneRadius] = radius;

		SafeZone_Refresh(id);
		SafeZone_Save(id);

		format(string, sizeof(string), "%s ได้ปรับระยะของ Safezone ไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, radius);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	return 1;
}

CMD:removesafezone(playerid, params[])
{
	new
		id = 0,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/removesafezone [safezone id]");

	if ((id < 0 || id >= MAX_SAFEZONES) || !SafeZoneData[id][safezoneExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดี Safezone ไม่ถูกต้อง");

	SafeZone_Delete(id);
	format(string, sizeof(string), "คุณได้ประสบความสำเร็จในการทำลาย Safezone ไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}