#if defined _inc_impl
	#undef _inc_impl
#endif

CarTune_Create(playerid){
    new
	    Float:x,
	    Float:y,
	    Float:z;

	if (GetPlayerPos(playerid, x, y, z)){
		for (new i = 0; i != MAX_CARTUNE; i ++) if (!CarTuneData[i][cartuneEx]){
            CarTuneData[i][cartuneEx] = true;
            CarTuneData[i][cartunePos][0] = x;
            CarTuneData[i][cartunePos][1] = y;
            CarTuneData[i][cartunePos][2] = z;
            CarTuneData[i][cartuneInt] = GetPlayerInterior(playerid);
            CarTuneData[i][cartuneWorld] = GetPlayerVirtualWorld(playerid);

            Cartune_Refresh(i);
            mysql_tquery(dbCon, "INSERT INTO `cartunes` (`cartuneInt`) VALUES(0)", "OnCarTuneCreated", "d", i);

            return i;
        }
    }
	    	
    return -1;
}

forward OnCarTuneCreated(cartuneid);
public OnCarTuneCreated(cartuneid)
{
	if (cartuneid == -1 || !CarTuneData[cartuneid][cartuneEx])
	    return 0;

	CarTuneData[cartuneid][cartuneID] = cache_insert_id();
	Cartune_Save(cartuneid);

	return 1;
}

Cartune_Refresh(cartuneid){
    if (cartuneid != -1 && CarTuneData[cartuneid][cartuneEx]){
        if (IsValidDynamic3DTextLabel(CarTuneData[cartuneid][cartuneText3D]))
            DestroyDynamic3DTextLabel(CarTuneData[cartuneid][cartuneText3D]);

        new string[128];

        format(string, sizeof(string), "[จุดปรับแต่งยานพาหนะ]\nกด 'Y' เพื่อปรับแต่งยานพาหนะ");
        CarTuneData[cartuneid][cartuneText3D] = CreateDynamic3DTextLabel(string, 0xFF0000FF, CarTuneData[cartuneid][cartunePos][0], CarTuneData[cartuneid][cartunePos][1], CarTuneData[cartuneid][cartunePos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, CarTuneData[cartuneid][cartuneWorld], CarTuneData[cartuneid][cartuneInt]);
    }
    return 1;
}

Cartune_Save(cartuneid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `cartunes` SET `cartunePosX` = '%.4f', `cartunePosY` = '%.4f', `cartunePosZ` = '%.4f', `cartuneWorld` = '%d', `cartuneInt` = '%d' WHERE `cartuneID` = '%d'",
		CarTuneData[cartuneid][cartunePos][0],
	    CarTuneData[cartuneid][cartunePos][1],
	    CarTuneData[cartuneid][cartunePos][2],
	    CarTuneData[cartuneid][cartuneWorld],
	    CarTuneData[cartuneid][cartuneInt],
        CarTuneData[cartuneid][cartuneID]
	);
	return mysql_tquery(dbCon, query);
}

forward Cartune_Load();
public Cartune_Load(){
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_CARTUNE)
	{
	    CarTuneData[i][cartuneEx] = true;

	    cache_get_value_name_int(i, "cartuneID", CarTuneData[i][cartuneID]);
	    cache_get_value_name_float(i, "cartunePosX", CarTuneData[i][cartunePos][0]);
	    cache_get_value_name_float(i, "cartunePosY", CarTuneData[i][cartunePos][1]);
	    cache_get_value_name_float(i, "cartunePosZ", CarTuneData[i][cartunePos][2]);
	    cache_get_value_name_int(i, "cartuneInt", CarTuneData[i][cartuneInt]);
	    cache_get_value_name_int(i, "cartuneWorld", CarTuneData[i][cartuneWorld]);

        count_cartune++;

 	    Cartune_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d Cartunes Successfully ))", count_cartune);
	return 1;
}

Cartune_Delete(cartuneid)
{
	if (cartuneid != -1 && CarTuneData[cartuneid][cartuneEx])
	{
	    new
	        string[64];

        count_cartune--;

		format(string, sizeof(string), "DELETE FROM `cartunes` WHERE `cartuneID` = '%d' LIMIT 1", CarTuneData[cartuneid][cartuneID]);
		mysql_tquery(dbCon, string);

        if (IsValidDynamic3DTextLabel(CarTuneData[cartuneid][cartuneText3D]))
            DestroyDynamic3DTextLabel(CarTuneData[cartuneid][cartuneText3D]);

		CarTuneData[cartuneid][cartuneEx] = false;
	    CarTuneData[cartuneid][cartuneID] = 0;
	}
	return 1;
}

