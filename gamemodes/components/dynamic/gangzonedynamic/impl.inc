#if defined _inc_impl
	#undef _inc_impl
#endif

forward GangZone_Load();
public GangZone_Load(){
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_GANGZONE)
	{
	    GangZoneData[i][zoneEx] = true;

	    cache_get_value_name_int(i, "zoneID", GangZoneData[i][zoneID]);
	    cache_get_value_name_int(i, "zoneOwner", GangZoneData[i][zoneOwner]);
	    cache_get_value_name_float(i, "zonePosMinX", GangZoneData[i][zonePos][0]);
	    cache_get_value_name_float(i, "zonePosMinY", GangZoneData[i][zonePos][1]);
	    cache_get_value_name_float(i, "zonePosMaxX", GangZoneData[i][zonePos][2]);
        cache_get_value_name_float(i, "zonePosMaxY", GangZoneData[i][zonePos][3]);
	    cache_get_value_name_int(i, "zoneDelay", GangZoneData[i][zoneDelay]);
        GangZoneData[i][zoneAttack] = -1;

        if(GangZoneData[i][zoneDelay] > 0){
            GangZoneData[i][zoneTimerDelay] = SetTimerEx("GangZoneUpdateDelay", 1000, false, "d", i);
        }
        else if(GangZoneData[i][zoneDelay] == 0){
            KillTimer(GangZoneData[i][zoneTimerDelay]);
        }

        GangZone_Create(i);
        Count_Zone++;
	}
	printf("(( [MYSQL]: Load %d GangZone Successfully ))", Count_Zone);
	return 1;
}


ShowGangZoneForPlayer(playerid){
    if(!LoggedIn[playerid]) return 1;
    for(new i=0; i<MAX_GANGZONE; i++) if(GangZoneData[i][zoneEx]){
        GangZoneHideForPlayer(playerid, GangZoneData[i][zoneArea]);
        GangZoneShowForPlayer(playerid, GangZoneData[i][zoneArea], GetGroupColor(GangZoneData[i][zoneOwner]));
    }
    return 1;
}

GangZone_Create(zoneid){
    if(GangZoneData[zoneid][zoneArea] != 0)
        GangZoneDestroy(GangZoneData[zoneid][zoneArea]);

    GangZoneData[zoneid][zoneArea] = GangZoneCreate(GangZoneData[zoneid][zonePos][0], GangZoneData[zoneid][zonePos][1], GangZoneData[zoneid][zonePos][2], GangZoneData[zoneid][zonePos][3]);
    return 1;
}

GangZone_NewCreate(Float:minx, Float:miny, Float:maxx, Float:maxy, groupid){
    for(new i=0; i<MAX_GANGZONE; i++) if(!GangZoneData[i][zoneEx]){
        GangZoneData[i][zoneEx] = true;
        GangZoneData[i][zonePos][0] = minx;
        GangZoneData[i][zonePos][1] = miny;
        GangZoneData[i][zonePos][2] = maxx;
        GangZoneData[i][zonePos][3] = maxy;

        GangZoneData[i][zoneOwner] = groupid;
        GangZoneData[i][zoneAttack] = -1;

        GangZone_Create(i);

        GangZoneShowForAll(GangZoneData[i][zoneArea], GetGroupColor(GangZoneData[i][zoneOwner]));

        mysql_tquery(dbCon, "INSERT INTO `gangzones` (`zoneDelay`) VALUES(0)", "OnGangZoneCreated", "d", i);
        return i;
    }
    return -1;
}

forward OnGangZoneCreated(zoneid);
public OnGangZoneCreated(zoneid)
{
	if (zoneid == -1 || !GangZoneData[zoneid][zoneEx])
	    return 0;

	GangZoneData[zoneid][zoneID] = cache_insert_id();
	GangZone_Save(zoneid);

	return 1;
}

