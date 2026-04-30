#if defined _inc_impl
	#undef _inc_impl
#endif

SideJob_GetName(type)
{
	new
	    str[32];

	switch (type)
	{
		case 1: str = "ตัดไม้";
		case 2: str = "ขุดเหมือง";
		case 3: str = "ขนกล่องพัสดุ";
		case 4: str = "ปลูกพืช";
	    default: str = "ว่างงาน";
	}
	return str;
}

forward SideJob_Load();
public SideJob_Load(){
    new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_SIDEJOB)
	{
	    SideJobData[i][sidejobExists] = true;

	    cache_get_value_name_int(i, "sidejobID", SideJobData[i][sidejobID]);
	    cache_get_value_name(i, "sidejobName", SideJobData[i][sidejobName], 32);
	    cache_get_value_name_int(i, "sidejobType", SideJobData[i][sidejobType]);
	    cache_get_value_name_float(i, "sidejobPosX", SideJobData[i][sidejobPos][0]);
	    cache_get_value_name_float(i, "sidejobPosY", SideJobData[i][sidejobPos][1]);
	    cache_get_value_name_float(i, "sidejobPosZ", SideJobData[i][sidejobPos][2]);
	    cache_get_value_name_int(i, "sidejobInt", SideJobData[i][sidejobInt]);
	    cache_get_value_name_int(i, "sidejobWorld", SideJobData[i][sidejobWorld]);
	    cache_get_value_name_float(i, "sidejobPointX", SideJobData[i][sidejobPoint][0]);
	    cache_get_value_name_float(i, "sidejobPointY", SideJobData[i][sidejobPoint][1]);
	    cache_get_value_name_float(i, "sidejobPointZ", SideJobData[i][sidejobPoint][2]);
	    cache_get_value_name_int(i, "sidejobPointInt", SideJobData[i][sidejobPointInt]);
	    cache_get_value_name_int(i, "sidejobPointWorld", SideJobData[i][sidejobPointWorld]);

        Sidejob_Count++;

 	    Sidejob_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d Sidejob Successfully ))", Sidejob_Count);
    return 1;
}

Sidejob_Nearest(playerid)
{
    for (new i = 0; i != MAX_SIDEJOB; i ++) if (SideJobData[i][sidejobExists] && IsPlayerInRangeOfPoint(playerid, 2.5, SideJobData[i][sidejobPos][0], SideJobData[i][sidejobPos][1], SideJobData[i][sidejobPos][2]))
	{
		if (GetPlayerInterior(playerid) == SideJobData[i][sidejobInt] && GetPlayerVirtualWorld(playerid) == SideJobData[i][sidejobWorld])
			return i;
	}
	return -1;
}

