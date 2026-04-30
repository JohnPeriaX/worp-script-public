#if defined _inc_impl
	#undef _inc_impl
#endif

ResetWeaponDealerJob(playerid){
    PlayerGetPow[playerid] = 0;
    PlayerGetPricePow[playerid] = 0;
    PlayerGetIDPow[playerid] = -1;
    RemoveAttachedObject(playerid, 8);
    PlayerOpenCraftWeaponMenu[playerid] = 0;
    PlayerGetIndexWeaponCraft[playerid] = -1;
    PlayerOpenCraftWeaponInfoMenu[playerid] = 0;
    CraftWeaponTimer[playerid] = 0;
    CraftWeaponPoint[playerid] = 0;
    StartingCraftWeapon[playerid] = 0;
    return 1;
}

#define MAX_CRAFT_PLAYER_TEXTDRAWS \
	50

#define MAX_CRAFT_MENU_ROWS \
	8

enum E_CRAFT_TEXTDRAW
{
    E_CRAFT_MODEL[MAX_CRAFT_MENU_ROWS],
    E_CRAFT_TEXT[MAX_CRAFT_MENU_ROWS],
    E_CRAFT_TEXTDRAW_CLOSE
};

new PlayerText:CraftTypeTextDraw[MAX_PLAYERS][MAX_CRAFT_PLAYER_TEXTDRAWS];
new CraftTypeTextDrawID[MAX_PLAYERS][E_CRAFT_TEXTDRAW];
new CraftTypeTextDrawCount[MAX_PLAYERS];

new PlayerText:CraftWeaponInfo[MAX_PLAYERS][15];

LoadPlayerCraftInfoTextDraw(playerid){
    CraftWeaponInfo[playerid][0] = CreatePlayerTextDraw(playerid, 323.000000, 131.000000, "_");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][0], 0.600000, 24.800003);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][0], 298.500000, 315.000000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][0], 2);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][0], 200);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][0], 0);

    CraftWeaponInfo[playerid][1] = CreatePlayerTextDraw(playerid, 321.000000, 134.000000, "Weapon Craft");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][1], 2);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][1], 0.337500, 1.899999);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][1], 380.000000, 247.000000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][1], 2);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][1], 0);

    CraftWeaponInfo[playerid][2] = CreatePlayerTextDraw(playerid, 278.000000, 158.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][2], 5);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][2], 84.500000, 92.000000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][2], 1);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][2], -1094795651);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][2], 255);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][2], 1);
    PlayerTextDrawSetPreviewModel(playerid, CraftWeaponInfo[playerid][2], 336);
    PlayerTextDrawSetPreviewRot(playerid, CraftWeaponInfo[playerid][2], -10.000000, 29.000000, -20.000000, 2.399998);
    PlayerTextDrawSetPreviewVehCol(playerid, CraftWeaponInfo[playerid][2], 1, 1);

    CraftWeaponInfo[playerid][3] = CreatePlayerTextDraw(playerid, 321.000000, 254.000000, "Baseball Bat");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][3], 2);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][3], 0.179167, 1.250000);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][3], 380.000000, 247.000000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][3], 2);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][3], 0);

    CraftWeaponInfo[playerid][4] = CreatePlayerTextDraw(playerid, 323.000000, 270.000000, "_");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][4], 0.600000, 8.649995);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][4], 298.500000, 298.500000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][4], 2);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][4], 1296911751);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][4], 0);

    CraftWeaponInfo[playerid][5] = CreatePlayerTextDraw(playerid, 461.000000, 137.000000, "CLOSE");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][5], 2);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][5], 0.158332, 1.100000);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][5], 16.500000, 28.500000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][5], 2);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][5], -16777016);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][5], 1);

    CraftWeaponInfo[playerid][6] = CreatePlayerTextDraw(playerid, 169.000000, 261.000000, "Item Use");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][6], 2);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][6], 0.179167, 1.250000);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][6], 380.000000, 247.000000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][6], 1);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][6], 0);

    CraftWeaponInfo[playerid][7] = CreatePlayerTextDraw(playerid, 187.000000, 276.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][7], 5);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][7], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][7], 48.500000, 54.500000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][7], 1);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][7], -1094795651);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][7], 255);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][7], 0);
    PlayerTextDrawSetPreviewModel(playerid, CraftWeaponInfo[playerid][7], 2057);
    PlayerTextDrawSetPreviewRot(playerid, CraftWeaponInfo[playerid][7], -2.000000, 1.000000, 14.000000, 1.230000);
    PlayerTextDrawSetPreviewVehCol(playerid, CraftWeaponInfo[playerid][7], 1, 1);

    CraftWeaponInfo[playerid][8] = CreatePlayerTextDraw(playerid, 212.000000, 333.000000, "Gun Powder (300 EA)");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][8], 2);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][8], 0.129167, 1.050001);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][8], 380.000000, 247.000000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][8], 2);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][8], 50);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][8], 0);

    CraftWeaponInfo[playerid][9] = CreatePlayerTextDraw(playerid, 261.000000, 276.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][9], 5);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][9], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][9], 48.500000, 54.500000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][9], 1);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][9], -1094795651);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][9], 255);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][9], 0);
    PlayerTextDrawSetPreviewModel(playerid, CraftWeaponInfo[playerid][9], 19793);
    PlayerTextDrawSetPreviewRot(playerid, CraftWeaponInfo[playerid][9], -2.000000, 1.000000, 14.000000, 1.230000);
    PlayerTextDrawSetPreviewVehCol(playerid, CraftWeaponInfo[playerid][9], 1, 1);

    CraftWeaponInfo[playerid][10] = CreatePlayerTextDraw(playerid, 285.000000, 333.000000, "Wood (200 EA)");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][10], 2);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][10], 0.129167, 1.050001);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][10], 380.000000, 247.000000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][10], 2);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][10], 50);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][10], 0);

    CraftWeaponInfo[playerid][11] = CreatePlayerTextDraw(playerid, 337.000000, 276.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][11], 5);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][11], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][11], 48.500000, 54.500000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][11], 1);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][11], -1094795651);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][11], 255);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][11], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][11], 0);
    PlayerTextDrawSetPreviewModel(playerid, CraftWeaponInfo[playerid][11], 19941);
    PlayerTextDrawSetPreviewRot(playerid, CraftWeaponInfo[playerid][11], -2.000000, 1.000000, 14.000000, 1.230000);
    PlayerTextDrawSetPreviewVehCol(playerid, CraftWeaponInfo[playerid][11], 1, 1);

    CraftWeaponInfo[playerid][12] = CreatePlayerTextDraw(playerid, 362.000000, 333.000000, "Ore (1200 EA)");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][12], 2);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][12], 0.129167, 1.050001);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][12], 380.000000, 247.000000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][12], 2);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][12], 50);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][12], 0);

    CraftWeaponInfo[playerid][13] = CreatePlayerTextDraw(playerid, 411.000000, 276.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][13], 5);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][13], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][13], 48.500000, 54.500000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][13], 0);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][13], 1);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][13], 9109629);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][13], 255);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][13], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][13], 0);
    PlayerTextDrawSetPreviewModel(playerid, CraftWeaponInfo[playerid][13], 1212);
    PlayerTextDrawSetPreviewRot(playerid, CraftWeaponInfo[playerid][13], -33.000000, 1.000000, 14.000000, 1.230000);
    PlayerTextDrawSetPreviewVehCol(playerid, CraftWeaponInfo[playerid][13], 0, 0);

    CraftWeaponInfo[playerid][14] = CreatePlayerTextDraw(playerid, 436.000000, 333.000000, "Money ($500,00)");
    PlayerTextDrawFont(playerid, CraftWeaponInfo[playerid][14], 2);
    PlayerTextDrawLetterSize(playerid, CraftWeaponInfo[playerid][14], 0.129167, 1.050001);
    PlayerTextDrawTextSize(playerid, CraftWeaponInfo[playerid][14], 380.000000, 247.000000);
    PlayerTextDrawSetOutline(playerid, CraftWeaponInfo[playerid][14], 0);
    PlayerTextDrawSetShadow(playerid, CraftWeaponInfo[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, CraftWeaponInfo[playerid][14], 2);
    PlayerTextDrawColor(playerid, CraftWeaponInfo[playerid][14], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftWeaponInfo[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, CraftWeaponInfo[playerid][14], 50);
    PlayerTextDrawUseBox(playerid, CraftWeaponInfo[playerid][14], 0);
    PlayerTextDrawSetProportional(playerid, CraftWeaponInfo[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, CraftWeaponInfo[playerid][14], 0);
    return 1;
}

LoadPlayerCraftTypeTextDraw(playerid){
    CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, 322.000000, 128.000000, "_");
    PlayerTextDrawFont(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawLetterSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0.600000, 27.800003);
    PlayerTextDrawTextSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 298.500000, 375.000000);
    PlayerTextDrawSetOutline(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetShadow(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0);
    PlayerTextDrawAlignment(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 2);
    PlayerTextDrawColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 255);
    PlayerTextDrawBoxColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 200);
    PlayerTextDrawUseBox(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetProportional(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetSelectable(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]++], 0);

    CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, 322.000000, 128.000000, "_");
    PlayerTextDrawFont(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawLetterSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0.600000, 1.700003);
    PlayerTextDrawTextSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 298.500000, 375.000000);
    PlayerTextDrawSetOutline(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetShadow(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0);
    PlayerTextDrawAlignment(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 2);
    PlayerTextDrawColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 255);
    PlayerTextDrawBoxColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1097458120);
    PlayerTextDrawUseBox(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetProportional(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetSelectable(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]++], 0);

    CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, 322.000000, 363.000000, "_");
    PlayerTextDrawFont(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawLetterSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0.600000, 1.700003);
    PlayerTextDrawTextSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 298.500000, 375.000000);
    PlayerTextDrawSetOutline(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetShadow(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0);
    PlayerTextDrawAlignment(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 2);
    PlayerTextDrawColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 255);
    PlayerTextDrawBoxColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1097458120);
    PlayerTextDrawUseBox(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetProportional(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetSelectable(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]++], 0);

    CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, 323.000000, 128.000000, "WEAPON CRAFT");
    PlayerTextDrawFont(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 2);
    PlayerTextDrawLetterSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0.220833, 1.500000);
    PlayerTextDrawTextSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 400.000000, 292.000000);
    PlayerTextDrawSetOutline(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetShadow(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0);
    PlayerTextDrawAlignment(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 2);
    PlayerTextDrawColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], -1);
    PlayerTextDrawBackgroundColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 255);
    PlayerTextDrawBoxColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 50);
    PlayerTextDrawUseBox(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0);
    PlayerTextDrawSetProportional(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetSelectable(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]++], 0);

    CraftTypeTextDrawID[playerid][E_CRAFT_TEXTDRAW_CLOSE] = CraftTypeTextDrawCount[playerid];
    CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, 485.000000, 131.000000, "CLOSE");
    PlayerTextDrawFont(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 2);
    PlayerTextDrawLetterSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0.158333, 1.100000);
    PlayerTextDrawTextSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 16.500000, 41.500000);
    PlayerTextDrawSetOutline(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetShadow(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0);
    PlayerTextDrawAlignment(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 2);
    PlayerTextDrawColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], -16776961);
    PlayerTextDrawBackgroundColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 255);
    PlayerTextDrawBoxColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 200);
    PlayerTextDrawUseBox(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetProportional(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
    PlayerTextDrawSetSelectable(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]++], 1);

    for (new i; i < MAX_CRAFT_MENU_ROWS; i++)
	{
        CraftTypeTextDrawID[playerid][E_CRAFT_MODEL][i] = CraftTypeTextDrawCount[playerid];
        CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, (141.000000 + (i * 46.000000)), 159.000000, "Preview_Model");
        PlayerTextDrawFont(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 5);
        PlayerTextDrawLetterSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 40.000000, 42.000000);
        PlayerTextDrawSetOutline(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0);
        PlayerTextDrawSetShadow(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0);
        PlayerTextDrawAlignment(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
        PlayerTextDrawColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], -1);
        PlayerTextDrawBackgroundColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], -1061109635);
        PlayerTextDrawBoxColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], -1061109505);
        PlayerTextDrawUseBox(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0);
        PlayerTextDrawSetProportional(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
        PlayerTextDrawSetPreviewModel(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 336);
        PlayerTextDrawSetPreviewRot(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 221.000000, 155.000000, 53.000000, 1.330000);
        PlayerTextDrawSetPreviewVehCol(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1, 1);
        PlayerTextDrawSetSelectable(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]++], 1);

        CraftTypeTextDrawID[playerid][E_CRAFT_TEXT][i] = CraftTypeTextDrawCount[playerid];
        CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, (162.000000 + (i * 46.000000)), 204.000000, "Baseball bat");
        PlayerTextDrawFont(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 2);
        PlayerTextDrawLetterSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0.112499, 0.850001);
        PlayerTextDrawTextSize(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 400.000000, 292.000000);
        PlayerTextDrawSetOutline(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
        PlayerTextDrawSetShadow(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0);
        PlayerTextDrawAlignment(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 2);
        PlayerTextDrawColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], -1);
        PlayerTextDrawBackgroundColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 255);
        PlayerTextDrawBoxColor(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 50);
        PlayerTextDrawUseBox(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 0);
        PlayerTextDrawSetProportional(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]], 1);
        PlayerTextDrawSetSelectable(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawCount[playerid]++], 0);
    }
    return 1;
}

