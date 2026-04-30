#if defined _inc_impl
	#undef _inc_impl
#endif

ResetPlayerTradeItem(playerid){
    PlayerTradingItem[playerid] = false;
    PlayerTradingTargetID[playerid] = INVALID_PLAYER_ID;
    PlayerStateRoleTrade[playerid] = 0;
    PlayerStateTrading[playerid] = false;
    PlayerTradeMoney[playerid] = 0;
    PlayerSelectingItem[playerid] = false;
    PlayerConfirmTrade[playerid] = false;

    for(new i=0; i<10; i++){
        Trade_Item[playerid][i][itemID] = -1;
        format(Trade_Item[playerid][i][itemName], 64, "NULL");
        Trade_Item[playerid][i][itemModel] = MODEL_NULL;
        Trade_Item[playerid][i][itemQuantity] = 0;
        Trade_Item[playerid][i][itemLevel] = 0;
        Trade_Item[playerid][i][itemAmmo] = 0;
    }
    return 1;
}

timer ReloadTradeItem[200](playerid){
    PlayerSelectingItem[playerid] = false;
    SelectTextDraw(playerid, PlayerInventoryHoverCodeColor[playerid]);
    PlayerInventoryType[playerid] = INVENTORY_TYPE;
    if(PlayerStateRoleTrade[playerid] == 1)  PlayerTradeItem_UpdateRender1(playerid);
    else if(PlayerStateRoleTrade[playerid] == 2) PlayerTradeItem_UpdateRender2(playerid);
}

CheckPlayerCanTradeZone(playerid){
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    if(x > 1074 && x < 1182 && y > -1519.5 && y < -1416.5) return 1;
    else if(x > -2276 && x < -2233 && y > 518.5 && y < 555.5) return 1;
    else return -1;
}

Dialog:InputIDTrade(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new userid;
        if(CheckPlayerCanTradeZone(playerid) == -1) return ErrorMsg(playerid, "คุณไม่ได้อยู่ในพื้นที่สำหรับเทรดของ");
		if (sscanf(inputtext, "u", userid)) return Dialog_ShowEasy(playerid, InputIDTrade, DIALOG_STYLE_INPUT, "กรอกไอดีผู้เล่นที่ต้องการ", "กรอกไอดีหรือชื่อผู้เล่นที่ต้องการจะแลกเปลี่ยนด้วย: ", "ตกลง", "ยกเลิก");
        if(userid == playerid) return Dialog_ShowEasy(playerid, InputIDTrade, DIALOG_STYLE_INPUT, "กรอกไอดีผู้เล่นที่ต้องการ", "คุณไม่สามารถยื่นข้อเสนอให้ตัวเองได้!\nกรอกไอดีหรือชื่อผู้เล่นที่ต้องการจะแลกเปลี่ยนด้วย: ", "ตกลง", "ยกเลิก");
        if(userid == INVALID_PLAYER_ID) return Dialog_ShowEasy(playerid, InputIDTrade, DIALOG_STYLE_INPUT, "กรอกไอดีผู้เล่นที่ต้องการ", "ไอดีผู้เล่นไม่ถูกต้อง!\nกรอกไอดีหรือชื่อผู้เล่นที่ต้องการจะแลกเปลี่ยนด้วย: ", "ตกลง", "ยกเลิก");
        if(!LoggedIn[userid]) return Dialog_ShowEasy(playerid, InputIDTrade, DIALOG_STYLE_INPUT, "กรอกไอดีผู้เล่นที่ต้องการ", "ผู้เล่นนั้นยังไม่ได้ทำการเข้าสู่ระบบ!\nกรอกไอดีหรือชื่อผู้เล่นที่ต้องการจะแลกเปลี่ยนด้วย: ", "ตกลง", "ยกเลิก");
        if(!IsPlayerNearPlayer(playerid, userid, 5.0)) return Dialog_ShowEasy(playerid, InputIDTrade, DIALOG_STYLE_INPUT, "กรอกไอดีผู้เล่นที่ต้องการ", "คุณไม่ได้อยู่ใกล้ผู้เล่นดังกล่าว!\nกรอกไอดีหรือชื่อผู้เล่นที่ต้องการจะแลกเปลี่ยนด้วย: ", "ตกลง", "ยกเลิก");
        if(CheckPlayerCanTradeZone(userid) == -1) return ErrorMsg(playerid, "ผู้เล่นนั้นไม่ได้อยู่ในโซนสำหรับการเทรด");
        if(PlayerData[userid][pPlayerhour] < 5) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_INPUT, "เกิดข้อผิดพลาด", "ผู้เล่นดังกล่าวมีชั่วโมงออนไลน์ไม่ถึง 5 ชม. ไม่สามารถเทรดได้!", "ตกลง", "ยกเลิก");
        if(CheckPlayerNotOpenInv(userid) != -1) return ErrorMsg(playerid, "ไม่สามารถใช้งานระบบเทรดกับผู้เล่นดังกล่าวได้ในขณะนี้");
        if(PlayerTradingTargetID[userid] != INVALID_PLAYER_ID) return 1;

        new string[128];
        SetPVarInt(playerid, "TradeID", userid);
        format(string, sizeof string, "คุณได้เสนอการแลกเปลี่ยนไปยัง %s(%d) เรียบร้อยแล้ว", ReturnRoleplayName(userid), userid);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ยื่นขอการแลกเปลี่ยน", string, "ตกลง", "");

        SetPVarInt(userid, "TradeID", playerid);
        format(string, sizeof string, "ผู้เล่น %s(%d) ได้เสนอการแลกเปลี่ยนกับคุณ", ReturnRoleplayName(playerid), playerid);
        Dialog_ShowEasy(userid, RequestTradeItem, DIALOG_STYLE_MSGBOX, "การแลกเปลี่ยนไอเท็ม", string, "ตกลง", "ปฏิเสธ");
    }
    return 1;
}

Dialog:RequestTradeItem(playerid, response, listitem, inputtext[]){
    if(!response){
        new tradeid = GetPVarInt(playerid, "TradeID");
        new string[128];
        format(string, sizeof string, "ผู้เล่น %s(%d) ได้ปฏิเสธการเสนอแลกเปลี่ยนของคุณ", ReturnRoleplayName(playerid), playerid);
        Dialog_ShowEasy(tradeid, ShowOnly, DIALOG_STYLE_MSGBOX, "ยื่นขอการแลกเปลี่ยน", string, "ตกลง", "");

        format(string, sizeof string, "คุณได้ปฏิเสธข้อเสนอการแลกเปลี่ยนของ %s(%d) เรียบร้อยแล้ว", ReturnRoleplayName(tradeid), tradeid);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ยื่นขอการแลกเปลี่ยน", string, "ตกลง", "");

        DeletePVar(tradeid, "TradeID");
        DeletePVar(playerid, "TradeID");
    }
    if(response){

        if(CheckPlayerCanTradeZone(playerid) == -1) return ErrorMsg(playerid, "คุณไม่สามารถเทรดได้ในบริเวณนี้");
        new tradeid = GetPVarInt(playerid, "TradeID");

        if(CheckPlayerNotOpenInv(playerid) != -1){
            DeletePVar(tradeid, "TradeID");
            DeletePVar(playerid, "TradeID");
            return ErrorMsg(playerid, "คุณไม่สามารถตอบรับคำเทรดได้ในตอนนี้");
        }

        PlayerStateRoleTrade[playerid] = 1;
        PlayerStateRoleTrade[tradeid] = 2;

        if(PlayerInventoryStatus[playerid]) OnPlayerInventory_Close(playerid);
        if(PlayerInventoryStatus[tradeid]) OnPlayerInventory_Close(tradeid);

        PlayerTradeItem_Show(playerid);
        PlayerTradeItem_Show(tradeid);
        PlayerTradeItem_UpdateRender1(playerid);
        PlayerTradeItem_UpdateRender2(tradeid);
    }
    return 1;
}

PlayerTradeItem_Show(playerid){
    LoadPlayerTDTradeItem_TradeItem(playerid);
    for(new i=0; i<74; i++){
        PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][i]);
    }
    PlayerTradingItem[playerid] = true;
    SelectTextDraw(playerid, 0x2BD900FF);
    return 1;
}

PlayerTradeItem_Hide(playerid){
    for(new i=0; i<74; i++){
        PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][i]);
        PlayerTextDrawDestroy(playerid, PlayerTDTradeItem[playerid][i]);
    }
    ResetPlayerTradeItem(playerid);
    CancelSelectTextDraw(playerid);
    return 1;
}

