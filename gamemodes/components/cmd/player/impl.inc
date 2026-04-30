#if defined _inc_impl
	#undef _inc_impl
#endif

CMD:stats(playerid, params[]){
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

	ShowStatsForPlayer(playerid, playerid);
	return 1;
}

CMD:ame(playerid, params[])
{
	if(LoggedIn[playerid] == false)
		return 0;

	new
	    string[128];

	if (isnull(params))
	    return SendClientMessage(playerid, -1, "/ame [action]");

	format(string, sizeof(string), "* %s %s", ReturnRoleplayName(playerid), params);
 	SetPlayerChatBubble(playerid, string, COLOR_RP, 30.0, 10000);

 	SendClientMessageEx(playerid, COLOR_RP, "* %s %s", ReturnRoleplayName(playerid), params);
	return 1;
}

CMD:me(playerid, params[])
{
	if(LoggedIn[playerid] == false)
		return 0;
		
	if (isnull(params))
	    return SendClientMessage(playerid, -1, "/me [action]");

	if (strlen(params) > 64) {
	    SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s %.64s", ReturnRoleplayName(playerid), params);
	    SendNearbyMessage(playerid, 30.0, COLOR_RP, "...%s", params[64]);
	}
	else {
	    SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s %s", ReturnRoleplayName(playerid), params);
	}
	return 1;
}

CMD:report(playerid, params[])
{
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");
		
	new string[128];
	if(systemVariables[reportSystem] == 0)
	{
		if(isnull(params))
		{
		    SystemMsg(playerid, "/report [ข้อความ]");
		}
		else
		{
		    if(PlayerData[playerid][pReport] >= 1)
			{
		        SendClientMessage(playerid, COLOR_WHITE, "คุณได้รายงานไปยังผู้ดูแลแล้ว กรุณารอการตอบหลับสักครู่");
		    }
		    else
			{
		        if(strlen(params) >= 64)
				{
		            return SendClientMessage(playerid, COLOR_GREY, "ข้อความการแจ้งรายงานของคุณยาวเกินไป กรุณาให้ตำกว่า 64 ตัวอักษร");
		        }
		        else
				{
				    SendClientMessage(playerid, COLOR_YELLOW, "รายงานของคุณได้ถูกส่งแล้วและอยู่ในคิว");

        			strcpy(PlayerData[playerid][pReportMessage], params, 64);
				    PlayerData[playerid][pReport] = 1;

					format(string, sizeof(string), "มีรายงานหัวข้อใหม่ได้ส่งมาแล้ว พิมพ์ '/reports list' เพื่อดู");
					SendAdminsMessage(1, 0xFF0066AA, string);
			    }
		    }
		}
	}
	else {
	    SendClientMessage(playerid, COLOR_RED, "ระบบการแจ้งรายถูกปิดอยู่ในขณะนี้ กรุณาติดต่อกลับมาภายหลัง");
	}

	return 1;
}

CMD:do(playerid, params[])
{
	if(LoggedIn[playerid] == false)
		return 0;

	if (isnull(params))
	    return SendClientMessage(playerid, -1, "/do [description]");

	if (strlen(params) > 64) {
	    SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %.64s", params);
	    SendNearbyMessage(playerid, 30.0, COLOR_RP, "...%s (( %s ))", params[64], ReturnRoleplayName(playerid));
	}
	else {
	    SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s (( %s ))", params, ReturnRoleplayName(playerid));
	}
	return 1;
}

alias:shout("s", "ตะโกน")
CMD:shout(playerid, params[])
{
	if(LoggedIn[playerid] == false)
		return 0;

	if (isnull(params))
	    return SystemMsg(playerid, "/(s)hout [shout text]");

    if (strlen(params) > 64)
	{
	    SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "[ตะโกน] %s(%d) ตะโกน: %.64s", ReturnRoleplayName(playerid), playerid, params);
	    SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "...%s!", params[64]);
	}
	else {
	    SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "[ตะโกน] %s(%d) ตะโกน: %s!", ReturnRoleplayName(playerid), playerid, params);
	}

	SetPlayerChatBubble(playerid, params, COLOR_WHITE, 20.0, strlen(params) * 500);

	if (!IsPlayerInAnyVehicle(playerid) && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK) {
		if(PlayerData[playerid][pLoopAnim] == 0){
			if(PlayerSitTable[playerid] == -1 && PlayerTable[playerid] == 0){
				ApplyAnimation(playerid,"PED","IDLE_CHAT",4.1, 0, 1, 1, 1, strlen(params) * 100, 1);
			}
		}
			
		//ApplyAnimation(playerid, "GANGS", "prtial_gngtlkA", 4.1, 0, 1, 1, 1, strlen(params) * 100, 1);
	}
	return 1;
}

alias:low("l")
CMD:low(playerid, params[])
{
	if(LoggedIn[playerid] == false)
		return 0;

	if (isnull(params))
	    return SystemMsg(playerid, "/(l)ow [low text]");

    if (strlen(params) > 64)
	{
	    SendNearbyMessage(playerid, 5.0, COLOR_GRAY, "[พูดเบาๆ] %s(%d) พูดเบาๆ: %.64s", ReturnRoleplayName(playerid), playerid, params);
	    SendNearbyMessage(playerid, 5.0, COLOR_GRAY, "...%s", params[64]);
	}
	else
	{
     	SendNearbyMessage(playerid, 5.0, COLOR_GRAY, "[พูดเบาๆ] %s(%d) พูดเบาๆ: %s", ReturnRoleplayName(playerid), playerid, params);
	}

	SetPlayerChatBubble(playerid, params, COLOR_GRAY, 20.0, strlen(params) * 500);

	if (!IsPlayerInAnyVehicle(playerid) && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK) {
		if(PlayerData[playerid][pLoopAnim] == 0){
			if(PlayerSitTable[playerid] == -1 && PlayerTable[playerid] == 0){
				ApplyAnimation(playerid,"PED","IDLE_CHAT",4.1, 0, 1, 1, 1, strlen(params) * 100, 1);
			}
		}
			
		//ApplyAnimation(playerid, "GANGS", "prtial_gngtlkA", 4.1, 0, 1, 1, 1, strlen(params) * 100, 1);
	}
	return 1;
}

CMD:o(playerid, const params[])
{
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

	if(TimeMute[playerid] > 0) return ErrorMsg(playerid, "คุณถูกใบ้อยู่");

	if (isnull(params))
	    return SystemMsg(playerid, "/o [global OOC]");

	if(DelayOOCandTW[playerid] > 0)
		return SendClientMessageEx(playerid, COLOR_RED, "คุณต้องรออีก %d วินาทีถึงจะใช้ได้อีกครั้ง", DelayOOCandTW[playerid]);

	if(GetMoney(playerid) < 50)
		return ErrorMsg(playerid, "คุณมีเงินไม่พอ");

	if(TogOOC == 1)
		return ErrorMsg(playerid, "ช่องทางนี้ถูกปิดอยู่");

	if (BitFlag_Get(g_PlayerFlags[playerid], PLAYER_DISABLE_OOC))
	    return ErrorMsg(playerid, "คุณปิดช่องแชทนี้อยู่");

    if (strlen(params) > 64)
	{
        foreach (new i : Player) if (!BitFlag_Get(g_PlayerFlags[i], PLAYER_DISABLE_OOC)) {
			if(LoggedIn[i]){
				SendClientMessageEx(i, 0xFF8A9EAA, "(( [OOC] %s(%d): %.64s ))", ReturnRoleplayName(playerid), playerid, params);
		    	SendClientMessageEx(i, 0xFF8A9EAA, "...%s ))", params[64]);
			}
		}
	}
	else
	{
        foreach (new i : Player) if (!BitFlag_Get(g_PlayerFlags[i], PLAYER_DISABLE_OOC)) {
			if(LoggedIn[i]){
		    	SendClientMessageEx(i, 0xFF8A9EAA, "(( [OOC] %s(%d): %s ))", ReturnRoleplayName(playerid), playerid, params);
			}
		}
	}
	DelayOOCandTW[playerid] += 40;
	return 1;
}

CMD:help(playerid, const params[]){
	if(LoggedIn[playerid]){
		ShowHelpMenu(playerid);
	}
	return 1;
}

CMD:checkveh(playerid, params[]){
	if(!LoggedIn[playerid]) return 1;
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		new vehicleid = GetPlayerVehicleID(playerid);
		new carid = Car_GetID(vehicleid);
		new Float:vehhp;
		GetVehicleHealth(vehicleid, vehhp);
		if(carid != -1){
			SendClientMessageEx(playerid, -1, "[ข้อมูลยานพาหนะชั่วคราว]: ความทนทาน %.2f HP | น้ำมัน %d เปอร์เซนต์", vehhp / 10, CarData[carid][carFuel]);
		}
	}
	return 1;
}

