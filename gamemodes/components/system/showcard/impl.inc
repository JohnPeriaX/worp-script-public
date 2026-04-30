#if defined _inc_impl
	#undef _inc_impl
#endif

LoadTextDrawPlayerShowBadge(playerid){
    ShowBadgeTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 528.000000, 106.000000, "_");
    PlayerTextDrawFont(playerid, ShowBadgeTextDraw[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, ShowBadgeTextDraw[playerid][0], 0.600000, 10.300003);
    PlayerTextDrawTextSize(playerid, ShowBadgeTextDraw[playerid][0], 298.500000, 155.000000);
    PlayerTextDrawSetOutline(playerid, ShowBadgeTextDraw[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, ShowBadgeTextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, ShowBadgeTextDraw[playerid][0], 2);
    PlayerTextDrawColor(playerid, ShowBadgeTextDraw[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, ShowBadgeTextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, ShowBadgeTextDraw[playerid][0], 135);
    PlayerTextDrawUseBox(playerid, ShowBadgeTextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, ShowBadgeTextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, ShowBadgeTextDraw[playerid][0], 0);

    ShowBadgeTextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 528.000000, 106.000000, "_");
    PlayerTextDrawFont(playerid, ShowBadgeTextDraw[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, ShowBadgeTextDraw[playerid][1], 0.600000, 1.300003);
    PlayerTextDrawTextSize(playerid, ShowBadgeTextDraw[playerid][1], 298.500000, 155.000000);
    PlayerTextDrawSetOutline(playerid, ShowBadgeTextDraw[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, ShowBadgeTextDraw[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, ShowBadgeTextDraw[playerid][1], 2);
    PlayerTextDrawColor(playerid, ShowBadgeTextDraw[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, ShowBadgeTextDraw[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, ShowBadgeTextDraw[playerid][1], 1097458055);
    PlayerTextDrawUseBox(playerid, ShowBadgeTextDraw[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, ShowBadgeTextDraw[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, ShowBadgeTextDraw[playerid][1], 0);

    ShowBadgeTextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 465.000000, 105.000000, "Badge");
    PlayerTextDrawFont(playerid, ShowBadgeTextDraw[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, ShowBadgeTextDraw[playerid][2], 0.270833, 1.200000);
    PlayerTextDrawTextSize(playerid, ShowBadgeTextDraw[playerid][2], 400.000000, 98.500000);
    PlayerTextDrawSetOutline(playerid, ShowBadgeTextDraw[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, ShowBadgeTextDraw[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, ShowBadgeTextDraw[playerid][2], 2);
    PlayerTextDrawColor(playerid, ShowBadgeTextDraw[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, ShowBadgeTextDraw[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, ShowBadgeTextDraw[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, ShowBadgeTextDraw[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, ShowBadgeTextDraw[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, ShowBadgeTextDraw[playerid][2], 0);

    ShowBadgeTextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 484.000000, 130.000000, "_");
    PlayerTextDrawFont(playerid, ShowBadgeTextDraw[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, ShowBadgeTextDraw[playerid][3], 0.600000, 6.300003);
    PlayerTextDrawTextSize(playerid, ShowBadgeTextDraw[playerid][3], 298.500000, 55.000000);
    PlayerTextDrawSetOutline(playerid, ShowBadgeTextDraw[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, ShowBadgeTextDraw[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, ShowBadgeTextDraw[playerid][3], 2);
    PlayerTextDrawColor(playerid, ShowBadgeTextDraw[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, ShowBadgeTextDraw[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, ShowBadgeTextDraw[playerid][3], -741092473);
    PlayerTextDrawUseBox(playerid, ShowBadgeTextDraw[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, ShowBadgeTextDraw[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, ShowBadgeTextDraw[playerid][3], 0);

    ShowBadgeTextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 451.000000, 126.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, ShowBadgeTextDraw[playerid][4], 5);
    PlayerTextDrawLetterSize(playerid, ShowBadgeTextDraw[playerid][4], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, ShowBadgeTextDraw[playerid][4], 61.000000, 65.000000);
    PlayerTextDrawSetOutline(playerid, ShowBadgeTextDraw[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, ShowBadgeTextDraw[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, ShowBadgeTextDraw[playerid][4], 1);
    PlayerTextDrawColor(playerid, ShowBadgeTextDraw[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, ShowBadgeTextDraw[playerid][4], 0);
    PlayerTextDrawBoxColor(playerid, ShowBadgeTextDraw[playerid][4], 255);
    PlayerTextDrawUseBox(playerid, ShowBadgeTextDraw[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, ShowBadgeTextDraw[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, ShowBadgeTextDraw[playerid][4], 0);
    PlayerTextDrawSetPreviewModel(playerid, ShowBadgeTextDraw[playerid][4], 275);
    PlayerTextDrawSetPreviewRot(playerid, ShowBadgeTextDraw[playerid][4], -10.000000, 0.000000, 0.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, ShowBadgeTextDraw[playerid][4], 1, 1);

    ShowBadgeTextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 518.000000, 130.000000, "Name: Jonathan Ethaner");
    PlayerTextDrawFont(playerid, ShowBadgeTextDraw[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, ShowBadgeTextDraw[playerid][5], 0.154166, 0.800000);
    PlayerTextDrawTextSize(playerid, ShowBadgeTextDraw[playerid][5], 600.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, ShowBadgeTextDraw[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, ShowBadgeTextDraw[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, ShowBadgeTextDraw[playerid][5], 1);
    PlayerTextDrawColor(playerid, ShowBadgeTextDraw[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, ShowBadgeTextDraw[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, ShowBadgeTextDraw[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, ShowBadgeTextDraw[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, ShowBadgeTextDraw[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, ShowBadgeTextDraw[playerid][5], 0);

    ShowBadgeTextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 518.000000, 144.000000, "Agency: Los Santos Police Department");
    PlayerTextDrawFont(playerid, ShowBadgeTextDraw[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, ShowBadgeTextDraw[playerid][6], 0.154166, 0.800000);
    PlayerTextDrawTextSize(playerid, ShowBadgeTextDraw[playerid][6], 600.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, ShowBadgeTextDraw[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, ShowBadgeTextDraw[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, ShowBadgeTextDraw[playerid][6], 1);
    PlayerTextDrawColor(playerid, ShowBadgeTextDraw[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, ShowBadgeTextDraw[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, ShowBadgeTextDraw[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, ShowBadgeTextDraw[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, ShowBadgeTextDraw[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, ShowBadgeTextDraw[playerid][6], 0);

    ShowBadgeTextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 518.000000, 166.000000, "Rank: Chief of Police");
    PlayerTextDrawFont(playerid, ShowBadgeTextDraw[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, ShowBadgeTextDraw[playerid][7], 0.154166, 0.800000);
    PlayerTextDrawTextSize(playerid, ShowBadgeTextDraw[playerid][7], 600.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, ShowBadgeTextDraw[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, ShowBadgeTextDraw[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, ShowBadgeTextDraw[playerid][7], 1);
    PlayerTextDrawColor(playerid, ShowBadgeTextDraw[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, ShowBadgeTextDraw[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, ShowBadgeTextDraw[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, ShowBadgeTextDraw[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, ShowBadgeTextDraw[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, ShowBadgeTextDraw[playerid][7], 0);

    ShowBadgeTextDraw[playerid][8] = CreatePlayerTextDraw(playerid, 590.000000, 189.000000, "CLOSE");
    PlayerTextDrawFont(playerid, ShowBadgeTextDraw[playerid][8], 2);
    PlayerTextDrawLetterSize(playerid, ShowBadgeTextDraw[playerid][8], 0.120833, 0.700000);
    PlayerTextDrawTextSize(playerid, ShowBadgeTextDraw[playerid][8], 16.500000, 19.500000);
    PlayerTextDrawSetOutline(playerid, ShowBadgeTextDraw[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, ShowBadgeTextDraw[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, ShowBadgeTextDraw[playerid][8], 2);
    PlayerTextDrawColor(playerid, ShowBadgeTextDraw[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, ShowBadgeTextDraw[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, ShowBadgeTextDraw[playerid][8], -16777016);
    PlayerTextDrawUseBox(playerid, ShowBadgeTextDraw[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, ShowBadgeTextDraw[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, ShowBadgeTextDraw[playerid][8], 1);
    return 1;
}

new PlayerText:IDCARDTEXTDRAW[MAX_PLAYERS][10];

LoadTextDrawPlayerShowIdCard(playerid){
    IDCARDTEXTDRAW[playerid][0] = CreatePlayerTextDraw(playerid, 533.000000, 108.000000, "_");
    PlayerTextDrawFont(playerid, IDCARDTEXTDRAW[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, IDCARDTEXTDRAW[playerid][0], 0.600000, 8.850005);
    PlayerTextDrawTextSize(playerid, IDCARDTEXTDRAW[playerid][0], 298.500000, 145.000000);
    PlayerTextDrawSetOutline(playerid, IDCARDTEXTDRAW[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, IDCARDTEXTDRAW[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, IDCARDTEXTDRAW[playerid][0], 2);
    PlayerTextDrawColor(playerid, IDCARDTEXTDRAW[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, IDCARDTEXTDRAW[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, IDCARDTEXTDRAW[playerid][0], 200);
    PlayerTextDrawUseBox(playerid, IDCARDTEXTDRAW[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, IDCARDTEXTDRAW[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, IDCARDTEXTDRAW[playerid][0], 0);

    IDCARDTEXTDRAW[playerid][1] = CreatePlayerTextDraw(playerid, 533.000000, 112.000000, "_");
    PlayerTextDrawFont(playerid, IDCARDTEXTDRAW[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, IDCARDTEXTDRAW[playerid][1], 0.600000, 7.850001);
    PlayerTextDrawTextSize(playerid, IDCARDTEXTDRAW[playerid][1], 298.500000, 138.000000);
    PlayerTextDrawSetOutline(playerid, IDCARDTEXTDRAW[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, IDCARDTEXTDRAW[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, IDCARDTEXTDRAW[playerid][1], 2);
    PlayerTextDrawColor(playerid, IDCARDTEXTDRAW[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, IDCARDTEXTDRAW[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, IDCARDTEXTDRAW[playerid][1], -56);
    PlayerTextDrawUseBox(playerid, IDCARDTEXTDRAW[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, IDCARDTEXTDRAW[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, IDCARDTEXTDRAW[playerid][1], 0);

    IDCARDTEXTDRAW[playerid][2] = CreatePlayerTextDraw(playerid, 488.000000, 117.000000, "_");
    PlayerTextDrawFont(playerid, IDCARDTEXTDRAW[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, IDCARDTEXTDRAW[playerid][2], 0.600000, 6.650008);
    PlayerTextDrawTextSize(playerid, IDCARDTEXTDRAW[playerid][2], 298.500000, 37.500000);
    PlayerTextDrawSetOutline(playerid, IDCARDTEXTDRAW[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, IDCARDTEXTDRAW[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, IDCARDTEXTDRAW[playerid][2], 2);
    PlayerTextDrawColor(playerid, IDCARDTEXTDRAW[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, IDCARDTEXTDRAW[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, IDCARDTEXTDRAW[playerid][2], 1296911816);
    PlayerTextDrawUseBox(playerid, IDCARDTEXTDRAW[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, IDCARDTEXTDRAW[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, IDCARDTEXTDRAW[playerid][2], 0);

    IDCARDTEXTDRAW[playerid][3] = CreatePlayerTextDraw(playerid, 455.000000, 116.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, IDCARDTEXTDRAW[playerid][3], 5);
    PlayerTextDrawLetterSize(playerid, IDCARDTEXTDRAW[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, IDCARDTEXTDRAW[playerid][3], 63.000000, 63.500000);
    PlayerTextDrawSetOutline(playerid, IDCARDTEXTDRAW[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, IDCARDTEXTDRAW[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, IDCARDTEXTDRAW[playerid][3], 1);
    PlayerTextDrawColor(playerid, IDCARDTEXTDRAW[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, IDCARDTEXTDRAW[playerid][3], 0);
    PlayerTextDrawBoxColor(playerid, IDCARDTEXTDRAW[playerid][3], 255);
    PlayerTextDrawUseBox(playerid, IDCARDTEXTDRAW[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, IDCARDTEXTDRAW[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, IDCARDTEXTDRAW[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, IDCARDTEXTDRAW[playerid][3], 72);
    PlayerTextDrawSetPreviewRot(playerid, IDCARDTEXTDRAW[playerid][3], -9.000000, 0.000000, -3.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, IDCARDTEXTDRAW[playerid][3], 1, 1);

    IDCARDTEXTDRAW[playerid][4] = CreatePlayerTextDraw(playerid, 512.000000, 117.000000, "Name: Jonathan Ethaner");
    PlayerTextDrawFont(playerid, IDCARDTEXTDRAW[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, IDCARDTEXTDRAW[playerid][4], 0.158333, 0.800001);
    PlayerTextDrawTextSize(playerid, IDCARDTEXTDRAW[playerid][4], 600.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, IDCARDTEXTDRAW[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, IDCARDTEXTDRAW[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, IDCARDTEXTDRAW[playerid][4], 1);
    PlayerTextDrawColor(playerid, IDCARDTEXTDRAW[playerid][4], 255);
    PlayerTextDrawBackgroundColor(playerid, IDCARDTEXTDRAW[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, IDCARDTEXTDRAW[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, IDCARDTEXTDRAW[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, IDCARDTEXTDRAW[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, IDCARDTEXTDRAW[playerid][4], 0);

    IDCARDTEXTDRAW[playerid][5] = CreatePlayerTextDraw(playerid, 512.000000, 130.000000, "Age: 20");
    PlayerTextDrawFont(playerid, IDCARDTEXTDRAW[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, IDCARDTEXTDRAW[playerid][5], 0.158333, 0.800001);
    PlayerTextDrawTextSize(playerid, IDCARDTEXTDRAW[playerid][5], 600.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, IDCARDTEXTDRAW[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, IDCARDTEXTDRAW[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, IDCARDTEXTDRAW[playerid][5], 1);
    PlayerTextDrawColor(playerid, IDCARDTEXTDRAW[playerid][5], 255);
    PlayerTextDrawBackgroundColor(playerid, IDCARDTEXTDRAW[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, IDCARDTEXTDRAW[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, IDCARDTEXTDRAW[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, IDCARDTEXTDRAW[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, IDCARDTEXTDRAW[playerid][5], 0);

    IDCARDTEXTDRAW[playerid][6] = CreatePlayerTextDraw(playerid, 512.000000, 143.000000, "Gender: Male");
    PlayerTextDrawFont(playerid, IDCARDTEXTDRAW[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, IDCARDTEXTDRAW[playerid][6], 0.158333, 0.800001);
    PlayerTextDrawTextSize(playerid, IDCARDTEXTDRAW[playerid][6], 600.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, IDCARDTEXTDRAW[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, IDCARDTEXTDRAW[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, IDCARDTEXTDRAW[playerid][6], 1);
    PlayerTextDrawColor(playerid, IDCARDTEXTDRAW[playerid][6], 255);
    PlayerTextDrawBackgroundColor(playerid, IDCARDTEXTDRAW[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, IDCARDTEXTDRAW[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, IDCARDTEXTDRAW[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, IDCARDTEXTDRAW[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, IDCARDTEXTDRAW[playerid][6], 0);

    IDCARDTEXTDRAW[playerid][7] = CreatePlayerTextDraw(playerid, 512.000000, 156.000000, "Job: Farmer");
    PlayerTextDrawFont(playerid, IDCARDTEXTDRAW[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, IDCARDTEXTDRAW[playerid][7], 0.158333, 0.800001);
    PlayerTextDrawTextSize(playerid, IDCARDTEXTDRAW[playerid][7], 600.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, IDCARDTEXTDRAW[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, IDCARDTEXTDRAW[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, IDCARDTEXTDRAW[playerid][7], 1);
    PlayerTextDrawColor(playerid, IDCARDTEXTDRAW[playerid][7], 255);
    PlayerTextDrawBackgroundColor(playerid, IDCARDTEXTDRAW[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, IDCARDTEXTDRAW[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, IDCARDTEXTDRAW[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, IDCARDTEXTDRAW[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, IDCARDTEXTDRAW[playerid][7], 0);

    IDCARDTEXTDRAW[playerid][8] = CreatePlayerTextDraw(playerid, 585.000000, 170.000000, "CLOSE");
    PlayerTextDrawFont(playerid, IDCARDTEXTDRAW[playerid][8], 2);
    PlayerTextDrawLetterSize(playerid, IDCARDTEXTDRAW[playerid][8], 0.133333, 1.100000);
    PlayerTextDrawTextSize(playerid, IDCARDTEXTDRAW[playerid][8], 16.500000, 30.500000);
    PlayerTextDrawSetOutline(playerid, IDCARDTEXTDRAW[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, IDCARDTEXTDRAW[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, IDCARDTEXTDRAW[playerid][8], 2);
    PlayerTextDrawColor(playerid, IDCARDTEXTDRAW[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, IDCARDTEXTDRAW[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, IDCARDTEXTDRAW[playerid][8], -16777016);
    PlayerTextDrawUseBox(playerid, IDCARDTEXTDRAW[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, IDCARDTEXTDRAW[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, IDCARDTEXTDRAW[playerid][8], 1);

    IDCARDTEXTDRAW[playerid][9] = CreatePlayerTextDraw(playerid, 530.000000, 97.000000, "ID CARD");
    PlayerTextDrawFont(playerid, IDCARDTEXTDRAW[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, IDCARDTEXTDRAW[playerid][9], 0.437500, 1.800000);
    PlayerTextDrawTextSize(playerid, IDCARDTEXTDRAW[playerid][9], 430.000000, 127.000000);
    PlayerTextDrawSetOutline(playerid, IDCARDTEXTDRAW[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, IDCARDTEXTDRAW[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, IDCARDTEXTDRAW[playerid][9], 2);
    PlayerTextDrawColor(playerid, IDCARDTEXTDRAW[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, IDCARDTEXTDRAW[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, IDCARDTEXTDRAW[playerid][9], 50);
    PlayerTextDrawUseBox(playerid, IDCARDTEXTDRAW[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, IDCARDTEXTDRAW[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, IDCARDTEXTDRAW[playerid][9], 0);
    return 1;
}

ResetShowCard(playerid){
    IsShowCard[playerid] = 0;
    return 1;
}

ShowIdCardForPlayer(playerid, targetid){
    IsShowCard[playerid] = 1;
    LoadTextDrawPlayerShowIdCard(playerid);

    new string[128];
    new stringgender[32];

    PlayerTextDrawSetPreviewModel(playerid, IDCARDTEXTDRAW[playerid][3], PlayerData[targetid][pSkin]);

    format(string, sizeof(string), "Name: %s", ReturnRoleplayName(targetid));
    PlayerTextDrawSetString(playerid, IDCARDTEXTDRAW[playerid][4], string);

    if(PlayerData[targetid][pGender] == 1)
        stringgender = "Male";
    else if(PlayerData[targetid][pGender] == 2)
        stringgender = "Female";

    format(string, sizeof(string), "Age: %d , Gender: %s", PlayerData[targetid][pAge], stringgender);
    PlayerTextDrawSetString(playerid, IDCARDTEXTDRAW[playerid][5], string);

    format(string, sizeof(string), "Factions: %s", Group_GetName(targetid));
    PlayerTextDrawSetString(playerid, IDCARDTEXTDRAW[playerid][6], string);

    format(string, sizeof(string), "Id Card: %d", PlayerData[targetid][pIdcard]);
    PlayerTextDrawSetString(playerid, IDCARDTEXTDRAW[playerid][7], string);

    for(new i=0; i<10; i++)
        PlayerTextDrawShow(playerid, IDCARDTEXTDRAW[playerid][i]);

    SelectTextDraw(playerid, 0xFFB900AA);
    return 1;
}

HideIdCardForPlayer(playerid){
    IsShowCard[playerid] = 0;

    for(new i=0; i<10; i++){
        PlayerTextDrawHide(playerid, IDCARDTEXTDRAW[playerid][i]);
        PlayerTextDrawDestroy(playerid, IDCARDTEXTDRAW[playerid][i]);
    }

    CancelSelectTextDraw(playerid);
    return 1;
}

ShowBadgeForPlayer(playerid, targetid){
    IsShowCard[playerid] = 1;
    LoadTextDrawPlayerShowBadge(playerid);

    PlayerTextDrawSetPreviewModel(playerid, ShowBadgeTextDraw[playerid][4], PlayerData[targetid][pSkin]);

    new string[128];

    format(string, sizeof(string), "Name: %s", ReturnRoleplayName(targetid));
    PlayerTextDrawSetString(playerid, ShowBadgeTextDraw[playerid][5], string);

    format(string, sizeof(string), "Agency: %s", Group_GetName(targetid));
    PlayerTextDrawSetString(playerid, ShowBadgeTextDraw[playerid][6], string);

    format(string, sizeof(string), "Rank: %s", Group_GetRank(targetid));
    PlayerTextDrawSetString(playerid, ShowBadgeTextDraw[playerid][7], string);

    PlayerTextDrawBoxColor(playerid, ShowBadgeTextDraw[playerid][1], GroupData[PlayerData[targetid][pGroup]][groupColor]);

    for(new i=0; i<9; i++)
        PlayerTextDrawShow(playerid, ShowBadgeTextDraw[playerid][i]);

    SelectTextDraw(playerid, 0xFFB900AA);

    return 1;
}

HideBadgeForPlayer(playerid){
    IsShowCard[playerid] = 0;

    for(new i=0; i<9; i++){
        PlayerTextDrawHide(playerid, ShowBadgeTextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, ShowBadgeTextDraw[playerid][i]);
    }

    CancelSelectTextDraw(playerid);
    return 1;
}