Dialog:AddMoneyTrade(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0) return Dialog_ShowEasy(playerid, AddMoneyTrade, DIALOG_STYLE_INPUT, "การแลกเปลี่ยนเงิน", "คุณต้องกรอกเงินมากกว่า 0 !\nใส่จำนวนเงินที่คุณต้องการจะแลกเปลี่ยน:", "ตกลง", "ยกเลิก");
        if(amount > GetMoney(playerid)) return Dialog_ShowEasy(playerid, AddMoneyTrade, DIALOG_STYLE_INPUT, "การแลกเปลี่ยนเงิน", "เงินของคุณมีไม่พอ!\nใส่จำนวนเงินที่คุณต้องการจะแลกเปลี่ยน:", "ตกลง", "ยกเลิก");
        if(amount > 1000000) return Dialog_ShowEasy(playerid, AddMoneyTrade, DIALOG_STYLE_INPUT, "การแลกเปลี่ยนเงิน", "คุณสามารถเทรดได้รอบละไม่เกิน 1 ล้านเท่านั้น!\nใส่จำนวนเงินที่คุณต้องการจะแลกเปลี่ยน:", "ตกลง", "ยกเลิก");
        new string[128];
        PlayerTradeMoney[playerid] = amount;
        format(string, sizeof string, "คุณลงแลกเปลี่ยนเงินเป็นจำนวนเงิน %s เรียบร้อยแล้ว", FormatNumber(PlayerTradeMoney[playerid]));
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ลงแลกเปลี่ยนเงิน", string, "ตกลง", "");
        new tradeid = GetPVarInt(playerid, "TradeID");
        if(tradeid != INVALID_PLAYER_ID && LoggedIn[tradeid]){
            if(PlayerStateRoleTrade[playerid] == 1){
                format(string, sizeof string, "%s", FormatNumber(PlayerTradeMoney[playerid]));
                PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][33], string);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][33], string);

                format(string, sizeof string, "%s", FormatNumber(PlayerTradeMoney[tradeid]));
                PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][65], string);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][65], string);
            }
            else if(PlayerStateRoleTrade[playerid] == 2){
                format(string, sizeof string, "%s", FormatNumber(PlayerTradeMoney[playerid]));
                PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][65], string);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][65], string);

                format(string, sizeof string, "%s", FormatNumber(PlayerTradeMoney[tradeid]));
                PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][33], string);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][33], string);
            }
        }
    }
    return 1;
}

Dialog:InputCountTradeItem(playerid, response, listitem, inputtext[]){
    if(!response){
        DeletePVar(playerid, "TempTradeItemID");
        PlayerSelectingItem[playerid] = false;
        return 1;
    }
    if(response){
        new amount = strval(inputtext);
        new string[128], itemid = GetPVarInt(playerid, "TempTradeItemID");
        if(itemid != -1){
            if(amount <= 0) {
                format(string, sizeof string, "ไอเท็ม %s (จำนวน: %d)\nกรอกจำนวนไอเท็มที่คุณต้องการจะเพิ่มเข้าการแลกเปลี่ยน:", Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity]);
                Dialog_ShowEasy(playerid, InputCountTradeItem, DIALOG_STYLE_INPUT, "แลกเปลี่ยนไอเท็ม", string, "ตกลง", "ปิด");
                return 1;
            }

            if(amount > 50){
                format(string, sizeof string, "จำนวนไอเท็มต่อชิ้นต้องไม่เกิน 50!\nไอเท็ม %s (จำนวน: %d)\nกรอกจำนวนไอเท็มที่คุณต้องการจะเพิ่มเข้าการแลกเปลี่ยน:", Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity]);
                Dialog_ShowEasy(playerid, InputCountTradeItem, DIALOG_STYLE_INPUT, "แลกเปลี่ยนไอเท็ม", string, "ตกลง", "ปิด");
                return 1;
            }

            if(amount > Inventory_Player[playerid][itemid][itemQuantity]) {
                format(string, sizeof string, "คุณมีจำนวนไอเท็มไม่เพียงพอ!!\nไอเท็ม %s (จำนวน: %d)\nกรอกจำนวนไอเท็มที่คุณต้องการจะเพิ่มเข้าการแลกเปลี่ยน:", Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemQuantity]);
                Dialog_ShowEasy(playerid, InputCountTradeItem, DIALOG_STYLE_INPUT, "แลกเปลี่ยนไอเท็ม", string, "ตกลง", "ปิด");
                return 1;
            }
            PlayerTradeItem_AddItem(playerid, Inventory_Player[playerid][itemid][itemName], Inventory_Player[playerid][itemid][itemKey], amount, Inventory_Player[playerid][itemid][itemAmmo], Inventory_Player[playerid][itemid][itemLevel], itemid);
        }
        else return ErrorMsg(playerid, "เกิดข้อผิดพลาด");   
    }
    return 1;
}

PlayerTradeItem_ViewItem(playerid, slotitem){
    new tradeid = GetPVarInt(playerid, "TradeID");
    if(tradeid != INVALID_PLAYER_ID){
        new string[128];
        format(string, sizeof string, "ชื่อไอเท็ม: %s\nจำนวน: %d ชิ้น\nเลเวลไอเท็ม: %d", Trade_Item[tradeid][slotitem][itemName], Trade_Item[tradeid][slotitem][itemQuantity], Trade_Item[tradeid][slotitem][itemLevel]);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ข้อมูลไอเท็ม", string, "ตกลง", "");
    }
    return 1;
}

PlayerTradeItem_MenuManageItem(playerid, slotitem){
    if(slotitem != -1){
        new caption[128];
        SetPVarInt(playerid, "tempSlotitem", slotitem);
        format(caption, sizeof caption, "ไอเท็ม: %s (จำนวน: %d)", Trade_Item[playerid][slotitem][itemName], Trade_Item[playerid][slotitem][itemQuantity]);
        Dialog_ShowEasy(playerid, MenuManageTradeItem, DIALOG_STYLE_LIST, caption, "ดูข้อมูลไอเท็ม\nนำออก", "เลือก", "ปิด");
    }
    return 1;
}

Dialog:MenuManageTradeItem(playerid, response, listitem, inputtext[]){
    if(!response){
        return DeletePVar(playerid, "tempSlotitem");
    }
    if(response){
        new slotitem = GetPVarInt(playerid, "tempSlotitem");
        new string[128];
        if(slotitem != -1){
            if(listitem == 0){
                format(string, sizeof string, "ชื่อไอเท็ม: %s\nจำนวน: %d ชิ้น\nเลเวลไอเท็ม: %d", Trade_Item[playerid][slotitem][itemName], Trade_Item[playerid][slotitem][itemQuantity], Trade_Item[playerid][slotitem][itemLevel]);
                Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ข้อมูลไอเท็ม", string, "ตกลง", "");
            }
            if(listitem == 1){

                if(PlayerStateTrading[playerid]){
                    DeletePVar(playerid, "tempSlotitem");
                    return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "คุณจะต้อง 'UNLOCK' ก่อนที่จะแก้ไขไอเท็ม", "ตกลง", "");
                } 

                format(string, sizeof string, "คุณได้นำไอเท็ม '%s' ออกจากการแลกเปลี่ยนเรียบร้อยแล้ว", Trade_Item[playerid][slotitem][itemName]);
                Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "นำไอเท็มออกสำเร็จ", string, "ตกลง", "");

                Trade_Item[playerid][slotitem][itemID] = -1;
                format(Trade_Item[playerid][slotitem][itemName], 64, "NULL");
                Trade_Item[playerid][slotitem][itemModel] = MODEL_NULL;
                Trade_Item[playerid][slotitem][itemQuantity] = 0;
                Trade_Item[playerid][slotitem][itemLevel] = 0;
                Trade_Item[playerid][slotitem][itemAmmo] = 0;

                if(PlayerStateRoleTrade[playerid] == 1) PlayerTradeItem_UpdateRender1(playerid);
                else if(PlayerStateRoleTrade[playerid] == 2) PlayerTradeItem_UpdateRender2(playerid);
            }
        }
    }
    return 1;
}

PlayerTradeItem_ShowInfoTrader(playerid){
    new tradeid = GetPVarInt(playerid, "TradeID");
    if(tradeid != INVALID_PLAYER_ID){
        new string[256];
        format(string, sizeof string, "[ข้อมูล คู่แลกเปลี่ยน]\
        \nชื่อ: %s (ID: %d)\
        \nชั่วโมงออนไลน์: %s\
        \nเลเวลตัวละคร: %d\
        \nเบอร์โทรศัพท์: %d", ReturnRoleplayName(tradeid), tradeid, FormatNumberNotMoney(PlayerData[tradeid][pPlayerhour]), PlayerData[tradeid][pLevel], PlayerData[tradeid][pNumberPhone]);
        Dialog_ShowEasy(playerid, ShowInfoOnly, DIALOG_STYLE_MSGBOX, "ข้อมูลการแลกเปลี่ยน", string, "ตกลง", "");
    }   
    return 1;
}