GangZone_Save(zoneid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `gangzones` SET `zoneOwner` = '%d', `zonePosMinX` = '%.4f', `zonePosMinY` = '%.4f', `zonePosMaxX` = '%.4f', `zonePosMaxY` = '%.4f', `zoneDelay` = '%d' WHERE `zoneID` = '%d'",
		GangZoneData[zoneid][zoneOwner],
		GangZoneData[zoneid][zonePos][0],
	    GangZoneData[zoneid][zonePos][1],
	    GangZoneData[zoneid][zonePos][2],
        GangZoneData[zoneid][zonePos][3],
	    GangZoneData[zoneid][zoneDelay],
        GangZoneData[zoneid][zoneID]
	);
	return mysql_tquery(dbCon, query);
}

GangZone_Delete(zoneid){

    GangZoneHideForAll(GangZoneData[zoneid][zoneArea]);

    if(GangZoneData[zoneid][zoneArea] != 0)
        GangZoneDestroy(GangZoneData[zoneid][zoneArea]);

    new string[256];

    Count_Zone--;

    GangZoneData[zoneid][zoneArea] = 0;
    GangZoneData[zoneid][zoneOwner] = -1;
    GangZoneData[zoneid][zoneDelay] = 0;
    GangZoneData[zoneid][zonePos][0] = 0.0;
    GangZoneData[zoneid][zonePos][1] = 0.0;
    GangZoneData[zoneid][zonePos][2] = 0.0;
    GangZoneData[zoneid][zonePos][3] = 0.0;
    KillTimer(GangZoneData[zoneid][zoneTimer]);
    KillTimer(GangZoneData[zoneid][zoneTimerDelay]);
    GangZoneData[zoneid][zoneTimer] = 0;

    format(string, sizeof(string), "DELETE FROM `gangzones` WHERE `zoneID` = '%d' LIMIT 1", GangZoneData[zoneid][zoneID]);
    mysql_tquery(dbCon, string);
    return 1;
}

IsPlayerInGZone(playerid, zoneid){
    if(LoggedIn[playerid]){
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        return (x > GangZoneData[zoneid][zonePos][0] && x < GangZoneData[zoneid][zonePos][2] && y > GangZoneData[zoneid][zonePos][1] && y < GangZoneData[zoneid][zonePos][3]);
    }
    return 1;
}

GetPlayerGZone(playerid){
    if(LoggedIn[playerid]){
        for(new i=0; i < MAX_GANGZONE; i++) if(GangZoneData[i][zoneEx]){
            if(IsPlayerInGZone(playerid, i)) return i;
        }
    }
    return -1;
}

SetPlayerFlashZone(playerid){
    if(LoggedIn[playerid]){
        for(new i=0; i<MAX_GANGZONE; i++) if(GangZoneData[i][zoneEx]){
            if(GangZoneData[i][zoneAttack] == -1) continue;
            else GangZoneFlashForPlayer(playerid, GangZoneData[i][zoneArea], GetGroupColor(GangZoneData[i][zoneAttack]));
        }
    }
    return 1;
}

forward GangZoneUpdateDelay(zoneid);
public GangZoneUpdateDelay(zoneid){
    if(zoneid != -1){
        if(GangZoneData[zoneid][zoneEx]){
            if(GangZoneData[zoneid][zoneDelay] > 0) {
                GangZoneData[zoneid][zoneDelay]--;
                GangZoneData[zoneid][zoneTimerDelay] = SetTimerEx("GangZoneUpdateDelay", 1000, false, "d", zoneid);
            }
            else if(GangZoneData[zoneid][zoneDelay] == 0){
                KillTimer(GangZoneData[zoneid][zoneTimerDelay]);
            }
        }
    }
}


