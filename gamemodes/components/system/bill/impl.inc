#if defined _inc_impl
	#undef _inc_impl
#endif

Ticket_Add(suspectid, price, groupid, playerid, const reason[])
{
	new
	    string[1024];

	for (new i = 0; i != MAX_PLAYER_TICKETS; i ++) if (!TicketData[suspectid][i][ticketExists])
	{
	    TicketData[suspectid][i][ticketExists] = true;
	    TicketData[suspectid][i][ticketFee] = price;
		TicketData[suspectid][i][ticketGroupID] = groupid;

	    format(TicketData[suspectid][i][ticketDate], 36, ReturnDate());
        format(TicketData[suspectid][i][ticketBy], 64, ReturnRoleplayName(playerid));
	    format(TicketData[suspectid][i][ticketReason], 64, reason);

		format(string, sizeof(string), "INSERT INTO `tickets` (`ID`, `ticketFee`, `ticketGroupID`, `ticketBy`, `ticketDate`, `ticketReason`) VALUES('%d', '%d', '%d', '%s', '%s', '%s')", PlayerData[suspectid][pID], price, TicketData[suspectid][i][ticketGroupID], TicketData[suspectid][i][ticketBy], TicketData[suspectid][i][ticketDate], SQL_ReturnEscaped(reason));
		mysql_tquery(dbCon, string, "OnTicketCreated", "dd", suspectid, i);

		return i;
	}
	return -1;
}

forward OnTicketCreated(playerid, ticketid);
public OnTicketCreated(playerid, ticketid)
{
	if (ticketid == -1 || !TicketData[playerid][ticketid][ticketExists])
	    return 0;

	TicketData[playerid][ticketid][ticketID] = cache_insert_id();
	return 1;
}

Ticket_Remove(playerid, ticketid)
{
	if (ticketid != -1 && TicketData[playerid][ticketid][ticketExists])
	{
	    new
	        string[90];

		format(string, sizeof(string), "DELETE FROM `tickets` WHERE `ID` = '%d' AND `ticketID` = '%d'", PlayerData[playerid][pID], TicketData[playerid][ticketid][ticketID]);
		mysql_tquery(dbCon, string);

	    TicketData[playerid][ticketid][ticketExists] = false;
	    TicketData[playerid][ticketid][ticketID] = 0;
	    TicketData[playerid][ticketid][ticketFee] = 0;
	}
	return 1;
}

CMD:ticket(playerid, params[])
{
	new
	    userid,
	    price,
	    reason[64];

	if (GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_MEDIC && GetGroupType(playerid) != GROUP_NATIONAL)
        return 0;

	if (sscanf(params, "uds[64]", userid, price, reason))
		return SystemMsg(playerid, "/ticket [playerid/name] [price] [reason]");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
	    return ErrorMsg(playerid, "ผู้เล่นนั้นตัดการเชื่อมต่อหรือไม่ได้อยู่ใกล้คุณ");

	/*if (userid == playerid)
	    return ErrorMsg(playerid, "คุณไม่สามารถเขียนใบสั่งให้ตัวเองได้");
*/
	if (price < 1 || price > 10000)
	    return ErrorMsg(playerid, "ราคาต้องไม่ต่ำกว่า $1 หรือมากกว่า $10,000");

	new id = Ticket_Add(userid, price, PlayerData[playerid][pGroup], playerid, reason);

	if (id != -1) {
	    SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้เขียน ใบสั่ง/บิล ให้ %s เป็นจำนวน %s สาเหตุ: %s", ReturnRoleplayName(userid), FormatNumber(price), reason);
	    SendClientMessageEx(userid, COLOR_YELLOW, "%s ได้เขียน ใบสั่ง/บิล ให้คุณเป็นจำนวน %s สาเหตุ: %s", ReturnRoleplayName(playerid), FormatNumber(price), reason);

		SendClientMessage(userid, COLOR_RED, "[คำเตือน]: หากคุณไม่จ่าย ใบสั่ง/บิล นี้เกิน 1 PayCheck ของคุณ ระบบจะทำการหักเงินของคุณอัตโนมัติ");

	    SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้เขียน ใบสั่ง/บิล ให้กับ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
	    Log_Write("logs/ticket_log.txt", "[%s] %s has written a %s ticket to %s, reason: %s", ReturnDate(), ReturnRoleplayName(playerid), FormatNumber(price), ReturnRoleplayName(userid), reason);
	}
	else {
	    ErrorMsg(playerid, "ผู้เล่นนั้นมีใบสั่ง %d ใบแล้ว", MAX_PLAYER_TICKETS);
	}
	return 1;
}

CMD:tickets(playerid, const params[])
{
    if(LoggedIn[playerid])
	    ViewTickets(playerid);
    return 1;
}

