forward ChangeNameToUsername(playerid);
public ChangeNameToUsername(playerid){
	printf("%s to %s", ReturnName(playerid), AccountData[playerid][uName]);
	if(UserNameValidator(AccountData[playerid][uName])){
		ErrorMsg(playerid, "ชื่อ Username ของคุณมี '_' ระบบจึงทำการตัดคุณออกจากระบบทันที");
		return SetTimerEx("FixKick", 200, false, "d", playerid);
	}
	SetPlayerName(playerid, AccountData[playerid][uName]);
	return 1;
}

forward StopSong(playerid);
public StopSong(playerid){
	StopAudioStreamForPlayer(playerid);
	return 1;
}

forward FixKick(playerid);
public FixKick(playerid){
	if(IsPlayerConnected(playerid)) Kick(playerid);
	return 1;
}

forward Move_Player(playerid, Float:X, Float:Y, Float:Z, Int, World);
public Move_Player(playerid, Float:X, Float:Y, Float:Z, Int, World){
	SetPlayerPos(playerid, X, Y, Z);
	SetPlayerInterior(playerid, Int);
	SetPlayerVirtualWorld(playerid, World);
	return 1;
}

forward Jumper(playerid);
public Jumper(playerid){
    ClearAnimations(playerid);
    return 1;
}

forward ShowPlayerTradeMoneyMenu(playerid);
public ShowPlayerTradeMoneyMenu(playerid){
	if(!LoggedIn[playerid]) return 1;
	new stringplayer[1024];
	new count;
	new menu[20];
	foreach(new x : Player){
		if(!LoggedIn[x]) continue;
		if(x == playerid) continue;
		if(PlayerData[x][pPlayerhour] < 5) continue;
		if(IsPlayerNearPlayer(playerid, x, 3.0)){
			format(menu, 20, "menu%d", count++);
			SetPVarInt(playerid, menu, x);
			format(stringplayer, sizeof(stringplayer), "%s %s(%d)\n", stringplayer, ReturnRoleplayName(x), x);
		}
		if(count >= 20) break;
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "เลือกผู้เล่นที่คุณต้องการจะให้เงิน", "ไม่มีใครอยู่ใกล้คุณเลย", "ตกลง", "ยกเลิก");
	else Dialog_ShowEasy(playerid, TradeMoney, DIALOG_STYLE_LIST, "เลือกผู้เล่นที่คุณต้องการจะให้เงิน", stringplayer, "เลือก", "ยกเลิก");
	return 1;
}

Dialog:TradeMoney(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);
			SetPVarInt(playerid, "playerID", GetPVarInt(playerid, str_biz));
			SetPlayerTradeMoney(playerid);
			return 1;
		}
    }
    return 1;
}

forward SetPlayerTradeMoney(playerid);
public SetPlayerTradeMoney(playerid){
	new targetid = GetPVarInt(playerid, "playerID");
	if(targetid != INVALID_PLAYER_ID && LoggedIn[targetid]){
		new string[256];
		format(string, sizeof string, "ผู้เล่นที่เทรดด้วย: %s(%d)\nใส่จำนวนเงินที่คุณการจะเทรด: ", ReturnRoleplayName(targetid), targetid);
		Dialog_ShowEasy(playerid, InputNumberTradeMoney, DIALOG_STYLE_INPUT, "ใส่จำนวนเงิน", string, "ตกลง", "ยกเลิก");

	} else return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
	return 1;
}

