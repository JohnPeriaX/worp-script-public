#if defined _inc_impl
	#undef _inc_impl
#endif


CMD:barshop(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    ShowMenuBarShop(playerid);
    return 1;
}

forward SetAnimationDrunkWalk(playerid);
public SetAnimationDrunkWalk(playerid){
    ApplyAnimationEx(playerid, "PED", "WALK_drunk", 4.1, 1, 1, 1, 1, 1, 1);
    return 1;
}

ShowMenuBarShop(playerid){
    if(!LoggedIn[playerid]) return 1;

    new string[128];
    format(string, sizeof(string), "เบียร์ (Beer)\t%s", FormatNumber(Beer_Price));
    Dialog_ShowEasy(playerid, Bar_Shop, DIALOG_STYLE_LIST, "บาร์", string, "ซื้อ", "ยกเลิก");

    return 1;
}

Dialog:Bar_Shop(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(GetMoney(playerid) < Beer_Price) return ErrorMsg(playerid, "คุณมีเงินไม่พอ");

            new id = PlayerInventory_AddItem(playerid, "Beer", 1520, 1);
            if(id == -1) return ErrorMsg(playerid, "คุณมีช่องเก็บไม่เพียงพอ");
            GiveMoney(playerid, -Beer_Price, "buy beer");
            SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ซื้อ 'เบียร์' ในราคา %s เรียบร้อยแล้ว", FormatNumber(Beer_Price));
        }
    }
    return 1;
}