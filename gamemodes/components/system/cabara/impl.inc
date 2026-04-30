#if defined _inc_impl
	#undef _inc_impl
#endif

forward Casino_Load();
public Casino_Load(){
    new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_CASINO)
	{
	    CasinoData[i][casinoEx] = true;

	    cache_get_value_name_int(i, "casinoID", CasinoData[i][casinoID]);
	    cache_get_value_name_float(i, "casinoPosX", CasinoData[i][casinoPos][0]);
	    cache_get_value_name_float(i, "casinoPosY", CasinoData[i][casinoPos][1]);
	    cache_get_value_name_float(i, "casinoPosZ", CasinoData[i][casinoPos][2]);
	    cache_get_value_name_int(i, "casinoInt", CasinoData[i][casinoInt]);
	    cache_get_value_name_int(i, "casinoWorld", CasinoData[i][casinoWorld]);

        Count_Casino++;

 	    Casino_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d Casinos Successfully ))", Count_Casino);
    return 1;
}

Casino_Refresh(casinoid)
{
	if (casinoid != -1 && CasinoData[casinoid][casinoEx])
	{
        if (IsValidDynamic3DTextLabel(CasinoData[casinoid][casinoText3D]))
            DestroyDynamic3DTextLabel(CasinoData[casinoid][casinoText3D]);

        if (IsValidDynamicPickup(CasinoData[casinoid][casinoPickup]))
            DestroyDynamicPickup(CasinoData[casinoid][casinoPickup]);

		new
		    string[128];

		format(string, sizeof(string), "[จุดเล่น คาบาร่า]\nกด 'Y' เพื่อเล่น");

		CasinoData[casinoid][casinoText3D] = CreateDynamic3DTextLabel(string, 0xFFFF09DD, CasinoData[casinoid][casinoPos][0], CasinoData[casinoid][casinoPos][1], CasinoData[casinoid][casinoPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, CasinoData[casinoid][casinoWorld], CasinoData[casinoid][casinoInt]);
	    CasinoData[casinoid][casinoPickup] = CreateDynamicPickup(1276, 23, CasinoData[casinoid][casinoPos][0], CasinoData[casinoid][casinoPos][1], CasinoData[casinoid][casinoPos][2], CasinoData[casinoid][casinoWorld], CasinoData[casinoid][casinoInt]);
	}
	return 1;
}

Casino_Delete(casinoid)
{
	if (casinoid != -1 && CasinoData[casinoid][casinoEx])
	{
	    new
	        string[64];

        Count_Casino--;

		format(string, sizeof(string), "DELETE FROM `casinos` WHERE `casinoID` = '%d'", CasinoData[casinoid][casinoID]);
		mysql_tquery(dbCon, string);

        if (IsValidDynamic3DTextLabel(CasinoData[casinoid][casinoText3D]))
            DestroyDynamic3DTextLabel(CasinoData[casinoid][casinoText3D]);

        if (IsValidDynamicPickup(CasinoData[casinoid][casinoPickup]))
            DestroyDynamicPickup(CasinoData[casinoid][casinoPickup]);

		CasinoData[casinoid][casinoEx] = false;
	    CasinoData[casinoid][casinoID] = 0;
	}
	return 1;
}

Casino_Save(casinoid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `casinos` SET `casinoPosX` = '%.4f', `casinoPosY` = '%.4f', `casinoPosZ` = '%.4f', `casinoInt` = '%d', `casinoWorld` = '%d' WHERE `casinoID` = '%d'",
		CasinoData[casinoid][casinoPos][0],
	    CasinoData[casinoid][casinoPos][1],
	    CasinoData[casinoid][casinoPos][2],
	    CasinoData[casinoid][casinoInt],
	    CasinoData[casinoid][casinoWorld],
        CasinoData[casinoid][casinoID]
	);

	return mysql_tquery(dbCon, query);
}

Casino_Create(playerid){
	new
	    Float:x,
	    Float:y,
	    Float:z;

	if (GetPlayerPos(playerid, x, y, z))
	{
		for (new i = 0; i != MAX_CASINO; i ++)
		{
	    	if (!CasinoData[i][casinoEx])
	    	{
	        	CasinoData[i][casinoEx] = true;

				CasinoData[i][casinoPos][0] = x;
	        	CasinoData[i][casinoPos][1] = y;
	        	CasinoData[i][casinoPos][2] = z;

	        	CasinoData[i][casinoInt] = GetPlayerInterior(playerid);
	        	CasinoData[i][casinoWorld] = GetPlayerVirtualWorld(playerid);

	        	Casino_Refresh(i);
	        	mysql_tquery(dbCon, "INSERT INTO `casinos` (`casinoInt`) VALUES(0)", "OnCasinoCreated", "d", i);

	        	return i;
	        }
	    }
	}
	return -1;
}

forward OnCasinoCreated(casinoid);
public OnCasinoCreated(casinoid)
{
	if (casinoid == -1 || !CasinoData[casinoid][casinoEx])
	    return 0;

	CasinoData[casinoid][casinoID] = cache_insert_id();
	Casino_Save(casinoid);

	return 1;
}