Dialog:InputNumberTradeMoney(playerid, response, listitem, inputtext[]){
	if(!response){
		DeletePVar(playerid, "playerID");
		return 1;
	}
	if(response){
		new targetid = GetPVarInt(playerid, "playerID");
		new amount = strval(inputtext);
		new string[256];
		if(amount <= 0){
			format(string, sizeof string, "[!] คุณต้องใส่จำนวนเงินมากกว่า 0\nผู้เล่นที่เทรดด้วย: %s(%d)\nใส่จำนวนเงินที่คุณการจะเทรด: ", ReturnRoleplayName(targetid), targetid);
			Dialog_ShowEasy(playerid, InputNumberTradeMoney, DIALOG_STYLE_INPUT, "ใส่จำนวนเงิน", string, "ตกลง", "ยกเลิก");
			return 1;
		}

		if(amount > GetMoney(playerid)){
			format(string, sizeof string, "[!] คุณมีจำนวนเงินไม่พอที่จะเทรด\nผู้เล่นที่เทรดด้วย: %s(%d)\nใส่จำนวนเงินที่คุณการจะเทรด: ", ReturnRoleplayName(targetid), targetid);
			Dialog_ShowEasy(playerid, InputNumberTradeMoney, DIALOG_STYLE_INPUT, "ใส่จำนวนเงิน", string, "ตกลง", "ยกเลิก");
			return 1;
		}

		if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) {
			DeletePVar(playerid, "playerID");
			return ErrorMsg(playerid, "ผู้เล่นนั้นออกห่างจากคุณไปแล้ว");
		}

		GiveMoney(playerid, -amount, "เทรดเงิน");
		GiveMoney(targetid, amount, "เทรดเงิน");
		SendClientMessageEx(playerid, COLOR_YELLOW, "| คุณได้ให้เงินจำนวน %s กับผู้เล่น %s(%d) สำเร็จ", FormatNumber(amount), ReturnRoleplayName(targetid), targetid);
		SendClientMessageEx(targetid, COLOR_YELLOW, "| คุณได้รับเงินจำนวน %s จากผู้เล่น %s(%d) สำเร็จ", FormatNumber(amount), ReturnRoleplayName(playerid), playerid);
	}
	return 1;
}

forward SyncCamera(playerid);
public SyncCamera(playerid)
{
	if(!LoggedIn[playerid]) return 0;
	if(GetPVarInt(playerid, "DisableFPS") == 1){
		if(!IsPlayerInAnyVehicle(playerid))
		{
			AttachObjectToPlayer(PlayerData[playerid][pCameraFPS], playerid, 0.0, 0.20, 0.75, 0.0, 0.0, 0.0);
			AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
		}
		else
		{
			if(IsABike(GetPlayerVehicleID(playerid)))
			{
    		if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 461) //PCJ Suc
		    {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), 0.089999, 0.050000, 1.004999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
				else
				{
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), -0.484999, -0.309999, 1.164999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
			}
     		else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 462) //Faggio Suc
		    {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), 0.089999, -0.100000, 1.004999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
				else
				{
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), -0.004999, -0.609999, 1.164999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
			}
     		else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 586) //Wayfarer
		    {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), 0.089999, -0.18, 1.190, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
				else
				{
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), -0.084999, -0.809999, 1.264999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
			}
     		else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 521) // FCR-900
		    {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), 0.089999, 0.050000, 1.004999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
				else
				{
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), -0.484999, -0.309999, 1.164999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
			}
     		else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 522) // NRG-500
		    {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), 0.049999, 0.050000, 1.004999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
				else
				{
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), -0.284999, -0.459999, 1.164999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
			}
     		else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 468) // Sanchez
		    {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), 0.00, -0.100000, 0.954999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
				else
				{
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), -0.324999, -0.485, 1.154999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
			}
   		    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 581) //BF
		    {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), 0.089999, 0.050000, 1.004999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
				else
				{
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), -0.484999, -0.309999, 1.164999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
			}
   		    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 463) //Freeway
		    {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), 0.044999, -0.269999, 1.039999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
				else
				{
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), -0.059999, -0.859999, 1.289999, 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
				}
			}
		    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 411)
		    {
		    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], GetPlayerVehicleID(playerid), -0.40, -0.15, 0.45, 0.0, 0.0, 0.0);
				AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
			}
			}
			else
			{
			    new vehicleid = GetPlayerVehicleID(playerid);
			    new vehiclemodelid = GetVehicleModel(vehicleid);

			    new iSeat = GetPlayerVehicleSeat(playerid);
			    new Float:X, Float:Y, Float:Z;
			    GetVehicleModelInfo(vehiclemodelid, VEHICLE_MODEL_INFO_FRONTSEAT, X, Y, Z);

				if(iSeat == 0)
			    {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], vehicleid, X+(-0.85), Y+(-0.18), Z+(0.585), 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
			    }
				else if(iSeat == 1)
			    {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], vehicleid, X+(0.05), Y+(-0.18), Z+(0.585), 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
			    }
				else if(iSeat == 2)
			    {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], vehicleid, X+(-0.85), Y+(-0.86), Z+(0.585), 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
			    }
				else if(iSeat == 3)
			    {
			    	AttachObjectToVehicle(PlayerData[playerid][pCameraFPS], vehicleid, X+(0.05), Y+(-0.86), Z+(0.585), 0.0, 0.0, 0.0);
					AttachCameraToObject(playerid, PlayerData[playerid][pCameraFPS]);
			    }
			}
		}
	}
	return 1;
}

