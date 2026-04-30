#if defined _inc_impl
	#undef _inc_impl
#endif

LoadTextDrawGaCha(playerid){
    GaCha[playerid][0] = CreatePlayerTextDraw(playerid, 319.000000, 157.000000, "_");
    PlayerTextDrawFont(playerid, GaCha[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][0], 0.600000, 17.800003);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][0], 298.500000, 521.000000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][0], 2);
    PlayerTextDrawColor(playerid, GaCha[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][0], 200);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][0], 0);

    GaCha[playerid][1] = CreatePlayerTextDraw(playerid, 313.000000, 130.000000, "Random Box");
    PlayerTextDrawFont(playerid, GaCha[playerid][1], 2);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][1], 0.441666, 2.149998);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][1], 400.000000, 192.000000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][1], 2);
    PlayerTextDrawColor(playerid, GaCha[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][1], 130);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][1], 0);

    GaCha[playerid][2] = CreatePlayerTextDraw(playerid, 61.000000, 163.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, GaCha[playerid][2], 5);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][2], 71.500000, 77.000000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][2], 1);
    PlayerTextDrawColor(playerid, GaCha[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][2], GACHA_NORMAL);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][2], 1687547391);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, GaCha[playerid][2], 18631);
    PlayerTextDrawSetPreviewRot(playerid, GaCha[playerid][2], -32.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, GaCha[playerid][2], 1, 1);

    GaCha[playerid][3] = CreatePlayerTextDraw(playerid, 135.000000, 163.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, GaCha[playerid][3], 5);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][3], 71.500000, 77.000000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][3], 1);
    PlayerTextDrawColor(playerid, GaCha[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][3], GACHA_NORMAL);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][3], 1687547391);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, GaCha[playerid][3], 18631);
    PlayerTextDrawSetPreviewRot(playerid, GaCha[playerid][3], -32.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, GaCha[playerid][3], 1, 1);

    GaCha[playerid][4] = CreatePlayerTextDraw(playerid, 209.000000, 163.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, GaCha[playerid][4], 5);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][4], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][4], 71.500000, 77.000000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][4], 1);
    PlayerTextDrawColor(playerid, GaCha[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][4], GACHA_NORMAL);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][4], 1687547391);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][4], 0);
    PlayerTextDrawSetPreviewModel(playerid, GaCha[playerid][4], 18631);
    PlayerTextDrawSetPreviewRot(playerid, GaCha[playerid][4], -32.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, GaCha[playerid][4], 1, 1);

    GaCha[playerid][5] = CreatePlayerTextDraw(playerid, 283.000000, 163.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, GaCha[playerid][5], 5);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][5], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][5], 71.500000, 77.000000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][5], 1);
    PlayerTextDrawColor(playerid, GaCha[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][5], GACHA_NORMAL);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][5], 1687547391);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][5], 0);
    PlayerTextDrawSetPreviewModel(playerid, GaCha[playerid][5], 18631);
    PlayerTextDrawSetPreviewRot(playerid, GaCha[playerid][5], -32.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, GaCha[playerid][5], 1, 1);

    GaCha[playerid][6] = CreatePlayerTextDraw(playerid, 357.000000, 163.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, GaCha[playerid][6], 5);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][6], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][6], 71.500000, 77.000000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][6], 1);
    PlayerTextDrawColor(playerid, GaCha[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][6], GACHA_NORMAL);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][6], 1687547391);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][6], 0);
    PlayerTextDrawSetPreviewModel(playerid, GaCha[playerid][6], 18631);
    PlayerTextDrawSetPreviewRot(playerid, GaCha[playerid][6], -32.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, GaCha[playerid][6], 1, 1);

    GaCha[playerid][7] = CreatePlayerTextDraw(playerid, 431.000000, 163.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, GaCha[playerid][7], 5);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][7], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][7], 71.500000, 77.000000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][7], 1);
    PlayerTextDrawColor(playerid, GaCha[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][7], GACHA_NORMAL);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][7], 1687547391);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][7], 0);
    PlayerTextDrawSetPreviewModel(playerid, GaCha[playerid][7], 18631);
    PlayerTextDrawSetPreviewRot(playerid, GaCha[playerid][7], -32.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, GaCha[playerid][7], 1, 1);

    GaCha[playerid][8] = CreatePlayerTextDraw(playerid, 505.000000, 163.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, GaCha[playerid][8], 5);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][8], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][8], 71.500000, 77.000000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][8], 1);
    PlayerTextDrawColor(playerid, GaCha[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][8], GACHA_NORMAL);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][8], 1687547391);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][8], 0);
    PlayerTextDrawSetPreviewModel(playerid, GaCha[playerid][8], 18631);
    PlayerTextDrawSetPreviewRot(playerid, GaCha[playerid][8], -32.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, GaCha[playerid][8], 1, 1);

    GaCha[playerid][9] = CreatePlayerTextDraw(playerid, 318.000000, 165.000000, "_");
    PlayerTextDrawFont(playerid, GaCha[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][9], 0.600000, 8.050000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][9], 298.500000, -5.000000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][9], 2);
    PlayerTextDrawColor(playerid, GaCha[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][9], -1);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][9], 0);

    GaCha[playerid][10] = CreatePlayerTextDraw(playerid, 317.000000, 282.000000, "Open");
    PlayerTextDrawFont(playerid, GaCha[playerid][10], 2);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][10], 0.258332, 1.750000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][10], 16.500000, 68.500000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][10], 1);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][10], 2);
    PlayerTextDrawColor(playerid, GaCha[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][10], 9109704);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][10], 1);

    GaCha[playerid][11] = CreatePlayerTextDraw(playerid, 561.000000, 139.000000, "CLOSE");
    PlayerTextDrawFont(playerid, GaCha[playerid][11], 2);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][11], 0.174998, 1.150000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][11], 16.500000, 37.500000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][11], 1);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][11], 2);
    PlayerTextDrawColor(playerid, GaCha[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][11], -16777016);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][11], 1);

    GaCha[playerid][12] = CreatePlayerTextDraw(playerid, 101.000000, 285.000000, "Key: 1");
    PlayerTextDrawFont(playerid, GaCha[playerid][12], 2);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][12], 0.312500, 1.500000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][12], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][12], 1);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][12], 1);
    PlayerTextDrawColor(playerid, GaCha[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][12], 50);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][12], 0);

    GaCha[playerid][13] = CreatePlayerTextDraw(playerid, 57.000000, 264.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, GaCha[playerid][13], 5);
    PlayerTextDrawLetterSize(playerid, GaCha[playerid][13], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, GaCha[playerid][13], 53.000000, 57.500000);
    PlayerTextDrawSetOutline(playerid, GaCha[playerid][13], 0);
    PlayerTextDrawSetShadow(playerid, GaCha[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, GaCha[playerid][13], 1);
    PlayerTextDrawColor(playerid, GaCha[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][13], 0);
    PlayerTextDrawBoxColor(playerid, GaCha[playerid][13], 255);
    PlayerTextDrawUseBox(playerid, GaCha[playerid][13], 0);
    PlayerTextDrawSetProportional(playerid, GaCha[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, GaCha[playerid][13], 0);
    PlayerTextDrawSetPreviewModel(playerid, GaCha[playerid][13], 11746);
    PlayerTextDrawSetPreviewRot(playerid, GaCha[playerid][13], 18.000000, 92.000000, -24.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, GaCha[playerid][13], 1, 1);
}

forward GaCha_Load();
public GaCha_Load(){
    new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_GACHA)
	{
	    GaChaData[i][gachaEx] = true;

	    cache_get_value_name_int(i, "gachaID", GaChaData[i][gachaID]);
	    cache_get_value_name_int(i, "gachaType", GaChaData[i][gachaType]);
        cache_get_value_name_int(i, "gachaItem1", GaChaData[i][gachaItem][0]);
        cache_get_value_name_int(i, "gachaItem2", GaChaData[i][gachaItem][1]);
        cache_get_value_name_int(i, "gachaItem3", GaChaData[i][gachaItem][2]);
        cache_get_value_name_int(i, "gachaItem4", GaChaData[i][gachaItem][3]);
        cache_get_value_name_int(i, "gachaItem5", GaChaData[i][gachaItem][4]);
        cache_get_value_name_int(i, "gachaItem6", GaChaData[i][gachaItem][5]);
        cache_get_value_name_int(i, "gachaItem7", GaChaData[i][gachaItem][6]);

        cache_get_value_name_int(i, "gachaItemAmount1", GaChaData[i][gachaItemAmount][0]);
        cache_get_value_name_int(i, "gachaItemAmount2", GaChaData[i][gachaItemAmount][1]);
        cache_get_value_name_int(i, "gachaItemAmount3", GaChaData[i][gachaItemAmount][2]);
        cache_get_value_name_int(i, "gachaItemAmount4", GaChaData[i][gachaItemAmount][3]);
        cache_get_value_name_int(i, "gachaItemAmount5", GaChaData[i][gachaItemAmount][4]);
        cache_get_value_name_int(i, "gachaItemAmount6", GaChaData[i][gachaItemAmount][5]);
        cache_get_value_name_int(i, "gachaItemAmount7", GaChaData[i][gachaItemAmount][6]);

        cache_get_value_name_int(i, "gachaItemLevel1", GaChaData[i][gachaItemLevel][0]);
        cache_get_value_name_int(i, "gachaItemLevel2", GaChaData[i][gachaItemLevel][1]);
        cache_get_value_name_int(i, "gachaItemLevel3", GaChaData[i][gachaItemLevel][2]);
        cache_get_value_name_int(i, "gachaItemLevel4", GaChaData[i][gachaItemLevel][3]);
        cache_get_value_name_int(i, "gachaItemLevel5", GaChaData[i][gachaItemLevel][4]);
        cache_get_value_name_int(i, "gachaItemLevel6", GaChaData[i][gachaItemLevel][5]);
        cache_get_value_name_int(i, "gachaItemLevel7", GaChaData[i][gachaItemLevel][6]);

        Count_GaCha++;
	}
	printf("(( [MYSQL]: Load %d GaCha Successfully ))", Count_GaCha);
	return 1;
}

