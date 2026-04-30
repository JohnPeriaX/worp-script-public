#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

Reset_Mine(playerid){
    PlayerStartMine[playerid] = false;

    if(PlayerGetMineID[playerid] != -1){
        MineData[PlayerGetMineID[playerid]][mineUsed] = false;
    }

    stop MineTime[playerid];
    stop ProcessMineTime[playerid];

    PlayerGetMineID[playerid] = -1;
    PlayerStartProcessMine[playerid] = false;
    return 1;
}

LoadMapMine(){
    tmpobjid = CreateDynamicObject(751, 551.408203, 890.668579, -44.040660, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(747, 546.796691, 906.306457, -44.010929, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(16114, 511.076599, 876.791076, -43.203052, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(16114, 516.886474, 911.941223, -45.313049, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(751, 590.638061, 886.888610, -45.070629, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(751, 579.618347, 913.618347, -44.040660, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(845, 552.672790, 885.995971, -44.006198, 0.000000, 0.000000, 38.399997, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(845, 575.495117, 912.986206, -44.456192, 0.000000, 0.000000, -38.100009, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(837, 573.842590, 878.068908, -44.608470, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(837, 562.312744, 878.068908, -44.338497, 0.000000, 0.000000, 32.899997, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3463, 568.370666, 895.659667, -44.097335, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3463, 568.370666, 901.540771, -44.097335, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);  
}

LoadMine(){
    MineData[0][minePos][0] = 573.711547;
    MineData[0][minePos][1] = 897.748107;
    MineData[0][minePos][2] = -44.282138;

    MineData[1][minePos][0] = 573.711547;
    MineData[1][minePos][1] = 905.888183;
    MineData[1][minePos][2] = -44.282138;

    MineData[2][minePos][0] = 564.451538;
    MineData[2][minePos][1] = 901.738098;
    MineData[2][minePos][2] = -43.932144;

    MineData[3][minePos][0] = 564.451538;
    MineData[3][minePos][1] = 908.318481;
    MineData[3][minePos][2] = -43.892150;

    MineData[4][minePos][0] = 562.501403;
    MineData[4][minePos][1] = 895.478027;
    MineData[4][minePos][2] = -43.972141;

    MineData[5][minePos][0] = 555.151000;
    MineData[5][minePos][1] = 901.488342;
    MineData[5][minePos][2] = -43.972141;

    MineData[6][minePos][0] = 555.151000;
    MineData[6][minePos][1] = 909.258422;
    MineData[6][minePos][2] = -43.972141;

    MineData[7][minePos][0] = 570.641235;
    MineData[7][minePos][1] = 912.708923;
    MineData[7][minePos][2] = -43.992137;

    MineData[8][minePos][0] = 563.791503;
    MineData[8][minePos][1] = 887.088195;
    MineData[8][minePos][2] = -44.182132;

    MineData[9][minePos][0] = 573.981750;
    MineData[9][minePos][1] = 887.088195;
    MineData[9][minePos][2] = -44.182132;

    MineData[10][minePos][0] = 569.411376;
    MineData[10][minePos][1] = 880.178039;
    MineData[10][minePos][2] = -44.402114;

    MineData[11][minePos][0] = 582.671630;
    MineData[11][minePos][1] = 905.888183;
    MineData[11][minePos][2] = -44.572128;

    MineData[12][minePos][0] = 583.951721;
    MineData[12][minePos][1] = 896.287963;
    MineData[12][minePos][2] = -44.952106;

    MineData[13][minePos][0] = 591.831848;
    MineData[13][minePos][1] = 900.748046;
    MineData[13][minePos][2] = -45.532073;

    MineData[14][minePos][0] = 581.652160;
    MineData[14][minePos][1] = 887.088195;
    MineData[14][minePos][2] = -44.782093;

    for(new i=0; i<MAX_MINE; i++){
        MineData[i][mineStill] = true;
        MineData[i][mineUsed] = false;
        MineData[i][mineDelay] = 0;
        Mine_RenderRefresh(i);
        Mine_Refresh(i);
    }
}

Mine_Near(playerid, Float:radius = 2.0){
    for (new i = 0; i != MAX_MINE; i ++) {
        if(!MineData[i][mineStill]) continue;
        if(MineData[i][mineUsed]) continue;
        if (IsPlayerInRangeOfPoint(playerid, radius, MineData[i][minePos][0], MineData[i][minePos][1], MineData[i][minePos][2]+1.5))
		    return i;
    }
	return -1;
}

Mine_RenderRefresh(mineid){
    if(mineid != -1){
        if(MineData[mineid][mineStill]){
            MineData[mineid][mineObject] = CreateDynamicObject(MINE_OBJ, MineData[mineid][minePos][0], MineData[mineid][minePos][1], MineData[mineid][minePos][2], 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
            SetDynamicObjectMaterial(MineData[mineid][mineObject], 0, 10412, "hotel1", "gold128", 0x00000000);
        }
    }
}

Mine_Refresh(mineid){
    if(mineid != -1){
        if(MineData[mineid][mineStill]){
            MoveDynamicObject(MineData[mineid][mineObject], MineData[mineid][minePos][0], MineData[mineid][minePos][1], MineData[mineid][minePos][2], 3.0, 0.000000, 0.000000, 0.000000);
        }
        else{
            MoveDynamicObject(MineData[mineid][mineObject], MineData[mineid][minePos][0], MineData[mineid][minePos][1], MineData[mineid][minePos][2]-5.0, 3.0, 0.000000, 0.000000, 0.000000);
        }
    }
}

hook OnGameModeInit(){
    LoadMapMine();
    LoadMine();
    return 1;
}

timer ProcessMineUpdate[200](playerid){
    if(PlayerStartProcessMine[playerid]){
        new Float:currentValueProcessMine = GetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0]);
        if(currentValueProcessMine < 100.0){
            currentValueProcessMine++;
            SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], currentValueProcessMine);
        }
        else{
            ProcessMine_Success(playerid);
        }
    }
}

ProcessMine_Success(playerid){
    Reset_Mine(playerid);
    TogglePlayerControllable(playerid, 1);
    ClearAnimations(playerid);
    SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], 0.0);
    HidePlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    PlayerTextDrawHide(playerid, NewProgressText[playerid][0]);
    DestroyPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    PlayerTextDrawDestroy(playerid, NewProgressText[playerid][0]);

    PlayerInventory_Remove(playerid, "Stone", 1);
    GetItemMine(playerid);
    return 1;
}

timer MineUpdate[50](playerid){
    if(PlayerStartMine[playerid]){
        new Float:currentValueMine = GetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0]);
        if(currentValueMine < 100.0){
            currentValueMine++;
            SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], currentValueMine);
        }
        else{
            Mine_Success(playerid);
        }
    }
    return 1;
}

