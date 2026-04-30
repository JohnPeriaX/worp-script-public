#if defined _inc_impl
	#undef _inc_impl
#endif

forward PlayerConnected(playerid);
public PlayerConnected(playerid){
	if(IsPlayerConnected(playerid)){
		new str[128];

		KillTimer(PlayerData[playerid][pLogCheckTime]);

		format(str, sizeof(str), "{23D101}| {FFFFFF}ยินดีต้อนรับเข้าสู่เซิฟเวอร์, %s", ReturnName(playerid));
	    SendClientMessage(playerid, COLOR_SERVER, str);

		for(new i=0; i<5; i++) PlayerTextDrawShow(playerid, ScreenTextDraw[playerid][i]);
		SelectTextDraw(playerid, COLOR_SERVER);
		PlayerInScreen[playerid] = true;
	    LoggedIn[playerid] = false;
	    LoginAttempts[playerid] = 0;
		PlayerTimeOutLogin[playerid] = 0;
	}
	return 1;
}

forward LoadingToFindAccount(playerid);
public LoadingToFindAccount(playerid){
	if(!IsPlayerConnected(playerid)) return 0;

	new query[128];
	mysql_format(dbCon, query, sizeof(query), "SELECT NULL FROM `accounts` WHERE Name = '%e' LIMIT 1", ReturnName(playerid));
	mysql_tquery(dbCon, query, "Handle_Account", "i", playerid);
	return 1;
}

forward Handle_Account(playerid);
public Handle_Account(playerid){
	if(!IsPlayerConnected(playerid)) return 0;

    if(cache_num_rows()) Login_Dialog(playerid);
    else Register_Dialog(playerid);
	StartPlayerCountTimeLogin[playerid] = SetTimerEx("CountTimeoutLogin", 1000, false, "i", playerid);
    return 1;
}

Login_Dialog(playerid){
    new str[500];
	new head[128];
	format(head, sizeof(head), "%s | เข้าสู่ระบบ", SERVER_SHORTNAME);
    format(str, sizeof(str), "{FFFFFF}สวัสดี, คุณ %s! ยินดีต้อนรับกลับสู่เซิฟเวอร์\n- คุณมีบัญชีกับทางเซิฟเวอร์ของเราอยู่แล้ว!\n\n- โปรดกรอกรหัสผ่านของคุณในช่องด้านล่างเพื่อทำการเข้าสู่ระบบ: \n{FFD500}[แนะนำ]: หากลืมรหัสผ่าน โปรดแจ้งผู้ดูแลทางแฟนเพจหรือ Discord", ReturnName(playerid));
    Dialog_ShowEasy(playerid, LOGIN, DIALOG_STYLE_PASSWORD, head, str, "เข้าสู่ระบบ", "");
    return 1;
}

Register_Dialog(playerid){
    new str[500];
	new head[128];
	format(head, sizeof(head), "%s | สมัครสมาชิก", SERVER_SHORTNAME);
    format(str, sizeof(str), "{FFFFFF}สวัสดี, คุณ %s!\n- คุณยังไม่ได้ลงทะเบียนบัญชีกับเซิฟเวอร์ของเรา!\n\n{FFFFFF}- โปรดกรอกรหัสผ่านที่คุณต้องการในช่องด้านล่างเพื่อทำการลงทะเบียน: \n{FF0000}[คำเตือน]: โปรดใช้ ตัวอักษร พิมพ์ 'เล็ก' พิมพ์ 'ใหญ่' และ 'ตัวเลข' ผสมกัน เพื่อความปลอดภัยของรหัสผ่าน", ReturnName(playerid));
    Dialog_ShowEasy(playerid, REGISTER, DIALOG_STYLE_INPUT, head, str,"สมัครสมาชิก","");
    return 1;
}

Dialog:LOGIN(playerid, response, listitem, inputtext[]){
	if(!response){ 
        SendClientMessage(playerid, COLOR_RED, "คุณออกจากเซิฟเวอร์."); 
        KickPlayer(playerid);
        return 1;
    }
    if(response){
        new query[256];
		mysql_format(dbCon, query, sizeof(query), "SELECT Password FROM accounts WHERE Name = '%e' LIMIT 1", ReturnName(playerid));
		mysql_query(dbCon, query);

		new rows;
		cache_get_row_count(rows);
		if(rows){
			new realpassword[64];
			cache_get_value_name(0, "Password", realpassword, sizeof realpassword);
			bcrypt_verify(playerid,"JDz_OnPassswordVerify", inputtext, realpassword);
		}else return ErrorMsg(playerid, "ไม่พบข้อมูลดังกล่าว, กรุณาติดต่อผู้ดูแลระบบ!");
	}
    return 1;
}

forward JDz_OnPassswordVerify(playerid, bool:success);
public JDz_OnPassswordVerify(playerid, bool:success){
	if(!IsPlayerConnected(playerid)) return 0;

    if(success){
		new query[512];
        mysql_format(dbCon, query, sizeof(query), "SELECT SQLID, Name, Wallet, Active, InGame FROM accounts WHERE Name = '%e' LIMIT 1", ReturnName(playerid));
		mysql_tquery(dbCon, query, "Login", "i", playerid);
    } else{
        if(LoginAttempts[playerid] < 2){
            Login_Dialog(playerid);

            SendClientMessage(playerid, COLOR_SERVER, "{23D101}| [Warning] {FFFFFF}รหัสของคุณผิดพลาด!.");
            LoginAttempts[playerid] ++;
        }
        else{
            SendClientMessage(playerid, COLOR_SERVER, "{23D101}| [Warning] {FFFFFF}คุณใส่รหัสผิดพลาดเยอะเกินไป");
            KickPlayer(playerid);
			return 1;
        }
    }
    return 1;
}

Dialog:REGISTER(playerid, response, listitem, inputtext[]){
	if(strlen(inputtext) < 6 || strlen(inputtext) > 24){
        SendClientMessage(playerid, COLOR_ORANGERED, "รหัสผ่านต้องมีอย่างน้อย 6-24 ตัว!");
        Register_Dialog(playerid);
    }
    else if(strlen(inputtext) > 5 && strlen(inputtext) < 24){
		bcrypt_hash(playerid, "JDz_OnPassswordHashRegister", inputtext, BCRYPT_COST);
	}
    return 1;
}

forward JDz_OnPassswordHashRegister(playerid);
public JDz_OnPassswordHashRegister(playerid){
	new dest[BCRYPT_HASH_LENGTH];
    bcrypt_get_hash(dest);
    new query[512];
    GetPlayerIp(playerid, PlayerData[playerid][pRegisterIP], 16);
	mysql_format(dbCon, query, sizeof(query), "INSERT INTO accounts (Name, Password, RegisterIP, RegisterDate) VALUES('%e','%e','%e', '%e')", ReturnName(playerid), dest, PlayerData[playerid][pRegisterIP], ReturnDate());
	mysql_tquery(dbCon, query, "GetAccID", "i", playerid);
	
	SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้ลงทะเบียนกับเราเรียบร้อยแล้ว, ขั้นตอนต่อไปให้คุณใส่รหัสผ่านเพื่อเข้าสู่ระบบ");
	Login_Dialog(playerid);
    return 1;
}

//Login
forward Login(playerid);
public Login(playerid){
    if(cache_num_rows()){
        cache_get_value_name_int(0, "SQLID", AccountData[playerid][uSQLID]);
		cache_get_value_name(0, "Name", AccountData[playerid][uName], 64);
		cache_get_value_name_int(0, "Wallet", AccountData[playerid][uWallet]);
		cache_get_value_name_int(0, "Active", AccountData[playerid][uActive]);
		cache_get_value_name_int(0, "InGame", AccountData[playerid][uInGame]);

		new query[128];
		mysql_format(dbCon, query, sizeof(query), "UPDATE accounts SET UpdateWallet = 0, WalletAfter = 0 WHERE SQLID = %d LIMIT 1", AccountData[playerid][uSQLID]);
		mysql_tquery(dbCon, query);

		if(AccountData[playerid][uSQLID] == 0){
			return Kick(playerid);
		}

		if(!strcmp(ReturnName(playerid), AccountData[playerid][uName], true)){
			AccountData[playerid][uInGame] = 1;
			Accounts_Save(playerid);
			printf("%s: Logged in [%d].", AccountData[playerid][uName], playerid);
			PlayerTimeOutLogin[playerid] = 0;
			KillTimer(StartPlayerCountTimeLogin[playerid]);
			SetSpawnInfo(playerid, NO_TEAM, 73, 1951.5914, 1341.8439, 15.3746, 357.9944, 0, 0, 0, 0, 0, 0);
			CallLocalFunction("Characters_Fetch", "i", playerid);
		}
		else{
			ErrorMsg(playerid, "เกิดข้อผิดพลาด");
			KickPlayer(playerid);
			return 1;
		}
		
    }
    return 1;
}

DialogInfomationPlayer(playerid){
	new caption[128];
	new sex[64];
	new string[80];
	format(caption, sizeof(caption), "ข้อมูลตัวละครของ %s", ReturnRoleplayName(playerid));

	if(PlayerData[playerid][pGender] == 0)
		sex = "ยังไม่ได้เลือก";
	else if(PlayerData[playerid][pGender] == 1)
		sex = "ชาย";
	else if(PlayerData[playerid][pGender] == 2)
		sex = "หญิง";

	format(string, sizeof(string), "- เพศ\t[%s]\n- อายุ\t[%d]\n- ยืนยันข้อมูล", sex, PlayerData[playerid][pAge]);
	Dialog_ShowEasy(playerid, DIALOG_INPUTINFO, DIALOG_STYLE_LIST, caption, string, "ตกลง", "ยกเลิก");
	return 1;
}

//Register
stock Register(playerid){
	DialogInfomationPlayer(playerid);
	return 1;
}

Dialog:DIALOG_INPUTINFO(playerid, response, listitem, inputtext[]){
	if(!response)
		return DialogInfomationPlayer(playerid);

	if(response){
		if(listitem == 0){
			Dialog_ShowEasy(playerid, SelectGender, DIALOG_STYLE_LIST, "เลือกเพศ", "- ชาย\n- หญิง", "เลือก", "กลับ");
		}
		if(listitem == 1){
			Dialog_ShowEasy(playerid, InputAge, DIALOG_STYLE_INPUT, "อายุของตัวละคร", "คุณจำเป็นต้องกรอกอายุให้กับตัวละครของคุณ:", "ตกลง", "กลับ");
		}
		if(listitem == 2){
			if(PlayerData[playerid][pGender] == 0){
				ErrorMsg(playerid, "คุณจำเป็นต้องเลือก เพศ");
				DialogInfomationPlayer(playerid);
				return 1;
			}

			if(PlayerData[playerid][pAge] == 0){
				ErrorMsg(playerid, "คุณจำเป็นต้องเลือก อายุ");
				DialogInfomationPlayer(playerid);
				return 1;
			}

			FinishRegister(playerid);
		}
	}
	return 1;
}

Dialog:SelectGender(playerid, response, listitem, inputtext[]){
	if(!response){
		DialogInfomationPlayer(playerid);
		return 0;
	}
	else{
		if(listitem == 0){
			SendClientMessage(playerid, COLOR_GREEN, "- โอเคคุณได้เลือกเพศ ชาย");
			PlayerData[playerid][pGender] = 1;
			DialogInfomationPlayer(playerid);
		}

		if(listitem == 1){
			SendClientMessage(playerid, COLOR_GREEN, "- โอเคคุณได้เลือกเพศ หญิง");
			PlayerData[playerid][pGender] = 2;
			DialogInfomationPlayer(playerid);
		}
	}
	return 1;
}

