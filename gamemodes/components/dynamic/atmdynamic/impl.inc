#if defined _inc_impl
	#undef _inc_impl
#endif

//atm
stock ATM_Delete(atmid){
	if (atmid != -1 && ATMData[atmid][atmExists]){
	    new string[64];

		format(string, sizeof(string), "DELETE FROM `atm` WHERE `atmID` = '%d' LIMIT 1", ATMData[atmid][atmID]);
		mysql_tquery(dbCon, string);

        if (IsValidDynamicObject(ATMData[atmid][atmObject]) && ATMData[atmid][atmObject] != -1) DestroyDynamicObject(ATMData[atmid][atmObject]);
	    if (IsValidDynamic3DTextLabel(ATMData[atmid][atmText3D])) DestroyDynamic3DTextLabel(ATMData[atmid][atmText3D]);
		ATMData[atmid][atmObject] = -1;

	    ATMData[atmid][atmExists] = false;
	    ATMData[atmid][atmID] = 0;
	}
	return 1;
}

ATM_Nearest(playerid){
    for (new i = 0; i != MAX_ATM_MACHINES; i ++) if (ATMData[i][atmExists] && IsPlayerInRangeOfPoint(playerid, 2.5, ATMData[i][atmPos][0], ATMData[i][atmPos][1], ATMData[i][atmPos][2]))
	{
		if (GetPlayerInterior(playerid) == ATMData[i][atmInterior] && GetPlayerVirtualWorld(playerid) == ATMData[i][atmWorld])
			return i;
	}
	return -1;
}

stock ATM_Create(playerid){
    new
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i < MAX_ATM_MACHINES; i ++) if (!ATMData[i][atmExists])
		{
		    ATMData[i][atmExists] = true;

		    x += 1.0 * floatsin(-angle, degrees);
			y += 1.0 * floatcos(-angle, degrees);

            ATMData[i][atmPos][0] = x;
            ATMData[i][atmPos][1] = y;
            ATMData[i][atmPos][2] = z;
            ATMData[i][atmPos][3] = angle;

            ATMData[i][atmInterior] = GetPlayerInterior(playerid);
            ATMData[i][atmWorld] = GetPlayerVirtualWorld(playerid);

			ATM_Refresh(i);
			mysql_tquery(dbCon, "INSERT INTO `atm` (`atmInterior`) VALUES(0)", "OnATMCreated", "d", i);

			return i;
		}
	}
	return -1;
}

forward OnATMCreated(atmid);
public OnATMCreated(atmid){
    if (atmid == -1 || !ATMData[atmid][atmExists])
		return 0;

	ATMData[atmid][atmID] = cache_insert_id();
 	ATM_Save(atmid);

	return 1;
}

