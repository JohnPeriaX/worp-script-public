#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

Reset_PlayerBiz(playerid){
    nearBiz_var[playerid] = -1;
    for(new i=0; i<20; i++){
        PlayerGetItemIndexBiz[playerid][i] = -1;
    }
    ItemBiz[playerid][ItemIndexBiz] = -1;
    format(ItemBiz[playerid][ItemNameBiz], 64, "NULL");
    ItemBiz[playerid][ItemKeyBiz] = MODEL_NULL;
    ItemBiz[playerid][ItemAmountBiz] = 0;
    ItemBiz[playerid][ItemPriceBiz] = 0;
    return 1;
}

Biz_GetName(type){

    new name[64];
    switch(type){
        case 1: name = "บาร์";
        case 2: name = "ร้านอาหาร";
        default: name = "ไม่พบประเภท";
    }
    return name;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(!LoggedIn[playerid]) return 1;
    new id = -1;
    if(newkeys & KEY_YES){
        if((id = Biz_Inside(playerid)) != -1){
            if(IsPlayerInRangeOfPoint(playerid, 3.0, Biz_Data[id][bizSelling][0], Biz_Data[id][bizSelling][1], Biz_Data[id][bizSelling][2]) && GetPlayerInterior(playerid) == Biz_Data[id][bizSellingInt] && GetPlayerVirtualWorld(playerid) == Biz_Data[id][bizSellingWorld]){
                ShowPlayerBizMenu(playerid, id);
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid){
    new bizid = Streamer_GetIntData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_EXTRA_ID);
    if(Iter_Contains(Iter_Biz, bizid)){
        if(nearBiz_var[playerid] == -1){
            if(checkpointid == Biz_Data[bizid][bizAreaEnter]){
                nearBiz_var[playerid] = bizid;
                PlayerShowMenuBiz(playerid);
            }
            else if(checkpointid == Biz_Data[bizid][bizAreaExit]){
                nearBiz_var[playerid] = bizid;
                PlayerShowMenuBizInt(playerid);
            }
        }
    }
    return 1;
}

ShowPlayerBizMenu(playerid, bizid){
    if(bizid != -1 && Iter_Contains(Iter_Biz, bizid)){
        new string[1024];
        if(Biz_Data[bizid][bizType] == 1){
            for(new i=0; i<MAX_ITEMS_BIZ; i++){
                if(Biz_Data[bizid][bizItems][i] == 0) format(string, sizeof string, "%s- ไม่มีสินค้า\n", string);
                else if(Biz_Data[bizid][bizItems][i] != 0) format(string, sizeof string, "%s- %s (จำนวนคงเหลือ: %s ชิ้น)\t\tราคา %s/ชิ้น\n", string, Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][i])][itemName]
                , FormatNumberNotMoney(Biz_Data[bizid][bizItemsAmount][i]), FormatNumber(Biz_Data[bizid][bizItemsPrice][i]));
            }
        }
        SetPVarInt(playerid, "BizGetID", bizid);
        Dialog_ShowEasy(playerid, BizSellingMenu, DIALOG_STYLE_LIST, "เมนูสำหรับกิจการนี้", string, "เลือก", "ยกเลิก");
    }
    return 1;
}

Dialog:BizSellingMenu(playerid, response, listitem, inputtext[]){
    if(!response) {
        DeletePVar(playerid, "BizGetID");
        return 1;
    }
    if(response){
        new bizid = GetPVarInt(playerid, "BizGetID");
        if(bizid == -1) return 1;   
        if(listitem >= 0 && listitem < MAX_ITEMS_BIZ){
            new string[128];
            SetPVarInt(playerid, "buyItemSlotBiz", listitem);
            format(string, sizeof string, "| %s (จำนวนคงเหลือ: %s ชิ้น)\tราคา %s/ชิ้น\nกรอกจำนวนที่คุณต้องการจะซื้อ: ", Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][listitem])][itemName]
            , FormatNumberNotMoney(Biz_Data[bizid][bizItemsAmount][listitem]), FormatNumber(Biz_Data[bizid][bizItemsPrice][listitem]));
            Dialog_ShowEasy(playerid, InputAmountBuyBiz, DIALOG_STYLE_INPUT, "ซื้อของกิจการ", string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:InputAmountBuyBiz(playerid, response, listitem, inputtext[]){
    if(!response) {
        DeletePVar(playerid, "BizGetID");
        return 1;
    }
    if(response){
        new bizid = GetPVarInt(playerid, "BizGetID");
        new slotitem = GetPVarInt(playerid, "buyItemSlotBiz");
		if(slotitem < 0 || slotitem >= MAX_ITEMS_BIZ) { SecurityAC_Report(playerid, "bad-biz-buy-slot", false); return 0; }
        new string[128];
        new amount = strval(inputtext);
        if(amount <= 0){
            format(string, sizeof string, "ไม่สามารถกรอกจำนวนน้อยกว่าหรือเท่ากับ 0 ชิ้นได้!!\n| %s (จำนวนคงเหลือ: %s ชิ้น)\tราคา %s/ชิ้น\nกรอกจำนวนที่คุณต้องการจะซื้อ: ", Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][slotitem])][itemName]
            , FormatNumberNotMoney(Biz_Data[bizid][bizItemsAmount][slotitem]), FormatNumber(Biz_Data[bizid][bizItemsPrice][slotitem]));
            Dialog_ShowEasy(playerid, InputAmountBuyBiz, DIALOG_STYLE_INPUT, "ซื้อของกิจการ", string, "ตกลง", "ยกเลิก");
            return 1;
        }

        if(amount > Biz_Data[bizid][bizItemsAmount][slotitem]){
            format(string, sizeof string, "สินค้านี้มีจำนวนไม่พอกับจำนวนที่คุณต้องการ!!\n| %s (จำนวนคงเหลือ: %s ชิ้น)\tราคา %s/ชิ้น\nกรอกจำนวนที่คุณต้องการจะซื้อ: ", Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][slotitem])][itemName]
            , FormatNumberNotMoney(Biz_Data[bizid][bizItemsAmount][slotitem]), FormatNumber(Biz_Data[bizid][bizItemsPrice][slotitem]));
            Dialog_ShowEasy(playerid, InputAmountBuyBiz, DIALOG_STYLE_INPUT, "ซื้อของกิจการ", string, "ตกลง", "ยกเลิก");
            return 1;
        }

        new price = amount * Biz_Data[bizid][bizItemsPrice][slotitem];
        if(GetMoney(playerid) < price){
            format(string, sizeof string, "คุณมีจำนวนเงินไม่พอกับราคาที่คุณต้องจ่าย!!\n| %s (จำนวนคงเหลือ: %s ชิ้น)\tราคา %s/ชิ้น\nกรอกจำนวนที่คุณต้องการจะซื้อ: ", Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][slotitem])][itemName]
            , FormatNumberNotMoney(Biz_Data[bizid][bizItemsAmount][slotitem]), FormatNumber(Biz_Data[bizid][bizItemsPrice][slotitem]));
            Dialog_ShowEasy(playerid, InputAmountBuyBiz, DIALOG_STYLE_INPUT, "ซื้อของกิจการ", string, "ตกลง", "ยกเลิก");
            return 1;
        }

        new itemid = PlayerInventory_AddItem(playerid, Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][slotitem])][itemName], Biz_Data[bizid][bizItems][slotitem], amount);
        if(itemid == -1) return ErrorMsg(playerid, "คุณมีพื้นที่กระเป๋าไม่เพียงพอ, กรุณาเคลียร์กระเป๋าของคุณก่อน");

        SendClientMessageEx(playerid, COLOR_YELLOW, "| คุณได้ซื้อ '%s' จำนวน %s ชิ้นในราคา %s เรียบร้อยแล้ว", Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][slotitem])][itemName],
        FormatNumberNotMoney(amount), FormatNumber(price));
        GiveMoney(playerid, -price, "Buying Item In Biz");
        Biz_Data[bizid][bizItemsAmount] -= amount;

        Biz_Data[bizid][bizTotalMoney] += price;

        if(Biz_Data[bizid][bizItemsAmount] - amount <= 0){
            Biz_Data[bizid][bizItems][slotitem] = 0;
            Biz_Data[bizid][bizItemsAmount][slotitem] = 0;
            Biz_Data[bizid][bizItemsPrice][slotitem] = 0;
        }

        Biz_Save(bizid);
    }
    return 1;
}

timer SetTimeResetNearBiz[8000](playerid){
    nearBiz_var[playerid] = -1;
}

hook OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP:checkpointid){
    new bizid = Streamer_GetIntData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_EXTRA_ID);
    if(Iter_Contains(Iter_Biz, bizid)){
        if(checkpointid == Biz_Data[bizid][bizAreaEnter] || checkpointid == Biz_Data[bizid][bizAreaExit]){
            defer SetTimeResetNearBiz(playerid);
        }
    }
    return 1;
}

Biz_Inside(playerid){
    foreach(new i : Iter_Biz) {
        if (GetPlayerInterior(playerid) == Biz_Data[i][bizIntExit] && GetPlayerVirtualWorld(playerid) == Biz_Data[i][bizID] + WORLD_BIZ) {
            return i;
        }
    }
	return -1;
}

ShowMenuMyBiz(playerid, bizid){
    if(bizid != -1 && Iter_Contains(Iter_Biz, bizid)){
        Dialog_ShowEasy(playerid, MyBizMenu, DIALOG_STYLE_LIST, "กิจการของฉัน","วางจุดขายของกิจการมายังจุดที่คุณยืนอยู่\nเพิ่มรายการสินค้า", "เลือก", "ยกเลิก");
    }
    return 1;
}

