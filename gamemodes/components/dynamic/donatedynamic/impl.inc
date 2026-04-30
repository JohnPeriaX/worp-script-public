#if defined _inc_impl
	#undef _inc_impl
#endif

forward DonateItem_Load();
public DonateItem_Load(){
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_DONATEITEM)
	{
	    DonateItemData[i][donateitemEx] = true;

	    cache_get_value_name_int(i, "donateitemID", DonateItemData[i][donateitemID]);
	    cache_get_value_name(i, "donateitemName", DonateItemData[i][donateitemName], 32);
	    cache_get_value_name_int(i, "donateitemModel", DonateItemData[i][donateitemModel]);
        cache_get_value_name(i, "donateitemInfo", DonateItemData[i][donateitemInfo], 64);
	    cache_get_value_name_int(i, "donateitemPrice", DonateItemData[i][donateitemPrice]);

        Count_DonateItem++;

	}
	printf("(( [MYSQL]: Load %d DonateItems Successfully ))", Count_DonateItem);
	return 1;
}

ShowMenuDonateCharacter(playerid){
    Dialog_ShowEasy(playerid, DonateItemCharacter, DIALOG_STYLE_LIST, "ไอเท็มโดเนทติดตัว", "- ฉายา Login\t500 Wallet", "ซื้อ", "ยกเลิก");
}

Dialog:DonateItemCharacter(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(PlayerData[playerid][pLevel] < 5) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] คุณจะต้องมีเลเวลมากกว่าเท่ากับ 5 ถึงจะซื้อได้", "ตกลง", "");
            if(AccountData[playerid][uWallet] < 500) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] คุณมี Wallet ไม่เพียงพอ", "ตกลง", "");
            if(PlayerData[playerid][pChayaLogin]) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] คุณมีฉายา Login อยู่แล้ว", "ตกลง", "");
            AccountData[playerid][uWallet] -= 500;
            UpdatePlayerWallet(playerid);
            PlayerData[playerid][pChayaLogin] = true;
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การสั่งซื้อสำเร็จ", "คุณได้ซื้อ ฉายา Login ในราคา 500 Wallet เรียบร้อยแล้ว", "ตกลง", "");
        }
    }
    return 1;
}

ShowMenuDonateItems(playerid){
    new string[2048], menu[20], count;

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);
	SetPVarInt(playerid, "donateitempages", 1);
	for(new i=0; i<MAX_DONATEITEM; i++)
	{
	    if(DonateItemData[i][donateitemEx])
	    {
            if(count == 20)
            {
                format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                break;
            }
            format(menu, 20, "menudonateitem%d", ++count);
            SetPVarInt(playerid, menu, i);
            format(string, sizeof(string), "%s %s  [%s Wallet]  %s\n", string, DonateItemData[i][donateitemName], FormatNumberNotMoney(DonateItemData[i][donateitemPrice]), DonateItemData[i][donateitemInfo]);
		}
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ร้านค้าโดเนท", "ไม่มีไอเท็มโดเนท..", "ปิด", "");
	else Dialog_ShowEasy(playerid, DonateItemShop, DIALOG_STYLE_LIST, "ร้านค้าโดเนท", string, "ซื้อ", "ปิด");
    return 1;
}

Dialog:DonateItemShop(playerid, response, listitem, inputtext[])
{
	if(response) {

		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menudonateitem%d", listitem);

			SetPVarInt(playerid, "donateitemID", GetPVarInt(playerid, str_biz));
			SetPlayerBuyDonateItem(playerid);
			return 1;
		}

		new currentPage = GetPVarInt(playerid, "donateitempages");
		if(listitem==0) {
			if(currentPage>1) currentPage--;
		}
		else if(listitem == 21) currentPage++;

		new string[2048], count;
		format(string, sizeof(string), "%s{B4B5B7}หน้า %d\n", string, (currentPage==1) ? 1 : currentPage-1);

		SetPVarInt(playerid, "donateitempages", currentPage);

		new skipitem = (currentPage-1) * 20;

		for(new i=0; i<MAX_DONATEITEM; i++)
        {
            if(DonateItemData[i][donateitemEx])
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
                format(menu, 20, "menudonateitem%d", ++count);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s %s  [%s Wallet]  %s\n", string, DonateItemData[i][donateitemName], FormatNumberNotMoney(DonateItemData[i][donateitemPrice]), DonateItemData[i][donateitemInfo]);
			}
		}
		Dialog_ShowEasy(playerid, DonateItemShop, DIALOG_STYLE_TABLIST_HEADERS, "ร้านค้าโดเนท", string, "ซื้อ", "ปิด");
	}
	return 1;
}

