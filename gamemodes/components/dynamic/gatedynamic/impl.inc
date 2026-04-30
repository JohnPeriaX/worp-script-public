#if defined _inc_impl
	#undef _inc_impl
#endif

forward CloseGate(gateid, linkid, Float:fX, Float:fY, Float:fZ, Float:speed, Float:fRotX, Float:fRotY, Float:fRotZ);
public CloseGate(gateid, linkid, Float:fX, Float:fY, Float:fZ, Float:speed, Float:fRotX, Float:fRotY, Float:fRotZ)
{
	if (GateData[gateid][gateExists] && GateData[gateid][gateOpened])
 	{
	 	if(GateData[gateid][gateSlow]) MoveDynamicObject(GateData[gateid][gateObject], fX, fY, fZ, 2.5, fRotX, fRotY, fRotZ);
		else MoveDynamicObject(GateData[gateid][gateObject], fX, fY, fZ, speed, fRotX, fRotY, fRotZ);
	 	GateData[gateid][gateOpened] = 0;

		new id = -1;
	 	if ((id = GetGateByID(linkid)) != -1){
			if(GateData[id][gateSlow]) MoveDynamicObject(GateData[id][gateObject], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], 2.5, GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5]);
			else MoveDynamicObject(GateData[id][gateObject], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], speed, GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5]);
			GateData[id][gateOpened] = 0;
		}
		return 1;
	}
	return 0;
}

stock Gate_Operate(gateid)
{
	if (gateid != -1 && GateData[gateid][gateExists])
	{
	    new id = -1;

		if (!GateData[gateid][gateOpened])
		{
		    GateData[gateid][gateOpened] = true;

			if(GateData[gateid][gateSlow]) MoveDynamicObject(GateData[gateid][gateObject], GateData[gateid][gateMove][0], GateData[gateid][gateMove][1], GateData[gateid][gateMove][2]+0.0001, 2.5, GateData[gateid][gateMove][3], GateData[gateid][gateMove][4], GateData[gateid][gateMove][5]);
		    else MoveDynamicObject(GateData[gateid][gateObject], GateData[gateid][gateMove][0], GateData[gateid][gateMove][1], GateData[gateid][gateMove][2], GateData[gateid][gateSpeed], GateData[gateid][gateMove][3], GateData[gateid][gateMove][4], GateData[gateid][gateMove][5]);

            if (GateData[gateid][gateTime] > 0) {
				GateData[gateid][gateTimer] = SetTimerEx("CloseGate", GateData[gateid][gateTime], false, "ddfffffff", gateid, GateData[gateid][gateLinkID], GateData[gateid][gatePos][0], GateData[gateid][gatePos][1], GateData[gateid][gatePos][2], GateData[gateid][gateSpeed], GateData[gateid][gatePos][3], GateData[gateid][gatePos][4], GateData[gateid][gatePos][5]);
			}
			if (GateData[gateid][gateLinkID] != -1 && (id = GetGateByID(GateData[gateid][gateLinkID])) != -1)
			{
			    GateData[id][gateOpened] = true;

			    if(GateData[id][gateSlow]) MoveDynamicObject(GateData[id][gateObject], GateData[id][gateMove][0], GateData[id][gateMove][1], GateData[id][gateMove][2]+0.0001, 2.5, GateData[id][gateMove][3], GateData[id][gateMove][4], GateData[id][gateMove][5]);
			    else MoveDynamicObject(GateData[id][gateObject], GateData[id][gateMove][0], GateData[id][gateMove][1], GateData[id][gateMove][2], GateData[id][gateSpeed], GateData[id][gateMove][3], GateData[id][gateMove][4], GateData[id][gateMove][5]);
			}
		}
		else if (GateData[gateid][gateOpened])
		{
		    GateData[gateid][gateOpened] = false;

           	if(GateData[gateid][gateSlow]) MoveDynamicObject(GateData[gateid][gateObject], GateData[gateid][gatePos][0], GateData[gateid][gatePos][1], GateData[gateid][gatePos][2], 2.5, GateData[gateid][gatePos][3], GateData[gateid][gatePos][4], GateData[gateid][gatePos][5]);
			else MoveDynamicObject(GateData[gateid][gateObject], GateData[gateid][gatePos][0], GateData[gateid][gatePos][1], GateData[gateid][gatePos][2], GateData[gateid][gateSpeed], GateData[gateid][gatePos][3], GateData[gateid][gatePos][4], GateData[gateid][gatePos][5]);

            if (GateData[gateid][gateTime] > 0) {
				KillTimer(GateData[gateid][gateTimer]);
		    }
			if (GateData[gateid][gateLinkID] != -1 && (id = GetGateByID(GateData[gateid][gateLinkID])) != -1)
			{
			    GateData[id][gateOpened] = false;
			    if(GateData[id][gateSlow]) MoveDynamicObject(GateData[id][gateObject], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], 2.5, GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5]);
				else MoveDynamicObject(GateData[id][gateObject], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], GateData[id][gateSpeed], GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5]);
			}
		}
	}
	return 1;
}

