#if defined _inc_impl
	#undef _inc_impl
#endif

Reset_HomePlayer(playerid){
    PlayerUsing_HomeInv[playerid] = false;
    PlayerHomeInvPage[playerid] = 1;
    PlayerHomeInvType[playerid] = HOMEINV_TYPE;
    PlayerHomeSlotCount[playerid] = 0;
    PlayerHomeInvLastPage[playerid] = 0;

    PlayerHomeInvListItemRows[playerid] = -1;
    PlayerHomeInvListItemColumn[playerid] = -1;
    PlayerGetIndexHomeSlotItem[playerid] = -1;
    PlayerGetIndexNextHomeSlotItem[playerid] = -1;
    PlayerHomeInvListItemRowsOld[playerid] = -1;
    PlayerHomeInvListItemColumnOld[playerid] = -1;

    GetHomeItemIndex[playerid] = -1;
    GetItemDropIndex[playerid] = -1;
    return 1;
}

Dialog:StorageHome(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new homeid = GetHomeOwnerIndex[playerid];
            if(homeid != -1){
                HomeData[homeid][homeStorageUsing] = true;
                if(!PlayerUsing_HomeInv[playerid]) OnPlayerHomeInv_Open(playerid);
                if(!PlayerInventoryStatus[playerid]) OnPlayerInventory_Open(playerid);
            }
        }
    }
    return 1;
}

OnPlayerHomeInv_Open(playerid){
    PlayerUsing_HomeInv[playerid] = true;
    PlayerHomeInvPage[playerid] = 1;
    PlayerInventoryType[playerid] = HOME_TYPE;
    PlayerHomeSlotCount[playerid] = 0;
    LoadHomeInvTextDraw(playerid);
    LoadHomeInvTD_Slot(playerid);
    for(new i=0; i<MAX_HOMETD; i++) PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][i]);
    OnPlayerHomeInv_Render(playerid);
    OnHomeInventory_UpdateCount(playerid);
    SelectTextDraw(playerid, PlayerInventoryHoverCodeColor[playerid]);
    return 1;
}

OnPlayerHomeInv_Close(playerid){
    if(GetHomeOwnerIndex[playerid] != -1){
        HomeData[GetHomeOwnerIndex[playerid]][homeStorageUsing] = false;
    }

    for(new i=0; i<MAX_HOMETD; i++) {
        PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][i]);
        PlayerTextDrawDestroy(playerid, PlayerHomeInvTD[playerid][i]);
    }

    for(new i=0; i<PlayerHomeSlotCount[playerid]; i++){
        PlayerTextDrawHide(playerid, PlayerHomeSlotTextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, PlayerHomeSlotTextDraw[playerid][i]);
    }

    RemoveHomeButton(playerid);
    PlayerHomeSlotCount[playerid] = 0;
    CancelSelectTextDraw(playerid);
    PlayerInventoryType[playerid] = INVENTORY_TYPE;
    Reset_HomePlayer(playerid);
    return 1;
}