PlayerTradeItem_AddItem(playerid, const item[], model, quantity = 1, ammo = 0, level = 0, itemid){
    if(itemid != -1){
        new bool:checked = false;
        for(new i=0; i<10; i++){
            if(Trade_Item[playerid][i][itemModel] != MODEL_NULL) continue;
            Trade_Item[playerid][i][itemID] = itemid;
            format(Trade_Item[playerid][i][itemName], 64, item);
            Trade_Item[playerid][i][itemModel] = model;
            Trade_Item[playerid][i][itemQuantity] = quantity;
            Trade_Item[playerid][i][itemLevel] = level;
            Trade_Item[playerid][i][itemAmmo] = ammo;
            checked = true;
            break;
        }
        if(!checked) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "ช่องเทรดไอเท็มของคุณเต็มแล้ว", "ตกลง", "");

        OnPlayerInventory_Close(playerid);
        SelectTextDraw(playerid, PlayerInventoryHoverCodeColor[playerid]);
        PlayerSelectingItem[playerid] = false;
        if(PlayerStateRoleTrade[playerid] == 1) {
            PlayerTradeItem_UpdateRender1(playerid);
        }
        else if(PlayerStateRoleTrade[playerid] == 2) {
            PlayerTradeItem_UpdateRender2(playerid);
        }
    }
    return 1;
}

PlayerTradeItem_UpdateState(playerid){
    new tradeid = GetPVarInt(playerid, "TradeID");
    if(tradeid != INVALID_PLAYER_ID && LoggedIn[tradeid]){
        new string[128];
        if(PlayerStateRoleTrade[playerid] == 1){
            if(!PlayerStateTrading[playerid]) format(string, sizeof string, "STATUS: UNLOCK");
            else format(string, sizeof string, "STATUS: LOCK");
            if(!PlayerSelectingItem[playerid]) PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][70], string);
            if(!PlayerSelectingItem[tradeid]) PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][70], string);
        }
        else if(PlayerStateRoleTrade[playerid] == 2){
            if(!PlayerStateTrading[playerid]) format(string, sizeof string, "STATUS: UNLOCK");
            else format(string, sizeof string, "STATUS: LOCK");
            if(!PlayerSelectingItem[playerid]) PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][71], string);
            if(!PlayerSelectingItem[tradeid]) PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][71], string);
        }
    }
    return 1;
}

PlayerConfirmTradeItem(playerid){
    new tradeid = GetPVarInt(playerid, "TradeID");
    if(tradeid != INVALID_PLAYER_ID && LoggedIn[tradeid]){
        PlayerConfirmTrade[playerid] = true;
        if(PlayerConfirmTrade[tradeid]){
            //เสร็จสิ้น
            new playeritemcount[10] = -1;
            new tradeitemcount[10] = -1;
            new string[128];

            for(new i=0; i<10; i++){
                if(Trade_Item[playerid][i][itemModel] != MODEL_NULL){
                    tradeitemcount[i] = PlayerInventory_AddItem(tradeid, Trade_Item[playerid][i][itemName], Trade_Item[playerid][i][itemModel], Trade_Item[playerid][i][itemQuantity], Trade_Item[playerid][i][itemAmmo], Trade_Item[playerid][i][itemLevel]);
                    if(tradeitemcount[i] == -1){
                        format(string, sizeof string, "[!] กระเป๋าของฝ่ายตรงข้ามไม่เพียงพอสำหรับเก็บไอเท็ม '%s'", Trade_Item[playerid][i][itemName]);
                        SendClientMessage(playerid, COLOR_RED, string);

                        format(string, sizeof string, "[!] คุณมีพื้นที่ไม่พอที่จะเก็บไอเท็ม '%s'", Trade_Item[playerid][i][itemName]);
                        SendClientMessage(tradeid, COLOR_RED, string);
                        continue;
                    }
                    else{
                        if(CheckItemIsWeapon(Trade_Item[playerid][i][itemName]) != -1) SendClientMessageEx(tradeid, COLOR_YELLOW, "- คุณได้รับ %s (จำนวน: %d ชิ้น | Level: %d) จากการแลกเปลี่ยน", Trade_Item[playerid][i][itemName], Trade_Item[playerid][i][itemQuantity], Trade_Item[playerid][i][itemLevel]);
                        else SendClientMessageEx(tradeid, COLOR_YELLOW, "- คุณได้รับ %s (จำนวน: %d ชิ้น) จากการแลกเปลี่ยน", Trade_Item[playerid][i][itemName], Trade_Item[playerid][i][itemQuantity]);
                        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เสีย %s (จำนวน: %d ชิ้น) จากการแลกเปลี่ยน", Trade_Item[playerid][i][itemName], Trade_Item[playerid][i][itemQuantity]);
                        Log_Write("logs/tradeitem.txt", "[%s] %s Get Item (%s) amount: (%d) Level: (%d) From %s", ReturnDate(), ReturnRoleplayName(tradeid), Trade_Item[playerid][i][itemName], Trade_Item[playerid][i][itemQuantity], Trade_Item[playerid][i][itemLevel], ReturnRoleplayName(playerid));
                        Log_Write("logs/tradeitem.txt", "[%s] %s Trade Item (%s) amount: (%d) Level: (%d) To %s", ReturnDate(), ReturnRoleplayName(playerid), Trade_Item[playerid][i][itemName], Trade_Item[playerid][i][itemQuantity], Trade_Item[playerid][i][itemLevel], ReturnRoleplayName(tradeid));
                        PlayerInventory_RemoveEx(playerid, Trade_Item[playerid][i][itemID], Trade_Item[playerid][i][itemQuantity]);
                    }
                }

                if(Trade_Item[tradeid][i][itemModel] != MODEL_NULL){
                    playeritemcount[i] = PlayerInventory_AddItem(playerid, Trade_Item[tradeid][i][itemName], Trade_Item[tradeid][i][itemModel], Trade_Item[tradeid][i][itemQuantity], Trade_Item[tradeid][i][itemAmmo], Trade_Item[tradeid][i][itemLevel]);
                    if(playeritemcount[i] == -1){
                        format(string, sizeof string, "[!] กระเป๋าของฝ่ายตรงข้ามไม่เพียงพอสำหรับเก็บไอเท็ม '%s'", Trade_Item[tradeid][i][itemName]);
                        SendClientMessage(tradeid, COLOR_RED, string);

                        format(string, sizeof string, "[!] คุณมีพื้นที่ไม่พอที่จะเก็บไอเท็ม '%s'", Trade_Item[tradeid][i][itemName]);
                        SendClientMessage(playerid, COLOR_RED, string);
                        continue;
                    }
                    else{
                        if(CheckItemIsWeapon(Trade_Item[tradeid][i][itemName]) != -1) SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้รับ %s (จำนวน: %d ชิ้น | Level: %d) จากการแลกเปลี่ยน", Trade_Item[tradeid][i][itemName], Trade_Item[tradeid][i][itemQuantity], Trade_Item[tradeid][i][itemLevel]);
                        else SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้รับ %s (จำนวน: %d ชิ้น) จากการแลกเปลี่ยน", Trade_Item[tradeid][i][itemName], Trade_Item[tradeid][i][itemQuantity]);
                        SendClientMessageEx(tradeid, COLOR_YELLOW, "- คุณได้เสีย %s (จำนวน: %d ชิ้น) จากการแลกเปลี่ยน", Trade_Item[tradeid][i][itemName], Trade_Item[tradeid][i][itemQuantity]);
                        Log_Write("logs/tradeitem.txt", "[%s] %s Get Item (%s) amount: (%d) Level: (%d) From %s", ReturnDate(), ReturnRoleplayName(playerid), Trade_Item[tradeid][i][itemName], Trade_Item[tradeid][i][itemQuantity], Trade_Item[tradeid][i][itemLevel], ReturnRoleplayName(tradeid));
                        Log_Write("logs/tradeitem.txt", "[%s] %s Trade Item (%s) amount: (%d) Level: (%d) To %s", ReturnDate(), ReturnRoleplayName(tradeid), Trade_Item[tradeid][i][itemName], Trade_Item[tradeid][i][itemQuantity], Trade_Item[tradeid][i][itemLevel], ReturnRoleplayName(playerid));
                        PlayerInventory_RemoveEx(tradeid, Trade_Item[tradeid][i][itemID], Trade_Item[tradeid][i][itemQuantity]);
                    } 
                }
            }

            if(PlayerTradeMoney[playerid] != 0 && PlayerTradeMoney[playerid] <= 1000000){
                GiveMoney(tradeid, PlayerTradeMoney[playerid], "From Trade");
                GiveMoney(playerid, -PlayerTradeMoney[playerid], "From Trade");
                SendClientMessageEx(playerid, COLOR_RED, "[!] คุณได้เสียเงินจำนวน %s จากการแลกเปลี่ยน", FormatNumber(PlayerTradeMoney[playerid]));
                SendClientMessageEx(tradeid, COLOR_ORANGE, "[!] คุณได้รับเงินจำนวน %s จากการแลกเปลี่ยน", FormatNumber(PlayerTradeMoney[playerid]));
            }

            if(PlayerTradeMoney[tradeid] != 0 && PlayerTradeMoney[tradeid] <= 1000000){
                GiveMoney(playerid, PlayerTradeMoney[tradeid], "From Trade");
                GiveMoney(tradeid, -PlayerTradeMoney[tradeid], "From Trade");
                SendClientMessageEx(tradeid, COLOR_RED, "[!] คุณได้เสียเงินจำนวน %s จากการแลกเปลี่ยน", FormatNumber(PlayerTradeMoney[tradeid]));
                SendClientMessageEx(playerid, COLOR_ORANGE, "[!] คุณได้รับเงินจำนวน %s จากการแลกเปลี่ยน", FormatNumber(PlayerTradeMoney[tradeid]));
            }

            SendClientMessage(playerid, COLOR_YELLOW, "[!] การแลกเปลี่ยนสำเร็จ");
            SendClientMessage(tradeid, COLOR_YELLOW, "[!] การแลกเปลี่ยนสำเร็จ");

            DeletePVar(tradeid, "TradeID");
            PlayerTradeItem_Hide(tradeid);
            DeletePVar(playerid, "TradeID");
            PlayerTradeItem_Hide(playerid);
        }
    }
    return 1;
}

