public OnGameModeInit(){
	new stringhostname[128];
	format(stringhostname, sizeof(stringhostname), "hostname %s", SERVER_NAME);
	SendRconCommand(stringhostname);
	SetGameModeText(SERVER_VERSION);

	AddServerRule("developer", "JustinzDev");

	mysql_set_charset("tis620");
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	ManualVehicleEngineAndLights();
	AllowInteriorWeapons(false);
	ShowNameTags(false);
	SetNameTagDrawDistance(8.0);
	SetVehiclePassengerDamage(true);
    SetDisableSyncBugs(true);

	SetWorldTime(ghour);

	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 1000);

	TogOOC = 1;
	TogTwitter = 0;
	TogNewbie = 1;
	TogVad = 0;

	SetWeather(1);
	g_serverWeather = 1;

	LoadingServer();
	LoadMapServer();
	LoadServerTextDraw();

	TextDrawSetString(LogoServer[0], "GTA-WORP.COM");
	new stringversion[24];
	format(stringversion, sizeof(stringversion), "%s", SERVER_VERSION);
	TextDrawSetString(LogoServer[2], stringversion);

	LoadActorServer();
	LoadCheckPointServer();
	LoadActorBlackMarket();
	LoadObjectGarden();
//	LoadMapEventConsert();
	LoadShell();
	LoadMapOrangeJob();
	Create_Orange();
	LoadTextDrawCabara();
	LoadTextSleepOnBed();
	RandomPlantPrice();

	SetWeaponDamage(0, DAMAGE_TYPE_STATIC, 1.0);
	SetWeaponDamage(1, DAMAGE_TYPE_STATIC, 6.0);
	SetWeaponDamage(2, DAMAGE_TYPE_STATIC, 6.0);
	SetWeaponDamage(6, DAMAGE_TYPE_STATIC, 6.0);
	SetWeaponDamage(15, DAMAGE_TYPE_STATIC, 2.0);
	SetWeaponDamage(7, DAMAGE_TYPE_STATIC, 3.5);
	SetWeaponDamage(5, DAMAGE_TYPE_STATIC, 4.0);
	SetWeaponDamage(8, DAMAGE_TYPE_STATIC, 8.0);
	SetWeaponDamage(WEAPON_DEAGLE, DAMAGE_TYPE_RANGE, 30.0, 10.0, 20.0, 20.0, 15.0);
	AntiDeAMX();

	LoadTopRank();

	Zone1 = GangZoneCreate(1074, -1519.5, 1182, -1416.5);
	Zone2 = GangZoneCreate(-2276, 518.5, -2233, 555.5);
	LabelZone = GangZoneCreate(2504, 2670.5, 2742, 2855.5);

	//NPC
	LoadNpc();
	return 1;
}

public OnGameModeExit(){
	foreach(new i : Player){
		if(LoggedIn[i]) Character_Save(i);
	}
	return 1;
}

public OnPlayerRequestClass(playerid, classid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(classid < 0) return 0;
	if(IsPlayerConnected(playerid)){
		PlayerCarryAirDrop[playerid] = -1;
		TogglePlayerControllable(playerid, 0);
		TogglePlayerSpectating(playerid, 1);

		if(UserNameValidator(ReturnName(playerid))){
			ErrorMsg(playerid, "ชื่อหน้า Samp หรือใน Data ไม่ควรมีอักษรพิเศษ และ ห้ามมี '_' (Underscore)");
			return SetTimerEx("FixKick", 200, false, "d", playerid);
		}
		else{
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, "http://154.202.2.5/musics/Sweet.mp3"); //เพลงเข้าเซิฟ

			for(new i=0; i<50; i++) SendClientMessage(playerid, -1, " ");
			SendClientMessage(playerid, COLOR_SERVER, "==============================================");
			SendClientMessage(playerid, COLOR_SERVER, "| {FFFFFF}กำลังโหลดเข้าเซิฟเวอร์ กรุณารอสักครู่...");
			SendClientMessage(playerid, COLOR_SERVER, "| {FFFFFF}พัฒนาโดย JustinzDev");
			SendClientMessage(playerid, COLOR_SERVER, "| {FFFFFF}เว็บไซต์: www.gta-worp.com");
			SendClientMessage(playerid, COLOR_SERVER, "==============================================");

			if (PlayerData[playerid][pLogCheckTime]) KillTimer(PlayerData[playerid][pLogCheckTime]);
			PlayerData[playerid][pLogCheckTime] = SetTimerEx("AccountCheck", 500, false, "d", playerid);
		}
	}
	return 1;
}

forward AccountCheck(playerid);
public AccountCheck(playerid){
	Account_Reset(playerid);
	CallLocalFunction("Character_Reset", "i", playerid);
	SetCamera(playerid);
	LoadScreenTextDraw(playerid);
	PlayerConnected(playerid);
	return 1;
}

forward SetCamera(playerid);
public SetCamera(playerid){
	SetPlayerCameraPos(playerid, 1294.101440, -2285.093261, 39.358066);
	SetPlayerCameraLookAt(playerid, 1298.082519, -2285.113769, 38.970550, CAMERA_CUT);
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(fX < -20000.0 || fX > 20000.0 || fY < -20000.0 || fY > 20000.0 || fZ < -1000.0 || fZ > 30000.0) return 0;
	if(!LoggedIn[playerid]) return 1;
	if(PlayerData[playerid][pAdmin] >= 1338) SetPlayerPos(playerid, fX, fY, fZ);

	gGPSRPlayerMarkerPos[playerid][0] = fX;
	gGPSRPlayerMarkerPos[playerid][1] = fY;
	gGPSRPlayerMarkerPos[playerid][2] = fZ;

	gGPSRPlayerMarkerSet[playerid] = true;
	return 1;
}

public OnPlayerConnect(playerid){
	Security_ResetPlayerNet(playerid);
	SecurityAC_Reset(playerid);
	if(IsPlayerNPC(playerid)){
		new string[128];
		format(string, sizeof string, "NPC %s(%d) Connecting.....", ReturnName(playerid), playerid);
		SendAdminsMessage(1, COLOR_RED, string);

		if(!strcmp(ReturnName(playerid), "NPCBUSNO1", true) || !strcmp(ReturnName(playerid), "NPCBUSNO2", true)) return 1;
		else if(Npc_IsValid(playerid) != -1) return 1;
		else if(strfind(ReturnName(playerid), "[Cuffed]", true) != -1) return 1;
		else {
			format(string, sizeof string, "NPC %s(%d) ถูกเตะออกจากเซิฟเวอร์ เนื่องจาก ใช้ Bot Hack", ReturnName(playerid), playerid);
			SendAdminsMessage(1, COLOR_RED, string);
			return Kick(playerid);
		}
	}

	GetPlayerIp(playerid, PlayerData[playerid][pLastIP], 16);

	if(!IsPlayerNPC(playerid)){
		if(UserNameValidator(ReturnName(playerid))){
			ErrorMsg(playerid, "ชื่อหน้า Samp หรือใน Data ไม่ควรมีอักษรพิเศษ และ ห้ามมี '_' (Underscore)");
			return SetTimerEx("FixKick", 200, false, "d", playerid);
		}
	}

	SetPlayerColor(playerid, 0x6FE6FFAA);
	RemoveObjectServerPlayer(playerid);
	RemovePrison(playerid);

	new str[128];
	mysql_format(dbCon, str, sizeof(str), "SELECT * FROM `blacklist` WHERE `Username` = '%e' OR `IP` = '%e'", ReturnName(playerid), PlayerData[playerid][pLastIP]);
	mysql_tquery(dbCon, str, "OnPlayerBlacklist", "d", playerid);

	TextDrawShowForPlayer(playerid, LogoServer[0]);
	TextDrawShowForPlayer(playerid, LogoServer[1]);
	TextDrawShowForPlayer(playerid, LogoServer[2]);
	SetPlayerVirtualWorld(playerid, playerid+1);
	return 1;
}

public OnIncomingConnection(playerid, ip_address[], port){
	new string[128];
	if(AntiBot_CheckConnection(ip_address))
	{
		format(string, sizeof string, "[Security]: Block incoming connection ID:%d IP:%s:%i Reason: flood", playerid, ip_address, port);
		print(string);
		return Kick(playerid);
	}

	if(IsPlayerNPC(playerid)){
		printf("Incoming connection for player ID (%d) [IP/port: %s:%i]", playerid, ip_address, port);
		format(string, sizeof string, "[Connecting]: (%d) กำลัง Connect เข้าสู่เซิฟเวอร์ (IP/Port: %s:%i)", playerid, ip_address, port);
		SendAdminsMessage(1, COLOR_GREY, string);
	}
	return 1;
}

forward OnPlayerFinishedDownloading(playerid, virtualworld);
public OnPlayerFinishedDownloading(playerid, virtualworld){
	new string[128];
    format(string, sizeof string, "[Downloading]: %s ได้ทำการเปลี่ยนโลกเสมือนจริงเป็น %i สำเร็จ", ReturnName(playerid), virtualworld);
	SendAdminsMessage(1, COLOR_GREY, string);
    return 1;
}

public OnPlayerDisconnect(playerid, reason){
	Security_ResetPlayerNet(playerid);
	SecurityAC_Reset(playerid);
	if(IsPlayerNPC(playerid)){
		if(!strcmp(ReturnName(playerid), "NPCBUSNO1", true)){
			TRP_DestroyVehicle(BusRed);
			BusRed = 0;
		}
		if(!strcmp(ReturnName(playerid), "NPCBUSNO2", true)){
			TRP_DestroyVehicle(BusYellow);
			BusYellow = 0;
		}
		return 1;
	}

	new str[128];

	if(PlayerCheckSleepOnBed[playerid]) GiveMoney(playerid, -500, "หักค่ารักษาพยาบาล");
	switch(reason){
        case 0: {
			format(str, 128, "%s ออกจากเซิฟเวอร์ (หลุดออกจากเซิฟเวอร์)", ReturnName(playerid));
			if(PlayerData[playerid][pOnPlayerDuty] == 1) PlayerData[playerid][pOnPlayerDuty] = 1;
			if(PlayerGetPow[playerid] == 1) PlayerData[playerid][pSavePow] = 1;
		}
        case 1: {
			format(str, 128, "%s ออกจากเซิฟเวอร์ (ออกจากเซิฟเวอร์)", ReturnName(playerid));
			PlayerData[playerid][pSavePow] = 0;
			PlayerData[playerid][pOnPlayerDuty] = 0;
		}
        case 2: {
			format(str, 128, "%s ออกจากเซิฟเวอร์ (โดนเตะ/แบน จากเซิฟเวอร์)", ReturnName(playerid));
			PlayerData[playerid][pSavePow] = 0;
			PlayerData[playerid][pOnPlayerDuty] = 0;
		}
    }

	if(PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID) callcmd::hangup(playerid, "\1");
	SendNearbyMessage(playerid, 30.0, COLOR_GRAY, str);

	//PlayerLeaveParty(playerid);

	if(PlayerEnterWarFlag[playerid] && PlayerGetFlag[playerid] && FlagDrill){
		foreach(new i : Player){
			if(!LoggedIn[i]) continue;
			if(!PlayerEnterWarFlag[i]) continue;
			SendClientMessageEx(i, 0xFF8300FF, "[วอชิงธง]: ผู้เล่น %s ได้ทำการออกจากเกมจึงทำให้ธงตกอีกครั้ง...", ReturnRoleplayName(playerid));
		}

		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		if(IsValidPickup(FlagPickup) && FlagPickup != -1) DestroyPickup(FlagPickup);
		FlagPickup = -1;
		FlagPickup = CreatePickup(2614, 2, x, y, z, 1);
		FlagDrill = false;
		PlayerGetFlag[playerid] = false;
		RemoveAttachedObject(playerid, 8);
	}

	if(PlayerEnterRacing[playerid]) SetPlayerPosEx(playerid,1120.4299,-1378.5870,14.2879, 0, 0);

	AccountData[playerid][uInGame] = 0;

	if(PlayerEnterWarCity[playerid] > 0){

		if(gangHoldingWarLSBy == playerid){
            SendClientMessageToAllEx(COLOR_RED, "[WAR-LS]: '%s' จากแก๊ง '%s' ที่กำลังยึดวอเมือง 'LS' อยู่ได้ตายแล้วทำให้การยึดวอเมืองถูกยกเลิก", ReturnRoleplayName(playerid), GetGroupName(PlayerData[playerid][pGroup]));
            gangHoldingWarLSBy = INVALID_PLAYER_ID;
            gangHoldingWarLS_Time = 0;
            gangHoldingWarLS = -1;
        }

        if(gangHoldingWarSFBy == playerid){
            SendClientMessageToAllEx(COLOR_RED, "[WAR-SF]: '%s' จากแก๊ง '%s' ที่กำลังยึดวอเมือง 'SF' อยู่ได้ตายแล้วทำให้การยึดวอเมืองถูกยกเลิก", ReturnRoleplayName(playerid), GetGroupName(PlayerData[playerid][pGroup]));
            gangHoldingWarSFBy = INVALID_PLAYER_ID;
            gangHoldingWarSF_Time = 0;
            gangHoldingWarSF = -1;
        }

        PlayerEnterWarCity[playerid] = 0;
        SetPlayerPos(playerid, PlayerLastPositionWarCity[playerid][0], PlayerLastPositionWarCity[playerid][1], PlayerLastPositionWarCity[playerid][2]);
        SetPlayerFacingAngle(playerid, PlayerLastPositionWarCity[playerid][3]);
        SetPlayerInterior(playerid, PlayerLastIntWarCity[playerid]);
        SetPlayerVirtualWorld(playerid, PlayerLastWorldWarCity[playerid]);
        TogglePlayerControllable(playerid, 1);
    }

	Accounts_Save(playerid);
	ResetGasPump(playerid);
	Character_Save(playerid);
	LoggedIn[playerid] = false;
	if(PlayerUsing_HomeInv[playerid]){
		if(GetHomeOwnerIndex[playerid] != -1){
			if(HomeData[GetHomeOwnerIndex[playerid]][homeStorageUsing]){
				HomeData[GetHomeOwnerIndex[playerid]][homeStorageUsing] = false;
			}
		}
	}
	Account_Reset(playerid);
	CallLocalFunction("Character_Reset", "i", playerid);

	if (lstream[playerid]){
		SvDeleteStream(lstream[playerid]);
		lstream[playerid] = SV_NULL;
	}

	TextDrawHideForPlayer(playerid, LogoServer[0]);
	TextDrawHideForPlayer(playerid, LogoServer[1]);
	TextDrawHideForPlayer(playerid, LogoServer[2]);
	return 1;
}

public OnPlayerSpawn(playerid){
	SecurityAC_Grace(playerid, 5000);
	if(IsPlayerNPC(playerid)){
		if(!strcmp(ReturnName(playerid), "NPCBUSNO1", true)){
			SetPlayerSkin(playerid, 253);
			PutPlayerInVehicle(playerid, BusRed, 0);
			SetPlayerColor(playerid, 0xFFFFFF00);
		}

		if(!strcmp(ReturnName(playerid), "NPCBUSNO2", true)){
			SetPlayerSkin(playerid, 253);
			PutPlayerInVehicle(playerid, BusYellow, 0);
			SetPlayerColor(playerid, 0xFFFFFF00);
		}
		return 1;
	}

	if(SelectCharTextDraw[playerid]){
		SetPlayerCameraPos(playerid, 1958.0909,1342.4780,15.3806);
		SetPlayerCameraLookAt(playerid, 1955.1283,1341.8752,15.3746);
		SetPlayerPos(playerid, 1951.5914,1341.8439,15.3746);
		SetPlayerFacingAngle(playerid, 269.0995);
		SetPlayerSkin(playerid, PlayerData[playerid][pPlayerGetSkinTemp]);
		ClearAnimations(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 1;
	}

	if(LoggedIn[playerid]){

		if(PlayerData[playerid][pWhitelist] == 0){
			Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ไม่มี Whitelist", "คุณไม่มี Whitelist คุณสามารถซื้อไวริสได้ที่ Discord: discord.gg/QfBhz9uXn9", "ตกลง", "");
			return SetTimerEx("FixKick", 1000, false, "d", playerid);
		}

		if(!playerLoadInventory[playerid]){
			new query[128];
			playerLoadInventory[playerid] = true;
			format(query, sizeof(query), "SELECT * FROM `inventory` WHERE `itemOwner` = '%d' AND `itemSlot` > -1", PlayerData[playerid][pID]);
			mysql_tquery(dbCon, query, "OnQuery_Finished", "dd", playerid, THREAD_LOAD_INVENTORY);
		}

		if(PlayerData[playerid][pInjured] == 1 && !PlayerEnterBoxing[playerid]){
			SetCameraBehindPlayer(playerid);
			SetTimerEx("SetPlayerInjured", 300, false, "d", playerid);
		}
		else if(PlayerData[playerid][pInjured] == 0 && PlayerData[playerid][pInHospital] == 1 && PlayerData[playerid][pJail] == 0 && !PlayerEnterBoxing[playerid]){
			if(PlayerData[playerid][pHospitalType] == 1){
				SetPlayerPosEx(playerid, 1172.5717,-1323.9811,15.4036, 0, 0);
				SetPlayerFacingAngle(playerid, 268.7968);
			}
			else if(PlayerData[playerid][pHospitalType] == 2){
				SetPlayerPosEx(playerid, -2651.1536,639.2015,14.4531, 0, 0);
				SetPlayerFacingAngle(playerid, 177.5880);
			}

			TogglePlayerSpectating(playerid, 1);
			HospitalHealth[playerid] = 0;
			SetTimerEx("SetCameraToHospital", 500, false, "d", playerid);
			SetPlayerHealth(playerid, 5);
			SetPlayerColor(playerid, 0xFFFFFF00);
			ResetDamages(playerid);
		}
		else if(HospitalHealth[playerid] >= 80 && PlayerData[playerid][pInjured] == 0 && PlayerData[playerid][pInHospital] == 0 && PlayerData[playerid][pJail] == 0){
			if(PlayerData[playerid][pHospitalType] == 1){
				SetPlayerPosEx(playerid, 1172.5717,-1323.9811,15.4036, 0, 0);
				SetPlayerFacingAngle(playerid, 268.7968);
			}
			else if(PlayerData[playerid][pHospitalType] == 2){
				SetPlayerPosEx(playerid, -2651.1536,639.2015,14.4531, 0, 0);
				SetPlayerFacingAngle(playerid, 177.5880);
			}

			SetPlayerHealth(playerid, 80);
			SetCameraBehindPlayer(playerid);
			HospitalHealth[playerid] = 0;
		}
		else if(PlayerEnterBoxing[playerid]){
			SetPlayerSpawnBoxing(playerid);
		}
		else{
			if(PlayerData[playerid][pFirstTime] == 1){
				CancelSelectTextDraw(playerid);
				SetCameraBehindPlayer(playerid);
				SetPlayerPosEx(playerid, 1494.4642, 1303.8282, 1093.2891, 3, playerid+1);
				SetPlayerFacingAngle(playerid, 357.9944);
				SetMessageWelcome(playerid);
			}
			else{
				SetPlayerPosEx(playerid, PlayerData[playerid][pPosX], PlayerData[playerid][pPosY], PlayerData[playerid][pPosZ], PlayerData[playerid][pInterior], PlayerData[playerid][pWorld]);
				SetPlayerFacingAngle(playerid, PlayerData[playerid][pAngle]);
				SetPlayerHealth(playerid, PlayerData[playerid][pHP]);
				SetPlayerArmour(playerid, PlayerData[playerid][pAM]);
				SetPlayerFightingStyle(playerid, FIGHT_STYLE_NORMAL);
				SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
				SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);

				if(PlayerData[playerid][pJail] == 1 && PlayerData[playerid][pJailTime] > 0) {
					SendPlayerToPrisonNow(playerid);
				}

				TogglePlayerControllable(playerid, 0);
			}
		}

		SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
		SetPlayerColor(playerid, 0xFFFFFF00);
		if(GetGroupType(playerid) == GROUP_MECHANIC) SetGroupColor(playerid);
		//RemoveMarkers(playerid);
		if(ServerData[ServerCanHoldGangZone] == 1 && GetGroupType(playerid) == GROUP_GANG) SetGroupColor(playerid);

		ShowGangZoneForPlayer(playerid);
		if(ServerData[ServerCanHoldGangZone] == 1) SetPlayerFlashZone(playerid);

		if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_MEDIC || GetGroupType(playerid) == GROUP_NATIONAL){
			if(PlayerData[playerid][pOnPlayerDuty] == 1){
				BitFlag_On(g_PlayerFlags[playerid], PLAYER_ONDUTY);
				SetGroupColor(playerid);
				PlayerData[playerid][pOnPlayerDuty] = 1;
			}
		}

		ResetWeapon(playerid);
		if(PlayerData[playerid][pSavePow] == 1) FixLoadPowCrash(playerid);
		for(new i=0; i<9; i++) RemoveAttachedObject(playerid, i);
		SetTimerEx("CheckAccessoryShow", 1000, false, "ii", playerid, playerid);

		if(!IsValidDynamic3DTextLabel(NameTag[playerid])){
			NameTag[playerid] = CreateDynamic3DTextLabel("", 0xFFFFFFFF, 0.0, 0.0, 0.2, 8.0, playerid, INVALID_VEHICLE_ID, 1);
			SetPlayerNameTag(playerid, playerid);
		}
		else SetPlayerNameTag(playerid, playerid);

		if(PlayerEnterWarFlag[playerid]){
			PlayerEnterWarFlag[playerid] = false;
			SetPlayerPos(playerid, GetPositionBeforeFlagWar[playerid][0], GetPositionBeforeFlagWar[playerid][1], GetPositionBeforeFlagWar[playerid][2]);
			SetPlayerFacingAngle(playerid, GetPositionBeforeFlagWar[playerid][3]);
			SetPlayerInterior(playerid, GetIntBeforeFlagWar[playerid]);
			SetPlayerVirtualWorld(playerid, GetWorldBeforeFlagWar[playerid]);
			TogglePlayerControllable(playerid, 1);
		}

		if(PlayerEnterWarCity[playerid] > 0){
			PlayerEnterWarCity[playerid] = 0;
			SetPlayerPos(playerid, PlayerLastPositionWarCity[playerid][0], PlayerLastPositionWarCity[playerid][1], PlayerLastPositionWarCity[playerid][2]);
			SetPlayerFacingAngle(playerid, PlayerLastPositionWarCity[playerid][3]);
			SetPlayerInterior(playerid, PlayerLastIntWarCity[playerid]);
			SetPlayerVirtualWorld(playerid, PlayerLastWorldWarCity[playerid]);
			TogglePlayerControllable(playerid, 1);

			PlayerDelayWarCity[playerid] = 30;
			PlayerIsHoldingWarCity[playerid] = false;
		}

		SetCameraBehindPlayer(playerid);

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 998);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 998);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 998);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 0);
		SetPlayerWeather(playerid, g_serverWeather);

		RemoveBuildingForPlayer(playerid, 955, 0.0, 0.0, 0.0, 20000.0); // CJ_EXT_SPRUNK
		RemoveBuildingForPlayer(playerid, 956, 0.0, 0.0, 0.0, 20000.0); // CJ_EXT_CANDY
		RemoveBuildingForPlayer(playerid, 1209, 0.0, 0.0, 0.0, 20000.0); // vendmach
		RemoveBuildingForPlayer(playerid, 1302, 0.0, 0.0, 0.0, 20000.0); // vendmachfd
		RemoveBuildingForPlayer(playerid, 1775, 0.0, 0.0, 0.0, 20000.0); // CJ_SPRUNK1
		RemoveBuildingForPlayer(playerid, 1776, 0.0, 0.0, 0.0, 20000.0); // CJ_CANDYVENDOR
		RemoveBuildingForPlayer(playerid, 1977, 0.0, 0.0, 0.0, 20000.0); // vendin3

		//ลบกรงเหล็ก label
		RemoveBuildingForPlayer(playerid, 985, 2497.409, 2777.070, 11.531, 0.250);
		RemoveBuildingForPlayer(playerid, 986, 2497.409, 2769.110, 11.531, 0.250);
	}
	return 1;
}

SetPlayerNameTag(playerid, targetid){
	if(!IsPlayerNPC(targetid) && LoggedIn[targetid] && NameTag[targetid]){
		new string[256], vipstr[64];

		if(AdminDuty[targetid]){
			if(PlayerData[targetid][pAdmin] > 0) format(string, sizeof(string), "\n{27E800}ปฏิบัติหน้าที่อยู่ในขณะนี้\n{FFB600}%s", PlayerData[targetid][pAdminName]);
		}
		else if(!AdminDuty[playerid]){
			if(PlayerData[targetid][pVip] == 1) vipstr = "{A22C00}Bronze Member";
			else if(PlayerData[targetid][pVip] == 2) vipstr = "{ECECEC}Silver Member";
			else if(PlayerData[targetid][pVip] == 3) vipstr = "{FFC100}Gold Member";
			if(ServerData[ServerCanHoldGangZone]){
				if(PlayerData[targetid][pGroup] != -1 && GetGroupType(targetid) == GROUP_GANG){
					if(PlayerData[targetid][pVip] != 0){
						if(PlayerData[targetid][pChayaHead]){
							if(IsAFK{targetid}){
								format(string, sizeof(string), "%s\n{FFFFFF}%s\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]\n\n{FFFFFF}(( {%06x}%s {FFFFFF}))", vipstr, PlayerData[targetid][pChayaHeadMessage], targetid, GroupData[PlayerData[targetid][pGroup]][groupColor] >>> 8, Group_GetName(targetid));
							}
							else{
								format(string, sizeof(string), "%s\n{FFFFFF}%s\n{FFB600}ID: {FFFFFF}%d\n\n{FFFFFF}(( {%06x}%s {FFFFFF}))", vipstr, PlayerData[targetid][pChayaHeadMessage], targetid, GroupData[PlayerData[targetid][pGroup]][groupColor] >>> 8, Group_GetName(targetid));
							}
						}
						else{
							if(IsAFK{targetid}){
								format(string, sizeof(string), "\n%s\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]\n\n{FFFFFF}(( {%06x}%s {FFFFFF}))", vipstr, targetid, GroupData[PlayerData[targetid][pGroup]][groupColor] >>> 8, Group_GetName(targetid));
							}
							else{
								format(string, sizeof(string), "\n%s\n{FFB600}ID: {FFFFFF}%d\n\n{FFFFFF}(( {%06x}%s {FFFFFF}))", vipstr, targetid, GroupData[PlayerData[targetid][pGroup]][groupColor] >>> 8, Group_GetName(targetid));
							}
						}
					}
					else{
						if(PlayerData[targetid][pChayaHead]){
							if(IsAFK{targetid}){
								format(string, sizeof(string), "\n%s\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]\n\n{FFFFFF}(( {%06x}%s {FFFFFF}))", PlayerData[targetid][pChayaHeadMessage], targetid, GroupData[PlayerData[targetid][pGroup]][groupColor] >>> 8, Group_GetName(targetid));
							}
							else{
								format(string, sizeof(string), "\n%s\n{FFB600}ID: {FFFFFF}%d\n\n{FFFFFF}(( {%06x}%s {FFFFFF}))", PlayerData[targetid][pChayaHeadMessage], targetid, GroupData[PlayerData[targetid][pGroup]][groupColor] >>> 8, Group_GetName(targetid));
							}
						}
						else{
							if(IsAFK{targetid}){
								format(string, sizeof(string), "\n\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]\n\n{FFFFFF}(( {%06x}%s {FFFFFF}))", targetid, GroupData[PlayerData[targetid][pGroup]][groupColor] >>> 8, Group_GetName(targetid));
							}
							else{
								format(string, sizeof(string), "\n\n{FFB600}ID: {FFFFFF}%d\n\n{FFFFFF}(( {%06x}%s {FFFFFF}))", targetid, GroupData[PlayerData[targetid][pGroup]][groupColor] >>> 8, Group_GetName(targetid));
							}
						}
					}
				}
				else{
					if(PlayerData[targetid][pVip] != 0){
						if(PlayerData[targetid][pChayaHead]){
							if(IsAFK{targetid}){
								format(string, sizeof(string), "%s\n{FFFFFF}%s\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]", vipstr, PlayerData[targetid][pChayaHeadMessage], targetid);
							}
							else{
								format(string, sizeof(string), "%s\n{FFFFFF}%s\n{FFB600}ID: {FFFFFF}%d", vipstr, PlayerData[targetid][pChayaHeadMessage], targetid);
							}
						}
						else{
							if(IsAFK{targetid}){
								format(string, sizeof(string), "\n{FFFFFF}%s\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]", vipstr, targetid);
							}
							else{
								format(string, sizeof(string), "\n{FFFFFF}%s\n{FFB600}ID: {FFFFFF}%d", vipstr, targetid);
							}
						}
					}
					else{
						if(PlayerData[targetid][pChayaHead]){
							if(IsAFK{targetid}){
								format(string, sizeof(string), "\n%s\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]", PlayerData[targetid][pChayaHeadMessage], targetid);
							}
							else{
								format(string, sizeof(string), "\n%s\n{FFB600}ID: {FFFFFF}%d", PlayerData[targetid][pChayaHeadMessage], targetid);
							}
						}
						else{
							if(IsAFK{targetid}){
								format(string, sizeof(string), "\n\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]", targetid);
							}
							else{
								format(string, sizeof(string), "\n\n{FFB600}ID: {FFFFFF}%d", targetid);
							}
						}
					}
				}
			}
			else{
				if(PlayerData[targetid][pVip] != 0){
					if(PlayerData[targetid][pChayaHead]){
						if(IsAFK{targetid}){
							format(string, sizeof(string), "%s\n{FFFFFF}%s\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]", vipstr, PlayerData[targetid][pChayaHeadMessage], targetid);
						}
						else{
							format(string, sizeof(string), "%s\n{FFFFFF}%s\n{FFB600}ID: {FFFFFF}%d", vipstr, PlayerData[targetid][pChayaHeadMessage], targetid);
						}
					}
					else{
						if(IsAFK{targetid}){
							format(string, sizeof(string), "\n{FFFFFF}%s\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]", vipstr, targetid);
						}
						else{
							format(string, sizeof(string), "\n{FFFFFF}%s\n{FFB600}ID: {FFFFFF}%d", vipstr, targetid);
						}
					}
				}
				else{
					if(PlayerData[targetid][pChayaHead]){
						if(IsAFK{targetid}){
							format(string, sizeof(string), "\n%s\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]", PlayerData[targetid][pChayaHeadMessage], targetid);
						}
						else{
							format(string, sizeof(string), "\n%s\n{FFB600}ID: {FFFFFF}%d", PlayerData[targetid][pChayaHeadMessage], targetid);
						}
					}
					else{
						if(IsAFK{targetid}){
							format(string, sizeof(string), "\n\n{FFB600}ID: {FFFFFF}%d {FF0000}[AFK]", targetid);
						}
						else{
							format(string, sizeof(string), "\n\n{FFB600}ID: {FFFFFF}%d", targetid);
						}
					}
				}
			}
		}
		UpdateDynamic3DTextLabelText(NameTag[playerid], 0xFFFFFFFF, string);
	}
	return 1;
}

forward SetPlayerCuffed(playerid);
public SetPlayerCuffed(playerid){
	BitFlag_On(g_PlayerFlags[playerid],PLAYER_CUFFED);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CUFFED);
	PlayerData[playerid][pCuffed] = 1;
	SetPlayerAttachedObject(playerid, 7, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
	return 1;
}

forward SetPlayerInjured(playerid);
public SetPlayerInjured(playerid){
	SetPlayerPosEx(playerid, PlayerData[playerid][pInjuredPos][0], PlayerData[playerid][pInjuredPos][1], PlayerData[playerid][pInjuredPos][2], PlayerData[playerid][pInjuredInt], PlayerData[playerid][pInjuredWorld]);
	SetPlayerFacingAngle(playerid, PlayerData[playerid][pInjuredPos][3]);
	SetPlayerInterior(playerid, PlayerData[playerid][pInjuredInt]);
	SetPlayerVirtualWorld(playerid, PlayerData[playerid][pInjuredWorld]);
	SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

	TimeInjuredStart[playerid] = 1;
	TogglePlayerControllable(playerid, 0);
	SetPlayerHealth(playerid, 100);
	SetPlayerColor(playerid, 0x9C9C9C00);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason){
	if(!LoggedIn[playerid]) return 1;
	if(IsPlayerNPC(playerid)) return 1;

	new bool:validKiller = (killerid != INVALID_PLAYER_ID && IsPlayerConnected(killerid) && LoggedIn[killerid]);
	new killerName[MAX_PLAYER_NAME];
	if(validKiller) GetPlayerName(killerid, killerName, sizeof(killerName));
	else format(killerName, sizeof(killerName), "INVALID");

	if (PlayerInventoryStatus[playerid]) OnPlayerInventory_Close(playerid);
	Log_Write("logs/death.txt", "[%s] [%s] Killed by [%s] by [%d]", ReturnDate(), ReturnName(playerid), killerName, reason);

	if(PlayerEnterWarFlag[playerid]){
		foreach(new i : Player){
			if(!LoggedIn[i]) continue;
			if(!PlayerEnterWarFlag[i]) continue;
			if(PlayerGetFlag[playerid]){
				SendClientMessageEx(i, 0xFF8300FF, "[วอชิงธง]: ผู้เล่น %s ได้ตายและทำให้ธงตกลงพื้น...", ReturnRoleplayName(playerid));
			}
		}

		if(PlayerGetFlag[playerid]){
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
			if(IsValidPickup(FlagPickup) && FlagPickup != -1) DestroyPickup(FlagPickup);
			FlagPickup = -1;
			FlagPickup = CreatePickup(2614, 2, x, y, z, 1);
			FlagDrill = false;
			PlayerGetFlag[playerid] = false;
			RemoveAttachedObject(playerid, 8);
		}

		PlayerData[playerid][pInHospital] = false;
		PlayerData[playerid][pInjured] = false;
		PlayerDelayFlagWar[playerid] = 60;
	}

	if(PlayerHaveStoryID[playerid] != -1 && PlayerData[playerid][pGroup] != -1 && !PlayerData[playerid][pInjured]){
		new story_id = PlayerHaveStoryID[playerid];
		if(Story_Gang[story_id][story_State] == Story_Confirm){
			if(Story_Gang[story_id][story_Mygang] == PlayerData[playerid][pGroup]){
				GroupData[Story_Gang[story_id][story_Enemy]][groupKill]++;
				SendFactionMessage(Story_Gang[story_id][story_Enemy], 0x00AAFFAA, "(( แก๊งของคุณได้รับคะแนนศพสำหรับสตอรี่ +1 [%d/%d] ))", GroupData[Story_Gang[story_id][story_Enemy]][groupKill], Story_Gang[story_id][story_Hidebody]);

				if(GroupData[Story_Gang[story_id][story_Enemy]][groupKill] >= Story_Gang[story_id][story_Hidebody]){
					SendFactionMessage(Story_Gang[story_id][story_Mygang], 0x00AAFFAA, "(( แก๊ง '%s' ได้ทำคะแนนศพจนครบ %d แล้ว การเล่นสตอรี่นี้จึงจบลง ))", Story_Gang[story_id][story_EnemyName], Story_Gang[story_id][story_Hidebody]);
					SendFactionMessage(Story_Gang[story_id][story_Enemy], 0x00AAFFAA, "(( แก๊งคุณได้ทำคะแนนศพจนครบ %d แล้ว การเล่นสตอรี่นี้จึงจบลง ))", Story_Gang[story_id][story_Hidebody]);
					StoryGang_Finish(story_id);
				}
				Group_Save(Story_Gang[story_id][story_Enemy]);
			}
			else if(validKiller && Story_Gang[story_id][story_Mygang] == PlayerData[killerid][pGroup]){
				GroupData[Story_Gang[story_id][story_Mygang]][groupKill]++;
				SendFactionMessage(Story_Gang[story_id][story_Mygang], 0x00AAFFAA, "(( แก๊งของคุณได้รับคะแนนศพสำหรับสตอรี่ +1 [%d/%d] ))", GroupData[Story_Gang[story_id][story_Mygang]][groupKill], Story_Gang[story_id][story_Hidebody]);

				if(GroupData[Story_Gang[story_id][story_Mygang]][groupKill] >= Story_Gang[story_id][story_Hidebody]){
					SendFactionMessage(Story_Gang[story_id][story_Enemy], 0x00AAFFAA, "(( แก๊ง '%s' ได้ทำคะแนนศพจนครบ %d แล้ว การเล่นสตอรี่นี้จึงจบลง ))", Story_Gang[story_id][story_MygangName], Story_Gang[story_id][story_Hidebody]);
					SendFactionMessage(Story_Gang[story_id][story_Mygang], 0x00AAFFAA, "(( แก๊งคุณได้ทำคะแนนศพจนครบ %d แล้ว การเล่นสตอรี่นี้จึงจบลง ))", Story_Gang[story_id][story_Hidebody]);
					StoryGang_Finish(story_id);
				}
				Group_Save(Story_Gang[story_id][story_Mygang]);
			}
		}
	}

	new string[128];
	format(string, sizeof(string), "ผู้เล่น %s ถูกฆ่าโดย %s ด้วย %s", ReturnName(playerid), killerName, ReturnWeaponName(reason));
	SendAdminsMessage(1, COLOR_GRAY, string);
	return 1;
}

