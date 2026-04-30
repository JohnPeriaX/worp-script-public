#if defined _inc_impl
	#undef _inc_impl
#endif

Reset_PizzaJob(playerid){
    PlayerOpenPizzaMenu[playerid] = false;
    CowmeatAmount[playerid] = 0;
    CowmeatMax[playerid] = 0;
    TomatoAmount[playerid] = 0;
    TomatoMax[playerid] = 0;
    TomatoSaiceAmount[playerid] = 0;
    TomatoSaiceMax[playerid] = 0;
    MayonnaiseSaiceAmount[playerid] = 0;
    MayonnaiseSaiceMax[playerid] = 0;
    KillTimer(PizzaBakedTime[playerid]);
    PizzaBakedPoint[playerid] = 0;
    StartBakedPizza[playerid] = false;
    return 1;
}

OpenPizzaMenu(playerid){
    LoadPizzaTextDraw(playerid);
    LoadProgressbarPizza(playerid);

    for(new i=0; i<22; i++){
        PlayerTextDrawShow(playerid, PizzaTextDraw[playerid][i]);
    }

    PlayerTextDrawHide(playerid, PizzaTextDraw[playerid][16]);
    PlayerTextDrawHide(playerid, PizzaTextDraw[playerid][17]);
    PlayerTextDrawHide(playerid, PizzaTextDraw[playerid][18]);
    PlayerTextDrawHide(playerid, PizzaTextDraw[playerid][19]);
    PlayerTextDrawHide(playerid, PizzaTextDraw[playerid][20]);

    new string[128];

    format(string, sizeof(string), "Tomato %d Ea", PlayerInventory_AllCount(playerid, "Tomato"));
    PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][3], string);

    format(string, sizeof(string), "CowMeat %d Ea", PlayerInventory_AllCount(playerid, "Raw Cow Meat"));
    PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][5], string);

    ShowPlayerProgressBar(playerid, PizzaProgressBar[playerid][0]);
    SelectTextDraw(playerid, 0xFFB600AA);
    TogglePlayerControllable(playerid, 0);
    RandomMenuListPizza(playerid);
    PlayerOpenPizzaMenu[playerid] = true;
    return 1;
}

RandomMenuListPizza(playerid){

    if(CowmeatMax[playerid] == 0){
        new bacon = random(8);
        if(bacon <= 0) bacon = 1;
        CowmeatMax[playerid] = bacon;
    }
    
    if(TomatoMax[playerid] == 0){
        new tomato = random(8);
        if(tomato <= 0) tomato = 1;
        TomatoMax[playerid] = tomato;
    }
    
    if(TomatoSaiceMax[playerid] == 0){
        new tomatosaice = random(8);
        if(tomatosaice <= 0) tomatosaice = 1;
        TomatoSaiceMax[playerid] = tomatosaice;
    }
    
    if(MayonnaiseSaiceMax[playerid] == 0){
        new mayonnaisesaice = random(8);
        if(mayonnaisesaice <= 0) mayonnaisesaice = 1;
        MayonnaiseSaiceMax[playerid] = mayonnaisesaice;
    }
    

    new string[128];
    format(string, sizeof(string), "x%d Cow Meat", CowmeatMax[playerid]);
    PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][12], string);

    format(string, sizeof(string), "x%d Tomato", TomatoMax[playerid]);
    PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][13], string);

    format(string, sizeof(string), "x%d Tomato Saice", TomatoSaiceMax[playerid]);
    PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][14], string);

    format(string, sizeof(string), "x%d Mayonnaise Saice", MayonnaiseSaiceMax[playerid]);
    PlayerTextDrawSetString(playerid, PizzaTextDraw[playerid][15], string);
    return 1;
}