CMD:takezone(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;

    if(ServerData[ServerCanHoldGangZone] == 0) return ErrorMsg(playerid, "ระบบการวอแก๊งยังไม่เปิด");

    if(PlayerData[playerid][pGroup] == -1)
        return ErrorMsg(playerid, "คุณไม่มีแก๊ง");

    if(GetGroupType(playerid) != GROUP_GANG)
        return ErrorMsg(playerid, "กลุ่มของคุณไม่ใช่แก๊ง");

    if (PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks])
        return SendClientMessageEx(playerid, -1, "คุณต้องมียศอย่างต่ำ %d", GroupData[PlayerData[playerid][pGroup]][groupRanks]);

    new inzone = -1;
    if((inzone = GetPlayerGZone(playerid)) != -1){
        new enemy = GangZoneData[inzone][zoneOwner];
        if(PlayerData[playerid][pGroup] != enemy){
            if(enemy == -1){
                if(GangZoneData[inzone][zoneAttack] == -1){
                    if(GangZoneData[inzone][zoneDelay] > 0)
                        return ErrorMsg(playerid, "แก๊งโซนนี้ยังไม่พร้อมให้ยึด");
                    else{
                        foreach(new i : Player){
                            if(!LoggedIn[i]) continue;
                            GangZoneHideForPlayer(i, GangZoneData[inzone][zoneArea]);
                            GangZoneShowForPlayer(i, GangZoneData[inzone][zoneArea], GetGroupColor(PlayerData[playerid][pGroup]));
                        }
                        GangZoneData[inzone][zoneOwner] = PlayerData[playerid][pGroup];
                        GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint]++;
                        Group_Save(PlayerData[playerid][pGroup]);
                        SendFactionMessage(PlayerData[playerid][pGroup], 0x46FF00AA, "(( (%s) ได้รับพ้อยแห่งความสำเร็จของแก๊ง +1 รวมเป็น %d))", GetGroupName(PlayerData[playerid][pGroup]), GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint]);
                        SendClientMessageToAllEx(COLOR_RED, "[WarZone]: แก๊ง %s ได้ทำการยึดพื้นที่ของ %s สำเร็จ", GetGroupName(PlayerData[playerid][pGroup]), GetGroupName(GangZoneData[inzone][zoneOwner]));
                        GangZoneData[inzone][zoneAttack] = -1;
                        GangZoneData[inzone][zoneDelay] = MAX_TIMEATTACK;
                        GangZoneData[inzone][zoneTimerDelay] = SetTimerEx("GangZoneUpdateDelay", 1000, false, "d", inzone);
                        GangZone_Save(inzone);
                    }
                }
            }
            else{
                if(GangZoneData[inzone][zoneAttack] == -1){
                    if(GangZoneData[inzone][zoneDelay] > 0)
                        return ErrorMsg(playerid, "แก๊งโซนนี้ยังไม่พร้อมให้ยึด");
                    else{
                        GangZoneData[inzone][zoneAttackTime] = 0;
                        GangZoneData[inzone][zoneAttack] = PlayerData[playerid][pGroup];
                        GangZoneData[inzone][zoneLeaderAttack] = playerid;
                        SendClientMessageToAllEx(COLOR_RED, "[WarZone]: แก๊ง %s กำลังทำการยึดโซนของ %s", GetGroupName(GangZoneData[inzone][zoneAttack]), GetGroupName(GangZoneData[inzone][zoneOwner]));
                        GangZoneFlashForAll(GangZoneData[inzone][zoneArea], GetGroupColor(GangZoneData[inzone][zoneAttack]));
                        GangZone_Save(inzone);
                        GangZoneData[inzone][zoneTimer] = SetTimerEx("UpdateZoneWar", 1000, false, "ii", playerid, inzone);
                    }
                }
            }
        }
        else return ErrorMsg(playerid, "แก๊งโซนนี้เป็นของคุณแล้ว");
    }
    return 1;
}

GetPlayersInZone(playerid, groupid, zoneid){
    if(!LoggedIn[playerid]) return 0;
    if(GetGroupType(playerid) == GROUP_GANG){
        if(PlayerData[playerid][pGroup] == groupid && PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks] && IsPlayerInGZone(playerid, zoneid)){
            return 1;
        }
    }
    return 0;
}