Mine_Success(playerid){
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    SetPlayerPos(playerid, x-1.0, y, z+1.5);

    MineData[PlayerGetMineID[playerid]][mineDelay] = DELAY_MINESPAWN;
    MineData[PlayerGetMineID[playerid]][mineStill] = false;
    Mine_Refresh(PlayerGetMineID[playerid]);

    Reset_Mine(playerid);
    TogglePlayerControllable(playerid, 1);
    ClearAnimations(playerid);
    SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], 0.0);
    HidePlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    PlayerTextDrawHide(playerid, NewProgressText[playerid][0]);
    DestroyPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    PlayerTextDrawDestroy(playerid, NewProgressText[playerid][0]);

    RemoveAttachedObject(playerid, 7);
    RemoveAttachedObject(playerid, 8);

    new stoneamount = jdzrandom(1, 2);
    new itemid = PlayerInventory_AddItem(playerid, "Stone", 3930, stoneamount);
    if(itemid == -1) return ErrorMsg(playerid, "ช่องเก็บของคุณเต็มไม่สามารถเก็บได้อีก");
    SendClientMessageEx(playerid, 0xFFB23BAA, "[การขุดแร่]:{FFFFFF} คุณได้รับ 'หิน (Stone)' + %d", stoneamount);
    return 1;
}

Start_PickingupMine(playerid, mineid){
    if(mineid != -1){
        MineData[mineid][mineUsed] = true;
        PlayerStartMine[playerid] = true;
        PlayerGetMineID[playerid] = mineid;
        TogglePlayerControllable(playerid, 0);
        LoadPlayerNewProgress(playerid);
        ShowPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
        SetPlayerProgressBarColour(playerid, NewProgressBar[playerid][0], 0xFFB23BAA);
        SetPlayerAttachedObject(playerid,7,18717,6,0.727000,0.238000,-2.481999,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
        SetPlayerAttachedObject(playerid,8,2711,6,0.285999,0.081999,-0.342999,13.399989,-33.200012,0.899989,1.846999,1.739000,5.334001);
        SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], 0.0);
        ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
        MineTime[playerid] = repeat MineUpdate(playerid);
    }
    return 1;
}

CMD:remine(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] >= 1338){
        for(new i=0; i<MAX_MINE; i++){
            Mine_Refresh(i);
        }
    }
    return 1;
}