CMD:tog(playerid, params[]){
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

    if (isnull(params)){
	    SystemMsg(playerid, "/tog [name]");
	    SendClientMessage(playerid, COLOR_GRAY, "[OPTION]: ooc, twitter, vehhud, hp, speaker, all, vad, hud, expx2");
	    return 1;
	}

	if(!strcmp(params, "expx2", true)){
		if(Jdz_Exp_Show[playerid]){
			Jdz_Exp_Hud_Hide(playerid);
		}
		else{
			Jdz_Exp_Hud_Show(playerid);
		}
	}

	if (!strcmp(params, "hud", true)){
		if(Jdz_Hunger_Bar_Show[playerid] && Jdz_Water_Bar_Show[playerid] && Jdz_Stamina_Bar_Show[playerid] && Jdz_Shower_Bar_Show[playerid] && Jdz_Stress_Bar_Show[playerid]){
			Jdz_Hunger_Hide(playerid);
			Jdz_Water_Hide(playerid);
			Jdz_Stamina_Hide(playerid);
			Jdz_Shower_Hide(playerid);
			Jdz_Stress_Hide(playerid);

			SendClientMessage(playerid, -1, "คุณได้ปิดหลอด Status Bar เรียบร้อยแล้ว");
		}
		else{
			Jdz_Hunger_Show(playerid);
			Jdz_Water_Show(playerid);
			Jdz_Stamina_Show(playerid);
			Jdz_Shower_Show(playerid);
			Jdz_Stress_Show(playerid);
			SendClientMessage(playerid, -1, "คุณได้เปิดหลอด Status Bar เรียบร้อยแล้ว");
		}
	}

    if (!strcmp(params, "ooc", true)){
        if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_DISABLE_OOC))
	    {
	        BitFlag_On(g_PlayerFlags[playerid], PLAYER_DISABLE_OOC);
         	SendClientMessage(playerid, 0xFF8A9EAA, "(( คุณได้ปิด OOC แล้ว ))");
		}
		else
		{
  			BitFlag_Off(g_PlayerFlags[playerid], PLAYER_DISABLE_OOC);
  			SendClientMessage(playerid, 0xFF8A9EAA, "(( คุณได้เปิด OOC แล้ว ))");
		}
    }

    if (!strcmp(params, "twitter", true)){
        if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_DISABLE_TWITTER))
	    {
	        BitFlag_On(g_PlayerFlags[playerid], PLAYER_DISABLE_TWITTER);
         	SendClientMessage(playerid, 0x42CBFFAA, "(( คุณได้ปิด Twitter แล้ว ))");
		}
		else
		{
  			BitFlag_Off(g_PlayerFlags[playerid], PLAYER_DISABLE_TWITTER);
  			SendClientMessage(playerid, 0x42CBFFAA, "(( คุณได้เปิด Twitter แล้ว ))");
		}
    }

	if (!strcmp(params, "vad", true)){
        if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_DISABLE_VAD))
	    {
	        BitFlag_On(g_PlayerFlags[playerid], PLAYER_DISABLE_VAD);
         	SendClientMessage(playerid, 0x42CBFFAA, "(( คุณได้ปิด VAD แล้ว ))");
		}
		else
		{
  			BitFlag_Off(g_PlayerFlags[playerid], PLAYER_DISABLE_VAD);
  			SendClientMessage(playerid, 0x42CBFFAA, "(( คุณได้เปิด VAD แล้ว ))");
		}
    }

	if(!strcmp(params, "hp", true)){
		if(BarHpToggle[playerid] == 0){
			BarHpToggle[playerid] = 1;
			EnableHealthBarForPlayer(playerid, false);
			SendClientMessage(playerid, COLOR_YELLOW, "คุณได้ปิดหลอดเลือดเรียบร้อยแล้ว");
		}
		else if(BarHpToggle[playerid] == 1){
			BarHpToggle[playerid] = 0;
			EnableHealthBarForPlayer(playerid, true);
			SendClientMessage(playerid, COLOR_YELLOW, "คุณได้เปิดหลอดเลือดเรียบร้อยแล้ว");
		}
	}

	if(!strcmp(params, "vehhud", true)){

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			return ErrorMsg(playerid, "คุณต้องลงจากรถก่อน");

		if(TogVehSpeedo[playerid] == 0){
			TogVehSpeedo[playerid] = 1;
			SendClientMessage(playerid, 0x42CBFFAA, "(( คุณได้ปิด HUD ของ รถ แล้ว ))");
		}
		else if(TogVehSpeedo[playerid] == 1){
			TogVehSpeedo[playerid] = 0;
			SendClientMessage(playerid, 0x42CBFFAA, "(( คุณได้เปิด HUD ของ รถ แล้ว ))");
		}
	}

	if(!strcmp(params, "speaker", true)){

		if(PlayerTogSpeaker[playerid] == 0){
			PlayerTogSpeaker[playerid] = 1;
			HidePlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
			DestroyPlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
			SendClientMessage(playerid, 0x42CBFFAA, "(( คุณได้ปิด HUD ของ Speaker แล้ว ))");
		}
		else if(PlayerTogSpeaker[playerid] == 1){
			PlayerTogSpeaker[playerid] = 0;
			LoadSpeakerTextDraw(playerid);
			ShowPlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
		}
	}

	if(!strcmp(params, "all", true)){
		if(PlayerTogSpeaker[playerid] == 0){
			PlayerTogSpeaker[playerid] = 1;
			HidePlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
			DestroyPlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
			SendClientMessage(playerid, 0x42CBFFAA, "(( คุณได้ปิด HUD ของ Speaker แล้ว ))");
		}

		if(ToggleLogo[playerid] == 0){
			TextDrawHideForPlayer(playerid, LogoServer[0]);
			TextDrawHideForPlayer(playerid, LogoServer[1]);
			TextDrawHideForPlayer(playerid, LogoServer[2]);
			ToggleLogo[playerid] = 1;
		}
	}
	return 1;
}

CMD:vad(playerid, params[]){
	if(LoggedIn[playerid] == false) return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");
	if(TimeMute[playerid] > 0) return ErrorMsg(playerid, "คุณถูกใบ้อยู่");
	if(PlayerData[playerid][pVip] == 0) return 0;
	if(DelayOOCandTW[playerid] > 0) return SendClientMessageEx(playerid, COLOR_RED, "คุณต้องรออีก %d วินาทีถึงจะใช้ได้อีกครั้ง", DelayOOCandTW[playerid]);
	if(TogVad == 1) return ErrorMsg(playerid, "ช่องทางนี้ถูกปิดอยู่");
	if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติให้ใช้คำสั่งนี้เพราะคุณติดคุกอยู่");
	if (BitFlag_Get(g_PlayerFlags[playerid], PLAYER_DISABLE_VAD)) return ErrorMsg(playerid, "คุณปิดช่องแชทนี้อยู่");

	if(isnull(params)) return SystemMsg(playerid, "/vad [ข้อความ]");
	if(strfind(params, "แอด", true) != -1 || strfind(params, "แอดมิน", true) != -1) return ErrorMsg(playerid, "รูปแบบวลีไม่ถูกต้อง");
	if(strfind(params, "ควย", true) != -1 || strfind(params, "เหี้ย", true) != -1 || strfind(params, "สัส", true) != -1 || strfind(params, "หี", true) != -1) return ErrorMsg(playerid, "พูดจาไม่สุภาพ เดี๋ยวก็ตบปากซะเลย");

	if(PlayerData[playerid][pVip] == 1){
		if (strlen(params) > 64){
			foreach (new i : Player) if(LoggedIn[i] && PlayerData[playerid][pFirstTime] == 0 && !BitFlag_Get(g_PlayerFlags[i], PLAYER_DISABLE_VAD)){
				SendClientMessageEx(i, 0xFF8700AA, "[Bronze Member] {FFB45F}%s(%d) โพสต์ว่า: {FFFFFF}%.64s", ReturnRoleplayName(playerid), playerid, params);
				SendClientMessageEx(i, 0xFF8700AA, "{FFFFFF}...%s", params[64]);
			}
		}else{
			foreach (new i : Player) if(LoggedIn[i] && PlayerData[playerid][pFirstTime] == 0 && !BitFlag_Get(g_PlayerFlags[i], PLAYER_DISABLE_VAD)){
				SendClientMessageEx(i, 0xFF8700AA, "[Bronze Member] {FFB45F}%s(%d) โพสต์ว่า: {FFFFFF}%s", ReturnRoleplayName(playerid), playerid, params);
			}
		}
	}
	else if(PlayerData[playerid][pVip] == 2){
		if (strlen(params) > 64){
			foreach (new i : Player) if(LoggedIn[i] && PlayerData[playerid][pFirstTime] == 0 && !BitFlag_Get(g_PlayerFlags[i], PLAYER_DISABLE_VAD)){
				SendClientMessageEx(i, 0x00FF04AA, "[Silver Member] {6AFF6D}%s(%d) โพสต์ว่า: {FFFFFF}%.64s", ReturnRoleplayName(playerid), playerid, params);
				SendClientMessageEx(i, 0x00FF04AA, "{FFFFFF}...%s", params[64]);
			}
		}else{
			foreach (new i : Player) if(LoggedIn[i] && PlayerData[playerid][pFirstTime] == 0 && !BitFlag_Get(g_PlayerFlags[i], PLAYER_DISABLE_VAD)){
				SendClientMessageEx(i, 0x00FF04AA, "[Silver Member] {6AFF6D}%s(%d) โพสต์ว่า: {FFFFFF}%s", ReturnRoleplayName(playerid), playerid, params);
			}
		}
	}
	else if(PlayerData[playerid][pVip] == 3){
		if (strlen(params) > 64){
			foreach (new i : Player) if(LoggedIn[i] && PlayerData[playerid][pFirstTime] == 0 && !BitFlag_Get(g_PlayerFlags[i], PLAYER_DISABLE_VAD)){
				if(PlayerTextColorGold[playerid] == 0){
					SendClientMessageEx(i, 0xFFC900AA, "[Gold Member] {FFE06E}%s(%d) โพสต์ว่า: {FFFFFF}%.64s", ReturnRoleplayName(playerid), playerid, params);
					SendClientMessageEx(i, 0xFFC900AA, "{FFFFFF}...%s", params[64]);
				}
				else if(PlayerTextColorGold[playerid] == 1){
					SendClientMessageEx(i, 0xFF0000AA, "[Gold Member] {FF6161}%s(%d) โพสต์ว่า: {FFFFFF}%.64s", ReturnRoleplayName(playerid), playerid, params);
					SendClientMessageEx(i, 0xFF0000AA, "{FFFFFF}...%s", params[64]);
				}
				else if(PlayerTextColorGold[playerid] == 2){
					SendClientMessageEx(i, 0xFF7F00AA, "[Gold Member] {FFAF60}%s(%d) โพสต์ว่า: {FFFFFF}%.64s", ReturnRoleplayName(playerid), playerid, params);
					SendClientMessageEx(i, 0xFF7F00AA, "{FFFFFF}...%s", params[64]);
				}
				else if(PlayerTextColorGold[playerid] == 3){
					SendClientMessageEx(i, 0xFFFF00AA, "[Gold Member] {FFFF5C}%s(%d) โพสต์ว่า: {FFFFFF}%.64s", ReturnRoleplayName(playerid), playerid, params);
					SendClientMessageEx(i, 0xFFFF00AA, "{FFFFFF}...%s", params[64]);
				}
				else if(PlayerTextColorGold[playerid] == 4){
					SendClientMessageEx(i, 0x00FF00AA, "[Gold Member] {66FF66}%s(%d) โพสต์ว่า: {FFFFFF}%.64s", ReturnRoleplayName(playerid), playerid, params);
					SendClientMessageEx(i, 0x00FF00AA, "{FFFFFF}...%s", params[64]);
				}
				else if(PlayerTextColorGold[playerid] == 5){
					SendClientMessageEx(i, 0x0000FFAA, "[Gold Member] {5B5BFF}%s(%d) โพสต์ว่า: {FFFFFF}%.64s", ReturnRoleplayName(playerid), playerid, params);
					SendClientMessageEx(i, 0x0000FFAA, "{FFFFFF}...%s", params[64]);
				}
				else if(PlayerTextColorGold[playerid] == 6){
					SendClientMessageEx(i, 0x4B0082AA, "[Gold Member] {925EB9}%s(%d) โพสต์ว่า: {FFFFFF}%.64s", ReturnRoleplayName(playerid), playerid, params);
					SendClientMessageEx(i, 0x4B0082AA, "{FFFFFF}...%s", params[64]);
				}
				else if(PlayerTextColorGold[playerid] == 7){
					SendClientMessageEx(i, 0x9400D3AA, "[Gold Member] {D165FF}%s(%d) โพสต์ว่า: {FFFFFF}%.64s", ReturnRoleplayName(playerid), playerid, params);
					SendClientMessageEx(i, 0x9400D3AA, "{FFFFFF}...%s", params[64]);
				}
			}
		}else{
			foreach (new i : Player) if(LoggedIn[i] && PlayerData[playerid][pFirstTime] == 0 && !BitFlag_Get(g_PlayerFlags[i], PLAYER_DISABLE_VAD)){
				if(PlayerTextColorGold[playerid] == 0){
					SendClientMessageEx(i, 0xFFC900AA, "[Gold Member] {FFE06E}%s(%d) โพสต์ว่า: {FFFFFF}%s", ReturnRoleplayName(playerid), playerid, params);
				}
				else if(PlayerTextColorGold[playerid] == 1){
					SendClientMessageEx(i, 0xFF0000AA, "[Gold Member] {FF6161}%s(%d) โพสต์ว่า: {FFFFFF}%s", ReturnRoleplayName(playerid), playerid, params);
				}
				else if(PlayerTextColorGold[playerid] == 2){
					SendClientMessageEx(i, 0xFF7F00AA, "[Gold Member] {FFAF60}%s(%d) โพสต์ว่า: {FFFFFF}%s", ReturnRoleplayName(playerid), playerid, params);
				}
				else if(PlayerTextColorGold[playerid] == 3){
					SendClientMessageEx(i, 0xFFFF00AA, "[Gold Member] {FFFF5C}%s(%d) โพสต์ว่า: {FFFFFF}%s", ReturnRoleplayName(playerid), playerid, params);
				}
				else if(PlayerTextColorGold[playerid] == 4){
					SendClientMessageEx(i, 0x00FF00AA, "[Gold Member] {66FF66}%s(%d) โพสต์ว่า: {FFFFFF}%s", ReturnRoleplayName(playerid), playerid, params);
				}
				else if(PlayerTextColorGold[playerid] == 5){
					SendClientMessageEx(i, 0x0000FFAA, "[Gold Member] {5B5BFF}%s(%d) โพสต์ว่า: {FFFFFF}%s", ReturnRoleplayName(playerid), playerid, params);
				}
				else if(PlayerTextColorGold[playerid] == 6){
					SendClientMessageEx(i, 0x4B0082AA, "[Gold Member] {925EB9}%s(%d) โพสต์ว่า: {FFFFFF}%s", ReturnRoleplayName(playerid), playerid, params);
				}
				else if(PlayerTextColorGold[playerid] == 7){
					SendClientMessageEx(i, 0x9400D3AA, "[Gold Member] {D165FF}%s(%d) โพสต์ว่า: {FFFFFF}%s", ReturnRoleplayName(playerid), playerid, params);
				}
			}
		}
	}
	DelayOOCandTW[playerid] += 60;
	return 1;
}

