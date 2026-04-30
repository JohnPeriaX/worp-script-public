#if defined _inc_header
	#undef _inc_header
#endif

new PlayerText:ProgressBarV2_Text[MAX_PLAYERS][2];
new PlayerBar:ProgressBarV2_Progressbar[MAX_PLAYERS][1];

new Timer:Progressbar_Timer[MAX_PLAYERS];
new PlayerStartProgressbar[MAX_PLAYERS];
new Float:PlayerPointSpace[MAX_PLAYERS];
new Float:PlayerRealPoint[MAX_PLAYERS];
new Float:PlayerGetPoint[MAX_PLAYERS];
new PlayerProgress_Color[MAX_PLAYERS] = -2016478465;
new PlayerMissPoint[MAX_PLAYERS];
new PlayerMaxMissPoint[MAX_PLAYERS];

PlayerLoadProgressbarV2(playerid){
    ProgressBarV2_Text[playerid][0] = CreatePlayerTextDraw(playerid, 317.299987, 351.000000, "_");
    PlayerTextDrawFont(playerid, ProgressBarV2_Text[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, ProgressBarV2_Text[playerid][0], 0.600000, 2.000003);
    PlayerTextDrawTextSize(playerid, ProgressBarV2_Text[playerid][0], 298.500000, 195.500000);
    PlayerTextDrawSetOutline(playerid, ProgressBarV2_Text[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, ProgressBarV2_Text[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, ProgressBarV2_Text[playerid][0], 2);
    PlayerTextDrawColor(playerid, ProgressBarV2_Text[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, ProgressBarV2_Text[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, ProgressBarV2_Text[playerid][0], -121);
    PlayerTextDrawUseBox(playerid, ProgressBarV2_Text[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, ProgressBarV2_Text[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, ProgressBarV2_Text[playerid][0], 0);

    ProgressBarV2_Progressbar[playerid][0] = CreatePlayerProgressBar(playerid, 221.000000, 352.000000, 196.500000, 17.000000, PlayerProgress_Color[playerid], 100.000000, 0);
    return 1;
}

PlayerLoadProgressbarV2Point(playerid){
    ProgressBarV2_Text[playerid][1] = CreatePlayerTextDraw(playerid, 220.000000+PlayerPointSpace[playerid], 334.000000, "l");
    PlayerTextDrawFont(playerid, ProgressBarV2_Text[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, ProgressBarV2_Text[playerid][1], 0.308333, 5.400004);
    PlayerTextDrawTextSize(playerid, ProgressBarV2_Text[playerid][1], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, ProgressBarV2_Text[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, ProgressBarV2_Text[playerid][1], 1);
    PlayerTextDrawAlignment(playerid, ProgressBarV2_Text[playerid][1], 2);
    PlayerTextDrawColor(playerid, ProgressBarV2_Text[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, ProgressBarV2_Text[playerid][1], 116);
    PlayerTextDrawBoxColor(playerid, ProgressBarV2_Text[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, ProgressBarV2_Text[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, ProgressBarV2_Text[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, ProgressBarV2_Text[playerid][1], 0);
    return 1;
}