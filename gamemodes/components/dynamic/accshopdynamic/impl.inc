#if defined _inc_impl
	#undef _inc_impl
#endif

forward AccShop_Load();
public AccShop_Load()
{
    new
	    rows;

    cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if (i < MAX_ACSHOP)
	{
	    AccDataShop[i][accShopEx] = true;
    	cache_get_value_name_int(i, "accShopID", AccDataShop[i][accShopID]);

    	cache_get_value_name_float(i, "accShopPosX", AccDataShop[i][accShopPos][0]);
     	cache_get_value_name_float(i, "accShopPosY", AccDataShop[i][accShopPos][1]);
     	cache_get_value_name_float(i, "accShopPosZ", AccDataShop[i][accShopPos][2]);
     	cache_get_value_name_int(i, "accShopInt", AccDataShop[i][accShopInt]);
     	cache_get_value_name_int(i, "accShopWorld", AccDataShop[i][accShopWorld]);

	    AccShop_Refresh(i);

	    AccShopCount++;
	}
	printf("(( [MYSQL]: Load %d AccShops Successfully ))", AccShopCount);
	return 1;
}

#define MAX_ACC (100)
enum hatitemData{
    hatitemID,
    hatitemEx,
    hatitemModel,
    hatitemName[32],
    hatitemPrice,
	hatShow
};
new HatDataItem[MAX_ACC][hatitemData], count_hatitem;

enum glassesitemData{
    glassesitemID,
    glassesitemEx,
    glassesitemModel,
    glassesitemName[32],
    glassesitemPrice,
	glassesShow
};
new GlassesDataItem[MAX_ACC][glassesitemData], count_glassesitem;

enum bodyitemData{
    bodyitemID,
    bodyitemEx,
    bodyitemModel,
    bodyitemName[32],
    bodyitemPrice,
	bodyShow
};
new BodyDataItem[MAX_ACC][bodyitemData], count_bodyitem;

enum handsitemData{
    handsitemID,
    handsitemEx,
    handsitemModel,
    handsitemName[32],
    handsitemPrice,
	handsShow
};
new HandsDataItem[MAX_ACC][handsitemData], count_handsitem;

forward HatItem_Load();
public HatItem_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_ACC)
	{
	    HatDataItem[i][hatitemEx] = true;

	    cache_get_value_name_int(i, "hatitemID", HatDataItem[i][hatitemID]);
        cache_get_value_name(i, "hatitemName", HatDataItem[i][hatitemName], 32);
	    cache_get_value_name_int(i, "hatitemModel", HatDataItem[i][hatitemModel]);
        cache_get_value_name_int(i, "hatitemPrice", HatDataItem[i][hatitemPrice]);
		cache_get_value_name_int(i, "hatShow", HatDataItem[i][hatShow]);

        count_hatitem++;

	}
	printf("(( [MYSQL]: Load %d HatAccItems Successfully ))", count_hatitem);
	return 1;
}

forward GlassesItem_Load();
public GlassesItem_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_ACC)
	{
	    GlassesDataItem[i][glassesitemEx] = true;

	    cache_get_value_name_int(i, "glassesitemID", GlassesDataItem[i][glassesitemID]);
        cache_get_value_name(i, "glassesitemName", GlassesDataItem[i][glassesitemName], 32);
	    cache_get_value_name_int(i, "glassesitemModel", GlassesDataItem[i][glassesitemModel]);
        cache_get_value_name_int(i, "glassesitemPrice", GlassesDataItem[i][glassesitemPrice]);
		cache_get_value_name_int(i, "glassesShow", GlassesDataItem[i][glassesShow]);

        count_glassesitem++;

	}
	printf("(( [MYSQL]: Load %d GlassesAccItems Successfully ))", count_glassesitem);
	return 1;
}

forward BodyItem_Load();
public BodyItem_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_ACC)
	{
	    BodyDataItem[i][bodyitemEx] = true;

	    cache_get_value_name_int(i, "bodyitemID", BodyDataItem[i][bodyitemID]);
        cache_get_value_name(i, "bodyitemName", BodyDataItem[i][bodyitemName], 32);
	    cache_get_value_name_int(i, "bodyitemModel", BodyDataItem[i][bodyitemModel]);
        cache_get_value_name_int(i, "bodyitemPrice", BodyDataItem[i][bodyitemPrice]);
		cache_get_value_name_int(i, "bodyShow", BodyDataItem[i][bodyShow]);

        count_bodyitem++;

	}
	printf("(( [MYSQL]: Load %d BodyAccItems Successfully ))", count_bodyitem);
	return 1;
}

