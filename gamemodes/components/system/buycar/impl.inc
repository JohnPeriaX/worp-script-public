#if defined _inc_impl
	#undef _inc_impl
#endif

forward CarSell_Load();
public CarSell_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_CARSELL)
	{
	    CarSellData[i][carsellExists] = true;

	    cache_get_value_name_int(i, "carsellID", CarSellData[i][carsellID]);
	    cache_get_value_name_int(i, "carsellModel", CarSellData[i][carsellModel]);
        cache_get_value_name_int(i, "carsellPriceType", CarSellData[i][carsellPriceType]);
	    cache_get_value_name_int(i, "carsellPrice", CarSellData[i][carsellPrice]);
	    cache_get_value_name_int(i, "carsellVipLevel", CarSellData[i][carsellVipLevel]);
        cache_get_value_name_int(i, "carsellType", CarSellData[i][carsellType]);

        Carsell_Count++;

	}
	printf("(( [MYSQL]: Load %d CarSell Successfully ))", Carsell_Count);
	return 1;
}

CarSell_Save(carsellid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `carsells` SET `carsellModel` = '%d', `carsellPriceType` = '%d', `carsellPrice` = '%d', `carsellVipLevel` = '%d', `carsellType` = '%d' WHERE `carsellID` = '%d'",
		CarSellData[carsellid][carsellModel],
        CarSellData[carsellid][carsellPriceType],
		CarSellData[carsellid][carsellPrice],
		CarSellData[carsellid][carsellVipLevel],
        CarSellData[carsellid][carsellType],
        CarSellData[carsellid][carsellID]
	);
	return mysql_tquery(dbCon, query);
}

CarSell_Add(model, pricetype, price, viplevel, type = 0)
{
    for (new i = 0; i != MAX_CARSELL; i ++)
    {
        if (!CarSellData[i][carsellExists])
        {
            CarSellData[i][carsellExists] = true;
            CarSellData[i][carsellModel] = model;
            CarSellData[i][carsellPriceType] = pricetype;
            CarSellData[i][carsellPrice] = price;
            CarSellData[i][carsellVipLevel] = viplevel;
            CarSellData[i][carsellType] = type;


            mysql_tquery(dbCon, "INSERT INTO `carsells` (`carsellVipLevel`) VALUES(0)", "OnCarSellCreated", "d", i);

            return i;
        }
    }
	return -1;
}

forward OnCarSellCreated(carsellid);
public OnCarSellCreated(carsellid)
{
	if (carsellid == -1 || !CarSellData[carsellid][carsellExists])
	    return 0;

	CarSellData[carsellid][carsellID] = cache_insert_id();
	CarSell_Save(carsellid);

	return 1;
}

CMD:carselladd(playerid, params[]){
    if(!LoggedIn[playerid])
        return 0;

    if(PlayerData[playerid][pAdmin] >= 1338){
        new model[32], pricetype, price, viplevel, id, string[128], type;
        if (sscanf(params, "s[32]I(1)I(1)I(0)I(0)", model, pricetype, price, viplevel, type)){
            SystemMsg(playerid, "/carselladd [model] [pricetype] [price] [viplevel] [type]");
            SystemMsg(playerid, "[PriceType]: [1: เงินเขียว], [2:พ้อย]");
            SystemMsg(playerid, "[Type]: [0: รถ], [1:เรือ]");
            return 1;
        }
            
        if ((model[0] = GetVehicleModelByName(model)) == 0)
            return SendClientMessage(playerid, -1, "ไอดีรุ่นไม่ถูกต้อง");

        if(price < 0)
            return ErrorMsg(playerid, "ราคาต้องมากกว่า 0");

        if(pricetype < 1 || pricetype > 2)
            return ErrorMsg(playerid, "[1: เงินเขียว], [2:พ้อย]");

        if(type < 0 || type > 1)
            return ErrorMsg(playerid, "[Type]: [0: รถ], [1:เรือ]");

        if(viplevel < 0 || viplevel > 3)
            return ErrorMsg(playerid, "VIP ต้องอยู่ในระดับ 0-3 เท่านั้น");

        id = CarSell_Add(model[0], pricetype, price, viplevel, type);

        if (id == -1)
            return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะขายเกินขีดจำกัดแล้ว");

        format(string, sizeof(string), "คุณประสบความสำเร็จยานพาหนะขายไอดี: %d", id);
        SendClientMessage(playerid, -1, string);
    }
    return 1;
}