Cartune_Nearest(playerid){
    for (new i = 0; i != MAX_CARTUNE; i ++) if (CarTuneData[i][cartuneEx] && IsPlayerInRangeOfPoint(playerid, 3.0, CarTuneData[i][cartunePos][0], CarTuneData[i][cartunePos][1], CarTuneData[i][cartunePos][2])){
		if (GetPlayerInterior(playerid) == CarTuneData[i][cartuneInt] && GetPlayerVirtualWorld(playerid) == CarTuneData[i][cartuneWorld])
			return i;
	}
	return -1;
}

ResetMechanic(playerid){
    KillTimer(RepairTimer[playerid]);
    KillTimer(RefillTime[playerid]);
    RepairTimer[playerid] = 0;
    RefillTime[playerid] = 0;
    RefillPoint[playerid] = 0;
    MechanicRepairPoint[playerid] = 0;
    StartRepair[playerid] = 0;
    StartRefill[playerid] = 0;
}

SetPlayerRefillGascan(playerid, vehicleid){
    //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0xFF4444AA, 100.000000, 0);
    CreatePlayerProgressbar_Job(playerid, 0xFF4444AA);
    RefillTime[playerid] = SetTimerEx("RefillingTime", 1000, 0, "ii", playerid, vehicleid);
    StartRefill[playerid] = 1;
    TogglePlayerControllable(playerid, 0);
    RefillPoint[playerid] = 0;
}

forward RefillingTime(playerid, vehicleid);
public RefillingTime(playerid, vehicleid){
    new string[128];
    new id = -1;
    if ((id = Car_Nearest(playerid)) != -1){
        if(RefillPoint[playerid] < 100){
            RefillPoint[playerid] += 5;
            SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], RefillPoint[playerid]);
            format(string,sizeof(string),"Refilling... (%d)", RefillPoint[playerid]);
            PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
            //GameTextForPlayer(playerid, string, 1000, 3);
            RefillTime[playerid] = SetTimerEx("RefillingTime", 1000, 0, "ii", playerid, vehicleid);
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
        }
        else if(RefillPoint[playerid] >= 100){
            ClearAnimations(playerid);
            PlayerInventory_Remove(playerid, "Gas Can");
            TogglePlayerControllable(playerid, 1);
            DestroyPlayerProgressbar_Job(playerid);
            CarData[id][carFuel] = 100;
		    Car_Save(id);
            ResetMechanic(playerid);
            SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ทำการเติมน้ำมันให้กับ %s เรียบร้อยแล้ว", ReturnVehicleName(vehicleid));
        }
    }
    else{
        ResetMechanic(playerid);
        SendClientMessage(playerid, COLOR_RED, "- การกระทำถูกยกเลิก");
        TogglePlayerControllable(playerid, 1);
        DestroyPlayerProgressbar_Job(playerid);
        ClearAnimations(playerid);
    }
    return 1;
}

timer FreezeRepair[800](playerid){
    TogglePlayerControllable(playerid, 0);
}

