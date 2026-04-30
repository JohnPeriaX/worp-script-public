#if defined _inc_impl
	#undef _inc_impl
#endif

forward Garage_Load();
public Garage_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_GARAGE)
	{
	    GarageData[i][garageExists] = true;

	    cache_get_value_name_int(i, "garageID", GarageData[i][garageID]);
	    cache_get_value_name_float(i, "garageGetCarX", GarageData[i][garageGetCar][0]);
	    cache_get_value_name_float(i, "garageGetCarY", GarageData[i][garageGetCar][1]);
	    cache_get_value_name_float(i, "garageGetCarZ", GarageData[i][garageGetCar][2]);
	    cache_get_value_name_int(i, "garageGetCarInt", GarageData[i][garageGetCarInt]);
	    cache_get_value_name_int(i, "garageGetCarWorld", GarageData[i][garageGetCarWorld]);

        cache_get_value_name_float(i, "garageStoreCarX", GarageData[i][garageStoreCar][0]);
	    cache_get_value_name_float(i, "garageStoreCarY", GarageData[i][garageStoreCar][1]);
	    cache_get_value_name_float(i, "garageStoreCarZ", GarageData[i][garageStoreCar][2]);
	    cache_get_value_name_int(i, "garageStoreCarInt", GarageData[i][garageStoreCarInt]);
	    cache_get_value_name_int(i, "garageStoreCarWorld", GarageData[i][garageStoreCarWorld]);
		cache_get_value_name_int(i, "garageType", GarageData[i][garageType]);


        Garage_Count++;

 	    Garage_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d Garage Successfully ))", Garage_Count);
	return 1;
}

Garage_GetNearest(playerid)
{
    for (new i = 0; i != MAX_GARAGE; i ++) if (GarageData[i][garageExists] && IsPlayerInRangeOfPoint(playerid, 3.0, GarageData[i][garageGetCar][0], GarageData[i][garageGetCar][1], GarageData[i][garageGetCar][2]))
	{
		if (GetPlayerInterior(playerid) == GarageData[i][garageGetCarInt] && GetPlayerVirtualWorld(playerid) == GarageData[i][garageGetCarWorld])
			return i;
	}
	return -1;
}

Garage_StoreNearest(playerid)
{
    for (new i = 0; i != MAX_GARAGE; i ++) if (GarageData[i][garageExists] && IsPlayerInRangeOfPoint(playerid, 4.0, GarageData[i][garageStoreCar][0], GarageData[i][garageStoreCar][1], GarageData[i][garageStoreCar][2]))
	{
		if (GetPlayerInterior(playerid) == GarageData[i][garageStoreCarInt] && GetPlayerVirtualWorld(playerid) == GarageData[i][garageStoreCarWorld])
			return i;
	}
	return -1;
}

Garage_Save(garageid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `garages` SET `garageGetCarX` = '%.4f', `garageGetCarY` = '%.4f', `garageGetCarZ` = '%.4f', `garageGetCarInt` = '%d', `garageGetCarWorld` = '%d', `garageStoreCarX` = '%.4f', `garageStoreCarY` = '%.4f', `garageStoreCarZ` = '%.4f', `garageStoreCarInt` = '%d', `garageStoreCarWorld` = '%d', `garageType` = '%d' WHERE `garageID` = '%d'",
		GarageData[garageid][garageGetCar][0],
	    GarageData[garageid][garageGetCar][1],
	    GarageData[garageid][garageGetCar][2],
	    GarageData[garageid][garageGetCarInt],
	    GarageData[garageid][garageGetCarWorld],
        GarageData[garageid][garageStoreCar][0],
	    GarageData[garageid][garageStoreCar][1],
	    GarageData[garageid][garageStoreCar][2],
	    GarageData[garageid][garageStoreCarInt],
	    GarageData[garageid][garageStoreCarWorld],
		GarageData[garageid][garageType],
        GarageData[garageid][garageID]
	);
	return mysql_tquery(dbCon, query);
}

