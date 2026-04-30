#if defined _inc_impl
	#undef _inc_impl
#endif

//dynamic pump
Pump_Create(playerid)
{
    new
	    Float:x,
	    Float:y,
	    Float:z,
		Float:angle,
		id = -1;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		if ((id = Pump_GetFreeID()) != -1)
  		{
	        x += 5.0 * floatsin(-angle, degrees);
	        y += 5.0 * floatcos(-angle, degrees);

			PumpData[id][pumpExists] = true;
			PumpData[id][pumpPos][0] = x;
			PumpData[id][pumpPos][1] = y;
			PumpData[id][pumpPos][2] = z;
			PumpData[id][pumpPos][3] = angle;
            PumpData[id][pumpFuel] = 3000;
			PumpData[id][pumpPrice] = 100;
			PumpData[id][pumpObject] = CreateDynamicObject(1676, x, y, z, 0.0, 0.0, angle);

			mysql_tquery(dbCon, "INSERT INTO `pumps` (`pumpFuel`) VALUES(3000)", "OnPumpCreated", "d", id);
			return id;
		}
		Pump_Refresh(id);
	}
	return -1;
}

forward Pump_Load(bizid);
public Pump_Load(bizid)
{
	new
	    rows,
		id = -1;

	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if ((id = Pump_GetFreeID()) != -1)
	{
	    PumpData[id][pumpExists] = true;

	    cache_get_value_name_int(i, "pumpID", PumpData[id][pumpID]);
	    cache_get_value_name_float(i, "pumpPosX", PumpData[id][pumpPos][0]);
	    cache_get_value_name_float(i, "pumpPosY", PumpData[id][pumpPos][1]);
	    cache_get_value_name_float(i, "pumpPosZ", PumpData[id][pumpPos][2]);
	    cache_get_value_name_float(i, "pumpPosA", PumpData[id][pumpPos][3]);
	    cache_get_value_name_int(i, "pumpFuel", PumpData[id][pumpFuel]);
		cache_get_value_name_int(i, "pumpPrice", PumpData[id][pumpPrice]);

		Pump_Refresh(id);

	    Total_Pumps_Created++;
	}
	printf("(( [MYSQL]: Load %d Pumps Successfully ))", Total_Pumps_Created);
	return 1;
}

stock Business_RemovePumps(bizid){
	if (BusinessData[bizid][bizExists] && BusinessData[bizid][bizType] == 6)
	{
	    new
	        string[32];

	    foreach (new i : Player) if (Character[i][Refill] != INVALID_VEHICLE_ID && Character[i][GasStation] == bizid)
	    {
			if(LoggedIn[i])
	        	StopRefilling(i);
	    }
		for (new i = 0; i != MAX_GAS_PUMPS; i ++) if (PumpData[i][pumpExists])
		{
			if(IsValidDynamicObject(PumpData[i][pumpObject]) && PumpData[i][pumpObject] != -1) DestroyDynamicObject(PumpData[i][pumpObject]);
			if(IsValidDynamic3DTextLabel(PumpData[i][pumpText3D])) DestroyDynamic3DTextLabel(PumpData[i][pumpText3D]);
			PumpData[i][pumpObject] = -1;

		    PumpData[i][pumpExists] = 0;
		    PumpData[i][pumpFuel] = 0;
		}
		format(string, sizeof(string), "DELETE FROM `pumps` WHERE `ID` = '%d'", BusinessData[bizid][bizID]);
		mysql_tquery(dbCon, string);
	}
	return 1;
}

Pump_GetFreeID()
{
	for (new i = 0; i < MAX_GAS_PUMPS; i ++) if (!PumpData[i][pumpExists]) {
	    return i;
	}
	return -1;
}