CMD:tw(playerid, params[]){
	if(LoggedIn[playerid] == false) return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");
	if(TimeMute[playerid] > 0) return ErrorMsg(playerid, "คุณถูกใบ้อยู่");
	if(DelayOOCandTW[playerid] > 0) return SendClientMessageEx(playerid, COLOR_RED, "คุณต้องรออีก %d วินาทีถึงจะใช้ได้อีกครั้ง", DelayOOCandTW[playerid]);
	if(GetMoney(playerid) < 100) return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะใช้ tw");
	if(TogTwitter == 1)return ErrorMsg(playerid, "ช่องทางนี้ถูกปิดอยู่");
	if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติให้ใช้คำสั่งนี้เพราะคุณติดคุกอยู่");
	if (BitFlag_Get(g_PlayerFlags[playerid], PLAYER_DISABLE_TWITTER)) return ErrorMsg(playerid, "คุณปิดช่องแชทนี้อยู่");

	if (isnull(params)) return SystemMsg(playerid, "/tw [text]");

	if(strfind(params, "แอด", true) != -1 || strfind(params, "แอดมิน", true) != -1) return ErrorMsg(playerid, "รูปแบบวลีไม่ถูกต้อง");

	if(strfind(params, "ควย", true) != -1 || strfind(params, "เหี้ย", true) != -1 || strfind(params, "สัส", true) != -1) return ErrorMsg(playerid, "พูดจาไม่สุภาพ เดี๋ยวก็ตบปากซะเลย");

	if (strlen(params) > 64){
		foreach (new i : Player) if (!BitFlag_Get(g_PlayerFlags[i], PLAYER_DISABLE_TWITTER) && PlayerData[playerid][pFirstTime] == 0) {
			if(LoggedIn[i] && PlayerData[playerid][pFirstTime] == 0){
				SendClientMessageEx(i, 0x42CBFFAA, "[Twitter] {A4E6FF}%s(%d) ได้โพสว่า: {FFFFFF}%.64s", ReturnRoleplayName(playerid), playerid, params);
				SendClientMessageEx(i, 0x42CBFFAA, "{FFFFFF}...%s", params[64]);
			}
		}
	}
	else{
		foreach (new i : Player) if (!BitFlag_Get(g_PlayerFlags[i], PLAYER_DISABLE_TWITTER) && PlayerData[playerid][pFirstTime] == 0) {
			if(LoggedIn[i] && PlayerData[playerid][pFirstTime] == 0)
				SendClientMessageEx(i, 0x42CBFFAA, "[Twitter] {A4E6FF}%s(%d) ได้โพสว่า: {FFFFFF}%s", ReturnRoleplayName(playerid), playerid, params);
		}
	}
	SendClientMessage(playerid, 0x42CBFFAA, "- คุณเสียเงิน $100 ในการโพส Twitter");
	GiveMoney(playerid, -100, "pay tw");
	DelayOOCandTW[playerid] += 120;
	return 1;
}

CMD:time(playerid, params[])
{
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

	new
	    string[128],
		month[12],
		date[6];

	getdate(date[2], date[1], date[0]);
	gettime(date[3], date[4], date[5]);

	switch (date[1]) {
	    case 1: month = "January";
	    case 2: month = "February";
	    case 3: month = "March";
	    case 4: month = "April";
	    case 5: month = "May";
	    case 6: month = "June";
	    case 7: month = "July";
	    case 8: month = "August";
	    case 9: month = "September";
	    case 10: month = "October";
	    case 11: month = "November";
	    case 12: month = "December";
	}
	SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ตรวจสอบเวลา", ReturnRoleplayName(playerid));
	ApplyAnimation(playerid, "COP_AMBIENT", "Coplook_watch", 4.0, 0, 0, 0, 0, 0);
	format(string, sizeof(string), "~g~%s %02d %d~n~~b~%02d:%02d:%02d", month, date[0], date[2], date[3], date[4], date[5]);
	GameTextForPlayer(playerid, string, 6000, 1);
	return 1;
}

CMD:lock(playerid, const params[])
{
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");
		
	new id = -1;
	if ((id = Car_Nearest(playerid)) != -1)
	{
		new
			engine,
			lights,
			alarm,
			doors,
			bonnet,
			boot,
			objective;

		GetVehicleParamsEx(CarData[id][carVehicle], engine, lights, alarm, doors, bonnet, boot, objective);

		if (Car_IsOwner(playerid, id))
		{
			if (!CarData[id][carLocked])
			{
				CarData[id][carLocked] = true;
				Car_Save(id);
				GameTextForPlayer(playerid,"~r~LOCK!",1000,3);
				PlayerPlaySoundEx(playerid, 24600);

				SetVehicleParamsEx(CarData[id][carVehicle], engine, lights, alarm, 1, bonnet, boot, objective);
				if(TogVehSpeedo[playerid] == 0){
					PlayerTextDrawHide(playerid, VehSpeedo[playerid][11]);
					PlayerTextDrawColor(playerid, VehSpeedo[playerid][11], 0xDC0000AA);
					PlayerTextDrawShow(playerid, VehSpeedo[playerid][11]);

					if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
						PlayerTextDrawHide(playerid, VehSpeedo[playerid][11]);
					}
				}
			}
			else
			{
				CarData[id][carLocked] = false;
				Car_Save(id);
				GameTextForPlayer(playerid,"~g~UNLOCK!",1000,3);
				PlayerPlaySoundEx(playerid, 24600);

				SetVehicleParamsEx(CarData[id][carVehicle], engine, lights, alarm, 0, bonnet, boot, objective);
				if(TogVehSpeedo[playerid] == 0){
					PlayerTextDrawHide(playerid, VehSpeedo[playerid][11]);
					PlayerTextDrawColor(playerid, VehSpeedo[playerid][11], -1);
					PlayerTextDrawShow(playerid, VehSpeedo[playerid][11]);

					if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
						PlayerTextDrawHide(playerid, VehSpeedo[playerid][11]);
					}
				}
			}
		}
		else{
			if(PlayerData[playerid][pTemporaryKey] == id){
				if (!CarData[id][carLocked])
				{
					CarData[id][carLocked] = true;
					Car_Save(id);
					GameTextForPlayer(playerid,"~r~LOCK!",1000,3);
					PlayerPlaySoundEx(playerid, 24600);

					SetVehicleParamsEx(CarData[id][carVehicle], engine, lights, alarm, 1, bonnet, boot, objective);
					if(TogVehSpeedo[playerid] == 0){
						PlayerTextDrawHide(playerid, VehSpeedo[playerid][11]);
						PlayerTextDrawColor(playerid, VehSpeedo[playerid][11], 0xDC0000AA);
						PlayerTextDrawShow(playerid, VehSpeedo[playerid][11]);

						if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
							PlayerTextDrawHide(playerid, VehSpeedo[playerid][11]);
						}
					}
				}
				else
				{
					CarData[id][carLocked] = false;
					Car_Save(id);
					GameTextForPlayer(playerid,"~g~UNLOCK!",1000,3);
					PlayerPlaySoundEx(playerid, 24600);

					SetVehicleParamsEx(CarData[id][carVehicle], engine, lights, alarm, 0, bonnet, boot, objective);
					if(TogVehSpeedo[playerid] == 0){
						PlayerTextDrawHide(playerid, VehSpeedo[playerid][11]);
						PlayerTextDrawColor(playerid, VehSpeedo[playerid][11], -1);
						PlayerTextDrawShow(playerid, VehSpeedo[playerid][11]);

						if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
							PlayerTextDrawHide(playerid, VehSpeedo[playerid][11]);
						}
					}
				}
			}
			else ErrorMsg(playerid, "คุณไม่มีกุญแจสำหรับยานพาหนะนี้");
		}
	}
    return 1;
}