forward UnfreezePlayer(playerid);
public UnfreezePlayer(playerid){
	TogglePlayerControllable(playerid, 1);
	if(PlayerData[playerid][pCuffed] == 1){
		BitFlag_On(g_PlayerFlags[playerid],PLAYER_CUFFED);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CUFFED);
		SetPlayerAttachedObject(playerid, 7, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
		TogglePlayerControllable(playerid, 0);
	}
	return 1;
}

forward RemoveAttachedObject(playerid, slot);
public RemoveAttachedObject(playerid, slot)
{
	if (IsPlayerConnected(playerid) && IsPlayerAttachedObjectSlotUsed(playerid, slot))
	{
	    RemovePlayerAttachedObject(playerid, slot);
	}
	return 1;
}

forward RemoveProp(playerid);
public RemoveProp(playerid){
	RemoveAttachedObject(playerid, 9);
	return 1;
}

forward SetCameraToHospital(playerid);
public SetCameraToHospital(playerid){
	if(PlayerData[playerid][pHospitalType] == 1){
		SetPlayerCameraPos(playerid, 1196.5680,-1340.9473,18.3507);
		SetPlayerCameraLookAt(playerid, 1172.5717,-1323.9811,15.4036);
	}
	else if(PlayerData[playerid][pHospitalType] == 2){
		SetPlayerCameraPos(playerid, -2670.5222,597.2415,19.3292);
		SetPlayerCameraLookAt(playerid, -2651.1536,639.2015,14.4531);
	}
	
	SetStartTimeHospital[playerid] = 1;
	return 1;
}

//กันโปร