ShowMenuProcessMine(playerid){
    new string[210];
    format(string, sizeof(string), "{FFB23B}คุณมีหินอยู่ '%d' ชิ้น\
    \n[ การแปรรูปคุณจะได้รับไอเท็มดังนี้ ]\
    \n1. เหล็ก\
    \n2. ทองแดง\
    \n3. ทอง\
    \n4. เพชร\
    \n{FFFFFF}( หากพร้อมแล้วให้กด 'เริ่ม' เพื่อทำการแปรรูป )", PlayerInventory_AllCount(playerid, "Stone"));
    Dialog_ShowEasy(playerid, ProcessMine, DIALOG_STYLE_MSGBOX, "การแปรรูปแร่หิน", string, "เริ่ม", "ปิด");
    return 1;
}

Dialog:ProcessMine(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(PlayerInventory_AllCount(playerid, "Stone") < 1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "{FF0000}คุณมี 'หิน' ไม่พอ", "ตกลง", "");
        StartProcessMine(playerid);
    }
    return 1;
}

StartProcessMine(playerid){
    PlayerStartProcessMine[playerid] = true;
    TogglePlayerControllable(playerid, 0);
    LoadPlayerNewProgress(playerid);
    ShowPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    SetPlayerProgressBarColour(playerid, NewProgressBar[playerid][0], 0xFFB23BAA);
    PlayerTextDrawSetString(playerid, NewProgressText[playerid][0], "Processing Mine");
    PlayerTextDrawShow(playerid, NewProgressText[playerid][0]);
    SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], 0.0);
    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
    ProcessMineTime[playerid] = repeat ProcessMineUpdate(playerid);
    return 1;
}

GetItemMine(playerid){
    new oreamount = jdzrandom(1, 2);
    new copperamount = jdzrandom(1, 2);
    new goldamount = jdzrandom(1, 2);
    new diamondrate = random(100);
    PlayerData[playerid][pStress]++;
    if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
    new itemore = PlayerInventory_AddItem(playerid, "Ore", 19941, oreamount);
    if(itemore == -1) return ErrorMsg(playerid, "คุณมีช่องเก็บของไม่พอที่จะเก็บ 'เหล็ก' แล้ว");
    SendClientMessageEx(playerid, COLOR_SERVER, "{23D101}| {FFFFFF}คุณได้รับ 'เหล็ก (Ore)' + '%d'", oreamount);

    new itemcopper = PlayerInventory_AddItem(playerid, "Copper", 19091, copperamount);
    if(itemcopper == -1) return ErrorMsg(playerid, "คุณมีช่องเก็บของไม่พอที่จะเก็บ 'ทองแดง' แล้ว");
    SendClientMessageEx(playerid, COLOR_SERVER, "{23D101}| {FFFFFF}คุณได้รับ 'ทองแดง (Copper)' + '%d'", copperamount);

    new itemgold = PlayerInventory_AddItem(playerid, "Gold", 19092, goldamount);
    if(itemgold == -1) return ErrorMsg(playerid, "คุณมีช่องเก็บของไม่พอที่จะเก็บ 'ทอง' แล้ว");
    SendClientMessageEx(playerid, COLOR_SERVER, "{23D101}| {FFFFFF}คุณได้รับ 'ทอง (Gold)' + '%d'", goldamount);

    if(diamondrate >= 73 && diamondrate <= 78){
        new itemdiamond = PlayerInventory_AddItem(playerid, "Diamond", 19090, 1);
        if(itemdiamond == -1) return ErrorMsg(playerid, "คุณมีช่องเก็บของไม่พอที่จะเก็บ 'เพชร' แล้ว");
        SendClientMessageEx(playerid, COLOR_SERVER, "{23D101}| {FFFFFF}คุณได้รับ 'เพชร (Diamond)' + '%d'", 1);
    }
    return 1;
}

//-2258.5933,549.5543,35.0156
ShowDialogSellMine(playerid){
    Dialog_ShowEasy(playerid, SellMine, DIALOG_STYLE_LIST, "ตลาดแร่", "- ทองแดง\n- ทอง\n- เพชร", "เลือก", "ยกเลิก");
    return 1;
}

Dialog:SellMine(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[128];
        switch(listitem){
            case 0:{
                format(string, sizeof(string), "คุณมี 'ทองแดง' อยู่จำนวน '%d'\
                \nกรอกจำนวนที่คุณต้องการจะขาย: ", PlayerInventory_AllCount(playerid, "Copper"));
                Dialog_ShowEasy(playerid, SellCopper, DIALOG_STYLE_INPUT, "ขายทองแดง", string, "ขาย", "ยกเลิก");
            }
            case 1:{
                format(string, sizeof(string), "คุณมี 'ทอง' อยู่จำนวน '%d'\
                \nกรอกจำนวนที่คุณต้องการจะขาย: ", PlayerInventory_AllCount(playerid, "Gold"));
                Dialog_ShowEasy(playerid, SellGold, DIALOG_STYLE_INPUT, "ขายทอง", string, "ขาย", "ยกเลิก");
            }
            case 2:{
                format(string, sizeof(string), "คุณมี 'เพชร' อยู่จำนวน '%d'\
                \nกรอกจำนวนที่คุณต้องการจะขาย: ", PlayerInventory_AllCount(playerid, "Diamond"));
                Dialog_ShowEasy(playerid, SellDiamond, DIALOG_STYLE_INPUT, "ขายเพชร", string, "ขาย", "ยกเลิก");
            }
        }
    }
    return 1;
}