PlayerTradeItem_UpdateRender1(playerid){
    new tradeid = GetPVarInt(playerid, "TradeID");
    if(tradeid != INVALID_PLAYER_ID && LoggedIn[tradeid]){

        new string[128];
        format(string, sizeof string, "%s", ReturnRoleplayName(playerid));
        PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][2], string);
        if(!PlayerSelectingItem[tradeid]) PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][2], string);

        format(string, sizeof string, "%s", ReturnRoleplayName(tradeid));
        PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][34], string);
        if(!PlayerSelectingItem[tradeid]) PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][34], string);

        format(string, sizeof string, "%s", FormatNumber(PlayerTradeMoney[playerid]));
        PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][33], string);
        if(!PlayerSelectingItem[tradeid]) PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][33], string);

        format(string, sizeof string, "%s", FormatNumber(PlayerTradeMoney[tradeid]));
        PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][65], string);
        if(!PlayerSelectingItem[tradeid]) PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][65], string);

        //================================================================//

        if(Trade_Item[playerid][0][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][3]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][3], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][3], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][3]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][4]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][5]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][3]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][3], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][3], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][3]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][4]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][5]);
            }
            
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][3]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][3], Trade_Item[playerid][0][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][3], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][3]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][4]);

            format(string, sizeof string, "%d", Trade_Item[playerid][0][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][4], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][5]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][3]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][3], Trade_Item[playerid][0][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][3], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][3]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][4]);

                format(string, sizeof string, "%d", Trade_Item[playerid][0][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][4], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][5]);
            }
        }

        if(Trade_Item[tradeid][0][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][35]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][35], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][35], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][35]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][36]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][37]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][35]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][35], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][35], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][35]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][36]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][37]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][35]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][35], Trade_Item[tradeid][0][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][35], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][35]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][36]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][0][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][36], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][37]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][35]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][35], Trade_Item[tradeid][0][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][35], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][35]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][36]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][0][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][36], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][37]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][1][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][6]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][6], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][6], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][6]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][7]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][8]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][6]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][6], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][6], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][6]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][7]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][8]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][6]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][6], Trade_Item[playerid][1][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][6], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][6]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][7]);

            format(string, sizeof string, "%d", Trade_Item[playerid][1][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][7], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][8]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][6]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][6], Trade_Item[playerid][1][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][6], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][6]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][7]);

                format(string, sizeof string, "%d", Trade_Item[playerid][1][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][7], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][8]);
            }
        }

        if(Trade_Item[tradeid][1][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][38]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][38], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][38], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][38]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][39]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][40]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][38]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][38], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][38], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][38]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][39]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][40]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][38]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][38], Trade_Item[tradeid][1][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][38], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][38]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][39]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][1][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][39], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][40]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][38]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][38], Trade_Item[tradeid][1][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][38], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][38]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][39]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][1][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][39], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][40]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][2][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][9]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][9], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][9], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][9]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][10]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][11]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][9]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][9], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][9], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][9]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][10]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][11]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][9]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][9], Trade_Item[playerid][2][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][9], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][9]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][10]);

            format(string, sizeof string, "%d", Trade_Item[playerid][2][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][10], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][11]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][9]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][9], Trade_Item[playerid][2][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][9], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][9]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][10]);

                format(string, sizeof string, "%d", Trade_Item[playerid][2][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][10], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][11]);
            }
        }

        if(Trade_Item[tradeid][2][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][41]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][41], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][41], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][41]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][42]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][43]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][41]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][41], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][41], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][41]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][42]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][43]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][41]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][41], Trade_Item[tradeid][2][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][41], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][41]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][42]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][2][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][42], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][43]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][41]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][41], Trade_Item[tradeid][2][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][41], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][41]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][42]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][2][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][42], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][43]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][3][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][12]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][12], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][12], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][12]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][13]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][14]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][12]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][12], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][12], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][12]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][13]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][14]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][12]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][12], Trade_Item[playerid][3][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][12], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][12]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][13]);

            format(string, sizeof string, "%d", Trade_Item[playerid][3][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][13], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][14]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][12]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][12], Trade_Item[playerid][3][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][12], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][12]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][13]);

                format(string, sizeof string, "%d", Trade_Item[playerid][3][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][13], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][14]);
            }
        }

        if(Trade_Item[tradeid][3][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][44]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][44], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][44], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][44]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][45]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][46]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][44]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][44], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][44], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][44]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][45]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][46]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][44]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][44], Trade_Item[tradeid][3][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][44], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][44]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][45]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][3][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][45], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][46]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][44]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][44], Trade_Item[tradeid][3][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][44], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][44]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][45]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][3][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][45], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][46]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][4][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][15]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][15], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][15], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][15]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][16]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][17]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][15]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][15], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][15], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][15]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][16]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][17]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][15]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][15], Trade_Item[playerid][4][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][15], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][15]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][16]);

            format(string, sizeof string, "%d", Trade_Item[playerid][4][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][16], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][17]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][15]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][15], Trade_Item[playerid][4][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][15], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][15]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][16]);

                format(string, sizeof string, "%d", Trade_Item[playerid][4][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][16], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][17]);
            }
        }

        if(Trade_Item[tradeid][4][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][47]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][47], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][47], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][47]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][48]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][49]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][47]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][47], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][47], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][47]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][48]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][49]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][47]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][47], Trade_Item[tradeid][4][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][47], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][47]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][48]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][4][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][48], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][49]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][47]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][47], Trade_Item[tradeid][4][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][47], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][47]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][48]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][4][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][48], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][49]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][5][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][18]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][18], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][18], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][18]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][19]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][20]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][18]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][18], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][18], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][18]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][19]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][20]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][18]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][18], Trade_Item[playerid][5][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][18], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][18]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][19]);

            format(string, sizeof string, "%d", Trade_Item[playerid][5][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][19], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][20]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][18]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][18], Trade_Item[playerid][5][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][18], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][18]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][19]);

                format(string, sizeof string, "%d", Trade_Item[playerid][5][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][19], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][20]);
            }
        }

        if(Trade_Item[tradeid][5][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][50]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][50], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][50], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][50]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][51]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][52]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][50]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][50], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][50], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][50]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][51]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][52]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][50]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][50], Trade_Item[tradeid][5][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][50], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][50]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][51]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][5][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][51], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][52]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][50]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][50], Trade_Item[tradeid][5][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][50], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][50]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][51]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][5][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][51], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][52]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][6][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][21]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][21], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][21], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][21]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][22]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][23]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][21]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][21], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][21], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][21]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][22]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][23]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][21]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][21], Trade_Item[playerid][6][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][21], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][21]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][22]);

            format(string, sizeof string, "%d", Trade_Item[playerid][6][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][22], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][23]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][21]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][21], Trade_Item[playerid][6][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][21], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][21]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][22]);

                format(string, sizeof string, "%d", Trade_Item[playerid][6][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][22], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][23]);
            }
        }

        if(Trade_Item[tradeid][6][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][53]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][53], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][53], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][53]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][54]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][55]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][53]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][53], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][53], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][53]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][54]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][55]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][53]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][53], Trade_Item[tradeid][6][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][53], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][53]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][54]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][6][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][54], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][55]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][53]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][53], Trade_Item[tradeid][6][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][53], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][53]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][54]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][6][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][54], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][55]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][7][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][24]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][24], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][24], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][24]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][25]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][26]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][24]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][24], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][24], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][24]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][25]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][26]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][24]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][24], Trade_Item[playerid][7][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][24], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][24]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][25]);

            format(string, sizeof string, "%d", Trade_Item[playerid][7][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][25], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][26]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][24]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][24], Trade_Item[playerid][7][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][24], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][24]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][25]);

                format(string, sizeof string, "%d", Trade_Item[playerid][7][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][25], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][26]);
            }
        }

        if(Trade_Item[tradeid][7][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][56]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][56], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][56], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][56]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][57]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][58]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][56]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][56], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][56], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][56]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][57]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][58]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][56]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][56], Trade_Item[tradeid][7][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][56], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][56]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][57]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][7][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][57], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][58]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][56]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][56], Trade_Item[tradeid][7][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][56], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][56]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][57]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][7][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][57], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][58]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][8][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][27]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][27], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][27], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][27]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][28]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][29]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][27]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][27], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][27], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][27]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][28]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][29]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][27]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][27], Trade_Item[playerid][8][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][27], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][27]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][28]);

            format(string, sizeof string, "%d", Trade_Item[playerid][8][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][28], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][29]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][27]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][27], Trade_Item[playerid][8][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][27], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][27]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][28]);

                format(string, sizeof string, "%d", Trade_Item[playerid][8][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][28], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][29]);
            }
        }

        if(Trade_Item[tradeid][8][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][59]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][59], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][59], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][59]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][60]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][61]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][59]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][59], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][59], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][59]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][60]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][61]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][59]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][59], Trade_Item[tradeid][8][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][59], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][59]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][60]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][8][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][60], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][61]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][59]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][59], Trade_Item[tradeid][8][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][59], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][59]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][60]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][8][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][60], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][61]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][9][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][30]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][30], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][30], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][30]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][31]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][32]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][30]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][30], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][30], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][30]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][31]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][32]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][30]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][30], Trade_Item[playerid][9][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][30], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][30]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][31]);

            format(string, sizeof string, "%d", Trade_Item[playerid][9][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][31], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][32]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][30]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][30], Trade_Item[playerid][9][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][30], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][30]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][31]);

                format(string, sizeof string, "%d", Trade_Item[playerid][9][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][31], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][32]);
            }
        }

        if(Trade_Item[tradeid][9][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][62]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][62], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][62], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][62]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][63]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][64]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][62]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][62], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][62], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][62]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][63]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][64]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][62]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][62], Trade_Item[tradeid][9][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][62], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][62]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][63]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][9][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][63], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][64]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][62]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][62], Trade_Item[tradeid][9][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][62], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][62]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][63]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][9][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][63], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][64]);
            }
        }

        //================================================================//
    }
    return 1;
}

