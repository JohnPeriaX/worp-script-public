#if defined _inc_impl
	#undef _inc_impl
#endif

ResetInstallTrack(playerid){
	KillTimer(TrackerTime[playerid]);
	TrackerTime[playerid] = 0;
	TrackerPoint[playerid] = 0;

	for(new i=0; i<10; i++){
		GetCarIDTracker[playerid][i] = -1;
	}
}

Car_IsOwner(playerid, carid){
	if (!LoggedIn[playerid] || PlayerData[playerid][pID] == -1) return 0;

	if(carid != -1 && CarData[carid][carHave]){
		if (CarData[carid][carOwner] != 0 && CarData[carid][carOwner] == PlayerData[playerid][pID])
			return 1;
	}

	return 0;
}

Car_NearestIsJob(playerid){
	new
	    Float:fX,
	    Float:fY,
	    Float:fZ;

	for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
		GetVehiclePos(CarData[i][carVehicle], fX, fY, fZ);
		if (IsPlayerInRangeOfPoint(playerid, 5.0, fX, fY, fZ)) {
			return i;
		}
	}
	return -1;
}

Car_Nearest(playerid){
	new
	    Float:fX,
	    Float:fY,
	    Float:fZ;

	for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
		GetVehiclePos(CarData[i][carVehicle], fX, fY, fZ);
		if (IsPlayerInRangeOfPoint(playerid, 3.0, fX, fY, fZ)) {
			return i;
		}
	}
	return -1;
}

Car_GetCount(playerid){
	new
		count = 0;

	for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
		if (CarData[i][carOwner] == PlayerData[playerid][pID]){
			count++;
		}
	}
	return count;
}

Car_Create(ownerid, modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2){
	new string[128];
    for(new i=0; i<MAX_DYNAMIC_CARS; i++){
		if(CarData[i][carHave]) continue;

		CarData[i][carHave] = true;

		if (color1 == -1) color1 = random(127);

		if (color2 == -1) color2 = random(127);

		CarData[i][carModel] = modelid;
		CarData[i][carOwner] = ownerid;

		CarData[i][carPos][0] = x;
		CarData[i][carPos][1] = y;
		CarData[i][carPos][2] = z;
		CarData[i][carPos][3] = angle;

		CarData[i][carColor1] = color1;
		CarData[i][carColor2] = color2;
		CarData[i][carPaintjob] = -1;
		CarData[i][carLocked] = false;
		CarData[i][carGroup] = -1;
		CarData[i][carJob] = 0;
		CarData[i][carFuel] = 100;
		CarData[i][carLock] = 0;
		CarData[i][carInsurance] = 2;
		CarData[i][carDestroyed] = 0;
		CarData[i][carGPS] = 0;
		CarData[i][carHealth] = 1000;
		CarData[i][carNeonStatus] = 0;
		CarData[i][carNeonColor] = 0;
		CarData[i][carInsideGarage] = 0;
		CarData[i][carDestroyed] =  0;
		CarData[i][carRealSiren] = 0;

		for (new j = 0; j < 14; j ++){
			if (j < 5){
				CarData[i][carWeapons][j] = 0;
				CarData[i][carAmmo][j] = 0;
			}
			CarData[i][carMods][j] = 0;
		}

		CarData[i][carVehicle] = CreateVehicle(modelid, x, y, z, angle, color1, color2, -1);
		if (CarData[i][carVehicle] != INVALID_VEHICLE_ID) ResetVehicle(CarData[i][carVehicle]);
		
		mysql_format(dbCon, string, sizeof(string), "INSERT INTO `cars` (`carOwner`) VALUES(0)");
		mysql_tquery(dbCon, string, "OnCarCreated", "d", i);
		return i;
	}
	return -1;
}

Car_Delete(carid){
	if(carid != -1 && CarData[carid][carHave]){
		if (carid != -1){
			new
				string[64];

			format(string, sizeof(string), "DELETE FROM `cars` WHERE `carID` = '%d' LIMIT 1", CarData[carid][carID]);
			mysql_tquery(dbCon, string);

			if (IsValidVehicle(CarData[carid][carVehicle]) && CarData[carid][carVehicle] != INVALID_VEHICLE_ID){
				TRP_DestroyVehicle(CarData[carid][carVehicle], true);
				CarData[carid][carVehicle] = INVALID_VEHICLE_ID;
			}

			CarData[carid][carID] = 0;
			CarData[carid][carHave] = false;
			CarData[carid][carOwner] = 0;
			CarData[carid][carGroup] = -1;
			CarData[carid][carJob] = 0;
			CarData[carid][carNeonStatus] = 0;
			CarData[carid][carNeonColor] = 0;
			CarData[carid][carDestroyed] = 0;
		}
	}
	return 1;
}

Car_Save(carid){
	new
	    query[2056];

	if(carid != -1 && CarData[carid][carHave]){
		if (CarData[carid][carOwner] != 0){
			if (CarData[carid][carVehicle] != INVALID_VEHICLE_ID){
				for (new i = 0; i < 14; i ++) {
					CarData[carid][carMods][i] = GetVehicleComponentInSlot(CarData[carid][carVehicle], i);
				}
			}
			SaveVehicleDamage(CarData[carid][carVehicle]);
		}

		format(query, sizeof(query), "UPDATE `cars` SET `carModel` = '%d', `carOwner` = '%d', `carPosX` = '%.4f', `carPosY` = '%.4f', `carPosZ` = '%.4f', `carPosR` = '%.4f', `carColor1` = '%d', `carColor2` = '%d', `carPaintjob` = '%d', `carLocked` = '%d'",
			CarData[carid][carModel],
			CarData[carid][carOwner],
			CarData[carid][carPos][0],
			CarData[carid][carPos][1],
			CarData[carid][carPos][2],
			CarData[carid][carPos][3],
			CarData[carid][carColor1],
			CarData[carid][carColor2],
			CarData[carid][carPaintjob],
			CarData[carid][carLocked]
		);
		format(query, sizeof(query), "%s, `carMod1` = '%d', `carMod2` = '%d', `carMod3` = '%d', `carMod4` = '%d', `carMod5` = '%d', `carMod6` = '%d', `carMod7` = '%d', `carMod8` = '%d', `carMod9` = '%d', `carMod10` = '%d', `carMod11` = '%d', `carMod12` = '%d', `carMod13` = '%d', `carMod14` = '%d'",
			query,
			CarData[carid][carMods][0],
			CarData[carid][carMods][1],
			CarData[carid][carMods][2],
			CarData[carid][carMods][3],
			CarData[carid][carMods][4],
			CarData[carid][carMods][5],
			CarData[carid][carMods][6],
			CarData[carid][carMods][7],
			CarData[carid][carMods][8],
			CarData[carid][carMods][9],
			CarData[carid][carMods][10],
			CarData[carid][carMods][11],
			CarData[carid][carMods][12],
			CarData[carid][carMods][13]
		);
		format(query, sizeof(query), "%s, `carFuel` = '%d', `carGroup` = '%d', `carJob` = '%d', `carWeapon1` = '%d', `carWeapon2` = '%d', `carWeapon3` = '%d', `carWeapon4` = '%d', `carWeapon5` = '%d', `carAmmo1` = '%d', `carAmmo2` = '%d', `carAmmo3` = '%d', `carAmmo4` = '%d', `carAmmo5` = '%d'",
			query,
			CarData[carid][carFuel],
			CarData[carid][carGroup],
			CarData[carid][carJob],
			CarData[carid][carWeapons][0],
			CarData[carid][carWeapons][1],
			CarData[carid][carWeapons][2],
			CarData[carid][carWeapons][3],
			CarData[carid][carWeapons][4],
			CarData[carid][carAmmo][0],
			CarData[carid][carAmmo][1],
			CarData[carid][carAmmo][2],
			CarData[carid][carAmmo][3],
			CarData[carid][carAmmo][4]
		);
		format(query, sizeof(query), "%s, `carInsurance` = '%d', `carDamage1` = '%d', `carDamage2` = '%d', `carDamage3` = '%d', `carDamage4` = '%d', `carHealth` = '%f', `carDestroyed` = '%d', `carLock` = '%d', `carGPS` = '%d', `carPlate` = '%s', `carInsideGarage` = '%d', `carDrivingLicense` = '%d'",
			query,
			CarData[carid][carInsurance],
			CarData[carid][carDamage][0],
			CarData[carid][carDamage][1],
			CarData[carid][carDamage][2],
			CarData[carid][carDamage][3],
			CarData[carid][carHealth],
			CarData[carid][carDestroyed],
			CarData[carid][carLock],
			CarData[carid][carGPS],
			CarData[carid][carPlate],
			CarData[carid][carInsideGarage],
			CarData[carid][carDrivingLicense]
		);
		format(query, sizeof(query), "%s, `carNeonStatus` = '%d', `carNeonColor` = '%d'  WHERE `carID` = '%d'",
			query,
			CarData[carid][carNeonStatus],
			CarData[carid][carNeonColor],
			CarData[carid][carID]
		);
		return mysql_tquery(dbCon, query);
	}
	return 1;
}