SetPlayerMechanicRepairVehicle(playerid, vehicleid, flag){
    CreatePlayerProgressbar_Job(playerid, 0xFF4444AA);
    if(flag == 1) RepairTimer[playerid] = SetTimerEx("RepairingTime", 1000, 0, "iii", playerid, vehicleid, flag);
    else if(flag == 2) RepairTimer[playerid] = SetTimerEx("RepairingTime", 1000, 0, "iii", playerid, vehicleid, flag);
    defer FreezeRepair(playerid);
    MechanicRepairPoint[playerid] = 0;
    StartRepair[playerid] = 1;
    SetPlayerAttachedObject(playerid,8,19627,6,0.066999,0.028000,0.029000,89.100051,8.800004,-80.200004,1.582000,1.312999,1.279999);
    SetPlayerAttachedObject(playerid,7,18717,6,0.058000,0.020000,-1.648000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
    return 1;
}

forward RepairingTime(playerid, vehicleid, flag);
public RepairingTime(playerid, vehicleid, flag){
    new string[128];
    new id = -1;
    if(flag >= 1){
        if ((id = Car_Nearest(playerid)) != -1){
            if(MechanicRepairPoint[playerid] < 100){
                MechanicRepairPoint[playerid] += 5;
                SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], MechanicRepairPoint[playerid]);
                format(string,sizeof(string),"Repairing... (%d)", MechanicRepairPoint[playerid]);
                PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
                if(flag == 1) {
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                    RepairTimer[playerid] = SetTimerEx("RepairingTime", 1000, 0, "iii", playerid, vehicleid, flag);
                }
                else if(flag == 2) {
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                    RepairTimer[playerid] = SetTimerEx("RepairingTime", 3000, 0, "iii", playerid, vehicleid, flag);

                }
            }
            else if(MechanicRepairPoint[playerid] >= 100){
                if(ToolType[playerid] == 1){
                    PlayerInventory_Remove(playerid, "Repair Kit");
                }
                else if(ToolType[playerid] == 2){
                    PlayerInventory_Remove(playerid, "Quick Repair Kit");
                }
                
                ToolType[playerid] = 0;
                RepairVehicleEx(vehicleid);
                TogglePlayerControllable(playerid, 1);
                ClearAnimations(playerid);
                DestroyPlayerProgressbar_Job(playerid);
                RemoveAttachedObject(playerid, 8);
                RemoveAttachedObject(playerid, 7);
                Car_Save(id);
                ResetMechanic(playerid);
                SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ทำการซ่อมรถ %s เรียบร้อยแล้ว", ReturnVehicleName(vehicleid));
            }
        }
        else{
            ResetMechanic(playerid);
            SendClientMessage(playerid, COLOR_RED, "- การกระทำถูกยกเลิก");
            TogglePlayerControllable(playerid, 1);
            DestroyPlayerProgressbar_Job(playerid);
            ClearAnimations(playerid);
            RemoveAttachedObject(playerid, 8);
            RemoveAttachedObject(playerid, 7);
        }
    }else{
        ResetMechanic(playerid);
        SendClientMessage(playerid, COLOR_RED, "- การกระทำถูกยกเลิก");
        TogglePlayerControllable(playerid, 1);
        DestroyPlayerProgressbar_Job(playerid);
        ClearAnimations(playerid);
        RemoveAttachedObject(playerid, 8);
        RemoveAttachedObject(playerid, 7);
    }
    return 1;
}

ShowPlayerLockerMechanic(playerid, id){
	new caption[128], string[128];
	format(caption, sizeof(caption), "Locker ของ %s", GroupData[id][groupName]);
	format(string, sizeof(string), "- เปลี่ยนชุด\n- ถอดชุด");
	Dialog_ShowEasy(playerid, LockerMechanic, DIALOG_STYLE_LIST, caption, string, "เลือก", "ยกเลิก");
	return 1;
}

Dialog:LockerMechanic(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(listitem == 0){
            ShowGroupSkin(playerid, PlayerData[playerid][pGroup]);
        }
        if(listitem == 1){
            SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
            RemoveAttachedObject(playerid, 8);
        }
    }
    return 1;
}

stock IsATowTruck(carid)
{
	if(GetVehicleModel(carid) == 485 || GetVehicleModel(carid) == 525 || GetVehicleModel(carid) == 583 || GetVehicleModel(carid) == 574)
	{
		return 1;
	}
	return 0;
}

CMD:tow(playerid, params[])
{
    if(GetGroupType(playerid) != GROUP_MECHANIC) return 0;

	if (GetVehicleModel(GetPlayerVehicleID(playerid)) != 525)
	    return ErrorMsg(playerid, "คุณไม่ได้อยู่บนรถบรรทุกพ่วง");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return ErrorMsg(playerid, "คุณไม่ใช่คนขับ");

	new vehicleid = GetVehicleFromBehind(GetPlayerVehicleID(playerid));

	if (vehicleid == INVALID_VEHICLE_ID)
	    return ErrorMsg(playerid, "ไม่มียานพาหนะคันไหนอยู่ในขอบเขต");

	if (!IsDoorVehicle(vehicleid) || IsAPlane(vehicleid) || IsABoat(vehicleid) || IsAHelicopter(vehicleid))
	    return ErrorMsg(playerid, "ไม่สามารถลากยานพาหนะคันนี้ได้");

	AttachTrailerToVehicle(vehicleid, GetPlayerVehicleID(playerid));
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s ได้เกี่ยวตะขอ %s ลงบนรถบรรทุกพ่วงของพวกเขา", ReturnRoleplayName(playerid), ReturnVehicleName(vehicleid));
	return 1;
}