PlayerTradeItem_UpdateRender2(playerid){
    new tradeid = GetPVarInt(playerid, "TradeID");
    if(tradeid != INVALID_PLAYER_ID && LoggedIn[tradeid]){

        new string[128];
        format(string, sizeof string, "%s", ReturnRoleplayName(playerid));
        PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][34], string);
        if(!PlayerSelectingItem[tradeid]) PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][34], string);

        format(string, sizeof string, "%s", ReturnRoleplayName(tradeid));
        PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][2], string);
        if(!PlayerSelectingItem[tradeid]) PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][2], string);

        format(string, sizeof string, "%s", FormatNumber(PlayerTradeMoney[playerid]));
        PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][65], string);
        if(!PlayerSelectingItem[tradeid]) PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[playerid][65], string);

        format(string, sizeof string, "%s", FormatNumber(PlayerTradeMoney[tradeid]));
        PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][33], string);
        if(!PlayerSelectingItem[tradeid]) PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[playerid][33], string);

        //================================================================//

        if(Trade_Item[playerid][0][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][35]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][35], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][35], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][35]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][36]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][37]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][35]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][35], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][35], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][35]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][36]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][37]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][35]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][35], Trade_Item[playerid][0][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][35], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][35]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][36]);

            format(string, sizeof string, "%d", Trade_Item[playerid][0][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][36], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][37]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][35]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][35], Trade_Item[playerid][0][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][35], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][35]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][36]);

                format(string, sizeof string, "%d", Trade_Item[playerid][0][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][36], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][37]);
            }
        }

        if(Trade_Item[tradeid][0][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][3]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][3], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][3], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][3]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][4]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][5]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][3]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][3], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][3], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][3]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][4]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][5]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][3]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][3], Trade_Item[tradeid][0][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][3], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][3]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][4]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][0][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][4], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][5]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][3]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][3], Trade_Item[tradeid][0][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][3], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][3]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][4]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][0][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][4], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][5]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][1][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][38]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][38], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][38], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][38]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][39]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][40]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][38]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][38], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][38], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][38]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][39]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][40]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][38]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][38], Trade_Item[playerid][1][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][38], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][38]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][39]);

            format(string, sizeof string, "%d", Trade_Item[playerid][1][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][39], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][40]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][38]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][38], Trade_Item[playerid][1][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][38], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][38]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][39]);

                format(string, sizeof string, "%d", Trade_Item[playerid][1][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][39], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][40]);
            }
        }

        if(Trade_Item[tradeid][1][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][6]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][6], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][6], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][6]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][7]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][8]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][6]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][6], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][6], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][6]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][7]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][8]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][6]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][6], Trade_Item[tradeid][1][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][6], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][6]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][7]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][1][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][7], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][8]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][6]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][6], Trade_Item[tradeid][1][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][6], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][6]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][7]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][1][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][7], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][8]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][2][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][41]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][41], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][41], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][41]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][42]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][43]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][41]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][41], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][41], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][41]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][42]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][43]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][41]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][41], Trade_Item[playerid][2][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][41], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][41]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][42]);

            format(string, sizeof string, "%d", Trade_Item[playerid][2][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][42], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][43]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][41]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][41], Trade_Item[playerid][2][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][41], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][41]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][42]);

                format(string, sizeof string, "%d", Trade_Item[playerid][2][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][42], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][43]);
            }
        }

        if(Trade_Item[tradeid][2][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][9]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][9], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][9], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][9]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][10]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][11]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][9]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][9], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][9], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][9]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][10]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][11]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][9]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][9], Trade_Item[tradeid][2][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][9], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][9]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][10]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][2][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][10], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][11]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][9]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][9], Trade_Item[tradeid][2][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][9], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][9]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][10]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][2][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][10], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][11]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][3][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][44]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][44], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][44], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][44]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][45]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][46]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][44]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][44], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][44], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][44]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][45]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][46]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][44]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][44], Trade_Item[playerid][3][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][44], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][44]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][45]);

            format(string, sizeof string, "%d", Trade_Item[playerid][3][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][45], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][46]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][44]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][44], Trade_Item[playerid][3][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][44], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][44]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][45]);

                format(string, sizeof string, "%d", Trade_Item[playerid][3][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][45], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][46]);
            }
        }

        if(Trade_Item[tradeid][3][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][12]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][12], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][12], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][12]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][13]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][14]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][12]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][12], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][12], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][12]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][13]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][14]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][12]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][12], Trade_Item[tradeid][3][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][12], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][12]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][13]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][3][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][13], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][14]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][12]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][12], Trade_Item[tradeid][3][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][12], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][12]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][13]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][3][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][13], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][14]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][4][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][47]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][47], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][47], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][47]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][48]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][49]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][47]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][47], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][47], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][47]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][48]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][49]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][47]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][47], Trade_Item[playerid][4][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][47], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][47]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][48]);

            format(string, sizeof string, "%d", Trade_Item[playerid][4][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][48], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][49]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][47]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][47], Trade_Item[playerid][4][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][47], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][47]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][48]);

                format(string, sizeof string, "%d", Trade_Item[playerid][4][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][48], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][49]);
            }
        }

        if(Trade_Item[tradeid][4][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][15]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][15], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][15], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][15]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][16]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][17]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][15]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][15], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][15], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][15]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][16]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][17]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][15]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][15], Trade_Item[tradeid][4][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][15], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][15]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][16]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][4][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][16], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][17]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][15]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][15], Trade_Item[tradeid][4][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][15], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][15]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][16]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][4][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][16], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][17]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][5][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][50]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][50], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][50], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][50]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][51]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][52]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][50]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][50], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][50], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][50]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][51]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][52]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][59]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][50], Trade_Item[playerid][5][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][50], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][50]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][51]);

            format(string, sizeof string, "%d", Trade_Item[playerid][5][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][51], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][52]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][50]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][50], Trade_Item[playerid][5][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][50], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][50]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][51]);

                format(string, sizeof string, "%d", Trade_Item[playerid][5][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][51], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][52]);
            }
        }

        if(Trade_Item[tradeid][5][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][18]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][18], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][18], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][18]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][19]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][20]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][18]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][18], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][18], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][18]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][19]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][20]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][18]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][18], Trade_Item[tradeid][5][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][18], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][18]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][19]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][5][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][19], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][20]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][18]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][18], Trade_Item[tradeid][5][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][18], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][18]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][19]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][5][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][19], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][20]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][6][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][53]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][53], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][53], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][53]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][54]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][55]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][53]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][53], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][53], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][53]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][54]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][55]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][53]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][53], Trade_Item[playerid][6][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][53], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][53]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][54]);

            format(string, sizeof string, "%d", Trade_Item[playerid][6][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][54], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][55]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][53]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][53], Trade_Item[playerid][6][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][53], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][53]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][54]);

                format(string, sizeof string, "%d", Trade_Item[playerid][6][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][54], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][55]);
            }
        }

        if(Trade_Item[tradeid][6][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][21]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][21], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][21], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][21]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][22]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][23]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][21]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][21], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][21], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][21]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][22]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][23]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][21]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][21], Trade_Item[tradeid][6][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][21], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][21]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][22]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][6][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][22], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][23]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][21]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][21], Trade_Item[tradeid][6][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][21], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][21]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][22]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][6][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][22], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][23]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][7][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][56]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][56], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][56], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][56]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][57]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][58]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][56]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][56], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][56], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][56]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][57]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][58]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][56]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][56], Trade_Item[playerid][7][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][56], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][56]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][57]);

            format(string, sizeof string, "%d", Trade_Item[playerid][7][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][57], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][58]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][56]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][56], Trade_Item[playerid][7][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][56], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][56]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][57]);

                format(string, sizeof string, "%d", Trade_Item[playerid][7][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][57], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][58]);
            }
        }

        if(Trade_Item[tradeid][7][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][24]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][24], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][24], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][24]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][25]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][26]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][24]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][24], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][24], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][24]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][25]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][26]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][24]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][24], Trade_Item[tradeid][7][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][24], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][24]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][25]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][7][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][25], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][26]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][24]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][24], Trade_Item[tradeid][7][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][24], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][24]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][25]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][7][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][25], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][26]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][8][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][59]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][59], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][59], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][59]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][60]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][61]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][59]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][59], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][59], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][59]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][60]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][61]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][59]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][59], Trade_Item[playerid][8][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][59], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][59]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][60]);

            format(string, sizeof string, "%d", Trade_Item[playerid][8][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][60], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][61]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][59]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][59], Trade_Item[playerid][8][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][59], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][59]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][60]);

                format(string, sizeof string, "%d", Trade_Item[playerid][8][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][60], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][61]);
            }
        }

        if(Trade_Item[tradeid][8][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][27]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][27], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][27], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][27]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][28]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][29]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][27]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][27], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][27], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][27]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][28]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][29]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][27]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][27], Trade_Item[tradeid][8][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][27], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][27]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][28]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][8][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][28], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][29]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][27]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][27], Trade_Item[tradeid][8][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][27], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][27]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][28]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][8][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][28], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][29]);
            }
        }

        //================================================================//

        if(Trade_Item[playerid][9][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][62]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][62], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][62], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][62]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][63]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][64]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][62]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][62], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][62], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][62]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][63]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][64]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][62]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][62], Trade_Item[playerid][9][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][62], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][62]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][63]);

            format(string, sizeof string, "%d", Trade_Item[playerid][9][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][63], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][64]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][62]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][62], Trade_Item[playerid][9][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][62], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][62]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][63]);

                format(string, sizeof string, "%d", Trade_Item[playerid][9][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][63], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][64]);
            }
        }

        if(Trade_Item[tradeid][9][itemModel] == MODEL_NULL){
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][30]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][30], MODEL_NULL);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][30], 0.000000, 0.000000, 0.000000, 0.000000);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][30]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][31]);
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][32]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][30]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][30], MODEL_NULL);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][30], 0.000000, 0.000000, 0.000000, 0.000000);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][30]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][31]);
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][32]);
            }
        }
        else{
            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][30]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][30], Trade_Item[tradeid][9][itemModel]);
            PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][30], -10.000000, 0.000000, -20.000000, 0.939999);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][30]);
            PlayerTextDrawShow(playerid, PlayerTDTradeItem[playerid][31]);

            format(string, sizeof string, "%d", Trade_Item[tradeid][9][itemQuantity]);
            PlayerTextDrawSetString(playerid, PlayerTDTradeItem[playerid][31], string);

            PlayerTextDrawHide(playerid, PlayerTDTradeItem[playerid][32]);

            if(!PlayerSelectingItem[tradeid]){
                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][30]);
                PlayerTextDrawSetPreviewModel(tradeid, PlayerTDTradeItem[tradeid][30], Trade_Item[tradeid][9][itemModel]);
                PlayerTextDrawSetPreviewRot(tradeid, PlayerTDTradeItem[tradeid][30], -10.000000, 0.000000, -20.000000, 0.939999);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][30]);
                PlayerTextDrawShow(tradeid, PlayerTDTradeItem[tradeid][31]);

                format(string, sizeof string, "%d", Trade_Item[tradeid][9][itemQuantity]);
                PlayerTextDrawSetString(tradeid, PlayerTDTradeItem[tradeid][31], string);

                PlayerTextDrawHide(tradeid, PlayerTDTradeItem[tradeid][32]);
            }
        }

        //================================================================//
    }
    return 1;
}