CMD:lights(playerid, const params[])
{
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		new vehicleid = GetPlayerVehicleID(playerid);

		if (!IsEngineVehicle(vehicleid))
			return ErrorMsg(playerid, "คุณไม่ได้อยู่ในยานพาหนะ");

		switch (GetLightStatus(vehicleid))
		{
			case false:
			{
				SetLightStatus(vehicleid, true);
				if(TogVehSpeedo[playerid] == 0){
					PlayerTextDrawHide(playerid, VehSpeedo[playerid][10]);
					PlayerTextDrawColor(playerid, VehSpeedo[playerid][10], 0x0AE600AA);
					PlayerTextDrawShow(playerid, VehSpeedo[playerid][10]);
				}
			}
			case true:
			{
				SetLightStatus(vehicleid, false);
				if(TogVehSpeedo[playerid] == 0){
					PlayerTextDrawHide(playerid, VehSpeedo[playerid][10]);
					PlayerTextDrawColor(playerid, VehSpeedo[playerid][10], -1);
					PlayerTextDrawShow(playerid, VehSpeedo[playerid][10]);
				}
			}
		}
	}
	return 1;
}

CMD:windows(playerid, const params[]){
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT){
		new idcar = GetPlayerVehicleID(playerid);
		if (!IsWindowedVehicle(idcar)) return SendClientMessage(playerid, COLOR_GREY, "คุณไม่ได้อยู่ในยานพาหนะใด ๆ ที่มีหน้าต่าง");

		Dialog_ShowEasy(playerid, WindowsCar, DIALOG_STYLE_LIST, "หน้าต่างยานพาหนะ", "กระจกคนขับ\nกระจกหน้าขวา\nกระจกหลังซ้าย\nกระจกหลังขวา", "เลือก", "ยกเลิก");
	}
	return 1;
}

Dialog:WindowsCar(playerid, response, listitem, inputtext[]){
	if(!response) return 1;
	if(response){

		new vehicleid = GetPlayerVehicleID(playerid);
		new wdriver, wpassenger, wbackleft, wbackright;
		GetVehicleParamsCarWindows(vehicleid, wdriver, wpassenger, wbackleft, wbackright);

		if(listitem == 0){
			if(wdriver == VEHICLE_PARAMS_OFF)
		    {
				SendNearbyMessage(playerid, 30.0, COLOR_RP, "หน้าต่างของรถ %s ฝั่งคนขับถูกปิด (( %s ))", ReturnVehicleName(vehicleid), ReturnRoleplayName(playerid));
				SetVehicleParamsCarWindows(vehicleid, 1, wpassenger, wbackleft, wbackright);
			}
			else if(wdriver == VEHICLE_PARAMS_ON || wdriver == VEHICLE_PARAMS_UNSET)
			{
				SendNearbyMessage(playerid, 30.0, COLOR_RP, "หน้าต่างของรถ %s ฝั่งคนขับถูกเปิด (( %s ))", ReturnVehicleName(vehicleid), ReturnRoleplayName(playerid));
				SetVehicleParamsCarWindows(vehicleid, 0, wpassenger, wbackleft, wbackright);
			}
		}
		if(listitem == 1){
			if(wpassenger == VEHICLE_PARAMS_OFF)
		    {
				SendNearbyMessage(playerid, 30.0, COLOR_RP, "หน้าต่างของรถ %s ฝั่งผู้โดยสารถูกปิด (( %s ))", ReturnVehicleName(vehicleid), ReturnRoleplayName(playerid));
				SetVehicleParamsCarWindows(vehicleid, wdriver, 1, wbackleft, wbackright);
			}
			else if(wpassenger == VEHICLE_PARAMS_ON || wpassenger == VEHICLE_PARAMS_UNSET)
			{
				SendNearbyMessage(playerid, 30.0, COLOR_RP, "หน้าต่างของรถ %s ฝั่งผู้โดยสารถูกเปิด (( %s ))", ReturnVehicleName(vehicleid), ReturnRoleplayName(playerid));
				SetVehicleParamsCarWindows(vehicleid, wdriver, 0, wbackleft, wbackright);
			}
		}
		if(listitem == 2){
			if(wbackleft == VEHICLE_PARAMS_OFF)
		    {
				SendNearbyMessage(playerid, 30.0, COLOR_RP, "หน้าต่างหลังซ้ายของรถ %s ถูกปิด (( %s ))", ReturnVehicleName(vehicleid), ReturnRoleplayName(playerid));
				SetVehicleParamsCarWindows(vehicleid, wdriver, wpassenger, 1, wbackright);
			}
			else if(wbackleft == VEHICLE_PARAMS_ON || wbackleft == VEHICLE_PARAMS_UNSET)
			{
				SendNearbyMessage(playerid, 30.0, COLOR_RP, "หน้าต่างหลังซ้ายของรถ %s ถูกเปิด (( %s ))", ReturnVehicleName(vehicleid), ReturnRoleplayName(playerid));
				SetVehicleParamsCarWindows(vehicleid, wdriver, wpassenger, 0, wbackright);
			}
		}
		if(listitem == 3){
			if(wbackright == VEHICLE_PARAMS_OFF)
		    {
				SendNearbyMessage(playerid, 30.0, COLOR_RP, "หน้าต่างหลังขวาของรถ %s ถูกปิด (( %s ))", ReturnVehicleName(vehicleid), ReturnRoleplayName(playerid));
				SetVehicleParamsCarWindows(vehicleid, wdriver, wpassenger, wbackleft, 1);
			}
			else if(wbackright == VEHICLE_PARAMS_ON || wbackright == VEHICLE_PARAMS_UNSET)
			{
				SendNearbyMessage(playerid, 30.0, COLOR_RP, "หน้าต่างหลังขวาของรถ %s ถูกเปิด (( %s ))", ReturnVehicleName(vehicleid), ReturnRoleplayName(playerid));
				SetVehicleParamsCarWindows(vehicleid, wdriver, wpassenger, wbackleft, 0);
			}
		}
	}
	return 1;
}

alias:givetempkey("gtk")
CMD:givetempkey(playerid, params[]){
	if(!LoggedIn[playerid]) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณจำเป็นต้องเป็นคนขับ");

	new userid;
	if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/givetempkey [playerid]");
	if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
	if(!LoggedIn[userid]) return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
	if(IsPlayerNearPlayer(playerid, userid, 5.0)){
		new vehicleid = GetPlayerVehicleID(playerid);
		new carid = Car_GetID(vehicleid);

		if(carid != -1){
			if(Car_IsOwner(playerid, carid) && CarData[carid][carVehicle] == vehicleid){
				PlayerData[userid][pTemporaryKey] = carid;
				SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ให้กุญแจชั่วคราวของยานพาหนะ %s กับ %s เรียบร้อยแล้ว", ReturnVehicleName(CarData[carid][carVehicle]), ReturnRoleplayName(userid));
				SendClientMessageEx(userid, COLOR_YELLOW, "- %s ได้ให้กุญแจชั่วคราวของยานพาหนะ %s กับคุณแล้ว", ReturnRoleplayName(playerid), ReturnVehicleName(CarData[carid][carVehicle]));
			}
			else return ErrorMsg(playerid, "ยานพาหนะนี้คุณไม่ได้เป็นเจ้าของ");
		}
		else return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
	}
	else return ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้น");
	return 1;
}

alias:engine("/en")
CMD:engine(playerid, const params[])
{
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		new vehicleid = GetPlayerVehicleID(playerid);

		new Float:fHealth;

		GetVehicleHealth(vehicleid, fHealth);

		if(fHealth <= 310)
			return ErrorMsg(playerid, "ยานพาหนะของคุณพังไม่สามารถเริ่มทำงานเครื่องยนต์ได้");

		new carid = Car_GetID(vehicleid);
		new EngineStatus = GetEngineStatus(vehicleid);

		if(isABikeVehicle(vehicleid))
			return 1;

		if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(carid > -1){

				if(CarData[carid][carFuel] <= 0) return ErrorMsg(playerid, "รถคันนี้ไม่มีน้ำมันอยู่ในถังเลย");

				if(CarData[carid][carOwner] > 0){

					switch (EngineStatus)
					{
						case false:
						{
							SetEngineStatus(vehicleid, true);
							SetLightStatus(vehicleid, true);
							SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s เริ่มทำงานเครื่องยนต์", ReturnRoleplayName(playerid));
							if(TogVehSpeedo[playerid] == 0){

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][15]);

								PlayerTextDrawShow(playerid, VehSpeedo[playerid][2]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][3]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][4]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][5]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][6]);
								ShowPlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
								ShowPlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][9]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][9], 0x0AE600AA);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][9]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][10]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][10], 0x0AE600AA);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][10]);
							}
						}
						case true:
						{
							SetEngineStatus(vehicleid, false);
							SetLightStatus(vehicleid, false);
							SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s หยุดเครื่องยนต์", ReturnRoleplayName(playerid));
							if(TogVehSpeedo[playerid] == 0){

								PlayerTextDrawShow(playerid, VehSpeedo[playerid][15]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][2]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][3]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][4]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][5]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][6]);
								HidePlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
								HidePlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][9]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][9], -1);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][9]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][10]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][10], -1);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][10]);
							}
						}
					}
				}
				else{
					switch (EngineStatus)
					{
						case false:
						{
							SetEngineStatus(vehicleid, true);
							SetLightStatus(vehicleid, true);
							SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s เริ่มทำงานเครื่องยนต์", ReturnRoleplayName(playerid));
							if(TogVehSpeedo[playerid] == 0){
								
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][15]);

								PlayerTextDrawShow(playerid, VehSpeedo[playerid][2]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][3]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][4]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][5]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][6]);
								ShowPlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
								ShowPlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][9]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][9], 0x0AE600AA);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][9]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][10]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][10], 0x0AE600AA);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][10]);
							}
						}
						case true:
						{
							SetEngineStatus(vehicleid, false);
							SetLightStatus(vehicleid, false);
							SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s หยุดเครื่องยนต์", ReturnRoleplayName(playerid));
							if(TogVehSpeedo[playerid] == 0){

								PlayerTextDrawShow(playerid, VehSpeedo[playerid][15]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][2]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][3]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][4]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][5]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][6]);
								HidePlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
								HidePlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][9]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][9], -1);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][9]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][10]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][10], -1);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][10]);
							}
						}
					}
				}
				return 1;
			}
			else if(carid == -1){
				if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				{
					switch (EngineStatus)
					{
						case false:
						{
							SetEngineStatus(vehicleid, true);
							SetLightStatus(vehicleid, true);
							SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s เริ่มทำงานเครื่องยนต์", ReturnRoleplayName(playerid));
							if(TogVehSpeedo[playerid] == 0){

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][15]);

								PlayerTextDrawShow(playerid, VehSpeedo[playerid][2]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][3]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][4]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][5]);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][6]);
								ShowPlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
								ShowPlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][9]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][9], 0x0AE600AA);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][9]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][10]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][10], 0x0AE600AA);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][10]);
							}
						}
						case true:
						{
							SetEngineStatus(vehicleid, false);
							SetLightStatus(vehicleid, false);
							SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s หยุดเครื่องยนต์", ReturnRoleplayName(playerid));
							if(TogVehSpeedo[playerid] == 0){

								PlayerTextDrawShow(playerid, VehSpeedo[playerid][15]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][2]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][3]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][4]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][5]);
								PlayerTextDrawHide(playerid, VehSpeedo[playerid][6]);
								HidePlayerProgressBar(playerid, VehSpeedoBar[playerid][0]);
								HidePlayerProgressBar(playerid, VehSpeedoBar[playerid][1]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][9]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][9], -1);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][9]);

								PlayerTextDrawHide(playerid, VehSpeedo[playerid][10]);
								PlayerTextDrawColor(playerid, VehSpeedo[playerid][10], -1);
								PlayerTextDrawShow(playerid, VehSpeedo[playerid][10]);
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