ClosePizzaMenu(playerid){
    for(new i=0; i<22; i++){
        PlayerTextDrawHide(playerid, PizzaTextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, PizzaTextDraw[playerid][i]);
    }
    HidePlayerProgressBar(playerid, PizzaProgressBar[playerid][0]);
    DestroyPlayerProgressBar(playerid, PizzaProgressBar[playerid][0]);
    CancelSelectTextDraw(playerid);
    PlayerOpenPizzaMenu[playerid] = false;
    CowmeatAmount[playerid] = 0;
    TomatoAmount[playerid] = 0;
    TomatoSaiceAmount[playerid] = 0;
    MayonnaiseSaiceAmount[playerid] = 0;
    TogglePlayerControllable(playerid, 1);
    return 1;
}

PlayerStartBakedPizza(playerid){
    if(TomatoAmount[playerid] == TomatoMax[playerid] &&
    CowmeatAmount[playerid] == CowmeatMax[playerid] &&
    TomatoSaiceAmount[playerid] == TomatoSaiceMax[playerid] &&
    MayonnaiseSaiceAmount[playerid] == MayonnaiseSaiceMax[playerid]){
        PizzaBakedPoint[playerid] = 0;
        StartBakedPizza[playerid] = true;
        PizzaBakedTime[playerid] = SetTimerEx("BakedPizza", 50, false, "i", playerid);
    }
    return 1;
}

forward BakedPizza(playerid);
public BakedPizza(playerid){
    if(StartBakedPizza[playerid]){
        if(PizzaBakedPoint[playerid] < 300){
            PizzaBakedPoint[playerid]++;
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
            SetPlayerProgressBarValue(playerid, PizzaProgressBar[playerid][0], PizzaBakedPoint[playerid]);
            PizzaBakedTime[playerid] = SetTimerEx("BakedPizza", 50, false, "i", playerid);
        }
        else{
            PlayerInventory_Remove(playerid, "Raw Cow Meat", CowmeatAmount[playerid]);
            PlayerInventory_Remove(playerid, "Tomato", TomatoAmount[playerid]);
            TogglePlayerControllable(playerid, 1);
            Reset_PizzaJob(playerid);
            ClosePizzaMenu(playerid);
            ClearAnimations(playerid);
            PlayerData[playerid][pStress]++;
            if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
            new itemid = PlayerInventory_AddItem(playerid, "Pizza Box", 1582, 1);
            if(itemid == -1) return ErrorMsg(playerid, "ไอเท็มชิ้นนี้ของคุณเต็มแล้วหรือกระเป๋าของคุณมีพื้นที่ไม่เพียงพอ");
            SendClientMessage(playerid, COLOR_ORANGE, "- คุณได้รับ Pizza Box (พิซซ่ากล่อง) + 1");
            SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: พิซซ่า 1 ถาดจะให้ความหิว + 100");
        }
    }
    return 1;
}