forward UpdateZoneWar(playerid, zoneid);
public UpdateZoneWar(playerid, zoneid){
    if(!LoggedIn[playerid] || playerid == INVALID_PLAYER_ID){
        KillTimer(GangZoneData[zoneid][zoneTimer]);
        GangZoneData[zoneid][zoneLeaderAttack] = -1;
        GangZoneData[zoneid][zoneTimer] = 0;
        GangZoneData[zoneid][zoneAttackTime] = 0;
        SendClientMessageToAllEx(COLOR_RED, "[WarZone]: แก๊ง %s ได้ทำการยึดพื้นที่ของ %s ล้มเหลว", GetGroupName(GangZoneData[zoneid][zoneAttack]), GetGroupName(GangZoneData[zoneid][zoneOwner]));
        GangZoneData[zoneid][zoneAttack] = -1;
        GangZoneData[zoneid][zoneDelay] = MAX_TIMEATTACK;
        GangZoneData[zoneid][zoneTimerDelay] = SetTimerEx("GangZoneUpdateDelay", 1000, false, "d", zoneid);
        GangZoneStopFlashForAll(GangZoneData[zoneid][zoneArea]);
        GangZone_Save(zoneid);
        return 1;
    }
    if(GangZoneData[zoneid][zoneAttack] != -1){
        if(GetPlayersInZone(playerid, GangZoneData[zoneid][zoneAttack], zoneid) == 1){
            if(GangZoneData[zoneid][zoneAttackTime] < MAX_TIMEATTACK){
                GangZoneData[zoneid][zoneAttackTime]++;
                GangZoneData[zoneid][zoneTimer] = SetTimerEx("UpdateZoneWar", 1000, false, "ii", playerid, zoneid);
            }
            else if(GangZoneData[zoneid][zoneAttackTime] >= MAX_TIMEATTACK){
                GangZoneData[zoneid][zoneAttackTime] = 0;
                GangZoneData[zoneid][zoneLeaderAttack] = -1;
                KillTimer(GangZoneData[zoneid][zoneTimer]);
                GangZoneData[zoneid][zoneTimer] = 0;
                GangZoneStopFlashForAll(GangZoneData[zoneid][zoneArea]);
                GroupData[GangZoneData[zoneid][zoneAttack]][groupHoldZonePoint]++;
                Group_Save(GangZoneData[zoneid][zoneAttack]);
                SendFactionMessage(GangZoneData[zoneid][zoneAttack], 0x46FF00AA, "(( (%s) ได้รับพ้อยแห่งความสำเร็จของแก๊ง +1 รวมเป็น %d))", GetGroupName(GangZoneData[zoneid][zoneAttack]), GroupData[GangZoneData[zoneid][zoneAttack]][groupHoldZonePoint]);
                SendClientMessageToAllEx(COLOR_RED, "[WarZone]: แก๊ง %s ได้ทำการยึดพื้นที่ของ %s สำเร็จ", GetGroupName(GangZoneData[zoneid][zoneAttack]), GetGroupName(GangZoneData[zoneid][zoneOwner]));
                GangZoneHideForAll(GangZoneData[zoneid][zoneArea]);
                GangZoneShowForAll(GangZoneData[zoneid][zoneArea], GetGroupColor(GangZoneData[zoneid][zoneAttack]));
                GangZoneData[zoneid][zoneOwner] = GangZoneData[zoneid][zoneAttack];
                GangZoneData[zoneid][zoneDelay] = MAX_TIMEATTACK;
                GangZoneData[zoneid][zoneAttack] = -1;
                GangZone_Save(zoneid);
                GangZoneData[zoneid][zoneTimerDelay] = SetTimerEx("GangZoneUpdateDelay", 1000, false, "d", zoneid);
            }
        }
        else{
            KillTimer(GangZoneData[zoneid][zoneTimer]);
            GangZoneData[zoneid][zoneTimer] = 0;
            GangZoneData[zoneid][zoneLeaderAttack] = -1;
            GangZoneData[zoneid][zoneAttackTime] = 0;
            SendClientMessageToAllEx(COLOR_RED, "[WarZone]: แก๊ง %s ได้ทำการยึดพื้นที่ของ %s ล้มเหลว", GetGroupName(GangZoneData[zoneid][zoneAttack]), GetGroupName(GangZoneData[zoneid][zoneOwner]));
            GangZoneData[zoneid][zoneAttack] = -1;
            GangZoneData[zoneid][zoneDelay] = MAX_TIMEATTACK;
            GangZoneData[zoneid][zoneTimerDelay] = SetTimerEx("GangZoneUpdateDelay", 1000, false, "d", zoneid);
            GangZoneStopFlashForAll(GangZoneData[zoneid][zoneArea]);
            GangZone_Save(zoneid);
        }
    }
    return 1;
}