Garage_Create(playerid)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	if (GetPlayerPos(playerid, x, y, z))
	{
		for (new i = 0; i != MAX_GARAGE; i ++)
		{
	    	if (!GarageData[i][garageExists])
	    	{
	        	GarageData[i][garageExists] = true;
	
	        	GarageData[i][garageGetCar][0] = 0.0;
	        	GarageData[i][garageGetCar][1] = 0.0;
	        	GarageData[i][garageGetCar][2] = 0.0;
				GarageData[i][garageStoreCar][0] = 0.0;
	        	GarageData[i][garageStoreCar][1] = 0.0;
	        	GarageData[i][garageStoreCar][2] = 0.0;

	        	GarageData[i][garageGetCarInt] = 0;
	        	GarageData[i][garageGetCarWorld] = 0;

                GarageData[i][garageStoreCarInt] = 0;
                GarageData[i][garageStoreCarWorld] = 0;

				GarageData[i][garageType] = 0;

	        	Garage_Refresh(i);
	        	mysql_tquery(dbCon, "INSERT INTO `garages` (`garageGetCarInt`) VALUES(0)", "OnGarageCreated", "d", i);

	        	return i;
	        }
	    }
	}
	return -1;
}

forward OnGarageCreated(garageid);
public OnGarageCreated(garageid)
{
	if (garageid == -1 || !GarageData[garageid][garageExists])
	    return 0;

	GarageData[garageid][garageID] = cache_insert_id();
	Garage_Save(garageid);

	return 1;
}

Garage_Delete(garageid)
{
	if (garageid != -1 && GarageData[garageid][garageExists])
	{
	    new
	        string[64];

        Garage_Count--;

		format(string, sizeof(string), "DELETE FROM `garages` WHERE `garageID` = '%d' LIMIT 1", GarageData[garageid][garageID]);
		mysql_tquery(dbCon, string);

        for (new i = 0; i < 2; i ++) {
			if (IsValidDynamic3DTextLabel(GarageData[garageid][garageText3D][i]))
		    	DestroyDynamic3DTextLabel(GarageData[garageid][garageText3D][i]);

			if (IsValidDynamicPickup(GarageData[garageid][garagePickup][i]))
		    	DestroyDynamicPickup(GarageData[garageid][garagePickup][i]);
		}

        DestroyDynamicMapIcon(GarageData[garageid][garageMapIcon]);

		GarageData[garageid][garageExists] = false;
	    GarageData[garageid][garageID] = 0;
	}
	return 1;
}