Dialog:InputAge(playerid, response, listitem, inputtext[]){
	if(!response){
		DialogInfomationPlayer(playerid);
		return 0;
	}
	else{
		new age = strval(inputtext);
		if(age < 18 || age > 100)
			return Dialog_ShowEasy(playerid, InputAge, DIALOG_STYLE_INPUT, "อายุของตัวละคร", "อายุตัวละครของคุณต้องไม่ต่ำกว่า 18 และไม่มากกว่า 100\nคุณจำเป็นต้องกรอกอายุให้กับตัวละครของคุณ:", "ตกลง", "ยกเลิก");
		
		PlayerData[playerid][pAge] = age;
		SendClientMessageEx(playerid, COLOR_GREEN, "- โอเคตัวละครของคุณอายุ %d", age);
		DialogInfomationPlayer(playerid);
	}
	return 1;
}

forward GetAccID(playerid);
public GetAccID(playerid){
	AccountData[playerid][uSQLID] = cache_insert_id();
	return 1;
}

forward GetCharacterID(playerid);
public GetCharacterID(playerid){
	PlayerData[playerid][pID] = cache_insert_id();
	return 1;
}

forward Characters_Fetch(playerid);
public Characters_Fetch(playerid){
    new query[128];
    mysql_format(dbCon, query, sizeof(query), "SELECT ID, Username, Level, Skin, Gender, Cash, BankMoney, Vip FROM characters WHERE A_ID = %d LIMIT 3", AccountData[playerid][uSQLID]);
    mysql_tquery(dbCon, query, "Characters_Menu", "i", playerid);
    return 1;
}

stock FinishRegister(playerid){
	KillTimer(PlayerData[playerid][pLoadingNameTime]);
 	PlayerData[playerid][pLevel] = 1;
	PlayerData[playerid][pPosX] = 1494.4642;
	PlayerData[playerid][pPosY] = 1303.8282;
	PlayerData[playerid][pPosZ] = 1093.2891;
	PlayerData[playerid][pAngle] = 357.9944;

	PlayerData[playerid][pCash] = 2500;
	PlayerData[playerid][pInjured] = 0;

	PlayerData[playerid][pHunger] = 100;
	PlayerData[playerid][pWater] = 100;
	PlayerData[playerid][pEnergy] = 100;
	PlayerData[playerid][pShower] = 0;
	PlayerData[playerid][pStress] = 0;

	PlayerData[playerid][pMaxItem] = 36;
	PlayerData[playerid][pItemAmount] = 50;
	PlayerData[playerid][pInvMaxWeight] = 50.0;

	PlayerData[playerid][pWhitelist] = 0;

	if(PlayerData[playerid][pGender] == 1)
		PlayerData[playerid][pSkin] = 289;
	else if(PlayerData[playerid][pGender] == 2)
		PlayerData[playerid][pSkin] = 191;

	SetPlayerHealth(playerid, 100);
	PlayerData[playerid][pHP] = 100;
	LoggedIn[playerid] = true;

	SelectCharTextDraw[playerid] = false;
	
	SetPlayerColor(playerid, 0xFFFFFF00);
	
	SetPlayerScore(playerid, PlayerData[playerid][pSelectChar]);

	PlayerData[playerid][pWorld] = playerid+1;
	PlayerData[playerid][pInterior] = 3;

	PlayerData[playerid][pFirstTime] = 1;

	GetPlayerIp(playerid, PlayerData[playerid][pLastIP], 16);

	new str[128];
	mysql_format(dbCon, str, sizeof(str), "SELECT * FROM `blacklist` WHERE `Username` = '%e' OR `IP` = '%e'", ReturnName(playerid), PlayerData[playerid][pLastIP]);
	mysql_tquery(dbCon, str, "OnPlayerBlacklist", "d", playerid);

	SendClientMessageEx(playerid, COLOR_SERVER, "{23D101}| {FFFFFF}ยินดีต้อนรับ %s เข้าสู่เซิฟเวอร์ของเรา, ขอให้คุณสนุกสนานกับเซิฟเวอร์ของเรา", ReturnRoleplayName(playerid));

	SendClientMessage(playerid, COLOR_DARKGREEN, "|--------------------------------------------------|");
	ShowSpeaker(playerid);
	SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
	TogglePlayerSpectating(playerid, false);
	SetTimerEx("StopSong", 3000, false, "i", playerid);
	return 1;
}

SetMessageWelcome(playerid){
	new string[1024];
	format(string, sizeof(string), "{FFB23C}>> ยินดีต้อนรับเข้าสู่เซิฟเวอร์ %s <<\
	\n[ ** คุณสมบัติที่คุณจะต้องมีในการเข้าเล่นเซิฟเวอร์ของเรา ** ]\
	\n1. คุณจะต้องรู้เรื่องเกี่ยวกับ Roleplay และความเป็นมารวมไปถึงการเล่นจำลองบทบาทต่างๆ\
	\n2. คุณจะต้องรู้เกี่ยวกับกฏของเซิฟเวอร์สามารถหาอ่านได้ที่ Discord ของเซิฟเวอร์เรา หากคุณทำผิดจะถูกลงโทษ\
	\n3. คุณจะต้องเคารพตามกฏของเซิฟเวอร์ และ ให้ความเคารพต่อผู้เล่นอื่นด้วย\
	\n4. คุณจำเป็นต้องจำลองบทบาทให้เหมือนชีวิตจริงเท่าที่สุดที่คุณจะทำได้\
	\n5. ไม่เปิดไมค์โครโฟนด่าหรือเปิดเสียงต่างๆที่ก่อให้เกิดการรบกวนกับผู้เล่นอื่น\
	\n==================================================================================\
	\n - ต่อไปหากอ่านกฏของเซิฟเวอร์มาพร้อมแล้ว และ พร้อมที่จะทำแบบทดสอบการเข้าเล่น ให้กด 'ต่อไป'", SERVER_NAME);
	Dialog_ShowEasy(playerid, MessageWelcome, DIALOG_STYLE_MSGBOX, "ยินดีต้อนรับเข้าสู่เซิฟเวอร์", string, "ต่อไป", "");
	return 1;
}

forward Characters_FetchReClick(playerid, C_ID);
public Characters_FetchReClick(playerid, C_ID){
    new query[256];
	PlayerClickCharList[playerid] = C_ID;
    mysql_format(dbCon, query, sizeof(query), "SELECT * FROM characters WHERE ID = %d AND A_ID = %d LIMIT 1", C_ID, AccountData[playerid][uSQLID]);
    mysql_tquery(dbCon, query, "Characters_ShowOneCha", "i", playerid);
    return 1;
}

timer StopWalk[2100](playerid){
	ApplyAnimation(playerid, "PED", "fucku", 4.1, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "COP_AMBIENT", "Coplook_loop", 4.1, 0, 1, 1, 1, 0, 1);
}

timer WalkingToScreenMale[100](playerid){
	ApplyAnimation(playerid, "PED", "WALK_player", 4.1, 1, 1, 1, 1, 1, 1);
	StopWalkScreen[playerid] = defer StopWalk(playerid);
}

timer WalkingToScreenFeMale[100](playerid){
	ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
	StopWalkScreen[playerid] = defer StopWalk(playerid);
}

timer LoadObjectChar[500](playerid){
    ShowAccessoryScreen(playerid);
}