Casino_Nearest(playerid)
{
    for (new i = 0; i != MAX_CASINO; i ++) if (CasinoData[i][casinoEx] && IsPlayerInRangeOfPoint(playerid, 5.0, CasinoData[i][casinoPos][0], CasinoData[i][casinoPos][1], CasinoData[i][casinoPos][2]))
	{
		if (GetPlayerInterior(playerid) == CasinoData[i][casinoInt] && GetPlayerVirtualWorld(playerid) == CasinoData[i][casinoWorld])
			return i;
	}
	return -1;
}

CMD:opencabara(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] > 1338){
        if(!CabaraIsOpen){
            CabaraIsOpen = true;
            SendClientMessageToAll(0xFF2309AA, "[CABARA]: {FFFFFF}ขณะนี้ Cabara ได้เปิดทำการแล้ว");
        }
        else{
            CabaraIsOpen = false;
            SendClientMessageToAll(0xFF2309AA, "[CABARA]: {FFFFFF}ขณะนี้ Cabara ได้ปิดทำการแล้ว");
        }
    }
    return 1;
}

CMD:casinocmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1338)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[CASINOCMDS]: /makecasino, /removecasino, /editcasino, /gotocasino, /opencabara");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
    return 1;
}

CMD:gotocasino(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/gotocasino [casino ID]");

	if ((id < 0 || id >= MAX_CASINO) || !CasinoData[id][casinoEx])
		return SendClientMessage(playerid, -1, "คุณระบุ Casino ID ไม่ถูกต้อง");

	SetPlayerPosEx(playerid, CasinoData[id][casinoPos][0], CasinoData[id][casinoPos][1], CasinoData[id][casinoPos][2], CasinoData[id][casinoInt], CasinoData[id][casinoWorld]);
	SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ Casino ID: %d", id);
	return 1;
}

CMD:makecasino(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
    new
		id = -1,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	id = Casino_Create(playerid);

	if (id == -1)
		return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้าง Casino เกินขีดจำกัดแล้ว");

	format(string, sizeof(string), "คุณประสบความสำเร็จสร้าง Casino ไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:removecasino(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id = 0,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/removecasino [casino id]");

	if ((id < 0 || id >= MAX_CASINO) || !CasinoData[id][casinoEx])
		return SendClientMessage(playerid, -1, "คุณระบุไอดี Casino ผิดพลาด");

	Casino_Delete(id);
	format(string, sizeof(string), "คุณประสบความสำเร็จในการทำลาย Casino ไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:editcasino(playerid, params[])
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
		SystemMsg(playerid, "/editcasino [id] [name]");
		SystemMsg(playerid, "[ตัวเลือก]:{FFFFFF} location");
		return 1;
	}

	if ((id < 0 || id >= MAX_CASINO) || !CasinoData[id][casinoEx])
		return SendClientMessage(playerid, -1, "คุณระบุไอดี Casino ผิดพลาด");

	if (!strcmp(type, "location", true))
	{
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);

		CasinoData[id][casinoPos][0] = x;
		CasinoData[id][casinoPos][1] = y;
		CasinoData[id][casinoPos][2] = z;

		CasinoData[id][casinoInt] = GetPlayerInterior(playerid);
		CasinoData[id][casinoWorld] = GetPlayerVirtualWorld(playerid);

		Casino_Refresh(id);
		Casino_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่งของ Casino ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	return 1;
}

ResetCabaraPlayer(playerid){
    PlayerMoneyDown[playerid] = 0;
    PlayerSelectTeam[playerid] = 0;
    PlayerOpeningMenuCabara[playerid] = false;
    return 1;
}

UpdateMoneyCabara(){
    new string[128];
    format(string, sizeof(string), "%s", FormatNumber(TotalMoneyPlayer));
    TextDrawSetString(TextDrawCabara[11], string);

    format(string, sizeof(string), "%s", FormatNumber(TotalMoneyBanker));
    TextDrawSetString(TextDrawCabara[12], string);

    format(string, sizeof(string), "%s", FormatNumber(TotalMoneyTie));
    TextDrawSetString(TextDrawCabara[13], string);
    return 1;
}

task UpdateCabara[1000](){ 
    if(!CabaraStart && TimingCountCabara > 0){
        new string[64];
        TimingCountCabara--;    
        format(string, sizeof(string), "Wait %d sec", TimingCountCabara);
        TextDrawSetString(TextDrawCabara[14], string);
        if(TimingCountCabara == 0){
            CabaraStart = true;
            TextDrawSetString(TextDrawCabara[14], "START");
        }
    }

    if(CabaraStart && !CabaraStarting){
        CabaraStarting = true;
        StartRandomCabara();
    }
}

/*CMD:showcabara(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    for(new i=0; i<15; i++){
        TextDrawShowForPlayer(playerid, TextDrawCabara[i]);
    }
    SelectTextDraw(playerid, 0x00E50AAA);
    TogglePlayerControllable(playerid, 0);
    PlayerOpeningMenuCabara[playerid] = true;
    UpdateMoneyCabara();
    return 1;
}*/