CMD:b(playerid, params[]){
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

    new str[200];
    if(sscanf(params, "s[200]", str)) return SendClientMessage(playerid, COLOR_GRAY, "/b [message]");

	if (strlen(params) > 64)
	{
		if(AdminDuty[playerid] == 1){
			SendNearbyMessage(playerid, 30.0, 0x36EF00AA, "(( %s(%d): %s ", PlayerData[playerid][pAdminName], playerid, params);
			SendNearbyMessage(playerid, 30.0, 0x36EF00AA, "...%s ))", params[64]);
			format(str, sizeof str, "(( %s ))", params);
			SetPlayerChatBubble(playerid, str, 0x04FF00FF, 30.0, strlen(str) * 500);
		}
		else{
			SendNearbyMessage(playerid, 30.0, -1, "(( %s(%d): %s ", ReturnRoleplayName(playerid), playerid, params);
			SendNearbyMessage(playerid, 30.0, -1, "...%s ))", params[64]);
			format(str, sizeof str, "(( %s ))", params);
			SetPlayerChatBubble(playerid, str, COLOR_WHITE, 30.0, strlen(str) * 500);
		}
	}
	else
	{
		if(AdminDuty[playerid] == 1){
			SendNearbyMessage(playerid, 30.0, 0x36EF00AA, "(( %s: %s ))", PlayerData[playerid][pAdminName], params);
			format(str, sizeof str, "(( %s ))", params);
			SetPlayerChatBubble(playerid, str, 0x04FF00FF, 30.0, strlen(str) * 500);
		}
		else{
			SendNearbyMessage(playerid, 30.0, -1, "(( %s: %s ))", ReturnRoleplayName(playerid), params);
			format(str, sizeof str, "(( %s ))", params);
			SetPlayerChatBubble(playerid, str, COLOR_WHITE, 30.0, strlen(str) * 500);
		}
	}
    return 1;
}

CMD:toglogo(playerid, params[]){
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

	if(ToggleLogo[playerid] == 0){
		TextDrawHideForPlayer(playerid, LogoServer[0]);
		TextDrawHideForPlayer(playerid, LogoServer[1]);
		TextDrawHideForPlayer(playerid, LogoServer[2]);
		ToggleLogo[playerid] = 1;
	}
	else if(ToggleLogo[playerid] == 1){
		TextDrawShowForPlayer(playerid, LogoServer[0]);
		TextDrawShowForPlayer(playerid, LogoServer[1]);
		TextDrawShowForPlayer(playerid, LogoServer[2]);
		ToggleLogo[playerid] = 0;
	}
	return 1;
}

ClearJob(playerid){
	if(PlayerData[playerid][pJob] == BUILDJOB){
		SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
	}

	if(PlayerData[playerid][pJob] == COWJOB){
		SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
	}

	if(PlayerData[playerid][pJob] == ENGJOB){
		SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
		RemoveAttachedObject(playerid, 8);
	}

	ResetFarmerJob(playerid);

	ResetBuildJob(playerid);

	ResetGasJob(playerid);

	ResetCowJob(playerid);
	if(PlayerUseKnife[playerid] == 1){
		PlayerUseKnife[playerid] = 0;
		RemoveAttachedObject(playerid, 8);
	}

	ResetEngjob(playerid);

	ResetCutWoodJob(playerid);

	EnterCheckPointJob[playerid] = 0;
	DisablePlayerCheckpoint(playerid);
	PlayerData[playerid][pJob] = 0;

	ResetJellyFish(playerid);
	ResetWeaponDealerJob(playerid);

	ResetGarbageJob(playerid);

	ResetRubberJob(playerid);

	ResetClothJob(playerid);
	ResetSeekerJob(playerid);
	ResetGardener(playerid);
	ResetOilJob(playerid);
	ResetShellJob(playerid);
	ResetOrangeJob(playerid);
	Reset_SharkJob(playerid);
	Reset_PizzaJob(playerid);
	ResetPlayerDeliverOilJob(playerid);
	return 1;
}

CMD:acarry(playerid, params[]){
	if(PlayerData[playerid][pAdmin] >= 1){
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
	}
	return 1;
}

alias:quitjob("ออกงาน")
CMD:quitjob(playerid, params[]){
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

	if(PlayerEnterWarFlag[playerid]) return 1;

	if(PlayerData[playerid][pJob] == 0)
		return ErrorMsg(playerid, "คุณไม่มีงานที่จะออก");

	ClearJob(playerid);

	SendClientMessage(playerid, COLOR_GRAY, ">> คุณได้ออกจากงานเรียบร้อยแล้ว <<");
	return 1;
}

CMD:discp(playerid, params[]){
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

	if(StartBuildJob[playerid] == 0){
		PlayerEnterCheckPoint[playerid] = 0;
		EnterCheckPointJob[playerid] = 0;
		DisablePlayerCheckpoint(playerid);
		ClearGPS(playerid);
	}
	return 1;
}

CMD:gps(playerid, const params[]){
	if(LoggedIn[playerid] == false)
		return 0;

	new string[1024];

	if(CheckEnterCutWood[playerid] == 1 || CheckEnterMine[playerid] == 1 || ChangeSkinEngJob[playerid] == 1 || CheckEnterPointEngJob[playerid] == 1 || CheckEnterPointGarbageJob[playerid] == 1
	||	StartChangeSkinBuildJob[playerid] == 1 || StartGardenerJob[playerid] == 1 || GotoSendBox[playerid] || PlayerStartDeliverOil[playerid] || PlayerGetOilDeliver[playerid])
		return ErrorMsg(playerid, "คุณไม่สามารถใช้ได้ตอนนี้");

	format(string, sizeof(string), "- ค้นหา อาชีพ\n- ค้นหา อาชีพเสริม\n- ค้นหา ตลาดกลาง LS\n- ค้นหา จุดหาคราฟไอเท็ม\n- ค้นหา การาจ เก็บ/เรียกรถ\n- ค้นหา ร้านอาหาร\n- ค้นหา จุดกู้คืนยานพาหนะ\n- ค้นหา ร้านขายรถ\
	\n- ค้นหา จุดซื้อใบประกันยานพาหนะ\n- ค้นหา ตลาดกลาง SF\n- ค้นหา จุดกู้คืนเรือ\n- ค้นหา จุดรับเควส WO:RP\n- ค้นหา จุดทำใบขับขี่");
	Dialog_ShowEasy(playerid, GpsMenu, DIALOG_STYLE_LIST, "GPS", string, "ตกลง", "ยกเลิก");
	return 1;
}

CMD:market(playerid, const params[]){
	if(!LoggedIn[playerid])
		return 1;

	if(PlayerToPoint(3.0, playerid, 1134.0571,-1471.0575,15.7799) || PlayerToPoint(2.0, playerid, -2273.9236,527.0815,35.0156)){
		ShowPlayerDialogMarket(playerid);
	}
	return 1;
}

CMD:blackmarket(playerid, const params[]){
	if(!LoggedIn[playerid])
		return 1;

	if(PlayerToPoint(3.0, playerid, -774.6674,1627.3953,27.1172)){
		ShowPlayerDialogBlackMarket(playerid);
	}
	return 1;
}

CMD:checkgov(playerid, params[]){

	if(!LoggedIn[playerid]) return 1;

	if(PlayerData[playerid][pAdmin] <= 0) return 1;

	new countpolice, countmedic, coutmechanic;
	foreach(new i : Player){
		if(!LoggedIn[i]) continue;

		if(GetGroupType(i) == GROUP_POLICE && BitFlag_Get(g_PlayerFlags[i], PLAYER_ONDUTY))
			countpolice++;
		if(GetGroupType(i) == GROUP_MEDIC)
			countmedic++;
		if(GetGroupType(i) == GROUP_MECHANIC)
			coutmechanic++;
	}
	SendClientMessageToAllEx(COLOR_SERVER, "| [Government-Online]: {FFFFFF}ตำรวจ: %d คน | แพทย์/หมอ: %d คน | ช่างยนต์: %d คน", countpolice, countmedic, coutmechanic);
	return 1;
}

CMD:f(playerid, params[])
{
    if(!LoggedIn[playerid])
        return ErrorMsg(playerid, "คุณไม่ได้ล็อคอิน");

    new groupid = PlayerData[playerid][pGroup];

    if (groupid == -1)
        return SystemMsg(playerid, "คุณต้องเป็นสมาชิกของฝ่ายหรือกลุ่ม");

    if (isnull(params))
        return SystemMsg(playerid, "/(f)ac [message]");

	if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติให้ใช้คำสั่งนี้เพราะคุณติดคุกอยู่");

    if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_MEDIC || GetGroupType(playerid) == GROUP_GOV || GetGroupType(playerid) == GROUP_GANG || GetGroupType(playerid) == GROUP_MECHANIC
	|| GetGroupType(playerid) == GROUP_NATIONAL)
    {
        SendFactionMessage(groupid, 0x00AAFFAA, "(( (%d) %s %s: %s ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid), params);
    }
    return 1;
}

