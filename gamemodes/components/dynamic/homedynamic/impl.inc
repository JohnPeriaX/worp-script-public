#if defined _inc_impl
	#undef _inc_impl
#endif

Home_Create(playerid, const name[], price){
    new 
        Float:x, Float:y, Float:z, Float:angle;

    if(GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle)){
        for(new i=0; i<MAX_HOME; i++) if(!HomeData[i][homeEx]){
            HomeData[i][homeEx] = true;
            HomeData[i][homeOwner] = 0;
            format(HomeData[i][homeName], 32, name);
            HomeData[i][homePrice] = price;

            HomeData[i][homeEnterPos][0] = x;
            HomeData[i][homeEnterPos][1] = y;
            HomeData[i][homeEnterPos][2] = z;
            HomeData[i][homeEnterPos][3] = angle;
            HomeData[i][homeEnterInt] = GetPlayerInterior(playerid);
            HomeData[i][homeEnterWorld] = GetPlayerVirtualWorld(playerid);

            HomeData[i][homeExitPos][0] = 2269.8772;
            HomeData[i][homeExitPos][1] = -1210.3240;
            HomeData[i][homeExitPos][2] = 1047.5625;
            HomeData[i][homeExitPos][3] = 90.0000;
            HomeData[i][homeExitInt] = 10;
            
            HomeData[i][homeBuild] = 0;
            HomeData[i][homeLocked] = 0;
            HomeData[i][homeMaxItem] = 36;
            HomeData[i][homeItemAmount] = 50;
            HomeData[i][homeRentAmount] = 0;
            HomeData[i][homeNewInv] = 1;
            HomeData[i][homeResetInv] = 1;

            for(new j=0; j<MAX_HOME_INV; j++){
                HouseStorage[i][j][hItemExists] = false;
                HouseStorage[i][j][hItemID] = 0;
                HouseStorage[i][j][hItemModel] = MODEL_NULL;
                HouseStorage[i][j][hItemQuantity] = 0;
                HouseStorage[i][j][hItemLevel] = 0;
                HouseStorage[i][j][hItemAmmo] = 0;
                HouseStorage[i][j][hItemSlot] = -1;
                format(HouseStorage[i][j][hItemName], 64, "NULL");
                if(j >= 107) break;
            }

            Home_Refresh(i);
            mysql_tquery(dbCon, "INSERT INTO `homes` (`homeOwner`) VALUES(0)", "OnHomeCreated", "d", i);
            return i;
        }
    }
    return -1;
}

forward OnHomeCreated(homeid);
public OnHomeCreated(homeid){
	if (homeid == -1 || !HomeData[homeid][homeEx])
	    return 0;

	HomeData[homeid][homeID] = cache_insert_id();
	Home_Save(homeid);

	return 1;
}