ResetGaCha(playerid){
    IsOpeningGaCha[playerid] = false;
    KillTimer(GaChaTime[playerid]);
    GaChaTime[playerid] = 0;
    GaChaPoint[playerid] = 0;
    GetLastColor[playerid] = 0;
    GaChaMaxPoint[playerid] = 0;
    StartRandom[playerid] = 0;
    GetLastItem[playerid] = 0;
    GetValueItem[playerid] = 0;
    GetLastItemAmount[playerid] = 0;
    GetLastItemLevel[playerid] = 0;
    GetValueItemAmount[playerid] = 0;
    GetValueItemLevel[playerid] = 0;
    PlayerGetBoxType[playerid] = 0;
    return 1;
}

forward ShowGaChaBox(playerid);
public ShowGaChaBox(playerid){

    LoadTextDrawGaCha(playerid);

    new string[128], check_key[64], count_key;

    format(string, sizeof(string), "%s", BoxNameData[playerid][boxName]);
    PlayerTextDrawSetString(playerid, GaCha[playerid][1], string);

    format(check_key, sizeof(check_key), "%s Key", BoxNameData[playerid][boxName]);

    if(PlayerInventory_HasItem(playerid, check_key)) count_key = PlayerInventory_AllCount(playerid, check_key);

    format(string, sizeof(string), "Key: %s", FormatNumberNotMoney(count_key));
    PlayerTextDrawSetString(playerid, GaCha[playerid][12], string);

    if(!strcmp(BoxNameData[playerid][boxName], "Marry Christmas Box", true)){
        PlayerTextDrawBoxColor(playerid, GaCha[playerid][0], 0xFF4F4FAA);
    }

    //Box
    /*if(!strcmp(BoxNameData[playerid][boxName], "Chinese NW Box", true)){
        PlayerTextDrawBoxColor(playerid, GaCha[playerid][0], 0xFF433DAA);
    }
    if(!strcmp(BoxNameData[playerid][boxName], "Weapon Box", true)){
        PlayerTextDrawBoxColor(playerid, GaCha[playerid][0], 0x353535AA);
    }
    if(!strcmp(BoxNameData[playerid][boxName], "Songkran Box", true)){
        PlayerTextDrawBoxColor(playerid, GaCha[playerid][0], 0x0093FFAA);
    }*/

    for(new i=0; i<14; i++){
        PlayerTextDrawShow(playerid, GaCha[playerid][i]);
    }

    IsOpeningGaCha[playerid] = true;
    SelectTextDraw(playerid, 0x0FFF00AA);
    TogglePlayerControllable(playerid, 0);
    return 1;
}