#define MAX_WEAPONCRAFT (24)
enum weaponcraftdata{
    weaponcraftID,
    weaponcraftEx,
    weaponcraftModel,
    weaponcraftType,
    weaponcraftName[32],
    weaponcraftGunpowder,
    weaponcraftWood,
    weaponcraftOre,
    weaponcraftMoney,
    weaponcraftLevelSkills
};
new WeaponCraftData[MAX_WEAPONCRAFT][weaponcraftdata], Count_WeaponCraft;

forward WeaponCraft_Load();
public WeaponCraft_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_WEAPONCRAFT)
	{
	    WeaponCraftData[i][weaponcraftEx] = true;

	    cache_get_value_name_int(i, "weaponcraftID", WeaponCraftData[i][weaponcraftID]);
        cache_get_value_name_int(i, "weaponcraftModel", WeaponCraftData[i][weaponcraftModel]);
        cache_get_value_name_int(i, "weaponcraftType", WeaponCraftData[i][weaponcraftType]);
	    cache_get_value_name(i, "weaponcraftName", WeaponCraftData[i][weaponcraftName], 32);
	    cache_get_value_name_int(i, "weaponcraftGunpowder", WeaponCraftData[i][weaponcraftGunpowder]);
	    cache_get_value_name_int(i, "weaponcraftWood", WeaponCraftData[i][weaponcraftWood]);
	    cache_get_value_name_int(i, "weaponcraftOre", WeaponCraftData[i][weaponcraftOre]);
        cache_get_value_name_int(i, "weaponcraftMoney", WeaponCraftData[i][weaponcraftMoney]);
	    cache_get_value_name_int(i, "weaponcraftLevelSkills", WeaponCraftData[i][weaponcraftLevelSkills]);

        Count_WeaponCraft++;

	}
	printf("(( [MYSQL]: Load %d WeaponCrafts Successfully ))", Count_WeaponCraft);
	return 1;
}

WeaponCraft_Save(weaponcraftid)
{
	new
	    query[1536];

	mysql_format(dbCon, query, sizeof(query), "UPDATE `weaponcrafts` SET `weaponcraftModel` = '%d', `weaponcraftType` = '%d', `weaponcraftName` = '%e', `weaponcraftGunpowder` = '%d', `weaponcraftWood` = '%d', `weaponcraftOre` = '%d', `weaponcraftMoney` = '%d', `weaponcraftLevelSkills` = '%d' WHERE `weaponcraftID` = '%d'",
		WeaponCraftData[weaponcraftid][weaponcraftModel],
        WeaponCraftData[weaponcraftid][weaponcraftType],
        WeaponCraftData[weaponcraftid][weaponcraftName],
	    WeaponCraftData[weaponcraftid][weaponcraftGunpowder],
	    WeaponCraftData[weaponcraftid][weaponcraftWood],
        WeaponCraftData[weaponcraftid][weaponcraftOre],
        WeaponCraftData[weaponcraftid][weaponcraftMoney],
        WeaponCraftData[weaponcraftid][weaponcraftLevelSkills],
        WeaponCraftData[weaponcraftid][weaponcraftID]
	);
	return mysql_tquery(dbCon, query);
}