Home_GetItem(playerid, itemid){
    new homeid = GetHomeOwnerIndex[playerid];
    if(homeid != -1){
        if(HouseStorage[homeid][itemid][hItemQuantity] == 1){
            //printf("get");
            new itemexid = PlayerInventory_AddItem(playerid, HouseStorage[homeid][itemid][hItemName], HouseStorage[homeid][itemid][hItemModel], 1, HouseStorage[homeid][itemid][hItemAmmo], HouseStorage[homeid][itemid][hItemLevel]);
            if (itemexid == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            Log_Write("logs/homeremoveitems.txt", "[%s] %s (level: %d) Destroy from home  %s", ReturnDate(), HouseStorage[homeid][itemid][hItemName], HouseStorage[homeid][itemid][hItemLevel], HomeData[homeid][homeOwnerName]);
            HomeItem_Delete(homeid, itemid);
            if(PlayerGetIndexHomeSlotItem[playerid] != -1) RemoveHomeButton(playerid);
            OnPlayerInventory_Render(playerid);

            foreach(new i : Player) {
                if(!LoggedIn[i]) continue;
                if(!PlayerUsing_HomeInv[i]) continue;
                if(Home_IsRentOwner(i, homeid) || Home_IsOwner(i, homeid) || CanFriskHome[i] == HomeData[homeid][homeOwner]){
                    OnPlayerHomeInv_Render(i);
                }
            }

            OnHomeInventory_UpdateCount(playerid);
            OnPlayerInventory_UpdateCount(playerid);
            PlayerGetIndexHomeSlotItem[playerid] = -1;
            PlayerGetIndexNextHomeSlotItem[playerid] = -1;
            PlayerHomeInvListItemRowsOld[playerid] = -1;
            PlayerHomeInvListItemColumnOld[playerid] = -1;
            return 1;
        }
        else if(HouseStorage[homeid][itemid][hItemQuantity] > 1){
            new string[128];
            PlayerCantSelectTextDraw[playerid] = true;
            GetHomeItemIndex[playerid] = itemid;
            format(string, sizeof(string), "ไอเท็ม: %s | จำนวน: %d\nกรุณาเลือกจำนวนที่จะเบิกออกจากคลัง:", HouseStorage[homeid][itemid][hItemName], HouseStorage[homeid][itemid][hItemQuantity]);
            Dialog_ShowEasy(playerid, HomePickupInputAmountNew, DIALOG_STYLE_INPUT, "[เบิกออกจากคลังบ้าน]", string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:HomePickupInputAmountNew(playerid, response, listitem, inputtext[]){

    if(!response){
        PlayerCantSelectTextDraw[playerid] = false;
        GetHomeItemIndex[playerid] = -1;
        return 1;
    }

    new itemid = GetHomeItemIndex[playerid];
    new string[128];
    if(response){
        new homeid = GetHomeOwnerIndex[playerid];
        new amount = strval(inputtext);

        if(homeid != -1){
            if(amount <= 0){
                format(string, sizeof(string), "* คุณจำเป็นต้องกรอกจำนวนที่มากกว่า 0 *\nไอเท็ม: %s | จำนวน: %d\nกรุณาเลือกจำนวนที่จะเบิกออกจากคลัง:", HouseStorage[homeid][itemid][hItemName], HouseStorage[homeid][itemid][hItemQuantity]);
                return Dialog_ShowEasy(playerid, HomePickupInputAmountNew, DIALOG_STYLE_INPUT, "[เก็บ]", string, "ตกลง", "ยกเลิก");
            }
            
            if(amount > HouseStorage[homeid][itemid][hItemQuantity]){
                format(string, sizeof(string), "* ไอเท็มในคลังบ้านมีไม่พอ *\nไอเท็ม: %s | จำนวน: %d\nกรุณาเลือกจำนวนที่จะเบิกออกจากคลัง:", HouseStorage[homeid][itemid][hItemName], HouseStorage[homeid][itemid][hItemQuantity]);
                return Dialog_ShowEasy(playerid, HomePickupInputAmountNew, DIALOG_STYLE_INPUT, "[เก็บ]", string, "ตกลง", "ยกเลิก");
            }

            if(amount > PlayerData[playerid][pItemAmount]){
                format(string, sizeof(string), "* คุณจะเก็บได้รอบละไม่เกิน %d ชิ้น เท่านั้น *\nไอเท็ม: %s | จำนวน: %d\nกรุณาเลือกจำนวนที่จะเบิกออกจากคลัง:", PlayerData[playerid][pItemAmount], HouseStorage[homeid][itemid][hItemName], HouseStorage[homeid][itemid][hItemQuantity]);
                return Dialog_ShowEasy(playerid, HomePickupInputAmountNew, DIALOG_STYLE_INPUT, "[เก็บ]", string, "ตกลง", "ยกเลิก");
            }

            new itemexid = PlayerInventory_AddItem(playerid, HouseStorage[homeid][itemid][hItemName], HouseStorage[homeid][itemid][hItemModel], amount, HouseStorage[homeid][itemid][hItemAmmo], HouseStorage[homeid][itemid][hItemLevel]);
            if (itemexid == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

            SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้หยิบ '%s' ออกจากคลังบ้าน", ReturnRoleplayName(playerid), HouseStorage[homeid][itemid][hItemName]);
            HouseStorage[homeid][itemid][hItemQuantity] -= amount;

            format(string, sizeof(string), "UPDATE `homestorage` SET `itemQuantity` = %d WHERE `itemID` = '%d'", HouseStorage[homeid][itemid][hItemQuantity], HouseStorage[homeid][itemid][hItemID]);
		    mysql_tquery(dbCon, string);

            Log_Write("logs/homeremoveitems.txt", "[%s] %s (level: %d) Remove from home  %s amount -= %d, Total: %d", ReturnDate(), HouseStorage[homeid][itemid][hItemName], HouseStorage[homeid][itemid][hItemLevel], HomeData[homeid][homeOwnerName], amount, HouseStorage[homeid][itemid][hItemQuantity]);

            if(HouseStorage[homeid][itemid][hItemQuantity] == 0){
                Log_Write("logs/homeremoveitems.txt", "[%s] %s (level: %d) Destroy from home  %s", ReturnDate(), HouseStorage[homeid][itemid][hItemName], HouseStorage[homeid][itemid][hItemLevel], HomeData[homeid][homeOwnerName]);
                HomeItem_Delete(homeid, itemid);
            }

            if(PlayerGetIndexHomeSlotItem[playerid] != -1) RemoveHomeButton(playerid);
            OnPlayerInventory_Render(playerid);
            foreach(new i : Player) {
                if(!LoggedIn[i]) continue;
                if(!PlayerUsing_HomeInv[i]) continue;
                if(Home_IsRentOwner(i, homeid) || Home_IsOwner(i, homeid) || CanFriskHome[i] == HomeData[homeid][homeOwner]){
                    OnPlayerHomeInv_Render(i);
                }
            }
            OnHomeInventory_UpdateCount(playerid);
            OnPlayerInventory_UpdateCount(playerid);
            PlayerGetIndexHomeSlotItem[playerid] = -1;
            PlayerGetIndexNextHomeSlotItem[playerid] = -1;
            PlayerHomeInvListItemRowsOld[playerid] = -1;
            PlayerHomeInvListItemColumnOld[playerid] = -1;
            PlayerCantSelectTextDraw[playerid] = false;
        }
    }
    return 1;
}

HomeItem_Delete(homeid, itemid){
    static query[64];

    if (itemid != -1 && HouseStorage[homeid][itemid][hItemExists]){
	    format(query, sizeof(query), "DELETE FROM `homestorage` WHERE `itemID` = '%d'", HouseStorage[homeid][itemid][hItemID]);
	    mysql_tquery(dbCon, query);

        HouseStorage[homeid][itemid][hItemID] = 0;
        format(HouseStorage[homeid][itemid][hItemName], 64, "NULL");
        HouseStorage[homeid][itemid][hItemExists] = false;
        HouseStorage[homeid][itemid][hItemModel] = MODEL_NULL;
        HouseStorage[homeid][itemid][hItemQuantity] = 0;
        HouseStorage[homeid][itemid][hItemAmmo] = 0;
        HouseStorage[homeid][itemid][hItemLevel] = 0;
	}
	return 1;
}

Home_AddItem(playerid, itemid){
    if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Skin Baseball HW", true)){
        if(PlayerUseSkinBaseHalloween[playerid]){
            return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "คุณจะต้องกดใช้งานสกินอีกครั้งเพื่อปิดใช้งานสกินนี้ก่อน", "ตกลง", "");
        }
    }

    new homeid = GetHomeOwnerIndex[playerid];
    if(homeid != -1){
        if(Item_CantPutHome(Inventory_Player[playerid][itemid][itemName]) != -1) return ErrorMsg(playerid, "คุณไม่สามารถฝากไอเท็มนี้ได้");

        if(ServerData[ServerCanTradeSpecial]){
            for (new i = 0; i < sizeof(WeaponData); i ++){
                if (!strcmp(WeaponData[i][weaponName], Inventory_Player[playerid][itemid][itemName], true)){
                    return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ไอเท็มนี้ไม่สามารถฝากเข้าคลังบ้านได้ชั่วคราว", "ตกลง", "");
                }
            }

            if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Mixed Drug", true)){
                return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ไอเท็มนี้ไม่สามารถฝากเข้าคลังบ้านได้ชั่วคราว", "ตกลง", "");
            }
        }

        if(Inventory_Player[playerid][itemid][itemQuantity] == 1){
            //printf("put");
            new id = HousePutItem(playerid, homeid, Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemKey], 1, Inventory_Player[playerid][itemid][itemAmmo], Inventory_Player[playerid][itemid][itemLevel]);
            if(id == -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] คลังบ้านของคุณเต็มแล้วไม่สามารถฝากเพิ่มได้อีก", "ตกลง", "");
            PlayerInventory_RemoveEx(playerid, itemid, 1);
            if(PlayerGetIndexSlotItem[playerid] != -1) RemoveUseInfoButton(playerid);
            OnPlayerInventory_Render(playerid);
            foreach(new i : Player) {
                if(!LoggedIn[i]) continue;
                if(!PlayerUsing_HomeInv[i]) continue;
                if(Home_IsRentOwner(i, homeid) || Home_IsOwner(i, homeid) || CanFriskHome[i] == HomeData[homeid][homeOwner]){
                    OnPlayerHomeInv_Render(i);
                }
            }
            OnHomeInventory_UpdateCount(playerid);
            OnPlayerInventory_UpdateCount(playerid);
            PlayerGetIndexSlotItem[playerid] = -1;
            PlayerGetIndexNextSlotItem[playerid] = -1;
            PlayerInvListItemRowsOld[playerid] = -1;
            PlayerInvListItemColumnOld[playerid] = -1;
            return 1;
        }
        if(Inventory_Player[playerid][itemid][itemQuantity] > 1){
            new string[128];
            GetItemDropIndex[playerid] = itemid;
            PlayerCantSelectTextDraw[playerid] = true;
            format(string, sizeof(string), "ไอเท็ม: %s | จำนวน: %d\nกรุณากรอกจำนวนที่จะต้องการใส่คลังบ้าน:", Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity]);
            Dialog_ShowEasy(playerid, HomeDropInputAmountNew, DIALOG_STYLE_INPUT, "[ใส่คลังบ้าน]", string, "ตกลง", "ยกเลิก");
            return 1;
        }
    }
    return 1;
}

Dialog:HomeDropInputAmountNew(playerid, response, listitem, inputtext[]){
    if(!response){
        PlayerCantSelectTextDraw[playerid] = false;
        GetItemDropIndex[playerid] = -1;
        return 1;
    }

    new itemid = GetItemDropIndex[playerid];
    new string[128];
    if(response){
        new homeid = GetHomeOwnerIndex[playerid];
        new amount = strval(inputtext);
        if(homeid != -1){
            if(amount <= 0){
                format(string, sizeof(string), "* คุณจำเป็นต้องกรอกจำนวนที่มากกว่า 0 *\nไอเท็ม: %s | จำนวน: %d\nกรุณากรอกจำนวนที่จะต้องการใส่คลังบ้าน:", Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity]);
                return Dialog_ShowEasy(playerid, HomeDropInputAmountNew, DIALOG_STYLE_INPUT, "[ใส่คลังบ้าน]", string, "ตกลง", "ยกเลิก");
            }
            
            if(amount > Inventory_Player[playerid][itemid][itemQuantity]){
                format(string, sizeof(string), "* คุณมีไอเท็มไม่เพียงพอที่จะฝาก *\nไอเท็ม: %s | จำนวน: %d\nกรุณากรอกจำนวนที่จะต้องการใส่คลังบ้าน:", Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity]);
                return Dialog_ShowEasy(playerid, HomeDropInputAmountNew, DIALOG_STYLE_INPUT, "[ใส่คลังบ้าน]", string, "ตกลง", "ยกเลิก");
            }

            if(amount > HomeData[homeid][homeItemAmount]){
                format(string, sizeof(string), "* คุณสามารถฝากได้รอบละไม่เกิน %d ชิ้น *\nไอเท็ม: %s | จำนวน: %d\nกรุณากรอกจำนวนที่จะต้องการใส่คลังบ้าน:", HomeData[homeid][homeItemAmount], Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity]);
                return Dialog_ShowEasy(playerid, HomeDropInputAmountNew, DIALOG_STYLE_INPUT, "[ใส่คลังบ้าน]", string, "ตกลง", "ยกเลิก");
            }

            new id = HousePutItem(playerid, homeid, Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemKey], amount, Inventory_Player[playerid][itemid][itemAmmo], Inventory_Player[playerid][itemid][itemLevel]);
            if(id == -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] คลังบ้านของคุณเต็มแล้วไม่สามารถฝากเพิ่มได้อีก", "ตกลง", "");
            PlayerInventory_RemoveEx(playerid, itemid, amount);
            if(PlayerGetIndexSlotItem[playerid] != -1) RemoveUseInfoButton(playerid);
            OnPlayerInventory_Render(playerid);
            foreach(new i : Player) {
                if(!LoggedIn[i]) continue;
                if(!PlayerUsing_HomeInv[i]) continue;
                if(Home_IsRentOwner(i, homeid) || Home_IsOwner(i, homeid) || CanFriskHome[i] == HomeData[homeid][homeOwner]){
                    OnPlayerHomeInv_Render(i);
                }
            }
            OnHomeInventory_UpdateCount(playerid);
            OnPlayerInventory_UpdateCount(playerid);
            PlayerGetIndexSlotItem[playerid] = -1;
            PlayerGetIndexNextSlotItem[playerid] = -1;
            PlayerInvListItemRowsOld[playerid] = -1;
            PlayerInvListItemColumnOld[playerid] = -1;
            PlayerCantSelectTextDraw[playerid] = false;
        }
    }
    return 1;
}