CMD:carsellcmds(playerid, params[]){
    if(PlayerData[playerid][pAdmin] >= 1338){
        SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
        SendClientMessage(playerid, COLOR_GRAY, "[CARSELLCMDS]: /carselladd, /viewcarsells");
        SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
    }
    return 1;
}

CMD:viewcarsells(playerid, params[]){

    if(!LoggedIn[playerid])
        return 0;

    new type;
    if(sscanf(params, "d", type)){
        SystemMsg(playerid, "/viewcarsells [type]");
        SystemMsg(playerid, "[Type]: 0:รถ, 1:เรือ");
        return 1;
    }

    if(type < 0 || type > 1) return ErrorMsg(playerid, "ตัวเลือกไม่ถูกต้อง");

    if(PlayerData[playerid][pAdmin] >= 1338){
        ViewCarSell(playerid, type);
        GetTypeCarsells[playerid] = type;
    }
    return 1;
}

ViewCarSell(playerid, type)
{
    new stringhead[2048];
	new string[1024], menu[20], count;
    new stringmember[64];

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);
	SetPVarInt(playerid, "page", 1);
	for(new i=0; i<MAX_CARSELL; i++)
	{
	    if(CarSellData[i][carsellExists]){
            if(CarSellData[i][carsellType] == type){
                if(count == 20){
                    format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                    break;
                }
                format(menu, 20, "menu%d", ++count);
                SetPVarInt(playerid, menu, i);

                if(CarSellData[i][carsellVipLevel] == 0)
                    stringmember = "Regular Member";
                else if(CarSellData[i][carsellVipLevel] == 1)
                    stringmember = "Bronze Member";
                else if(CarSellData[i][carsellVipLevel] == 2)
                    stringmember = "Silver Member";
                else if(CarSellData[i][carsellVipLevel] == 3)
                    stringmember = "Gold Member";

                if(CarSellData[i][carsellPriceType] == 1)
                    format(string, sizeof(string), "%sระดับ %s\t%s(%d)\t%s\n", string, stringmember, ReturnVehicleModelName(CarSellData[i][carsellModel]), CarSellData[i][carsellModel], FormatNumber(CarSellData[i][carsellPrice]));
                else if(CarSellData[i][carsellPriceType] == 2)
                    format(string, sizeof(string), "%sระดับ %s\t%s(%d)\t%d Wallet\n", string, stringmember, ReturnVehicleModelName(CarSellData[i][carsellModel]), CarSellData[i][carsellModel], CarSellData[i][carsellPrice]);
            }
        }
	}
    format(stringhead, sizeof(stringhead), "ระดับ VIP\tชื่อยานพาหนะ\tราคา\n%s", string);
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ร้านขายยานพาหนะ", "ไม่พบข้อมูลยานพาหนะที่ขายอยู่..", "ปิด", "");
	else Dialog_ShowEasy(playerid, EditCarSell, DIALOG_STYLE_TABLIST_HEADERS, "ร้านขายยานพาหนะ", stringhead, "เลือก", "ปิด");
	return 1;
}