forward Characters_ShowOneCha(playerid);
public Characters_ShowOneCha(playerid){
	if(cache_num_rows()){
		printf("[!]: %s Loadded", ReturnName(playerid));
		new C_ID, C_Name[64], C_Level, C_Skin, C_Cash, C_Bank, C_Vip, C_Gender;
		new string[128], vipstring[128];

		for(new i=0; i<9; i++) RemoveAttachedObject(playerid, i);

		cache_get_value_name_int(0, "ID", C_ID);
		cache_get_value_name(0, "Username", C_Name, 64);
		cache_get_value_name_int(0, "Level", C_Level);
		cache_get_value_name_int(0, "Skin", C_Skin);
		cache_get_value_name_int(0, "Cash", C_Cash);
		cache_get_value_name_int(0, "BankMoney", C_Bank);
		cache_get_value_name_int(0, "Vip", C_Vip);
		cache_get_value_name_int(0, "Gender", C_Gender);

		cache_get_value_name_int(0, "AccessoryModelHat", achat[playerid]);
		cache_get_value_name_int(0, "AccessoryModelGlasses", acglass[playerid]);
		cache_get_value_name_int(0, "AccessoryModelBody", acbody[playerid]);
		cache_get_value_name_int(0, "AccessoryModelArms", acarms[playerid]);

		new string1[128];
		cache_get_value_name(0, "AccessoryPosHat", string1, sizeof(string1));
		sscanf(string1, "p<|>fffffffff", acposhat[playerid][0], acposhat[playerid][1], acposhat[playerid][2], acposhat[playerid][3], acposhat[playerid][4], acposhat[playerid][5], acposhat[playerid][6], acposhat[playerid][7], acposhat[playerid][8]);

		new string2[128];
		cache_get_value_name(0, "AccessoryPosGlasses", string2, sizeof(string2));
		sscanf(string2, "p<|>fffffffff", acposglass[playerid][0], acposglass[playerid][1], acposglass[playerid][2], acposglass[playerid][3], acposglass[playerid][4], acposglass[playerid][5], acposglass[playerid][6], acposglass[playerid][7], acposglass[playerid][8]);

		new string3[128];
		cache_get_value_name(0, "AccessoryPosBody", string3, sizeof(string3));
		sscanf(string3, "p<|>fffffffff", acposbody[playerid][0], acposbody[playerid][1], acposbody[playerid][2], acposbody[playerid][3], acposbody[playerid][4], acposbody[playerid][5], acposbody[playerid][6], acposbody[playerid][7], acposbody[playerid][8]);

		new string4[128];
		cache_get_value_name(0, "AccessoryPosArms", string4, sizeof(string4));
		sscanf(string4, "p<|>fffffffff", acposarms[playerid][0], acposarms[playerid][1], acposarms[playerid][2], acposarms[playerid][3], acposarms[playerid][4], acposarms[playerid][5], acposarms[playerid][6], acposarms[playerid][7], acposarms[playerid][8]);

		cache_get_value_name_int(0, "AccessoryEditHat", acedithat[playerid]);
		cache_get_value_name_int(0, "AccessoryEditGlasses", aceditglass[playerid]);
		cache_get_value_name_int(0, "AccessoryEditBody", aceditbody[playerid]);
		cache_get_value_name_int(0, "AccessoryEditArms", aceditarms[playerid]);

		cache_get_value_name_int(0, "AccessoryAllSetShow", ashowallset[playerid]);
		cache_get_value_name_int(0, "AccessoryShowHat", acshowhat[playerid]);
		cache_get_value_name_int(0, "AccessoryShowGlasses", acshowglass[playerid]);
		cache_get_value_name_int(0, "AccessoryShowBody", acshowbody[playerid]);
		cache_get_value_name_int(0, "AccessoryShowArms", acshowarms[playerid]);
		cache_get_value_name_int(0, "AccessoryArmsType", acctypearms[playerid]);
		
		TogglePlayerSpectating(playerid, false);
		SetPlayerCameraPos(playerid, 1958.0909,1342.4780,15.3806);
		SetPlayerCameraLookAt(playerid, 1955.1283,1341.8752,15.3746);
		SetPlayerPos(playerid, 1951.5914,1341.8439,15.3746);
		SetPlayerFacingAngle(playerid, 269.0995);
		PlayerData[playerid][pPlayerGetSkinTemp] = C_Skin;
		SetPlayerSkin(playerid, PlayerData[playerid][pPlayerGetSkinTemp]);
		ClearAnimations(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

		stop LoadObjectCharScreen[playerid];
		LoadObjectCharScreen[playerid] = defer LoadObjectChar(playerid);

		stop RunWalk[playerid];
		stop StopWalkScreen[playerid];

		if(C_Gender == 1){
			RunWalk[playerid] = defer WalkingToScreenMale(playerid);
		}
		else if(C_Gender == 2){
			RunWalk[playerid] = defer WalkingToScreenFeMale(playerid);
		}

		format(string, sizeof string, "%s", C_Name);
		PlayerTextDrawSetString(playerid, CharSelect[playerid][6], string);

		format(string, sizeof string, "~y~LEVEL: ~w~%d", C_Level);
		PlayerTextDrawSetString(playerid, CharSelect[playerid][7], string);

		format(string, sizeof string, "~y~MONEY: ~w~%s", FormatNumber(C_Cash));
		PlayerTextDrawSetString(playerid, CharSelect[playerid][8], string);

		format(string, sizeof string, "~y~BANK MONEY: ~w~%s", FormatNumber(C_Bank));
		PlayerTextDrawSetString(playerid, CharSelect[playerid][9], string);

		if(C_Vip == 0) format(vipstring, sizeof vipstring, "REGULAR MEMBER");
		else if(C_Vip == 1) format(vipstring, sizeof vipstring, "BRONZE MEMBER");
		else if(C_Vip == 2) format(vipstring, sizeof vipstring, "SILVER MEMBER");
		else if(C_Vip == 3) format(vipstring, sizeof vipstring, "GOLD MEMBER");

		format(string, sizeof string, "~y~VIP: ~w~%s", vipstring);
		PlayerTextDrawSetString(playerid, CharSelect[playerid][10], string);

		PlayerData[playerid][pSelectPlayChar] = C_ID;

		PlayerTextDrawShow(playerid, CharSelect[playerid][5]);
		PlayerTextDrawShow(playerid, CharSelect[playerid][6]);
		PlayerTextDrawShow(playerid, CharSelect[playerid][7]);
		PlayerTextDrawShow(playerid, CharSelect[playerid][8]);
		PlayerTextDrawShow(playerid, CharSelect[playerid][9]);
		PlayerTextDrawShow(playerid, CharSelect[playerid][10]);
		PlayerTextDrawShow(playerid, CharSelect[playerid][11]);
	}
	return 1;
}

forward ReLoadCameraScreen(playerid);
public ReLoadCameraScreen(playerid){
	SetPlayerCameraPos(playerid, 1958.0909,1342.4780,15.3806);
	SetPlayerCameraLookAt(playerid, 1955.1283,1341.8752,15.3746);
	return 1;
}

forward Characters_Menu(playerid);
public Characters_Menu(playerid){
    new C_ID, C_Name[64];
	new string[128];

	SetPlayerPos(playerid, 1951.5914,1341.8439,15.3746);
	SetPlayerFacingAngle(playerid, 269.0995);
	SetPlayerVirtualWorld(playerid, playerid+1);

	SetTimerEx("ReLoadCameraScreen", 300, false, "i", playerid);

	LoadCharSelectTextDraw(playerid);
	SelectCharTextDraw[playerid] = true;
	SelectTextDraw(playerid, COLOR_SERVER);

	if(cache_num_rows() < 3){
		//Char 1
		PlayerTextDrawShow(playerid, CharSelect[playerid][12]);
		//Char 2
		PlayerTextDrawShow(playerid, CharSelect[playerid][13]);
		//Char 3
		PlayerTextDrawShow(playerid, CharSelect[playerid][14]);
    }

    for(new id = 0; id < cache_num_rows(); id++){
		if(id == 0){
			cache_get_value_name_int(id, "ID", C_ID);
			cache_get_value_name(id, "Username", C_Name, 64);

			format(string, sizeof string, "%s", C_Name);
			PlayerTextDrawSetString(playerid, CharSelect[playerid][2], string);

			PlayerData[playerid][pSelectChar1] = C_ID;

			PlayerTextDrawHide(playerid, CharSelect[playerid][12]);
			PlayerTextDrawShow(playerid, CharSelect[playerid][2]);
		}

		if(id == 1){
			cache_get_value_name_int(id, "ID", C_ID);
			cache_get_value_name(id, "Username", C_Name, 64);

			format(string, sizeof string, "%s", C_Name);
			PlayerTextDrawSetString(playerid, CharSelect[playerid][3], string);

			PlayerData[playerid][pSelectChar2] = C_ID;

			PlayerTextDrawHide(playerid, CharSelect[playerid][13]);
			PlayerTextDrawShow(playerid, CharSelect[playerid][3]);
		}

		if(id == 2){
			cache_get_value_name_int(id, "ID", C_ID);
			cache_get_value_name(id, "Username", C_Name, 64);

			format(string, sizeof string, "%s", C_Name);
			PlayerTextDrawSetString(playerid, CharSelect[playerid][4], string);

			PlayerData[playerid][pSelectChar3] = C_ID;

			PlayerTextDrawHide(playerid, CharSelect[playerid][14]);
			PlayerTextDrawShow(playerid, CharSelect[playerid][4]);
		}
    }

	PlayerTextDrawShow(playerid, CharSelect[playerid][0]);
	PlayerTextDrawShow(playerid, CharSelect[playerid][1]);
    return 1;
}

Dialog:Character_Select(playerid, response, listitem, inputtext[])
{
    if(!response){ SendClientMessage(playerid, COLOR_RED, "คุณได้ออกจากเซิฟเวอร์."); KickPlayer(playerid);}
    if(response){
		if(LoggedIn[playerid]) return 1;
        new C_ID[6];
        strmid(C_ID, inputtext, strfind(inputtext, "[") + 1,  strfind(inputtext, "]"));
        Character_Fetch(playerid, strval(C_ID));
    }
    return 1;
}

forward Character_Fetch(playerid, id);
public Character_Fetch(playerid, id){
    new query[80];
	playerClickFetchCharacter[playerid] = true;
    if(id){
	    PlayerData[playerid][pID] = id;
	    mysql_format(dbCon, query, sizeof(query), "SELECT * FROM `characters` WHERE `ID` = %d AND `A_ID` = %d LIMIT 1", PlayerData[playerid][pID], AccountData[playerid][uSQLID]);
	    return mysql_tquery(dbCon, query, "Character_Load", "i", playerid);
    }
    else{
    	Character_Create(playerid);
    }
    return true;
}

Character_Create(playerid){
	Dialog_ShowEasy(playerid, CREATECHARACTER, DIALOG_STYLE_INPUT, "การสร้างตัวละคร", "กรุณาใส่ชื่อตัวละครใหม่ของคุณด้านล่าง:\n\nคำเตือน: ชื่อของคุณต้องอยู่ในรูปแบบ Firstname_Lastname และไม่เกิน 64 ตัวอักษร เช่น Justin_Cotner:", "สร้าง","ยกเลิก");
	return 1;
}

//LoadPlayer
forward Character_Load(playerid);
public Character_Load(playerid){
    if(cache_num_rows()) {
	    cache_get_value_name(0, "Username", PlayerData[playerid][pUsername], 64);
		cache_get_value_name_int(0, "A_ID", PlayerData[playerid][pA_ID]);
	    cache_get_value_name_int(0, "Level", PlayerData[playerid][pLevel]);
	    cache_get_value_name_int(0, "Cash", PlayerData[playerid][pCash]);
		cache_get_value_name_int(0, "Admin", PlayerData[playerid][pAdmin]);
		cache_get_value_name_int(0, "UseSkin", PlayerData[playerid][pUseSkin]);
	    cache_get_value_name_int(0, "Skin", PlayerData[playerid][pSkin]);
		cache_get_value_name_int(0, "Gender", PlayerData[playerid][pGender]);
		cache_get_value_name_int(0, "Age", PlayerData[playerid][pAge]);
		cache_get_value_name_int(0, "Exp", PlayerData[playerid][pExp]);
	    cache_get_value_name_float(0, "PosX", PlayerData[playerid][pPosX]);
	    cache_get_value_name_float(0, "PosY", PlayerData[playerid][pPosY]);
	    cache_get_value_name_float(0, "PosZ", PlayerData[playerid][pPosZ]);
	    cache_get_value_name_float(0, "Angle", PlayerData[playerid][pAngle]);
	    cache_get_value_name_int(0, "Interior", PlayerData[playerid][pInterior]);
	    cache_get_value_name_int(0, "World", PlayerData[playerid][pWorld]);
		cache_get_value_name_float(0, "HP", PlayerData[playerid][pHP]);
		cache_get_value_name_float(0, "AM", PlayerData[playerid][pAM]);
		cache_get_value_name_int(0, "Job", PlayerData[playerid][pJob]);
		cache_get_value_name_int(0, "MaxItem", PlayerData[playerid][pMaxItem]);
		cache_get_value_name_int(0, "ItemAmount", PlayerData[playerid][pItemAmount]);
		cache_get_value_name_float(0, "InvMaxWeight", PlayerData[playerid][pInvMaxWeight]);
		cache_get_value_name_int(0, "Injured", PlayerData[playerid][pInjured]);
		cache_get_value_name_int(0, "InjuredTime", PlayerData[playerid][pInjuredTime]);
		cache_get_value_name_float(0, "InjuredPosX", PlayerData[playerid][pInjuredPos][0]);
		cache_get_value_name_float(0, "InjuredPosY", PlayerData[playerid][pInjuredPos][1]);
		cache_get_value_name_float(0, "InjuredPosZ", PlayerData[playerid][pInjuredPos][2]);
		cache_get_value_name_float(0, "InjuredPosA", PlayerData[playerid][pInjuredPos][3]);
		cache_get_value_name_int(0, "InjuredWorld", PlayerData[playerid][pInjuredWorld]);
		cache_get_value_name_int(0, "InjuredInt", PlayerData[playerid][pInjuredInt]);
		cache_get_value_name_int(0, "Vip", PlayerData[playerid][pVip]);
		cache_get_value_name_int(0, "VipDay", PlayerData[playerid][pVipDay]);
		cache_get_value_name_int(0, "VipMonth", PlayerData[playerid][pVipMonth]);
		cache_get_value_name_int(0, "VipYear", PlayerData[playerid][pVipYear]);
		cache_get_value_name_int(0, "VipHour", PlayerData[playerid][pVipHour]);
		cache_get_value_name_int(0, "Minutes", PlayerData[playerid][pMinutes]);
		cache_get_value_name_int(0, "Ban", PlayerData[playerid][pBan]);
		cache_get_value_name_int(0, "IsPassAdmin", PlayerData[playerid][pIsPassAdmin]);
		cache_get_value_name(0, "PassAdmin", PlayerData[playerid][pPassAdmin], 64);
		cache_get_value_name_int(0, "Playerhour", PlayerData[playerid][pPlayerhour]);

		cache_get_value_name_int(0, "Hunger", PlayerData[playerid][pHunger]);
		cache_get_value_name_int(0, "Water", PlayerData[playerid][pWater]);
		cache_get_value_name_int(0, "Energy", PlayerData[playerid][pEnergy]);
		cache_get_value_name_int(0, "Shower", PlayerData[playerid][pShower]);
		cache_get_value_name_int(0, "Stress", PlayerData[playerid][pStress]);

		cache_get_value_name_int(0, "BoxLevel1", PlayerData[playerid][pBoxLevel1]);
		cache_get_value_name_int(0, "BoxLevel5", PlayerData[playerid][pBoxLevel5]);
		cache_get_value_name_int(0, "BoxLevel10", PlayerData[playerid][pBoxLevel10]);
		cache_get_value_name_int(0, "BoxLevel15", PlayerData[playerid][pBoxLevel15]);
		cache_get_value_name_int(0, "BoxLevel20", PlayerData[playerid][pBoxLevel20]);

		cache_get_value_name_int(0, "GroupID", PlayerData[playerid][pGroupID]);
		cache_get_value_name_int(0, "GroupRank", PlayerData[playerid][pGroupRank]);

		cache_get_value_name_int(0, "Whitelist", PlayerData[playerid][pWhitelist]);
		cache_get_value_name_int(0, "Warn", PlayerData[playerid][pWarn]);

		cache_get_value_name_int(0, "MyWeapon1", PlayerData[playerid][pMyWeapon][0]);
		cache_get_value_name_int(0, "MyWeapon2", PlayerData[playerid][pMyWeapon][1]);
		cache_get_value_name_int(0, "MyWeapon3", PlayerData[playerid][pMyWeapon][2]);

		cache_get_value_name_int(0, "MyAmmo1", PlayerData[playerid][pMyAmmo][0]);
		cache_get_value_name_int(0, "MyAmmo2", PlayerData[playerid][pMyAmmo][1]);
		cache_get_value_name_int(0, "MyAmmo3", PlayerData[playerid][pMyAmmo][2]);

		cache_get_value_name_int(0, "MyWeaponLevel1", PlayerData[playerid][pMyWeaponLevel][0]);
		cache_get_value_name_int(0, "MyWeaponLevel2", PlayerData[playerid][pMyWeaponLevel][1]);
		cache_get_value_name_int(0, "MyWeaponLevel3", PlayerData[playerid][pMyWeaponLevel][2]);

		cache_get_value_name_int(0, "InHospital", PlayerData[playerid][pInHospital]);
		cache_get_value_name_int(0, "HospitalType", PlayerData[playerid][pHospitalType]);

		cache_get_value_name_int(0, "RedMoney", PlayerData[playerid][pRedMoney]);

		cache_get_value_name_int(0, "Jail", PlayerData[playerid][pJail]);
		cache_get_value_name_int(0, "JailTime", PlayerData[playerid][pJailTime]);

		cache_get_value_name_int(0, "NumberPhone", PlayerData[playerid][pNumberPhone]);
		cache_get_value_name_int(0, "Idcard", PlayerData[playerid][pIdcard]);

		cache_get_value_name_int(0, "WeaponDealerSkills", PlayerData[playerid][pWeaponDealerSkills]);
		cache_get_value_name_int(0, "WeaponDealerExp", PlayerData[playerid][pWeaponDealerExp]);

		cache_get_value_name_int(0, "StorageGunPowder", PlayerData[playerid][pStorageWeaponCraft][0]);
		cache_get_value_name_int(0, "StorageWood", PlayerData[playerid][pStorageWeaponCraft][1]);
		cache_get_value_name_int(0, "StorageOre", PlayerData[playerid][pStorageWeaponCraft][2]);

		cache_get_value_name_int(0, "BuildItemWood", PlayerData[playerid][pBuildItemHome][0]);
		cache_get_value_name_int(0, "BuildItemOre", PlayerData[playerid][pBuildItemHome][1]);

		cache_get_value_name_int(0, "BankMoney", PlayerData[playerid][pBankMoney]);
		cache_get_value_name_int(0, "ActiveChar", PlayerData[playerid][pActiveChar]);
		cache_get_value_name_int(0, "Cuffed", PlayerData[playerid][pCuffed]);

		cache_get_value_name_int(0, "OnPlayerDuty", PlayerData[playerid][pOnPlayerDuty]);

		cache_get_value_name_int(0, "SavePow", PlayerData[playerid][pSavePow]);
		cache_get_value_name_int(0, "MicMute", PlayerData[playerid][pMicMute]);
		cache_get_value_name_int(0, "DelayWeapon1", PlayerData[playerid][pDelayWeapon][0]);
		cache_get_value_name_int(0, "DelayWeapon2", PlayerData[playerid][pDelayWeapon][1]);
		cache_get_value_name_int(0, "DelayWeapon3", PlayerData[playerid][pDelayWeapon][2]);

		cache_get_value_name_int(0, "FirstTime", PlayerData[playerid][pFirstTime]);
		cache_get_value_name(0, "AdminName", PlayerData[playerid][pAdminName], 64);

		cache_get_value_name_int(0, "RentHome", PlayerData[playerid][pRentHome]);

		cache_get_value_name_int(0, "MarrySQLID", PlayerData[playerid][pMarrySQLID]);
		cache_get_value_name(0, "MarryName", PlayerData[playerid][pMarryName], 64);
		cache_get_value_name_int(0, "MarryLevel", PlayerData[playerid][pMarryLevel]);
		cache_get_value_name(0, "MarryDate", PlayerData[playerid][pMarryDate], 64);
		cache_get_value_name_int(0, "MarrySkin", PlayerData[playerid][pMarrySkin]);
		cache_get_value_name_int(0, "MarryKissed", PlayerData[playerid][pMarryKissed]);
		cache_get_value_name_int(0, "MarryGetGift", PlayerData[playerid][pMarryGetGift]);

		cache_get_value_name(0, "AccessoryNameHat", PlayerData[playerid][pAccessoryNameHat], 32);
		cache_get_value_name_int(0, "AccessoryModelHat", PlayerData[playerid][pAccessoryModelHat]);
		cache_get_value_name(0, "AccessoryNameGlasses", PlayerData[playerid][pAccessoryNameGlasses], 32);
		cache_get_value_name_int(0, "AccessoryModelGlasses", PlayerData[playerid][pAccessoryModelGlasses]);
		cache_get_value_name(0, "AccessoryNameBody", PlayerData[playerid][pAccessoryNameBody], 32);
		cache_get_value_name_int(0, "AccessoryModelBody", PlayerData[playerid][pAccessoryModelBody]);
		cache_get_value_name(0, "AccessoryNameArms", PlayerData[playerid][pAccessoryNameArms], 32);
		cache_get_value_name_int(0, "AccessoryModelArms", PlayerData[playerid][pAccessoryModelArms]);

		cache_get_value_name_int(0, "AccessoryShowHat", PlayerData[playerid][pAccessoryShowHat]);
		cache_get_value_name_int(0, "AccessoryShowGlasses", PlayerData[playerid][pAccessoryShowGlasses]);
		cache_get_value_name_int(0, "AccessoryShowBody", PlayerData[playerid][pAccessoryShowBody]);
		cache_get_value_name_int(0, "AccessoryShowArms", PlayerData[playerid][pAccessoryShowArms]);

		new string1[128];
		cache_get_value_name(0, "AccessoryPosHat", string1, sizeof(string1));
		sscanf(string1, "p<|>fffffffff", AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);

		new string2[128];
		cache_get_value_name(0, "AccessoryPosGlasses", string2, sizeof(string2));
		sscanf(string2, "p<|>fffffffff", AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);

		new string3[128];
		cache_get_value_name(0, "AccessoryPosBody", string3, sizeof(string3));
		sscanf(string3, "p<|>fffffffff", AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);

		new string4[128];
		cache_get_value_name(0, "AccessoryPosArms", string4, sizeof(string4));
		sscanf(string4, "p<|>fffffffff", AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
	
		cache_get_value_name_int(0, "AccessoryEditHat", PlayerData[playerid][pAccessoryEditHat]);
		cache_get_value_name_int(0, "AccessoryEditGlasses", PlayerData[playerid][pAccessoryEditGlasses]);
		cache_get_value_name_int(0, "AccessoryEditBody", PlayerData[playerid][pAccessoryEditBody]);
		cache_get_value_name_int(0, "AccessoryEditArms", PlayerData[playerid][pAccessoryEditArms]);
		cache_get_value_name_int(0, "AccessoryArmsType", PlayerData[playerid][pAccessoryArmsType]);

		cache_get_value_name_int(0, "AccessoryAllSetShow", PlayerData[playerid][pAccessoryAllSetShow]);
		cache_get_value_name(0, "AccessoryAllSet", PlayerData[playerid][pAccessoryAllSet], 64);

		cache_get_value_name_int(0, "FailStack", PlayerData[playerid][pFailStack]);

		cache_get_value_name_int(0, "SharkJobExp", PlayerData[playerid][pSharkJobExp]);
		cache_get_value_name_int(0, "SharkJobLevel", PlayerData[playerid][pSharkJobLevel]);

		cache_get_value_name_int(0, "ChayaHead", PlayerData[playerid][pChayaHead]);
		cache_get_value_name(0, "ChayaHeadMessage", PlayerData[playerid][pChayaHeadMessage], 64);

		cache_get_value_name_int(0, "PlantJobExp", PlayerData[playerid][pPlantJobExp]);
		cache_get_value_name_int(0, "PlantJobLevel", PlayerData[playerid][pPlantJobLevel]);

		cache_get_value_name_int(0, "DelayFlagWar", PlayerDelayFlagWar[playerid]);

		cache_get_value_name_int(0, "RacingWin", PlayerData[playerid][pRacingWin]);
		cache_get_value_name_int(0, "RacingLose", PlayerData[playerid][pRacingLose]);

		cache_get_value_name_int(0, "TimeQuitGang", PlayerData[playerid][pTimeQuitGang]);

		cache_get_value_name_int(0, "InventoryColor", PlayerInventoryCodeColor[playerid]);
        cache_get_value_name_int(0, "InventoryHoverColor", PlayerInventoryHoverCodeColor[playerid]);
		cache_get_value_name_float(0, "InventoryPostionX", PlayerPositionInventoryX[playerid]);
        cache_get_value_name_float(0, "InventoryPostionY", PlayerPositionInventoryY[playerid]);

		cache_get_value_name_int(0, "PlayerInventoryColorR", PlayerInventoryColorR[playerid]);
		cache_get_value_name_int(0, "PlayerInventoryColorG", PlayerInventoryColorG[playerid]);
		cache_get_value_name_int(0, "PlayerInventoryColorB", PlayerInventoryColorB[playerid]);
	
		cache_get_value_name_int(0, "PlayerQuestAccept", PlayerQuestAccept[playerid]);
		cache_get_value_name_int(0, "PlayerQuestState", PlayerQuestState[playerid]);

		cache_get_value_name_int(0, "TotalOpenBox", PlayerData[playerid][pTotalOpenBox]);

		cache_get_value_name_int(0, "ChayaLogin", PlayerData[playerid][pChayaLogin]);
		cache_get_value_name(0, "ChayaLoginMessage", PlayerData[playerid][pChayaLoginMessage], 64);
		cache_get_value_name_int(0, "PassDrivingTest", PlayerData[playerid][pPassDrivingTest]);

		cache_get_value_name_int(0, "PlayerFreeGetCar", PlayerData[playerid][pPlayerFreeGetCar]);
		cache_get_value_name_int(0, "RepairKitBuying", PlayerData[playerid][pRepairKitBuying]);
		cache_get_value_name_int(0, "BandageBuying", PlayerData[playerid][pBandageBuying]);
		cache_get_value_name_int(0, "UseExpx2", PlayerData[playerid][pUseExpx2]);
		cache_get_value_name_int(0, "InBoxing", PlayerEnterBoxing[playerid]);
	}

	if(PlayerData[playerid][pA_ID] != AccountData[playerid][uSQLID]){
		ErrorMsg(playerid, "เกิดข้อผิดพลาดไอดีตัวละครไม่ตรงกับชื่อผู้ใช้");
		return SetTimerEx("FixKick", 200, false, "d", playerid);
	}
	
	if(!IsValidRpName(PlayerData[playerid][pUsername])){
		ErrorMsg(playerid, "ชื่อไม่ถูกต้อง");
		return SetTimerEx("FixKick", 200, false, "d", playerid);
	}

	SetPlayerName(playerid, PlayerData[playerid][pUsername]);

	if(PlayerData[playerid][pLevel] == 0){
		TogglePlayerSpectating(playerid, 1);
		TogglePlayerControllable(playerid, 0);
		SetTimerEx("SetCamera", 500, false, "i", playerid);
		return Register(playerid);
	}

	GivePlayerMoney(playerid, PlayerData[playerid][pCash]);
	SetPlayerScore(playerid, PlayerData[playerid][pSelectChar]);
	GetPlayerIp(playerid, PlayerData[playerid][pLastIP], 16);

	if(PlayerData[playerid][pBan] == 1){
		ErrorMsg(playerid, "ตัวละครนี้ของคุณถูก 'แบน' ไม่สามารถเข้าเล่นได้");
		return SetTimerEx("FixKick", 500, false, "d", playerid);
	}

	new str[128];
	mysql_format(dbCon, str, sizeof(str), "SELECT * FROM `blacklist` WHERE `Username` = '%e' OR `IP` = '%e'", AccountData[playerid][uName], PlayerData[playerid][pLastIP]);
	mysql_tquery(dbCon, str, "OnPlayerBlacklist", "d", playerid);

	if(!UserNameValidator(ReturnName(playerid))){
		return Kick(playerid);
	}

	CancelSelectTextDraw(playerid);
	SelectCharTextDraw[playerid] = false;
	for(new i=0; i<15; i++){
		PlayerTextDrawHide(playerid, CharSelect[playerid][i]);
		PlayerTextDrawDestroy(playerid, CharSelect[playerid][i]);
	}

	SendClientMessage(playerid, COLOR_SERVER, "==============================================");
	format(str, sizeof(str), "{23D101}| {FFFFFF}คุณได้เลือกเข้าสู่ระบบตัวละคร: %s", ReturnRoleplayName(playerid));
	SendClientMessage(playerid, COLOR_SERVER, str);

	if(PlayerData[playerid][pVipDay] == 0 && PlayerData[playerid][pVipMonth] != 0){
		PlayerData[playerid][pVipDay] = 1;
	}

	if(PlayerData[playerid][pVip] != 0){
		new stringvip[64];
		if(PlayerData[playerid][pVip] == 1) stringvip = "Bronze Member";
		else if(PlayerData[playerid][pVip] == 2) stringvip = "Silver Member";
		else if(PlayerData[playerid][pVip] == 3) stringvip = "Gold Member";

		new tmphour, tmpminute, tmpsecond;
		gettime(tmphour, tmpminute, tmpsecond);
		new Day, Month, Year;
		getdate(Year, Month, Day);

		new string[128];
		SendClientMessageEx(playerid, COLOR_SERVER, "{23D101}| [Vip] {FFFFFF}%s ของคุณจะหมดอายุภายใน วันที่ %d เดือน %d ปี %d เวลา %d:00", stringvip, PlayerData[playerid][pVipDay], PlayerData[playerid][pVipMonth], PlayerData[playerid][pVipYear], PlayerData[playerid][pVipHour]);
		if(Day >= PlayerData[playerid][pVipDay] && Month >= PlayerData[playerid][pVipMonth] && tmphour >= PlayerData[playerid][pVipHour]){
			format(string, sizeof(string), "%s ของ %s ได้หมดอายุแล้ว", stringvip, ReturnRoleplayName(playerid));
			SendAdminsMessage(1, 0x2F91FFAA, string);
			SendClientMessageEx(playerid, 0x2F91FFAA, "[หมดอายุ]: %s ของคุณได้หมดอายุแล้ว", stringvip);
			Log_Write("logs/vip_log.txt", "[%s] VIP %s's %s expire", ReturnDate(), stringvip, ReturnRoleplayName(playerid));
			PlayerData[playerid][pVip] = 0;
			PlayerData[playerid][pVipDay] = 0;
			PlayerData[playerid][pVipMonth] = 0;
			PlayerData[playerid][pVipHour] = 0;
		}

		if(Year > PlayerData[playerid][pVipYear]){
			format(string, sizeof(string), "%s ของ %s ได้หมดอายุแล้ว", stringvip, ReturnRoleplayName(playerid));
			SendAdminsMessage(1, 0x2F91FFAA, string);
			SendClientMessageEx(playerid, 0x2F91FFAA, "[หมดอายุ]: %s ของคุณได้หมดอายุแล้ว", stringvip);
			Log_Write("logs/vip_log.txt", "[%s] VIP %s's %s expire", ReturnDate(), stringvip, ReturnRoleplayName(playerid));
			PlayerData[playerid][pVip] = 0;
			PlayerData[playerid][pVipDay] = 0;
			PlayerData[playerid][pVipMonth] = 0;
			PlayerData[playerid][pVipHour] = 0;
		}
	}

	if(PlayerData[playerid][pChayaLogin]){
		if(!strcmp(PlayerData[playerid][pChayaLoginMessage], "NULL", true)){
			printf("%s Not Show Chaya Login", ReturnRoleplayName(playerid));
		}
		else SendClientMessageToAllEx(-1, "%s %s ได้เข้าเมืองเรียบร้อยแล้ว", PlayerData[playerid][pChayaLoginMessage], ReturnRoleplayName(playerid));
	}

	SendClientMessageEx(playerid, COLOR_SERVER, "{23D101}| [Warning] {FFFFFF}คุณถูกเตือนมาแล้ว %d/3 หากครบ 3 ครั้งคุณจะถูกแบนทันที", PlayerData[playerid][pWarn]);
	SendClientMessage(playerid, COLOR_SERVER, "{23D101}| [Hint] {FFFFFF}หากต้องการออกไปหน้าเปลี่ยนตัวละครให้ กดปุ่ม 'H' > ออกจากระบบ");

	if(PlayerData[playerid][pInterior] == 0 && PlayerData[playerid][pWorld] != 0){
		PlayerData[playerid][pInterior] = 0;
		PlayerData[playerid][pWorld] = 0;
		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
		SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
	}

	AccountData[playerid][uActive] = 4;
	PlayerData[playerid][pActiveChar] = 4;

	GangZoneShowForPlayer(playerid, CampingZone, 0xFFFFFFAA);
	GangZoneShowForPlayer(playerid, Zone1, 0x00FF7FAA);
	GangZoneShowForPlayer(playerid, Zone2, 0x00FF7FAA);
	GangZoneShowForPlayer(playerid, LabelZone, 0xFF0000AA);

	if(PlayerData[playerid][pAdmin] >= 1){
		if(PlayerData[playerid][pIsPassAdmin] == 0){
			Dialog_ShowEasy(playerid, PASSADMIN, DIALOG_STYLE_INPUT, "รหัสลับ", "กรุณาตั้งรหัสลับแอดมินของคุณ:", "ตกลง", "ยกเลิก");
		}
		else if(PlayerData[playerid][pIsPassAdmin] == 1){
			Dialog_ShowEasy(playerid, INPUTPASSADMIN, DIALOG_STYLE_PASSWORD, "รหัสลับ", "กรุณากรอกรหัสลับสำหรับแอดมิน:", "ตกลง", "ยกเลิก");
		}
	}
	

	if (PlayerData[playerid][pGroupID] != -1) {
		PlayerData[playerid][pGroup] = GetGroupByID(PlayerData[playerid][pGroupID]);

		if (PlayerData[playerid][pGroup] == -1) {
			ResetGroup(playerid);
		}
	}

	if(PlayerData[playerid][pMicMute] == 1){
		SvMutePlayerEnable(playerid);
		SendClientMessage(playerid, COLOR_RED, "- คุณถูกปิดการใช้งานไมค์โครโฟนอยู่");
	}

	SetTimerEx("StopSong", 3000, false, "i", playerid);

	if (lstream[playerid]) {
		SvAttachListenerToStream(lstream[playerid], playerid);
		SvAttachSpeakerToStream(lstream[playerid], playerid);
		SvUpdateDistanceForLStream(lstream[playerid], 15.0);
	}

	SvDetachListenerFromStream(police, playerid);
	SvDetachListenerFromStream(medic, playerid);
	SvDetachSpeakerFromStream(police, playerid);
	SvDetachSpeakerFromStream(medic, playerid);

	if(ServerRestart && ServerSeconds > 0){
		TextDrawShowForPlayer(playerid, RestartServer);
	}

	PlayerSetVariableStory(playerid);
	ShowSpeaker(playerid);

	LoggedIn[playerid] = true;
	playerClickFetchCharacter[playerid] = false;
	CheckSpawnDontPressH[playerid] = 1;
	SetTimerEx("UnLockPressH", 1000, false, "i", playerid);

	new query[512];
	format(query, sizeof(query), "SELECT * FROM `inventory` WHERE `itemOwner` = '%d' AND `itemSlot` > -1 LIMIT 108", PlayerData[playerid][pID]);
	mysql_tquery(dbCon, query, "PlayerLoadInventory", "d", playerid);

	if(PlayerData[playerid][pFirstTime]){
		SetSpawnInfo(playerid, NO_TEAM, 289, 1494.4642, 1303.8282, 1093.2891, 357.9944, 0, 0, 0, 0, 0, 0);
		SetPlayerInterior(playerid, 3);
		SetPlayerVirtualWorld(playerid, playerid+1);
	} else {
		SetSpawnInfo(playerid, NO_TEAM, PlayerData[playerid][pSkin], PlayerData[playerid][pPosX], PlayerData[playerid][pPosY], PlayerData[playerid][pPosZ], PlayerData[playerid][pAngle], 0, 0, 0, 0, 0, 0);
	}
	SpawnPlayer(playerid);
    return 1;
}

forward UnLockPressH(playerid);
public UnLockPressH(playerid){
	CheckSpawnDontPressH[playerid] = 0;
	return 1;
}

forward OnQueryFinished(extraid, threadid);
public OnQueryFinished(extraid, threadid){
	if (!IsPlayerConnected(extraid)) return 0;
		
	new rows;
	switch (threadid)
	{
        case THREAD_LOAD_TICKETS:
		{
		    cache_get_row_count(rows);

			for (new i = 0; i < rows && i < MAX_PLAYER_TICKETS; i ++) {
				cache_get_value_name(i, "ticketReason", TicketData[extraid][i][ticketReason], 64);
				cache_get_value_name(i, "ticketDate", TicketData[extraid][i][ticketDate], 36);
				cache_get_value_name(i, "ticketBy", TicketData[extraid][i][ticketBy], 64);

				TicketData[extraid][i][ticketExists] = true;
                cache_get_value_name_int(i, "ticketID", TicketData[extraid][i][ticketID]);
                cache_get_value_name_int(i, "ticketFee", TicketData[extraid][i][ticketFee]);
			}

			new query[128];
			format(query, sizeof(query), "SELECT * FROM `contacts` WHERE `ID` = '%d'", PlayerData[extraid][pID]);
			mysql_tquery(dbCon, query, "OnQueryFinished", "dd", extraid, THREAD_LOAD_CONTACTS);
			return true;
		}
		case THREAD_LOAD_CONTACTS:
		{
		    cache_get_row_count(rows);

			for (new i = 0; i < rows && i < MAX_CONTACTS; i ++) {
				cache_get_value_name(i, "contactName", ContactData[extraid][i][contactName], 32);

				ContactData[extraid][i][contactExists] = true;
				cache_get_value_name_int(i, "contactID", ContactData[extraid][i][contactID]);
                cache_get_value_name_int(i, "contactNumber", ContactData[extraid][i][contactNumber]);
			}
			return true;
		}
	}
	return 1;
}

forward CheckIPBan(playerid);
public CheckIPBan(playerid){
	new
		ip[16],
		reason[128],
		date[36],
		rows;

	cache_get_row_count(rows);

	if (rows) {
		cache_get_value_name(0, "IP", ip, 16);
		cache_get_value_name(0, "Date", date, 36);
		cache_get_value_name(0, "Reason", reason, 128);

		if (!strcmp(PlayerData[playerid][pLastIP], ip, true))
		{
			Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Ban Notice", "ไอพีของคุณถูกแบนจากเซิฟเวอร์\n\nไอพี: %s\nวันที่: %s\nสาเหตุ: %s\n\nเพื่อยื่นคำร้องการโดนแบนครั้งนี้โปรดติดต่อผู้ดูแลระบบ", "ปิด", "", PlayerData[playerid][pLastIP], date, reason);
			SetTimerEx("FixKick", 500, false, "d", playerid);
		}
	}
	return 1;
}

forward OnPlayerBlacklist(playerid);
public OnPlayerBlacklist(playerid){
	if(!IsPlayerConnected(playerid)) return 0;

	new
		reason[128],
		date[36],
		username[64],
		rows;

	cache_get_row_count(rows);

	if (rows) {
		cache_get_value_name(0, "Username", username, 64);
		cache_get_value_name(0, "Date", date, 36);
		cache_get_value_name(0, "Reason", reason, 128);

		if (!strcmp(username, "null", true) || !username[0])
		{
			Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Ban Notice", "ไอพีของคุณถูกแบนจากเซิฟเวอร์\n\nไอพี: %s\nวันที่: %s\nสาเหตุ: %s\n\nเพื่อยื่นคำร้องการโดนแบนครั้งนี้โปรดติดต่อผู้ดูแลระบบ", "ปิด", "", PlayerData[playerid][pLastIP], date, reason);
			SetTimerEx("FixKick", 500, false, "d", playerid);
		}
		else
		{
			Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Ban Notice", "คุณถูกแบนจากเซิฟเวอร์\n\nชื่อผู้ใช้: %s\nวันที่: %s\nสาเหตุ: %s\n\nเพื่อยื่นคำร้องการโดนแบนครั้งนี้โปรดติดต่อผู้ดูแลระบบ", "ปิด", "", AccountData[playerid][uName], date, reason);
			SetTimerEx("FixKick", 500, false, "d", playerid);
		}
	}
	return 1;
}

Accounts_Save(playerid){
	new query[128];

	mysql_format(dbCon, query, sizeof(query), "UPDATE accounts SET Active = %d, InGame = %d WHERE SQLID = %d LIMIT 1",
		AccountData[playerid][uActive],
		AccountData[playerid][uInGame],
		AccountData[playerid][uSQLID]);
	mysql_tquery(dbCon, query);

	return 1;
}

//SavePlayer
Character_Save(playerid){
	if(LoggedIn[playerid]){
		new query[1024];
		GetPlayerHealth(playerid, PlayerData[playerid][pHP]);
		GetPlayerArmour(playerid, PlayerData[playerid][pAM]);
		
		GetPlayerPos(playerid, PlayerData[playerid][pPosX], PlayerData[playerid][pPosY], PlayerData[playerid][pPosZ]);
		GetPlayerFacingAngle(playerid, PlayerData[playerid][pAngle]);

		if(PlayerData[playerid][pInjured]){
			PlayerData[playerid][pInjuredPos][0] = PlayerData[playerid][pPosX];
			PlayerData[playerid][pInjuredPos][1] = PlayerData[playerid][pPosY];
			PlayerData[playerid][pInjuredPos][2] = PlayerData[playerid][pPosZ];
			PlayerData[playerid][pInjuredInt] = GetPlayerInterior(playerid);
			PlayerData[playerid][pInjuredWorld] = GetPlayerVirtualWorld(playerid);
		}

		mysql_format(dbCon, query, sizeof(query), "UPDATE accounts SET Active = %d, InGame = %d WHERE SQLID = %d LIMIT 1",
			AccountData[playerid][uActive],
			AccountData[playerid][uInGame],
			AccountData[playerid][uSQLID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET Level = %d, Cash = %d, Admin = %d, UseSkin = %d, Skin = %d, Gender = %d, Age = %d, Exp = %d, PosX = %f, PosY = %f, PosZ = %f, Angle = %f, Interior = %d, World = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pLevel],
			PlayerData[playerid][pCash],
			PlayerData[playerid][pAdmin],
			PlayerData[playerid][pUseSkin],
			PlayerData[playerid][pSkin],
			PlayerData[playerid][pGender],
			PlayerData[playerid][pAge],
			PlayerData[playerid][pExp],
		    PlayerData[playerid][pPosX],
			PlayerData[playerid][pPosY],
			PlayerData[playerid][pPosZ],
			PlayerData[playerid][pAngle],
			GetPlayerInterior(playerid),
			GetPlayerVirtualWorld(playerid),
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);


		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET LastIP = '%e', LastOnline = '%e', HP = %f, AM = %f, Job = %d, MaxItem = %d, ItemAmount = %d, InvMaxWeight = %f, Injured = %d, InjuredTime = %d, InjuredPosX = %f, InjuredPosY = %f, InjuredPosZ = %f, InjuredPosA = %f, InjuredWorld = %d, InjuredInt = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pLastIP],
			ReturnDate(),
			PlayerData[playerid][pHP],
			PlayerData[playerid][pAM],
			PlayerData[playerid][pJob],
			PlayerData[playerid][pMaxItem],
			PlayerData[playerid][pItemAmount],
			PlayerData[playerid][pInvMaxWeight],
			PlayerData[playerid][pInjured],
			PlayerData[playerid][pInjuredTime],
			PlayerData[playerid][pInjuredPos][0],
			PlayerData[playerid][pInjuredPos][1],
			PlayerData[playerid][pInjuredPos][2],
			PlayerData[playerid][pInjuredPos][3],
			PlayerData[playerid][pInjuredWorld],
			PlayerData[playerid][pInjuredInt],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET Vip = %d, VipDay = %d, VipMonth = %d, VipYear = %d, VipHour = %d, Minutes = %d, Ban = %d, IsPassAdmin = %d, PassAdmin = '%e', Playerhour = %d, Hunger = %d, Water = %d, Energy = %d, Shower = %d, Stress = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pVip],
			PlayerData[playerid][pVipDay],
			PlayerData[playerid][pVipMonth],
			PlayerData[playerid][pVipYear],
			PlayerData[playerid][pVipHour],
			PlayerData[playerid][pMinutes],
			PlayerData[playerid][pBan],
			PlayerData[playerid][pIsPassAdmin],
			PlayerData[playerid][pPassAdmin],
			PlayerData[playerid][pPlayerhour],
			PlayerData[playerid][pHunger],
			PlayerData[playerid][pWater],
			PlayerData[playerid][pEnergy],
			PlayerData[playerid][pShower],
			PlayerData[playerid][pStress],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET BoxLevel1 = %d, BoxLevel5 = %d, BoxLevel10 = %d, BoxLevel15 = %d, BoxLevel20 = %d, GroupID = %d, GroupRank = %d, Whitelist = %d, Warn = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pBoxLevel1],
			PlayerData[playerid][pBoxLevel5],
			PlayerData[playerid][pBoxLevel10],
			PlayerData[playerid][pBoxLevel15],
			PlayerData[playerid][pBoxLevel20],
			PlayerData[playerid][pGroupID],
			PlayerData[playerid][pGroupRank],
			PlayerData[playerid][pWhitelist],
			PlayerData[playerid][pWarn],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET MyWeapon1 = %d, MyWeapon2 = %d, MyWeapon3 = %d, MyAmmo1 = %d, MyAmmo2 = %d, MyAmmo3 = %d, InHospital = %d, HospitalType = %d, RedMoney = %d, Jail = %d, JailTime = %d, NumberPhone = %d, Idcard = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pMyWeapon][0],
			PlayerData[playerid][pMyWeapon][1],
			PlayerData[playerid][pMyWeapon][2],
			PlayerData[playerid][pMyAmmo][0],
			PlayerData[playerid][pMyAmmo][1],
			PlayerData[playerid][pMyAmmo][2],
			PlayerData[playerid][pInHospital],
			PlayerData[playerid][pHospitalType],
			PlayerData[playerid][pRedMoney],
			PlayerData[playerid][pJail],
			PlayerData[playerid][pJailTime],
			PlayerData[playerid][pNumberPhone],
			PlayerData[playerid][pIdcard],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET WeaponDealerSkills = %d, WeaponDealerExp = %d, StorageGunPowder = %d, StorageWood = %d, StorageOre = %d, BuildItemWood = %d, BuildItemOre = %d, BankMoney = %d, ActiveChar = %d, Cuffed = %d, OnPlayerDuty = %d, SavePow = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pWeaponDealerSkills],
			PlayerData[playerid][pWeaponDealerExp],
			PlayerData[playerid][pStorageWeaponCraft][0],
			PlayerData[playerid][pStorageWeaponCraft][1],
			PlayerData[playerid][pStorageWeaponCraft][2],
			PlayerData[playerid][pBuildItemHome][0],
			PlayerData[playerid][pBuildItemHome][1],
			PlayerData[playerid][pBankMoney],
			PlayerData[playerid][pActiveChar],
			PlayerData[playerid][pCuffed],
			PlayerData[playerid][pOnPlayerDuty],
			PlayerData[playerid][pSavePow],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET MicMute = %d, DelayWeapon1 = %d, DelayWeapon2 = %d, DelayWeapon3 = %d, FirstTime = %d, AdminName = '%e', RentHome = %d, MarrySQLID = %d, MarryName = '%e', MarryLevel = %d, MarryDate = '%e', MarrySkin = %d, MarryKissed = %d, MarryGetGift = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pMicMute],
			PlayerData[playerid][pDelayWeapon][0],
			PlayerData[playerid][pDelayWeapon][1],
			PlayerData[playerid][pDelayWeapon][2],
			PlayerData[playerid][pFirstTime],
			PlayerData[playerid][pAdminName],
			PlayerData[playerid][pRentHome],
			PlayerData[playerid][pMarrySQLID],
			PlayerData[playerid][pMarryName],
			PlayerData[playerid][pMarryLevel],
			PlayerData[playerid][pMarryDate],
			PlayerData[playerid][pMarrySkin],
			PlayerData[playerid][pMarryKissed],
			PlayerData[playerid][pMarryGetGift],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET AccessoryNameHat = '%e', AccessoryModelHat = %d, AccessoryNameGlasses = '%e', AccessoryModelGlasses = %d, AccessoryNameBody = '%e', AccessoryModelBody = %d, AccessoryNameArms = '%e', AccessoryModelArms = %d, AccessoryShowHat = %d, AccessoryShowGlasses = %d, AccessoryShowBody = %d, AccessoryShowArms = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pAccessoryNameHat],
			PlayerData[playerid][pAccessoryModelHat],
			PlayerData[playerid][pAccessoryNameGlasses],
			PlayerData[playerid][pAccessoryModelGlasses],
			PlayerData[playerid][pAccessoryNameBody],
			PlayerData[playerid][pAccessoryModelBody],
			PlayerData[playerid][pAccessoryNameArms],
			PlayerData[playerid][pAccessoryModelArms],
			PlayerData[playerid][pAccessoryShowHat],
			PlayerData[playerid][pAccessoryShowGlasses],
			PlayerData[playerid][pAccessoryShowBody],
			PlayerData[playerid][pAccessoryShowArms],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET `AccessoryPosHat` = '%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f' WHERE ID = %d LIMIT 1",
			AccessoryData[playerid][0][0],
			AccessoryData[playerid][0][1],
			AccessoryData[playerid][0][2],
			AccessoryData[playerid][0][3],
			AccessoryData[playerid][0][4],
			AccessoryData[playerid][0][5],
			AccessoryData[playerid][0][6],
			AccessoryData[playerid][0][7],
			AccessoryData[playerid][0][8],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET `AccessoryPosGlasses` = '%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f' WHERE ID = %d LIMIT 1",
			AccessoryData[playerid][1][0],
			AccessoryData[playerid][1][1],
			AccessoryData[playerid][1][2],
			AccessoryData[playerid][1][3],
			AccessoryData[playerid][1][4],
			AccessoryData[playerid][1][5],
			AccessoryData[playerid][1][6],
			AccessoryData[playerid][1][7],
			AccessoryData[playerid][1][8],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET `AccessoryPosBody` = '%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f' WHERE ID = %d LIMIT 1",
			AccessoryData[playerid][2][0],
			AccessoryData[playerid][2][1],
			AccessoryData[playerid][2][2],
			AccessoryData[playerid][2][3],
			AccessoryData[playerid][2][4],
			AccessoryData[playerid][2][5],
			AccessoryData[playerid][2][6],
			AccessoryData[playerid][2][7],
			AccessoryData[playerid][2][8],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET `AccessoryPosArms` = '%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f' WHERE ID = %d LIMIT 1",
			AccessoryData[playerid][3][0],
			AccessoryData[playerid][3][1],
			AccessoryData[playerid][3][2],
			AccessoryData[playerid][3][3],
			AccessoryData[playerid][3][4],
			AccessoryData[playerid][3][5],
			AccessoryData[playerid][3][6],
			AccessoryData[playerid][3][7],
			AccessoryData[playerid][3][8],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET AccessoryEditHat = %d, AccessoryEditGlasses = %d, AccessoryEditBody = %d, AccessoryEditArms = %d, AccessoryArmsType = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pAccessoryEditHat],
			PlayerData[playerid][pAccessoryEditGlasses],
			PlayerData[playerid][pAccessoryEditBody],
			PlayerData[playerid][pAccessoryEditArms],
			PlayerData[playerid][pAccessoryArmsType],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET MyWeaponLevel1 = %d, MyWeaponLevel2 = %d, MyWeaponLevel3 = %d, FailStack = %d, SharkJobExp = %d, SharkJobLevel = %d, ChayaHead = %d, ChayaHeadMessage = '%e', PlantJobExp = %d, PlantJobLevel = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pMyWeaponLevel][0],
			PlayerData[playerid][pMyWeaponLevel][1],
			PlayerData[playerid][pMyWeaponLevel][2],
			PlayerData[playerid][pFailStack],
			PlayerData[playerid][pSharkJobExp],
			PlayerData[playerid][pSharkJobLevel],
			PlayerData[playerid][pChayaHead],
			PlayerData[playerid][pChayaHeadMessage],
			PlayerData[playerid][pPlantJobExp],
			PlayerData[playerid][pPlantJobLevel],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET DelayFlagWar = %d, RacingWin = %d, RacingLose = %d, TimeQuitGang = %d, InventoryColor = '%d', InventoryHoverColor = '%d', InventoryPostionX = %f, InventoryPostionY = %f, PlayerQuestAccept = %d, PlayerQuestState = %d WHERE ID = %d LIMIT 1",
			PlayerDelayFlagWar[playerid],
			PlayerData[playerid][pRacingWin],
			PlayerData[playerid][pRacingLose],
			PlayerData[playerid][pTimeQuitGang],
			PlayerInventoryCodeColor[playerid],
            PlayerInventoryHoverCodeColor[playerid],
			PlayerPositionInventoryX[playerid],
            PlayerPositionInventoryY[playerid],
			PlayerQuestAccept[playerid],
			PlayerQuestState[playerid],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET TotalOpenBox = %d, ChayaLogin = %d, ChayaLoginMessage = '%e', PlayerInventoryColorR = %d, PlayerInventoryColorG = %d, PlayerInventoryColorB = %d, PassDrivingTest = %d, PlayerFreeGetCar = %d, AccessoryAllSet = '%e', AccessoryAllSetShow = %d, RepairKitBuying = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pTotalOpenBox],
			PlayerData[playerid][pChayaLogin],
			PlayerData[playerid][pChayaLoginMessage],
			PlayerInventoryColorR[playerid],
			PlayerInventoryColorG[playerid],
			PlayerInventoryColorB[playerid],
			PlayerData[playerid][pPassDrivingTest],
			PlayerData[playerid][pPlayerFreeGetCar],
			PlayerData[playerid][pAccessoryAllSet],
			PlayerData[playerid][pAccessoryAllSetShow],
			PlayerData[playerid][pRepairKitBuying],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);

		mysql_format(dbCon, query, sizeof(query), "UPDATE characters SET BandageBuying = %d, UseExpx2 = %d, InBoxing = %d WHERE ID = %d LIMIT 1",
			PlayerData[playerid][pBandageBuying],
			PlayerData[playerid][pUseExpx2],
			PlayerEnterBoxing[playerid],
			PlayerData[playerid][pID]);
		mysql_tquery(dbCon, query);
	}
	return true;
}

