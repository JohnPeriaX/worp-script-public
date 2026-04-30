#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

//------------------------------------//

// PRESSED(keys)
#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

//------------------------------------//
hook OnGameModeInit(){
    for(new i=0; i<MAX_DROPPED_ITEMS; i++){
        Drop_Data[i][droppedID] = 0;
        format(Drop_Data[i][droppedItem], 64, "NULL");
        Drop_Data[i][droppedModel] = MODEL_NULL;
        Drop_Data[i][droppedQuantity] = 0;
        Drop_Data[i][droppedPos][0] = 0.0;
        Drop_Data[i][droppedPos][1] = 0.0;
        Drop_Data[i][droppedPos][2] = 0.0;
        Drop_Data[i][droppedInt] = 0;
        Drop_Data[i][droppedWorld] = 0;
    }
    return 1;
}

ResetPlayer_Inventory(playerid){

    for(new i=0; i<MAX_INVENTORYPLAYERS; i++){
        Inventory_Player[playerid][i][itemHave] = false;
        Inventory_Player[playerid][i][itemID] = 0;
        Inventory_Player[playerid][i][itemOwner] = 0;
        Inventory_Player[playerid][i][itemKey] = MODEL_NULL;
        Inventory_Player[playerid][i][itemQuantity] = 0;
        Inventory_Player[playerid][i][itemLevel] = 0;
        Inventory_Player[playerid][i][itemAmmo] = 0;
        Inventory_Player[playerid][i][itemSlot] = -1;
        format(Inventory_Player[playerid][i][itemName], 64, "NULL");
        if(i >= 107) break;
    }

    PlayerVicinity[playerid] = false;
    PlayerInventoryStatus[playerid] = false;
    PlayerSlotInventoryCount[playerid] = 0;
    PlayerInvListItemRows[playerid] = -1;
    PlayerInvListItemColumn[playerid] = -1;
    PlayerGetIndexSlotItem[playerid] = -1;
    PlayerGetIndexNextSlotItem[playerid] = -1;
    PlayerInvListItemRowsOld[playerid] = -1;
    PlayerInvListItemColumnOld[playerid] = -1;
    PlayerInventoryDropInput[playerid] = false;
    PlayerInventoryPage[playerid] = 1;
    PlayerEditPositionInventory[playerid] = false;
    PlayerEditColorInventory[playerid] = false;

    PlayerInventoryColorType[playerid] = 0;

    PlayerPositionInventoryX[playerid] = -105;
	PlayerPositionInventoryY[playerid] = 55;

    PlayerInventoryLastPage[playerid] = 0;

    for (new i = 0; i < MAX_VICINITY; i ++) {
	    PlayerNearestItems[playerid][i] = -1;
	}

    PlayerInventoryType[playerid] = INVENTORY_TYPE;
    PlayerInventoryCodeColor[playerid] = 0xFFA200FF;
    PlayerInventoryHoverCodeColor[playerid] = 0xFF5100AA;

    PlayerShowButton[playerid] = false;
    PlayerCantSelectTextDraw[playerid] = false;
    return 1;
}

OnPlayerInventory_Open(playerid){
    PlayerInventoryStatus[playerid] = true;
    LoadPlayerInventoryTextDraw(playerid);
    LoadPlayerInventorySlotTextDraw(playerid);

    for(new i=0; i!=MAX_INVENTORYTEXTDRAW; i++){
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][i]);
    }

    PlayerTextDrawSetString(playerid, PlayerInventoryTextDraw[playerid][2], "Loading...");
    PlayerTextDrawSetString(playerid, PlayerInventoryTextDraw[playerid][16], "Loading...");
    PlayerTextDrawSetString(playerid, PlayerInventoryTextDraw[playerid][20], "Loading...");

    if(!PlayerTradingItem[playerid]){
        if(!PlayerUsing_HomeInv[playerid]){
            new count = 0;
            //printf("[1] %s Load Vicinity", ReturnRoleplayName(playerid));
            foreach(new i : Iter_DropItem) if(Iter_Contains(Iter_DropItem, i) && count < MAX_VICINITY && Drop_Data[i][droppedModel] != MODEL_NULL && IsPlayerInRangeOfPoint(playerid, 1.5, Drop_Data[i][droppedPos][0], Drop_Data[i][droppedPos][1], Drop_Data[i][droppedPos][2]) && GetPlayerInterior(playerid) == Drop_Data[i][droppedInt] && GetPlayerVirtualWorld(playerid) == Drop_Data[i][droppedWorld]){
                PlayerNearestItems[playerid][count] = i;
                //printf("List of Vicinity: [%d] %s", PlayerNearestItems[playerid][count], Drop_Data[PlayerNearestItems[playerid][count]][droppedItem]);
                count++;
            }

            if(count != 0){
                //printf("count: %d", count);
                if(!PlayerVicinity[playerid]){
                    PlayerVicinity[playerid] = true;
                    LoadPlayerVicinityTextDraw(playerid);
                    LoadPlayerVicinitySlotTextDraw(playerid);
                    for(new i=0; i<MAX_VICINITYTEXTDRAW; i++){
                        PlayerTextDrawShow(playerid, PlayerVicinityTextDraw[playerid][i]);
                    }
                }
                OnPlayerVicinity_Render(playerid);
            }

            if(!PlayerVicinity[playerid]){
                LoadPlayerCharacterTextDraw(playerid);
                for(new i=0; i<MAX_CHARTEXT; i++){
                    PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][i]);
                }
                PlayerCharacterShow[playerid] = true;
                PlayerCharacterTD_Render(playerid);
            }
        }
    }

    OnPlayerInventory_Render(playerid);
    if(IsAndroidPlayer(playerid)) SetTimerEx("Reload_RenderInv", 200, false, "i", playerid);

    OnPlayerInventory_UpdateCount(playerid);
    PlayerTextDrawSetString(playerid, PlayerInventoryTextDraw[playerid][2], "Inventory");
    SelectTextDraw(playerid, PlayerInventoryHoverCodeColor[playerid]);

    TogglePlayerControllable(playerid, 0);
    return 1;
}

forward Reload_RenderInv(playerid);
public Reload_RenderInv(playerid){
    OnPlayerInventory_Render(playerid);
    return 1;
}

RemoveUseInfoButton(playerid){
    PlayerTextDrawHide(playerid, UseButton[playerid]);
    PlayerTextDrawHide(playerid, InfoButton[playerid]);
    PlayerTextDrawDestroy(playerid, UseButton[playerid]);
    PlayerTextDrawDestroy(playerid, InfoButton[playerid]);
    PlayerShowButton[playerid] = false;
    return 1;
}

OnPlayerInventory_Close(playerid){

    for(new i=0; i!=MAX_INVENTORYTEXTDRAW; i++){
        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, PlayerInventoryTextDraw[playerid][i]);
    }

    for (new i=0; i<PlayerSlotInventoryCount[playerid]; i++){
  		PlayerTextDrawHide(playerid, PlayerSlotInventoryTextDraw[playerid][i]);
		PlayerTextDrawDestroy(playerid, PlayerSlotInventoryTextDraw[playerid][i]);
    }

    RemoveUseInfoButton(playerid);

    if(PlayerVicinity[playerid]){
        for(new i=0; i<MAX_VICINITYTEXTDRAW; i++){
            PlayerTextDrawHide(playerid, PlayerVicinityTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerVicinityTextDraw[playerid][i]);
        }

        for (new i=0; i<PlayerSlotVicinityCount[playerid]; i++){
            PlayerTextDrawHide(playerid, PlayerSlotVicinityTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerSlotVicinityTextDraw[playerid][i]);
        }
    }

    for(new i=0; i<MAX_VICINITY; i++){
        PlayerNearestItems[playerid][i] = -1;
    }

    if(PlayerCharacterShow[playerid]){
        for(new i=0; i<MAX_CHARTEXT; i++){
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerCharacterTextDraw[playerid][i]);
        }
        PlayerCharacterShow[playerid] = false;
    }
    

    PlayerVicinity[playerid] = false;
    PlayerSlotVicinityCount[playerid] = 0;

    PlayerInventoryStatus[playerid] = false;
    PlayerSlotInventoryCount[playerid] = 0;
    PlayerInvListItemRows[playerid] = -1;
    PlayerInvListItemColumn[playerid] = -1;
    PlayerGetIndexSlotItem[playerid] = -1;
    PlayerGetIndexNextSlotItem[playerid] = -1;
    PlayerInvListItemRowsOld[playerid] = -1;
    PlayerInvListItemColumnOld[playerid] = -1;
    PlayerInventoryType[playerid] = INVENTORY_TYPE;
    PlayerInventoryDropInput[playerid] = false;
    PlayerInventoryLastPage[playerid] = 0;
    PlayerCantSelectTextDraw[playerid] = false;
    CancelSelectTextDraw(playerid);
    TogglePlayerControllable(playerid, 1);
    return true;
}