Dialog:MyBizMenu(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new bizid = -1;
            if(( bizid = Biz_Inside(playerid)) != -1 && Biz_Data[bizid][bizOwner] == PlayerData[playerid][pID]){
                new Float:px, Float:py, Float:pz, Float:pa, pint = GetPlayerInterior(playerid);
                GetPlayerPos(playerid, px, py, pz);
                GetPlayerFacingAngle(playerid, pa);

                Biz_Data[bizid][bizSelling][0] = px;
                Biz_Data[bizid][bizSelling][1] = py;
                Biz_Data[bizid][bizSelling][2] = pz;
                Biz_Data[bizid][bizSellingInt] = pint;
                Biz_Data[bizid][bizSellingWorld] = Biz_Data[bizid][bizID] + WORLD_BIZ;

                Biz_Refresh(bizid);
                Biz_Save(bizid);

                SendClientMessage(playerid, COLOR_YELLOW, "| คุณได้ปรับจุดขายของกิจการของคุณมายังตำแหน่งปัจจุบันของคุณเรียบร้อยแล้ว");
            }
        }
        if(listitem == 1){
            new bizid = -1;
            if(( bizid = Biz_Inside(playerid)) != -1 && Biz_Data[bizid][bizOwner] == PlayerData[playerid][pID]){
                new string[1024];
                SetPVarInt(playerid, "BizGetID", bizid);
                for(new i=0; i<MAX_ITEMS_BIZ; i++){
                    if(Biz_Data[bizid][bizItems][i] == 0) format(string, sizeof string, "%s- ไม่มีสินค้า\n", string);
                    else if(Biz_Data[bizid][bizItems][i] != 0) format(string, sizeof string, "%s- %s (จำนวนคงเหลือ: %s ชิ้น)\t\tราคา %s/ชิ้น\n", string, Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][i])][itemName]
                    , FormatNumberNotMoney(Biz_Data[bizid][bizItemsAmount][i]), FormatNumber(Biz_Data[bizid][bizItemsPrice][i]));
                }
                Dialog_ShowEasy(playerid, EdititemBiz, DIALOG_STYLE_LIST, "สินค้าที่กำลังขายอยู่", string, "เลือก", "ยกเลิก");
            }
        }
    }
    return 1;
}

CheckPlayerItemCanPut(playerid, typebiz, itemid){
    if(typebiz == 1){
        if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Beer", true)) return 1;
        else if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Apple Wine", true)) return 1;
    }
    return -1;
}

Dialog:InputItemBiz(playerid, response, listitem, inputtext[]){
    if(!response){
        DeletePVar(playerid, "BizGetID");
        DeletePVar(playerid, "itemInputBizSlot");
        return 1;
    }
    if(response){
        new bizid = GetPVarInt(playerid, "BizGetID");
        if(bizid == -1) return 1;
        if(listitem >= 0 && listitem < 20){
            new itemid = PlayerGetItemIndexBiz[playerid][listitem];
            if(itemid != -1){
                new caption[256];
                ItemBiz[playerid][ItemIndexBiz] = itemid;
                format(ItemBiz[playerid][ItemNameBiz], 64, Inventory_Player[playerid][itemid][itemName]);
                ItemBiz[playerid][ItemKeyBiz] = Inventory_Player[playerid][itemid][itemKey];
                format(caption, sizeof caption, "%s (จำนวน: %d)", Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity]);
                Dialog_ShowEasy(playerid, InputAmountItemBiz, DIALOG_STYLE_INPUT, caption, "กรุณากรอกจำนวนที่คุณต้องการจะลงขาย:", "ตกลง", "ยกเลิก");
            }
        }
    }
    return 1;
}

Dialog:InputAmountItemBiz(playerid, response, listitem, inputtext[]){
    if(!response){
        DeletePVar(playerid, "BizGetID");
        DeletePVar(playerid, "itemInputBizSlot");
        for(new i=0; i<20; i++){
            PlayerGetItemIndexBiz[playerid][i] = -1;
        }
        return 1;
    }
    if(response){
        new itemid = ItemBiz[playerid][ItemIndexBiz];
		if(itemid < 0 || itemid >= 108) { SecurityAC_Report(playerid, "bad-biz-item-index", false); return 0; }
        new caption[256];
        new amount = strval(inputtext);

        if(amount > Inventory_Player[playerid][itemid][itemQuantity]){
            if(itemid != -1){
                ItemBiz[playerid][ItemIndexBiz] = itemid;
                format(ItemBiz[playerid][ItemNameBiz], 64, Inventory_Player[playerid][itemid][itemName]);
                ItemBiz[playerid][ItemKeyBiz] = Inventory_Player[playerid][itemid][itemKey];
                format(caption, sizeof caption, "%s (จำนวน: %d)", Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity]);
                Dialog_ShowEasy(playerid, InputAmountItemBiz, DIALOG_STYLE_INPUT, caption, "คุณมีจำนวนไอเท็มไม่เพียงพอ!\nกรุณากรอกจำนวนที่คุณต้องการจะลงขาย:", "ตกลง", "ยกเลิก");
            }
            return 1;
        }

        ItemBiz[playerid][ItemAmountBiz] = amount;

        if(itemid != -1){
            format(caption, sizeof caption, "%s (จำนวนที่เลือก: %d)", Inventory_Player[playerid][itemid][itemName], ItemBiz[playerid][ItemAmountBiz]);
            Dialog_ShowEasy(playerid, InputPriceItemBiz, DIALOG_STYLE_INPUT, caption, "กรอก ราคา/ชิ้น ที่คุณต้องการจะขายไอเท็มชิ้นนี้:", "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:InputPriceItemBiz(playerid, response, listitem, inputtext[]){
    if(!response){
        DeletePVar(playerid, "BizGetID");
        DeletePVar(playerid, "itemInputBizSlot");
        for(new i=0; i<20; i++){
            PlayerGetItemIndexBiz[playerid][i] = -1;
        }
        return 1;
    }
    if(response){
        new bizid = GetPVarInt(playerid, "BizGetID");
        new itemid = ItemBiz[playerid][ItemIndexBiz];
        new caption[256];
        new price = strval(inputtext);
        if(itemid != -1){
            if(price <= 0){
                format(caption, sizeof caption, "%s (จำนวนที่เลือก: %d)", Inventory_Player[playerid][itemid][itemName], ItemBiz[playerid][ItemAmountBiz]);
                Dialog_ShowEasy(playerid, InputPriceItemBiz, DIALOG_STYLE_INPUT, caption, "คุณต้องกรอกราคามากกว่า 0!\nกรอก ราคา/ชิ้น ที่คุณต้องการจะขายไอเท็มชิ้นนี้:", "ตกลง", "ยกเลิก");
                return 1;
            }
            
            ItemBiz[playerid][ItemPriceBiz] = price;

            new slotitem = GetPVarInt(playerid, "itemInputBizSlot");

            Biz_Data[bizid][bizItems][slotitem] = Inventory_Player[playerid][itemid][itemKey];
            Biz_Data[bizid][bizItemsAmount][slotitem] = ItemBiz[playerid][ItemAmountBiz];
            Biz_Data[bizid][bizItemsPrice][slotitem] = ItemBiz[playerid][ItemPriceBiz];
            Biz_Save(bizid);
            SendClientMessageEx(playerid, COLOR_YELLOW, "| คุณได้ลงขาย %s จำนวน %s ชิ้น ราคา %s/ชิ้น เรียบร้อยแล้ว", Inventory_Player[playerid][itemid][itemName], FormatNumberNotMoney(Biz_Data[bizid][bizItemsAmount][slotitem]), FormatNumber(Biz_Data[bizid][bizItemsPrice][slotitem]));
            
            PlayerInventory_RemoveEx(playerid, itemid, Biz_Data[bizid][bizItemsAmount][slotitem]);

            DeletePVar(playerid, "BizGetID");
            DeletePVar(playerid, "itemInputBizSlot");
            DeletePVar(playerid, "itemInputBizSlot");
            for(new i=0; i<20; i++){
                PlayerGetItemIndexBiz[playerid][i] = -1;
            }
            ItemBiz[playerid][ItemIndexBiz] = -1;
            format(ItemBiz[playerid][ItemNameBiz], 64, "NULL");
            ItemBiz[playerid][ItemKeyBiz] = MODEL_NULL;
            ItemBiz[playerid][ItemAmountBiz] = 0;
            ItemBiz[playerid][ItemPriceBiz] = 0;
        }
    }
    return 1;
}

Dialog:EdititemBiz(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new bizid = GetPVarInt(playerid, "BizGetID");
        if(bizid == -1) return 1;
        new string[1024], caption[256], count = 0;
        if(listitem >= 0 && listitem < MAX_ITEMS_BIZ){
            if(Biz_Data[bizid][bizItems][listitem] == 0){
                for(new i=0; i<PlayerData[playerid][pMaxItem]; i++) if(i < 108){
                    if(CheckPlayerItemCanPut(playerid, Biz_Data[bizid][bizType], i) == -1) continue;
                    format(string, sizeof string, "%s- %s (มีจำนวน: %d ชิ้น)\n", string, Inventory_Player[playerid][i][itemName], Inventory_Player[playerid][i][itemQuantity]);
                    PlayerGetItemIndexBiz[playerid][count++] = i;
                }
                if(count == 0) format(string, sizeof string, "ไม่พบไอเท็มที่สามารถลงขายได้");
                else {
                    SetPVarInt(playerid, "itemInputBizSlot", listitem);
                }
                Dialog_ShowEasy(playerid, InputItemBiz, DIALOG_STYLE_LIST, "เลือกสินค้าที่ต้องการจะลงขาย", string, "เลือก", "ยกเลิก");
            }
            else{
                SetPVarInt(playerid, "slotitemBiz", listitem);
                format(caption, sizeof caption, "| %s (จำนวนคงเหลือ: %s ชิ้น | ราคา %s/ชิ้น)", Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][listitem])][itemName],
                FormatNumberNotMoney(Biz_Data[bizid][bizItemsAmount][listitem]), FormatNumber(Biz_Data[bizid][bizItemsPrice][listitem]));
                Dialog_ShowEasy(playerid, BizHasItem, DIALOG_STYLE_LIST, caption, "แก้ไข ราคา\nนำไอเท็มออก", "เลือก", "ยกเลิก");
            }
        }
    }
    return 1;
}