public OnVehicleSpawn(vehicleid){
	ResetVehicle(vehicleid);
	return 1;
}

public OnVehicleDeath(vehicleid, killerid){

	if(vehicleid == INVALID_VEHICLE_ID) return 1;
	if (CoreVehicles[vehicleid][vehTemporary]){
	    CoreVehicles[vehicleid][vehTemporary] = false;
		ResetVehicleDamage(vehicleid);
	    TRP_DestroyVehicle(vehicleid);
		return 1;
	}

	new id = -1;
	if((id = Car_GetID(vehicleid)) != -1){
		new ownerid = -1;
		if(CarData[id][carOwner] > 0){
			if(CarData[id][carInsideGarage] == 0 && CarData[id][carDestroyed] == 0){
				if((ownerid = IsCharacterOnline(CarData[id][carOwner])) != -1){
					SendClientMessageEx(ownerid, COLOR_RED, "[แจ้งเตือน]: ยานพาหนะ %s ของคุณถูกทำลาย โดย %s", ReturnVehicleName(CarData[id][carVehicle]), ReturnRoleplayName(killerid));
					Log_Write("logs/destroycar.txt", "[%s] %s of [%s] Destroy By %s", ReturnDate(), ReturnVehicleName(CarData[id][carVehicle]), ReturnRoleplayName(ownerid), ReturnRoleplayName(killerid));
					foreach(new i : Player) if(LoggedIn[i]){
						if(PlayerData[i][pAdmin] > 1) SendClientMessageEx(i, COLOR_RED, "[แจ้งเตือน]: ยานพาหนะ %s ของ %s ถูกทำลายโดย %s", ReturnVehicleName(CarData[id][carVehicle]), ReturnRoleplayName(ownerid), ReturnRoleplayName(killerid));
					}

					CarData[id][carDestroyed] = 1;
					CarData[id][carHealth] = 100;
					SetVehicleHealth(CarData[id][carVehicle], 100);
					TRP_DestroyVehicle(CarData[id][carVehicle], true);
					CarData[id][carVehicle] = INVALID_VEHICLE_ID;
					Car_Save(id);
				}
				else{
					Log_Write("logs/destroycar.txt", "[%s] %s of [OwnerID: %d] Destroy By %s", ReturnDate(), ReturnVehicleName(CarData[id][carVehicle]), CarData[id][carOwner], ReturnRoleplayName(killerid));
					CarData[id][carDestroyed] = 1;
					CarData[id][carHealth] = 100;
					SetVehicleHealth(CarData[id][carVehicle], 100);
					TRP_DestroyVehicle(CarData[id][carVehicle], true);
					CarData[id][carVehicle] = INVALID_VEHICLE_ID;
					Car_Save(id);
				}
			}
		}
		else if(CarData[id][carOwner] == 0){
			CarData[id][carFuel] = 100;
			foreach(new i : Player) if(LoggedIn[i]){
				if(PlayerData[i][pAdmin] > 1) SendClientMessageEx(i, 0xFF5500AA, "| [แจ้งเตือน] ยานพาหนะ %s(%d) ที่ไม่มีเจ้าของ ถูกทำลาย", ReturnVehicleName(CarData[id][carVehicle]), CarData[id][carVehicle]);
			}
			CarData[id][carHealth] = 100;
			SetVehicleHealth(CarData[id][carVehicle], 100);
			TRP_DestroyVehicle(CarData[id][carVehicle], true);
			CarData[id][carVehicle] = INVALID_VEHICLE_ID;
			Car_Save(id);
			Car_Spawn(id);
		}

		ResetVehicle(vehicleid);
		ResetVehicleDamage(vehicleid);
	}
	return 1;
}

public OnPlayerDeathFinished(playerid){
	if(IsPlayerNPC(playerid)) return 1;
	if(!LoggedIn[playerid]) return 1;
	if(IsPlayerConnected(playerid)){

		if(!PlayerEnterBoxing[playerid]){
			for(new i=0; i<3; i++){
				if(PlayerData[playerid][pMyWeapon][i] != 0){
					if(PlayerInventory_AllCount(playerid, "Weapon Card") >= 1){
						PlayerInventory_Remove(playerid, "Weapon Card", 1);
						Log_Write("logs/weaponcarduse.txt", "[%s] %s Use Weapon Card", ReturnDate(), ReturnRoleplayName(playerid));
						SendClientMessage(playerid, COLOR_RED, "[บัตรกันดรอปอาวุธ]: คุณได้ใช้บัตรกันดรอปอาวุธ อาวุธของคุณจะไม่หายไป");
						SendClientMessageEx(playerid, COLOR_YELLOW, "- อาวุธ [%s] ของคุณถูกเก็บเข้ากระเป๋าเรียบร้อยแล้ว", ReturnWeaponName(PlayerData[playerid][pMyWeapon][i]));
						PlayerData[playerid][pDelayWeapon][i] = 0;
						OnPlayerStoreWeapon3(playerid, PlayerData[playerid][pMyWeapon][i]);
					}
					else{
						SendClientMessageEx(playerid, COLOR_RED, "อาวุธ: %s ของคุณได้ตกและหายไป", ReturnWeaponName(PlayerData[playerid][pMyWeapon][i]));
						Log_Write("logs/weapondrop.txt", "[%s] %s Weapon %s (level: %d) has drop", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][i]), PlayerData[playerid][pMyWeaponLevel][i]);
						PlayerData[playerid][pMyWeapon][i] = 0;
						PlayerData[playerid][pMyAmmo][i] = 0;
						PlayerData[playerid][pMyWeaponLevel][i] = 0;
						PlayerData[playerid][pDelayWeapon][i] = 0;
					}
				}
			}
			ResetWeapon(playerid);
		}

		if(PlayerData[playerid][pInjured] == 0 && !PlayerEnterWarFlag[playerid] && !PlayerEnterBoxing[playerid] && PlayerEnterWarCity[playerid] == 0){
			PlayerData[playerid][pInjured] = 1;
			GetPlayerPos(playerid, PlayerData[playerid][pInjuredPos][0], PlayerData[playerid][pInjuredPos][1], PlayerData[playerid][pInjuredPos][2]);
			GetPlayerFacingAngle(playerid, PlayerData[playerid][pInjuredPos][3]);
			PlayerData[playerid][pInjuredWorld] = GetPlayerVirtualWorld(playerid);
			PlayerData[playerid][pInjuredInt] = GetPlayerInterior(playerid);
			PlayerData[playerid][pInjuredTime] = 600;

			SetSpawnInfo(playerid, NO_TEAM, PlayerData[playerid][pSkin], PlayerData[playerid][pInjuredPos][0], PlayerData[playerid][pInjuredPos][1], PlayerData[playerid][pInjuredPos][2], PlayerData[playerid][pInjuredPos][3], 0, 0, 0, 0, 0, 0);


			new Float:ls = GetPlayerDistanceFromPoint(playerid, 1172.5717,-1323.9811,15.4036);
			new Float:sf = GetPlayerDistanceFromPoint(playerid, -2651.1536,639.2015,14.4531);

			if(ls < sf) PlayerData[playerid][pHospitalType] = 1;
			else PlayerData[playerid][pHospitalType] = 2;
		}
		else if(PlayerData[playerid][pInjured] == 1 && !PlayerEnterWarFlag[playerid] && PlayerEnterWarCity[playerid] == 0){
			PlayerData[playerid][pInjured] = 0;
			if(PlayerData[playerid][pJail] != 0) PlayerData[playerid][pInHospital] = 0;
			else if(PlayerData[playerid][pJail] == 0) PlayerData[playerid][pInHospital] = 1;
		}
	}
	return 1;
}

public OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(issuerid < 0 || issuerid >= MAX_PLAYERS || !IsPlayerConnected(issuerid)) return 0;
	if(!LoggedIn[playerid] || !LoggedIn[issuerid]) return 0;
	if(amount < 0.0 || amount > 250.0) return 0;
	if(weapon < 0 || weapon > 55) return 0;
	if(bodypart != 0 && (bodypart < 3 || bodypart > 9)) return 0;

	if(playerid != INVALID_PLAYER_ID && issuerid != INVALID_PLAYER_ID){
		if(LoggedIn[playerid] || LoggedIn[issuerid]){
			new Float:hp, Float:armour;
			GetPlayerHealth(playerid, hp);
			GetPlayerArmour(playerid, armour);

			if(ServerData[ServerSkillGang] == 0){
				if(PlayerData[issuerid][pGroup] != -1){
					if(GroupData[PlayerData[issuerid][pGroup]][groupSkills][0] == 1) amount += 1.0;
					if(GroupData[PlayerData[issuerid][pGroup]][groupSkills][1] == 1) amount += 1.5;

					if(PlayerData[issuerid][pMyWeapon][2] != 0 && weapon != 0){
						if(GroupData[PlayerData[issuerid][pGroup]][groupSkills][2] == 1) amount += 2.0;
					}
				}
			}

			if(PlayerData[issuerid][pMyWeapon][2] != 0 && PlayerData[issuerid][pMyWeaponLevel][2] != 0){
				if(GetPlayerWeapon(issuerid) == PlayerData[issuerid][pMyWeapon][2]){
					new levelweapon = PlayerData[issuerid][pMyWeaponLevel][2];
					if(levelweapon == 1) amount += 2.0;
					else if(levelweapon == 2) amount += 4.0;
					else if(levelweapon == 3) amount += 6.0;
					else if(levelweapon == 4) amount += 8.0;
					else if(levelweapon == 5) amount += 10.0;
					// if(PlayerData[issuerid][pMyWeapon][2] == 1){
					// 	if(levelweapon == 1) amount += 4.0;
					// 	else if(levelweapon == 2) amount += 6.0;
					// 	else if(levelweapon == 3) amount += 8.0;
					// 	else if(levelweapon == 4) amount += 10.0;
					// 	else if(levelweapon == 5) amount += 12.0;
					// }
					// else if(PlayerData[issuerid][pMyWeapon][2] == 8){
					// 	if(levelweapon == 1) amount += 2.0;
					// 	else if(levelweapon == 2) amount += 8.0;
					// 	else if(levelweapon == 3) amount += 12.0;
					// 	else if(levelweapon == 4) amount += 16.0;
					// 	else if(levelweapon == 5) amount += 20.0;
					// }
					// else{
					// 	if(levelweapon == 1) amount += 2.0;
					// 	else if(levelweapon == 2) amount += 3.0;
					// 	else if(levelweapon == 3) amount += 4.0;
					// 	else if(levelweapon == 4) amount += 5.0;
					// 	else if(levelweapon == 5) amount += 6.0;
					// }
				}
			}

			if(weapon == WEAPON_VEHICLE){
				new string[128];
				format(string, sizeof(string), "ผู้เล่น: %s ได้พยายามทำการ DB %s", ReturnRoleplayName(issuerid), ReturnRoleplayName(playerid));
				SendAdminsMessage(1, COLOR_RED, string);
			}

			if(weapon == 24 || weapon == 25 || weapon == 26 || weapon == 27 || weapon == 33 || weapon == 34 || weapon == 38){
				switch(bodypart){
					case 3: amount += 8.0; // Torso.
					case 5: amount += 5.0; // Left Arm.
					case 6: amount += 5.0; // Right Arm.
					case 7: amount += 5.0; // Left Leg.
					case 8: amount += 5.0; // Right Leg.
					case 9: amount += 15.0; //Head

				}
			}

			if(amount > 0){
				if(armour > 0.0) AddPlayerDamage(playerid, weapon, amount, 1, bodypart);
				else AddPlayerDamage(playerid, weapon, amount, 0, bodypart);
			}
		}
	}
	return 1;
}

forward UnfreezeDamage(playerid);
public UnfreezeDamage(playerid){
	CheckPlayerStunFromDamage[playerid] = 0;
	TogglePlayerControllable(playerid, 1);
	return 1;
}

public OnPlayerDamageDone(playerid, Float:amount, issuerid, weapon, bodypart){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(issuerid < 0 || issuerid >= MAX_PLAYERS || !IsPlayerConnected(issuerid)) return 0;
	if(!LoggedIn[playerid] || !LoggedIn[issuerid]) return 0;
	if(amount < 0.0 || amount > 250.0) return 0;
	if(weapon < 0 || weapon > 55) return 0;
	if(bodypart != 0 && (bodypart < 3 || bodypart > 9)) return 0;

	//playerid = คนที่ถูกกระทำ, issuerid == คนกระทำ
	if(weapon == 55) return 0;
	if(weapon == 54) return 0;

	if(playerid != INVALID_PLAYER_ID && issuerid != INVALID_PLAYER_ID){
		if(LoggedIn[playerid] || LoggedIn[issuerid]){
			if (GetGroupType(issuerid) == GROUP_POLICE && BitFlag_Get(g_PlayerFlags[issuerid], PLAYER_BEANBAG) && PlayerData[playerid][pStunned] < 1 && weapon == 25){
				if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ErrorMsg(issuerid, "ผู้เล่นนั้นจะต้องอยู่บนพื้นถึงจะถูกทำให้สลบ");
				if (GetPlayerDistanceFromPlayer(issuerid, playerid) > 10.0) return ErrorMsg(issuerid, "คุณจะต้องอยู่ใกล้ผู้เล่นนั้นเพื่อยิง");

				amount = 0;
				PlayerData[playerid][pStunned] = 10;
				TogglePlayerControllable(playerid, 0);

				ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);

				SendNearbyMessage(issuerid, 30.0, COLOR_RP, "** %s ได้ทำให้ %s สลบด้วย Beanbag Shotgun", ReturnRoleplayName(issuerid), ReturnRoleplayName(playerid));
			}

			// if(PlayerData[issuerid][pPlayerhour] < 5){
			// 	SetPlayerHealth(playerid, PlayerData[playerid][pHP]);
			// 	TogglePlayerControllable(issuerid, 0);
			// 	CheckPlayerStunFromDamage[issuerid] = 1;
			// 	SetTimerEx("UnfreezeDamage", 10000, false, "i", issuerid);
			// 	SendClientMessage(issuerid, COLOR_RED, "- คุณมีต้องมีชั่วโมงออนไลน์มากกว่า 5 ถึงจะทำดาเมจได้...");
			// 	return 1;
			// }

			if(!PlayerEnterWarFlag[issuerid] && !PlayerEnterBoxing[playerid]){
				if(ServerData[ServerCanAttack] == 1){
					new safezoneid = -1;
					if((safezoneid = SafeZone_Nearest(playerid)) != -1) {
						if(SafeZoneData[safezoneid][safezoneType] == 2) return 1;
					}

					if(GetGroupType(issuerid) != GROUP_POLICE && GetGroupType(issuerid) != GROUP_NATIONAL){
						if(GetGroupType(issuerid) == GROUP_GANG && ServerData[ServerCanHoldGangZone] == 1) return 1;

						TogglePlayerControllable(issuerid, 0);
						CheckPlayerStunFromDamage[issuerid] = 1;
						SetTimerEx("UnfreezeDamage", 10000, false, "i", issuerid);
						SendClientMessage(issuerid, COLOR_RED, "- คุณถูกแช่แข็งเนื่องจากระบบกันทำดาเมจทำงานอยู่...");
					}
				}
			}
		}
	}

	if(playerid != INVALID_PLAYER_ID && issuerid != INVALID_PLAYER_ID){
		if(LoggedIn[playerid] || LoggedIn[issuerid]){
			if(weapon == 24 || weapon == 25 || weapon == 26 || weapon == 27 || weapon == 33 || weapon == 34 || weapon == 38){
				switch(bodypart){
					case 3: ApplyAnimation(playerid,"PED","DAM_stomach_frmBK",4.1,0,1,1,0,0,1); // Torso.
					case 5: ApplyAnimation(playerid,"PED","DAM_armL_frmBK",4.1,0,1,1,0,0,1); // Left Arm.
					case 6: ApplyAnimation(playerid,"PED","DAM_armR_frmBK",4.1,0,1,1,0,0,1); // Right Arm.
					case 7: ApplyAnimation(playerid,"PED","DAM_LegL_frmBK",4.1,0,1,1,0,0,1); // Left Leg.
					case 8: ApplyAnimation(playerid,"PED","DAM_LegR_frmBK",4.1,0,1,1,0,0,1); // Right Leg.
					case 9:{ // Head.
						GameTextForPlayer(issuerid,"~r~HEAD SHOT!", 2000,3);
						if(random(5) <= 2){
							ApplyAnimation(playerid,"PED","BIKE_fall_off",4.1,0,1,1,0,0,1);
						}
					}
				}
			}
		}
	}
	return 1;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(strlen(cmd) > 31 || strlen(params) > 512) { SecurityKick(playerid, "bad-command-size"); return 0; }
    if(!LoggedIn[playerid]) return 0;
	printf("[CMD LOG] [%d] %s: /%s %s", playerid, ReturnPlayerName(playerid), cmd, params);
    return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(!LoggedIn[playerid]) return 0;
    if(result == -1) return 0;
    return 1;
}

public OnPlayerText(playerid, text[]){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	new textLen = strlen(text);
	if(textLen < 1 || textLen > 144) { SecurityKick(playerid, "bad-chat-size"); return 0; }

	if(!strcmp(text, "/.killall", true) || !strcmp(text, "/find", true) || !strcmp(text, "/salo", true) || !strcmp(text, "/aimbot", true)){
		Kick(playerid);
		return 0;
	}

	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pFirstTime]) return 0;

	if(IsPlayerConnected(playerid)){
		if(PlayerData[playerid][pInjured] == 1){
			ErrorMsg(playerid, "คุณบาดเจ็บอยู่ไม่สามารถพิมพ์ได้");
			return 0;
		}

		new targetid = PlayerData[playerid][pCallLine], str[128];

		if(IsPlayerOnPhone(playerid)) {
			if (strlen(text) > 64){
				SendNearbyMessage(playerid, 8.0, COLOR_WHITE, "[โทรศัพท์] %s(%d) พูดว่า: %s", ReturnRoleplayName(playerid), playerid, text);
				SendNearbyMessage(playerid, 8.0, COLOR_WHITE, "...%s!", text[64]);
			}
			else {
				SendNearbyMessage(playerid, 8.0, COLOR_WHITE, "[โทรศัพท์] %s(%d) พูดว่า: %s", ReturnRoleplayName(playerid), playerid, text);
			}
			format(str,sizeof(str),"[โทรศัพท์] พูดว่า: %s", text);
			SetPlayerChatBubble(playerid, str, COLOR_WHITE, 8.0, strlen(text) * 500);
		}
		else{
			if (strlen(text) > 64){
				SendNearbyMessage(playerid, 8.0, COLOR_WHITE, "%s(%d) พูดว่า: %s", ReturnRoleplayName(playerid), playerid, text);
				SendNearbyMessage(playerid, 8.0, COLOR_WHITE, "...%s!", text[64]);
			}
			else {
				SendNearbyMessage(playerid, 8.0, COLOR_WHITE, "%s(%d) พูดว่า: %s", ReturnRoleplayName(playerid), playerid, text);
			}

			SetPlayerChatBubble(playerid, text, COLOR_WHITE, 8.0, strlen(text) * 500);

			if (!IsPlayerInAnyVehicle(playerid) && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK) {
				if(PlayerData[playerid][pLoopAnim] == 0){
					if(PlayerSitTable[playerid] == -1 && PlayerTable[playerid] == 0){
						ApplyAnimation(playerid, "GANGS", "prtial_gngtlkA", 4.1, 0, 1, 1, 1, strlen(text) * 100, 1);
					}
				}
			}
		}

		if(PlayerData[playerid][pMechanicCall] == 1){
			SendFactionMessageEx(GROUP_MECHANIC, COLOR_ORANGE, "112 CALL: ลูกค้า %s(%d) (%s)", ReturnRoleplayName(playerid), playerid, GetPlayerLocation(playerid));
			SendFactionMessageEx(GROUP_MECHANIC, COLOR_ORANGE, "รายละเอียด: %s", text);
			SendFactionMessageEx(GROUP_MECHANIC, COLOR_ORANGE, "พิมพ์ '/chm [playerid]' เพื่อระบุตำแหน่งของลูกค้า");

			PlayerData[playerid][pCanMechanicChm] = 1;

			SendClientMessage(playerid, COLOR_YELLOW, "[OPERATOR]:{FFFFFF} ระบบได้ทำการแจ้งช่างยนต์ในพื้นที่เรียบร้อยแล้ว");
			callcmd::hangup(playerid, "\1");
		}

		if(PlayerData[playerid][pEmergency] == 1){
			if (!strcmp(text, "ตำรวจ", true))
			{
				PlayerData[playerid][pEmergency] = 2;
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "[OPERATOR]:{FFFFFF} สายของคุณถูกย้ายมายังกองบัญชาการตำรวจ กรุณาอธิบายเกี่ยวกับเหตุอาชญากรรม");
			}
			else if (!strcmp(text, "หมอ", true))
			{
				PlayerData[playerid][pEmergency] = 3;
				SendClientMessage(playerid, COLOR_HOSPITAL, "[OPERATOR]:{FFFFFF} สายของคุณถูกย้ายมายังกองบัญชาการทางการแพทย์กรุณาอธิบายเหตุฉุกเฉิน");
			}
			else SendClientMessage(playerid, COLOR_LIGHTBLUE, "[OPERATOR]:{FFFFFF} ขออภัยเราไม่เข้าใจ คุณต้องการ \"ตำรวจ\" หรือ \"หมอ\"?");
		}
		else if(PlayerData[playerid][pEmergency] == 2){
			SendGroupMessageEx(GROUP_POLICE, COLOR_RADIO, "911 CALL: %s (Tel: %d) (%s)", ReturnRoleplayName(playerid), PlayerData[playerid][pNumberPhone], GetPlayerLocation(playerid));
			SendGroupMessageEx(GROUP_POLICE, COLOR_RADIO, "รายละเอียด: %s", text);

			SendGroupMessageEx(GROUP_NATIONAL, COLOR_RADIO, "911 CALL: %s (Tel: %d) (%s)", ReturnRoleplayName(playerid), PlayerData[playerid][pNumberPhone], GetPlayerLocation(playerid));
			SendGroupMessageEx(GROUP_NATIONAL, COLOR_RADIO, "รายละเอียด: %s", text);

			SendClientMessage(playerid, COLOR_LIGHTBLUE, "[OPERATOR]:{FFFFFF} ทุกหน่วยงานในพื้นที่ได้รับการแจ้งเตือนแล้ว");
			callcmd::hangup(playerid, "\1");
		}
		else if(PlayerData[playerid][pEmergency] == 3){
			SendFactionMessageEx(GROUP_MEDIC, COLOR_HOSPITAL, "911 CALL: %s (Tel: %d) (%s)", ReturnRoleplayName(playerid), PlayerData[playerid][pNumberPhone], GetPlayerLocation(playerid));
			SendFactionMessageEx(GROUP_MEDIC, COLOR_HOSPITAL, "รายละเอียด: %s", text);

			SendClientMessage(playerid, COLOR_HOSPITAL, "[OPERATOR]:{FFFFFF} ทุกหน่วยงานในพื้นที่ได้รับการแจ้งเตือนแล้ว");
			callcmd::hangup(playerid, "\1");
		}
		if (targetid != INVALID_PLAYER_ID && !PlayerData[playerid][pIncomingCall]){
			SendClientMessageEx(targetid, COLOR_YELLOW, "[โทรศัพท์] %s(%d) พูดว่า: %s", ReturnRoleplayName(playerid), playerid, text);
		}
	}
	return 0;
}

public OnPlayerEnterDynamicCP(playerid, checkpointid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
    return 1;
}

public OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP:checkpointid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
    return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES) return 0;

	if (IsPlayerNPC(playerid)) return 1;

	if(!LoggedIn[playerid]) return 1;

	if(isABikeVehicle(vehicleid)){
		SetEngineStatus(vehicleid, true);
	}

	if(PlayerGetToolRubber[playerid]) return ClearAnimations(playerid);

	if(Player_GetWater[playerid]){
		return ClearAnimations(playerid);
	}

	if(PlayerInvWeightTemp[playerid] > PlayerData[playerid][pInvMaxWeight]){
		return ClearAnimations(playerid);
	}

	if(PlayerGetCowObject[playerid]){
		return ClearAnimations(playerid);
	}

	if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) {
		ErrorMsg(playerid, "คุณถูกใส่กุญแจมือไม่สามารถขึ้นได้");
	    ClearAnimations(playerid);
	    return 1;
	}

	if(CarHas_CowObject[vehicleid]) SendClientMessage(playerid, COLOR_YELLOW, "[!] รถคันนี้มีวัวอยู่");

	if(PlayerData[playerid][pInjured] == 1){
		ErrorMsg(playerid, "คุณอยู่ในสถานะบาดเจ็บ");
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);
		SetPlayerPosEx(playerid, x, y, z + 5, PlayerData[playerid][pInterior], PlayerData[playerid][pWorld]);

		PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);

	    return 1;
	}

	new id = Car_GetID(vehicleid);

	if(!ispassenger && id == -1){
		if(vehicleid == BusYellow){
			ErrorMsg(playerid, "ยานพาหนะคันนี้ไม่สามารถขึ้นได้");
			ClearAnimations(playerid);
			return 1;
		}

		if(vehicleid == BusRed){
			ErrorMsg(playerid, "ยานพาหนะคันนี้ไม่สามารถขึ้นได้");
			ClearAnimations(playerid);
			return 1;
		}
	}

	if(PlayerData[playerid][pPlayerhour] < 5 && !ispassenger && id != -1){
		if(CarData[id][carOwner] != 0){
			ClearAnimations(playerid);
			return SendClientMessage(playerid, COLOR_ORANGERED, "คุณต้องมี ชั่วโมง ออนไลน์ มากกว่า 5 ขึ้นไปคุณถึงจะขับยานพาหนะที่มีเจ้าของได้");
		}
	}
	if (!ispassenger && id != -1 && CarData[id][carGroup] > -1 && PlayerData[playerid][pGroup] != CarData[id][carGroup]) {
	    ClearAnimations(playerid);
	    return SendClientMessageEx(playerid, -1, "รถคันนี้เป็นของกลุ่ม/แก๊ง: {FF0000}%s", GroupData[CarData[id][carGroup]][groupName]);
	}

	if (!ispassenger && id != -1 && CarData[id][carJob] > 0 && PlayerData[playerid][pJob] != CarData[id][carJob]) {
	    ClearAnimations(playerid);
	    return SendClientMessageEx(playerid, -1, "- คุณไม่มีกุญแจสำหรับยานพาหนะคันนี้ [ของอาชีพ: %s]", Job_GetName(CarData[id][carJob]));
	}

	if(StartBuildJob[playerid] == 1 && PlayerData[playerid][pJob] == BUILDJOB){
		ClearAnimations(playerid);
		return 1;
	}

	if(StartPickupDrug[playerid] || StartProcessDrug[playerid]){
		ClearAnimations(playerid);
		return 1;
	}

	if(CarryGas[playerid] != 0){
		CarryGas[playerid] = 0;
		ClearAnimations(playerid);
		RemoveAttachedObject(playerid, 8);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return ErrorMsg(playerid, "คุณไม่สามารถถือแก๊สขึ้นรถได้");
	}

	if(PlayerData[playerid][pJob] == GASJOB){

		if(id == -1) return 1;

		if(CarData[id][carJob] != GASJOB) return 1;

		if(IsLoadGasVehicle(vehicleid)){

			if(CarryGas[playerid] == 1){
				CarryGas[playerid] = 0;
				ClearAnimations(playerid);
				RemoveAttachedObject(playerid, 8);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				return ErrorMsg(playerid, "คุณไม่สามารถถือแก๊สขึ้นรถได้");
			}

			if(CoreVehicles[vehicleid][vehGas] != 0){
				new idjob = GetClosestJobDeliver(playerid, PlayerData[playerid][pJob]);
				if (idjob != -1)
				{
					if(JobData[idjob][jobDeliver][0] == 0.0 && JobData[idjob][jobDeliver][1] == 0.0 && JobData[idjob][jobDeliver][2] == 0.0)
						return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

					EnterCheckPointJob[playerid] = 1;
					SetPlayerCheckpoint(playerid, JobData[idjob][jobDeliver][0], JobData[idjob][jobDeliver][1], JobData[idjob][jobDeliver][2],3.0);
					GPSNavigateToPoint(playerid, JobData[idjob][jobDeliver][0], JobData[idjob][jobDeliver][1], JobData[idjob][jobDeliver][2]);
					SendClientMessageEx(playerid, -1,"คุณได้เปิด GPS ไปยัง จุดส่งแก๊ส");
				}
			}
			else if(CoreVehicles[vehicleid][vehGas] == 0){
				new idjob = GetClosestJobPoint(playerid, PlayerData[playerid][pJob]);
				if (idjob != -1)
				{
					if(JobData[idjob][jobPoint][0] == 0.0 && JobData[idjob][jobPoint][1] == 0.0 && JobData[idjob][jobPoint][2] == 0.0)
						return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

					EnterCheckPointJob[playerid] = 1;
					SetPlayerCheckpoint(playerid, JobData[idjob][jobPoint][0], JobData[idjob][jobPoint][1], JobData[idjob][jobPoint][2],3.0);
					SendClientMessageEx(playerid, COLOR_YELLOW,"- ไปยังจุดสีแดงเพื่อรับ ถังแก๊ส!");
				}
			}
		}
	}
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES) return 0;
	if(!LoggedIn[playerid]) return 1;
	if(PlayerSpeedoShowing[playerid] && TogVehSpeedo[playerid] == 0){
		PlayerSpeedoShowing[playerid] = false;
		HidePlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
		HidePlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);
		DestroyPlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
		DestroyPlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);

		for(new i=0; i<16; i++){
			PlayerTextDrawHide(playerid, VehSpeedo[playerid][i]);
			PlayerTextDrawDestroy(playerid, VehSpeedo[playerid][i]);
		}

		PlayerToggleRightVehSpeedo[playerid] = false;
		PlayerToggleLeftVehSpeedo[playerid] = false;
	}

	if(PlayerData[playerid][pInjured] == 1){
		new seatid = GetAvailableSeat(vehicleid, 0);
		if (seatid == -1) return ErrorMsg(playerid, "ไม่มีที่นั่งเหลือที่จะเข้าไป");
		PutPlayerInVehicleEx(playerid, vehicleid, seatid);
	}

	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(newstate < 0 || newstate > 9 || oldstate < 0 || oldstate > 9) return 0;
	if(IsPlayerNPC(playerid)) return 1;

	if(!LoggedIn[playerid]) return 1;

	if(newstate == PLAYER_STATE_WASTED){
		if(PlayerData[playerid][pJail] == 0){
			if(PlayerData[playerid][pInjured] == 0){
				PlayerData[playerid][pInjured] = 1;
				GetPlayerPos(playerid, PlayerData[playerid][pInjuredPos][0], PlayerData[playerid][pInjuredPos][1], PlayerData[playerid][pInjuredPos][2]);
				GetPlayerFacingAngle(playerid, PlayerData[playerid][pInjuredPos][3]);
				PlayerData[playerid][pInjuredInt] = GetPlayerInterior(playerid);
				PlayerData[playerid][pInjuredWorld] = GetPlayerVirtualWorld(playerid);
				PlayerData[playerid][pInjuredTime] = 300;
				SetSpawnInfo(playerid, NO_TEAM, PlayerData[playerid][pSkin], PlayerData[playerid][pInjuredPos][0], PlayerData[playerid][pInjuredPos][1], PlayerData[playerid][pInjuredPos][2], PlayerData[playerid][pInjuredPos][3], 0, 0, 0, 0, 0, 0);
			}
			else if(PlayerData[playerid][pInjured] == 1){
				PlayerData[playerid][pInjured] = 0;
				PlayerData[playerid][pInHospital] = 1;
			}
		}
	}

	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER){

		if(PlayerData[playerid][pJob] == RUBBERJOB && PlayerGetToolRubber[playerid] == 1){
            RemovePlayerFromVehicle(playerid);
        }

		if (PlayerData[playerid][pBoombox] != INVALID_PLAYER_ID){
	        PlayerData[playerid][pBoombox] = INVALID_PLAYER_ID;
			StopAudioStreamForPlayer(playerid);
	    }

		if(CarryGas[playerid] != 0){
			new
				Float:x,
				Float:y,
				Float:z;

			GetPlayerPos(playerid, x, y, z);
			SetPlayerPos(playerid, x, y, z + 5);

			PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
		}

		if(StartBuildJob[playerid] == 1 && PlayerData[playerid][pJob] == BUILDJOB){
			new
				Float:x,
				Float:y,
				Float:z;

			GetPlayerPos(playerid, x, y, z);
			SetPlayerPos(playerid, x, y, z + 5);

			PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
		}

		if(CheckEnterMine[playerid] == 1){
			new
				Float:x,
				Float:y,
				Float:z;

			GetPlayerPos(playerid, x, y, z);
			SetPlayerPos(playerid, x, y, z + 5);

			PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
		}

		if(CheckEnterCutWood[playerid] == 1){
			new
				Float:x,
				Float:y,
				Float:z;

			GetPlayerPos(playerid, x, y, z);
			SetPlayerPos(playerid, x, y, z + 5);

			PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
		}
	}

	if(newstate == PLAYER_STATE_DRIVER){
		if(PlayerData[playerid][pInjured]){
			new
				Float:x,
				Float:y,
				Float:z;

			GetPlayerPos(playerid, x, y, z);
			SetPlayerPosEx(playerid, x, y, z + 5, PlayerData[playerid][pInterior], PlayerData[playerid][pWorld]);

			PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
			return 1;
		}

		new vehicleid = GetPlayerVehicleID(playerid);

		if(GetVehicleModel(vehicleid) == 408){
            new id = Car_GetID(vehicleid);
            if(PlayerData[playerid][pJob] != GARBAGEJOB){
                RemovePlayerFromVehicle(playerid);
                return SendClientMessageEx(playerid, -1, "- คุณไม่มีกุญแจสำหรับยานพาหนะคันนี้ [ของอาชีพ: %s]", Job_GetName(CarData[id][carJob]));
            }

            if(PlayerData[playerid][pJob] == GARBAGEJOB && PlayerHoldJunk[playerid] == 0){

                if(CoreVehicles[vehicleid][vehJunk] < 10)
                    SetPlayerGarbageCheckPoint(playerid);
                else{
                    new idjob = GetClosestJobDeliver(playerid, PlayerData[playerid][pJob]);
                    if (idjob != -1)
                    {
                        if(JobData[idjob][jobDeliver][0] == 0.0 && JobData[idjob][jobDeliver][1] == 0.0 && JobData[idjob][jobDeliver][2] == 0.0)
                            return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

                        CheckEnterDeliverPoint[playerid] = 1;
                        SetPlayerCheckpoint(playerid, JobData[idjob][jobDeliver][0], JobData[idjob][jobDeliver][1], JobData[idjob][jobDeliver][2],5.0);
                        SendClientMessageEx(playerid, COLOR_YELLOW,"- ถุงขยะของคุณเต็ม [10/10] ไปยังจุดแดงเพื่อส่งมอบขยะ");
                    }
                }
            }
        }

		new EngineStatus = GetEngineStatus(vehicleid);
		if(!isABikeVehicle(vehicleid)){
			if(!EngineStatus){
				if(TogVehSpeedo[playerid] == 0){
					SendClientMessage(playerid, 0xFFB600AA, "[คำแนะนำ]: เครื่องยนต์ยานพาหนะของคุณดับอยู่ กด 'N' เพื่อจัดการยานพาหนะของคุณ");
					SendClientMessage(playerid, 0xFFB600AA, "- หลังจากกด N ให้ไปกดที่ 'ENGINE' เพื่อเริ่ม/หยุดทำงานเครื่องยนต์");
				}
				else{
					SendClientMessage(playerid, 0xFFB600AA, "[คำแนะนำ]: เครื่องยนต์ยานพาหนะของคุณดับอยู่ พิมพ์ '/engine' เพื่อสตาร์ทรถ");
				}
			}
		}

    	new idcar = Car_GetID(vehicleid);

		if(idcar != -1){
			PlayerCarGetID[playerid] = idcar;
			if(CarData[idcar][carDrivingLicense]){
				if(!PlayerData[playerid][pPassDrivingTest]){
					new
						Float:x,
						Float:y,
						Float:z;

					GetPlayerPos(playerid, x, y, z);
					SetPlayerPos(playerid, x, y, z + 5);
					PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, COLOR_RED, "[!]: คุณจะต้องผ่านแบบทดสอบใบขับขี่การตอบคำถามก่อน");
				}else{
					if(PlayerInventory_AllCount(playerid, "Driving Card") > 0){
						new
							Float:x,
							Float:y,
							Float:z;

						GetPlayerPos(playerid, x, y, z);
						SetPlayerPos(playerid, x, y, z + 5);
						PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
						SendClientMessage(playerid, COLOR_RED, "[!]: คุณมีใบขับขี่แล้วไม่จำเป็นต้องทดสอบอีก");
					}
					else SetPlayerStartCheckpointDrving(playerid);
				}
			}

			// if(CarData[idcar][carJob] != 0){
			// 	if(PlayerData[playerid][pLevel] < 2){
			// 		new
			// 			Float:x,
			// 			Float:y,
			// 			Float:z;

			// 		GetPlayerPos(playerid, x, y, z);
			// 		SetPlayerPos(playerid, x, y, z + 5);

			// 		PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);

			// 		SendClientMessage(playerid, COLOR_RED, "!! คุณต้องมีเลเวลมากกว่าหรือเท่ากับ 2 ถึงจะขับยานพาหนะที่เป็นของอาชีพได้ !!");
			// 	}
			// }
		}

		/*if(PlayerData[playerid][pPlayerhour] < 5){
			if(idcar != -1){
				if(CarData[idcar][carOwner] != 0){
					new
						Float:x,
						Float:y,
						Float:z;

					GetPlayerPos(playerid, x, y, z);
					SetPlayerPos(playerid, x, y, z + 5);
					PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, COLOR_RED, "!! คุณจะต้องมีชั่วโมงออนไลน์เกิน 5 ชม. ถึงจะขับรถยานพาหนะที่มีเจ้าของได้ !!");
				}
			}
		}*/

		LoadVehSpeedoTextPlayer(playerid);
		LoadVehCarSpeedoBarPlayer(playerid);
		PlayerSpeedoShowing[playerid] = true;

		if(isABikeVehicle(vehicleid)) SetEngineStatus(vehicleid, true);

		if(TogVehSpeedo[playerid] == 0){

			switch (GetLightStatus(vehicleid))
			{
				case false:
				{
					PlayerTextDrawColor(playerid, VehSpeedo[playerid][10], -1);
				}
				case true:
				{
					PlayerTextDrawColor(playerid, VehSpeedo[playerid][10], 0x0AE600AA);
				}
			}

			switch (EngineStatus)
			{
				case false:
				{
					PlayerTextDrawShow(playerid, VehSpeedo[playerid][15]);
					PlayerTextDrawColor(playerid, VehSpeedo[playerid][9], -1);
				}
				case true:
				{
					PlayerTextDrawShow(playerid, VehSpeedo[playerid][2]);
					PlayerTextDrawShow(playerid, VehSpeedo[playerid][3]);
					PlayerTextDrawShow(playerid, VehSpeedo[playerid][4]);
					PlayerTextDrawShow(playerid, VehSpeedo[playerid][5]);
					PlayerTextDrawShow(playerid, VehSpeedo[playerid][6]);
					ShowPlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
					ShowPlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);
					PlayerTextDrawColor(playerid, VehSpeedo[playerid][9], 0x0AE600AA);
				}
			}

			if (!GetTrunkStatus(vehicleid)){
				PlayerTextDrawColor(playerid, VehSpeedo[playerid][14], -1);
			}
			else{
				PlayerTextDrawColor(playerid, VehSpeedo[playerid][14], 0x0AE600AA);
			}

			if (!GetHoodStatus(vehicleid)){
				PlayerTextDrawColor(playerid, VehSpeedo[playerid][13], -1);
			}
			else{
				PlayerTextDrawColor(playerid, VehSpeedo[playerid][13], 0x0AE600AA);
			}

			PlayerTextDrawShow(playerid, VehSpeedo[playerid][0]);
			PlayerTextDrawShow(playerid, VehSpeedo[playerid][1]);
			PlayerTextDrawShow(playerid, VehSpeedo[playerid][7]);
			PlayerTextDrawShow(playerid, VehSpeedo[playerid][8]);

			//ShowPlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
			//ShowPlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);
		}

		if(idcar != -1){
			if(CarData[idcar][carGroup] != -1 && PlayerData[playerid][pGroup] != CarData[idcar][carGroup]){
				RemovePlayerFromVehicle(playerid);
				return SendClientMessageEx(playerid, -1, "รถคันนี้เป็นของกลุ่ม/แก๊ง: {FF0000}%s", GroupData[CarData[idcar][carGroup]][groupName]);
			}

			if (CarData[idcar][carJob] > 0 && PlayerData[playerid][pJob] != CarData[idcar][carJob]) {
				RemovePlayerFromVehicle(playerid);
				return SendClientMessageEx(playerid, -1, "- คุณไม่มีกุญแจสำหรับยานพาหนะคันนี้ [ของอาชีพ: %s]", Job_GetName(CarData[idcar][carJob]));
			}

			if(PlayerData[playerid][pJob] == FISHJOB){
				if(IsABoatSendModel(CarData[idcar][carModel]) == 1){
					SetPlayerToFishPoint(playerid);
				}
			}

			if(PlayerData[playerid][pJob] == SHARKJOB){
				if(IsABoatSendModel(CarData[idcar][carModel]) == 1){
					SetPlayerToFishSharkPoint(playerid);
				}
			}

			if(CarData[idcar][carJob] == CLOTHJOB){
				if(CarData[idcar][carJob] == PlayerData[playerid][pJob])
					SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำอาชีพ ขนเสื้อผ้า]: กด 'Y' เพื่อเริ่มทำงาน");
			}

			if(PlayerData[playerid][pJob] == CLOTHJOB){
				if(CarData[idcar][carJob] == PlayerData[playerid][pJob]){
					if(CoreVehicles[CarData[idcar][carVehicle]][vehCloth] >= 5){
						ClothJobStartDeliver[playerid] = true;
						ViewClothShop(playerid);
					}
				}
			}

			if(PlayerData[playerid][pJob] == ENGJOB){

				if(ChangeSkinEngJob[playerid] == 1 && CarData[idcar][carJob] != PlayerData[playerid][pJob]){
					RemovePlayerFromVehicle(playerid);
					ErrorMsg(playerid, "คุณจะต้องใช้รถช่างไฟฟ้าเท่านั้น");
				}
				else if(CarData[idcar][carJob] == PlayerData[playerid][pJob] && ChangeSkinEngJob[playerid] == 1){

					if(CheckEnterPointEngJob[playerid] == 1){
						ErrorMsg(playerid, "คุณต้องไปที่จุด Checkpoint ก่อน");
					}
					else{
						StartPointEngJob(playerid);
					}
				}
			}
		}
	}

	if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT){

		if(EnterCheckPointClothJob[playerid]){
            EnterCheckPointClothJob[playerid] = false;
            DisablePlayerCheckpoint(playerid);
        }
        GetStartJobCloth[playerid] = false;

		if(TogVehSpeedo[playerid] == 0){
			PlayerSpeedoShowing[playerid] = false;
			HidePlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
			HidePlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);
			DestroyPlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
			DestroyPlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);

			for(new i=0; i<16; i++){
				PlayerTextDrawHide(playerid, VehSpeedo[playerid][i]);
				PlayerTextDrawDestroy(playerid, VehSpeedo[playerid][i]);
			}

			PlayerToggleRightVehSpeedo[playerid] = false;
			PlayerToggleLeftVehSpeedo[playerid] = false;
		}
		PlayerCarGetID[playerid] = -1;
	}

	if(PlayerData[playerid][pJob] == FARMERJOB){
		if(StartFarmerJob[playerid] == 1){
			if(newstate == PLAYER_STATE_DRIVER){
				new vehicleid = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(vehicleid) == 532){
					SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: ขับรถเข้าไปเหยียบข้าวเพื่อเก็บ");
					HarvestVehID[playerid] = vehicleid;
					//ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 9109759, 50.000000, 0);
					CreatePlayerProgressbar_Job(playerid, 9109759, 50.0);
					HarvestTimer[playerid] = SetTimerEx("HarvestingFarm", 1000, 0, "i", playerid);
				}
			}

			if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT){
				DestroyPlayerProgressbar_Job(playerid);
			}
		}
	}
	return 1;
}