Home_Refresh(homeid){
    if(homeid != -1 && HomeData[homeid][homeEx]){
        if (IsValidDynamic3DTextLabel(HomeData[homeid][homeText3D]) && HomeData[homeid][homeText3D])
		    DestroyDynamic3DTextLabel(HomeData[homeid][homeText3D]);

		if (IsValidDynamicPickup(HomeData[homeid][homePickup]) && HomeData[homeid][homePickup])
		    DestroyDynamicPickup(HomeData[homeid][homePickup]);

        new string[128];

        if(HomeData[homeid][homeOwner] == 0){
            format(string, sizeof(string), "[%s]\n%s\n( ยังไม่มีเจ้าของ )", FormatNumber(HomeData[homeid][homePrice]), HomeData[homeid][homeName]);
            HomeData[homeid][homeText3D] = CreateDynamic3DTextLabel(string, COLOR_WHITE, HomeData[homeid][homeEnterPos][0], HomeData[homeid][homeEnterPos][1], HomeData[homeid][homeEnterPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, HomeData[homeid][homeEnterWorld], HomeData[homeid][homeEnterInt]);
            HomeData[homeid][homePickup] = CreateDynamicPickup(1273, 23, HomeData[homeid][homeEnterPos][0], HomeData[homeid][homeEnterPos][1], HomeData[homeid][homeEnterPos][2], HomeData[homeid][homeEnterWorld], HomeData[homeid][homeEnterInt]);
        }
        else if(HomeData[homeid][homeOwner] != 0){
            if(HomeData[homeid][homeBuild] == 0){
                format(string, sizeof(string), "[%s]\n( * อยู่ระหว่างการก่อสร้าง * )\n( เจ้าของ: %s )", HomeData[homeid][homeName], HomeData[homeid][homeOwnerName]);
                HomeData[homeid][homeText3D] = CreateDynamic3DTextLabel(string, COLOR_WHITE, HomeData[homeid][homeEnterPos][0], HomeData[homeid][homeEnterPos][1], HomeData[homeid][homeEnterPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, HomeData[homeid][homeEnterWorld], HomeData[homeid][homeEnterInt]);
                HomeData[homeid][homePickup] = CreateDynamicPickup(19523, 23, HomeData[homeid][homeEnterPos][0], HomeData[homeid][homeEnterPos][1], HomeData[homeid][homeEnterPos][2], HomeData[homeid][homeEnterWorld], HomeData[homeid][homeEnterInt]);
            } 
            else if(HomeData[homeid][homeBuild] == 1){
                format(string, sizeof(string), "[%s]\n( เจ้าของ: %s )", HomeData[homeid][homeName], HomeData[homeid][homeOwnerName]);
                HomeData[homeid][homeText3D] = CreateDynamic3DTextLabel(string, COLOR_WHITE, HomeData[homeid][homeEnterPos][0], HomeData[homeid][homeEnterPos][1], HomeData[homeid][homeEnterPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, HomeData[homeid][homeEnterWorld], HomeData[homeid][homeEnterInt]);
                HomeData[homeid][homePickup] = CreateDynamicPickup(19522, 23, HomeData[homeid][homeEnterPos][0], HomeData[homeid][homeEnterPos][1], HomeData[homeid][homeEnterPos][2], HomeData[homeid][homeEnterWorld], HomeData[homeid][homeEnterInt]);
            }
        }
    }
    return 1;
}

Home_Save(homeid){
    new
	    query[2056];

    mysql_format(dbCon, query, sizeof(query), "UPDATE `homes` SET `homeOwner` = '%d', `homePrice` = '%d', `homeOwnerName` = '%e', `homeName` = '%e', `homeEnterPosX` = '%.4f', `homeEnterPosY` = '%.4f', `homeEnterPosZ` = '%.4f', `homeEnterPosA` = '%.4f', `homeExitPosX` = '%.4f', `homeExitPosY` = '%.4f', `homeExitPosZ` = '%.4f', `homeExitPosA` = '%.4f', `homeExitInt` = '%d', `homeEnterInt` = '%d', `homeEnterWorld` = '%d'",
	    HomeData[homeid][homeOwner],
	    HomeData[homeid][homePrice],
        HomeData[homeid][homeOwnerName],
	    HomeData[homeid][homeName],
	    HomeData[homeid][homeEnterPos][0],
	    HomeData[homeid][homeEnterPos][1],
	    HomeData[homeid][homeEnterPos][2],
	    HomeData[homeid][homeEnterPos][3],
	    HomeData[homeid][homeExitPos][0],
	    HomeData[homeid][homeExitPos][1],
	    HomeData[homeid][homeExitPos][2],
	    HomeData[homeid][homeExitPos][3],
        HomeData[homeid][homeExitInt],
        HomeData[homeid][homeEnterInt],
        HomeData[homeid][homeEnterWorld]
	);
    format(query, sizeof(query), "%s, `homeBuild` = '%d', `homeLocked` = '%d', `homeMaxItem` = '%d', `homeItemAmount` = '%d', `homeRentAmount` = '%d', `homeNewInv` = '%d', `homeResetInv` = '%d' WHERE `homeID` = '%d'",
	    query,
	    HomeData[homeid][homeBuild],
        HomeData[homeid][homeLocked],
        HomeData[homeid][homeMaxItem],
        HomeData[homeid][homeItemAmount],
        HomeData[homeid][homeRentAmount],
        HomeData[homeid][homeNewInv],
        HomeData[homeid][homeResetInv],
        HomeData[homeid][homeID]
	);
    return mysql_tquery(dbCon, query);
}

Home_Delete(homeid){
	if (homeid != -1 && HomeData[homeid][homeEx])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `homes` WHERE `homeID` = '%d' LIMIT 1", HomeData[homeid][homeID]);
		mysql_tquery(dbCon, string);

        format(string, sizeof(string), "DELETE FROM `homestorage` WHERE `ID` = '%d'", HomeData[homeid][homeID]);
        mysql_tquery(dbCon, string);

        if (IsValidDynamic3DTextLabel(HomeData[homeid][homeText3D]))
		    DestroyDynamic3DTextLabel(HomeData[homeid][homeText3D]);

		if (IsValidDynamicPickup(HomeData[homeid][homePickup]))
		    DestroyDynamicPickup(HomeData[homeid][homePickup]);


        for(new j=0; j<MAX_HOME_INV; j++){
            HouseStorage[homeid][j][hItemExists] = false;
            HouseStorage[homeid][j][hItemID] = 0;
            HouseStorage[homeid][j][hItemModel] = MODEL_NULL;
            HouseStorage[homeid][j][hItemQuantity] = 0;
            HouseStorage[homeid][j][hItemLevel] = 0;
            HouseStorage[homeid][j][hItemAmmo] = 0;
            HouseStorage[homeid][j][hItemSlot] = -1;
            format(HouseStorage[homeid][j][hItemName], 64, "NULL");
            if(j >= 107) break;
        }

	    HomeData[homeid][homeEx] = false;
	    HomeData[homeid][homeOwner] = 0;
	    HomeData[homeid][homeID] = 0;
        HomeData[homeid][homeBuild] = 0;
	}
	return 1;
}

forward Home_Load();
public Home_Load()
{
	static
	    rows,
        str[128];

	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if (i < MAX_HOME){
        HomeData[i][homeEx] = true;
        HomeData[i][homeStorageUsing] = false;

        cache_get_value_name_int(i, "homeID", HomeData[i][homeID]);
	 	cache_get_value_name_int(i, "homeOwner", HomeData[i][homeOwner]);
	 	cache_get_value_name_int(i, "homePrice", HomeData[i][homePrice]);

		cache_get_value_name(i, "homeOwnerName", HomeData[i][homeOwnerName], 64);
		cache_get_value_name(i, "homeName", HomeData[i][homeName], 64);

		cache_get_value_name_float(i, "homeEnterPosX", HomeData[i][homeEnterPos][0]);
	 	cache_get_value_name_float(i, "homeEnterPosY", HomeData[i][homeEnterPos][1]);
	 	cache_get_value_name_float(i, "homeEnterPosZ", HomeData[i][homeEnterPos][2]);
	 	cache_get_value_name_float(i, "homeEnterPosA", HomeData[i][homeEnterPos][3]);
	 	cache_get_value_name_float(i, "homeExitPosX", HomeData[i][homeExitPos][0]);
	 	cache_get_value_name_float(i, "homeExitPosY", HomeData[i][homeExitPos][1]);
	 	cache_get_value_name_float(i, "homeExitPosZ", HomeData[i][homeExitPos][2]);
	 	cache_get_value_name_float(i, "homeExitPosA", HomeData[i][homeExitPos][3]);
	 	cache_get_value_name_int(i, "homeExitInt", HomeData[i][homeExitInt]);
	 	cache_get_value_name_int(i, "homeEnterInt", HomeData[i][homeEnterInt]);
	 	cache_get_value_name_int(i, "homeEnterWorld", HomeData[i][homeEnterWorld]);
        cache_get_value_name_int(i, "homeBuild", HomeData[i][homeBuild]);
   		cache_get_value_name_int(i, "homeLocked", HomeData[i][homeLocked]);

        cache_get_value_name_int(i, "homeMaxItem", HomeData[i][homeMaxItem]);
        cache_get_value_name_int(i, "homeItemAmount", HomeData[i][homeItemAmount]);
        cache_get_value_name_int(i, "homeRentAmount", HomeData[i][homeRentAmount]);
        cache_get_value_name_int(i, "homeNewInv", HomeData[i][homeNewInv]);
        cache_get_value_name_int(i, "homeResetInv", HomeData[i][homeResetInv]);

        if(HomeData[i][homeResetInv] == 0){
            if(HomeData[i][homeMaxItem] == 8){
                HomeData[i][homeMaxItem] = 36;
            }

            if(HomeData[i][homeMaxItem] == 16){
                HomeData[i][homeMaxItem] = 36;
            }

            if(HomeData[i][homeMaxItem] == 24){
                HomeData[i][homeMaxItem] = 72;
            }

            if(HomeData[i][homeMaxItem] == 32){
                HomeData[i][homeMaxItem] = 108;
            }
            HomeData[i][homeResetInv] = 1;
        }

		Home_Refresh(i);
		count_home++;
	}
    for (new i = 0; i < MAX_HOME; i ++) if (HomeData[i][homeEx]) {

        for(new j=0; j<MAX_HOME_INV; j++){
            HouseStorage[i][j][hItemExists] = false;
            HouseStorage[i][j][hItemID] = 0;
            HouseStorage[i][j][hItemModel] = MODEL_NULL;
            HouseStorage[i][j][hItemQuantity] = 0;
            HouseStorage[i][j][hItemLevel] = 0;
            HouseStorage[i][j][hItemAmmo] = 0;
            HouseStorage[i][j][hItemSlot] = -1;
            format(HouseStorage[i][j][hItemName], 64, "NULL");
            if(j >= 107) break;
        }

		format(str, sizeof(str), "SELECT * FROM `homestorage` WHERE `ID` = '%d'", HomeData[i][homeID]);
		mysql_tquery(dbCon, str, "OnLoadStorage", "d", i);
	}
	printf("(( [MYSQL]: Load %d Homes Successfully ))", count_home);
	return 1;
}

forward OnLoadStorage(houseid);
public OnLoadStorage(houseid)
{
	new rows;
	cache_get_row_count(rows);
    new string[128];
    new j = 0;
	for (new i = 0; i != rows; i ++) {
		HouseStorage[houseid][i][hItemExists] = true;
        cache_get_value_name_int(i, "itemID", HouseStorage[houseid][i][hItemID]);
        cache_get_value_name(i, "itemName", HouseStorage[houseid][i][hItemName], 64);
        cache_get_value_name_int(i, "itemModel", HouseStorage[houseid][i][hItemModel]);
        cache_get_value_name_int(i, "itemQuantity", HouseStorage[houseid][i][hItemQuantity]);
        cache_get_value_name_int(i, "itemAmmo", HouseStorage[houseid][i][hItemAmmo]);
        cache_get_value_name_int(i, "itemLevel", HouseStorage[houseid][i][hItemLevel]);
        cache_get_value_name_int(i, "itemSlot", HouseStorage[houseid][i][hItemSlot]);
        if(!HomeData[houseid][homeNewInv]){
            if(HouseStorage[houseid][i][hItemSlot] == -1){
                HouseStorage[houseid][i][hItemSlot] = j;
                mysql_format(dbCon, string, sizeof(string), "UPDATE `homestorage` SET `itemSlot` = %d WHERE `ID` = '%d' AND `itemID` = '%d' LIMIT 1", HouseStorage[houseid][i][hItemSlot], HomeData[houseid][homeID], HouseStorage[houseid][i][hItemID]);
                mysql_tquery(dbCon, string);
                j++;
            }
        }
        else{
            if(HouseStorage[houseid][i][hItemSlot] == -1){
                HouseStorage[houseid][i][hItemSlot] = i;
                mysql_format(dbCon, string, sizeof(string), "UPDATE `homestorage` SET `itemSlot` = %d WHERE `ID` = '%d' AND `itemID` = '%d' LIMIT 1", HouseStorage[houseid][i][hItemSlot], HomeData[houseid][homeID], HouseStorage[houseid][i][hItemID]);
                mysql_tquery(dbCon, string);
            }
        }

        if(i >= 107) {
            printf("break");
            break;
        }
	}
    if(!HomeData[houseid][homeNewInv]) {
        HomeData[houseid][homeNewInv] = 1;
        Home_Save(houseid);
    }
    ReloadHomeSlotIndexItem(houseid);
	return 1;
}

//ReloadHomeSlot
ReloadHomeSlotIndexItem(houseid){
    if(houseid != -1){
        printf("[House_Load]: Start Load House Storage ID: %d", houseid);
        new tempI = -1, j = -1, check = true, checkround = -1;
        new itemHaveEx, itemIDEx, itemNameEx[64], itemKeyEx, itemQuantityEx, itemLevelEx, itemAmmoEx, itemSlotEx;
        while(check && checkround < MAX_HOME_INV){
            new x = 0;
            for(new i=0; i<HomeData[houseid][homeMaxItem]; i++) if(i < MAX_HOME_INV){
                if(HouseStorage[houseid][i][hItemModel] == MODEL_NULL) continue;
                if(HouseStorage[houseid][i][hItemSlot] == -1) continue;

                tempI = i;
                j = HouseStorage[houseid][tempI][hItemSlot];
                if(j != -1 && i != j){
                    itemHaveEx = HouseStorage[houseid][j][hItemExists];
                    itemIDEx = HouseStorage[houseid][j][hItemID];
                    format(itemNameEx, 64, HouseStorage[houseid][j][hItemName]);
                    itemKeyEx = HouseStorage[houseid][j][hItemModel];
                    itemQuantityEx = HouseStorage[houseid][j][hItemQuantity];
                    itemLevelEx = HouseStorage[houseid][j][hItemLevel];
                    itemAmmoEx = HouseStorage[houseid][j][hItemAmmo];
                    itemSlotEx = HouseStorage[houseid][j][hItemSlot];

                    HouseStorage[houseid][j][hItemExists] = HouseStorage[houseid][tempI][hItemExists];
                    HouseStorage[houseid][j][hItemID] = HouseStorage[houseid][tempI][hItemID];
                    format(HouseStorage[houseid][j][hItemName], 64, HouseStorage[houseid][tempI][hItemName]);
                    HouseStorage[houseid][j][hItemModel] = HouseStorage[houseid][tempI][hItemModel];
                    HouseStorage[houseid][j][hItemQuantity] = HouseStorage[houseid][tempI][hItemQuantity];
                    HouseStorage[houseid][j][hItemLevel] = HouseStorage[houseid][tempI][hItemLevel];
                    HouseStorage[houseid][j][hItemAmmo] = HouseStorage[houseid][tempI][hItemAmmo];
                    HouseStorage[houseid][j][hItemSlot] = HouseStorage[houseid][tempI][hItemSlot];

                    HouseStorage[houseid][tempI][hItemExists] = itemHaveEx;
                    HouseStorage[houseid][tempI][hItemID] = itemIDEx;
                    format(HouseStorage[houseid][tempI][hItemName], 64, itemNameEx);
                    HouseStorage[houseid][tempI][hItemModel] = itemKeyEx;
                    HouseStorage[houseid][tempI][hItemQuantity] = itemQuantityEx;
                    HouseStorage[houseid][tempI][hItemLevel] = itemLevelEx;
                    HouseStorage[houseid][tempI][hItemAmmo] = itemAmmoEx;
                    HouseStorage[houseid][tempI][hItemSlot] = itemSlotEx;
                    x++;
                }
            }
            checkround++;
            if(checkround >= 107) check = false;

            if(x > 0) check = true;
            else check = false;
        }
        printf("[House_Load]: HouseID: %d Reload Index House Storage Finish", houseid);
    }
    return 1;
}

stock House_GetItemID(homeid, const item[]){
	for (new i = 0; i < MAX_HOME_INV; i ++){
	    if (!HouseStorage[homeid][i][hItemExists]) continue;
		if (!strcmp(HouseStorage[homeid][i][hItemName], item)) {
            if(HouseStorage[homeid][i][hItemQuantity] < HomeData[homeid][homeItemAmount]){
                return i;
            }
            
        }
        if(i >= 107) break;
	}
	return -1;
}

stock House_GetFreeID(homeid){
    if(Home_Items(homeid) >= HomeData[homeid][homeMaxItem]) return -1;

	for (new i = 0; i < MAX_HOME_INV; i ++){
	    if (!HouseStorage[homeid][i][hItemExists]) return i;
        if(i >= 107) break;
	}
	return -1;
}

stock Home_Items(homeid){
    new count;
    for (new i = 0; i != MAX_HOME_INV; i ++) if(HouseStorage[homeid][i][hItemExists]) {
        count++;
        if(i >= 107) break;
	}
	return count;
}

stock HouseItem_Count(homeid, const item[]){
	new itemid = House_GetItemID(homeid, item);

	if (itemid != -1)
	    return HouseStorage[homeid][itemid][hItemQuantity];

	return 0;
}

stock HouseItem_CountEx(homeid, itemid){
	if (itemid != -1) return HouseStorage[homeid][itemid][hItemQuantity];
	return 0;
}

forward OnStorageAdd(homeid, itemid);
public OnStorageAdd(homeid, itemid){
	HouseStorage[homeid][itemid][hItemID] = cache_insert_id();
	return 1;
}

HomePlayerInventory_Count(homeid, const item[]){
    new itemid = House_GetItemID(homeid, item);
    if(itemid != -1) return HouseStorage[homeid][itemid][hItemQuantity];
    return 0;
}

HousePutItem(playerid, homeid, const item[], model, quantity, ammo = 0, level = 0){
    if (homeid == -1 || !HomeData[homeid][homeEx]) return -1;
    new itemid = -1, string[256];
    if(HomePlayerInventory_Count(homeid, item) + quantity > HomeData[homeid][homeItemAmount]){
        if(quantity > HomeData[homeid][homeItemAmount]){
            new newamount = quantity - HomeData[homeid][homeItemAmount];

            new checkitem = House_GetItemID(homeid, item);
            if(checkitem != -1){
                new amountsplit = (quantity + HouseStorage[homeid][checkitem][hItemQuantity]);
                if(amountsplit <= HomeData[homeid][homeItemAmount]){
                    HouseStorage[homeid][checkitem][hItemQuantity] += quantity;
                    format(string, sizeof(string), "UPDATE `homestorage` SET `itemQuantity` = %d WHERE `ID` = '%d' AND `itemID` = '%d' LIMIT 1", HouseStorage[homeid][checkitem][hItemQuantity], HomeData[homeid][homeID], HouseStorage[homeid][checkitem][hItemID]);
                    mysql_tquery(dbCon, string);
                    Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount = %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][checkitem][hItemLevel], HomeData[homeid][homeOwnerName], quantity, HouseStorage[homeid][checkitem][hItemQuantity]);  
                }
                else{
                    new amountnew = (HouseStorage[homeid][checkitem][hItemQuantity] + quantity) - HomeData[homeid][homeItemAmount];
                    HouseStorage[homeid][checkitem][hItemQuantity] = HomeData[homeid][homeItemAmount];
                    format(string, sizeof(string), "UPDATE `homestorage` SET `itemQuantity` = %d WHERE `ID` = '%d' AND `itemID` = '%d' LIMIT 1", HouseStorage[homeid][checkitem][hItemQuantity], HomeData[homeid][homeID], HouseStorage[homeid][checkitem][hItemID]);
                    mysql_tquery(dbCon, string);
                    Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount = %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][checkitem][hItemLevel], HomeData[homeid][homeOwnerName], quantity, HouseStorage[homeid][checkitem][hItemQuantity]);  
                
                    itemid = House_GetFreeID(homeid);
                    if(itemid != -1){
                        printf("Add '%s' amount '%d' To SlotHomeSpecial '%d'", item, amountnew, itemid);
                        HouseStorage[homeid][itemid][hItemExists] = true;
                        HouseStorage[homeid][itemid][hItemModel] = model;
                        HouseStorage[homeid][itemid][hItemQuantity] = amountnew;
                        HouseStorage[homeid][itemid][hItemAmmo] = ammo;
                        HouseStorage[homeid][itemid][hItemLevel] = level;
                        HouseStorage[homeid][itemid][hItemSlot] = itemid;
                        format(HouseStorage[homeid][itemid][hItemName], 64, item);

                        mysql_format(dbCon, string, sizeof(string), "INSERT INTO `homestorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`, `itemAmmo`, `itemLevel`, `itemSlot`) VALUES('%d', '%e', '%d', '%d', '%d', '%d', '%d')", HomeData[homeid][homeID], item, model, amountnew, ammo, level, itemid);
                        mysql_tquery(dbCon, string, "OnStorageAdd", "dd", homeid, itemid);
                        Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount = %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][itemid][hItemLevel], HomeData[homeid][homeOwnerName], amountnew, HouseStorage[homeid][itemid][hItemQuantity]);
                        return itemid;
                    }
                }
            }
            else{
                new itemid1 = -1, itemid2 = -1;
                itemid1 = House_GetFreeID(homeid);
                if(itemid1 != -1) HouseStorage[homeid][itemid1][hItemExists] = true;
                itemid2 = House_GetFreeID(homeid);
                if(itemid1 != -1){
                    printf("Add '%s' amount '%d' To SlotHome '%d'", item, HomeData[homeid][homeItemAmount], itemid1);
                    HouseStorage[homeid][itemid1][hItemModel] = model;
                    HouseStorage[homeid][itemid1][hItemQuantity] = HomeData[homeid][homeItemAmount];
                    HouseStorage[homeid][itemid1][hItemAmmo] = ammo;
                    HouseStorage[homeid][itemid1][hItemLevel] = level;
                    HouseStorage[homeid][itemid1][hItemSlot] = itemid;
                    format(HouseStorage[homeid][itemid1][hItemName], 64, item);

                    mysql_format(dbCon, string, sizeof(string), "INSERT INTO `homestorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`, `itemAmmo`, `itemLevel`, `itemSlot`) VALUES('%d', '%e', '%d', '%d', '%d', '%d', '%d')", HomeData[homeid][homeID], item, model, HomeData[homeid][homeItemAmount], ammo, level, itemid1);
                    mysql_tquery(dbCon, string, "OnStorageAdd", "dd", homeid, itemid1);
                    Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount = %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][itemid1][hItemLevel], HomeData[homeid][homeOwnerName], HomeData[homeid][homeItemAmount], HouseStorage[homeid][itemid1][hItemQuantity]);
                    if(itemid2 == -1) {
                        new additem = PlayerInventory_AddItem(playerid, item, model, quantity-HomeData[homeid][homeItemAmount], ammo, level);
                        format(string, sizeof string, "เนื่องจากบ้านของคุณเต็มแล้วจึงสามารถฝาก %s ได้เพียง %d ชิ้นเท่านั้น", item, HomeData[homeid][homeItemAmount]);
                        if(additem != -1) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "แจ้งเตือน", string, "ตกลง", "");
                        return itemid1;
                    }
                }
                if(itemid2 != -1){
                    printf("Add '%s' amount '%d' To SecondSlotHome '%d'", item, newamount, itemid2);
                    HouseStorage[homeid][itemid2][hItemExists] = true;
                    HouseStorage[homeid][itemid2][hItemModel] = model;
                    HouseStorage[homeid][itemid2][hItemQuantity] = newamount;
                    HouseStorage[homeid][itemid2][hItemAmmo] = ammo;
                    HouseStorage[homeid][itemid2][hItemLevel] = level;
                    HouseStorage[homeid][itemid2][hItemSlot] = itemid2;
                    format(HouseStorage[homeid][itemid2][hItemName], 64, item);

                    mysql_format(dbCon, string, sizeof(string), "INSERT INTO `homestorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`, `itemAmmo`, `itemLevel`, `itemSlot`) VALUES('%d', '%e', '%d', '%d', '%d', '%d', '%d')", HomeData[homeid][homeID], item, model, newamount, ammo, level, itemid2);
                    mysql_tquery(dbCon, string, "OnStorageAdd", "dd", homeid, itemid2);
                    Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount = %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][itemid2][hItemLevel], HomeData[homeid][homeOwnerName], newamount, HouseStorage[homeid][itemid2][hItemQuantity]);
                    return itemid2;
                }
            }
            return -1;
        }
        else{
            new checkitem = House_GetItemID(homeid, item);
            if(checkitem != -1){
                new amountsplit = (quantity + HouseStorage[homeid][checkitem][hItemQuantity]);
                if(amountsplit <= HomeData[homeid][homeItemAmount]){
                    HouseStorage[homeid][checkitem][hItemQuantity] += quantity;
                    format(string, sizeof(string), "UPDATE `homestorage` SET `itemQuantity` = %d WHERE `ID` = '%d' AND `itemID` = '%d' LIMIT 1", HouseStorage[homeid][checkitem][hItemQuantity], HomeData[homeid][homeID], HouseStorage[homeid][checkitem][hItemID]);
                    mysql_tquery(dbCon, string);
                    Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount = %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][checkitem][hItemLevel], HomeData[homeid][homeOwnerName], quantity, HouseStorage[homeid][checkitem][hItemQuantity]);  
                }
                else{
                    new amountnew = (HouseStorage[homeid][checkitem][hItemQuantity] + quantity) - HomeData[homeid][homeItemAmount];
                    HouseStorage[homeid][checkitem][hItemQuantity] = HomeData[homeid][homeItemAmount];
                    format(string, sizeof(string), "UPDATE `homestorage` SET `itemQuantity` = %d WHERE `ID` = '%d' AND `itemID` = '%d' LIMIT 1", HouseStorage[homeid][checkitem][hItemQuantity], HomeData[homeid][homeID], HouseStorage[homeid][checkitem][hItemID]);
                    mysql_tquery(dbCon, string);
                    Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount = %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][checkitem][hItemLevel], HomeData[homeid][homeOwnerName], quantity, HouseStorage[homeid][checkitem][hItemQuantity]);  
                
                    itemid = House_GetFreeID(homeid);
                    if(itemid != -1){
                        printf("Add '%s' amount '%d' To SecondSlotHomeSpecial '%d'", item, amountnew, itemid);
                        HouseStorage[homeid][itemid][hItemExists] = true;
                        HouseStorage[homeid][itemid][hItemModel] = model;
                        HouseStorage[homeid][itemid][hItemQuantity] = amountnew;
                        HouseStorage[homeid][itemid][hItemAmmo] = ammo;
                        HouseStorage[homeid][itemid][hItemLevel] = level;
                        HouseStorage[homeid][itemid][hItemSlot] = itemid;
                        format(HouseStorage[homeid][itemid][hItemName], 64, item);

                        mysql_format(dbCon, string, sizeof(string), "INSERT INTO `homestorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`, `itemAmmo`, `itemLevel`, `itemSlot`) VALUES('%d', '%e', '%d', '%d', '%d', '%d', '%d')", HomeData[homeid][homeID], item, model, amountnew, ammo, level, itemid);
                        mysql_tquery(dbCon, string, "OnStorageAdd", "dd", homeid, itemid);
                        Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount = %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][itemid][hItemLevel], HomeData[homeid][homeOwnerName], amountnew, HouseStorage[homeid][itemid][hItemQuantity]);
                        return itemid;
                    }
                }
            }
            else{
                itemid = House_GetFreeID(homeid);
                if(itemid != -1){
                    printf("Add '%s' amount '%d' To HomeSlot '%d'", item, quantity, itemid);
                    HouseStorage[homeid][itemid][hItemExists] = true;
                    HouseStorage[homeid][itemid][hItemModel] = model;
                    HouseStorage[homeid][itemid][hItemQuantity] = quantity;
                    HouseStorage[homeid][itemid][hItemAmmo] = ammo;
                    HouseStorage[homeid][itemid][hItemLevel] = level;
                    HouseStorage[homeid][itemid][hItemSlot] = itemid;
                    format(HouseStorage[homeid][itemid][hItemName], 64, item);

                    mysql_format(dbCon, string, sizeof(string), "INSERT INTO `homestorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`, `itemAmmo`, `itemLevel`, `itemSlot`) VALUES('%d', '%e', '%d', '%d', '%d', '%d', '%d')", HomeData[homeid][homeID], item, model, quantity, ammo, level, itemid);
                    mysql_tquery(dbCon, string, "OnStorageAdd", "dd", homeid, itemid);
                    Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount = %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][itemid][hItemLevel], HomeData[homeid][homeOwnerName], quantity, HouseStorage[homeid][itemid][hItemQuantity]);
                    return itemid;
                }
            }
            return -1;
        }
    }
    else{
        if(CheckItemIsWeapon(item) != -1){
            itemid = House_GetFreeID(homeid);
            if(itemid != -1){
                printf("Add '%s' amount '%d' To SlotHome '%d'", item, quantity, itemid);
                HouseStorage[homeid][itemid][hItemExists] = true;
                HouseStorage[homeid][itemid][hItemModel] = model;
                HouseStorage[homeid][itemid][hItemQuantity] = quantity;
                HouseStorage[homeid][itemid][hItemAmmo] = ammo;
                HouseStorage[homeid][itemid][hItemLevel] = level;
                HouseStorage[homeid][itemid][hItemSlot] = itemid;
                format(HouseStorage[homeid][itemid][hItemName], 64, item);

                mysql_format(dbCon, string, sizeof(string), "INSERT INTO `homestorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`, `itemAmmo`, `itemLevel`, `itemSlot`) VALUES('%d', '%e', '%d', '%d', '%d', '%d', '%d')", HomeData[homeid][homeID], item, model, quantity, ammo, level, itemid);
                mysql_tquery(dbCon, string, "OnStorageAdd", "dd", homeid, itemid);
                Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount += %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][itemid][hItemLevel], HomeData[homeid][homeOwnerName], quantity, HouseStorage[homeid][itemid][hItemQuantity]);
                return itemid;
            }
            return -1;
        }
        else{
            itemid = House_GetItemID(homeid, item);
            if(itemid == -1){
                itemid = House_GetFreeID(homeid);
                if(itemid != -1){
                    printf("Add '%s' amount '%d' To SlotHome '%d'", item, quantity, itemid);
                    HouseStorage[homeid][itemid][hItemExists] = true;
                    HouseStorage[homeid][itemid][hItemModel] = model;
                    HouseStorage[homeid][itemid][hItemQuantity] = quantity;
                    HouseStorage[homeid][itemid][hItemAmmo] = ammo;
                    HouseStorage[homeid][itemid][hItemLevel] = level;
                    HouseStorage[homeid][itemid][hItemSlot] = itemid;
                    format(HouseStorage[homeid][itemid][hItemName], 64, item);

                    mysql_format(dbCon, string, sizeof(string), "INSERT INTO `homestorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`, `itemAmmo`, `itemLevel`, `itemSlot`) VALUES('%d', '%e', '%d', '%d', '%d', '%d', '%d')", HomeData[homeid][homeID], item, model, quantity, ammo, level, itemid);
                    mysql_tquery(dbCon, string, "OnStorageAdd", "dd", homeid, itemid);
                    Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount += %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][itemid][hItemLevel], HomeData[homeid][homeOwnerName], quantity, HouseStorage[homeid][itemid][hItemQuantity]);
                    return itemid;
                }
            }
            else{
                HouseStorage[homeid][itemid][hItemQuantity] += quantity;
                format(string, sizeof(string), "UPDATE `homestorage` SET `itemQuantity` = `itemQuantity` + %d WHERE `ID` = '%d' AND `itemID` = '%d' LIMIT 1", quantity, HomeData[homeid][homeID], HouseStorage[homeid][itemid][hItemID]);
                mysql_tquery(dbCon, string);
                Log_Write("logs/homeadditems.txt", "[%s] %s (level: %d) Add to home %s amount += %d, Total: %d", ReturnDate(), item, HouseStorage[homeid][itemid][hItemLevel], HomeData[homeid][homeOwnerName], quantity, HouseStorage[homeid][itemid][hItemQuantity]);  
            }
        }
    }
	return itemid;
}


