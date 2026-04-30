#if defined _inc_impl
	#undef _inc_impl
#endif

LoadPlayerNewProgress(playerid){
    NewProgressBar[playerid][0] = CreatePlayerProgressBar(playerid, 220.000000, 353.000000, 201.500000, 9.000000, -294256385, 100.000000, 0);

    NewProgressText[playerid][0] = CreatePlayerTextDraw(playerid, 318.000000, 353.000000, "ProgressBar 100/100");
    PlayerTextDrawFont(playerid, NewProgressText[playerid][0], 2);
    PlayerTextDrawLetterSize(playerid, NewProgressText[playerid][0], 0.170833, 1.050000);
    PlayerTextDrawTextSize(playerid, NewProgressText[playerid][0], 400.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, NewProgressText[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, NewProgressText[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, NewProgressText[playerid][0], 2);
    PlayerTextDrawColor(playerid, NewProgressText[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, NewProgressText[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, NewProgressText[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, NewProgressText[playerid][0], 0);
    PlayerTextDrawSetProportional(playerid, NewProgressText[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, NewProgressText[playerid][0], 0);
    return 1;
}