public OnPlayerEnterCheckpoint(playerid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(!LoggedIn[playerid]) return 1;

	if(PlayerData[playerid][pJob] == ENGJOB){
        if(GetSumEngRandom[playerid] != -1){
            if(PlayerToPoint(3.0, playerid, RandomPointEngJob[GetSumEngRandom[playerid]][0], RandomPointEngJob[GetSumEngRandom[playerid]][1], RandomPointEngJob[GetSumEngRandom[playerid]][2])){
                if(CheckEnterPointEngJob[playerid] == 1 && !IsPlayerInAnyVehicle(playerid) && ChangeSkinEngJob[playerid] == 1){
                    RepairPoint[playerid] = 0;
                    DisablePlayerCheckpoint(playerid);
                    StartRepairEngJob(playerid);
                    CheckEnterPointEngJob[playerid] = 0;
                    GetSumEngRandom[playerid] = -1;
                }
            }
        }
    }

	if(StartDeliverBox[playerid] && GotoSendBox[playerid]){
        ClearAnimations(playerid);
        ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
        StartDeliverBox[playerid] = 0;
        GotoSendBox[playerid] = 0;
        SendClientMessageEx(playerid, -1, "คุณได้รับเงินค่าแรง %s", FormatNumber(pricejobprison));
        SetTimerEx("RemoveBoxOnHand", 1000, false, "i", playerid);
        GiveMoney(playerid, pricejobprison, "job prison");
        SendClientMessage(playerid, COLOR_YELLOW, "ไปยังจุดรับพัสดุเพื่อนำมาส่งต่อ");
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        DisablePlayerCheckpoint(playerid);
    }

	if(CheckEnterCutWood[playerid] == 1){
        if(CheckEnterMine[playerid] == 1) return ErrorMsg(playerid, "คุณยังทำงานขุดเหมืองอยู่ ให้ไปยกเลิกก่อน");
        if(ChangeSkinCutWood[playerid] == 1 && GetToolCutWood[playerid] == 1){
            CheckEnterCutWood[playerid] = 0;
            DisablePlayerCheckpoint(playerid);
            StartCutWood(playerid);
        }
	}

	if(PlayerData[playerid][pFirstTime] == 1 && TestingRules[playerid] == 1){
        ShowTestingOne(playerid);
        DisablePlayerCheckpoint(playerid);
    }

    if(PlayerData[playerid][pFirstTime] == 1 && TestingRules[playerid] == 2){
        ShowServerTestingOne(playerid);
        DisablePlayerCheckpoint(playerid);
    }

    if(PlayerData[playerid][pFirstTime] == 1 && TestingRules[playerid] == 3){
        CheckConfirmQuestion(playerid);
        DisablePlayerCheckpoint(playerid);
    }

	if(PlayerData[playerid][pJob] == WEAPONDEALERJOB){
		if(PlayerGetPow[playerid] == 1){
			if(Job_NearestDelivery(playerid) != -1){
				new id = PlayerInventory_AddItem(playerid, "Gun Powder", 2057, 2);
				if (id == -1){
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }

				SendClientMessage(playerid, COLOR_DARKGREEN, "|---------------------------------------------------------|");
				SendClientMessage(playerid, -1, "- คุณได้รับดินปืน + 2");

				new amountexp;
				if(PlayerData[playerid][pVip] == 3){
					amountexp = 2;
					PlayerData[playerid][pWeaponDealerExp] += amountexp;
				} else {
					amountexp = 1;
					PlayerData[playerid][pWeaponDealerExp] += amountexp;
				}

				new nxtlevelweapondealer = PlayerData[playerid][pWeaponDealerSkills] + 1;
				new expamountweapondealer = nxtlevelweapondealer*levelexpweapondealer;

				SendClientMessageEx(playerid, -1, "- คุณได้รับ Exp ของสกิลการคราฟปืน + %d", amountexp);
				if(PlayerData[playerid][pWeaponDealerExp] >= expamountweapondealer){
					PlayerData[playerid][pWeaponDealerSkills]++;
					PlayerData[playerid][pWeaponDealerExp] = 0;
					SendClientMessageEx(playerid, -1, "- คุณได้เลื่อนระดับ Skills เป็น %d เรียบร้อยแล้ว", PlayerData[playerid][pWeaponDealerSkills]);
				}
				SendClientMessage(playerid, COLOR_DARKGREEN, "|---------------------------------------------------------|");
				ResetWeaponDealerJob(playerid);
				DisablePlayerCheckpoint(playerid);
				PlayerData[playerid][pSavePow] = 0;
			}
		}
	}

	if(PlayerData[playerid][pJob] == RUBBERJOB && !IsPlayerInAnyVehicle(playerid)){
        new id = -1;
        if((id = Job_NearestPoint2(playerid)) != -1){
            if(JobData[id][jobType] == RUBBERJOB){
                if(IsPlayerInDynamicCP(playerid, JobData[id][jobCPDynamic])){
                    if(RubberPoint[playerid] < 100) return 0;
                    RubberProcessTime[playerid] = SetTimerEx("StartProcessRubber", 1000, false, "i", playerid);
                    //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0xFFBE3DAA, 100.000000, 0);
                    CreatePlayerProgressbar_Job(playerid, 0xFFBE3DAA);
                }
            }
        }
    }

	if(PlayerData[playerid][pJob] == GARDENER){
        if(CheckPlayerEnterPointGarden[playerid] == 1){
            if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ErrorMsg(playerid, "คุณต้องห้ามอยู่บนยานพาหนะ");
            if(PlayerToPoint(2.0, playerid, RamdomPointGarden[CheckLastRamdomGardener[playerid]][0], RamdomPointGarden[CheckLastRamdomGardener[playerid]][1], RamdomPointGarden[CheckLastRamdomGardener[playerid]][2])){
                if(StartGardenerJob[playerid] == 1){
                    DisablePlayerCheckpoint(playerid);
                    CheckPlayerEnterPointGarden[playerid] = false;
                    TogglePlayerControllable(playerid, 0);
                    ClearAnimations(playerid);
                    ApplyAnimation(playerid, "SHOP", "ROB_Loop_Threat", 4.1, 1, 0, 0, 0, 0, 1);
                    SetPlayerAttachedObject(playerid,8,18705,6,0.251000,0.230999,-1.543000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
                    //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0xFF006CAA, 100.000000, 0);
                    CreatePlayerProgressbar_Job(playerid, 0xFF006CAA);
                    GardenerPoint[playerid] = 0;
                    StartingWater[playerid] = true;
                    GardenerTime[playerid] = SetTimerEx("UpdateGardener", 100, false, "i", playerid);
                }
            }
        }
    }

	if(CheckEnterPointGarbageJob[playerid] == 1 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
        new rand = GetSumRan[playerid];
        if(PlayerToPoint(3.0, playerid, RandomPointGarbageJob[rand][0], RandomPointGarbageJob[rand][1], RandomPointGarbageJob[rand][2])){
            PlayerHoldJunk[playerid] = 1;
            SetPlayerAttachedObject(playerid,7,1264,6,0.320999,-0.067000,0.125000,0.000000,-94.999992,-48.400001,0.689999,0.753000,0.682999);
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้หยิบถุงขยะเรียบร้อยแล้วไปท้ายรถเก็บขยะเพื่อนำใส่รถ");
            SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: กด 'ต่อย' ท้ายรถเพื่อนำถุงขยะใส่รถ");
            DisablePlayerCheckpoint(playerid);
            CheckEnterPointGarbageJob[playerid] = 0;
        }
    }
    if(CheckEnterDeliverPoint[playerid] == 1 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
        new vehicleid = GetPlayerVehicleID(playerid);
        if(CoreVehicles[vehicleid][vehJunk] >= 10){
            if(PlayerData[playerid][pJob] == GARBAGEJOB && GetVehicleModel(vehicleid) == 408){
                GarbagePoint[playerid] = 0;
                //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0x838383AA, 100.000000, 0);
                CreatePlayerProgressbar_Job(playerid, 0x838383AA);
                GarbageTime[playerid] = SetTimerEx("LoadingJunkOut", 1000, 0, "ii", playerid, vehicleid);
                TogglePlayerControllable(playerid, 0);
                CheckEnterDeliverPoint[playerid] = 0;
                DisablePlayerCheckpoint(playerid);
            }
        }
    }

	if(UseCheckpointDeliver[playerid]){
        UseCheckpointDeliver[playerid] = false;
        ClothJobStartDeliver[playerid] = false;
        DisablePlayerCheckpoint(playerid);
        SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: หยิบกล่องเสื้อผ้าออกจากหลังรถจากนั้นกด 'ต่อย' ที่หน้าประตูร้านค้าเพื่อส่งสินค้า");
    }

	if(IsPlayerInDynamicCP(playerid, checkpointcloth)){
		if(CheckEnterPointEngJob[playerid] == 1) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
		ShowBuyClothMenu(playerid);
	}

	if(PlayerEnterCheckPoint[playerid] == 1){
		PlayerEnterCheckPoint[playerid] = 0;
		DisablePlayerCheckpoint(playerid);
		ClearGPS(playerid);
	}

	if(PlayerEnterCheckPointMedic[playerid] == 1){
		PlayerEnterCheckPointMedic[playerid] = 0;
		if(MedicToMe[playerid] != -1){
			MedicToMe[MedicToMe[playerid]] = -1;
			MedicToMe[playerid] = -1;
		}
		DisablePlayerCheckpoint(playerid);
	}

	if(PointToFishShark[playerid]){
		SendClientMessage(playerid, COLOR_YELLOW, "- กด 'ต่อย' เพื่อเริ่มตกปลาฉลามได้ทันที");
		PointToFishShark[playerid] = false;
	}

	if(EnterCheckPointJob[playerid] == 1){
		if(StartBuildJob[playerid] == 1 && PlayerData[playerid][pJob] == BUILDJOB){
			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
				new id = BuilddingGetID[playerid];
				StartBuildJob[playerid] = 0;
				RemovePlayerAttachedObject(playerid, 8);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				SendClientMessageEx(playerid, COLOR_ORANGE, "- คุณได้ส่งปูนเรียบร้อยแล้ว, และได้รับเงิน %s", FormatNumber(JobData[id][jobDeliverPrice]));
				GiveMoney(playerid, JobData[id][jobDeliverPrice], "send poon");

				DisablePlayerCheckpoint(playerid);
			}
		}

		EnterCheckPointJob[playerid] = 0;
		DisablePlayerCheckpoint(playerid);
		ClearGPS(playerid);
	}

	if(PlayerData[playerid][pJob] == FISHJOB){
		new vehicleid = GetPlayerVehicleID(playerid);
		new id = Car_GetID(vehicleid);
		if(id != -1){
			if(IsABoatSendModel(CarData[id][carModel]) == 1){
				if(Job_NearestPoint2Fish(playerid) != -1){
					if(PlayerCanFishing[playerid] == 0){
						SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: คุณสามารถใช้เบ็ดตกปลาของคุณเพื่อเริ่มตกปลาได้โดยการกดปุ่ม 'Y' ที่ท้ายเรือ");
						PlayerCanFishing[playerid] = 1;
						DisablePlayerCheckpoint(playerid);
					}
				}
			}
		}
	}

	new id = -1;
    if((id = AccShop_Nearest(playerid)) != -1){
		if(IsPlayerInDynamicCP(playerid, AccDataShop[id][accShopCheckPoint])){
			PlayerOpenAccessoryMenu[playerid] = true;
        	Dialog_ShowEasy(playerid, AccessoryShop, DIALOG_STYLE_LIST, "ร้านขายเครื่องแต่งกาย", "ส่วน หัว\nส่วน ใบหน้า\nส่วน ลำตัว\nส่วน มือ", "เลือก", "ยกเลิก");
		}
    }
	return 1;
}

CMD:checkskin(playerid, params[]){
	printf("%d", PlayerOpenAccessoryMenu[playerid]);
	return 1;
}

public OnModelSelectionResponse(playerid, extraid, index, modelid, response){
	if(!LoggedIn[playerid]) return 1;

	if(PlayerShowSkinShopMenu[playerid]) PlayerShowSkinShopMenu[playerid] = false;
	if(PlayerOpenAccessoryMenu[playerid]) PlayerOpenAccessoryMenu[playerid] = false;

	if ((response) && (extraid == MODEL_SELECTION_SKIN)){
		new stringmodel[128];

		new doorid;
		if((doorid = Entrance_Inside(playerid)) != -1){
			if(EntranceData[doorid][entranceType] == 3){
				if(EntranceData[doorid][entranceProducts] <= 0){
					return ErrorMsg(playerid, "ร้านนี้มีสินค้าไม่พอ");
				}

				EntranceData[doorid][entranceProducts]-= 5;
			}
		}

		if(PlayerData[playerid][pFirstTime] == 0){
			if(GetMoney(playerid) < 3000) return ErrorMsg(playerid, "คุณมีเงินไม่พอ");

			format(stringmodel, sizeof(stringmodel), "%d", modelid);
			new id = PlayerInventory_AddItem(playerid, stringmodel, 2384, 1);
			if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
			GiveMoney(playerid, -3000, "buy skin");
			SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ซื้อชุดไอดี %d ในราคา $3,000 แล้ว", modelid);
			SendClientMessage(playerid, -1, "- เปิดกระเป๋าและใช้งานได้ทันที");
		}
		printf("%s Select Model %d", ReturnRoleplayName(playerid), modelid);
	}

	if ((response) && (extraid == MODEL_BUY_HAT)){
		if(GetMoney(playerid) < HatDataItem[index][hatitemPrice])
			return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะซื้อชิ้นนี้");

		new id = PlayerInventory_AddItem(playerid, HatDataItem[index][hatitemName], HatDataItem[index][hatitemModel], 1);
		if (id == -1){
			return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
		}
		GiveMoney(playerid, -HatDataItem[index][hatitemPrice], "buy hat");
		SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ประสบความสำเร็จในการซื้อ '%s' ในราคา '%s' เรียบร้อยแล้ว", HatDataItem[index][hatitemName], FormatNumber(HatDataItem[index][hatitemPrice]));
		printf("%s Buy Acc Model %d", ReturnRoleplayName(playerid), modelid);
	}

	if ((response) && (extraid == MODEL_BUY_GLASSES)){
		if(GetMoney(playerid) < GlassesDataItem[index][glassesitemPrice])
			return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะซื้อชิ้นนี้");

		new id = PlayerInventory_AddItem(playerid, GlassesDataItem[index][glassesitemName], GlassesDataItem[index][glassesitemModel], 1);
		if (id == -1){
			return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
		}
		GiveMoney(playerid, -GlassesDataItem[index][glassesitemPrice], "buy glasses");
		SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ประสบความสำเร็จในการซื้อ '%s' ในราคา '%s' เรียบร้อยแล้ว", GlassesDataItem[index][glassesitemName], FormatNumber(GlassesDataItem[index][glassesitemPrice]));
		printf("%s Buy Acc Model %d", ReturnRoleplayName(playerid), modelid);
	}

	if ((response) && (extraid == MODEL_BUY_BODY)){
		if(GetMoney(playerid) < BodyDataItem[index][bodyitemPrice])
			return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะซื้อชิ้นนี้");

		new id = PlayerInventory_AddItem(playerid, BodyDataItem[index][bodyitemName], BodyDataItem[index][bodyitemModel], 1);
		if (id == -1){
			return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
		}
		GiveMoney(playerid, -BodyDataItem[index][bodyitemPrice], "buy body");
		SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ประสบความสำเร็จในการซื้อ '%s' ในราคา '%s' เรียบร้อยแล้ว", BodyDataItem[index][bodyitemName], FormatNumber(BodyDataItem[index][bodyitemPrice]));
		printf("%s Buy Acc Model %d", ReturnRoleplayName(playerid), modelid);
	}

	if ((response) && (extraid == MODEL_BUY_HANDS)){
		if(GetMoney(playerid) < HandsDataItem[index][handsitemPrice])
			return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะซื้อชิ้นนี้");

		new id = PlayerInventory_AddItem(playerid, HandsDataItem[index][handsitemName], HandsDataItem[index][handsitemModel], 1);
		if (id == -1){
			return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
		}
		GiveMoney(playerid, -HandsDataItem[index][handsitemPrice], "buy hands");
		SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ประสบความสำเร็จในการซื้อ '%s' ในราคา '%s' เรียบร้อยแล้ว", HandsDataItem[index][handsitemName], FormatNumber(HandsDataItem[index][handsitemPrice]));
		printf("%s Buy Acc Model %d", ReturnRoleplayName(playerid), modelid);
	}
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	new string[128];
	if(PlayerEnterRacing[playerid] && PlayerRacingStarted[playerid] && PlayerGetDuel[playerid] != INVALID_PLAYER_ID){
		RepairVehicle(PlayerRacingCar[playerid]);
		if(PlayerRacingRacePoint[playerid] == 0){
			PlayerPlaySoundEx(playerid, 1139);
			PlayerRacingRacePoint[playerid] = 1;
			SetPlayerRaceCheckpoint(playerid,0, -1313.9750,-274.9555,1047.7542, -1435.9537,-130.6746,1045.6503, 10.0);
		}
		else if(PlayerRacingRacePoint[playerid] == 1){
			PlayerPlaySoundEx(playerid, 1139);
			PlayerRacingRacePoint[playerid] = 2;
			SetPlayerRaceCheckpoint(playerid,0, -1435.9537,-130.6746,1045.6503, -1521.3333,-245.5031,1050.6412, 10.0);
		}
		else if(PlayerRacingRacePoint[playerid] == 2){
			PlayerPlaySoundEx(playerid, 1139);
			PlayerRacingRacePoint[playerid] = 3;
			SetPlayerRaceCheckpoint(playerid,0, -1521.3333,-245.5031,1050.6412, -1396.5789,-186.5254,1051.4761, 10.0);
		}
		else if(PlayerRacingRacePoint[playerid] == 3){
			PlayerPlaySoundEx(playerid, 1139);
			PlayerRacingRacePoint[playerid] = 4;
			SetPlayerRaceCheckpoint(playerid,0, -1396.5789,-186.5254,1051.4761, -1310.6257,-140.9307,1050.1255, 10.0);
		}

		else if(PlayerRacingRacePoint[playerid] == 4){
			PlayerPlaySoundEx(playerid, 1138);
			PlayerRacingRacePoint[playerid] = 5;
			SetPlayerRaceCheckpoint(playerid,0, -1310.6257,-140.9307,1050.1255, -1313.9750,-274.9555,1047.7542, 10.0);
			format(string, sizeof string, "~Y~1/3");
			GameTextForPlayer(playerid, string, 3000, 5);
		}
		else if(PlayerRacingRacePoint[playerid] == 5){
			PlayerPlaySoundEx(playerid, 1139);
			PlayerRacingRacePoint[playerid] = 6;
			SetPlayerRaceCheckpoint(playerid,0, -1313.9750,-274.9555,1047.7542, -1435.9537,-130.6746,1045.6503, 10.0);
		}
		else if(PlayerRacingRacePoint[playerid] == 6){
			PlayerPlaySoundEx(playerid, 1139);
			PlayerRacingRacePoint[playerid] = 7;
			SetPlayerRaceCheckpoint(playerid,0, -1435.9537,-130.6746,1045.6503, -1521.3333,-245.5031,1050.6412, 10.0);
		}
		else if(PlayerRacingRacePoint[playerid] == 7){
			PlayerPlaySoundEx(playerid, 1139);
			PlayerRacingRacePoint[playerid] = 8;
			SetPlayerRaceCheckpoint(playerid,0, -1521.3333,-245.5031,1050.6412, -1396.5789,-186.5254,1051.4761, 10.0);
		}
		else if(PlayerRacingRacePoint[playerid] == 8){
			PlayerPlaySoundEx(playerid, 1139);
			PlayerRacingRacePoint[playerid] = 9;
			SetPlayerRaceCheckpoint(playerid,0, -1396.5789,-186.5254,1051.4761, -1310.6257,-140.9307,1050.1255, 10.0);
		}

		else if(PlayerRacingRacePoint[playerid] == 9){
			PlayerPlaySoundEx(playerid, 1138);
			PlayerRacingRacePoint[playerid] = 10;
			SetPlayerRaceCheckpoint(playerid,0, -1310.6257,-140.9307,1050.1255, -1313.9750,-274.9555,1047.7542, 10.0);
			format(string, sizeof string, "~Y~2/3");
			GameTextForPlayer(playerid, string, 3000, 5);
		}
		else if(PlayerRacingRacePoint[playerid] == 10){
			PlayerPlaySoundEx(playerid, 1139);
			PlayerRacingRacePoint[playerid] = 11;
			SetPlayerRaceCheckpoint(playerid,0, -1313.9750,-274.9555,1047.7542, -1435.9537,-130.6746,1045.6503, 10.0);
		}
		else if(PlayerRacingRacePoint[playerid] == 11){
			PlayerPlaySoundEx(playerid, 1139);
			PlayerRacingRacePoint[playerid] = 12;
			SetPlayerRaceCheckpoint(playerid,0, -1435.9537,-130.6746,1045.6503, -1521.3333,-245.5031,1050.6412, 10.0);
		}
		else if(PlayerRacingRacePoint[playerid] == 12){
			PlayerPlaySoundEx(playerid, 1139);
			PlayerRacingRacePoint[playerid] = 13;
			SetPlayerRaceCheckpoint(playerid,0, -1521.3333,-245.5031,1050.6412, -1396.5789,-186.5254,1051.4761, 10.0);
		}
		else if(PlayerRacingRacePoint[playerid] == 13){
			PlayerPlaySoundEx(playerid, 1138);
			PlayerRacingRacePoint[playerid] = 14;
			SetPlayerRaceCheckpoint(playerid,1, -1396.5789,-186.5254,1051.4761, -1310.6257,-140.9307,1050.1255, 10.0);
		}
		else if(PlayerRacingRacePoint[playerid] == 14){
			format(string, sizeof string, "คุณได้รับชัยชนะในการแข่งขันครั้งนี้กับ %s(%d)", ReturnRoleplayName(PlayerGetDuel[playerid]), PlayerGetDuel[playerid]);
			Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ชัยชนะ!", string, "ตกลง", "");

			format(string, sizeof string, "คุณได้พ่ายแพ้ในการแข่งขันครั้งนี้กับ %s(%d)", ReturnRoleplayName(playerid), playerid);
			Dialog_ShowEasy(PlayerGetDuel[playerid], ShowOnly, DIALOG_STYLE_MSGBOX, "ชัยชนะ!", string, "ตกลง", "");

			PlayerRacingRacePoint[playerid] = 15;
			DisablePlayerRaceCheckpoint(playerid);
			DisablePlayerRaceCheckpoint(PlayerGetDuel[playerid]);
			format(string, sizeof string, "~Y~3/3 FINISH");
			GameTextForPlayer(playerid, string, 3000, 5);

			PlayerData[playerid][pRacingWin] ++;
			PlayerData[PlayerGetDuel[playerid]][pRacingLose] ++;

			CoreVehicles[PlayerRacingCar[PlayerGetDuel[playerid]]][vehTemporary] = false;
	        TRP_DestroyVehicle(PlayerRacingCar[PlayerGetDuel[playerid]]);
			TRP_DestroyVehicle(PlayerRacingCar[PlayerGetDuel[playerid]]);

			CoreVehicles[PlayerRacingCar[playerid]][vehTemporary] = false;
	        TRP_DestroyVehicle(PlayerRacingCar[playerid]);
			ResetVehicle(PlayerRacingCar[playerid]);

			SetPlayerPosEx(PlayerGetDuel[playerid], PlayerRacingGetPlayerPos[PlayerGetDuel[playerid]][0], PlayerRacingGetPlayerPos[PlayerGetDuel[playerid]][1], PlayerRacingGetPlayerPos[PlayerGetDuel[playerid]][2], PlayerRacingGetInterior[PlayerGetDuel[playerid]], PlayerRacingGetWorld[PlayerGetDuel[playerid]]);
			SetPlayerPosEx(playerid, PlayerRacingGetPlayerPos[playerid][0], PlayerRacingGetPlayerPos[playerid][1], PlayerRacingGetPlayerPos[playerid][2], PlayerRacingGetInterior[playerid], PlayerRacingGetWorld[playerid]);
			SetCameraBehindPlayer(playerid);
			SetCameraBehindPlayer(PlayerGetDuel[playerid]);

			ResetPlayerRacing(PlayerGetDuel[playerid]);
			ResetPlayerRacing(playerid);
		}
	}
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	return 1;
}