Dialog:Input_MoneyPlayer(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new money = strval(inputtext);
        new string[128];

        if(CabaraStart) return ErrorMsg(playerid, "กรุณารอลงรอบต่อไป...");

        if(money < 1 || money > 10000){
            format(string, sizeof(string), "* คุณไม่สามารถลงเงินได้ ต่ำกว่า 1 และมากกว่า 10k ได้ *\nคุณมีเงินอยู่: %s\nกรอกจำนวนด้านล่างเพื่อลงเงินของคุณ: ", FormatNumber(GetMoney(playerid)));
            Dialog_ShowEasy(playerid, Input_MoneyPlayer, DIALOG_STYLE_INPUT, "ลงเงินของคุณ - Player", string, "ลงเงิน", "ยกเลิก");
            return 1;
        }

        if(GetMoney(playerid) < money){
            format(string, sizeof(string), "* คุณมีเงินไม่พอกับจำนวนที่คุณกรอก *\nคุณมีเงินอยู่: %s\nกรอกจำนวนด้านล่างเพื่อลงเงินของคุณ: ", FormatNumber(GetMoney(playerid)));
            Dialog_ShowEasy(playerid, Input_MoneyPlayer, DIALOG_STYLE_INPUT, "ลงเงินของคุณ - Player", string, "ลงเงิน", "ยกเลิก");
            return 1;
        }

        PlayerMoneyDown[playerid] = money;
        PlayerSelectTeam[playerid] = 1;
        format(string, sizeof(string), "คุณได้ลงเงินไปยัง Player จำนวน %s เรียบร้อยแล้ว", FormatNumber(PlayerMoneyDown[playerid]));
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ลงเงินของคุณ - Player", string, "ตกลง", "");

        GiveMoney(playerid, -PlayerMoneyDown[playerid], "player down");
        TotalMoneyPlayer += PlayerMoneyDown[playerid];
        format(string, sizeof(string), "%s", FormatNumber(TotalMoneyPlayer));
        TextDrawSetString(TextDrawCabara[11], string);
    }
    return 1;
}

Dialog:Input_MoneyBanker(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new money = strval(inputtext);
        new string[128];

        if(CabaraStart) return ErrorMsg(playerid, "กรุณารอลงรอบต่อไป...");

        if(money < 1 || money > 10000){
            format(string, sizeof(string), "* คุณไม่สามารถลงเงินได้ ต่ำกว่า 1 และมากกว่า 10k ได้ *\nคุณมีเงินอยู่: %s\nกรอกจำนวนด้านล่างเพื่อลงเงินของคุณ: ", FormatNumber(GetMoney(playerid)));
            Dialog_ShowEasy(playerid, Input_MoneyBanker, DIALOG_STYLE_INPUT, "ลงเงินของคุณ - Banker", string, "ลงเงิน", "ยกเลิก");
            return 1;
        }

        if(GetMoney(playerid) < money){
            format(string, sizeof(string), "* คุณมีเงินไม่พอกับจำนวนที่คุณกรอก *\nคุณมีเงินอยู่: %s\nกรอกจำนวนด้านล่างเพื่อลงเงินของคุณ: ", FormatNumber(GetMoney(playerid)));
            Dialog_ShowEasy(playerid, Input_MoneyBanker, DIALOG_STYLE_INPUT, "ลงเงินของคุณ - Banker", string, "ลงเงิน", "ยกเลิก");
            return 1;
        }

        PlayerMoneyDown[playerid] = money;
        PlayerSelectTeam[playerid] = 2;
        format(string, sizeof(string), "คุณได้ลงเงินไปยัง Banker จำนวน %s เรียบร้อยแล้ว", FormatNumber(PlayerMoneyDown[playerid]));
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ลงเงินของคุณ - Banker", string, "ตกลง", "");

        GiveMoney(playerid, -PlayerMoneyDown[playerid], "banker down");
        TotalMoneyBanker += PlayerMoneyDown[playerid];
        format(string, sizeof(string), "%s", FormatNumber(TotalMoneyBanker));
        TextDrawSetString(TextDrawCabara[12], string);
    }
    return 1;
}