forward OnCarCreated(carid);
public OnCarCreated(carid)
{
	if (carid == -1)
	    return 0;

	new insert_id = cache_insert_id();
	if(insert_id) {
		CarData[carid][carID] = insert_id;
		FetchVehiclePlate(carid);
		Car_Save(carid);
    }
	return 1;
}

stock isABikeVehicle(vehicleID) {
    switch(GetVehicleModel(vehicleID)) {
		case 481, 509, 510: return 1;
	}
	return 0;
}

task ReSpawnCar[1000](){
	if(StartRespawnCar == 1){
		if(TimerRespawnCar > 0){
			TimerRespawnCar--;
			
			if(TimerRespawnCar == 30)
				SendClientMessageToAll(COLOR_ORANGE, "[รียานพาหนะ]: อีก 30 วินาที ระบบจะทำการรียานพาหนะภายในเซิฟเวอร์กลับจุดเดิม, หากยานพาหนะที่มีผู้ใช้อยู่จะไม่ถูกรีกลับจุดเดิม");

			if(TimerRespawnCar == 10)
				SendClientMessageToAll(COLOR_ORANGE, "[รียานพาหนะ]: อีก 10 วินาที ระบบจะทำการรียานพาหนะภายในเซิฟเวอร์กลับจุดเดิม, หากยานพาหนะที่มีผู้ใช้อยู่จะไม่ถูกรีกลับจุดเดิม");

			if(TimerRespawnCar <= 0){
				TimerRespawnCar = 0;
				StartRespawnCar = 0;
				for (new i=1; i<MAX_VEHICLES; i++){
					if(i == INVALID_VEHICLE_ID) continue;
					if(i == BusRed) continue;
					if(i == BusYellow) continue;
					if(!IsVehicleEmpty(i)) RespawnVehicle(i);
				}
				SendClientMessageToAll(COLOR_ORANGE, "[รียานพาหนะ]: ระบบได้ทำการรียานพาหนะที่ไม่มีผู้ใช้กลับจุดเดิมแล้ว");
			}
		}
	}
	return 1;
}

static const stock g_arrVehicleNames[][] = {
    "Landstalker", "Bravura", "Buffalo", "Linerunner", "Perrenial", "Sentinel", "Dumper", "Firetruck", "Trashmaster",
    "Stretch", "Manana", "Infernus", "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam",
    "Esperanto", "Taxi", "Washington", "Bobcat", "Whoopee", "BF Injection", "Hunter", "Premier", "Enforcer",
    "Securicar", "Banshee", "Predator", "Bus", "Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Coach",
    "Cabbie", "Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral", "Squalo", "Seasparrow",
    "Pizzaboy", "Tram", "Trailer", "Turismo", "Speeder", "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair",
    "Berkley's RC Van", "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale", "Oceanic",
    "Sanchez", "Sparrow", "Patriot", "Quad", "Coastguard", "Dinghy", "Hermes", "Sabre", "Rustler", "ZR-350", "Walton",
    "Regina", "Comet", "BMX", "Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick", "News Chopper", "Rancher",
    "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring", "Sandking", "Blista Compact", "Police Maverick",
    "Boxville", "Benson", "Mesa", "RC Goblin", "Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher",
    "Super GT", "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster", "Stunt", "Tanker", "Roadtrain",
    "Nebula", "Majestic", "Buccaneer", "Shamal", "Hydra", "FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Tow Truck",
    "Fortune", "Cadrona", "SWAT Truck", "Willard", "Forklift", "Tractor", "Combine", "Feltzer", "Remington", "Slamvan",
    "Blade", "Streak", "Freight", "Vortex", "Vincent", "Bullet", "Clover", "Sadler", "Firetruck", "Hustler", "Intruder",
    "Primo", "Cargobob", "Tampa", "Sunrise", "Merit", "Utility", "Nevada", "Yosemite", "Windsor", "Monster", "Monster",
    "Uranus", "Jester", "Sultan", "Stratum", "Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito",
    "Freight Flat", "Streak Carriage", "Kart", "Mower", "Dune", "Sweeper", "Broadway", "Tornado", "AT-400", "DFT-30",
    "Huntley", "Stafford", "BF-400", "News Van", "Tug", "Trailer", "Emperor", "Wayfarer", "Euros", "Hotdog", "Club",
    "Freight Box", "Trailer", "Andromada", "Dodo", "RC Cam", "Launch", "LSPD Car", "SFPD Car", "LVPD Car",
    "Police Rancher", "Picador", "S.W.A.T", "Alpha", "Phoenix", "Glendale", "Sadler", "Luggage", "Luggage", "Stairs",
    "Boxville", "Tiller", "Utility Trailer"
};

stock ReturnVehicleName(vehicleid)
{
	new
		model = GetVehicleModel(vehicleid),
		name[32] = "None";

    if (model < 400 || model > 611)
	    return name;

	format(name, sizeof(name), g_arrVehicleNames[model - 400]);
	return name;
}

stock IsEngineVehicle(vehicleid)
{
	if(vehicleid == 0) return 0;

	static const g_aEngineStatus[] = {
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
	    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0
	};
    new modelid = GetVehicleModel(vehicleid);

    if (modelid < 400 || modelid > 611)
        return 0;

    return (g_aEngineStatus[modelid - 400]);
}

IsCharacterOnline(character){
	if (character == 0) return -1;
	foreach(new i : Player) if(LoggedIn[i]){
		if(PlayerData[i][pID] == character) return i;
	}
	return -1;
}

stock FuelVehicle(vehicleid)
{
	new id = Car_GetID(vehicleid);

	if (id != -1)
		return CarData[id][carFuel];

	return 0;
}