ViewTickets(playerid)
{
	new string[2048], menu[20], count;

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

	SetPVarInt(playerid, "page", 1);

	for(new i=0; i<MAX_PLAYER_TICKETS; i++)
	{
	    if(TicketData[playerid][i][ticketExists])
	    {
            if(count == 20)
            {
                format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                break;
            }
            format(menu, 20, "menu%d", ++count);
            SetPVarInt(playerid, menu, i);
            format(string, sizeof(string), "%s%s (ถูกเขียนโดย: %s) (%s - %s)\n", string, TicketData[playerid][i][ticketReason], TicketData[playerid][i][ticketBy], FormatNumber(TicketData[playerid][i][ticketFee]), TicketData[playerid][i][ticketDate]);
        }
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ใบสั่ง/บิล", "ไม่พบใบสั่ง/บิล..", "ปิด", "");
	else Dialog_ShowEasy(playerid, ShowPlayerTickets, DIALOG_STYLE_LIST, "ใบสั่ง/บิล", string, "จ่าย", "ยกเลิก");
	return 1;
}

ShowPlayerViewTickets(playerid){
    new ticketid = GetPVarInt(playerid, "billID");

    if (!TicketData[playerid][ticketid][ticketExists])
        return ErrorMsg(playerid, "ไม่มีใบสั่งในช่องที่เลือกนี้");

    if (GetMoney(playerid) < TicketData[playerid][ticketid][ticketFee])
        return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะจ่ายใบสั่งนี้");

    GiveMoney(playerid, -TicketData[playerid][ticketid][ticketFee], "Pay ticket");
	GroupData[TicketData[playerid][ticketid][ticketGroupID]][groupMoney] += TicketData[playerid][ticketid][ticketFee];
	Group_Save(TicketData[playerid][ticketid][ticketGroupID]);

	//SendFactionMessage(TicketData[playerid][ticketid][ticketGroupID], COLOR_RADIO, "(( %s(%d) ได้ทำการจ่าย ใบสั่ง/บิล จำนวนเงิน %s จะเข้าคลังเงินของกลุ่ม ))", ReturnRoleplayName(playerid), playerid, FormatNumber(TicketData[playerid][ticketid][ticketFee]));
    SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้จ่าย %s ให้กับ ใบสั่ง/บิล เป็นจำนวน \"%s\"", FormatNumber(TicketData[playerid][ticketid][ticketFee]), TicketData[playerid][ticketid][ticketReason]);
    Ticket_Remove(playerid, ticketid);
    return ViewTickets(playerid);
}

AllRemoveTicket(playerid){
	new priceallticket, count = 0;
	for(new i=0; i<MAX_PLAYER_TICKETS; i++){
		if(TicketData[playerid][i][ticketExists]){
			count++;
			priceallticket += TicketData[playerid][i][ticketFee];
			GroupData[TicketData[playerid][i][ticketGroupID]][groupMoney] += TicketData[playerid][i][ticketFee];
			Group_Save(TicketData[playerid][i][ticketGroupID]);
			Ticket_Remove(playerid, i);
		}
	}

	if(count != 0){
		SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณมีใบสั่งทั้งหมดจำนวน %d ใบ และคุณได้ทำการจ่ายทั้งหมดเป็นจำนวนเงิน %s", count, FormatNumber(priceallticket));
		GiveMoney(playerid, -priceallticket, "pay ticket all");
	}
	else if(count == 0){
		SendClientMessage(playerid, COLOR_YELLOW, "- คุณไม่มี ใบสั่ง/บิล ที่ติดค้างไว้");
	}
	return 1;
}

CMD:allremoveticket(playerid, params[]){
	if(PlayerData[playerid][pAdmin] >= 1338){
		AllRemoveTicket(playerid);
	}
	return 1;
}

Dialog:ShowPlayerTickets(playerid, response, listitem, inputtext[])
{
	if(response) {

		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "billID", GetPVarInt(playerid, str_biz));
			ShowPlayerViewTickets(playerid);
			return 1;
		}

		new currentPage = GetPVarInt(playerid, "page");
		if(listitem==0) {
			if(currentPage>1) currentPage--;
		}
		else if(listitem == 21) currentPage++;

		new string[2048], count;
		format(string, sizeof(string), "%s{B4B5B7}หน้า %d\n", string, (currentPage==1) ? 1 : currentPage-1);

		SetPVarInt(playerid, "page", currentPage);

		new skipitem = (currentPage-1) * 20;

		for(new i=0; i<MAX_PLAYER_TICKETS; i++)
		{
		    if(TicketData[playerid][i][ticketExists])
	    	{
                if(skipitem)
                {
                    skipitem--;
                    continue;
                }
                if(count == 20)
                {
                    format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                    break;
                }
                format(menu, 20, "menu%d", ++count);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s%s (ถูกเขียนโดย: %s) (%s - %s)\n", string, TicketData[playerid][i][ticketReason], TicketData[playerid][i][ticketBy], FormatNumber(TicketData[playerid][i][ticketFee]), TicketData[playerid][i][ticketDate]);
			}
		}

		Dialog_ShowEasy(playerid, ShowPlayerTickets, DIALOG_STYLE_LIST, "ใบสั่ง/บิล", string, "จ่าย", "ยกเลิก");
	}
	return 1;
}