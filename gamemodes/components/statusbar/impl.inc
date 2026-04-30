#if defined _inc_impl
	#undef _inc_impl
#endif

ptask UpdateStatusBar[1500](playerid){
    if(PlayerShowStatusBar[playerid] && !TogHud[playerid]){
        SetPlayerProgressBarValue(playerid, StatusProgressBar[playerid][0], PlayerData[playerid][pHunger]);
        SetPlayerProgressBarValue(playerid, StatusProgressBar[playerid][1], PlayerData[playerid][pWater]);
        SetPlayerProgressBarValue(playerid, StatusProgressBar[playerid][2], PlayerData[playerid][pEnergy]);
        SetPlayerProgressBarValue(playerid, StatusProgressBar[playerid][3], PlayerData[playerid][pShower]);
        SetPlayerProgressBarValue(playerid, StatusProgressBar[playerid][4], PlayerData[playerid][pStress]);
    }
}

LoadPlayerStatusBar(playerid){
    StatusBar[playerid][0] = CreatePlayerTextDraw(playerid, 20.000000, 414.000000, "HUD:radar_burgershot");
    PlayerTextDrawFont(playerid, StatusBar[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, StatusBar[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, StatusBar[playerid][0], 10.500000, 10.500000);
    PlayerTextDrawSetOutline(playerid, StatusBar[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, StatusBar[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, StatusBar[playerid][0], 1);
    PlayerTextDrawColor(playerid, StatusBar[playerid][0], -106);
    PlayerTextDrawBackgroundColor(playerid, StatusBar[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, StatusBar[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, StatusBar[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, StatusBar[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, StatusBar[playerid][0], 0);

    StatusBar[playerid][1] = CreatePlayerTextDraw(playerid, 38.000000, 414.000000, "HUD:radar_diner");
    PlayerTextDrawFont(playerid, StatusBar[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, StatusBar[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, StatusBar[playerid][1], 10.500000, 10.500000);
    PlayerTextDrawSetOutline(playerid, StatusBar[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, StatusBar[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, StatusBar[playerid][1], 1);
    PlayerTextDrawColor(playerid, StatusBar[playerid][1], -106);
    PlayerTextDrawBackgroundColor(playerid, StatusBar[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, StatusBar[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, StatusBar[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, StatusBar[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, StatusBar[playerid][1], 0);

    StatusBar[playerid][2] = CreatePlayerTextDraw(playerid, 56.000000, 414.000000, "HUD:radar_gym");
    PlayerTextDrawFont(playerid, StatusBar[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, StatusBar[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, StatusBar[playerid][2], 10.500000, 10.500000);
    PlayerTextDrawSetOutline(playerid, StatusBar[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, StatusBar[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, StatusBar[playerid][2], 1);
    PlayerTextDrawColor(playerid, StatusBar[playerid][2], -106);
    PlayerTextDrawBackgroundColor(playerid, StatusBar[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, StatusBar[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, StatusBar[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, StatusBar[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, StatusBar[playerid][2], 0);

    StatusBar[playerid][3] = CreatePlayerTextDraw(playerid, 74.000000, 414.000000, "HUD:radar_tshirt");
    PlayerTextDrawFont(playerid, StatusBar[playerid][3], 4);
    PlayerTextDrawLetterSize(playerid, StatusBar[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, StatusBar[playerid][3], 10.500000, 10.500000);
    PlayerTextDrawSetOutline(playerid, StatusBar[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, StatusBar[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, StatusBar[playerid][3], 1);
    PlayerTextDrawColor(playerid, StatusBar[playerid][3], -106);
    PlayerTextDrawBackgroundColor(playerid, StatusBar[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, StatusBar[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, StatusBar[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, StatusBar[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, StatusBar[playerid][3], 0);

    StatusBar[playerid][4] = CreatePlayerTextDraw(playerid, 92.000000, 414.000000, "HUD:radar_locosyndicate");
    PlayerTextDrawFont(playerid, StatusBar[playerid][4], 4);
    PlayerTextDrawLetterSize(playerid, StatusBar[playerid][4], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, StatusBar[playerid][4], 10.500000, 10.500000);
    PlayerTextDrawSetOutline(playerid, StatusBar[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, StatusBar[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, StatusBar[playerid][4], 1);
    PlayerTextDrawColor(playerid, StatusBar[playerid][4], -106);
    PlayerTextDrawBackgroundColor(playerid, StatusBar[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, StatusBar[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, StatusBar[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, StatusBar[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, StatusBar[playerid][4], 0);
    return 1;
}

LoadPlayerStatusProgressBar(playerid){
    StatusProgressBar[playerid][0] = CreatePlayerProgressBar(playerid, 35.000000, 447.000000, 16.500000, 21.500000, -1020010, 100.000000, 2);
    StatusProgressBar[playerid][1] = CreatePlayerProgressBar(playerid, 53.000000, 447.000000, 16.500000, 21.500000, -1695809642, 100.000000, 2);
    StatusProgressBar[playerid][2] = CreatePlayerProgressBar(playerid, 71.000000, 447.000000, 16.500000, 21.500000, -1224762730, 100.000000, 2);
    StatusProgressBar[playerid][3] = CreatePlayerProgressBar(playerid, 89.000000, 447.000000, 16.500000, 21.500000, -8433514, 100.000000, 2);
    StatusProgressBar[playerid][4] = CreatePlayerProgressBar(playerid, 107.000000, 447.000000, 16.500000, 21.500000, 9109654, 200.000000, 2);
    return 1;
}