Pump_Delete(pumpid)
{
	if (pumpid != -1 && PumpData[pumpid][pumpExists])
	{
	    new
	        string[90];

		format(string, sizeof(string), "DELETE FROM `pumps` WHERE `pumpID` = '%d' LIMIT 1", PumpData[pumpid][pumpID]);
		mysql_tquery(dbCon, string);

		Total_Pumps_Created--;

        if (IsValidDynamic3DTextLabel(PumpData[pumpid][pumpText3D]))
		    DestroyDynamic3DTextLabel(PumpData[pumpid][pumpText3D]);

		if (IsValidDynamicObject(PumpData[pumpid][pumpObject]) && PumpData[pumpid][pumpObject] != -1)
		    DestroyDynamicObject(PumpData[pumpid][pumpObject]);

		PumpData[pumpid][pumpObject] = -1;

		foreach (new i : Player) if (PlayerData[i][pGasPump] == pumpid) {
			if(LoggedIn[i])
		    	StopRefilling(i);
		}
	    PumpData[pumpid][pumpExists] = false;
	    PumpData[pumpid][pumpFuel] = 0;
	}
	return 1;
}

StopRefilling(playerid)
{
    PlayerData[playerid][pGasPump] = -1;
   	PlayerData[playerid][pRefill] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pRefillPrice] = 0;
}

Pump_Refresh(pumpid){
	if (pumpid != -1 && PumpData[pumpid][pumpExists]){
		if (IsValidDynamic3DTextLabel(PumpData[pumpid][pumpText3D])) DestroyDynamic3DTextLabel(PumpData[pumpid][pumpText3D]);
		if (IsValidDynamicObject(PumpData[pumpid][pumpObject]) && PumpData[pumpid][pumpObject] != -1) DestroyDynamicObject(PumpData[pumpid][pumpObject]);
		PumpData[pumpid][pumpObject] = -1;
	    new string[256];
		format(string, sizeof(string), "[ปั้มน้ำมัน: %d]\n{FFFFFF}น้ำมันที่เหลืออยู่: %d ลิตร\n{FF0000}* ราคา ลิตรละ %s *\n{FFFFFF}( กด 'Y' เพื่อเติมน้ำมัน )\n( พิมพ์ '/gascan' เพื่อซื้อแกลลอนน้ำมัน )", pumpid, PumpData[pumpid][pumpFuel], FormatNumber(PumpData[pumpid][pumpPrice]));
		PumpData[pumpid][pumpText3D] = CreateDynamic3DTextLabel(string, COLOR_YELLOW, PumpData[pumpid][pumpPos][0], PumpData[pumpid][pumpPos][1], PumpData[pumpid][pumpPos][2], 15.0);
        PumpData[pumpid][pumpObject] = CreateDynamicObject(1676, PumpData[pumpid][pumpPos][0], PumpData[pumpid][pumpPos][1], PumpData[pumpid][pumpPos][2], 0.0, 0.0, PumpData[pumpid][pumpPos][3]);
	}
	return 1;
}

Pump_Save(pumpid)
{
	new
	    query[256];

	format(query, sizeof(query), "UPDATE `pumps` SET `pumpPosX` = '%.4f', `pumpPosY` = '%.4f', `pumpPosZ` = '%.4f', `pumpPosA` = '%.4f', `pumpFuel` = '%d', `pumpPrice` = '%d' WHERE `pumpID` = '%d'",
	    PumpData[pumpid][pumpPos][0],
	    PumpData[pumpid][pumpPos][1],
	    PumpData[pumpid][pumpPos][2],
		PumpData[pumpid][pumpPos][3],
	    PumpData[pumpid][pumpFuel],
		PumpData[pumpid][pumpPrice],
	    PumpData[pumpid][pumpID]
	);
	return mysql_tquery(dbCon, query);
}

Pump_Nearest(playerid)
{
    for (new i = 0; i != MAX_GAS_PUMPS; i ++) if (PumpData[i][pumpExists] && IsPlayerInRangeOfPoint(playerid, 4.0, PumpData[i][pumpPos][0], PumpData[i][pumpPos][1], PumpData[i][pumpPos][2]) && PumpData[i][pumpExists]) {
	    return i;
	}
	return -1;
}

stock IsPumpOccupied(pumpid)
{
	foreach (new i : Player) if (PlayerData[i][pRefill] != INVALID_VEHICLE_ID) {
		if(LoggedIn[i])
	    	if (PlayerData[i][pGasPump] == pumpid) return 1;
	}
	return 0;
}

forward OnPumpCreated(pumpid);
public OnPumpCreated(pumpid)
{
    PumpData[pumpid][pumpID] = cache_insert_id();
	Pump_Save(pumpid);

	return 1;
}

//CMD