forward Dropped_Load();
public Dropped_Load(){
	static
	    rows;

	new string[128];

    cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if (i < MAX_DROPPED_ITEMS){
 		cache_get_value_name_int(i, "ID", Drop_Data[i][droppedID]);

		cache_get_value_name(i, "itemName", Drop_Data[i][droppedItem], 64);

		cache_get_value_name_int(i, "itemModel", Drop_Data[i][droppedModel]);
	 	cache_get_value_name_int(i, "itemQuantity", Drop_Data[i][droppedQuantity]);
        cache_get_value_name_int(i, "itemAmmo", Drop_Data[i][droppedAmmo]);
	 	cache_get_value_name_float(i, "itemX", Drop_Data[i][droppedPos][0]);
	 	cache_get_value_name_float(i, "itemY", Drop_Data[i][droppedPos][1]);
		cache_get_value_name_float(i, "itemZ", Drop_Data[i][droppedPos][2]);
	 	cache_get_value_name_int(i, "itemInt", Drop_Data[i][droppedInt]);
	 	cache_get_value_name_int(i, "itemWorld", Drop_Data[i][droppedWorld]);
        cache_get_value_name_int(i, "itemLevel", Drop_Data[i][droppedWeaponLevel]);

        if(Drop_Data[i][droppedModel] >= 400 && Drop_Data[i][droppedModel] <= 611){
            Drop_Data[i][droppedObject] = CreateDynamicObjectEx(18631, Drop_Data[i][droppedPos][0], Drop_Data[i][droppedPos][1], Drop_Data[i][droppedPos][2], 0.0, 0.0, 0.0, Drop_Data[i][droppedWorld], Drop_Data[i][droppedInt]);
        }
        else if(Drop_Data[i][droppedModel] == 1608){
            Drop_Data[i][droppedObject] = CreateDynamicObjectEx(18631, Drop_Data[i][droppedPos][0], Drop_Data[i][droppedPos][1], Drop_Data[i][droppedPos][2], 0.0, 0.0, 0.0, Drop_Data[i][droppedWorld], Drop_Data[i][droppedInt]);
        }
		else{
            Drop_Data[i][droppedObject] = CreateDynamicObjectEx(Drop_Data[i][droppedModel], Drop_Data[i][droppedPos][0], Drop_Data[i][droppedPos][1], Drop_Data[i][droppedPos][2], 0.0, 0.0, 0.0, Drop_Data[i][droppedWorld], Drop_Data[i][droppedInt]);
        }

        if(CheckItemIsWeapon(Drop_Data[i][droppedItem]) != -1){
            format(string, sizeof(string), "%s (Level: %d)", Drop_Data[i][droppedItem], Drop_Data[i][droppedWeaponLevel]);
        }
        else{
            if(Drop_Data[i][droppedQuantity] == 1)
                format(string, sizeof(string), "%s", Drop_Data[i][droppedItem]);
            else if(Drop_Data[i][droppedQuantity] > 1)
                format(string, sizeof(string), "%s (%s)", Drop_Data[i][droppedItem], FormatNumberNotMoney(Drop_Data[i][droppedQuantity]));
        } 
        
		Drop_Data[i][droppedText3D] = CreateDynamic3DTextLabel(string, DROP_COLOR, Drop_Data[i][droppedPos][0], Drop_Data[i][droppedPos][1], Drop_Data[i][droppedPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Drop_Data[i][droppedWorld], Drop_Data[i][droppedInt]);
        Iter_Add(Iter_DropItem, i);
    }
	printf("(( [MYSQL]: Load %d ItemDrop Successfully ))", Iter_Count(Iter_DropItem));
	return 1;
}

ItemDrop_Refresh(itemid){
    if (itemid != -1 && Iter_Contains(Iter_DropItem, itemid)){
        new string[128];

        if(CheckItemIsWeapon(Drop_Data[itemid][droppedItem]) != -1){
            format(string, sizeof(string), "%s (Level: %d)", Drop_Data[itemid][droppedItem], Drop_Data[itemid][droppedWeaponLevel]);
        }
        else{
            if(Drop_Data[itemid][droppedQuantity] == 1)
                format(string, sizeof(string), "%s", Drop_Data[itemid][droppedItem]);
            else if(Drop_Data[itemid][droppedQuantity] > 1)
                format(string, sizeof(string), "%s (%s)", Drop_Data[itemid][droppedItem], FormatNumberNotMoney(Drop_Data[itemid][droppedQuantity]));
        }   

        UpdateDynamic3DTextLabelText(Drop_Data[itemid][droppedText3D], DROP_COLOR, string);
    }
    return 1;
}

CMD:destroyitem(playerid, params[]){
	static
	    id = -1;

    if (PlayerData[playerid][pAdmin] < 1337)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้รับอรุญาติให้ใช้คำสั่งนี้!");

	if ((id = DropItem_Nearest(playerid)) == -1)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้อยู่ใกล้ไอเท็มใดๆ.");

    SendClientMessageEx(playerid, -1, "คุณได้ทำลายไอเท็ม \"%s\" เรียบร้อยแล้ว.", Drop_Data[id][droppedItem]);
    ItemVicinity_Delete(id, Drop_Data[id][droppedQuantity]);
    return 1;
}

CMD:destroyitemall(playerid, params[]){
    if(PlayerData[playerid][pAdmin] < 1339)
        return 0;

    for (new i = 0; i < MAX_DROPPED_ITEMS; i ++) if (Drop_Data[i][droppedModel]){
	    ItemVicinity_Delete(i, Drop_Data[i][droppedQuantity]);
	}
    new string[128];

    format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการลบไอเท็มบนพื้นทั้งหมดของเซิฟเวอร์แล้ว", ReturnRoleplayName(playerid));
    SendAdminsMessage(1, COLOR_YELLOW, string);
	return 1;
}

CMD:weaponlist(playerid, params[]){
    if (PlayerData[playerid][pAdmin] < 1337)
	    return 1;

	static
	    string[1024];

	if (!strlen(string)) {
		for (new i = 0; i < sizeof(WeaponData); i ++) {
			format(string, sizeof(string), "%s[%d] %s [Model:%d]\n", string, i, WeaponData[i][weaponName], WeaponData[i][weaponModel]);
		}
	}
	return Dialog_ShowEasy(playerid, Dialog_ShowEasy, DIALOG_STYLE_LIST, "[รายชื่ออาวุธทั้งหมด]", string, "ปิด", "");
}

CMD:itemlist(playerid, params[]){
    if (PlayerData[playerid][pAdmin] < 1337)
	    return 1;

	static
	    string[1024];

	if (!strlen(string)) {
		for (new i = 0; i < sizeof(Item_Data); i ++) {
			format(string, sizeof(string), "%s%s\n", string, Item_Data[i][itemName]);
		}
	}
	return Dialog_ShowEasy(playerid, Dialog_ShowEasy, DIALOG_STYLE_LIST, "[รายชื่อไอเท็มทั้งหมด]", string, "ปิด", "");
}

CMD:spawnhat(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new modelid;
    if(sscanf(params, "d", modelid)) return SystemMsg(playerid, "/spawnhat [modelid]");
	new Float:x, Float:y, Float:z, Float:ang;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

    for (new i = 0; i < MAX_ACC; i ++) if (modelid == HatDataItem[i][hatitemModel]){
	    new id = Drop_Item(HatDataItem[i][hatitemName], HatDataItem[i][hatitemModel], 1, 0, 0, x, y, z - 0.9, ang, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
        Log_Write("logs/dropitems.txt", "[%s] %s Drop Item %s", ReturnDate(), ReturnName(playerid), HatDataItem[i][hatitemName]);

	    if (id == -1) return SendClientMessage(playerid, -1, "ไอเท็มเต็มเซิฟเวอร์แล้ว.");
		SendClientMessageEx(playerid, -1, "คุณได้สร้างไอเท็ม \"%s\" เรียบร้อยแล้ว", HatDataItem[i][hatitemName]);
		Streamer_Update(playerid);
		return 1;
	}
    SendClientMessage(playerid, -1, "ไม่พบไอเท็ม");
    return 1;
}

CMD:spawnglasses(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new modelid;
    if(sscanf(params, "d", modelid)) return SystemMsg(playerid, "/spawnhat [modelid]");
	new Float:x, Float:y, Float:z, Float:ang;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

    for (new i = 0; i < MAX_ACC; i ++) if (modelid == GlassesDataItem[i][glassesitemModel]){
	    new id = Drop_Item(GlassesDataItem[i][glassesitemName], GlassesDataItem[i][glassesitemModel], 1, 0, 0, x, y, z - 0.9, ang, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
        Log_Write("logs/dropitems.txt", "[%s] %s Drop Item %s", ReturnDate(), ReturnName(playerid), GlassesDataItem[i][glassesitemName]);

	    if (id == -1) return SendClientMessage(playerid, -1, "ไอเท็มเต็มเซิฟเวอร์แล้ว.");
		SendClientMessageEx(playerid, -1, "คุณได้สร้างไอเท็ม \"%s\" เรียบร้อยแล้ว", GlassesDataItem[i][glassesitemName]);
		Streamer_Update(playerid);
		return 1;
	}
    SendClientMessage(playerid, -1, "ไม่พบไอเท็ม");
    return 1;
}

CMD:spawnbody(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new modelid;
    if(sscanf(params, "d", modelid)) return SystemMsg(playerid, "/spawnhat [modelid]");
	new Float:x, Float:y, Float:z, Float:ang;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

    for (new i = 0; i < MAX_ACC; i ++) if (modelid == BodyDataItem[i][bodyitemModel]){
	    new id = Drop_Item(BodyDataItem[i][bodyitemName], BodyDataItem[i][bodyitemModel], 1, 0, 0, x, y, z - 0.9, ang, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
        Log_Write("logs/dropitems.txt", "[%s] %s Drop Item %s", ReturnDate(), ReturnName(playerid), BodyDataItem[i][bodyitemName]);

	    if (id == -1) return SendClientMessage(playerid, -1, "ไอเท็มเต็มเซิฟเวอร์แล้ว.");
		SendClientMessageEx(playerid, -1, "คุณได้สร้างไอเท็ม \"%s\" เรียบร้อยแล้ว", BodyDataItem[i][bodyitemName]);
		Streamer_Update(playerid);
		return 1;
	}
    SendClientMessage(playerid, -1, "ไม่พบไอเท็ม");
    return 1;
}

CMD:spawnhands(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new modelid;
    if(sscanf(params, "d", modelid)) return SystemMsg(playerid, "/spawnhat [modelid]");
	new Float:x, Float:y, Float:z, Float:ang;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

    for (new i = 0; i < MAX_ACC; i ++) if (modelid == HandsDataItem[i][handsitemModel]){
	    new id = Drop_Item(HandsDataItem[i][handsitemName], HandsDataItem[i][handsitemModel], 1, 0, 0, x, y, z - 0.9, ang, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
        Log_Write("logs/dropitems.txt", "[%s] %s Drop Item %s", ReturnDate(), ReturnName(playerid), HandsDataItem[i][handsitemName]);

	    if (id == -1) return SendClientMessage(playerid, -1, "ไอเท็มเต็มเซิฟเวอร์แล้ว.");
		SendClientMessageEx(playerid, -1, "คุณได้สร้างไอเท็ม \"%s\" เรียบร้อยแล้ว", HandsDataItem[i][handsitemName]);
		Streamer_Update(playerid);
		return 1;
	}
    SendClientMessage(playerid, -1, "ไม่พบไอเท็ม");
    return 1;
}

CMD:spawnitem(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    if (isnull(params)) return SendClientMessage(playerid, -1, "/spawnitem [item name]");

	new Float:x, Float:y, Float:z, Float:ang;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

    for (new i = 0; i < sizeof(Item_Data); i ++) if (!strcmp(Item_Data[i][itemName], params, true)){
	    new id = Drop_Item(Item_Data[i][itemName], Item_Data[i][itemModel], 1, 0, 0, x, y, z - 0.9, ang, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
        Log_Write("logs/dropitems.txt", "[%s] %s Drop Item %s", ReturnDate(), ReturnName(playerid), Item_Data[i][itemName]);

	    if (id == -1) return SendClientMessage(playerid, -1, "ไอเท็มเต็มเซิฟเวอร์แล้ว.");
		SendClientMessageEx(playerid, -1, "คุณได้สร้างไอเท็ม \"%s\" เรียบร้อยแล้ว", Item_Data[i][itemName]);
		Streamer_Update(playerid);
		return 1;
	}
    SendClientMessage(playerid, -1, "ไม่มีไอเท็มชื่อนี้");
	return 1;
}

CMD:setquan(playerid, params[]){
	static id = -1, amount;
    if (PlayerData[playerid][pAdmin] < 1338) return SendClientMessage(playerid, -1, "คุณไม่ได้รับอรุญาติให้ใช้คำสั่งนี้!");
	if ((id = DropItem_Nearest(playerid)) == -1) return SendClientMessage(playerid, -1, "ไม่มีไอเท็มอยู่ใกล้คุณ.");
	if (sscanf(params, "d", amount)) return SendClientMessage(playerid, -1, "/setquan [amount]");
	if (amount < 1) return SendClientMessage(playerid, -1, "จำนวนต้องมากกว่า 1.");
    DropItem_SetQuantity(id, amount);
    ItemDrop_Refresh(id);
    SendClientMessageEx(playerid, -1, "คุณได้ปรับจำนวนชิ้นของไอเท็ม \"%s\" เป็น %d.", Drop_Data[id][droppedItem], amount);
    return 1;
}

CMD:spawnskin(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 1338)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้รับอรุญาติให้ใช้คำสั่งนี้!");

	if (isnull(params))
	    return SendClientMessage(playerid, -1, "/spawnskin [skinid]");

	new
		Float:x,
		Float:y,
		Float:z,
		Float:ang;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

    new skinid = strval(params);
    if(skinid < 0 || skinid > 311)
        return ErrorMsg(playerid, "ไอดีสกินที่กรอกไม่ถูกต้อง");

    new id = Drop_Item(params, 2384, 1, 0, 0, x, y, z - 0.9, ang, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

    if (id == -1) return SendClientMessage(playerid, -1, "ไอเท็มเต็มเซิฟเวอร์แล้ว.");

    SendClientMessageEx(playerid, -1, "คุณได้สร้างสกิน \"%s\" เรียบร้อยแล้ว (ใช้ /setquan เพื่อปรับจำนวน).", params);
    Streamer_Update(playerid);
	return 1;
}

CMD:spawnweapon(playerid, params[]){
    if (PlayerData[playerid][pAdmin] < 1338)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้รับอรุญาติให้ใช้คำสั่งนี้!");

	if (isnull(params))
	    return SendClientMessage(playerid, -1, "/spawnweapon [weaponname]");

	new
		Float:x,
		Float:y,
		Float:z,
		Float:ang;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

    for (new i = 0; i < sizeof(WeaponData); i ++) if (!strcmp(WeaponData[i][weaponName], params, true)){
	    new id = Drop_Item(WeaponData[i][weaponName], WeaponData[i][weaponModel], 1, 0, 0, x, y, z - 0.9, ang, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

	    if (id == -1)
	        return SendClientMessage(playerid, -1, "ไอเท็มเต็มเซิฟเวอร์แล้ว.");

		SendClientMessageEx(playerid, -1, "คุณได้สร้างไอเท็ม \"%s\" เรียบร้อยแล้ว", WeaponData[i][weaponName]);

		Streamer_Update(playerid);
		return 1;
	}
	return 1;
}

CMD:setlevelweapon(playerid, params[]){
	static
	    id = -1,
		amount,
        string[128];

    if (PlayerData[playerid][pAdmin] < 1337)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้รับอรุญาติให้ใช้คำสั่งนี้!");

	if ((id = DropItem_Nearest(playerid)) == -1)
	    return SendClientMessage(playerid, -1, "ไม่มีไอเท็มอยู่ใกล้คุณ.");

    if(CheckItemIsWeapon(Drop_Data[id][droppedItem]) != 1)
        return ErrorMsg(playerid, "ไอเท็มนี้ไม่ใช่อาวุธ");

	if (sscanf(params, "d", amount))
	    return SendClientMessage(playerid, -1, "/setlevelweapon [level]");

	if (amount < 0)
	    return SendClientMessage(playerid, -1, "จำนวนต้องมากกว่าหรือเท่ากับ 0.");

    Drop_Data[id][droppedWeaponLevel] = amount;
    format(string, sizeof(string), "UPDATE `dropped` SET `itemLevel` = %d WHERE `ID` = '%d'", amount, Drop_Data[id][droppedID]);
    mysql_tquery(dbCon, string);
    ItemDrop_Refresh(id);
    SendClientMessageEx(playerid, -1, "คุณได้ปรับเลเวลอาวุธ \"%s\" เป็น %d.", Drop_Data[id][droppedItem], amount);
    return 1;
}

CMD:setammo(playerid, params[]){
	static
	    id = -1,
		amount,
        string[128];

    if (PlayerData[playerid][pAdmin] < 1337)
	    return SendClientMessage(playerid, -1, "คุณไม่ได้รับอรุญาติให้ใช้คำสั่งนี้!");

	if ((id = DropItem_Nearest(playerid)) == -1)
	    return SendClientMessage(playerid, -1, "ไม่มีไอเท็มอยู่ใกล้คุณ.");

    if(CheckItemIsWeapon(Drop_Data[id][droppedItem]) != 1)
        return ErrorMsg(playerid, "ไอเท็มนี้ไม่ใช่อาวุธ");

	if (sscanf(params, "d", amount))
	    return SendClientMessage(playerid, -1, "/setammo [amount]");

	if (amount < 0)
	    return SendClientMessage(playerid, -1, "จำนวนต้องมากกว่าหรือเท่ากับ 0.");

    Drop_Data[id][droppedAmmo] = amount;
    format(string, sizeof(string), "UPDATE `dropped` SET `itemAmmo` = %d WHERE `ID` = '%d'", amount, Drop_Data[id][droppedID]);
    mysql_tquery(dbCon, string);
    ItemDrop_Refresh(id);
    SendClientMessageEx(playerid, -1, "คุณได้ปรับจำนวนกระสุนของอาวุธ \"%s\" เป็น %d.", Drop_Data[id][droppedItem], amount);
    return 1;
}

DropItem_Nearest(playerid){
    for (new i = 0; i != MAX_DROPPED_ITEMS; i ++) if (Drop_Data[i][droppedModel] && IsPlayerInRangeOfPoint(playerid, 2.0, Drop_Data[i][droppedPos][0], Drop_Data[i][droppedPos][1], Drop_Data[i][droppedPos][2])){
	    if (GetPlayerInterior(playerid) == Drop_Data[i][droppedInt] && GetPlayerVirtualWorld(playerid) == Drop_Data[i][droppedWorld])
			return i;
	}
	return -1;
}

DropItem_SetQuantity(itemid, amount){
	if(itemid != -1 && Iter_Contains(Iter_DropItem, itemid)){
        new string[128];
	    Drop_Data[itemid][droppedQuantity] = amount;
        format(string, sizeof(string), "UPDATE `dropped` SET `itemQuantity` = %d WHERE `ID` = '%d'", amount, Drop_Data[itemid][droppedID]);
        mysql_tquery(dbCon, string);
	}
	return 1;
}

PlayerInventory_GetItemID(playerid, const item[]){
    for(new i=0; i<MAX_INVENTORYPLAYERS; i++){
        if(!Inventory_Player[playerid][i][itemHave]) continue;
        if(!strcmp(Inventory_Player[playerid][i][itemName], item, true)) {
            if(Inventory_Player[playerid][i][itemQuantity] < PlayerData[playerid][pItemAmount]){
                return i;
            }
        }

        if(i >= 107) break;
    }
    return -1;
}

PlayerInventory_AllCount(playerid, const item[]){
    new count = 0;
    for(new i=0; i<MAX_INVENTORYPLAYERS; i++){
        if(!Inventory_Player[playerid][i][itemHave]) continue;
        if(!strcmp(Inventory_Player[playerid][i][itemName], item, true)){
            count += Inventory_Player[playerid][i][itemQuantity];
        }
        if(i >= 107) break;
    }
    return count;
}

PlayerInventory_Count(playerid, const item[]){
    new itemid = PlayerInventory_GetItemID(playerid, item);
    if(itemid != -1) return Inventory_Player[playerid][itemid][itemQuantity];
    return 0;
}

PlayerInventory_CountEx(playerid, itemid){
    if(itemid != -1) return Inventory_Player[playerid][itemid][itemQuantity];
    return 0;
}

PlayerInventory_Items(playerid){
    new count;
    for(new i=0; i<MAX_INVENTORYPLAYERS; i++){
        if(!Inventory_Player[playerid][i][itemID]) continue;
        count++;

        if(i >= 107) break;

    }
    return count;
}

PlayerInventory_GetFreeID(playerid){
    for(new i=0; i<PlayerData[playerid][pMaxItem]; i++){
        if(Inventory_Player[playerid][i][itemSlot] != -1) continue;
        else return i;
    }
    return -1;
}

stock PlayerInventory_Weights(playerid){
    new Float:weight;
    for(new i=0; i<PlayerData[playerid][pMaxItem]; i++){
        if(!Inventory_Player[playerid][i][itemHave]) continue;
        if(CheckItemIsWeapon(Inventory_Player[playerid][i][itemName]) != -1){
            for(new j=0; j<sizeof(WeaponData); j++){
                if(!strcmp(WeaponData[j][weaponName], Inventory_Player[playerid][i][itemName], true)){
                    weight += WeaponData[j][weaponWeight] * Inventory_Player[playerid][i][itemQuantity];
                }
            }
        }
        else{
            for(new j=0; j<sizeof(Item_Data); j++){
                if(!strcmp(Item_Data[j][itemName], Inventory_Player[playerid][i][itemName], true)){
                    weight += Item_Data[j][itemWeight] * Inventory_Player[playerid][i][itemQuantity];
                }
            }
        }
    }
    PlayerInvWeightTemp[playerid] = weight;
    return 1;
}

CMD:checkitem(playerid, params[]){
    new modelid;
    if(sscanf(params, "d", modelid)) return 1;
    SendClientMessageEx(playerid, -1, "%s", Item_Data[CheckItemModelIsName(modelid)][itemName]);
    return 1;
}

CheckItemModelIsName(modelid){
    for (new i = 0; i < sizeof(Item_Data); i ++){
        if(modelid == Item_Data[i][itemModel]){
            return i;
        }
    }
    return -1;
}

CheckItemIsGun(const item[]){
    if (!strcmp(item, "M4A1", true)) return 1;
    else if(!strcmp(item, "Clot 45")) return 1;
    return -1;
}

CheckItemIsWeapon(const item[]){
    for (new i = 0; i < sizeof(WeaponData); i ++) if (!strcmp(WeaponData[i][weaponName], item, true)){
        return 1;
    }
    return -1;
}

PlayerInventory_HasItem(playerid, const item[]){
	return (PlayerInventory_GetItemID(playerid, item) != -1);
}

PlayerInventory_AddItem(playerid, const item[], model = MODEL_NULL, amount = 1, ammo = 0, level = 0){
    new itemid = -1, string[256];
    PlayerInventory_Weights(playerid);
    if(PlayerInvWeightTemp[playerid] > PlayerData[playerid][pInvMaxWeight]) return -1;
    if(PlayerInventory_Count(playerid, item) + amount > PlayerData[playerid][pItemAmount]){
        //printf("Max");
        if(amount > PlayerData[playerid][pItemAmount]) {
            new newamount = amount - PlayerData[playerid][pItemAmount];
            new checkitem = PlayerInventory_GetItemID(playerid, item);
            if(checkitem != -1){
                new amountsplit = (amount + Inventory_Player[playerid][checkitem][itemQuantity]);
                if(amountsplit <= PlayerData[playerid][pItemAmount]){
                    //printf("Update '%s' amount '%d' To Slot '%d'", item, amount, checkitem);
                    Inventory_Player[playerid][checkitem][itemQuantity] += amount;
                    mysql_format(dbCon, string, sizeof(string), "UPDATE `inventory` SET `itemQuantity` = %d WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", Inventory_Player[playerid][checkitem][itemQuantity], PlayerData[playerid][pID], Inventory_Player[playerid][checkitem][itemID]);
                    mysql_tquery(dbCon, string);
                    Log_Write("logs/additems.txt", "[%s] Update %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][checkitem][itemName], Inventory_Player[playerid][checkitem][itemLevel], amount, Inventory_Player[playerid][checkitem][itemQuantity]);
                    if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, checkitem);
                }
                else{
                    new amountnew = (Inventory_Player[playerid][checkitem][itemQuantity] + amount) - PlayerData[playerid][pItemAmount];
                    //printf("Update '%s' amount '%d' To Slot '%d'", item, amount, checkitem);
                    Inventory_Player[playerid][checkitem][itemQuantity] = PlayerData[playerid][pItemAmount];
                    mysql_format(dbCon, string, sizeof(string), "UPDATE `inventory` SET `itemQuantity` = %d WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", Inventory_Player[playerid][checkitem][itemQuantity], PlayerData[playerid][pID], Inventory_Player[playerid][checkitem][itemID]);
                    mysql_tquery(dbCon, string);
                    Log_Write("logs/additems.txt", "[%s] Update %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][checkitem][itemName], Inventory_Player[playerid][checkitem][itemLevel], amount, Inventory_Player[playerid][checkitem][itemQuantity]);
                    if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, checkitem);

                    itemid = PlayerInventory_GetFreeID(playerid);
                    if(itemid != -1){
                        //printf("Add '%s' amount '%d' To SecondSlotSpecial '%d'", item, amountnew, itemid);
                        Inventory_Player[playerid][itemid][itemHave] = true;
                        Inventory_Player[playerid][itemid][itemKey] = model;
                        Inventory_Player[playerid][itemid][itemQuantity] = amountnew;
                        Inventory_Player[playerid][itemid][itemLevel] = level;
                        Inventory_Player[playerid][itemid][itemAmmo] = ammo;
                        Inventory_Player[playerid][itemid][itemSlot] = itemid;
                        format(Inventory_Player[playerid][itemid][itemName], 64, item);
                        mysql_format(dbCon, string, sizeof(string), "INSERT INTO `inventory` (`itemOwner`, `itemName`, `itemKey`, `itemQuantity`, `itemLevel`, `itemAmmo`, `itemSlot`) VALUES ('%d', '%e', '%d', '%d', '%d', '%d', '%d')", PlayerData[playerid][pID], item, model, amountnew, level, ammo, itemid);
                        mysql_tquery(dbCon, string, "OnInventory_Add", "dd", playerid, itemid);
                        Log_Write("logs/additems.txt", "[%s] Add %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemLevel], amountnew, Inventory_Player[playerid][itemid][itemQuantity]);
                        if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, itemid);
                        return itemid;
                    }
                }
            }
            else{
                new itemid1 = -1, itemid2 = -1;
                itemid1 = PlayerInventory_GetFreeID(playerid);
                if(itemid1 != -1) Inventory_Player[playerid][itemid1][itemHave] = true;
                itemid2 = PlayerInventory_GetFreeID(playerid);
                if(itemid1 != -1){
                    //printf("Add '%s' amount '%d' To Slot '%d'", item, amount, itemid1);
                    Inventory_Player[playerid][itemid1][itemKey] = model;
                    Inventory_Player[playerid][itemid1][itemQuantity] = PlayerData[playerid][pItemAmount];
                    Inventory_Player[playerid][itemid1][itemLevel] = level;
                    Inventory_Player[playerid][itemid1][itemAmmo] = ammo;
                    Inventory_Player[playerid][itemid1][itemSlot] = itemid1;
                    format(Inventory_Player[playerid][itemid1][itemName], 64, item);
                    mysql_format(dbCon, string, sizeof(string), "INSERT INTO `inventory` (`itemOwner`, `itemName`, `itemKey`, `itemQuantity`, `itemLevel`, `itemAmmo`, `itemSlot`) VALUES ('%d', '%e', '%d', '%d', '%d', '%d', '%d')", PlayerData[playerid][pID], item, model, PlayerData[playerid][pItemAmount], level, ammo, itemid1);
                    mysql_tquery(dbCon, string, "OnInventory_Add", "dd", playerid, itemid1);
                    Log_Write("logs/additems.txt", "[%s] Add %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][itemid1][itemName], Inventory_Player[playerid][itemid1][itemLevel], amount, Inventory_Player[playerid][itemid1][itemQuantity]);
                    if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, itemid1);
                    if(itemid2 == -1) return itemid1;
                }
                if(itemid2 != -1){
                    //printf("Add '%s' amount '%d' To SecondSlot '%d'", item, newamount, itemid2);
                    Inventory_Player[playerid][itemid2][itemHave] = true;
                    Inventory_Player[playerid][itemid2][itemKey] = model;
                    Inventory_Player[playerid][itemid2][itemQuantity] = newamount;
                    Inventory_Player[playerid][itemid2][itemLevel] = level;
                    Inventory_Player[playerid][itemid2][itemAmmo] = ammo;
                    Inventory_Player[playerid][itemid2][itemSlot] = itemid2;
                    format(Inventory_Player[playerid][itemid2][itemName], 64, item);
                    mysql_format(dbCon, string, sizeof(string), "INSERT INTO `inventory` (`itemOwner`, `itemName`, `itemKey`, `itemQuantity`, `itemLevel`, `itemAmmo`, `itemSlot`) VALUES ('%d', '%e', '%d', '%d', '%d', '%d', '%d')", PlayerData[playerid][pID], item, model, newamount, level, ammo, itemid2);
                    mysql_tquery(dbCon, string, "OnInventory_Add", "dd", playerid, itemid2);
                    Log_Write("logs/additems.txt", "[%s] Add %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][itemid2][itemName], Inventory_Player[playerid][itemid2][itemLevel], newamount, Inventory_Player[playerid][itemid2][itemQuantity]);
                    if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, itemid2);
                    return itemid2;
                }
            }
            return -1;
        }
        else {
            new checkitem = PlayerInventory_GetItemID(playerid, item);
            if(checkitem != -1){
                new amountsplit = (amount + Inventory_Player[playerid][checkitem][itemQuantity]);
                if(amountsplit <= PlayerData[playerid][pItemAmount]){
                    //printf("Update '%s' amount '%d' To Slot '%d'", item, amount, checkitem);
                    Inventory_Player[playerid][checkitem][itemQuantity] += amount;
                    mysql_format(dbCon, string, sizeof(string), "UPDATE `inventory` SET `itemQuantity` = %d WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", Inventory_Player[playerid][checkitem][itemQuantity], PlayerData[playerid][pID], Inventory_Player[playerid][checkitem][itemID]);
                    mysql_tquery(dbCon, string);
                    Log_Write("logs/additems.txt", "[%s] Update %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][checkitem][itemName], Inventory_Player[playerid][checkitem][itemLevel], amount, Inventory_Player[playerid][checkitem][itemQuantity]);
                    if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, checkitem);
                }
                else{
                    new amountnew = (Inventory_Player[playerid][checkitem][itemQuantity] + amount) - PlayerData[playerid][pItemAmount];
                    //printf("Update '%s' amount '%d' To Slot '%d'", item, amount, checkitem);
                    Inventory_Player[playerid][checkitem][itemQuantity] = PlayerData[playerid][pItemAmount];
                    mysql_format(dbCon, string, sizeof(string), "UPDATE `inventory` SET `itemQuantity` = %d WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", Inventory_Player[playerid][checkitem][itemQuantity], PlayerData[playerid][pID], Inventory_Player[playerid][checkitem][itemID]);
                    mysql_tquery(dbCon, string);
                    Log_Write("logs/additems.txt", "[%s] Update %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][checkitem][itemName], Inventory_Player[playerid][checkitem][itemLevel], PlayerData[playerid][pItemAmount], Inventory_Player[playerid][checkitem][itemQuantity]);
                    if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, checkitem);

                    itemid = PlayerInventory_GetFreeID(playerid);
                    if(itemid != -1){
                        //printf("Add '%s' amount '%d' To SecondSlotSpecial '%d'", item, amountnew, itemid);
                        Inventory_Player[playerid][itemid][itemHave] = true;
                        Inventory_Player[playerid][itemid][itemKey] = model;
                        Inventory_Player[playerid][itemid][itemQuantity] = amountnew;
                        Inventory_Player[playerid][itemid][itemLevel] = level;
                        Inventory_Player[playerid][itemid][itemAmmo] = ammo;
                        Inventory_Player[playerid][itemid][itemSlot] = itemid;
                        format(Inventory_Player[playerid][itemid][itemName], 64, item);
                        mysql_format(dbCon, string, sizeof(string), "INSERT INTO `inventory` (`itemOwner`, `itemName`, `itemKey`, `itemQuantity`, `itemLevel`, `itemAmmo`, `itemSlot`) VALUES ('%d', '%e', '%d', '%d', '%d', '%d', '%d')", PlayerData[playerid][pID], item, model, amountnew, level, ammo, itemid);
                        mysql_tquery(dbCon, string, "OnInventory_Add", "dd", playerid, itemid);
                        Log_Write("logs/additems.txt", "[%s] Add %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemLevel], amountnew, Inventory_Player[playerid][itemid][itemQuantity]);
                        if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, itemid);
                        return itemid;
                    }
                }
            }
            else{
                itemid = PlayerInventory_GetFreeID(playerid);
                if(itemid != -1){
                    //printf("Add '%s' amount '%d' To Slot '%d'", item, amount, itemid);
                    Inventory_Player[playerid][itemid][itemHave] = true;
                    Inventory_Player[playerid][itemid][itemKey] = model;
                    Inventory_Player[playerid][itemid][itemQuantity] = amount;
                    Inventory_Player[playerid][itemid][itemLevel] = level;
                    Inventory_Player[playerid][itemid][itemAmmo] = ammo;
                    Inventory_Player[playerid][itemid][itemSlot] = itemid;
                    format(Inventory_Player[playerid][itemid][itemName], 64, item);
                    mysql_format(dbCon, string, sizeof(string), "INSERT INTO `inventory` (`itemOwner`, `itemName`, `itemKey`, `itemQuantity`, `itemLevel`, `itemAmmo`, `itemSlot`) VALUES ('%d', '%e', '%d', '%d', '%d', '%d', '%d')", PlayerData[playerid][pID], item, model, amount, level, ammo, itemid);
                    mysql_tquery(dbCon, string, "OnInventory_Add", "dd", playerid, itemid);
                    Log_Write("logs/additems.txt", "[%s] Add %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemLevel], amount, Inventory_Player[playerid][itemid][itemQuantity]);
                    if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, itemid);
                    return itemid;
                }
            }
            return -1;
        }
    }
    else{
        //printf("Not Max");
        if(CheckItemIsWeapon(item) != -1){
            itemid = PlayerInventory_GetFreeID(playerid);
            if(itemid != -1){
                //printf("Add '%s' amount '%d' To Slot '%d'", item, amount, itemid);
                Inventory_Player[playerid][itemid][itemHave] = true;
                Inventory_Player[playerid][itemid][itemKey] = model;
                Inventory_Player[playerid][itemid][itemQuantity] = amount;
                Inventory_Player[playerid][itemid][itemLevel] = level;
                Inventory_Player[playerid][itemid][itemAmmo] = ammo;
                Inventory_Player[playerid][itemid][itemSlot] = itemid;
                format(Inventory_Player[playerid][itemid][itemName], 64, item);
                mysql_format(dbCon, string, sizeof(string), "INSERT INTO `inventory` (`itemOwner`, `itemName`, `itemKey`, `itemQuantity`, `itemLevel`, `itemAmmo`, `itemSlot`) VALUES ('%d', '%e', '%d', '%d', '%d', '%d', '%d')", PlayerData[playerid][pID], item, model, amount, level, ammo, itemid);
                mysql_tquery(dbCon, string, "OnInventory_Add", "dd", playerid, itemid);
                Log_Write("logs/additems.txt", "[%s] Add %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemLevel], amount, Inventory_Player[playerid][itemid][itemQuantity]);
                if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, itemid);
                return itemid;
            }
            return -1;
        }
        else{
            itemid = PlayerInventory_GetItemID(playerid, item);
            if(itemid == -1){
                itemid = PlayerInventory_GetFreeID(playerid);
                if(itemid != -1){
                    //printf("Add '%s' amount '%d' To Slot '%d'", item, amount, itemid);
                    Inventory_Player[playerid][itemid][itemHave] = true;
                    Inventory_Player[playerid][itemid][itemKey] = model;
                    Inventory_Player[playerid][itemid][itemQuantity] = amount;
                    Inventory_Player[playerid][itemid][itemLevel] = level;
                    Inventory_Player[playerid][itemid][itemAmmo] = ammo;
                    Inventory_Player[playerid][itemid][itemSlot] = itemid;
                    format(Inventory_Player[playerid][itemid][itemName], 64, item);
                    mysql_format(dbCon, string, sizeof(string), "INSERT INTO `inventory` (`itemOwner`, `itemName`, `itemKey`, `itemQuantity`, `itemLevel`, `itemAmmo`, `itemSlot`) VALUES ('%d', '%e', '%d', '%d', '%d', '%d', '%d')", PlayerData[playerid][pID], item, model, amount, level, ammo, itemid);
                    mysql_tquery(dbCon, string, "OnInventory_Add", "dd", playerid, itemid);
                    Log_Write("logs/additems.txt", "[%s] Add %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemLevel], amount, Inventory_Player[playerid][itemid][itemQuantity]);
                    if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, itemid);
                    return itemid;
                }
                return -1;
            }
            else{
                //printf("Update '%s' amount '%d' To Slot '%d'", item, amount, itemid);
                Inventory_Player[playerid][itemid][itemQuantity] += amount;
                mysql_format(dbCon, string, sizeof(string), "UPDATE `inventory` SET `itemQuantity` = `itemQuantity` + %d WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", amount, PlayerData[playerid][pID], Inventory_Player[playerid][itemid][itemID]);
                mysql_tquery(dbCon, string);
                Log_Write("logs/additems.txt", "[%s] Update %s (level: %d) amount %d Total : %d", ReturnDate(), Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemLevel], amount, Inventory_Player[playerid][itemid][itemQuantity]);
                if(PlayerInventoryStatus[playerid]) OnPlayerInventory_PickupSlot(playerid, itemid);
            }
        }
    }
    return itemid;
}

forward OnInventory_Add(playerid, itemid);
public OnInventory_Add(playerid, itemid){
	Inventory_Player[playerid][itemid][itemID] = cache_insert_id();
	return 1;
}

forward OnQuery_Finished(extraid, threadid);
public OnQuery_Finished(extraid, threadid){
	if (!IsPlayerConnected(extraid)) return 0;
	if(!LoggedIn[extraid]) return 0;	
	new rows;

	switch (threadid){
		case THREAD_LOAD_INVENTORY:{
            cache_get_row_count(rows);
            for (new i = 0; i < rows && i < MAX_INVENTORYPLAYERS; i ++) {
                Inventory_Player[extraid][i][itemHave] = true;
                cache_get_value_name_int(i, "itemID", Inventory_Player[extraid][i][itemID]);
                cache_get_value_name_int(i, "itemOwner", Inventory_Player[extraid][i][itemOwner]);
                cache_get_value_name(i, "itemName", Inventory_Player[extraid][i][itemName], 64);
                cache_get_value_name_int(i, "itemKey", Inventory_Player[extraid][i][itemKey]);
                cache_get_value_name_int(i, "itemQuantity", Inventory_Player[extraid][i][itemQuantity]);
                cache_get_value_name_int(i, "itemAmmo", Inventory_Player[extraid][i][itemAmmo]);
                cache_get_value_name_int(i, "itemLevel", Inventory_Player[extraid][i][itemLevel]);
				cache_get_value_name_int(i, "itemSlot", Inventory_Player[extraid][i][itemSlot]);

                if(i >= 107) break;
            }
            ReloadSlotIndexItem(extraid);
		}
	}
	return 1;
}

ReloadSlotIndexItem(playerid){
    printf("[Inventory_Load]: Start Load Inventory %s(%d)", ReturnRoleplayName(playerid), playerid);
    new tempI = -1, j = -1, check = true, checkround = 0;
    new itemHaveEx, itemIDEx, itemNameEx[64], itemKeyEx, itemOwnerEx, itemQuantityEx, itemLevelEx, itemAmmoEx, itemSlotEx;
    while(check && checkround < MAX_INVENTORYPLAYERS){
        new x = 0;
        for(new i=0; i<PlayerData[playerid][pMaxItem]; i++) if(i < MAX_INVENTORYPLAYERS){
            if(Inventory_Player[playerid][i][itemKey] == MODEL_NULL) continue;
            if(Inventory_Player[playerid][i][itemSlot] == -1) continue;

            tempI = i;
            j = Inventory_Player[playerid][tempI][itemSlot];
            if(j != -1 && i != j){
                //เก็บค่าช่องเดิมไว้
                itemHaveEx = Inventory_Player[playerid][j][itemHave];
                itemIDEx = Inventory_Player[playerid][j][itemID];
                format(itemNameEx, 64, Inventory_Player[playerid][j][itemName]);
                itemKeyEx = Inventory_Player[playerid][j][itemKey];
                itemOwnerEx = Inventory_Player[playerid][j][itemOwner];
                itemQuantityEx = Inventory_Player[playerid][j][itemQuantity];
                itemLevelEx = Inventory_Player[playerid][j][itemLevel];
                itemAmmoEx = Inventory_Player[playerid][j][itemAmmo];
                itemSlotEx = Inventory_Player[playerid][j][itemSlot];

                //ทำการเอาช่องเดิมเท่ากับช่องจริง
                Inventory_Player[playerid][j][itemHave] = Inventory_Player[playerid][tempI][itemHave];
                Inventory_Player[playerid][j][itemID] = Inventory_Player[playerid][tempI][itemID];
                format(Inventory_Player[playerid][j][itemName], 64, Inventory_Player[playerid][tempI][itemName]);
                Inventory_Player[playerid][j][itemKey] = Inventory_Player[playerid][tempI][itemKey];
                Inventory_Player[playerid][j][itemOwner] = Inventory_Player[playerid][tempI][itemOwner];
                Inventory_Player[playerid][j][itemQuantity] = Inventory_Player[playerid][tempI][itemQuantity];
                Inventory_Player[playerid][j][itemLevel] = Inventory_Player[playerid][tempI][itemLevel];
                Inventory_Player[playerid][j][itemAmmo] = Inventory_Player[playerid][tempI][itemAmmo];
                Inventory_Player[playerid][j][itemSlot] = Inventory_Player[playerid][tempI][itemSlot];

                //ช่องเดิมของช่องจริงเท่ากับช่องเดิม
                Inventory_Player[playerid][tempI][itemHave] = itemHaveEx;
                Inventory_Player[playerid][tempI][itemID] = itemIDEx;
                format(Inventory_Player[playerid][tempI][itemName], 64, itemNameEx);
                Inventory_Player[playerid][tempI][itemKey] = itemKeyEx;
                Inventory_Player[playerid][tempI][itemOwner] = itemOwnerEx;
                Inventory_Player[playerid][tempI][itemQuantity] = itemQuantityEx;
                Inventory_Player[playerid][tempI][itemLevel] = itemLevelEx;
                Inventory_Player[playerid][tempI][itemAmmo] = itemAmmoEx;
                Inventory_Player[playerid][tempI][itemSlot] = itemSlotEx;
                x++;
            }
        }

        checkround++;
        if(checkround >= 107) check = false;

        if(x > 0) check = true;
        else check = false;
    }

    new query[512];

    format(query, sizeof(query), "SELECT * FROM `inventory` WHERE `itemOwner` = '%d' AND `itemSlot` = -1", PlayerData[playerid][pID]);
    mysql_tquery(dbCon, query, "ReCheckSlotInvalidInventory", "d", playerid);
    printf("[Inventory_Load]: %s(%d) Reload Index Inventory Finish", ReturnRoleplayName(playerid), playerid);
    return 1;
}

forward ReCheckSlotInvalidInventory(playerid);
public ReCheckSlotInvalidInventory(playerid){
    new rows, string[512];
    cache_get_row_count(rows);
    for (new i = 0; i < rows && i < MAX_INVENTORYPLAYERS; i ++) {
        new newitemslot = -1;
        if((newitemslot = PlayerInventory_GetFreeID(playerid)) != -1){
            Inventory_Player[playerid][newitemslot][itemHave] = true;
            cache_get_value_name_int(i, "itemID", Inventory_Player[playerid][newitemslot][itemID]);
            cache_get_value_name_int(i, "itemOwner", Inventory_Player[playerid][newitemslot][itemOwner]);
            cache_get_value_name(i, "itemName", Inventory_Player[playerid][newitemslot][itemName], 64);
            cache_get_value_name_int(i, "itemKey", Inventory_Player[playerid][newitemslot][itemKey]);
            cache_get_value_name_int(i, "itemQuantity", Inventory_Player[playerid][newitemslot][itemQuantity]);
            cache_get_value_name_int(i, "itemAmmo", Inventory_Player[playerid][newitemslot][itemAmmo]);
            cache_get_value_name_int(i, "itemLevel", Inventory_Player[playerid][newitemslot][itemLevel]);
            cache_get_value_name_int(i, "itemSlot", Inventory_Player[playerid][newitemslot][itemSlot]);
            Inventory_Player[playerid][newitemslot][itemSlot] = newitemslot;

            mysql_format(dbCon, string, sizeof(string), "UPDATE `inventory` SET `itemSlot` = %d WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", newitemslot, PlayerData[playerid][pID], Inventory_Player[playerid][newitemslot][itemID]);
            mysql_tquery(dbCon, string);
        }
        if(i >= 107) break;
    }
    format(string, sizeof(string), "SELECT * FROM `tickets` WHERE `ID` = '%d'", PlayerData[playerid][pID]);
	mysql_tquery(dbCon, string, "OnQueryFinished", "dd", playerid, THREAD_LOAD_TICKETS);
    return 1;
}

CMD:reloaditem(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    ReloadSlotIndexItem(playerid);
    return 1;
}

OnPlayerVicinity_Update(playerid){
    for(new i=0; i<MAX_VICINITY; i++){
        PlayerNearestItems[playerid][i] = -1;
    }

    new count = 0;
    foreach(new i : Iter_DropItem) if(Iter_Contains(Iter_DropItem, i) && count < MAX_VICINITY && Drop_Data[i][droppedModel] != MODEL_NULL && IsPlayerInRangeOfPoint(playerid, 1.5, Drop_Data[i][droppedPos][0], Drop_Data[i][droppedPos][1], Drop_Data[i][droppedPos][2]) && GetPlayerInterior(playerid) == Drop_Data[i][droppedInt] && GetPlayerVirtualWorld(playerid) == Drop_Data[i][droppedWorld]){
        PlayerNearestItems[playerid][count] = i;
        count++;
    }

    if(count != 0){
        if(PlayerCharacterShow[playerid]){
            for(new i=0; i<MAX_CHARTEXT; i++){
                PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][i]);
                PlayerTextDrawDestroy(playerid, PlayerCharacterTextDraw[playerid][i]);
            }
            PlayerCharacterShow[playerid] = false;
        }

        if(!PlayerVicinity[playerid]){
            PlayerVicinity[playerid] = true;
            LoadPlayerVicinityTextDraw(playerid);
            LoadPlayerVicinitySlotTextDraw(playerid);
            for(new i=0; i<MAX_VICINITYTEXTDRAW; i++){
                PlayerTextDrawShow(playerid, PlayerVicinityTextDraw[playerid][i]);
            }
        }
        OnPlayerVicinity_Render(playerid);
    }
    else if(count == 0){
        if(PlayerVicinity[playerid]){
            PlayerVicinity[playerid] = false;
            for(new i=0; i<MAX_VICINITYTEXTDRAW; i++){
                PlayerTextDrawHide(playerid, PlayerVicinityTextDraw[playerid][i]);
                PlayerTextDrawDestroy(playerid, PlayerVicinityTextDraw[playerid][i]);
            }

            for (new i=0; i<PlayerSlotVicinityCount[playerid]; i++){
                PlayerTextDrawHide(playerid, PlayerSlotVicinityTextDraw[playerid][i]);
                PlayerTextDrawDestroy(playerid, PlayerSlotVicinityTextDraw[playerid][i]);
            }
            PlayerSlotVicinityCount[playerid] = 0;
        }

        LoadPlayerCharacterTextDraw(playerid);
        for(new i=0; i<MAX_CHARTEXT; i++){
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][i]);
        }
        PlayerCharacterShow[playerid] = true;
        PlayerCharacterTD_Render(playerid);
    }

    return 1;
}

OnPlayerVicinity_Render(playerid){
    new index = 0;
    new string[128];

    for(new i=0; i<MAX_VICINITY_ROWS; i++){
        for(new j=0; j<MAX_VICINITY_COLUMN; j++){
            if(PlayerNearestItems[playerid][index] != -1 && Drop_Data[PlayerNearestItems[playerid][index]][droppedModel] != MODEL_NULL){
                PlayerTextDrawSetPreviewModel(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityModel[playerid][i][j]], Drop_Data[PlayerNearestItems[playerid][index]][droppedModel]);
                PlayerTextDrawSetPreviewRot(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
                PlayerTextDrawShow(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityModel[playerid][i][j]]);
                format(string, sizeof(string), "%s", FormatNumberNotMoney(Drop_Data[PlayerNearestItems[playerid][index]][droppedQuantity]));
                PlayerTextDrawSetString(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityAmount[playerid][i][j]], string);
                PlayerTextDrawShow(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityAmount[playerid][i][j]]);
            }
            else if(PlayerNearestItems[playerid][index] == -1){
                PlayerTextDrawSetPreviewModel(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityModel[playerid][i][j]], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityModel[playerid][i][j]], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityModel[playerid][i][j]]);
                PlayerTextDrawHide(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityAmount[playerid][i][j]]);
            }
            index++;
        }
    }
    return 1;
}