public OnObjectMoved(objectid)
{
	if(objectid < 0) return 0;
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(objectid < 0) return 0;
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES) return 0;
	if(componentid < 1000 || componentid > 1193) return 0;
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES) return 0;
	if(paintjobid < 0 || paintjobid > 3) return 0;
	SetVehiclePaintjob(vehicleid, paintjobid);
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(row < 0 || row > 127) return 0;
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid){
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(pickupid < 0) return 0;
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(!LoggedIn[playerid]) return 1;
	if(LoggedIn[playerid]){
		if(newkeys & KEY_CTRL_BACK){
			if(CheckPlayerNotOpenInv(playerid) != -1) return 1;
			if (BitFlag_Get(g_PlayerFlags[playerid],PLAYER_CUFFED) && PlayerData[playerid][pCuffed]) return 1;
			new string[500];
			format(string, sizeof(string), "{23D101}กระเป๋าสัมภาระ\
			\n{23D101}สถานะตัวละคร\
			\n{23D101}สิทธิประโยชน์ของระดับผู้บริจาค\
			\n{23D101}เช็ครถส่วนตัว\
			\n{23D101}เช็คใบสั่ง/บิล\
			\n{23D101}โชว์บัตรต่างๆ\
			\n{23D101}ท่าทางต่างๆ\
			\n{23D101}รูปแบบไมค์โครโฟน\
			\n{23D101}แจ้งตกแมพ\
			\n{23D101}สกิลอาชีพ\
			\n{23D101}ฉายาบนหัว\
			\n{23D101}แลกเปลี่ยนไอเท็ม\
			\n{23D101}ฉายา Login\
			\n{23D101}ออกจากระบบ");
			Dialog_ShowEasy(playerid, DIALOGHELPMENU, DIALOG_STYLE_LIST, "{20AF03}หน้าต่างช่วยเหลือ", string, "เลือก", "ยกเลิก");
		}

		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
			if(newkeys & KEY_JUMP){
				if(!AdminDuty[playerid]){
					PlayerData[playerid][pEnergy] -= 1;
					if(PlayerData[playerid][pEnergy] <= 0) PlayerData[playerid][pEnergy] = 0;
				}
			}

			if(newkeys & KEY_SPRINT){
				if(PlayerData[playerid][pLoopAnim]){
					callcmd::stopanim(playerid, "\1");
				}
			}

			if(newkeys & KEY_JUMP && newkeys & KEY_SPRINT){
				if(PlayerData[playerid][pEnergy] <= 20){
					SendClientMessage(playerid, COLOR_GRAY, "- พลังงานของคุณเหลือน้อย สามารถไปซื้อ 'Energy Drink' ได้ที่ร้านอาหารใช้ '/gps'");
					ApplyAnimation(playerid, "FAT", "IDLE_tired", 4.0, 1, 0, 0, 0, 0, 1);
					SetTimerEx("UnfreezeTired", 5000, false, "d", playerid);
				}
			}
			if(newkeys & KEY_SPRINT){
				if(PlayerData[playerid][pEnergy] <= 20){
					SendClientMessage(playerid, COLOR_GRAY, "- พลังงานของคุณเหลือน้อย สามารถไปซื้อ 'Energy Drink' ได้ที่ร้านอาหารใช้ '/gps'");
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 1, 0, 0, 0, 0, 1);
					SetTimerEx("UnfreezeTired", 5000, false, "d", playerid);
				}
			}
			if(newkeys & KEY_JUMP){
				if(PlayerData[playerid][pEnergy] <= 20){
					SendClientMessage(playerid, COLOR_GRAY, "- พลังงานของคุณเหลือน้อย สามารถไปซื้อ 'Energy Drink' ได้ที่ร้านอาหารใช้ '/gps'");
					ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 1, 0, 0, 0, 0, 1);
					SetTimerEx("UnfreezeTired", 5000, false, "d", playerid);
				}
			}
		}

		if(newkeys & KEY_WALK){
			new id = -1;
			new jobid = -1;

			if(PlayerEnterCamera[playerid] == 1){
				SetPVarInt(playerid, "DisableFPS", 0);
				if(IsValidObject(PlayerData[playerid][pCameraFPS]) && PlayerData[playerid][pCameraFPS]) DestroyObject(PlayerData[playerid][pCameraFPS]);
				SetCameraBehindPlayer(playerid);
				BitFlag_Off(g_PlayerFlags[playerid], PLAYER_FPS);
				PlayerEnterCamera[playerid] = 0;
				PlayerCameraType[playerid] = 0;
				ClearAnimations(playerid);
				HideMobilePhone(playerid);
				TogglePlayerControllable(playerid, 1);
			}

            if((jobid = Job_NearestPoint(playerid)) != -1){
                if(PlayerData[playerid][pJob] == ORANGEJOB && JobData[jobid][jobType] == ORANGEJOB){
                    if(PlayerIsCarryCrate[playerid] && Player_Orange_InCrate[playerid]){
                        if(!Player_Orange_StartChecking[playerid])
                            Start_Check_Orange(playerid);
                    }
                }
            }

			if (( id = Garage_GetNearest(playerid)) != -1){
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณต้องลงจากยานพาหนะก่อน");
				ShowCarPlayerGetGarage(playerid, id);
			}

			if (( id = Garage_StoreNearest(playerid)) != -1){
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณต้องลงจากยานพาหนะก่อน");
				ShowCarPlayerStoreGarage(playerid);
			}
		}

		if(newkeys & KEY_FIRE){

			new Float:x, Float:y, Float:z;
    		GetPlayerPos(playerid, x, y, z);
			static bool:act;

			if(InfoSkate[playerid][sActive] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
				if(!SkatePlayerUsing[playerid]){
					SkatePlayerUsing[playerid] = true;
					ApplyAnimation(playerid, "SKATE","skate_run",4.1,1,1,1,1,1,1);
					PlayerTimerSkate[playerid] = SetTimerEx("ChangeRunAnimSkate", 5000, false, "i", playerid);
					if(!act){
						act = true;
						RemovePlayerAttachedObject(playerid,INDEX_SKATE);
						SetPlayerAttachedObject(playerid,INDEX_SKATE,19878,9,0.115999,0.000000,-0.025000,110.200027,-89.800025,0.000000,1.000000,1.000000,1.000000);
					}
				}
				else if(SkatePlayerUsing[playerid]){
					SkatePlayerUsing[playerid] = false;
					ClearAnimations(playerid);
					KillTimer(PlayerTimerSkate[playerid]);
					SetTimerEx("FixAnimationPickupSkate", 100, false, "i", playerid);
					SkateChangeAction[playerid] = false;
					if(act){
						act = false;
						RemovePlayerAttachedObject(playerid,INDEX_SKATE);
						SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					}
				}

			}

			if(PlayerEnterCamera[playerid] == 1){
				if(PlayerCameraType[playerid] == 0){
					PlayerCameraType[playerid] = 1;
					if(IsValidObject(PlayerData[playerid][pCameraFPS]) && PlayerData[playerid][pCameraFPS]) DestroyObject(PlayerData[playerid][pCameraFPS]);
					GetPlayerPos(playerid, x, y, z);
					SetPlayerFacingAngle(playerid, 216.0);
					SetPlayerCameraPos(playerid, x+0.5, y-0.5, z+1.0);
					SetPlayerCameraLookAt(playerid, x, y, z+0.85);
					TogglePlayerControllable(playerid, 0);
					ClearAnimations(playerid);
					ApplyAnimationEx(playerid, "ON_LOOKERS", "Pointup_loop", 4.0, 1, 0, 0, 0, 0);
				}
				else if(PlayerCameraType[playerid] == 1){
					PlayerCameraType[playerid] = 0;
					SetPVarInt(playerid, "DisableFPS", 1);
					if(IsValidObject(PlayerData[playerid][pCameraFPS]) && PlayerData[playerid][pCameraFPS]) DestroyObject(PlayerData[playerid][pCameraFPS]);
					PlayerData[playerid][pCameraFPS] = CreateObject(19300, 0.0, 0.0, 5.0, 0.0, 0.0, 0.0);
					SetCameraBehindPlayer(playerid);
					SyncCamera(playerid);
					TogglePlayerControllable(playerid, 0);
					BitFlag_On(g_PlayerFlags[playerid], PLAYER_FPS);
					ClearAnimations(playerid);
				}
			}

			if(x > -1851 && x < -1395 && y > -2308.5 && y < -1897.5){
				for(new i=0; i<MAX_DEERS; i++){
					if(DeerData[i][deerEx] && !DeerData[i][deerScared] && !DeerData[i][deerIsPickup] && !DeerData[i][deerIsDead]){
						if(IsPlayerInRangeOfPoint(playerid, 3.0, DeerData[i][deerPos][0], DeerData[i][deerPos][1], DeerData[i][deerPos][2])){
							if(PlayerInventory_AllCount(playerid, "Knife") < 1) return ErrorMsg(playerid, "คุณไม่มีมีด");
							if(PlayerUseKnife[playerid] == 0) return ErrorMsg(playerid, "คุณยังไม่ได้กดใช้งานมีด");
							if(IsPlayerInAnyVehicle(playerid)) return ErrorMsg(playerid, "คุณต้องลงจากยานพาหนะก่อน");

							new random_amount = jdzrandom(1,2);
							if(random_amount == 1){
								ClearAnimations(playerid);
								ApplyAnimation(playerid, "KNIFE", "knife_3", 4.1, 0, 1, 1, 0, 0, 1);
								MoveDynamicObject(DeerData[i][deerObject], DeerData[i][deerPos][0], DeerData[i][deerPos][1], DeerData[i][deerPos][2]-0.5, 8.0, 90.0, 0, DeerData[i][deerPos][3]);
								DeerData[i][deerIsDead] = true;
							}
							else if(random_amount == 2){
								ClearAnimations(playerid);
								ApplyAnimation(playerid, "KNIFE", "knife_3", 4.1, 0, 1, 1, 0, 0, 1);
								DeerData[i][deerScared] = true;
								DeerData[i][deerIsPickup] = true;
								DeerData[i][deerIsDead] = true;
								DeerData[i][deerDeathTime] = 120;
								MoveDynamicObject(DeerData[i][deerObject], DeerData[i][deerPos][0]+3.0, DeerData[i][deerPos][1]+3.0, DeerData[i][deerPos][2]-10.0, 8.0, 0.00000, 0.00000, DeerData[i][deerPos][3]);
								SetTimerEx("SetDeerIsHide", 1000, false, "i", i);
								SendClientMessage(playerid, 0xFF0000AA, "[!]: {FF7000}น่าเสียดาย, กวางน้อยผู้น่าสงสารได้ตื่นตระหนกและหลบหนีไป");
								DeerData[i][deerTimer] = SetTimerEx("ReviveDeer", 1000, false, "i", i);
							}
						}
					}
				}
			}

			if(PlayerGetToolRubber[playerid] == 1 && PlayerData[playerid][pJob] == RUBBERJOB && !IsPlayerInAnyVehicle(playerid)){
                new id = -1;
                if((id = Rubber_Nearest(playerid)) != -1){
                    if(RubberPoint[playerid] < 100){

                        if(RubberStarting[playerid] == 1) return 0;

                        if(RubberData[id][rubberHealth] < 5) return ErrorMsg(playerid, "ต้นยางนี้มีน้ำยางไม่พอกรีด");

                        ClearAnimations(playerid);
                        ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.1, 0, 0, 0, 0, 0, 1);
                        RubberStarting[playerid] = 1;
                        RubberTime[playerid] = SetTimerEx("StartingRubber", 1000, false, "ii", playerid, id);
                    }
                    else if(RubberPoint[playerid] >= 100) return ErrorMsg(playerid, "น้ำยางของคุณเต็มแล้ว");
                }
            }

			if(PlayerData[playerid][pJob] == ORANGEJOB){
                if(PlayerIsCarryCrate[playerid] && Player_GetID_Orange[playerid] == -1 && !Player_Orange_InCrate[playerid]){
                    new id = -1;
                    if((id = Orange_Nearest(playerid)) != -1){
                        if(!OrangeData[id][orangePlayerUse]){

                            if(OrangeData[id][orangeHealth] < 5) return ErrorMsg(playerid, "ส้มต้นนมีผลผลิตไม่พอเก็บ");

                            Player_GetID_Orange[playerid] = id;
                            Start_Pickup_Orange(playerid);
                        }
                    }
                }
            }

			if(PlayerData[playerid][pJob] == OILJOB && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
				new id = -1;
				if((id = Oil_Near(playerid)) != -1){
					if(OilData[id][oilAmount] < 10) return ErrorMsg(playerid, "บ่อน้ำมันนี้มีไม่พอที่จะขุด");
					if(OilData[id][oilUse] == 1) return ErrorMsg(playerid, "จุดนี้มีคนกำลังขุดอยู่");
					if(StartDrill[playerid] == 0){
						if(PlayerInventory_AllCount(playerid, "Drill Tool") >= 1){
							StartDrill[playerid] = 1;
							DrillPoint[playerid] = 0;
							OilGetID[playerid] = id;
							LoadPlayerJobTypeTwo(playerid);
							ProgressBarJobTypeTwo[playerid][0] = CreatePlayerProgressBar(playerid, 185.000000, 372.000000, 261.500000, 9.000000, 0xFF5500AA, 100.000000, 0);
							PlayerTextDrawShow(playerid, TextDrawJobTypeTwo[playerid][0]);
							ShowPlayerProgressBar(playerid, ProgressBarJobTypeTwo[playerid][0]);
							SetPlayerAttachedObject(playerid,7,18717,6,0.727000,0.238000,-2.481999,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
							SetPlayerAttachedObject(playerid,8,2711,6,0.285999,0.081999,-0.342999,13.399989,-33.200012,0.899989,1.846999,1.739000,5.334001);
							DrillTime[playerid] = SetTimerEx("DrillingOil", 500, 0, "i", playerid);
							TogglePlayerControllable(playerid, 0);
							OilData[id][oilUse] = 1;
						}
					}
				}
			}

			if(PlayerData[playerid][pJob] == GARBAGEJOB){
				if(PlayerHoldJunk[playerid] != 0){

					new carid = -1;
					if((carid = Car_NearestIsJob(playerid)) != -1){

						if(CarData[carid][carJob] != GARBAGEJOB) return ErrorMsg(playerid, "รถคันนี้ไม่ใช่รถอาชีพเก็บขยะ");

						if (IsPlayerNearBoot(playerid, CarData[carid][carVehicle])){

							if(CoreVehicles[CarData[carid][carVehicle]][vehJunk] >= 10)
								return ErrorMsg(playerid, "สามารถบรรจุถุงขยะได้แค่ 10 ชิ้นเท่านั้น");

							CoreVehicles[CarData[carid][carVehicle]][vehJunk]++;
							SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้โยนถุงขยะเข้าไปในรถแล้ว [%d/10]", CoreVehicles[CarData[carid][carVehicle]][vehJunk]);
							PlayerHoldJunk[playerid] = 0;
							ClearAnimations(playerid);
							ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 3.0, 0, 0, 0, 0, 0);
							RemoveAttachedObject(playerid, 7);
						}
					}
				}
			}

			if(PlayerData[playerid][pJob] == CLOTHJOB){
				new carid = -1;
				if((carid = Car_NearestIsJob(playerid)) != -1){
					if(CarData[carid][carJob] == PlayerData[playerid][pJob]){
						if (IsPlayerNearBoot(playerid, CarData[carid][carVehicle]))
						{
							if (GetBoxCloth[playerid]){
								if (CoreVehicles[CarData[carid][carVehicle]][vehCloth] >= 5)
									return SendClientMessage(playerid, COLOR_WHITE, "ยานพาหนะคันนี้บรรจุกล่องเสื้อผ้าได้แค่ 5 กล่อง");

								CoreVehicles[CarData[carid][carVehicle]][vehCloth]++;

								ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0);

								SendClientMessageEx(playerid, COLOR_ORANGE, "- คุณได้นำกล่องเสื้อผ้าใส่รถแล้ว [%d/5]", CoreVehicles[CarData[carid][carVehicle]][vehCloth]);

								GetBoxCloth[playerid] = false;
								SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
								RemoveAttachedObject(playerid, 7);
								return 1;
							}
							else if(!GetBoxCloth[playerid]){
								if(CoreVehicles[CarData[carid][carVehicle]][vehCloth] <= 0)
									return ErrorMsg(playerid, "ในรถคันนี้ไม่มีกล่องเสื้อผ้าแล้ว");

								GetBoxCloth[playerid] = true;
								CoreVehicles[CarData[carid][carVehicle]][vehCloth]--;
								SendClientMessageEx(playerid, COLOR_ORANGE, "- คุณได้นำกล่องเสื้อผ้าออกจากรถแล้ว [%d/5]", CoreVehicles[CarData[carid][carVehicle]][vehCloth]);
								ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
								SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
								SetPlayerAttachedObject(playerid,7,2654,6,-0.015999,0.096999,-0.232000,-109.999992,-29.799995,-10.899980,0.786999,0.616999,0.883000);
							}
						}
					}

				}
			}

			if(PlayerData[playerid][pJob] == CLOTHJOB){
				new doorid = -1;
				if((doorid = Entrance_Nearest(playerid)) != -1){
					if(EntranceData[doorid][entranceType] == 3){

						if(EntranceData[doorid][entranceProducts] >= MAX_PRODUCTS)
							return ErrorMsg(playerid, "ร้านเสื้อผ้านี้มีสินค้าเต็มคลังแล้ว");

						if(GetBoxCloth[playerid]){
							ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0);
							EntranceData[doorid][entranceProducts]++;
							Entrance_Save(doorid);
							SendClientMessageEx(playerid, COLOR_ORANGE, "- คุณได้นำกล่องเสื้อผ้าส่งถึงร้านเรียบร้อยแล้ว [%d/%d]", EntranceData[doorid][entranceProducts], MAX_PRODUCTS);
							GetBoxCloth[playerid] = false;
							SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
							RemoveAttachedObject(playerid, 7);

							new getprice = 0;
							for(new i=0; i<MAX_DYNAMIC_JOBS; i++) if(JobData[i][jobExists]){
								if(JobData[i][jobType] != CLOTHJOB) continue;
								else{
									getprice = JobData[i][jobDeliverPrice];
								}
							}

							GiveMoney(playerid, getprice, "clothing send");
							SendClientMessageEx(playerid, COLOR_ORANGE, "- คุณได้รับเงินจำนวน %s จากการส่งสินค้า", FormatNumber(getprice));

						}
					}
				}
			}

			if(CheckPlayerChangeSkin[playerid] == 1 && PlayerData[playerid][pJob] == COWJOB){
				for(new i=0; i<MAX_COWS; i++) if(CowData[i][cowStill]){
					if(IsPlayerInRangeOfObject(playerid, CowData[i][cowObject], 2.0)){
						if(PlayerInventory_AllCount(playerid, "Knife") > 0 && PlayerUseKnife[playerid] == 1){
							StopDynamicObject(CowData[i][cowObject]);
							CowData[i][cowDeath] = 1;
							GetDynamicObjectPos(CowData[i][cowObject], CowData[i][cowFixPos][0], CowData[i][cowFixPos][1], CowData[i][cowFixPos][2]);
							MoveDynamicObject(CowData[i][cowObject], CowData[i][cowFixPos][0], CowData[i][cowFixPos][1], CowData[i][cowFixPos][2], 2.0, 0.00000, -91.0000, CowData[i][cowPos][3]);
						}
					}
				}
			}

			if(PlayerData[playerid][pJob] == GASJOB){
				new carid = -1;
				if((carid = Car_NearestIsJob(playerid)) != -1){

					if(CarData[carid][carJob] != GASJOB) return 0;

					if (IsPlayerNearBoot(playerid, CarData[carid][carVehicle]))
					{
						if(!GetTrunkStatus(CarData[carid][carVehicle]))
							return ErrorMsg(playerid, "คุณต้องขึ้นรถไปเปิดกระโปรงหลังรถก่อน");

						if (CarryGas[playerid] == 1){
							if (CoreVehicles[CarData[carid][carVehicle]][vehGas] >= 1)
								return SendClientMessage(playerid, COLOR_WHITE, "ยานพาหนะคันนี้สามารถบรรจุได้เพียง 1 ชิ้นเท่านั้น");
						}

						if(IsGasOnVeh[CarData[carid][carVehicle]] == 0){
							if(CarryGas[playerid] == 1)
							{
								CoreVehicles[CarData[carid][carVehicle]][vehGas]++;

								ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0);

								CarryGas[playerid] = 0;
								SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
								RemoveAttachedObject(playerid, 8);

								IsGasOnVeh[CarData[carid][carVehicle]] = 1;
								SetTimerEx("LoadGasOnVeh", 500, false, "d", CarData[carid][carVehicle]);
								SendClientMessage(playerid, COLOR_YELLOW, "[แนะนำ]: กด 'ต่อย' อีกครั้งเพื่อหยิบแก๊สจากรถ");
								return 1;
							}
						}
						else if(IsGasOnVeh[CarData[carid][carVehicle]] == 1){
							if(CarryGas[playerid] == 0)
							{
								CoreVehicles[CarData[carid][carVehicle]][vehGas]--;

								SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
								ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
								SetPlayerAttachedObject(playerid, 8, 1348,1,0.248999,0.503000,0.006000,-93.700035,80.499900,-83.400001,0.474000,0.603999,0.433999);

								CarryGas[playerid] = 1;

								IsGasOnVeh[CarData[carid][carVehicle]] = 0;
								EnterCheckPointJob[playerid] = 0;
								DisablePlayerCheckpoint(playerid);
								ClearGPS(playerid);

								if(IsValidDynamicObject(GasOnVeh[CarData[carid][carVehicle]]) && GasOnVeh[CarData[carid][carVehicle]] != -1) DestroyDynamicObject(GasOnVeh[CarData[carid][carVehicle]]);
								GasOnVeh[CarData[carid][carVehicle]] = -1;
								return 1;
							}
						}
					}
				}
			}
			if(PlayerData[playerid][pJob] == SHELLJOB){
				new shellid = -1;
				if((shellid = Shell_Nearest(playerid)) != -1){
					if(PlayerPickingUpShell[playerid] == 0){
						if(PlayerInventory_AllCount(playerid, "Knife") < 1) return ErrorMsg(playerid, "ต้องการ 'Knife' ในการเก็บหอย");
						if(PlayerUseKnife[playerid] == 0) return ErrorMsg(playerid, "คุณจำเป็นต้องกดใช้ 'Knife' ก่อน");
						PlayerPickUpShell(playerid, shellid);
					}
				}
			}
		}

		if(newkeys & KEY_NO){

			if (GetBoxCloth[playerid]){
				GetBoxCloth[playerid] = false;
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				RemoveAttachedObject(playerid, 7);
				SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้ทิ้งกล่องเสื้อผ้าแล้ว");
			}

			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
				if(PlayerData[playerid][pMyWeapon][0] != 0){
					OnPlayerReloadAmmo1(playerid, PlayerData[playerid][pMyWeapon][0]);
				}

				if(PlayerData[playerid][pMyWeapon][1] != 0){
					OnPlayerReloadAmmo2(playerid, PlayerData[playerid][pMyWeapon][1]);
				}
			}

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
				if(TogVehSpeedo[playerid] == 0){
					SelectTextDraw(playerid, 0x46F301AA);
				}
			}

			new id = -1;

			if ((id = Entrance_Nearest(playerid)) != -1){
				if(EntranceData[id][entranceType] == 4){
					if(StartTradeMoney[playerid] == 1){
						TogglePlayerControllable(playerid, 1);
						ClearAnimations(playerid);
						DestroyPlayerProgressbar_Job(playerid);
						SendClientMessage(playerid, COLOR_RED, "คุณได้ยกเลิกการกระทำแล้ว");
						ResetDrugPlayer(playerid);
					}
				}
			}

			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
				if((id = Car_Nearest(playerid)) != -1){
					if(Car_IsOwner(playerid, id)){
						callcmd::lock(playerid, "\1");
					}
					else{
						if(PlayerData[playerid][pTemporaryKey] == id){
							callcmd::lock(playerid, "\1");
						}
					}
				}
			}

			if(PlayerData[playerid][pInjured] == 1){
				if(PlayerData[playerid][pInjuredTime] == 0){
					SetPlayerHealth(playerid, 0);
					TogglePlayerControllable(playerid, 1);
					SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ยอมตาย", ReturnRoleplayName(playerid));
					ResetDamages(playerid);
				}
				else
					return ErrorMsg(playerid, "คุณต้องรอเวลานับจนเหลือ 0 ถึงจะยอมตายได้");
			}

			if(PlayerData[playerid][pJob] == GASJOB){
				if(CarryGas[playerid] == 1){
					ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					RemoveAttachedObject(playerid, 8);
					CarryGas[playerid] = 0;
					SendClientMessage(playerid, COLOR_RED, "- คุณได้ทิ้งถังแก๊สของคุณแล้ว!");
				}
			}
		}

		if(IsKeyJustDown(KEY_WALK, newkeys, oldkeys)) {
			if(PlayerData[playerid][pSpec] != INVALID_PLAYER_ID && PlayerData[playerid][pAdmin] >= 1 || GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) {
				PlayerData[playerid][pSpec] = INVALID_PLAYER_ID;
				SetPlayerColor(playerid, 0xFFFFFF00);
				TogglePlayerSpectating(playerid, false);
				return 1;
			}
		}

		if(newkeys & KEY_YES){
			new
				id = -1,
				idgroup = -1,
				string[128];

			new Float:xx, Float:yy, Float:zz;
    		GetPlayerPos(playerid, xx, yy, zz);

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
				if(IsPlayerInRangeOfPoint(playerid, 5.0, 1017.6605,-917.6010,42.1797)){
					ShowMenuInstallNeon(playerid);
				}
			}

			if(xx > -1851 && xx < -1395 && yy > -2308.5 && yy < -1897.5){
				new header[100];
				if(( id = Camping_Nearest(playerid)) != -1){
					if(IsPlayerInAnyVehicle(playerid)) return ErrorMsg(playerid, "คุณต้องลงจากยานพาหนะก่อน");
					format(header, sizeof(header), "คุณกำลังใช้งานแคมป์ของ: %s", CampData[id][campOwnerName]);
					if(CampData[id][campOwnerID] != playerid){
						format(string, sizeof(string), "> แล่เนื้อกวาง");
						Dialog_ShowEasy(playerid, CampingUseing, DIALOG_STYLE_LIST, header, string, "เลือก", "ปิด");
					}
					else{
						format(string, sizeof(string), "> แล่เนื้อกวาง\n> เก็บแคมป์");
						Dialog_ShowEasy(playerid, CampingUseingOwner, DIALOG_STYLE_LIST, header, string, "เลือก", "ปิด");
					}
				}
    		}

			if((id = Mine_Near(playerid)) != -1){
                if(IsPlayerInAnyVehicle(playerid)) return ErrorMsg(playerid, "คุณจะต้องลงจากยานพาหนะก่อน");
                if(PlayerInventory_AllCount(playerid, "Drill Tool") < 1) return ErrorMsg(playerid, "คุณไม่มีเครื่องขุดเจาะ");
                if(!PlayerStartMine[playerid]){
                    Start_PickingupMine(playerid, id);
                }
            }

            if (IsPlayerInRangeOfPoint(playerid, 2.5, -2258.5933,549.5543,35.0156)){
                ShowDialogSellMine(playerid);
            }

			if(IsPlayerInRangeOfPoint(playerid, 4.0, -2242.7539,522.1887,35.1719)){
				if(IsPlayerInAnyVehicle(playerid)) return ErrorMsg(playerid, "คุณต้องลงจากยานพาหนะก่อน");
				ShowDeerSeller(playerid);
			}

			if(!PlayerPickingupDeer[playerid]){
                for(new i=0; i<MAX_DEERS; i++) if(DeerData[i][deerEx]){
                    if(IsPlayerInRangeOfPoint(playerid, 3.0, DeerData[i][deerPos][0], DeerData[i][deerPos][1], DeerData[i][deerPos][2])){
                        if(IsPlayerInAnyVehicle(playerid)) return ErrorMsg(playerid, "คุณต้องลงจากยานพาหนะก่อน");
                        if(DeerData[i][deerIsDead] && !DeerData[i][deerIsPickup]){
                            ClearAnimations(playerid);
                            ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
                            SetTimerEx("SetDeerOnHand", 500, false, "i", playerid);
                            DeerData[i][deerIsPickup] = true;
                            DeerData[i][deerDeathTime] = 120;
                            Deer_Refresh(i);
                            PlayerPickingupDeer[playerid] = true;
                            DeerData[i][deerTimer] = SetTimerEx("ReviveDeer", 1000, false, "i", i);
                        }
                    }
                }
            }

			if(!IsPlayerInAnyVehicle(playerid)){

				if ((id = Drug_DeliverNearest(playerid)) != -1){
					if(DrugData[id][drugType] == 1){
						format(string, sizeof(string), "แพ็คกัญชาในตัว : %d\nกรอกจำนวนที่จะต้องการขาย", PlayerInventory_AllCount(playerid, "Pack Weed"));
						Dialog_ShowEasy(playerid, SellDrug, DIALOG_STYLE_INPUT, "ขายยา", string, "ขาย", "ยกเลิก");
					}
					if(DrugData[id][drugType] == 2){
						format(string, sizeof(string), "แพ็คโคเคนในตัว : %d\nกรอกจำนวนที่จะต้องการขาย", PlayerInventory_AllCount(playerid, "Pack Cocain"));
						Dialog_ShowEasy(playerid, SellDrug, DIALOG_STYLE_INPUT, "ขายยา", string, "ขาย", "ยกเลิก");
					}
					if(DrugData[id][drugType] == 4){
						format(string, sizeof(string), "แพ็คปูนในตัว : %d\nกรอกจำนวนที่จะต้องการขาย", PlayerInventory_AllCount(playerid, "Pack Cement"));
						Dialog_ShowEasy(playerid, SellDrug, DIALOG_STYLE_INPUT, "ขายยา", string, "ขาย", "ยกเลิก");
					}
					if(DrugData[id][drugType] == 5){
						format(string, sizeof(string), "สายไฟในตัว : %d\nกรอกจำนวนที่จะต้องการขาย", PlayerInventory_AllCount(playerid, "Wire"));
						Dialog_ShowEasy(playerid, SellDrug, DIALOG_STYLE_INPUT, "ขายสายไฟ", string, "ขาย", "ยกเลิก");
					}
				}

				if ((id = Drug_Nearest(playerid)) != -1){

					if(StartPickupDrug[playerid] == 1) return 1;

					new countpolice = 0;
					foreach(new x : Player) {
						if(!LoggedIn[x]) continue;
						if(GetGroupType(x) != GROUP_POLICE) continue;
						if(GetGroupType(x) == GROUP_POLICE && BitFlag_Get(g_PlayerFlags[x], PLAYER_ONDUTY)){
							countpolice++;
						}

						if(countpolice >= 7) break;
					}

					if(DrugData[id][drugType] == 1){
						if(countpolice >= 7){
							if(DrugData[id][drugAmount] < 7)
								return ErrorMsg(playerid, "มีกัญชาไม่พอให้คุณเก็บ");

							if(StartPickupDrug[playerid] == 0 && PlayerGetDrug[playerid] == 0 && StartProcessDrug[playerid] == 0){
								if(!IsPlayerInAnyVehicle(playerid)){

									if(PlayerData[playerid][pLevel] < 2)
										return ErrorMsg(playerid, "คุณต้องมีเลเวล 2 ขึ้นไป");

									StartPickingUpDrug(playerid, id);
								}
							}
						}
						else ErrorMsg(playerid, "ตำรวจต้องออนไลน์อย่างน้อย 7 คน");
					}

					if(DrugData[id][drugType] == 2){
						if(countpolice >= 7){
							if(DrugData[id][drugAmount] < 7)
								return ErrorMsg(playerid, "มีโคเคนไม่พอให้คุณเก็บ");

							if(StartPickupDrug[playerid] == 0 && PlayerGetDrug[playerid] == 0 && StartProcessDrug[playerid] == 0){
								if(!IsPlayerInAnyVehicle(playerid)){
									if(PlayerData[playerid][pLevel] < 3)
										return ErrorMsg(playerid, "คุณต้องมีเลเวล 3 ขึ้นไป");

									StartPickingUpDrug(playerid, id);
								}
							}
						}
						else ErrorMsg(playerid, "ตำรวจต้องออนไลน์อย่างน้อย 7 คน");
					}

					if(DrugData[id][drugType] == 3){
						if(!OpenMenuCraftDrug[playerid]){
							LoadCraftDrugTextDraw(playerid);
							TogglePlayerControllable(playerid, 0);
							ShowMenuCraftDrug(playerid);
						}
						else{
							DrugCraft_Hide(playerid);
							TogglePlayerControllable(playerid, 1);
						}
					}

					if(DrugData[id][drugType] == 4){
						if(countpolice >= 7){
							if(DrugData[id][drugAmount] < 7)
								return ErrorMsg(playerid, "มีปูนไม่พอให้จก");

							if(StartPickupDrug[playerid] == 0 && PlayerGetDrug[playerid] == 0 && StartProcessDrug[playerid] == 0){
								if(!IsPlayerInAnyVehicle(playerid)){

									if(PlayerData[playerid][pLevel] < 4)
										return ErrorMsg(playerid, "คุณต้องมีเลเวล 4 ขึ้นไป");

									StartPickingUpDrug(playerid, id);
								}
							}
						}
						else ErrorMsg(playerid, "ตำรวจต้องออนไลน์อย่างน้อย 7 คน");
					}

					if(DrugData[id][drugType] == 5){
						if(DrugData[id][drugAmount] < 2)
							return ErrorMsg(playerid, "สายไฟไม่เพียงพอ");

						if(StartPickupDrug[playerid] == 0 && PlayerGetDrug[playerid] == 0 && StartProcessDrug[playerid] == 0){
							if(!IsPlayerInAnyVehicle(playerid)){
								if(PlayerData[playerid][pLevel] < 7) return ErrorMsg(playerid, "คุณต้องมีเลเวล 7 ขึ้นไป");
								StartPickupWire(playerid, id);
							}
						}
					}
				}

				if ((id = Drug_ProcessNearest(playerid)) != -1){

					if(StartProcessDrug[playerid] == 1) return 1;

					new countpolice = 0;
					foreach(new x : Player){
						if(!LoggedIn[x]) continue;
						if(GetGroupType(x) != GROUP_POLICE) continue;
						else if(GetGroupType(x) == GROUP_POLICE && BitFlag_Get(g_PlayerFlags[x], PLAYER_ONDUTY)){
							countpolice++;
						}

						if(countpolice >= 7) break;
					}

					if(DrugData[id][drugType] == 1){
						if(countpolice < 10) return ErrorMsg(playerid, "ต้องการตำรวจอย่างน้อย 10 คน");
						if(PlayerGetDrug[playerid] == 1 && StartProcessDrug[playerid] == 0 && StartPickupDrug[playerid] == 0){
							if(!IsPlayerInAnyVehicle(playerid)){

								if(PlayerGetDrug[playerid] != 1) return ErrorMsg(playerid, "ชนิดของยาไม่ถูกต้อง");

								if(PlayerData[playerid][pLevel] < 2)
									return ErrorMsg(playerid, "คุณต้องมีเลเวล 2 ขึ้นไป");

								StartProcessingDrug(playerid, id);
							}
						}
					}
					else if(DrugData[id][drugType] == 2){
						if(countpolice < 10) return ErrorMsg(playerid, "ต้องการตำรวจอย่างน้อย 10 คน");
						if(PlayerGetDrug[playerid] == 2 && StartProcessDrug[playerid] == 0 && StartPickupDrug[playerid] == 0){
							if(!IsPlayerInAnyVehicle(playerid)){

								if(PlayerGetDrug[playerid] != 2) return ErrorMsg(playerid, "ชนิดของยาไม่ถูกต้อง");

								if(PlayerData[playerid][pLevel] < 3)
									return ErrorMsg(playerid, "คุณต้องมีเลเวล 3 ขึ้นไป");

								StartProcessingDrug(playerid, id);
							}
						}
					}
					else if(DrugData[id][drugType] == 4){
						if(countpolice < 10) return ErrorMsg(playerid, "ต้องการตำรวจอย่างน้อย 10 คน");
						if(PlayerGetDrug[playerid] == 4 && StartProcessDrug[playerid] == 0 && StartPickupDrug[playerid] == 0){
							if(!IsPlayerInAnyVehicle(playerid)){

								if(PlayerGetDrug[playerid] != 4) return ErrorMsg(playerid, "ชนิดของยาไม่ถูกต้อง");

								if(PlayerData[playerid][pLevel] < 4)
									return ErrorMsg(playerid, "คุณต้องมีเลเวล 4 ขึ้นไป");

								StartProcessingDrug(playerid, id);
							}
						}
					}
				}
			}

			new Float:NPCPos[3];
			if(IsPlayerNearPlayer(playerid, NPCPUBLICGIRL, 2.5)){
				FCNPC_GetPosition(NPCPUBLICGIRL, NPCPos[0],NPCPos[1],NPCPos[2]);
				if(IsPlayerInRangeOfPoint(playerid, 3, NPCPos[0],NPCPos[1],NPCPos[2])){
					ApplyAnimation(NPCPUBLICGIRL, "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 0, 1);
					SetPlayerChatBubble(NPCPUBLICGIRL,"\"ยินดีต้อนรับค่ะ ต้องการทราบข้อมูลอะไรสามารถสอบถามได้เลยค่ะ\"",0xFFFFFFAA,50,5000);
					format(string, sizeof(string), "> ตลาดกลาง คืออะไร?\n> แลก ชั่วโมงออนไลน์ เป็น EXP");
					Dialog_ShowEasy(playerid, DialogNPCHELP, DIALOG_STYLE_LIST, "น้องซูซาน", string, "เลือก", "ยกเลิก");
				}
			}

			if(PlayerData[playerid][pJob] == SHARKJOB){
				if((id = Job_NearestPointFishShark(playerid)) != -1){ //
					if(IsPlayerInAnyVehicle(playerid)) return ErrorMsg(playerid, "คุณจะต้องออกจากสถานะขับยานพาหนะก่อน");
					if(JobData[id][jobType] == SHARKJOB){
						if(!StartFishingShark[playerid] && !SharkOnRod[playerid]){
							if(PlayerInventory_AllCount(playerid, "Fishing Rod") < 1) return ErrorMsg(playerid, "คุณไม่มีเบ็ดตกปลา");
							StartFishingSharkJob(playerid);
						}
						else if(StartFishingShark[playerid] && SharkOnRod[playerid]){
							GetRodOnHand(playerid);
						}
					}
				}
			}

			if(PlayerData[playerid][pJob] == SEEKERJOB){
				if((id = Seeker_Near(playerid)) != -1){
					if(TreasureData[id][treasureStill] == 0) return 1;
					ClearAnimations(playerid);
					ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
					TreasureData[id][treasureStill] = 0;
					Treasure_Refresh(id);
					new itemid = PlayerInventory_AddItem(playerid, "Dirty Treasure", 1276, 1);
					if (itemid == -1){
						return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
					}

					SendClientMessage(playerid, COLOR_YELLOW, "|================================================|");
					SendClientMessage(playerid, -1, "- คุณได้รับสมบัติเจือปนรังสี (Dirty Treasure) + 1 ชิ้น");
					SendClientMessage(playerid, COLOR_YELLOW, "|================================================|");
				}
			}

			if(PlayerData[playerid][pJob] == PIZZAJOB){
				if(( id = Job_NearestPoint(playerid)) != -1){
					if(!PlayerOpenPizzaMenu[playerid]){
						if(JobData[id][jobType] == PIZZAJOB){
							OpenPizzaMenu(playerid);
						}
					}
				}
			}

			if(PlayerData[playerid][pJob] == JELLYJOB){
				if ((id = JellyFish_Nearest(playerid)) != -1){
					if(JellyFishStartPickup[playerid] == 0){
						if(WearLifeVest[playerid] == 0)
							return ErrorMsg(playerid, "คุณต้องใส่เสื้อชูชีพในการที่จะเก็บแมงกระพรุน");

						if(JellyFishData[id][jellyfishStill] == 0)
							return ErrorMsg(playerid, "แมงกระพรุนยังไม่พร้อมเก็บ");

						if(JellyFishData[id][jellyfishPicking] == 1)
							return ErrorMsg(playerid, "ไม่สามารถเก็บได้");

						TogglePlayerControllable(playerid, 0);
						StartPickupJellyFish(playerid, id);
						JellyFishData[id][jellyfishPicking] = 1;
					}
				}
			}

			if((id = Job_NearestPoint(playerid)) != -1){
				if(!GetBoxCloth[playerid]){
					if(PlayerData[playerid][pJob] == CLOTHJOB && JobData[id][jobType] == CLOTHJOB){
						PlayerGetBoxCloth(playerid);
					}
				}
			}

			if(PlayerData[playerid][pJob] == CLOTHJOB){
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
					new vehicleid = GetPlayerVehicleID(playerid);
					new carid = Car_GetID(vehicleid);
					if(carid != -1){
						if(CarData[carid][carJob] == PlayerData[playerid][pJob]){
							if(!GetStartJobCloth[playerid] && !ClothJobStartDeliver[playerid]){
								new idjob = GetClosestJobPoint(playerid, PlayerData[playerid][pJob]);
								if (idjob != -1)
								{
									if(JobData[idjob][jobPoint][0] == 0.0 && JobData[idjob][jobPoint][1] == 0.0 && JobData[idjob][jobPoint][2] == 0.0)
										return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

									EnterCheckPointClothJob[playerid] = true;
									SetPlayerCheckpoint(playerid, JobData[idjob][jobPoint][0], JobData[idjob][jobPoint][1], JobData[idjob][jobPoint][2],3.0);
									SendClientMessageEx(playerid, COLOR_YELLOW,"- ไปยังจุดสีแดงเพื่อรับ กล่องเสื้อผ้า!");
								}
								GetStartJobCloth[playerid] = true;
							}
						}
					}
				}
			}

			if(Cartune_Nearest(playerid) != -1){
                if(GetGroupType(playerid) != GROUP_MECHANIC) return ErrorMsg(playerid, "สำหรับ ช่างยนต์ เท่านั้น");

                if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณต้องเป็นคนขับรถ");

                new vehicleid = GetPlayerVehicleID(playerid);
                if(vehicleid == INVALID_VEHICLE_ID) return 1;

                if(IsABoatSendModel(GetVehicleModel(vehicleid)) == 1) return ErrorMsg(playerid, "คุณไม่สามารถแต่งเรือได้");

                Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
            }

            if((id = Home_Nearest(playerid)) != -1){

                new count = 0;
                for(new i=0; i<MAX_HOME; i++) if(HomeData[i][homeEx]){
                    if(Home_IsOwner(playerid, i)){
                        count++;
                    }
                }

                if(HomeData[id][homeOwner] == 0){

                    if(count >= MAX_HOME_PLAYERS)
                        return SendClientMessageEx(playerid, COLOR_RED, "คุณสามารถซื้อบ้านได้แค่ %d หลังเท่านั้น", MAX_HOME_PLAYERS);

                    new statshome[32];
                    if(HomeData[id][homeBuild] == 0)
                        statshome = "ยังสร้างไม่เสร็จ";
                    else
                        statshome = "สร้างเสร็จแล้ว";

                    format(string, sizeof(string), "ชื่อบ้าน: %s\
                    \nราคา: %s\
                    \nสถานะของบ้านหลังนี้: %s\
                    \nคุณต้องการจะซื้อบ้านหลังนี้หรือไม่?", HomeData[id][homeName], FormatNumber(HomeData[id][homePrice]), statshome);
                    Dialog_ShowEasy(playerid, BUYHOUSE, DIALOG_STYLE_MSGBOX, "ซื้อบ้าน", string, "ซื้อ", "ยกเลิก");
                }
                else if(HomeData[id][homeOwner] != 0){
                    if(Home_IsOwner(playerid, id) || Home_IsRentOwner(playerid, id)){
                        if(HomeData[id][homeBuild] == 0){
                            format(string, sizeof(string), "> ไม้ในคลัง\t[%d]\n> เหล็กในคลัง\t[%d]\n> เริ่มการก่อสร้าง <", PlayerData[playerid][pBuildItemHome][0], PlayerData[playerid][pBuildItemHome][1]);
                            Dialog_ShowEasy(playerid, BuildHome, DIALOG_STYLE_LIST, "ก่อสร้างบ้าน", string, "เลือก", "ยกเลิก");
                        }
                        else if(HomeData[id][homeBuild] == 1){
                            format(string, sizeof(string), "เข้าบ้าน\nปลดล็อค/ล็อค บ้าน\nดูผู้เช่าที่ออนไลน์\nดูผู้เช่าทั้งหมด");
                            Dialog_ShowEasy(playerid, OwnerHome, DIALOG_STYLE_LIST, "บ้านของคุณ", string, "เลือก", "ยกเลิก");
                        }
                    }
                    else{

                        if(HomeData[id][homeBuild] == 0)
                            return ErrorMsg(playerid, "บ้านหลังนี้ยังสร้างไม่เสร็จ");

                        new caption[128];
                        format(caption, sizeof(caption), "บ้านของ: %s", HomeData[id][homeOwnerName]);
                        Dialog_ShowEasy(playerid, NoOwnerHome, DIALOG_STYLE_LIST, caption, "เข้าบ้าน", "เลือก", "ยกเลิก");
                    }
                }
            }
            if((id = Home_NearestInside(playerid)) != -1){
                if(Home_IsOwner(playerid, id) || Home_IsRentOwner(playerid, id)){
                    format(string, sizeof(string), "ออกบ้าน\nปลดล็อค/ล็อค บ้าน");
                    Dialog_ShowEasy(playerid, ExitOwnerHome, DIALOG_STYLE_LIST, "บ้านของคุณ", string, "เลือก", "ยกเลิก");
                }
                else{
                    new caption[128];
                    format(caption, sizeof(caption), "บ้านของ: %s", HomeData[id][homeOwnerName]);
                    Dialog_ShowEasy(playerid, ExitNoOwnerHome, DIALOG_STYLE_LIST, caption, "ออกบ้าน", "เลือก", "ยกเลิก");
                }
            }

            if((id = Home_Inside(playerid)) != -1 && Home_NearestInside(playerid) == -1){
                if(Home_IsOwner(playerid, id) || Home_IsRentOwner(playerid, id) || CanFriskHome[playerid] == HomeData[id][homeOwner]){
					if(!PlayerEditPositionInventory[playerid] && !PlayerEditColorInventory[playerid]){
						if(HomeData[id][homeStorageUsing]) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "คล้งบ้าน", "[!] ขณะนี้มีคนใช้งานคลังบ้านอยู่", "ตกลง", "");
						GetHomeOwnerIndex[playerid] = id;
						format(string, sizeof(string), "คลังบ้าน");
						Dialog_ShowEasy(playerid, StorageHome, DIALOG_STYLE_LIST, "จัดการบ้าน", string, "เลือก", "ยกเลิก");
					}
                }
            }

			if(PlayerData[playerid][pInjured] == 1){
				if(CallMedic[playerid] == 1)
					return ErrorMsg(playerid, "คุณได้เรียก แพทย์/หมอ ไปแล้ว");

				if(MedicToMe[playerid] != -1)
					return ErrorMsg(playerid, "คุณได้เรียก แพทย์/หมอ ไปแล้ว");

				foreach(new x : Player){
					if(!LoggedIn[x]) continue;
					if(x == playerid) continue;
					if(GetGroupType(x) == GROUP_MEDIC){
						SendClientMessageEx(x, 0xFF3E00AA, "(( %s(%d) ขอความช่วยเหลือใช้ >> '/chm [playerid] << ))", ReturnRoleplayName(playerid), playerid);
					}
				}
				SendClientMessage(playerid, COLOR_YELLOW, "คุณได้ส่งคำขอช่วยเหลือไปยัง หน่วยแพทย์/หมอ แล้ว");
				CallMedic[playerid] = 1;
			}

			//นอนโรงพยาบาล
			if(!PlayerCheckSleepOnBed[playerid]){
				//เตียง 1
				if(IsPlayerInRangeOfPoint(playerid, 3.0, 1393.7346,-4.9261,1001.0047)){
					new Float:hp;
					GetPlayerHealth(playerid, hp);
					if(hp >= 100) return ErrorMsg(playerid, "เลือดคุณเต็มแล้วไม่สามารถนอนได้");
					if(GetMoney(playerid) < 500) return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะนอนรักษา");
					SetPlayerPos(playerid, 1394.8353,-4.5559,1001.4913);
					SetPlayerFacingAngle(playerid, 83.2943);
					ClearAnimations(playerid);
					TogglePlayerControllable(playerid, 0);
					ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 0, 1);
					PlayerCheckSleepOnBed[playerid] = true;
				}
				//เตียง 2
				if(IsPlayerInRangeOfPoint(playerid, 3.0, 1383.1830,-5.0377,1001.0047)){
					new Float:hp;
					GetPlayerHealth(playerid, hp);
					if(hp >= 100) return ErrorMsg(playerid, "เลือดคุณเต็มแล้วไม่สามารถนอนได้");

					if(GetMoney(playerid) < 500) return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะนอนรักษา");

					SetPlayerPos(playerid, 1384.6593,-4.6863,1001.4913);
					SetPlayerFacingAngle(playerid, 87.1564);
					ClearAnimations(playerid);
					TogglePlayerControllable(playerid, 0);
					ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 0, 1);
					PlayerCheckSleepOnBed[playerid] = true;

				}
				//เตียง 3
				if(IsPlayerInRangeOfPoint(playerid, 3.0, 1372.1964,-5.0009,1001.0047)){

					new Float:hp;
					GetPlayerHealth(playerid, hp);
					if(hp >= 100) return ErrorMsg(playerid, "เลือดคุณเต็มแล้วไม่สามารถนอนได้");

					if(GetMoney(playerid) < 500) return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะนอนรักษา");

					SetPlayerPos(playerid, 1373.6599,-4.6932,1001.4913);
					SetPlayerFacingAngle(playerid, 88.7626);
					ClearAnimations(playerid);
					TogglePlayerControllable(playerid, 0);
					ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 0, 1);
					PlayerCheckSleepOnBed[playerid] = true;
				}
			}

			//----------------//

			if(PlayerToPoint(5.0, playerid, 1119.7837,-1494.6923,22.7690)){
				if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
				ShowDialogGiftMarry(playerid);
			}

			if(PlayerToPoint(5.0, playerid, 1988.0581,-2062.1467,13.3710)){
				if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณจำเป็นต้องเป็นคนขับ");
				InsuranceMenu(playerid);
			}

			if(PlayerToPoint(5.0, playerid, 358.5531,180.2974,1008.3828)){
				if(PlayerData[playerid][pMarrySQLID] == 0) return ErrorMsg(playerid, "คุณไม่มีคู่แต่งงาน");
				DivorcedMenu(playerid);
			}

			if(PlayerToPoint(3.0, playerid, 2316.6206,-9.9686,26.7422) || PlayerToPoint(3.0, playerid, 1110.6248,-1168.3284,23.8505)){
				Dialog_ShowEasy(playerid, Bank, DIALOG_STYLE_LIST, "บัญชีธนาคาร", "เงินเขียวในธนาคาร: %s", "เลือก", "ยกเลิก", FormatNumber(PlayerData[playerid][pBankMoney]));
			}

			if(ATM_Nearest(playerid) != -1){
				callcmd::atm(playerid, "\1");
			}

			if(Gate_Nearest(playerid) != -1){
				callcmd::door(playerid, "\1");
			}

			if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_NATIONAL){
				if (Arrest_Nearest(playerid) != -1){
					ShowSendPlayerToPrisonDialog(playerid);
				}
			}

			if ((id = Pump_Nearest(playerid)) != -1){
				new vehicleid = GetPlayerVehicleID(playerid);
				new carid = Car_GetID(vehicleid);
				if(carid != -1){
					if (PlayerData[playerid][pRefill] != INVALID_VEHICLE_ID){
						GiveMoney(playerid, -PlayerData[playerid][pRefillPrice], "pay pump");

						SendClientMessageEx(playerid, -1,"คุณได้เติมน้ำมันสำหรับรถของคุณในราคา %s", FormatNumber(PlayerData[playerid][pRefillPrice]));
						StopRefilling(playerid);
						KillTimer(RefuelTime[playerid]);
						RefuelTime[playerid] = 0;

						return 1;
					}

					if (!vehicleid)
						return ErrorMsg(playerid, "คุณไม่ได้อยู่ในยานพาหนะใด ๆ !");

					if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
						return ErrorMsg(playerid, "คุณต้องเป็นคนขับ!");

					if (GetEngineStatus(vehicleid))
						return ErrorMsg(playerid, "คุณต้องดับเครื่องยนต์ก่อน");

					if (id != -1)
					{
						if(carid != -1)
						{
							if (FuelVehicle(vehicleid) > 95)
								return ErrorMsg(playerid, "ยานพาหนะคันนี้ยังไม่จำเป็นต้องใช้น้ำมัน");

							if (IsPumpOccupied(id))
								return ErrorMsg(playerid, "ปั้มนี้มีคนใช้งานอยู่");

							if (PumpData[id][pumpFuel] < 1)
								return ErrorMsg(playerid, "ปั้มนี้มีน้ำมันไม่เพียงพอ");

							PlayerData[playerid][pGasPump] = id;

							PlayerData[playerid][pRefill] = vehicleid;
							RefuelTime[playerid] = SetTimerEx("RefillingFuel", 1000, false, "i", playerid);
							SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s เริ่มต้นเติมน้ำมันใส่ยานพาหนะของเขา", ReturnRoleplayName(playerid));
						}
					}
					else
					{
						ErrorMsg(playerid, "คุณไม่ได้อยู่ในขอบเขตปั้มก๊าซที่ไม่มีคนใช้");
					}
				}
			}

			//makeidcard
			if(PlayerToPoint(2.0, playerid, 361.8299, 173.5183, 1008.3828)){
				callcmd::makeidcard(playerid, "\1");
			}

			//checkmarket
			if(PlayerToPoint(2.0, playerid, 1134.0571,-1471.0575,15.7799) || PlayerToPoint(2.0, playerid, -2273.9236,527.0815,35.0156)){
				callcmd::market(playerid, "\1");
			}
			//checkblackmarket
			if(PlayerToPoint(2.0, playerid, -774.6674,1627.3953,27.1172)){
				callcmd::blackmarket(playerid, "\1");
			}
			//checkcrm
			if(PlayerToPoint(2.0, playerid, 1124.2960,-1470.8641,15.7682) || PlayerToPoint(2.0, playerid, -2274.0762,541.2120,35.0156)){
				CheckCrm(playerid);
			}

			//กู้คืนยานพาหนะ
			if(PlayerToPoint(3.0, playerid, 2413.9641,-2469.0508,13.6250)){
				ShowVehicleDestroy(playerid);
			}

			//กู้คืนเรือ
			if(PlayerToPoint(3.0, playerid, 125.9490,-1815.0796,0.4441)){
				ShowBoatDestroy(playerid);
			}

			//กู้คืนฮอ
			if(PlayerToPoint(3.0, playerid, 1905.3783,-2283.8252,13.5469)){
				ShowHeliDestroy(playerid);
			}

			//ร้านค้า VIP
			if(PlayerToPoint(2.0, playerid, 1112.0813,-1472.1615,15.7969)){
				ShowVipShop(playerid);
			}

			//ร้านค้าโดเนท
			if(PlayerToPoint(2.0, playerid, 1112.1853,-1466.6198,15.7969)){
				ShowDonateShop(playerid);
			}

			//ร้านสะดวกซื้อ
			if(PlayerToPoint(2.0, playerid, 1112.1279,-1461.1118,15.7969) || PlayerToPoint(3.0, playerid, 1919.5917,-1775.8834,13.5828)){
				Show24Shop(playerid);
			}

			//ตลาดสด
			if(PlayerToPoint(2.0, playerid, -2266.7739,549.7039,35.0156)){
				ShowMarketRaw(playerid);
			}

			if(PlayerData[playerid][pGroup] != -1){
				if((idgroup = IsNearGroupLocker(playerid)) != -1){
					if(GroupData[idgroup][groupType] == GROUP_MEDIC){
						ShowPlayerLockerMedic(playerid, idgroup);
					}
					if(GroupData[idgroup][groupType] == GROUP_POLICE){
						ShowPlayerLockerPolice(playerid, idgroup);
					}
					if(GroupData[idgroup][groupType] == GROUP_NATIONAL){
						ShowPlayerLockerPolice(playerid, idgroup);
					}
					if(GroupData[idgroup][groupType] == GROUP_MECHANIC){
						ShowPlayerLockerMechanic(playerid, idgroup);
					}
					if(GroupData[idgroup][groupType] == GROUP_GANG){
						ShowPlayerLockerGang(playerid, idgroup);
					}
					return 1;
				}
			}

			if((id = Casino_Nearest(playerid)) != -1){
				if(!CabaraIsOpen) return ErrorMsg(playerid, "ขณะนี้ไม่สามารถเล่นได้กรุณามาลองใหม่ในช่วงเวลา 12:00 - 14:00, 18:00 - 20:00, 00:00 - 03:00");

				if(PlayerData[playerid][pLevel] < 2) return ErrorMsg(playerid, "คุณต้องมีเลเวลมากกว่า 2");

				if(!PlayerOpeningMenuCabara[playerid]){
					for(new i=0; i<15; i++){
						TextDrawShowForPlayer(playerid, TextDrawCabara[i]);
					}
					SelectTextDraw(playerid, 0x00E50AAA);
					TogglePlayerControllable(playerid, 0);
					PlayerOpeningMenuCabara[playerid] = true;
					UpdateMoneyCabara();
				}
			}

			if ((id = Entrance_Nearest(playerid)) != -1){
				if(IsPlayerInAnyVehicle(playerid))
					return ErrorMsg(playerid, "คุณต้องลงจากรถก่อนจะเข้าไปข้างใน");

				if (EntranceData[id][entranceLocked])
					return SendClientMessage(playerid, -1, "ทางเข้านี้ถูกล็อคในขณะนี้");

				if(TimeEnterInterior[playerid] > 0) return 1;

				if(EntranceData[id][entranceType] == 2){
					ViewCarSell(playerid, 0);
					return 1;
				}

				if(EntranceData[id][entranceType] == 6){
					ViewCarSell(playerid, 1);
					return 1;
				}

				if(EntranceData[id][entranceType] == 4){
					if(StartTradeMoney[playerid] == 0){
						new countpolice = 0;
						foreach(new x : Player){
							if(!LoggedIn[x]) continue;
							if(GetGroupType(x) == GROUP_POLICE && BitFlag_Get(g_PlayerFlags[x], PLAYER_ONDUTY)){
								countpolice++;

								if(countpolice >= 7) break;
							}
						}

						if(countpolice >= 7)
							StartTradeRedMoney(playerid);

						else ErrorMsg(playerid, "ตำรวจต้องออนไลน์อย่างน้อย 7 คน");
					}
					return 1;
				}

				if(EntranceData[id][entranceFaction] > -1){
					new factionid = EntranceData[id][entranceFaction];

					if(PlayerData[playerid][pGroup] != EntranceData[id][entranceFaction])
						return SendClientMessageEx(playerid, COLOR_RED, "ทางเข้านี้ถูกจำกัดไว้เฉพาะ แฟคชั่น : %s", GroupData[factionid][groupName]);

					SetPlayerPosEx(playerid, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2], EntranceData[id][entranceInterior], EntranceData[id][entranceWorld]);
					SetPlayerFacingAngle(playerid, EntranceData[id][entranceInt][3]);
					SendClientMessageEx(playerid, COLOR_YELLOW, "%s", EntranceData[id][entranceMessage]);
					PlayerData[playerid][pEntrance] = EntranceData[id][entranceID];
					PlayerData[playerid][pEntranceIndex] = id;
				}
				else{
					SetPlayerPosEx(playerid, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2], EntranceData[id][entranceInterior], EntranceData[id][entranceWorld]);
					SetPlayerFacingAngle(playerid, EntranceData[id][entranceInt][3]);
					SendClientMessageEx(playerid, COLOR_YELLOW, "%s", EntranceData[id][entranceMessage]);
					PlayerData[playerid][pEntrance] = EntranceData[id][entranceID];
					PlayerData[playerid][pEntranceIndex] = id;
				}
				GameTextForPlayer(playerid,"~n~~n~~y~Loading Object....",5000,3);
				TimeEnterInterior[playerid] = 7;
				SetPlayerWeather(playerid, 1);
				return 1;
			}

			if ((id = Entrance_NearestInside(playerid)) != -1 && IsPlayerInRangeOfPoint(playerid, 2.5, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2])){
				if(TimeEnterInterior[playerid] > 0) return 1;

				if(EntranceData[id][entranceFaction] > -1){
					new factionid = EntranceData[id][entranceFaction];

					if(PlayerData[playerid][pGroup] != EntranceData[id][entranceFaction])
						return SendClientMessageEx(playerid, COLOR_RED, "ทางเข้านี้ถูกจำกัดไว้เฉพาะ กลุ่ม : %s", GroupData[factionid][groupName]);

					SetPlayerPosEx(playerid, EntranceData[id][entrancePos][0], EntranceData[id][entrancePos][1], EntranceData[id][entrancePos][2], EntranceData[id][entranceExterior], EntranceData[id][entranceExteriorVW]);
					SetPlayerFacingAngle(playerid, EntranceData[id][entrancePos][3] - 180.0);
					PlayerData[playerid][pEntrance] = Entrance_GetLink(playerid);
				}
				else{
					SetPlayerPosEx(playerid, EntranceData[id][entrancePos][0], EntranceData[id][entrancePos][1], EntranceData[id][entrancePos][2], EntranceData[id][entranceExterior], EntranceData[id][entranceExteriorVW]);
					SetPlayerFacingAngle(playerid, EntranceData[id][entrancePos][3] - 180.0);
					PlayerData[playerid][pEntrance] = Entrance_GetLink(playerid);
				}
				TimeEnterInterior[playerid] = 7;
				GameTextForPlayer(playerid,"~n~~n~~y~Loading Object....",5000,3);
				SetPlayerWeather(playerid, g_serverWeather);
				return 1;
			}

			if(CheckPlayerChangeSkin[playerid] == 1 && PlayerData[playerid][pJob] == COWJOB){
				if(PlayerInventory_AllCount(playerid, "Knife") > 0 && PlayerUseKnife[playerid] == 1){
					if ((id = Cow_Nearest(playerid)) != -1){
						if(CowData[id][cowDeath] == 1 && CowData[id][cowPicking] == 0){
							CowData[id][cowPicking] = 1;
							CowGetID[playerid] = id;

							if(CowGetID[playerid] != -1){
								//ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0xC9FF00AA, 100.000000, 0);
								CreatePlayerProgressbar_Job(playerid, 0xC9FF00AA);
								PickingUpCow[playerid] = 1;
								TogglePlayerControllable(playerid, 0);
								CowJobTimer[playerid] = SetTimerEx("PickingupMeat", 1000, 0, "i", playerid);
							}
						}
					}
				}
			}

			if((id = UpgradeWeapon_Nearest(playerid)) != -1){
				if(PlayerData[playerid][pLevel] < 5) return ErrorMsg(playerid, "คุณต้องมีเลเวล 5 ขึ้นไปถึงจะใช้ระบบนี้ได้");
				if(PlayerStart_UpgradeWeapon[playerid] == 0){
					if(Open_UpgradeMenu[playerid] == 0){
						OnPlayer_UpgradeWeaponShow(playerid);
					}
					else if(Open_UpgradeMenu[playerid] == 1){
						OnPlayer_UpgradeWeaponHide(playerid);
					}
				}
			}

			if ((id = Sidejob_Nearest(playerid)) != -1){
				if(SideJobData[id][sidejobType] == 1){
					ShowDialogCutWood(playerid);
				}

				if(SideJobData[id][sidejobType] == 2){
					//แปรรูปแร่
					if(!PlayerStartProcessMine[playerid])
						ShowMenuProcessMine(playerid);
				}

				if(SideJobData[id][sidejobType] == 3){
					SetPlayerStartDeliverBox(playerid);
				}
			}

			if ((id = Job_Nearest(playerid)) != -1){
				if (PlayerData[playerid][pJob] > 0)
					return SendClientMessage(playerid, -1, "คุณมีงานอยู่แล้ว");

				if (PlayerData[playerid][pJob] == JobData[id][jobType])
					return SendClientMessage(playerid, -1, "คุณสมัครงานนี้อยู่แล้ว");

				if(PlayerData[playerid][pLevel] < JobData[id][jobLevel]) return ErrorMsg(playerid, "คุณมีเลเวลไม่พอสำหรับอาชีพนี้");

				if(GetMoney(playerid) < 500)
					return ErrorMsg(playerid, "คุณมีเงินไม่พอ");

				PlayerData[playerid][pJob] = JobData[id][jobType];

				format(string, sizeof(string), "คุณได้สมัครงาน '%s' เรียบร้อยแล้วสามารถเริ่มงานได้เลย", Job_GetName(JobData[id][jobType]));
				SendClientMessage(playerid, COLOR_YELLOW, string);

				if(JobData[id][jobType] == FISHJOB){
					if(PlayerInventory_AllCount(playerid, "Fishing Rod") == 0){
						SendClientMessage(playerid, COLOR_ORANGE, "[คำเตือน]: คุณยังไม่มี 'เบ็ดตกปลา (Fishing Rod)' ดังนั้นไปคราฟก่อน");
					}
				}

				if(JobData[id][jobType] == SHARKJOB){
					if(PlayerInventory_AllCount(playerid, "Fishing Rod") == 0){
						SendClientMessage(playerid, COLOR_ORANGE, "[คำเตือน]: คุณยังไม่มี 'เบ็ดตกปลา (Fishing Rod)' ดังนั้นไปคราฟก่อน");
					}
				}

				if(JobData[id][jobType] == COWJOB){
					if(PlayerInventory_AllCount(playerid, "Knife") == 0){
						SendClientMessage(playerid, COLOR_ORANGE, "[คำเตือน]: คุณยังไม่มี 'มีด (Knife)' ดังนั้นไปคราฟก่อน");
					}
				}

				GiveMoney(playerid, -500, "register job");
				return 1;
			}

			if((id = Job_NearestPoint(playerid)) != -1){
				if(JobData[id][jobType] == FARMERJOB){
					if(PlayerData[playerid][pJob] == FARMERJOB){
						if(StartFarmerJob[playerid] == 0){
							StartFarmerJob[playerid] = 1;
							SendClientMessage(playerid, COLOR_ORANGE, "- คุณได้เริ่มงานของ ชาวนา แล้ว");
							SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: โปรดขึ้นรถเก็บข้าวเพื่อเริ่มงาน");
						}

						else if(StartFarmerJob[playerid] == 1){
							StartFarmerJob[playerid] = 0;
							ResetFarmerJob(playerid);
							SendClientMessage(playerid, COLOR_ORANGE, "- คุณได้เลิกงาน ชาวนา เรียบร้อยแล้ว");
						}
					}
				}

				if(JobData[id][jobType] == BUILDJOB){
					if(PlayerData[playerid][pJob] == BUILDJOB){
						if(StartChangeSkinBuildJob[playerid] == 0){
							SetPlayerSkin(playerid, 260);
							SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เปลี่ยนชุดทำงานก่อสร้างเรียบร้อยแล้ว");
							StartChangeSkinBuildJob[playerid] = 1;
						}
						else if(StartChangeSkinBuildJob[playerid] == 1){
							SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
							SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เปลี่ยนชุดกลับเป็นชุดเดิมของคุณแล้ว");
							StartChangeSkinBuildJob[playerid] = 0;
							ResetBuildJob(playerid);
						}
					}
				}

				if(JobData[id][jobType] == GASJOB){
					if(PlayerData[playerid][pJob] == GASJOB){
						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) return 1;
						PickupGas(playerid);
					}
				}

				if(JobData[id][jobType] == COWJOB && PlayerData[playerid][pJob] == COWJOB){
					SetPlayerSkinToCowJob(playerid);
				}

				if(JobData[id][jobType] == ENGJOB){
					if(PlayerData[playerid][pJob] == ENGJOB){
						if(ChangeSkinEngJob[playerid] == 0){
							SetPlayerSkin(playerid, 16);
							SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เปลี่ยนชุดทำงานช่างไฟเรียบร้อยแล้ว");
							SetPlayerAttachedObject(playerid,8,19921,6,0.038999,0.023000,0.004000,-71.699935,-179.699859,94.899955,1.000000,1.000000,1.000000);
							ChangeSkinEngJob[playerid] = 1;
							GetJobID[playerid] = id;
						}
						else if(ChangeSkinEngJob[playerid] == 1){
							SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
							SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เปลี่ยนชุดกลับเป็นชุดเดิมของคุณแล้ว");
							ChangeSkinEngJob[playerid] = 0;
							DisablePlayerCheckpoint(playerid);
							RemoveAttachedObject(playerid, 8);
							ResetEngjob(playerid);
							GetJobID[playerid] = -1;
						}
					}
				}

				if(JobData[id][jobType] == WEAPONDEALERJOB){
					if(PlayerData[playerid][pJob] == WEAPONDEALERJOB){
						GetPowForPlayer(playerid, id);
					}
				}

				if(JobData[id][jobType] == GARBAGEJOB && PlayerData[playerid][pJob] == GARBAGEJOB){
					SetPlayerSkinGarbage(playerid);
				}

				if(JobData[id][jobType] == RUBBERJOB && PlayerData[playerid][pJob] == RUBBERJOB){
					SetPlayerToolRubber(playerid);
				}

				if(JobData[id][jobType] == SEEKERJOB && PlayerData[playerid][pJob] == SEEKERJOB){
					OnPlayerStartJobSeeker(playerid);
				}

				if(JobData[id][jobType] == GARDENER && PlayerData[playerid][pJob] == GARDENER){
					StartJobGardener(playerid);
				}

				if(JobData[id][jobType] == OILJOB && PlayerData[playerid][pJob] == OILJOB){
					StartPlayerProcessOil(playerid);
				}
			}

			if((id = Job_NearestPoint2Fish(playerid)) != -1){
				if(PlayerData[playerid][pJob] == FISHJOB){
					if(PlayerCanFishing[playerid] == 1){
						if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER){
							if(PlayerInventory_AllCount(playerid, "Fishing Rod") < 1)
								return ErrorMsg(playerid, "คุณไม่มี เบ็ดตกปลา");

							if(PlayerPressYToFishing[playerid] == 1)
								return ErrorMsg(playerid, "คุณกำลังตกปลาอยู่, ไม่สามารถกดอีกได้");

							PlayerPressYToFishing[playerid] = 1;
							SetPlayerAttachedObject(playerid, 7, 18632, 6,0.079376,0.037070,0.007706,181.482910,0.000000,0.000000,1.000000,1.000000,1.000000);
							SetCameraBehindPlayer(playerid);
							ApplyAnimation(playerid,"SWORD","sword_block",50.0,0,1,0,1,1);

							//ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0x00CDFFAA, 100.000000, 0);
							CreatePlayerProgressbar_Job(playerid, 0x00CDFFAA);
							FishJobTimer[playerid] = SetTimerEx("Fishing", 1000, 0, "i", playerid);
						}
					}
				}
			}

			if((id = Job_NearestPoint2(playerid)) != -1){
				if(JobData[id][jobType] == BUILDJOB){
					if(PlayerData[playerid][pJob] == BUILDJOB){

						if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
							return ErrorMsg(playerid, "คุณจำเป็นต้องลงจากรถก่อน");

						if(StartChangeSkinBuildJob[playerid] == 0)
							return ErrorMsg(playerid, "คุณยังไม่ได้ใส่ชุดทำงานก่อสร้าง");

						if(StartBuildJob[playerid] == 1)
							return ErrorMsg(playerid, "คุณแบกปูนอยู่เอาไปส่งก่อน");

						StartBuildJob[playerid] = 1;
						BuilddingGetID[playerid] = id;
						SetPlayerAttachedObject(playerid,8,2060,6,-0.010999,0.015000,-0.239000,-115.699996,-17.800022,-102.099998,1.000000,1.000000,1.000000);
						SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
						new idx = GetClosestJobDeliver(playerid, PlayerData[playerid][pJob]);
						if (idx != -1)
						{
							if(JobData[idx][jobDeliver][0] == 0.0 && JobData[idx][jobDeliver][1] == 0.0 && JobData[idx][jobDeliver][2] == 0.0)
								return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

							EnterCheckPointJob[playerid] = 1;

							SetPlayerCheckpoint(playerid, JobData[idx][jobDeliver][0], JobData[idx][jobDeliver][1], JobData[idx][jobDeliver][2],3.0);
							SendClientMessage(playerid, -1,"ไปยังจุดสีแดงเพื่อส่งปูน");
						}
					}
				}

				if(JobData[id][jobType] == COWJOB && PlayerData[playerid][pJob] == COWJOB){
					if(StartProcessMeat[playerid] == 1)
						return ErrorMsg(playerid, "คุณกำลัง Process อยู่");

					if(PlayerInventory_AllCount(playerid, "Raw Cow Meat") < 10)
						return ErrorMsg(playerid, "คุณต้องมีเนื้อมากกว่า 10");

					StartProcessMeat[playerid] = 1;
					//ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0xC9FF00AA, 100.000000, 0);
					CreatePlayerProgressbar_Job(playerid, 0xC9FF00AA);
					TogglePlayerControllable(playerid, 0);
					CowJobTimer[playerid] = SetTimerEx("ProcessMeat", 1000, 0, "i", playerid);
				}

				if(JobData[id][jobType] == WEAPONDEALERJOB && PlayerData[playerid][pJob] == WEAPONDEALERJOB){
					if(StartingCraftWeapon[playerid] == 1)
						return ErrorMsg(playerid, "คุณกำลังคราฟอาวุธอยู่...");

					ShowPlayerCraftWeaponMenu(playerid);
				}

				if(JobData[id][jobType] == SEEKERJOB && PlayerData[playerid][pJob] == SEEKERJOB){
					if(StartingWashTreasure[playerid] == 0){
						OnPlayerWashTreasure(playerid);
					}
				}

				if(JobData[id][jobType] == GARDENER && PlayerData[playerid][pJob] == GARDENER){
					if(FinishGardener[playerid] == 1){
						SendGardener(playerid);
					}
				}
			}

			if((id = Job_NearestDelivery(playerid)) != -1){
				if(JobData[id][jobType] == GASJOB)
				{
					if(CarryGas[playerid] == 0)
						return ErrorMsg(playerid, "คุณไม่ได้ถือแก๊สอยู่");

					CarryGas[playerid] = 0;
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					RemoveAttachedObject(playerid, 8);
					GiveMoney(playerid, JobData[id][jobDeliverPrice], "send gas");
					SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้รับเงินจำนวน %s จากการส่งแก๊สครั้งนี้", FormatNumber(JobData[id][jobDeliverPrice]));
				}

				if(JobData[id][jobType] == FARMERJOB){
					GetJobID[playerid] = id;
					ShowDialogSellRice(playerid);
				}

				if(JobData[id][jobType] == FISHJOB){
					GetJobID[playerid] = id;
					ShowDialogSellFish(playerid);
				}

				if(JobData[id][jobType] == SHARKJOB){
					GetJobID[playerid] = id;
					ShowDialogSellFishShark(playerid);
				}

				if(JobData[id][jobType] == JELLYJOB){
					GetJobID[playerid] = id;
					ShowDialogSellJellyFish(playerid);
				}

				if(JobData[id][jobType] == COWJOB){
					GetJobID[playerid] = id;
					ShowDialogSellCow(playerid);
				}

				if(JobData[id][jobType] == RUBBERJOB){
					GetJobID[playerid] = id;
					ShowDialogSellRubber(playerid);
				}

				if(JobData[id][jobType] == SEEKERJOB){
					GetJobID[playerid] = id;
					ShowDialogSellSeeker(playerid);
				}

				if(JobData[id][jobType] == OILJOB){
					GetJobID[playerid] = id;
					ShowDialogSellOil(playerid);
				}

				if(JobData[id][jobType] == SHELLJOB){
					GetJobID[playerid] = id;
					ShowDialogSellShell(playerid);
				}

				if(JobData[id][jobType] == ORANGEJOB){
					GetJobID[playerid] = id;
					ShowDialogSellOrange(playerid);
				}
			}

			if((id = Job_NearestPoint2Farmer(playerid)) != -1){
				if(PlayerData[playerid][pJob] == FARMERJOB){
					if(StartFarmerJob[playerid] == 1){
						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
							new vehicleid = GetPlayerVehicleID(playerid);
							if(GetVehicleModel(vehicleid) == 532){

								if(HarvestPont[playerid] < 50) return ErrorMsg(playerid, "คุณต้องเก็บข้าวให้เต็มรถก่อน");

								DestroyPlayerProgressbar_Job(playerid);

								//ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 9109759, 100.000000, 0);
								CreatePlayerProgressbar_Job(playerid, 9109759);

								KillTimer(HarvestTimer[playerid]);

								StartProcessFarmer[playerid] = 1;
								ProcessFarmerTime[playerid] = SetTimerEx("StartingProcessRice", 1000, false, "ii", playerid, ProcessFarmerPoint[playerid]);
								TogglePlayerControllable(playerid, 0);
								format(string,sizeof(string),"~n~~n~~n~~n~~n~~n~~n~~n~~y~Process Rice: %d/100", ProcessFarmerPoint[playerid]);
				    			GameTextForPlayer(playerid, string, 1500, 3);
							}
							else
								return ErrorMsg(playerid, "คุณไม่ได้อยู่บนรถเก็บข้าว");
						}
						else
							return ErrorMsg(playerid, "คุณไม่ได้อยู่บนรถ");
					}
				}
			}
		}
	}
	return 1;
}