Car_Spawn(carid){
	if(carid != -1 && CarData[carid][carHave]){
		if(CarData[carid][carVehicle] == INVALID_VEHICLE_ID && CarData[carid][carModel] != 0){
			if(CarData[carid][carInsideGarage] == 0 && CarData[carid][carDestroyed] == 0){
				if (CarData[carid][carColor1] == -1) CarData[carid][carColor1] = random(127);
				if (CarData[carid][carColor2] == -1) CarData[carid][carColor2] = random(127);

				if(CarData[carid][carRealSiren] == 1) CarData[carid][carVehicle] = CreateVehicle(CarData[carid][carModel], CarData[carid][carPos][0], CarData[carid][carPos][1], CarData[carid][carPos][2], CarData[carid][carPos][3], CarData[carid][carColor1], CarData[carid][carColor2], -1, true);
				else if(CarData[carid][carRealSiren] == 0) CarData[carid][carVehicle] = CreateVehicle(CarData[carid][carModel], CarData[carid][carPos][0], CarData[carid][carPos][1], CarData[carid][carPos][2], CarData[carid][carPos][3], CarData[carid][carColor1], CarData[carid][carColor2], -1);

				if (CarData[carid][carVehicle] != INVALID_VEHICLE_ID){
					ResetVehicle(CarData[carid][carVehicle]);
					CarLoadNeon(carid);
					if (CarData[carid][carPaintjob] != -1) ChangeVehiclePaintjob(CarData[carid][carVehicle], CarData[carid][carPaintjob]);
					if (CarData[carid][carLocked]){
						new engine, lights, alarm, doors, bonnet, boot, objective;
						GetVehicleParamsEx(CarData[carid][carVehicle], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(CarData[carid][carVehicle], engine, lights, alarm, 1, bonnet, boot, objective);
					}
					
					for (new i = 0; i < 14; i ++) AddVehicleComponent(CarData[carid][carVehicle], CarData[carid][carMods][i]);
					if (CarData[carid][carOwner] > 0) SetVehicleDamage(CarData[carid][carVehicle]);

					if(strlen(CarData[carid][carPlate])) SetVehicleNumberPlate(CarData[carid][carVehicle],CarData[carid][carPlate]);
					else FetchVehiclePlate(carid);
					return 1;
				}
			}
		}
	}
	return 0;
}

CarLoadNeon(carid){
	if(carid != -1 && CarData[carid][carHave]){
		if(CarData[carid][carNeonStatus] == 1){
			if(CarData[carid][carNeonColor] == 1){ //น้ำเงิน
				if(IsPlayerOnBike(carid)){
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18648,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18648,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 1;
				}
				else{
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18648,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18648,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObjectEx(18648,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObjectEx(18648,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);
					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 1;
				}
			}
			else if(CarData[carid][carNeonColor] == 2){ //สีแดง
				if(IsPlayerOnBike(carid)){
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18647,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18647,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);

					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 2;
				}
				else{
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18647,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18647,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObjectEx(18647,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObjectEx(18647,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);

					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 2;
				}
			}
			else if(CarData[carid][carNeonColor] == 3){ //สีเขียว
				if(IsPlayerOnBike(carid)){
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18649,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18649,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);

					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 3;
				}
				else{
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18649,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18649,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObjectEx(18649,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObjectEx(18649,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);

					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 3;
				}
			}
			else if(CarData[carid][carNeonColor] == 4){ //สีขาว
				if(IsPlayerOnBike(carid)){
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18652,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18652,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);

					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 4;
				}
				else{
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18652,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18652,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObjectEx(18652,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObjectEx(18652,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);

					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 4;
				}
			}
			else if(CarData[carid][carNeonColor] == 5){ //สีชมพู
				if(IsPlayerOnBike(carid)){
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18651,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18651,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);

					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 5;
				}
				else{
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18651,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18651,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObjectEx(18651,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObjectEx(18651,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);

					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 5;
				}
			}
			else if(CarData[carid][carNeonColor] == 6){ //สีเหลือง
				if(IsPlayerOnBike(carid)){
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18650,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18650,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);

					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 6;
				}
				else{
					NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObjectEx(18650,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObjectEx(18650,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObjectEx(18650,0,0,0,0,0,0);
					NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObjectEx(18650,0,0,0,0,0,0);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
					AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);

					CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
					CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 6;
				}
			}
		}
	}
	return 1;
}

stock ResetVehicle(vehicleid){
	if (1 <= vehicleid <= MAX_VEHICLES){
		if(IsValidDynamicObject(GasOnVeh[vehicleid]) && GasOnVeh[vehicleid] != -1) DestroyDynamicObject(GasOnVeh[vehicleid]);

		if(IsValid3DTextLabel(vehicle3Dtext[vehicleid])) {
			Delete3DTextLabel(vehicle3Dtext[vehicleid]);
			vehiclecallsign[vehicleid] = 0;
		}
		if(IsValidDynamicObject(CowObject_Vehicle[vehicleid]) && CowObject_Vehicle[vehicleid] != -1) DestroyDynamicObject(CowObject_Vehicle[vehicleid]);
		if(Siren[vehicleid] != 0 && IsValidDynamicObject(SirenObject[vehicleid])) DestroyDynamicObject(SirenObject[vehicleid]);
		for(new i=0; i<4; i++){
			if(IsValidDynamicObject(NeonVehicle[vehicleid][i]) && NeonVehicle[vehicleid][i] != -1) DestroyDynamicObject(NeonVehicle[vehicleid][i]);
			NeonVehicle[vehicleid][i] = -1;
		}

		GasOnVeh[vehicleid] = -1;
		CowObject_Vehicle[vehicleid] = -1;
		SirenObject[vehicleid] = -1;

		IsGasOnVeh[vehicleid] = 0;
		CoreVehicles[vehicleid][vehTemporary] = false;
		CoreVehicles[vehicleid][vehSirenOn] = 0;
		CoreVehicles[vehicleid][vehGas] = 0;
		CoreVehicles[vehicleid][vehCloth] = 0;
		CoreVehicles[vehicleid][vehNeonStatus] = 0;
		CoreVehicles[vehicleid][vehNeonColor] = 0;
		CarHas_CowObject[vehicleid] = false;
	}
	return 1;
}

Car_GetID(vehicleid){
	for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]) {
		if(CarData[i][carVehicle] == vehicleid) return i;
	}
	return -1;
}

stock RandomPlate(){
	const len = 7, hyphenpos = 4;
	new plate[len+1];
	for (new i = 0; i < len; i++)
	{
	    if (i + 1 == hyphenpos)
	    {
	      plate[i] = '-';
	      continue;
	    }
	    if (i < hyphenpos) // letter or number?
	    { // letter
	      plate[i] = 'A' + random(26);
	    }
	    else
	    { // number
	      plate[i] = '0' + random(10);
	    }
	}
	return plate;
}

stock RepairVehicleEx(vehicleid){
	RepairVehicle(vehicleid);
	ResetVehicleDamage(vehicleid);
}

GetVehicleDriver(vehicleid) {
	foreach (new i : Player) {
		if (GetPlayerState(i) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) == vehicleid) return i;
	}
	return INVALID_PLAYER_ID;
}

stock SaveVehicleDamage(vehicleid)
{

	new slot = Car_GetID(vehicleid);
	if(slot > -1 && CarData[slot][carOwner] > 0)
	{
	    new panels,doors,lights,tires;
		GetVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
		CarData[slot][carDamage][0] = panels;
		CarData[slot][carDamage][1] = doors;
		CarData[slot][carDamage][2] = lights;
		CarData[slot][carDamage][3] = tires;
		GetVehicleHealth(vehicleid,CarData[slot][carHealth]);
	}
}

forward FetchVehiclePlate(carid);
public FetchVehiclePlate(carid)
{
	new
		name[32],
	    query[128];

	format(name, sizeof(name), RandomPlate());

    format(query, sizeof(query), "SELECT `carPlate` FROM `cars` WHERE `carPlate` = '%s' LIMIT 1", name);
	mysql_tquery(dbCon, query, "CheckVehiclePlate", "is", carid, name);
}

stock SetHoodStatus(vehicleid, bool:status)
{
	new
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, status, boot, objective);
}

stock GetHoodStatus(vehicleid)
{
	new
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if (bonnet != 1)
		return 0;

	return 1;
}

stock GetVehicleHood(vehicleid, &Float:x, &Float:y, &Float:z)
{
    if (!GetVehicleModel(vehicleid) || vehicleid == INVALID_VEHICLE_ID)
	    return (x = 0.0, y = 0.0, z = 0.0), 0;

	new
	    Float:pos[7]
	;
	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, pos[0], pos[1], pos[2]);
	GetVehiclePos(vehicleid, pos[3], pos[4], pos[5]);
	GetVehicleZAngle(vehicleid, pos[6]);

	x = pos[3] + (floatsqroot(pos[1] + pos[1]) * floatsin(-pos[6], degrees));
	y = pos[4] + (floatsqroot(pos[1] + pos[1]) * floatcos(-pos[6], degrees));
 	z = pos[5];

	return 1;
}

stock IsPlayerNearHood(playerid, vehicleid)
{
	new
		Float:fX,
		Float:fY,
		Float:fZ;

	GetVehicleHood(vehicleid, fX, fY, fZ);

	return (GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(vehicleid)) && IsPlayerInRangeOfPoint(playerid, 3.0, fX, fY, fZ);
}

stock IsPlayerNearBoot(playerid, vehicleid)
{
	new
		Float:fX,
		Float:fY,
		Float:fZ;

	GetVehicleBoot(vehicleid, fX, fY, fZ);

	return (GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(vehicleid)) && IsPlayerInRangeOfPoint(playerid, 1.0, fX, fY, fZ);
}

stock GetVehiclePanelsDamageStatus(vehicleid, &FrontLeft, &FrontRight, &RearLeft, &RearRight, &WindShield, &FrontBumper, &RearBumper)
{
	new Panels, Doorss, Lights, Tires;
	GetVehicleDamageStatus(vehicleid, Panels, Doorss, Lights, Tires);
	FrontLeft = Panels & 15;
	FrontRight = Panels >> 4 & 15;
	RearLeft = Panels >> 8 & 15;
	RearRight = Panels >> 12 & 15;
	WindShield = Panels >> 16 & 15;
	FrontBumper = Panels >> 20 & 15;
	RearBumper = Panels >> 24 & 15;
	return true;
}

stock SetTrunkStatus(vehicleid, bool:status)
{
	new
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, status, objective);
}

stock GetVehicleBoot(vehicleid, &Float:x, &Float:y, &Float:z)
{
	if (!GetVehicleModel(vehicleid) || vehicleid == INVALID_VEHICLE_ID)
	    return (x = 0.0, y = 0.0, z = 0.0), 0;

	new
	    Float:pos[7]
	;
	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, pos[0], pos[1], pos[2]);
	GetVehiclePos(vehicleid, pos[3], pos[4], pos[5]);
	GetVehicleZAngle(vehicleid, pos[6]);

	x = pos[3] - (floatsqroot(pos[1] + pos[1]) * floatsin(-pos[6], degrees));
	y = pos[4] - (floatsqroot(pos[1] + pos[1]) * floatcos(-pos[6], degrees));
 	z = pos[5];

	return 1;
}