Dialog:Input_MoneyTie(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new money = strval(inputtext);
        new string[128];

        if(CabaraStart) return ErrorMsg(playerid, "กรุณารอลงรอบต่อไป...");

        if(money < 1 || money > 10000){
            format(string, sizeof(string), "* คุณไม่สามารถลงเงินได้ ต่ำกว่า 1 และมากกว่า 10k ได้ *\nคุณมีเงินอยู่: %s\nกรอกจำนวนด้านล่างเพื่อลงเงินของคุณ: ", FormatNumber(GetMoney(playerid)));
            Dialog_ShowEasy(playerid, Input_MoneyTie, DIALOG_STYLE_INPUT, "ลงเงินของคุณ - Tie", string, "ลงเงิน", "ยกเลิก");
            return 1;
        }

        if(GetMoney(playerid) < money){
            format(string, sizeof(string), "* คุณมีเงินไม่พอกับจำนวนที่คุณกรอก *\nคุณมีเงินอยู่: %s\nกรอกจำนวนด้านล่างเพื่อลงเงินของคุณ: ", FormatNumber(GetMoney(playerid)));
            Dialog_ShowEasy(playerid, Input_MoneyTie, DIALOG_STYLE_INPUT, "ลงเงินของคุณ - Tie", string, "ลงเงิน", "ยกเลิก");
            return 1;
        }

        PlayerMoneyDown[playerid] = money;
        PlayerSelectTeam[playerid] = 3;
        format(string, sizeof(string), "คุณได้ลงเงินไปยัง Tie จำนวน %s เรียบร้อยแล้ว", FormatNumber(PlayerMoneyDown[playerid]));
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ลงเงินของคุณ - Tie", string, "ตกลง", "");

        GiveMoney(playerid, -PlayerMoneyDown[playerid], "tie down");
        TotalMoneyTie += PlayerMoneyDown[playerid];
        format(string, sizeof(string), "%s", FormatNumber(TotalMoneyTie));
        TextDrawSetString(TextDrawCabara[13], string);
    }
    return 1;
}

forward CheckPlayerIsCorrectCard();
public CheckPlayerIsCorrectCard(){
    foreach(new i : Player){
        if(!LoggedIn[i]) continue;
        if(PlayerOpeningMenuCabara[i]){
            new string[128];
            if(PlayerSelectTeam[i] != 0){
                if(PlayerSelectTeam[i] == CheckWhoWin){
                    GiveMoney(i, PlayerMoneyDown[i]*2, "Win Bacara");
                    Log_Write("logs/cabaraaddmoney.txt", "[%s] %s GetMoney %s", ReturnDate(), ReturnRoleplayName(i), FormatNumber(PlayerMoneyDown[i]*2));
                    format(string, sizeof(string), "{00FE0B}คุณได้รับชัยชนะ และ ได้รับเงิน %s", FormatNumber(PlayerMoneyDown[i]*2));
                    Dialog_ShowEasy(i, ShowOnly, DIALOG_STYLE_MSGBOX, "{00FE0B}ได้รับชัยชนะ", string, "ตกลง", "");
                }
                else{
                    //GiveMoney(i, -PlayerMoneyDown[i], "แพ้คาบาร่า");
                    Log_Write("logs/cabararemovemoney.txt", "[%s] %s RemoveMoney %s", ReturnDate(), ReturnRoleplayName(i), FormatNumber(PlayerMoneyDown[i]));
                    format(string, sizeof(string), "{FE0000}คุณพ่ายแพ้ และ ได้เสียเงิน %s", FormatNumber(PlayerMoneyDown[i]));
                    Dialog_ShowEasy(i, ShowOnly, DIALOG_STYLE_MSGBOX, "{FE0000}พ่ายแพ้", string, "ตกลง", "");
                }
            }   
            PlayerSelectTeam[i] = 0;
            PlayerMoneyDown[i] = 0;
        }
    }
}

forward SetNextRoundsCabara();
public SetNextRoundsCabara(){
    TextDrawSetString(TextDrawCabara[2], "ld_card:cdback"); 
    TextDrawSetString(TextDrawCabara[4], "ld_card:cdback"); 
    TextDrawSetString(TextDrawCabara[3], "ld_card:cdback");  
    TextDrawSetString(TextDrawCabara[5], "ld_card:cdback");

    ScorePlayer = 0; ScoreBanker = 0;
    TotalMoneyPlayer = 0; TotalMoneyBanker = 0; TotalMoneyTie = 0;

    new string[64];
    format(string, sizeof(string), "%s", FormatNumber(TotalMoneyPlayer));
    TextDrawSetString(TextDrawCabara[11], string);

    format(string, sizeof(string), "%s", FormatNumber(TotalMoneyBanker));
    TextDrawSetString(TextDrawCabara[12], string);

    format(string, sizeof(string), "%s", FormatNumber(TotalMoneyTie));
    TextDrawSetString(TextDrawCabara[13], string);

    TimingCountCabara = 30; CabaraStart = false; CabaraStarting = false;
}

