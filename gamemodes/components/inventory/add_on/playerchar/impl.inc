#if defined _inc_impl
	#undef _inc_impl
#endif

ResetPlayer_CharacterTD(playerid){
    PlayerCharacterShow[playerid] = false;
    return 1;
}

PlayerCharacterTD_Render(playerid){
    if(PlayerCharacterShow[playerid]){
        new string[128];
        format(string, sizeof string, "%s", ReturnRoleplayName(playerid));
        PlayerTextDrawSetString(playerid, PlayerCharacterTextDraw[playerid][4], string);

        PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][5]);
        PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][5], PlayerData[playerid][pSkin]);
        PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][5]);

        if(PlayerData[playerid][pMyWeapon][2] == 0){
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][6]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][6], MODEL_NULL);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][6]);

            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][7]);
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][8]);
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][9]);
        }
        else{
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][6]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][6], ReturnWeaponsModel(PlayerData[playerid][pMyWeapon][2]));
            PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][6], 11.000000, 36.000000, -17.000000, 1.189999);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][6]);

            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][7]);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][8]);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][9]);

            format(string, sizeof string, "%s", ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]));
            PlayerTextDrawSetString(playerid, PlayerCharacterTextDraw[playerid][7], string);
            format(string, sizeof string, "Level: %d", PlayerData[playerid][pMyWeaponLevel][2]);
            PlayerTextDrawSetString(playerid, PlayerCharacterTextDraw[playerid][8], string);
            PlayerTextDrawSetString(playerid, PlayerCharacterTextDraw[playerid][9], "1 ea");
        }

        if(PlayerData[playerid][pMyWeapon][1] == 0){
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][10]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][10], MODEL_NULL);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][10]);

            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][11]);
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][12]);
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][13]);
        }
        else{
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][10]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][10], ReturnWeaponsModel(PlayerData[playerid][pMyWeapon][1]));
            PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][10], 11.000000, 36.000000, -17.000000, 1.189999);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][10]);

            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][11]);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][12]);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][13]);

            format(string, sizeof string, "%s", ReturnWeaponName(PlayerData[playerid][pMyWeapon][1]));
            PlayerTextDrawSetString(playerid, PlayerCharacterTextDraw[playerid][11], string);
            format(string, sizeof string, "Level: %d", PlayerData[playerid][pMyWeaponLevel][1]);
            PlayerTextDrawSetString(playerid, PlayerCharacterTextDraw[playerid][12], string);
            format(string, sizeof string, "%d ammo", PlayerData[playerid][pMyAmmo][1]);
            PlayerTextDrawSetString(playerid, PlayerCharacterTextDraw[playerid][13], string);
        }

        if(PlayerData[playerid][pMyWeapon][0] == 0){
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][14]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][14], MODEL_NULL);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][14]);

            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][15]);
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][16]);
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][17]);
        }
        else{
            PlayerTextDrawHide(playerid, PlayerCharacterTextDraw[playerid][14]);
            PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][14], ReturnWeaponsModel(PlayerData[playerid][pMyWeapon][0]));
            PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][14], 11.000000, 36.000000, -17.000000, 1.189999);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][14]);

            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][15]);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][16]);
            PlayerTextDrawShow(playerid, PlayerCharacterTextDraw[playerid][17]);

            format(string, sizeof string, "%s", ReturnWeaponName(PlayerData[playerid][pMyWeapon][0]));
            PlayerTextDrawSetString(playerid, PlayerCharacterTextDraw[playerid][15], string);
            format(string, sizeof string, "Level: %d", PlayerData[playerid][pMyWeaponLevel][0]);
            PlayerTextDrawSetString(playerid, PlayerCharacterTextDraw[playerid][16], string);
            format(string, sizeof string, "%d ammo", PlayerData[playerid][pMyAmmo][1]);
            PlayerTextDrawSetString(playerid, PlayerCharacterTextDraw[playerid][17], string);
        }
    }
    return 1;
}