forward HandsItem_Load();
public HandsItem_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_ACC)
	{
	    HandsDataItem[i][handsitemEx] = true;

	    cache_get_value_name_int(i, "handsitemID", HandsDataItem[i][handsitemID]);
        cache_get_value_name(i, "handsitemName", HandsDataItem[i][handsitemName], 32);
	    cache_get_value_name_int(i, "handsitemModel", HandsDataItem[i][handsitemModel]);
        cache_get_value_name_int(i, "handsitemPrice", HandsDataItem[i][handsitemPrice]);
		cache_get_value_name_int(i, "handsShow", HandsDataItem[i][handsShow]);

        count_handsitem++;

	}
	printf("(( [MYSQL]: Load %d HandsAccItems Successfully ))", count_handsitem);
	return 1;
}

CMD:reloadacc(playerid, params[]){
    if(PlayerData[playerid][pAdmin] >= 1338){

        for(new i=0; i<MAX_ACC; i++){
            if(HatDataItem[i][hatitemEx]){
                HatDataItem[i][hatitemEx] = false;
                HatDataItem[i][hatitemModel] = 0;
                HatDataItem[i][hatitemPrice] = 0;
				HatDataItem[i][hatShow] = 0;
                format(HatDataItem[i][hatitemName], 32, "NULL");
            }

			if(GlassesDataItem[i][glassesitemEx]){
                GlassesDataItem[i][glassesitemEx] = false;
                GlassesDataItem[i][glassesitemModel] = 0;
                GlassesDataItem[i][glassesitemPrice] = 0;
				GlassesDataItem[i][glassesShow] = 0;
                format(GlassesDataItem[i][glassesitemName], 32, "NULL");
            }

			if(BodyDataItem[i][bodyitemEx]){
                BodyDataItem[i][bodyitemEx] = false;
                BodyDataItem[i][bodyitemModel] = 0;
                BodyDataItem[i][bodyitemPrice] = 0;
				BodyDataItem[i][bodyShow] = 0;
                format(BodyDataItem[i][bodyitemName], 32, "NULL");
            }

			if(HandsDataItem[i][handsitemEx]){
                HandsDataItem[i][handsitemEx] = false;
                HandsDataItem[i][handsitemModel] = 0;
                HandsDataItem[i][handsitemPrice] = 0;
				HandsDataItem[i][handsShow] = 0;
                format(HandsDataItem[i][handsitemName], 32, "NULL");
            }
        }

		count_hatitem = 0;
		count_glassesitem = 0;
		count_bodyitem = 0;
		count_handsitem = 0;
        mysql_tquery(dbCon, "SELECT * FROM `hatitems`", "HatItem_Load", "");
		mysql_tquery(dbCon, "SELECT * FROM `glassesitems`", "GlassesItem_Load", "");
		mysql_tquery(dbCon, "SELECT * FROM `bodyitems`", "BodyItem_Load", "");
		mysql_tquery(dbCon, "SELECT * FROM `handsitems`", "HandsItem_Load", "");
        SendClientMessage(playerid, COLOR_YELLOW, "คุณได้ทำการโหลดเครื่องกายเรียบร้อยแล้ว");
    }
    return 1;
}

Dialog:AccessoryShop(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            ShowBuyHead(playerid);
        }
        if(listitem == 1){
            ShowBuyGlasses(playerid);
        }
        if(listitem == 2){
            ShowBuyBody(playerid);
        }
        if(listitem == 3){
            ShowBuyHands(playerid);
        }
    }
    return 1;
}

ShowBuyHead(playerid){

	static
	    items[MAX_ACC],
		price[MAX_ACC];

    for (new i = 0; i < MAX_ACC; i++){
 		if (HatDataItem[i][hatitemEx] && HatDataItem[i][hatShow] == 1){
   			items[i] = HatDataItem[i][hatitemModel];
			price[i] = HatDataItem[i][hatitemPrice];
		}
		else {
		    items[i] = -1;
			price[i] = -1;
		}
	}
	ShowModelSelectionMenu(playerid, "Hat", MODEL_BUY_HAT, items, sizeof(items), -10.000000, 0.000000, -20.000000, 1.0, -1, true, price);
	return 1;
}

ShowBuyGlasses(playerid){

	static
	    items[MAX_ACC],
		price[MAX_ACC];

    for (new i = 0; i < MAX_ACC; i++){
 		if (GlassesDataItem[i][glassesitemEx] && GlassesDataItem[i][glassesShow] == 1){
   			items[i] = GlassesDataItem[i][glassesitemModel];
			price[i] = GlassesDataItem[i][glassesitemPrice];
		}
		else {
		    items[i] = -1;
			price[i] = -1;
		}
	}
	ShowModelSelectionMenu(playerid, "Glasses", MODEL_BUY_GLASSES, items, sizeof(items), -10.000000, 0.000000, -20.000000, 1.0, -1, true, price);
	return 1;
}