stock ATM_Refresh(atmid){
	if (atmid != -1 && ATMData[atmid][atmExists]){
	    if (IsValidDynamicObject(ATMData[atmid][atmObject]) && ATMData[atmid][atmObject] != -1) DestroyDynamicObject(ATMData[atmid][atmObject]);
	    if (IsValidDynamic3DTextLabel(ATMData[atmid][atmText3D])) DestroyDynamic3DTextLabel(ATMData[atmid][atmText3D]);
		ATMData[atmid][atmObject] = -1;
		new
	        string[64];

		format(string, sizeof(string), "[ATM %d]\n{FFFFFF}กด 'Y' เพื่อใช้งาน", atmid);

		ATMData[atmid][atmObject] = CreateDynamicObject(2942, ATMData[atmid][atmPos][0], ATMData[atmid][atmPos][1], ATMData[atmid][atmPos][2] - 0.4, 0.0, 0.0, ATMData[atmid][atmPos][3], ATMData[atmid][atmWorld], ATMData[atmid][atmInterior]);
        ATMData[atmid][atmText3D] = CreateDynamic3DTextLabel(string, COLOR_YELLOW, ATMData[atmid][atmPos][0], ATMData[atmid][atmPos][1], ATMData[atmid][atmPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, ATMData[atmid][atmWorld], ATMData[atmid][atmInterior]);

		return 1;
	}
	return 0;
}

stock ATM_Save(atmid)
{
	new
	    query[200];

	format(query, sizeof(query), "UPDATE `atm` SET `atmX` = '%.4f', `atmY` = '%.4f', `atmZ` = '%.4f', `atmA` = '%.4f', `atmInterior` = '%d', `atmWorld` = '%d' WHERE `atmID` = '%d'",
	    ATMData[atmid][atmPos][0],
	    ATMData[atmid][atmPos][1],
	    ATMData[atmid][atmPos][2],
	    ATMData[atmid][atmPos][3],
	    ATMData[atmid][atmInterior],
	    ATMData[atmid][atmWorld],
	    ATMData[atmid][atmID]
	);
	return mysql_tquery(dbCon, query);
}

forward ATM_Load();
public ATM_Load()
{
    new
	    rows;

	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if (i < MAX_ATM_MACHINES)
	{
	    ATMData[i][atmExists] = true;
     	cache_get_value_name_int(i, "atmID", ATMData[i][atmID]);
	    cache_get_value_name_float(i, "atmX", ATMData[i][atmPos][0]);
     	cache_get_value_name_float(i, "atmY", ATMData[i][atmPos][1]);
     	cache_get_value_name_float(i, "atmZ", ATMData[i][atmPos][2]);
      	cache_get_value_name_float(i, "atmA", ATMData[i][atmPos][3]);
       	cache_get_value_name_int(i, "atmInterior", ATMData[i][atmInterior]);
 		cache_get_value_name_int(i, "atmWorld", ATMData[i][atmWorld]);

		Total_Atms_Created++;

		ATM_Refresh(i);
	}
	printf("(( [MYSQL]: Load %d Atms Successfully ))", Total_Atms_Created);
	return 1;
}

//ATM
Dialog:Bank(playerid, response, listitem, inputtext[]){
	if (response){
	    switch (listitem)
	    {
	        case 0:
	        {
				Dialog_ShowEasy(playerid, BankAccount, DIALOG_STYLE_LIST, "บัญชีธนาคาร", "ฝากเงิน\nถอนเงิน\nทำการโอน", "เลือก", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:BankAccount(playerid, response, listitem, inputtext[]){

	if (response){
	    switch (listitem)
	    {
			case 0:
	        {
				Dialog_ShowEasy(playerid, Deposit, DIALOG_STYLE_INPUT, "ฝากเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการฝาก:", "ฝากเงิน", "ยกเลิก", FormatNumber(PlayerData[playerid][pBankMoney]));
			}
	        case 1:
	        {
				Dialog_ShowEasy(playerid, Withdraw, DIALOG_STYLE_INPUT, "ถอนเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการถอน:", "ถอนเงิน", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));
			}
			case 2:{
			    Dialog_ShowEasy(playerid, Transfer, DIALOG_STYLE_INPUT, "โอนเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));
			}
	    }
	}
	else
	{
	    Dialog_ShowEasy(playerid, Bank, DIALOG_STYLE_LIST, "บัญชีธนาคาร", "เงินเขียวในธนาคาร: %s", "เลือก", "ยกเลิก", FormatNumber(PlayerData[playerid][pBankMoney]));
	}
	return 1;
}

Dialog:Transfer(playerid, response, listitem, inputtext[])
{
	if(ServerData[ServerCanGiveMoney] == 1) return ErrorMsg(playerid, "ขณะนี้เซิฟเวอร์ได้ปิดการอนุญาตการให้เงินกับผู้เล่นอยู่");

	if (response)
	{
	    new
	        userid;

		if (sscanf(inputtext, "u", userid))
		    return Dialog_ShowEasy(playerid, Transfer, DIALOG_STYLE_INPUT, "โอนเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (userid == INVALID_PLAYER_ID)
		    return Dialog_ShowEasy(playerid, Transfer, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: ผู้เล่นที่ระบุไม่ถูกต้อง\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));

		if(PlayerData[userid][pPlayerhour] < 5)
			return Dialog_ShowEasy(playerid, Transfer, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: ผู้เล่นนั้ยังออนไลน์ครบ 5 ชั่วโมง\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));

		if(PlayerData[playerid][pPlayerhour] < 5)
			return Dialog_ShowEasy(playerid, Transfer, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: คุณต้องออนไลน์อย่างน้อย 5 ชั่วโมง\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (userid == playerid)
		    return Dialog_ShowEasy(playerid, Transfer, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: คุณไม่สามารถโอนเงินให้ตัวเองได้\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));

		PlayerData[playerid][pTransfer] = userid;
		Dialog_ShowEasy(playerid, TransferCash, DIALOG_STYLE_INPUT, "โอนเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการโอนให้กับ %s:", "ทำรายการ", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer]));
	}
    else {	
		Dialog_ShowEasy(playerid, BankAccount, DIALOG_STYLE_LIST, "บัญชีธนาคาร", "ฝากเงิน\nถอนเงิน\nทำการโอน", "เลือก", "กลับ");
	}
	return 1;
}

Dialog:TransferCash(playerid, response, listitem, inputtext[])
{
	new string[128];

	if (response)
	{
		if(PlayerData[playerid][pTransfer] == -1) return ErrorMsg(playerid, "ID ผู้เล่นที่จะโอนผิดพลาด");
		if(!LoggedIn[PlayerData[playerid][pTransfer]]) return ErrorMsg(playerid, "ผู้เล่นนั้นออฟไลน์ไปแล้ว");

	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_ShowEasy(playerid, TransferCash, DIALOG_STYLE_INPUT, "โอนเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการโอนให้กับ %s:", "ทำรายการ", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer]));

		if (amount < 1 || amount > PlayerData[playerid][pBankMoney])
			return Dialog_ShowEasy(playerid, TransferCash, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: มีเงินไม่พอ!\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการโอนให้กับ %s:", "ทำรายการ", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer]));

		if(amount > 1000000) return Dialog_ShowEasy(playerid, TransferCash, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: ไม่สามารถโอนเกิน 1M ได้!\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการโอนให้กับ %s:", "ทำรายการ", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer]));

		format(string, sizeof(string), "%s ได้โอนเงิน %s ให้กับ %s", ReturnName(playerid), FormatNumber(amount), ReturnName(PlayerData[playerid][pTransfer]));
        SendAdminsMessage(1, COLOR_YELLOW, string);

		new query[256];
		mysql_format(dbCon, query, sizeof(query), "INSERT INTO `transfer_logs` (`sendID`, `sendName`, `reciveID`, `reciveName`, `amount`, `date`) VALUES('%d', '%e', '%d', '%e', '%d', '%e')", PlayerData[playerid][pID], ReturnName(playerid),
		PlayerData[PlayerData[playerid][pTransfer]][pID], ReturnName(PlayerData[playerid][pTransfer]), amount*1, ReturnDate());
		mysql_tquery(dbCon, query);
	
		PlayerData[playerid][pBankMoney] -= amount;
		PlayerData[PlayerData[playerid][pTransfer]][pBankMoney] += amount;

	    SendClientMessageEx(playerid, -1, "คุณโอนเงิน %s ให้บัญชีธนาคารของ %s", FormatNumber(amount), ReturnName(PlayerData[playerid][pTransfer]));
	    SendClientMessageEx(PlayerData[playerid][pTransfer], -1, "%s ได้โอนเงิน %s เข้าบัญชีธนาคารของคุณ", ReturnName(playerid), FormatNumber(amount));

		if(TogAlertLog){
			if(amount >= 100000){
				format(string, sizeof(string), "> [%s] [%s] transfermoney to [%s] amount [%s]", ReturnDate(), ReturnRoleplayName(playerid), ReturnRoleplayName(PlayerData[playerid][pTransfer]), FormatNumber(amount));
				DCC_SendChannelMessage(MoneyLogChannel, string);
			}
		}
		Log_Write("logs/transfermoney.txt", "[%s] %s transfermoney to %s [%s]", ReturnDate(), ReturnRoleplayName(playerid), ReturnRoleplayName(PlayerData[playerid][pTransfer]), FormatNumber(amount));

		if(PlayerUsingPhone[playerid] == 0)
        	Dialog_ShowEasy(playerid, BankAccount, DIALOG_STYLE_LIST, "บัญชีธนาคาร", "ฝากเงิน\nถอนเงิน\nทำการโอน", "เลือก", "ยกเลิก");
	}
	else {
		if(PlayerUsingPhone[playerid] == 0)
	    	Dialog_ShowEasy(playerid, BankAccount, DIALOG_STYLE_LIST, "บัญชีธนาคาร", "ฝากเงิน\nถอนเงิน\nทำการโอน", "เลือก", "กลับ");
	}
	return 1;
}

Dialog:TransferMobile(playerid, response, listitem, inputtext[])
{
	if(ServerData[ServerCanGiveMoney] == 1) return ErrorMsg(playerid, "ขณะนี้เซิฟเวอร์ได้ปิดการอนุญาตการให้เงินกับผู้เล่นอยู่");

	if (response)
	{
	    new
	        userid;

		if (sscanf(inputtext, "u", userid))
		    return Dialog_ShowEasy(playerid, TransferMobile, DIALOG_STYLE_INPUT, "โอนเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (userid == INVALID_PLAYER_ID)
		    return Dialog_ShowEasy(playerid, TransferMobile, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: ผู้เล่นที่ระบุไม่ถูกต้อง\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "", FormatNumber(PlayerData[playerid][pBankMoney]));

		if(PlayerData[userid][pPlayerhour] < 5)
			return Dialog_ShowEasy(playerid, TransferMobile, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: ผู้เล่นนั้ยังออนไลน์ครบ 5 ชั่วโมง\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "", FormatNumber(PlayerData[playerid][pBankMoney]));

		if(PlayerData[playerid][pPlayerhour] < 5)
			return Dialog_ShowEasy(playerid, TransferMobile, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: คุณต้องออนไลน์อย่างน้อย 5 ชั่วโมง\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (userid == playerid)
		    return Dialog_ShowEasy(playerid, TransferMobile, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: คุณไม่สามารถโอนเงินให้ตัวเองได้\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนชื่อหรือไอดีผู้เล่นด้านล่าง:", "ทำรายการ", "", FormatNumber(PlayerData[playerid][pBankMoney]));

		PlayerData[playerid][pTransfer] = userid;
		Dialog_ShowEasy(playerid, TransferMobileCash, DIALOG_STYLE_INPUT, "โอนเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการโอนให้กับ %s:", "ทำรายการ", "", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer]));
	}
	return 1;
}

Dialog:TransferMobileCash(playerid, response, listitem, inputtext[])
{
	new string[128];

	if (response)
	{
		if(PlayerData[playerid][pTransfer] == -1) return ErrorMsg(playerid, "ID ผู้เล่นที่จะโอนผิดพลาด");
		if(!LoggedIn[PlayerData[playerid][pTransfer]]) return ErrorMsg(playerid, "ผู้เล่นนั้นออฟไลน์ไปแล้ว");

	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_ShowEasy(playerid, TransferMobileCash, DIALOG_STYLE_INPUT, "โอนเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการโอนให้กับ %s:", "ทำรายการ", "", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer]));

		if (amount < 1 || amount > PlayerData[playerid][pBankMoney])
			return Dialog_ShowEasy(playerid, TransferMobileCash, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: มีเงินไม่พอ!\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการโอนให้กับ %s:", "ทำรายการ", "", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer]));

		if(amount > 1000000) return Dialog_ShowEasy(playerid, TransferMobileCash, DIALOG_STYLE_INPUT, "โอนเงิน", "ข้อผิดพลาด: ไม่สามารถโอนเกิน 1M ได้!\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการโอนให้กับ %s:", "ทำรายการ", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer]));

		format(string, sizeof(string), "%s ได้โอนเงิน %s ให้กับ %s", ReturnName(playerid), FormatNumber(amount), ReturnName(PlayerData[playerid][pTransfer]));
        SendAdminsMessage(1, COLOR_YELLOW, string);
	
		new query[256];
		mysql_format(dbCon, query, sizeof(query), "INSERT INTO `transfer_logs` (`sendID`, `sendName`, `reciveID`, `reciveName`, `amount`, `date`) VALUES('%d', '%e', '%d', '%e', '%d', '%e')", PlayerData[playerid][pID], ReturnName(playerid),
		PlayerData[PlayerData[playerid][pTransfer]][pID], ReturnName(PlayerData[playerid][pTransfer]), amount*1, ReturnDate());
		mysql_tquery(dbCon, query);

		PlayerData[playerid][pBankMoney] -= amount;
		PlayerData[PlayerData[playerid][pTransfer]][pBankMoney] += amount;

	    SendClientMessageEx(playerid, -1, "คุณโอนเงิน %s ให้บัญชีธนาคารของ %s", FormatNumber(amount), ReturnName(PlayerData[playerid][pTransfer]));
	    SendClientMessageEx(PlayerData[playerid][pTransfer], -1, "%s ได้โอนเงิน %s เข้าบัญชีธนาคารของคุณ", ReturnName(playerid), FormatNumber(amount));

		if(TogAlertLog){
			if(amount >= 100000){
				format(string, sizeof(string), "> [%s] [%s] transfermoney to [%s] amount [%s]", ReturnDate(), ReturnRoleplayName(playerid), ReturnRoleplayName(PlayerData[playerid][pTransfer]), FormatNumber(amount));
				DCC_SendChannelMessage(MoneyLogChannel, string);
			}
		}
		Log_Write("logs/transfermoney.txt", "[%s] %s transfermoney to %s [%s]", ReturnDate(), ReturnRoleplayName(playerid), ReturnRoleplayName(PlayerData[playerid][pTransfer]), FormatNumber(amount));
	}
	return 1;
}

Dialog:Withdraw(playerid, response, listitem, inputtext[]){
	if (response){
	    new amount = strval(inputtext);

	    if (isnull(inputtext)) return Dialog_ShowEasy(playerid, Withdraw, DIALOG_STYLE_INPUT, "ถอนเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการถอน:", "ถอนเงิน", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (amount < 1 || amount > PlayerData[playerid][pBankMoney]) return Dialog_ShowEasy(playerid, Withdraw, DIALOG_STYLE_INPUT, "ถอนเงิน", "ข้อผิดพลาด: มีเงินไม่พอ!\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการถอน:", "ถอนเงิน", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));

		PlayerData[playerid][pBankMoney] -= amount;
	    GiveMoney(playerid, amount, "withdrawbank");

	    SendClientMessageEx(playerid, -1, "คุณถอนเงิน %s ออกจากบัญชีธนาคารของคุณ", FormatNumber(amount));
        Dialog_ShowEasy(playerid, Withdraw, DIALOG_STYLE_INPUT, "ถอนเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการถอน:", "ถอนเงิน", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));
	}
	else {
	    Dialog_ShowEasy(playerid, BankAccount, DIALOG_STYLE_LIST, "บัญชีธนาคาร", "ฝากเงิน\nถอนเงิน\nทำการโอน", "เลือก", "กลับ");
	}
	return 1;
}