stock GetTrunkStatus(vehicleid)
{
	new
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if (boot != 1)
		return 0;

	return 1;
}

stock GetVehicleDoorsDamageStatus(vehicleid, &Bonnet, &Boot, &FrontLeft, &FrontRight, &RearLeft, &RearRight)
{
	new Panels, Doors, Lights, Tires;
	GetVehicleDamageStatus(vehicleid, Panels, Doors, Lights, Tires);
	Bonnet = Doors & 7;
	Boot = Doors >> 8 & 7;
	FrontLeft = Doors >> 16 & 7;
	FrontRight = Doors >> 24 & 7;
	RearLeft = Doors >> 32 & 7;
	RearRight = Doors >> 40 & 7;
	return true;
}

stock IsDoorVehicle(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
		case 400..424, 426..429, 431..440, 442..445, 451, 455, 456, 458, 459, 466, 467, 470, 474, 475:
		    return 1;

		case 477..480, 482, 483, 486, 489, 490..492, 494..496, 498..500, 502..508, 514..518, 524..529, 533..536:
		    return 1;

		case 540..547, 549..552, 554..562, 565..568, 573, 575, 576, 578..580, 582, 585, 587..589, 596..605, 609:
			return 1;
	}
	return 0;
}

stock SetVehicleDamage(vehicleid){
	new slot;
	if((slot = Car_GetID(vehicleid)) != -1){
		UpdateVehicleDamageStatus(vehicleid,CarData[slot][carDamage][0],CarData[slot][carDamage][1],CarData[slot][carDamage][2],CarData[slot][carDamage][3]);
		if(CarData[slot][carHealth] > 310){
			SetVehicleHealth(vehicleid,CarData[slot][carHealth]);
		}
		else{
			SetVehicleHealth(vehicleid,310);
		}
	}
	return 1;
}

stock ResetVehicleDamage(vehicleid){
	new slot = Car_GetID(vehicleid);
	if(slot > -1){
		CarData[slot][carDamage][0] = 0;
		CarData[slot][carDamage][1] = 0;
		CarData[slot][carDamage][2] = 0;
		CarData[slot][carDamage][3] = 0;
		CarData[slot][carHealth] = 1000.0;
	}
}

forward CheckVehiclePlate(carid, plate[]);
public CheckVehiclePlate(carid, plate[]){
	new
		rows;

	cache_get_row_count(rows);
	if(!rows)
	{
		format(CarData[carid][carPlate], 32, plate);
		SetVehicleNumberPlate(CarData[carid][carVehicle],CarData[carid][carPlate]);
		Car_Save(carid);
	}
	else SetTimerEx("FetchVehiclePlate", 0, false, "d", carid);

	return 1;
}

ShowVehicleDestroy(playerid){
	new string[2056];
	new count = 0;
	for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
		if (Car_IsOwner(playerid, i)) {
			if(IsABoatSendModel(CarData[i][carModel])) continue;
			if(IsAHelicopterSendModel(CarData[i][carModel])) continue;
			if(CarData[i][carInsideGarage] == 0){
				format(string, sizeof(string), "%s[ ช่อง #%d | ยานพาหนะ: %s | ป้ายทะเบียน: %s ]\n", string, count+1, ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate]);
				GetCarIDDestroy[playerid][count] = i;
				count++;
			}
		}
	}
	if(count) Dialog_ShowEasy(playerid, PlayerVehicleDestroy, DIALOG_STYLE_LIST, "การกู้คืนยานพาหนะ", string, "เลือก", "ยกเลิก");
	else Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การกู้คืนยานพาหนะ", "คุณไม่มีรถที่ถูกทำลายอยู่เลย...", "ตกลง", "");
	return 1;
}

ShowBoatDestroy(playerid){
	new string[2056];
	new count = 0;
	for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
		if (Car_IsOwner(playerid, i)) {
			if(IsABoatSendModel(CarData[i][carModel])){
				if(CarData[i][carInsideGarage] == 0){
					format(string, sizeof(string), "%s[ ช่อง #%d | ยานพาหนะ: %s | ป้ายทะเบียน: %s ]\n", string, count+1, ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate]);
					GetCarIDDestroy[playerid][count] = i;
					count++;
				}
			}
		}
	} 
	if(count) Dialog_ShowEasy(playerid, PlayerVehicleDestroy, DIALOG_STYLE_LIST, "การกู้คืนยานพาหนะ", string, "เลือก", "ยกเลิก");
	else Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การกู้คืนยานพาหนะ", "คุณไม่มีเรือที่ถูกทำลายอยู่เลย...", "ตกลง", "");
	return 1;
}

ShowHeliDestroy(playerid){
	new string[2056];
	new count = 0;
	for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
		if (Car_IsOwner(playerid, i)) {
			if(IsAHelicopterSendModel(CarData[i][carModel])) {
				if(CarData[i][carInsideGarage] == 0){
					format(string, sizeof(string), "%s[ ช่อง #%d | ยานพาหนะ: %s | ป้ายทะเบียน: %s ]\n", string, count+1, ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate]);
					GetCarIDDestroy[playerid][count] = i;
					count++;
				}
			}
		}
	} 
	if(count) Dialog_ShowEasy(playerid, PlayerVehicleDestroy, DIALOG_STYLE_LIST, "การกู้คืนยานพาหนะ", string, "เลือก", "ยกเลิก");
	else Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การกู้คืนยานพาหนะ", "คุณไม่มีเรือที่ถูกทำลายอยู่เลย...", "ตกลง", "");
	return 1;
}

Dialog:PlayerVehicleDestroy(playerid, response, listitem, inputtext[]){
	if(!response)
		return 1;

	if(response){
		if(listitem >= 0 && listitem <= MAX_OWNABLE_CARS){
			new carid = GetCarIDDestroy[playerid][listitem];
			new string[150];
			GetCarIDDestroyConfirm[playerid] = carid;

			if(PlayerData[playerid][pPlayerFreeGetCar] > 0){
				PlayerData[playerid][pPlayerFreeGetCar]--;
				CarData[carid][carDestroyed] = 0;
				CarData[carid][carInsideGarage] = 0;
				SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้กู้คืนยานพาหนะ %s ด้วยใบกู้ยานพาหนะฟรี เรียบร้อยแล้ว", ReturnVehicleModelName(CarData[carid][carModel]));
				if(IsValidVehicle(CarData[carid][carVehicle]) && CarData[carid][carVehicle] != INVALID_VEHICLE_ID){
					new
						Float:x,
						Float:y,
						Float:z;

					GetPlayerPos(playerid, x, y, z);
					SetVehiclePosEx(CarData[carid][carVehicle], x + 2, y - 2, z);

					SetVehicleVirtualWorld(CarData[carid][carVehicle], GetPlayerVirtualWorld(playerid));
					LinkVehicleToInterior(CarData[carid][carVehicle], GetPlayerInterior(playerid));
					LoadVehSpeedoTextPlayer(playerid);
					PutPlayerInVehicleEx(playerid, CarData[carid][carVehicle], 0);
				}
				else{	
					Car_Spawn(carid);
					new
						Float:x,
						Float:y,
						Float:z;

					GetPlayerPos(playerid, x, y, z);
					SetVehiclePosEx(CarData[carid][carVehicle], x + 2, y - 2, z);

					SetVehicleVirtualWorld(CarData[carid][carVehicle], GetPlayerVirtualWorld(playerid));
					LinkVehicleToInterior(CarData[carid][carVehicle], GetPlayerInterior(playerid));
					LoadVehSpeedoTextPlayer(playerid);
					PutPlayerInVehicleEx(playerid, CarData[carid][carVehicle], 0);
				}
				
				RepairVehicleEx(CarData[carid][carVehicle]);
				Car_Save(carid);
			}
			else{
				if(CarData[carid][carInsurance] != 0){
					format(string, sizeof(string), "- ยานพาหนะ %s ของคุณมีใบประกันเหลืออยู่ %d ใบ\nคุณต้องการใช้หรือไม่?", ReturnVehicleModelName(CarData[carid][carModel]), CarData[carid][carInsurance]);
					Dialog_ShowEasy(playerid, UseInsurance, DIALOG_STYLE_MSGBOX, "กู้คืนยานพาหนะ", string, "ใช้", "ไม่ใช้");
				}
				else{
					if(PlayerData[playerid][pVip] == 1){
						pricevehdestroy[playerid] = 8000;
					}
					else if(PlayerData[playerid][pVip] == 2){
						pricevehdestroy[playerid] = 6000;
					}
					else if(PlayerData[playerid][pVip] == 3){
						pricevehdestroy[playerid] = 4000;
					}
					else if(PlayerData[playerid][pVip] == 0){
						pricevehdestroy[playerid] = 10000;
					}
					format(string, sizeof(string), "- ยานพาหนะคันนี้ของคุณไม่มีใบประกัน\nคุณแน่ใจหรือไม่ว่าที่จะต้องการกู้คืนยานพาหนะ %s ในราคา %s", ReturnVehicleModelName(CarData[carid][carModel]), FormatNumber(pricevehdestroy[playerid]));
					Dialog_ShowEasy(playerid, ConfirmVehicleDestroy, DIALOG_STYLE_MSGBOX, "การกู้คืนยานพาหนะ", string, "ตกลง", "ยกเลิก");
				}
			}
		}
	}
	return 1;
}