Dialog:CREATECHARACTER(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		KickPlayer(playerid);
		return 0;
	}

    else if(response)
    {
        if(IsValidRpName(inputtext))
		{
			format(PlayerData[playerid][pUsername], 64, "%s", inputtext);

			if(!PlayerData[playerid][pLoadingNameTime]){
				GameTextForPlayer(playerid,"~n~~n~~y~Loading....",3500,3);
				PlayerData[playerid][pLoadingNameTime] = SetTimerEx("LoadingCheckName", 3000, false, "i", playerid);
			}
		}
		else
		{
		    ErrorMsg(playerid, "ชื่อไม่ถูกต้อง!!.");
		    Dialog_ShowEasy(playerid, CREATECHARACTER, DIALOG_STYLE_INPUT, "การสร้างตัวละคร", "กรุณาใส่ชื่อตัวละครใหม่ของคุณด้านล่าง:\n\nคำเตือน: ชื่อของคุณต้องอยู่ในรูปแบบ Firstname_Lastname และไม่เกิน 64 ตัวอักษร เช่น Justin_Cotner:", "สร้าง","ยกเลิก");
		}
	}
    return 1;
}

forward LoadingCheckName(playerid);
public LoadingCheckName(playerid){
	DBNameCheck(playerid, PlayerData[playerid][pUsername]);
	return 1;
}