Home_IsOwner(playerid, homeid)
{
	if (PlayerData[playerid][pID] == -1)
	    return 0;

    if ((HomeData[homeid][homeEx] && HomeData[homeid][homeOwner] != 0) && HomeData[homeid][homeOwner] == PlayerData[playerid][pID])
		return 1;

	return 0;
}

Home_IsRentOwner(playerid, homeid)
{
	if (PlayerData[playerid][pID] == -1)
	    return 0;

    if ((HomeData[homeid][homeEx] && HomeData[homeid][homeOwner] != 0) && HomeData[homeid][homeID] == PlayerData[playerid][pRentHome])
		return 1;

	return 0;
}

Home_Inside(playerid)
{
    for (new i = 0; i != MAX_HOME; i ++) if (HomeData[i][homeEx] && GetPlayerInterior(playerid) == HomeData[i][homeExitInt] && GetPlayerVirtualWorld(playerid) == HomeData[i][homeID] + WORLD_HOME) {
        return i;
    }
	return -1;
}

Home_NearestInside(playerid){
    for (new i = 0; i != MAX_HOME; i ++) if (HomeData[i][homeEx] && IsPlayerInRangeOfPoint(playerid, 2.5, HomeData[i][homeExitPos][0], HomeData[i][homeExitPos][1], HomeData[i][homeExitPos][2]))
	{
		if (GetPlayerInterior(playerid) == HomeData[i][homeExitInt] && GetPlayerVirtualWorld(playerid) == HomeData[i][homeID] + WORLD_HOME)
			return i;
	}
	return -1;
}