Dialog:UseInsurance(playerid, response, listitem, inputtext[]){
	if(!response){
		new string[256];
		new carid = GetCarIDDestroyConfirm[playerid];
		if(PlayerData[playerid][pVip] == 1){
			pricevehdestroy[playerid] = 8000;
		}
		else if(PlayerData[playerid][pVip] == 2){
			pricevehdestroy[playerid] = 6000;
		}
		else if(PlayerData[playerid][pVip] == 3){
			pricevehdestroy[playerid] = 4000;
		}
		else if(PlayerData[playerid][pVip] == 0){
			pricevehdestroy[playerid] = 10000;
		}
		format(string, sizeof(string), "- คุณเลือกที่จะไม่ใช้ใบประกัน!!\nคุณแน่ใจหรือไม่ว่าที่จะต้องการกู้คืนยานพาหนะ %s ในราคา %s", ReturnVehicleModelName(CarData[carid][carModel]), FormatNumber(pricevehdestroy[playerid]));
		Dialog_ShowEasy(playerid, ConfirmVehicleDestroy, DIALOG_STYLE_MSGBOX, "การกู้คืนยานพาหนะ", string, "ตกลง", "ยกเลิก");
	}
	if(response){
		new carid = GetCarIDDestroyConfirm[playerid];
		CarData[carid][carDestroyed] = 0;
		CarData[carid][carInsideGarage] = 0;
		CarData[carid][carInsurance] -= 1;
		SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้กู้คืนยานพาหนะ %s เรียบร้อยแล้ว", ReturnVehicleModelName(CarData[carid][carModel]));
		SendClientMessageEx(playerid, COLOR_YELLOW, "- ใบประกันของยานพาหนะ %s ของคุณเหลืออยู่ %d ใบ", ReturnVehicleModelName(CarData[carid][carModel]), CarData[carid][carInsurance]);
		if(IsValidVehicle(CarData[carid][carVehicle]) && CarData[carid][carVehicle] != INVALID_VEHICLE_ID){
			new
				Float:x,
				Float:y,
				Float:z;

			GetPlayerPos(playerid, x, y, z);
			SetVehiclePosEx(CarData[carid][carVehicle], x + 2, y - 2, z);

			SetVehicleVirtualWorld(CarData[carid][carVehicle], GetPlayerVirtualWorld(playerid));
			LinkVehicleToInterior(CarData[carid][carVehicle], GetPlayerInterior(playerid));
			LoadVehSpeedoTextPlayer(playerid);
			PutPlayerInVehicleEx(playerid, CarData[carid][carVehicle], 0);
		}
		else{	
			Car_Spawn(carid);
			new
				Float:x,
				Float:y,
				Float:z;

			GetPlayerPos(playerid, x, y, z);
			SetVehiclePosEx(CarData[carid][carVehicle], x + 2, y - 2, z);

			SetVehicleVirtualWorld(CarData[carid][carVehicle], GetPlayerVirtualWorld(playerid));
			LinkVehicleToInterior(CarData[carid][carVehicle], GetPlayerInterior(playerid));
			LoadVehSpeedoTextPlayer(playerid);
			PutPlayerInVehicleEx(playerid, CarData[carid][carVehicle], 0);
		}
		
		RepairVehicleEx(CarData[carid][carVehicle]);
		Car_Save(carid);
	}
	return 1;
}

Dialog:ConfirmVehicleDestroy(playerid, response, listitem, inputtext[]){
	if(!response)
		return 1;

	if(response){

		if(PlayerData[playerid][pVip] == 1){
			pricevehdestroy[playerid] = 8000;
		}
		else if(PlayerData[playerid][pVip] == 2){
			pricevehdestroy[playerid] = 6000;
		}
		else if(PlayerData[playerid][pVip] == 3){
			pricevehdestroy[playerid] = 4000;
		}
		else if(PlayerData[playerid][pVip] == 0){
			pricevehdestroy[playerid] = 10000;
		}

		if(GetMoney(playerid) < pricevehdestroy[playerid])
			return ErrorMsg(playerid, "คุณมีเงินไม่พอ");
			
		new carid = GetCarIDDestroyConfirm[playerid];
		CarData[carid][carDestroyed] = 0;
		CarData[carid][carInsideGarage] = 0;
		SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้กู้คืนยานพาหนะ %s ของคุณในราคา %s เรียบร้อยแล้ว", ReturnVehicleModelName(CarData[carid][carModel]), FormatNumber(pricevehdestroy[playerid]));
		GiveMoney(playerid, -pricevehdestroy[playerid], "revive vehicle");
		if(IsValidVehicle(CarData[carid][carVehicle]) && CarData[carid][carVehicle] != INVALID_VEHICLE_ID){
			new
				Float:x,
				Float:y,
				Float:z;

			GetPlayerPos(playerid, x, y, z);
			SetVehiclePosEx(CarData[carid][carVehicle], x + 2, y - 2, z);

			SetVehicleVirtualWorld(CarData[carid][carVehicle], GetPlayerVirtualWorld(playerid));
			LinkVehicleToInterior(CarData[carid][carVehicle], GetPlayerInterior(playerid));
			LoadVehSpeedoTextPlayer(playerid);
			PutPlayerInVehicleEx(playerid, CarData[carid][carVehicle], 0);
		}
		else{
			Car_Spawn(carid);

			new
				Float:x,
				Float:y,
				Float:z;

			GetPlayerPos(playerid, x, y, z);
			SetVehiclePosEx(CarData[carid][carVehicle], x + 2, y - 2, z);

			SetVehicleVirtualWorld(CarData[carid][carVehicle], GetPlayerVirtualWorld(playerid));
			LinkVehicleToInterior(CarData[carid][carVehicle], GetPlayerInterior(playerid));
			LoadVehSpeedoTextPlayer(playerid);
			PutPlayerInVehicleEx(playerid, CarData[carid][carVehicle], 0);
		}
		RepairVehicleEx(CarData[carid][carVehicle]);
		Car_Save(carid);
	}
	return 1;
}