stock Gate_Create(playerid)
{
	new
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i < MAX_GATES; i ++) if (!GateData[i][gateExists])
		{
		    GateData[i][gateExists] = true;
			GateData[i][gateModel] = 980;
			GateData[i][gateSpeed] = 3.0;
			GateData[i][gateRadius] = 5.0;
			GateData[i][gateOpened] = 0;
			GateData[i][gateTime] = 0;

			GateData[i][gatePos][0] = x + (3.0 * floatsin(-angle, degrees));
			GateData[i][gatePos][1] = y + (3.0 * floatcos(-angle, degrees));
			GateData[i][gatePos][2] = z;
			GateData[i][gatePos][3] = 0.0;
			GateData[i][gatePos][4] = 0.0;
			GateData[i][gatePos][5] = angle;

			GateData[i][gateMove][0] = x + (3.0 * floatsin(-angle, degrees));
			GateData[i][gateMove][1] = y + (3.0 * floatcos(-angle, degrees));
			GateData[i][gateMove][2] = z - 10.0;
			GateData[i][gateMove][3] = -1000.0;
			GateData[i][gateMove][4] = -1000.0;
			GateData[i][gateMove][5] = -1000.0;

            GateData[i][gateInterior] = GetPlayerInterior(playerid);
            GateData[i][gateWorld] = GetPlayerVirtualWorld(playerid);

            GateData[i][gateLinkID] = -1;
            GateData[i][gateFaction] = -1;

            GateData[i][gateSlow] = 0;

            GateData[i][gatePass][0] = '\0';
            GateData[i][gateObject] = CreateDynamicObject(GateData[i][gateModel], GateData[i][gatePos][0], GateData[i][gatePos][1], GateData[i][gatePos][2], GateData[i][gatePos][3], GateData[i][gatePos][4], GateData[i][gatePos][5], GateData[i][gateWorld], GateData[i][gateInterior]);

			mysql_tquery(dbCon, "INSERT INTO `gates` (`gateModel`) VALUES(980)", "OnGateCreated", "d", i);
			return i;
		}
	}
	return -1;
}

stock Gate_Delete(gateid){
	if (gateid != -1 && GateData[gateid][gateExists])
	{
		new
		    query[64];

		format(query, sizeof(query), "DELETE FROM `gates` WHERE `gateID` = '%d' LIMIT 1", GateData[gateid][gateID]);
		mysql_tquery(dbCon, query);

		if (IsValidDynamicObject(GateData[gateid][gateObject]) && GateData[gateid][gateObject] != -1) DestroyDynamicObject(GateData[gateid][gateObject]);
		GateData[gateid][gateObject] = -1;

		for (new i = 0; i != MAX_GATES; i ++) if (GateData[i][gateExists] && GateData[i][gateLinkID] == GateData[gateid][gateID]) {
		    GateData[i][gateLinkID] = -1;
		    Gate_Save(i);
		}
		if (GateData[gateid][gateOpened] && GateData[gateid][gateTime] > 0) {
		    KillTimer(GateData[gateid][gateTimer]);
		}
	    GateData[gateid][gateExists] = false;
	    GateData[gateid][gateID] = 0;
	    GateData[gateid][gateOpened] = 0;
		GateData[gateid][gateSlow] = 0;
	}
	return 1;
}