OnPlayerInventory_UpdateCount(playerid){
    new countitem = 0;

    for(new i=0; i<MAX_INVENTORYPLAYERS; i++){
        if(Inventory_Player[playerid][i][itemKey] != MODEL_NULL){
            countitem++;
        }

        if(i >= 107) break;
    }
    new string[128];
    PlayerInventory_Weights(playerid);
    format(string, sizeof string, "Weight: (%.1f/%.1f)", PlayerInvWeightTemp[playerid], PlayerData[playerid][pInvMaxWeight]);
    PlayerTextDrawSetString(playerid, PlayerInventoryTextDraw[playerid][20], string);

    format(string, sizeof string, "%d/%d", countitem, PlayerData[playerid][pMaxItem]);
    PlayerTextDrawSetString(playerid, PlayerInventoryTextDraw[playerid][16], string);
    PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][16]);
    PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][16]);
    return 1;
}

OnPlayerInventory_Render(playerid){
    new slotitem, string[10];

    if(PlayerInventoryPage[playerid] == 1){
        slotitem = 0;
    }
    else if(PlayerInventoryPage[playerid] == 2){
        slotitem = 36;
    }
    else if(PlayerInventoryPage[playerid] == 3){
        slotitem = 72;
    }

    for(new i=0; i<MAX_INV_MENU_ROWS; i++){
        for(new j=0; j<MAX_INV_MENU_COLUMN; j++){
            if(Inventory_Player[playerid][slotitem][itemKey] == MODEL_NULL){
                PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]]);
                PlayerTextDrawHide(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]]);
            }
            else{
                PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], Inventory_Player[playerid][slotitem][itemKey]);
                PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]]);
                if(CheckItemIsWeapon(Inventory_Player[playerid][slotitem][itemName]) != -1) format(string, sizeof(string), "%s", FormatNumberNotMoney(Inventory_Player[playerid][slotitem][itemQuantity]));
                else format(string, sizeof(string), "%s/%d", FormatNumberNotMoney(Inventory_Player[playerid][slotitem][itemQuantity]), PlayerData[playerid][pItemAmount]);
                PlayerTextDrawSetString(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]], string);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]]);
            }
            slotitem++;
        }
    }

    format(string, sizeof(string), "%s", FormatNumber(PlayerData[playerid][pCash]));
    PlayerTextDrawSetString(playerid, PlayerInventoryTextDraw[playerid][11], string);

    format(string, sizeof(string), "%s", FormatNumberNotMoney(AccountData[playerid][uWallet]));
    PlayerTextDrawSetString(playerid, PlayerInventoryTextDraw[playerid][13], string);

    format(string, sizeof(string), "%s", FormatNumber(PlayerData[playerid][pBankMoney]));
    PlayerTextDrawSetString(playerid, PlayerInventoryTextDraw[playerid][15], string);

    format(string, sizeof(string), "%s", FormatNumber(PlayerData[playerid][pRedMoney]));
    PlayerTextDrawSetString(playerid, PlayerInventoryTextDraw[playerid][15], string);

    if(PlayerInventoryType[playerid] == INVENTORY_TYPE || PlayerInventoryType[playerid] == HOME_TYPE){
        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][7]);
        PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][7], PlayerInventoryCodeColor[playerid]);
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][7]);
    }

    if(PlayerInventoryPage[playerid] == 1){

        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][18]);
        PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][18], 1296911871);
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][18]);

        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][19]);
        PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][19], 1296911871);
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][19]);

        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][17]);
        PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][17], PlayerInventoryCodeColor[playerid]);
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][17]);
    }
    else if(PlayerInventoryPage[playerid] == 2){

        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][17]);
        PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][17], 1296911871);
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][17]);

        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][19]);
        PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][19], 1296911871);
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][19]);

        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][18]);
        PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][18], PlayerInventoryCodeColor[playerid]);
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][18]);
    }
    else if(PlayerInventoryPage[playerid] == 3){

        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][17]);
        PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][17], 1296911871);
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][17]);

        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][18]);
        PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][18], 1296911871);
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][18]);

        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][19]);
        PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][19], PlayerInventoryCodeColor[playerid]);
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][19]);
    }
    return 1;
}

OnPlayerInventory_PickupSlot(playerid, itemindex){
    new string[10], slotitem = 0;

    if(PlayerInventoryPage[playerid] == 1){
        slotitem = 0;
    }
    else if(PlayerInventoryPage[playerid] == 2){
        slotitem = 36;
    }
    else if(PlayerInventoryPage[playerid] == 3){
        slotitem = 72;
    }

    for(new i=0; i<MAX_INV_MENU_ROWS; i++){
        for(new j=0; j<MAX_INV_MENU_COLUMN; j++){
            if(itemindex == slotitem){
                PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], Inventory_Player[playerid][slotitem][itemKey]);
                PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]]);
                if(CheckItemIsWeapon(Inventory_Player[playerid][slotitem][itemName]) != -1) format(string, sizeof(string), "%s", FormatNumberNotMoney(Inventory_Player[playerid][slotitem][itemQuantity]));
                else format(string, sizeof(string), "%s/%d", FormatNumberNotMoney(Inventory_Player[playerid][slotitem][itemQuantity]), PlayerData[playerid][pItemAmount]);
                PlayerTextDrawSetString(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]], string);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]]);
            }
            slotitem++;
        }
    }

    if(PlayerInventoryType[playerid] == INVENTORY_TYPE || PlayerInventoryType[playerid] == HOME_TYPE){
        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][7]);
        PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][7], PlayerInventoryCodeColor[playerid]);
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][7]);
    }

    return 1;
}

OnPlayerInventory_UpdateSlot(playerid, slotitem){
    new string[128];
    new i = PlayerInvListItemRows[playerid], j = PlayerInvListItemColumn[playerid];
    if(slotitem != -1){
        if(Inventory_Player[playerid][slotitem][itemKey] == MODEL_NULL){
            if(i != -1 && j != -1){
                PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]]);
                PlayerTextDrawHide(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]]);
            }
        }
        else{
            if(i != -1 && j != -1){
                PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], Inventory_Player[playerid][slotitem][itemKey]);
                PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]]);
                if(CheckItemIsWeapon(Inventory_Player[playerid][slotitem][itemName]) != -1) format(string, sizeof(string), "%s", FormatNumberNotMoney(Inventory_Player[playerid][slotitem][itemQuantity]));
                else format(string, sizeof(string), "%s/%d", FormatNumberNotMoney(Inventory_Player[playerid][slotitem][itemQuantity]), PlayerData[playerid][pItemAmount]);
                PlayerTextDrawSetString(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]], string);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]]);
            }
        }
    }
    return 1;
}

OnPlayerInventory_Update(playerid){
    new slotitem = PlayerGetIndexSlotItem[playerid], slotitemnext = PlayerGetIndexNextSlotItem[playerid];
    new i = PlayerInvListItemRows[playerid], j = PlayerInvListItemColumn[playerid];
    new iold = PlayerInvListItemRowsOld[playerid], jold = PlayerInvListItemColumnOld[playerid];
    new string[10];
    //printf("i = %d | j = %d", i, j);
    if(slotitem != -1 && slotitemnext == -1){
        if(Inventory_Player[playerid][Inventory_Player[playerid][slotitem][itemSlot]][itemKey] == MODEL_NULL){
            if(i != -1 && j != -1){
                //printf("Draw Model Null slotitemold != -1 and slotnextitem == -1");
                PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]]);
                PlayerTextDrawHide(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]]);
            }
        }
        else{
            if(i != -1 && j != -1){
                //printf("Draw Model Not Null slotitemold != -1 and slotnextitem == -1");
                PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], Inventory_Player[playerid][Inventory_Player[playerid][slotitem][itemSlot]][itemKey]);
                PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]]);
                if(CheckItemIsWeapon(Inventory_Player[playerid][slotitem][itemName]) != -1) format(string, sizeof(string), "%s", FormatNumberNotMoney(Inventory_Player[playerid][slotitem][itemQuantity]));
                else format(string, sizeof(string), "%s/%d", FormatNumberNotMoney(Inventory_Player[playerid][slotitem][itemQuantity]), PlayerData[playerid][pItemAmount]);
                PlayerTextDrawSetString(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]], string);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]]);
            }
        }
    }
    else if(slotitem != -1 && slotitemnext != -1){
        if(i != -1 && j != -1){
            //printf("[New] Draw Model Not Null slotitemold != -1 and slotnextitem != -1");
            PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], Inventory_Player[playerid][Inventory_Player[playerid][slotitemnext][itemSlot]][itemKey]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
            PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]]);
            if(CheckItemIsWeapon(Inventory_Player[playerid][slotitemnext][itemName]) != -1) format(string, sizeof(string), "%s", FormatNumberNotMoney(Inventory_Player[playerid][slotitemnext][itemQuantity]));
            else format(string, sizeof(string), "%s/%d", FormatNumberNotMoney(Inventory_Player[playerid][slotitemnext][itemQuantity]), PlayerData[playerid][pItemAmount]);
            PlayerTextDrawSetString(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]], string);
            PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]]);

            //ResetOldSlot
            //printf("%d = %d | %d = %d", i, iold, j, jold);
            if(i != iold || j != jold){
                //printf("LastPage: %d | Page: %d", PlayerInventoryLastPage[playerid], PlayerInventoryPage[playerid]);
                if(PlayerInventoryLastPage[playerid] == PlayerInventoryPage[playerid]){
                    //printf("[Old] Draw Model Null slotitemold != -1 and slotnextitem != -1");
                    PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][iold][jold]], MODEL_NULL);
                    PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][iold][jold]], 0.000000, 0.000000, 0.000000, 0.000000);
                    PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][iold][jold]]);
                    PlayerTextDrawHide(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][iold][jold]]);  
                }
            }
            else if(i == iold || j == jold){
                //printf("LastPage: %d | Page: %d", PlayerInventoryLastPage[playerid], PlayerInventoryPage[playerid]);
                if(PlayerInventoryLastPage[playerid] == PlayerInventoryPage[playerid]){
                    //printf("[Old] Draw Model Null slotitemold != -1 and slotnextitem != -1");
                    PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][iold][jold]], MODEL_NULL);
                    PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][iold][jold]], 0.000000, 0.000000, 0.000000, 0.000000);
                    PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][iold][jold]]);
                    PlayerTextDrawHide(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][iold][jold]]);  
                }

                //printf("[New Reload Slot] Draw Model Not Null slotitemold != -1 and slotnextitem != -1");
                PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], Inventory_Player[playerid][Inventory_Player[playerid][slotitemnext][itemSlot]][itemKey]);
                PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryModel[playerid][i][j]]);
                if(CheckItemIsWeapon(Inventory_Player[playerid][slotitemnext][itemName]) != -1) format(string, sizeof(string), "%s", FormatNumberNotMoney(Inventory_Player[playerid][slotitemnext][itemQuantity]));
                else format(string, sizeof(string), "%s/%d", FormatNumberNotMoney(Inventory_Player[playerid][slotitemnext][itemQuantity]), PlayerData[playerid][pItemAmount]);
                PlayerTextDrawSetString(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]], string);
                PlayerTextDrawShow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryAmount[playerid][i][j]]);
            }
        }
    }
    PlayerInventoryLastPage[playerid] = 0;
    return 1;
}