forward Car_Load();
public Car_Load(){
	new rows, str[32];
    cache_get_row_count(rows);
	for (new i = 0; i < rows; i++) if(i < MAX_DYNAMIC_CARS){
		CarData[i][carHave] = true;
     	cache_get_value_name_int(i, "carID", CarData[i][carID]);
     	cache_get_value_name_int(i, "carModel", CarData[i][carModel]);
     	cache_get_value_name_int(i, "carOwner", CarData[i][carOwner]);
     	cache_get_value_name_float(i, "carPosX", CarData[i][carPos][0]);
     	cache_get_value_name_float(i, "carPosY", CarData[i][carPos][1]);
     	cache_get_value_name_float(i, "carPosZ", CarData[i][carPos][2]);
     	cache_get_value_name_float(i, "carPosR", CarData[i][carPos][3]);
     	cache_get_value_name_int(i, "carColor1", CarData[i][carColor1]);
     	cache_get_value_name_int(i, "carColor2", CarData[i][carColor2]);
     	cache_get_value_name_int(i, "carPaintjob", CarData[i][carPaintjob]);
     	cache_get_value_name_int(i, "carLocked", CarData[i][carLocked]);
      	cache_get_value_name_int(i, "carGroup", CarData[i][carGroup]);
       	cache_get_value_name_int(i, "carJob", CarData[i][carJob]);
        cache_get_value_name_int(i, "carFuel", CarData[i][carFuel]);
        cache_get_value_name_int(i, "carInsurance", CarData[i][carInsurance]);
        cache_get_value_name_int(i, "carDamage1", CarData[i][carDamage][0]);
        cache_get_value_name_int(i, "carDamage2", CarData[i][carDamage][1]);
        cache_get_value_name_int(i, "carDamage3", CarData[i][carDamage][2]);
        cache_get_value_name_int(i, "carDamage4", CarData[i][carDamage][3]);
        cache_get_value_name_int(i, "carDestroyed", CarData[i][carDestroyed]);
		cache_get_value_name_float(i, "carHealth", CarData[i][carHealth]);
        cache_get_value_name_int(i, "carLock", CarData[i][carLock]);
 		cache_get_value_name_int(i, "carGPS", CarData[i][carGPS]);
		cache_get_value_name(i, "carPlate", CarData[i][carPlate], 32);
		cache_get_value_name_int(i, "carInsideGarage", CarData[i][carInsideGarage]);
		cache_get_value_name_int(i, "carDrivingLicense", CarData[i][carDrivingLicense]);

		cache_get_value_name_int(i, "carNeonStatus", CarData[i][carNeonStatus]);
		cache_get_value_name_int(i, "carNeonColor", CarData[i][carNeonColor]);

		//
		for (new j = 0; j < 14; j ++){
	        format(str, sizeof(str), "carMod%d", j + 1);
         	cache_get_value_name_int(i, str, CarData[i][carMods][j]);
	    }
		
		Total_Car++;
		CarData[i][carRealSiren] = 0;
		CarData[i][carVehicle] = INVALID_VEHICLE_ID;
		if(CarData[i][carOwner] != 0) CarData[i][carInsideGarage] = 1;
		else Car_Spawn(i);
	}
	printf("(( [MYSQL]: Load %d Cars Successfully ))", Total_Car);
	return 1;
}

stock PutPlayerInVehicleEx(playerid,vehicleid,seatid){
	PlayerEnterTime[playerid] = vehicleid;
	PutPlayerInVehicle(playerid,vehicleid,seatid);
}

CMD:carcmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[JOBCMDS]: /makecar, /removecar, /editcar");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

CMD:makecar(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		model[32],
		color1,
		color2,
		id = -1,
		type = 0,
		string[128];

    if (PlayerData[playerid][pAdmin] < 1338)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "s[32]I(-1)I(-1)I(0)", model, color1, color2, type))
 	{
	 	SendClientMessage(playerid, -1, "/makecar [model id/name] [color 1] [color 2]");
	 	return 1;
	}
	if ((model[0] = GetVehicleModelByName(model)) == 0)
	    return SendClientMessage(playerid, -1, "ไอดีโมเดลไม่ถูกต้อง");

	new
	    Float:x,
		Float:y,
		Float:z,
		Float:angle;

    GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);

	id = Car_Create(0, model[0], x, y, z, angle, color1, color2);

	if (id == -1)
	    return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");

    SetEngineStatus(id, true);
	SetLightStatus(id, true);
    PutPlayerInVehicleEx(playerid, id, 0);
	SetPlayerPosExten(playerid, x, y, z + 2);
	format(string, sizeof(string), "คุณประสบความสำเร็จในการสร้างยานพาหนะไอดี: %d", CarData[id][carVehicle]);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:removecar(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	new
	    id = 0,
	    string[128];

    if (PlayerData[playerid][pAdmin] < 1338)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id)){
	 	if (IsPlayerInAnyVehicle(playerid))
		 	id = GetPlayerVehicleID(playerid);

		else return SendClientMessage(playerid, -1, "/removecar [vehicle id]");
	}
	if (!IsValidVehicle(id) || Car_GetID(id) == -1)
	    return SendClientMessage(playerid, -1, "คุณระบุไอดียานพาหนะไม่ถูกต้อง");

	new carid = Car_GetID(id);

	if(CarData[carid][carVehicle] != id) return ErrorMsg(playerid, "ไอดียานพาหนะไม่ถูกต้อง");

	Car_Delete(carid);
	format(string, sizeof(string), "คุณประสบความสำเร็จในการทำลายยานพาหนะไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:refuelall(playerid, params[]){

	new string[128];
	if(!LoggedIn[playerid]) return 0;

	if (PlayerData[playerid][pAdmin] < 5)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
		CarData[i][carFuel] = 100;
	}
		
	format(string, sizeof(string), "%s ได้เติมน้ำมันหมดทั้งเซิฟแล้ว", ReturnRoleplayName(playerid));
	SendAdminsMessage(1, COLOR_GRAY, string);
	return 1;
}