stock Gate_Save(gateid)
{
	new
	    query[768];

	mysql_format(dbCon, query, sizeof(query), "UPDATE `gates` SET `gateModel` = '%d', `gateSpeed` = '%.4f', `gateRadius` = '%.4f', `gateTime` = '%d', `gateX` = '%.4f', `gateY` = '%.4f', `gateZ` = '%.4f', `gateRX` = '%.4f', `gateRY` = '%.4f', `gateRZ` = '%.4f' WHERE `gateID` = '%d'",
	    GateData[gateid][gateModel],
	    GateData[gateid][gateSpeed],
	    GateData[gateid][gateRadius],
	    GateData[gateid][gateTime],
	    GateData[gateid][gatePos][0],
	    GateData[gateid][gatePos][1],
	    GateData[gateid][gatePos][2],
	    GateData[gateid][gatePos][3],
	    GateData[gateid][gatePos][4],
	    GateData[gateid][gatePos][5],
	    GateData[gateid][gateID]
	);
	mysql_tquery(dbCon, query);

	mysql_format(dbCon, query, sizeof(query), "UPDATE `gates` SET `gateInterior` = '%d', `gateWorld` = '%d', `gateMoveX` = '%.4f', `gateMoveY` = '%.4f', `gateMoveZ` = '%.4f', `gateMoveRX` = '%.4f', `gateMoveRY` = '%.4f', `gateMoveRZ` = '%.4f', `gateLinkID` = '%d', `gateFaction` = '%d', `gatePass` = '%e', `gateSlow` = '%d' WHERE `gateID` = '%d'",

	    GateData[gateid][gateInterior],
	    GateData[gateid][gateWorld],
	    GateData[gateid][gateMove][0],
	    GateData[gateid][gateMove][1],
	    GateData[gateid][gateMove][2],
	    GateData[gateid][gateMove][3],
	    GateData[gateid][gateMove][4],
	    GateData[gateid][gateMove][5],
	    GateData[gateid][gateLinkID],
	    GateData[gateid][gateFaction],
	    GateData[gateid][gatePass],
	    GateData[gateid][gateSlow],
	    GateData[gateid][gateID]
	);
	mysql_tquery(dbCon, query);
	return 1;
}

forward Gate_Load();
public Gate_Load()
{
    new
	    rows;

	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if (i < MAX_GATES)
	{
	    GateData[i][gateExists] = true;
	    GateData[i][gateOpened] = false;

		cache_get_value_name_int(i, "gateID", GateData[i][gateID]);
  		cache_get_value_name_int(i, "gateModel", GateData[i][gateModel]);
    	cache_get_value_name_float(i, "gateSpeed", GateData[i][gateSpeed]);
		cache_get_value_name_float(i, "gateRadius", GateData[i][gateRadius]);
		cache_get_value_name_int(i, "gateTime", GateData[i][gateTime]);
		cache_get_value_name_int(i, "gateInterior", GateData[i][gateInterior]);
		cache_get_value_name_int(i, "gateWorld", GateData[i][gateWorld]);
		cache_get_value_name_int(i, "gateSlow", GateData[i][gateSlow]);

		cache_get_value_name_float(i, "gateX", GateData[i][gatePos][0]);
		cache_get_value_name_float(i, "gateY", GateData[i][gatePos][1]);
		cache_get_value_name_float(i, "gateZ", GateData[i][gatePos][2]);
		cache_get_value_name_float(i, "gateRX", GateData[i][gatePos][3]);
		cache_get_value_name_float(i, "gateRY", GateData[i][gatePos][4]);
		cache_get_value_name_float(i, "gateRZ", GateData[i][gatePos][5]);

		cache_get_value_name_float(i, "gateMoveX", GateData[i][gateMove][0]);
		cache_get_value_name_float(i, "gateMoveY", GateData[i][gateMove][1]);
		cache_get_value_name_float(i, "gateMoveZ", GateData[i][gateMove][2]);
		cache_get_value_name_float(i, "gateMoveRX", GateData[i][gateMove][3]);
		cache_get_value_name_float(i, "gateMoveRY", GateData[i][gateMove][4]);
		cache_get_value_name_float(i, "gateMoveRZ", GateData[i][gateMove][5]);

		cache_get_value_name_int(i, "gateLinkID", GateData[i][gateLinkID]);
		cache_get_value_name_int(i, "gateFaction", GateData[i][gateFaction]);

		cache_get_value_name(i, "gatePass", GateData[i][gatePass], 32);

	    GateData[i][gateObject] = CreateDynamicObject(GateData[i][gateModel], GateData[i][gatePos][0], GateData[i][gatePos][1], GateData[i][gatePos][2], GateData[i][gatePos][3], GateData[i][gatePos][4], GateData[i][gatePos][5], GateData[i][gateWorld], GateData[i][gateInterior]);
		CountGate++;
	}
	printf("(( [MYSQL]: Load %d Gates Successfully ))", CountGate);
	return 1;
}