OnHomeInventory_UpdateCount(playerid){
    new homeid = GetHomeOwnerIndex[playerid];
    if(homeid != -1){
        new countitem = 0;
        for(new i=0; i<MAX_HOME_INV; i++){
            if(HouseStorage[homeid][i][hItemModel] != MODEL_NULL) countitem++;
            if(i >= 107) break;
        }
        new string[128];
        format(string, sizeof string, "%d/%d", countitem, HomeData[homeid][homeMaxItem]);
        PlayerTextDrawSetString(playerid, PlayerHomeInvTD[playerid][5], string);
        PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][5]);
        PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][5]);
    }
    return 1;
}

OnHomeInventory_Update(playerid, homeid){
    new slotitem = PlayerGetIndexHomeSlotItem[playerid], slotitemnext = PlayerGetIndexNextHomeSlotItem[playerid];
    new i = PlayerHomeInvListItemRows[playerid], j = PlayerHomeInvListItemColumn[playerid];
    new iold = PlayerHomeInvListItemRowsOld[playerid], jold = PlayerHomeInvListItemColumnOld[playerid];
    new string[10];
    //printf("i = %d | j = %d", i, j);
    if(slotitem != -1 && slotitemnext == -1){
        if(HouseStorage[homeid][HouseStorage[homeid][slotitem][hItemSlot]][hItemModel] == MODEL_NULL){
            if(i != -1 && j != -1){
                printf("Draw Model Null slotitemold != -1 and slotnextitem == -1");
                PlayerTextDrawSetPreviewModel(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]]);
                PlayerTextDrawHide(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][i][j]]);
            }
        }
        else{
            if(i != -1 && j != -1){
                printf("Draw Model Not Null slotitemold != -1 and slotnextitem == -1");
                PlayerTextDrawSetPreviewModel(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], HouseStorage[homeid][HouseStorage[homeid][slotitem][hItemSlot]][hItemModel]);
                PlayerTextDrawSetPreviewRot(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
                PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]]);
                if(CheckItemIsWeapon(HouseStorage[homeid][HouseStorage[homeid][slotitem][hItemSlot]][hItemName]) != -1) format(string, sizeof(string), "%s", FormatNumberNotMoney(HouseStorage[homeid][HouseStorage[homeid][slotitem][hItemSlot]][hItemQuantity]));
                else format(string, sizeof(string), "%s/%d", FormatNumberNotMoney(HouseStorage[homeid][HouseStorage[homeid][slotitem][hItemSlot]][hItemQuantity]), HomeData[homeid][homeItemAmount]);
                PlayerTextDrawSetString(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][i][j]], string);
                PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][i][j]]);
            }
        }
    }
    else if(slotitem != -1 && slotitemnext != -1){
        if(i != -1 && j != -1){
            printf("[New] Draw Model Not Null slotitemold != -1 and slotnextitem != -1");
            PlayerTextDrawSetPreviewModel(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], HouseStorage[homeid][HouseStorage[homeid][slotitemnext][hItemSlot]][hItemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
            PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]]);
            if(CheckItemIsWeapon(HouseStorage[homeid][HouseStorage[homeid][slotitemnext][hItemSlot]][hItemName]) != -1) format(string, sizeof(string), "%s", FormatNumberNotMoney(HouseStorage[homeid][HouseStorage[homeid][slotitemnext][hItemSlot]][hItemQuantity]));
            else format(string, sizeof(string), "%s/%d", FormatNumberNotMoney(HouseStorage[homeid][HouseStorage[homeid][slotitemnext][hItemSlot]][hItemQuantity]), HomeData[homeid][homeItemAmount]);
            PlayerTextDrawSetString(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][i][j]], string);
            PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][i][j]]);

            //ResetOldSlot
            //printf("%d = %d | %d = %d", i, iold, j, jold);
            if(i != iold || j != jold){
                printf("LastPage: %d | Page: %d", PlayerHomeInvLastPage[playerid], PlayerHomeInvPage[playerid]);
                if(PlayerHomeInvLastPage[playerid] == PlayerHomeInvPage[playerid]){
                    printf("[Old] Draw Model Null slotitemold != -1 and slotnextitem != -1");
                    PlayerTextDrawSetPreviewModel(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][iold][jold]], MODEL_NULL);
                    PlayerTextDrawSetPreviewRot(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][iold][jold]], 0.000000, 0.000000, 0.000000, 0.000000);
                    PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][iold][jold]]);
                    PlayerTextDrawHide(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][iold][jold]]);  
                }
            }
            else if(i == iold || j == jold){
                printf("LastPage: %d | Page: %d", PlayerHomeInvLastPage[playerid], PlayerHomeInvPage[playerid]);
                if(PlayerHomeInvLastPage[playerid] == PlayerHomeInvPage[playerid]){
                    printf("[Old] Draw Model Null slotitemold != -1 and slotnextitem != -1");
                    PlayerTextDrawSetPreviewModel(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][iold][jold]], MODEL_NULL);
                    PlayerTextDrawSetPreviewRot(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][iold][jold]], 0.000000, 0.000000, 0.000000, 0.000000);
                    PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][iold][jold]]);
                    PlayerTextDrawHide(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][iold][jold]]);  
                }

                printf("[New Reload Slot] Draw Model Not Null slotitemold != -1 and slotnextitem != -1");
                PlayerTextDrawSetPreviewModel(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], HouseStorage[homeid][HouseStorage[homeid][slotitemnext][hItemSlot]][hItemModel]);
                PlayerTextDrawSetPreviewRot(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
                PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]]);
                if(CheckItemIsWeapon(HouseStorage[homeid][HouseStorage[homeid][slotitemnext][hItemSlot]][hItemName]) != -1) format(string, sizeof(string), "%s", FormatNumberNotMoney(HouseStorage[homeid][HouseStorage[homeid][slotitemnext][hItemSlot]][hItemQuantity]));
                else format(string, sizeof(string), "%s/%d", FormatNumberNotMoney(HouseStorage[homeid][HouseStorage[homeid][slotitemnext][hItemSlot]][hItemQuantity]), HomeData[homeid][homeItemAmount]);
                PlayerTextDrawSetString(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][i][j]], string);
                PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][i][j]]);
            }
        }
    }
    PlayerHomeInvLastPage[playerid] = 0;
    return 1;
}

