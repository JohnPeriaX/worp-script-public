#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
	AddItem_MarketStore();
	return 1;
}

AddItem_MarketStore(){
	Market_Store[0][item_Have] = true;
	format(Market_Store[0][item_Name], 64, "เชือก");
	format(Market_Store[0][item_RealName], 64, "Rope");
	Market_Store[0][item_Model] = 19088;
	Market_Store[0][item_Price] = 500;
	format(Market_Store[0][item_Info], 64, "ใช้สำหรับลากคน");

	Market_Store[1][item_Have] = true;
	format(Market_Store[1][item_Name], 64, "โทรศัพท์มือถือ");
	format(Market_Store[1][item_RealName], 64, "Mobile Phone");
	Market_Store[1][item_Model] = 18872;
	Market_Store[1][item_Price] = 5000;
	format(Market_Store[1][item_Info], 64, "ใช้โทรออก, ส่งข้อความ");

	Market_Store[2][item_Have] = true;
	format(Market_Store[2][item_Name], 64, "บุหรี่");
	format(Market_Store[2][item_RealName], 64, "Cigar");
	Market_Store[2][item_Model] = 3044;
	Market_Store[2][item_Price] = 100;
	format(Market_Store[2][item_Info], 64, "ใช้สูบเพื่อความเท่");

	Market_Store[3][item_Have] = true;
	format(Market_Store[3][item_Name], 64, "เสื้อชูชีพ");
	format(Market_Store[3][item_RealName], 64, "Life Vest");
	Market_Store[3][item_Model] = 19904;
	Market_Store[3][item_Price] = 1500;
	format(Market_Store[3][item_Info], 64, "ใช้สำหรับทำงานเก็บแมงกระพรุน");

	Market_Store[4][item_Have] = true;
	format(Market_Store[4][item_Name], 64, "พิมพ์เขียวเครื่องขุดบ่อน้ำมัน");
	format(Market_Store[4][item_RealName], 64, "Drill Tool Blueprint");
	Market_Store[4][item_Model] = 1277;
	Market_Store[4][item_Price] = 2000;
	format(Market_Store[4][item_Info], 64, "ใช้คราฟเครื่องขุดบ่อน้ำมัน");

	Market_Store[5][item_Have] = true;
	format(Market_Store[5][item_Name], 64, "กล้องถ่ายรูป");
	format(Market_Store[5][item_RealName], 64, "Camera");
	Market_Store[5][item_Model] = 367;
	Market_Store[5][item_Price] = 50000;
	format(Market_Store[5][item_Info], 64, "ใช้สำหรับถ่ายภาพต่างๆ (ใช้ได้ตลอดชีพ)");

	Market_Store[6][item_Have] = true;
	format(Market_Store[6][item_Name], 64, "กระเป๋าตั้งแคมป์");
	format(Market_Store[6][item_RealName], 64, "Tent Backpack");
	Market_Store[6][item_Model] = 19559;
	Market_Store[6][item_Price] = 3000;
	format(Market_Store[6][item_Info], 64, "ใช้สำหรับตั้งแคมป์ในพื้นที่ล่าสัตว์");

	Market_Store[7][item_Have] = true;
	format(Market_Store[7][item_Name], 64, "กล่องซ่อมด่วน");
	format(Market_Store[7][item_RealName], 64, "Quick Repair Kit");
	Market_Store[7][item_Model] = 19832;
	Market_Store[7][item_Price] = 5000;
	format(Market_Store[7][item_Info], 64, "ใช้สำหรับซ่อมยานพาหนะ");

	Market_Store[8][item_Have] = true;
	format(Market_Store[8][item_Name], 64, "น้ำยา EXP x2");
	format(Market_Store[8][item_RealName], 64, "EXP X2 Bottle");
	Market_Store[8][item_Model] = 1950;
	Market_Store[8][item_Price] = 50000;
	format(Market_Store[8][item_Info], 64, "ใช้สำหรับเปิดเพื่อเพิ่มอัตรา EXP x2");
	return 1;
}