Dialog:SellCopper(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new string[128];
        if(amount <= 0){
            format(string, sizeof(string), "คุณมี 'ทองแดง' อยู่จำนวน '%d'\
            \nกรอกจำนวนที่คุณต้องการจะขาย: ", PlayerInventory_AllCount(playerid, "Copper"));
            Dialog_ShowEasy(playerid, SellCopper, DIALOG_STYLE_INPUT, "ขายทองแดง", string, "ขาย", "ยกเลิก");
            return 1;
        }

        if(amount > PlayerInventory_AllCount(playerid, "Copper")){
            format(string, sizeof(string), "* คุณมีจำนวนทองแดงไม่พอ *\nคุณมี 'ทองแดง' อยู่จำนวน '%d'\
            \nกรอกจำนวนที่คุณต้องการจะขาย: ", PlayerInventory_AllCount(playerid, "Copper"));
            Dialog_ShowEasy(playerid, SellCopper, DIALOG_STYLE_INPUT, "ขายทองแดง", string, "ขาย", "ยกเลิก");
            return 1;
        }

        new price = COPPER_PRICE * amount;
        PlayerInventory_Remove(playerid, "Copper", amount);
        GiveMoney(playerid, price, "Sell Copper");
        SendClientMessageEx(playerid, COLOR_YELLOW, "+ คุณได้ขาย 'ทองแดง' จำนวน '%d' และได้รับเงิน '%s'", amount, FormatNumber(price));
    }
    return 1;
}

Dialog:SellGold(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new string[128];
        if(amount <= 0){
            format(string, sizeof(string), "คุณมี 'ทอง' อยู่จำนวน '%d'\
            \nกรอกจำนวนที่คุณต้องการจะขาย: ", PlayerInventory_AllCount(playerid, "Gold"));
            Dialog_ShowEasy(playerid, SellGold, DIALOG_STYLE_INPUT, "ขายทอง", string, "ขาย", "ยกเลิก");
            return 1;
        }

        if(amount > PlayerInventory_AllCount(playerid, "Gold")){
            format(string, sizeof(string), "* คุณมีจำนวนทองไม่พอ *\nคุณมี 'ทอง' อยู่จำนวน '%d'\
            \nกรอกจำนวนที่คุณต้องการจะขาย: ", PlayerInventory_AllCount(playerid, "Gold"));
            Dialog_ShowEasy(playerid, SellGold, DIALOG_STYLE_INPUT, "ขายทอง", string, "ขาย", "ยกเลิก");
            return 1;
        }

        new price = GOLDMINE_PRICE * amount;
        PlayerInventory_Remove(playerid, "Gold", amount);
        GiveMoney(playerid, price, "Sell Gold");
        SendClientMessageEx(playerid, COLOR_YELLOW, "+ คุณได้ขาย 'ทอง' จำนวน '%d' และได้รับเงิน '%s'", amount, FormatNumber(price));
    }
    return 1;
}

Dialog:SellDiamond(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new string[128];
        if(amount <= 0){
            format(string, sizeof(string), "คุณมี 'เพชร' อยู่จำนวน '%d'\
            \nกรอกจำนวนที่คุณต้องการจะขาย: ", PlayerInventory_AllCount(playerid, "Diamond"));
            Dialog_ShowEasy(playerid, SellDiamond, DIALOG_STYLE_INPUT, "ขายเพชร", string, "ขาย", "ยกเลิก");
            return 1;
        }

        if(amount > PlayerInventory_AllCount(playerid, "Diamond")){
            format(string, sizeof(string), "* คุณมีจำนวนเพชรไม่พอ *\nคุณมี 'เพชร' อยู่จำนวน '%d'\
            \nกรอกจำนวนที่คุณต้องการจะขาย: ", PlayerInventory_AllCount(playerid, "Diamond"));
            Dialog_ShowEasy(playerid, SellDiamond, DIALOG_STYLE_INPUT, "ขายเพชร", string, "ขาย", "ยกเลิก");
            return 1;
        }

        new price = DIAMOND_PRICE * amount;
        PlayerInventory_Remove(playerid, "Diamond", amount);
        GiveMoney(playerid, price, "Sell Diamond");
        SendClientMessageEx(playerid, COLOR_YELLOW, "+ คุณได้ขาย 'เพชร' จำนวน '%d' และได้รับเงิน '%s'", amount, FormatNumber(price));
    }
    return 1;
}