Dialog:EditCarSell(playerid, response, listitem, inputtext[])
{
	if(response) {

        new stringhead[2048];
        new stringmember[64];
		new menu[20];
        new id = -1;
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "carsellID", GetPVarInt(playerid, str_biz));
            if ((id = Entrance_Nearest(playerid)) != -1){
                if(EntranceData[id][entranceType] == 2){
                    BuyCarSell(playerid);
                }
                if(EntranceData[id][entranceType] == 6){
                    BuyCarSell(playerid);
                }
            }
            else{
                if(PlayerData[playerid][pAdmin] >= 1338)
			        EditCarSell(playerid);
            }
			return 1;
		}

		new currentPage = GetPVarInt(playerid, "page");
		if(listitem==0) {
			if(currentPage>1) currentPage--;
		}
		else if(listitem == 21) currentPage++;

		new string[1024], count;
		format(string, sizeof(string), "%s{B4B5B7}หน้า %d\n", string, (currentPage==1) ? 1 : currentPage-1);

		SetPVarInt(playerid, "page", currentPage);

		new skipitem = (currentPage-1) * 20;

		for(new i=0; i<MAX_CARSELL; i++)
		{
		    if(CarSellData[i][carsellExists])
	    {
                if(skipitem)
                {
                    skipitem--;
                    continue;
                }
                if(count == 20)
                {
                    format(string, sizeof(string), "%s{B4B5B7}หน้า %d\n", string, (currentPage==1) ? 1+1 : currentPage+1);
                    //format(string, sizeof(string), "%s{B4B5B7}หน้าต่อไป >>\t\t\t\n", string);
                    break;
                }
                format(menu, 20, "menu%d", ++count);
                SetPVarInt(playerid, menu, i);
                
                if(CarSellData[i][carsellVipLevel] == 0)
                    stringmember = "Regular Member";
                else if(CarSellData[i][carsellVipLevel] == 1)
                    stringmember = "Bronze Member";
                else if(CarSellData[i][carsellVipLevel] == 2)
                    stringmember = "Silver Member";
                else if(CarSellData[i][carsellVipLevel] == 3)
                    stringmember = "Gold Member";

                if(CarSellData[i][carsellPriceType] == 1)
                    format(string, sizeof(string), "%sระดับ %s\t%s(%d)\t%s\n", string, stringmember, ReturnVehicleModelName(CarSellData[i][carsellModel]), CarSellData[i][carsellModel], FormatNumber(CarSellData[i][carsellPrice]));
                else if(CarSellData[i][carsellPriceType] == 2)
                    format(string, sizeof(string), "%sระดับ %s\t%s(%d)\t%d Wallet\n", string, stringmember, ReturnVehicleModelName(CarSellData[i][carsellModel]), CarSellData[i][carsellModel], CarSellData[i][carsellPrice]);
			}
		}
        format(stringhead, sizeof(stringhead), "ระดับ VIP\tชื่อยานพาหนะ\tราคา\n%s", string);
		Dialog_ShowEasy(playerid, EditCarSell, DIALOG_STYLE_TABLIST_HEADERS, "ร้านขายยานพาหนะ", stringhead, "เลือก", "ปิด");
	}
	return 1;
}

BuyCarSell(playerid){
    new carsellid = GetPVarInt(playerid, "carsellID");
    GetCarBuy[playerid] = carsellid;
    new string[256];
    if(PlayerData[playerid][pVip] < CarSellData[GetCarBuy[playerid]][carsellVipLevel]){
        GetCarBuy[playerid] = -1;
        return ErrorMsg(playerid, "คุณมีระดับ VIP ไม่พอที่จะซื้อยานพาหนะคันนี้");
    }

    if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS)
	    return SendClientMessage(playerid, -1, "คุณเป็นเจ้าของยานพาหนะจนเต็มแล้ว");
    
    if(CarSellData[GetCarBuy[playerid]][carsellPriceType] == 1)
        format(string, sizeof(string), "คุณต้องการจะซื้อยานพาหนะ %s(%d) คันนี้ในราคา %s หรือไม่?\nหากต้องการซื้อให้กด 'ซื้อ' หากไม่ต้องการซื้อให้กด 'ยกเลิก'", ReturnVehicleModelName(CarSellData[GetCarBuy[playerid]][carsellModel]), CarSellData[GetCarBuy[playerid]][carsellModel], FormatNumber(CarSellData[GetCarBuy[playerid]][carsellPrice]));
    else if(CarSellData[GetCarBuy[playerid]][carsellPriceType] == 2)
        format(string, sizeof(string), "คุณต้องการจะซื้อยานพาหนะ %s(%d) คันนี้ในราคา %d Wallet หรือไม่?\nหากต้องการซื้อให้กด 'ซื้อ' หากไม่ต้องการซื้อให้กด 'ยกเลิก'", ReturnVehicleModelName(CarSellData[GetCarBuy[playerid]][carsellModel]), CarSellData[GetCarBuy[playerid]][carsellModel], CarSellData[GetCarBuy[playerid]][carsellPrice]);
    Dialog_ShowEasy(playerid, BuyCar, DIALOG_STYLE_MSGBOX, "ซื้อยานพาหนะ", string, "ซื้อ", "ยกเลิก");
    return 1;
}