GetPowForPlayer(playerid, jobid){
    if(PlayerData[playerid][pJob] != WEAPONDEALERJOB)
        return 0;

    new string[128];
    PlayerGetPricePow[playerid] = JobData[jobid][jobDeliverPrice];
    PlayerGetIDPow[playerid] = jobid;
    format(string, sizeof(string), "คุณต้องการที่จะวิ่งดินปืนจำนวน 2 ถุงและคุณจำเป็นต้องจ่ายเงินจำนวน %s ในการวิ่งดินปืนครั้งนี้\nคุณต้องการจะวิ่งดินปืนหรือไม่?", FormatNumber(JobData[jobid][jobDeliverPrice]));
    Dialog_ShowEasy(playerid, DIALOG_GETPOW, DIALOG_STYLE_MSGBOX, "การวิ่งดินปืน", string, "ตกลง", "ยกเลิก");
    return 1;
}

Dialog:DIALOG_GETPOW(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new price = PlayerGetPricePow[playerid];

        if(GetMoney(playerid) < price)
            return ErrorMsg(playerid, "คุณมีเงินไม่พอ");

        PlayerGetPow[playerid] = 1;
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ทำการรับการวิ่งดินปืนแล้วและคุณได้จ่ายเงินสำหรับการวิ่งครั้งนี้ไป %s", FormatNumber(price));
        SendClientMessage(playerid, COLOR_YELLOW, "(( ไปยังจุดสีแดงในแผนที่เพื่อรับถุงดินปืนของคุณ ))");
        GiveMoney(playerid, - PlayerGetPricePow[playerid], "get pow");
        SetPlayerAttachedObject(playerid,8,1575,1,0.086000,-0.023999,0.000000,99.700027,-12.199998,0.000000,1.000000,1.000000,1.000000);

        PlayerData[playerid][pSavePow] = 1;

        new id = PlayerGetIDPow[playerid];

        if (id != -1)
        {
            if(JobData[id][jobDeliver][0] == 0.0 && JobData[id][jobDeliver][1] == 0.0 && JobData[id][jobDeliver][2] == 0.0)
                return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

            SetPlayerCheckpoint(playerid, JobData[id][jobDeliver][0], JobData[id][jobDeliver][1], JobData[id][jobDeliver][2],3.0);
            SendClientMessage(playerid, -1,"คุณได้เปิด GPS ไปยัง จุดรับดินปืนแล้ว");
        }
    }
    return 1;
}

FixLoadPowCrash(playerid){
    PlayerGetPow[playerid] = 1;
    SendClientMessage(playerid, COLOR_RED, "[ระบบกันหลุด]: ไปยังจุดสีแดงในแผนที่เพื่อรับถุงดินปืนของคุณ");
    SetPlayerAttachedObject(playerid,8,1575,1,0.086000,-0.023999,0.000000,99.700027,-12.199998,0.000000,1.000000,1.000000,1.000000);

    PlayerData[playerid][pSavePow] = 1;

    for(new i=0; i<MAX_DYNAMIC_JOBS; i++) if(JobData[i][jobExists]){
        if(JobData[i][jobType] == WEAPONDEALERJOB) PlayerGetIDPow[playerid] = i;
    }

    new id = PlayerGetIDPow[playerid];

    if (id != -1)
    {
        if(JobData[id][jobDeliver][0] == 0.0 && JobData[id][jobDeliver][1] == 0.0 && JobData[id][jobDeliver][2] == 0.0)
            return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

        SetPlayerCheckpoint(playerid, JobData[id][jobDeliver][0], JobData[id][jobDeliver][1], JobData[id][jobDeliver][2],3.0);
        SendClientMessage(playerid, -1,"คุณได้เปิด GPS ไปยัง จุดรับดินปืนแล้ว");
    }
    return 1;
}

forward SetPlayerStartCraftWeapon(playerid);
public SetPlayerStartCraftWeapon(playerid){
    new id = PlayerGetIndexWeaponCraft[playerid];

    if(id == -1){
        ResetWeaponDealerJob(playerid);
        return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
    }
    
    if(WeaponCraftData[id][weaponcraftEx]){

        if(PlayerData[playerid][pStorageWeaponCraft][0] < WeaponCraftData[id][weaponcraftGunpowder])
            return ErrorMsg(playerid, "คุณมี ดินปืน ในคลัง ไม่พอ");

        if(PlayerData[playerid][pStorageWeaponCraft][1] < WeaponCraftData[id][weaponcraftWood])
            return ErrorMsg(playerid, "คุณมี ไม้ ในคลัง ไม่พอ");

        if(PlayerData[playerid][pStorageWeaponCraft][2] < WeaponCraftData[id][weaponcraftOre])
            return ErrorMsg(playerid, "คุณมี เหล็ก ในคลัง ไม่พอ");

        if(GetMoney(playerid) < WeaponCraftData[id][weaponcraftMoney])
            return ErrorMsg(playerid, "คุณมี เงิน ไม่พอ");

        TogglePlayerControllable(playerid, 0);
        //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0xFF3600AA, 100.000000, 0);
        CreatePlayerProgressbar_Job(playerid, 0xFF3600AA);
        CraftWeaponPoint[playerid] = 0;
        StartingCraftWeapon[playerid] = 1;
        new rands = random(50);
        PlayerOpenMenuTime[playerid] = rands;
        CraftWeaponTimer[playerid] = SetTimerEx("CraftingWeapon", 500, false, "ii", playerid, id);
    }
    return 1;
}

forward CraftingWeapon(playerid, weaponid);
public CraftingWeapon(playerid, weaponid){
    new string[128];
    if(LoggedIn[playerid]){
        if(weaponid != -1){
            if(CraftWeaponPoint[playerid] < 100){
                if(StartingCraftWeapon[playerid] == 1){
                    CraftWeaponPoint[playerid] += 10;
                    SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], CraftWeaponPoint[playerid]);
                    format(string,sizeof(string),"Weapon Crafting... (%d)", CraftWeaponPoint[playerid]);
                    PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
                    //GameTextForPlayer(playerid, string, 1500, 3);
                    TogglePlayerControllable(playerid, 0);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
                    CraftWeaponTimer[playerid] = SetTimerEx("CraftingWeapon", 500, false, "ii", playerid, weaponid);
                }
            }
            else if(CraftWeaponPoint[playerid] >= 100){
                if(StartingCraftWeapon[playerid] == 1){
                    StartingCraftWeapon[playerid] = 0;
                    TogglePlayerControllable(playerid, 1);
                    KillTimer(CraftWeaponTimer[playerid]);
                    ResetWeaponDealerJob(playerid);
                    DestroyPlayerProgressbar_Job(playerid);

                    PlayerData[playerid][pStorageWeaponCraft][0] -= WeaponCraftData[weaponid][weaponcraftGunpowder];
                    PlayerData[playerid][pStorageWeaponCraft][1] -= WeaponCraftData[weaponid][weaponcraftWood];
                    PlayerData[playerid][pStorageWeaponCraft][2] -= WeaponCraftData[weaponid][weaponcraftOre];

                    GiveMoney(playerid, -WeaponCraftData[weaponid][weaponcraftMoney], "craft weapon");

                    SendClientMessage(playerid, COLOR_DARKGREEN, "|---------------------------------------------------------------|");
                    SendClientMessageEx(playerid, -1, "- คุณเสีย ดินปืน - %d", WeaponCraftData[weaponid][weaponcraftGunpowder]);
                    SendClientMessageEx(playerid, -1, "- คุณเสีย ไม้ - %d", WeaponCraftData[weaponid][weaponcraftWood]);
                    SendClientMessageEx(playerid, -1, "- คุณเสีย เหล็ก - %d", WeaponCraftData[weaponid][weaponcraftOre]);
                    StartRandomCraftWeapon(playerid, weaponid);
                    SendClientMessage(playerid, COLOR_DARKGREEN, "|---------------------------------------------------------------|");
                    HideWeaponCraftInfo(playerid);
                }
            }
        }
    }
    return 1;
}