OnPlayerHomeInv_Render(playerid){
    new slotitem, string[10];
    new homeid = GetHomeOwnerIndex[playerid];
    if(homeid != -1){
        if(PlayerHomeInvPage[playerid] == 1){
            slotitem = 0;
        }
        else if(PlayerHomeInvPage[playerid] == 2){
            slotitem = 36;
        }
        else if(PlayerHomeInvPage[playerid] == 3){
            slotitem = 72;
        }

        for(new i=0; i<MAX_HOME_MENU_ROWS; i++){
            for(new j=0; j<MAX_HOME_MENU_COLUMN; j++){
                if(HouseStorage[homeid][slotitem][hItemModel] == MODEL_NULL){
                    PlayerTextDrawSetPreviewModel(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], MODEL_NULL);
                    PlayerTextDrawSetPreviewRot(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], 0.000000, 0.000000, 0.000000, 0.000000);
                    PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]]);
                    PlayerTextDrawHide(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][i][j]]);
                }
                else{
                    PlayerTextDrawSetPreviewModel(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], HouseStorage[homeid][slotitem][hItemModel]);
                    PlayerTextDrawSetPreviewRot(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
                    PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotModel[playerid][i][j]]);
                    if(CheckItemIsWeapon(HouseStorage[homeid][slotitem][hItemName]) != -1) format(string, sizeof(string), "%s", FormatNumberNotMoney(HouseStorage[homeid][slotitem][hItemQuantity]));
                    else format(string, sizeof(string), "%s/%d", FormatNumberNotMoney(HouseStorage[homeid][slotitem][hItemQuantity]), HomeData[homeid][homeItemAmount]);
                    PlayerTextDrawSetString(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][i][j]], string);
                    PlayerTextDrawShow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotAmount[playerid][i][j]]);
                }
                slotitem++;
            }
        }

        if(PlayerHomeInvType[playerid] == HOMEINV_TYPE){
            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][4]);
            PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][4], PlayerInventoryCodeColor[playerid]);
            PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][4]);
        }

        if(PlayerHomeInvPage[playerid] == 1){
            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][7]);
            PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][7], 1296911871);
            PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][7]);

            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][7]);
            PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][7], 1296911871);
            PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][7]);

            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][6]);
            PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][6], PlayerInventoryCodeColor[playerid]);
            PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][6]);
        }
        else if(PlayerHomeInvPage[playerid] == 2){

            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][6]);
            PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][6], 1296911871);
            PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][6]);

            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][8]);
            PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][8], 1296911871);
            PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][8]);

            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][7]);
            PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][7], PlayerInventoryCodeColor[playerid]);
            PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][7]);
        }
        else if(PlayerHomeInvPage[playerid] == 3){

            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][6]);
            PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][6], 1296911871);
            PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][6]);

            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][7]);
            PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][7], 1296911871);
            PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][7]);

            PlayerTextDrawHide(playerid, PlayerHomeInvTD[playerid][8]);
            PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][8], PlayerInventoryCodeColor[playerid]);
            PlayerTextDrawShow(playerid, PlayerHomeInvTD[playerid][8]);
        }
    }
    return 1;
}