forward RefillingFuel(x);
public RefillingFuel(x){
	if(!LoggedIn[x]) return KillTimer(RefuelTime[x]);
	new string[256];
	if(GetPlayerState(x) == PLAYER_STATE_DRIVER){
		if (PlayerData[x][pRefill] != INVALID_VEHICLE_ID && PlayerData[x][pGasPump] != -1){
			PlayerData[x][pRefillPrice] += PumpData[PlayerData[x][pGasPump]][pumpPrice];
			new id = Car_GetID(PlayerData[x][pRefill]);

			if(id != -1){
				CarData[id][carFuel]++;

				PumpData[PlayerData[x][pGasPump]][pumpFuel] --;

				RefuelTime[x] = SetTimerEx("RefillingFuel", 1000, false, "i", x);

				if (PumpData[PlayerData[x][pGasPump]][pumpExists]){
					format(string, sizeof(string), "[ปั้มน้ำมัน: %d]\n{FFFFFF}น้ำมันที่เหลืออยู่: %d ลิตร\n{FF0000}* ราคา ลิตรละ %s *\n{FFFFFF}( กด 'Y' เพื่อเติมน้ำมัน )\n( พิมพ์ '/gascan' เพื่อซื้อแกลลอนน้ำมัน )", PlayerData[x][pGasPump], PumpData[PlayerData[x][pGasPump]][pumpFuel], FormatNumber(PumpData[PlayerData[x][pGasPump]][pumpPrice]));
					UpdateDynamic3DTextLabelText(PumpData[PlayerData[x][pGasPump]][pumpText3D], COLOR_YELLOW, string);
				}
				if (CarData[id][carFuel] >= 100 || GetEngineStatus(PlayerData[x][pRefill]) || !PumpData[PlayerData[x][pGasPump]][pumpExists] || PumpData[PlayerData[x][pGasPump]][pumpFuel] < 0){
					KillTimer(RefuelTime[x]);
					RefuelTime[x] = 0;
					GiveMoney(x, -PlayerData[x][pRefillPrice], "pay fuel");
					SendClientMessageEx(x, -1, "คุณเติมเชื้อเพลิงให้กับยานพาหนะของคุณในราคา %s", FormatNumber(PlayerData[x][pRefillPrice]));

					if (PumpData[PlayerData[x][pGasPump]][pumpExists]){
						if (PumpData[PlayerData[x][pGasPump]][pumpFuel] < 0)
							PumpData[PlayerData[x][pGasPump]][pumpFuel] = 0;

						Pump_Save(PlayerData[x][pGasPump]);
					}
					StopRefilling(x);
				}
			}
		}
	}
	return 1;
}