Garage_Refresh(garageid)
{
	if (garageid != -1 && GarageData[garageid][garageExists])
	{
	    for (new i = 0; i < 2; i ++) {
			if (IsValidDynamic3DTextLabel(GarageData[garageid][garageText3D][i]))
		    	DestroyDynamic3DTextLabel(GarageData[garageid][garageText3D][i]);

			if (IsValidDynamicPickup(GarageData[garageid][garagePickup][i]))
		    	DestroyDynamicPickup(GarageData[garageid][garagePickup][i]);
		}

        DestroyDynamicMapIcon(GarageData[garageid][garageMapIcon]);

		new
		    string[128],
		    string1[128];

		if(GarageData[garageid][garageType] == 0){
			format(string, sizeof(string), "[จุดเรียกรถ]\nกด 'ALT' เพื่อใช้งาน\n(* ต้องลงจากยานพาหนะก่อน *)");
			format(string1, sizeof(string1), "[จุดเก็บรถ]\nกด 'ALT' เพื่อใช้งาน\n(* ต้องลงจากยานพาหนะก่อน *)");
		}
		else if(GarageData[garageid][garageType] == 1){
			format(string, sizeof(string), "[จุดเรียกเรือ]\nกด 'ALT' เพื่อใช้งาน\n(* ต้องลงจากยานพาหนะก่อน *)");
			format(string1, sizeof(string1), "[จุดเก็บเรือ]\nกด 'ALT' เพื่อใช้งาน\n(* ต้องลงจากยานพาหนะก่อน *)");
		}
		else if(GarageData[garageid][garageType] == 2){
			format(string, sizeof(string), "[จุดเรียกฮอ]\nกด 'ALT' เพื่อใช้งาน\n(* ต้องลงจากยานพาหนะก่อน *)");
			format(string1, sizeof(string1), "[จุดเก็บฮอ]\nกด 'ALT' เพื่อใช้งาน\n(* ต้องลงจากยานพาหนะก่อน *)");
		}
        
        GarageData[garageid][garageText3D][0] = CreateDynamic3DTextLabel(string, 0xFFD60CFF, GarageData[garageid][garageGetCar][0], GarageData[garageid][garageGetCar][1], GarageData[garageid][garageGetCar][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GarageData[garageid][garageGetCarWorld], GarageData[garageid][garageGetCarInt]);
        GarageData[garageid][garagePickup][0] = CreateDynamicPickup(19130, 23, GarageData[garageid][garageGetCar][0], GarageData[garageid][garageGetCar][1], GarageData[garageid][garageGetCar][2], GarageData[garageid][garageGetCarWorld], GarageData[garageid][garageGetCarInt]);
        GarageData[garageid][garageMapIcon] = CreateDynamicMapIcon(GarageData[garageid][garageGetCar][0], GarageData[garageid][garageGetCar][1], GarageData[garageid][garageGetCar][2], 55, 0, GarageData[garageid][garageGetCarWorld], GarageData[garageid][garageGetCarInt], -1, 500.0, MAPICON_GLOBAL, -1, 0);
        
		GarageData[garageid][garageText3D][1] = CreateDynamic3DTextLabel(string1, 0xFFD60CFF, GarageData[garageid][garageStoreCar][0], GarageData[garageid][garageStoreCar][1], GarageData[garageid][garageStoreCar][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GarageData[garageid][garageStoreCarWorld], GarageData[garageid][garageStoreCarInt]);
	    GarageData[garageid][garagePickup][1] = CreateDynamicPickup(19130, 23, GarageData[garageid][garageStoreCar][0], GarageData[garageid][garageStoreCar][1], GarageData[garageid][garageStoreCar][2], GarageData[garageid][garageStoreCarWorld], GarageData[garageid][garageStoreCarInt]);
	}
	return 1;
}

CMD:garagecmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[GARAGECMDS]: /makegarage, /removegarage, /editgarage, /gotogarage");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

//CMD
CMD:gotogarage(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/gotogarage [garage ID]");

	if ((id < 0 || id >= MAX_GARAGE) || !GarageData[id][garageExists])
		return SendClientMessage(playerid, -1, "คุณระบุ Garage ID ไม่ถูกต้อง");

	SetPlayerPosEx(playerid, GarageData[id][garageGetCar][0], GarageData[id][garageGetCar][1], GarageData[id][garageGetCar][2], GarageData[id][garageGetCarInt], GarageData[id][garageGetCarWorld]);
	SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ Garage ID: %d", id);
	return 1;
}

CMD:makegarage(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id = -1,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	id = Garage_Create(playerid);

	if (id == -1)
		return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างโรงเก็บยานพาหนะเกินขีดจำกัดแล้ว");

	format(string, sizeof(string), "คุณประสบความสำเร็จสร้างโรงเก็บยานพาหนะไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:removegarage(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id = 0,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/removegarage [garage id]");

	if ((id < 0 || id >= MAX_GARAGE) || !GarageData[id][garageExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีโรงเก็บยานพาหนะผิดพลาด");

	Garage_Delete(id);
	format(string, sizeof(string), "คุณประสบความสำเร็จในการทำลายโรงเก็บยานพาหนะไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:editgarage(playerid, params[])
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
		SystemMsg(playerid, "/editgarage [id] [name]");
		SystemMsg(playerid, "[ตัวเลือก]:{FFFFFF} getcar, storecar, type");
		return 1;
	}
	if ((id < 0 || id >= MAX_GARAGE) || !GarageData[id][garageExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีโรงเก็บยานพาหนะไม่ถูกต้อง");

	if (!strcmp(type, "getcar", true))
	{
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);

		GarageData[id][garageGetCar][0] = x;
		GarageData[id][garageGetCar][1] = y;
		GarageData[id][garageGetCar][2] = z;
		GarageData[id][garageGetCarInt] = GetPlayerInterior(playerid);
		GarageData[id][garageGetCarWorld] = GetPlayerVirtualWorld(playerid);

		Garage_Refresh(id);
		Garage_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่ง เรียกยานพาหนะ ของโรงเก็บยานพาหนะ ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "storecar", true))
	{
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);

		GarageData[id][garageStoreCar][0] = x;
		GarageData[id][garageStoreCar][1] = y;
		GarageData[id][garageStoreCar][2] = z;
		GarageData[id][garageStoreCarInt] = GetPlayerInterior(playerid);
		GarageData[id][garageStoreCarWorld] = GetPlayerVirtualWorld(playerid);

		Garage_Refresh(id);
		Garage_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่ง เก็บยานพาหนะ ของโรงเก็บยานพาหนะ ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
    }
	else if (!strcmp(type, "type", true))
	{
		new typeint;
		if(sscanf(string, "d", typeint)){
			SystemMsg(playerid, "/editgarage [id] [type] [typeid]");
			SendClientMessage(playerid, COLOR_YELLOW, "[Type]: 0: รถ | 1: เรือ | 2: ฮอ");
			return 1;
		}

		if(typeint < 0 || typeint > 2)
			return ErrorMsg(playerid, "ประเภทที่ระบุไม่ถูกต้อง");

		GarageData[id][garageType] = typeint;
		Garage_Save(id);
		Garage_Refresh(id);
		format(string, sizeof(string), "%s ได้ปรับตำแหน่ง ตัวเลือก ของโรงเก็บยานพาหนะ ไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, typeint);
		SendAdminsMessage(1, COLOR_GRAY, string);
    }
	return 1;
}

stock IsABoatSendModel(model){
	switch (model) {
		case 430, 446, 452, 453, 454, 472, 473, 484, 493, 595: return 1;
	}
	return 0;
}

stock IsAHelicopterSendModel(model){
	switch (model) {
		case 417, 425, 447, 465, 469, 487, 488, 497, 501, 548, 563: return 1;
	}
	return 0;
}


ShowCarPlayerGetGarage(playerid, garageid){
	new string[2056];
	new count = 0;

	if(PlayerData[playerid][pVip] < 2){
		if(CountGetVehicle[playerid] >= 1) {
			ErrorMsg(playerid, "คุณสามารถเบิกยานพาหนะออกจากการาจได้เพียงคันเดียวเท่านั้นหากจะเบิกอีกคันให้นำไปเก็บก่อน");
			ErrorMsg(playerid, "ถ้าหากยานพาหนะของคุณถูกรีเข้าการาจแล้วไม่สามารถเบิกได้ให้ 'ออกจากระบบ' แล้ว 'เข้าสู่ระบบ' อีกครั้ง");
			SendClientMessage(playerid, COLOR_YELLOW, "หมายเหตุ: หากคุณมี Silver Member คุณจะสามายานพาหนะเบิกได้หลายคัน");
			return 1;
		}
	}

	if(garageid != -1){
		if(GarageData[garageid][garageType] == 0){
			for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
				if(IsABoatSendModel(CarData[i][carModel])) continue;
				if(IsAHelicopterSendModel(CarData[i][carModel])) continue;
				if (Car_IsOwner(playerid, i) && CarData[i][carInsideGarage] == 1) {
					format(string, sizeof(string), "%s[ ช่อง #%d | ยานพาหนะ: %s | ป้ายทะเบียน: %s ]\n", string, count+1, ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate]);
					GetCarIDGarage[playerid][count] = i;
					count++;
				}
			}
			if(count) Dialog_ShowEasy(playerid, PlayerGetCarExitGarage, DIALOG_STYLE_LIST, "การาจเรียกรถ", string, "เลือก", "ยกเลิก");
			else Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การาจเรียกรถ", "คุณไม่มีรถอยู่ในการาจเลย...", "ตกลง", "");
		}
		else if(GarageData[garageid][garageType] == 1){
			for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
				if(IsABoatSendModel(CarData[i][carModel])){
					if (Car_IsOwner(playerid, i) && CarData[i][carInsideGarage] == 1) {
						format(string, sizeof(string), "%s[ ช่อง #%d | ยานพาหนะ: %s | ป้ายทะเบียน: %s ]\n", string, count+1, ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate]);
						GetCarIDGarage[playerid][count] = i;
						count++;
					}
				}
			}

			if(count) Dialog_ShowEasy(playerid, PlayerGetCarExitGarage, DIALOG_STYLE_LIST, "การาจเรียกเรือ", string, "เลือก", "ยกเลิก");
			else Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การาจเรียกเรือ", "คุณไม่มีเรืออยู่ในการาจเลย...", "ตกลง", "");
		}
		else if(GarageData[garageid][garageType] == 2){
			for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
				if(IsAHelicopterSendModel(CarData[i][carModel])){
					if (Car_IsOwner(playerid, i) && CarData[i][carInsideGarage] == 1) {
						format(string, sizeof(string), "%s[ ช่อง #%d | ยานพาหนะ: %s | ป้ายทะเบียน: %s ]\n", string, count+1, ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate]);
						GetCarIDGarage[playerid][count] = i;
						count++;
					}
				}
			}

			if(count) Dialog_ShowEasy(playerid, PlayerGetCarExitGarage, DIALOG_STYLE_LIST, "การาจเรียกฮอ", string, "เลือก", "ยกเลิก");
			else Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การาจเรียกฮอ", "คุณไม่มีฮออยู่ในการาจเลย...", "ตกลง", "");
		}
	}
	return 1;
}