Player_PickupItem(playerid, itemid){

    if(PlayerTradingItem[playerid]) return 1;

    if(Iter_Contains(Iter_DropItem, itemid)){
        if(Item_CantPickup(Drop_Data[itemid][droppedItem]) != -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ไอเท็มนี้ไม่สามารถเก็บได้", "ตกลง", "");
        if(Drop_Data[itemid][droppedQuantity] == 1){
            new additem = PlayerInventory_AddItem(playerid, Drop_Data[itemid][droppedItem], Drop_Data[itemid][droppedModel], Drop_Data[itemid][droppedQuantity], Drop_Data[itemid][droppedAmmo], Drop_Data[itemid][droppedWeaponLevel]);
            if(additem == -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "{FF0000}[!] เกิดข้อผิดพลาด", "{FF0000}กระเป๋าของคุณเต็มไม่สามารถเก็บไอเท็มนี้ได้", "ตกลง", "");
            SendClientMessageEx(playerid, COLOR_ORANGE, "[!]:{FFFFFF} คุณได้เก็บไอเท็ม '%s' จำนวน '%d' เข้ากระเป๋า", Drop_Data[itemid][droppedItem], Drop_Data[itemid][droppedQuantity]);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำการเก็บไอเท็ม '%s'", ReturnRoleplayName(playerid), Drop_Data[itemid][droppedItem]);
            ItemVicinity_Delete(itemid, 1);

            foreach(new i : Player){
                if(!LoggedIn[i]) continue;
                if(!PlayerInventoryStatus[i]) continue;
                if(IsPlayerNearPlayer(playerid, i, 5.0)){
                    OnPlayerVicinity_Update(i);
                }
            }

            OnPlayerInventory_PickupSlot(playerid, additem);
            OnPlayerInventory_UpdateCount(playerid);
            Streamer_Update(playerid);
        }
        else{
            new string[128];
            PlayerCantSelectTextDraw[playerid] = true;
            SetPVarInt(playerid, "GetPickupIndex", itemid);
            format(string, sizeof string, "- ไอเท็ม '%s' จำนวน '%d'\
            \nกรอกจำนวนที่คุณต้องการจะเก็บ: ", Drop_Data[itemid][droppedItem], Drop_Data[itemid][droppedQuantity]);
            Dialog_ShowEasy(playerid, InputQuanPickupItem, DIALOG_STYLE_INPUT, "เก็บไอเท็ม", string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:InputQuanPickupItem(playerid, response, listitem, inputtext[]){
    if(!response) {
        PlayerCantSelectTextDraw[playerid] = false;
        return DeletePVar(playerid, "GetPickupIndex");
    }
    if(response){
        new string[128];
        new itemid = GetPVarInt(playerid, "GetPickupIndex");
        if(itemid != -1){
            new amount = strval(inputtext);
            if(amount <= 0 || amount > Drop_Data[itemid][droppedQuantity]){
                format(string, sizeof string, "[!] จำนวนไอเท็มไม่ถูกต้อง \n- ไอเท็ม '%s' จำนวน '%d'\
                \nกรอกจำนวนที่คุณต้องการจะเก็บ: ", Drop_Data[itemid][droppedItem], Drop_Data[itemid][droppedQuantity]);
                Dialog_ShowEasy(playerid, InputQuanPickupItem, DIALOG_STYLE_INPUT, "เก็บไอเท็ม", string, "ตกลง", "ยกเลิก");
                return 1;
            }

            if(amount > PlayerData[playerid][pItemAmount]){
                format(string, sizeof string, "[!] คุณจะใส่เก็บต่อรอบได้ไม่เกิน %d ชิ้นเท่านั้น \n- ไอเท็ม '%s' จำนวน '%d'\
                \nกรอกจำนวนที่คุณต้องการจะเก็บ: ", PlayerData[playerid][pItemAmount], Drop_Data[itemid][droppedItem], Drop_Data[itemid][droppedQuantity]);
                Dialog_ShowEasy(playerid, InputQuanPickupItem, DIALOG_STYLE_INPUT, "เก็บไอเท็ม", string, "ตกลง", "ยกเลิก");
                return 1;
            }

            new additem = PlayerInventory_AddItem(playerid, Drop_Data[itemid][droppedItem], Drop_Data[itemid][droppedModel], amount, Drop_Data[itemid][droppedAmmo], Drop_Data[itemid][droppedWeaponLevel]);
            if(additem == -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "{FF0000}[!] เกิดข้อผิดพลาด", "{FF0000}กระเป๋าของคุณเต็มไม่สามารถเก็บไอเท็มนี้ได้", "ตกลง", "");
            SendClientMessageEx(playerid, COLOR_ORANGE, "[!]:{FFFFFF} คุณได้เก็บไอเท็ม '%s' จำนวน '%d' เข้ากระเป๋า", Drop_Data[itemid][droppedItem], amount);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำการเก็บไอเท็ม '%s'", ReturnRoleplayName(playerid), Drop_Data[itemid][droppedItem]);
            ItemVicinity_Delete(itemid, amount);

            foreach(new i : Player){
                if(!LoggedIn[i]) continue;
                if(!PlayerInventoryStatus[i]) continue;
                if(IsPlayerNearPlayer(playerid, i, 5.0)){
                    OnPlayerVicinity_Update(i);
                }
            }

            OnPlayerInventory_PickupSlot(playerid, additem);
            OnPlayerInventory_UpdateCount(playerid);
            Streamer_Update(playerid);
            PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
            PlayerCantSelectTextDraw[playerid] = false;
        }
    }
    return 1;
}

Player_DropItem(playerid, itemindex){

    if(PlayerTradingItem[playerid]) return 1;

    if(Item_CantDrop(Inventory_Player[playerid][itemindex][itemName]) != -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ไอเท็มนี้ไม่สามารถทิ้งได้", "ตกลง", "");
    if(CheckItemIsWeapon(Inventory_Player[playerid][itemindex][itemName]) != -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] อาวุธไม่สามารถทิ้งได้", "ตกลง", "");

    if(!strcmp(Inventory_Player[playerid][itemindex][itemName], "Skin Baseball HW", true)){
        if(PlayerUseSkinBaseHalloween[playerid]){
            return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "คุณจะต้องกดใช้งานสกินอีกครั้งเพื่อปิดใช้งานสกินนี้ก่อน", "ตกลง", "");
        }
    }

    new Float:x, Float:y, Float:z, Float:a;
    new int = GetPlayerInterior(playerid), world = GetPlayerVirtualWorld(playerid);

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    if(Inventory_Player[playerid][itemindex][itemQuantity] == 1){
        new id = Drop_Item(Inventory_Player[playerid][itemindex][itemName], Inventory_Player[playerid][itemindex][itemKey], Inventory_Player[playerid][itemindex][itemQuantity], Inventory_Player[playerid][itemindex][itemLevel], Inventory_Player[playerid][itemindex][itemAmmo], x, y, z- 0.9, a, int, world);
        if(id == -1) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
        SendClientMessageEx(playerid, COLOR_ORANGE, "[!]:{FFFFFF} คุณได้ทำการทิ้ง '%s' จำนวน '%d'", Inventory_Player[playerid][itemindex][itemName], Inventory_Player[playerid][itemindex][itemQuantity]);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำการทิ้งไอเท็ม '%s'", ReturnRoleplayName(playerid), Inventory_Player[playerid][itemindex][itemName]);
        Streamer_Update(playerid);
        
        RemoveUseInfoButton(playerid);

        foreach(new i : Player){
            if(!LoggedIn[i]) continue;
            if(!PlayerInventoryStatus[i]) continue;
            if(IsPlayerNearPlayer(playerid, i, 5.0)){
                OnPlayerVicinity_Update(i);
            }
        }
        
        PlayerInventory_RemoveEx(playerid, itemindex);
        OnPlayerInventory_UpdateSlot(playerid, itemindex);
        OnPlayerInventory_UpdateCount(playerid);
        PlayerGetIndexSlotItem[playerid] = -1;
        PlayerInvListItemRowsOld[playerid] = -1;
        PlayerInvListItemColumnOld[playerid] = -1;
    }
    else{
        PlayerInventoryDropInput[playerid] = true;
        PlayerCantSelectTextDraw[playerid] = true;
        new string[128];
        format(string, sizeof string, "- ไอเท็ม: '%s' จำนวน '%d'\
        \nกรอกจำนวนไอเท็มที่ต้องการจะทิ้ง: ", Inventory_Player[playerid][itemindex][itemName], Inventory_Player[playerid][itemindex][itemQuantity]);
        Dialog_ShowEasy(playerid, InputQuanDropItem, DIALOG_STYLE_INPUT, "ทิ้งไอเท็ม", string, "ตกลง", "ยกเลิก");
    }
    return 1;
}

Dialog:InputQuanDropItem(playerid, response, listitem, inputtext[]){
    if(!response){
        PlayerInventoryDropInput[playerid] = false;
        PlayerCantSelectTextDraw[playerid] = false;
        PlayerGetIndexSlotItem[playerid] = -1;
        RemoveUseInfoButton(playerid);
        return 1;
    }
    if(response){
        new string[256];
        new itemindex = PlayerGetIndexSlotItem[playerid];
        new amount = strval(inputtext);
        if(amount <= 0 || amount > PlayerInventory_CountEx(playerid, itemindex)){
            format(string, sizeof string, "! เกิดข้อผิดพลาด: คุณกรอกจำนวนไม่ถูกต้องหรือจำนวนไอเท็มของคุณมีไม่พอ\n- ไอเท็ม: '%s' จำนวน '%d'\
            \nกรอกจำนวนไอเท็มที่ต้องการจะทิ้ง: ", Inventory_Player[playerid][itemindex][itemName], Inventory_Player[playerid][itemindex][itemQuantity]);
            Dialog_ShowEasy(playerid, InputQuanDropItem, DIALOG_STYLE_INPUT, "ทิ้งไอเท็ม", string, "ตกลง", "ยกเลิก");
            return 1;
        }

        new Float:x, Float:y, Float:z, Float:a;
        new int = GetPlayerInterior(playerid),
            world = GetPlayerVirtualWorld(playerid);

        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);

        new id = Drop_Item(Inventory_Player[playerid][itemindex][itemName], Inventory_Player[playerid][itemindex][itemKey], amount, Inventory_Player[playerid][itemindex][itemLevel], Inventory_Player[playerid][itemindex][itemAmmo], x, y, z- 0.9, a, int, world);
        if(id == -1) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
        SendClientMessageEx(playerid, COLOR_ORANGE, "[!]:{FFFFFF} คุณได้ทำการทิ้ง '%s' จำนวน '%d'", Inventory_Player[playerid][itemindex][itemName], amount);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้ทำการทิ้งไอเท็ม '%s'", ReturnRoleplayName(playerid), Inventory_Player[playerid][itemindex][itemName]);
        Streamer_Update(playerid);

        RemoveUseInfoButton(playerid);

        foreach(new i : Player){
            if(!LoggedIn[i]) continue;
            if(!PlayerInventoryStatus[i]) continue;
            if(IsPlayerNearPlayer(playerid, i, 5.0)){
                OnPlayerVicinity_Update(i);
            }
        }

        PlayerInventory_RemoveEx(playerid, itemindex, amount);
        OnPlayerInventory_UpdateSlot(playerid, itemindex);
        OnPlayerInventory_UpdateCount(playerid);
        PlayerGetIndexSlotItem[playerid] = -1;
        PlayerInvListItemRowsOld[playerid] = -1;
        PlayerInvListItemColumnOld[playerid] = -1;
        PlayerInventoryDropInput[playerid] = false;
        PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
        PlayerCantSelectTextDraw[playerid] = false;
    }
    return 1;
}

ItemVicinity_Delete(itemid, amount = 1){
    if(itemid != -1 && Iter_Contains(Iter_DropItem, itemid)){
        new string[128], query[128];
        if(Drop_Data[itemid][droppedQuantity] - amount > 0){
            //printf("Not Remove");
            Drop_Data[itemid][droppedQuantity] -= amount;
            if(IsValidDynamic3DTextLabel(Drop_Data[itemid][droppedText3D]) && Drop_Data[itemid][droppedText3D]){
                format(string, sizeof string, "%s (%d)", Drop_Data[itemid][droppedItem], Drop_Data[itemid][droppedQuantity]);
                UpdateDynamic3DTextLabelText(Drop_Data[itemid][droppedText3D], DROP_COLOR, string);
            }   
        }
        else{
            //printf("Remove");
            Drop_Data[itemid][droppedModel] = MODEL_NULL;
            Drop_Data[itemid][droppedQuantity] = 0;
            Drop_Data[itemid][droppedPos][0] = 0.0;
            Drop_Data[itemid][droppedPos][1] = 0.0;
            Drop_Data[itemid][droppedPos][2] = 0.0;
            Drop_Data[itemid][droppedInt] = 0;
            Drop_Data[itemid][droppedWorld] = 0;

            if(IsValidDynamic3DTextLabel(Drop_Data[itemid][droppedText3D]) && Drop_Data[itemid][droppedText3D]) {
                DestroyDynamic3DTextLabel(Drop_Data[itemid][droppedText3D]);
            }
            if(IsValidDynamicObject(Drop_Data[itemid][droppedObject]) && Drop_Data[itemid][droppedObject] != -1) {
                DestroyDynamicObject(Drop_Data[itemid][droppedObject]);
                Drop_Data[itemid][droppedObject] = -1;
            }
            Iter_Remove(Iter_DropItem, itemid);

            format(query, sizeof(query), "DELETE FROM `dropped` WHERE `ID` = '%d'", Drop_Data[itemid][droppedID]);
            mysql_tquery(dbCon, query);
        }
    }
    return 1;
}

PlayerInventory_Remove(playerid, const item[], quantity = 1){
    new string[128];
    new gettempcount = 0;
    for(new i=0; i<MAX_INVENTORYPLAYERS; i++){
        if(!Inventory_Player[playerid][i][itemHave]) continue;
        if(!strcmp(item, Inventory_Player[playerid][i][itemName], true)){
            if(quantity <= Inventory_Player[playerid][i][itemQuantity]){
                Inventory_Player[playerid][i][itemQuantity] -= quantity - gettempcount;

                if(Inventory_Player[playerid][i][itemQuantity] != 0){
                    //printf("[Remove]: UpdateItem %s amount %d", Inventory_Player[playerid][i][itemName], Inventory_Player[playerid][i][itemQuantity]);
                    format(string, sizeof(string), "UPDATE `inventory` SET `itemQuantity` = `itemQuantity` - %d WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", quantity - gettempcount, PlayerData[playerid][pID], Inventory_Player[playerid][i][itemID]);
                    mysql_tquery(dbCon, string);
                }
                else{
                    //printf("[Remove]: Delelte %s amount %d", Inventory_Player[playerid][i][itemName], Inventory_Player[playerid][i][itemQuantity]);
                    Inventory_Player[playerid][i][itemHave] = false;
                    Inventory_Player[playerid][i][itemKey] = MODEL_NULL;
                    Inventory_Player[playerid][i][itemQuantity] = 0;
                    Inventory_Player[playerid][i][itemLevel] = 0;
                    Inventory_Player[playerid][i][itemAmmo] = 0;
                    Inventory_Player[playerid][i][itemSlot] = -1;
                    format(Inventory_Player[playerid][i][itemName], 64, "NULL");
                    format(string, sizeof(string), "DELETE FROM `inventory` WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", PlayerData[playerid][pID], Inventory_Player[playerid][i][itemID]);
                    mysql_tquery(dbCon, string);

                }
                break;
            }
            else if(quantity > Inventory_Player[playerid][i][itemQuantity]){
                gettempcount = Inventory_Player[playerid][i][itemQuantity];
                //printf("[Remove]: Delelte %s amount %d", Inventory_Player[playerid][i][itemName], gettempcount);
                Inventory_Player[playerid][i][itemHave] = false;
                Inventory_Player[playerid][i][itemKey] = MODEL_NULL;
                Inventory_Player[playerid][i][itemQuantity] = 0;
                Inventory_Player[playerid][i][itemLevel] = 0;
                Inventory_Player[playerid][i][itemAmmo] = 0;
                Inventory_Player[playerid][i][itemSlot] = -1;
                format(Inventory_Player[playerid][i][itemName], 64, "NULL");
            
                format(string, sizeof(string), "DELETE FROM `inventory` WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", PlayerData[playerid][pID], Inventory_Player[playerid][i][itemID]);
                mysql_tquery(dbCon, string);
            }
        }
        if(i >= 107) break;
    }
    return 0;
}

PlayerInventory_RemoveEx(playerid, itemid, quantity = 1){
    new string[128];
    if(itemid != -1 && quantity > 0){
        if(Inventory_Player[playerid][itemid][itemQuantity] > 0){
            Inventory_Player[playerid][itemid][itemQuantity] -= quantity;
            //printf("[Remove]: Delelte %s amount %d", Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity]);
            if(Inventory_Player[playerid][itemid][itemQuantity] <= 0){
                Inventory_Player[playerid][itemid][itemHave] = false;
                Inventory_Player[playerid][itemid][itemKey] = MODEL_NULL;
                Inventory_Player[playerid][itemid][itemQuantity] = 0;
                Inventory_Player[playerid][itemid][itemLevel] = 0;
                Inventory_Player[playerid][itemid][itemAmmo] = 0;
                Inventory_Player[playerid][itemid][itemSlot] = -1;
                format(Inventory_Player[playerid][itemid][itemName], 64, "NULL");
            
                format(string, sizeof(string), "DELETE FROM `inventory` WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", PlayerData[playerid][pID], Inventory_Player[playerid][itemid][itemID]);
	            mysql_tquery(dbCon, string);
            }
            else if(Inventory_Player[playerid][itemid][itemQuantity] > 0){
                //printf("[Remove]: Update %s amount %d", Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity] - quantity);
                format(string, sizeof(string), "UPDATE `inventory` SET `itemQuantity` = `itemQuantity` - %d WHERE `itemOwner` = '%d' AND `itemID` = '%d' LIMIT 1", quantity, PlayerData[playerid][pID], Inventory_Player[playerid][itemid][itemID]);
                mysql_tquery(dbCon, string);
            }
        }
        else return ErrorMsg(playerid, "เกิดข้อผิดพลาด, โปรดแจ้งผู้ดูแลระบบ");
    }
    return 0;
}

Drop_Item(const item[], model, quantity, level = 0, ammo = 0, Float:x, Float:y, Float:z, Float:ang, Int, World){
    new query[300];
    new i = -1;
    if(( i = Iter_Free(Iter_DropItem)) != -1 && i < MAX_DROPPED_ITEMS){
        //Debug Drop Item Finish");
        format(Drop_Data[i][droppedItem], 64, item);
        x += (0.5 * floatsin(-ang, degrees));
		y += (0.5 * floatcos(-ang, degrees));
        Drop_Data[i][droppedModel] = model;
        Drop_Data[i][droppedQuantity] = quantity;
        Drop_Data[i][droppedAmmo] = ammo;
        Drop_Data[i][droppedWeaponLevel] = level;
        Drop_Data[i][droppedPos][0] = x;
        Drop_Data[i][droppedPos][1] = y;
        Drop_Data[i][droppedPos][2] = z;
        Drop_Data[i][droppedInt] = Int;
        Drop_Data[i][droppedWorld] = World;
        Drop_Data[i][droppedObject] = CreateDynamicObject(model, x, y, z, 0.0, 0.0, 0.0, World, Int);
    
        new string[128];

        if(CheckItemIsWeapon(Drop_Data[i][droppedItem]) != -1){
            format(string, sizeof(string), "%s (Level: %d)", Drop_Data[i][droppedItem], Drop_Data[i][droppedWeaponLevel]);
        }
        else{
            if(Drop_Data[i][droppedQuantity] == 1)
                format(string, sizeof(string), "%s", Drop_Data[i][droppedItem]);
            else if(Drop_Data[i][droppedQuantity] > 1)
                format(string, sizeof(string), "%s (%s)", Drop_Data[i][droppedItem], FormatNumberNotMoney(Drop_Data[i][droppedQuantity]));
        }   

        Drop_Data[i][droppedText3D] = CreateDynamic3DTextLabel(string, DROP_COLOR, x, y, z, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, World, Int);
        Iter_Add(Iter_DropItem, i);

        mysql_format(dbCon, query, sizeof(query), "INSERT INTO `dropped` (`itemName`, `itemModel`, `itemQuantity`, `itemAmmo`, `itemX`, `itemY`, `itemZ`, `itemInt`, `itemWorld`) VALUES('%e', '%d', '%d', '%d', '%.4f', '%.4f', '%.4f', '%d', '%d')", item, model, quantity, ammo, x, y, z, Int, World);
		mysql_tquery(dbCon, query, "OnDroppedItem", "d", i);
        return i;
    }
    return -1;
}

forward OnDroppedItem(itemid);
public OnDroppedItem(itemid){
	if(itemid != -1 && Iter_Contains(Iter_DropItem, itemid)){
        Drop_Data[itemid][droppedID] = cache_insert_id();
    }
	return 1;
}

forward OnPlayerInventory_UseItem(playerid, const name[], model, itemid);
public OnPlayerInventory_UseItem(playerid, const name[], model, itemid){
    if(itemid == -1) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
    if(Inventory_Player[playerid][itemid][itemQuantity] == 0) {
        new string[128];
        format(string, sizeof(string), "%s(%d) พยายามกดใช้ไอเท็ม '%s' ที่มีจำนวน 0", ReturnRoleplayName(playerid), playerid, Inventory_Player[playerid][itemid][itemName]);
        SendAdminsMessage(1, COLOR_YELLOW, string);
        return ErrorMsg(playerid, "เกิดข้อผิดพลาดกรุณาแจ้งผู้ดูแลระบบ");
    }
    new checkacctype = 0;

    if((checkacctype = CheckItemIsAccessory(name)) != -1){

        if(ServerRestart) return ErrorMsg(playerid, "ฟังก์ชั่นนี้ถูกปิดใช้งานชั่วคราว");

        if(checkacctype != 0){
            if(checkacctype == 1){
                if(PlayerData[playerid][pAccessoryModelHat] != 0) return ErrorMsg(playerid, "คุณกำลังใส่ 'หมวก' อยู่กรุณาถอดก่อน");
                PlayerData[playerid][pAccessoryModelHat] = model;
                format(PlayerData[playerid][pAccessoryNameHat], 32, name);
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ใส่เครื่องแต่งกาย '%s' เรียบร้อยแล้ว", name);
                PlayerInventory_Remove(playerid, name, 1);
            }
            else if(checkacctype == 2){
                if(PlayerData[playerid][pAccessoryModelGlasses] != 0) return ErrorMsg(playerid, "คุณกำลังใส่ 'แว่นหรือผ้าปิดปาก' อยู่กรุณาถอดก่อน");
                PlayerData[playerid][pAccessoryModelGlasses] = model;
                format(PlayerData[playerid][pAccessoryNameGlasses], 32, name);
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ใส่เครื่องแต่งกาย '%s' เรียบร้อยแล้ว", name);
                PlayerInventory_Remove(playerid, name, 1);
            }
            else if(checkacctype == 3){
                if(PlayerData[playerid][pAccessoryModelBody] != 0) return ErrorMsg(playerid, "คุณกำลังใส่ 'ลำตัว' อยู่กรุณาถอดก่อน");
                PlayerData[playerid][pAccessoryModelBody] = model;
                format(PlayerData[playerid][pAccessoryNameBody], 32, name);
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ใส่เครื่องแต่งกาย '%s' เรียบร้อยแล้ว", name);
                PlayerInventory_Remove(playerid, name, 1);
            }
            else if(checkacctype == 4){
                if(PlayerData[playerid][pAccessoryModelArms] != 0) return ErrorMsg(playerid, "คุณกำลังใส่ 'มือ' อยู่กรุณาถอดก่อน");
                PlayerData[playerid][pAccessoryModelArms] = model;
                format(PlayerData[playerid][pAccessoryNameArms], 32, name);
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ใส่เครื่องแต่งกาย '%s' เรียบร้อยแล้ว", name);
                PlayerData[playerid][pAccessoryArmsType] = 6; //มือขวา
                PlayerInventory_Remove(playerid, name, 1);
            }
        }
        if(PlayerShowButton[playerid]) RemoveUseInfoButton(playerid);
        if(PlayerInventoryStatus[playerid]) OnPlayerInventory_Close(playerid);
        if(PlayerCharacterShow[playerid]) PlayerCharacterTD_Render(playerid);
        return 1;
    }
    else{

        if(!strcmp(name, "Tent Backpack", true)){
            callcmd::camping(playerid, "\1");
        }

        else if(!strcmp(name, "Camera", true)){
            GivePlayerWeapon(playerid, 43, 50);
        }

        else if(!strcmp(name, "Skin Baseball HW", true)){

            if(PlayerData[playerid][pMyWeapon][2] != WEAPON_BAT) return ErrorMsg(playerid, "สามารถใช้ได้กับ Baseball Bat เท่านั้น");

            if(!PlayerUseSkinBaseHalloween[playerid]){
                PlayerUseSkinBaseHalloween[playerid] = true;
                SendClientMessage(playerid, COLOR_ORANGE, "คุณได้เปิดใช้งาน สกินเบสบอลฮาโลวีน แล้ว");
            }
            else{
                PlayerUseSkinBaseHalloween[playerid] = false;
                RemoveAttachedObject(playerid, 5);
                SendClientMessage(playerid, COLOR_ORANGE, "คุณได้ปิดใช้งาน สกินเบสบอลฮาโลวีน แล้ว");
            }
        }

        else if (!strcmp(name, "Knife", true)){
            if(PlayerUseKnife[playerid] == 0){
                PlayerUseKnife[playerid] = 1;
                SetPlayerAttachedObject(playerid,9,335,6,-0.012000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
            }   
            else{
                PlayerUseKnife[playerid] = 0;
                RemoveAttachedObject(playerid, 9);
            }
        }

        else if(!strcmp(name, "Box Level", true)){
            if(PlayerData[playerid][pBoxLevel1] == 0){
                if(PlayerData[playerid][pLevel] >= 1){
                    SendClientMessage(playerid, COLOR_GREEN, "- คุณเปิดกล่อง LEVEL สำหรับ LEVEL 1 และได้รับเงิน + $500");
                    SendClientMessage(playerid, COLOR_YELLOW, "- คุณสามารถเปิดกล่องนี้ได้อีกตอนคุณมีเลเวล 5");
                    GiveMoney(playerid, 500, "Box Level 1");
                    PlayerData[playerid][pBoxLevel1] = 1;
                }
            }
            else if(PlayerData[playerid][pBoxLevel5] == 0){
                if(PlayerData[playerid][pLevel] >= 5){
                    SendClientMessage(playerid, COLOR_GREEN, "- คุณเปิดกล่อง LEVEL สำหรับ LEVEL 5 และได้รับเงิน + $1,000");
                    SendClientMessage(playerid, COLOR_YELLOW, "- คุณสามารถเปิดกล่องนี้ได้อีกตอนคุณมีเลเวล 10");
                    GiveMoney(playerid, 1000, "Box Level 5");
                    PlayerData[playerid][pBoxLevel5] = 1;
                }
            }
            else if(PlayerData[playerid][pBoxLevel10] == 0){
                if(PlayerData[playerid][pLevel] >= 10){
                    SendClientMessage(playerid, COLOR_GREEN, "- คุณเปิดกล่อง LEVEL สำหรับ LEVEL 10");
                    SendClientMessage(playerid, -1, "- ได้รับเงิน + $1,000");
                    SendClientMessage(playerid, -1, "- ได้รับ EXP + 3");
                    SendClientMessage(playerid, COLOR_YELLOW, "- คุณสามารถเปิดกล่องนี้ได้อีกตอนคุณมีเลเวล 15");
                    GiveMoney(playerid, 1000, "Box Level 10");
                    PlayerData[playerid][pExp] += 3;
                    PlayerData[playerid][pBoxLevel10] = 1;
                }
            }
            else if(PlayerData[playerid][pBoxLevel15] == 0){
                if(PlayerData[playerid][pLevel] >= 15){
                    SendClientMessage(playerid, COLOR_GREEN, "- คุณเปิดกล่อง LEVEL สำหรับ LEVEL 15");
                    SendClientMessage(playerid, -1, "- ได้รับเงิน + $1,000");
                    SendClientMessage(playerid, -1, "- ได้รับ EXP + 5");
                    SendClientMessage(playerid, -1, "- ได้รับ ชั่วโมงออนไลน์ + 3");
                    SendClientMessage(playerid, COLOR_YELLOW, "- คุณสามารถเปิดกล่องนี้ได้อีกตอนคุณมีเลเวล 20");
                    GiveMoney(playerid, 1000, "Box Level 15");
                    PlayerData[playerid][pExp] += 5;
                    PlayerData[playerid][pPlayerhour] += 3;
                    PlayerData[playerid][pBoxLevel15] = 1;
                }
            }
            else if(PlayerData[playerid][pBoxLevel20] == 0){
                if(PlayerData[playerid][pLevel] >= 20){
                    SendClientMessage(playerid, COLOR_GREEN, "- คุณเปิดกล่อง LEVEL สำหรับ LEVEL 20");
                    SendClientMessage(playerid, -1, "- ได้รับเงิน + $2,000");
                    SendClientMessage(playerid, -1, "- ได้รับ EXP + 5");
                    SendClientMessage(playerid, -1, "- ได้รับ ชั่วโมงออนไลน์ + 3");
                    SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เปิดกล่อง LEVEL จนครบแล้ว");
                    GiveMoney(playerid, 2000, "Box Level 20");
                    PlayerData[playerid][pExp] += 5;
                    PlayerData[playerid][pPlayerhour] += 3;
                    PlayerData[playerid][pBoxLevel20] = 1;
                    PlayerInventory_Remove(playerid, "Box Level", 1);
                }
            }
        }

        // ชุดเซ็ท

        else if(!strcmp(name, "Lupin Set", true)){
            if(!strcmp(PlayerData[playerid][pAccessoryAllSet], "NULL", true)){
                format(PlayerData[playerid][pAccessoryAllSet], 64, name);
                SendClientMessage(playerid, COLOR_YELLOW, "| คุณได้ใส่ชุดเซ็ท Lupin Set เรียบร้อยแล้วสามารถใช้งานได้ที่ Accessory Menu");
            }
            else return ErrorMsg(playerid, "คุณต้องถอดชุดเซ็ทที่ใส่ออกก่อน");
            PlayerInventory_RemoveEx(playerid, itemid, 1);
        }

        else if(!strcmp(name, "Wooden Crate", true)){
            if(!PlayerIsCarryCrate[playerid] && !Player_Orange_InCrate[playerid] && Player_GetID_Orange[playerid] == -1){
                PlayerIsCarryCrate[playerid] = true;
                SetPlayerAttachedObject(playerid,CARRY_ORANGE_SLOT,19639,6,0.105999,0.012000,-0.180999,-110.799987,-9.199998,-5.499994,1.000000,1.000000,1.000000);
                ClearAnimations(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
            }
            else if(PlayerIsCarryCrate[playerid] && !Player_Orange_InCrate[playerid] && Player_GetID_Orange[playerid] == -1){
                PlayerIsCarryCrate[playerid] = false;
                RemoveAttachedObject(playerid, CARRY_ORANGE_SLOT);
                ClearAnimations(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            }
        }

        else if(!strcmp(name, "Orange juice", true)){
            PlayerData[playerid][pWater] += 30;
            if(PlayerData[playerid][pWater] >= 100) PlayerData[playerid][pWater] = 100;

            PlayerInventory_Remove(playerid, "Orange juice", 1);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Orange juice (น้ำส้ม)' ขึ้นมาและดื่ม", ReturnRoleplayName(playerid));
        }

        else if(!strcmp(name, "Green Apple Juice", true)){
            PlayerData[playerid][pWater] += 40;
            if(PlayerData[playerid][pWater] >= 100) PlayerData[playerid][pWater] = 100;

            PlayerInventory_Remove(playerid, "Green Apple Juice", 1);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Green Apple Juice (น้ำแอปเปิ้ลเขียว)' ขึ้นมาและดื่ม", ReturnRoleplayName(playerid));
        }



        else if(!strcmp(name, "Beer", true)){

            PlayerData[playerid][pEnergy] += 30;
            if(PlayerData[playerid][pEnergy] >= 100) PlayerData[playerid][pEnergy] = 100;

            PlayerData[playerid][pStress] -= 30;
            if(PlayerData[playerid][pStress] < 180) SetPlayerWeather(playerid, g_serverWeather);
            if(PlayerData[playerid][pStress] <= 0) PlayerData[playerid][pStress] = 0;
            SetPlayerDrunkLevel(playerid, 10000);
            SetPlayerWeather(playerid, -67);
            SetPlayerTime(playerid, 12, 12);
            DrunkTime[playerid] = 90;
            PlayerInventory_Remove(playerid, "Beer", 1);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SetTimerEx("SetAnimationDrunkWalk", 3000, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Beer' ขึ้นมาและดื่ม", ReturnRoleplayName(playerid));
        }

        else if(!strcmp(name, "Red Apple Wine", true)){

            PlayerData[playerid][pEnergy] += 10;
            if(PlayerData[playerid][pEnergy] >= 100) PlayerData[playerid][pEnergy] = 100;

            PlayerData[playerid][pStress] -= 50;
            if(PlayerData[playerid][pStress] < 180) SetPlayerWeather(playerid, g_serverWeather);
            if(PlayerData[playerid][pStress] <= 0) PlayerData[playerid][pStress] = 0;
            SetPlayerDrunkLevel(playerid, 5000);
            SetPlayerWeather(playerid, -67);
            SetPlayerTime(playerid, 12, 12);
            DrunkTime[playerid] = 50;
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SetTimerEx("SetAnimationDrunkWalk", 3000, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Red Apple Wine' ขึ้นมาและดื่ม", ReturnRoleplayName(playerid));
        }

        else if(!strcmp(name, "Green Apple Wine", true)){

            PlayerData[playerid][pEnergy] += 10;
            if(PlayerData[playerid][pEnergy] >= 100) PlayerData[playerid][pEnergy] = 100;

            PlayerData[playerid][pStress] -= 50;
            if(PlayerData[playerid][pStress] < 180) SetPlayerWeather(playerid, g_serverWeather);
            if(PlayerData[playerid][pStress] <= 0) PlayerData[playerid][pStress] = 0;
            SetPlayerDrunkLevel(playerid, 5000);
            SetPlayerWeather(playerid, -67);
            SetPlayerTime(playerid, 12, 12);
            DrunkTime[playerid] = 50;
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SetTimerEx("SetAnimationDrunkWalk", 3000, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Green Apple Wine' ขึ้นมาและดื่ม", ReturnRoleplayName(playerid));
        }

        else if(!strcmp(name, "Life Vest", true)){
            if(WearLifeVest[playerid] == 0){
                WearLifeVest[playerid] = 1;
                SendClientMessage(playerid, COLOR_YELLOW, "คุณได้ทำการใส่ เสื้อชูชีพ เรียบร้อยแล้ว");
                SetPlayerAttachedObject(playerid,7,19904,1,0.030999,0.044999,-0.017000,170.000000,92.000030,1.999999,1.215000,1.229999,1.097000);
            }
            else if(WearLifeVest[playerid] == 1){
                WearLifeVest[playerid] = 0;
                SendClientMessage(playerid, COLOR_YELLOW, "คุณได้ทำการถอด เสื้อชูชีพ เรียบร้อยแล้ว");
                RemoveAttachedObject(playerid, 7);
            }
        }

        else if(!strcmp(name, "Hippo Pack", true)){
            new id = PlayerInventory_AddItem(playerid, "Hippo Fashion", 1371, 1);
		    if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            SendClientMessage(playerid, -1, "- คุณได้รับ Hippo Fashion + 1");
            PlayerInventory_Remove(playerid, "Hippo Pack", 1);
        }

        else if(!strcmp(name, "Surf Board 3 Pack", true)){
            new id = PlayerInventory_AddItem(playerid, "Surf Board 3", 2406, 1);
		    if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            SendClientMessage(playerid, -1, "- คุณได้รับ Surf Board 3 + 1");
            PlayerInventory_Remove(playerid, "Surf Board 3 Pack", 1);
        }

        else if(!strcmp(name, "Chainsaw Dildo Pack", true)){
            new id = PlayerInventory_AddItem(playerid, "Chainsaw Dildo", 19086, 1);
		    if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            SendClientMessage(playerid, -1, "- คุณได้รับ Chainsaw Dildo + 1");
            PlayerInventory_Remove(playerid, "Chainsaw Dildo Pack", 1);
        }

        else if(!strcmp(name, "Jason Mask2 Pack", true)){
            new id = PlayerInventory_AddItem(playerid, "Jason Mask2", 19037, 1);
		    if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            SendClientMessage(playerid, -1, "- คุณได้รับ Jason Mask2 + 1");
            PlayerInventory_Remove(playerid, "Jason Mask2 Pack", 1);
        }

        else if(!strcmp(name, "Mafia Hat Pack", true)){
            new id = PlayerInventory_AddItem(playerid, "Mafia Hat", 19352, 1);
		    if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            SendClientMessage(playerid, -1, "- คุณได้รับ Mafia Hat + 1");
            PlayerInventory_Remove(playerid, "Mafia Hat Pack", 1);
        }

        else if(!strcmp(name, "Parrot Pack", true)){
            new id = PlayerInventory_AddItem(playerid, "Parrot Fashion", 19079, 1);
		    if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            SendClientMessage(playerid, -1, "- คุณได้รับ Parrot Fashion + 1");
            PlayerInventory_Remove(playerid, "Parrot Pack", 1);
        }

        else if(!strcmp(name, "Guitar 1 Pack", true)){
            new id = PlayerInventory_AddItem(playerid, "Guitar 1", 19317, 1);
		    if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            SendClientMessage(playerid, -1, "- คุณได้รับ Guitar 1 + 1");
            PlayerInventory_Remove(playerid, "Guitar 1 Pack", 1);
        }

        else if(!strcmp(name, "Id Card", true)){
            Dialog_ShowEasy(playerid, MyIdCard, DIALOG_STYLE_LIST, "บัตรประจำตัวประชาชน", "- ดูบัตรประจำตัวประชาชน\n- ให้ผู้เล่นอื่นดู", "เลือก", "ยกเลิก");
            return OnPlayerInventory_Close(playerid);
        }

        else if(!strcmp(name, "Chaya Card", true)){
            if(PlayerData[playerid][pChayaHead] == 1) return ErrorMsg(playerid, "คุณมีฉายาบนหัวอยู่แล้ว");
            PlayerInventory_Remove(playerid, "Chaya Card", 1);
            PlayerData[playerid][pChayaHead] = 1;
            SendClientMessage(playerid, COLOR_YELLOW, "คุณได้ทำการใช้บัตรฉายาบนหัวเรียบร้อยแล้ว");
            SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: คุณสามารถกด H > ฉายาบนหัวเพื่อตั้งฉายาของคุณได้");
        }

        else if(!strcmp(name, "Agency Card", true)){
            if(GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_MEDIC && GetGroupType(playerid) != GROUP_NATIONAL)
                return ErrorMsg(playerid, "คุณไม่ได้เป็นสมาชิกในหน่วยงานใดๆ");

            Dialog_ShowEasy(playerid, MyAgencyCard, DIALOG_STYLE_LIST, "บัตรประจำตัวหน่วยงาน", "- ดูบัตรประจำตัวหน่วยงาน\n- ให้ผู้เล่นอื่นดู", "เลือก", "ยกเลิก");
            return OnPlayerInventory_Close(playerid);
        }

        else if(!strcmp(name, "Cigar", true)){

            PlayerData[playerid][pStress] -= 40;

            if(PlayerData[playerid][pStress] < 180){
                SetPlayerWeather(playerid, g_serverWeather);
            }

            if(PlayerData[playerid][pStress] <= 0)
                PlayerData[playerid][pStress] = 0;

            PlayerInventory_Remove(playerid, "Cigar", 1);
            ClearAnimations(playerid);
            SetPlayerSpecialAction(playerid,SPECIAL_ACTION_SMOKE_CIGGY);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Cigar' ขึ้นมาดูด", ReturnRoleplayName(playerid));
        }

        else if(!strcmp(name, "Burger", true)){
            PlayerInventory_Remove(playerid, "Burger", 1);
            ClearAnimations(playerid);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Burger' ขึ้นมาแล้วกิน", ReturnRoleplayName(playerid));
            PlayerData[playerid][pHunger] += 30;
            if(PlayerData[playerid][pHunger] >= 100)
                PlayerData[playerid][pHunger] = 100;
        }

        else if(!strcmp(name, "Pizza Box", true)){
            PlayerInventory_Remove(playerid, "Pizza Box", 1);
            ClearAnimations(playerid);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Pizza Box' ขึ้นมาแล้วเปิดและกิน", ReturnRoleplayName(playerid));
            PlayerData[playerid][pHunger] += 40;
            if(PlayerData[playerid][pHunger] >= 100) PlayerData[playerid][pHunger] = 100;
        }

        else if(!strcmp(name, "Water Drink", true)){
            PlayerInventory_Remove(playerid, "Water Drink", 1);
            ClearAnimations(playerid);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Water Drink' ขึ้นมาแล้วดื่ม", ReturnRoleplayName(playerid));
            PlayerData[playerid][pWater] += 40;
            if(PlayerData[playerid][pWater] >= 100)
                PlayerData[playerid][pWater] = 100;
        }

        else if(!strcmp(name, "Green Apple Juice", true)){
            PlayerInventory_Remove(playerid, "Green Apple Juice", 1);
            ClearAnimations(playerid);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Green Apple Juice' ขึ้นมาแล้วดื่ม", ReturnRoleplayName(playerid));
            PlayerData[playerid][pWater] += 80;
            if(PlayerData[playerid][pWater] >= 100)
                PlayerData[playerid][pWater] = 100;
        }

        else if(!strcmp(name, "Energy Drink", true)){
            PlayerInventory_Remove(playerid, "Energy Drink", 1);
            ClearAnimations(playerid);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SetPlayerAttachedObject(playerid, 9, 1544,6,0.050999,0.039999,-0.103999,-2.699999,0.000000,0.000000,1.000000,1.000000,1.000000);
            SetTimerEx("RemoveProp", 5000, false, "i", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Energy Drink' ขึ้นมาแล้วดื่ม", ReturnRoleplayName(playerid));
            PlayerData[playerid][pEnergy] += 50;
            if(PlayerData[playerid][pEnergy] >= 100) PlayerData[playerid][pEnergy] = 100;
        }

        else if(!strcmp(name, "Banana Seed", true)){
            PlayerIsPlanting(playerid, BANANATYPE);
        }

        else if(!strcmp(name, "Banana", true)){
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            ClearAnimations(playerid);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Banana' ขึ้นมาแล้วเปิดและกิน", ReturnRoleplayName(playerid));
            PlayerData[playerid][pHunger] += 10;
            if(PlayerData[playerid][pHunger] >= 100) PlayerData[playerid][pHunger] = 100;
        }

        else if(!strcmp(name, "Pumpkin Seed", true)){
            PlayerIsPlanting(playerid, PUMPKINTYPE);
        }

        else if(!strcmp(name, "Pumpkin", true)){
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            ClearAnimations(playerid);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Pumpkin' ขึ้นมาแล้วเปิดและกิน", ReturnRoleplayName(playerid));
            PlayerData[playerid][pHunger] += 10;
            if(PlayerData[playerid][pHunger] >= 100) PlayerData[playerid][pHunger] = 100;
        }

        else if(!strcmp(name, "Apple Seed", true)){
            PlayerIsPlanting(playerid, APPLETYPE);
        }

        else if(!strcmp(name, "Apple", true)){
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            ClearAnimations(playerid);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Apple' ขึ้นมาแล้วเปิดและกิน", ReturnRoleplayName(playerid));
            PlayerData[playerid][pHunger] += 10;
            if(PlayerData[playerid][pHunger] >= 100) PlayerData[playerid][pHunger] = 100;
        }

        else if(!strcmp(name, "Green Apple Seed", true)){
            PlayerIsPlanting(playerid, GREENAPPLETYPE);
        }

        else if(!strcmp(name, "Green Apple", true)){
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            ClearAnimations(playerid);
            SetTimerEx("SetAnimationEating", 500, false, "d", playerid);
            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s หยิบ 'Green Apple' ขึ้นมาแล้วเปิดและกิน", ReturnRoleplayName(playerid));
            PlayerData[playerid][pHunger] += 10;
            if(PlayerData[playerid][pHunger] >= 100) PlayerData[playerid][pHunger] = 100;
        }

        else if(!strcmp(name, "Mobile Phone", true)){

            if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "ไม่สามารถใช้ได้ในขณะนี้");

            if (BitFlag_Get(g_PlayerFlags[playerid],PLAYER_PHONE_OFF))
                return ErrorMsg(playerid, "คุณต้องเปิดเครื่องโทรศัพท์ของคุณ");

            if(PlayerUsingPhone[playerid] == 0){
                LoadPlayerPhoneTD(playerid);
                SetPlayerAttachedObject(playerid,7,18872,6,0.080999,0.001000,0.018000,-98.399986,0.000000,168.799987,1.000000,1.000000,1.000000);
                if(PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID){
                    SetTimerEx("ShowCallingPhone", 500, false, "d", playerid);
                }
                else{
                    SendClientMessage(playerid, COLOR_YELLOW, "[แนะนำ]: (911 = เพื่อเหตุด่วน) | (112 = ช่างยนต์)");
                    SetTimerEx("ShowMobilePhone", 500, false, "d", playerid);
                }
            }
            else if(PlayerUsingPhone[playerid] == 1){
                HideMobilePhone(playerid);
            }
            return OnPlayerInventory_Close(playerid);
        }

        else if(!strcmp(name, "Mixed Drug", true)){
            new message[128];
            new Float:am;
            if(am >= 100) return ErrorMsg(playerid, "คุณมีเกราะเต็มแล้วไม่สามารถใช้ได้");
            if(PlayerInventory_CountEx(playerid, itemid) > 1){
                SetPVarInt(playerid, "itemMixedid", itemid);
                format(message, sizeof(message), "คุณมี Mixed Drug จำนวน: %d\nกรอกจำนวนที่คุณต้องการจะใช้:", PlayerInventory_CountEx(playerid, itemid));
                Dialog_ShowEasy(playerid, UseMixedDrug, DIALOG_STYLE_INPUT, "กรอกจำนวนยาที่จะใช้", message, "ตกลง", "ยกเลิก");
                return OnPlayerInventory_Close(playerid);
            }
            else{
                GetPlayerArmour(playerid, am);
                PlayerInventory_RemoveEx(playerid, itemid, 1);
                SetPlayerArmour(playerid, am+25);
                SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้รับเกราะ +25");
            }
        }

        else if(!strcmp(name, "Car Tracker Tool", true)){
            InstallTrackerForCar(playerid);
        }

        else if(!strcmp(name, "Tracker Remote", true)){
            UseTrackerRemote(playerid);
        }

        else if(!strcmp(name, "Password Card", true)){
            PlayerChangePassword(playerid);
        }

        else if(!strcmp(name, "Name Card", true)){
            PlayerChangeName(playerid);
        }

        else if(!strcmp(name, "Gas Can", true)){

            new carid = -1;

            if((carid = Car_Nearest(playerid)) != -1){
                new EngineStatus = GetEngineStatus(CarData[carid][carVehicle]);

                if (!IsDoorVehicle(CarData[carid][carVehicle])){

                    if(EngineStatus)
                        return ErrorMsg(playerid, "จำเป็นต้องดับเครื่องยนต์ก่อนจะเริ่มซ่อม");

                    SetPlayerRefillGascan(playerid, CarData[carid][carVehicle]);
                }
                else{
                    if (IsPlayerNearHood(playerid, CarData[carid][carVehicle])){
                        if(EngineStatus)
                            return ErrorMsg(playerid, "จำเป็นต้องดับเครื่องยนต์ก่อนจะเริ่มซ่อม");

                        if (!GetHoodStatus(CarData[carid][carVehicle]))
                            return ErrorMsg(playerid, "กระโปรงรถคันนี้ปิดอยู่");

                        SetPlayerRefillGascan(playerid, CarData[carid][carVehicle]);
                    }
                }
            }
        }

        //GachaBox
        else if(!strcmp(name, "Jester Box", true)){
            PlayerGetBoxType[playerid] = 1;
            format(BoxNameData[playerid][boxName], 64, name);
            SetTimerEx("ShowGaChaBox", 300, false, "i", playerid);
        }

        else if(!strcmp(name, "Fashion Box", true)){
            PlayerGetBoxType[playerid] = 2;
            format(BoxNameData[playerid][boxName], 64, name);
            SetTimerEx("ShowGaChaBox", 300, false, "i", playerid);
        }

        else if(!strcmp(name, "Lupin Box", true)){
            PlayerGetBoxType[playerid] = 3;
            format(BoxNameData[playerid][boxName], 64, name);
            SetTimerEx("ShowGaChaBox", 300, false, "i", playerid);
        }

        else if(!strcmp(name, "Valentine Box", true)){
            PlayerGetBoxType[playerid] = 4;
            format(BoxNameData[playerid][boxName], 64, name);
            SetTimerEx("ShowGaChaBox", 300, false, "i", playerid);
        }

        else if(!strcmp(name, "Bullet Box", true)){
            PlayerGetBoxType[playerid] = 5;
            format(BoxNameData[playerid][boxName], 64, name);
            SetTimerEx("ShowGaChaBox", 300, false, "i", playerid);
        }

        else if(!strcmp(name, "Weapon Box", true)){
            PlayerGetBoxType[playerid] = 6;
            format(BoxNameData[playerid][boxName], 64, name);
            SetTimerEx("ShowGaChaBox", 300, false, "i", playerid);
        }

        else if(!strcmp(name, "Gacha V1 Box", true)){
            PlayerGetBoxType[playerid] = 7;
            format(BoxNameData[playerid][boxName], 64, name);
            SetTimerEx("ShowGaChaBox", 300, false, "i", playerid);
        }

        else if(!strcmp(name, "Sultan Box", true)){
            PlayerGetBoxType[playerid] = 8;
            format(BoxNameData[playerid][boxName], 64, name);
            SetTimerEx("ShowGaChaBox", 300, false, "i", playerid);
        }

        //Vehicle Key Open
        else if(!strcmp(name, "Jester Key", true)){
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

            id = Car_Create(PlayerData[playerid][pID], 559, x, y + 2, z + 1, angle, random(127), random(127));
            if (id == -1) return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");
            if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS) return SendClientMessage(playerid, -1, "คุณมียานพาหนะเต็มแล้ว");

            LinkVehicleToInterior(id, int);
            SetVehicleVirtualWorld(id, world);

            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Jester Key", "คุณได้เปิดกุญแจ Jester Key และได้รับยานพาหนะ Jester เรีบยร้อยแล้ว", "ตกลง", "");
            new str[128];
            format(str, sizeof(str), "[เปิดกุญแจยานพาหนะ]: ผู้เล่น %s(%d) ได้ทำการเปิดกุญแจ 'Jester Key' และได้รับยานพาหนะ 'Jester'", ReturnRoleplayName(playerid), playerid);
            SendAdminsMessage(1, COLOR_GRAY, str);
            PlayerInventory_RemoveEx(playerid, itemid, 1);
        }

        else if(!strcmp(name, "Bullet Key", true)){
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

            id = Car_Create(PlayerData[playerid][pID], 541, x, y + 2, z + 1, angle, random(127), random(127));
            if (id == -1) return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");
            if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS) return SendClientMessage(playerid, -1, "คุณมียานพาหนะเต็มแล้ว");

            LinkVehicleToInterior(id, int);
            SetVehicleVirtualWorld(id, world);

            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Bullet Key", "คุณได้เปิดกุญแจ Bullet Key และได้รับยานพาหนะ Bullet เรีบยร้อยแล้ว", "ตกลง", "");
            new str[128];
            format(str, sizeof(str), "[เปิดกุญแจยานพาหนะ]: ผู้เล่น %s(%d) ได้ทำการเปิดกุญแจ 'Bullet Key' และได้รับยานพาหนะ 'Bullet'", ReturnRoleplayName(playerid), playerid);
            SendAdminsMessage(1, COLOR_GRAY, str);
            PlayerInventory_RemoveEx(playerid, itemid, 1);
        }

        else if(!strcmp(name, "Mountain Bike Key", true)){
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

            id = Car_Create(PlayerData[playerid][pID], 510, x, y + 2, z + 1, angle, random(127), random(127));
            if (id == -1) return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");
            if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS) return SendClientMessage(playerid, -1, "คุณมียานพาหนะเต็มแล้ว");

            LinkVehicleToInterior(id, int);
            SetVehicleVirtualWorld(id, world);

            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Mountain Bike Key", "คุณได้เปิดกุญแจ Mountain Bike Key และได้รับยานพาหนะ Mountain Bike เรีบยร้อยแล้ว", "ตกลง", "");
            new str[128];
            format(str, sizeof(str), "[เปิดกุญแจยานพาหนะ]: ผู้เล่น %s(%d) ได้ทำการเปิดกุญแจ 'Mountain Bike Key' และได้รับยานพาหนะ 'Mountain Bike'", ReturnRoleplayName(playerid), playerid);
            SendAdminsMessage(1, COLOR_GRAY, str);

            PlayerInventory_RemoveEx(playerid, itemid, 1);
        }

        else if(!strcmp(name, "Bandito Key", true)){
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

            id = Car_Create(PlayerData[playerid][pID], 568, x, y + 2, z + 1, angle, random(127), random(127));
            if (id == -1) return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");
            if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS) return SendClientMessage(playerid, -1, "คุณมียานพาหนะเต็มแล้ว");

            LinkVehicleToInterior(id, int);
            SetVehicleVirtualWorld(id, world);

            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Bandito Key", "คุณได้เปิดกุญแจ Bandito Key และได้รับยานพาหนะ Bandito เรีบยร้อยแล้ว", "ตกลง", "");
            new str[128];
            format(str, sizeof(str), "[เปิดกุญแจยานพาหนะ]: ผู้เล่น %s(%d) ได้ทำการเปิดกุญแจ 'Bandito Key' และได้รับยานพาหนะ 'Bandito'", ReturnRoleplayName(playerid), playerid);
            SendAdminsMessage(1, COLOR_GRAY, str);

            PlayerInventory_RemoveEx(playerid, itemid, 1);
        }

        else if(!strcmp(name, "Sultan Key", true)){
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

            id = Car_Create(PlayerData[playerid][pID], 560, x, y + 2, z + 1, angle, random(127), random(127));
            if (id == -1) return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");
            if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS) return SendClientMessage(playerid, -1, "คุณมียานพาหนะเต็มแล้ว");

            LinkVehicleToInterior(id, int);
            SetVehicleVirtualWorld(id, world);

            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Sultan Key", "คุณได้เปิดกุญแจ Sultan Key และได้รับยานพาหนะ Sultan เรีบยร้อยแล้ว", "ตกลง", "");
            new str[128];
            format(str, sizeof(str), "[เปิดกุญแจยานพาหนะ]: ผู้เล่น %s(%d) ได้ทำการเปิดกุญแจ 'Sultan Key' และได้รับยานพาหนะ 'Sultan'", ReturnRoleplayName(playerid), playerid);
            SendAdminsMessage(1, COLOR_GRAY, str);

            PlayerInventory_RemoveEx(playerid, itemid, 1);
        }

        else if(!strcmp(name, "Camper Key", true)){
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

            id = Car_Create(PlayerData[playerid][pID], 483, x, y + 2, z + 1, angle, random(127), random(127));
            if (id == -1) return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");
            if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS) return SendClientMessage(playerid, -1, "คุณมียานพาหนะเต็มแล้ว");

            LinkVehicleToInterior(id, int);
            SetVehicleVirtualWorld(id, world);

            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Camper Key", "คุณได้เปิดกุญแจ Camper Key และได้รับยานพาหนะ Camper เรีบยร้อยแล้ว", "ตกลง", "");
            new str[128];
            format(str, sizeof(str), "[เปิดกุญแจยานพาหนะ]: ผู้เล่น %s(%d) ได้ทำการเปิดกุญแจ 'Camper Key' และได้รับยานพาหนะ 'Camper'", ReturnRoleplayName(playerid), playerid);
            SendAdminsMessage(1, COLOR_GRAY, str);

            PlayerInventory_RemoveEx(playerid, itemid, 1);
        }

        else if(!strcmp(name, "Kart Key", true)){
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

            id = Car_Create(PlayerData[playerid][pID], 571, x, y + 2, z + 1, angle, random(127), random(127));
            if (id == -1) return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");
            if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS) return SendClientMessage(playerid, -1, "คุณมียานพาหนะเต็มแล้ว");

            LinkVehicleToInterior(id, int);
            SetVehicleVirtualWorld(id, world);

            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Kart Key", "คุณได้เปิดกุญแจ Kart Key และได้รับยานพาหนะ Kart เรีบยร้อยแล้ว", "ตกลง", "");
            new str[128];
            format(str, sizeof(str), "[เปิดกุญแจยานพาหนะ]: ผู้เล่น %s(%d) ได้ทำการเปิดกุญแจ 'Kart Key' และได้รับยานพาหนะ 'Kart'", ReturnRoleplayName(playerid), playerid);
            SendAdminsMessage(1, COLOR_GRAY, str);

            PlayerInventory_RemoveEx(playerid, itemid, 1);
        }

        else if(!strcmp(name, "BF Injection Key", true)){
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

            id = Car_Create(PlayerData[playerid][pID], 424, x, y + 2, z + 1, angle, random(127), random(127));
            if (id == -1) return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");
            if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS) return SendClientMessage(playerid, -1, "คุณมียานพาหนะเต็มแล้ว");

            LinkVehicleToInterior(id, int);
            SetVehicleVirtualWorld(id, world);

            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "BF Injection", "คุณได้เปิดกุญแจ BF Injection และได้รับยานพาหนะ BF Injection เรีบยร้อยแล้ว", "ตกลง", "");
            new str[128];
            format(str, sizeof(str), "[เปิดกุญแจยานพาหนะ]: ผู้เล่น %s(%d) ได้ทำการเปิดกุญแจ 'BF Injection' และได้รับยานพาหนะ 'BF Injection'", ReturnRoleplayName(playerid), playerid);
            SendAdminsMessage(1, COLOR_GRAY, str);

            PlayerInventory_RemoveEx(playerid, itemid, 1);
        }

        else if(!strcmp(name, "DFT-30 Key", true)){
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

            id = Car_Create(PlayerData[playerid][pID], 578, x, y + 2, z + 1, angle, random(127), random(127));
            if (id == -1) return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างยานพาหนะไดนามิคเกินขีดจำกัดแล้ว");
            if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS) return SendClientMessage(playerid, -1, "คุณมียานพาหนะเต็มแล้ว");

            LinkVehicleToInterior(id, int);
            SetVehicleVirtualWorld(id, world);

            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "DFT-30 Key", "คุณได้เปิดกุญแจ DFT-30 Key และได้รับยานพาหนะ DFT-30 เรีบยร้อยแล้ว", "ตกลง", "");
            new str[128];
            format(str, sizeof(str), "[เปิดกุญแจยานพาหนะ]: ผู้เล่น %s(%d) ได้ทำการเปิดกุญแจ 'DFT-30 Key' และได้รับยานพาหนะ 'DFT-30'", ReturnRoleplayName(playerid), playerid);
            SendAdminsMessage(1, COLOR_GRAY, str);

            PlayerInventory_RemoveEx(playerid, itemid, 1);
        }

        //================================//

        else if(!strcmp(name, "Boombox", true)){
            if(CheckBoombox[playerid] == 0){
                CheckBoombox[playerid] = 1;
                SetPlayerAttachedObject(playerid,8,2226,6,0.365000,0.027000,0.145000,0.000000,-111.299995,0.000000,1.000000,1.000000,1.000000);
                SendClientMessage(playerid, -1, "[คำแนะนำ]: ใช้ '/boombox' เพื่อใช้งาน");
            }
            else if(CheckBoombox[playerid] == 1){
                CheckBoombox[playerid] = 0;
                RemoveAttachedObject(playerid, 8);
            }
            
        }

        //Marry
        else if(!strcmp(name, "Marry Box", true)){
            new id = PlayerInventory_AddItem(playerid, "Marry Card", 19194, 1);
            if (id == -1)
                return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เปิดกล่อง 'Marry Box' และได้รับ 'Marry Card' เอาไว้สำหรับขอแต่งงาน");
            PlayerInventory_Remove(playerid, "Marry Box", 1);
        }

        else if(!strcmp(name, "Marry Card", true)){
            if(PlayerData[playerid][pMarrySQLID] == 0){
                ShowTargetUseMarry(playerid);
                return OnPlayerInventory_Close(playerid);
            }else{
                Dialog_ShowEasy(playerid, ShowCardMarry, DIALOG_STYLE_LIST, "โชว์บัตรแต่งงาน", "ดู\nโชว์ให้ผู้เล่นอื่น", "ตกลง", "ยกเลิก");
            }
        }

        else if(!strcmp(name, "Marry Ring", true)){
            if(PlayerData[playerid][pMarrySQLID] == 0) return ErrorMsg(playerid, "คุณไม่มีคู่รัก");
            if(RingShow[playerid] == 0){
                RingShow[playerid] = 1;
                SetPlayerAttachedObject(playerid,4,1316,1,0.717999,0.029000,0.011000,0.000000,88.599914,0.000000,0.130000,0.134000,0.112999);
                SendClientMessage(playerid, COLOR_YELLOW, "คุณได้เปิดการแสดงแหวนคู่รักแล้ว");
            }
            else if(RingShow[playerid] == 1){
                RingShow[playerid] = 0;
                RemoveAttachedObject(playerid, 4);
                SendClientMessage(playerid, COLOR_YELLOW, "คุณได้ปิดการแสดงแหวนคู่รักแล้ว");
            }
        }

        else if(!strcmp(name, "Marry Flower", true)){
            if(CheckHoldFlower[playerid] == 0){
                CheckHoldFlower[playerid] = 1;
                SetPlayerAttachedObject(playerid,5,325,6,-0.017999,0.026000,0.000000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
            }
            else if(CheckHoldFlower[playerid] == 1){
                CheckHoldFlower[playerid] = 0;
                RemoveAttachedObject(playerid, 5);
            }
        }

        else if(!strcmp(name, "EXP X2 Bottle", true)){
            PlayerData[playerid][pUseExpx2]++;
            Jdz_Exp_Hud_Show(playerid);
            PlayerInventory_RemoveEx(playerid, itemid, 1);
        }

        else if(!strcmp(name, "Repair Kit", true)){
            if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ErrorMsg(playerid, "คุณจำเป็นต้องลงจากยานพาหนะ");
            if(GetGroupType(playerid) != GROUP_MECHANIC) return ErrorMsg(playerid, "คุณไม่มีทักษะเกี่ยวกับการซ่อมรถ");
            new carid = -1;
	        if((carid = Car_Nearest(playerid)) != -1){
                new EngineStatus = GetEngineStatus(CarData[carid][carVehicle]);
                if (!IsDoorVehicle(CarData[carid][carVehicle])){
                    if(EngineStatus) return ErrorMsg(playerid, "จำเป็นต้องดับเครื่องยนต์ก่อนจะเริ่มซ่อม");
                    ToolType[playerid] = 1;
                    SetPlayerMechanicRepairVehicle(playerid, CarData[carid][carVehicle], 1);
                }
                else{
                    if (IsPlayerNearHood(playerid, CarData[carid][carVehicle])){
                        if(EngineStatus) return ErrorMsg(playerid, "จำเป็นต้องดับเครื่องยนต์ก่อนจะเริ่มซ่อม");
                        if (!GetHoodStatus(CarData[carid][carVehicle])) return ErrorMsg(playerid, "กระโปรงรถคันนี้ปิดอยู่");
                        ToolType[playerid] = 1;
                        SetPlayerMechanicRepairVehicle(playerid, CarData[carid][carVehicle], 1);
                    }
                }
            }
        }

        else if(!strcmp(name, "Quick Repair Kit", true)){
            if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ErrorMsg(playerid, "คุณจำเป็นต้องลงจากยานพาหนะ");
            new carid = -1;
	        if((carid = Car_Nearest(playerid)) != -1){
                new EngineStatus = GetEngineStatus(CarData[carid][carVehicle]);
                if (!IsDoorVehicle(CarData[carid][carVehicle])){
                    if(EngineStatus) return ErrorMsg(playerid, "จำเป็นต้องดับเครื่องยนต์ก่อนจะเริ่มซ่อม");
                    ToolType[playerid] = 2;
                    SetPlayerMechanicRepairVehicle(playerid, CarData[carid][carVehicle], 2);
                }
                else{
                    if (IsPlayerNearHood(playerid, CarData[carid][carVehicle])){
                        if(EngineStatus) return ErrorMsg(playerid, "จำเป็นต้องดับเครื่องยนต์ก่อนจะเริ่มซ่อม");
                        if (!GetHoodStatus(CarData[carid][carVehicle])) return ErrorMsg(playerid, "กระโปรงรถคันนี้ปิดอยู่");
                        ToolType[playerid] = 2;
                        SetPlayerMechanicRepairVehicle(playerid, CarData[carid][carVehicle], 2);
                    }
                }
            }
        }

        else if(!strcmp(name, "Bandage", true)){
            SetPlayerHealingWithBandage(playerid);
        }


        else if(!strcmp(name, "Medkit", true)){
            new Float:xx, Float:yy, Float:zz;
            GetPlayerPos(playerid, xx, yy, zz);
            if(xx > 1354 && xx < 1558 && yy > 661.5 && yy < 802.5) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "คุณไม่สามารถทำการปฐมพยาบาลในพื้นที่นี้ได้!", "ตกลง", "");

            if(GetGroupType(playerid) != GROUP_MEDIC) return ErrorMsg(playerid, "คุณไม่มีความรู้ด้านการรักษา");

            new stringplayer[1024];
            new count;
            new menu[20];
            new status[64];
            foreach(new x : Player){
                if(!LoggedIn[x]) continue;
                if(x == playerid) continue;
                if(IsPlayerNearPlayer(playerid, x, 3.0)){
                    if(PlayerData[x][pInjured] == 1)
                        status = "บาดเจ็บ";
                    else
                        status = "ไม่ได้บาดเจ็บ";

                    format(menu, 20, "menu%d", count++);
                    SetPVarInt(playerid, menu, x);
                    format(stringplayer, sizeof(stringplayer), "%s %s(%d) (%s)\n", stringplayer, ReturnRoleplayName(x), x, status);
                }
                if(count >= 20) break;
            }
            if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "เลือกผู้เล่นที่คุณต้องการจะรักษา", "ไม่มีใครอยู่ใกล้คุณเลย", "ตกลง", "ยกเลิก");
            else Dialog_ShowEasy(playerid, CprPlayer, DIALOG_STYLE_LIST, "เลือกผู้เล่นที่คุณต้องการจะรักษา", stringplayer, "เลือก", "ยกเลิก");
            return OnPlayerInventory_Close(playerid);
        }

        else if(!strcmp(name, "Blood bag", true)){

            new Float:x, Float:y, Float:z;
            GetPlayerPos(playerid, x, y, z);
            if(x > 1354 && x < 1558 && y > 661.5 && y < 802.5) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "คุณไม่สามารถทำการปฐมพยาบาลในพื้นที่นี้ได้!", "ตกลง", "");

            Dialog_ShowEasy(playerid, BloodBagMenu, DIALOG_STYLE_LIST, "Blood Bag (ถุงเลือด)", "- ใช้กับตัวเอง\n- ใช้กับผู้เล่นใกล้ๆ", "เลือก", "ยกเลิก");
            return OnPlayerInventory_Close(playerid);
        }

        //Weapon
        //เพิ่มอาวุธ
        else if(!strcmp(name, "Katana", true)){
            if(ServerData[ServerUseWeapon] == 1) return ErrorMsg(playerid, "ระบบการใช้อาวุธถูกปิด");
            if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณติดคุกอยู่ไม่สามารถใช้งานได้");

            if(PlayerData[playerid][pMyWeapon][2] != 0) return ErrorMsg(playerid, "กรุณาเก็บอาวุธที่ใช้ก่อน");

            PlayerData[playerid][pMyWeapon][2] = 8;
            PlayerData[playerid][pMyAmmo][2] = 1;
            PlayerData[playerid][pMyWeaponLevel][2] = Inventory_Player[playerid][itemid][itemLevel];
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            PlayerData[playerid][pDelayWeapon][2] = 60;
            GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][2], PlayerData[playerid][pMyAmmo][2]);

            if(TogAlertLog){
                new _message[128];
                format(_message, sizeof(_message), "> [%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
                DCC_SendChannelMessage(UseWeaponChannel, _message);
            }

            Log_Write("logs/useweapon.txt", "[%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
        }

        else if(!strcmp(name, "Golf Club", true)){

            if(ServerData[ServerUseWeapon] == 1) return ErrorMsg(playerid, "ระบบการใช้อาวุธถูกปิด");

            if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณติดคุกอยู่ไม่สามารถใช้งานได้");

            if(PlayerData[playerid][pMyWeapon][2] != 0)
                return ErrorMsg(playerid, "กรุณาเก็บอาวุธที่ใช้ก่อน");

            PlayerData[playerid][pMyWeapon][2] = 2;
            PlayerData[playerid][pMyAmmo][2] = 1;
            PlayerData[playerid][pMyWeaponLevel][2] = Inventory_Player[playerid][itemid][itemLevel];
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            PlayerData[playerid][pDelayWeapon][2] = 60;
            GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][2], PlayerData[playerid][pMyAmmo][2]);

            if(TogAlertLog){
                new _message[64];
                format(_message, sizeof(_message), "> [%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
                DCC_SendChannelMessage(UseWeaponChannel, _message);
            }

            Log_Write("logs/useweapon.txt", "[%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
        }

        else if(!strcmp(name, "Shovel", true)){

            if(ServerData[ServerUseWeapon] == 1) return ErrorMsg(playerid, "ระบบการใช้อาวุธถูกปิด");
            if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณติดคุกอยู่ไม่สามารถใช้งานได้");

            if(PlayerData[playerid][pMyWeapon][2] != 0)
                return ErrorMsg(playerid, "กรุณาเก็บอาวุธที่ใช้ก่อน");

            PlayerData[playerid][pMyWeapon][2] = 6;
            PlayerData[playerid][pMyAmmo][2] = 1;
            PlayerData[playerid][pMyWeaponLevel][2] = Inventory_Player[playerid][itemid][itemLevel];
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            PlayerData[playerid][pDelayWeapon][2] = 60;
            GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][2], PlayerData[playerid][pMyAmmo][2]);

            if(TogAlertLog){
                new _message[64];
                format(_message, sizeof(_message), "> [%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
                DCC_SendChannelMessage(UseWeaponChannel, _message);
            }

            Log_Write("logs/useweapon.txt", "[%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
        }

        else if(!strcmp(name, "Pool cue", true)){

            if(ServerData[ServerUseWeapon] == 1) return ErrorMsg(playerid, "ระบบการใช้อาวุธถูกปิด");

            if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณติดคุกอยู่ไม่สามารถใช้งานได้");

            if(PlayerData[playerid][pMyWeapon][2] != 0)
                return ErrorMsg(playerid, "กรุณาเก็บอาวุธที่ใช้ก่อน");

            PlayerData[playerid][pMyWeapon][2] = 7;
            PlayerData[playerid][pMyAmmo][2] = 1;
            PlayerData[playerid][pMyWeaponLevel][2] = Inventory_Player[playerid][itemid][itemLevel];
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            PlayerData[playerid][pDelayWeapon][2] = 60;
            GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][2], PlayerData[playerid][pMyAmmo][2]);

            if(TogAlertLog){
                new _message[64];
                format(_message, sizeof(_message), "> [%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
                DCC_SendChannelMessage(UseWeaponChannel, _message);
            }

            Log_Write("logs/useweapon.txt", "[%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
        }

        else if(!strcmp(name, "Cane", true)){

            if(ServerData[ServerUseWeapon] == 1) return ErrorMsg(playerid, "ระบบการใช้อาวุธถูกปิด");

            if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณติดคุกอยู่ไม่สามารถใช้งานได้");

            if(PlayerData[playerid][pMyWeapon][2] != 0)
                return ErrorMsg(playerid, "กรุณาเก็บอาวุธที่ใช้ก่อน");

            PlayerData[playerid][pMyWeapon][2] = 15;
            PlayerData[playerid][pMyAmmo][2] = 1;
            PlayerData[playerid][pMyWeaponLevel][2] = Inventory_Player[playerid][itemid][itemLevel];
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            PlayerData[playerid][pDelayWeapon][2] = 60;
            GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][2], PlayerData[playerid][pMyAmmo][2]);
            
            if(TogAlertLog){
                new _message[64];
                format(_message, sizeof(_message), "> [%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
                DCC_SendChannelMessage(UseWeaponChannel, _message);
            }

            Log_Write("logs/useweapon.txt", "[%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
        }

        else if(!strcmp(name, "Brass knuckles", true)){

            if(ServerData[ServerUseWeapon] == 1) return ErrorMsg(playerid, "ระบบการใช้อาวุธถูกปิด");

            if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณติดคุกอยู่ไม่สามารถใช้งานได้");

            if(PlayerData[playerid][pMyWeapon][2] != 0)
                return ErrorMsg(playerid, "กรุณาเก็บอาวุธที่ใช้ก่อน");

            PlayerData[playerid][pMyWeapon][2] = 1;
            PlayerData[playerid][pMyAmmo][2] = 1;
            PlayerData[playerid][pMyWeaponLevel][2] = Inventory_Player[playerid][itemid][itemLevel];
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            PlayerData[playerid][pDelayWeapon][2] = 60;
            GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][2], PlayerData[playerid][pMyAmmo][2]);
            
            if(TogAlertLog){
                new _message[64];
                format(_message, sizeof(_message), "> [%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
                DCC_SendChannelMessage(UseWeaponChannel, _message);
            }

            Log_Write("logs/useweapon.txt", "[%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
        }

        else if(!strcmp(name, "Baseball bat", true)){

            if(ServerData[ServerUseWeapon] == 1) return ErrorMsg(playerid, "ระบบการใช้อาวุธถูกปิด");

            if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณติดคุกอยู่ไม่สามารถใช้งานได้");

            if(PlayerData[playerid][pMyWeapon][2] != 0)
                return ErrorMsg(playerid, "กรุณาเก็บอาวุธที่ใช้ก่อน");

            PlayerData[playerid][pMyWeapon][2] = 5;
            PlayerData[playerid][pMyAmmo][2] = 1;
            PlayerData[playerid][pMyWeaponLevel][2] = Inventory_Player[playerid][itemid][itemLevel];
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            PlayerData[playerid][pDelayWeapon][2] = 60;
            GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][2], PlayerData[playerid][pMyAmmo][2]);
            
            if(TogAlertLog){
                new _message[64];
                format(_message, sizeof(_message), "> [%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
                DCC_SendChannelMessage(UseWeaponChannel, _message);
            }

            Log_Write("logs/useweapon.txt", "[%s] %s Use Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
        }

        else if(!strcmp(name, "M4A1", true)){

            if(ServerData[ServerUseWeapon] == 1) return ErrorMsg(playerid, "ระบบการใช้อาวุธถูกปิด");

            if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณติดคุกอยู่ไม่สามารถใช้งานได้");

            if(PlayerData[playerid][pMyWeapon][0] != 0)
                return ErrorMsg(playerid, "กรุณาเก็บอาวุธที่ใช้ก่อน");

            if(Inventory_Player[playerid][itemid][itemAmmo] == 0){
                PlayerData[playerid][pMyWeapon][0] = 31;
                PlayerData[playerid][pMyAmmo][0] = 0;
                PlayerInventory_Remove(playerid, "M4A1");
                SetPlayerAttachedObject(playerid,5,356,6,-0.001999,0.000000,0.018999,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
            }
            else{
                PlayerData[playerid][pMyWeapon][0] = 31;
                PlayerData[playerid][pMyAmmo][0] = Inventory_Player[playerid][itemid][itemAmmo];
                RemoveAttachedObject(playerid, 5);
                GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][0], PlayerData[playerid][pMyAmmo][0]);
                PlayerPlaySoundEx(playerid, 36401);
                SetTimerEx("PlayReloadAnimation", 500, false, "ii", playerid, 31);
                PlayerInventory_Remove(playerid, "M4A1");
            }
            PlayerData[playerid][pDelayWeapon][0] = 60;
            Log_Write("logs/useweapon.txt", "[%s] %s User Weapon %s", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][0]));
        }

        else if(!strcmp(name, "5.56x45mm", true)){
            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
				if(PlayerData[playerid][pMyAmmo][0] == 0){
					new weaponid = PlayerData[playerid][pMyWeapon][0];
					if(weaponid == 31){
						if(PlayerInventory_AllCount(playerid, "5.56x45mm") > 0){
							PlayerInventory_Remove(playerid, "5.56x45mm", 1);
							PlayerData[playerid][pMyAmmo][0] = 30;
							RemoveAttachedObject(playerid, 5);
							GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][0], PlayerData[playerid][pMyAmmo][0]);
							PlayerPlaySoundEx(playerid, 36401);
							PlayReloadAnimation(playerid, weaponid);
						}
					}
				}
			}
        }

        else if(!strcmp(name, "Clot 45", true)){

            if(ServerData[ServerUseWeapon] == 1) return ErrorMsg(playerid, "ระบบการใช้อาวุธถูกปิด");

            if(PlayerData[playerid][pJail] != 0) return ErrorMsg(playerid, "คุณติดคุกอยู่ไม่สามารถใช้งานได้");

            if(PlayerData[playerid][pMyWeapon][1] != 0)
                return ErrorMsg(playerid, "กรุณาเก็บอาวุธที่ใช้ก่อน");

            if(Inventory_Player[playerid][itemid][itemAmmo] == 0){
                PlayerData[playerid][pMyWeapon][1] = 22;
                PlayerData[playerid][pMyAmmo][1] = 0;
                PlayerInventory_Remove(playerid, "Clot 45");
                SetPlayerAttachedObject(playerid,6,346,6,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
            }
            else{
                PlayerData[playerid][pMyWeapon][1] = 22;
                PlayerData[playerid][pMyAmmo][1] = Inventory_Player[playerid][itemid][itemAmmo];
                RemoveAttachedObject(playerid, 6);
                GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][1], PlayerData[playerid][pMyAmmo][1]);
                PlayerPlaySoundEx(playerid, 36401);
                SetTimerEx("PlayReloadAnimation", 500, false, "ii", playerid, 22);
                PlayerInventory_Remove(playerid, "Clot 45");
            }
            PlayerData[playerid][pDelayWeapon][1] = 60;
            Log_Write("logs/useweapon.txt", "[%s] %s User Weapon %s", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][0]));
        }

        else if(!strcmp(name, "9mm", true)){
            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
				if(PlayerData[playerid][pMyAmmo][1] == 0){
					new weaponid = PlayerData[playerid][pMyWeapon][1];
					if(weaponid == 22){
						if(PlayerInventory_AllCount(playerid, "9mm") > 0){
							PlayerInventory_Remove(playerid, "9mm", 1);
							PlayerData[playerid][pMyAmmo][1] = 17;
							RemoveAttachedObject(playerid, 6);
							GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][1], PlayerData[playerid][pMyAmmo][1]);
							PlayerPlaySoundEx(playerid, 36401);
							PlayReloadAnimation(playerid, weaponid);
						}
					}
				}
			}
        }

        new skin = strval(name);
        if(skin > 0 || skin < 311){
            new stringchar[64];
            new stringcharEx[64];
            format(stringchar, sizeof(stringchar), "%d", skin);
            if(!strcmp(name, stringchar, true)){

                if(ServerRestart) return ErrorMsg(playerid, "ฟังก์ชั่นนี้ถูกปิดใช้งานชั่วคราว");

                if(PlayerData[playerid][pJail] != 0) {
                    SendPlayerToPrisonNow(playerid);
                    return ErrorMsg(playerid, "คุณเป็นนักโทษไม่สามารถเปลี่ยนสกินได้");
                }

                if(PlayerData[playerid][pGender] == 1)
                    if(CheckIsFeMaleSkin(skin) == 1)
                        return ErrorMsg(playerid, "ชุดนี้เป็นของเพศ หญิง คุณไม่สามารถใส่ได้");

                if(PlayerData[playerid][pGender] == 2)
                    if(CheckIsMaleSkin(skin) == 1)
                        return ErrorMsg(playerid, "ชุดนี้เป็นของเพศ ชาย คุณไม่สามารถใส่ได้");

                if(PlayerData[playerid][pUseSkin] == 1){
                    format(stringcharEx, sizeof(stringcharEx), "%d", PlayerData[playerid][pSkin]);
                    new id = PlayerInventory_AddItem(playerid, stringcharEx, 2384, 1);
                    if (id == -1){
                        return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                    }
                    
                    SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้สวมใส่ชุด: %d เรียบร้อยแล้ว", skin);
                    PlayerData[playerid][pSkin] = skin;
                    SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

                    PlayerInventory_Remove(playerid, name, 1);
                    Character_Save(playerid);
                }   
                else{
                    PlayerData[playerid][pSkin] = skin;
                    SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
                    SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้สวมใส่ชุด: %d เรียบร้อยแล้ว", skin);
                    PlayerData[playerid][pUseSkin] = 1;
                    PlayerInventory_Remove(playerid, name, 1);
                    Character_Save(playerid);
                }
            }
        }
        if(PlayerShowButton[playerid]) RemoveUseInfoButton(playerid);
        if(PlayerInventoryStatus[playerid]) OnPlayerInventory_Close(playerid);
        if(PlayerCharacterShow[playerid]) PlayerCharacterTD_Render(playerid);
    }
    return 1;
}