HideGaChaBox(playerid){
    for(new i=0; i<14; i++){
        PlayerTextDrawHide(playerid, GaCha[playerid][i]);
        PlayerTextDrawDestroy(playerid, GaCha[playerid][i]);
    }
    IsOpeningGaCha[playerid] = false;
    CancelSelectTextDraw(playerid);
    ResetGaCha(playerid);
    TogglePlayerControllable(playerid, 1);
    return 1;
}

SetBoxGaChaColor(playerid){
    GaChaColor[playerid][2] = GACHA_NORMAL;
    GaChaColor[playerid][3] = GACHA_NORMAL;
    GaChaColor[playerid][4] = GACHA_NORMAL;
    GaChaColor[playerid][5] = GACHA_RANK1;
    GaChaColor[playerid][6] = GACHA_NORMAL;
    GaChaColor[playerid][7] = GACHA_NORMAL;
    GaChaColor[playerid][8] = GACHA_RARE;
    return 1;
}

CheckConfirmRandomBox(playerid){
    if(IsOpeningGaCha[playerid]){
        new check_key[64], count_key, caption[128], message[500];

        format(check_key, sizeof(check_key), "%s Key", BoxNameData[playerid][boxName]);

        if(PlayerInventory_HasItem(playerid, check_key)) count_key = PlayerInventory_AllCount(playerid, check_key);

        if(count_key <= 0)
            return ErrorMsg(playerid, "คุณไม่มีกุญแจสำหรับกล่องนี้");

        format(caption, sizeof(caption), "%s", BoxNameData[playerid][boxName]);
        format(message, sizeof(message), "{FFFFFF}- คุณแน่ใจแล้วหรือไม่ว่าที่จะเปิดกล่องนี้?");
        Dialog_ShowEasy(playerid, ConfirmRandom, DIALOG_STYLE_MSGBOX, caption, message, "ตกลง", "ยกเลิก");
    }
    return 1;
}