Dialog:PlayerGetCarExitGarage(playerid, response, listitem, inputtext[]){
	if(!response)
		return 1;

	if(response){
		if(listitem >= 0 && listitem <= MAX_OWNABLE_CARS){
			new carid = GetCarIDGarage[playerid][listitem];

			if(CarData[carid][carDestroyed] == 1)
				SendClientMessageEx(playerid, COLOR_RED, "- ยานพาหนะ %s ของคุณถูกทำลาย, คุณจะต้องไปกูคืนก่อนเพื่อจะสามายานพาหนะใช้ได้", ReturnVehicleModelName(CarData[carid][carModel]));

			CarData[carid][carInsideGarage] = 0;
			new id = Car_Spawn(carid);
			Car_Save(carid);

			if(id == 1){
				new Float:x, Float:y, Float:z;

				GetPlayerPos(playerid, x, y, z);
				SetVehiclePosEx(CarData[carid][carVehicle], x + 2, y - 2, z);

				SetVehicleVirtualWorld(CarData[carid][carVehicle], GetPlayerVirtualWorld(playerid));
				LinkVehicleToInterior(CarData[carid][carVehicle], GetPlayerInterior(playerid));
				LoadVehSpeedoTextPlayer(playerid);
				PutPlayerInVehicleEx(playerid, CarData[carid][carVehicle], 0);
				CountGetVehicle[playerid]++;
			}
		}
	}
	return 1;
}