forward OpenCardTwo();
public OpenCardTwo(){
    new playercardtwo = random(12);
    if(playercardtwo == 0) {
        ScorePlayer += 1;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd1h");  
    }
    if(playercardtwo == 1) {
        ScorePlayer += 2;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd2h");  
    }
    if(playercardtwo == 2) {
        ScorePlayer += 3;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd3h");  
    }
    if(playercardtwo == 3) {
        ScorePlayer += 4;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd4h");  
    }
    if(playercardtwo == 4) {
        ScorePlayer += 5;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd5h");  
    }
    if(playercardtwo == 5) {
        ScorePlayer += 6;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd6h"); 
    }
    if(playercardtwo == 6) {
        ScorePlayer += 7;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd7h");
    }   
    if(playercardtwo == 7) {
        ScorePlayer += 8;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd8h"); 
    } 
    if(playercardtwo == 8) {
        ScorePlayer += 9;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd9h");  
    }
    if(playercardtwo == 9) {
        ScorePlayer += 0;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd10h");  
    }
    if(playercardtwo == 10) {
        ScorePlayer += 0;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd11h");
    }
    if(playercardtwo == 11) {
        ScorePlayer += 0;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd12h");
    }
    if(playercardtwo == 12) {
        ScorePlayer += 0;
        TextDrawSetString(TextDrawCabara[3], "ld_card:cd13h");
    }

    new bankercardtwo = random(12);
    if(bankercardtwo == 0) {
        ScoreBanker += 1;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd1d"); 
    } 
    if(bankercardtwo == 1) {
        ScoreBanker += 2;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd2d"); 
    } 
    if(bankercardtwo == 2) {
        ScoreBanker += 3;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd3d");
    }  
    if(bankercardtwo == 3) {
        ScoreBanker += 4;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd4d");  
    }
    if(bankercardtwo == 4) {
        ScoreBanker += 5;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd5d");
    }  
    if(bankercardtwo == 5) {
        ScoreBanker += 6;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd6d"); 
    }
    if(bankercardtwo == 6) {
        ScoreBanker += 7;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd7d");  
    } 
    if(bankercardtwo == 7) {
        ScoreBanker += 8;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd8d");  
    }
    if(bankercardtwo == 8) {
        ScoreBanker += 9;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd9d");  
    }
    if(bankercardtwo == 9) {
        ScoreBanker += 0;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd10d");  
    }
    if(bankercardtwo == 10) {
        ScoreBanker += 0;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd11d");
    }
    if(bankercardtwo == 11) {
        ScoreBanker += 0;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd12d");
    }
    if(bankercardtwo == 12) {
        ScoreBanker += 0;
        TextDrawSetString(TextDrawCabara[5], "ld_card:cd13d");
    }

    if(ScorePlayer == 10) ScorePlayer = 0;
    else if(ScorePlayer > 10) {
        ScorePlayer -= 10;
        if(ScorePlayer == 10) ScorePlayer = 0;
    }

    if(ScoreBanker == 10) ScoreBanker = 0;
    else if(ScoreBanker > 10) {
        ScoreBanker -= 10;
        if(ScoreBanker == 10) ScoreBanker = 0;
    }

    new string[64];
    format(string, sizeof(string), "%d : %d", ScorePlayer, ScoreBanker);
    TextDrawSetString(TextDrawCabara[14], string);

    if(ScorePlayer > ScoreBanker) CheckWhoWin = 1;
    else if(ScoreBanker > ScorePlayer) CheckWhoWin = 2;
    else if(ScorePlayer == ScoreBanker) CheckWhoWin = 3;

    SetTimer("CheckPlayerIsCorrectCard", 2000, false);
    //defer CheckPlayerIsCorrectCard();
    SetTimer("SetNextRoundsCabara", 4000, false);
    //defer SetNextRoundsCabara();
}

StartRandomCabara(){
    new playercardone = random(12);
    if(playercardone == 0) {
        ScorePlayer += 1;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd1s");  
    }
    if(playercardone == 1) {
        ScorePlayer += 2;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd2s");  
    }
    if(playercardone == 2) {
        ScorePlayer += 3;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd3s");  
    }
    if(playercardone == 3) {
        ScorePlayer += 4;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd4s");  
    }
    if(playercardone == 4) {
        ScorePlayer += 5;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd5s");  
    }
    if(playercardone == 5) {
        ScorePlayer += 6;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd6s"); 
    }
    if(playercardone == 6) {
        ScorePlayer += 7;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd7s");
    }   
    if(playercardone == 7) {
        ScorePlayer += 8;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd8s"); 
    } 
    if(playercardone == 8) {
        ScorePlayer += 9;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd9s");  
    }
    if(playercardone == 9) {
        ScorePlayer += 0;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd10s");  
    }
    if(playercardone == 10) {
        ScorePlayer += 0;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd11s");
    }
    if(playercardone == 11) {
        ScorePlayer += 0;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd12s");
    }
    if(playercardone == 12) {
        ScorePlayer += 0;
        TextDrawSetString(TextDrawCabara[2], "ld_card:cd13s");
    }

    new bankercardone = random(12);
    if(bankercardone == 0) {
        ScoreBanker += 1;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd1c"); 
    } 
    if(bankercardone == 1) {
        ScoreBanker += 2;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd2c"); 
    } 
    if(bankercardone == 2) {
        ScoreBanker += 3;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd3c");
    }  
    if(bankercardone == 3) {
        ScoreBanker += 4;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd4c");  
    }
    if(bankercardone == 4) {
        ScoreBanker += 5;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd5c");
    }  
    if(bankercardone == 5) {
        ScoreBanker += 6;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd6c"); 
    }
    if(bankercardone == 6) {
        ScoreBanker += 7;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd7c");  
    } 
    if(bankercardone == 7) {
        ScoreBanker += 8;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd8c");  
    }
    if(bankercardone == 8) {
        ScoreBanker += 9;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd9c");  
    }
    if(bankercardone == 9) {
        ScoreBanker += 0;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd10c");  
    }
    if(bankercardone == 10) {
        ScoreBanker += 0;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd11c");
    }
    if(bankercardone == 11) {
        ScoreBanker += 0;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd12c");
    }
    if(bankercardone == 12) {
        ScoreBanker += 0;
        TextDrawSetString(TextDrawCabara[4], "ld_card:cd13c");
    }

    SetTimer("OpenCardTwo", 2000, false);
    //defer OpenCardTwo();
    return 1;
}

