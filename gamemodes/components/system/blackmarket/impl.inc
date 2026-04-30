#if defined _inc_impl
	#undef _inc_impl
#endif

LoadActorBlackMarket(){
    ActorWeed = CreateActor(28, -769.3740,1646.4735,27.5873,178.1235);
    SetActorVirtualWorld(ActorWeed, 0);

    ActorCocain = CreateActor(30, -762.5397,1646.3760,27.4727,180.8697);
    SetActorVirtualWorld(ActorCocain, 0);
    return 1;
}

Dialog:SellDrug(playerid, response, listitem, inputtext[]){
    if(!response)  return 1;
    new string[128];
    if(response){
        new amount = strval(inputtext);

        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนมากกว่า 0");

        new id = -1;
        if ((id = Drug_DeliverNearest(playerid)) != -1){
            if(DrugData[id][drugType] == 1){
                if(amount > PlayerInventory_AllCount(playerid, "Pack Weed")){
                    format(string, sizeof(string), "* คุณมีแพ็คกัญชาไม่พอที่จะขาย *\nแพ็คกัญชาในตัว : %d\nกรอกจำนวนที่จะต้องการขาย", PlayerInventory_AllCount(playerid, "Pack Weed"));
                    Dialog_ShowEasy(playerid, SellDrug, DIALOG_STYLE_INPUT, "ขายยา", string, "ขาย", "ยกเลิก");
                    return 1;
                }

                new price = amount*DrugData[id][drugPrice];

                PlayerInventory_Remove(playerid, "Pack Weed", amount);
                PlayerData[playerid][pRedMoney] += price;
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Pack Weed' จำนวน %d และได้รับเงินแดง %s", amount, FormatNumber(price));
            }
            if(DrugData[id][drugType] == 2){
                if(amount > PlayerInventory_AllCount(playerid, "Pack Cocain")){
                    format(string, sizeof(string), "* คุณมีแพ็คโคเคนไม่พอที่จะขาย *\nแพ็คโคเคนในตัว : %d\nกรอกจำนวนที่จะต้องการขาย", PlayerInventory_AllCount(playerid, "Pack Cocain"));
                    Dialog_ShowEasy(playerid, SellDrug, DIALOG_STYLE_INPUT, "ขายยา", string, "ขาย", "ยกเลิก");
                    return 1;
                }

                new price = amount*DrugData[id][drugPrice];

                PlayerInventory_Remove(playerid, "Pack Cocain", amount);
                PlayerData[playerid][pRedMoney] += price;
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Pack Cocain' จำนวน %d และได้รับเงินแดง %s", amount, FormatNumber(price));
            }
            if(DrugData[id][drugType] == 4){
                if(amount > PlayerInventory_AllCount(playerid, "Pack Cement")){
                    format(string, sizeof(string), "* คุณมีแพ็คปูนไม่พอที่จะขาย *\nแพ็คปูนในตัว : %d\nกรอกจำนวนที่จะต้องการขาย", PlayerInventory_AllCount(playerid, "Pack Cement"));
                    Dialog_ShowEasy(playerid, SellDrug, DIALOG_STYLE_INPUT, "ขายยา", string, "ขาย", "ยกเลิก");
                    return 1;
                }

                new price = amount*DrugData[id][drugPrice];

                PlayerInventory_Remove(playerid, "Pack Cement", amount);
                PlayerData[playerid][pRedMoney] += price;
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Pack Cement' จำนวน %d และได้รับเงินแดง %s", amount, FormatNumber(price));
            }
            if(DrugData[id][drugType] == 5){
                if(amount > PlayerInventory_AllCount(playerid, "Wire")){
                    format(string, sizeof(string), "* คุณมีสายไฟไม่พอ *\nสายไฟในตัว : %d\nกรอกจำนวนที่จะต้องการขาย", PlayerInventory_AllCount(playerid, "Wire"));
                    Dialog_ShowEasy(playerid, SellDrug, DIALOG_STYLE_INPUT, "ขายยสายไฟ", string, "ขาย", "ยกเลิก");
                    return 1;
                }

                new price = amount*DrugData[id][drugPrice];

                PlayerInventory_Remove(playerid, "Wire", amount);
                PlayerData[playerid][pRedMoney] += price;
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Wire' จำนวน %d และได้รับเงินแดง %s", amount, FormatNumber(price));
            }
        }
    }
    return 1;
}