CMD:gov(playerid, params[]){
	new string[256];
	if(!LoggedIn[playerid]) return 1;
	if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_MEDIC || GetGroupType(playerid) == GROUP_NATIONAL || GetGroupType(playerid) == GROUP_MECHANIC || GetGroupType(playerid) == GROUP_NEWS){
		if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]-1) return ErrorMsg(playerid, "คุณไม่มีอำนาจในการใช้คำสั่งนี้");

		if(isnull(params)) return SystemMsg(playerid, "/gov [message]");

		new groupid = PlayerData[playerid][pGroup];
		if(groupid == -1) return 1;
		format(string, sizeof(string), "|---------------[ ข่าวสารจาก %s ]---------------|", Group_GetName(playerid));
		SendClientMessageToAll(GroupData[groupid][groupColor], string);
		SendClientMessageToAllEx(COLOR_WHITE, "* %s %s: %s", Group_GetRank(playerid), ReturnRoleplayName(playerid), params);
	}
	return 1;
}

CMD:dischm(playerid, params[]){
	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

	new string[256];
	if(GetGroupType(playerid) == GROUP_MEDIC){
		new groupid = PlayerData[playerid][pGroup];
		if(MedicToMe[playerid] != -1 && groupid != -1){
			SendFactionMessage(groupid, COLOR_RED, "(( (%d) %s %s: ได้ทำการยกเลิกการขอความช่วยของ %s(%d) เรียบร้อยแล้ว, เปลี่ยน ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid), ReturnRoleplayName(MedicToMe[playerid]), MedicToMe[playerid]);
			format(string, sizeof(string), "*[Radio] %s: ได้ทำการยกเลิกการขอความช่วยของ %s(%d) เรียบร้อยแล้ว", ReturnRoleplayName(playerid), ReturnRoleplayName(MedicToMe[MedicToMe[playerid]]), MedicToMe[MedicToMe[playerid]]);
			SetPlayerChatBubble(playerid, string, COLOR_RP, 30.0, 10000);
			SendClientMessageEx(MedicToMe[playerid], COLOR_YELLOW, "- หน่วยแพทย์ %s ได้ทำการยกเลิกความช่วยเหลือของคุณแล้ว", ReturnRoleplayName(playerid));
			MedicToMe[MedicToMe[playerid]] = -1;
			MedicToMe[playerid] = -1;
			DisablePlayerCheckpoint(playerid);
		}
	}
	return 1;
}

CMD:chm(playerid, params[]){

	if(LoggedIn[playerid] == false)
		return ErrorMsg(playerid, "คุณยังไม่ได้เข้าสู่ระบบ");

	if(CheckPlayerNotSendGps(playerid) != -1) return ErrorMsg(playerid, "คุณไม่สามารถใช้ได้ตอนนี้");

	new userid;
	if(sscanf(params, "u", userid))
		return SystemMsg(playerid, "/chm [playerid]");

	if(userid == INVALID_PLAYER_ID)
		return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");

	if(GetGroupType(playerid) == GROUP_MEDIC){

		new groupid = PlayerData[playerid][pGroup];

		new string[128];

		new Float:x, Float:y, Float:z;
		if(userid != INVALID_PLAYER_ID && LoggedIn[userid]){
			if(MedicToMe[userid] != -1) return ErrorMsg(playerid, "คำร้องขอช่วยเหลือนั้นถูกรับไปแล้ว");
			if(CallMedic[userid] == 1){
				GetPlayerPos(userid, x, y, z);
				SetPlayerCheckpoint(playerid, x, y, z, 5.0);
				CallMedic[userid] = 0;
				MedicToMe[userid] = playerid;
				MedicToMe[playerid] = userid;
				PlayerEnterCheckPointMedic[playerid] = true;
				SendFactionMessage(groupid, COLOR_RADIO, "(( (%d) %s %s: ได้ตอบรับความช่วยเหลือของ %s(%d) เรียบร้อยแล้ว, เปลี่ยน ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid), ReturnRoleplayName(userid), userid);
				format(string, sizeof(string), "*[Radio] %s: ได้ตอบรับความช่วยเหลือของ %s(%d) เรียบร้อยแล้ว", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), userid);
				SetPlayerChatBubble(playerid, string, COLOR_RP, 30.0, 10000);
				SendClientMessage(userid, COLOR_YELLOW, ">> หน่วย แพทย์/หมอ ได้ตอบรับคำขอช่วยเหลือของคุณแล้ว");
			}
			else return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เรียกหน่วยแพทย์");
			SendClientMessageEx(playerid, COLOR_ORANGE, "- คุณได้เปิดระบบค้นหาไปยัง %s(%d) เรียบร้อยแล้ว", ReturnRoleplayName(userid), userid);
			SendClientMessage(playerid, COLOR_YELLOW, "- หากคุณต้องการยกเลิกให้ใช้ '/dischm'");
		}
	}
	
	if(GetGroupType(playerid) == GROUP_MECHANIC){
		if(PlayerData[userid][pCanMechanicChm] == 0)
			return ErrorMsg(playerid, "ผู้เล่นคนนั้นยังไม่ได้เรียกใช้บริการ");

		new Float:x, Float:y, Float:z;

		if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");

		if(userid != INVALID_PLAYER_ID && LoggedIn[userid]){
			GetPlayerPos(userid, x, y, z);
			PlayerEnterCheckPoint[playerid] = 1;
			SetPlayerCheckpoint(playerid, x, y, z, 5.0);
			if(PlayerData[userid][pCanMechanicChm] == 1){
				PlayerData[userid][pCanMechanicChm] = 0;
				SendClientMessage(userid, COLOR_YELLOW, ">> ช่างยนต์ได้ตอบรับการเรียกใช้บริการของคุณแล้ว");
			}
			SendClientMessageEx(playerid, COLOR_ORANGE, "- คุณได้เปิดระบบค้นหาไปยัง %s(%d) เรียบร้อยแล้ว", ReturnRoleplayName(userid), userid);
		}
	}
	return 1;
}

CMD:r(playerid, params[])
{
    if(!LoggedIn[playerid])
        return 1;

    new
        string[128];

    new groupid = PlayerData[playerid][pGroup];

    if (groupid == -1)
        return SystemMsg(playerid, "คุณต้องเป็นสมาชิกของฝ่ายหรือกลุ่ม");

    if (GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_MEDIC && GetGroupType(playerid) != GROUP_GOV && GetGroupType(playerid) != GROUP_NATIONAL)
        return SendClientMessage(playerid, -1, "คุณจะต้องเป็นผู้ปฏิบัติงานข้าราชการพลเรือน");

    if (isnull(params))
        return SystemMsg(playerid, "/r [message]");

    if(GetGroupType(playerid) == GROUP_POLICE || GetGroupType(playerid) == GROUP_MEDIC || GetGroupType(playerid) == GROUP_GOV || GetGroupType(playerid) == GROUP_NATIONAL)
    {
        SendFactionMessage(groupid, COLOR_RADIO, "(( (%d) %s %s: %s, เปลี่ยน ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid), params);
        format(string, sizeof(string), "*[Radio] %s %s", ReturnRoleplayName(playerid), params);
        SetPlayerChatBubble(playerid, string, COLOR_RP, 30.0, 10000);
    }
    return 1;
}

CMD:d(playerid, params[])
{
    if(!LoggedIn[playerid])
        return 1;

    new
        string[128];

    if (GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_MEDIC && GetGroupType(playerid) != GROUP_GOV && GetGroupType(playerid) != GROUP_NATIONAL)
        return SendClientMessage(playerid, -1, "คุณจะต้องเป็นผู้ปฏิบัติงานข้าราชการพลเรือน");

    if (isnull(params))
        return SendClientMessage(playerid, -1, "/d [department radio]");

    for (new i = 0; i != MAX_GROUPS; i ++) if(GroupData[i][groupExists]){
		if (GroupData[i][groupType] == GROUP_POLICE || GroupData[i][groupType] == GROUP_MEDIC || GroupData[i][groupType] == GROUP_GOV || GroupData[i][groupType] == GROUP_NATIONAL) {
			SendFactionMessage(i, COLOR_DEPARTMENT, "** [%s] %s %s: %s **", GetInitials(Group_GetName(playerid)), Group_GetRank(playerid), ReturnRoleplayName(playerid), params);

			format(string, sizeof(string), "*[Radio] %s %s", ReturnRoleplayName(playerid), params);
			SetPlayerChatBubble(playerid, string, COLOR_RP, 30.0, 10000);
		}
    }
    return 1;
}

CMD:vip(playerid, params[]){

	if(!LoggedIn[playerid])
        return 0;

	if(PlayerData[playerid][pVip] >= 1){
		ShowMenuVip(playerid);
	}
	return 1;
}

CMD:atune(playerid, params[]){
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return ErrorMsg(playerid, "คุณจะต้องขับรถอยู่");

	Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
	return 1;
}

//

stock IsACruiser(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
	    case 523, 427, 490, 528, 596..599, 601: return 1;
	}
	return 0;
}

CMD:carsign(playerid, params[]){
	new string[32];
	if(!IsPlayerInAnyVehicle(playerid)) return ErrorMsg(playerid, "คุณไม่ได้อยู่ในยานพาหนะ");
	
	if (GetGroupType(playerid) != GROUP_POLICE)
		return ErrorMsg(playerid, "คุณจะต้องเป็นเจ้าหน้าที่ตำรวจ");

	if(sscanf(params, "s[32]", string)) return ErrorMsg(playerid, "คุณต้องป้อนสัญญาณเรียกขาน");

	new vehicleid = GetPlayerVehicleID(playerid);
	if(vehiclecallsign[vehicleid] == 0){
		vehicle3Dtext[vehicleid] = Create3DTextLabel(string, COLOR_WHITE, 0.0, 0.0, 0.0, 50.0, 0, 1);
		Attach3DTextLabelToVehicle(vehicle3Dtext[vehicleid], vehicleid, -0.7, -1.9, -0.3);
		vehiclecallsign[vehicleid] = 1;
		SendClientMessage(playerid, COLOR_RED, "ใช้ '/remove_carsign' ในการลบ");
	}
	return 1;
}

CMD:remove_carsign(playerid, params[]){
	if(!IsPlayerInAnyVehicle(playerid)) return ErrorMsg(playerid, "คุณไม่ได้อยู่ในยานพาหนะ");
	if (GetGroupType(playerid) != GROUP_POLICE) return ErrorMsg(playerid, "คุณจะต้องเป็นเจ้าหน้าที่ตำรวจ");
	new vehicleid = GetPlayerVehicleID(playerid);
	if(IsValid3DTextLabel(vehicle3Dtext[vehicleid])) {
		Delete3DTextLabel(vehicle3Dtext[vehicleid]);
		vehiclecallsign[vehicleid] = 0;
		SendClientMessage(playerid, COLOR_RED, "สัญญาณเรียกขานถูกลบ");
	}
	return 1;
}

CMD:takeagencycard(playerid, params[]){
	if(!LoggedIn[playerid]) return 1;
	new
        userid;
    if (PlayerData[playerid][pGroup] == -1)
        return SendClientMessage(playerid, -1, "คุณต้องเป็นสมาชิกของฝ่ายหรือกลุ่ม");

    if (PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks])
        return SendClientMessageEx(playerid, -1, "คุณต้องมียศอย่างต่ำ %d", GroupData[PlayerData[playerid][pGroup]][groupRanks]);

    if (sscanf(params, "u", userid))
        return SystemMsg(playerid, "/takeagencycard [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นได้ตัดการเชื่อมต่อแล้ว");

    if (PlayerData[userid][pGroup] == PlayerData[playerid][pGroup])
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นเป็นส่วนหนึ่งของฝ่ายหรือกลุ่มคุณแล้ว");

    if (PlayerData[userid][pGroup] != -1)
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นเป็นส่วนหนึ่งของฝ่ายหรือกลุ่มอื่นอยู่แล้ว");

    if(PlayerInventory_AllCount(userid, "Agency Card") <= 0)
		return ErrorMsg(playerid, "ผู้เล่นนั้นไม่มีบัตรประจำตัวหน่วยงาน");

    PlayerInventory_Remove(userid, "Agency Card", 1);
	SendClientMessageEx(playerid, -1, "คุณได้ทำการยึดบัตรประจำตัวหน่วยงาน %s เรียบร้อยแล้ว", ReturnRoleplayName(userid));
    SendClientMessageEx(userid, -1, "%s ได้ทำการยึดบัตรประจำตัวหน่วยงานของคุณเรียบร้อยแล้ว", ReturnRoleplayName(playerid));
	return 1;
}