Home_Nearest(playerid)
{
    for (new i = 0; i != MAX_HOME; i ++) if (HomeData[i][homeEx] && IsPlayerInRangeOfPoint(playerid, 2.5, HomeData[i][homeEnterPos][0], HomeData[i][homeEnterPos][1], HomeData[i][homeEnterPos][2]))
	{
		if (GetPlayerInterior(playerid) == HomeData[i][homeEnterInt] && GetPlayerVirtualWorld(playerid) == HomeData[i][homeEnterWorld])
			return i;
	}
	return -1;
}

Dialog:ExitNoOwnerHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new id = -1;
            if((id = Home_NearestInside(playerid)) != -1){

                if(HomeData[id][homeLocked] == 1)
                    return ErrorMsg(playerid, "บ้านหลังนี้ ล็อค อยู่");

                SetPlayerPosEx(playerid, HomeData[id][homeEnterPos][0], HomeData[id][homeEnterPos][1], HomeData[id][homeEnterPos][2], HomeData[id][homeEnterInt], HomeData[id][homeEnterWorld]);
                SetPlayerFacingAngle(playerid, HomeData[id][homeEnterPos][3]);
            }
        }
    }
    return 1;
}

Dialog:ExitOwnerHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new id = -1;
            if((id = Home_NearestInside(playerid)) != -1){

                if(HomeData[id][homeLocked] == 1)
                    return ErrorMsg(playerid, "บ้านหลังนี้ ล็อค อยู่");

                SetPlayerPosEx(playerid, HomeData[id][homeEnterPos][0], HomeData[id][homeEnterPos][1], HomeData[id][homeEnterPos][2], HomeData[id][homeEnterInt], HomeData[id][homeEnterWorld]);
                SetPlayerFacingAngle(playerid, HomeData[id][homeEnterPos][3]);
            }
        }
        if(listitem == 1){
            new id = -1;
            if((id = Home_NearestInside(playerid)) != -1){

                if(HomeData[id][homeLocked] == 0){
                    GameTextForPlayer(playerid,"~r~HOUSE LOCK!",1000,3);
                    PlayerPlaySoundEx(playerid, 1145);
                    HomeData[id][homeLocked] = 1;
                    Home_Save(id);
                }
                else if(HomeData[id][homeLocked] == 1){
                    GameTextForPlayer(playerid,"~g~HOUSE UNLOCK!",1000,3);
                    PlayerPlaySoundEx(playerid, 1145);
                    HomeData[id][homeLocked] = 0;
                    Home_Save(id);
                }
            }
        }
    }
    return 1;
}