forward OnHomeInventory_InfoItem(playerid, homeid, const item[], model, itemid);
public OnHomeInventory_InfoItem(playerid, homeid, const item[], model, itemid){
    if(itemid == -1) {
        PlayerCantSelectTextDraw[playerid] = false;
        return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
    }
    if(homeid != -1){
        new string[512];
        format(string, sizeof string, "ไอเท็ม: %s\
        \nจำนวนไอเท็ม: %d\
        \nเลเวลไอเท็ม: %d\
        \n[ คำแนะนำ ]\n", item, HouseStorage[homeid][itemid][hItemQuantity], HouseStorage[homeid][itemid][hItemLevel]);

        if(!strcmp(item, "Orange", true)){
            format(string ,sizeof string, "%s- ใช้สำหรับกินเพื่อเพิ่มค่าอาหารและความกระหาย", string);
        }
        else if(!strcmp(item, "Medkit", true)){
            format(string ,sizeof string, "%s- ใช้สำหรับรักษาบาดแผลต่างๆ", string);
        }
        else{
            format(string ,sizeof string, "%s- ไม่พบข้อมูลคำแนะนำในระบบ", string);
        }

        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "รายละเอียดไอเท็ม [Item Info]", string, "ตกลง", "");
    }
    PlayerCantSelectTextDraw[playerid] = false;
    return 1;
}