CMD:pumpcmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[PUMPCMDS]: /makepump, /removepump, /setpumpprice, /setpump, /refreshpump");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

alias:makepump("สร้างปั้ม")
CMD:makepump(playerid)
{
	if(!LoggedIn[playerid]) return 0;
	new
		id,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
		return SendClientMessage(playerid, -1, "คุณสามารถสร้างปั้มก๊าซได้นอกอาคารเท่านั้น");

	id = Pump_Create(playerid);

	if (id == -1)
		return SendClientMessage(playerid, -1, "ธุรกิจนี้ได้สร้างปั้มก๊าซเกินขีดจำกัดแล้ว");

	format(string, sizeof(string), "คุณได้ประสบความสำเร็จในการสร้างปั้มก๊าซไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	EditDynamicObject(playerid, PumpData[id][pumpObject]);

	PlayerData[playerid][pEditPump] = id;
	return 1;
}

alias:removepump("ลบปั้ม")
CMD:removepump(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id = 0,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SendClientMessage(playerid, -1, "/removepump [pump id]");

	if ((id < 0 || id >= MAX_GAS_PUMPS) || !PumpData[id][pumpExists])
		return SendClientMessage(playerid, -1, "ไอดีปั้มไม่ถูกต้อง");

	Pump_Delete(id);
	format(string, sizeof(string), "คุณได้ประสบความสำเร็จในการทำลายปั้มไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:setpumpprice(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	new
		id = 0,
		amount,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "dd", id, amount))
		return SendClientMessage(playerid, -1, "/setpumpprice [pump id] [price]");

	if ((id < 0 || id >= MAX_GAS_PUMPS) || !PumpData[id][pumpExists])
		return SendClientMessage(playerid, -1, "ไอดีปั้มไม่ถูกต้อง");

	PumpData[id][pumpPrice] = amount;

	Pump_Refresh(id);
	Pump_Save(id);

	format(string, sizeof(string), "คุณตั้งราคาน้ำมันเชื้อเพลิง %d ให้ปั้มไอดี: %d.", amount, id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

alias:setpump("ตั้งค่าปั้ม")
CMD:setpump(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id = 0,
		amount,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "dd", id, amount))
		return SendClientMessage(playerid, -1, "/setpump [pump id] [fuel amount]");

	if ((id < 0 || id >= MAX_GAS_PUMPS) || !PumpData[id][pumpExists])
		return SendClientMessage(playerid, -1, "ไอดีปั้มไม่ถูกต้อง");

	if(amount > MAX_FUEL_GAS){
		return SendClientMessage(playerid, -1, "ต้องไม่เกิน 5,000");
	}

	PumpData[id][pumpFuel] = amount;

	Pump_Refresh(id);
	Pump_Save(id);

	format(string, sizeof(string), "คุณตั้งค่าน้ำมันเชื้อเพลิง %d ให้ปั้มไอดี: %d.", amount, id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:refreshpump(playerid, params[]){
	if(LoggedIn[playerid]){
		if(PlayerData[playerid][pAdmin] >= 1338){
			for(new i=0; i<MAX_GAS_PUMPS; i++) if(PumpData[i][pumpExists]){
				Pump_Refresh(i);
			}
			SendClientMessage(playerid, -1, "คุณได้รีปั้มน้ำมันสำเร็จ");
		}
	}
	return 1;
}

CMD:gascan(playerid, params[]){
	if(!LoggedIn[playerid])
		return 1;

	new idx = -1;
	if ((idx = Pump_Nearest(playerid)) != -1)
	{
		if(GetMoney(playerid) < PumpData[idx][pumpPrice] * 100)
			return SendClientMessageEx(playerid, COLOR_RED, "คุณมีเงินไม่พอ (ต้องการ: %s)", FormatNumber(PumpData[idx][pumpPrice] * 100));

		new id = PlayerInventory_AddItem(playerid, "Gas Can", 1650, 1);
		if (id == -1){
			return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
		}
		GiveMoney(playerid, -PumpData[idx][pumpPrice] * 100, "buy gascan");
		SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ซื้อแกลลอนน้ำมันในราคา: %s", FormatNumber(PumpData[idx][pumpPrice] * 100));
	}

	if(idx == -1)
		return ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ปั้มน้ำมัน");
	return 1;
}