Dialog:BizHasItem(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new bizid = GetPVarInt(playerid, "BizGetID");
        if(bizid == -1) return 1;
        new string[256];
        if(listitem == 0){
            new slotitem = GetPVarInt(playerid, "slotitemBiz");
            format(string, sizeof string, "| %s (จำนวนคงเหลือ: %s ชิ้น | ราคา %s/ชิ้น)\
            \nกรุณากรอกราคาใหม่ที่คุณต้องการจะเปลี่ยน:", Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][slotitem])][itemName],
            FormatNumberNotMoney(Biz_Data[bizid][bizItemsAmount][slotitem]), FormatNumber(Biz_Data[bizid][bizItemsPrice][slotitem]));
            Dialog_ShowEasy(playerid, EditPriceItemBiz, DIALOG_STYLE_INPUT, "| %s", string, "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            new slotitem = GetPVarInt(playerid, "slotitemBiz");

            new itemid = PlayerInventory_AddItem(playerid, Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][slotitem])][itemName], Biz_Data[bizid][bizItems][slotitem], Biz_Data[bizid][bizItemsAmount][slotitem]);
            if(itemid == -1) return ErrorMsg(playerid, "กระเป๋าของคุณไม่เพียงพอต่อการเก็บไอเท็มชิ้นนี้กรุณาเคลียร์กระเป๋าของคุณก่อน");

            SendClientMessageEx(playerid, COLOR_YELLOW, "| คุณได้รับไอเท็ม '%s' + %s", Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][slotitem])][itemName], FormatNumberNotMoney(Biz_Data[bizid][bizItemsAmount][slotitem]));

            SendClientMessageEx(playerid, COLOR_YELLOW, "| คุณได้นำสินค้า %s ออกจากการขายเรียบร้อยแล้ว", Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][slotitem])][itemName]);
            Biz_Data[bizid][bizItems][slotitem] = 0;
            Biz_Data[bizid][bizItemsAmount][slotitem] = 0;
            Biz_Data[bizid][bizItemsPrice][slotitem] = 0;
            Biz_Save(bizid);
        }
    }
    return 1;
}

Dialog:EditPriceItemBiz(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new price = strval(inputtext);
        new bizid = GetPVarInt(playerid, "BizGetID");
        new slotitem = GetPVarInt(playerid, "slotitemBiz");
        if(price <= 0){
            new string[256];
            format(string, sizeof string, "กรุณากรอกราคาให้มากกว่า 0!\n| %s (จำนวนคงเหลือ: %s ชิ้น | ราคา %s/ชิ้น)\
            \nกรุณากรอกราคาใหม่ที่คุณต้องการจะเปลี่ยน:", Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][slotitem])][itemName],
            FormatNumberNotMoney(Biz_Data[bizid][bizItemsAmount][slotitem]), FormatNumber(Biz_Data[bizid][bizItemsPrice][slotitem]));
            Dialog_ShowEasy(playerid, EditPriceItemBiz, DIALOG_STYLE_INPUT, "| %s", string, "ตกลง", "ยกเลิก");
            return 1;
        }

        Biz_Data[bizid][bizItemsPrice][slotitem] = price;
        Biz_Save(bizid);

        SendClientMessageEx(playerid, COLOR_YELLOW, "| คุณได้อัพเดทราคา %s ใหม่เป็น %s/ชิ้น เรียบร้อยแล้ว", Item_Data[CheckItemModelIsName(Biz_Data[bizid][bizItems][slotitem])][itemName],
        FormatNumber(Biz_Data[bizid][bizItemsPrice][slotitem]));
    }
    return 1;
}

CMD:mybiz(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    new bizid = -1;
    if((bizid = Biz_Inside(playerid)) != -1){
        ShowMenuMyBiz(playerid, bizid);
    }
    return 1;
}

CMD:openmusic(playerid, params[]){
    new id = -1, string[128];
    if((id = Biz_Inside(playerid)) != -1){
        if(Biz_Data[id][bizType] != 1) return ErrorMsg(playerid, "กิจการของคุณไม่ใช่บาร์ ไม่สามารถใช้งานได้");
        if(Biz_Data[id][bizOwner] != PlayerData[playerid][pID] && Biz_Data[id][bizBarDJ] != playerid) return ErrorMsg(playerid, "คุณไม่ใช่เจ้าบาร์หรือ DJ ประจำบาร์");
        if (sscanf(params, "s[128]", string)) return SystemMsg(playerid, "/openmusic [song url]");
		if(CheckIsHaveThaiFont(string) == 1) return ErrorMsg(playerid, "รูปแบบลิ้งไม่ถูกต้อง");
		foreach(new i : Player){
            if(!LoggedIn[i]) continue;
            if(GetPlayerInterior(i) == Biz_Data[id][bizIntExit] && GetPlayerVirtualWorld(i) == Biz_Data[id][bizID] + WORLD_BIZ){
                StopAudioStreamForPlayer(i);
				PlayAudioStreamForPlayer(i, string);
                SendClientMessageEx(i, COLOR_YELLOW, "- DJ ได้ทำการเปลี่ยนเพลงแล้ว", ReturnRoleplayName(playerid));
            }
        }
        format(Biz_Data[id][bizUrlMp3], 128, string);
    }
    return 1;
}

CMD:closemusic(playerid, params[]){
    new id = -1;
    if((id = Biz_Inside(playerid)) != -1){
        if(Biz_Data[id][bizType] != 1) return ErrorMsg(playerid, "กิจการของคุณไม่ใช่บาร์ ไม่สามารถใช้งานได้");
        if(Biz_Data[id][bizOwner] != PlayerData[playerid][pID] && Biz_Data[id][bizBarDJ] != playerid) return ErrorMsg(playerid, "คุณไม่ใช่เจ้าบาร์หรือ DJ ประจำบาร์");
		foreach(new i : Player){
            if(!LoggedIn[i]) continue;
            if(GetPlayerInterior(i) == Biz_Data[id][bizIntExit] && GetPlayerVirtualWorld(i) == Biz_Data[id][bizID] + WORLD_BIZ){
                StopAudioStreamForPlayer(i);
                SendClientMessageEx(i, COLOR_YELLOW, "- DJ ได้ทำการปิดเพลงเรียบร้อยแล้ว", ReturnRoleplayName(playerid));
            }
        }
        format(Biz_Data[id][bizUrlMp3], 128, "NULL");
    }
    return 1;
}

PlayerShowMenuBizInt(playerid){
    new string[256];
    new bizid = nearBiz_var[playerid];
    if(bizid != -1){
        if(Biz_Data[bizid][bizOwner] == PlayerData[playerid][pID]){
            format(string, sizeof string, "- ออกจากกิจการ\
            \n- เช็คกิจการ\
            \n- ล็อค/ปลดล็อค กิจการ");
            Dialog_ShowEasy(playerid, BizOwnerExit, DIALOG_STYLE_LIST, "กิจการของคุณ", string, "เลือก", "ปิด");
        }
        else{
            format(string, sizeof string, "- กิจการของ: [%s]\
            \n- ประเภทกิจการ: [%s]", Biz_Data[bizid][bizOwnerName], Biz_GetName(Biz_Data[bizid][bizType]));
            Dialog_ShowEasy(playerid, BizNotOwnerExit, DIALOG_STYLE_MSGBOX, "กิจการ", string, "ออก", "ปิด");
        }
    }
    return 1;
}

PlayerShowMenuBiz(playerid){
    new string[256];
    new bizid = nearBiz_var[playerid];
    if(bizid != -1){
        if(!Biz_Data[bizid][bizOwner]){
            format(string, sizeof string, "- ประเภทกิจการ: %s\
            \n- ราคากิจการแห่งนี้: %s\
            \n- เจ้าของ: ยังไม่มี\
            \n( หากคุณสนใจที่จะซื้อกิจการนี้ให้กดปุ่ม 'ซื้อ' เพื่อเริ่มทำสัญญาการซื้อขาย )", Biz_GetName(Biz_Data[bizid][bizType]), FormatNumber(Biz_Data[bizid][bizPrice]));
            Dialog_ShowEasy(playerid, BuyBiz, DIALOG_STYLE_MSGBOX, "กิจการ", string, "ซื้อ", "ปิด");
        }
        else{
            if(Biz_Data[bizid][bizOwner] == PlayerData[playerid][pID]){
                format(string, sizeof string, "- เข้ากิจการ\
                \n- เช็คกิจการ\
                \n- ล็อค/ปลดล็อค กิจการ");
                Dialog_ShowEasy(playerid, BizOwner, DIALOG_STYLE_LIST, "กิจการของคุณ", string, "เลือก", "ปิด");
            }
            else{
                format(string, sizeof string, "- กิจการของ: [%s]\
                \n- ประเภทกิจการ: [%s]", Biz_Data[bizid][bizOwnerName], Biz_GetName(Biz_Data[bizid][bizType]));
                Dialog_ShowEasy(playerid, BizNotOwner, DIALOG_STYLE_MSGBOX, "กิจการ", string, "เข้า", "ปิด");
            }
        }
    }
    return 1;
}

PlayerShowMenuMyBiz(playerid){
    new bizid = nearBiz_var[playerid], string[128];
    if(bizid != -1){
        if(Biz_Data[bizid][bizType] == 1){
            format(string, sizeof string, "- เงินในกิจการของคุณ: [%s]\n- รับสมัคร DJ ชั่วคราว\n- ตั้งค่าเข้ากิจการ: [%s]", FormatNumber(Biz_Data[bizid][bizTotalMoney]), FormatNumber(Biz_Data[bizid][bizEnterPrice]));
            Dialog_ShowEasy(playerid, BizOwnerMenuBar, DIALOG_STYLE_LIST, "กิจการของคุณ", string, "เลือก", "ปิด");
        }
        else{
            format(string, sizeof string, "- เงินในกิจการของคุณ: [%s]\n- ตั้งค่าเข้ากิจการ: [%s]", FormatNumber(Biz_Data[bizid][bizTotalMoney]), FormatNumber(Biz_Data[bizid][bizEnterPrice]));
            Dialog_ShowEasy(playerid, BizOwnerMenu, DIALOG_STYLE_LIST, "กิจการของคุณ", string, "เลือก", "ปิด");
        }
    }
    return 1;
}