LoadPlayerCharacterTextDraw(playerid){
    PlayerCharacterTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 316.500000+PlayerPositionInventoryX[playerid], 41.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][0], 0.600000, 30.500061);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][0], 298.500000, 176.500000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][0], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][0], 555819519);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][0], 0);

    PlayerCharacterTextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 316.500000+PlayerPositionInventoryX[playerid], 74.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][1], 0.600000, 26.500061);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][1], 298.500000, 173.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][1], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][1], 320017407);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][1], 0);

    PlayerCharacterTextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 316.500000+PlayerPositionInventoryX[playerid], 41.000000+PlayerPositionInventoryY[playerid], "_");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][2], 0);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][2], 0.600000, 1.450034);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][2], 298.500000, 176.500000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][2], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][2], PlayerInventoryCodeColor[playerid]);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][2], 0);

    PlayerCharacterTextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 229.000000+PlayerPositionInventoryX[playerid], 40.000000+PlayerPositionInventoryY[playerid], "Character");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][3], 0.262499, 1.500000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][3], 466.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][3], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][3], 0);

    PlayerCharacterTextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 230.000000+PlayerPositionInventoryX[playerid], 60.000000+PlayerPositionInventoryY[playerid], "JustinzDev");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][4], 0.195833, 0.950000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][4], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][4], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][4], 0);

    PlayerCharacterTextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 230.000000+PlayerPositionInventoryX[playerid], 74.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][5], 5);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][5], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][5], 97.500000, 108.500000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][5], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][5], 125);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][5], 255);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][5], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][5], 0);
    PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][5], -3.000000, 1.000000, -6.000000, 0.899999);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerCharacterTextDraw[playerid][5], 1, 1);

    //11.000000, 36.000000, -17.000000, 1.189999
    PlayerCharacterTextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 329.000000+PlayerPositionInventoryX[playerid], 74.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][6], 5);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][6], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][6], 34.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][6], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][6], 125);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][6], 255);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][6], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][6], 339);
    PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][6], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerCharacterTextDraw[playerid][6], 1, 1);

    PlayerCharacterTextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 384.000000+PlayerPositionInventoryX[playerid], 77.000000+PlayerPositionInventoryY[playerid], "Katana");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][7], 0.141665, 0.750000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][7], 401.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][7], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][7], 1296911666);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][7], 0);

    PlayerCharacterTextDraw[playerid][8] = CreatePlayerTextDraw(playerid, 384.000000+PlayerPositionInventoryX[playerid], 88.000000+PlayerPositionInventoryY[playerid], "Level: 5");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][8], 0.141667, 0.750000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][8], 401.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][8], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][8], 1296911666);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][8], 0);

    PlayerCharacterTextDraw[playerid][9] = CreatePlayerTextDraw(playerid, 384.000000+PlayerPositionInventoryX[playerid], 99.000000+PlayerPositionInventoryY[playerid], "1 EA");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][9], 0.141667, 0.750000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][9], 401.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][9], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][9], 1296911666);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][9], 0);

    //11.000000, 36.000000, -17.000000, 1.189999
    PlayerCharacterTextDraw[playerid][10] = CreatePlayerTextDraw(playerid, 329.000000+PlayerPositionInventoryX[playerid], 111.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][10], 5);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][10], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][10], 34.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][10], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][10], 125);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][10], 255);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][10], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][10], 348);
    PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][10], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerCharacterTextDraw[playerid][10], 1, 1);

    PlayerCharacterTextDraw[playerid][11] = CreatePlayerTextDraw(playerid, 384.000000+PlayerPositionInventoryX[playerid], 114.000000+PlayerPositionInventoryY[playerid], "Desert Eagle");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][11], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][11], 0.141667, 0.750000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][11], 401.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][11], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][11], 1296911666);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][11], 0);

    PlayerCharacterTextDraw[playerid][12] = CreatePlayerTextDraw(playerid, 384.000000+PlayerPositionInventoryX[playerid], 125.000000+PlayerPositionInventoryY[playerid], "Level: 5");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][12], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][12], 0.141667, 0.750000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][12], 401.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][12], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][12], 1296911666);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][12], 0);

    PlayerCharacterTextDraw[playerid][13] = CreatePlayerTextDraw(playerid, 384.000000+PlayerPositionInventoryX[playerid], 136.000000+PlayerPositionInventoryY[playerid], "7 ammo");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][13], 0.141667, 0.750000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][13], 401.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][13], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][13], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][13], 1296911666);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][13], 0);

    //11.000000, 36.000000, -17.000000, 1.189999
    PlayerCharacterTextDraw[playerid][14] = CreatePlayerTextDraw(playerid, 329.000000+PlayerPositionInventoryX[playerid], 148.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][14], 5);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][14], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][14], 34.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][14], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][14], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][14], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][14], 125);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][14], 255);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][14], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][14], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][14], 356);
    PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][14], 0.000000, 0.000000, 0.000000, 0.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerCharacterTextDraw[playerid][14], 1, 1);

    PlayerCharacterTextDraw[playerid][15] = CreatePlayerTextDraw(playerid, 384.000000+PlayerPositionInventoryX[playerid], 151.000000+PlayerPositionInventoryY[playerid], "M4A1");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][15], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][15], 0.141667, 0.750000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][15], 401.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][15], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][15], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][15], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][15], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][15], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][15], 1296911666);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][15], 0);

    PlayerCharacterTextDraw[playerid][16] = CreatePlayerTextDraw(playerid, 384.000000+PlayerPositionInventoryX[playerid], 162.000000+PlayerPositionInventoryY[playerid], "Level: 5");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][16], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][16], 0.141667, 0.750000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][16], 401.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][16], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][16], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][16], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][16], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][16], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][16], 1296911666);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][16], 0);

    PlayerCharacterTextDraw[playerid][17] = CreatePlayerTextDraw(playerid, 384.000000+PlayerPositionInventoryX[playerid], 173.000000+PlayerPositionInventoryY[playerid], "30 ammo");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][17], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][17], 0.141667, 0.750000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][17], 401.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][17], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][17], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][17], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][17], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][17], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][17], 1296911666);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][17], 1);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][17], 0);

    PlayerCharacterTextDraw[playerid][18] = CreatePlayerTextDraw(playerid, 230.000000+PlayerPositionInventoryX[playerid], 191.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][18], 5);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][18], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][18], 29.500000, 34.500000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][18], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][18], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][18], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][18], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][18], 125);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][18], 255);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][18], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][18], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][18], 1275);
    PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][18], -3.000000, 1.000000, -6.000000, 0.899999);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerCharacterTextDraw[playerid][18], 1, 1);

    PlayerCharacterTextDraw[playerid][19] = CreatePlayerTextDraw(playerid, 266.000000+PlayerPositionInventoryX[playerid], 191.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][19], 5);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][19], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][19], 29.500000, 34.500000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][19], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][19], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][19], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][19], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][19], 125);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][19], 255);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][19], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][19], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][19], 1239);
    PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][19], -3.000000, 1.000000, -6.000000, 0.899999);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerCharacterTextDraw[playerid][19], 1, 1);

    PlayerCharacterTextDraw[playerid][20] = CreatePlayerTextDraw(playerid, 302.000000+PlayerPositionInventoryX[playerid], 191.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][20], 5);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][20], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][20], 29.500000, 34.500000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][20], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][20], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][20], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][20], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][20], 125);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][20], 255);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][20], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][20], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][20], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][20], 1272);
    PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][20], -3.000000, 1.000000, -6.000000, 0.899999);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerCharacterTextDraw[playerid][20], 1, 1);

    PlayerCharacterTextDraw[playerid][21] = CreatePlayerTextDraw(playerid, 338.000000+PlayerPositionInventoryX[playerid], 191.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][21], 5);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][21], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][21], 29.500000, 34.500000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][21], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][21], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][21], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][21], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][21], 125);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][21], 255);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][21], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][21], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][21], 1277);
    PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][21], -3.000000, 1.000000, -6.000000, 0.899999);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerCharacterTextDraw[playerid][21], 1, 1);

    PlayerCharacterTextDraw[playerid][22] = CreatePlayerTextDraw(playerid, 374.000000+PlayerPositionInventoryX[playerid], 191.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][22], 5);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][22], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][22], 29.500000, 34.500000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][22], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][22], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][22], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][22], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][22], 125);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][22], 255);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][22], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][22], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][22], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][22], 1581);
    PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][22], 3.000000, 1.000000, -161.000000, 0.899999);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerCharacterTextDraw[playerid][22], 1, 1);

    PlayerCharacterTextDraw[playerid][23] = CreatePlayerTextDraw(playerid, 230.000000+PlayerPositionInventoryX[playerid], 233.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][23], 5);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][23], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][23], 29.500000, 34.500000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][23], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][23], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][23], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][23], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][23], 125);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][23], 255);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][23], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][23], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][23], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][23], 1239);
    PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][23], -3.000000, 1.000000, -6.000000, 0.899999);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerCharacterTextDraw[playerid][23], 1, 1);

    PlayerCharacterTextDraw[playerid][24] = CreatePlayerTextDraw(playerid, 266.000000+PlayerPositionInventoryX[playerid], 233.000000+PlayerPositionInventoryY[playerid], "Preview_Model");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][24], 5);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][24], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][24], 29.500000, 34.500000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][24], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][24], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][24], 1);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][24], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][24], 125);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][24], 255);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][24], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][24], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][24], 1);
    PlayerTextDrawSetPreviewModel(playerid, PlayerCharacterTextDraw[playerid][24], 1314);
    PlayerTextDrawSetPreviewRot(playerid, PlayerCharacterTextDraw[playerid][24], -3.000000, 1.000000, -6.000000, 0.899999);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerCharacterTextDraw[playerid][24], 1, 1);

    PlayerCharacterTextDraw[playerid][25] = CreatePlayerTextDraw(playerid, 245.000000+PlayerPositionInventoryX[playerid], 204.000000+PlayerPositionInventoryY[playerid], "Accessory");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][25], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][25], 0.170833, 0.949998);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][25], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][25], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][25], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][25], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][25], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][25], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][25], 50);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][25], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][25], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][25], 0);

    PlayerCharacterTextDraw[playerid][26] = CreatePlayerTextDraw(playerid, 281.000000+PlayerPositionInventoryX[playerid], 204.000000+PlayerPositionInventoryY[playerid], "Infomation");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][26], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][26], 0.170833, 0.949998);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][26], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][26], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][26], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][26], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][26], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][26], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][26], 50);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][26], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][26], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][26], 0);

    PlayerCharacterTextDraw[playerid][27] = CreatePlayerTextDraw(playerid, 317.000000+PlayerPositionInventoryX[playerid], 204.000000+PlayerPositionInventoryY[playerid], "Home");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][27], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][27], 0.170833, 0.949998);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][27], 400.000000, 42.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][27], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][27], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][27], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][27], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][27], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][27], 50);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][27], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][27], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][27], 0);

    PlayerCharacterTextDraw[playerid][28] = CreatePlayerTextDraw(playerid, 353.000000+PlayerPositionInventoryX[playerid], 204.000000+PlayerPositionInventoryY[playerid], "Skills");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][28], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][28], 0.170833, 0.949998);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][28], 400.000000, 42.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][28], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][28], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][28], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][28], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][28], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][28], 50);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][28], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][28], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][28], 0);

    PlayerCharacterTextDraw[playerid][29] = CreatePlayerTextDraw(playerid, 388.000000+PlayerPositionInventoryX[playerid], 203.000000+PlayerPositionInventoryY[playerid], "Licenses");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][29], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][29], 0.170833, 0.949998);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][29], 400.000000, 42.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][29], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][29], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][29], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][29], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][29], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][29], 50);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][29], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][29], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][29], 0);

    PlayerCharacterTextDraw[playerid][30] = CreatePlayerTextDraw(playerid, 245.000000+PlayerPositionInventoryX[playerid], 247.000000+PlayerPositionInventoryY[playerid], "Quests");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][30], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][30], 0.170833, 0.949998);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][30], 400.000000, 42.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][30], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][30], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][30], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][30], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][30], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][30], 50);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][30], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][30], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][30], 0);

    PlayerCharacterTextDraw[playerid][31] = CreatePlayerTextDraw(playerid, 281.000000+PlayerPositionInventoryX[playerid], 247.000000+PlayerPositionInventoryY[playerid], "Party");
    PlayerTextDrawFont(playerid, PlayerCharacterTextDraw[playerid][31], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCharacterTextDraw[playerid][31], 0.170833, 0.949998);
    PlayerTextDrawTextSize(playerid, PlayerCharacterTextDraw[playerid][31], 400.000000, 42.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCharacterTextDraw[playerid][31], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCharacterTextDraw[playerid][31], 0);
    PlayerTextDrawAlignment(playerid, PlayerCharacterTextDraw[playerid][31], 2);
    PlayerTextDrawColor(playerid, PlayerCharacterTextDraw[playerid][31], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCharacterTextDraw[playerid][31], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCharacterTextDraw[playerid][31], 50);
    PlayerTextDrawUseBox(playerid, PlayerCharacterTextDraw[playerid][31], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCharacterTextDraw[playerid][31], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCharacterTextDraw[playerid][31], 0);
    return 1;
}