forward OnPlayerInventory_InfoItem(playerid, const item[], model, itemid);
public OnPlayerInventory_InfoItem(playerid, const item[], model, itemid){
    if(itemid == -1) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
    new string[512];
    
    if(CheckItemIsGun(item) != -1){
        format(string, sizeof string, "ไอเท็ม: %s\
        \nจำนวนไอเท็ม: %d\
        \nกระสุนในอาวุธ: %d\
        \nเลเวลไอเท็ม: %d\
        \n[ คำแนะนำ ]\n", item, Inventory_Player[playerid][itemid][itemQuantity], Inventory_Player[playerid][itemid][itemAmmo], Inventory_Player[playerid][itemid][itemLevel]);
    }else{
        format(string, sizeof string, "ไอเท็ม: %s\
        \nจำนวนไอเท็ม: %d\
        \nเลเวลไอเท็ม: %d\
        \n[ คำแนะนำ ]\n", item, Inventory_Player[playerid][itemid][itemQuantity], Inventory_Player[playerid][itemid][itemLevel]);
    }

    if(!strcmp(item, "Orange", true)){
        format(string ,sizeof string, "%s- ใช้สำหรับกินเพื่อเพิ่มค่าอาหารและความกระหาย", string);
    }
    else if(!strcmp(item, "Medkit", true)){
        format(string ,sizeof string, "%s- ใช้สำหรับรักษาบาดแผลต่างๆ", string);
    }
    else if(!strcmp(item, "Red Apple Wine", true)){
        format(string ,sizeof string, "%s- ใช้สำหรับกินเพิ่มลดความเครียด 50 เปอร์เซ็นต์ และเพิ่ม Stamina 10 เปอร์เซ็นต์", string);
    }
    else if(!strcmp(item, "Green Apple Wine", true)){
        format(string ,sizeof string, "%s- ใช้สำหรับกินเพิ่มลดความเครียด 50 เปอร์เซ็นต์ และเพิ่ม Stamina 10 เปอร์เซ็นต์", string);
    }
    else{
        format(string ,sizeof string, "%s- ไม่พบข้อมูลคำแนะนำในระบบ", string);
    }

    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "รายละเอียดไอเท็ม [Item Info]", string, "ตกลง", "");
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(LoggedIn[playerid]){
        if(newkeys & KEY_YES){
            if(PlayerEditPositionInventory[playerid] || PlayerEditColorInventory[playerid]){

                if(IsAndroidPlayer(playerid)){
                    for(new i=0; i<4; i++){
                        PlayerTextDrawHide(playerid, ArrowEditInv[playerid][i]);
                        PlayerTextDrawDestroy(playerid, ArrowEditInv[playerid][i]);
                    }
                }

                stop UpdateInventory[playerid];
                PlayerEditPositionInventory[playerid] = false;

                if(PlayerEditColorInventory[playerid]){
                    PlayerInventoryHoverCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid]-10,PlayerInventoryColorG[playerid]-10,PlayerInventoryColorB[playerid]-10,155);
                }

                PlayerEditColorInventory[playerid] = false;

                GameTextForPlayer(playerid, "~W~Inventory ~G~Edited", 3000, 5);
                OnPlayerInventory_Close(playerid);
                OnPlayerHomeInv_Close(playerid);
                TogglePlayerControllable(playerid, 1);
            }
        }
    }
    return 1;
}