Dialog:BuyCar(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(CarSellData[GetCarBuy[playerid]][carsellPriceType] == 1){
            if(GetMoney(playerid) < CarSellData[GetCarBuy[playerid]][carsellPrice])
                return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะซื้อยานพาหนะคันนี้");
        }
        else if(CarSellData[GetCarBuy[playerid]][carsellPriceType] == 2){
            if(AccountData[playerid][uWallet] < CarSellData[GetCarBuy[playerid]][carsellPrice])
                return ErrorMsg(playerid, "คุณมี Wallet ไม่พอที่จะซื้อยานพาหนะคันนี้");
        }

        new
            Float:x,
            Float:y,
            Float:z,
            Float:angle,
            id = -1;

        new world, int;

        int = GetPlayerInterior(playerid);
        world = GetPlayerVirtualWorld(playerid);

        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, angle);

        id = Car_Create(PlayerData[playerid][pID], CarSellData[GetCarBuy[playerid]][carsellModel], x, y + 2, z + 1, angle, random(127), random(127));

        if (id == -1)
            return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");

        LinkVehicleToInterior(id, int);
        SetVehicleVirtualWorld(id, world);

        if(CarSellData[GetCarBuy[playerid]][carsellPriceType] == 1){
            GiveMoney(playerid, -CarSellData[GetCarBuy[playerid]][carsellPrice], "buy vehicle");
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ซื้อยานพาหนะ %s(%d) ในราคา %s เรียบร้อยแล้ว [กด H > เช็คยานพาหนะส่วนตัว เพื่อตรวจสอบ]", ReturnVehicleModelName(CarSellData[GetCarBuy[playerid]][carsellModel]), CarSellData[GetCarBuy[playerid]][carsellModel], FormatNumber(CarSellData[GetCarBuy[playerid]][carsellPrice]));
        }
        else if(CarSellData[GetCarBuy[playerid]][carsellPriceType] == 2){
            AccountData[playerid][uWallet] -= CarSellData[GetCarBuy[playerid]][carsellPrice];
            UpdatePlayerWallet(playerid);
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ซื้อยานพาหนะ %s(%d) ในราคา %d Wallet เรียบร้อยแล้ว [กด H > เช็คยานพาหนะส่วนตัว เพื่อตรวจสอบ]", ReturnVehicleModelName(CarSellData[GetCarBuy[playerid]][carsellModel]), CarSellData[GetCarBuy[playerid]][carsellModel], CarSellData[GetCarBuy[playerid]][carsellPrice]);
        }
    }
    return 1;
}

EditCarSell(playerid){
    new carsellid = GetPVarInt(playerid, "carsellID");
    new stringmember[64];
    new stringpricetype[32];
    new caption[128], dialog_str[1024];
    new stringtype[24];
    EditCarIDSell[playerid] = carsellid;

    if(CarSellData[carsellid][carsellVipLevel] == 0)
        stringmember = "Regular Member";
    else if(CarSellData[carsellid][carsellVipLevel] == 1)
        stringmember = "Bronze Member";
    else if(CarSellData[carsellid][carsellVipLevel] == 2)
        stringmember = "Silver Member";
    else if(CarSellData[carsellid][carsellVipLevel] == 3)
        stringmember = "Gold Member";

    if(CarSellData[carsellid][carsellType] == 0)
        stringtype = "รถ";
    else if(CarSellData[carsellid][carsellType] == 1)
        stringtype = "เรือ";

    if(CarSellData[carsellid][carsellPriceType] == 1){
        stringpricetype = "เงินเขียว";
    }
        
    else if(CarSellData[carsellid][carsellPriceType] == 2){
        stringpricetype = "True Wallet";
    }

    format(caption, sizeof(caption), "แก้ไขยานพาหนะไอดี: %s(%d)", ReturnVehicleModelName(CarSellData[carsellid][carsellModel]), carsellid);
    format(dialog_str, sizeof dialog_str, "โมเดลยานพาหนะ\t%s\n", ReturnVehicleModelName(CarSellData[carsellid][carsellModel]));
    format(dialog_str, sizeof dialog_str, "%sค่าเงิน\t%s\n", dialog_str, stringpricetype);
    if(CarSellData[carsellid][carsellPriceType] == 1)
        format(dialog_str, sizeof dialog_str, "%sราคา\t%s\n", dialog_str, FormatNumber(CarSellData[carsellid][carsellPrice]));
    else if(CarSellData[carsellid][carsellPriceType] == 2)
        format(dialog_str, sizeof dialog_str, "%sราคา\t%d Wallet\n", dialog_str, CarSellData[carsellid][carsellPrice]);
    format(dialog_str, sizeof dialog_str, "%sระดับ VIP\t%s\n", dialog_str, stringmember);
    format(dialog_str, sizeof dialog_str, "%sตัวเลือก\t%s\n", dialog_str, stringtype);
    Dialog_ShowEasy(playerid, EditCarSellID, DIALOG_STYLE_TABLIST, caption, dialog_str, "เลือก", "กลับ");
    return 1;
}