Dialog:ConfirmRandom(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){

        new count = 0;
        for(new i=0; i<MAX_INVENTORYPLAYERS; i++) if(Inventory_Player[playerid][i][itemHave]){
            count++;
            if(i >= 107) break;
        }

        if(count + 1 >= PlayerData[playerid][pMaxItem]) return ErrorMsg(playerid, "คุณต้องเคลียร์กระเป๋าของคุณให้ว่างก่อน");

        StartRandomGaCha(playerid);
    }
    return 1;
}

StartRandomGaCha(playerid){
    if(IsOpeningGaCha[playerid]){

        new string[128], check_key[64], count_key;

        format(check_key, sizeof(check_key), "%s Key", BoxNameData[playerid][boxName]);

        if(PlayerInventory_HasItem(playerid, check_key)) count_key = PlayerInventory_AllCount(playerid, check_key);

        if(count_key <= 0)
            return ErrorMsg(playerid, "คุณไม่มีกุญแจสำหรับกล่องนี้");

        SetBoxGaChaColor(playerid);
        for(new i=2; i<9; i++){
            PlayerTextDrawHide(playerid, GaCha[playerid][i]);
        }

        PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][2], GaChaColor[playerid][2]);
        PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][3], GaChaColor[playerid][3]);
        PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][4], GaChaColor[playerid][4]);
        PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][5], GaChaColor[playerid][5]);
        PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][6], GaChaColor[playerid][6]);
        PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][7], GaChaColor[playerid][7]);
        PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][8], GaChaColor[playerid][8]);

        new boxid;
        for(new j=0; j<MAX_GACHA; j++) if(GaChaData[j][gachaEx]){
            if(GaChaData[j][gachaType] == PlayerGetBoxType[playerid]){
                boxid = j;
                break;
            }
        }

        for(new i=2; i<9; i++){
            GaChaGetItem[playerid][i] = GaChaData[boxid][gachaItem][i-2];
            GaChaGetItemAmount[playerid][i] = GaChaData[boxid][gachaItemAmount][i-2];
            GaChaGetItemLevel[playerid][i] = GaChaData[boxid][gachaItemLevel][i-2];
        }

        for(new i=2; i<9; i++){
            PlayerTextDrawSetPreviewModel(playerid, GaCha[playerid][i], GaChaGetItem[playerid][i]);
            PlayerTextDrawShow(playerid, GaCha[playerid][i]);
        }

        GaChaMaxPoint[playerid] = 0;
        GaChaPoint[playerid] = 0;

        //gachaItem4 = สีฟ้า
        //gachaItem5 = สีเทาหายาก 1
        //gachaItem6 = สีเทาหายาก 2
        //gachaItem7 = สีฟ้า

        new rand = random(3000);
        //printf("%d",rand);
        if((rand >= 1200 && rand <= 1250)||(rand >= 901 && rand <= 930)) GaChaMaxPoint[playerid] = 350; // ฟ้า
        else if(rand >= 1801 && rand <= 1810) GaChaMaxPoint[playerid] = 310; // ทอง
        else if(rand >= 2401 && rand <= 2480) GaChaMaxPoint[playerid] = 300; // ของเทายาก 1
        else if(rand >= 2701 && rand <= 2780) GaChaMaxPoint[playerid] = 360; // ของเทายาก 2
        else{
            new x = modgacha(rand);
            if((x%3)==0) GaChaMaxPoint[playerid] = 330;
            else if((x%2)==0) GaChaMaxPoint[playerid] = 320;
            else GaChaMaxPoint[playerid] = 340;
        }

        format(string, sizeof(string), "ผู้เล่น %s ได้เปิดกล่องสุ่มกาชาและสุ่มได้ MaxPoint = %s", ReturnRoleplayName(playerid), FormatNumberNotMoney(GaChaMaxPoint[playerid]));
        SendAdminsMessage(1, COLOR_GRAY, string);
        Log_Write("logs/opengacha.txt", "[%s] %s Open Maxpoint =  %s", ReturnDate(), ReturnRoleplayName(playerid), FormatNumberNotMoney(GaChaMaxPoint[playerid]));

        StartRandom[playerid] = true;

        PlayerTextDrawHide(playerid, GaCha[playerid][12]);

        if(PlayerInventory_AllCount(playerid, check_key) >= 1){
            PlayerInventory_Remove(playerid, check_key, 1);
        }

        count_key--;

        PlayerInventory_Remove(playerid, BoxNameData[playerid][boxName], 1);

        format(string, sizeof(string), "Key: %s", FormatNumberNotMoney(count_key));
        PlayerTextDrawSetString(playerid, GaCha[playerid][12], string);

        PlayerTextDrawShow(playerid, GaCha[playerid][12]);

        GaChaTime[playerid] = SetTimerEx("GaChaOpening", 100, 0, "i", playerid);
    }
    return 1;
}