/*Dialog:EditColorInventory(playerid, response, listitem, inputtext[]){
    if(!response) {
        PlayerCantSelectTextDraw[playerid] = false;
        return 1;
    }
    if(response){
        new string[128];
        if(listitem == 0){
            format(string, sizeof string, "โค้ดจะอยู่ในรูปแบบ RGBA เช่น [ 0xFFA200FF ]\
            \n- สามารถหาข้อมูลได้ในอินเตอร์เน็ตโดยการพิมพ์ Code Color HTML");
            Dialog_ShowEasy(playerid, EditColorInventory2, DIALOG_STYLE_INPUT, "ใส่โค้ดสีสำหรับกระเป๋าของคุณ", string, "ตกลง", "ปิด");
        }

        if(listitem == 1){
            format(string, sizeof string, "โค้ดจะอยู่ในรูปแบบ RGBA เช่น [ 0xFFA200AA ]\
            \n- สามารถหาข้อมูลได้ในอินเตอร์เน็ตโดยการพิมพ์ Code Color HTML");
            Dialog_ShowEasy(playerid, EditColorInventory3, DIALOG_STYLE_INPUT, "ใส่โค้ดสีสำหรับการ Hover เมนูกระเป๋า", string, "ตกลง", "ปิด");
        }
    }
    return 1;
}

Dialog:EditColorInventory2(playerid, response, listitem, inputtext[]){
    if(!response) {
        PlayerCantSelectTextDraw[playerid] = false;
        return 1;
    }
    if(response){
        new string[128], color;
        if (sscanf(inputtext, "x", color)) {
			format(string, sizeof string, "[!] รูปแบบของโค้ดสีไม่ถูกต้อง \nโค้ดจะอยู่ในรูปแบบ RGBA เช่น [ 0xFFA200FF ]\
			\n- สามารถหาข้อมูลได้ในอินเตอร์เน็ตโดยการพิมพ์ Code Color HTML");
			Dialog_ShowEasy(playerid, EditColorInventory2, DIALOG_STYLE_INPUT, "ใส่โค้ดสีสำหรับกระเป๋าของคุณ", string, "ตกลง", "ปิด");
			return true;
		}

        PlayerInventoryCodeColor[playerid] = color;
        GameTextForPlayer(playerid, "~W~Color Inventory ~G~Edit", 3000, 5);
        OnPlayerInventory_Close(playerid);
        TogglePlayerControllable(playerid, 1);
        SendClientMessage(playerid, COLOR_YELLOW, "[!] คุณได้ทำการเปลี่ยนสีกระเป๋าของคุณเรียบร้อยแล้ว");
        PlayerCantSelectTextDraw[playerid] = false;
    }
    return 1;
}

Dialog:EditColorInventory3(playerid, response, listitem, inputtext[]){
    if(!response) {
        PlayerCantSelectTextDraw[playerid] = false;
        return 1;
    }
    if(response){
        new string[128], color;
        if (sscanf(inputtext, "x", color)) {
			format(string, sizeof string, "[!] รูปแบบของโค้ดสีไม่ถูกต้อง \nโค้ดจะอยู่ในรูปแบบ RGBA เช่น [ 0xFFA200AA ]\
			\n- สามารถหาข้อมูลได้ในอินเตอร์เน็ตโดยการพิมพ์ Code Color HTML");
			Dialog_ShowEasy(playerid, EditColorInventory3, DIALOG_STYLE_INPUT, "ใส่โค้ดสีสำหรับการ Hover เมนูกระเป๋า", string, "ตกลง", "ปิด");
			return true;
		}

        PlayerInventoryHoverCodeColor[playerid] = color;
        GameTextForPlayer(playerid, "~W~Color Hover Inventory ~G~Edit", 3000, 5);
        OnPlayerInventory_Close(playerid);
        TogglePlayerControllable(playerid, 1);
        SendClientMessage(playerid, COLOR_YELLOW, "[!] คุณได้ทำการเปลี่ยนสีการ Hover กระเป๋าของคุณเรียบร้อยแล้ว");
        PlayerCantSelectTextDraw[playerid] = false;
    }
    return 1;
}*/