ShowBuyBody(playerid){

	static
	    items[MAX_ACC],
		price[MAX_ACC];

    for (new i = 0; i < MAX_ACC; i++){
 		if (BodyDataItem[i][bodyitemEx] && BodyDataItem[i][bodyShow] == 1){
   			items[i] = BodyDataItem[i][bodyitemModel];
			price[i] = BodyDataItem[i][bodyitemPrice];
		}
		else {
		    items[i] = -1;
			price[i] = -1;
		}
	}
	ShowModelSelectionMenu(playerid, "Body", MODEL_BUY_BODY, items, sizeof(items), -10.000000, 0.000000, -20.000000, 1.0, -1, true, price);
	return 1;
}

ShowBuyHands(playerid){

	static
	    items[MAX_ACC],
		price[MAX_ACC];

    for (new i = 0; i < MAX_ACC; i++){
 		if (HandsDataItem[i][handsitemEx] && HandsDataItem[i][handsShow] == 1){
   			items[i] = HandsDataItem[i][handsitemModel];
			price[i] = HandsDataItem[i][handsitemPrice];
		}
		else {
		    items[i] = -1;
			price[i] = -1;
		}
	}
	ShowModelSelectionMenu(playerid, "Hands", MODEL_BUY_HANDS, items, sizeof(items), -10.000000, 0.000000, -20.000000, 1.0, -1, true, price);
	return 1;
}

AccShop_Refresh(shopid){
    if(shopid != -1 && AccDataShop[shopid][accShopEx])
	{
		if (IsValidDynamic3DTextLabel(AccDataShop[shopid][accShopText]))
		    DestroyDynamic3DTextLabel(AccDataShop[shopid][accShopText]);

        if(IsValidDynamicCP(AccDataShop[shopid][accShopCheckPoint]))
            DestroyDynamicCP(AccDataShop[shopid][accShopCheckPoint]);

		new string[128];
        format(string, sizeof(string), "[ร้านขายเครื่องแต่งกาย]");
        AccDataShop[shopid][accShopText] = CreateDynamic3DTextLabel(string, COLOR_YELLOW, AccDataShop[shopid][accShopPos][0], AccDataShop[shopid][accShopPos][1], AccDataShop[shopid][accShopPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, AccDataShop[shopid][accShopWorld], AccDataShop[shopid][accShopInt]);
        AccDataShop[shopid][accShopCheckPoint] = CreateDynamicCP(AccDataShop[shopid][accShopPos][0], AccDataShop[shopid][accShopPos][1], AccDataShop[shopid][accShopPos][2], 2.0, AccDataShop[shopid][accShopWorld], AccDataShop[shopid][accShopInt], -1, 5.0, -1, 0);
    }
    return 1;
}

AccShop_Save(shopid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `accshops` SET `accShopPosX` = '%.4f', `accShopPosY` = '%.4f', `accShopPosZ` = '%.4f', `accShopInt` = '%d', `accShopWorld` = '%d' WHERE `accShopID` = '%d'",
		AccDataShop[shopid][accShopPos][0],
	    AccDataShop[shopid][accShopPos][1],
	    AccDataShop[shopid][accShopPos][2],
        AccDataShop[shopid][accShopInt],
        AccDataShop[shopid][accShopWorld],
        AccDataShop[shopid][accShopID]
	);
	return mysql_tquery(dbCon, query);
}

AccShop_Create(playerid)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	if (GetPlayerPos(playerid, x, y, z))
	{
		for (new i = 0; i != MAX_ACSHOP; i ++)
		{
	    	if (!AccDataShop[i][accShopEx])
	    	{
	        	AccDataShop[i][accShopEx] = true;

				AccDataShop[i][accShopPos][0] = x;
	        	AccDataShop[i][accShopPos][1] = y;
	        	AccDataShop[i][accShopPos][2] = z;

	        	AccDataShop[i][accShopInt] = GetPlayerInterior(playerid);
	        	AccDataShop[i][accShopWorld] = GetPlayerVirtualWorld(playerid);

	        	AccShop_Refresh(i);
	        	mysql_tquery(dbCon, "INSERT INTO `accshops` (`accShopInt`) VALUES(0)", "OnAcShopCreated", "d", i);

	        	return i;
	        }
	    }
	}
	return -1;
}

forward OnAcShopCreated(shopid);
public OnAcShopCreated(shopid)
{
	if (shopid == -1 || !AccDataShop[shopid][accShopEx])
	    return 0;

	AccDataShop[shopid][accShopID] = cache_insert_id();
	AccShop_Save(shopid);

	return 1;
}