alias:invite("รับคน")
CMD:invite(playerid, params[])
{
	if(!LoggedIn[playerid]) return 1;
    new
        userid;

    if (PlayerData[playerid][pGroup] == -1)
        return SendClientMessage(playerid, -1, "คุณต้องเป็นสมาชิกของฝ่ายหรือกลุ่ม");

    if (PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks])
        return SendClientMessageEx(playerid, -1, "คุณต้องมียศอย่างต่ำ %d", GroupData[PlayerData[playerid][pGroup]][groupRanks]);

    if (sscanf(params, "u", userid))
        return SystemMsg(playerid, "/invite [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นได้ตัดการเชื่อมต่อแล้ว");

    if (PlayerData[userid][pGroup] == PlayerData[playerid][pGroup])
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นเป็นส่วนหนึ่งของฝ่ายหรือกลุ่มคุณแล้ว");

    if (PlayerData[userid][pGroup] != -1)
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นเป็นส่วนหนึ่งของฝ่ายหรือกลุ่มอื่นอยู่แล้ว");

	if(PlayerData[userid][pTimeQuitGang] > 0) return SendClientMessageEx(playerid, COLOR_RED, "ผู้เล่นนั้นยังเหลือเวลาอีก %d ชั่วโมงถึงจะเข้าแก๊งได้อีก", PlayerData[userid][pTimeQuitGang]);

    PlayerData[userid][pGroupOffer] = playerid;
    PlayerData[userid][pGroupOffed] = PlayerData[playerid][pGroup];

    SendClientMessageEx(playerid, -1, "คุณได้ส่งคำร้องถึง %s ให้เข้าร่วม \"%s\"", ReturnRoleplayName(userid), Group_GetName(playerid));
    SendClientMessageEx(userid, -1, "%s ได้เสนอให้คุณเข้าร่วม \"%s\" (ใช้ \"/ยอมรับ\")", ReturnRoleplayName(playerid), Group_GetName(playerid));

    return 1;
}

alias:acceptinvite("ยอมรับ")
CMD:acceptinvite(playerid)
{
	if(!LoggedIn[playerid]) return 1;
    new
        targetid = PlayerData[playerid][pGroupOffer],
        groupid = PlayerData[playerid][pGroupOffed];

    if(targetid == INVALID_PLAYER_ID)
        return ErrorMsg(playerid, "คุณไม่มีข้อเสนอเข้าร่วม กลุ่ม/แก๊ง ใดๆ");

    if (!GroupData[groupid][groupExists])
        return SendClientMessage(playerid, -1, "ข้อเสนอฝ่ายหรือกลุ่มไม่สามารถใช้งานได้");

    SetGroup(playerid, groupid);
    PlayerData[playerid][pGroupRank] = 1;

	if(GetGroupType(playerid) == GROUP_GANG){
		if(ServerData[ServerCanHoldGangZone] == 1){
			SetGroupColor(playerid);
		}
	}

    SendClientMessageEx(playerid, -1, "คุณได้ยอมรับข้อเสนอ %s เพื่อเข้าร่วม \"%s\"", ReturnRoleplayName(targetid), Group_GetName(targetid));
    SendClientMessageEx(targetid, -1, "%s ได้ยอมรับข้อเสนอของคุณเพื่อเข้าร่วม \"%s\"", ReturnRoleplayName(playerid), Group_GetName(targetid));

	SetPlayerNameTag(playerid, playerid);

    PlayerData[playerid][pGroupOffer] = INVALID_PLAYER_ID;
    PlayerData[playerid][pGroupOffed] = -1;
    return 1;
}

alias:uninvite("ปลดคน")
CMD:uninvite(playerid, params[])
{
	if(!LoggedIn[playerid]) return 1;
    new
        userid;

    if (PlayerData[playerid][pGroup] == -1)
        return SendClientMessage(playerid, -1, "คุณต้องเป็นสมาชิกของฝ่ายหรือกลุ่ม");

    if (PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]-1)
        return SendClientMessageEx(playerid, -1, "คุณต้องมียศอย่างต่ำ %d", GroupData[PlayerData[playerid][pGroup]][groupRanks]);

    if (sscanf(params, "u", userid))
        return SystemMsg(playerid, "/uninvite [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นได้ตัดการเชื่อมต่อแล้ว");

    if(userid == playerid)
        return ErrorMsg(playerid, "จะเตะตัวเองทำเพื่อ?");

    if (PlayerData[userid][pGroup] != PlayerData[playerid][pGroup])
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นไม่ได้เป็นส่วนหนึ่งของฝ่ายหรือกลุ่มเดียวกับคุณ");

    if(PlayerData[userid][pGroupRank] > PlayerData[playerid][pGroupRank])
        return ErrorMsg(playerid, "คุณไม่สามารถเตะยศที่สูงกว่าได้");

    SetPlayerColor(userid, 0xFFFFFF00);
	PlayerData[userid][pTimeQuitGang] = 1;

    SendClientMessageEx(playerid, -1, "คุณได้ลบ %s ออกจาก \"%s\"", ReturnRoleplayName(userid), Group_GetName(playerid));
    SendClientMessageEx(userid, -1, "%s ได้ลบคุณออกจากฝ่ายหรือกลุ่ม \"%s\"", ReturnRoleplayName(playerid), Group_GetName(playerid));

    ResetGroup(userid);
	SetPlayerNameTag(userid, userid);
    return 1;
}

alias:giverank("ให้ยศ")
CMD:giverank(playerid, params[])
{
	if(!LoggedIn[playerid]) return 1;

    new
        userid,
        rankid;

    if (PlayerData[playerid][pGroup] == -1)
        return SendClientMessage(playerid, -1, "คุณต้องเป็นสมาชิกของฝ่ายหรือกลุ่ม");

    if (PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks])
        return SendClientMessageEx(playerid, -1, "คุณต้องมียศอย่างต่ำ %d", GroupData[PlayerData[playerid][pGroup]][groupRanks]);

    if (sscanf(params, "ud", userid, rankid))
        return SystemMsg(playerid, "/giverank [playerid/name] [rank (1-%d)]", GroupData[PlayerData[playerid][pGroup]][groupRanks]);

    if (userid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นได้ตัดการเชื่อมต่อแล้ว");

    if (userid == playerid)
        return SendClientMessage(playerid, -1, "คุณไม่สามารถปรับยศตัวเองได้");

    if (PlayerData[userid][pGroup] != PlayerData[playerid][pGroup])
        return SendClientMessage(playerid, -1, "ผู้เล่นนั้นไม่ได้เป็นส่วนหนึ่งของฝ่ายหรือกลุ่มเดียวกับคุณ");
		
    if (rankid < 1 || rankid > GroupData[PlayerData[playerid][pGroup]][groupRanks] - 1)
        return SendClientMessageEx(playerid, -1, "ยศที่ระบุไม่ถูกต้อง ยศต้องอยู่ระหว่าง 1 ถึง %d", GroupData[PlayerData[playerid][pGroup]][groupRanks]);

    PlayerData[userid][pGroupRank] = rankid;

    SendClientMessageEx(playerid, -1, "คุณได้เลื่อนตำแหน่ง %s เป็น %s (%d)", ReturnRoleplayName(userid), Group_GetRank(userid), rankid);
    SendClientMessageEx(userid, -1, "%s ได้เลื่อนตำแหน่งคุณเป็น %s (%d)", ReturnRoleplayName(playerid), Group_GetRank(userid), rankid);

    return 1;
}

CMD:eject(playerid, params[]) {
	if(!LoggedIn[playerid]) return 1;
	new
		targetID;

	if(sscanf(params, "u", targetID))
		return SystemMsg(playerid, "/eject [playerid]");

	if(targetID == INVALID_PLAYER_ID) return 1;

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		if(GetPlayerVehicleID(playerid) == GetPlayerVehicleID(targetID)) {

			SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้ผลัก %s ออกจากพาหนะรถยนต์", ReturnRoleplayName(playerid), ReturnRoleplayName(targetID));
			RemovePlayerFromVehicle(targetID);
		}
		else ErrorMsg(playerid, "ผู้เล่นนี้ไม่ได้อยู่ภายในพาหนะ");
	}
	else ErrorMsg(playerid, "คุณต้องอยู่ในสถานะผู้ขับรถ");
	return 1;
}