//ปรับการทำงานให้รองรับ APK

timer PlayerUpdateInventory[100](playerid){
    //if(IsAndroidPlayer(playerid)) return 1;

    if(PlayerEditColorInventory[playerid]){
        new Keys,ud,lr;
        GetPlayerKeys(playerid, Keys, ud, lr);

        if(ud == KEY_UP){
            if(PlayerInventoryColorType[playerid] == 0){
                if(PlayerInventoryColorR[playerid] < 255){
                    PlayerInventoryColorR[playerid] += 5;
                    if(PlayerInventoryColorR[playerid] >= 255) PlayerInventoryColorR[playerid] = 255;
                    //printf("[R]: %d", PlayerInventoryColorR[playerid]);
                    PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
                    //printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
                    Update_EditColorInventory(playerid);
                }
            }
            else if(PlayerInventoryColorType[playerid] == 1){
                if(PlayerInventoryColorG[playerid] < 255){
                    PlayerInventoryColorG[playerid] += 5;
                    if(PlayerInventoryColorG[playerid] >= 255) PlayerInventoryColorG[playerid] = 255;
                    //printf("[G]: %d", PlayerInventoryColorG[playerid]);
                    PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
                    //printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
                    Update_EditColorInventory(playerid);
                }
            }
            else if(PlayerInventoryColorType[playerid] == 2){
                if(PlayerInventoryColorB[playerid] < 255){
                    PlayerInventoryColorB[playerid] += 5;
                    if(PlayerInventoryColorB[playerid] >= 255) PlayerInventoryColorB[playerid] = 255;
                    //printf("[G]: %d", PlayerInventoryColorB[playerid]);
                    PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
                    //printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
                    Update_EditColorInventory(playerid);
                }
            }
        }

        if(ud == KEY_DOWN){
            if(PlayerInventoryColorType[playerid] == 0){
                if(PlayerInventoryColorR[playerid] > 0){
                    PlayerInventoryColorR[playerid] -= 5;
                    if(PlayerInventoryColorR[playerid] <= 0) PlayerInventoryColorR[playerid] = 0;
                    //printf("[R]: %d", PlayerInventoryColorR[playerid]);
                    PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
                    //printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
                    Update_EditColorInventory(playerid);
                }
            }
            else if(PlayerInventoryColorType[playerid] == 1){
                if(PlayerInventoryColorG[playerid] > 0){
                    PlayerInventoryColorG[playerid] -= 5;
                    if(PlayerInventoryColorG[playerid] <= 0) PlayerInventoryColorG[playerid] = 0;
                    //printf("[R]: %d", PlayerInventoryColorG[playerid]);
                    PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
                    //printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
                    Update_EditColorInventory(playerid);
                }
            }
            else if(PlayerInventoryColorType[playerid] == 2){
                if(PlayerInventoryColorB[playerid] > 0){
                    PlayerInventoryColorB[playerid] -= 5;
                    if(PlayerInventoryColorB[playerid] <= 0) PlayerInventoryColorB[playerid] = 0;
                    //printf("[R]: %d", PlayerInventoryColorB[playerid]);
                    PlayerInventoryCodeColor[playerid] = RGB::HexToRGBA(PlayerInventoryColorR[playerid],PlayerInventoryColorG[playerid],PlayerInventoryColorB[playerid],255);
                    //printf("[Hex]: %d", PlayerInventoryCodeColor[playerid]);
                    Update_EditColorInventory(playerid);
                }
            }
        }

        if(lr == KEY_RIGHT){
            if(PlayerInventoryColorType[playerid] == 0) {
                PlayerInventoryColorType[playerid] = 1;
                GameTextForPlayer(playerid, "~W~Edit Color ~G~GREEN", 3000, 6);
            }
            else if(PlayerInventoryColorType[playerid] == 1) {
                PlayerInventoryColorType[playerid] = 2; 
                GameTextForPlayer(playerid, "~W~Edit Color ~B~BLUE", 3000, 6);
            }
            else if(PlayerInventoryColorType[playerid] == 2) {
                PlayerInventoryColorType[playerid] = 0;
                GameTextForPlayer(playerid, "~W~Edit Color ~R~RED", 3000, 6);
            }
        }

        if(lr == KEY_LEFT){
            if(PlayerInventoryColorType[playerid] == 0) {
                PlayerInventoryColorType[playerid] = 2;
                GameTextForPlayer(playerid, "~W~Edit Color ~B~BLUE", 3000, 6);
            }
            else if(PlayerInventoryColorType[playerid] == 1) {
                PlayerInventoryColorType[playerid] = 0; 
                GameTextForPlayer(playerid, "~W~Edit Color ~R~RED", 3000, 6);
            }
            else if(PlayerInventoryColorType[playerid] == 2) {
                PlayerInventoryColorType[playerid] = 1;
                GameTextForPlayer(playerid, "~W~Edit Color ~G~GREEN", 3000, 6);
            }
        }
    }

    if(PlayerEditPositionInventory[playerid]){
        new Keys,ud,lr;
        GetPlayerKeys(playerid, Keys, ud, lr);
        
        new Float:speed = 0.0;

        if(Keys & KEY_JUMP){
            speed += 10.0;
        }

        if(ud == KEY_UP){
            if(PlayerPositionInventoryY[playerid] > -30){
                //printf("UP");
                PlayerPositionInventoryY[playerid] -= 5.0 + speed;
                Update_EditPositionInventory(playerid);
            }
        }

        if(ud == KEY_DOWN){
            if(PlayerPositionInventoryY[playerid] < 200){
                //printf("DOWN");
                PlayerPositionInventoryY[playerid] += 5.0 + speed;
                Update_EditPositionInventory(playerid);
            }
        }

        if(lr == KEY_RIGHT){
            if(PlayerPositionInventoryX[playerid] < 50){
                //printf("RIGHT");
                PlayerPositionInventoryX[playerid] += 5.0 + speed;
                Update_EditPositionInventory(playerid);
            }
        }

        if(lr == KEY_LEFT){
            if(PlayerPositionInventoryX[playerid] > -225){
                //printf("LEFT");
                PlayerPositionInventoryX[playerid] -= 5.0 + speed;
                Update_EditPositionInventory(playerid);
            }
        }
    }
    return 1;
}

Update_EditColorInventory(playerid){
    for (new i=0; i<PlayerSlotInventoryCount[playerid]; i++){
  		PlayerTextDrawHide(playerid, PlayerSlotInventoryTextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, PlayerSlotInventoryTextDraw[playerid][i]);
    }

    PlayerSlotInventoryCount[playerid] = 0;
    LoadPlayerInventorySlotTextDraw(playerid);

    //OnPlayerInventory_Render(playerid);

    for(new i=0; i!=MAX_INVENTORYTEXTDRAW; i++){
        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, PlayerInventoryTextDraw[playerid][i]);
    }

    LoadPlayerInventoryTextDraw(playerid);

    for(new i=0; i!=MAX_INVENTORYTEXTDRAW; i++){
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][i]);
    }

    //อัพเดทของบนพื้น
    if(PlayerVicinity[playerid]){
        for(new i=0; i<MAX_VICINITYTEXTDRAW; i++){
            PlayerTextDrawHide(playerid, PlayerVicinityTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerVicinityTextDraw[playerid][i]);
        }

        for (new i=0; i<PlayerSlotVicinityCount[playerid]; i++){
            PlayerTextDrawHide(playerid, PlayerSlotVicinityTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerSlotVicinityTextDraw[playerid][i]);
        }

        PlayerSlotVicinityCount[playerid] = 0;
        LoadPlayerVicinityTextDraw(playerid);
        LoadPlayerVicinitySlotTextDraw(playerid);

        for(new i=0; i<MAX_VICINITYTEXTDRAW; i++){
            PlayerTextDrawShow(playerid, PlayerVicinityTextDraw[playerid][i]);
        }

        //OnPlayerVicinity_Render(playerid);
    }

    //อัพเดทปุ่ม
    if(PlayerGetIndexSlotItem[playerid] != -1 && PlayerShowButton[playerid]){
        PlayerTextDrawHide(playerid, UseButton[playerid]);
        PlayerTextDrawHide(playerid, InfoButton[playerid]);
        PlayerTextDrawDestroy(playerid, UseButton[playerid]);
        PlayerTextDrawDestroy(playerid, InfoButton[playerid]);
        LoadUseInfoButtonTextDraw(playerid);
    }
    
    //อัพเดทสถานะตัวละคร
    if(PlayerCharacterShow[playerid]){
        for (new i=0; i<MAX_CHARTEXT; i++){
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerCharacterTextDraw[playerid][i]);
        }

        LoadPlayerCharacterTextDraw(playerid);

        for(new i=0; i<MAX_CHARTEXT; i++){
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][i]);
        }

        //PlayerCharacterTD_Render(playerid);
    }

    //อัพเดทคลังบ้าน
    if(PlayerUsing_HomeInv[playerid]){
        for(new i=0; i<MAX_HOMETD; i++){
            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerHomeInvTD[playerid][i]);
        }

        for(new i=0; i<PlayerHomeSlotCount[playerid]; i++){
            PlayerTextDrawHide(playerid, PlayerHomeSlotTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerHomeSlotTextDraw[playerid][i]);
        }

        PlayerHomeSlotCount[playerid] = 0;
        LoadHomeInvTextDraw(playerid);
        LoadHomeInvTD_Slot(playerid);
        for(new i=0; i<MAX_HOMETD; i++) PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][i]);
        //OnPlayerHomeInv_Render(playerid);
    }
    return 1;
}

Update_EditPositionInventory(playerid){

    //อัพเดทกระเป๋า
    for (new i=0; i<PlayerSlotInventoryCount[playerid]; i++){
  		PlayerTextDrawHide(playerid, PlayerSlotInventoryTextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, PlayerSlotInventoryTextDraw[playerid][i]);
    }

    PlayerSlotInventoryCount[playerid] = 0;
    LoadPlayerInventorySlotTextDraw(playerid);

    //OnPlayerInventory_Render(playerid);

    for(new i=0; i!=MAX_INVENTORYTEXTDRAW; i++){
        PlayerTextDrawHide(playerid, PlayerInventoryTextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, PlayerInventoryTextDraw[playerid][i]);
    }

    LoadPlayerInventoryTextDraw(playerid);

    for(new i=0; i!=MAX_INVENTORYTEXTDRAW; i++){
        PlayerTextDrawShow(playerid, PlayerInventoryTextDraw[playerid][i]);
    }

    //อัพเดทของบนพื้น
    if(PlayerVicinity[playerid]){
        for(new i=0; i<MAX_VICINITYTEXTDRAW; i++){
            PlayerTextDrawHide(playerid, PlayerVicinityTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerVicinityTextDraw[playerid][i]);
        }

        for (new i=0; i<PlayerSlotVicinityCount[playerid]; i++){
            PlayerTextDrawHide(playerid, PlayerSlotVicinityTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerSlotVicinityTextDraw[playerid][i]);
        }

        PlayerSlotVicinityCount[playerid] = 0;
        LoadPlayerVicinityTextDraw(playerid);
        LoadPlayerVicinitySlotTextDraw(playerid);

        for(new i=0; i<MAX_VICINITYTEXTDRAW; i++){
            PlayerTextDrawShow(playerid, PlayerVicinityTextDraw[playerid][i]);
        }

        //OnPlayerVicinity_Render(playerid);
    }

    //อัพเดทปุ่ม
    if(PlayerGetIndexSlotItem[playerid] != -1 && PlayerShowButton[playerid]){
        PlayerTextDrawHide(playerid, UseButton[playerid]);
        PlayerTextDrawHide(playerid, InfoButton[playerid]);
        PlayerTextDrawDestroy(playerid, UseButton[playerid]);
        PlayerTextDrawDestroy(playerid, InfoButton[playerid]);
        LoadUseInfoButtonTextDraw(playerid);
    }
    
    //อัพเดทสถานะตัวละคร
    if(PlayerCharacterShow[playerid]){
        for (new i=0; i<MAX_CHARTEXT; i++){
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerCharacterTextDraw[playerid][i]);
        }

        LoadPlayerCharacterTextDraw(playerid);

        for(new i=0; i<MAX_CHARTEXT; i++){
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][i]);
        }

        //PlayerCharacterTD_Render(playerid);
    }

    //อัพเดทคลังบ้าน
    if(PlayerUsing_HomeInv[playerid]){
        for(new i=0; i<MAX_HOMETD; i++){
            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerHomeInvTD[playerid][i]);
        }

        for(new i=0; i<PlayerHomeSlotCount[playerid]; i++){
            PlayerTextDrawHide(playerid, PlayerHomeSlotTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PlayerHomeSlotTextDraw[playerid][i]);
        }

        PlayerHomeSlotCount[playerid] = 0;

        LoadHomeInvTextDraw(playerid);
        LoadHomeInvTD_Slot(playerid);
        for(new i=0; i<MAX_HOMETD; i++) PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][i]);
        //OnPlayerHomeInv_Render(playerid);
    }
    return 1;
}