modgacha(rand){
	new End = 0;
	End += rand/(1000);
	rand = rand%1000;
	
	End += rand/(100);
	rand = rand%100;
	
	End += rand/(10);
	rand = rand%10;
	
	End += rand;
    return End;
}

forward GaChaOpening(playerid);
public GaChaOpening(playerid){
    if(GaChaPoint[playerid] < GaChaMaxPoint[playerid]){
        for(new i=2; i<9; i++){
            PlayerTextDrawHide(playerid, GaCha[playerid][i]);
            if(i == 2){
                GetLastColor[playerid] = GaChaColor[playerid][i];
                GetLastItem[playerid] = GaChaGetItem[playerid][i];
                GetLastItemAmount[playerid] = GaChaGetItemAmount[playerid][i];
                GetLastItemLevel[playerid] = GaChaGetItemLevel[playerid][i];
            }
            GaChaColor[playerid][i] = GaChaColor[playerid][i+1];
            GaChaGetItem[playerid][i] = GaChaGetItem[playerid][i+1];
            GaChaGetItemAmount[playerid][i] = GaChaGetItemAmount[playerid][i+1];
            GaChaGetItemLevel[playerid][i] = GaChaGetItemLevel[playerid][i+1];
            if(i >= 8){
                GaChaColor[playerid][i] = GetLastColor[playerid];
                GaChaGetItem[playerid][i] = GetLastItem[playerid];
                GaChaGetItemAmount[playerid][i] = GetLastItemAmount[playerid];
                GaChaGetItemLevel[playerid][i] = GetLastItemLevel[playerid];
            }
            PlayerTextDrawSetPreviewModel(playerid, GaCha[playerid][i], GaChaGetItem[playerid][i]);
            PlayerTextDrawBackgroundColor(playerid, GaCha[playerid][i], GaChaColor[playerid][i]);
            PlayerTextDrawShow(playerid, GaCha[playerid][i]);
        }
        PlayerPlaySound(playerid,1135,0.0,0.0,0.0);
        GaChaPoint[playerid] += 10;
        if(GaChaPoint[playerid] < 190) GaChaTime[playerid] = SetTimerEx("GaChaOpening", 100, 0, "i", playerid);
        else GaChaTime[playerid] = SetTimerEx("GaChaOpening", 500, 0, "i", playerid);
    }
    else if(GaChaPoint[playerid] >= GaChaMaxPoint[playerid]){
        KillTimer(GaChaTime[playerid]);
        PlayerData[playerid][pTotalOpenBox]++;

        for(new i=2; i<9; i++){
            if(i == 5){
                GetValueItem[playerid] = GaChaGetItem[playerid][i];
                GetValueItemAmount[playerid] = GaChaGetItemAmount[playerid][i];
                GetValueItemLevel[playerid] = GaChaGetItemLevel[playerid][i];
            }
        }

        if(GetValueItem[playerid] >= 0 && GetValueItem[playerid] <= 311){
            new stringskin[32];
            format(stringskin, sizeof(stringskin), "%d", GetValueItem[playerid]);
            new id = PlayerInventory_AddItem(playerid, stringskin, 2384, GetValueItemAmount[playerid]);
            if(id == -1) return ErrorMsg(playerid, "ไอเท็มของคุณเท็มไม่สามารถเก็บได้");
            SendClientMessageEx(playerid, COLOR_YELLOW, "[กล่องสุ่ม]: คุณได้รับไอเท็ม '%d' จำนวน %s ชิ้น", GetValueItem[playerid], FormatNumberNotMoney(GetValueItemAmount[playerid]));
        }
        else{
            new getindexweapon = -1;
            for (new i = 0; i < sizeof(WeaponData); i ++) {
                if(GetValueItem[playerid] == WeaponData[i][weaponModel]){
                    getindexweapon = i;
                }
            }

            // เพิ่มสำหรับได้ไอเท็มแต่งตัว

            if(getindexweapon != -1){
                new id = PlayerInventory_AddItem(playerid, WeaponData[getindexweapon][weaponName], WeaponData[getindexweapon][weaponModel], GetValueItemAmount[playerid], 0, GetValueItemLevel[playerid]);
                if(id == -1) return ErrorMsg(playerid, "ไอเท็มของคุณเท็มไม่สามารถเก็บได้");
                SendClientMessageEx(playerid, COLOR_YELLOW, "[กล่องสุ่ม]: คุณได้รับไอเท็ม '%s' (ระดับตีบวก: %d) จำนวน %s ชิ้น", WeaponData[getindexweapon][weaponName], GetValueItemLevel[playerid], FormatNumberNotMoney(GetValueItemAmount[playerid]));
            }
            else{
                new getindexitem = -1;
                for (new i = 0; i < sizeof(Item_Data); i ++) if(Item_Data[i][itemModel] == GetValueItem[playerid]){
                    getindexitem = i;
                }

                if(getindexitem != -1){
                    if(Item_Data[getindexitem][itemModel] == 1277) format(Item_Data[getindexitem][itemName], 64, "Weapon Card");
                    new id = PlayerInventory_AddItem(playerid, Item_Data[getindexitem][itemName], Item_Data[getindexitem][itemModel], GetValueItemAmount[playerid], 0, 0);
                    if(id == -1) return ErrorMsg(playerid, "ไอเท็มของคุณเท็มไม่สามารถเก็บได้");
                    SendClientMessageEx(playerid, COLOR_YELLOW, "[กล่องสุ่ม]: คุณได้รับไอเท็ม '%s' จำนวน %s ชิ้น", Item_Data[getindexitem][itemName], FormatNumberNotMoney(GetValueItemAmount[playerid]));
                }
                else{
                    new gethatitem = -1, getglassesitem = -1, getbodyitem = -1, gethandsitem = -1;
                    for (new i=0; i < MAX_ACC; i++) {
                        if (GetValueItem[playerid] == HatDataItem[i][hatitemModel]){
                            gethatitem = i;
                            break;
                        }
                        if (GetValueItem[playerid] == GlassesDataItem[i][glassesitemModel]){
                            getglassesitem = i;
                            break;
                        }
                        if (GetValueItem[playerid] == BodyDataItem[i][bodyitemModel]){
                            getbodyitem = i;
                            break;
                        }
                        if (GetValueItem[playerid] == HandsDataItem[i][handsitemModel]){
                            gethandsitem = i;
                            break;
                        }
                    }

                    if(gethatitem != -1){
                        new id = PlayerInventory_AddItem(playerid, HatDataItem[gethatitem][hatitemName], HatDataItem[gethatitem][hatitemModel], GetValueItemAmount[playerid], 0, 0);
                        if(id == -1) return ErrorMsg(playerid, "ไอเท็มของคุณเท็มไม่สามารถเก็บได้");
                        SendClientMessageEx(playerid, COLOR_YELLOW, "[กล่องสุ่ม]: คุณได้รับไอเท็ม '%s' จำนวน %s ชิ้น", HatDataItem[gethatitem][hatitemName], FormatNumberNotMoney(GetValueItemAmount[playerid]));
                    }

                    if(getglassesitem != -1){
                        new id = PlayerInventory_AddItem(playerid, GlassesDataItem[getglassesitem][glassesitemName], GlassesDataItem[getglassesitem][glassesitemModel], GetValueItemAmount[playerid], 0, 0);
                        if(id == -1) return ErrorMsg(playerid, "ไอเท็มของคุณเท็มไม่สามารถเก็บได้");
                        SendClientMessageEx(playerid, COLOR_YELLOW, "[กล่องสุ่ม]: คุณได้รับไอเท็ม '%s' จำนวน %s ชิ้น", GlassesDataItem[getglassesitem][glassesitemName], FormatNumberNotMoney(GetValueItemAmount[playerid]));
                    }

                    if(getbodyitem != -1){
                        new id = PlayerInventory_AddItem(playerid, BodyDataItem[getbodyitem][bodyitemName], BodyDataItem[getbodyitem][bodyitemModel], GetValueItemAmount[playerid], 0, 0);
                        if(id == -1) return ErrorMsg(playerid, "ไอเท็มของคุณเท็มไม่สามารถเก็บได้");
                        SendClientMessageEx(playerid, COLOR_YELLOW, "[กล่องสุ่ม]: คุณได้รับไอเท็ม '%s' จำนวน %s ชิ้น", BodyDataItem[getbodyitem][bodyitemName], FormatNumberNotMoney(GetValueItemAmount[playerid]));
                    }

                    if(gethandsitem != -1){
                        new id = PlayerInventory_AddItem(playerid, HandsDataItem[gethandsitem][handsitemName], HandsDataItem[gethandsitem][handsitemModel], GetValueItemAmount[playerid], 0, 0);
                        if(id == -1) return ErrorMsg(playerid, "ไอเท็มของคุณเท็มไม่สามารถเก็บได้");
                        SendClientMessageEx(playerid, COLOR_YELLOW, "[กล่องสุ่ม]: คุณได้รับไอเท็ม '%s' จำนวน %s ชิ้น", HandsDataItem[gethandsitem][handsitemName], FormatNumberNotMoney(GetValueItemAmount[playerid]));
                    }
                }
            }
        }

        
        GetValueItem[playerid] = 0;
        GetValueItemAmount[playerid] = 0;

        GaChaTime[playerid] = 0;
        GaChaPoint[playerid] = 0;
        GetLastColor[playerid] = 0;
        GaChaMaxPoint[playerid] = 0;
        StartRandom[playerid] = 0;
        GetLastItem[playerid] = 0;

        if(PlayerInventory_AllCount(playerid, BoxNameData[playerid][boxName]) <= 0){
            SetTimerEx("SetTimeHideGaCha", 1000, false, "i", playerid);
        }

    }
    return 1;
}