Dialog:Deposit(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_ShowEasy(playerid, Deposit, DIALOG_STYLE_INPUT, "ฝากเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการฝาก:", "ฝากเงิน", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (amount < 1 || amount > GetMoney(playerid))
			return Dialog_ShowEasy(playerid, Deposit, DIALOG_STYLE_INPUT, "ฝากเงิน", "ข้อผิดพลาด: คุณไม่ได้มีเงินมากขนาดนั้น\n\nยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการฝาก:", "ฝากเงิน", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));

		PlayerData[playerid][pBankMoney] += amount;
	    GiveMoney(playerid, -amount, "depositbank");

	    SendClientMessageEx(playerid, -1, "คุณฝากเงิน %s เข้าบัญชีธนาคารของคุณ", FormatNumber(amount));
        Dialog_ShowEasy(playerid, Deposit, DIALOG_STYLE_INPUT, "ฝากเงิน", "ยอดเงินในบัญชีธนาคารของคุณ: %s\n\nโปรดป้อนจำนวนเงินที่ต้องการฝาก:", "ฝากเงิน", "กลับ", FormatNumber(PlayerData[playerid][pBankMoney]));
	}
	else {
	    Dialog_ShowEasy(playerid, BankAccount, DIALOG_STYLE_LIST, "บัญชีธนาคาร", "ฝากเงิน\nถอนเงิน\nทำการโอน", "เลือก", "กลับ");
	}
	return 1;
}