CorrectCraftWeapon(playerid, weaponid){
    new string[160];

	new id = PlayerInventory_AddItem(playerid, WeaponCraftData[weaponid][weaponcraftName], WeaponCraftData[weaponid][weaponcraftModel], 1, 0, 0);
	if (id == -1){
		return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
	}
	format(string, sizeof(string), "ผู้เล่น %s คราฟอาวุธ '%s' ติด", ReturnRoleplayName(playerid), WeaponCraftData[weaponid][weaponcraftName]);
	SendAdminsMessage(1, COLOR_GRAY, string);
    format(string, sizeof(string), "```- [%s] Player %s Craft Weapon [%s] Successfully```", ReturnDate(), ReturnRoleplayName(playerid), WeaponCraftData[weaponid][weaponcraftName]);
    DCC_SendChannelMessage(CraftWeapon, string);
    Log_Write("logs/craftweapon.txt", "[%s] [%s] Craft [%s] Successfully", ReturnDate(), ReturnRoleplayName(playerid), WeaponCraftData[weaponid][weaponcraftName]);
	return SendClientMessageEx(playerid, COLOR_GREEN, "- คุณได้รับอาวุธ '%s' จำนวน 1 ชิ้น", WeaponCraftData[weaponid][weaponcraftName]);
}

StartRandomCraftWeapon(playerid, weaponid){
    new rands = random(1000);
    new randstime = random(48);
    //printf("rands: %d, randstime: %d", rands, randstime);
    new ratetime = PlayerOpenMenuTime[playerid];
    if ((ratetime >= randstime && ratetime <= randstime+2)){
        if((rands >= 100 && rands <= 159) || (rands >= 301 && rands <= 350) || (rands >= 449 && rands <= 508) || (rands >= 941 && rands <= 1000)){
            CorrectCraftWeapon(playerid, weaponid);
            StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "https://www.mboxdrive.com/correctweapon.mp3");
        }
        else {
            SendClientMessage(playerid, COLOR_RED, "- คุณไม่ได้รับอะไรจากการคราฟครั้งนี้เลย!!");
            StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "https://www.mboxdrive.com/notcorrectweapon.mp3");
        }
    }
    else{
        if((rands >= 100 && rands <= 159) || (rands >= 449 && rands <= 508) || (rands >= 941 && rands <= 1000)){
            CorrectCraftWeapon(playerid, weaponid);
            StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "https://www.mboxdrive.com/correctweapon.mp3");
        }
        else {
            SendClientMessage(playerid, COLOR_RED, "- คุณไม่ได้รับอะไรจากการคราฟครั้งนี้เลย!!");
            StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "https://www.mboxdrive.com/notcorrectweapon.mp3");
        }
    }
    PlayerOpenMenuTime[playerid] = 0;
    return 1;
}

forward ShowWeaponCraftInfo(playerid);
public ShowWeaponCraftInfo(playerid){
    LoadPlayerCraftInfoTextDraw(playerid);

    new id = PlayerGetIndexWeaponCraft[playerid];
    new string[128];
    if(id != -1){
        if(WeaponCraftData[id][weaponcraftEx]){
            PlayerTextDrawSetPreviewModel(playerid, CraftWeaponInfo[playerid][2], WeaponCraftData[id][weaponcraftModel]);
            format(string, sizeof(string), "%s", WeaponCraftData[id][weaponcraftName]);
            PlayerTextDrawSetString(playerid, CraftWeaponInfo[playerid][3], string);
            format(string, sizeof(string), "Gun Powder (%d EA)", WeaponCraftData[id][weaponcraftGunpowder]);
            PlayerTextDrawSetString(playerid, CraftWeaponInfo[playerid][8], string);
            format(string, sizeof(string), "Wood (%d EA)", WeaponCraftData[id][weaponcraftWood]);
            PlayerTextDrawSetString(playerid, CraftWeaponInfo[playerid][10], string);
            format(string, sizeof(string), "Ore (%d EA)", WeaponCraftData[id][weaponcraftOre]);
            PlayerTextDrawSetString(playerid, CraftWeaponInfo[playerid][12], string);
            format(string, sizeof(string), "Money (%s)", FormatNumber(WeaponCraftData[id][weaponcraftMoney]));
            PlayerTextDrawSetString(playerid, CraftWeaponInfo[playerid][14], string);
        }
    }

    for(new i=0; i<15; i++) PlayerTextDrawShow(playerid, CraftWeaponInfo[playerid][i]);

    PlayerOpenCraftWeaponInfoMenu[playerid] = 1;
    SelectTextDraw(playerid, 0xFFB900AA);
    return 1;
}

HideWeaponCraftInfo(playerid){
    for (new i; i < 15; i++){
  		PlayerTextDrawHide(playerid, CraftWeaponInfo[playerid][i]);
		PlayerTextDrawDestroy(playerid, CraftWeaponInfo[playerid][i]);
    }
    TogglePlayerControllable(playerid, 1);
    StartingCraftWeapon[playerid] = 0;
    CraftTypeTextDrawCount[playerid] = 0;
    CancelSelectTextDraw(playerid);
    ResetWeaponDealerJob(playerid);
    return 1;
}

HidePlayerCraftWeaponMenu(playerid){
    for (new i; i < CraftTypeTextDrawCount[playerid]; i++){
  		PlayerTextDrawHide(playerid, CraftTypeTextDraw[playerid][i]);
		PlayerTextDrawDestroy(playerid, CraftTypeTextDraw[playerid][i]);
    }
    CraftTypeTextDrawCount[playerid] = 0;
    StartingCraftWeapon[playerid] = 0;
    CancelSelectTextDraw(playerid);
    ResetWeaponDealerJob(playerid);
    return 1;
}

CraftWeaponMenu(playerid){
    LoadPlayerCraftTypeTextDraw(playerid);
    new bool:skip;
    for (new i; i < CraftTypeTextDrawCount[playerid]; i++)
    {
        for (new x; x < MAX_CRAFT_MENU_ROWS; x++)
	    {
	        if (CraftTypeTextDrawID[playerid][E_CRAFT_MODEL][x] == i)
	        {
	            skip = true;
	            break;
			}
		}

        for (new x; x < MAX_CRAFT_MENU_ROWS; x++)
	    {
            if (CraftTypeTextDrawID[playerid][E_CRAFT_TEXT][x] == i)
	        {
	            skip = true;
	            break;
			}
		}

		if (skip)
		{
		    skip = false;
		    continue;
		}
        PlayerTextDrawShow(playerid, CraftTypeTextDraw[playerid][i]);
    }

    UpdateCraftWeaponMenu(playerid);
    PlayerOpenCraftWeaponMenu[playerid] = 1;
    PlayerOpenMenuTime[playerid] = 0;
    SelectTextDraw(playerid, 0xFFB900AA);
    return 1;
}

ShowPlayerCraftWeaponMenu(playerid){
    Dialog_ShowEasy(playerid, CraftMenuWeapon, DIALOG_STYLE_LIST, "คราฟอาวุธ", "- คราฟอาวุธ\n- คลังวัตถุดิบสำหรับคราฟอาวุธ", "เลือก", "ยกเลิก");
    return 1;
}