forward SetTimeHideGaCha(playerid);
public SetTimeHideGaCha(playerid){
    HideGaChaBox(playerid);
    return 1;
}

CMD:gacharefresh(playerid, params[]){
    if(PlayerData[playerid][pAdmin] >= 1338){
        if(LoggedIn[playerid]){
            Count_GaCha = 0;

            for(new i=0; i<MAX_GACHA; i++){
                if(GaChaData[i][gachaEx]){
                    GaChaData[i][gachaEx] = false;

                    GaChaData[i][gachaType] = 0;

                    GaChaData[i][gachaItem][0] = 0;
                    GaChaData[i][gachaItem][1] = 0;
                    GaChaData[i][gachaItem][2] = 0;
                    GaChaData[i][gachaItem][3] = 0;
                    GaChaData[i][gachaItem][4] = 0;
                    GaChaData[i][gachaItem][5] = 0;
                    GaChaData[i][gachaItem][6] = 0;

                    GaChaData[i][gachaItemAmount][0] = 0;
                    GaChaData[i][gachaItemAmount][1] = 0;
                    GaChaData[i][gachaItemAmount][2] = 0;
                    GaChaData[i][gachaItemAmount][3] = 0;
                    GaChaData[i][gachaItemAmount][4] = 0;
                    GaChaData[i][gachaItemAmount][5] = 0;
                    GaChaData[i][gachaItemAmount][6] = 0;
                }
            }

            mysql_tquery(dbCon, "SELECT * FROM `gachas`", "GaCha_Load", "");  
            SendClientMessage(playerid, -1, "คุณได้รีโหลดกล่องเรียบร้อยแล้ว");          
        }
    }
    return 1;
}

CMD:box(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1337) return 0;
    ShowGaChaBox(playerid);
    return 1;
}