Dialog:NoOwnerHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new id = -1;
            if((id = Home_Nearest(playerid)) != -1){

                if(HomeData[id][homeLocked] == 1)
                    return ErrorMsg(playerid, "บ้านหลังนี้ ล็อค อยู่");

                SetPlayerPosEx(playerid, HomeData[id][homeExitPos][0], HomeData[id][homeExitPos][1], HomeData[id][homeExitPos][2], HomeData[id][homeExitInt], HomeData[id][homeID] + WORLD_HOME);
                SetPlayerFacingAngle(playerid, HomeData[id][homeExitPos][3]);
            }
        }
    }
    return 1;
}

Dialog:OwnerHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new id = -1;
            if((id = Home_Nearest(playerid)) != -1){

                if(HomeData[id][homeLocked] == 1)
                    return ErrorMsg(playerid, "บ้านหลังนี้ ล็อค อยู่");

                SetPlayerPosEx(playerid, HomeData[id][homeExitPos][0], HomeData[id][homeExitPos][1], HomeData[id][homeExitPos][2], HomeData[id][homeExitInt], HomeData[id][homeID] + WORLD_HOME);
                SetPlayerFacingAngle(playerid, HomeData[id][homeExitPos][3]);
                SendClientMessage(playerid, COLOR_YELLOW, "[แนะนำ]: กด 'Y' เพื่อใช้งานเมนูในบ้านต่างๆ");
            }
        }
        if(listitem == 1){
            new id = -1;
            if((id = Home_Nearest(playerid)) != -1){

                if(HomeData[id][homeLocked] == 0){
                    GameTextForPlayer(playerid,"~r~HOUSE LOCK!",1000,3);
                    PlayerPlaySoundEx(playerid, 1145);
                    HomeData[id][homeLocked] = 1;
                    Home_Save(id);
                }
                else if(HomeData[id][homeLocked] == 1){
                    GameTextForPlayer(playerid,"~g~HOUSE UNLOCK!",1000,3);
                    PlayerPlaySoundEx(playerid, 1145);
                    HomeData[id][homeLocked] = 0;
                    Home_Save(id);
                }
            }
        }

        if(listitem == 2){
            if(Home_Nearest(playerid) != -1){
                callcmd::viewrents(playerid, "\1");
            }
        }

        if(listitem == 3){
            new id = -1;
            new query[256];
            if((id = Home_Nearest(playerid)) != -1){
                if(Home_IsOwner(playerid, id)){
                    mysql_format(dbCon, query, sizeof(query), "SELECT Username, RentHome FROM `characters` WHERE RentHome = '%d' LIMIT 5", HomeData[id][homeID]);
	                mysql_tquery(dbCon, query, "CheckRentHomeAll", "ii", playerid, 1);
                }
                else return ErrorMsg(playerid, "คุณจะต้องเป็นเจ้าของบ้าน");
            }
        }
    }
    return 1;
}

forward CheckRentHomeAll(playerid, threadid);
public CheckRentHomeAll(playerid, threadid){
    if(cache_num_rows()){
        new string[256], string2[500];
        new name[64];
        new rows = cache_num_rows();
        if(threadid == 1){
            for(new i = 0; i < rows; i ++){
                cache_get_value_name(i, "Username", name, 64);
                format(string, sizeof(string), "{FFFFFF}%d. ผู้เช่า: %s\n", i+1, name);
                strcat(string2, string);
            }
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "ผู้เช่าบ้านทั้งหมด", string2, "ตกลง", "ปิด");
        }
    }
    else Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "ผู้เช่าบ้านทั้งหมด", "ไม่พบผู้เช่าบ้าน!", "ตกลง", "ปิด");
    return 1;
}