CMD:editcar(playerid, params[])
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
	 	SendClientMessage(playerid, -1, "/editcar [id] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, group, job, color1, color2, rent, driving");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} mileage, lock, destroyed, fuel, insurance, repair, battery, engine");
		return 1;
	}
	if (!IsValidVehicle(id) || Car_GetID(id) == -1)
	    return SendClientMessage(playerid, -1, "คุณระบุไอดียานพาหนะไม่ถูกต้อง");

	id = Car_GetID(id);

	if (!strcmp(type, "location", true))
	{
	    if (GetPlayerVehicleID(playerid) == CarData[id][carVehicle])
	    {
			GetVehiclePos(CarData[id][carVehicle], CarData[id][carPos][0], CarData[id][carPos][1], CarData[id][carPos][2]);
			GetVehicleZAngle(CarData[id][carVehicle], CarData[id][carPos][3]);
		}
		else
		{
	 		GetPlayerPos(playerid, CarData[id][carPos][0], CarData[id][carPos][1], CarData[id][carPos][2]);
			GetPlayerFacingAngle(playerid, CarData[id][carPos][3]);
		}

		Car_Save(id);
		TRP_DestroyVehicle(CarData[id][carVehicle], true);
		CarData[id][carVehicle] = INVALID_VEHICLE_ID;
		Car_Spawn(id);

		SetPlayerPosExten(playerid, CarData[id][carPos][0], CarData[id][carPos][1], CarData[id][carPos][2] + 2.0);
		format(string, sizeof(string), "%s ได้ปรับตำแหน่งของพาหนะไอดี: %d", ReturnRoleplayName(playerid), CarData[id][carVehicle]);
		SendAdminsMessage(1, COLOR_GRAY, string);

	}
	else if (!strcmp(type, "group", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
     	{
     	    SendClientMessage(playerid, -1, "/editcar [id] [group] [type]");
		 	return 1;
		}

		if(typeint == -1){
			CarData[id][carJob] = 0;
			CarData[id][carGroup] = -1;
			format(string, sizeof(string), "%s ได้ปรับกลุ่มของยานพาหนะไอดี: %d เป็น ประชาชน", ReturnRoleplayName(playerid), CarData[id][carVehicle]);
			SendAdminsMessage(1, COLOR_GRAY, string);
			Car_Save(id);
			TRP_DestroyVehicle(CarData[id][carVehicle], true);
			CarData[id][carVehicle] = INVALID_VEHICLE_ID;
			Car_Spawn(id);
			return 1;
		}

        CarData[id][carJob] = 0;
		CarData[id][carGroup] = typeint;

		Car_Save(id);
		TRP_DestroyVehicle(CarData[id][carVehicle], true);
		CarData[id][carVehicle] = INVALID_VEHICLE_ID;
		Car_Spawn(id);
		format(string, sizeof(string), "%s ได้ปรับกลุ่มของยานพาหนะไอดี: %d เป็น %s", ReturnRoleplayName(playerid), CarData[id][carVehicle], GroupData[typeint][groupName]);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "job", true))
	{
		new typeint;

		if (sscanf(string, "d", typeint))
		{
			SystemMsg(playerid, "/editcar [id] [job] [type]");
			SendClientMessage(playerid, COLOR_YELLOW, "[ตัวเลือก]:{FFFFFF} 1-25");
			return 1;
		}
		if (typeint < 0 || typeint > MAX_DYNAMIC_JOBS)
			return ErrorMsg(playerid, "ไอดีงานที่ระบุไม่ถูกต้อง");

		CarData[id][carGroup] = -1;
		CarData[id][carJob] = typeint;

		format(CarData[id][carPlate], 32, Job_GetPlateName(typeint));
		SetVehicleNumberPlate(CarData[id][carVehicle], CarData[id][carPlate]);

		Car_Save(id);
		TRP_DestroyVehicle(CarData[id][carVehicle], true);
		CarData[id][carVehicle] = INVALID_VEHICLE_ID;
		Car_Spawn(id);
		format(string, sizeof(string), "%s ได้ปรับงานของยานพาหนะไอดี: %d เป็นของ: %s(%d)", ReturnRoleplayName(playerid), CarData[id][carVehicle], Job_GetName(typeint), typeint);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
    else if (!strcmp(type, "color1", true))
	{
	    new color1;

	    if (sscanf(string, "d", color1))
			return SendClientMessage(playerid, -1, "/editcar [id] [color1] [color 1]");

		if (color1 < 0 || color1 > 255)
		    return SendClientMessage(playerid, -1, "สีที่ระบุต้องไม่ต่ำกว่า 0 หรือมากกว่า 255");

		CarData[id][carColor1] = color1;
		ChangeVehicleColor(CarData[id][carVehicle], CarData[id][carColor1], CarData[id][carColor2]);

		Car_Save(id);
		format(string, sizeof(string), "%s ได้ปรับสีที่ 1 ของยานพาหนะไอดี: %d เป็น %d", ReturnRoleplayName(playerid), CarData[id][carVehicle], color1);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
    else if (!strcmp(type, "color2", true))
	{
	    new color2;

	    if (sscanf(string, "d", color2))
			return SendClientMessage(playerid, -1, "/editcar [id] [color2] [color 2]");

		if (color2 < 0 || color2 > 255)
		    return SendClientMessage(playerid, -1, "สีที่ระบุต้องไม่ต่ำกว่า 0 หรือมากกว่า 255");

		CarData[id][carColor2] = color2;
		ChangeVehicleColor(CarData[id][carVehicle], CarData[id][carColor1], CarData[id][carColor2]);

		Car_Save(id);
		format(string, sizeof(string), "%s ได้ปรับสีที่ 2 ของยานพาหนะไอดี: %d เป็น %d", ReturnRoleplayName(playerid), CarData[id][carVehicle], color2);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "lock", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
     	{
     	    SendClientMessage(playerid, -1, "/editcar [id] [lock] [type]");
		 	SendClientMessage(playerid, COLOR_YELLOW, "[TYPES]:{FFFFFF} 0-4");
		 	return 1;
		}
		if (typeint < 0 || typeint > 4)
		    return SendClientMessage(playerid, -1, "ประเภทที่ระบุต้องไม่ต่ำกว่า 0 หรือมากกว่า 4");

        CarData[id][carLock] = typeint;

		Car_Save(id);
		format(string, sizeof(string), "%s ได้ปรับระบบล็อคของยานพาหนะไอดี: %d เป็น %d", ReturnRoleplayName(playerid), CarData[id][carVehicle], typeint);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "destroyed", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
     	{
     	    SendClientMessage(playerid, -1, "/editcar [id] [destroyed] [number]");
			SendClientMessage(playerid, -1, "[0]:ไม่ถูกทำลาย, [1]:ถูกทำลาย");
		 	return 1;
		}

		if(typeint < 0 || typeint > 1)
			return ErrorMsg(playerid, "ต้องกรอกระหว่าง 0 หรือ 1 เท่านั้น");

        CarData[id][carDestroyed] = typeint;

		Car_Save(id);
		TRP_DestroyVehicle(CarData[id][carVehicle], true);
		CarData[id][carVehicle] = INVALID_VEHICLE_ID;
		Car_Spawn(id);
		format(string, sizeof(string), "%s ได้ปรับการถูกทำลายของยานพาหนะไอดี: %d เป็น %d", ReturnRoleplayName(playerid), CarData[id][carVehicle], typeint);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "fuel", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
     	{
     	    SendClientMessage(playerid, -1, "/editcar [id] [fuel] [number]");
		 	return 1;
		}

        CarData[id][carFuel] = typeint;

		Car_Save(id);
		format(string, sizeof(string), "%s ได้ปรับน้ำมันของยานพาหนะไอดี: %d เป็น %d", ReturnRoleplayName(playerid), CarData[id][carVehicle], typeint);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "rent", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
     	{
     	    SendClientMessage(playerid, -1, "/editcar [id] [rent] [0 = ไม่เปิดให้เช่า | 1 = เปิดให้เช่า]");
		 	return 1;
		}

		if (typeint < 0 || typeint > 1)
		    return SendClientMessage(playerid, -1, "ประเภทที่ระบุต้องไม่ต่ำกว่า 0 หรือ 1");

		Car_Save(id);
		format(string, sizeof(string), "%s ได้ปรับ Rent ยานพาหนะไอดี: %d เป็น %d", ReturnRoleplayName(playerid), CarData[id][carVehicle], typeint);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if(!strcmp(type, "driving", true)){
		if(!CarData[id][carDrivingLicense]){
			CarData[id][carGroup] = -1;
			CarData[id][carJob] = 0;
			CarData[id][carDrivingLicense] = true;
			Car_Save(id);
			format(string, sizeof(string), "%s ได้ปรับยานพาหนะไอดี: %d เป็น เป็นยานพาหนะสำหรับทำใบขับขี่", ReturnRoleplayName(playerid), CarData[id][carVehicle]);
			SendAdminsMessage(1, COLOR_GRAY, string);
		}
		else if(CarData[id][carDrivingLicense]){
			CarData[id][carDrivingLicense] = false;
			Car_Save(id);
			format(string, sizeof(string), "%s ได้ปรับยานพาหนะไอดี: %d เป็น เป็นปกติ", ReturnRoleplayName(playerid), CarData[id][carVehicle]);
			SendAdminsMessage(1, COLOR_GRAY, string);
		}
	}
	else if (!strcmp(type, "repair", true))
	{
		if(GetVehicleDriver(CarData[id][carVehicle]) != INVALID_PLAYER_ID)
			SetPVarInt(GetVehicleDriver(CarData[id][carVehicle]), "VehicleRepair", 1);

	    RepairVehicleEx(CarData[id][carVehicle]);
		Car_Save(id);
		format(string, sizeof(string), "%s ได้ซ่อมยานพาหนะไอดี: %d", ReturnRoleplayName(playerid), CarData[id][carVehicle]);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "insurance", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
     	{
     	    SendClientMessage(playerid, -1, "/editcar [id] [insurance] [number]");
		 	return 1;
		}

        CarData[id][carInsurance] = typeint;

		Car_Save(id);
		format(string, sizeof(string), "%s ได้ปรับประกันภัยของยานพาหนะไอดี: %d เป็น %d", ReturnRoleplayName(playerid), CarData[id][carVehicle], typeint);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	return 1;
}

CMD:givecar(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		userid,
	    model[32],
	    string[128];

    if (PlayerData[playerid][pAdmin] < 1338)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "us[32]", userid, model))
	    return SendClientMessage(playerid, -1, "/givecar [playerid/name] [modelid/name]");

	if (Car_GetCount(userid) >= MAX_OWNABLE_CARS)
	    return SendClientMessage(playerid, -1, "ผู้เล่นนี้เป็นเจ้าของยานพาหนะจนเต็มแล้ว");

    if ((model[0] = GetVehicleModelByName(model)) == 0)
	    return SendClientMessage(playerid, -1, "รุ่นไม่ถูกต้อง");

	new
	    Float:x,
		Float:y,
		Float:z,
		Float:angle,
		id = -1;

	new world, int;

	int = GetPlayerInterior(userid);
	world = GetPlayerVirtualWorld(userid);

    GetPlayerPos(userid, x, y, z);
	GetPlayerFacingAngle(userid, angle);

	id = Car_Create(PlayerData[userid][pID], model[0], x, y + 2, z + 1, angle, random(127), random(127));

	if (id == -1)
	    return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");

	LinkVehicleToInterior(id, int);
	SetVehicleVirtualWorld(id, world);

    format(string, sizeof(string), "คุณได้สร้างยานพาหนะไอดี: %d สำหรับ %s", CarData[id][carVehicle], ReturnName(userid));
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:respawncar(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new vehicleid;

    if (PlayerData[playerid][pAdmin] < 2)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", vehicleid))
	    return SystemMsg(playerid, "/respawncar [veh]");

	if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
		return ErrorMsg(playerid, "คุณระบุไอดียานพาหนะไม่ถูกต้อง");

	RespawnVehicle(vehicleid);
	SendClientMessageEx(playerid, -1, "คุณได้ส่งยานพาหนะกลับไปจุดเกิด: %d", vehicleid);

	return 1;
}

stock GetIDFromName(sqlid)
{
	new pname[MAX_NAME], query[64], string[64];
	mysql_format(dbCon, query, sizeof(query), "SELECT * FROM `characters` WHERE `ID` = %d LIMIT 1", sqlid);
	mysql_query(dbCon, query);

    new
		rows;

   	cache_get_row_count(rows);
    if(rows)
    {
		cache_get_value_name(0, "Username", string, 64);
		format(pname, sizeof(pname), string);
    }
	return pname;
}

CMD:carvars(playerid,params[])
{
	if(!LoggedIn[playerid]) return 0;

    if (PlayerData[playerid][pAdmin] > 2)
    {
		new vehicleid;
		if (sscanf(params, "d", vehicleid))
			return SystemMsg(playerid, "/carvars [vehicleid]");

        new slot = Car_GetID(vehicleid);

        if(slot > -1){
	        new str[128];
	        new engineon = (GetEngineStatus(vehicleid)) ? 1 :0;

	        SendClientMessage(playerid,COLOR_WHITE,"|---------Vehicle Stats----------|");
	        format(str,sizeof(str),"VID:[%d] Model:[%d] Color1:[%d] Color2:[%d] Owner:[%d] Owner Name:[%s] ID:[%d]",
	        CarData[slot][carID],
	        CarData[slot][carModel],
	        CarData[slot][carColor1],
	        CarData[slot][carColor2],
	        CarData[slot][carOwner],
	        CarData[slot][carOwner] ? GetIDFromName(CarData[slot][carOwner]) : ("None"),
	        CarData[slot][carVehicle]);
	        SendClientMessage(playerid,COLOR_WHITE,str);
	        format(str,sizeof(str),"Fuel:[%d] Insurance:[%d] Lock:[%d] Locked:[%d] Destroyed:[%d]",
	        CarData[slot][carFuel],
	        CarData[slot][carInsurance],
	        CarData[slot][carLock],
	        CarData[slot][carLocked],
	        CarData[slot][carDestroyed]);
	        SendClientMessage(playerid,COLOR_WHITE,str);
	        format(str,sizeof(str),"Group:[%d] Job:[%d] Paintjob:[%d] Engine:[%d] Plate:[%s]",
	        CarData[slot][carGroup],
	        CarData[slot][carJob],
	        CarData[slot][carPaintjob],
			engineon,
			CarData[slot][carPlate]);
	        SendClientMessage(playerid,COLOR_WHITE,str);
			return 1;
		}
		else
		{
		    ErrorMsg(playerid,"พาหนะคันนี้ไม่สามารถดูข้อมูลได้");
		    return 1;

		}
	}
	else
	{
	    ErrorMsg(playerid,"คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");
	    return 1;

	}
}

InstallTrackerForCar(playerid){

	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ErrorMsg(playerid, "คุณจำเป็นต้องอยู่บนพื้น");

	new id = -1;
	new string[128];
	if((id = Car_Nearest(playerid)) != -1){
		if(CarData[id][carOwner] == 0) return ErrorMsg(playerid, "สำหรับยานพาหนะที่มีเจ้าของเท่านั้น");
		if(CarData[id][carGPS] == 0){
			CarIDInstallTracker[playerid] = id;
			format(string, sizeof(string), "คุณแน่ใจหรือไม่?, ที่จะติดตั้งระบบ Tracker ให้กับยานพาหนะ %s คันนี้", ReturnVehicleName(CarData[id][carVehicle]));
			Dialog_ShowEasy(playerid, ConfirmInstallTracker, DIALOG_STYLE_MSGBOX, "ระบบติดตั้ง", string, "ตกลง", "ยกเลิก");
		}
		else return ErrorMsg(playerid, "รถคันนี้มีระบบ Tracker อยู่แล้ว");
	}

	if(id == -1) return ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ยานพาหนะใดๆ");
	return 1;
}

Dialog:ConfirmInstallTracker(playerid, response, listitem, inputtext[]){
	if(!response) return 1;
	if(response){
		if(CarIDInstallTracker[playerid] != -1){
			StartingInstallTracker(playerid, CarIDInstallTracker[playerid]);
		}
	}
	return 1;
}

StartingInstallTracker(playerid, carid){
	if(Car_Nearest(playerid) != carid) return ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ยานพาหนะ");
	if(GetEngineStatus(CarData[carid][carVehicle])) return ErrorMsg(playerid, "จำเป็นต้องดับเครื่องยนต์ก่อน");
	//ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0x00FFC5AA, 100.000000, 0);
	CreatePlayerProgressbar_Job(playerid, 0x00FFC5AA);
	TrackerPoint[playerid] = 0;
	TrackerTime[playerid] = SetTimerEx("InstallingTracker", 500, 0, "ii", playerid, carid);
	TogglePlayerControllable(playerid, 0);
	return 1;
}

forward InstallingTracker(playerid, carid);
public InstallingTracker(playerid, carid){
	if(LoggedIn[playerid]){
		new string[128];
		if(TrackerPoint[playerid] < 100){
			TrackerPoint[playerid]++;
			SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], TrackerPoint[playerid]);
			format(string,sizeof(string),"Installing... (%d)", TrackerPoint[playerid]);
			PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
			//GameTextForPlayer(playerid, string, 1000, 3);
			ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
			TrackerTime[playerid] = SetTimerEx("InstallingTracker", 500, 0, "ii", playerid, carid);
		}
		else if(TrackerPoint[playerid] >= 100){
			KillTimer(TrackerTime[playerid]);
			TrackerPoint[playerid] = 0;
			DestroyPlayerProgressbar_Job(playerid);

			if(carid != -1){
				CarData[carid][carGPS] = 1;
				Car_Save(carid);
				SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ติดตั้งระบบ Track สำหรับติดตามยานพาหนะให้กับ %s เรียบร้อยแล้ว", ReturnVehicleName(CarData[carid][carVehicle]));
				PlayerInventory_Remove(playerid, "Car Tracker Tool");
			}
			CarIDInstallTracker[playerid] = -1;
			TogglePlayerControllable(playerid, 1);
		}
	}
	
	return 1;
}