RemoveHomeButton(playerid){
    PlayerTextDrawHide(playerid, HomeGetButton[playerid]);
    PlayerTextDrawHide(playerid, HomeInfoButton[playerid]);
    PlayerTextDrawDestroy(playerid, HomeGetButton[playerid]);
    PlayerTextDrawDestroy(playerid, HomeInfoButton[playerid]);
    PlayerHomeShowButton[playerid] = false;
    return 1;
}

LoadHomeButtonTextDraw(playerid){
    new Float:getX = 244.0, Float:getY = 76.0;
    new Float:infoX = 244.0, Float:infoY = 91.0;
    PlayerHomeShowButton[playerid] = true;
    for(new i; i<MAX_HOME_MENU_ROWS; i++){
        for(new j; j<MAX_HOME_MENU_COLUMN; j++){
            if(PlayerHomeInvListItemRows[playerid] == i && PlayerHomeInvListItemColumn[playerid] == j){
                printf("[Home]: create usebutton index: %d", PlayerGetIndexHomeSlotItem[playerid]);
                HomeGetButton[playerid] = CreatePlayerTextDraw(playerid, getX+PlayerPositionInventoryX[playerid], getY+PlayerPositionInventoryY[playerid], "GET");
                PlayerTextDrawFont(playerid, HomeGetButton[playerid], 1);
                PlayerTextDrawLetterSize(playerid, HomeGetButton[playerid], 0.220833, 1.149999);
                PlayerTextDrawTextSize(playerid, HomeGetButton[playerid], 16.500000, 22.500000);
                PlayerTextDrawSetOutline(playerid, HomeGetButton[playerid], 1);
                PlayerTextDrawSetShadow(playerid, HomeGetButton[playerid], 0);
                PlayerTextDrawAlignment(playerid, HomeGetButton[playerid], 2);
                PlayerTextDrawColor(playerid, HomeGetButton[playerid], -1);
                PlayerTextDrawBackgroundColor(playerid, HomeGetButton[playerid], 255);
                PlayerTextDrawBoxColor(playerid, HomeGetButton[playerid], 200);
                PlayerTextDrawUseBox(playerid, HomeGetButton[playerid], 1);
                PlayerTextDrawSetProportional(playerid, HomeGetButton[playerid], 1);
                PlayerTextDrawSetSelectable(playerid, HomeGetButton[playerid], 1);

                HomeInfoButton[playerid] = CreatePlayerTextDraw(playerid, infoX+PlayerPositionInventoryX[playerid], infoY+PlayerPositionInventoryY[playerid], "INFO");
                PlayerTextDrawFont(playerid, HomeInfoButton[playerid], 1);
                PlayerTextDrawLetterSize(playerid, HomeInfoButton[playerid], 0.220833, 1.149999);
                PlayerTextDrawTextSize(playerid, HomeInfoButton[playerid], 16.500000, 22.500000);
                PlayerTextDrawSetOutline(playerid, HomeInfoButton[playerid], 1);
                PlayerTextDrawSetShadow(playerid, HomeInfoButton[playerid], 0);
                PlayerTextDrawAlignment(playerid, HomeInfoButton[playerid], 2);
                PlayerTextDrawColor(playerid, HomeInfoButton[playerid], -1);
                PlayerTextDrawBackgroundColor(playerid, HomeInfoButton[playerid], 255);
                PlayerTextDrawBoxColor(playerid, HomeInfoButton[playerid], 200);
                PlayerTextDrawUseBox(playerid, HomeInfoButton[playerid], 1);
                PlayerTextDrawSetProportional(playerid, HomeInfoButton[playerid], 1);
                PlayerTextDrawSetSelectable(playerid, HomeInfoButton[playerid], 1);

                PlayerTextDrawShow(playerid, HomeGetButton[playerid]);
                PlayerTextDrawShow(playerid, HomeInfoButton[playerid]);

                break;
            }
            getX += 29.0;
            infoX += 29.0;
        }

        getX = 244.0;
        infoX = 244.0;

        getY += 33.0;
        infoY += 33.0;
    }
    return 1;
}