Dialog:InputAmountBuyDonate(playerid, response, listitem, inputtext[]){
    if(!response) {
        DeletePVar(playerid, "donateitemID");
        ShowMenuDonateItems(playerid);
        return 1;
    }
    if(response){
        new itemid = GetPVarInt(playerid, "donateitemID");
        new string[256];
        if(itemid != -1){
            new amount = strval(inputtext);
            if(amount <= 0){
                format(string, sizeof string, "[!] คุณต้องกรอกจำนวนมากกว่า 0\nสินค้า: %s ราคา %s Wallet/ชิ้น\nระบุจำนวนที่คุณต้องการจะซื้อ: ", DonateItemData[itemid][donateitemName], FormatNumberNotMoney(DonateItemData[itemid][donateitemPrice]));
                Dialog_ShowEasy(playerid, InputAmountBuyDonate, DIALOG_STYLE_INPUT, "ใส่จำนวนที่ต้องการซื้อ", string, "ตกลง", "กลับ");
                return 1;
            }

            if(amount >= 50){
                format(string, sizeof string, "[!] ซื้อได้รอบละไม่เกิน 50 ชิ้นเท่านั้น\nสินค้า: %s ราคา %s Wallet/ชิ้น\nระบุจำนวนที่คุณต้องการจะซื้อ: ", DonateItemData[itemid][donateitemName], FormatNumberNotMoney(DonateItemData[itemid][donateitemPrice]));
                Dialog_ShowEasy(playerid, InputAmountBuyDonate, DIALOG_STYLE_INPUT, "ใส่จำนวนที่ต้องการซื้อ", string, "ตกลง", "กลับ");
                return 1;
            }

            new price = amount * DonateItemData[itemid][donateitemPrice];
            if(AccountData[playerid][uWallet] < price){
                format(string, sizeof string, "[!] คุณมี Wallet ไม่พอ\nสินค้า: %s ราคา %s Wallet/ชิ้น\nระบุจำนวนที่คุณต้องการจะซื้อ: ", DonateItemData[itemid][donateitemName], FormatNumberNotMoney(DonateItemData[itemid][donateitemPrice]));
                Dialog_ShowEasy(playerid, InputAmountBuyDonate, DIALOG_STYLE_INPUT, "ใส่จำนวนที่ต้องการซื้อ", string, "ตกลง", "กลับ");
                return 1;
            }

            PlayerGetAmountBuyDonate[playerid] = amount;
            format(string, sizeof string, "{FFFFFF}| สินค้า: {FFB025}%s {FFFFFF}ราคา {FFB025}%s Wallet/ชิ้น\
            \n{FFFFFF}| คุณต้องการซื้อจำนวน {FFB025}'%d' {FFFFFF}ชิ้นในราคา {FFB025}'%s Wallet'", DonateItemData[itemid][donateitemName], FormatNumberNotMoney(DonateItemData[itemid][donateitemPrice]), PlayerGetAmountBuyDonate[playerid], FormatNumberNotMoney(price));
            Dialog_ShowEasy(playerid, ConfirmBuyDonate, DIALOG_STYLE_MSGBOX, "ยืนยันการซื้อ", string, "ซื้อ", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:ConfirmBuyDonate(playerid, response, listitem, inputtext[]){
    if(!response) {
        DeletePVar(playerid, "donateitemID");
        PlayerGetAmountBuyDonate[playerid] = 0;
        return 1;
    }
    if(response){
        new itemid = GetPVarInt(playerid, "donateitemID");
        if(itemid != -1 && PlayerGetAmountBuyDonate[playerid] != 0){
            new string[256];
            new price = PlayerGetAmountBuyDonate[playerid] * DonateItemData[itemid][donateitemPrice];
            new id = PlayerInventory_AddItem(playerid, DonateItemData[itemid][donateitemName], DonateItemData[itemid][donateitemModel], PlayerGetAmountBuyDonate[playerid]);
            if (id == -1){
                return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            }

            format(string, sizeof string, "{FFFFFF}[ซื้อของโดเนท]: คุณได้ซื้อ {FFB025}'%s' {FFFFFF}จำนวน {FFB025}'%d' {FFFFFF}ในราคา {FFB025}'%s Wallet' {FFFFFF}สำเร็จแล้ว", DonateItemData[itemid][donateitemName], PlayerGetAmountBuyDonate[playerid], FormatNumberNotMoney(price));
            Dialog_ShowEasy(playerid, DetailBuyDonateFinish, DIALOG_STYLE_MSGBOX, "การซื้อสำเร็จ", string, "ตกลง", "");

            format(string, sizeof(string), "%s ได้ทำการซื้อ %s จำนวน %d ในราคา %s Wallet", ReturnRoleplayName(playerid), DonateItemData[itemid][donateitemName], PlayerGetAmountBuyDonate[playerid], FormatNumberNotMoney(price));
            SendAdminsMessage(1, COLOR_YELLOW, string);
            Log_Write("logs/buydonateitems.txt", "[%s] %s buy %s amount %d price %s Wallet", ReturnDate(), ReturnRoleplayName(playerid), DonateItemData[itemid][donateitemName], PlayerGetAmountBuyDonate[playerid], FormatNumberNotMoney(price));
            AccountData[playerid][uWallet] -= price;
            PlayerGetAmountBuyDonate[playerid] = 0;
            UpdatePlayerWallet(playerid);
        }
    }
    return 1;
}

SetPlayerBuyDonateItem(playerid){
    new itemid = GetPVarInt(playerid, "donateitemID");
    new string[256];

    format(string, sizeof string, "สินค้า: %s ราคา %s Wallet/ชิ้น\nระบุจำนวนที่คุณต้องการจะซื้อ: ", DonateItemData[itemid][donateitemName], FormatNumberNotMoney(DonateItemData[itemid][donateitemPrice]));
    Dialog_ShowEasy(playerid, InputAmountBuyDonate, DIALOG_STYLE_INPUT, "ใส่จำนวนที่ต้องการซื้อ", string, "ตกลง", "กลับ");
    return 1;
}

CMD:refreshdonateitem(playerid, params[]){
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pAdmin] >= 1338){
            for(new i=0; i<MAX_DONATEITEM; i++) if(DonateItemData[i][donateitemEx]){
                DonateItemData[i][donateitemEx] = false;
                DonateItemData[i][donateitemModel] = 0;
                DonateItemData[i][donateitemID] = 0;
            }

            Count_DonateItem = 0;
            mysql_tquery(dbCon, "SELECT * FROM `donateitems`", "DonateItem_Load", "");
            SendClientMessage(playerid, -1, "คุณได้ทำการโหลด 'DonateItem'");
        }
    }
    return 1;
}