forward OnCheatDetected(playerid, const ip_address[], type, code);
public OnCheatDetected(playerid, const ip_address[], type, code){

	new hacking[64], Float:extrafloat;
	switch(code){
		case 0: {
			format(hacking, sizeof(hacking), "AirBreak (onfoot)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
  		case 1: {
			format(hacking, sizeof(hacking), "AirBreak (in vehicle)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}

		}
		case 2:{
			if(PlayerData[playerid][pAdmin] <= 0){
				format(hacking, sizeof(hacking), "teleport hack (onfoot)");
				foreach(new x : Player) if(LoggedIn[x]){
					if(PlayerData[x][pAdmin] <= 0) continue;
					if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
				}
			}
		}
		case 3: {
			format(hacking, sizeof(hacking), "teleport hack (in vehicle)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 4: {
			if(!IsAndroidPlayer(playerid)){
				format(hacking, sizeof(hacking), "teleport hack (into vehicles)");
				foreach(new x : Player) if(LoggedIn[x]){
					if(PlayerData[x][pAdmin] <= 0) continue;
					if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
				}
			}
		}
		case 5: {
			format(hacking, sizeof(hacking), "teleport hack (vehicle to player)");
			/*foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}*/
		}
		case 6: {
			format(hacking, sizeof(hacking), "teleport hack (pickups)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 7: {
			format(hacking, sizeof(hacking), "FlyHack (onfoot)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
			return Kick(playerid);
		}
		case 8: {
			format(hacking, sizeof(hacking), "FlyHack (in vehicle)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 9: {
			format(hacking, sizeof(hacking), "SpeedHack (onfoot)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
			return Kick(playerid);
		}
		case 10: {
			format(hacking, sizeof(hacking), "SpeedHack (in vehicle)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
			Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ระบบป้องกันโปร", "ระบบได้ตรวจพบว่าคุณพยายามที่จะใช้ Speed Hack กรุณาลบออกทันที ไม่งั้นคุณจะโดนแบน", "ตกลง", "");
			KickPlayer(playerid);
			return 1;
		}
		case 11: {
			format(hacking, sizeof(hacking), "Health Vehicle Hack (ใช้โปรเพิ่มเลือดยานพาหนะ)");
      		new vehicleid = GetPlayerVehicleID(playerid), d1, d2, d3, d4;
			AntiCheatGetVehicleHealth(vehicleid, extrafloat);
			SetVehicleHealth(vehicleid, extrafloat);
   			UpdateVehicleDamageStatus(vehicleid, d1, d2, d3, d4);
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 12: {
			format(hacking, sizeof(hacking), "Health hack (onfoot)");
		    AntiCheatGetHealth(playerid, extrafloat);
		    SetPlayerHealthEx(playerid, extrafloat);
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 13: {
			format(hacking, sizeof(hacking), "Armour hack");
		    AntiCheatGetArmour(playerid, extrafloat);
		    SetPlayerArmour(playerid, extrafloat);
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 14: {
			if(LoggedIn[playerid]){
				format(hacking, sizeof(hacking), "Money hack (เสกเงิน)");
				foreach(new x : Player) if(LoggedIn[x]){
					if(PlayerData[x][pAdmin] <= 0) continue;
					if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
				}
			}
		}
		case 15: {
			if(GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_NATIONAL){
				format(hacking, sizeof(hacking), "Weapon hack (เสกอาวุธ)");
				foreach(new x : Player) if(LoggedIn[x]){
					if(PlayerData[x][pAdmin] <= 0) continue;
					if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
				}
				return Kick(playerid);
			}
		}
		case 16: {
			format(hacking, sizeof(hacking), "Ammo hack (add)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 17: {
			format(hacking, sizeof(hacking), "Ammo hack (infinite)");
		}
		case 18: format(hacking, sizeof(hacking), "Special actions hack");
		case 19: {
			format(hacking, sizeof(hacking), "GodMode from bullets (onfoot)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 20: {
			format(hacking, sizeof(hacking), "GodMode from bullets (in vehicle)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 21: {
			format(hacking, sizeof(hacking), "Invisible hack");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 22: {
			format(hacking, sizeof(hacking), "lagcomp-spoof");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 23: {
			format(hacking, sizeof(hacking), "Tuning hack");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 24: {
			format(hacking, sizeof(hacking), "Parkour mod");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 25: {
			format(hacking, sizeof(hacking), "Quick turn");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 26: {
			format(hacking, sizeof(hacking), "Rapid fire (ยิงเร็ว)");
			/*foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}*/
		}
		case 27: {
			format(hacking, sizeof(hacking), "FakeSpawn");
			/*foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}*/
		}
		case 28: {
			format(hacking, sizeof(hacking), "FakeKill");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 29: {
			format(hacking, sizeof(hacking), "Pro Aim (ใช้ Aimbot)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 30: {
			format(hacking, sizeof(hacking), "CJ run (ใช้ท่าวิ่ง CJ)");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 31: {
			format(hacking, sizeof(hacking), "CarShot");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 32: {
			format(hacking, sizeof(hacking), "CarJack");
			CountCheckCarJack[playerid]++;
			if(CountCheckCarJack[playerid] >= 5){
				foreach(new x : Player) if(LoggedIn[x]){
					if(PlayerData[x][pAdmin] <= 0) continue;
					if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
				}
				return Kick(playerid);
			}
		}
		case 33: {
			format(hacking, sizeof(hacking), "UnFreeze");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 34: {
			format(hacking, sizeof(hacking), "AFK Ghost");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 35: {
			format(hacking, sizeof(hacking), "Full Aiming");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 36: {
			format(hacking, sizeof(hacking), "Fake NPC");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 37: {
			format(hacking, sizeof(hacking), "Reconnect");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
			return Kick(playerid);
		}
		case 38: {
			format(hacking, sizeof(hacking), "High ping (อาจจะมีผลต่อการ Sync ของผู้เล่น) โดนเตะออกจากเซิฟเวอร์");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
			return Kick(playerid);
		}
		case 39: {
			format(hacking, sizeof(hacking), "Dialog hack");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
			return Kick(playerid);
		}
		case 40: {
			format(hacking, sizeof(hacking), "Protection from the sandbox");
			/*foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}*/
		}
		case 41: {
			format(hacking, sizeof(hacking), "Protection against an invalid version");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 42: {
			format(hacking, sizeof(hacking), "Rcon hack");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
			return Kick(playerid);
		}
		case 43: {
			format(hacking, sizeof(hacking), "Tuning crasher");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 44: {
			format(hacking, sizeof(hacking), "Invalid seat crasher");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 45: {
			format(hacking, sizeof(hacking), "Dialog crasher");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
			return Kick(playerid);
		}
		case 46: {
			format(hacking, sizeof(hacking), "Attached object crasher");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
			return Kick(playerid);
		}
		case 47: {
			format(hacking, sizeof(hacking), "Weapon Crasher");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
			return Kick(playerid);
		}
		case 48: {
			format(hacking, sizeof(hacking), "Flood protection connects to one slot");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 49: {
			format(hacking, sizeof(hacking), "flood callback functions");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 50: {
			format(hacking, sizeof(hacking), "flood change seat");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 51: {
			format(hacking, sizeof(hacking), "Ddos");
			foreach(new x : Player) if(LoggedIn[x]){
				if(PlayerData[x][pAdmin] <= 0) continue;
				if(CheckToggleAlert[x] == 0) SendClientMessageEx(x, 0xFF2020AA, "[%s] %s(%d) (IP: %s) > %s", Cheat_Version, ReturnRoleplayName(playerid), playerid, PlayerData[playerid][pLastIP], hacking);
			}
		}
		case 52: format(hacking, sizeof(hacking), "NOP's");
	}
	return 1;
}

forward TimeUnfreeze(playerid);
public TimeUnfreeze(playerid){
	TogglePlayerControllable(playerid, 1);
	return 1;
}

forward PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z);
public PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
    if(IsPlayerConnected(playerid)){
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		tempposx = (oldposx -x);
		tempposy = (oldposy -y);
		tempposz = (oldposz -z);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
			return 1;
	}
	return 0;
}

forward UnfreezeTired(playerid);
public UnfreezeTired(playerid){
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	ClearAnimations(playerid);
	return 1;
}

forward SetAnimationEating(playerid);
public SetAnimationEating(playerid){
	ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
	return 1;
}

LoadTopRank(){
	new query[128];
	mysql_format(dbCon, query, sizeof(query), "SELECT Username, Cash FROM `characters` ORDER BY `Cash` DESC LIMIT 5");
	mysql_tquery(dbCon, query, "TopRank", "i", 1);

	mysql_format(dbCon, query, sizeof(query), "SELECT Username, Level FROM `characters` ORDER BY `Level` DESC LIMIT 5");
	mysql_tquery(dbCon, query, "TopRank", "i", 2);

	mysql_format(dbCon, query, sizeof(query), "SELECT Username, Playerhour FROM `characters` ORDER BY `Playerhour` DESC LIMIT 5");
	mysql_tquery(dbCon, query, "TopRank", "i", 3);

	mysql_format(dbCon, query, sizeof(query), "SELECT Name,Wallet FROM `accounts` ORDER BY `Wallet` DESC LIMIT 5");
	mysql_tquery(dbCon, query, "TopRank", "i", 4);

	mysql_format(dbCon, query, sizeof(query), "SELECT groupName, groupMoney FROM `groups` WHERE `groupType` = '%d' ORDER BY `groupMoney` DESC LIMIT 5", 5);
	mysql_tquery(dbCon, query, "TopRank", "i", 5);

	mysql_format(dbCon, query, sizeof(query), "SELECT Username, BankMoney FROM `characters` ORDER BY `BankMoney` DESC LIMIT 5");
	mysql_tquery(dbCon, query, "TopRank", "i", 6);

	mysql_format(dbCon, query, sizeof(query), "SELECT Username, RedMoney FROM `characters` ORDER BY `RedMoney` DESC LIMIT 5");
	mysql_tquery(dbCon, query, "TopRank", "i", 7);

	mysql_format(dbCon, query, sizeof(query), "SELECT groupName, groupHoldZonePoint FROM `groups` WHERE `groupType` = '%d' ORDER BY `groupHoldZonePoint` DESC LIMIT 5", 5);
	mysql_tquery(dbCon, query, "TopRank", "i", 8);

	mysql_format(dbCon, query, sizeof(query), "SELECT Username, RacingWin FROM `characters` ORDER BY `RacingWin` DESC LIMIT 5");
	mysql_tquery(dbCon, query, "TopRank", "i", 9);

	mysql_format(dbCon, query, sizeof(query), "SELECT Username, RacingLose FROM `characters` ORDER BY `RacingLose` DESC LIMIT 5");
	mysql_tquery(dbCon, query, "TopRank", "i", 10);
	return 1;
}

forward TopRank(threadid);
public TopRank(threadid)
{
	if(cache_num_rows()){
		new string[256];
		new rows = cache_num_rows();
		new name[64], money, level, playerhour, wallet, gmoney, bankmoney, redmoney, gpoint, rw, rl;
		switch(threadid){
			case 1:{

				TopRankMoney[0] = '\0';
				MemSet(TopRankMoney,0,strlen(TopRankMoney));

				for(new i = 0; i < rows; i ++){
					cache_get_value_name(i, "Username", name, 64);
					cache_get_value_name_int(i, "Cash", money);

					format(string, sizeof(string), "{FFFFFF}%d. %s  > %s\n", i+1, name, FormatNumber(money));
					strcat(TopRankMoney, string);
				}
			}
			case 2:{

				TopRankLevel[0] = '\0';
				MemSet(TopRankLevel,0,strlen(TopRankLevel));

				for(new i = 0; i < rows; i ++){
					cache_get_value_name(i, "Username", name, 64);
					cache_get_value_name_int(i, "Level", level);

					format(string, sizeof(string), "{FFFFFF}%d. %s > %s\n", i+1, name, FormatNumberNotMoney(level));
					strcat(TopRankLevel, string);
				}
			}
			case 3:
			{
				TopRankHour[0] = '\0';
				MemSet(TopRankHour,0,strlen(TopRankHour));

				for(new i = 0; i < rows; i ++)
				{
					cache_get_value_name(i, "Username", name, 64);
					cache_get_value_name_int(i, "Playerhour", playerhour);

					format(string, sizeof(string), "{FFFFFF}%d. %s > %s\n", i+1, name, FormatNumberNotMoney(playerhour));
					strcat(TopRankHour, string);
				}
			}
			case 4://ของแอดมิน
			{

				TopRankWallet[0] = '\0';
				MemSet(TopRankWallet,0,strlen(TopRankWallet));

				for(new i = 0; i < rows; i ++)
				{
					cache_get_value_name(i, "Name", name, 64);
					cache_get_value_name_int(i, "Wallet", wallet);

					format(string, sizeof(string), "{FFFFFF}%d. %s > %s\n", i+1, name, FormatNumberNotMoney(wallet));
					strcat(TopRankWallet, string);
				}
			}
			case 5://
			{
				TopRankGangMoney[0] = '\0';
				MemSet(TopRankGangMoney,0,strlen(TopRankGangMoney));

				for(new i = 0; i < rows; i ++)
				{
					cache_get_value_name(i, "groupName", name, 64);
					cache_get_value_name_int(i, "groupMoney", gmoney);

					format(string, sizeof(string), "{FFFFFF}%d. %s > %s\n", i+1, name, FormatNumber(gmoney));
					strcat(TopRankGangMoney, string);
				}
			}
			case 6:
			{
				TopRankBank[0] = '\0';
				MemSet(TopRankBank,0,strlen(TopRankBank));

				for(new i = 0; i < rows; i ++)
				{
					cache_get_value_name(i, "Username", name, 64);
					cache_get_value_name_int(i, "BankMoney", bankmoney);

					format(string, sizeof(string), "{FFFFFF}%d. %s > %s\n", i+1, name, FormatNumber(bankmoney));
					strcat(TopRankBank, string);
				}
			}
			case 7:
			{
				TopRankRedMoney[0] = '\0';
				MemSet(TopRankRedMoney,0,strlen(TopRankRedMoney));

				for(new i = 0; i < rows; i ++)
				{
					cache_get_value_name(i, "Username", name, 64);
					cache_get_value_name_int(i, "RedMoney", redmoney);

					format(string, sizeof(string), "{FFFFFF}%d. %s > %s\n", i+1, name, FormatNumber(redmoney));
					strcat(TopRankRedMoney, string);
				}
			}
			case 8://
			{
				TopRankPointGang[0] = '\0';
				MemSet(TopRankPointGang,0,strlen(TopRankPointGang));

				for(new i = 0; i < rows; i ++)
				{
					cache_get_value_name(i, "groupName", name, 64);
					cache_get_value_name_int(i, "groupHoldZonePoint", gpoint);

					format(string, sizeof(string), "{FFFFFF}%d. %s > %s\n", i+1, name, FormatNumberNotMoney(gpoint));
					strcat(TopRankPointGang, string);
				}
			}
			case 9:{

				TopRankRacingWin[0] = '\0';
				MemSet(TopRankRacingWin,0,strlen(TopRankRacingWin));

				for(new i = 0; i < rows; i ++){
					cache_get_value_name(i, "Username", name, 64);
					cache_get_value_name_int(i, "RacingWin", rw);

					format(string, sizeof(string), "{FFFFFF}%d. %s ชนะทั้งหมด %s ครั้ง\n", i+1, name, FormatNumberNotMoney(rw));
					strcat(TopRankRacingWin, string);
				}
			}
			case 10:{
				TopRankRacingLose[0] = '\0';
				MemSet(TopRankRacingLose,0,strlen(TopRankRacingLose));

				for(new i = 0; i < rows; i ++){
					cache_get_value_name(i, "Username", name, 64);
					cache_get_value_name_int(i, "RacingLose", rl);

					format(string, sizeof(string), "{FFFFFF}%d. %s แพ้ทั้งหมด %s ครั้ง\n", i+1, name, FormatNumberNotMoney(rl));
					strcat(TopRankRacingLose, string);
				}
			}
		}
	}
	return 1;
}

forward AC_SetPlayerHealth(playerid,Float:health);
public AC_SetPlayerHealth(playerid,Float:health){
	PlayerData[playerid][pHP] = health;
	SetPlayerHealth(playerid,health);
    return 1;
}

forward BloodbagUpdate(playerid);
public BloodbagUpdate(playerid){
	new
	    Float:health;

	GetPlayerHealth(playerid, health);

    if (!IsPlayerInAnyVehicle(playerid) && GetPlayerAnimationIndex(playerid) != 1508)
    	ApplyAnimation(playerid, "SWAT", "gnstwall_injurd", 4.0, 1, 0, 0, 0, 0);

	if (health >= 95.0)
	{
	    AC_SetPlayerHealth(playerid, 100.0);

		if (!IsPlayerInAnyVehicle(playerid)) {
			ClearAnimations(playerid);
		}

		TogglePlayerControllable(playerid, 1);
		PlayerData[playerid][pFirstAid] = false;
		KillTimer(PlayerData[playerid][pAidTimer]);
	}
	else if(health < 95.0){
		AC_SetPlayerHealth(playerid, floatadd(health, 4.0));
		PlayerData[playerid][pAidTimer] = SetTimerEx("BloodbagUpdate", 1000, 0, "i", playerid);
	}
	return 1;
}

forward FixHour(hour);
public FixHour(hour)
{
	hour = timeshift+hour;
	if (hour < 0)
	{
		hour = hour+24;
	}
	else if (hour > 23)
	{
		hour = hour-24;
	}
	shifthour = hour;
	return 1;
}