LoadTextDrawCabara(){
    TextDrawCabara[0] = TextDrawCreate(322.000000, 125.000000, "_");
    TextDrawFont(TextDrawCabara[0], 1);
    TextDrawLetterSize(TextDrawCabara[0], 0.683333, 27.800003);
    TextDrawTextSize(TextDrawCabara[0], 298.500000, 390.000000);
    TextDrawSetOutline(TextDrawCabara[0], 1);
    TextDrawSetShadow(TextDrawCabara[0], 0);
    TextDrawAlignment(TextDrawCabara[0], 2);
    TextDrawColor(TextDrawCabara[0], -1);
    TextDrawBackgroundColor(TextDrawCabara[0], 255);
    TextDrawBoxColor(TextDrawCabara[0], 200);
    TextDrawUseBox(TextDrawCabara[0], 1);
    TextDrawSetProportional(TextDrawCabara[0], 1);
    TextDrawSetSelectable(TextDrawCabara[0], 0);

    TextDrawCabara[1] = TextDrawCreate(509.000000, 119.000000, "ld_chat:thumbdn");
    TextDrawFont(TextDrawCabara[1], 4);
    TextDrawLetterSize(TextDrawCabara[1], 0.600000, 2.000000);
    TextDrawTextSize(TextDrawCabara[1], 12.500000, 13.500000);
    TextDrawSetOutline(TextDrawCabara[1], 1);
    TextDrawSetShadow(TextDrawCabara[1], 0);
    TextDrawAlignment(TextDrawCabara[1], 1);
    TextDrawColor(TextDrawCabara[1], -1);
    TextDrawBackgroundColor(TextDrawCabara[1], 255);
    TextDrawBoxColor(TextDrawCabara[1], 50);
    TextDrawUseBox(TextDrawCabara[1], 1);
    TextDrawSetProportional(TextDrawCabara[1], 1);
    TextDrawSetSelectable(TextDrawCabara[1], 1);

    TextDrawCabara[2] = TextDrawCreate(153.000000, 162.000000, "ld_card:cdback");
    TextDrawFont(TextDrawCabara[2], 4);
    TextDrawLetterSize(TextDrawCabara[2], 0.600000, 2.000000);
    TextDrawTextSize(TextDrawCabara[2], 51.500000, 83.500000);
    TextDrawSetOutline(TextDrawCabara[2], 1);
    TextDrawSetShadow(TextDrawCabara[2], 0);
    TextDrawAlignment(TextDrawCabara[2], 1);
    TextDrawColor(TextDrawCabara[2], -1);
    TextDrawBackgroundColor(TextDrawCabara[2], 255);
    TextDrawBoxColor(TextDrawCabara[2], 50);
    TextDrawUseBox(TextDrawCabara[2], 1);
    TextDrawSetProportional(TextDrawCabara[2], 1);
    TextDrawSetSelectable(TextDrawCabara[2], 0);

    TextDrawCabara[3] = TextDrawCreate(210.000000, 162.000000, "ld_card:cdback");
    TextDrawFont(TextDrawCabara[3], 4);
    TextDrawLetterSize(TextDrawCabara[3], 0.600000, 2.000000);
    TextDrawTextSize(TextDrawCabara[3], 51.500000, 83.500000);
    TextDrawSetOutline(TextDrawCabara[3], 1);
    TextDrawSetShadow(TextDrawCabara[3], 0);
    TextDrawAlignment(TextDrawCabara[3], 1);
    TextDrawColor(TextDrawCabara[3], -1);
    TextDrawBackgroundColor(TextDrawCabara[3], 255);
    TextDrawBoxColor(TextDrawCabara[3], 50);
    TextDrawUseBox(TextDrawCabara[3], 1);
    TextDrawSetProportional(TextDrawCabara[3], 1);
    TextDrawSetSelectable(TextDrawCabara[3], 0);

    TextDrawCabara[4] = TextDrawCreate(382.000000, 162.000000, "ld_card:cdback");
    TextDrawFont(TextDrawCabara[4], 4);
    TextDrawLetterSize(TextDrawCabara[4], 0.600000, 2.000000);
    TextDrawTextSize(TextDrawCabara[4], 51.500000, 83.500000);
    TextDrawSetOutline(TextDrawCabara[4], 1);
    TextDrawSetShadow(TextDrawCabara[4], 0);
    TextDrawAlignment(TextDrawCabara[4], 1);
    TextDrawColor(TextDrawCabara[4], -1);
    TextDrawBackgroundColor(TextDrawCabara[4], 255);
    TextDrawBoxColor(TextDrawCabara[4], 50);
    TextDrawUseBox(TextDrawCabara[4], 1);
    TextDrawSetProportional(TextDrawCabara[4], 1);
    TextDrawSetSelectable(TextDrawCabara[4], 0);

    TextDrawCabara[5] = TextDrawCreate(439.000000, 162.000000, "ld_card:cdback");
    TextDrawFont(TextDrawCabara[5], 4);
    TextDrawLetterSize(TextDrawCabara[5], 0.600000, 2.000000);
    TextDrawTextSize(TextDrawCabara[5], 51.500000, 83.500000);
    TextDrawSetOutline(TextDrawCabara[5], 1);
    TextDrawSetShadow(TextDrawCabara[5], 0);
    TextDrawAlignment(TextDrawCabara[5], 1);
    TextDrawColor(TextDrawCabara[5], -1);
    TextDrawBackgroundColor(TextDrawCabara[5], 255);
    TextDrawBoxColor(TextDrawCabara[5], 50);
    TextDrawUseBox(TextDrawCabara[5], 1);
    TextDrawSetProportional(TextDrawCabara[5], 1);
    TextDrawSetSelectable(TextDrawCabara[5], 0);

    TextDrawCabara[6] = TextDrawCreate(207.000000, 132.000000, "PLAYER");
    TextDrawFont(TextDrawCabara[6], 2);
    TextDrawLetterSize(TextDrawCabara[6], 0.387500, 2.599999);
    TextDrawTextSize(TextDrawCabara[6], 400.000000, -98.000000);
    TextDrawSetOutline(TextDrawCabara[6], 0);
    TextDrawSetShadow(TextDrawCabara[6], 0);
    TextDrawAlignment(TextDrawCabara[6], 2);
    TextDrawColor(TextDrawCabara[6], -2686721);
    TextDrawBackgroundColor(TextDrawCabara[6], 255);
    TextDrawBoxColor(TextDrawCabara[6], 50);
    TextDrawUseBox(TextDrawCabara[6], 0);
    TextDrawSetProportional(TextDrawCabara[6], 1);
    TextDrawSetSelectable(TextDrawCabara[6], 0);

    TextDrawCabara[7] = TextDrawCreate(434.000000, 132.000000, "BANKER");
    TextDrawFont(TextDrawCabara[7], 2);
    TextDrawLetterSize(TextDrawCabara[7], 0.387500, 2.599999);
    TextDrawTextSize(TextDrawCabara[7], 400.000000, -118.000000);
    TextDrawSetOutline(TextDrawCabara[7], 0);
    TextDrawSetShadow(TextDrawCabara[7], 0);
    TextDrawAlignment(TextDrawCabara[7], 2);
    TextDrawColor(TextDrawCabara[7], -1);
    TextDrawBackgroundColor(TextDrawCabara[7], 255);
    TextDrawBoxColor(TextDrawCabara[7], 50);
    TextDrawUseBox(TextDrawCabara[7], 0);
    TextDrawSetProportional(TextDrawCabara[7], 1);
    TextDrawSetSelectable(TextDrawCabara[7], 0);

    TextDrawCabara[8] = TextDrawCreate(207.000000, 315.000000, "PLAYER");
    TextDrawFont(TextDrawCabara[8], 2);
    TextDrawLetterSize(TextDrawCabara[8], 0.258332, 1.750000);
    TextDrawTextSize(TextDrawCabara[8], 16.500000, 90.500000);
    TextDrawSetOutline(TextDrawCabara[8], 1);
    TextDrawSetShadow(TextDrawCabara[8], 0);
    TextDrawAlignment(TextDrawCabara[8], 2);
    TextDrawColor(TextDrawCabara[8], -1);
    TextDrawBackgroundColor(TextDrawCabara[8], 255);
    TextDrawBoxColor(TextDrawCabara[8], -65336);
    TextDrawUseBox(TextDrawCabara[8], 1);
    TextDrawSetProportional(TextDrawCabara[8], 1);
    TextDrawSetSelectable(TextDrawCabara[8], 1);

    TextDrawCabara[9] = TextDrawCreate(436.000000, 315.000000, "BANKER");
    TextDrawFont(TextDrawCabara[9], 2);
    TextDrawLetterSize(TextDrawCabara[9], 0.258332, 1.750000);
    TextDrawTextSize(TextDrawCabara[9], 16.500000, 90.500000);
    TextDrawSetOutline(TextDrawCabara[9], 1);
    TextDrawSetShadow(TextDrawCabara[9], 0);
    TextDrawAlignment(TextDrawCabara[9], 2);
    TextDrawColor(TextDrawCabara[9], -1);
    TextDrawBackgroundColor(TextDrawCabara[9], 255);
    TextDrawBoxColor(TextDrawCabara[9], -56);
    TextDrawUseBox(TextDrawCabara[9], 1);
    TextDrawSetProportional(TextDrawCabara[9], 1);
    TextDrawSetSelectable(TextDrawCabara[9], 1);

    TextDrawCabara[10] = TextDrawCreate(322.000000, 315.000000, "TIE");
    TextDrawFont(TextDrawCabara[10], 2);
    TextDrawLetterSize(TextDrawCabara[10], 0.258332, 1.750000);
    TextDrawTextSize(TextDrawCabara[10], 16.500000, 90.500000);
    TextDrawSetOutline(TextDrawCabara[10], 1);
    TextDrawSetShadow(TextDrawCabara[10], 0);
    TextDrawAlignment(TextDrawCabara[10], 2);
    TextDrawColor(TextDrawCabara[10], -1);
    TextDrawBackgroundColor(TextDrawCabara[10], 255);
    TextDrawBoxColor(TextDrawCabara[10], 9109704);
    TextDrawUseBox(TextDrawCabara[10], 1);
    TextDrawSetProportional(TextDrawCabara[10], 1);
    TextDrawSetSelectable(TextDrawCabara[10], 1);

    TextDrawCabara[11] = TextDrawCreate(207.000000, 275.000000, "$10,000,000");
    TextDrawFont(TextDrawCabara[11], 2);
    TextDrawLetterSize(TextDrawCabara[11], 0.245833, 1.600000);
    TextDrawTextSize(TextDrawCabara[11], 400.000000, -98.000000);
    TextDrawSetOutline(TextDrawCabara[11], 0);
    TextDrawSetShadow(TextDrawCabara[11], 0);
    TextDrawAlignment(TextDrawCabara[11], 2);
    TextDrawColor(TextDrawCabara[11], -2686721);
    TextDrawBackgroundColor(TextDrawCabara[11], 255);
    TextDrawBoxColor(TextDrawCabara[11], 50);
    TextDrawUseBox(TextDrawCabara[11], 0);
    TextDrawSetProportional(TextDrawCabara[11], 1);
    TextDrawSetSelectable(TextDrawCabara[11], 0);

    TextDrawCabara[12] = TextDrawCreate(437.000000, 275.000000, "$10,000,000");
    TextDrawFont(TextDrawCabara[12], 2);
    TextDrawLetterSize(TextDrawCabara[12], 0.245833, 1.600000);
    TextDrawTextSize(TextDrawCabara[12], 400.000000, -98.000000);
    TextDrawSetOutline(TextDrawCabara[12], 0);
    TextDrawSetShadow(TextDrawCabara[12], 0);
    TextDrawAlignment(TextDrawCabara[12], 2);
    TextDrawColor(TextDrawCabara[12], -1);
    TextDrawBackgroundColor(TextDrawCabara[12], 255);
    TextDrawBoxColor(TextDrawCabara[12], 50);
    TextDrawUseBox(TextDrawCabara[12], 0);
    TextDrawSetProportional(TextDrawCabara[12], 1);
    TextDrawSetSelectable(TextDrawCabara[12], 0);

    TextDrawCabara[13] = TextDrawCreate(324.000000, 275.000000, "$10,000,000");
    TextDrawFont(TextDrawCabara[13], 2);
    TextDrawLetterSize(TextDrawCabara[13], 0.245833, 1.600000);
    TextDrawTextSize(TextDrawCabara[13], 400.000000, -98.000000);
    TextDrawSetOutline(TextDrawCabara[13], 0);
    TextDrawSetShadow(TextDrawCabara[13], 0);
    TextDrawAlignment(TextDrawCabara[13], 2);
    TextDrawColor(TextDrawCabara[13], 9109759);
    TextDrawBackgroundColor(TextDrawCabara[13], 255);
    TextDrawBoxColor(TextDrawCabara[13], 50);
    TextDrawUseBox(TextDrawCabara[13], 0);
    TextDrawSetProportional(TextDrawCabara[13], 1);
    TextDrawSetSelectable(TextDrawCabara[13], 0);

    TextDrawCabara[14] = TextDrawCreate(321.000000, 191.000000, "Player WIN");
    TextDrawFont(TextDrawCabara[14], 2);
    TextDrawLetterSize(TextDrawCabara[14], 0.379166, 2.649999);
    TextDrawTextSize(TextDrawCabara[14], 400.000000, 162.000000);
    TextDrawSetOutline(TextDrawCabara[14], 0);
    TextDrawSetShadow(TextDrawCabara[14], 0);
    TextDrawAlignment(TextDrawCabara[14], 2);
    TextDrawColor(TextDrawCabara[14], -2686721);
    TextDrawBackgroundColor(TextDrawCabara[14], 255);
    TextDrawBoxColor(TextDrawCabara[14], 50);
    TextDrawUseBox(TextDrawCabara[14], 0);
    TextDrawSetProportional(TextDrawCabara[14], 1);
    TextDrawSetSelectable(TextDrawCabara[14], 0);
    return 1;
}