LoadPlayerTDTradeItem_TradeItem(playerid){
    PlayerTDTradeItem[playerid][0] = CreatePlayerTextDraw(playerid, 323.500000, 108.000000, "_");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][0], 1.016666, 29.800003);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][0], 298.500000, 175.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][0], 2);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][0], 185);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][0], 0);

    PlayerTDTradeItem[playerid][1] = CreatePlayerTextDraw(playerid, 238.000000, 109.000000, "Trade");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][1], 0.312500, 1.450000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][1], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][1], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][1], 0);

    PlayerTDTradeItem[playerid][2] = CreatePlayerTextDraw(playerid, 321.000000, 127.000000, "Firstname Lastname");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][2], 0.312500, 1.450000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][2], 400.000000, 112.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][2], 2);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][2], -1094795726);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][2], 0);

    //-10.000000, 0.000000, -20.000000, 0.939999

    PlayerTDTradeItem[playerid][3] = CreatePlayerTextDraw(playerid, 244.000000, 147.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][3], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][3], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][3], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][3], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][3], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][3], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][3], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][3], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][3], 1, 1);

    PlayerTDTradeItem[playerid][4] = CreatePlayerTextDraw(playerid, 273.000000, 170.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][4], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][4], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][4], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][4], 0);

    PlayerTDTradeItem[playerid][5] = CreatePlayerTextDraw(playerid, 245.000000, 148.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][5], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][5], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][5], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][5], 0);

    PlayerTDTradeItem[playerid][6] = CreatePlayerTextDraw(playerid, 276.000000, 147.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][6], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][6], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][6], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][6], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][6], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][6], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][6], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][6], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][6], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][6], 1, 1);

    PlayerTDTradeItem[playerid][7] = CreatePlayerTextDraw(playerid, 305.000000, 170.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][7], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][7], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][7], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][7], 0);

    PlayerTDTradeItem[playerid][8] = CreatePlayerTextDraw(playerid, 277.000000, 148.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][8], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][8], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][8], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][8], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][8], 0);

    PlayerTDTradeItem[playerid][9] = CreatePlayerTextDraw(playerid, 308.000000, 147.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][9], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][9], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][9], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][9], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][9], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][9], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][9], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][9], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][9], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][9], 1, 1);

    PlayerTDTradeItem[playerid][10] = CreatePlayerTextDraw(playerid, 337.000000, 170.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][10], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][10], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][10], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][10], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][10], 0);

    PlayerTDTradeItem[playerid][11] = CreatePlayerTextDraw(playerid, 309.000000, 148.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][11], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][11], 0.137500, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][11], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][11], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][11], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][11], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][11], 0);

    PlayerTDTradeItem[playerid][12] = CreatePlayerTextDraw(playerid, 340.000000, 147.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][12], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][12], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][12], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][12], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][12], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][12], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][12], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][12], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][12], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][12], 1, 1);

    PlayerTDTradeItem[playerid][13] = CreatePlayerTextDraw(playerid, 369.000000, 170.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][13], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][13], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][13], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][13], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][13], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][13], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][13], 0);

    PlayerTDTradeItem[playerid][14] = CreatePlayerTextDraw(playerid, 341.000000, 148.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][14], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][14], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][14], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][14], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][14], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][14], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][14], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][14], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][14], 0);

    PlayerTDTradeItem[playerid][15] = CreatePlayerTextDraw(playerid, 372.000000, 147.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][15], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][15], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][15], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][15], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][15], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][15], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][15], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][15], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][15], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][15], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][15], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][15], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][15], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][15], 1, 1);

    PlayerTDTradeItem[playerid][16] = CreatePlayerTextDraw(playerid, 401.000000, 170.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][16], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][16], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][16], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][16], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][16], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][16], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][16], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][16], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][16], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][16], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][16], 0);

    PlayerTDTradeItem[playerid][17] = CreatePlayerTextDraw(playerid, 373.000000, 148.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][17], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][17], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][17], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][17], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][17], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][17], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][17], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][17], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][17], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][17], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][17], 0);

    PlayerTDTradeItem[playerid][18] = CreatePlayerTextDraw(playerid, 244.000000, 181.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][18], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][18], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][18], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][18], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][18], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][18], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][18], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][18], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][18], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][18], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][18], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][18], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][18], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][18], 1, 1);

    PlayerTDTradeItem[playerid][19] = CreatePlayerTextDraw(playerid, 273.000000, 204.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][19], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][19], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][19], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][19], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][19], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][19], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][19], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][19], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][19], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][19], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][19], 0);

    PlayerTDTradeItem[playerid][20] = CreatePlayerTextDraw(playerid, 245.000000, 182.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][20], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][20], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][20], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][20], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][20], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][20], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][20], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][20], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][20], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][20], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][20], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][20], 0);

    PlayerTDTradeItem[playerid][21] = CreatePlayerTextDraw(playerid, 276.000000, 181.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][21], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][21], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][21], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][21], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][21], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][21], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][21], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][21], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][21], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][21], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][21], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][21], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][21], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][21], 1, 1);

    PlayerTDTradeItem[playerid][22] = CreatePlayerTextDraw(playerid, 305.000000, 204.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][22], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][22], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][22], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][22], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][22], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][22], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][22], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][22], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][22], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][22], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][22], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][22], 0);

    PlayerTDTradeItem[playerid][23] = CreatePlayerTextDraw(playerid, 277.000000, 182.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][23], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][23], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][23], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][23], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][23], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][23], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][23], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][23], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][23], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][23], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][23], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][23], 0);

    PlayerTDTradeItem[playerid][24] = CreatePlayerTextDraw(playerid, 308.000000, 181.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][24], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][24], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][24], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][24], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][24], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][24], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][24], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][24], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][24], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][24], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][24], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][24], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][24], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][24], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][24], 1, 1);

    PlayerTDTradeItem[playerid][25] = CreatePlayerTextDraw(playerid, 337.000000, 204.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][25], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][25], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][25], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][25], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][25], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][25], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][25], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][25], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][25], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][25], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][25], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][25], 0);

    PlayerTDTradeItem[playerid][26] = CreatePlayerTextDraw(playerid, 309.000000, 182.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][26], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][26], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][26], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][26], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][26], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][26], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][26], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][26], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][26], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][26], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][26], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][26], 0);

    PlayerTDTradeItem[playerid][27] = CreatePlayerTextDraw(playerid, 340.000000, 181.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][27], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][27], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][27], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][27], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][27], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][27], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][27], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][27], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][27], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][27], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][27], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][27], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][27], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][27], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][27], 1, 1);

    PlayerTDTradeItem[playerid][28] = CreatePlayerTextDraw(playerid, 369.000000, 204.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][28], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][28], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][28], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][28], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][28], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][28], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][28], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][28], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][28], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][28], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][28], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][28], 0);

    PlayerTDTradeItem[playerid][29] = CreatePlayerTextDraw(playerid, 341.000000, 182.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][29], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][29], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][29], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][29], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][29], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][29], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][29], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][29], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][29], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][29], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][29], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][29], 0);

    PlayerTDTradeItem[playerid][30] = CreatePlayerTextDraw(playerid, 372.000000, 181.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][30], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][30], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][30], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][30], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][30], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][30], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][30], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][30], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][30], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][30], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][30], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][30], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][30], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][30], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][30], 1, 1);

    PlayerTDTradeItem[playerid][31] = CreatePlayerTextDraw(playerid, 401.000000, 204.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][31], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][31], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][31], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][31], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][31], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][31], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][31], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][31], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][31], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][31], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][31], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][31], 0);

    PlayerTDTradeItem[playerid][32] = CreatePlayerTextDraw(playerid, 373.000000, 182.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][32], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][32], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][32], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][32], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][32], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][32], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][32], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][32], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][32], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][32], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][32], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][32], 0);

    PlayerTDTradeItem[playerid][33] = CreatePlayerTextDraw(playerid, 337.000000, 219.000000, "$10,000");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][33], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][33], 0.250000, 1.000003);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][33], 401.000000, 75.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][33], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][33], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][33], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][33], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][33], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][33], -1094795641);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][33], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][33], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][33], 0);

    PlayerTDTradeItem[playerid][34] = CreatePlayerTextDraw(playerid, 321.000000, 236.000000, "Firstname Lastname");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][34], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][34], 0.312500, 1.450000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][34], 400.000000, 112.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][34], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][34], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][34], 2);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][34], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][34], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][34], -1094795726);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][34], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][34], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][34], 0);

    PlayerTDTradeItem[playerid][35] = CreatePlayerTextDraw(playerid, 244.000000, 257.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][35], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][35], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][35], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][35], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][35], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][35], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][35], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][35], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][35], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][35], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][35], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][35], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][35], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][35], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][35], 1, 1);

    PlayerTDTradeItem[playerid][36] = CreatePlayerTextDraw(playerid, 273.000000, 280.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][36], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][36], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][36], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][36], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][36], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][36], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][36], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][36], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][36], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][36], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][36], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][36], 0);

    PlayerTDTradeItem[playerid][37] = CreatePlayerTextDraw(playerid, 245.000000, 258.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][37], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][37], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][37], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][37], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][37], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][37], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][37], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][37], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][37], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][37], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][37], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][37], 0);

    PlayerTDTradeItem[playerid][38] = CreatePlayerTextDraw(playerid, 276.000000, 257.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][38], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][38], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][38], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][38], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][38], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][38], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][38], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][38], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][38], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][38], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][38], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][38], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][38], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][38], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][38], 1, 1);

    PlayerTDTradeItem[playerid][39] = CreatePlayerTextDraw(playerid, 305.000000, 280.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][39], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][39], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][39], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][39], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][39], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][39], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][39], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][39], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][39], -16777166);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][39], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][39], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][39], 0);

    PlayerTDTradeItem[playerid][40] = CreatePlayerTextDraw(playerid, 277.000000, 258.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][40], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][40], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][40], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][40], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][40], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][40], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][40], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][40], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][40], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][40], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][40], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][40], 0);

    PlayerTDTradeItem[playerid][41] = CreatePlayerTextDraw(playerid, 308.000000, 257.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][41], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][41], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][41], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][41], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][41], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][41], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][41], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][41], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][41], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][41], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][41], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][41], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][41], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][41], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][41], 1, 1);

    PlayerTDTradeItem[playerid][42] = CreatePlayerTextDraw(playerid, 337.000000, 280.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][42], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][42], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][42], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][42], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][42], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][42], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][42], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][42], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][42], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][42], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][42], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][42], 0);

    PlayerTDTradeItem[playerid][43] = CreatePlayerTextDraw(playerid, 309.000000, 258.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][43], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][43], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][43], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][43], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][43], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][43], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][43], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][43], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][43], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][43], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][43], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][43], 0);

    PlayerTDTradeItem[playerid][44] = CreatePlayerTextDraw(playerid, 340.000000, 257.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][44], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][44], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][44], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][44], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][44], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][44], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][44], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][44], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][44], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][44], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][44], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][44], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][44], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][44], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][44], 1, 1);

    PlayerTDTradeItem[playerid][45] = CreatePlayerTextDraw(playerid, 369.000000, 280.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][45], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][45], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][45], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][45], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][45], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][45], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][45], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][45], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][45], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][45], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][45], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][45], 0);

    PlayerTDTradeItem[playerid][46] = CreatePlayerTextDraw(playerid, 341.000000, 258.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][46], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][46], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][46], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][46], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][46], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][46], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][46], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][46], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][46], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][46], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][46], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][46], 0);

    PlayerTDTradeItem[playerid][47] = CreatePlayerTextDraw(playerid, 372.000000, 257.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][47], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][47], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][47], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][47], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][47], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][47], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][47], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][47], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][47], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][47], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][47], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][47], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][47], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][47], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][47], 1, 1);

    PlayerTDTradeItem[playerid][48] = CreatePlayerTextDraw(playerid, 401.000000, 280.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][48], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][48], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][48], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][48], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][48], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][48], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][48], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][48], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][48], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][48], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][48], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][48], 0);

    PlayerTDTradeItem[playerid][49] = CreatePlayerTextDraw(playerid, 373.000000, 258.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][49], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][49], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][49], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][49], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][49], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][49], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][49], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][49], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][49], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][49], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][49], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][49], 0);

    PlayerTDTradeItem[playerid][50] = CreatePlayerTextDraw(playerid, 244.000000, 291.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][50], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][50], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][50], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][50], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][50], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][50], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][50], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][50], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][50], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][50], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][50], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][50], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][50], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][50], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][50], 1, 1);

    PlayerTDTradeItem[playerid][51] = CreatePlayerTextDraw(playerid, 273.000000, 314.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][51], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][51], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][51], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][51], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][51], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][51], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][51], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][51], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][51], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][51], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][51], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][51], 0);

    PlayerTDTradeItem[playerid][52] = CreatePlayerTextDraw(playerid, 245.000000, 292.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][52], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][52], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][52], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][52], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][52], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][52], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][52], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][52], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][52], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][52], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][52], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][52], 0);

    PlayerTDTradeItem[playerid][53] = CreatePlayerTextDraw(playerid, 276.000000, 291.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][53], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][53], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][53], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][53], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][53], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][53], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][53], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][53], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][53], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][53], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][53], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][53], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][53], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][53], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][53], 1, 1);

    PlayerTDTradeItem[playerid][54] = CreatePlayerTextDraw(playerid, 304.000000, 314.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][54], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][54], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][54], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][54], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][54], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][54], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][54], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][54], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][54], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][54], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][54], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][54], 0);

    PlayerTDTradeItem[playerid][55] = CreatePlayerTextDraw(playerid, 277.000000, 292.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][55], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][55], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][55], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][55], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][55], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][55], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][55], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][55], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][55], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][55], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][55], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][55], 0);

    PlayerTDTradeItem[playerid][56] = CreatePlayerTextDraw(playerid, 308.000000, 291.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][56], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][56], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][56], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][56], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][56], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][56], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][56], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][56], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][56], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][56], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][56], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][56], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][56], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][56], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][56], 1, 1);

    PlayerTDTradeItem[playerid][57] = CreatePlayerTextDraw(playerid, 337.000000, 314.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][57], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][57], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][57], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][57], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][57], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][57], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][57], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][57], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][57], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][57], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][57], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][57], 0);

    PlayerTDTradeItem[playerid][58] = CreatePlayerTextDraw(playerid, 309.000000, 292.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][58], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][58], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][58], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][58], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][58], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][58], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][58], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][58], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][58], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][58], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][58], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][58], 0);

    PlayerTDTradeItem[playerid][59] = CreatePlayerTextDraw(playerid, 340.000000, 291.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][59], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][59], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][59], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][59], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][59], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][59], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][59], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][59], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][59], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][59], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][59], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][59], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][59], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][59], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][59], 1, 1);

    PlayerTDTradeItem[playerid][60] = CreatePlayerTextDraw(playerid, 369.000000, 314.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][60], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][60], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][60], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][60], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][60], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][60], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][60], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][60], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][60], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][60], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][60], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][60], 0);

    PlayerTDTradeItem[playerid][61] = CreatePlayerTextDraw(playerid, 341.000000, 292.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][61], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][61], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][61], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][61], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][61], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][61], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][61], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][61], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][61], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][61], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][61], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][61], 0);

    PlayerTDTradeItem[playerid][62] = CreatePlayerTextDraw(playerid, 372.000000, 291.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][62], 5);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][62], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][62], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][62], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][62], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][62], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][62], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][62], -1094795651);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][62], 255);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][62], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][62], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][62], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerTDTradeItem[playerid][62], MODEL_NULL);
    PlayerTextDrawSetPreviewRot(playerid, PlayerTDTradeItem[playerid][62], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerTDTradeItem[playerid][62], 1, 1);

    PlayerTDTradeItem[playerid][63] = CreatePlayerTextDraw(playerid, 401.000000, 314.000000, "10");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][63], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][63], 0.179166, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][63], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][63], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][63], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][63], 3);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][63], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][63], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][63], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][63], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][63], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][63], 0);

    PlayerTDTradeItem[playerid][64] = CreatePlayerTextDraw(playerid, 373.000000, 292.000000, "Boombox");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][64], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][64], 0.129166, 0.700000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][64], 273.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][64], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][64], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][64], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][64], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][64], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][64], 50);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][64], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][64], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][64], 0);

    PlayerTDTradeItem[playerid][65] = CreatePlayerTextDraw(playerid, 337.000000, 329.000000, "$10,000");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][65], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][65], 0.250000, 1.000003);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][65], 401.000000, 75.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][65], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][65], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][65], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][65], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][65], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][65], -1094795641);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][65], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][65], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][65], 0);

    PlayerTDTradeItem[playerid][66] = CreatePlayerTextDraw(playerid, 259.000000, 358.000000, "LOCK");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][66], 2);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][66], 0.191666, 1.500000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][66], 16.500000, 37.500000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][66], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][66], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][66], 2);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][66], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][66], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][66], -1962934072);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][66], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][66], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][66], 1);

    PlayerTDTradeItem[playerid][67] = CreatePlayerTextDraw(playerid, 301.000000, 358.000000, "CONFIRM");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][67], 2);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][67], 0.191666, 1.500000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][67], 16.500000, 37.500000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][67], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][67], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][67], 2);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][67], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][67], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][67], 852308680);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][67], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][67], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][67], 1);

    PlayerTDTradeItem[playerid][68] = CreatePlayerTextDraw(playerid, 344.000000, 358.000000, "INFO");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][68], 2);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][68], 0.191666, 1.500000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][68], 16.500000, 37.500000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][68], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][68], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][68], 2);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][68], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][68], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][68], -2016478520);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][68], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][68], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][68], 1);

    PlayerTDTradeItem[playerid][69] = CreatePlayerTextDraw(playerid, 387.000000, 358.000000, "CANCEL");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][69], 2);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][69], 0.191666, 1.500000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][69], 16.500000, 37.500000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][69], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][69], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][69], 2);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][69], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][69], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][69], -16777016);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][69], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][69], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][69], 1);

    PlayerTDTradeItem[playerid][70] = CreatePlayerTextDraw(playerid, 245.000000, 219.000000, "STATUS: UNLOCK");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][70], 2);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][70], 0.158333, 1.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][70], 332.500000, 112.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][70], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][70], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][70], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][70], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][70], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][70], -1094795726);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][70], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][70], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][70], 0);

    PlayerTDTradeItem[playerid][71] = CreatePlayerTextDraw(playerid, 245.000000, 329.000000, "STATUS: UNLOCK");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][71], 2);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][71], 0.158333, 1.000000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][71], 332.500000, 112.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][71], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][71], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][71], 1);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][71], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][71], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][71], -1094795726);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][71], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][71], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][71], 0);

    PlayerTDTradeItem[playerid][72] = CreatePlayerTextDraw(playerid, 440.000000, 149.000000, "ADD ITEM");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][72], 2);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][72], 0.191666, 1.500000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][72], 16.500000, 51.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][72], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][72], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][72], 2);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][72], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][72], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][72], 1296911816);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][72], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][72], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][72], 1);

    PlayerTDTradeItem[playerid][73] = CreatePlayerTextDraw(playerid, 440.000000, 176.000000, "ADD MONEY");
    PlayerTextDrawFont(playerid, PlayerTDTradeItem[playerid][73], 2);
    PlayerTextDrawLetterSize(playerid, PlayerTDTradeItem[playerid][73], 0.191666, 1.500000);
    PlayerTextDrawTextSize(playerid, PlayerTDTradeItem[playerid][73], 16.500000, 51.500000);
    PlayerTextDrawSetOutline(playerid, PlayerTDTradeItem[playerid][73], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTDTradeItem[playerid][73], 0);
    PlayerTextDrawAlignment(playerid, PlayerTDTradeItem[playerid][73], 2);
    PlayerTextDrawColor(playerid, PlayerTDTradeItem[playerid][73], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTDTradeItem[playerid][73], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTDTradeItem[playerid][73], 1296911816);
    PlayerTextDrawUseBox(playerid, PlayerTDTradeItem[playerid][73], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTDTradeItem[playerid][73], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTDTradeItem[playerid][73], 1);
    return 1;
}