CMD:zonecmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[ZONECMDS]: /makezone, /editzone, /removezone, /reloadgangzone");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}


CMD:makezone(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] >= 1338){
        new Float:minx, Float:miny, Float:maxx, Float:maxy;
        new groupid;
        if(sscanf(params, "ffffd", minx, miny, maxx, maxy, groupid))
            return SystemMsg(playerid, "/makezone [minx] [miny] [maxx] [maxy] [groupid]");

        new id = GangZone_NewCreate(minx, miny, maxx, maxy, groupid);

        if(id == -1) return ErrorMsg(playerid, "เซิฟเวอร์ได้สร้าง Gangzone เกินขีดจำกัดแล้ว");
        
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ประสบความสำเร็จในการสร้าง GangZone id : %d", id);
    }
    return 1;
}

CMD:removezone(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        new zoneid;
        if(sscanf(params, "d", zoneid)) return SystemMsg(playerid, "/removezone [zoneid]");

        if ((zoneid < 0 || zoneid >= MAX_GANGZONE) || !GangZoneData[zoneid][zoneEx])
		    return SendClientMessage(playerid, -1, "คุณระบุไอดี GangZone ผิดพลาด");

        GangZone_Delete(zoneid);
	    SendClientMessageEx(playerid, -1, "คุณประสบความสำเร็จในการทำลาย GangZone ไอดี: %d", zoneid);
    }
    return 1;
}

CMD:editzone(playerid, params[])
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
		SystemMsg(playerid, "/editzone [id] [name]");
		SystemMsg(playerid, "[ตัวเลือก]:{FFFFFF} groupid, delay");
		return 1;
	}

	if ((id < 0 || id >= MAX_GANGZONE) || !GangZoneData[id][zoneEx])
		return SendClientMessage(playerid, -1, "คุณระบุไอดี GangZone ไม่ถูกต้อง");

	if (!strcmp(type, "groupid", true))
	{
		new typeint;

		if (sscanf(string, "d", typeint))
			return SendClientMessage(playerid, -1, "/editzone [id] [groupid] [new groupid]");

		GangZoneData[id][zoneOwner] = typeint;

		GangZoneHideForPlayer(playerid, GangZoneData[id][zoneArea]);
        GangZoneShowForPlayer(playerid, GangZoneData[id][zoneArea], GetGroupColor(GangZoneData[id][zoneOwner]));
		GangZone_Save(id);

		format(string, sizeof(string), "%s ได้ปรับเจ้าของ GangZon ไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, GangZoneData[id][zoneOwner]);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
    else if(!strcmp(type, "delay", true)){
        new delay;
        if(sscanf(params, "d", delay))
            return SystemMsg(playerid, "/editzone [id] [delay] [new delay]");

        GangZoneData[id][zoneDelay] = delay;
        GangZoneData[id][zoneTimerDelay] = SetTimerEx("GangZoneUpdateDelay", 1000, false, "d", id);
        GangZone_Save(id);

		format(string, sizeof(string), "%s ได้ปรับ Delay GangZon ไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, delay);
		SendAdminsMessage(1, COLOR_GRAY, string);
    }
	return 1;
}

CMD:reloadgangzone(playerid, params[]){
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pAdmin] >= 1338){
            for(new i=0; i<MAX_GANGZONE; i++) if(GangZoneData[i][zoneEx]){
                GangZoneData[i][zoneEx] = false;
            }

            Count_Zone = 0;
            mysql_tquery(dbCon, "SELECT * FROM `gangzones`", "GangZone_Load", "");
            SendClientMessage(playerid, -1, "คุณได้ทำการโหลด 'GangZone'");
        }
    }
    return 1;
}