Dialog:BizOwnerMenu(playerid, response, listitem, inputtext[]){
    if(!response) return nearBiz_var[playerid] = -1;
    if(response){
        new bizid = nearBiz_var[playerid], string[128];
        if(listitem == 0){
            format(string, sizeof string, "- เงินในกิจการของคุณมี: [%s]\
            \n- กรอกจำนวนเงินที่คุณต้องการจะถอนออก:", FormatNumber(Biz_Data[bizid][bizTotalMoney]));
            Dialog_ShowEasy(playerid, WithDrawMoneyBiz, DIALOG_STYLE_INPUT, "เบิกเงินกิจการ", string, "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            format(string, sizeof string, "- ค่าเข้ากิจการ: [%s]\
            \n- กรอกจำนวนเงินทีต้องการเก็บค่าเข้า:", FormatNumber(Biz_Data[bizid][bizEnterPrice]));
            Dialog_ShowEasy(playerid, EditEnterPrice, DIALOG_STYLE_INPUT, "ตั้งค่าเข้ากิจการ", string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:BizOwnerMenuBar(playerid, response, listitem, inputtext[]){
    if(!response) return nearBiz_var[playerid] = -1;
    if(response){
        new bizid = nearBiz_var[playerid], string[128];
        if(listitem == 0){
            format(string, sizeof string, "- เงินในกิจการของคุณมี: [%s]\
            \n- กรอกจำนวนเงินที่คุณต้องการจะถอนออก:", FormatNumber(Biz_Data[bizid][bizTotalMoney]));
            Dialog_ShowEasy(playerid, WithDrawMoneyBiz, DIALOG_STYLE_INPUT, "เบิกเงินกิจการ", string, "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            Dialog_ShowEasy(playerid, SelectIDDJ, DIALOG_STYLE_INPUT, "รับสมัคร DJ", "* อ่านก่อน การให้อำนาจ DJ จะถูกยกเลิกต่อเมื่อผู้เล่นออกเกม *\nกรุณากรอกไอดีผู้เล่นที่ต้องการจะให้เปิดเพลง:", "ตกลง", "ยกเลิก");
        }
        if(listitem == 2){
            format(string, sizeof string, "- ค่าเข้ากิจการ: [%s]\
            \n- กรอกจำนวนเงินทีต้องการเก็บค่าเข้า:", FormatNumber(Biz_Data[bizid][bizEnterPrice]));
            Dialog_ShowEasy(playerid, EditEnterPrice, DIALOG_STYLE_INPUT, "ตั้งค่าเข้ากิจการ", string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:EditEnterPrice(playerid, response, listitem, inputtext[]){
    if(!response) return nearBiz_var[playerid] = -1;
    if(response){
        new money = strval(inputtext);
        new string[256];
        new bizid = nearBiz_var[playerid];
        if(money < 0 || money > 5000){
            format(string, sizeof string, "* คุณตั้งค่าเข้าได้ 1 - 5000 เท่านั้น *\n- ค่าเข้ากิจการ: [%s]\
            \n- กรอกจำนวนเงินทีต้องการเก็บค่าเข้า:", FormatNumber(Biz_Data[bizid][bizEnterPrice]));
            Dialog_ShowEasy(playerid, EditEnterPrice, DIALOG_STYLE_INPUT, "ตั้งค่าเข้ากิจการ", string, "ตกลง", "ยกเลิก");
            return 1;
        }

        if(bizid != -1){
            Biz_Data[bizid][bizEnterPrice] = money;
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ปรับค่าเข้ากิจการของคุณเป็น [%s] เรียบร้อยแล้ว", FormatNumber(money));
            Biz_Save(bizid);
        }
    }
    return 1;
}

Dialog:SelectIDDJ(playerid, response, listitem, inputtext[]){
    if(!response) return nearBiz_var[playerid] = -1;
    if(response){
        new bizid = nearBiz_var[playerid];
        new userid;

        if (sscanf(inputtext, "u", userid))
            return Dialog_ShowEasy(playerid, SelectIDDJ, DIALOG_STYLE_INPUT, "รับสมัคร DJ", "* อ่านก่อน การให้อำนาจ DJ จะถูกยกเลิกต่อเมื่อผู้เล่นออกเกม *\nกรุณากรอกไอดีผู้เล่นที่ต้องการจะให้เปิดเพลง:", "ตกลง", "ยกเลิก");
        
        if(userid == INVALID_PLAYER_ID || !LoggedIn[userid]){
            return Dialog_ShowEasy(playerid, SelectIDDJ, DIALOG_STYLE_INPUT, "รับสมัคร DJ", "* ไอดีผู้เล่นไม่ถูกต้อง *\n* อ่านก่อน การให้อำนาจ DJ จะถูกยกเลิกต่อเมื่อผู้เล่นออกเกม *\nกรุณากรอกไอดีผู้เล่นที่ต้องการจะให้เปิดเพลง:", "ตกลง", "ยกเลิก");
        }

        if(bizid != -1){
            Biz_Data[bizid][bizBarDJ] = userid;
            SendClientMessageEx(userid, COLOR_YELLOW, "- คุณได้ถูกรับเชิญให้เป็น DJ ประจำบาร์ของ %s", ReturnRoleplayName(playerid));
            SendClientMessage(userid, COLOR_YELLOW, "[คำแนะนำ]: /openmusic, /closemusic");
        }
    }
    return 1;
}

Dialog:WithDrawMoneyBiz(playerid, response, listitem, inputtext[]){
    if(!response) return nearBiz_var[playerid] = -1;
    if(response){
        new money = strval(inputtext);
        new bizid = nearBiz_var[playerid], string[128];
        if(money <= 0 || money > Biz_Data[bizid][bizTotalMoney]){
            format(string, sizeof string, "* จำนวนเงินไม่ถูกต้อง *\n- เงินในกิจการของคุณมี: [%s]\
            \n- กรอกจำนวนเงินที่คุณต้องการจะถอนออก:", FormatNumber(Biz_Data[bizid][bizTotalMoney]));
            Dialog_ShowEasy(playerid, WithDrawMoneyBiz, DIALOG_STYLE_INPUT, "เบิกเงินกิจการ", string, "ตกลง", "ยกเลิก");
            return 1;
        }

        Biz_Data[bizid][bizTotalMoney] -= money;
        GiveMoney(playerid, money, "Get Money From Biz");
        format(string, sizeof string, "- คุณได้ทำการเบิกเงินจากกิจการของคุณเป็นจำนวนเงิน [%s] เรียบร้อยแล้ว", FormatNumber(money));
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การเบิกเงินสำเร็จ", string, "ตกลง", "");
        nearBiz_var[playerid] = -1;
    }
    return 1;
}

PlayerSetToIntBiz(playerid){
    new bizid = nearBiz_var[playerid];
    if(bizid != -1){
        if(Biz_Data[bizid][bizPosExit][0] != 0.0 && Biz_Data[bizid][bizPosExit][1] != 0.0){
            SetPlayerPosEx(playerid, Biz_Data[bizid][bizPosExit][0], Biz_Data[bizid][bizPosExit][1], Biz_Data[bizid][bizPosExit][2], Biz_Data[bizid][bizIntExit], Biz_Data[bizid][bizWorldExit]);
            SetPlayerFacingAngle(playerid, Biz_Data[bizid][bizPosExit][3]);
            SendClientMessageEx(playerid, COLOR_YELLOW, Biz_Data[bizid][bizInfo]);
            GameTextForPlayer(playerid,"~n~~n~~y~Loading Object....",8000,3);
            if(strcmp(Biz_Data[bizid][bizUrlMp3], "NULL")){
                StopAudioStreamForPlayer(playerid);
                PlayAudioStreamForPlayer(playerid, Biz_Data[bizid][bizUrlMp3]);
            }
        }
    }
    return 1;
}

PlayerSetToExitIntBiz(playerid){
    new bizid = nearBiz_var[playerid];
    if(bizid != -1){
        SetPlayerPosEx(playerid, Biz_Data[bizid][bizPosEnter][0], Biz_Data[bizid][bizPosEnter][1], Biz_Data[bizid][bizPosEnter][2], Biz_Data[bizid][bizIntEnter], Biz_Data[bizid][bizWorldEnter]);
        SetPlayerFacingAngle(playerid, Biz_Data[bizid][bizPosEnter][3]);
        GameTextForPlayer(playerid,"~n~~n~~y~Loading Object....",8000,3);
        StopAudioStreamForPlayer(playerid);
    }
    return 1;
}

Dialog:BizNotOwnerExit(playerid, response, listitem, inputtext[]){
    if(!response) return nearBiz_var[playerid] = -1;
    if(response){
        new bizid = nearBiz_var[playerid];
        if(bizid != -1){
            if(Biz_Data[bizid][bizLocked]){
                return ErrorMsg(playerid, "กิจการนี้ถูกล็อคอยู่");
            }
            PlayerSetToExitIntBiz(playerid);
        }
        return 1;
    }
    return 1;
}

Dialog:BizOwnerExit(playerid, response, listitem, inputtext[]){
    if(!response) return nearBiz_var[playerid] = -1;
    if(response){
        new bizid = nearBiz_var[playerid];
        if(bizid != -1){
            switch(listitem){
                case 0:{    
                    if(Biz_Data[bizid][bizLocked]){
                        ErrorMsg(playerid, "กิจการนี้ถูกล็อคอยู่");
                        return PlayerShowMenuBizInt(playerid);
                    }
                    PlayerSetToExitIntBiz(playerid);
                }
                case 1:{
                    PlayerShowMenuMyBiz(playerid);
                }
                case 2:{
                    if(!Biz_Data[bizid][bizLocked]){
                        Biz_Data[bizid][bizLocked] = true;
                        GameTextForPlayer(playerid, "~w~Biz ~r~Locked", 5000, 6);
                        PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                        Biz_Save(bizid);
                    }
                    else{
                        Biz_Data[bizid][bizLocked] = false;
                        GameTextForPlayer(playerid, "~w~Biz ~g~Unlocked", 5000, 6);
                        PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                        Biz_Save(bizid);
                    }
                    return PlayerShowMenuBizInt(playerid);
                }
            }
        }
    }
    return 1;
}

Dialog:BizNotOwner(playerid, response, listitem, inputtext[]){
    if(!response) return nearBiz_var[playerid] = -1;
    if(response){
        new bizid = nearBiz_var[playerid];
        if(bizid != -1){
            if(Biz_Data[bizid][bizLocked]){
                return ErrorMsg(playerid, "กิจการนี้ถูกล็อคอยู่");
            }

            if(Biz_Data[bizid][bizEnterPrice] != 0){
                new string[128];
                format(string, sizeof string, "กิจการแห่งนี้มีค่าเข้ากิจการ [%s] คุณต้องการจะจ่ายหรือไม่?", FormatNumber(Biz_Data[bizid][bizEnterPrice]));
                Dialog_ShowEasy(playerid, ConfirmEnterBiz, DIALOG_STYLE_MSGBOX, "กิจการ", string, "ตกลง", "ยกเลิก");
            }
            else{
                PlayerSetToIntBiz(playerid);
            }
        }
        return 1;
    }
    return 1;
}

Dialog:ConfirmEnterBiz(playerid, response, listitem, inputtext[]){
    if(!response) return nearBiz_var[playerid] = -1;
    if(response){
        new bizid = nearBiz_var[playerid];
        if(GetMoney(playerid) < Biz_Data[bizid][bizEnterPrice]) {
            nearBiz_var[playerid] = -1;
            return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะจ่ายค่าเข้ากิจการ");
        }

        GiveMoney(playerid, -Biz_Data[bizid][bizEnterPrice], "Pay EnterPrice Biz");
        Biz_Data[bizid][bizTotalMoney] += Biz_Data[bizid][bizEnterPrice];
        PlayerSetToIntBiz(playerid);
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้จ่ายค่าเข้ากิจการเป็นจำนวนเงิน [%s] เรียบร้อยแล้ว", FormatNumber(Biz_Data[bizid][bizEnterPrice]));
    }
    return 1;
}

Dialog:BizOwner(playerid, response, listitem, inputtext[]){
    if(!response) return nearBiz_var[playerid] = -1;
    if(response){
        new bizid = nearBiz_var[playerid];
        if(bizid != -1){
            switch(listitem){
                case 0:{    
                    if(Biz_Data[bizid][bizLocked]){
                        ErrorMsg(playerid, "กิจการนี้ถูกล็อคอยู่");
                        return PlayerShowMenuBiz(playerid);
                    }

                    PlayerSetToIntBiz(playerid);
                }
                case 1:{
                    PlayerShowMenuMyBiz(playerid);
                }
                case 2:{
                    if(!Biz_Data[bizid][bizLocked]){
                        Biz_Data[bizid][bizLocked] = true;
                        GameTextForPlayer(playerid, "~w~Biz ~r~Locked", 5000, 6);
                        PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                        Biz_Save(bizid);
                    }
                    else{
                        Biz_Data[bizid][bizLocked] = false;
                        GameTextForPlayer(playerid, "~w~Biz ~g~Unlocked", 5000, 6);
                        PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                        Biz_Save(bizid);
                    }
                    return PlayerShowMenuBiz(playerid);
                }
            }
        }
    }
    return 1;
}

Dialog:BuyBiz(playerid, response, listitem, inputtext[]){
    if(!response) return nearBiz_var[playerid] = -1;
    if(response){
        new bizid = nearBiz_var[playerid];
        new string[128];
        if(GetMoney(playerid) < Biz_Data[bizid][bizPrice]) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การซื้อกิจการ", "[!] คุณมีเงินไม่เพียงพอที่จะซื้อกิจการนี้", "ตกลง", "");
        if(Biz_Data[bizid][bizOwner] != 0) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การซื้อกิจการ", "[!] กิจการนี้มีเจ้าของแล้ว, ไม่สามารถซื้อได้", "ตกลง", "");
        GiveMoney(playerid, -Biz_Data[bizid][bizPrice], "Buy Biz");
        Biz_Data[bizid][bizOwner] = PlayerData[playerid][pID];
        format(Biz_Data[bizid][bizOwnerName], 64, ReturnRoleplayName(playerid));
        format(string, sizeof string, "+ คุณได้ทำการซื้อกิจการนี้เรียบร้อยแล้ว โดยเงินรวมทั้งหมดคือ %s", FormatNumber(Biz_Data[bizid][bizPrice]));
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การซื้อกิจการ", string, "ตกลง", "");
        Biz_RefreshPickup(bizid);
        Biz_Save(bizid);
        nearBiz_var[playerid] = -1;
    }
    return 1;
}

ViewBizs(playerid){
	new string[2048], menu[20], count;

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

	SetPVarInt(playerid, "page", 1);

	foreach(new i : Iter_Biz){
        if(count == 20){
            format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
            break;
        }
        format(menu, 20, "menu%d", ++count);
        SetPVarInt(playerid, menu, i);
        format(string, sizeof(string), "%s(%i) | กิจการของ: %s\n", string, i, Biz_Data[i][bizOwnerName]);
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "รายชื่อกิจการ", "ไม่พบข้อมูลของกิจการ..", "ปิด", "");
	else Dialog_ShowEasy(playerid, BizList, DIALOG_STYLE_LIST, "รายชื่อกิจการ", string, "แก้ไข", "กลับ");
	return 1;
}

Dialog:BizList(playerid, response, listitem, inputtext[]){
	if(response) {
		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "BizEditID", GetPVarInt(playerid, str_biz));
			ShowPlayerEditBiz(playerid);
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

		foreach(new i : Iter_Biz){
            if(skipitem){
                skipitem--;
                continue;
            }
            if(count == 20){
                format(string, sizeof(string), "%s{B4B5B7}หน้า %d\n", string, (currentPage==1) ? 1 : currentPage+1);
                break;
            }
            format(menu, 20, "menu%d", ++count);
            SetPVarInt(playerid, menu, i);
            format(string, sizeof(string), "%s(%i) | กิจการของ: %s\n", string, i, Biz_Data[i][bizOwnerName]);
		}

		Dialog_ShowEasy(playerid, BizList, DIALOG_STYLE_LIST, "รายชื่อกิจการ", string, "แก้ไข", "กลับ");
	}
	return 1;
}

ShowPlayerEditBiz(playerid){
    new id = GetPVarInt(playerid, "BizEditID");
	new caption[128], dialog_str[1024];
	format(caption, sizeof(caption), "แก้ไขกิจการของ: %s (SQLID:%d)", Biz_Data[id][bizOwnerName], Biz_Data[id][bizID]);
    format(dialog_str, sizeof dialog_str, "เจ้าของกิจการ\t%s\n", Biz_Data[id][bizOwnerName]);
	format(dialog_str, sizeof dialog_str, "%s ข้อมูลของกิจการ\t%s\n", dialog_str, Biz_Data[id][bizInfo]);
    format(dialog_str, sizeof dialog_str, "%s ประเภทกิจการ\t%d\n", dialog_str, Biz_Data[id][bizType]);
    format(dialog_str, sizeof dialog_str, "%s เงินในกิจการ\t%d\n", dialog_str, Biz_Data[id][bizTotalMoney]);
    format(dialog_str, sizeof dialog_str, "%s ตั้งตำแหน่งทางเข้ากิจการมายังที่คุณอยู่\t\n", dialog_str);
    format(dialog_str, sizeof dialog_str, "%s ตั้งตำแหน่งทางออกกิจการมายังที่คุณอยู่\t\n", dialog_str);
	format(dialog_str, sizeof dialog_str, "%s ล็อค/ปลดล็อค กิจการ\t\n", dialog_str);
    format(dialog_str, sizeof dialog_str, "%s วางจุดขายของสำหรับกิจการ\t\n", dialog_str);
    format(dialog_str, sizeof dialog_str, "%s วาร์ปไปยังทางเข้ากิจการนี้\t", dialog_str);
	Dialog_ShowEasy(playerid, BizEdit, DIALOG_STYLE_TABLIST, caption, dialog_str, "แก้ไข", "กลับ");
	return 1;
}

Dialog:BizEdit(playerid, response, listitem, inputtext[]){
	if(response) {

		new caption[128];
        new id = GetPVarInt(playerid, "BizEditID");
		switch(listitem){
			case 0: // เจ้าของกิจการ
			{
				format(caption, sizeof(caption), "แก้ไข -> เจ้าของกิจการ: %s", Biz_Data[id][bizOwnerName]);
				Dialog_ShowEasy(playerid, BizEdit_Owner, DIALOG_STYLE_INPUT, caption, "กรุณากรอกไอดีผู้เล่นที่ต้องการจะให้เป็นเจ้าของ:", "ตกลง", "กลับ");
			}
			case 1: // ข้อมูลของกิจการ
			{
				format(caption, sizeof(caption), "แก้ไข -> ข้อมูลกิจการ: %s", Biz_Data[id][bizInfo]);
				Dialog_ShowEasy(playerid, BizEdit_Info, DIALOG_STYLE_INPUT, caption, "กรุณากรอกข้อมูลกิจการ:", "เปลี่ยน", "กลับ");
			}
            case 2:{
                format(caption, sizeof(caption), "แก้ไข -> ประเภทกิจการ: %s", Biz_Data[id][bizType]);
				Dialog_ShowEasy(playerid, BizEdit_Type, DIALOG_STYLE_INPUT, caption, "กรอกเลขประเภทกิจการ:", "เปลี่ยน", "กลับ");
                SystemMsg(playerid, "[Type]: 1.บาร์, 2.ร้านอาหาร");
            }
            case 3:{
                format(caption, sizeof(caption), "แก้ไข -> เงินในกิจการ: %s", Biz_Data[id][bizTotalMoney]);
				Dialog_ShowEasy(playerid, BizEdit_TotalMoney, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนเงินในกิจการใหม่:", "เปลี่ยน", "กลับ");
            }
			case 4:
			{
				format(caption, sizeof(caption), "แก้ไข -> แก้ไขทางเข้า");
				Dialog_ShowEasy(playerid, BizEdit_Enter, DIALOG_STYLE_MSGBOX, caption, "คุณแน่ใจหรือที่จะปรับ ทางเข้ากิจการ นี้มายังตำแหน่งปัจจุบันของคุณ", "ยืนยัน", "กลับ");
			}
			case 5:
			{
				format(caption, sizeof(caption), "แก้ไข -> แก้ไขทางออก");
				Dialog_ShowEasy(playerid, BizEdit_Exit, DIALOG_STYLE_MSGBOX, caption, "คุณแน่ใจหรือที่จะปรับ ทางออกกิจการ มายังตำแหน่งปัจจุบันของคุณ", "ยืนยัน", "กลับ");
			}
			case 6:{
				new string[128];
				if(!Biz_Data[id][bizLocked])
				{
					Biz_Data[id][bizLocked] = true;
					Biz_Save(id);
					format(string, sizeof(string), "%s ได้ล็อคทางเข้ากิจการไอดี: %d", ReturnRoleplayName(playerid), id);
					SendAdminsMessage(1, COLOR_GRAY, string);
				}
				else if(Biz_Data[id][bizLocked])
				{
					Biz_Data[id][bizLocked] = false;
					Biz_Save(id);
					format(string, sizeof(string), "%s ได้ปลดล็อคทางเข้ากิจการไอดี: %d", ReturnRoleplayName(playerid), id);
					SendAdminsMessage(1, COLOR_GRAY, string);
				}
			}
            case 7:{
                new string[128];
                new Float:px, Float:py, Float:pz, Float:pa, pint = GetPlayerInterior(playerid);
                GetPlayerPos(playerid, px, py, pz);
                GetPlayerFacingAngle(playerid, pa);

                format(string, sizeof(string), "%s ได้ปรับกิจการ 'จุดขายของกิจการ' [%d (SQLID: %d)] มายังตำแหน่งของเขาแล้ว", ReturnRoleplayName(playerid), id, Biz_Data[id][bizID]);
                SendAdminsMessage(1, COLOR_GRAY, string);

                Biz_Data[id][bizSelling][0]=px;
                Biz_Data[id][bizSelling][1]=py;
                Biz_Data[id][bizSelling][2]=pz;
                Biz_Data[id][bizSellingInt]=pint;
                Biz_Data[id][bizSellingWorld]= Biz_Data[id][bizID] + WORLD_BIZ;

                Biz_Refresh(id);
                Biz_Save(id);
            }
   			case 8:{
				SetPlayerPos(playerid, Biz_Data[id][bizPosEnter][0], Biz_Data[id][bizPosEnter][1], Biz_Data[id][bizPosEnter][2]);
				SetPlayerInterior(playerid, Biz_Data[id][bizIntEnter]);
				SetPlayerVirtualWorld(playerid, Biz_Data[id][bizWorldEnter]);
				SetPlayerFacingAngle(playerid, Biz_Data[id][bizPosEnter][3]);
				SendClientMessageEx(playerid, COLOR_GRAD1, "   คุณได้วาร์ปไปยังกิจการของ %s(%d) ", Biz_Data[id][bizOwnerName], id);
			}
		}
	}
	else{
	    DeletePVar(playerid, "BizEditID");
        ViewBizs(playerid);
	}
    return 1;
}

Dialog:BizEdit_Owner(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128], string[128];
		new id = GetPVarInt(playerid, "BizEditID");

		new userid = strval(inputtext);
        if(userid == INVALID_PLAYER_ID || !LoggedIn[userid]){
            format(caption, sizeof(caption), "แก้ไข -> เจ้าของกิจการ: %s", Biz_Data[id][bizOwnerName]);
            Dialog_ShowEasy(playerid, BizEdit_Owner, DIALOG_STYLE_INPUT, caption, "* ไอดีผู้เล่นดังกล่าวไม่ถูกต้อง * \nกรุณากรอกไอดีผู้เล่นที่ต้องการจะให้เป็นเจ้าของ:", "ตกลง", "กลับ");
            return 1;
        }
        format(string, sizeof(string), "%s ได้ปรับกิจการ 'เจ้าของกิจการ' [%d (SQLID: %d)] เป็น %s", ReturnRoleplayName(playerid), id, Biz_Data[id][bizID], ReturnRoleplayName(userid));
		SendAdminsMessage(1, COLOR_GRAY, string);
		format(Biz_Data[id][bizOwnerName], 64, ReturnRoleplayName(userid));
        Biz_Data[id][bizOwner] = PlayerData[userid][pID];
		Biz_RefreshPickup(id);
        Biz_Save(id);
    }
    return ShowPlayerEditBiz(playerid);
}

Dialog:BizEdit_Info(playerid, response, listitem, inputtext[]){
	if(response) {
		new caption[128], string[128];
		new id = GetPVarInt(playerid, "BizEditID");

		if(isnull(inputtext) || strlen(inputtext) >= 64) {
			format(caption, sizeof(caption), "แก้ไข -> ข้อมูลกิจการ: %s", EntranceData[id][entranceName]);
			Dialog_ShowEasy(playerid, BizEdit_Info, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nความยาวของชื่อต้องมากกว่า 0 และไม่เกิน 64 ตัวอักษร", "เปลี่ยน", "กลับ");
			return 1;
		}

		format(string, sizeof(string), "%s ได้ปรับกิจการ 'ข้อมูลกิจการ' [%d (SQLID: %d)] เป็น %s", ReturnRoleplayName(playerid), id, Biz_Data[id][bizID], inputtext);
		SendAdminsMessage(1, COLOR_GRAY, string);
		format(Biz_Data[id][bizInfo], 64, inputtext);
		Biz_Save(id);
	}
	return ShowPlayerEditBiz(playerid);
}

Dialog:BizEdit_Type(playerid, response, listitem, inputtext[]){
	if(response) {
		new caption[128], string[128];
		new id = GetPVarInt(playerid, "BizEditID");
        new typeid = strval(inputtext);

		if(typeid < 0 || typeid > MAX_TYPE_BIZS) {
			format(caption, sizeof(caption), "แก้ไข -> ประเภทกิจการ: %s", Biz_Data[id][bizType]);
			Dialog_ShowEasy(playerid, BizEdit_Type, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nกรอกเลขประเภทกิจการ:", "เปลี่ยน", "กลับ");
            SystemMsg(playerid, "[Type]: 1.บาร์, 2.ร้านอาหาร");
			return 1;
		}

		format(string, sizeof(string), "%s ได้ปรับกิจการ 'ประเภทกิจการ' [%d (SQLID: %d)] เป็น %s", ReturnRoleplayName(playerid), id, Biz_Data[id][bizID], typeid);
		SendAdminsMessage(1, COLOR_GRAY, string);
        Biz_Data[id][bizType] = typeid;
		Biz_Save(id);
	}
	return ShowPlayerEditBiz(playerid);
}

Dialog:BizEdit_TotalMoney(playerid, response, listitem, inputtext[]){
	if(response) {
		new string[128];
		new id = GetPVarInt(playerid, "BizEditID");
        new money = strval(inputtext);

		format(string, sizeof(string), "%s ได้ปรับกิจการ 'เงินกิจการ' [%d (SQLID: %d)] เป็น %s", ReturnRoleplayName(playerid), id, Biz_Data[id][bizID], FormatNumber(money));
		SendAdminsMessage(1, COLOR_GRAY, string);
        Biz_Data[id][bizTotalMoney] = money;
		Biz_Save(id);
	}
	return ShowPlayerEditBiz(playerid);
}


Dialog:BizEdit_Enter(playerid, response, listitem, inputtext[]){
	if (response){
        new string[128];
		new id = GetPVarInt(playerid, "BizEditID");
		new Float:px, Float:py, Float:pz, Float:pa, pint = GetPlayerInterior(playerid), pworld = GetPlayerVirtualWorld(playerid);
		GetPlayerPos(playerid, px, py, pz);
		GetPlayerFacingAngle(playerid, pa);

		format(string, sizeof(string), "%s ได้ปรับกิจการ 'ทางเข้า' [%d (SQLID: %d)] มายังตำแหน่งของเขาแล้ว", ReturnRoleplayName(playerid), id, Biz_Data[id][bizID]);
		SendAdminsMessage(1, COLOR_GRAY, string);

        Biz_Data[id][bizPosEnter][0]=px;
        Biz_Data[id][bizPosEnter][1]=py;
        Biz_Data[id][bizPosEnter][2]=pz;
		Biz_Data[id][bizPosEnter][3]=pa;
        Biz_Data[id][bizIntEnter]=pint;
        Biz_Data[id][bizWorldEnter]=pworld;

		Biz_RefreshCP(id);
        Biz_RefreshPickup(id);
        Biz_Save(id);
	}
	return ShowPlayerEditBiz(playerid);
}

Dialog:BizEdit_Exit(playerid, response, listitem, inputtext[]){
	if (response){
        new string[128];
		new id = GetPVarInt(playerid, "BizEditID");
		new Float:px, Float:py, Float:pz, Float:pa, pint = GetPlayerInterior(playerid);
		GetPlayerPos(playerid, px, py, pz);
		GetPlayerFacingAngle(playerid, pa);

		format(string, sizeof(string), "%s ได้ปรับกิจการ 'ทางออก' [%d (SQLID: %d)] มายังตำแหน่งของเขาแล้ว", ReturnRoleplayName(playerid), id, Biz_Data[id][bizID]);
		SendAdminsMessage(1, COLOR_GRAY, string);

        Biz_Data[id][bizPosExit][0]=px;
        Biz_Data[id][bizPosExit][1]=py;
        Biz_Data[id][bizPosExit][2]=pz;
		Biz_Data[id][bizPosExit][3]=pa;
        Biz_Data[id][bizIntExit]=pint;
        Biz_Data[id][bizWorldExit]= Biz_Data[id][bizID] + WORLD_BIZ;

		Biz_RefreshCP(id);
        Biz_RefreshPickup(id);
        Biz_Save(id);
	}
	return ShowPlayerEditBiz(playerid);
}

CMD:bizcmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1338)
        return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[BIZCMDS]: /makebiz, /viewbizs");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
    return 1;
}

CMD:viewbizs(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	ViewBizs(playerid);
    return 1;
}

CMD:makebiz(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new bizid, type, price = 0, info[64];
    if(sscanf(params, "dds[64]", type, price, info)) {
        SystemMsg(playerid, "/makebiz [type] [price] [info]");
        SystemMsg(playerid, "[Type]: 1.Bar, 2.Restaurant");
        return 1;
    }

    if(isnull(info)) return ErrorMsg(playerid, "คุณจะต้องกรอกข้อมูลของกิจการ");
    if(type < 0 || type > MAX_TYPE_BIZS) return ErrorMsg(playerid, "ตัวเลือกกิจการไม่ถูกต้อง");

    if((bizid = Iter_Free(Iter_Biz)) != -1){
        new Float:x, Float:y, Float:z, Float:a;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);

        Biz_Data[bizid][bizType] = type;
        Biz_Data[bizid][bizPrice] = price;

        Biz_Data[bizid][bizOwner] = 0;
        Biz_Data[bizid][bizPosEnter][0] = x;
        Biz_Data[bizid][bizPosEnter][1] = y;
        Biz_Data[bizid][bizPosEnter][2] = z;
        Biz_Data[bizid][bizPosEnter][3] = a;
        Biz_Data[bizid][bizIntEnter] = GetPlayerInterior(playerid);
        Biz_Data[bizid][bizWorldEnter] = GetPlayerVirtualWorld(playerid);
        Biz_Data[bizid][bizPosExit][0] = 0.0;
        Biz_Data[bizid][bizPosExit][1] = 0.0;
        Biz_Data[bizid][bizPosExit][2] = 0.0;
        Biz_Data[bizid][bizPosExit][3] = 0.0;
        Biz_Data[bizid][bizIntExit] = 0;
        Biz_Data[bizid][bizWorldExit] = 0;
        Biz_Data[bizid][bizLocked] = false;

        Biz_Data[bizid][bizTotalMoney] = 0;
        Biz_Data[bizid][bizEnterPrice] = 0;

        format(Biz_Data[bizid][bizOwnerName], 64, "NULL");
        format(Biz_Data[bizid][bizInfo], 64, info);

        format(Biz_Data[bizid][bizUrlMp3], 128, "NULL");

        if(IsValidDynamicCP(Biz_Data[bizid][bizAreaEnter]))
            DestroyDynamicCP(Biz_Data[bizid][bizAreaEnter]);

        if(IsValidDynamicPickup(Biz_Data[bizid][bizPickupEnter]))
            DestroyDynamicPickup(Biz_Data[bizid][bizPickupEnter]);

        Biz_Data[bizid][bizAreaEnter] = CreateDynamicCP(Biz_Data[bizid][bizPosEnter][0], Biz_Data[bizid][bizPosEnter][1], Biz_Data[bizid][bizPosEnter][2], 1.5, Biz_Data[bizid][bizWorldEnter], Biz_Data[bizid][bizIntEnter], -1, 5.0);
        Streamer_SetIntData(STREAMER_TYPE_CP, Biz_Data[bizid][bizAreaEnter], E_STREAMER_EXTRA_ID, bizid);
        Biz_Data[bizid][bizPickupEnter] = CreateDynamicPickup(Biz_Data[bizid][bizOwner] ? 19524 : 1272, 23, Biz_Data[bizid][bizPosEnter][0], Biz_Data[bizid][bizPosEnter][1], Biz_Data[bizid][bizPosEnter][2], Biz_Data[bizid][bizWorldEnter], Biz_Data[bizid][bizIntEnter]);

        new query[256];
        mysql_format(dbCon, query, sizeof query, "INSERT INTO `bizs` (`bizPrice`, `bizType`) VALUES(%d, %d)", price, type);
		mysql_tquery(dbCon, query, "OnBizCreated", "ii", playerid, bizid);
    }
    else SendClientMessageEx(playerid, -1, "[!] เกิดข้อผิดพลาด, เซิฟเวอร์ได้ทำการสร้างกิจการจนถึงขีดจำกัดแล้ว %d", MAX_BIZS);
    return 1;
}

forward OnBizCreated(playerid, bizid);
public OnBizCreated(playerid, bizid){
	new insert_id = cache_insert_id();
	if(insert_id) {
        new string[128];
		Iter_Add(Iter_Biz, bizid);
		Biz_Data[bizid][bizID] = insert_id;
		Biz_Save(bizid);
		format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการสร้างกิจการ %d (BizID: %d) เรียบร้อยแล้ว", ReturnRoleplayName(playerid), bizid, Biz_Data[bizid][bizID]);
        SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else {
		if(IsValidDynamicCP(Biz_Data[bizid][bizAreaEnter]))
			DestroyDynamicCP(Biz_Data[bizid][bizAreaEnter]);

		if(IsValidDynamicPickup(Biz_Data[bizid][bizPickupEnter]))
			DestroyDynamicPickup(Biz_Data[bizid][bizPickupEnter]);

		SendClientMessage(playerid, -1, "[!] ไม่สามารถสร้างกิจการได้โปรดติดต่อผู้ดูแลระบบ");
	}
	return 1;
}

forward Biz_Load();
public Biz_Load(){
    new rows;
    cache_get_row_count(rows);
    for (new i = 0; i < rows; i ++) if (i < MAX_BIZS){
        cache_get_value_name_int(i, "bizID", Biz_Data[i][bizID]);
        cache_get_value_name_int(i, "bizOwner", Biz_Data[i][bizOwner]);
        cache_get_value_name(i, "bizOwnerName", Biz_Data[i][bizOwnerName], 64);
        cache_get_value_name_int(i, "bizType", Biz_Data[i][bizType]);
        cache_get_value_name_int(i, "bizPrice", Biz_Data[i][bizPrice]);
        cache_get_value_name(i, "bizInfo", Biz_Data[i][bizInfo], 64);
        cache_get_value_name_float(i, "bizPosEnterX", Biz_Data[i][bizPosEnter][0]);
        cache_get_value_name_float(i, "bizPosEnterY", Biz_Data[i][bizPosEnter][1]);
        cache_get_value_name_float(i, "bizPosEnterZ", Biz_Data[i][bizPosEnter][2]);
        cache_get_value_name_float(i, "bizPosEnterA", Biz_Data[i][bizPosEnter][3]);
        cache_get_value_name_int(i, "bizIntEnter", Biz_Data[i][bizIntEnter]);
        cache_get_value_name_int(i, "bizWorldEnter", Biz_Data[i][bizWorldEnter]);
        cache_get_value_name_float(i, "bizPosExitX", Biz_Data[i][bizPosExit][0]);
        cache_get_value_name_float(i, "bizPosExitY", Biz_Data[i][bizPosExit][1]);
        cache_get_value_name_float(i, "bizPosExitZ", Biz_Data[i][bizPosExit][2]);
        cache_get_value_name_float(i, "bizPosExitA", Biz_Data[i][bizPosExit][3]);
        cache_get_value_name_int(i, "bizIntExit", Biz_Data[i][bizIntExit]);
        cache_get_value_name_int(i, "bizWorldExit", Biz_Data[i][bizWorldExit]);
        cache_get_value_name_int(i, "bizLocked", Biz_Data[i][bizLocked]);
        cache_get_value_name_int(i, "bizTotalMoney", Biz_Data[i][bizTotalMoney]);
        cache_get_value_name_int(i, "bizEnterPrice", Biz_Data[i][bizEnterPrice]);

        cache_get_value_name_float(i, "bizSellingX", Biz_Data[i][bizSelling][0]);
        cache_get_value_name_float(i, "bizSellingY", Biz_Data[i][bizSelling][1]);
        cache_get_value_name_float(i, "bizSellingZ", Biz_Data[i][bizSelling][2]);
        cache_get_value_name_int(i, "bizSellingInt", Biz_Data[i][bizSellingInt]);
        cache_get_value_name_int(i, "bizSellingWorld", Biz_Data[i][bizSellingWorld]);

        cache_get_value_name_int(i, "bizItems1", Biz_Data[i][bizItems][0]);
        cache_get_value_name_int(i, "bizItems2", Biz_Data[i][bizItems][1]);
        cache_get_value_name_int(i, "bizItems3", Biz_Data[i][bizItems][2]);
        cache_get_value_name_int(i, "bizItems4", Biz_Data[i][bizItems][3]);
        cache_get_value_name_int(i, "bizItems5", Biz_Data[i][bizItems][4]);

        cache_get_value_name_int(i, "bizItemsAmount1", Biz_Data[i][bizItemsAmount][0]);
        cache_get_value_name_int(i, "bizItemsAmount2", Biz_Data[i][bizItemsAmount][1]);
        cache_get_value_name_int(i, "bizItemsAmount3", Biz_Data[i][bizItemsAmount][2]);
        cache_get_value_name_int(i, "bizItemsAmount4", Biz_Data[i][bizItemsAmount][3]);
        cache_get_value_name_int(i, "bizItemsAmount5", Biz_Data[i][bizItemsAmount][4]);

        cache_get_value_name_int(i, "bizItemsPrice1", Biz_Data[i][bizItemsPrice][0]);
        cache_get_value_name_int(i, "bizItemsPrice2", Biz_Data[i][bizItemsPrice][1]);
        cache_get_value_name_int(i, "bizItemsPrice3", Biz_Data[i][bizItemsPrice][2]);
        cache_get_value_name_int(i, "bizItemsPrice4", Biz_Data[i][bizItemsPrice][3]);
        cache_get_value_name_int(i, "bizItemsPrice5", Biz_Data[i][bizItemsPrice][4]);

        Iter_Add(Iter_Biz, i);

        Biz_Data[i][bizAreaEnter] = CreateDynamicCP(Biz_Data[i][bizPosEnter][0], Biz_Data[i][bizPosEnter][1], Biz_Data[i][bizPosEnter][2], 1.5, Biz_Data[i][bizWorldEnter], Biz_Data[i][bizIntEnter], -1, 5.0);
        Streamer_SetIntData(STREAMER_TYPE_CP, Biz_Data[i][bizAreaEnter], E_STREAMER_EXTRA_ID, i);

        if(Biz_Data[i][bizPosExit][0] != 0.0 && Biz_Data[i][bizPosExit][1] != 0.0){
            Biz_Data[i][bizAreaExit] = CreateDynamicCP(Biz_Data[i][bizPosExit][0], Biz_Data[i][bizPosExit][1], Biz_Data[i][bizPosExit][2], 1.5, Biz_Data[i][bizWorldExit], Biz_Data[i][bizIntExit], -1, 5.0);
            Streamer_SetIntData(STREAMER_TYPE_CP, Biz_Data[i][bizAreaExit], E_STREAMER_EXTRA_ID, i);
        }

        Biz_Data[i][bizPickupEnter] = CreateDynamicPickup(Biz_Data[i][bizOwner] ? 19524 : 1272, 23, Biz_Data[i][bizPosEnter][0], Biz_Data[i][bizPosEnter][1], Biz_Data[i][bizPosEnter][2], Biz_Data[i][bizWorldEnter], Biz_Data[i][bizIntEnter]);

        if(Biz_Data[i][bizPosExit][0] != 0.0 && Biz_Data[i][bizPosExit][1] != 0.0){
            Biz_Data[i][bizPickupExit] = CreateDynamicPickup(Biz_Data[i][bizOwner] ? 19524 : 1272, 23, Biz_Data[i][bizPosExit][0], Biz_Data[i][bizPosExit][1], Biz_Data[i][bizPosExit][2], Biz_Data[i][bizWorldExit], Biz_Data[i][bizIntExit]);
        }

        new string[128];
        format(string, sizeof string, "[%s]\nจุดขายของกิจการ กด 'Y' เพื่อใช้งาน", Biz_Data[i][bizInfo]);
        Biz_Data[i][bizSellingText3D] = CreateDynamic3DTextLabel(string, 0xFF0000FF, Biz_Data[i][bizSelling][0], Biz_Data[i][bizSelling][1], Biz_Data[i][bizSelling][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Biz_Data[i][bizWorldExit], Biz_Data[i][bizIntExit]);

        format(Biz_Data[i][bizUrlMp3], 128, "NULL");
    }
    printf("(( [MYSQL]: Load %d Bizs Successfully ))", Iter_Count(Iter_Biz));
    return 1;
}

Biz_Refresh(bizid){
    if(bizid != -1 && Iter_Contains(Iter_Biz, bizid)){
        if(IsValidDynamic3DTextLabel(Biz_Data[bizid][bizSellingText3D]) && Biz_Data[bizid][bizSellingText3D]) DestroyDynamic3DTextLabel(Biz_Data[bizid][bizSellingText3D]);

        new string[128];
        format(string, sizeof string, "[%s]\nจุดขายของกิจการ กด 'Y' เพื่อใช้งาน", Biz_Data[bizid][bizInfo]);
        Biz_Data[bizid][bizSellingText3D] = CreateDynamic3DTextLabel(string, 0xFF0000FF, Biz_Data[bizid][bizSelling][0], Biz_Data[bizid][bizSelling][1], Biz_Data[bizid][bizSelling][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Biz_Data[bizid][bizWorldExit], Biz_Data[bizid][bizIntExit]);
    }
}

Biz_RefreshCP(bizid){
    if(Iter_Contains(Iter_Biz, bizid)){
        if(IsValidDynamicCP(Biz_Data[bizid][bizAreaEnter]))
            DestroyDynamicCP(Biz_Data[bizid][bizAreaEnter]);

        Biz_Data[bizid][bizAreaEnter] = CreateDynamicCP(Biz_Data[bizid][bizPosEnter][0], Biz_Data[bizid][bizPosEnter][1], Biz_Data[bizid][bizPosEnter][2], 1.5, Biz_Data[bizid][bizWorldEnter], Biz_Data[bizid][bizIntEnter], -1, 5.0);
    
        if(Biz_Data[bizid][bizPosExit][0] != 0.0 && Biz_Data[bizid][bizPosExit][1] != 0.0){
            if(IsValidDynamicCP(Biz_Data[bizid][bizAreaExit]))
                DestroyDynamicCP(Biz_Data[bizid][bizAreaExit]);

            Biz_Data[bizid][bizAreaExit] = CreateDynamicCP(Biz_Data[bizid][bizPosExit][0], Biz_Data[bizid][bizPosExit][1], Biz_Data[bizid][bizPosExit][2], 1.5, Biz_Data[bizid][bizWorldExit], Biz_Data[bizid][bizIntExit], -1, 5.0);
        }
    }
    return 1;
}

Biz_RefreshPickup(bizid){
    if(Iter_Contains(Iter_Biz, bizid)){
        if(IsValidDynamicPickup(Biz_Data[bizid][bizPickupEnter]))
            DestroyDynamicPickup(Biz_Data[bizid][bizPickupEnter]);

        Biz_Data[bizid][bizPickupEnter] = CreateDynamicPickup(Biz_Data[bizid][bizOwner] ? 19524 : 1272, 23, Biz_Data[bizid][bizPosEnter][0], Biz_Data[bizid][bizPosEnter][1], Biz_Data[bizid][bizPosEnter][2], Biz_Data[bizid][bizWorldEnter], Biz_Data[bizid][bizIntEnter]);
    
        if(Biz_Data[bizid][bizPosExit][0] != 0.0 && Biz_Data[bizid][bizPosExit][1] != 0.0){
            if(IsValidDynamicPickup(Biz_Data[bizid][bizPickupExit]))
                DestroyDynamicPickup(Biz_Data[bizid][bizPickupExit]);
            
            Biz_Data[bizid][bizPickupExit] = CreateDynamicPickup(Biz_Data[bizid][bizOwner] ? 19524 : 1272, 23, Biz_Data[bizid][bizPosExit][0], Biz_Data[bizid][bizPosExit][1], Biz_Data[bizid][bizPosExit][2], Biz_Data[bizid][bizWorldExit], Biz_Data[bizid][bizIntExit]);
        }
    }
    return 1;
}

Biz_Save(bizid){
    if(Iter_Contains(Iter_Biz, bizid)){
        new
            query[1024];

        format(query, sizeof(query), "UPDATE `bizs` SET `bizPosEnterX` = '%.4f', `bizPosEnterY` = '%.4f', `bizPosEnterZ` = '%.4f', `bizPosEnterA` = '%.4f', `bizIntEnter` = '%d', `bizWorldEnter` = '%d'",
            Biz_Data[bizid][bizPosEnter][0],
            Biz_Data[bizid][bizPosEnter][1],
            Biz_Data[bizid][bizPosEnter][2],
            Biz_Data[bizid][bizPosEnter][3],
            Biz_Data[bizid][bizIntEnter],
            Biz_Data[bizid][bizWorldEnter]
        );

        format(query, sizeof(query), "%s, `bizPosExitX` = '%.4f', `bizPosExitY` = '%.4f', `bizPosExitZ` = '%.4f', `bizPosExitA` = '%.4f', `bizIntExit` = '%d', `bizWorldExit` = '%d'",
            query,
            Biz_Data[bizid][bizPosExit][0],
            Biz_Data[bizid][bizPosExit][1],
            Biz_Data[bizid][bizPosExit][2],
            Biz_Data[bizid][bizPosExit][3],
            Biz_Data[bizid][bizIntExit],
            Biz_Data[bizid][bizWorldExit]
        );

        mysql_format(dbCon, query, sizeof(query), "%s, `bizOwner` = '%d', `bizOwnerName` = '%e', `bizPrice` = '%d', `bizType` = '%d', `bizInfo` = '%e', `bizLocked` = '%d', `bizTotalMoney` = '%d', `bizEnterPrice` = '%d'",
            query,
            Biz_Data[bizid][bizOwner],
            Biz_Data[bizid][bizOwnerName],
            Biz_Data[bizid][bizPrice],
            Biz_Data[bizid][bizType],
            Biz_Data[bizid][bizInfo],
            Biz_Data[bizid][bizLocked],
            Biz_Data[bizid][bizTotalMoney],
            Biz_Data[bizid][bizEnterPrice]
        );

        format(query, sizeof(query), "%s, `bizSellingX` = '%.4f', `bizSellingY` = '%.4f', `bizSellingZ` = '%.4f', `bizSellingInt` = '%d', `bizSellingWorld` = '%d'",
            query,
            Biz_Data[bizid][bizSelling][0],
            Biz_Data[bizid][bizSelling][1],
            Biz_Data[bizid][bizSelling][2],
            Biz_Data[bizid][bizSellingInt],
            Biz_Data[bizid][bizSellingWorld]
        );

        format(query, sizeof(query), "%s, `bizItems1` = '%d', `bizItems2` = '%d', `bizItems3` = '%d', `bizItems4` = '%d', `bizItems5` = '%d', `bizItemsAmount1` = '%d', `bizItemsAmount2` = '%d', `bizItemsAmount3` = '%d', `bizItemsAmount4` = '%d', `bizItemsAmount5` = '%d'",
            query,
            Biz_Data[bizid][bizItems][0],
            Biz_Data[bizid][bizItems][1],
            Biz_Data[bizid][bizItems][2],
            Biz_Data[bizid][bizItems][3],
            Biz_Data[bizid][bizItems][4],
            Biz_Data[bizid][bizItemsAmount][0],
            Biz_Data[bizid][bizItemsAmount][1],
            Biz_Data[bizid][bizItemsAmount][2],
            Biz_Data[bizid][bizItemsAmount][3],
            Biz_Data[bizid][bizItemsAmount][4]
        );

        format(query, sizeof(query), "%s, `bizItemsPrice1` = '%d', `bizItemsPrice2` = '%d', `bizItemsPrice3` = '%d', `bizItemsPrice4` = '%d', `bizItemsPrice5` = '%d' WHERE `bizID` = %d",
            query,
            Biz_Data[bizid][bizItemsPrice][0],
            Biz_Data[bizid][bizItemsPrice][1],
            Biz_Data[bizid][bizItemsPrice][2],
            Biz_Data[bizid][bizItemsPrice][3],
            Biz_Data[bizid][bizItemsPrice][4],
            Biz_Data[bizid][bizID]
        );
        return mysql_tquery(dbCon, query);
    }
    return 1;
}