AccShop_Nearest(playerid)
{
    for (new i = 0; i != MAX_ACSHOP; i ++) if (AccDataShop[i][accShopEx] && IsPlayerInRangeOfPoint(playerid, 2.0, AccDataShop[i][accShopPos][0], AccDataShop[i][accShopPos][1], AccDataShop[i][accShopPos][2]))
	{
		if (GetPlayerInterior(playerid) == AccDataShop[i][accShopInt] && GetPlayerVirtualWorld(playerid) == AccDataShop[i][accShopWorld])
			return i;
	}
	return -1;
}

AccShop_Delete(shopid)
{
	if (shopid != -1 && AccDataShop[shopid][accShopEx])
	{
	    new
	        string[64];

        AccShopCount--;

		format(string, sizeof(string), "DELETE FROM `accShops` WHERE `accShopID` = '%d' LIMIT1", AccDataShop[shopid][accShopID]);
		mysql_tquery(dbCon, string);

        if (IsValidDynamic3DTextLabel(AccDataShop[shopid][accShopText]))
		    DestroyDynamic3DTextLabel(AccDataShop[shopid][accShopText]);

        if(IsValidDynamicCP(AccDataShop[shopid][accShopCheckPoint]))
            DestroyDynamicCP(AccDataShop[shopid][accShopCheckPoint]);

		AccDataShop[shopid][accShopEx] = false;
	    AccDataShop[shopid][accShopID] = 0;
	}
	return 1;
}

CMD:accshopcmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[ACCSHOPCMDS]: /makeaccshop, /removeaccshop, /editaccshop, /gotoaccshop, /refreshaccshop, /reloadacc");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

CMD:gotoaccshop(playerid, params[])
{
	new
		id;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SendClientMessage(playerid, -1, "/gotoaccshop [acc ID]");

	if ((id < 0 || id >= MAX_ACSHOP) || !AccDataShop[id][accShopEx])
		return SendClientMessage(playerid, -1, "คุณระบุ Acc ID ไม่ถูกต้อง");

	SetPlayerPosEx(playerid, AccDataShop[id][accShopPos][0], AccDataShop[id][accShopPos][1], AccDataShop[id][accShopPos][2], AccDataShop[id][accShopInt], AccDataShop[id][accShopWorld]);
	SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ Acc ID: %d", id);
	return 1;
}

CMD:makeaccshop(playerid, params[])
{
	new
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	new id = AccShop_Create(playerid);

	if (id == -1)
		return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้ AccShop เกินขีดจำกัดแล้ว");

	format(string, sizeof(string), "คุณได้ประสบความสำเร็จในการสร้าง AccShop ไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:editaccshop(playerid, params[])
{
	new
		id,
		type[24],
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
	{
		SystemMsg(playerid, "/editsafezone [id] [name]");
		SystemMsg(playerid, "[NAMES]:{FFFFFF} location");
		return 1;
	}

	if ((id < 0 || id >= MAX_ACSHOP) || !AccDataShop[id][accShopEx])
		return SendClientMessage(playerid, -1, "คุณระบุ Acc ID ไม่ถูกต้อง");

	if (!strcmp(type, "location", true))
	{
		GetPlayerPos(playerid, AccDataShop[id][accShopPos][0], AccDataShop[id][accShopPos][1], AccDataShop[id][accShopPos][2]);

		AccDataShop[id][accShopInt] = GetPlayerInterior(playerid);
		AccDataShop[id][accShopWorld] = GetPlayerVirtualWorld(playerid);

		AccShop_Refresh(id);
		AccShop_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่งของ AccShop ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	return 1;
}

CMD:removeaccshop(playerid, params[])
{
	new
		id = 0,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/removeaccshop [acc id]");

	if ((id < 0 || id >= MAX_ACSHOP) || !AccDataShop[id][accShopEx])
		return SendClientMessage(playerid, -1, "คุณระบุ Acc ID ไม่ถูกต้อง");

	AccShop_Delete(id);
	format(string, sizeof(string), "คุณได้ประสบความสำเร็จในการทำลาย AccShop ไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:refreshaccshop(playerid, params[])
{
	new
		id = 0,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/refreshaccshop [acc id]");

	if ((id < 0 || id >= MAX_ACSHOP) || !AccDataShop[id][accShopEx])
		return SendClientMessage(playerid, -1, "คุณระบุ Acc ID ไม่ถูกต้อง");

	AccShop_Refresh(id);
	format(string, sizeof(string), "คุณได้ประสบความสำเร็จในรีเฟรช AccShop ไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}