Dialog:CraftMenuWeapon(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[128];
        if(listitem == 0){
            CraftWeaponMenu(playerid);
        }
        if(listitem == 1){
            format(string, sizeof(string), "ดินปืน ในคลัง\t[%d]\nท่อนไม้ ในคลัง\t[%d]\nเหล็ก ในคลัง\t[%d]", PlayerData[playerid][pStorageWeaponCraft][0], PlayerData[playerid][pStorageWeaponCraft][1], PlayerData[playerid][pStorageWeaponCraft][2]);
            Dialog_ShowEasy(playerid, StorageCraftWeapon, DIALOG_STYLE_LIST, "คลังวัตถุดิบสำหรับคราฟอาวุธ", string, "เลือก", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:StorageCraftWeapon(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new caption[128];
        if(listitem == 0){
            format(caption, sizeof(caption), "ดินปืนในคลัง [%d]", PlayerData[playerid][pStorageWeaponCraft][0]);
            Dialog_ShowEasy(playerid, ManageGunPowder, DIALOG_STYLE_LIST, caption, "เก็บใส่คลัง\nเบิกออกจากคลัง", "เลือก", "ยกเลิก");
        }
        if(listitem == 1){
            format(caption, sizeof(caption), "ไม้ในคลัง [%d]", PlayerData[playerid][pStorageWeaponCraft][1]);
            Dialog_ShowEasy(playerid, ManageWood, DIALOG_STYLE_LIST, caption, "เก็บใส่คลัง\nเบิกออกจากคลัง", "เลือก", "ยกเลิก");
        }
        if(listitem == 2){
            format(caption, sizeof(caption), "เหล็กในคลัง [%d]", PlayerData[playerid][pStorageWeaponCraft][2]);
            Dialog_ShowEasy(playerid, ManageOre, DIALOG_STYLE_LIST, caption, "เก็บใส่คลัง\nเบิกออกจากคลัง", "เลือก", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:ManageOre(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new caption[128];
        if(listitem == 0){
            new count = PlayerInventory_AllCount(playerid, "Ore");
            format(caption, sizeof(caption), "เหล็กในตัว [%d]", count);
            Dialog_ShowEasy(playerid, StoreOre, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            format(caption, sizeof(caption), "เหล็กในคลัง [%d]", PlayerData[playerid][pStorageWeaponCraft][2]);
            Dialog_ShowEasy(playerid, TakeOre, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:StoreOre(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new count = PlayerInventory_AllCount(playerid, "Ore");

        new caption[128];
        
        if(amount <= 0){
            format(caption, sizeof(caption), "เหล็กในตัว [%d]", count);
            return Dialog_ShowEasy(playerid, StoreOre, DIALOG_STYLE_INPUT, caption, "* คุณต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }

        if(count < amount){
            format(caption, sizeof(caption), "เหล็กในตัว [%d]", count);
            return Dialog_ShowEasy(playerid, StoreOre, DIALOG_STYLE_INPUT, caption, "* คุณมีเหล็กในตัวไม่พอ *\nกรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }

        if(PlayerData[playerid][pStorageWeaponCraft][2] + amount > 2000)
            return ErrorMsg(playerid, "เหล็กในคลังของคุณเต็มแล้ว");

        PlayerInventory_Remove(playerid, "Ore", amount);
        PlayerData[playerid][pStorageWeaponCraft][2] += amount;
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เก็บ เหล็ก จำนวน %d เข้าคลังเรียบร้อยแล้ว", amount);
    }
    return 1;
}

Dialog:TakeOre(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new count = PlayerData[playerid][pStorageWeaponCraft][2];

        new caption[128];
        if(amount <= 0){
            format(caption, sizeof(caption), "เหล็กในคลัง [%d]", count);
            return Dialog_ShowEasy(playerid, TakeOre, DIALOG_STYLE_INPUT, caption, "* คุณต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }

        if(count < amount){
            format(caption, sizeof(caption), "เหล็กในคลัง [%d]", count);
            return Dialog_ShowEasy(playerid, TakeOre, DIALOG_STYLE_INPUT, caption, "* คุณมีเหล็กในคลังไม่พอ *\nกรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }

        /*if(PlayerInventory_AllCount(playerid, "Ore") + amount > PlayerData[playerid][pItemAmount])
            return ErrorMsg(playerid, "กระเป๋าของคุณมีพื้นที่ไม่พอเก็บ");*/

        new id = PlayerInventory_AddItem(playerid, "Ore", 19941, amount);
        if (id == -1)
            return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

        PlayerData[playerid][pStorageWeaponCraft][2] -= amount;
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้หยิบ เหล็ก จำนวน %d ออกจากคลังเรียบร้อยแล้ว", amount);
    }
    return 1;
}

Dialog:ManageWood(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new caption[128];
        if(listitem == 0){
            new count = PlayerInventory_AllCount(playerid, "Wood");
            format(caption, sizeof(caption), "ไม้ในตัว [%d]", count);
            Dialog_ShowEasy(playerid, StoreWood, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            format(caption, sizeof(caption), "ไม้ในคลัง [%d]", PlayerData[playerid][pStorageWeaponCraft][1]);
            Dialog_ShowEasy(playerid, TakeWood, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:StoreWood(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new count = PlayerInventory_AllCount(playerid, "Wood");

        new caption[128];
        if(amount <= 0){
            format(caption, sizeof(caption), "ไม้ในตัว [%d]", count);
            return Dialog_ShowEasy(playerid, StoreWood, DIALOG_STYLE_INPUT, caption, "* คุณต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }

        if(count < amount){
            format(caption, sizeof(caption), "ไม้ในตัว [%d]", count);
            return Dialog_ShowEasy(playerid, StoreWood, DIALOG_STYLE_INPUT, caption, "* คุณมีไม้ในตัวไม่พอ *\nกรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }

        if(PlayerData[playerid][pStorageWeaponCraft][1] + amount > 2000)
            return ErrorMsg(playerid, "ไม้ในคลังของคุณเต็มแล้ว");

        PlayerInventory_Remove(playerid, "Wood", amount);
        PlayerData[playerid][pStorageWeaponCraft][1] += amount;
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เก็บ ไม้ จำนวน %d เข้าคลังเรียบร้อยแล้ว", amount);
    }
    return 1;
}

Dialog:TakeWood(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new count = PlayerData[playerid][pStorageWeaponCraft][1];

        new caption[128];
        if(amount <= 0){
            format(caption, sizeof(caption), "ไม้ในคลัง [%d]", count);
            return Dialog_ShowEasy(playerid, TakeWood, DIALOG_STYLE_INPUT, caption, "* คุณต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }

        if(count < amount){
            format(caption, sizeof(caption), "ไม้ในคลัง [%d]", count);
            return Dialog_ShowEasy(playerid, TakeWood, DIALOG_STYLE_INPUT, caption, "* คุณมีไม้ในคลังไม่พอ *\nกรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }

        /*if(PlayerInventory_AllCount(playerid, "Wood") + amount > PlayerData[playerid][pItemAmount])
            return ErrorMsg(playerid, "กระเป๋าของคุณมีพื้นที่ไม่พอเก็บ");*/

        new id = PlayerInventory_AddItem(playerid, "Wood", 19793, amount);
        if (id == -1)
            return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

        PlayerData[playerid][pStorageWeaponCraft][1] -= amount;
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้หยิบ ไม้ จำนวน %d ออกจากคลังเรียบร้อยแล้ว", amount);
    }
    return 1;
}

Dialog:ManageGunPowder(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new caption[128];
        if(listitem == 0){
            new count = PlayerInventory_AllCount(playerid, "Gun Powder");
            format(caption, sizeof(caption), "ดินปืนในตัว [%d]", count);
            Dialog_ShowEasy(playerid, StoreGunPowder, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            format(caption, sizeof(caption), "ดินปืนในคลัง [%d]", PlayerData[playerid][pStorageWeaponCraft][0]);
            Dialog_ShowEasy(playerid, TakeGunPowder, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:StoreGunPowder(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new count = PlayerInventory_AllCount(playerid, "Gun Powder");

        new caption[128];
        if(amount <= 0){
            format(caption, sizeof(caption), "ดินปืนในตัว [%d]", count);
            return Dialog_ShowEasy(playerid, StoreGunPowder, DIALOG_STYLE_INPUT, caption, "* คุณต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }

        if(count < amount){
            format(caption, sizeof(caption), "ดินปืนในตัว [%d]", count);
            return Dialog_ShowEasy(playerid, StoreGunPowder, DIALOG_STYLE_INPUT, caption, "* คุณมีดินปืนในตัวไม่พอ *\nกรอกจำนวนที่ต้องการจะเก็บเข้าคลัง:", "ตกลง", "ยกเลิก");
        }

        if(PlayerData[playerid][pStorageWeaponCraft][0] + amount > 2000)
            return ErrorMsg(playerid, "ดินปืนในคลังของคุณเต็มแล้ว");

        PlayerInventory_Remove(playerid, "Gun Powder", amount);
        PlayerData[playerid][pStorageWeaponCraft][0] += amount;
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เก็บ ดินปืน จำนวน %d เข้าคลังเรียบร้อยแล้ว", amount);
    }
    return 1;
}

Dialog:TakeGunPowder(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new count = PlayerData[playerid][pStorageWeaponCraft][0];

        new caption[128];
        if(amount <= 0){
            format(caption, sizeof(caption), "ดินปืนในคลัง [%d]", count);
            return Dialog_ShowEasy(playerid, TakeGunPowder, DIALOG_STYLE_INPUT, caption, "* คุณต้องกรอกจำนวนมากกว่า 0 *\nกรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }

        if(count < amount){
            format(caption, sizeof(caption), "ดินปืนในคลัง [%d]", count);
            return Dialog_ShowEasy(playerid, TakeGunPowder, DIALOG_STYLE_INPUT, caption, "* คุณมีดินปืนในคลังไม่พอ *\nกรอกจำนวนที่ต้องการจะหยิบออกจากคลัง:", "ตกลง", "ยกเลิก");
        }

        new id = PlayerInventory_AddItem(playerid, "Gun Powder", 2057, amount);
        if (id == -1)
            return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

        PlayerData[playerid][pStorageWeaponCraft][0] -= amount;
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้หยิบ ดินปืน จำนวน %d ออกจากคลังเรียบร้อยแล้ว", amount);
    }
    return 1;
}

UpdateCraftWeaponMenu(playerid){
    new
		string[128],
        level = PlayerData[playerid][pWeaponDealerSkills];

	if(level == 0){
        for (new i; i < MAX_CRAFT_MENU_ROWS; i++){
			PlayerTextDrawHide(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawID[playerid][E_CRAFT_MODEL][i]]);
            PlayerTextDrawHide(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawID[playerid][E_CRAFT_TEXT][i]]);
        }
    }
    else{
        for (new i=0; i < MAX_CRAFT_MENU_ROWS; i++){
            if(WeaponCraftData[i][weaponcraftEx]){
                if(WeaponCraftData[i][weaponcraftLevelSkills] <= level){
                    PlayerTextDrawSetPreviewModel(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawID[playerid][E_CRAFT_MODEL][i]], WeaponCraftData[i][weaponcraftModel]);
                    PlayerTextDrawShow(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawID[playerid][E_CRAFT_MODEL][i]]);
                    format(string, sizeof(string), "%s", WeaponCraftData[i][weaponcraftName]);
                    PlayerTextDrawSetString(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawID[playerid][E_CRAFT_TEXT][i]], string);
                    PlayerTextDrawShow(playerid, CraftTypeTextDraw[playerid][CraftTypeTextDrawID[playerid][E_CRAFT_TEXT][i]]);
                }
            }
        }
    }
    return 1;
}

ViewWeaponCrafts(playerid){
    Dialog_ShowEasy(playerid, ShowWeaponCraftType, DIALOG_STYLE_LIST, "ปรับแต่งการคราฟอาวุธ", "- อาวุธประชิด\n- อาวุธปืนเบา\n- อาวุธปืนหนัก", "เลือก", "ยกเลิก");
    return 1;
}

Dialog:ShowWeaponCraftType(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new string[2048], menu[20], count;

            format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

            SetPVarInt(playerid, "page", 1);

            for(new i=0; i<MAX_WEAPONCRAFT; i++)
            {
                if(WeaponCraftData[i][weaponcraftEx] && WeaponCraftData[i][weaponcraftType] == 1)
                {
                    if(count == 20)
                    {
                        format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                        break;
                    }
                    format(menu, 20, "menu%d", ++count);
                    SetPVarInt(playerid, menu, i);
                    format(string, sizeof(string), "%s(%i) | %s [Model: %d | Level: %d]\n", string, i, WeaponCraftData[i][weaponcraftName], WeaponCraftData[i][weaponcraftModel], WeaponCraftData[i][weaponcraftLevelSkills]);
                }
            }
            if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "รายชื่ออาวุธประชิด", "ไม่พบข้อมูลอาวุธ...", "ปิด", "");
            else Dialog_ShowEasy(playerid, WeaponCraftList1, DIALOG_STYLE_LIST, "รายชื่ออาวุธประชิด", string, "แก้ไข", "กลับ");
        }
        if(listitem == 1){
            new string[2048], menu[20], count;

            format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

            SetPVarInt(playerid, "page", 1);

            for(new i=0; i<MAX_WEAPONCRAFT; i++)
            {
                if(WeaponCraftData[i][weaponcraftEx] && WeaponCraftData[i][weaponcraftType] == 2)
                {
                    if(count == 20)
                    {
                        format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                        break;
                    }
                    format(menu, 20, "menu%d", ++count);
                    SetPVarInt(playerid, menu, i);
                    format(string, sizeof(string), "%s(%i) | %s [Model: %d | Level: %d]\n", string, i, WeaponCraftData[i][weaponcraftName], WeaponCraftData[i][weaponcraftModel], WeaponCraftData[i][weaponcraftLevelSkills]);
                }
            }
            if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "รายชื่ออาวุธปืนเบา", "ไม่พบข้อมูลอาวุธ...", "ปิด", "");
            else Dialog_ShowEasy(playerid, WeaponCraftList2, DIALOG_STYLE_LIST, "รายชื่ออาวุธปืนเบา", string, "แก้ไข", "กลับ");
        }
    }
    return 1;
}

Dialog:WeaponCraftList1(playerid, response, listitem, inputtext[])
{
	if(response) {

		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "weaponcraft1editID", GetPVarInt(playerid, str_biz));
			ShowPlayerEditWeaponCraft1(playerid);
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

		for(new i=0; i<MAX_WEAPONCRAFT; i++)
        {
            if(WeaponCraftData[i][weaponcraftEx] && WeaponCraftData[i][weaponcraftType] == 1){
                if(skipitem)
                {
                    skipitem--;
                    continue;
                }
                if(count == 20)
                {
                    format(string, sizeof(string), "%s{B4B5B7}หน้า %d\n", string, (currentPage==1) ? 1 : currentPage+1);
                    break;
                }
                format(menu, 20, "menu%d", ++count);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s(%i) | %s [Model: %d | Level: %d]\n", string, i, WeaponCraftData[i][weaponcraftName], WeaponCraftData[i][weaponcraftModel], WeaponCraftData[i][weaponcraftLevelSkills]);

            }
		}

		Dialog_ShowEasy(playerid, WeaponCraftList1, DIALOG_STYLE_LIST, "รายชื่ออาวุธประชิด", string, "แก้ไข", "กลับ");
	}
	return 1;
}

ShowPlayerEditWeaponCraft1(playerid)
{
    new id = GetPVarInt(playerid, "weaponcraft1editID");
	new caption[128], dialog_str[1024];
	format(caption, sizeof(caption), "แก้ไขอาวุธ: %s (Model :%d | Level: %d)", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftModel], WeaponCraftData[id][weaponcraftLevelSkills]);
    format(dialog_str, sizeof dialog_str, "ชื่ออาวุธ\t%s\n", WeaponCraftData[id][weaponcraftName]);
	format(dialog_str, sizeof dialog_str, "%s โมเดลอาวุธ\t%d\n", dialog_str, WeaponCraftData[id][weaponcraftModel]);
    format(dialog_str, sizeof dialog_str, "%s ใช้ดินปืน\t%d\n", dialog_str, WeaponCraftData[id][weaponcraftGunpowder]);
	format(dialog_str, sizeof dialog_str, "%s ใช้ไม้\t%d\n", dialog_str, WeaponCraftData[id][weaponcraftWood]);
    format(dialog_str, sizeof dialog_str, "%s ใช้เหล็ก\t%d\n", dialog_str, WeaponCraftData[id][weaponcraftOre]);
    format(dialog_str, sizeof dialog_str, "%s ใช้เงิน\t%s\n", dialog_str, FormatNumber(WeaponCraftData[id][weaponcraftMoney]));
	Dialog_ShowEasy(playerid, WeaponCraft1Edit, DIALOG_STYLE_TABLIST, caption, dialog_str, "แก้ไข", "กลับ");
	return 1;
}

Dialog:WeaponCraft1Edit(playerid, response, listitem, inputtext[])
{
	if(response) {

		new caption[128];
        new id = GetPVarInt(playerid, "weaponcraft1editID");
		switch(listitem)
		{
			case 0:
			{
				format(caption, sizeof(caption), "แก้ไข -> ชื่ออาวุธ: %s", WeaponCraftData[id][weaponcraftName]);
				Dialog_ShowEasy(playerid, WeaponCraft1_Name, DIALOG_STYLE_INPUT, caption, "ความยาวของชื่อต้องมากกว่า 0 และไม่เกิน 32 ตัวอักษร\n\nกรอกชื่ออาวุธใหม่ที่ต้องการ:", "เปลี่ยน", "กลับ");
			}
            case 1:
			{
				format(caption, sizeof(caption), "แก้ไข -> โมเดลอาวุธ: %d", WeaponCraftData[id][weaponcraftModel]);
				Dialog_ShowEasy(playerid, WeaponCraft1_Model, DIALOG_STYLE_INPUT, caption, "กรอกโมเดลอาวุธที่ต้องการจะเปลี่ยน:", "เปลี่ยน", "กลับ");
			}
            case 2:
			{
				format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้ดินปืน > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftGunpowder]);
				Dialog_ShowEasy(playerid, WeaponCraft1_Gunpowder, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนดินปืนที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			}
            case 3:
			{
				format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้ไม้ > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftWood]);
				Dialog_ShowEasy(playerid, WeaponCraft1_Wood, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนไม้ที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			}
            case 4:
			{
				format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้เหล็ก > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftOre]);
				Dialog_ShowEasy(playerid, WeaponCraft1_Ore, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนเหล็กที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			}
            case 5:
			{
				format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้เงิน > %s", WeaponCraftData[id][weaponcraftName], FormatNumber(WeaponCraftData[id][weaponcraftMoney]));
				Dialog_ShowEasy(playerid, WeaponCraft1_Money, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนเเงินที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			}
		}
	}
	else
	{
	    DeletePVar(playerid, "weaponcraft1editID");
        ViewWeaponCrafts(playerid);
	}
    return 1;
}

Dialog:WeaponCraft1_Name(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft1editID");

		if(isnull(inputtext) || strlen(inputtext) >= 32) {
			format(caption, sizeof(caption), "แก้ไข -> ชื่ออาวุธ: %s", WeaponCraftData[id][weaponcraftName]);
			Dialog_ShowEasy(playerid, WeaponCraft1_Name, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nความยาวของชื่อต้องมากกว่า 0 และไม่เกิน 32 ตัวอักษร", "เปลี่ยน", "กลับ");
			return 1;
		}
		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนเป็น %s", WeaponCraftData[id][weaponcraftName], inputtext);

		format(WeaponCraftData[id][weaponcraftName], 32, inputtext);
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft1(playerid);
}

Dialog:WeaponCraft1_Model(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft1editID");

		if(isnull(inputtext) || strlen(inputtext) >= 12) {
			format(caption, sizeof(caption), "แก้ไข -> โมเดลอาวุธ: %d", WeaponCraftData[id][weaponcraftModel]);
			Dialog_ShowEasy(playerid, WeaponCraft1_Model, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nกรอกโมเดลอาวุธที่ต้องการจะเปลี่ยน:", "เปลี่ยน", "กลับ");
			return 1;
		}

		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนโมเดลเป็น %s", WeaponCraftData[id][weaponcraftName], inputtext);

        new model = strval(inputtext);

		WeaponCraftData[id][weaponcraftModel] = model;
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft1(playerid);
}

Dialog:WeaponCraft1_Gunpowder(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft1editID");

		if(isnull(inputtext) || strlen(inputtext) >= 12) {
			format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้ดินปืน > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftGunpowder]);
			Dialog_ShowEasy(playerid, WeaponCraft1_Gunpowder, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nกรอกจำนวนดินปืนที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			return 1;
		}

		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนดินปืนที่ใช้คราฟเป็น %s", WeaponCraftData[id][weaponcraftName], inputtext);

        new gunpowder = strval(inputtext);

		WeaponCraftData[id][weaponcraftGunpowder] = gunpowder;
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft1(playerid);
}

Dialog:WeaponCraft1_Wood(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft1editID");

		if(isnull(inputtext) || strlen(inputtext) >= 12) {
			format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้ไม้ > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftWood]);
			Dialog_ShowEasy(playerid, WeaponCraft1_Wood, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nกรอกจำนวนไม้ที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			return 1;
		}

		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนไม้ที่ใช้คราฟเป็น %s", WeaponCraftData[id][weaponcraftName], inputtext);

        new wood = strval(inputtext);

		WeaponCraftData[id][weaponcraftWood] = wood;
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft1(playerid);
}

Dialog:WeaponCraft1_Ore(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft1editID");

		if(isnull(inputtext) || strlen(inputtext) >= 12) {
			format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้เหล็ก > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftOre]);
			Dialog_ShowEasy(playerid, WeaponCraft1_Ore, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nกรอกจำนวนเหล็กที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			return 1;
		}

		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนเหล็กที่ใช้คราฟเป็น %s", WeaponCraftData[id][weaponcraftName], inputtext);

        new Ore = strval(inputtext);

		WeaponCraftData[id][weaponcraftOre] = Ore;
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft1(playerid);
}

Dialog:WeaponCraft1_Money(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft1editID");

		if(isnull(inputtext) || strlen(inputtext) >= 12) {
			format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้เงิน > %s", WeaponCraftData[id][weaponcraftName], FormatNumber(WeaponCraftData[id][weaponcraftMoney]));
			Dialog_ShowEasy(playerid, WeaponCraft1_Money, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nกรอกจำนวนเเงินที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			return 1;
		}

        new money = strval(inputtext);

		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนเงินที่ใช้คราฟเป็น %s", WeaponCraftData[id][weaponcraftName], FormatNumber(money));

		WeaponCraftData[id][weaponcraftMoney] = money;
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft1(playerid);
}

Dialog:WeaponCraftList2(playerid, response, listitem, inputtext[])
{
	if(response) {

		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "weaponcraft2editID", GetPVarInt(playerid, str_biz));
			ShowPlayerEditWeaponCraft2(playerid);
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

		for(new i=0; i<MAX_WEAPONCRAFT; i++)
        {
            if(WeaponCraftData[i][weaponcraftEx] && WeaponCraftData[i][weaponcraftType] == 2){
                if(skipitem)
                {
                    skipitem--;
                    continue;
                }
                if(count == 20)
                {
                    format(string, sizeof(string), "%s{B4B5B7}หน้า %d\n", string, (currentPage==1) ? 1 : currentPage+1);
                    break;
                }
                format(menu, 20, "menu%d", ++count);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s(%i) | %s [Model: %d | Level: %d]\n", string, i, WeaponCraftData[i][weaponcraftName], WeaponCraftData[i][weaponcraftModel], WeaponCraftData[i][weaponcraftLevelSkills]);

            }
		}

		Dialog_ShowEasy(playerid, WeaponCraftList2, DIALOG_STYLE_LIST, "รายชื่ออาวุธปืนเบา", string, "แก้ไข", "กลับ");
	}
	return 1;
}

ShowPlayerEditWeaponCraft2(playerid)
{
    new id = GetPVarInt(playerid, "weaponcraft2editID");
	new caption[128], dialog_str[1024];
	format(caption, sizeof(caption), "แก้ไขอาวุธ: %s (Model :%d | Level: %d)", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftModel], WeaponCraftData[id][weaponcraftLevelSkills]);
    format(dialog_str, sizeof dialog_str, "ชื่ออาวุธ\t%s\n", WeaponCraftData[id][weaponcraftName]);
	format(dialog_str, sizeof dialog_str, "%s โมเดลอาวุธ\t%d\n", dialog_str, WeaponCraftData[id][weaponcraftModel]);
    format(dialog_str, sizeof dialog_str, "%s ใช้ดินปืน\t%d\n", dialog_str, WeaponCraftData[id][weaponcraftGunpowder]);
	format(dialog_str, sizeof dialog_str, "%s ใช้ไม้\t%d\n", dialog_str, WeaponCraftData[id][weaponcraftWood]);
    format(dialog_str, sizeof dialog_str, "%s ใช้เหล็ก\t%d\n", dialog_str, WeaponCraftData[id][weaponcraftOre]);
    format(dialog_str, sizeof dialog_str, "%s ใช้เงิน\t%s\n", dialog_str, FormatNumber(WeaponCraftData[id][weaponcraftMoney]));
	Dialog_ShowEasy(playerid, WeaponCraft2Edit, DIALOG_STYLE_TABLIST, caption, dialog_str, "แก้ไข", "กลับ");
	return 1;
}

Dialog:WeaponCraft2Edit(playerid, response, listitem, inputtext[])
{
	if(response) {

		new caption[128];
        new id = GetPVarInt(playerid, "weaponcraft2editID");
		switch(listitem)
		{
			case 0:
			{
				format(caption, sizeof(caption), "แก้ไข -> ชื่ออาวุธ: %s", WeaponCraftData[id][weaponcraftName]);
				Dialog_ShowEasy(playerid, WeaponCraft2_Name, DIALOG_STYLE_INPUT, caption, "ความยาวของชื่อต้องมากกว่า 0 และไม่เกิน 32 ตัวอักษร\n\nกรอกชื่ออาวุธใหม่ที่ต้องการ:", "เปลี่ยน", "กลับ");
			}
            case 1:
			{
				format(caption, sizeof(caption), "แก้ไข -> โมเดลอาวุธ: %d", WeaponCraftData[id][weaponcraftModel]);
				Dialog_ShowEasy(playerid, WeaponCraft2_Model, DIALOG_STYLE_INPUT, caption, "กรอกโมเดลอาวุธที่ต้องการจะเปลี่ยน:", "เปลี่ยน", "กลับ");
			}
            case 2:
			{
				format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้ดินปืน > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftGunpowder]);
				Dialog_ShowEasy(playerid, WeaponCraft2_Gunpowder, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนดินปืนที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			}
            case 3:
			{
				format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้ไม้ > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftWood]);
				Dialog_ShowEasy(playerid, WeaponCraft2_Wood, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนไม้ที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			}
            case 4:
			{
				format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้เหล็ก > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftOre]);
				Dialog_ShowEasy(playerid, WeaponCraft2_Ore, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนเหล็กที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			}
            case 5:
			{
				format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้เงิน > %s", WeaponCraftData[id][weaponcraftName], FormatNumber(WeaponCraftData[id][weaponcraftMoney]));
				Dialog_ShowEasy(playerid, WeaponCraft2_Money, DIALOG_STYLE_INPUT, caption, "กรอกจำนวนเเงินที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			}
		}
	}
	else
	{
	    DeletePVar(playerid, "weaponcraft2editID");
        ViewWeaponCrafts(playerid);
	}
    return 1;
}

Dialog:WeaponCraft2_Name(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft2editID");

		if(isnull(inputtext) || strlen(inputtext) >= 32) {
			format(caption, sizeof(caption), "แก้ไข -> ชื่ออาวุธ: %s", WeaponCraftData[id][weaponcraftName]);
			Dialog_ShowEasy(playerid, WeaponCraft2_Name, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nความยาวของชื่อต้องมากกว่า 0 และไม่เกิน 32 ตัวอักษร", "เปลี่ยน", "กลับ");
			return 1;
		}
		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนเป็น %s", WeaponCraftData[id][weaponcraftName], inputtext);

		format(WeaponCraftData[id][weaponcraftName], 32, inputtext);
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft2(playerid);
}

Dialog:WeaponCraft2_Model(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft2editID");

		if(isnull(inputtext) || strlen(inputtext) >= 12) {
			format(caption, sizeof(caption), "แก้ไข -> โมเดลอาวุธ: %d", WeaponCraftData[id][weaponcraftModel]);
			Dialog_ShowEasy(playerid, WeaponCraft2_Model, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nกรอกโมเดลอาวุธที่ต้องการจะเปลี่ยน:", "เปลี่ยน", "กลับ");
			return 1;
		}

		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนโมเดลเป็น %s", WeaponCraftData[id][weaponcraftName], inputtext);

        new model = strval(inputtext);

		WeaponCraftData[id][weaponcraftModel] = model;
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft2(playerid);
}

Dialog:WeaponCraft2_Gunpowder(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft2editID");

		if(isnull(inputtext) || strlen(inputtext) >= 12) {
			format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้ดินปืน > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftGunpowder]);
			Dialog_ShowEasy(playerid, WeaponCraft2_Gunpowder, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nกรอกจำนวนดินปืนที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			return 1;
		}

		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนดินปืนที่ใช้คราฟเป็น %s", WeaponCraftData[id][weaponcraftName], inputtext);

        new gunpowder = strval(inputtext);

		WeaponCraftData[id][weaponcraftGunpowder] = gunpowder;
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft2(playerid);
}

Dialog:WeaponCraft2_Wood(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft2editID");

		if(isnull(inputtext) || strlen(inputtext) >= 12) {
			format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้ไม้ > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftWood]);
			Dialog_ShowEasy(playerid, WeaponCraft2_Wood, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nกรอกจำนวนไม้ที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			return 1;
		}

		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนไม้ที่ใช้คราฟเป็น %s", WeaponCraftData[id][weaponcraftName], inputtext);

        new wood = strval(inputtext);

		WeaponCraftData[id][weaponcraftWood] = wood;
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft2(playerid);
}

Dialog:WeaponCraft2_Ore(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft1editID");

		if(isnull(inputtext) || strlen(inputtext) >= 12) {
			format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้เหล็ก > %d", WeaponCraftData[id][weaponcraftName], WeaponCraftData[id][weaponcraftOre]);
			Dialog_ShowEasy(playerid, WeaponCraft2_Ore, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nกรอกจำนวนเหล็กที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			return 1;
		}

		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนเหล็กที่ใช้คราฟเป็น %s", WeaponCraftData[id][weaponcraftName], inputtext);

        new Ore = strval(inputtext);

		WeaponCraftData[id][weaponcraftOre] = Ore;
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft2(playerid);
}

Dialog:WeaponCraft2_Money(playerid, response, listitem, inputtext[]){
    if(response){
        new caption[128];
		new id = GetPVarInt(playerid, "weaponcraft1editID");

		if(isnull(inputtext) || strlen(inputtext) >= 12) {
			format(caption, sizeof(caption), "แก้ไข -> อาวุธ: %s ใช้เงิน > %s", WeaponCraftData[id][weaponcraftName], FormatNumber(WeaponCraftData[id][weaponcraftMoney]));
			Dialog_ShowEasy(playerid, WeaponCraft2_Money, DIALOG_STYLE_INPUT, caption, "พบข้อผิดพลาด:\nกรอกจำนวนเเงินที่ใช้คราฟอาวุธชิ้นนี้:", "เปลี่ยน", "กลับ");
			return 1;
		}

        new money = strval(inputtext);

		SendClientMessageEx(playerid, COLOR_GRAD1, "อาวุธชื่อ %s ถูกเปลี่ยนเงินที่ใช้คราฟเป็น %s", WeaponCraftData[id][weaponcraftName], FormatNumber(money));

		WeaponCraftData[id][weaponcraftMoney] = money;
		WeaponCraft_Save(id);
    }
    return ShowPlayerEditWeaponCraft2(playerid);
}

CMD:reloadweapons(playerid, params[]){
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pAdmin] >= 1338){
            Count_WeaponCraft = 0;
            mysql_tquery(dbCon, "SELECT * FROM `weaponcrafts`", "WeaponCraft_Load", "");
            SendClientMessage(playerid, -1, "คุณได้ทำการโหลด 'weaponcrafts'");
        }
    }
    return 1;
}

CMD:viewweapons(playerid, params[]){
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pAdmin] >= 1338){
            ViewWeaponCrafts(playerid);
        }
    }
    return 1;
}