LoadPizzaTextDraw(playerid){
    PizzaTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 325.000000, 157.000000, "_");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][0], 0.600000, 24.300003);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][0], 298.500000, 321.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][0], 2);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][0], 135);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][0], 0);

    PizzaTextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 248.000000, 144.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][1], 5);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][1], 144.500000, 181.500000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][1], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][1], 0);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][1], 255);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, PizzaTextDraw[playerid][1], 19580);
    PlayerTextDrawSetPreviewRot(playerid, PizzaTextDraw[playerid][1], -69.000000, 0.000000, -22.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PizzaTextDraw[playerid][1], 1, 1);

    PizzaTextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 185.000000, 163.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][2], 5);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][2], 34.500000, 40.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][2], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][2], 1296911741);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][2], 255);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][2], 1);
    PlayerTextDrawSetPreviewModel(playerid, PizzaTextDraw[playerid][2], 19577);
    PlayerTextDrawSetPreviewRot(playerid, PizzaTextDraw[playerid][2], -10.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PizzaTextDraw[playerid][2], 1, 1);

    PizzaTextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 203.000000, 198.000000, "Tomato 10 EA");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][3], 0.200000, 0.990000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][3], 400.000000, 62.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][3], 2);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][3], 0);

    PizzaTextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 185.000000, 214.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][4], 5);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][4], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][4], 34.500000, 40.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][4], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][4], 1296911741);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][4], 255);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][4], 1);
    PlayerTextDrawSetPreviewModel(playerid, PizzaTextDraw[playerid][4], 19582);
    PlayerTextDrawSetPreviewRot(playerid, PizzaTextDraw[playerid][4], -10.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PizzaTextDraw[playerid][4], 1, 1);

    PizzaTextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 203.000000, 249.000000, "CowMeat 10 EA");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][5], 0.200000, 0.990000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][5], 400.000000, 62.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][5], 2);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][5], 0);

    PizzaTextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 185.000000, 264.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][6], 5);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][6], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][6], 34.500000, 40.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][6], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][6], 1296911741);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][6], 255);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][6], 1);
    PlayerTextDrawSetPreviewModel(playerid, PizzaTextDraw[playerid][6], 11722);
    PlayerTextDrawSetPreviewRot(playerid, PizzaTextDraw[playerid][6], -10.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PizzaTextDraw[playerid][6], 1, 1);

    PizzaTextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 203.000000, 299.000000, "Tomato Saice");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][7], 0.200000, 0.990000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][7], 400.000000, 72.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][7], 2);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][7], 0);

    PizzaTextDraw[playerid][8] = CreatePlayerTextDraw(playerid, 185.000000, 314.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][8], 5);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][8], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][8], 34.500000, 40.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][8], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][8], 1296911741);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][8], 255);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][8], 1);
    PlayerTextDrawSetPreviewModel(playerid, PizzaTextDraw[playerid][8], 11723);
    PlayerTextDrawSetPreviewRot(playerid, PizzaTextDraw[playerid][8], -10.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PizzaTextDraw[playerid][8], 1, 1);

    PizzaTextDraw[playerid][9] = CreatePlayerTextDraw(playerid, 203.000000, 347.000000, "Mayonnaise Saice");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][9], 0.200000, 0.990000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][9], 400.000000, 72.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][9], 2);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][9], 50);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][9], 0);

    PizzaTextDraw[playerid][10] = CreatePlayerTextDraw(playerid, 426.000000, 169.000000, "_");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][10], 0.600000, 6.649996);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][10], 298.500000, 98.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][10], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][10], 2);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][10], 1296911751);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][10], 0);

    PizzaTextDraw[playerid][11] = CreatePlayerTextDraw(playerid, 376.000000, 161.000000, "Request List");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][11], 1);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][11], 0.316666, 1.300000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][11], 470.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][11], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][11], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][11], 50);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][11], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][11], 0);

    PizzaTextDraw[playerid][12] = CreatePlayerTextDraw(playerid, 380.000000, 178.000000, "x5 Bacon");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][12], 1);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][12], 0.170000, 1.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][12], 470.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][12], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][12], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][12], 50);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][12], 0);

    PizzaTextDraw[playerid][13] = CreatePlayerTextDraw(playerid, 380.000000, 190.000000, "x2 Tomato");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][13], 0.170000, 1.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][13], 470.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][13], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][13], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][13], 50);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][13], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][13], 0);

    PizzaTextDraw[playerid][14] = CreatePlayerTextDraw(playerid, 380.000000, 202.000000, "x3 Tomato Saice");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][14], 1);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][14], 0.170000, 1.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][14], 470.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][14], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][14], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][14], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][14], 50);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][14], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][14], 0);

    PizzaTextDraw[playerid][15] = CreatePlayerTextDraw(playerid, 380.000000, 214.000000, "x1 Mayonnaise Saice");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][15], 1);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][15], 0.170000, 1.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][15], 470.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][15], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][15], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][15], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][15], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][15], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][15], 50);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][15], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][15], 0);

    PizzaTextDraw[playerid][16] = CreatePlayerTextDraw(playerid, 293.000000, 203.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][16], 5);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][16], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][16], 34.500000, 40.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][16], 0);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][16], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][16], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][16], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][16], 1296911616);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][16], 255);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][16], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][16], 1);
    PlayerTextDrawSetPreviewModel(playerid, PizzaTextDraw[playerid][16], 19577);
    PlayerTextDrawSetPreviewRot(playerid, PizzaTextDraw[playerid][16], -10.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PizzaTextDraw[playerid][16], 1, 1);

    PizzaTextDraw[playerid][17] = CreatePlayerTextDraw(playerid, 313.000000, 230.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][17], 5);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][17], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][17], 34.500000, 40.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][17], 0);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][17], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][17], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][17], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][17], 1296911616);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][17], 255);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][17], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][17], 1);
    PlayerTextDrawSetPreviewModel(playerid, PizzaTextDraw[playerid][17], 19577);
    PlayerTextDrawSetPreviewRot(playerid, PizzaTextDraw[playerid][17], -10.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PizzaTextDraw[playerid][17], 1, 1);

    PizzaTextDraw[playerid][18] = CreatePlayerTextDraw(playerid, 286.000000, 230.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][18], 5);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][18], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][18], 34.500000, 40.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][18], 0);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][18], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][18], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][18], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][18], 1296911616);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][18], 255);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][18], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][18], 1);
    PlayerTextDrawSetPreviewModel(playerid, PizzaTextDraw[playerid][18], 19577);
    PlayerTextDrawSetPreviewRot(playerid, PizzaTextDraw[playerid][18], -10.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PizzaTextDraw[playerid][18], 1, 1);

    PizzaTextDraw[playerid][19] = CreatePlayerTextDraw(playerid, 325.000000, 204.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][19], 5);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][19], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][19], 34.500000, 40.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][19], 0);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][19], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][19], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][19], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][19], 1296911616);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][19], 255);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][19], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][19], 1);
    PlayerTextDrawSetPreviewModel(playerid, PizzaTextDraw[playerid][19], 19582);
    PlayerTextDrawSetPreviewRot(playerid, PizzaTextDraw[playerid][19], -71.000000, 0.000000, -20.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PizzaTextDraw[playerid][19], 1, 1);

    PizzaTextDraw[playerid][20] = CreatePlayerTextDraw(playerid, 281.000000, 207.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][20], 5);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][20], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][20], 34.500000, 40.000000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][20], 0);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][20], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][20], 1);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][20], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][20], 1296911616);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][20], 255);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][20], 0);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][20], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][20], 1);
    PlayerTextDrawSetPreviewModel(playerid, PizzaTextDraw[playerid][20], 19582);
    PlayerTextDrawSetPreviewRot(playerid, PizzaTextDraw[playerid][20], -71.000000, 0.000000, 26.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PizzaTextDraw[playerid][20], 1, 1);

    PizzaTextDraw[playerid][21] = CreatePlayerTextDraw(playerid, 425.000000, 254.000000, "Baked");
    PlayerTextDrawFont(playerid, PizzaTextDraw[playerid][21], 2);
    PlayerTextDrawLetterSize(playerid, PizzaTextDraw[playerid][21], 0.258332, 1.750000);
    PlayerTextDrawTextSize(playerid, PizzaTextDraw[playerid][21], 16.500000, 90.500000);
    PlayerTextDrawSetOutline(playerid, PizzaTextDraw[playerid][21], 1);
    PlayerTextDrawSetShadow(playerid, PizzaTextDraw[playerid][21], 0);
    PlayerTextDrawAlignment(playerid, PizzaTextDraw[playerid][21], 2);
    PlayerTextDrawColor(playerid, PizzaTextDraw[playerid][21], -1);
    PlayerTextDrawBackgroundColor(playerid, PizzaTextDraw[playerid][21], 255);
    PlayerTextDrawBoxColor(playerid, PizzaTextDraw[playerid][21], 9109704);
    PlayerTextDrawUseBox(playerid, PizzaTextDraw[playerid][21], 1);
    PlayerTextDrawSetProportional(playerid, PizzaTextDraw[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, PizzaTextDraw[playerid][21], 1);
    return 1;
}

LoadProgressbarPizza(playerid){
    PizzaProgressBar[playerid][0] = CreatePlayerProgressBar(playerid, 259.000000, 344.000000, 6.000000, 180.000000, -1, 300.000000, 2);
}