ResetGasPump(x){
	if(GetPlayerState(x) == PLAYER_STATE_DRIVER){
		if (PlayerData[x][pRefill] != INVALID_VEHICLE_ID && PlayerData[x][pGasPump] != -1){
			PlayerData[x][pRefillPrice] += PumpData[PlayerData[x][pGasPump]][pumpPrice];
			new id = Car_GetID(PlayerData[x][pRefill]);

			if(id != -1){
				KillTimer(RefuelTime[x]);
				RefuelTime[x] = 0;
				GiveMoney(x, -PlayerData[x][pRefillPrice], "pay fuel");
				SendClientMessageEx(x, -1, "คุณเติมเชื้อเพลิงให้กับยานพาหนะของคุณในราคา %s", FormatNumber(PlayerData[x][pRefillPrice]));

				if (PumpData[PlayerData[x][pGasPump]][pumpExists]){
					if (PumpData[PlayerData[x][pGasPump]][pumpFuel] < 0)
						PumpData[PlayerData[x][pGasPump]][pumpFuel] = 0;

					Pump_Save(PlayerData[x][pGasPump]);
				}
				StopRefilling(x);
			}
		}
	}
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success){
	if(!success){
		new string[128];
		format(string, sizeof(string), "%s พยายามเข้า Rcon Password แต่ไม่สำเร็จ", ip);
    	SendAdminsMessage(1, COLOR_RED, string);
	}
	return 1;
}

public OnPlayerUpdate(playerid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	SecurityAC_CheckPlayer(playerid);
	if(IsAFK{playerid} && LoggedIn[playerid]){
		printf("%s Come in Server After AFK", ReturnRoleplayName(playerid));
		new query[256];
		mysql_format(dbCon, query, sizeof(query), "SELECT Wallet, UpdateWallet, WalletAfter FROM `accounts` WHERE Name = '%e' AND SQLID = %d AND UpdateWallet = 1 LIMIT 1", AccountData[playerid][uName], AccountData[playerid][uSQLID]);
		mysql_tquery(dbCon, query, "UpdateAccountWallet", "i", playerid);
	}
	IsAFK{playerid} = false;
	AFKTimer[playerid] = 3;
	if(!IsAFK{playerid} && LoggedIn[playerid]){
		SetPlayerNameTag(playerid, playerid);
	}
	return 1;
}