ShowCarPlayerStoreGarage(playerid){
	new carid = -1;
	if ((carid = Car_Nearest(playerid)) != -1){
		if(Car_IsOwner(playerid, carid)){
			new g_arrSeatData[10] = {INVALID_PLAYER_ID, ...}, seatid;
			for (new i = 0; i < 14; i ++) CarData[carid][carMods][i] = GetVehicleComponentInSlot(CarData[carid][carVehicle], i);
			SaveVehicleDamage(CarData[carid][carVehicle]);
			foreach (new i : Player) if (IsPlayerInVehicle(i, CarData[carid][carVehicle])) {
				if(LoggedIn[i]){
					seatid = GetPlayerVehicleSeat(i);
					g_arrSeatData[seatid] = i;
				}
			}
			SendClientMessageEx(playerid, COLOR_GREEN, "คุณได้ประสบความสําเร็จในการเก็บยานพาหนะ : %s", ReturnVehicleName(CarData[carid][carVehicle]));
			CarData[carid][carInsideGarage] = 1;

			Car_Save(carid);
			TRP_DestroyVehicle(CarData[carid][carVehicle], true);
			CarData[carid][carVehicle] = INVALID_VEHICLE_ID;
			CountGetVehicle[playerid]--;
		}
	}
	return 1;
}