Show24Shop(playerid){
	new string[2056], stringdata[1024];

	for(new i=0; i<MAX_MARKET_STORE_ITEM; i++) if(Market_Store[i][item_Have]){
		format(stringdata, sizeof stringdata, "%s| %s\t%s\t%s\n", stringdata, Market_Store[i][item_Name], FormatNumber(Market_Store[i][item_Price]), Market_Store[i][item_Info]);
	}

	format(string, sizeof string, "ชื่อสินค้า\tราคา\tรายละเอียด\n%s", stringdata);
	Dialog_ShowEasy(playerid, DialogMarketShop, DIALOG_STYLE_TABLIST_HEADERS, "ร้านสะดวกซื้อ", string, "ซื้อ", "ยกเลิก");
	return 1;
}

Dialog:DialogMarketShop(playerid, response, listitem, inputtext[]){
	if(!response) return 1;
	if(response){
		if(listitem >= 0 && listitem <= MAX_MARKET_STORE_ITEM){
			new string[128];
			SetPVarInt(playerid, "MarketShopItemID", listitem);
			format(string, sizeof string, "{FFFFFF}| ไอเท็ม: {FFB025}'%s' {FFFFFF}ราคา {FFB025}'%s/ชิ้น'\n{FFFFFF}ระบุจำนวนที่คุณต้องการจะซื้อ: ", Market_Store[listitem][item_Name], FormatNumber(Market_Store[listitem][item_Price]));
			Dialog_ShowEasy(playerid, InputAmountMarketShop, DIALOG_STYLE_INPUT, "ใส่จำนวนที่ต้องการจะซื้อ", string, "ซื้อ", "กลับ");
		}
	}
	return 1;
}

Dialog:InputAmountMarketShop(playerid, response, listitem, inputtext[]){
	if(!response){
		DeletePVar(playerid, "MarketShopItemID");
		return Show24Shop(playerid);
	}
	if(response){
		new itemid = GetPVarInt(playerid, "MarketShopItemID");
		if(itemid >= 0 && itemid <= MAX_MARKET_STORE_ITEM){
			new string[256];
			new amount = strval(inputtext);
			if(amount <= 0){
				format(string, sizeof string, "{FF2525}[!] คุณต้องกรอกจำนวนมากกว่า 0 เท่านั้น\n{FFFFFF}| ไอเท็ม: {FFB025}'%s' {FFFFFF}ราคา {FFB025}'%s/ชิ้น'\n{FFFFFF}ระบุจำนวนที่คุณต้องการจะซื้อ: ", Market_Store[itemid][item_Name], FormatNumber(Market_Store[itemid][item_Price]));
				Dialog_ShowEasy(playerid, InputAmountMarketShop, DIALOG_STYLE_INPUT, "ใส่จำนวนที่ต้องการจะซื้อ", string, "ซื้อ", "กลับ");
				return 1;
			}

			if(!strcmp(Market_Store[itemid][item_RealName], "Quick Repair Kit", true)){
				if(amount > 10){
					format(string, sizeof string, "{FF2525}[!] คุณสามารถซื้อได้จำนวนสูงสุด 10 ชิ้น ต่อครั้ง\n{FFFFFF}| ไอเท็ม: {FFB025}'%s' {FFFFFF}ราคา {FFB025}'%s/ชิ้น'\n{FFFFFF}ระบุจำนวนที่คุณต้องการจะซื้อ: ", Market_Store[itemid][item_Name], FormatNumber(Market_Store[itemid][item_Price]));
					Dialog_ShowEasy(playerid, InputAmountMarketShop, DIALOG_STYLE_INPUT, "ใส่จำนวนที่ต้องการจะซื้อ", string, "ซื้อ", "กลับ");
					return 1;
				}
			}
			else{
				if(amount > 50){
					format(string, sizeof string, "{FF2525}[!] คุณสามารถซื้อได้จำนวนสูงสุด 50 ชิ้น ต่อครั้ง\n{FFFFFF}| ไอเท็ม: {FFB025}'%s' {FFFFFF}ราคา {FFB025}'%s/ชิ้น'\n{FFFFFF}ระบุจำนวนที่คุณต้องการจะซื้อ: ", Market_Store[itemid][item_Name], FormatNumber(Market_Store[itemid][item_Price]));
					Dialog_ShowEasy(playerid, InputAmountMarketShop, DIALOG_STYLE_INPUT, "ใส่จำนวนที่ต้องการจะซื้อ", string, "ซื้อ", "กลับ");
					return 1;
				}
			}

			new price = amount * Market_Store[itemid][item_Price];
			if(GetMoney(playerid) < price){
				format(string, sizeof string, "{FF2525}[!] คุณมีเงินไม่พอ (ขาดอีก %s)\n{FFFFFF}| ไอเท็ม: {FFB025}'%s' {FFFFFF}ราคา {FFB025}'%s/ชิ้น'\n{FFFFFF}ระบุจำนวนที่คุณต้องการจะซื้อ: ", FormatNumber(price-GetMoney(playerid)), Market_Store[itemid][item_Name], FormatNumber(Market_Store[itemid][item_Price]));
				Dialog_ShowEasy(playerid, InputAmountMarketShop, DIALOG_STYLE_INPUT, "ใส่จำนวนที่ต้องการจะซื้อ", string, "ซื้อ", "กลับ");
				return 1;
			}

			SetPVarInt(playerid, "TotalPriceMarketShop", price);
			SetPVarInt(playerid, "AmountMarketShop", amount);
			format(string, sizeof string, "{FFFFFF}| คุณต้องการที่จะซื้อไอเท็ม {FFAC25}'%s' {FFFFFF}จำนวน {FFAC25}'%d' {FFFFFF}ชิ้น ในราคา {FFAC25}'%s' {FFFFFF}หรือไม่?", Market_Store[itemid][item_Name], amount, FormatNumber(price));
			Dialog_ShowEasy(playerid, ConfirmBuyMarketShop, DIALOG_STYLE_MSGBOX, "ยืนยันการซื้อไอเท็ม", string, "ซื้อ", "ยกเลิก");
		}
	}
	return 1;
}