Dialog:EditCarSellID(playerid, response, listitem, inputtext[]){
    if(!response)
        return ViewCarSell(playerid, GetTypeCarsells[playerid]);

    new string[128];
    if(response){
        if(listitem == 0){
            format(string, sizeof(string), "โมเดลยานพาหนะ: %s", ReturnVehicleModelName(CarSellData[EditCarIDSell[playerid]][carsellModel]));
            Dialog_ShowEasy(playerid, CarSell_EditModel, DIALOG_STYLE_INPUT, "ตั้งค่า Model ยานพาหนะ", string, "เปลี่ยน", "กลับ");
        }
        if(listitem == 1){
            new stringpricetype[32];
            if(CarSellData[EditCarIDSell[playerid]][carsellPriceType] == 1)
                stringpricetype = "เงินเขียว";
            else if(CarSellData[EditCarIDSell[playerid]][carsellPriceType] == 2)
                stringpricetype = "True Wallet";
            format(string, sizeof(string), "ค่าเงิน: %s\n[1]: เงินเขียว, [2]: True Wallet", stringpricetype);
            Dialog_ShowEasy(playerid, CarSell_EditPriceType, DIALOG_STYLE_INPUT, "ตั้งค่า ค่าเงิน ยานพาหนะ", string, "เปลี่ยน", "กลับ");
        }
        if(listitem == 2){
            format(string, sizeof(string), "ราคา: %s", FormatNumber(CarSellData[EditCarIDSell[playerid]][carsellPrice]));
            Dialog_ShowEasy(playerid, CarSell_EditPrice, DIALOG_STYLE_INPUT, "ตั้งค่า ราคา ยานพาหนะ", string, "เปลี่ยน", "กลับ");
        }
        if(listitem == 3){
            new stringmember[64];
            if(CarSellData[EditCarIDSell[playerid]][carsellVipLevel] == 0)
                stringmember = "Regular Member";
            else if(CarSellData[EditCarIDSell[playerid]][carsellVipLevel] == 1)
                stringmember = "Bronze Member";
            else if(CarSellData[EditCarIDSell[playerid]][carsellVipLevel] == 2)
                stringmember = "Silver Member";
            else if(CarSellData[EditCarIDSell[playerid]][carsellVipLevel] == 3)
                stringmember = "Gold Member";

            format(string, sizeof(string), "ระดับ VIP: %s", stringmember);
            Dialog_ShowEasy(playerid, CarSell_EditVipLevel, DIALOG_STYLE_INPUT, "ตั้งค่า ระดับ VIP ยานพาหนะ", string, "เปลี่ยน", "กลับ");
        }
        if(listitem == 4){
            new stringtype[24];
            if(CarSellData[EditCarIDSell[playerid]][carsellType] == 0)
                stringtype = "รถ";
            else if(CarSellData[EditCarIDSell[playerid]][carsellType] == 1)
                stringtype = "เรือ";

            format(string, sizeof(string), "ตัวเลือก: %s", stringtype);
            Dialog_ShowEasy(playerid, CarSell_EditType, DIALOG_STYLE_INPUT, "ตั้งค่า ตัวเลือก", string, "เปลี่ยน", "กลับ");
        }
    }
    return 1;
}