UseTrackerRemote(playerid){
	new count = 0;
	new string[128];
	for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
		if (Car_IsOwner(playerid, i)) {
			if(CarData[i][carGPS] == 1 && CarData[i][carInsideGarage] == 0){
				format(string, sizeof(string), "%s[ ยานพาหนะ: %s | ป้ายทะเบียน: %s [เลือกเพื่อติดตาม] ]\n", string, ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate]);
				GetCarIDTracker[playerid][count] = i;
				count++;
			}
		}
	}
	if(count) Dialog_ShowEasy(playerid, TrackerVehicle, DIALOG_STYLE_LIST, "ระบบติดตามยานพาหนะ", string, "เลือก", "ยกเลิก");
	else Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ระบบติดตามยานพาหนะ", "คุณไม่มีรถที่มีระบบติดตามเลย...", "ตกลง", "");
	return 1;
}

Dialog:TrackerVehicle(playerid, response, listitem, inputtext[]){
	if(!response)
		return 1;

	if(response){
		if(listitem >= 0 && listitem <= MAX_OWNABLE_CARS){
			new carid = GetCarIDTracker[playerid][listitem];

			if(CarData[carid][carDestroyed] == 1) return SendClientMessageEx(playerid, COLOR_RED, "- ยานพาหนะ %s ของคุณถูกทำลาย, คุณจะต้องไปกูคืนก่อนเพื่อจะสามารถใช้ได้", ReturnVehicleModelName(CarData[carid][carModel]));

			new
				Float:x,
				Float:y,
				Float:z;

			GetVehiclePos(CarData[carid][carVehicle], x, y, z);
			SetPlayerCheckpoint(playerid, x, y, z, 8.0);
			PlayerEnterCheckPoint[playerid] = 1;
			SendClientMessageEx(playerid, COLOR_YELLOW, "- ยานพาหนะ %s ของคุณอยู่ที่ %s ตามจุดสีแดงไปยังยานพาหนะของคุณ", ReturnVehicleName(CarData[carid][carVehicle]), GetLocation(x, y, z));
		}
	}
	return 1;
}

CMD:vscrap(playerid, params[]){
	if(!LoggedIn[playerid]) return 1;
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		new vehicleid = GetPlayerVehicleID(playerid);
		new carid = Car_GetID(vehicleid);
		if(carid != -1){
			if(Car_IsOwner(playerid, carid)){
				new string[128];
				format(string, sizeof(string), "คุณต้องการที่จะทำลายยานพาหนะ %s ของคุณหรือไม่?\nคุณจะได้คืนครึ่งราคาของยานพาหนะที่คุณซื้อมา", ReturnVehicleName(CarData[carid][carVehicle]));
				Dialog_ShowEasy(playerid, ScrapVeh, DIALOG_STYLE_MSGBOX, "ทำลายยานพาหนะ", string, "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}