Gate_Nearest(playerid)
{
    for (new i = 0; i != MAX_GATES; i ++) if (GateData[i][gateExists] && IsPlayerInRangeOfPoint(playerid, GateData[i][gateRadius], GateData[i][gatePos][0], GateData[i][gatePos][1], GateData[i][gatePos][2]))
	{
		if (GetPlayerInterior(playerid) == GateData[i][gateInterior] && GetPlayerVirtualWorld(playerid) == GateData[i][gateWorld])
			return i;
	}
	return -1;
}

stock GetGateByID(sqlid)
{
	for (new i = 0; i != MAX_GATES; i ++) if (GateData[i][gateExists] && GateData[i][gateID] == sqlid)
	    return i;

	return -1;
}

forward OnGateCreated(gateid);
public OnGateCreated(gateid)
{
	if (gateid == -1 || !GateData[gateid][gateExists])
	    return 0;

	GateData[gateid][gateID] = cache_insert_id();
	Gate_Save(gateid);

	return 1;
}

CMD:gatecmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[GATECMDS]: /makegate, /removegate, /editgate");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

CMD:gotogate(playerid, params[]){
	if(LoggedIn[playerid]){
		if(PlayerData[playerid][pAdmin] >= 1338){
			new id = -1;
			if (sscanf(params, "d", id))
		        return SystemMsg(playerid, "/goto [gate] [gate ID]");

			if ((id < 0 || id >= MAX_GATES) || !GateData[id][gateExists])
			    return ErrorMsg(playerid, "คุณระบุ Gate ID ไม่ถูกต้อง");

		    SetPlayerPosEx(playerid, GateData[id][gatePos][0] - (2.5 * floatsin(-GateData[id][gatePos][3], degrees)), GateData[id][gatePos][1] - (2.5 * floatcos(-GateData[id][gatePos][3], degrees)), GateData[id][gatePos][2], GateData[id][gateInterior], GateData[id][gateWorld]);
		    SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ Gate ID: %d", id);
		}
	}
	return 1;
}

CMD:makegate(playerid, params[])
{
	new
	    id = -1;

    if (PlayerData[playerid][pAdmin] < 1338)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	id = Gate_Create(playerid);

	if (id == -1)
	    return ErrorMsg(playerid, "เซิฟเวอร์นี้ได้สร้างประตูเกินขีดจำกัดแล้ว");

	SendClientMessageEx(playerid, -1, "คุณประสบความสำเร็จในการสร้างประตูไอดี: %d", id);
	return 1;
}

CMD:removegate(playerid, params[])
{
	new
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 1338)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
	    return SystemMsg(playerid, "/removegate [gate id]");

	if ((id < 0 || id >= MAX_GATES) || !GateData[id][gateExists])
	    return ErrorMsg(playerid, "คุณระบุไอดีประตูไม่ถูกต้อง");

	Gate_Delete(id);
	SendClientMessageEx(playerid, -1, "คุณประสบความสำเร็จในการทำลายประตูไอดี: %d", id);
	return 1;
}