LoadHomeInvTD_Slot(playerid){
    new Float:modelX = 230.0, Float:modelY = 73.0;
    new Float:amountX = 256.0, Float:amountY = 95.0;

    for(new i=0; i<MAX_HOME_MENU_ROWS; i++){
        for(new j=0; j<MAX_HOME_MENU_COLUMN; j++){
            PlayerHomeSlotModel[playerid][i][j] = PlayerHomeSlotCount[playerid];
            PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]] = CreatePlayerTextDraw(playerid, modelX+PlayerPositionInventoryX[playerid], modelY+PlayerPositionInventoryY[playerid], "Preview_Model");
            PlayerTextDrawFont(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 5);
            PlayerTextDrawLetterSize(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 28.000000, 31.500000);
            PlayerTextDrawSetOutline(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 0);
            PlayerTextDrawSetShadow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 0);
            PlayerTextDrawAlignment(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 1);
            PlayerTextDrawColor(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], -1);
            PlayerTextDrawBackgroundColor(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 842150655);
            PlayerTextDrawBoxColor(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 255);
            PlayerTextDrawUseBox(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 0);
            PlayerTextDrawSetProportional(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 1);
            PlayerTextDrawSetPreviewModel(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 19918);
            PlayerTextDrawSetPreviewRot(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], -10.000000, 0.000000, -20.000000, 1.000000);
            PlayerTextDrawSetPreviewVehCol(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 1, 1);
            PlayerTextDrawSetSelectable(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]++], 1);

            PlayerHomeSlotAmount[playerid][i][j] = PlayerHomeSlotCount[playerid];
            PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]] = CreatePlayerTextDraw(playerid, amountX+PlayerPositionInventoryX[playerid], amountY+PlayerPositionInventoryY[playerid], "1000");
            PlayerTextDrawFont(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 1);
            PlayerTextDrawLetterSize(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 0.170833, 0.800000);
            PlayerTextDrawTextSize(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 0);
            PlayerTextDrawSetShadow(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 0);
            PlayerTextDrawAlignment(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 3);
            PlayerTextDrawColor(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], -1);
            PlayerTextDrawBackgroundColor(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 255);
            PlayerTextDrawBoxColor(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 50);
            PlayerTextDrawUseBox(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 0);
            PlayerTextDrawSetProportional(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]], 1);
            PlayerTextDrawSetSelectable(playerid, PlayerHomeSlotTextDraw[playerid][PlayerHomeSlotCount[playerid]++], 0);

            modelX += 29.0;
            amountX += 29.0;
        }  

        modelX = 230.0;
        amountX = 256.0;

        modelY += 33.0;
        amountY += 33.0;         
    }
}