Dialog:BuildHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new caption[128];
        if(listitem == 0){
            format(caption, sizeof(caption), "ไม้ในคลังบ้าน [%d]", PlayerData[playerid][pBuildItemHome][0]);
            Dialog_ShowEasy(playerid, ManageWoodHome, DIALOG_STYLE_LIST, caption, "เก็บใส่คลัง\nเบิกออกจากคลัง", "เลือก", "ยกเลิก");
        }
        if(listitem == 1){
            format(caption, sizeof(caption), "เหล็กในคลังบ้าน [%d]", PlayerData[playerid][pBuildItemHome][1]);
            Dialog_ShowEasy(playerid, ManageOreHome, DIALOG_STYLE_LIST, caption, "เก็บใส่คลัง\nเบิกออกจากคลัง", "เลือก", "ยกเลิก");
        }
        if(listitem == 2){
            new string[256];
            format(string, sizeof(string), "ไม้ที่ต้องใช้: [%d] >> ไม้ที่มีในคลังบ้าน: [%d] <<\
            \nเหล็กที่ต้องใช้: [%d] >> เหล็กที่มีในคลังบ้าน: [%d] <<\
            \nคุณต้องการที่จะเริ่มก่อสร้างเลยหรือไม่?", USEWOOD, PlayerData[playerid][pBuildItemHome][0], USEORE, PlayerData[playerid][pBuildItemHome][1]);
            Dialog_ShowEasy(playerid, StartBuildHome, DIALOG_STYLE_MSGBOX, "การก่อสร้างบ้าน", string, "สร้าง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:StartBuildHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new id = -1;
        if((id = Home_Nearest(playerid)) != -1){
            if(Home_IsOwner(playerid, id)){
                if(PlayerData[playerid][pBuildItemHome][0] < USEWOOD)
                    return ErrorMsg(playerid, "ในคลังบ้านของคุณมีไม้ไม่พอสำหรับการก่อสร้าง");

                if(PlayerData[playerid][pBuildItemHome][1] < USEORE)
                    return ErrorMsg(playerid, "ในคลังบ้านของคุณมีเหล็กไม่พอสำหรับการก่อสร้าง");

                PlayerData[playerid][pBuildItemHome][0] -= USEWOOD;
                PlayerData[playerid][pBuildItemHome][1] -= USEORE;
                SendClientMessage(playerid, -1, "|-----------------------------------------------------|");
                SendClientMessage(playerid, COLOR_YELLOW, "- คุณประสบความสำเร็จในการก่อสร้างบ้านเรียบร้อยแล้ว");
                SendClientMessageEx(playerid, COLOR_RED, "- ไม้ในคลังบ้าน - %d", USEWOOD);
                SendClientMessageEx(playerid, COLOR_RED, "- เหล็กในคลังบ้าน - %d", USEORE);
                SendClientMessage(playerid, -1, "|-----------------------------------------------------|");
                HomeData[id][homeBuild] = 1;
                Home_Refresh(id);
                Home_Save(id);
            }
        }
    }
    return 1;
}