stock DBNameCheck(playerid, const string[])
{
	new query[128];
	mysql_format(dbCon, query, sizeof(query), "SELECT * FROM `characters` WHERE `Username` = '%e' LIMIT 1", string);
	mysql_tquery(dbCon, query, "FreeNameCheck", "i", playerid);
	return 1;
}

forward FreeNameCheck(playerid);
public FreeNameCheck(playerid)
{
 	if(cache_num_rows()){
		ErrorMsg(playerid, "ชื่อนี้มีผู้ใช้งานแล้ว!");
		KillTimer(PlayerData[playerid][pLoadingNameTime]);
		format(PlayerData[playerid][pUsername], 64, "");
		Dialog_ShowEasy(playerid, CREATECHARACTER, DIALOG_STYLE_INPUT, "การสร้างตัวละคร", "กรุณาใส่ชื่อตัวละครใหม่ของคุณด้านล่าง:\n\nคำเตือน: ชื่อของคุณต้องอยู่ในรูปแบบ Firstname_Lastname และไม่เกิน 64 ตัวอักษร เช่น Justin_Cotner:", "สร้าง","ยกเลิก");
    }
    else{
		new query[256];
		GetPlayerIp(playerid, PlayerData[playerid][pRegisterIP], 16);
		mysql_format(dbCon, query, sizeof(query), "INSERT INTO `characters` (A_ID, Username, RegisterIP, RegisterDate) VALUES(%d, '%e', '%e', '%e')", AccountData[playerid][uSQLID], PlayerData[playerid][pUsername], PlayerData[playerid][pRegisterIP], ReturnDate());
		mysql_tquery(dbCon, query, "GetCharacterID", "i", playerid);
		SetPlayerName(playerid, PlayerData[playerid][pUsername]);
		Register(playerid);
    }
	return 1;
}