alias:detain("ดึงขึ้นรถ")
CMD:detain(playerid, params[]) {
	if(!LoggedIn[playerid]) return 1;

	new
		seat,
		userid;

    if(!LoggedIn[playerid])
        return ErrorMsg(playerid, "คุณไม่ได้ล็อคอิน");

	if(sscanf(params, "ud", userid, seat))
		return SystemMsg(playerid, "/detain [playerid] [seat (1-3)]");

    if (userid == INVALID_PLAYER_ID)
        return ErrorMsg(playerid, "ผู้เล่นนั้นได้ตัดการเชื่อมต่อแล้ว");

    if (userid == playerid)
        return ErrorMsg(playerid, "คุณไม่สามารถโยนตัวเองได้");

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณต้องเป็นคนขับ");

	new vehicleid = GetPlayerVehicleID(playerid);

    if (vehicleid == INVALID_VEHICLE_ID)
	    return ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ยานพาหนะใด ๆ");

    if (!BitFlag_Get(g_PlayerFlags[userid],PLAYER_CUFFED) && !PlayerData[userid][pInjured])
        return ErrorMsg(playerid, "ผู้เล่นนั้นไม่ได้ถูกใส่กุญแจมือหรือบาดเจ็บในขณะนี้");

    if(seat > 0 && seat < 4) {
        if(IsPlayerNearPlayer(playerid, userid, 5.0)) {
            if(checkVehicleSeat(vehicleid, seat) != 0) SendClientMessage(playerid, COLOR_GREY, "หมายเลข ID ที่นั่งไม่ว่าง");
            else {
                SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s เปิดประตูและจับ %s นั่งในยานพาหนะ", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
                PutPlayerInVehicle(userid, vehicleid, seat);
            }
        }
        else SendClientMessage(playerid, COLOR_GREY, "คุณและรถต้องอยู่ใกล้กับคนที่คุณจะควบคุมตัวขึ้นรถ");
    }
	return 1;
}

stock checkVehicleSeat(vehicleid, seatid) {
	foreach(new x : Player){
		if(!LoggedIn[x]) continue;
	    if(GetPlayerVehicleID(x) == vehicleid && GetPlayerVehicleSeat(x) == seatid) return 1;
	}
	return 0;
}

CMD:makeidcard(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 1;
	if (!IsPlayerInRangeOfPoint(playerid, 3.0, 361.8299, 173.5183, 1008.3828))
	    return ErrorMsg(playerid, "คุณไม่ได้อยู่ในขอบเขตของ City Hall");

	if (GetMoney(playerid) < 1000)
		return ErrorMsg(playerid, "คุณมีเงินไม่เพียงพอ");
			
	if (PlayerInventory_AllCount(playerid, "Id Card") >= 1)
 		return ErrorMsg(playerid, "คุณมีบัตรประชาชนแล้ว");

	GiveMoney(playerid, -1000, "makeidcard");
 	PlayerData[playerid][pIdcard] = random(90000) + 10000;
 	SendClientMessageEx(playerid, -1, "หมายเลขบัตรประชาชนคือ : %d", PlayerData[playerid][pIdcard]);
	new id = PlayerInventory_AddItem(playerid, "Id Card", 1581, 1);
	if (id == -1){
		return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
	}
   	SendClientMessage(playerid, -1, "คุณได้ทำบัตรประชาชนเรียบร้อยแล้ว");
	
	return 1;
}

CMD:fps(playerid)
{
    if(!LoggedIn[playerid])
        return ErrorMsg(playerid, "คุณไม่ได้ล็อคอิน");

    if(!IsPlayerConnected(playerid)) return SendClientMessage(playerid, COLOR_GREY, "คุณยังไม่ได้เข้าสู่ระบบ");

    if(!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_FPS)) {

        SetPVarInt(playerid, "DisableFPS", 1);
        PlayerData[playerid][pCameraFPS] = CreateObject(19300, 0.0, 0.0, 5.0, 0.0, 0.0, 0.0);
        SetCameraBehindPlayer(playerid);
        SyncCamera(playerid);
        BitFlag_On(g_PlayerFlags[playerid], PLAYER_FPS);
    } else {

        SetPVarInt(playerid, "DisableFPS", 0);
        if(IsValidObject(PlayerData[playerid][pCameraFPS]) && PlayerData[playerid][pCameraFPS]) DestroyObject(PlayerData[playerid][pCameraFPS]);
        SetCameraBehindPlayer(playerid);
        BitFlag_Off(g_PlayerFlags[playerid], PLAYER_FPS);
    }
    return 1;
}

alias:sharelocation("sl")
CMD:sharelocation(playerid, params[]){
	if(!LoggedIn[playerid]) return 1;
	
	if(CheckPlayerNotSendGps(playerid) != -1) return ErrorMsg(playerid, "คุณไม่สามารถใช้ได้ตอนนี้");

	if (BitFlag_Get(g_PlayerFlags[playerid],PLAYER_PHONE_OFF))
		return ErrorMsg(playerid, "โปรดเปิดโทรศัพท์มือถือของท่านก่อน");

	if(PlayerStartDeliverOil[playerid]) return 1;
	if(PlayerGetOilDeliver[playerid]) return 1;

	new userid, string[128], checkhavenumber = 0;
	if(PlayerInventory_AllCount(playerid, "Mobile Phone") < 1) return ErrorMsg(playerid, "คุณไม่มีโทรศัพท์");
	if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/sharelocation [playerid]");
	if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
	if(userid != INVALID_PLAYER_ID){
		if(LoggedIn[userid]){

			if(PlayerStartDeliverOil[userid]) return 1;
			if(PlayerGetOilDeliver[userid]) return 1;

			if(CheckPlayerNotSendGps(userid) != -1)
				return ErrorMsg(playerid, "เฮ้ย! วัยรุ่นทำไรอะ");

			if(PlayerInventory_AllCount(userid, "Mobile Phone") < 1) return ErrorMsg(playerid, "ผู้เล่นนั้นไม่มีโทรศัพท์");

			for (new i = 0; i != MAX_CONTACTS; i ++) if (ContactData[playerid][i][contactExists]){
				if(ContactData[playerid][i][contactNumber] == PlayerData[userid][pNumberPhone]) checkhavenumber = 1;
	    	}

			if(checkhavenumber != 1) return ErrorMsg(playerid, "คุณไม่มีเบอร์ติดต่อหรือช่องทางติดต่อกับผู้เล่นนั้น ไม่สามารถใช้งานได้");

			if (BitFlag_Get(g_PlayerFlags[userid],PLAYER_PHONE_OFF))
				return ErrorMsg(playerid, "โปรดเปิดโทรศัพท์มือถือของท่านก่อน");

			SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ส่งตำแหน่งของคุณให้กับ %s แล้ว", ReturnRoleplayName(userid));
			GetPlayerShareLocation[userid] = playerid;
			format(string, sizeof(string), "%s ได้ส่งตำแหน่งของเขาให้คุณ\nหากคุณต้องการรับให้กดปุ่ม 'รับ'\nหากคุณต้องการยกเลิกให้กดปุ่ม 'ยกเลิก'", ReturnRoleplayName(playerid));
			Dialog_ShowEasy(userid, ShareLocation, DIALOG_STYLE_MSGBOX, "ระบบแชร์ตำแหน่ง", string, "รับ", "ยกเลิก");
		}
	}
	return 1;
}

CMD:boombox(playerid, params[]){
	new
	    type[24],
	    string[128];

	if (!PlayerInventory_HasItem(playerid, "Boombox"))
	    return ErrorMsg(playerid, "คุณไม่มี Boombox อยู่ในตัว");

	if(PlayerEnterWarFlag[playerid]) return 1;

	if (sscanf(params, "s[24]S()[128]", type, string))
	{
	    SystemMsg(playerid, "/boombox [name]");
	    SystemMsg(playerid, "[Type]:{FFFFFF} place, pickup, url");
	    return 1;
	}
	if (!strcmp(type, "place", true))
	{
	    if (BoomboxData[playerid][boomboxPlaced])
	        return ErrorMsg(playerid, "คุณได้วาง Boombox แล้ว");

		if (Boombox_Nearest(playerid) != INVALID_PLAYER_ID)
		    return ErrorMsg(playerid, "คุณอยู่ในขอบเขตของ Boombox อื่น");

		if (IsPlayerInAnyVehicle(playerid))
		    return ErrorMsg(playerid, "คุณต้องออกจากยานพาหนะก่อน");

		new id;
  		if ((id = Entrance_Inside(playerid)) != -1 && EntranceData[id][entranceType] == 6)
  		    return ErrorMsg(playerid, "คุณไม่สามารถวาง Boombox ในพื้นที่นี้ได้");

		Boombox_Place(playerid);

		RemoveAttachedObject(playerid, 8);
		SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้วาง Boombox ลงกับพื้น", ReturnRoleplayName(playerid));
		SendClientMessage(playerid, -1, "คุณได้วาง Boombox ของคุณ (ใช้ \"/boombox\" สำหรับตัวเลือก)");
	}
	else if (!strcmp(type, "pickup", true))
	{
	    if (!BoomboxData[playerid][boomboxPlaced])
	        return ErrorMsg(playerid, "คุณยังไม่ได้ใช้ Boombox");

		if (!IsPlayerInRangeOfPoint(playerid, 3.0, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2]))
		    return ErrorMsg(playerid, "คุณไม่ได้อยู่ในขอบเขต Boombox ของคุณ");

		CheckBoombox[playerid] = 1;
		Boombox_Destroy(playerid);
		SetPlayerAttachedObject(playerid,8,2226,6,0.365000,0.027000,0.145000,0.000000,-111.299995,0.000000,1.000000,1.000000,1.000000);
		SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s พยายามหยิบ Boombox ของเขาขึ้น", ReturnRoleplayName(playerid));
	}
	else if (!strcmp(type, "url", true))
	{
	    if (sscanf(string, "s[128]", string))
	        return SystemMsg(playerid, "/boombox [url] [song url]");

        if (!BoomboxData[playerid][boomboxPlaced])
	        return ErrorMsg(playerid, "คุณยังไม่ได้ใช้ Boombox");

		if (!IsPlayerInRangeOfPoint(playerid, 3.0, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2]))
		    return ErrorMsg(playerid, "คุณไม่ได้อยู่ในขอบเขต Boombox ของคุณ");

		if(CheckIsHaveThaiFont(string) == 1) return ErrorMsg(playerid, "รูปแบบลิ้งไม่ถูกต้อง");

		Boombox_SetURL(playerid, string);
		SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้ปรับเปลี่ยนเพลง Boombox ของเขา", ReturnRoleplayName(playerid));
	}
	return 1;
}