CMD:untow(playerid, params[])
{
    if(GetGroupType(playerid) != GROUP_MECHANIC) return 1;

	if (GetVehicleModel(GetPlayerVehicleID(playerid)) != 525)
	    return ErrorMsg(playerid, "คุณไม่ได้อยู่บนรถบรรทุกพ่วง");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return ErrorMsg(playerid, "คุณไม่ใช่คนขับ");

	new
	    trailerid = GetVehicleTrailer(GetPlayerVehicleID(playerid));

    if (!trailerid)
	    return ErrorMsg(playerid, "ไม่มียานพาหนะคันไหนถูกลากโดยรถบรรทุกนี้");

	DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s ได้ปลดตะขอ %s ออกจากรถบรรทุกพ่วง", ReturnRoleplayName(playerid), ReturnVehicleName(trailerid));

	return 1;
}

CMD:clearmods(playerid, params[]){
    if(GetGroupType(playerid) != GROUP_MECHANIC && PlayerData[playerid][pAdmin] < 1337) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติให้ใช้คำสั่งนี้");
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
        new vehicleid = GetPlayerVehicleID(playerid);
        if(vehicleid != INVALID_VEHICLE_ID){
            ClearMods(vehicleid);
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้ทำการเคลียร์ของแต่งทั้งหมดของยานพาหนะคันนี้แล้ว");
        }
    }
    return 1;
}

CMD:cartunecmds(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[CARTUNECMDS]: /makecartune, /removecartune, /editcartune");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

CMD:makecartune(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        new id = -1;
        id = CarTune_Create(playerid);
        if(id == -1)
            return ErrorMsg(playerid, "เซิฟเวอร์ได้สร้างจุดปรับแต่งยานพาหนะเต็มแล้ว");

        SendClientMessageEx(playerid, -1, "คุณประสบความสำเร็จในการสร้าง จุดปรับแต่งยานพาหนะ ไอดี: %d", id);
    }
    return 1;
}

CMD:removecartune(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        new id = -1;
        if(sscanf(params, "d", id))
            return SystemMsg(playerid, "/removecartune [id]");

        if ((id < 0 || id >= MAX_CARTUNE) || !CarTuneData[id][cartuneEx])
		    return SendClientMessage(playerid, -1, "คุณระบุไอดีจุดปรับแต่งผิดพลาด");

        SendClientMessageEx(playerid, -1, "คุณประสบความสำเร็จในการทำลาย จุดปรับแต่งยานพาหนะ ไอดี: %d", id);
        Cartune_Delete(id);
    }
    return 1;
}

CMD:editcartune(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        new
            id,
            type[24],
            string[128];

        if (sscanf(params, "ds[24]S()[128]", id, type, string))
        {
            SystemMsg(playerid, "/editcartune [id] [name]");
            SystemMsg(playerid, "[ตัวเลือก]:{FFFFFF} location");
            return 1;
        }

        if ((id < 0 || id >= MAX_CARTUNE) || !CarTuneData[id][cartuneEx])
		    return SendClientMessage(playerid, -1, "คุณระบุไอดีจุดปรับแต่งผิดพลาด");

        if (!strcmp(type, "location", true))
        {
            new
                Float:x,
                Float:y,
                Float:z;

            GetPlayerPos(playerid, x, y, z);

            CarTuneData[id][cartunePos][0] = x;
            CarTuneData[id][cartunePos][1] = y;
            CarTuneData[id][cartunePos][2] = z;

            CarTuneData[id][cartuneInt] = GetPlayerInterior(playerid);
            CarTuneData[id][cartuneWorld] = GetPlayerVirtualWorld(playerid);

            Cartune_Refresh(id);
            Cartune_Save(id);

            format(string, sizeof(string), "%s ได้ปรับตำแหน่งของ จุดปรับแต่งยานพาหนะ ไอดี: %d", ReturnRoleplayName(playerid), id);
            SendAdminsMessage(1, COLOR_GRAY, string);
        }
    }
    return 1;
}