forward UpdateAccountWallet(playerid);
public UpdateAccountWallet(playerid){
    if(cache_num_rows()){
		new query[256], walletafter;
		cache_get_value_name_int(0, "Wallet", AccountData[playerid][uWallet]);
		cache_get_value_name_int(0, "WalletAfter", walletafter);
		mysql_format(dbCon, query, sizeof(query), "UPDATE accounts SET UpdateWallet = 0, WalletAfter = 0 WHERE Name = '%e' AND SQLID = %d LIMIT 1", AccountData[playerid][uName], AccountData[playerid][uSQLID]);
		mysql_tquery(dbCon, query);
		printf("Wallet %s Update", AccountData[playerid][uName]);
		SendClientMessageEx(playerid, COLOR_GREEN, "[การเติมเงิน]: {FFFFFF}คุณได้รับ %d Wallet", walletafter);
	}
    return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(forplayerid < 0 || forplayerid >= MAX_PLAYERS || !IsPlayerConnected(forplayerid)) return 0;
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	if(playerid < 0 || playerid >= MAX_PLAYERS) return 0;
	if(forplayerid < 0 || forplayerid >= MAX_PLAYERS || !IsPlayerConnected(forplayerid)) return 0;
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES) return 0;
	if(forplayerid < 0 || forplayerid >= MAX_PLAYERS || !IsPlayerConnected(forplayerid)) return 0;
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	if(vehicleid < 1 || vehicleid >= MAX_VEHICLES) return 0;
	if(forplayerid < 0 || forplayerid >= MAX_PLAYERS || !IsPlayerConnected(forplayerid)) return 0;
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;

	if(PlayerInScreen[playerid]){
		if(playertextid == ScreenTextDraw[playerid][1]){
			CancelSelectTextDraw(playerid);
			for(new i=0; i<5; i++){
				PlayerTextDrawHide(playerid, ScreenTextDraw[playerid][i]);
				PlayerTextDrawDestroy(playerid, ScreenTextDraw[playerid][i]);
			}
			PlayerInScreen[playerid] = false;
			return LoadingToFindAccount(playerid);
		}

		if(playertextid == ScreenTextDraw[playerid][2]){
			CancelSelectTextDraw(playerid);
			for(new i=0; i<5; i++){
				PlayerTextDrawHide(playerid, ScreenTextDraw[playerid][i]);
				PlayerTextDrawDestroy(playerid, ScreenTextDraw[playerid][i]);
			}
			PlayerInScreen[playerid] = false;
			return Kick(playerid);
		}
	}

	if(SelectCharTextDraw[playerid] == 1){
		if(playertextid == CharSelect[playerid][11] && !playerClickFetchCharacter[playerid]){
			if(PlayerData[playerid][pSelectPlayChar] != -1){
				stop RunWalk[playerid];
				stop StopWalkScreen[playerid];
				Character_Fetch(playerid, PlayerData[playerid][pSelectPlayChar]);
				PlayerData[playerid][pSelectPlayChar] = -1;
			}
			return 1;
		}

		if(playertextid == CharSelect[playerid][2]){
			if(PlayerClickCharList[playerid] == PlayerData[playerid][pSelectChar1]) return 1;
			PlayerData[playerid][pSelectChar] = 1;
			Characters_FetchReClick(playerid, PlayerData[playerid][pSelectChar1]);
			return 1;
		}

		if(playertextid == CharSelect[playerid][3]){
			if(PlayerClickCharList[playerid] == PlayerData[playerid][pSelectChar2]) return 1;
			PlayerData[playerid][pSelectChar] = 2;
			PlayerClickCharList[playerid] = PlayerData[playerid][pSelectChar2];
			Characters_FetchReClick(playerid, PlayerData[playerid][pSelectChar2]);
			return 1;
		}

		if(playertextid == CharSelect[playerid][4]){
			if(PlayerClickCharList[playerid] == PlayerData[playerid][pSelectChar3]) return 1;
			PlayerData[playerid][pSelectChar] = 3;
			PlayerClickCharList[playerid] = PlayerData[playerid][pSelectChar3];
			Characters_FetchReClick(playerid, PlayerData[playerid][pSelectChar3]);
			return 1;
		}

		if(playertextid == CharSelect[playerid][12]){

			if(LoggedIn[playerid]) return 1;

			new str[64], dialog[512];
			format(dialog, sizeof(dialog), " สร้างตัวละครใหม่");
			format(str, sizeof(str), "ตัวละครของ: %s", ReturnName(playerid));
			Dialog_ShowEasy(playerid, Character_Select, DIALOG_STYLE_LIST, str, dialog, "ตกลง","ยกเลิก");

			PlayerData[playerid][pSelectChar] = 1;

			for(new i=0; i<15; i++){
				PlayerTextDrawHide(playerid, CharSelect[playerid][i]);
				PlayerTextDrawDestroy(playerid, CharSelect[playerid][i]);
			}
			CancelSelectTextDraw(playerid);
			return 1;
		}

		if(playertextid == CharSelect[playerid][13]){

			if(LoggedIn[playerid]) return 1;

			new str[64], dialog[512];
			format(dialog, sizeof(dialog), " สร้างตัวละครใหม่");
			format(str, sizeof(str), "ตัวละครของ: %s", ReturnName(playerid));
			Dialog_ShowEasy(playerid, Character_Select, DIALOG_STYLE_LIST, str, dialog, "ตกลง","ยกเลิก");

			PlayerData[playerid][pSelectChar] = 2;

			for(new i=0; i<15; i++){
				PlayerTextDrawHide(playerid, CharSelect[playerid][i]);
				PlayerTextDrawDestroy(playerid, CharSelect[playerid][i]);
			}
			CancelSelectTextDraw(playerid);
			return 1;
		}

		if(playertextid == CharSelect[playerid][14]){

			if(LoggedIn[playerid]) return 1;

			new str[64], dialog[512];

			format(dialog, sizeof(dialog), " สร้างตัวละครใหม่");
			format(str, sizeof(str), "ตัวละครของ: %s", ReturnName(playerid));
			Dialog_ShowEasy(playerid, Character_Select, DIALOG_STYLE_LIST, str, dialog, "ตกลง","ยกเลิก");

			PlayerData[playerid][pSelectChar] = 3;

			for(new i=0; i<15; i++){
				PlayerTextDrawHide(playerid, CharSelect[playerid][i]);
				PlayerTextDrawDestroy(playerid, CharSelect[playerid][i]);
			}
			CancelSelectTextDraw(playerid);
			return 1;
		}
	}

	if(!LoggedIn[playerid]) return 0;

	if(PlayerOpenFoodShop[playerid]){
		if(playertextid == FoodShop[playerid][3]){
			if(!PlayerCarryFood[playerid]) PlayerBuyFoodShop(playerid, 1);
		}

		if(playertextid == FoodShop[playerid][8]){
			if(!PlayerCarryFood[playerid]) PlayerBuyFoodShop(playerid, 2);
		}

		if(playertextid == FoodShop[playerid][12]){
			PlayerBuyFoodShop(playerid, 3);
		}

		if(playertextid == FoodShop[playerid][2]){
			PlayerFoodShopMenu_Hide(playerid);
		}
	}

	if(PlayerInventoryStatus[playerid]){

		if(PlayerEditColorInventory[playerid]){
			if(IsAndroidPlayer(playerid)){
				new Keys,ud,lr;
				GetPlayerKeys(playerid, Keys, ud, lr);

				if(playertextid == ArrowEditInv[playerid][0]){ //ขึ้น
					if(PlayerInventoryColorType[playerid] == 0){
						if(PlayerInventoryColorR[playerid] < 255){
							PlayerInventoryColorR[playerid] += 5;
							if(PlayerInventoryColorR[playerid] >= 255) PlayerInventoryColorR[playerid] = 255;
							//printf("[R]: %d", PlayerInventoryColorR[playerid]);
							PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
							//printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
							Update_EditColorInventory(playerid);
						}
					}
					else if(PlayerInventoryColorType[playerid] == 1){
						if(PlayerInventoryColorG[playerid] < 255){
							PlayerInventoryColorG[playerid] += 5;
							if(PlayerInventoryColorG[playerid] >= 255) PlayerInventoryColorG[playerid] = 255;
							//printf("[G]: %d", PlayerInventoryColorG[playerid]);
							PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
							//printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
							Update_EditColorInventory(playerid);
						}
					}
					else if(PlayerInventoryColorType[playerid] == 2){
						if(PlayerInventoryColorB[playerid] < 255){
							PlayerInventoryColorB[playerid] += 5;
							if(PlayerInventoryColorB[playerid] >= 255) PlayerInventoryColorB[playerid] = 255;
							//printf("[G]: %d", PlayerInventoryColorB[playerid]);
							PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
							//printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
							Update_EditColorInventory(playerid);
						}
					}
				}

				if(playertextid == ArrowEditInv[playerid][1]){ //ลง
					if(PlayerInventoryColorType[playerid] == 0){
						if(PlayerInventoryColorR[playerid] > 0){
							PlayerInventoryColorR[playerid] -= 5;
							if(PlayerInventoryColorR[playerid] <= 0) PlayerInventoryColorR[playerid] = 0;
							//printf("[R]: %d", PlayerInventoryColorR[playerid]);
							PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
							//printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
							Update_EditColorInventory(playerid);
						}
					}
					else if(PlayerInventoryColorType[playerid] == 1){
						if(PlayerInventoryColorG[playerid] > 0){
							PlayerInventoryColorG[playerid] -= 5;
							if(PlayerInventoryColorG[playerid] <= 0) PlayerInventoryColorG[playerid] = 0;
							//printf("[R]: %d", PlayerInventoryColorG[playerid]);
							PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
							//printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
							Update_EditColorInventory(playerid);
						}
					}
					else if(PlayerInventoryColorType[playerid] == 2){
						if(PlayerInventoryColorB[playerid] > 0){
							PlayerInventoryColorB[playerid] -= 5;
							if(PlayerInventoryColorB[playerid] <= 0) PlayerInventoryColorB[playerid] = 0;
							//printf("[R]: %d", PlayerInventoryColorB[playerid]);
							PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
							//printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
							Update_EditColorInventory(playerid);
						}
					}
				}

				if(playertextid == ArrowEditInv[playerid][3]){ //ขวา
					if(PlayerInventoryColorType[playerid] == 0) {
						PlayerInventoryColorType[playerid] = 1;
						GameTextForPlayer(playerid, "~W~Edit Color ~G~GREEN", 3000, 6);
					}
					else if(PlayerInventoryColorType[playerid] == 1) {
						PlayerInventoryColorType[playerid] = 2;
						GameTextForPlayer(playerid, "~W~Edit Color ~B~BLUE", 3000, 6);
					}
					else if(PlayerInventoryColorType[playerid] == 2) {
						PlayerInventoryColorType[playerid] = 0;
						GameTextForPlayer(playerid, "~W~Edit Color ~R~RED", 3000, 6);
					}
				}

				if(playertextid == ArrowEditInv[playerid][2]){ //ซ้าย
					if(PlayerInventoryColorType[playerid] == 0) {
						PlayerInventoryColorType[playerid] = 2;
						GameTextForPlayer(playerid, "~W~Edit Color ~B~BLUE", 3000, 6);
					}
					else if(PlayerInventoryColorType[playerid] == 1) {
						PlayerInventoryColorType[playerid] = 0;
						GameTextForPlayer(playerid, "~W~Edit Color ~R~RED", 3000, 6);
					}
					else if(PlayerInventoryColorType[playerid] == 2) {
						PlayerInventoryColorType[playerid] = 1;
						GameTextForPlayer(playerid, "~W~Edit Color ~G~GREEN", 3000, 6);
					}
				}
			}
		}

		if(PlayerEditPositionInventory[playerid]){
			if(IsAndroidPlayer(playerid)){
				if(playertextid == ArrowEditInv[playerid][0]){ //ขึ้น
					if(PlayerPositionInventoryY[playerid] > -30){
						//printf("UP");
						PlayerPositionInventoryY[playerid] -= 5.0;
						Update_EditPositionInventory(playerid);
					}
				}

				if(playertextid == ArrowEditInv[playerid][1]){ //ลง
					if(PlayerPositionInventoryY[playerid] < 200){
						//printf("DOWN");
						PlayerPositionInventoryY[playerid] += 5.0;
						Update_EditPositionInventory(playerid);
					}
				}

				if(playertextid == ArrowEditInv[playerid][2]){ //ซ้าย
					if(PlayerPositionInventoryX[playerid] > -225){
						//printf("LEFT");
						PlayerPositionInventoryX[playerid] -= 5.0;
						Update_EditPositionInventory(playerid);
					}

				}

				if(playertextid == ArrowEditInv[playerid][3]){ //ขวา
					if(PlayerPositionInventoryX[playerid] < 50){
						//printf("RIGHT");
						PlayerPositionInventoryX[playerid] += 5.0;
						Update_EditPositionInventory(playerid);
					}
				}
			}
		}

		if(!PlayerCantSelectTextDraw[playerid]){
			if(PlayerCharacterShow[playerid]){
				if(playertextid == PlayerCharacterTextDraw[playerid][6]){
					if(PlayerData[playerid][pMyWeapon][2] != 0){
						OnPlayerStoreWeapon3(playerid, PlayerData[playerid][pMyWeapon][2]);
						PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
					}
				}

				if(playertextid == PlayerCharacterTextDraw[playerid][10]){
					if(PlayerData[playerid][pMyWeapon][1] != 0){
						OnPlayerStoreWeapon2(playerid, PlayerData[playerid][pMyWeapon][1]);
						PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
					}
				}

				if(playertextid == PlayerCharacterTextDraw[playerid][14]){
					if(PlayerData[playerid][pMyWeapon][0] != 0){
						OnPlayerStoreWeapon1(playerid, PlayerData[playerid][pMyWeapon][0]);
						PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
					}
				}

				if(playertextid == PlayerCharacterTextDraw[playerid][5]){
					if(PlayerData[playerid][pUseSkin] == 1) SkinOutPlayer(playerid);
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}

				//Accessory
				if(playertextid == PlayerCharacterTextDraw[playerid][18]){
					ShowPlayerAccessory(playerid);
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}

				//info
				if(playertextid == PlayerCharacterTextDraw[playerid][19]){
					ShowStatsForPlayer(playerid, playerid);
					OnPlayerInventory_Close(playerid);
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}

				//home
				if(playertextid == PlayerCharacterTextDraw[playerid][20]){
					Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "แจ้งเตือน", "รอการอัพเดท...", "ตกลง", "");
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}

				//skills
				if(playertextid == PlayerCharacterTextDraw[playerid][21]){
					ShowPlayerSkills(playerid);
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}

				//licenses
				if(playertextid == PlayerCharacterTextDraw[playerid][22]){
					Dialog_ShowEasy(playerid, ShowLicenses, DIALOG_STYLE_LIST, "บัตรประจำตัวต่างๆ", "- บัตรประชาชน\n- บัตรประจำตัวหน่วยงาน\n- ใบขับขี่", "เลือก", "ยกเลิก");
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
					OnPlayerInventory_Close(playerid);
				}

				//quest
				if(playertextid == PlayerCharacterTextDraw[playerid][23]){
					ShowPlayerQuest(playerid);
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}

				//party
				if(playertextid == PlayerCharacterTextDraw[playerid][24]){
					Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "แจ้งเตือน", "รอการอัพเดท...", "ตกลง", "");
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}
			}

			if(playertextid == PlayerInventoryTextDraw[playerid][10]){
				OnPlayerInventory_Close(playerid);
				if(PlayerUsing_HomeInv[playerid]) OnPlayerHomeInv_Close(playerid);

				ShowPlayerTradeMoneyMenu(playerid);
				PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
			}

			if(playertextid == PlayerInventoryTextDraw[playerid][3]){
				OnPlayerInventory_Close(playerid);

				if(PlayerUsing_HomeInv[playerid]){
					OnPlayerHomeInv_Close(playerid);
				}

				if(PlayerSelectingItem[playerid]){
					defer ReloadTradeItem(playerid);
				}
				PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
			}

			if(playertextid == PlayerInventoryTextDraw[playerid][9]){
				if(PlayerInventoryType[playerid] != HOME_TYPE){
					if(PlayerGetIndexSlotItem[playerid] != -1 && !PlayerTradingItem[playerid]){
						Player_DropItem(playerid, PlayerGetIndexSlotItem[playerid]);
						PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
					}
				}

				PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
			}

			if(playertextid == PlayerInventoryTextDraw[playerid][17]){
				if(PlayerInventoryPage[playerid] != 1){
					if(PlayerData[playerid][pMaxItem] < 36) return 1;
					PlayerInventoryPage[playerid] = 1;
					if(PlayerGetIndexSlotItem[playerid] != -1) RemoveUseInfoButton(playerid);
					OnPlayerInventory_Render(playerid);
				}
				PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
			}

			if(playertextid == PlayerInventoryTextDraw[playerid][18]){
				if(PlayerInventoryPage[playerid] != 2){
					if(PlayerData[playerid][pMaxItem] < 72) return 1;
					PlayerInventoryPage[playerid] = 2;
					if(PlayerGetIndexSlotItem[playerid] != -1) RemoveUseInfoButton(playerid);
					OnPlayerInventory_Render(playerid);
				}
				PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
			}

			if(playertextid == PlayerInventoryTextDraw[playerid][19]){
				if(PlayerInventoryPage[playerid] != 3){
					if(PlayerData[playerid][pMaxItem] < 108) return 1;
					PlayerInventoryPage[playerid] = 3;
					if(PlayerGetIndexSlotItem[playerid] != -1) RemoveUseInfoButton(playerid);
					OnPlayerInventory_Render(playerid);
				}
				PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
			}

			if(PlayerShowButton[playerid]){
				if(playertextid == UseButton[playerid]){
					if(PlayerInventoryType[playerid] == INVENTORY_TYPE){
						if(PlayerGetIndexSlotItem[playerid] != -1){
							CallLocalFunction("OnPlayerInventory_UseItem", "dsdd", playerid, Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemName], Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemKey], PlayerGetIndexSlotItem[playerid]);
						}
					}
					else if(PlayerInventoryType[playerid] == TRADE_TYPE){
						new itemid = PlayerGetIndexSlotItem[playerid];
						if(itemid != -1){
							if(Item_CantDrop(Inventory_Player[playerid][itemid][itemName]) != -1){
								return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ไอเท็มนี้ไม่สามารถแลกเปลี่ยนได้", "ตกลง", "");
							}

							if(ServerData[ServerCanTradeSpecial]){
								for (new i = 0; i < sizeof(WeaponData); i ++){
									if (!strcmp(WeaponData[i][weaponName], Inventory_Player[playerid][itemid][itemName], true)){
										return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ไอเท็มนี้ไม่สามารถแลกเปลี่ยนได้ในขณะนี้", "ตกลง", "");
									}
								}

								if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Mixed Drug", true)){
									return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ไอเท็มนี้ไม่สามารถแลกเปลี่ยนได้ในขณะนี้", "ตกลง", "");
								}
							}

							new bool:checkitemistrade = false;
							for(new i=0; i<10; i++){
								if(Trade_Item[playerid][i][itemID] == itemid){
									checkitemistrade = true;
									break;
								}
							}

							if(checkitemistrade) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "ไอเท็มชิ้นนี้คุณได้ใส่ไว้ในการแลกเปลี่ยนแล้ว!", "ตกลง", "");

							if(Inventory_Player[playerid][itemid][itemQuantity] > 1){
								SetPVarInt(playerid, "TempTradeItemID", itemid);
								new string[128];
								format(string, sizeof string, "ไอเท็ม %s (จำนวน: %d)\nกรอกจำนวนไอเท็มที่คุณต้องการจะเพิ่มเข้าการแลกเปลี่ยน:", Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity]);
								Dialog_ShowEasy(playerid, InputCountTradeItem, DIALOG_STYLE_INPUT, "แลกเปลี่ยนไอเท็ม", string, "ตกลง", "ปิด");
							}
							else{
								PlayerTradeItem_AddItem(playerid, Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemKey], 1, Inventory_Player[playerid][itemid][itemAmmo], Inventory_Player[playerid][itemid][itemLevel], itemid);
							}
						}
					}
					else if(PlayerInventoryType[playerid] == HOME_TYPE){
						if(PlayerUsing_HomeInv[playerid]){
							if(PlayerGetIndexSlotItem[playerid] != -1){
								Home_AddItem(playerid, PlayerGetIndexSlotItem[playerid]);
							}
						}
					}
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}

				if(playertextid == InfoButton[playerid]){
					if(PlayerGetIndexSlotItem[playerid] != -1){
						CallLocalFunction("OnPlayerInventory_InfoItem", "dsdd", playerid, Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemName], Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemKey], PlayerGetIndexSlotItem[playerid]);
						PlayerGetIndexSlotItem[playerid] = -1;
						PlayerGetIndexNextSlotItem[playerid] = -1;
						PlayerInvListItemRowsOld[playerid] = -1;
						PlayerInvListItemColumnOld[playerid] = -1;
						RemoveUseInfoButton(playerid);
					}
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
					return 1;
				}
			}

			if(playertextid == PlayerInventoryTextDraw[playerid][4]){
				if(!PlayerEditPositionInventory[playerid]){
					PlayerEditPositionInventory[playerid] = true;
					TogglePlayerControllable(playerid, 0);
					new string[128];
					if(IsAndroidPlayer(playerid)){
						LoadArrowEditInv(playerid);
						for(new i=0; i<4; i++) PlayerTextDrawShow(playerid, ArrowEditInv[playerid][i]);
						format(string, sizeof string, "{FFBE11}[คำแนะนำ]: ใช้ลูกษรที่ขึ้นอยู่ทางซ้ายหน้าจอและด้านล่างเพื่อปรับตำแหน่ง\n{FFBE11}[คำแนะนำ]: ใช้ปุ่ม 'Y' เพื่อบันทึกการปรับ");
						Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ปรับตำแหน่งของกระเป๋า", string, "ตกลง", "");
					}
					else{
						UpdateInventory[playerid] = repeat PlayerUpdateInventory(playerid);
						CancelSelectTextDraw(playerid);
						format(string, sizeof string, "{FFBE11}[คำแนะนำ]: ใช้ปุ่ม 'เดิน' หรือ 'ลูกศร' เพื่อปรับตำแหน่ง\n{FFBE11}[คำแนะนำ]: ใช้ปุ่ม 'Y' เพื่อบันทึกการปรับ");
						Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ปรับตำแหน่งของกระเป๋า", string, "ตกลง", "");
					}
				}
				PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
			}

			if(playertextid == PlayerInventoryTextDraw[playerid][5]){
				if(!PlayerCantSelectTextDraw[playerid]) PlayerCantSelectTextDraw[playerid] = true;
				if(!PlayerEditColorInventory[playerid]){
					new string[256];
					PlayerEditColorInventory[playerid] = true;
					PlayerInventoryColorType[playerid] = 0;
					TogglePlayerControllable(playerid, 0);

					if(IsAndroidPlayer(playerid)){
						LoadArrowEditInv(playerid);
						for(new i=0; i<4; i++) PlayerTextDrawShow(playerid, ArrowEditInv[playerid][i]);
						format(string, sizeof string, "{FFBE11}การปรับค่าสี RGB\n{FFBE11}ใช้ลูกศร ขึ้น เพื่อน + ค่าสี\n{FFBE11}ใช้ลูกศร ลง เพื่อ - ค่าสี\n{FFBE11}ใช้ลูกศร ซ้าย และ ขวา เพื่อเลือกระดับสี R : G : B");
						Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ปรับค่าสีของกระเป๋า", string, "ตกลง", "");
					}
					else{
						UpdateInventory[playerid] = repeat PlayerUpdateInventory(playerid);
						CancelSelectTextDraw(playerid);
						format(string, sizeof string, "{FFBE11}การปรับค่าสี RGB\n{FFBE11}- เดินไปข้างหน้า + ค่าสี\n{FFBE11}- เดินไปข้างหลัง - ค่าสี\n{FFBE11}- เดินไปซ้ายและขวา เพื่อเปลี่ยนระดับสี R : G : B");
						Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ปรับค่าสีของกระเป๋า", string, "ตกลง", "");
					}

					GameTextForPlayer(playerid, "~W~Edit Color ~R~RED", 3000, 6);
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}
			}
		}
	}

	if(PlayerUsing_HomeInv[playerid] && PlayerInventoryType[playerid] == HOME_TYPE){
		if(!PlayerCantSelectTextDraw[playerid]){
			new homeid = GetHomeOwnerIndex[playerid];
			if(homeid != -1){
				if(playertextid == PlayerHomeInvTD[playerid][6]){
					if(PlayerHomeInvPage[playerid] != 1){
						if(HomeData[homeid][homeMaxItem] < 36) return 1;
						PlayerHomeInvPage[playerid] = 1;
						if(PlayerGetIndexHomeSlotItem[playerid] != -1) RemoveHomeButton(playerid);
						OnPlayerHomeInv_Render(playerid);
					}
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}

				if(playertextid == PlayerHomeInvTD[playerid][7]){
					if(PlayerHomeInvPage[playerid] != 2){
						if(HomeData[homeid][homeMaxItem] < 72) return 1;
						PlayerHomeInvPage[playerid] = 2;
						if(PlayerGetIndexHomeSlotItem[playerid] != -1) RemoveHomeButton(playerid);
						OnPlayerHomeInv_Render(playerid);
					}
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}

				if(playertextid == PlayerHomeInvTD[playerid][8]){
					if(PlayerHomeInvPage[playerid] != 3){
						if(HomeData[homeid][homeMaxItem] < 108) return 1;
						PlayerHomeInvPage[playerid] = 3;
						if(PlayerGetIndexHomeSlotItem[playerid] != -1) RemoveHomeButton(playerid);
						OnPlayerHomeInv_Render(playerid);
					}
					PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
				}
			}

			if(PlayerHomeShowButton[playerid]){
				if(playertextid == HomeGetButton[playerid]){
					if(homeid != -1 && PlayerGetIndexHomeSlotItem[playerid] != -1){
						Home_GetItem(playerid, PlayerGetIndexHomeSlotItem[playerid]);
					}
				}
				if(playertextid == HomeInfoButton[playerid]){
					if(homeid != -1 && PlayerGetIndexHomeSlotItem[playerid] != -1){
						if(!PlayerCantSelectTextDraw[playerid]) PlayerCantSelectTextDraw[playerid] = true;
						CallLocalFunction("OnHomeInventory_InfoItem", "ddsdd", playerid, homeid, HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemName], HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemModel], PlayerGetIndexHomeSlotItem[playerid]);
						PlayerGetIndexHomeSlotItem[playerid] = -1;
						PlayerGetIndexNextHomeSlotItem[playerid] = -1;
						PlayerHomeInvListItemRowsOld[playerid] = -1;
						PlayerHomeInvListItemColumnOld[playerid] = -1;
						RemoveHomeButton(playerid);
					}
				}
			}
		}
		PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
	}

	if(PlayerInventoryStatus[playerid] && !PlayerInventoryDropInput[playerid]){
		if(!PlayerCantSelectTextDraw[playerid]){
			new index = 0;

			if(PlayerInventoryPage[playerid] == 1) index = 0;
			else if(PlayerInventoryPage[playerid] == 2) index = 36;
			else if(PlayerInventoryPage[playerid] == 3) index = 72;

			for (new i = 0; i < (MAX_INV_MENU_ROWS); i++){
				for (new j = 0; j < (MAX_INV_MENU_COLUMN); j++){
					if(index < PlayerData[playerid][pMaxItem]){
						if (playertextid == PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]]){
							PlayerInvListItemRows[playerid] = i;
							PlayerInvListItemColumn[playerid] = j;

							if(PlayerGetIndexSlotItem[playerid] == -1){ // เมื่อคลิกไอเท็มครั้งแรก
								if(Inventory_Player[playerid][index][itemKey] != MODEL_NULL) {
									PlayerGetIndexSlotItem[playerid] = index;
									PlayerInvListItemRowsOld[playerid] = i;
									PlayerInvListItemColumnOld[playerid] = j;

									PlayerInventoryLastPage[playerid] = PlayerInventoryPage[playerid];

									if(!PlayerShowButton[playerid]) LoadUseInfoButtonTextDraw(playerid);
								}
							}
							else if(PlayerGetIndexSlotItem[playerid] == index){
								if(Inventory_Player[playerid][index][itemKey] != MODEL_NULL) {
									PlayerGetIndexSlotItem[playerid] = index;
									PlayerInvListItemRowsOld[playerid] = i;
									PlayerInvListItemColumnOld[playerid] = j;

									PlayerInventoryLastPage[playerid] = PlayerInventoryPage[playerid];

									if(!PlayerShowButton[playerid]) LoadUseInfoButtonTextDraw(playerid);
								}
							}
							else{

								if(PlayerTradingItem[playerid]) return 1;

								if(PlayerShowButton[playerid]) RemoveUseInfoButton(playerid);
								PlayerGetIndexNextSlotItem[playerid] = index;

								new string[128];

								//swap
								if(Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemKey] == MODEL_NULL){
									if(!Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemHave]){
										//Next
										Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemHave] = Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemHave];
										Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemID] = Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemID];
										format(Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemName], 64, Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemName]);
										Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemKey] = Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemKey];
										Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemQuantity] = Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemQuantity];
										Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemAmmo] = Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemAmmo];
										Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemLevel] = Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemLevel];
										Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemSlot] = PlayerGetIndexNextSlotItem[playerid];

										printf("Inv: Update Item %s To Slot %d", Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemName], Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemSlot]);
										mysql_format(dbCon, string, sizeof(string), "UPDATE `inventory` SET `itemSlot` = %d WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemSlot], PlayerData[playerid][pID], Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemID]);
										mysql_tquery(dbCon, string);

										//Previues
										Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemHave] = false;
										Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemID] = 0;
										format(Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemName], 64, "NULL");
										Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemKey] = MODEL_NULL;
										Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemQuantity] = 0;
										Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemAmmo] = 0;
										Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemLevel] = 0;
										Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemSlot] = -1;

										//printf("%d", PlayerGetIndexSlotItem[playerid]); //
										///printf("%d", PlayerGetIndexNextSlotItem[playerid]); //

										OnPlayerInventory_Update(playerid);

										PlayerGetIndexSlotItem[playerid] = -1;
										PlayerGetIndexNextSlotItem[playerid] = -1;
										PlayerInvListItemRowsOld[playerid] = -1;
										PlayerInvListItemColumnOld[playerid] = -1;
									}
								}
								else{

									if(PlayerTradingItem[playerid]) return 1;

									//ไอเท็มซ้ำกันจะรวมกัน
									if(CheckItemIsWeapon(Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemName]) == -1){
										if(PlayerInventory_CountEx(playerid, PlayerGetIndexNextSlotItem[playerid]) + Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemQuantity] <= PlayerData[playerid][pItemAmount]){
											if(Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemKey] == Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemKey] && !strcmp(Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemName], Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemName], true)){
												//Next
												//Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemID] = Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemID];
												//Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemKey] = Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemKey];
												Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemQuantity] += Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemQuantity];
												Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemSlot] = PlayerGetIndexNextSlotItem[playerid];


												printf("Inv: Update Item %s To Slot %d", Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemName], Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemSlot]);
												mysql_format(dbCon, string, sizeof(string), "UPDATE `inventory` SET `itemQuantity` = %d WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemQuantity], PlayerData[playerid][pID], Inventory_Player[playerid][PlayerGetIndexNextSlotItem[playerid]][itemID]);
												mysql_tquery(dbCon, string);

												printf("Inv: Remove Item From Slot");
												mysql_format(dbCon, string, sizeof(string), "DELETE FROM `inventory` WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", PlayerData[playerid][pID], Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemID]);
												mysql_tquery(dbCon, string);

												//Previues
												Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemHave] = false;
												Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemID] = 0;
												Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemKey] = MODEL_NULL;
												Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemQuantity] = 0;
												Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemAmmo] = 0;
												Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemLevel] = 0;
												Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemSlot] = -1;
												format(Inventory_Player[playerid][PlayerGetIndexSlotItem[playerid]][itemName], 64, "NULL");

												//printf("%d", PlayerGetIndexSlotItem[playerid]); //
												//printf("%d", PlayerGetIndexNextSlotItem[playerid]); //
												OnPlayerInventory_Update(playerid);
											}
										}
									}
									else Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] อาวุธไม่สามารถรวมกันได้", "ตกลง", "");


									PlayerGetIndexSlotItem[playerid] = -1;
									PlayerGetIndexNextSlotItem[playerid] = -1;
									PlayerInvListItemRowsOld[playerid] = -1;
									PlayerInvListItemColumnOld[playerid] = -1;

									if(Inventory_Player[playerid][index][itemKey] != MODEL_NULL) {
										PlayerGetIndexSlotItem[playerid] = index;
										PlayerInvListItemRowsOld[playerid] = i;
										PlayerInvListItemColumnOld[playerid] = j;

										PlayerInventoryLastPage[playerid] = PlayerInventoryPage[playerid];

										if(!PlayerShowButton[playerid]) LoadUseInfoButtonTextDraw(playerid);
									}
								}
							}

							if(PlayerHomeShowButton[playerid]){
								RemoveHomeButton(playerid);
							}

							PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
							return 1;
						}
					}
					index++;
				}
			}

			if(PlayerVicinity[playerid] && !PlayerTradingItem[playerid]){
				new indexvicinity = 0;
				for (new i = 0; i < (MAX_VICINITY_ROWS); i++){
					for (new j = 0; j < (MAX_VICINITY_COLUMN); j++){
						if(indexvicinity < 10){
							if (playertextid == PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityModel[playerid][i][j]]){
								printf("NearItem: [%d]", PlayerNearestItems[playerid][indexvicinity]);
								if(PlayerNearestItems[playerid][indexvicinity] != -1){
									Player_PickupItem(playerid, PlayerNearestItems[playerid][indexvicinity]);
								}
							}
							indexvicinity++;
						}
					}
				}
				PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
			}
		}
	}

	if(PlayerUsing_HomeInv[playerid] && !PlayerInventoryDropInput[playerid]){
		if(!PlayerCantSelectTextDraw[playerid]){
			new homeid = GetHomeOwnerIndex[playerid];
			if(homeid != -1){
				new index = 0;

				if(PlayerHomeInvPage[playerid] == 1) index = 0;
				else if(PlayerHomeInvPage[playerid] == 2) index = 36;
				else if(PlayerHomeInvPage[playerid] == 3) index = 72;

				for (new i; i < (MAX_HOME_MENU_ROWS); i++){
					for (new j; j < (MAX_HOME_MENU_COLUMN); j++){
						if(index < HomeData[homeid][homeMaxItem]){
							if (playertextid == PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]]){
								PlayerHomeInvListItemRows[playerid] = i;
								PlayerHomeInvListItemColumn[playerid] = j;

								if(PlayerGetIndexHomeSlotItem[playerid] == -1){ // เมื่อคลิกไอเท็มครั้งแรก
									if(HouseStorage[homeid][index][hItemModel] != MODEL_NULL) {
										PlayerGetIndexHomeSlotItem[playerid] = index;
										PlayerHomeInvListItemRowsOld[playerid] = i;
										PlayerHomeInvListItemColumnOld[playerid] = j;

										PlayerHomeInvLastPage[playerid] = PlayerHomeInvPage[playerid];

										LoadHomeButtonTextDraw(playerid);
									}
								}
								else if(PlayerGetIndexHomeSlotItem[playerid] == index){
									if(HouseStorage[homeid][index][hItemModel] != MODEL_NULL) {
										PlayerGetIndexHomeSlotItem[playerid] = index;
										PlayerHomeInvListItemRowsOld[playerid] = i;
										PlayerHomeInvListItemColumnOld[playerid] = j;

										PlayerHomeInvLastPage[playerid] = PlayerHomeInvPage[playerid];

										if(!PlayerHomeShowButton[playerid]) LoadHomeButtonTextDraw(playerid);
									}
								}
								else{

									if(PlayerTradingItem[playerid]) return 1;

									RemoveHomeButton(playerid);
									PlayerGetIndexNextHomeSlotItem[playerid] = index;

									new string[128];

									//swap
									if(HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemModel] == MODEL_NULL){
										if(!HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemExists]){
											//Next
											HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemExists] = HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemExists];
											HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemID] = HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemID];
											format(HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemName], 64, HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemName]);
											HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemModel] = HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemModel];
											HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemQuantity] = HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemQuantity];
											HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemAmmo] = HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemAmmo];
											HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemLevel] = HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemLevel];
											HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemSlot] = PlayerGetIndexNextHomeSlotItem[playerid];

											printf("Home: Update Item %s to Slot %d", HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemName], HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemSlot]);
											mysql_format(dbCon, string, sizeof(string), "UPDATE `homestorage` SET `itemSlot` = %d WHERE `ID` = '%d' AND `itemID` = '%d' LIMIT 1", HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemSlot], HomeData[homeid][homeID], HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemID]);
											mysql_tquery(dbCon, string);

											//Previues
											HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemExists] = false;
											HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemID] = 0;
											format(HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemName], 64, "NULL");
											HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemModel] = MODEL_NULL;
											HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemQuantity] = 0;
											HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemAmmo] = 0;
											HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemLevel] = 0;
											HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemSlot] = -1;

											//printf("%d", PlayerGetIndexHomeSlotItem[playerid]); //
											//printf("%d", PlayerGetIndexNextHomeSlotItem[playerid]); //

											OnHomeInventory_Update(playerid, homeid);

											PlayerGetIndexHomeSlotItem[playerid] = -1;
											PlayerGetIndexNextHomeSlotItem[playerid] = -1;
											PlayerHomeInvListItemRowsOld[playerid] = -1;
											PlayerHomeInvListItemColumnOld[playerid] = -1;
										}
									}
									else{

										if(PlayerTradingItem[playerid]) return 1;

										//ไอเท็มซ้ำกันจะรวมกัน
										if(CheckItemIsWeapon(HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemName]) == -1){
											if(HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemModel] == HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemModel] && !strcmp(HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemName], HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemName], true)){
												if(HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemQuantity] + HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemQuantity] <= HomeData[homeid][homeItemAmount]){
													//Next
													//HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemID] = HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemID];
													//HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemModel] = HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemModel];
													HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemQuantity] += HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemQuantity];
													HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemSlot] = PlayerGetIndexNextHomeSlotItem[playerid];

													printf("Home: Update Item %s to Slot %d", HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemName], HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemSlot]);
													mysql_format(dbCon, string, sizeof(string), "UPDATE `homestorage` SET `itemQuantity` = %d WHERE `ID` = '%d' AND `itemID` = '%d' LIMIT 1", HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemQuantity], HomeData[homeid][homeID], HouseStorage[homeid][PlayerGetIndexNextHomeSlotItem[playerid]][hItemID]);
													mysql_tquery(dbCon, string);

													printf("Home: Remove Item From Slot");
													mysql_format(dbCon, string, sizeof(string), "DELETE FROM `homestorage` WHERE `ID` = '%d' AND `itemID` = '%d' LIMIT 1", HomeData[homeid][homeID], HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemID]);
													mysql_tquery(dbCon, string);

													//Previues
													HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemExists] = false;
													HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemID] = 0;
													HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemModel] = MODEL_NULL;
													HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemQuantity] = 0;
													HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemAmmo] = 0;
													HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemLevel] = 0;
													HouseStorage[homeid][PlayerGetIndexHomeSlotItem[playerid]][hItemSlot] = -1;

													//printf("%d", PlayerGetIndexHomeSlotItem[playerid]); //
													//printf("%d", PlayerGetIndexNextHomeSlotItem[playerid]); //

													OnHomeInventory_Update(playerid, homeid);
												}
											}
										}

										PlayerGetIndexHomeSlotItem[playerid] = -1;
										PlayerGetIndexNextHomeSlotItem[playerid] = -1;
										PlayerHomeInvListItemRowsOld[playerid] = -1;
										PlayerHomeInvListItemColumnOld[playerid] = -1;

										if(HouseStorage[homeid][index][hItemModel] != MODEL_NULL) {
											PlayerGetIndexHomeSlotItem[playerid] = index;
											PlayerHomeInvListItemRowsOld[playerid] = i;
											PlayerHomeInvListItemColumnOld[playerid] = j;

											PlayerHomeInvLastPage[playerid] = PlayerHomeInvPage[playerid];

											if(!PlayerHomeShowButton[playerid]) LoadHomeButtonTextDraw(playerid);
										}
									}
								}

								if(PlayerShowButton[playerid]) RemoveUseInfoButton(playerid);

								PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
								return 1;
							}
						}
						index++;
					}
				}
			}
		}
	}

	if(PlayerTradingItem[playerid] && !PlayerSelectingItem[playerid]){
		//คลิกช่องเพื่อเลือกเมนูจัดการไอเท็ม
		new tradeid = GetPVarInt(playerid, "TradeID");
		if(tradeid != INVALID_PLAYER_ID && LoggedIn[tradeid]){

			if(PlayerStateRoleTrade[playerid] == 1){
				if(playertextid == PlayerTDTradeItem[playerid][3]){
					if(Trade_Item[playerid][0][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 0);
				}

				if(playertextid == PlayerTDTradeItem[playerid][6]){
					if(Trade_Item[playerid][1][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 1);
				}

				if(playertextid == PlayerTDTradeItem[playerid][9]){
					if(Trade_Item[playerid][2][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 2);
				}

				if(playertextid == PlayerTDTradeItem[playerid][12]){
					if(Trade_Item[playerid][3][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 3);
				}

				if(playertextid == PlayerTDTradeItem[playerid][15]){
					if(Trade_Item[playerid][4][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 4);
				}

				if(playertextid == PlayerTDTradeItem[playerid][18]){
					if(Trade_Item[playerid][5][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 5);
				}

				if(playertextid == PlayerTDTradeItem[playerid][21]){
					if(Trade_Item[playerid][6][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 6);
				}

				if(playertextid == PlayerTDTradeItem[playerid][24]){
					if(Trade_Item[playerid][7][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 7);
				}

				if(playertextid == PlayerTDTradeItem[playerid][27]){
					if(Trade_Item[playerid][8][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 8);
				}

				if(playertextid == PlayerTDTradeItem[playerid][30]){
					if(Trade_Item[playerid][9][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 9);
				}

				//ตรงข้าม
				if(playertextid == PlayerTDTradeItem[playerid][35]){
					if(Trade_Item[tradeid][0][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 0);
				}

				if(playertextid == PlayerTDTradeItem[playerid][38]){
					if(Trade_Item[tradeid][1][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 1);
				}

				if(playertextid == PlayerTDTradeItem[playerid][41]){
					if(Trade_Item[tradeid][2][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 2);
				}

				if(playertextid == PlayerTDTradeItem[playerid][44]){
					if(Trade_Item[tradeid][3][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 3);
				}

				if(playertextid == PlayerTDTradeItem[playerid][47]){
					if(Trade_Item[tradeid][4][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 4);
				}

				if(playertextid == PlayerTDTradeItem[playerid][50]){
					if(Trade_Item[tradeid][5][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 5);
				}

				if(playertextid == PlayerTDTradeItem[playerid][53]){
					if(Trade_Item[tradeid][6][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 6);
				}

				if(playertextid == PlayerTDTradeItem[playerid][56]){
					if(Trade_Item[tradeid][7][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 7);
				}

				if(playertextid == PlayerTDTradeItem[playerid][59]){
					if(Trade_Item[tradeid][8][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 8);
				}

				if(playertextid == PlayerTDTradeItem[playerid][62]){
					if(Trade_Item[tradeid][9][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 9);
				}
			}

			if(PlayerStateRoleTrade[playerid] == 2){
				if(playertextid == PlayerTDTradeItem[playerid][35]){
					if(Trade_Item[playerid][0][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 0);
				}

				if(playertextid == PlayerTDTradeItem[playerid][38]){
					if(Trade_Item[playerid][1][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 1);
				}

				if(playertextid == PlayerTDTradeItem[playerid][41]){
					if(Trade_Item[playerid][2][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 2);
				}

				if(playertextid == PlayerTDTradeItem[playerid][44]){
					if(Trade_Item[playerid][3][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 3);
				}

				if(playertextid == PlayerTDTradeItem[playerid][47]){
					if(Trade_Item[playerid][4][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 4);
				}

				if(playertextid == PlayerTDTradeItem[playerid][50]){
					if(Trade_Item[playerid][5][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 5);
				}

				if(playertextid == PlayerTDTradeItem[playerid][53]){
					if(Trade_Item[playerid][6][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 6);
				}

				if(playertextid == PlayerTDTradeItem[playerid][56]){
					if(Trade_Item[playerid][7][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 7);
				}

				if(playertextid == PlayerTDTradeItem[playerid][59]){
					if(Trade_Item[playerid][8][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 8);
				}

				if(playertextid == PlayerTDTradeItem[playerid][62]){
					if(Trade_Item[playerid][9][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_MenuManageItem(playerid, 9);
				}

				//ตรงข้าม
				if(playertextid == PlayerTDTradeItem[playerid][3]){
					if(Trade_Item[tradeid][0][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 0);
				}

				if(playertextid == PlayerTDTradeItem[playerid][6]){
					if(Trade_Item[tradeid][1][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 1);
				}

				if(playertextid == PlayerTDTradeItem[playerid][9]){
					if(Trade_Item[tradeid][2][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 2);
				}

				if(playertextid == PlayerTDTradeItem[playerid][12]){
					if(Trade_Item[tradeid][3][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 3);
				}

				if(playertextid == PlayerTDTradeItem[playerid][15]){
					if(Trade_Item[tradeid][4][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 4);
				}

				if(playertextid == PlayerTDTradeItem[playerid][18]){
					if(Trade_Item[tradeid][5][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 5);
				}

				if(playertextid == PlayerTDTradeItem[playerid][21]){
					if(Trade_Item[tradeid][6][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 6);
				}

				if(playertextid == PlayerTDTradeItem[playerid][24]){
					if(Trade_Item[tradeid][7][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 7);
				}

				if(playertextid == PlayerTDTradeItem[playerid][27]){
					if(Trade_Item[tradeid][8][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 8);
				}

				if(playertextid == PlayerTDTradeItem[playerid][30]){
					if(Trade_Item[tradeid][9][itemModel] == MODEL_NULL) return 1;
					PlayerTradeItem_ViewItem(playerid, 9);
				}
			}
		}

		//-------------------------------------//

		if(playertextid == PlayerTDTradeItem[playerid][69]){
			if(tradeid != INVALID_PLAYER_ID && LoggedIn[tradeid]){
				DeletePVar(tradeid, "TradeID");
				PlayerTradeItem_Hide(tradeid);
				DeletePVar(playerid, "TradeID");
				PlayerTradeItem_Hide(playerid);
			}
		}

		if(playertextid == PlayerTDTradeItem[playerid][66]){
			if(!PlayerStateTrading[playerid]) PlayerStateTrading[playerid] = true;
			else PlayerStateTrading[playerid] = false;
			PlayerTradeItem_UpdateState(playerid);
		}

		if(playertextid == PlayerTDTradeItem[playerid][68]){
			PlayerTradeItem_ShowInfoTrader(playerid);
		}

		if(playertextid == PlayerTDTradeItem[playerid][72]){
			if(PlayerStateTrading[playerid]) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] คุณจำเป็นต้อง 'UNLOCK' ก่อนที่จะแก้ไขหรือเพิ่มไอเท็ม", "ตกลง", "");

			PlayerSelectingItem[playerid] = true;
			PlayerInventoryType[playerid] = TRADE_TYPE;
			if(!PlayerInventoryStatus[playerid]) {
				OnPlayerInventory_Open(playerid);
				if(PlayerCharacterShow[playerid]){
					for(new i=0; i<MAX_CHARTEXT; i++){
						PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][i]);
						PlayerTextDrawDestroy(playerid, PlayerCharacterTextDraw[playerid][i]);
					}
					PlayerCharacterShow[playerid] = false;
				}
			}
		}

		if(playertextid == PlayerTDTradeItem[playerid][67]){
			if(!PlayerConfirmTrade[playerid]){
				if(tradeid != INVALID_PLAYER_ID && LoggedIn[tradeid]){
					if(!PlayerStateTrading[playerid]) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] คุณจำเป็นต้องกด Lock ก่อนที่จะกด Confirm ได้", "เข้าใจแล้ว", "");
					if(!PlayerStateTrading[tradeid]) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ฝ่ายตรงข้ามคุณยังไม่ได้ทำการกด Lock", "เข้าใจแล้ว", "");
					PlayerConfirmTradeItem(playerid);
				}
			}
		}

		if(playertextid == PlayerTDTradeItem[playerid][73]){
			if(PlayerData[playerid][pPlayerhour] < 5) return ErrorMsg(playerid, "คุณต้องออนไลน์อย่างน้อย 5 ชั่วโมง");
			Dialog_ShowEasy(playerid, AddMoneyTrade, DIALOG_STYLE_INPUT, "การแลกเปลี่ยนเงิน", "ใส่จำนวนเงินที่คุณต้องการจะแลกเปลี่ยน:", "ตกลง", "ยกเลิก");
		}
	}
	if(PlayerEnterRacing[playerid]){
		if(playertextid == RacingPlayerTextDraw[playerid][13]){
			if(!PlayerRacingStartTimeCount[playerid]){
				new string[128];
				if(PlayerRacingTypeInRoom[playerid] == OWNER_ROOM){
					if(!PlayerRacingReady[playerid]) {
						format(string, sizeof string, "READY");
						PlayerRacingReady[playerid] = true;
					}
					else {
						format(string, sizeof string, "NOT READY");
						PlayerRacingReady[playerid] = false;
					}
					PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][6], string);
					if(PlayerGetDuel[playerid] != INVALID_PLAYER_ID) PlayerTextDrawSetString(PlayerGetDuel[playerid], RacingPlayerTextDraw[PlayerGetDuel[playerid]][6], string);
				}
				else if(PlayerRacingTypeInRoom[playerid] == PLAYER_ROOM){
					if(!PlayerRacingReady[playerid]) {
						format(string, sizeof string, "READY");
						PlayerRacingReady[playerid] = true;
					}
					else {
						format(string, sizeof string, "NOT READY");
						PlayerRacingReady[playerid] = false;
					}
					PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][10], string);
					if(PlayerGetDuel[playerid] != INVALID_PLAYER_ID) PlayerTextDrawSetString(PlayerGetDuel[playerid], RacingPlayerTextDraw[PlayerGetDuel[playerid]][10], string);
				}
			}
		}

		if(playertextid == RacingPlayerTextDraw[playerid][14]){
			if(!PlayerRacingStartTimeCount[playerid]) PlayerRacing_Hide(playerid);
		}

		if(playertextid == RacingPlayerTextDraw[playerid][11]){
			if(PlayerRacingTypeInRoom[playerid] == OWNER_ROOM && !PlayerRacingStartTimeCount[playerid]){
				PlayerRacing_UpdateModelCar(playerid);
			}
		}
	}

	if(PlayerOpenPizzaMenu[playerid]){
		new string[128];
		if(playertextid == PizzaTextDraw[playerid][2]){ //Tomato
			if(TomatoAmount[playerid] < TomatoMax[playerid]){

				if(PlayerInventory_AllCount(playerid, "Tomato")-TomatoAmount[playerid] < 1) return ErrorMsg(playerid, "คุณมีมะเขือเทศไม่เพียงพอ");

				TomatoAmount[playerid]++;

				format(string, sizeof(string), "Tomato %d Ea", PlayerInventory_AllCount(playerid, "Tomato")-TomatoAmount[playerid]);
    			PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][3], string);

				if(TomatoAmount[playerid] == 1){
					PlayerTextDrawShow(playerid, PizzaTextDraw[playerid][16]);
				}
				else if(TomatoAmount[playerid] == 2){
					PlayerTextDrawShow(playerid, PizzaTextDraw[playerid][17]);
				}
				else if(TomatoAmount[playerid] == 3){
					PlayerTextDrawShow(playerid, PizzaTextDraw[playerid][18]);
				}
				format(string, sizeof(string), "x%d Tomato", TomatoMax[playerid]-TomatoAmount[playerid]);
    			PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][13], string);

				if(TomatoAmount[playerid] == TomatoMax[playerid]){
					format(string, sizeof(string), "Tomato FULL");
    				PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][13], string);
				}
			}
		}

		if(playertextid == PizzaTextDraw[playerid][4]){ //CowMeat
			if(CowmeatAmount[playerid] < CowmeatMax[playerid]){
				if(PlayerInventory_AllCount(playerid, "Raw Cow Meat")-CowmeatAmount[playerid] < 1) return ErrorMsg(playerid, "คุณมีเนื้อวัวไม่พอ");
				CowmeatAmount[playerid]++;
				format(string, sizeof(string), "CowMeat %d Ea", PlayerInventory_AllCount(playerid, "Raw Cow Meat")-CowmeatAmount[playerid]);
    			PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][5], string);

				if(CowmeatAmount[playerid] == 1){
					PlayerTextDrawShow(playerid, PizzaTextDraw[playerid][19]);
				}
				else if(CowmeatAmount[playerid] == 2){
					PlayerTextDrawShow(playerid, PizzaTextDraw[playerid][20]);
				}
				format(string, sizeof(string), "x%d CowMeat", CowmeatMax[playerid]-CowmeatAmount[playerid]);
    			PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][12], string);
				if(CowmeatAmount[playerid] == CowmeatMax[playerid]){
					format(string, sizeof(string), "CowMeat FULL");
    				PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][12], string);
				}
			}
		}

		if(playertextid == PizzaTextDraw[playerid][6]){ //Tomato Saice
			if(TomatoSaiceAmount[playerid] < TomatoSaiceMax[playerid]){
				TomatoSaiceAmount[playerid]++;
				format(string, sizeof(string), "x%d Tomato Saice", TomatoSaiceMax[playerid]-TomatoSaiceAmount[playerid]);
    			PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][14], string);
				if(TomatoSaiceAmount[playerid] == TomatoSaiceMax[playerid]){
					format(string, sizeof(string), "Tomato Saice FULL");
    				PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][14], string);
				}
			}
		}

		if(playertextid == PizzaTextDraw[playerid][8]){ //Mayonnaise Saice
			if(MayonnaiseSaiceAmount[playerid] < MayonnaiseSaiceMax[playerid]){
				MayonnaiseSaiceAmount[playerid]++;
				format(string, sizeof(string), "x%d Mayonnaise Saice", MayonnaiseSaiceMax[playerid]-MayonnaiseSaiceAmount[playerid]);
    			PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][15], string);
				if(MayonnaiseSaiceAmount[playerid] == MayonnaiseSaiceMax[playerid]){
					format(string, sizeof(string), "Mayonnaise Saice FULL");
    				PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][15], string);
				}
			}
		}

		if(playertextid == PizzaTextDraw[playerid][21]){
			PlayerStartBakedPizza(playerid);
		}
	}

	if(PlayerEditingObject[playerid] == 1){
		new string[128];
		if(playertextid == MoveObjectTextDraw[playerid][0]){
			format(string, sizeof(string), "UP AND DOWN");
			PlayerTextDrawSetString(playerid, MoveObjectTextDraw[playerid][12], string);
			PlayerTextDrawHide(playerid, MoveObjectTextDraw[playerid][12]);
			PlayerTextDrawShow(playerid, MoveObjectTextDraw[playerid][12]);
			PlayerEditObjectType[playerid] = 1;
			SendClientMessage(playerid, COLOR_YELLOW, "คุณได้เลือกใช้งานเป็นการ 'เคลื่อนย้ายทิศทาง' แล้ว");
		}

		if(playertextid == MoveObjectTextDraw[playerid][1]){
			format(string, sizeof(string), "SIDEWAYS");
			PlayerTextDrawSetString(playerid, MoveObjectTextDraw[playerid][12], string);
			PlayerTextDrawHide(playerid, MoveObjectTextDraw[playerid][12]);
			PlayerTextDrawShow(playerid, MoveObjectTextDraw[playerid][12]);
			PlayerEditObjectType[playerid] = 2;
			SendClientMessage(playerid, COLOR_YELLOW, "คุณได้เลือกใช้งานเป็นการ 'หมุนองศา' แล้ว");
		}

		if(playertextid == MoveObjectTextDraw[playerid][2]){
			HideEditingObject(playerid);
			SendClientMessage(playerid, COLOR_YELLOW, "คุณได้เซฟการแต่งกายเรียบร้อยแล้ว");
		}

		//Size X
		if(playertextid == MoveObjectTextDraw[playerid][14]){
			if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
				AccessoryData[playerid][0][6] += 0.01;
				RemoveAttachedObject(playerid, 0);
				SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
				AccessoryData[playerid][1][6] += 0.01;
				RemoveAttachedObject(playerid, 1);
				SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
				AccessoryData[playerid][2][6] += 0.01;
				RemoveAttachedObject(playerid, 2);
				SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 3){ //มือ
				AccessoryData[playerid][3][6] -= 0.01;
				RemoveAttachedObject(playerid, 3);
				SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
				Streamer_Update(playerid);
			}
		}

		if(playertextid == MoveObjectTextDraw[playerid][15]){
			if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
				AccessoryData[playerid][0][6] -= 0.01;
				RemoveAttachedObject(playerid, 0);
				SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
				AccessoryData[playerid][1][6] -= 0.01;
				RemoveAttachedObject(playerid, 1);
				SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
				AccessoryData[playerid][2][6] -= 0.01;
				RemoveAttachedObject(playerid, 2);
				SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 3){ //มือ
				AccessoryData[playerid][3][6] += 0.01;
				RemoveAttachedObject(playerid, 3);
				SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
				Streamer_Update(playerid);
			}
		}

		//Size Y
		if(playertextid == MoveObjectTextDraw[playerid][16]){
			if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
				AccessoryData[playerid][0][7] += 0.01;
				RemoveAttachedObject(playerid, 0);
				SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
				AccessoryData[playerid][1][7] += 0.01;
				RemoveAttachedObject(playerid, 1);
				SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
				AccessoryData[playerid][2][7] += 0.01;
				RemoveAttachedObject(playerid, 2);
				SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 3){ //มือ
				AccessoryData[playerid][3][7] -= 0.01;
				RemoveAttachedObject(playerid, 3);
				SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
				Streamer_Update(playerid);
			}
		}

		if(playertextid == MoveObjectTextDraw[playerid][17]){
			if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
				AccessoryData[playerid][0][7] -= 0.01;
				RemoveAttachedObject(playerid, 0);
				SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
				AccessoryData[playerid][1][7] -= 0.01;
				RemoveAttachedObject(playerid, 1);
				SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
				AccessoryData[playerid][2][7] -= 0.01;
				RemoveAttachedObject(playerid, 2);
				SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 3){ //มือ
				AccessoryData[playerid][3][7] += 0.01;
				RemoveAttachedObject(playerid, 3);
				SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
				Streamer_Update(playerid);
			}
		}

		//Size Z
		if(playertextid == MoveObjectTextDraw[playerid][18]){
			if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
				AccessoryData[playerid][0][8] += 0.01;
				RemoveAttachedObject(playerid, 0);
				SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
				AccessoryData[playerid][1][8] += 0.01;
				RemoveAttachedObject(playerid, 1);
				SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
				AccessoryData[playerid][2][8] += 0.01;
				RemoveAttachedObject(playerid, 2);
				SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 3){ //มือ
				AccessoryData[playerid][3][8] -= 0.01;
				RemoveAttachedObject(playerid, 3);
				SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
				Streamer_Update(playerid);
			}
		}

		if(playertextid == MoveObjectTextDraw[playerid][19]){
			if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
				AccessoryData[playerid][0][8] -= 0.01;
				RemoveAttachedObject(playerid, 0);
				SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
				AccessoryData[playerid][1][8] -= 0.01;
				RemoveAttachedObject(playerid, 1);
				SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
				AccessoryData[playerid][2][8] -= 0.01;
				RemoveAttachedObject(playerid, 2);
				SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
				Streamer_Update(playerid);
			}
			if(PlayerEditObjectSlot[playerid] == 3){ //มือ
				AccessoryData[playerid][3][8] += 0.01;
				RemoveAttachedObject(playerid, 3);
				SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
				Streamer_Update(playerid);
			}
		}

		if(PlayerEditObjectType[playerid] == 1){
			if(playertextid == MoveObjectTextDraw[playerid][10]){ //ขึ้น
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][0] += 0.01;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][0] += 0.01;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][0] += 0.01;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][0] -= 0.01;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}
			}
			if(playertextid == MoveObjectTextDraw[playerid][11]){ //ลง
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][0] -= 0.01;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][0] -= 0.01;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][0] -= 0.01;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][0] += 0.01;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}
			}
			if(playertextid == MoveObjectTextDraw[playerid][4]){ //ไปข้างหน้า
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][1] += 0.01;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][1] += 0.01;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][1] += 0.01;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][2] += 0.01;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}
			}
			if(playertextid == MoveObjectTextDraw[playerid][5]){ //ไปข้างหลัง
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][1] -= 0.01;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][1] -= 0.01;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][1] -= 0.01;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][2] -= 0.01;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}
			}
			if(playertextid == MoveObjectTextDraw[playerid][7]){ //ไปขวา
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][2] -= 0.01;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][2] -= 0.01;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][2] -= 0.01;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][1] -= 0.01;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}

			}
			if(playertextid == MoveObjectTextDraw[playerid][6]){ //ไปซ้าย
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][2] += 0.01;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][2] += 0.01;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][2] += 0.01;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][1] += 0.01;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}

			}
		}
		else if(PlayerEditObjectType[playerid] == 2){
			if(playertextid == MoveObjectTextDraw[playerid][6]){ // หมุนซ้าย
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][3] += 1.0;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][3] += 1.0;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][3] += 1.0;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][3] -= 1.0;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}
			}
			if(playertextid == MoveObjectTextDraw[playerid][7]){ // หมุนขวา
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][3] -= 1.0;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][3] -= 1.0;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][3] -= 1.0;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][3] += 1.0;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}

			}
			if(playertextid == MoveObjectTextDraw[playerid][10]){ // เอียงซ้าย
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][4] += 1.0;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][4] += 1.0;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][4] += 1.0;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][4] -= 1.0;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}
			}
			if(playertextid == MoveObjectTextDraw[playerid][11]){ // เอียงขวา
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][4] -= 1.0;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][4] -= 1.0;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][4] -= 1.0;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][4] += 1.0;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}

			}
			if(playertextid == MoveObjectTextDraw[playerid][4]){ // หมุนหน้า
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][5] += 1.0;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][5] += 1.0;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][5] += 1.0;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][5] -= 1.0;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}
			}
			if(playertextid == MoveObjectTextDraw[playerid][5]){ // หมุนหลัง
				if(PlayerEditObjectSlot[playerid] == 0){ //หมวก
					AccessoryData[playerid][0][5] -= 1.0;
					RemoveAttachedObject(playerid, 0);
					SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 1){ //แว่น
					AccessoryData[playerid][1][5] -= 1.0;
					RemoveAttachedObject(playerid, 1);
					SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 2){ //ลำตัว
					AccessoryData[playerid][2][5] -= 1.0;
					RemoveAttachedObject(playerid, 2);
					SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					Streamer_Update(playerid);
				}
				if(PlayerEditObjectSlot[playerid] == 3){ //มือ
					AccessoryData[playerid][3][5] += 1.0;
					RemoveAttachedObject(playerid, 3);
					SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
					Streamer_Update(playerid);
				}

			}
		}
	}

	if(OnPlayerShowMarryCard[playerid] == 1){
		if(playertextid == MarryText[playerid][2]){
			for(new i=0; i<TEXTMARRY; i++){
                PlayerTextDrawHide(playerid, MarryText[playerid][i]);
				PlayerTextDrawDestroy(playerid, MarryText[playerid][i]);
            }

			HidePlayerProgressBar(playerid, MarryBar[playerid][0]);
			DestroyPlayerProgressBar(playerid, MarryBar[playerid][0]);

			CancelSelectTextDraw(playerid);
			OnPlayerShowMarryCard[playerid] = 0;
		}
	}

	if(IsOpeningGaCha[playerid] && StartRandom[playerid] != 1){
		if(!LoggedIn[playerid]) return 0;
		if(playertextid == GaCha[playerid][11]){
			HideGaChaBox(playerid);
		}

		if(playertextid == GaCha[playerid][10]){
			CheckConfirmRandomBox(playerid);
		}
	}

	if(PlayerOpenCraftWeaponMenu[playerid] == 1){
		if(!LoggedIn[playerid]) return 0;
		if (playertextid == CraftTypeTextDraw[playerid][CraftTypeTextDrawID[playerid][E_CRAFT_TEXTDRAW_CLOSE]]){
			HidePlayerCraftWeaponMenu(playerid);
		}

		for (new i; i < MAX_CRAFT_MENU_ROWS; i++){
			if (playertextid == CraftTypeTextDraw[playerid][CraftTypeTextDrawID[playerid][E_CRAFT_MODEL][i]])
			{
				HidePlayerCraftWeaponMenu(playerid);
				PlayerGetIndexWeaponCraft[playerid] = i;
				//SendClientMessageEx(playerid, -1, "WeaponName: %s | Weapon Model: %d | WeaponLevel: %d", WeaponCraftData[PlayerGetIndexWeaponCraft[playerid]][weaponcraftName], WeaponCraftData[PlayerGetIndexWeaponCraft[playerid]][weaponcraftModel], WeaponCraftData[PlayerGetIndexWeaponCraft[playerid]][weaponcraftLevelSkills]);
				SetTimerEx("ShowWeaponCraftInfo", 200, false, "i", playerid);
				return 1;
			}
		}
	}

	if(PlayerOpenCraftWeaponInfoMenu[playerid] == 1){
		if(!LoggedIn[playerid]) return 0;
		if(playertextid == CraftWeaponInfo[playerid][5]){
			HideWeaponCraftInfo(playerid);

			DestroyPlayerProgressbar_Job(playerid);
		}

		if(playertextid == CraftWeaponInfo[playerid][2]){

			if(StartingCraftWeapon[playerid] == 1)
            	return ErrorMsg(playerid, "คุณกำลังคราฟอาวุธอยู่");

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณจะต้องไม่อยู่บนยานพาหนะ");

			SetTimerEx("SetPlayerStartCraftWeapon", 100, false, "i", playerid);
		}
	}

	if(IsShowCard[playerid] == 1){
		if(!LoggedIn[playerid]) return 0;
		if(playertextid == IDCARDTEXTDRAW[playerid][8]){
			HideIdCardForPlayer(playerid);
		}
		if(playertextid == ShowBadgeTextDraw[playerid][8]){
			HideBadgeForPlayer(playerid);
		}
	}

	if(PlayerUsingPhone[playerid] == 1){
		if(!LoggedIn[playerid]) return 0;
		if(playertextid == PlayerPhoneTD[playerid][4]){
			HideMobilePhone(playerid);
		}

		if(playertextid == PlayerPhoneTD[playerid][3]){
			ShowCallPhone(playerid);
		}

		if(playertextid == PlayerPhoneTD[playerid][19]){
			HideMobilePhone(playerid);
			callcmd::answer(playerid, "\1");
		}

		if(playertextid == PlayerPhoneTD[playerid][20]){
			HideMobilePhone(playerid);
			callcmd::hangup(playerid, "\1");
		}

		if(playertextid == PlayerPhoneTD[playerid][6]){
			HideMobilePhone(playerid);
			ShowContacts(playerid);
		}

		if(playertextid == PlayerPhoneTD[playerid][14]){
			SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: ให้ใช้ /sms [เบอร์โทรศัพท์ที่ต้องการส่ง] [ข้อความ]");
			//ShowPlayerSms(playerid);
		}

		if(playertextid == PlayerPhoneTD[playerid][24]){
			SetPlayerEnterCamera(playerid);
		}

		if(playertextid == PlayerPhoneTD[playerid][27]){
			Dialog_ShowEasy(playerid, TransferMobile, DIALOG_STYLE_INPUT, "โอนเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "", FormatNumber(PlayerData[playerid][pBankMoney]));
		}

		if(playertextid == PlayerPhoneTD[playerid][30]){
			ShowPlayerDialogMarket(playerid);
		}
	}

	if(TogVehSpeedo[playerid] == 0 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		if(!LoggedIn[playerid]) return 0;

		if(playertextid == VehSpeedo[playerid][7]){
			if(!PlayerToggleRightVehSpeedo[playerid]){
				PlayerToggleRightVehSpeedo[playerid] = true;
				PlayerTextDrawShow(playerid, VehSpeedo[playerid][9]);
				PlayerTextDrawShow(playerid, VehSpeedo[playerid][10]);
				PlayerTextDrawSetString(playerid, VehSpeedo[playerid][7], "<<");
			}
			else{
				PlayerToggleRightVehSpeedo[playerid] = false;
				PlayerTextDrawHide(playerid, VehSpeedo[playerid][9]);
				PlayerTextDrawHide(playerid, VehSpeedo[playerid][10]);
				PlayerTextDrawSetString(playerid, VehSpeedo[playerid][7], ">>");
			}
		}

		if(playertextid == VehSpeedo[playerid][8]){
			if(!PlayerToggleLeftVehSpeedo[playerid]){
				PlayerToggleLeftVehSpeedo[playerid] = true;
				PlayerTextDrawShow(playerid, VehSpeedo[playerid][11]);
				PlayerTextDrawShow(playerid, VehSpeedo[playerid][12]);
				PlayerTextDrawShow(playerid, VehSpeedo[playerid][13]);
				PlayerTextDrawShow(playerid, VehSpeedo[playerid][14]);
				PlayerTextDrawSetString(playerid, VehSpeedo[playerid][8], ">>");
			}
			else{
				PlayerToggleLeftVehSpeedo[playerid] = false;
				PlayerTextDrawHide(playerid, VehSpeedo[playerid][11]);
				PlayerTextDrawHide(playerid, VehSpeedo[playerid][12]);
				PlayerTextDrawHide(playerid, VehSpeedo[playerid][13]);
				PlayerTextDrawHide(playerid, VehSpeedo[playerid][14]);
			}
		}

		if(playertextid == VehSpeedo[playerid][9]){
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
				callcmd::engine(playerid, "\1");
				CancelSelectTextDraw(playerid);
			}
		}

		if(playertextid == VehSpeedo[playerid][11]){
			callcmd::lock(playerid, "\1");
			CancelSelectTextDraw(playerid);
		}

		if(playertextid == VehSpeedo[playerid][10]){
			callcmd::lights(playerid, "\1");
			CancelSelectTextDraw(playerid);
		}

		if(playertextid == VehSpeedo[playerid][12]){
			callcmd::windows(playerid, "\1");
			CancelSelectTextDraw(playerid);
		}

		if(playertextid == VehSpeedo[playerid][14]){
			new vehicleid = GetPlayerVehicleID(playerid);
			new carid = Car_GetID(vehicleid);
			if(carid != -1){
				if(IsPlayerInAnyVehicle(playerid)){
					if (CarData[carid][carLocked])
						return SendClientMessage(playerid, -1, "ยานพาหนะนี้ถูกล็อค");

					if (!IsDoorVehicle(vehicleid))
						return SendClientMessage(playerid, -1, "รถคันนี้ไม่มีฝากระโปรงหลังรถ");

					new FrontLeft, FrontRight, RearLeft, RearRight, WindShield, FrontBumper, RearBumper;
					GetVehiclePanelsDamageStatus(vehicleid, FrontLeft, FrontRight, RearLeft, RearRight, WindShield, FrontBumper, RearBumper);

					if (!GetTrunkStatus(vehicleid))
					{
						SetTrunkStatus(vehicleid, true);

						SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้เปิดฝากระโปรงหลังรถ", ReturnRoleplayName(playerid));
						if(TogVehSpeedo[playerid] == 0){
							PlayerTextDrawHide(playerid, VehSpeedo[playerid][14]);
							PlayerTextDrawColor(playerid, VehSpeedo[playerid][14], 0x0AE600AA);
							PlayerTextDrawShow(playerid, VehSpeedo[playerid][14]);
						}
					}
					else
					{
						SetTrunkStatus(vehicleid, false);

						SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้ปิดฝากระโปรงหลังรถ", ReturnRoleplayName(playerid));
						if(TogVehSpeedo[playerid] == 0){
							PlayerTextDrawHide(playerid, VehSpeedo[playerid][14]);
							PlayerTextDrawColor(playerid, VehSpeedo[playerid][14], -1);
							PlayerTextDrawShow(playerid, VehSpeedo[playerid][14]);
						}
					}
				}
			}
			CancelSelectTextDraw(playerid);
		}

		if(playertextid == VehSpeedo[playerid][13]){
			if(!LoggedIn[playerid]) return 0;
			new vehicleid = GetPlayerVehicleID(playerid);
			new carid = Car_GetID(vehicleid);
			if(carid != -1){
				if(IsPlayerInAnyVehicle(playerid)){
					if (CarData[carid][carLocked])
						return ErrorMsg(playerid, "ยานพาหนะนี้ถูกล็อค");

					if (!IsDoorVehicle(vehicleid))
						return ErrorMsg(playerid, "รถคันนี้ไม่มีฝากระโปรงหน้ารถ");

					new FrontLeft, FrontRight, RearLeft, RearRight, WindShield, FrontBumper, RearBumper;
					GetVehiclePanelsDamageStatus(vehicleid, FrontLeft, FrontRight, RearLeft, RearRight, WindShield, FrontBumper, RearBumper);

					if (!GetHoodStatus(vehicleid))
					{
						SetHoodStatus(vehicleid, true);

						SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้เปิดฝากระโปรงหน้ารถ", ReturnRoleplayName(playerid));
						if(TogVehSpeedo[playerid] == 0){
							PlayerTextDrawHide(playerid, VehSpeedo[playerid][13]);
							PlayerTextDrawColor(playerid, VehSpeedo[playerid][13], 0x0AE600AA);
							PlayerTextDrawShow(playerid, VehSpeedo[playerid][13]);
						}
					}
					else
					{
						SetHoodStatus(vehicleid, false);

						SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้ปิดฝากระโปรงหน้ารถ", ReturnRoleplayName(playerid));
						if(TogVehSpeedo[playerid] == 0){
							PlayerTextDrawHide(playerid, VehSpeedo[playerid][13]);
							PlayerTextDrawColor(playerid, VehSpeedo[playerid][13], -1);
							PlayerTextDrawShow(playerid, VehSpeedo[playerid][13]);
						}
					}
				}
			}
			CancelSelectTextDraw(playerid);
		}
	}

	if(OpenMenuCraftDrug[playerid] == 1){
		if(!LoggedIn[playerid]) return 0;
		if(playertextid == CraftDrug[playerid][5]){

			if(PlayerTradingItem[playerid]) return 1;

			if(StartCraftMixedDrug[playerid] == 0){
				Dialog_ShowEasy(playerid, SelectTypeMixedDrug, DIALOG_STYLE_LIST, "เลือกส่วนผสมที่ต้องการใช้", "ใช้ ส่วนผสมธรรมดา (แพ็คกัญชากับแพ็คโคเคน)", "เลือก", "ยกเลิก");
			}
		}
		if(playertextid == CraftDrug[playerid][6]){
			DrugCraft_Hide(playerid);
			TogglePlayerControllable(playerid, 1);
		}
	}

	if(Open_UpgradeMenu[playerid] == 1){
		if(playertextid == UpgradeWeapon_TextDraw[playerid][4]){
			if(PlayerStart_UpgradeWeapon[playerid] == 0)
				OnPlayer_UpgradeWeaponHide(playerid);
		}

		if(playertextid == UpgradeWeapon_TextDraw[playerid][5]){
			Show_PlayerSelectWeaponMain(playerid);
		}

		if(playertextid == UpgradeWeapon_TextDraw[playerid][9]){
			if(Weapon_MainModel[playerid] == 18631) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "คุณต้องเลือกอาวุธหลักที่จะบวกก่อน", "ตกลง", "");
			Show_PlayerSelectWeaponSecond(playerid);
		}

		if(playertextid == UpgradeWeapon_TextDraw[playerid][12]){

			if(UnBorkenCardModel[playerid] != 18631) return ErrorMsg(playerid, "คุณได้ใส่ดาวกันแตกไปแล้ว");

			Show_PlayerSelectUnbrokenCard(playerid);
		}

		if(playertextid == UpgradeWeapon_TextDraw[playerid][16]){
			if(!strcmp(UpgradeWeapon_GetStatus[playerid], "Not Ready", true)){
				return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "เงื่อนไขการตีบวกยังไม่ครบ!!", "ตกลง", "");
			}

			if(PlayerStart_UpgradeWeapon[playerid] == 0)
				OnPlayer_StartUpgradeWeapon(playerid);
		}
	}

	if(Open_UpgradeMenuFinish[playerid] == 1){
		if(playertextid == UpgradeWeapon_TextDrawSuc[playerid][11]){
			OnPlayerHide_TextDrawUpgradeSuc(playerid);
		}
	}
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;

	if(PlayerInScreen[playerid]){
		if(clickedid == Text:INVALID_TEXT_DRAW){
			return SelectTextDraw(playerid, 0xFF3A3AAA);
		}
	}

	if(LoggedIn[playerid]){
		if(PlayerInventoryStatus[playerid]){
			if(!PlayerEditPositionInventory[playerid] && !PlayerEditColorInventory[playerid]){
				if(clickedid == Text:INVALID_TEXT_DRAW){
					OnPlayerInventory_Close(playerid);
					if(PlayerUsing_HomeInv[playerid]){
						OnPlayerHomeInv_Close(playerid);
					}

					if(PlayerSelectingItem[playerid]){
						defer ReloadTradeItem(playerid);
					}
				}
			}
		}

		if(PlayerOpenFoodShop[playerid]){
			if(clickedid == Text:INVALID_TEXT_DRAW){
				return PlayerFoodShopMenu_Hide(playerid);
			}
		}
	}

	if(PlayerEnterRacing[playerid] && !PlayerRacingStarted[playerid]){
		if(clickedid == Text:INVALID_TEXT_DRAW){
			SelectTextDraw(playerid, 0x27FF00AA);
		}
	}

	if(PlayerTradingItem[playerid] && !PlayerSelectingItem[playerid]){
		if(clickedid == Text:INVALID_TEXT_DRAW){
			SelectTextDraw(playerid, PlayerInventoryHoverCodeColor[playerid]);
		}
		return 1;
	}

	if(IsOpeningGaCha[playerid] && StartRandom[playerid] != 1){
        if (clickedid == Text:INVALID_TEXT_DRAW) return HideGaChaBox(playerid);
    }

    if(IsOpeningGaCha[playerid] && StartRandom[playerid] == 1){
        if (clickedid == Text:INVALID_TEXT_DRAW) return SelectTextDraw(playerid, 0x0FFF00AA);
    }

	if(LoggedIn[playerid]){
        new string[128];

        if (clickedid == Text:INVALID_TEXT_DRAW){
            if(PlayerOpeningMenuCabara[playerid]){
                if(PlayerMoneyDown[playerid] != 0) {
                    SelectTextDraw(playerid, 0x00E50AAA);
                    TogglePlayerControllable(playerid, 0);
                    return ErrorMsg(playerid, "คุณลงเงินแล้วไม่สามารถปิดได้จนกว่าจะขึ้นรอบใหม่");
                }
                for(new i=0; i<15; i++){
                    TextDrawHideForPlayer(playerid, TextDrawCabara[i]);
                }
                CancelSelectTextDraw(playerid);
                TogglePlayerControllable(playerid, 1);
                ResetCabaraPlayer(playerid);
                return 1;
            }
		}

        if(PlayerOpeningMenuCabara[playerid]){
            if(clickedid == TextDrawCabara[1]){
                if(PlayerMoneyDown[playerid] != 0) return ErrorMsg(playerid, "คุณลงเงินแล้วไม่สามารถปิดได้จนกว่าจะขึ้นรอบใหม่");
                for(new i=0; i<15; i++){
                    TextDrawHideForPlayer(playerid, TextDrawCabara[i]);
                }
                CancelSelectTextDraw(playerid);
                TogglePlayerControllable(playerid, 1);
                ResetCabaraPlayer(playerid);
            }

            if(clickedid == TextDrawCabara[8]){
                if(CabaraStart) return 1;
                if(!CabaraIsOpen) return ErrorMsg(playerid, "ขณะนี้ไม่สามารถเล่นได้กรุณามาลองใหม่ในช่วงเวลา 12:00 - 14:00, 18:00 - 20:00, 00:00 - 03:00");
                if(PlayerMoneyDown[playerid] == 0){
                    format(string, sizeof(string), "คุณมีเงินอยู่: %s\nกรอกจำนวนด้านล่างเพื่อลงเงินของคุณ: ", FormatNumber(GetMoney(playerid)));
                    Dialog_ShowEasy(playerid, Input_MoneyPlayer, DIALOG_STYLE_INPUT, "ลงเงินของคุณ - Player", string, "ลงเงิน", "ยกเลิก");
                }
            }

            if(clickedid == TextDrawCabara[9]){
                if(CabaraStart) return 1;
                if(!CabaraIsOpen) return ErrorMsg(playerid, "ขณะนี้ไม่สามารถเล่นได้กรุณามาลองใหม่ในช่วงเวลา 12:00 - 14:00, 18:00 - 20:00, 00:00 - 03:00");
                if(PlayerMoneyDown[playerid] == 0){
                    format(string, sizeof(string), "คุณมีเงินอยู่: %s\nกรอกจำนวนด้านล่างเพื่อลงเงินของคุณ: ", FormatNumber(GetMoney(playerid)));
                    Dialog_ShowEasy(playerid, Input_MoneyBanker, DIALOG_STYLE_INPUT, "ลงเงินของคุณ - Banker", string, "ลงเงิน", "ยกเลิก");
                }
            }

            if(clickedid == TextDrawCabara[10]){
                if(CabaraStart) return 1;
                if(!CabaraIsOpen) return ErrorMsg(playerid, "ขณะนี้ไม่สามารถเล่นได้กรุณามาลองใหม่ในช่วงเวลา 12:00 - 14:00, 18:00 - 20:00, 00:00 - 03:00");
                if(PlayerMoneyDown[playerid] == 0){
                    format(string, sizeof(string), "คุณมีเงินอยู่: %s\nกรอกจำนวนด้านล่างเพื่อลงเงินของคุณ: ", FormatNumber(GetMoney(playerid)));
                    Dialog_ShowEasy(playerid, Input_MoneyTie, DIALOG_STYLE_INPUT, "ลงเงินของคุณ - Tie", string, "ลงเงิน", "ยกเลิก");
                }
            }
        }
    }

	if(LoggedIn[playerid]){
        if(PlayerData[playerid][pJob] == WEAPONDEALERJOB){
            if(PlayerOpenCraftWeaponMenu[playerid] == 1){
                if (clickedid == Text:INVALID_TEXT_DRAW)
                {
                    TogglePlayerControllable(playerid, 1);
                    CancelSelectTextDraw(playerid);
                    HidePlayerCraftWeaponMenu(playerid);
                    return 1;
                }
            }

            if(PlayerOpenCraftWeaponInfoMenu[playerid] == 1){
                if(clickedid == Text:INVALID_TEXT_DRAW){
                    TogglePlayerControllable(playerid, 1);
                    CancelSelectTextDraw(playerid);
                    HideWeaponCraftInfo(playerid);

                    DestroyPlayerProgressbar_Job(playerid);
                    return 1;
                }
            }
        }
    }

	if(PlayerOpenPizzaMenu[playerid]){
        if(!LoggedIn[playerid]) return 0;
        if (clickedid == Text:INVALID_TEXT_DRAW){
            if(!StartBakedPizza[playerid]) ClosePizzaMenu(playerid);
        }
    }

	if(Can_CloseUpgradeFinish[playerid] == 1){
		if(!LoggedIn[playerid]) return 0;
		if (clickedid == Text:INVALID_TEXT_DRAW){
			OnPlayerHide_TextDrawUpgradeSuc(playerid);
		}
	}

	if(Open_UpgradeMenu[playerid] == 1){
		if(!LoggedIn[playerid]) return 0;
		if (clickedid == Text:INVALID_TEXT_DRAW){
			if(PlayerStart_UpgradeWeapon[playerid] == 0)
				OnPlayer_UpgradeWeaponHide(playerid);
		}
	}

	if(OnPlayerShowMarryCard[playerid] == 1){
		if(!LoggedIn[playerid]) return 0;
		for(new i=0; i<TEXTMARRY; i++){
			PlayerTextDrawHide(playerid, MarryText[playerid][i]);
			PlayerTextDrawDestroy(playerid, MarryText[playerid][i]);
		}

		HidePlayerProgressBar(playerid, MarryBar[playerid][0]);
		DestroyPlayerProgressBar(playerid, MarryBar[playerid][0]);

		CancelSelectTextDraw(playerid);
		OnPlayerShowMarryCard[playerid] = 0;
		return 1;
	}

	if(PlayerUsingPhone[playerid] == 1){
		if(!LoggedIn[playerid]) return 0;
		if (clickedid == Text:INVALID_TEXT_DRAW)
		{
            TogglePlayerControllable(playerid, 1);
			HideMobilePhone(playerid);
            return 1;
		}
	}

	if(PlayerEditingObject[playerid] == 1){
		if(!LoggedIn[playerid]) return 0;
		if (clickedid == Text:INVALID_TEXT_DRAW){
			HideEditingObject(playerid);
			SendClientMessage(playerid, COLOR_YELLOW, "คุณได้เซฟการแต่งกายเรียบร้อยแล้ว");
		}
	}
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(clickedplayerid < 0 || clickedplayerid >= MAX_PLAYERS || !IsPlayerConnected(clickedplayerid)) return 0;
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] >= 1) {

		if(!IsPlayerConnected(clickedplayerid))
			return SendClientMessage(playerid, COLOR_GREY, "ไอดีผู้เล่นที่คุณระบุ ไม่ได้เชื่อต่อกับเซิฟเวอร์");

		if(PlayerData[playerid][pSpec] == INVALID_PLAYER_ID) {
			GetPlayerPos(playerid, PlayerData[playerid][pPosX], PlayerData[playerid][pPosY], PlayerData[playerid][pPosZ]);
			Character_Save(playerid);
			PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);
			PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
			//PlayerData[playerid][pSkin] = GetPlayerSkin(playerid);
			GetPlayerHealth(playerid, PlayerData[playerid][pHP]);
			GetPlayerArmour(playerid, PlayerData[playerid][pAM]);
		}
		PlayerData[playerid][pSpec] = clickedplayerid;
		TogglePlayerSpectating(playerid, true);
		SetPlayerColor(playerid, 0xFFFFFF00);
		SetPlayerInterior(playerid, GetPlayerInterior(clickedplayerid));
		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(clickedplayerid));

		if(IsPlayerInAnyVehicle(clickedplayerid)) {
			PlayerSpectateVehicle(playerid, GetPlayerVehicleID(clickedplayerid));
		}
		else {
			PlayerSpectatePlayer(playerid, clickedplayerid);
		}
	}
	return 1;
}