Dialog:ConfirmBuyMarketShop(playerid, response, listitem, inputtext[]){
	if(!response) {
		DeletePVar(playerid, "MarketShopItemID");
		DeletePVar(playerid, "TotalPriceMarketShop");
		DeletePVar(playerid, "AmountMarketShop");
		return 1;
	}
	if(response){
		new price = GetPVarInt(playerid, "TotalPriceMarketShop");
		new itemid = GetPVarInt(playerid, "MarketShopItemID");
		new amount = GetPVarInt(playerid, "AmountMarketShop");
		new string[128];

		if(!strcmp(Market_Store[itemid][item_RealName], "Quick Repair Kit", true)){
			if(PlayerData[playerid][pRepairKitBuying] + amount > 10){
				DeletePVar(playerid, "MarketShopItemID");
				DeletePVar(playerid, "TotalPriceMarketShop");
				DeletePVar(playerid, "AmountMarketShop");
				SendClientMessageEx(playerid, COLOR_RED, "| คุณสามารถซื้อกล่องซ่อมด่วนได้ไม่เกินวันละ 10 กล่อง (คุณสามารถซื้อได้อีก %d กล่อง)", 10 - PlayerData[playerid][pRepairKitBuying]);
				return 1;
			}
		}

		new additem = PlayerInventory_AddItem(playerid, Market_Store[itemid][item_RealName], Market_Store[itemid][item_Model], amount);
		if(additem == -1) {
			DeletePVar(playerid, "MarketShopItemID");
			DeletePVar(playerid, "TotalPriceMarketShop");
			DeletePVar(playerid, "AmountMarketShop");
			return ErrorMsg(playerid, "คุณมีช่องเก็บของไม่พอที่จะเก็บไอเท็มชิ้นนี้");
		}

		if(!strcmp(Market_Store[itemid][item_RealName], "Mobile Phone", true)){
			PlayerData[playerid][pNumberPhone] = random(90000) + 10000;
		}
		else if(!strcmp(Market_Store[itemid][item_RealName], "Quick Repair Kit", true)){
			PlayerData[playerid][pRepairKitBuying] += amount;
		}

		GiveMoney(playerid, -price, "ซื้อของจากร้าน 24/7");
		format(string, sizeof string, "{FFFFFF}| คุณได้ซื้อไอเท็ม {FFAC25}'%s' {FFFFFF}จำนวน {FFAC25}'%d' {FFFFFF}ในราคา {FFAC25}'%s' {FFFFFF}สำเร็จแล้ว", Market_Store[itemid][item_Name], amount, FormatNumber(price));
		Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การซื้อสำเร็จ", string, "ตกลง", "");

		DeletePVar(playerid, "MarketShopItemID");
		DeletePVar(playerid, "TotalPriceMarketShop");
		DeletePVar(playerid, "AmountMarketShop");
	}
	return 1;
}