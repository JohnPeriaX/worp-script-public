#if defined _inc_impl
	#undef _inc_impl
#endif

InsuranceMenu(playerid){
    new string[200];
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณจำเป็นต้องอยู่ยานพาหนะ");
    new vehicleid = GetPlayerVehicleID(playerid);
    new carid = Car_GetID(vehicleid);
    if(carid != -1){
        if(Car_IsOwner(playerid, carid)){
            if(PlayerData[playerid][pVip] == 1){ //Bronze Member
                format(string, sizeof(string), "- ขณะนี้คุณได้เป็น Bronze Member คุณได้จะสามารถซื้อใบประกันสำหรับยานพาหนะในราคา $4,000/1 ใบ\
                \nกรุณากรอกจำนวนที่คุณต้องการจะซื้อใบประกันให้กับยานพาหนะคันนี้: ");
            }
            else if(PlayerData[playerid][pVip] == 2){ //Silver Member
                format(string, sizeof(string), "- ขณะนี้คุณได้เป็น Silver Member คุณได้จะสามารถซื้อใบประกันสำหรับยานพาหนะในราคา $3,000/1 ใบ\
                \nกรุณากรอกจำนวนที่คุณต้องการจะซื้อใบประกันให้กับยานพาหนะคันนี้: ");
            }
            else if(PlayerData[playerid][pVip] == 3){ // Gold Member
                format(string, sizeof(string), "- ขณะนี้คุณได้เป็น Gold Member คุณได้จะสามารถซื้อใบประกันสำหรับยานพาหนะในราคา $2,000/1 ใบ\
                \nกรุณากรอกจำนวนที่คุณต้องการจะซื้อใบประกันให้กับยานพาหนะคันนี้: ");
            }
            else if(PlayerData[playerid][pVip] == 0){ //Regular Member
                format(string, sizeof(string), "- ขณะนี้คุณได้เป็น Regular Member คุณได้จะสามารถซื้อใบประกันสำหรับยานพาหนะในราคา $5,000/1 ใบ\
                \nกรุณากรอกจำนวนที่คุณต้องการจะซื้อใบประกันให้กับยานพาหนะคันนี้: ");
            }
            Dialog_ShowEasy(playerid, InsuranceDialog, DIALOG_STYLE_INPUT, "ใบประกันยานพาหนะ", string, "ตกลง", "ยกเลิก");
        }
        else return ErrorMsg(playerid, "ยานพาหนะคันนี้คุณไม่ได้เป็นเจ้าของ");
    }
    return 1;
}

Dialog:InsuranceDialog(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณจำเป็นต้องอยู่ยานพาหนะ");
        new string[256];
        new amount = strval(inputtext);
        if(amount <= 0 || amount > 10) return ErrorMsg(playerid, "คุณต้องกรอกจำนวน 1-10 เท่านั้น");
        new price;
        if(PlayerData[playerid][pVip] == 1){ //Bronze Member
            price = BRONZE_PRICE * amount;
            if(GetMoney(playerid) < price){
                format(string, sizeof(string), "* เงินของคุณไม่เพียงพอ *\n- ขณะนี้คุณได้เป็น Bronze Member คุณได้จะสามารถซื้อใบประกันสำหรับยานพาหนะในราคา $4,000/1 ใบ\
                \nกรุณากรอกจำนวนที่คุณต้องการจะซื้อใบประกันให้กับยานพาหนะคันนี้: ");
                return Dialog_ShowEasy(playerid, InsuranceDialog, DIALOG_STYLE_INPUT, "ใบประกันยานพาหนะ", string, "ตกลง", "ยกเลิก");
            }
        }
        else if(PlayerData[playerid][pVip] == 2){ //Silver Member
            price = SILVER_PRICE * amount;
            if(GetMoney(playerid) < price){
                format(string, sizeof(string), "* เงินของคุณไม่เพียงพอ *\n- ขณะนี้คุณได้เป็น Silver Member คุณได้จะสามารถซื้อใบประกันสำหรับยานพาหนะในราคา $3,000/1 ใบ\
                \nกรุณากรอกจำนวนที่คุณต้องการจะซื้อใบประกันให้กับยานพาหนะคันนี้: ");
                return Dialog_ShowEasy(playerid, InsuranceDialog, DIALOG_STYLE_INPUT, "ใบประกันยานพาหนะ", string, "ตกลง", "ยกเลิก");
            }
        }
        else if(PlayerData[playerid][pVip] == 3){ // Gold Member
            price = GOLD_PRICE * amount;
            if(GetMoney(playerid) < price){
                format(string, sizeof(string), "* เงินของคุณไม่เพียงพอ *\n- ขณะนี้คุณได้เป็น Gold Member คุณได้จะสามารถซื้อใบประกันสำหรับยานพาหนะในราคา $2,000/1 ใบ\
                \nกรุณากรอกจำนวนที่คุณต้องการจะซื้อใบประกันให้กับยานพาหนะคันนี้: ");
                return Dialog_ShowEasy(playerid, InsuranceDialog, DIALOG_STYLE_INPUT, "ใบประกันยานพาหนะ", string, "ตกลง", "ยกเลิก");
            }
        }
        else if(PlayerData[playerid][pVip] == 0){ //Regular Member
            price = REGULAR_PRICE * amount;
            if(GetMoney(playerid) < price){
                format(string, sizeof(string), "* เงินของคุณไม่เพียงพอ *\n- ขณะนี้คุณได้เป็น Regular Member คุณได้จะสามารถซื้อใบประกันสำหรับยานพาหนะในราคา $5,000/1 ใบ\
                \nกรุณากรอกจำนวนที่คุณต้องการจะซื้อใบประกันให้กับยานพาหนะคันนี้: ");
                return Dialog_ShowEasy(playerid, InsuranceDialog, DIALOG_STYLE_INPUT, "ใบประกันยานพาหนะ", string, "ตกลง", "ยกเลิก");
            }
        }

        new vehicleid = GetPlayerVehicleID(playerid);
        new carid = Car_GetID(vehicleid);
        if(carid != -1){
            GiveMoney(playerid, -price, "buy insureance");
            CarData[carid][carInsurance] += amount;
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ซื้อใบประกันให้กับยานพาหนะ %s ในราคา %s เรียบร้อยแล้ว", ReturnVehicleName(CarData[carid][carVehicle]), FormatNumber(price));
            Car_Save(carid);
        }
        
    }
    return 1;
}