LoadHomeInvTextDraw(playerid){
    PlayerHomeInvTD[playerid][0] = CreatePlayerTextDraw(playerid, 316.500000+PlayerPositionInventoryX[playerid], 41.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][0], 0.600000, 30.500061);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][0], 298.500000, 176.500000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][0], 2);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][0], 555819519);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][0], 0);

    PlayerHomeInvTD[playerid][1] = CreatePlayerTextDraw(playerid, 316.500000+PlayerPositionInventoryX[playerid], 74.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][1], 0.600000, 21.750133);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][1], 298.500000, 173.000000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][1], 2);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][1], 320017407);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][1], 0);

    PlayerHomeInvTD[playerid][2] = CreatePlayerTextDraw(playerid, 316.500000+PlayerPositionInventoryX[playerid], 41.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][2], 0);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][2], 0.600000, 1.450034);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][2], 298.500000, 176.500000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][2], 2);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][2], PlayerInventoryCodeColor[playerid]);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][2], 0);

    PlayerHomeInvTD[playerid][3] = CreatePlayerTextDraw(playerid, 229.000000+PlayerPositionInventoryX[playerid], 40.000000+PlayerPositionInventoryY[playerid], "My Home");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][3], 0.262499, 1.500000);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][3], 466.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][3], 0);

    PlayerHomeInvTD[playerid][4] = CreatePlayerTextDraw(playerid, 254.500000+PlayerPositionInventoryX[playerid], 58.000000+PlayerPositionInventoryY[playerid], "Home Storage");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][4], 0.195831, 1.250000);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][4], 16.500000, 49.000000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][4], 2);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][4], 1296911816);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][4], 1);

    PlayerHomeInvTD[playerid][5] = CreatePlayerTextDraw(playerid, 403.000000+PlayerPositionInventoryX[playerid], 58.000000+PlayerPositionInventoryY[playerid], "0/64");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][5], 0.195831, 1.250000);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][5], 16.500000, 49.000000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][5], 3);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][5], 1296911816);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][5], 0);

    PlayerHomeInvTD[playerid][6] = CreatePlayerTextDraw(playerid, 230.000000+PlayerPositionInventoryX[playerid], 274.000000+PlayerPositionInventoryY[playerid], "ld_pool:ball");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][6], 4);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][6], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][6], 6.000000, 8.000000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][6], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][6], -16776961);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][6], -16777166);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][6], 1);

    PlayerHomeInvTD[playerid][7] = CreatePlayerTextDraw(playerid, 244.000000+PlayerPositionInventoryX[playerid], 274.000000+PlayerPositionInventoryY[playerid], "ld_pool:ball");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][7], 4);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][7], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][7], 6.000000, 8.000000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][7], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][7], -16776961);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][7], -16777166);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][7], 1);

    PlayerHomeInvTD[playerid][8] = CreatePlayerTextDraw(playerid, 258.000000+PlayerPositionInventoryX[playerid], 274.000000+PlayerPositionInventoryY[playerid], "ld_pool:ball");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][8], 4);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][8], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][8], 6.000000, 8.000000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][8], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][8], -16776961);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][8], -16777166);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][8], 1);

    PlayerHomeInvTD[playerid][9] = CreatePlayerTextDraw(playerid, 232.000000+PlayerPositionInventoryX[playerid], 287.000000+PlayerPositionInventoryY[playerid], "$");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][9], 0.270832, 1.399999);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][9], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][9], 2);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][9], 2094792959);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][9], 50);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][9], 0);

    PlayerHomeInvTD[playerid][10] = CreatePlayerTextDraw(playerid, 237.000000+PlayerPositionInventoryX[playerid], 289.000000+PlayerPositionInventoryY[playerid], "$0");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][10], 0.187500, 0.949998);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][10], 665.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][10], 1);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][10], 50);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][10], 0);

    PlayerHomeInvTD[playerid][11] = CreatePlayerTextDraw(playerid, 232.000000+PlayerPositionInventoryX[playerid], 302.000000+PlayerPositionInventoryY[playerid], "$");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][11], 1);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][11], 0.224996, 1.350000);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][11], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][11], 2);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][11], -16776961);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][11], 50);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][11], 0);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][11], 0);

    PlayerHomeInvTD[playerid][12] = CreatePlayerTextDraw(playerid, 237.000000+PlayerPositionInventoryX[playerid], 304.000000+PlayerPositionInventoryY[playerid], "$0");
    PlayerTextDrawFont(playerid, PlayerHomeInvTD[playerid][12], 1);
    PlayerTextDrawLetterSize(playerid, PlayerHomeInvTD[playerid][12], 0.187500, 0.949998);
    PlayerTextDrawTextSize(playerid, PlayerHomeInvTD[playerid][12], 665.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerHomeInvTD[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, PlayerHomeInvTD[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, PlayerHomeInvTD[playerid][12], 1);
    PlayerTextDrawColor(playerid, PlayerHomeInvTD[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerHomeInvTD[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, PlayerHomeInvTD[playerid][12], 50);
    PlayerTextDrawUseBox(playerid, PlayerHomeInvTD[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, PlayerHomeInvTD[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerHomeInvTD[playerid][12], 0);
}