Dialog:ManageOreHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new caption[128];
        if(listitem == 0){
            new count = PlayerInventory_AllCount(playerid, "Ore");
            format(caption, sizeof(caption), "เหล็กในตัว [%d]", count);
            Dialog_ShowEasy(playerid, StoreOreHome, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            format(caption, sizeof(caption), "เหล็กในคลังบ้าน [%d]", PlayerData[playerid][pBuildItemHome][1]);
            Dialog_ShowEasy(playerid, TakeOreHome, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:StoreOreHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new count = PlayerInventory_AllCount(playerid, "Ore");

        new caption[128];
        if(amount <= 0){
            format(caption, sizeof(caption), "เหล็กในตัว [%d]", count);
            return Dialog_ShowEasy(playerid, StoreOreHome, DIALOG_STYLE_INPUT, caption, "* คุณต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }

        if(count < amount){
            format(caption, sizeof(caption), "เหล็กในตัว [%d]", count);
            return Dialog_ShowEasy(playerid, StoreOreHome, DIALOG_STYLE_INPUT, caption, "* คุณมีเหล็กในตัวไม่พอ *\nกรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }

        if(PlayerData[playerid][pBuildItemHome][1] + amount > USEORE)
            return SendClientMessageEx(playerid, COLOR_RED, "เหล็กในคลังบ้านของคุณเต็มได้ไม่เกิน %d", USEORE);

        PlayerInventory_Remove(playerid, "Ore", amount);
        PlayerData[playerid][pBuildItemHome][1] += amount;
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เก็บ เหล็ก จำนวน %d เข้าคลังบ้านเรียบร้อยแล้ว", amount);
    }
    return 1;
}

Dialog:TakeOreHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new count = PlayerData[playerid][pBuildItemHome][1];

        new caption[128];
        if(amount <= 0){
            format(caption, sizeof(caption), "เหล็กในคลังบ้าน [%d]", count);
            return Dialog_ShowEasy(playerid, TakeOreHome, DIALOG_STYLE_INPUT, caption, "* คุณต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }

        if(count < amount){
            format(caption, sizeof(caption), "เหล็กในคลังบ้าน [%d]", count);
            return Dialog_ShowEasy(playerid, TakeOreHome, DIALOG_STYLE_INPUT, caption, "* คุณมีไม้ในคลังไม่พอ *\nกรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }

        new id = PlayerInventory_AddItem(playerid, "Ore", 19941, amount);
        if (id == -1)
            return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

        PlayerData[playerid][pBuildItemHome][1] -= amount;
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้หยิบ เหล็ก จำนวน %d ออกจากคลังบ้านเรียบร้อยแล้ว", amount);
    }
    return 1;
}

Dialog:ManageWoodHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new caption[128];
        if(listitem == 0){
            new count = PlayerInventory_AllCount(playerid, "Wood");
            format(caption, sizeof(caption), "ไม้ในตัว [%d]", count);
            Dialog_ShowEasy(playerid, StoreWoodHome, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            format(caption, sizeof(caption), "ไม้ในคลังบ้าน [%d]", PlayerData[playerid][pBuildItemHome][0]);
            Dialog_ShowEasy(playerid, TakeWoodHome, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:StoreWoodHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new count = PlayerInventory_AllCount(playerid, "Wood");

        new caption[128];
        if(amount <= 0){
            format(caption, sizeof(caption), "ไม้ในตัว [%d]", count);
            return Dialog_ShowEasy(playerid, StoreWoodHome, DIALOG_STYLE_INPUT, caption, "* คุณต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }

        if(count < amount){
            format(caption, sizeof(caption), "ไม้ในตัว [%d]", count);
            return Dialog_ShowEasy(playerid, StoreWoodHome, DIALOG_STYLE_INPUT, caption, "* คุณมีไม้ในตัวไม่พอ *\nกรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }

        if(PlayerData[playerid][pBuildItemHome][0] + amount > USEWOOD)
            return SendClientMessageEx(playerid, COLOR_RED, "ไม้ในคลังบ้านของคุณเต็มได้ไม่เกิน %d", USEWOOD);

        PlayerInventory_Remove(playerid, "Wood", amount);
        PlayerData[playerid][pBuildItemHome][0] += amount;
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เก็บ ไม้ จำนวน %d เข้าคลังบ้านเรียบร้อยแล้ว", amount);
    }
    return 1;
}

Dialog:TakeWoodHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new count = PlayerData[playerid][pBuildItemHome][0];

        new caption[128];
        if(amount <= 0){
            format(caption, sizeof(caption), "ไม้ในคลังบ้าน [%d]", count);
            return Dialog_ShowEasy(playerid, TakeWoodHome, DIALOG_STYLE_INPUT, caption, "* คุณต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }

        if(count < amount){
            format(caption, sizeof(caption), "ไม้ในคลังบ้าน [%d]", count);
            return Dialog_ShowEasy(playerid, TakeWoodHome, DIALOG_STYLE_INPUT, caption, "* คุณมีไม้ในคลังไม่พอ *\nกรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }

        new id = PlayerInventory_AddItem(playerid, "Wood", 19793, amount);
        if (id == -1)
            return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

        PlayerData[playerid][pBuildItemHome][0] -= amount;
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้หยิบ ไม้ จำนวน %d ออกจากคลังบ้านเรียบร้อยแล้ว", amount);
    }
    return 1;
}

Dialog:BUYHOUSE(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new id = -1;
        if((id = Home_Nearest(playerid)) != -1){
            if(HomeData[id][homeOwner] == 0){

                if(GetMoney(playerid) < HomeData[id][homePrice])
                    return ErrorMsg(playerid, "คุณมีเงินไม่พอ");
                    
                HomeData[id][homeOwner] = PlayerData[playerid][pID];
                format(HomeData[id][homeOwnerName], 64, ReturnRoleplayName(playerid));
                GiveMoney(playerid, -HomeData[id][homePrice], "buy home");
                SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ซื้อบ้าน %s ในราคา %s เรียบร้อยแล้ว", HomeData[id][homeName], FormatNumber(HomeData[id][homePrice]));
                Home_Refresh(id);
                Home_Save(id);
            }
        }
    }
    return 1;
}

CMD:doorbell(playerid, params[]){
	new id = Home_Nearest(playerid);
	if (id == -1) return ErrorMsg(playerid, "คุณต้องยืนอยู่ใกล้บ้าน");

	foreach (new i : Player) if (Home_Inside(i) == id) {
	    SendClientMessage(i, COLOR_RP, "** คุณได้ยินเสียงออด");
	    PlayerPlaySound(i, 20801, 0, 0, 0);
	}

	PlayerPlaySoundEx(playerid, 20801);
	SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s สั่นกระดิ่ง เสียงออดของบ้าน", ReturnRoleplayName(playerid));
	return 1;
}

CMD:homecmds(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[HOMECMDS]: /makehome, /removehome, /edithome, /gotohome");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

CMD:gotohome(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	new
		id;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/gotohome [home ID]");

	if ((id < 0 || id >= MAX_HOME) || !HomeData[id][homeEx])
		return SendClientMessage(playerid, -1, "คุณระบุ home ID ไม่ถูกต้อง");

	SetPlayerPosEx(playerid, HomeData[id][homeEnterPos][0], HomeData[id][homeEnterPos][1], HomeData[id][homeEnterPos][2], HomeData[id][homeEnterInt], HomeData[id][homeEnterWorld]);
	SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ home ID: %d", id);
	return 1;
}

CMD:makehome(playerid, params[]){
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pAdmin] >= 1338){
            new id = -1, name[32], price;
            if(sscanf(params, "ds[32]", price, name))
                return SystemMsg(playerid, "/makehouse [homeprice] [homename]");

            id = Home_Create(playerid, name, price);
            if(id == -1)
                return ErrorMsg(playerid, "เซิฟเวอร์ได้สร้าง บ้าน เกินขีดจำกัดแล้ว");

            SendClientMessageEx(playerid, -1, "คุณได้ประสบความสำเร็จในการสร้างบ้านไอดี: %d", id);
        }
    }
    return 1;
}

CMD:removehome(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	new
		id = 0;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/removehome [house id]");

	if ((id < 0 || id >= MAX_HOME) || !HomeData[id][homeEx])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีบ้านไม่ถูกต้อง");

	Home_Delete(id);
	SendClientMessageEx(playerid, -1, "คุณทำลายบ้านสำเร็จแล้วไอดี: %d", id);
	return 1;
}

CMD:edithome(playerid, params[])
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
		SystemMsg(playerid, "/edithome [id] [name]");
		SystemMsg(playerid, "[ตัวเลือก]:{FFFFFF} location, interior, price, name, owner, maxitem, itemamount, type, ownername");
		return 1;
	}
	if ((id < 0 || id >= MAX_HOME) || !HomeData[id][homeEx])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีบ้านไม่ถูกต้อง");

	if (!strcmp(type, "location", true))
	{
		GetPlayerPos(playerid, HomeData[id][homeEnterPos][0], HomeData[id][homeEnterPos][1], HomeData[id][homeEnterPos][2]);
		GetPlayerFacingAngle(playerid, HomeData[id][homeEnterPos][3]);

		HomeData[id][homeEnterInt] = GetPlayerInterior(playerid);
		HomeData[id][homeEnterWorld] = GetPlayerVirtualWorld(playerid);

		Home_Refresh(id);
		Home_Save(id);

        format(string, sizeof(string), "%s ได้ปรับตำแหน่งของบ้านไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "interior", true))
	{
		GetPlayerPos(playerid, HomeData[id][homeExitPos][0], HomeData[id][homeExitPos][1], HomeData[id][homeExitPos][2]);
		GetPlayerFacingAngle(playerid, HomeData[id][homeExitPos][3]);

		HomeData[id][homeExitInt] = GetPlayerInterior(playerid);
        SetPlayerPosEx(playerid, HomeData[id][homeExitPos][0], HomeData[id][homeExitPos][1], HomeData[id][homeExitPos][2], HomeData[id][homeExitInt], HomeData[id][homeID] + WORLD_HOME);
        SetPlayerFacingAngle(playerid, HomeData[id][homeExitPos][3]);
		Home_Save(id);
        format(string, sizeof(string), "%s ได้ปรับตำแหน่งจุดเกิดภายในของบ้านไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "price", true))
	{
		new price;

		if (sscanf(string, "d", price))
			return SendClientMessage(playerid, -1, "/edithome [id] [price] [new price]");

		HomeData[id][homePrice] = price;

		Home_Refresh(id);
		Home_Save(id);

        format(string, sizeof(string), "%s ได้ปรับราคาของบ้านไอดี: %d เป็น %s", ReturnRoleplayName(playerid), id, FormatNumber(price));
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
    else if (!strcmp(type, "maxitem", true))
	{
		new maxi;

		if (sscanf(string, "d", maxi))
			return SendClientMessage(playerid, -1, "/edithome [id] [maxitem] [new maxitem]");

		HomeData[id][homeMaxItem] = maxi;

		Home_Refresh(id);
		Home_Save(id);

        format(string, sizeof(string), "%s ได้ปรับ จำนวนไอเท็มสูงสุด ของบ้านไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, maxi);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
    else if (!strcmp(type, "itemamount", true))
	{
		new amount;

		if (sscanf(string, "d", amount))
			return SendClientMessage(playerid, -1, "/edithome [id] [itemamount] [new itemamount]");

		HomeData[id][homeItemAmount] = amount;

		Home_Refresh(id);
		Home_Save(id);

        format(string, sizeof(string), "%s ได้ปรับ จำนวนชิ้นไอเท็ม ของบ้านไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, amount);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "owner", true))
	{
		new sid;

		if (sscanf(string, "d", sid))
			return SendClientMessage(playerid, -1, "/edithome [id] [owner] [owner ID]");

		HomeData[id][homeOwner] = sid;

		Home_Refresh(id);
		Home_Save(id);

        format(string, sizeof(string), "%s ได้ปรับเจ้าของของบ้านไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, sid);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
    else if(!strcmp(type, "ownername", true)){
        new ownername[64];

		if (sscanf(string, "s[64]", ownername))
			return SendClientMessage(playerid, -1, "/edithome [id] [ownername] [new ownername]");

		format(HomeData[id][homeOwnerName], 64, ownername);

		Home_Refresh(id);
		Home_Save(id);

        format(string, sizeof(string), "%s ได้ปรับชื่อเจ้าของบ้านไอดี: %d เป็น \"%s\"", ReturnRoleplayName(playerid), id, ownername);
		SendAdminsMessage(1, COLOR_GRAY, string);
    }
	else if (!strcmp(type, "name", true))
	{
		new address[32];

		if (sscanf(string, "s[32]", address))
			return SendClientMessage(playerid, -1, "/edithome [id] [address] [new address]");

		format(HomeData[id][homeName], 32, address);

		Home_Refresh(id);
		Home_Save(id);

        format(string, sizeof(string), "%s ได้ปรับที่อยู่ของบ้านไอดี: %d เป็น \"%s\"", ReturnRoleplayName(playerid), id, address);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
    else if (!strcmp(type, "type", true))
	{
		new typeint;

		if (sscanf(string, "d", typeint))
			return SendClientMessage(playerid, -1, "/edithome [id] [type] [interior type]");

		if (typeint < 1 || typeint > sizeof(arrHouseInteriors))
			return SendClientMessageEx(playerid, -1, "ประเภทที่ระบุต้องไม่ต่ำกว่า 1 ถึง %d", sizeof(arrHouseInteriors));

		typeint--;

		HomeData[id][homeExitPos][0] = arrHouseInteriors[typeint][eHouseX];
		HomeData[id][homeExitPos][1] = arrHouseInteriors[typeint][eHouseY];
		HomeData[id][homeExitPos][2] = arrHouseInteriors[typeint][eHouseZ];
		HomeData[id][homeExitPos][3] = arrHouseInteriors[typeint][eHouseAngle];
		HomeData[id][homeExitInt] = arrHouseInteriors[typeint][eHouseInterior];

        SetPlayerPosEx(playerid, HomeData[id][homeExitPos][0], HomeData[id][homeExitPos][1], HomeData[id][homeExitPos][2], HomeData[id][homeExitInt], HomeData[id][homeID] + WORLD_HOME);
        SetPlayerFacingAngle(playerid, HomeData[id][homeExitPos][3]);
        SetCameraBehindPlayer(playerid);

        Home_Refresh(id);
		Home_Save(id);
        format(string, sizeof(string), "%s ได้ปรับประเภทของบ้านไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, typeint+1);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	return 1;
}

alias:cancelhomerent("cchr")
CMD:cancelhomerent(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pRentHome] == 0) return ErrorMsg(playerid, "คุณยังไม่มีบ้านเช่าใดๆ");
    else{
        new query[128];
        mysql_format(dbCon, query, sizeof(query), "SELECT * FROM `homes` WHERE homeID = '%d' LIMIT 1", PlayerData[playerid][pRentHome]);
        mysql_tquery(dbCon, query, "CancelHomeRent", "i", playerid);
    }
    return 1;
}

forward CancelHomeRent(playerid);
public CancelHomeRent(playerid){
    if(cache_num_rows()){
        new query[128];
        new OwnerName[64], RentAmount;
        cache_get_value_name(0, "homeOwnerName", OwnerName, 64);
        cache_get_value_int(0, "homeRentAmount", RentAmount);
        SendClientMessageEx(playerid, COLOR_RED, "คุณได้ยกเลิกเช่าบ้านของ %s เรียบร้อยแล้ว", OwnerName);

        RentAmount--;
        mysql_format(dbCon, query, sizeof(query), "UPDATE `homes` SET homeRentAmount = '%d' WHERE homeID = '%d'", RentAmount, PlayerData[playerid][pRentHome]);
        mysql_tquery(dbCon, query);

        foreach(new i : Player){
            if(!LoggedIn[i]) continue;
            for(new j=0; j<MAX_HOME; j++) if(HomeData[j][homeEx]){
                if(PlayerData[playerid][pRentHome] == HomeData[j][homeID]){
                    if(Home_IsOwner(i, j)) SendClientMessageEx(i, COLOR_YELLOW, "%s ได้ยกเลิกการเช่าบ้านของคุณแล้ว", ReturnRoleplayName(playerid));
                }
            }
        }

        PlayerData[playerid][pRentHome] = 0;
    }

    return 1;
}


alias:givekeyhome("gkh")
CMD:givekeyhome(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    new userid;
    if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/givekeyhome [playerid]");
    if(userid == INVALID_PLAYER_ID) return 1;
    if(userid != INVALID_PLAYER_ID){
        if(IsPlayerNearPlayer(playerid, userid, 5.0)){
            new count = 0;
            new homeid = -1;
            if(LoggedIn[userid]){

                for(new i=0; i<MAX_HOME; i++) if(HomeData[i][homeEx]){
                    if(Home_IsOwner(playerid, i)){
                        count++;
                        homeid = i;
                    }
                }

                if(count >= 1){
                    if(HomeData[homeid][homeID] > 0){
                        if(HomeData[homeid][homeRentAmount] >= MAX_RENT_AMOUNT) return ErrorMsg(playerid, "บ้านของคุณมีผู้เช่าเต็มแล้ว");

                        if(PlayerData[userid][pRentHome] != 0)
                            return ErrorMsg(playerid, "ผู้เล่นนั้นมีบ้านเช่าอยู่แล้ว");

                        PlayerData[userid][pRentHome] = HomeData[homeid][homeID];
                        HomeData[homeid][homeRentAmount]++;
                        Home_Save(homeid);
                        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้มอบกุญแจสำรองของบ้านให้กับ %s เรียบร้อยแล้ว", ReturnRoleplayName(userid));
                        SendClientMessageEx(userid, COLOR_YELLOW, "%s ได้มอบกุญแจสำรองของบ้านให้กับคุณเรียบร้อยแล้ว", ReturnRoleplayName(playerid)); 
                    }
                }
            }
        }
    }
    return 1;
}

CMD:viewrents(playerid, const params[]){
    if(!LoggedIn[playerid]) return 1;
    new homeid = -1;
    for(new i=0; i<MAX_HOME; i++) if(HomeData[i][homeEx]){
        if(Home_IsOwner(playerid, i)){
            homeid = i;
        }
    }

    if(homeid != -1){
        GetHomeIDTemp[playerid] = homeid;
        ShowDialogRents(playerid, homeid);
    }
    return 1;
}

ShowDialogRents(playerid, homeid){
    if(homeid != -1){
        new count;
        new menu[20];
        new string[256], string2[500];
        foreach(new i : Player){
            if(!LoggedIn[i]) continue;
            if(i == playerid) continue;
            if(PlayerData[i][pRentHome] == HomeData[homeid][homeID]){
                format(menu, 20, "menu%d", count++);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), " %s(%d)\n", ReturnRoleplayName(i), i);
                strcat(string2, string);
            }
        }
        if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "รายชื่อคนเช่าบ้านของคุณที่ออนไลน์อยู่", "ไม่มีผู้เช่าบ้านที่ออนไลน์อยู่", "ตกลง", "ยกเลิก");
        else Dialog_ShowEasy(playerid, ViewRentsHome, DIALOG_STYLE_LIST, "รายชื่อคนเช่าบ้านของคุณที่ออนไลน์อยู่", string2, "เลือก", "ยกเลิก");
    }
    return 1;
}

Dialog:ViewRentsHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem >= 0 && listitem <= 5) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);
			SetPVarInt(playerid, "playerID", GetPVarInt(playerid, str_biz));
			ManageRenterMyHome(playerid);
			return 1;
		}
    }
    return 1;
}

ManageRenterMyHome(playerid){
    new targetid = GetPVarInt(playerid, "playerID");
    new caption[128];
    if(!LoggedIn[targetid]) return ErrorMsg(playerid, "ผู้เล่นนั้นไม่ได้เข้าสู่ระบบ");
    GetPlayerRentHome[playerid] = targetid;
    format(caption, sizeof(caption), "ผู้เช่า: %s(%d)", ReturnRoleplayName(targetid), targetid);
    Dialog_ShowEasy(playerid, ManageRents, DIALOG_STYLE_LIST, caption, "ไล่ออก", "เลือก", "ยกเลิก");
    return 1;
}

Dialog:ManageRents(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new targetid = GetPlayerRentHome[playerid];
        if(targetid == -1) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
        if(!LoggedIn[targetid]) return ErrorMsg(playerid, "ผู้เล่นนั้นไม่ได้เข้าสู่ระบบ");
        PlayerData[targetid][pRentHome] = 0;
        HomeData[GetHomeIDTemp[playerid]][homeRentAmount]--;
        Home_Save(GetHomeIDTemp[playerid]);
        SendClientMessageEx(targetid, COLOR_YELLOW, "- ผู้เช่า %s ได้ไล่คุณออกจากการเช่าบ้านของเขาแล้ว", ReturnRoleplayName(playerid));
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ไล่ %s ออกจากการผู้เช่าบ้านของคุณแล้ว", ReturnRoleplayName(targetid));
        GetHomeIDTemp[playerid] = -1;
        GetPlayerRentHome[playerid] = 0;
    }
    return 1;
}

CMD:findmyhome(playerid, params[]){
    new homeid = -1;
    for(new i=0; i<MAX_HOME; i++) if(HomeData[i][homeEx]){
        if(Home_IsOwner(playerid, i)){
            homeid = i;
        }
    }
    if(homeid == -1) return ErrorMsg(playerid, "คุณไม่มีบ้านอยู่เลย");

    SendClientMessage(playerid, COLOR_ORANGE, "- คุณได้เปิด GPS ไปยังบ้านของคุณแล้ว");
    PlayerEnterCheckPoint[playerid] = 1;
    GPSNavigateToPoint(playerid, HomeData[homeid][homeEnterPos][0], HomeData[homeid][homeEnterPos][1], HomeData[homeid][homeEnterPos][2]);
    SetPlayerCheckpoint(playerid, HomeData[homeid][homeEnterPos][0], HomeData[homeid][homeEnterPos][1], HomeData[homeid][homeEnterPos][2], 3.0);
    return 1;
}

CMD:thouse(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    new userid;

    if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/thouse [playerid]");
    if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
    if(userid != INVALID_PLAYER_ID && LoggedIn[userid]){

        if(PlayerData[playerid][pLevel] < 2) return ErrorMsg(playerid, "คุณต้องมีเลเวล 2 ขึ้นไปถึงจะแชร์บ้านได้");
        if(PlayerData[userid][pLevel] < 2) return ErrorMsg(playerid, "คนที่คุณจะให้แชร์กุญแจบ้านจะต้องมีเลเวล 2 ขึ้นไป");

        new count = 0;
        new homeid = -1;
        new usercount = 0;
        for(new i=0; i<MAX_HOME; i++) if(HomeData[i][homeEx]){
            if(Home_IsOwner(playerid, i)){
                count++;
                homeid = i;
            }
            if(Home_IsOwner(userid, i)){
                usercount++;
            }
        }
        
        if(count < 1) return ErrorMsg(playerid, "คุณไม่มีบ้านอยู่เลย");
        if(usercount >= 1) return ErrorMsg(playerid, "ผู้เล่นนั้นมีบ้านเกินขีดจำกัดแล้ว");

        foreach(new i : Player) {
            if(!LoggedIn[i]) continue;
            if(PlayerData[i][pRentHome] == HomeData[homeid][homeID]){
                SendClientMessageEx(i, COLOR_YELLOW, "- คุณได้ยกเลิกเช่าบ้านของ %s เรียบร้อยแล้ว", HomeData[homeid][homeOwnerName]);
                PlayerData[i][pRentHome] = 0;
            }
        }

        new string[128];

        format(string, sizeof(string), "UPDATE `characters` SET `RentHome` = '-1' WHERE `RentHome` = '%d' LIMIT 5", HomeData[homeid][homeID]);
        mysql_tquery(dbCon, string);

        HomeData[homeid][homeOwner] = PlayerData[userid][pID];
        HomeData[homeid][homeRentAmount] = 0;
        format(HomeData[homeid][homeOwnerName], 64, ReturnRoleplayName(userid));
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณจะประสบควาสำเร็จในการโอนบ้านให้กับ: %s", ReturnRoleplayName(userid));
        SendClientMessageEx(userid, COLOR_YELLOW, "- คุณได้รับกุญแจบ้านจาก %s เรียบร้อยแล้ว", ReturnRoleplayName(playerid));
        Home_Refresh(homeid);
        Home_Save(homeid);
    }
    return 1;
}