Account_Reset(playerid){
	for(new i; userdata:i < userdata; i++)
    	AccountData[playerid][userdata:i] = 0;
	return 1;
}

forward Character_Reset(playerid);
public Character_Reset(playerid){

    for(new i; playerdata:i < playerdata; i++) PlayerData[playerid][playerdata:i] = 0;

	ResetPlayer_Inventory(playerid);

	PlayerData[playerid][pGroup] = -1;
	PlayerData[playerid][pMyWeapon][0] = 0;
	PlayerData[playerid][pMyWeapon][1] = 0;
	PlayerData[playerid][pMyWeapon][2] = 0;
	PlayerData[playerid][pMyAmmo][0] = 0;
	PlayerData[playerid][pMyAmmo][1] = 0;
	PlayerData[playerid][pMyAmmo][2] = 0;
	PlayerData[playerid][pMyWeaponLevel][0] = 0;
	PlayerData[playerid][pMyWeaponLevel][1] = 0;
	PlayerData[playerid][pMyWeaponLevel][2] = 0;

	PlayerData[playerid][pStunned] = 0;

	ResetPlayerWeapons(playerid);

	KillTimer(PlayerData[playerid][pAidTimer]);
	PlayerData[playerid][pFirstAid] = false;

	ResetPlayerCircleProgressbar(playerid);

	SetPlayerSkin(playerid, 1);
	ResetPlayerMoney(playerid);
	SetPlayerScore(playerid, 0);

	ResetFarmerJob(playerid);
	ResetBuildJob(playerid);
	ResetFishJob(playerid);
	ResetGasJob(playerid);
	ResetCowJob(playerid);

	ResetCutWoodJob(playerid);
	Reset_Mine(playerid);

	ResetPlayerCrafting(playerid);

	SetPlayerPlane[playerid] = 0;
	EnterCheckPointJob[playerid] = 0;
	CheckToggleAlert[playerid] = 0;
	TimeInjuredStart[playerid] = 0;
	SetStartTimeHospital[playerid] = 0;
	HospitalHealth[playerid] = 0;

	AdminDuty[playerid] = 0;
	GetJobID[playerid] = -1;
	GetConfirmJoinJob[playerid] = 0;
	IDPlayerGetVIP[playerid] = -1;
	TogVehSpeedo[playerid] = 0;
	DelayOOCandTW[playerid] = 0;

	PlayerToggleRightVehSpeedo[playerid] = false;
	PlayerToggleLeftVehSpeedo[playerid] = false;

	for(new i=0; i<10; i++){
		GetCarIDGarage[playerid][i] = -1;
	}

	PlayerOpenFoodShop[playerid] = false;
	PlayerCarryFood[playerid] = false;
	PlayerCarryFoodType[playerid] = 0;

	if(PlayerSitTable[playerid] != -1){
		if(PlayerTable[playerid] == 1){
			EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][PlayerSitTable[playerid]] = false;
		}
		else if(PlayerTable[playerid] == 2){
			EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][PlayerSitTable[playerid]] = false;
		}
		else if(PlayerTable[playerid] == 3){
			EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][PlayerSitTable[playerid]] = false;
		}
		else if(PlayerTable[playerid] == 4){
			EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][PlayerSitTable[playerid]] = false;
		}
	}

	PlayerSitTable[playerid] = -1;
	PlayerTable[playerid] = 0;

	stop PlayerUpdateFood[playerid];
	PlayerTempHunger[playerid] = 0;
	PlayerTempWater[playerid] = 0;

	PlayerData[playerid][pSpec] = INVALID_PLAYER_ID;
	GetPlayerGiveMoneyID[playerid] = INVALID_PLAYER_ID;
	EditCarIDSell[playerid] = -1;
	GetCarBuy[playerid] = -1;
	PlayerData[playerid][pSelectedSlot] = -1;
	PlayerData[playerid][pGroupEdit] = -1;
	ResetGroup(playerid);

	for(new i=0; i<10; i++){
		GetCarIDDestroy[playerid][i] = -1;
	}

	if (BitFlag_Get(g_PlayerFlags[playerid], PLAYER_ONDUTY)) {
		ResetPlayerWeapons(playerid);
	}

	BitFlag_Off(g_PlayerFlags[playerid], PLAYER_ONDUTY);

	GetCarIDDestroyConfirm[playerid] = 0;
	PlayerData[playerid][pGroupOffer] = INVALID_PLAYER_ID;
    PlayerData[playerid][pGroupOffed] = -1;
	ToggleLogo[playerid] = 0;
	CallMedic[playerid] = 0;

	PlayerGetAttackNpc[playerid] = INVALID_PLAYER_ID;

	ResetDrugPlayer(playerid);
	ResetPoliceVar(playerid);

	ResetJellyFish(playerid);

	TargetChangePassID[playerid] = -1;

	PlayerData[playerid][pRefill] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pRefillPrice] = 0;
	PlayerData[playerid][pGasPump] = -1;

	PlayerUsingPhone[playerid] = 0;
	PlayerData[playerid][pMechanicCall] = 0;
	PlayerData[playerid][pEmergency] = 0;
	PlayerData[playerid][pIncomingCall] = 0;
	PlayerData[playerid][pCallLine] = INVALID_PLAYER_ID;
	PlayerData[playerid][pNumberPhoneCall] = 0;

	for (new i = 0; i != MAX_PLAYER_TICKETS; i ++) if(TicketData[playerid][i][ticketExists]){
	    TicketData[playerid][i][ticketID] = 0;
		TicketData[playerid][i][ticketExists] = false;
		TicketData[playerid][i][ticketFee] = 0;
	}

	for (new i = 0; i != MAX_CONTACTS; i ++) if(ContactData[playerid][i][contactExists]){
	    ContactData[playerid][i][contactExists] = false;
	    ContactData[playerid][i][contactID] = 0;
	    ContactData[playerid][i][contactNumber] = 0;
	    ListedContacts[playerid][i] = -1;
	}


	PlayerGetNumberSMS[playerid] = 0;

	ResetShowCard(playerid);

	ResetWeaponDealerJob(playerid);

	ResetGarbageJob(playerid);

	if(PlayerUsing_HomeInv[playerid]){
		if(GetHomeOwnerIndex[playerid] != -1){
			if(HomeData[GetHomeOwnerIndex[playerid]][homeStorageUsing]){
				HomeData[GetHomeOwnerIndex[playerid]][homeStorageUsing] = false;
			}
		}
	}

	GetHomeOwnerIndex[playerid] = -1;
	BarHpToggle[playerid] = 0;
	EditATM[playerid] = -1;

	ResetGaCha(playerid);

	ResetRubberJob(playerid);
	
	ResetClothJob(playerid);

	ResetDrugPlayer(playerid);

	ResetSeekerJob(playerid);

	ResetEngjob(playerid);

	if(OilGetID[playerid] != -1){
		OilData[OilGetID[playerid]][oilUse] = 0;
	}

	ResetOilJob(playerid);

	pricevehdestroy[playerid] = 0;
	PlayerEnterCamera[playerid] = 0;
	PlayerCameraType[playerid] = 0;

	DelayNewbie[playerid] = 0;
	TimeMute[playerid] = 0;
	
	CarIDInstallTracker[playerid] = -1;

	ResetInstallTrack(playerid);

	CountGetVehicle[playerid] = 0;
	GetPlayerShareLocation[playerid] = -1;
	PlayerData[playerid][pTransfer] = -1;
	PlayerData[playerid][pTemporaryKey] = -1;

	ResetPlayer(playerid);

	if (BoomboxData[playerid][boomboxPlaced])
		Boombox_Destroy(playerid);

	PlayerData[playerid][pBoombox] = INVALID_PLAYER_ID;
	CheckBoombox[playerid] = 0;
	ResetDamages(playerid);
	GetBodyID[playerid] = -1;
	StartingTakeBody[playerid] = 0;
	TakeBodyPoint[playerid] = 0;

	if (PlayerData[playerid][pLogCheckTime])
		KillTimer(PlayerData[playerid][pLogCheckTime]);

	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	ClearAnimations(playerid);

	ResetPlayerVoice(playerid);

	TestingRules[playerid] = 0;
	TestingScore[playerid] = 0;
	TestingScoreTwo[playerid] = 0;

	PlayerGetJobGPSID[playerid] = -1;

	CountCheckCarJack[playerid] = 0;
	
	if(MedicToMe[playerid] != -1){
		DisablePlayerCheckpoint(MedicToMe[playerid]);
		DisablePlayerCheckpoint(playerid);
		PlayerEnterCheckPointMedic[MedicToMe[playerid]] = 0;
		PlayerEnterCheckPointMedic[playerid] = 0;
		MedicToMe[MedicToMe[playerid]] = -1;
		MedicToMe[playerid] = -1;
	}

	TimeSleepPoint[playerid] = 0;
	StartSleep[playerid] = 0;
	MicEventOn[playerid] = 0;

	MarryID[playerid] = -1;
	OnPlayerShowMarryCard[playerid] = 0;
	RingShow[playerid] = 0;
	PlayerData[playerid][pRentHome] = 0;
	CheckHoldFlower[playerid] = 0;

	GetHomeIDTemp[playerid] = -1;
	GetPlayerRentHome[playerid] = -1;

	StartDeliverBox[playerid] = 0;
	GotoSendBox[playerid] = 0;
	TimeCountLogout[playerid] = 0;
	CheckingLogout[playerid] = 0;

	format(PlayerData[playerid][pAdminName], 64, "NULL");

	format(PlayerData[playerid][pAccessoryNameHat], 32, "NULL");
	format(PlayerData[playerid][pAccessoryNameGlasses], 32, "NULL");
	format(PlayerData[playerid][pAccessoryNameBody], 32, "NULL");
	format(PlayerData[playerid][pAccessoryNameArms], 32, "NULL");

	for(new i=0; i<10; i++){
		RemoveAttachedObject(playerid, i);
	}

	PlayerEditingObject[playerid] = 0;
	PlayerEditObjectSlot[playerid] = -1;
	PlayerEditObjectType[playerid] = 0;
	KillTimer(RefuelTime[playerid]);
	RefuelTime[playerid] = 0;

	PlayerCarGetID[playerid] = -1;
	CheckPlayerStunFromDamage[playerid] = 0;

	ResetShellJob(playerid);
	CheckSpawnDontPressH[playerid] = 0;
	TimeEnterInterior[playerid] = 0;
	GetIndexItemWeapon[playerid] = -1;
	GetUserIDItemWeapon[playerid] = -1;
	//ResetPartyPlayer(playerid);

	if(Player_GetID_Orange[playerid] != -1){
		OrangeData[Player_GetID_Orange[playerid]][orangePlayerUse] = false;
	}
	
	ResetOrangeJob(playerid);

	DrunkTime[playerid] = 0;

	Reset_PlayerUpgradeWeapon(playerid);
	GetTypeCarsells[playerid] = 0;
	ResetCabaraPlayer(playerid);
	ResetSkateBoard(playerid);
	CheckCampingIsPlayer(playerid);
	ResetDeerPlayer(playerid);
	ResetPlayerCamping(playerid);

	PlayerCheckSleepOnBed[playerid] = false;
	PlayerIsDropMap[playerid] = false;

	PlayerOpenMenuTime[playerid] = 0;
	PlayerTimeOutLogin[playerid] = 0;
	KillTimer(StartPlayerCountTimeLogin[playerid]);

	Reset_SharkJob(playerid);
	Reset_PizzaJob(playerid);

	AdminManagePlayerID[playerid] = INVALID_PLAYER_ID;

	BitFlag_Off(g_PlayerFlags[playerid],PLAYER_PHONE_OFF);

	Reset_PlayerBiz(playerid);
	ResetPlayer_WarFlag(playerid);

	ResetPlayerPlant(playerid);
	PlayerResetBoxing(playerid);

	PlayerCheckDuel_Disconnect(playerid);

	ResetPlayerRacing(playerid); 
	ResetCowPickingup(playerid); 
	ResetPlayerCow(playerid);

	PlayerInvWeightTemp[playerid] = 0.0;

	PlayerUseSkinBaseHalloween[playerid] = false;
	ResetPlayerTradeItem(playerid);

	ResetPlayer_CharacterTD(playerid);
	Reset_HomePlayer(playerid);
	
	//PlayerShowStatusBar[playerid] = false;

	TogHud[playerid] = false;

	ResetPlayerQuest(playerid);
	ResetPlayerDeliverOilJob(playerid);

	PlayerData[playerid][pSelectPlayChar] = -1;
	PlayerClickCharList[playerid] = 0;

//	ResetPlayerLoyKathong(playerid);
//	ResetPlayerRogerPlant(playerid);
	
	PlayerShoutVoice[playerid] = false;
	ResetPlayerShow(playerid);

	PlayerSpeedoShowing[playerid] = false;
	PlayerTextColorGold[playerid] = 0;

	ResetPlayerDrivingTest(playerid);

	PlayerInScreen[playerid] = false;
	PlayerMicEvent[playerid] = false;

	ResetPlayerProgressbarV2(playerid);	
	PlayerPlaySongChristmas[playerid] = false;
	ResetPlayerAirDrop(playerid);

	PlayerOpenAccessoryMenu[playerid] = false;
	PlayerShowSkinShopMenu[playerid] = false;
	PlayerGetAmountBuyDonate[playerid] = 0;

	ResetPlayerJdzHud(playerid);

	ResetPlayerStory(playerid);

	ToolType[playerid] = 0;

	PlayerHaveStoryID[playerid] = -1;

//	ResetBoomboxNewYear(playerid);

	ResetPlayerWarCity(playerid);

	playerLoadInventory[playerid] = false;
	playerClickFetchCharacter[playerid] = false;

	ResetPlayerDrag(playerid);
	return true;
}