public OnIncomingPacket(playerid, packetid, BitStream:bs)
{
	#pragma unused bs
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(Security_CheckNetFlood(playerid, packetid, false)) return 0;

	switch(packetid)
	{
		case 200, 203, 207, 211:
		{
			if(!IsPlayerNPC(playerid) && !LoggedIn[playerid]) return 0;
		}
	}
	return 1;
}

public OnIncomingRPC(playerid, rpcid, BitStream:bs)
{
	#pragma unused bs
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;
	if(Security_CheckNetFlood(playerid, rpcid, true)) return 0;
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid) || !LoggedIn[playerid]) return 0;
	if(weaponid < 0 || weaponid > 55) return 0;
	if(SecurityAC_CheckShot(playerid, weaponid)) return 0;
	if(hittype == BULLET_HIT_TYPE_PLAYER && (hitid == INVALID_PLAYER_ID || !IsPlayerConnected(hitid))) return 0;

	if(weaponid == PlayerData[playerid][pMyWeapon][0]){
		PlayerData[playerid][pMyAmmo][0]--;
		if(PlayerData[playerid][pMyAmmo][0] == 0){
			if(PlayerData[playerid][pMyWeapon][0] == 31){
				SetPlayerAttachedObject(playerid,5,356,6,-0.001999,0.000000,0.018999,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
			}
		}
	}

	if(weaponid == PlayerData[playerid][pMyWeapon][1]){
		PlayerData[playerid][pMyAmmo][1]--;
		if(PlayerData[playerid][pMyAmmo][1] == 0){
			if(PlayerData[playerid][pMyWeapon][1] == 22){
				SetPlayerAttachedObject(playerid,6,346,6,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
			}
		}
	}

	if(weaponid == TASER_WEAPON){
		if(taser[playerid]){
			GiveTaserAgainTimerEx[playerid] = 0;
			GiveTaserAgainTimer[playerid] = SetTimerEx("GiveTaserAgain",TASER_USE_TIME, 0, "i", playerid);
			TaserShoot[playerid] = 1;
			ApplyAnimation(playerid, "SWORD", "sword_block", 4.1, 0, 1, 0, 1, 1, 1);
			SetPlayerAttachedObject(playerid, 0, TASER_OBJECT, 6);
			SetPlayerArmedWeapon(playerid, 0);

			if(hittype == BULLET_HIT_TYPE_PLAYER){
				new Float:x, Float:y, Float:z;
				GetPlayerPos(hitid, x, y, z);
				IsPlayerTaser[hitid] = 1;
				TaserTime[hitid] = 0;
				TogglePlayerControllable(hitid, 0);
				ApplyAnimation(hitid, "CRACK", "crckdeth2", 4.1, 0, 1, 1, 1, TASER_EFFECT_TIME, 1);
				SetPlayerDrunkLevel(hitid, 5000);
				SetTimerEx("EndTaserEffect", TASER_EFFECT_TIME, 0, "i", hitid);
			}
		}
	}
    return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid) || !LoggedIn[playerid]) return 0;
	if(index < 0 || index > 9 || boneid < 1 || boneid > 18) { SecurityKick(playerid, "bad-attached-object-index"); return 0; }
	if(modelid < 1 || modelid > 20000) { SecurityKick(playerid, "bad-attached-object-model"); return 0; }
	if(fScaleX < 0.01 || fScaleX > 10.0 || fScaleY < 0.01 || fScaleY > 10.0 || fScaleZ < 0.01 || fScaleZ > 10.0) { SecurityKick(playerid, "bad-attached-object-scale"); return 0; }
	if(fOffsetX < -10.0 || fOffsetX > 10.0 || fOffsetY < -10.0 || fOffsetY > 10.0 || fOffsetZ < -10.0 || fOffsetZ > 10.0) { SecurityKick(playerid, "bad-attached-object-offset"); return 0; }
	if (response){
		if(GetPVarInt(playerid, "AttachEdit") == 1){
   			DeletePVar(playerid, "AttachEdit");
        	SetPlayerAttachedObject(playerid, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ);
			printf("SetPlayerAttachedObject(%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f);", playerid, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ);
		}

		if(GetPVarInt(playerid, "EditHat") == 1){

			PlayerData[playerid][pAccessoryEditHat] = 1;
			AccessoryData[playerid][0][0] = fOffsetX;
			AccessoryData[playerid][0][1] = fOffsetY;
			AccessoryData[playerid][0][2] = fOffsetZ;

			AccessoryData[playerid][0][3] = fRotX;
			AccessoryData[playerid][0][4] = fRotY;
			AccessoryData[playerid][0][5] = fRotZ;

			AccessoryData[playerid][0][6] = fScaleX;
			AccessoryData[playerid][0][7] = fScaleY;
			AccessoryData[playerid][0][8] = fScaleZ;

			SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ยืนยันการแต่ง '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameHat]);

			SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
			Character_Save(playerid);

			DeletePVar(playerid, "EditHat");
		}

		if(GetPVarInt(playerid, "EditGlasses") == 1){
			PlayerData[playerid][pAccessoryEditGlasses] = 1;
			AccessoryData[playerid][1][0] = fOffsetX;
			AccessoryData[playerid][1][1] = fOffsetY;
			AccessoryData[playerid][1][2] = fOffsetZ;

			AccessoryData[playerid][1][3] = fRotX;
			AccessoryData[playerid][1][4] = fRotY;
			AccessoryData[playerid][1][5] = fRotZ;

			AccessoryData[playerid][1][6] = fScaleX;
			AccessoryData[playerid][1][7] = fScaleY;
			AccessoryData[playerid][1][8] = fScaleZ;

			SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ยืนยันการแต่ง '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameGlasses]);

			SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
			Character_Save(playerid);

			DeletePVar(playerid, "EditGlasses");
		}

		if(GetPVarInt(playerid, "EditBody") == 1){

			PlayerData[playerid][pAccessoryEditBody] = 1;
			AccessoryData[playerid][2][0] = fOffsetX;
			AccessoryData[playerid][2][1] = fOffsetY;
			AccessoryData[playerid][2][2] = fOffsetZ;

			AccessoryData[playerid][2][3] = fRotX;
			AccessoryData[playerid][2][4] = fRotY;
			AccessoryData[playerid][2][5] = fRotZ;

			AccessoryData[playerid][2][6] = fScaleX;
			AccessoryData[playerid][2][7] = fScaleY;
			AccessoryData[playerid][2][8] = fScaleZ;

			SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ยืนยันการแต่ง '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameBody]);

			SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
			Character_Save(playerid);

			DeletePVar(playerid, "EditBody");
		}

		if(GetPVarInt(playerid, "EditArms") == 1){

			PlayerData[playerid][pAccessoryEditArms] = 1;
			AccessoryData[playerid][3][0] = fOffsetX;
			AccessoryData[playerid][3][1] = fOffsetY;
			AccessoryData[playerid][3][2] = fOffsetZ;

			AccessoryData[playerid][3][3] = fRotX;
			AccessoryData[playerid][3][4] = fRotY;
			AccessoryData[playerid][3][5] = fRotZ;

			AccessoryData[playerid][3][6] = fScaleX;
			AccessoryData[playerid][3][7] = fScaleY;
			AccessoryData[playerid][3][8] = fScaleZ;

			SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ยืนยันการแต่ง '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameArms]);

			SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
			Character_Save(playerid);

			DeletePVar(playerid, "EditArms");
		}
	}
	return 1;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz){
	if(playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid) || !LoggedIn[playerid]) return 0;
	if(!IsValidDynamicObject(objectid)) { SecurityKick(playerid, "bad-dynamic-object-id"); return 0; }
	if(response < EDIT_RESPONSE_CANCEL || response > EDIT_RESPONSE_UPDATE) { SecurityKick(playerid, "bad-dynamic-object-response"); return 0; }
	if(x < -20000.0 || x > 20000.0 || y < -20000.0 || y > 20000.0 || z < -1000.0 || z > 30000.0) { SecurityKick(playerid, "bad-dynamic-object-pos"); return 0; }
	if(rx < -3600.0 || rx > 3600.0 || ry < -3600.0 || ry > 3600.0 || rz < -3600.0 || rz > 3600.0) { SecurityKick(playerid, "bad-dynamic-object-rot"); return 0; }

	if (PlayerData[playerid][pEditGate] != -1 && GateData[PlayerData[playerid][pEditGate]][gateExists]){
		if (response == EDIT_RESPONSE_FINAL){
			switch (PlayerData[playerid][pEditType]){
				case 1:{
					new id = PlayerData[playerid][pEditGate];
					GateData[id][gatePos][0] = x;
					GateData[id][gatePos][1] = y;
					GateData[id][gatePos][2] = z;
					GateData[id][gatePos][3] = rx;
					GateData[id][gatePos][4] = ry;
					GateData[id][gatePos][5] = rz;
					if(IsValidDynamicObject(GateData[id][gateObject]) && GateData[id][gateObject] != -1) DestroyDynamicObject(GateData[id][gateObject]);
					GateData[id][gateObject] = -1;
					GateData[id][gateObject] = CreateDynamicObject(GateData[id][gateModel], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5], GateData[id][gateWorld], GateData[id][gateInterior]);
					Gate_Save(id);
					SendClientMessageEx(playerid, -1, "คุณได้แก้ไขตำแหน่งปรกติของ Gate ไอดี: %d.", id);
				}
				case 2:{
					new id = PlayerData[playerid][pEditGate];
					GateData[id][gateMove][0] = x;
					GateData[id][gateMove][1] = y;
					GateData[id][gateMove][2] = z;
					GateData[id][gateMove][3] = rx;
					GateData[id][gateMove][4] = ry;
					GateData[id][gateMove][5] = rz;
					if(IsValidDynamicObject(GateData[id][gateObject]) && GateData[id][gateObject] != -1) DestroyDynamicObject(GateData[id][gateObject]);
					GateData[id][gateObject] = -1;
					GateData[id][gateObject] = CreateDynamicObject(GateData[id][gateModel], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5], GateData[id][gateWorld], GateData[id][gateInterior]);

					Gate_Save(id);
					SendClientMessageEx(playerid, -1, "คุณได้แก้ไขตำแหน่งการเคลื่อนย้ายของ Gate ไอดี: %d", id);
				}
			}
		}
	}

	if (PlayerData[playerid][pEditPump] != -1 && PumpData[PlayerData[playerid][pEditPump]][pumpExists]){
		if (response == EDIT_RESPONSE_FINAL)
		{
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][0] = x;
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][1] = y;
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][2] = z;
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][3] = rz;

			Pump_Refresh(PlayerData[playerid][pEditPump]);
			Pump_Save(PlayerData[playerid][pEditPump]);

			SendClientMessageEx(playerid, -1, "คุณได้แก้ไขปั้ม ID: %d", PlayerData[playerid][pEditPump]);

			PlayerData[playerid][pEditPump] = -1;
		}
		return 1;
	}

	if (EditATM[playerid] != -1 && ATMData[EditATM[playerid]][atmExists]){
		if (response == EDIT_RESPONSE_FINAL){
			ATMData[EditATM[playerid]][atmPos][0] = x;
			ATMData[EditATM[playerid]][atmPos][1] = y;
			ATMData[EditATM[playerid]][atmPos][2] = z+0.3;
			ATMData[EditATM[playerid]][atmPos][3] = rz;

			ATM_Refresh(EditATM[playerid]);
			ATM_Save(EditATM[playerid]);

			SendClientMessageEx(playerid, -1, "คุณได้แก้ไข ATM ID: %d เรียบร้อยแล้ว!", EditATM[playerid]);

			EditATM[playerid] = -1;
		}
		return 1;
	}
	return 1;
}

Dialog:GatePass(playerid, response, listitem, inputtext[]){
	if(!response) return 1;
	if (response){
	    new id = Gate_Nearest(playerid);

	    if (id == -1)
	        return 0;

        if (isnull(inputtext))
        	return Dialog_ShowEasy(playerid, GatePass, DIALOG_STYLE_INPUT, "Enter Password", "กรุณาป้อนรหัสผ่านของ Gate ด้านล่างนี้:", "Submit", "Cancel");

		if (strcmp(inputtext, GateData[id][gatePass]) != 0)
  			return Dialog_ShowEasy(playerid, GatePass, DIALOG_STYLE_INPUT, "Enter Password", "ข้อผิดพลาด: รหัสผ่านที่ระบุไม่ถูกต้อง\n\nกรุณาป้อนรหัสผ่าน Gate ด้านล่างนี้:", "Submit", "Cancel");

		Gate_Operate(id);
	}
	return 1;
}