Sidejob_Refresh(sidejobid){
    if (sidejobid != -1 && SideJobData[sidejobid][sidejobExists]){
        for (new i = 0; i < 2; i ++) {
			if (IsValidDynamic3DTextLabel(SideJobData[sidejobid][sidejobText3D][i]))
		    	DestroyDynamic3DTextLabel(SideJobData[sidejobid][sidejobText3D][i]);

			if (IsValidDynamicPickup(SideJobData[sidejobid][sidejobPickup][i]))
		    	DestroyDynamicPickup(SideJobData[sidejobid][sidejobPickup][i]);
		}
        new string[128];
		new string2[128];

		if(SideJobData[sidejobid][sidejobType] == 4){
			format(string, sizeof(string), "[อาชีพเสริม: %s]\nกดปุ่ม 'Y' เพื่อตักน้ำ", SideJob_GetName(SideJobData[sidejobid][sidejobType]));
			SideJobData[sidejobid][sidejobText3D][0] = CreateDynamic3DTextLabel(string, COLOR_YELLOW, SideJobData[sidejobid][sidejobPos][0], SideJobData[sidejobid][sidejobPos][1], SideJobData[sidejobid][sidejobPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, SideJobData[sidejobid][sidejobWorld], SideJobData[sidejobid][sidejobInt]);
	    	SideJobData[sidejobid][sidejobPickup][0] = CreateDynamicPickup(1318, 23, SideJobData[sidejobid][sidejobPos][0], SideJobData[sidejobid][sidejobPos][1], SideJobData[sidejobid][sidejobPos][2], SideJobData[sidejobid][sidejobWorld], SideJobData[sidejobid][sidejobInt]);
		}
		else if(SideJobData[sidejobid][sidejobType] == 2){
			format(string, sizeof(string), "[ขุดแปรรูปแร่ อาชีพ: %s]\nกดปุ่ม 'Y' เพื่อเริ่มแปรรูป", SideJob_GetName(SideJobData[sidejobid][sidejobType]));
			SideJobData[sidejobid][sidejobText3D][0] = CreateDynamic3DTextLabel(string, COLOR_YELLOW, SideJobData[sidejobid][sidejobPos][0], SideJobData[sidejobid][sidejobPos][1], SideJobData[sidejobid][sidejobPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, SideJobData[sidejobid][sidejobWorld], SideJobData[sidejobid][sidejobInt]);
	    	SideJobData[sidejobid][sidejobPickup][0] = CreateDynamicPickup(19133, 23, SideJobData[sidejobid][sidejobPos][0], SideJobData[sidejobid][sidejobPos][1], SideJobData[sidejobid][sidejobPos][2], SideJobData[sidejobid][sidejobWorld], SideJobData[sidejobid][sidejobInt]);
		}
        else{
			format(string, sizeof(string), "[อาชีพเสริม: %s]\nกดปุ่ม 'Y' เพื่อใช้งาน", SideJob_GetName(SideJobData[sidejobid][sidejobType]));
			SideJobData[sidejobid][sidejobText3D][0] = CreateDynamic3DTextLabel(string, 0xFF4218FF, SideJobData[sidejobid][sidejobPos][0], SideJobData[sidejobid][sidejobPos][1], SideJobData[sidejobid][sidejobPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, SideJobData[sidejobid][sidejobWorld], SideJobData[sidejobid][sidejobInt]);
	    	SideJobData[sidejobid][sidejobPickup][0] = CreateDynamicPickup(1318, 23, SideJobData[sidejobid][sidejobPos][0], SideJobData[sidejobid][sidejobPos][1], SideJobData[sidejobid][sidejobPos][2], SideJobData[sidejobid][sidejobWorld], SideJobData[sidejobid][sidejobInt]);
		}

		if(SideJobData[sidejobid][sidejobType] == 3){
			format(string2, sizeof(string2), "[%s]\nจุดส่งพัสดุ", SideJob_GetName(SideJobData[sidejobid][sidejobType]));
			SideJobData[sidejobid][sidejobText3D][1] = CreateDynamic3DTextLabel(string2, 0xFF4218FF, SideJobData[sidejobid][sidejobPoint][0], SideJobData[sidejobid][sidejobPoint][1], SideJobData[sidejobid][sidejobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, SideJobData[sidejobid][sidejobPointWorld], SideJobData[sidejobid][sidejobPointInt]);
			SideJobData[sidejobid][sidejobPickup][1] = CreateDynamicPickup(1318, 23, SideJobData[sidejobid][sidejobPoint][0], SideJobData[sidejobid][sidejobPoint][1], SideJobData[sidejobid][sidejobPoint][2], SideJobData[sidejobid][sidejobPointWorld], SideJobData[sidejobid][sidejobPointInt]);
        }
    }
    return 1;
}

GetClosestSideJob(playerid, type)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1;
		
	for (new i = 0; i < MAX_SIDEJOB; i ++) if (SideJobData[i][sidejobExists] && SideJobData[i][sidejobType] == type && GetPlayerInterior(playerid) == SideJobData[i][sidejobInt] && GetPlayerVirtualWorld(playerid) == SideJobData[i][sidejobWorld])
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, SideJobData[i][sidejobPos][0], SideJobData[i][sidejobPos][1], SideJobData[i][sidejobPos][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}

GetClosestSideJobPoint(playerid, type)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1
	;
	for (new i = 0; i < MAX_SIDEJOB; i ++) if (SideJobData[i][sidejobExists] && SideJobData[i][sidejobType] == type && GetPlayerInterior(playerid) == SideJobData[i][sidejobPointInt] && GetPlayerVirtualWorld(playerid) == SideJobData[i][sidejobPointWorld])
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, SideJobData[i][sidejobPoint][0], SideJobData[i][sidejobPoint][1], SideJobData[i][sidejobPoint][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}

Sidejob_Delete(sidejobid)
{
	if (sidejobid != -1 && SideJobData[sidejobid][sidejobExists])
	{
	    new
	        string[64];

        Sidejob_Count--;

		format(string, sizeof(string), "DELETE FROM `sidejobs` WHERE `sidejobID` = '%d' LIMIT 1", SideJobData[sidejobid][sidejobID]);
		mysql_tquery(dbCon, string);

        for (new i = 0; i < 3; i ++) {
			if (IsValidDynamic3DTextLabel(SideJobData[sidejobid][sidejobText3D][i]))
		    	DestroyDynamic3DTextLabel(SideJobData[sidejobid][sidejobText3D][i]);

			if (IsValidDynamicPickup(SideJobData[sidejobid][sidejobPickup][i]))
		    	DestroyDynamicPickup(SideJobData[sidejobid][sidejobPickup][i]);
		}
		SideJobData[sidejobid][sidejobExists] = false;
		SideJobData[sidejobid][sidejobType] = 0;
	    SideJobData[sidejobid][sidejobID] = 0;
	}
	return 1;
}

Sidejob_Save(sidejobid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `sidejobs` SET `sidejobName` = '%s', `sidejobType` = '%d', `sidejobPosX` = '%.4f', `sidejobPosY` = '%.4f', `sidejobPosZ` = '%.4f', `sidejobInt` = '%d', `sidejobWorld` = '%d', `sidejobPointX` = '%.4f', `sidejobPointY` = '%.4f', `sidejobPointZ` = '%.4f', `sidejobPointInt` = '%d', `sidejobPointWorld` = '%d' WHERE `sidejobID` = '%d'",
		SideJobData[sidejobid][sidejobName],
		SideJobData[sidejobid][sidejobType],
		SideJobData[sidejobid][sidejobPos][0],
	    SideJobData[sidejobid][sidejobPos][1],
	    SideJobData[sidejobid][sidejobPos][2],
	    SideJobData[sidejobid][sidejobInt],
	    SideJobData[sidejobid][sidejobWorld],
	    SideJobData[sidejobid][sidejobPoint][0],
	    SideJobData[sidejobid][sidejobPoint][1],
	    SideJobData[sidejobid][sidejobPoint][2],
        SideJobData[sidejobid][sidejobPointInt],
	    SideJobData[sidejobid][sidejobPointWorld],
        SideJobData[sidejobid][sidejobID]
	);
	return mysql_tquery(dbCon, query);
}

Sidejob_Create(playerid, type)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	if (GetPlayerPos(playerid, x, y, z))
	{
		for (new i = 0; i != MAX_SIDEJOB; i ++)
		{
	    	if (!SideJobData[i][sidejobExists])
	    	{
	        	SideJobData[i][sidejobExists] = true;
	        	SideJobData[i][sidejobType] = type;
				SideJobData[i][sidejobName] = SideJob_GetName(type);

				SideJobData[i][sidejobPos][0] = x;
	        	SideJobData[i][sidejobPos][1] = y;
	        	SideJobData[i][sidejobPos][2] = z;
	        	SideJobData[i][sidejobPoint][0] = 0.0;
	        	SideJobData[i][sidejobPoint][1] = 0.0;
	        	SideJobData[i][sidejobPoint][2] = 0.0;

	        	SideJobData[i][sidejobInt] = GetPlayerInterior(playerid);
	        	SideJobData[i][sidejobWorld] = GetPlayerVirtualWorld(playerid);

                SideJobData[i][sidejobPointInt] = 0;
                SideJobData[i][sidejobPointWorld] = 0;

	        	Sidejob_Refresh(i);
	        	mysql_tquery(dbCon, "INSERT INTO `sidejobs` (`sidejobInt`) VALUES(0)", "OnSideJobCreated", "d", i);

	        	return i;
	        }
	    }
	}
	return -1;
}

forward OnSideJobCreated(sidejobid);
public OnSideJobCreated(sidejobid)
{
	if (sidejobid == -1 || !SideJobData[sidejobid][sidejobExists])
	    return 0;

	SideJobData[sidejobid][sidejobID] = cache_insert_id();
	Sidejob_Save(sidejobid);

	return 1;
}

CMD:sidejobcmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[SIDEJOBCMDS]: /makesidejob, /removesidejob, /editsidejob, /gotosidejob, /sidejobrefresh");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

//CMD
CMD:gotosidejob(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/gotosidejob [job ID]");

	if ((id < 0 || id >= MAX_SIDEJOB) || !SideJobData[id][sidejobExists])
		return SendClientMessage(playerid, -1, "คุณระบุ SideJob ID ไม่ถูกต้อง");

	SetPlayerPosEx(playerid, SideJobData[id][sidejobPos][0], SideJobData[id][sidejobPos][1], SideJobData[id][sidejobPos][2], SideJobData[id][sidejobInt], SideJobData[id][sidejobWorld]);
	SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ SideJob ID: %d", id);
	return 1;
}

alias:makesidejob("สร้างงานเสริม")
CMD:makesidejob(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id = -1,
		type,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", type))
		return SystemMsg(playerid, "/makesidejob [type]");

	if (type < 1 || type > MAX_SIDEJOB)
	{
		format(string, sizeof(string), "ประเภทที่ระบุไม่ถูกต้องต้องอยู่ในระหว่าง 1 ถึง %d", MAX_SIDEJOB);
		SendClientMessage(playerid, -1, string);
		return 1;
	}

	id = Sidejob_Create(playerid, type);

	if (id == -1)
		return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างอาชีพเสริมเกินขีดจำกัดแล้ว");

	format(string, sizeof(string), "คุณประสบความสำเร็จสร้างอาชีพเสริมไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

alias:removesidejob("ลบงานเสริม")
CMD:removesidejob(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id = 0,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/removesidejob [job id]");

	if ((id < 0 || id >= MAX_SIDEJOB) || !SideJobData[id][sidejobExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีงานเสริมผิดพลาด");

	Sidejob_Delete(id);
	format(string, sizeof(string), "คุณประสบความสำเร็จในการทำลายอาชีพเสริมไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:sidejobrefresh(playerid)
{
	if(!LoggedIn[playerid]) return 0;
	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	for(new i=0; i< MAX_SIDEJOB;i++) if(SideJobData[i][sidejobExists]){
		Sidejob_Refresh(i);
	}
	return 1;
}

alias:editsidejob("แก้ไขงานเสริม")
CMD:editsidejob(playerid, params[])
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
		SystemMsg(playerid, "/editsidejob [id] [name]");
		SystemMsg(playerid, "[ตัวเลือก]:{FFFFFF} location, point, deliver, type, price");
		return 1;
	}
	if ((id < 0 || id >= MAX_SIDEJOB) || !SideJobData[id][sidejobExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีงานเสริมไม่ถูกต้อง");

	if (!strcmp(type, "location", true))
	{
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);

		SideJobData[id][sidejobPos][0] = x;
		SideJobData[id][sidejobPos][1] = y;
		SideJobData[id][sidejobPos][2] = z;

		SideJobData[id][sidejobInt] = GetPlayerInterior(playerid);
		SideJobData[id][sidejobWorld] = GetPlayerVirtualWorld(playerid);

		Sidejob_Refresh(id);
		Sidejob_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่งของอาชีพเสริม ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "type", true))
	{
		new typeint;

		if (sscanf(string, "d", typeint))
			return SendClientMessage(playerid, -1, "/editsidejob [id] [type] [new type]");

		if (typeint < 1 || typeint > 19)
			return SendClientMessage(playerid, -1, "ประเภทที่ระบุต้องอยู่ระหว่าง 1 ถึง 19");

		SideJobData[id][sidejobType] = typeint;

		Sidejob_Refresh(id);
		Sidejob_Save(id);

		format(string, sizeof(string), "%s ได้ปรับประเภทของอาชีพเสริม ไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, SideJobData[id][sidejobType]);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "point", true))
	{
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);

		SideJobData[id][sidejobPoint][0] = x;
		SideJobData[id][sidejobPoint][1] = y;
		SideJobData[id][sidejobPoint][2] = z;
		SideJobData[id][sidejobPointInt] = GetPlayerInterior(playerid);
		SideJobData[id][sidejobPointWorld] = GetPlayerVirtualWorld(playerid);

		Sidejob_Refresh(id);
		Sidejob_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่ง Point ของอาชีพเสริม ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	return 1;
}