Dialog:CarSell_EditModel(playerid, response, listitem, inputtext[]){
    if(response){
        new string[128];

        if ((inputtext[0] = GetVehicleModelByName(inputtext)) == 0){
            format(string, sizeof(string), "* ไอดีรุ่นยานพาหนะไม่ถูกต้อง *\nโมเดลยานพาหนะ: %s", ReturnVehicleModelName(CarSellData[EditCarIDSell[playerid]][carsellModel]));
            Dialog_ShowEasy(playerid, CarSell_EditModel, DIALOG_STYLE_INPUT, "ตั้งค่า Model ยานพาหนะ", string, "เปลี่ยน", "กลับ");
            return 1;
        }

        CarSellData[EditCarIDSell[playerid]][carsellModel] = inputtext[0];
        format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ Model ของยานพาหนะขายไอดี: %d เป็น Model: %d", ReturnRoleplayName(playerid), EditCarIDSell[playerid], inputtext[0]);
        SendAdminsMessage(1, COLOR_GRAY, string);
        CarSell_Save(EditCarIDSell[playerid]);
    }
    return ViewCarSell(playerid, GetTypeCarsells[playerid]);
}

Dialog:CarSell_EditPriceType(playerid, response, listitem, inputtext[]){
    if(response){
        new string[128];

        new type = strval(inputtext);

        new stringpricetype[32];
        if(CarSellData[EditCarIDSell[playerid]][carsellPriceType] == 1)
            stringpricetype = "เงินเขียว";
        else if(CarSellData[EditCarIDSell[playerid]][carsellPriceType] == 2)
            stringpricetype = "True Wallet";

        if (type < 1 || type > 2){
            format(string, sizeof(string), "* คุณต้องกรอก 1 กับ 2 เท่านั้น *\nค่าเงิน: %s\n[1]: เงินเขียว, [2]: True Wallet", stringpricetype);
            Dialog_ShowEasy(playerid, CarSell_EditPriceType, DIALOG_STYLE_INPUT, "ตั้งค่า ราคา ยานพาหนะ", string, "เปลี่ยน", "กลับ");
            return 1;
        }

        CarSellData[EditCarIDSell[playerid]][carsellPriceType] = type;
        format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ ค่าเงิน ของยานพาหนะขายไอดี: %d เป็น ราคา: %d", ReturnRoleplayName(playerid), EditCarIDSell[playerid], type);
        SendAdminsMessage(1, COLOR_GRAY, string);
        CarSell_Save(EditCarIDSell[playerid]);
    }
    return ViewCarSell(playerid, GetTypeCarsells[playerid]);
}

Dialog:CarSell_EditPrice(playerid, response, listitem, inputtext[]){
    if(response){
        new string[128];
        new price = strval(inputtext);

        if (price <= 0){
            format(string, sizeof(string), "* คุณต้องกรอกราคามากกว่า 0 *\nราคา: %s", FormatNumber(CarSellData[EditCarIDSell[playerid]][carsellPrice]));
            Dialog_ShowEasy(playerid, CarSell_EditPrice, DIALOG_STYLE_INPUT, "ตั้งค่า ราคา ยานพาหนะ", string, "เปลี่ยน", "กลับ");
            return 1;
        }

        CarSellData[EditCarIDSell[playerid]][carsellPrice] = price;
        if(CarSellData[EditCarIDSell[playerid]][carsellPriceType] == 1)
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ ราคา ของยานพาหนะขายไอดี: %d เป็น ราคา: %s", ReturnRoleplayName(playerid), EditCarIDSell[playerid], FormatNumber(price));
        else if(CarSellData[EditCarIDSell[playerid]][carsellPriceType] == 2)
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ ราคา ของยานพาหนะขายไอดี: %d เป็น ราคา: %d Wallet", ReturnRoleplayName(playerid), EditCarIDSell[playerid], price);
        SendAdminsMessage(1, COLOR_GRAY, string);
        CarSell_Save(EditCarIDSell[playerid]);
    }
    return ViewCarSell(playerid, GetTypeCarsells[playerid]);
}