/*CMD:openinv(playerid, params[]){
    OnPlayerInventory_Open(playerid);
    return 1;
}

CMD:closeinv(playerid, params[]){
    OnPlayerInventory_Close(playerid);
    return 1;
}*/

LoadPlayerVicinitySlotTextDraw(playerid){
    new Float: modelx = 259.0, Float: modely = 60.0;
    new Float: amountx = 285.0, Float: amounty = 82.0;
    for(new i=0; i<MAX_VICINITY_ROWS; i++){
        for(new j=0; j<MAX_VICINITY_COLUMN; j++){
            PlayerSlotVicinityModel[playerid][i][j] = PlayerSlotVicinityCount[playerid];
            PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]] = CreatePlayerTextDraw(playerid, modelx+PlayerPositionInventoryX[playerid], modely+PlayerPositionInventoryY[playerid], "Preview_Model");
            PlayerTextDrawFont(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 5);
            PlayerTextDrawLetterSize(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 28.000000, 31.500000);
            PlayerTextDrawSetOutline(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 0);
            PlayerTextDrawSetShadow(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 0);
            PlayerTextDrawAlignment(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 1);
            PlayerTextDrawColor(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], -1);
            PlayerTextDrawBackgroundColor(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 842150655);
            PlayerTextDrawBoxColor(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 255);
            PlayerTextDrawUseBox(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 0);
            PlayerTextDrawSetProportional(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 1);
            PlayerTextDrawSetPreviewModel(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawSetPreviewVehCol(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 1, 1);
            PlayerTextDrawSetSelectable(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]++], 1);

            PlayerSlotVicinityAmount[playerid][i][j] = PlayerSlotVicinityCount[playerid];
            PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]] = CreatePlayerTextDraw(playerid, amountx+PlayerPositionInventoryX[playerid], amounty+PlayerPositionInventoryY[playerid], "1000");
            PlayerTextDrawFont(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 1);
            PlayerTextDrawLetterSize(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 0.170833, 0.800000);
            PlayerTextDrawTextSize(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 0);
            PlayerTextDrawSetShadow(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 0);
            PlayerTextDrawAlignment(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 3);
            PlayerTextDrawColor(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], -1);
            PlayerTextDrawBackgroundColor(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 255);
            PlayerTextDrawBoxColor(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 50);
            PlayerTextDrawUseBox(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 0);
            PlayerTextDrawSetProportional(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]], 1);
            PlayerTextDrawSetSelectable(playerid, PlayerSlotVicinityTextDraw[playerid][PlayerSlotVicinityCount[playerid]++], 0);
        
            modelx += 29.0;
            amountx += 29.0;
        }

        modelx = 259.0;
        amountx = 285.0;

        modely += 33.0;
        amounty += 33.0;

    }
    return 1;
}

LoadUseInfoButtonTextDraw(playerid){
    new Float:useX = 428.0, Float:useY = 76.0;
    new Float:infoX = 428.0, Float:infoY = 91.0;
    PlayerShowButton[playerid] = true;
    for(new i; i<MAX_INV_MENU_ROWS; i++){
        for(new j; j<MAX_INV_MENU_COLUMN; j++){
            if(PlayerInvListItemRows[playerid] == i && PlayerInvListItemColumn[playerid] == j){
                if(PlayerInventoryType[playerid] == INVENTORY_TYPE){
                    UseButton[playerid] = CreatePlayerTextDraw(playerid, useX+PlayerPositionInventoryX[playerid], useY+PlayerPositionInventoryY[playerid], "USE");
                }
                else if(PlayerInventoryType[playerid] == TRADE_TYPE){
                    UseButton[playerid] = CreatePlayerTextDraw(playerid, useX+PlayerPositionInventoryX[playerid], useY+PlayerPositionInventoryY[playerid], "ADD");
                }
                else if(PlayerInventoryType[playerid] == HOME_TYPE && PlayerUsing_HomeInv[playerid]){
                    UseButton[playerid] = CreatePlayerTextDraw(playerid, useX+PlayerPositionInventoryX[playerid], useY+PlayerPositionInventoryY[playerid], "PUT");
                }
                PlayerTextDrawFont(playerid, UseButton[playerid], 1);
                PlayerTextDrawLetterSize(playerid, UseButton[playerid], 0.220833, 1.150000);
                PlayerTextDrawTextSize(playerid, UseButton[playerid], 16.500000, 22.500000);
                PlayerTextDrawSetOutline(playerid, UseButton[playerid], 1);
                PlayerTextDrawSetShadow(playerid, UseButton[playerid], 0);
                PlayerTextDrawAlignment(playerid, UseButton[playerid], 2);
                PlayerTextDrawColor(playerid, UseButton[playerid], -1);
                PlayerTextDrawBackgroundColor(playerid, UseButton[playerid], 255);
                PlayerTextDrawBoxColor(playerid, UseButton[playerid], 200);
                PlayerTextDrawUseBox(playerid, UseButton[playerid], 1);
                PlayerTextDrawSetProportional(playerid, UseButton[playerid], 1);
                PlayerTextDrawSetSelectable(playerid, UseButton[playerid], 1);

                InfoButton[playerid] = CreatePlayerTextDraw(playerid, infoX+PlayerPositionInventoryX[playerid], infoY+PlayerPositionInventoryY[playerid], "INFO");
                PlayerTextDrawFont(playerid, InfoButton[playerid], 1);
                PlayerTextDrawLetterSize(playerid, InfoButton[playerid], 0.220833, 1.150000);
                PlayerTextDrawTextSize(playerid, InfoButton[playerid], 16.500000, 22.500000);
                PlayerTextDrawSetOutline(playerid, InfoButton[playerid], 1);
                PlayerTextDrawSetShadow(playerid, InfoButton[playerid], 0);
                PlayerTextDrawAlignment(playerid, InfoButton[playerid], 2);
                PlayerTextDrawColor(playerid, InfoButton[playerid], -1);
                PlayerTextDrawBackgroundColor(playerid, InfoButton[playerid], 255);
                PlayerTextDrawBoxColor(playerid, InfoButton[playerid], 200);
                PlayerTextDrawUseBox(playerid, InfoButton[playerid], 1);
                PlayerTextDrawSetProportional(playerid, InfoButton[playerid], 1);
                PlayerTextDrawSetSelectable(playerid, InfoButton[playerid], 1);

                PlayerTextDrawShow(playerid, UseButton[playerid]);
                PlayerTextDrawShow(playerid, InfoButton[playerid]);

                break;
            }
            useX += 29.0;
            infoX += 29.0;
        }

        useX = 428.0;
        infoX = 428.0;

        useY += 33.0;
        infoY += 33.0;
    }
    return 1;
}

LoadPlayerInventorySlotTextDraw(playerid){
    new Float:modelX = 414.0, Float:modelY = 73.0;
    new Float:amountX = 440.0, Float:amountY = 95.0;

    for(new i; i<MAX_INV_MENU_ROWS; i++){
        for(new j; j<MAX_INV_MENU_COLUMN; j++){
            PlayerSlotInventoryModel[playerid][i][j] = PlayerSlotInventoryCount[playerid];
            PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]] = CreatePlayerTextDraw(playerid, modelX+PlayerPositionInventoryX[playerid], modelY+PlayerPositionInventoryY[playerid], "Preview_Model");
            PlayerTextDrawFont(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 5);
            PlayerTextDrawLetterSize(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 28.000000, 31.500000);
            PlayerTextDrawSetOutline(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 0);
            PlayerTextDrawSetShadow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 0);
            PlayerTextDrawAlignment(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 1);
            PlayerTextDrawColor(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], -1);
            PlayerTextDrawBackgroundColor(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 842150655);
            PlayerTextDrawBoxColor(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 255);
            PlayerTextDrawUseBox(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 0);
            PlayerTextDrawSetProportional(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 1);
            PlayerTextDrawSetPreviewModel(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], MODEL_NULL);
            //-10.000000, 0.000000, -20.000000, 1.000000
            PlayerTextDrawSetPreviewRot(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawSetPreviewVehCol(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 1, 1);
            PlayerTextDrawSetSelectable(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]++], 1);

            PlayerSlotInventoryAmount[playerid][i][j] = PlayerSlotInventoryCount[playerid];
            PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]] = CreatePlayerTextDraw(playerid, amountX+PlayerPositionInventoryX[playerid], amountY+PlayerPositionInventoryY[playerid], "1");
            PlayerTextDrawFont(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 1);
            PlayerTextDrawLetterSize(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 0.170833, 0.800000);
            PlayerTextDrawTextSize(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 0);
            PlayerTextDrawSetShadow(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 0);
            PlayerTextDrawAlignment(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 3);
            PlayerTextDrawColor(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], -1);
            PlayerTextDrawBackgroundColor(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 255);
            PlayerTextDrawBoxColor(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 50);
            PlayerTextDrawUseBox(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 0);
            PlayerTextDrawSetProportional(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]], 1);
            PlayerTextDrawSetSelectable(playerid, PlayerSlotInventoryTextDraw[playerid][PlayerSlotInventoryCount[playerid]++], 0);

            modelX += 29.0;
            amountX += 29.0;
        }

        modelX = 414.0;
        amountX = 440.0;

        modelY += 33.0;
        amountY += 33.0;
    }

    return 1;
}

LoadPlayerVicinityTextDraw(playerid){
    PlayerVicinityTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 331.500000+PlayerPositionInventoryX[playerid], 41.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerVicinityTextDraw[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PlayerVicinityTextDraw[playerid][0], 0.600000, 9.400062);
    PlayerTextDrawTextSize(playerid, PlayerVicinityTextDraw[playerid][0], 298.500000, 146.000000);
    PlayerTextDrawSetOutline(playerid, PlayerVicinityTextDraw[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PlayerVicinityTextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PlayerVicinityTextDraw[playerid][0], 2);
    PlayerTextDrawColor(playerid, PlayerVicinityTextDraw[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerVicinityTextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PlayerVicinityTextDraw[playerid][0], 555819519);
    PlayerTextDrawUseBox(playerid, PlayerVicinityTextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PlayerVicinityTextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerVicinityTextDraw[playerid][0], 0);

    PlayerVicinityTextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 331.500000+PlayerPositionInventoryX[playerid], 41.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerVicinityTextDraw[playerid][1], 0);
    PlayerTextDrawLetterSize(playerid, PlayerVicinityTextDraw[playerid][1], 0.600000, 1.450034);
    PlayerTextDrawTextSize(playerid, PlayerVicinityTextDraw[playerid][1], 298.500000, 146.000000);
    PlayerTextDrawSetOutline(playerid, PlayerVicinityTextDraw[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PlayerVicinityTextDraw[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PlayerVicinityTextDraw[playerid][1], 2);
    PlayerTextDrawColor(playerid, PlayerVicinityTextDraw[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerVicinityTextDraw[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PlayerVicinityTextDraw[playerid][1], PlayerInventoryCodeColor[playerid]);
    PlayerTextDrawUseBox(playerid, PlayerVicinityTextDraw[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, PlayerVicinityTextDraw[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerVicinityTextDraw[playerid][1], 0);

    PlayerVicinityTextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 260.000000+PlayerPositionInventoryX[playerid], 40.000000+PlayerPositionInventoryY[playerid], "Vicinity");
    PlayerTextDrawFont(playerid, PlayerVicinityTextDraw[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, PlayerVicinityTextDraw[playerid][2], 0.262499, 1.500000);
    PlayerTextDrawTextSize(playerid, PlayerVicinityTextDraw[playerid][2], 466.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerVicinityTextDraw[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, PlayerVicinityTextDraw[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, PlayerVicinityTextDraw[playerid][2], 1);
    PlayerTextDrawColor(playerid, PlayerVicinityTextDraw[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerVicinityTextDraw[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PlayerVicinityTextDraw[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, PlayerVicinityTextDraw[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, PlayerVicinityTextDraw[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerVicinityTextDraw[playerid][2], 0);

    PlayerVicinityTextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 331.000000+PlayerPositionInventoryX[playerid], 61.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerVicinityTextDraw[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, PlayerVicinityTextDraw[playerid][3], 0.600000, 7.000059);
    PlayerTextDrawTextSize(playerid, PlayerVicinityTextDraw[playerid][3], 298.500000, 143.000000);
    PlayerTextDrawSetOutline(playerid, PlayerVicinityTextDraw[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, PlayerVicinityTextDraw[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, PlayerVicinityTextDraw[playerid][3], 2);
    PlayerTextDrawColor(playerid, PlayerVicinityTextDraw[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerVicinityTextDraw[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, PlayerVicinityTextDraw[playerid][3], 320017407);
    PlayerTextDrawUseBox(playerid, PlayerVicinityTextDraw[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, PlayerVicinityTextDraw[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerVicinityTextDraw[playerid][3], 0);
    return 1;
}

LoadPlayerInventoryTextDraw(playerid){

    PlayerInventoryTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 500.500000+PlayerPositionInventoryX[playerid], 41.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][0], 0.600000, 30.500061);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][0], 298.500000, 176.500000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][0], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][0], 555819519);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][0], 0);

    PlayerInventoryTextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 500.500000+PlayerPositionInventoryX[playerid], 41.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][1], 0);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][1], 0.600000, 1.450034);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][1], 298.500000, 176.500000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][1], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][1], PlayerInventoryCodeColor[playerid]);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][1], 0);

    PlayerInventoryTextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 413.000000+PlayerPositionInventoryX[playerid], 40.000000+PlayerPositionInventoryY[playerid], "Inventory");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][2], 0.262499, 1.500000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][2], 466.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][2], 1);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][2], 0);

    PlayerInventoryTextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 582.000000+PlayerPositionInventoryX[playerid], 39.000000+PlayerPositionInventoryY[playerid], "X");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][3], 0.358332, 1.750000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][3], 16.500000, 13.500000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][3], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][3], 200);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][3], 1);

    PlayerInventoryTextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 568.000000+PlayerPositionInventoryX[playerid], 39.000000+PlayerPositionInventoryY[playerid], "P");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][4], 0.358332, 1.750000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][4], 16.500000, 13.500000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][4], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][4], 200);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][4], 1);

    PlayerInventoryTextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 551.000000+PlayerPositionInventoryX[playerid], 39.000000+PlayerPositionInventoryY[playerid], "C");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][5], 0.358332, 1.750000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][5], 16.500000, 13.500000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][5], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][5], 200);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][5], 1);

    PlayerInventoryTextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 500.500000+PlayerPositionInventoryX[playerid], 73.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][6], 0.600000, 21.800064);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][6], 298.500000, 173.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][6], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][6], 320017407);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][6], 0);

    PlayerInventoryTextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 438.500000+PlayerPositionInventoryX[playerid], 58.000000+PlayerPositionInventoryY[playerid], "Inventory");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][7], 0.195832, 1.250000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][7], 16.500000, 49.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][7], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][7], 1296911816);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][7], 1);

    PlayerInventoryTextDraw[playerid][8] = CreatePlayerTextDraw(playerid, 491.000000+PlayerPositionInventoryX[playerid], 58.000000+PlayerPositionInventoryY[playerid], "Wallet");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][8], 0.195832, 1.250000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][8], 16.500000, 49.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][8], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][8], 1296911816);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][8], 1);

    PlayerInventoryTextDraw[playerid][9] = CreatePlayerTextDraw(playerid, 556.000000+PlayerPositionInventoryX[playerid], 276.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][9], 5);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][9], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][9], 31.000000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][9], 1);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][9], -1962934147);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][9], 255);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][9], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerInventoryTextDraw[playerid][9], 1343);
    PlayerTextDrawSetPreviewRot(playerid, PlayerInventoryTextDraw[playerid][9], -10.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerInventoryTextDraw[playerid][9], 1, 1);

    PlayerInventoryTextDraw[playerid][10] = CreatePlayerTextDraw(playerid, 417.000000+PlayerPositionInventoryX[playerid], 286.000000+PlayerPositionInventoryY[playerid], "$");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][10], 0.391665, 1.899999);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][10], 16.500000, 10.500000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][10], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][10], 2094792959);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][10], 200);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][10], 1);

    PlayerInventoryTextDraw[playerid][11] = CreatePlayerTextDraw(playerid, 426.000000+PlayerPositionInventoryX[playerid], 290.000000+PlayerPositionInventoryY[playerid], "0");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][11], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][11], 0.216666, 1.200000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][11], 488.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][11], 1);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][11], 50);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][11], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][11], 0);

    PlayerInventoryTextDraw[playerid][12] = CreatePlayerTextDraw(playerid, 418.000000+PlayerPositionInventoryX[playerid], 302.000000+PlayerPositionInventoryY[playerid], "W");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][12], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][12], 0.341665, 1.599999);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][12], 16.500000, 10.500000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][12], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][12], -293409025);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][12], 200);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][12], 0);

    PlayerInventoryTextDraw[playerid][13] = CreatePlayerTextDraw(playerid, 426.000000+PlayerPositionInventoryX[playerid], 304.000000+PlayerPositionInventoryY[playerid], "0");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][13], 0.216666, 1.200000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][13], 488.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][13], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][13], 1);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][13], 50);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][13], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][13], 0);

    PlayerInventoryTextDraw[playerid][14] = CreatePlayerTextDraw(playerid, 483.000000+PlayerPositionInventoryX[playerid], 286.000000+PlayerPositionInventoryY[playerid], "$");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][14], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][14], 0.391665, 1.899999);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][14], 16.500000, 10.500000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][14], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][14], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][14], -16776961);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][14], 200);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][14], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][14], 0);

    PlayerInventoryTextDraw[playerid][15] = CreatePlayerTextDraw(playerid, 492.000000+PlayerPositionInventoryX[playerid], 290.000000+PlayerPositionInventoryY[playerid], "0");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][15], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][15], 0.216666, 1.200000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][15], 488.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][15], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][15], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][15], 1);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][15], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][15], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][15], 50);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][15], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][15], 0);

    PlayerInventoryTextDraw[playerid][16] = CreatePlayerTextDraw(playerid, 587.000000+PlayerPositionInventoryX[playerid], 58.000000+PlayerPositionInventoryY[playerid], "0/64");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][16], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][16], 0.195832, 1.250000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][16], 16.500000, 49.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][16], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][16], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][16], 3);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][16], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][16], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][16], 1296911816);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][16], 0);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][16], 0);

    PlayerInventoryTextDraw[playerid][17] = CreatePlayerTextDraw(playerid, 414.000000+PlayerPositionInventoryX[playerid], 274.000000+PlayerPositionInventoryY[playerid], "ld_pool:ball");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][17], 4);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][17], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][17], 6.000000, 7.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][17], 1);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][17], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][17], 1);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][17], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][17], -16776961);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][17], -16777166);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][17], 1);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][17], 1);

    PlayerInventoryTextDraw[playerid][18] = CreatePlayerTextDraw(playerid, 425.000000+PlayerPositionInventoryX[playerid], 274.000000+PlayerPositionInventoryY[playerid], "ld_pool:ball");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][18], 4);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][18], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][18], 6.000000, 7.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][18], 1);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][18], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][18], 1);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][18], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][18], -16776961);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][18], -16777166);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][18], 1);

    PlayerInventoryTextDraw[playerid][19] = CreatePlayerTextDraw(playerid, 436.000000+PlayerPositionInventoryX[playerid], 274.000000+PlayerPositionInventoryY[playerid], "ld_pool:ball");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][19], 4);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][19], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][19], 6.000000, 7.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][19], 1);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][19], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][19], 1);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][19], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][19], -16776961);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][19], -16777166);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][19], 1);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][19], 1);

    PlayerInventoryTextDraw[playerid][20] = CreatePlayerTextDraw(playerid, 499.000000+PlayerPositionInventoryX[playerid], 274.000000+PlayerPositionInventoryY[playerid], "Weight: (50.0/50.0)");
    PlayerTextDrawFont(playerid, PlayerInventoryTextDraw[playerid][20], 1);
    PlayerTextDrawLetterSize(playerid, PlayerInventoryTextDraw[playerid][20], 0.183333, 0.949999);
    PlayerTextDrawTextSize(playerid, PlayerInventoryTextDraw[playerid][20], 400.000000, 97.000000);
    PlayerTextDrawSetOutline(playerid, PlayerInventoryTextDraw[playerid][20], 0);
    PlayerTextDrawSetShadow(playerid, PlayerInventoryTextDraw[playerid][20], 0);
    PlayerTextDrawAlignment(playerid, PlayerInventoryTextDraw[playerid][20], 2);
    PlayerTextDrawColor(playerid, PlayerInventoryTextDraw[playerid][20], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerInventoryTextDraw[playerid][20], 255);
    PlayerTextDrawBoxColor(playerid, PlayerInventoryTextDraw[playerid][20], 50);
    PlayerTextDrawUseBox(playerid, PlayerInventoryTextDraw[playerid][20], 1);
    PlayerTextDrawSetProportional(playerid, PlayerInventoryTextDraw[playerid][20], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerInventoryTextDraw[playerid][20], 0);
    return 1;
}

LoadArrowEditInv(playerid){
    ArrowEditInv[playerid][0] = CreatePlayerTextDraw(playerid, 76.000000, 182.000000, "ld_beat:up");
    PlayerTextDrawFont(playerid, ArrowEditInv[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, ArrowEditInv[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, ArrowEditInv[playerid][0], 25.000000, 27.000000);
    PlayerTextDrawSetOutline(playerid, ArrowEditInv[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, ArrowEditInv[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, ArrowEditInv[playerid][0], 1);
    PlayerTextDrawColor(playerid, ArrowEditInv[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, ArrowEditInv[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, ArrowEditInv[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, ArrowEditInv[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, ArrowEditInv[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, ArrowEditInv[playerid][0], 1);

    ArrowEditInv[playerid][1] = CreatePlayerTextDraw(playerid, 76.000000, 277.000000, "ld_beat:down");
    PlayerTextDrawFont(playerid, ArrowEditInv[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, ArrowEditInv[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, ArrowEditInv[playerid][1], 25.000000, 27.000000);
    PlayerTextDrawSetOutline(playerid, ArrowEditInv[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, ArrowEditInv[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, ArrowEditInv[playerid][1], 1);
    PlayerTextDrawColor(playerid, ArrowEditInv[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, ArrowEditInv[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, ArrowEditInv[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, ArrowEditInv[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, ArrowEditInv[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, ArrowEditInv[playerid][1], 1);

    ArrowEditInv[playerid][2] = CreatePlayerTextDraw(playerid, 244.000000, 406.000000, "ld_beat:left");
    PlayerTextDrawFont(playerid, ArrowEditInv[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, ArrowEditInv[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, ArrowEditInv[playerid][2], 25.000000, 27.000000);
    PlayerTextDrawSetOutline(playerid, ArrowEditInv[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, ArrowEditInv[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, ArrowEditInv[playerid][2], 1);
    PlayerTextDrawColor(playerid, ArrowEditInv[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, ArrowEditInv[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, ArrowEditInv[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, ArrowEditInv[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, ArrowEditInv[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, ArrowEditInv[playerid][2], 1);

    ArrowEditInv[playerid][3] = CreatePlayerTextDraw(playerid, 370.000000, 406.000000, "ld_beat:right");
    PlayerTextDrawFont(playerid, ArrowEditInv[playerid][3], 4);
    PlayerTextDrawLetterSize(playerid, ArrowEditInv[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, ArrowEditInv[playerid][3], 25.000000, 27.000000);
    PlayerTextDrawSetOutline(playerid, ArrowEditInv[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, ArrowEditInv[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, ArrowEditInv[playerid][3], 1);
    PlayerTextDrawColor(playerid, ArrowEditInv[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, ArrowEditInv[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, ArrowEditInv[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, ArrowEditInv[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, ArrowEditInv[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, ArrowEditInv[playerid][3], 1);
    return 1;
}