CMD:editgate(playerid, params[])
{
	new
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SystemMsg(playerid, "/editgate [id] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, speed, radius, time, model, pos, move, pass, linkid, group, slowgate");
		return 1;
	}
	if ((id < 0 || id >= MAX_GATES) || !GateData[id][gateExists])
	    return ErrorMsg(playerid, "คุณระบุไอดีประตูไม่ถูกต้อง");

    if (!strcmp(type, "location", true))
	{
		new
		    Float:x,
		    Float:y,
		    Float:z,
		    Float:angle;

		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, angle);

		x += 3.0 * floatsin(-angle, degrees);
		y += 3.0 * floatcos(-angle, degrees);

		GateData[id][gatePos][0] = x;
		GateData[id][gatePos][1] = y;
		GateData[id][gatePos][2] = z;
		GateData[id][gatePos][3] = 0.0;
		GateData[id][gatePos][4] = 0.0;
		GateData[id][gatePos][5] = angle;

		SetDynamicObjectPos(GateData[id][gateObject], x, y, z);
		SetDynamicObjectRot(GateData[id][gateObject], 0.0, 0.0, angle);

		GateData[id][gateOpened] = false;

		Gate_Save(id);
		format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับที่ตั้งของประตูไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
		return 1;
	}
	else if (!strcmp(type, "speed", true))
	{
	    new
	        Float:speed;

		if (sscanf(string, "f", speed))
		    return SystemMsg(playerid, "/editgate [id] [speed] [move speed]");

		if (speed < 0.0 || speed > 20.0)
		    return ErrorMsg(playerid, "ความเร็วที่ระบุต้องไม่ต่ำกว่า 0 หรือมากกว่า 20");

        GateData[id][gateSpeed] = speed;

		Gate_Save(id);
		format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับความเร็วของประตูไอดี: %d เป็น %f", ReturnRoleplayName(playerid), id, speed);
		SendAdminsMessage(1, COLOR_GRAY, string);
		return 1;
	}
	else if (!strcmp(type, "radius", true))
	{
	    new
	        Float:radius;

		if (sscanf(string, "f", radius))
		    return SystemMsg(playerid, "/editgate [id] [radius] [open radius]");

		if (radius < 0.0 || radius > 20.0)
		    return ErrorMsg(playerid, "รัศมีที่ระบุต้องไม่ต่ำกว่า 0 หรือมากกว่า 0");

        GateData[id][gateRadius] = radius;

		Gate_Save(id);
		format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับรัศมีของประตูไอดี: %d เป็น %.2f", ReturnRoleplayName(playerid), id, radius);
		SendAdminsMessage(1, COLOR_GRAY, string);
		return 1;
	}
	else if (!strcmp(type, "time", true))
	{
	    new
	        time;

		if (sscanf(string, "d", time))
		    return SystemMsg(playerid, "/editgate [id] [time] [close time] (0 เพื่อปิดการใช้งาน)");

		if (time < 0 || time > 60000)
		    return ErrorMsg(playerid, "เวลาที่ระบุต้องไม่ต่ำกว่า 0 หรือมากกว่า 60,000 ms.");

        GateData[id][gateTime] = time;

		Gate_Save(id);
		format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับเวลาปิดของประตูไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, time);
		SendAdminsMessage(1, COLOR_GRAY, string);
		return 1;
	}
	else if (!strcmp(type, "model", true))
	{
	    new
	        model;

		if (sscanf(string, "d", model))
		    return SystemMsg(playerid, "/editgate [id] [model] [gate model]");

		if (!IsValidDynamicObjectModel(model))
		    return ErrorMsg(playerid, "โมเดลวัตถุไม่ถูกต้อง");

        GateData[id][gateModel] = model;

		if(IsValidDynamicObject(GateData[id][gateObject]) && GateData[id][gateObject] != -1) DestroyDynamicObject(GateData[id][gateObject]);
		GateData[id][gateObject] = -1;
		GateData[id][gateObject] = CreateDynamicObject(GateData[id][gateModel], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5], GateData[id][gateWorld], GateData[id][gateInterior]);

		Gate_Save(id);
		format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับโมเดลของประตูไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, model);
		SendAdminsMessage(1, COLOR_GRAY, string);
		return 1;
	}
    else if (!strcmp(type, "pos", true))
	{
	    ResetEditing(playerid);
	    Streamer_Update(playerid);
	   	EditDynamicObject(playerid, GateData[id][gateObject]);

		PlayerData[playerid][pEditGate] = id;
		PlayerData[playerid][pEditType] = 1;
		PlayerData[playerid][pEditPump] = -1;
		EditATM[playerid] = -1;

		SendClientMessageEx(playerid, -1, "คุณได้ปรับตำแหน่งของประตูไอดี: %d", id);
		return 1;
	}
	else if (!strcmp(type, "move", true))
	{
	    ResetEditing(playerid);
	    Streamer_Update(playerid);
	   	EditDynamicObject(playerid, GateData[id][gateObject]);

		PlayerData[playerid][pEditGate] = id;
		PlayerData[playerid][pEditType] = 2;
		PlayerData[playerid][pEditPump] = -1;
		EditATM[playerid] = -1;

		SendClientMessageEx(playerid, -1, "คุณได้ปรับตำแหน่งการเคลื่อนย้ายของประตูไอดี: %d", id);
		return 1;
	}
	else if (!strcmp(type, "linkid", true))
	{
	    new
	        linkid = -1;

		if (sscanf(string, "d", linkid))
		    return SystemMsg(playerid, "/editgate [id] [linkid] [gate link] (-1 for none)");

        if ((linkid < -1 || linkid >= MAX_GATES) || (linkid != -1 && !GateData[linkid][gateExists]))
	    	return ErrorMsg(playerid, "คุณระบุไอดีประตูไม่ถูกต้อง");

        GateData[id][gateLinkID] = (linkid == -1) ? (-1) : (GateData[linkid][gateID]);
		Gate_Save(id);

		if (id == -1){
			format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับไอดีประตูฝ่ายหรือกลุ่ม: %d ไม่ให้เชื่อมกับประตูอื่น", ReturnRoleplayName(playerid), id);
			SendAdminsMessage(1, COLOR_GRAY, string);
		}

		else{
			format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับไอดีประตูฝ่ายหรือกลุ่ม: %d เชื่อมกับประตูไอดี: %d", ReturnRoleplayName(playerid), id, linkid);
			SendAdminsMessage(1, COLOR_GRAY, string);
		}

		return 1;
	}
	else if (!strcmp(type, "group", true))
	{
	    new
	        factionid = -1;

		if (sscanf(string, "d", factionid))
		    return SystemMsg(playerid, "/editgate [id] [group] [gate group] (-1 for none)");

        if ((factionid < -1 || factionid >= MAX_GROUPS) || (factionid != -1 && !GroupData[factionid][groupExists]))
	    	return ErrorMsg(playerid, "คุณระบุไอดี ฝ่ายหรือกลุ่มไม่ถูกต้อง");

        GateData[id][gateFaction] = (factionid == -1) ? (-1) : (GroupData[factionid][groupID]);
		Gate_Save(id);

		if (factionid == -1){
			format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับไอดีประตูฝ่ายหรือกลุ่ม: %d ไม่ให้เชื่อมกับฝ่ายหรือกลุ่ม", ReturnRoleplayName(playerid), id);
			SendAdminsMessage(1, COLOR_GRAY, string);
		}

		else{
			format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับไอดีประตูฝ่ายหรือกลุ่ม: %d เป็นของ \"%s\"", ReturnRoleplayName(playerid), id, GroupData[factionid][groupName]);
			SendAdminsMessage(1, COLOR_GRAY, string);
		}

		return 1;
	}
	else if (!strcmp(type, "pass", true))
	{
	    new
	        pass[32];

		if (sscanf(string, "s[32]", pass))
		    return SystemMsg(playerid, "/editgate [id] [pass] [gate password] (ใช้ 'none' เพื่อปิดการใช้งาน)");

		if (!strcmp(string, "none", true))
			GateData[id][gatePass][0] = '\0';

		else format(GateData[id][gatePass], 32, pass);

		Gate_Save(id);
		format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับรหัสผ่านของประตูไอดี: %d เป็น %s", ReturnRoleplayName(playerid), id, pass);
		SendAdminsMessage(1, COLOR_GRAY, string);
		return 1;
	}
	else if (!strcmp(type, "slowgate", true))
	{

		if(GateData[id][gateSlow])
		{
		    GateData[id][gateSlow] = 0;
			format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับไอดีประตู: %d ให้เคลื่อนที่แบบปรกติ", ReturnRoleplayName(playerid), id);
			SendAdminsMessage(1, COLOR_GRAY, string);
		}
		else
		{
		    GateData[id][gateSlow] = 1;
			format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับไอดีประตู: %d ให้เคลื่อนที่แบบช้า ๆ", ReturnRoleplayName(playerid), id);
			SendAdminsMessage(1, COLOR_GRAY, string);
		}
		Gate_Save(id);

		return 1;
	}
	return 1;
}

CMD:refreshgate(playerid, params[]){
	if(LoggedIn[playerid]){
		if(PlayerData[playerid][pAdmin] >= 1338){
			for(new i=0; i<MAX_GATES; i++) if(GateData[i][gateExists]){
				if (IsValidDynamicObject(GateData[i][gateObject]) && GateData[i][gateObject] != -1) DestroyDynamicObject(GateData[i][gateObject]);
				GateData[i][gateObject] = -1;

				if (GateData[i][gateOpened] && GateData[i][gateTime] > 0) {
					KillTimer(GateData[i][gateTimer]);
				}
				GateData[i][gateExists] = false;
				GateData[i][gateID] = 0;
				GateData[i][gateOpened] = 0;
				GateData[i][gateSlow] = 0;
				GateData[i][gateLinkID] = -1;
			}
			CountGate = 0;
			mysql_tquery(dbCon, "SELECT * FROM `gates`", "Gate_Load", "");
			SendClientMessage(playerid, -1, "คุณได้รีประตูเลื่อนสำเร็จแล้ว");
		}
	}
	return 1;
}