Dialog:CarSell_EditVipLevel(playerid, response, listitem, inputtext[]){
    if(response){
        new string[128];
        new viplevel = strval(inputtext);

        new stringmember[64];
        if(CarSellData[EditCarIDSell[playerid]][carsellVipLevel] == 0)
            stringmember = "Regular Member";
        else if(CarSellData[EditCarIDSell[playerid]][carsellVipLevel] == 1)
            stringmember = "Bronze Member";
        else if(CarSellData[EditCarIDSell[playerid]][carsellVipLevel] == 2)
            stringmember = "Silver Member";
        else if(CarSellData[EditCarIDSell[playerid]][carsellVipLevel] == 3)
            stringmember = "Gold Member";

        if (viplevel < 0 || viplevel > 3){
            format(string, sizeof(string), "* VIP มีแค่ 0-3 เท่านั้น *\nระดับ VIP: %s", stringmember);
            Dialog_ShowEasy(playerid, CarSell_EditVipLevel, DIALOG_STYLE_INPUT, "ตั้งค่า ระดับ VIP ยานพาหนะ", string, "เปลี่ยน", "กลับ");
            return 1;
        }

        CarSellData[EditCarIDSell[playerid]][carsellVipLevel] = viplevel;
        format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ ระดับ VIP ของยานพาหนะขายไอดี: %d เป็น ราคา: %d", ReturnRoleplayName(playerid), EditCarIDSell[playerid], viplevel);
        SendAdminsMessage(1, COLOR_GRAY, string);
        CarSell_Save(EditCarIDSell[playerid]);
    }
    return ViewCarSell(playerid, GetTypeCarsells[playerid]);
}

Dialog:CarSell_EditType(playerid, response, listitem, inputtext[]){
    if(response){
        new string[128];
        new type = strval(inputtext);

        new stringtype[24];
        if(CarSellData[EditCarIDSell[playerid]][carsellType] == 0)
            stringtype = "รถ";
        else if(CarSellData[EditCarIDSell[playerid]][carsellType] == 1)
            stringtype = "เรือ";

        if (type < 0 || type > 1){
            format(string, sizeof(string), "* Type มีแค่ 0-1 เท่านั้น *\nตัวเลือก: %s", stringtype);
            Dialog_ShowEasy(playerid, CarSell_EditType, DIALOG_STYLE_INPUT, "ตั้งค่า ตัวเลือก", string, "เปลี่ยน", "กลับ");
            return 1;
        }

        CarSellData[EditCarIDSell[playerid]][carsellType] = type;
        format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับ ตัวเลือก ของยานพาหนะขายไอดี: %d เป็น ราคา: %d", ReturnRoleplayName(playerid), EditCarIDSell[playerid], type);
        SendAdminsMessage(1, COLOR_GRAY, string);
        CarSell_Save(EditCarIDSell[playerid]);
    }
    return ViewCarSell(playerid, GetTypeCarsells[playerid]);
}

Dialog:ScrapVeh(playerid, response, listitem, inputtext[]){
	if(!response) return 1;
	if(response){
		new getindex = -1;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
            new vehicleid = GetPlayerVehicleID(playerid);
            new carid = Car_GetID(vehicleid);
			if(carid != -1){
				if(Car_IsOwner(playerid, carid)){
					for(new i=0; i<MAX_CARSELL; i++){
						if(CarSellData[i][carsellExists]){
							if(CarData[carid][carModel] == CarSellData[i][carsellModel]){
								getindex = i;
							}
						}
					}
					if(getindex != -1){
						if(CarSellData[getindex][carsellPriceType] == 1){
							new price = CarSellData[getindex][carsellPrice] / 2;
							GiveMoney(playerid, price, "scrap vehicle");
							SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้รับเงินคืนจำนวน %s จากการทำลายยานพาหนะ", FormatNumber(price));
						}
						else if(CarSellData[getindex][carsellPriceType] == 2){
							new price = CarSellData[getindex][carsellPrice] / 2;
							AccountData[playerid][uWallet] += price;
                            UpdatePlayerWallet(playerid);
							SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้รับ Wallet คืนจำนวน %s Wallet จากการทำลายยานพาหนะ", FormatNumberNotMoney(price));
						}
					} 
					
					SendClientMessageEx(playerid, COLOR_RED, "คุณได้ทำลายยานพาหนะ %s ของคุณแล้ว", ReturnVehicleName(CarData[carid][carVehicle]));
                    Log_Write("logs/setmoney.txt", "[%s] %s ScrapVeh %s", ReturnDate(), ReturnRoleplayName(playerid), ReturnVehicleName(CarData[carid][carVehicle]));
					Car_Delete(carid);
				}
			}
		}
		
	}
	return 1;
}