//CMD
CMD:atm(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;

	if (ATM_Nearest(playerid) == -1)
		return SendClientMessage(playerid, -1, "คุณไม่ได้อยู่ในขอบเขตของเครื่อง ATM");

	Dialog_ShowEasy(playerid, Bank, DIALOG_STYLE_LIST, "บัญชีธนาคาร", "เงินเขียวในธนาคาร: %s", "เลือก", "ยกเลิก", FormatNumber(PlayerData[playerid][pBankMoney]));
	return 1;
}

CMD:atmcmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[ATMCMDS]: /makeatm, /removeatm, /editatm");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

CMD:makeatm(playerid)
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	new id = -1;

	id = ATM_Create(playerid);

	if (id == -1)
		return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างเครื่อง ATM เกินขีดจำกัดแล้ว");

	SendClientMessageEx(playerid, -1, "คุณประสบความสำเร็จในการสร้างเครื่อง ATM ไอดี: %d", id);
	return 1;
}

CMD:editatm(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	new id = -1;

	if (sscanf(params, "d", id))
		return SendClientMessage(playerid, -1, "/editatm [atm id]");

	if ((id < 0 || id >= MAX_ATM_MACHINES) || !ATMData[id][atmExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีเครื่อง ATM ไม่ถูกต้อง");

	PlayerData[playerid][pEditPump] = -1;
	EditDynamicObject(playerid, ATMData[id][atmObject]);
	EditATM[playerid] = id;
	SendClientMessageEx(playerid, -1, "คุณได้เริ่มแก้ไข ATM ID: %d", id);
	return 1;
}

CMD:removeatm(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	new id = -1;

	if (sscanf(params, "d", id))
		return SendClientMessage(playerid, -1, "/destroyatm [atm id]");

	if ((id < 0 || id >= MAX_ATM_MACHINES) || !ATMData[id][atmExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีเครื่อง ATM ไม่ถูกต้อง");

	ATM_Delete(id);
	SendClientMessageEx(playerid, -1, "คุณประสบความสำเร็จในการทำลายเครื่อง ATM ไอดี: %d", id);
	return 1;
}