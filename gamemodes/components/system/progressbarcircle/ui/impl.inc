#if defined _inc_impl
	#undef _inc_impl
#endif

void:OP_DestroyProgressbarCircle(playerid){
	if(playerShowProgressbarCircle[playerid]){
		for(new i=0; i<MAX_PROGRESSCIRCLE_TEXTDRAW; i++){
			if(IsPlayerTextDrawVisible(playerid, PlayerCircleProgressbarTextDraw[playerid][i])){
				PlayerTextDrawHide(playerid, PlayerCircleProgressbarTextDraw[playerid][i]);
			}

			PlayerTextDrawDestroy(playerid, PlayerCircleProgressbarTextDraw[playerid][i]);
		}
		playerShowProgressbarCircle[playerid] = false;
	}
}

timer UpdatePlayerCircleProgress[playerCountTimeCircle[playerid]](playerid){
	if(playerShowProgressbarCircle[playerid]){
		if(playerCountingTextDrawCircle[playerid] < 0){
			OP_DestroyProgressbarCircle(playerid);
			if(strcmp(playerCircleProgressCallback[playerid], "NULL", false)) CallLocalFunction(playerCircleProgressCallback[playerid], "i", playerid);
			ResetPlayerCircleProgressbar(playerid);
			return true;
		}

		PlayerTextDrawHide(playerid, PlayerCircleProgressbarTextDraw[playerid][playerCountingTextDrawCircle[playerid]]);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][playerCountingTextDrawCircle[playerid]], playerCircleProgressColor[playerid]);
		PlayerTextDrawShow(playerid, PlayerCircleProgressbarTextDraw[playerid][playerCountingTextDrawCircle[playerid]]);

		playerCountingTextDrawCircle[playerid]--;
	}
	return true;
}

void:OP_CreateProgressbarCircle(playerid){
	if(!playerShowProgressbarCircle[playerid]){
		PlayerCircleProgressbarTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 312.000000, 300.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][0], 0);

		PlayerCircleProgressbarTextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 305.000000, 301.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][1], 0);

		PlayerCircleProgressbarTextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 299.000000, 304.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][2], 0);

		PlayerCircleProgressbarTextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 295.000000, 307.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][3], 0);

		PlayerCircleProgressbarTextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 290.000000, 312.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][4], 0);

		PlayerCircleProgressbarTextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 287.000000, 317.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][5], 0);

		PlayerCircleProgressbarTextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 285.000000, 324.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][6], 0);

		PlayerCircleProgressbarTextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 284.000000, 331.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][7], 0);

		PlayerCircleProgressbarTextDraw[playerid][8] = CreatePlayerTextDraw(playerid, 285.000000, 336.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][8], 0);

		PlayerCircleProgressbarTextDraw[playerid][9] = CreatePlayerTextDraw(playerid, 288.000000, 343.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][9], 0);

		PlayerCircleProgressbarTextDraw[playerid][10] = CreatePlayerTextDraw(playerid, 292.000000, 349.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][10], 0);

		PlayerCircleProgressbarTextDraw[playerid][11] = CreatePlayerTextDraw(playerid, 297.000000, 353.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][11], 0);

		PlayerCircleProgressbarTextDraw[playerid][12] = CreatePlayerTextDraw(playerid, 301.000000, 355.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][12], 0);

		PlayerCircleProgressbarTextDraw[playerid][13] = CreatePlayerTextDraw(playerid, 304.000000, 356.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][13], 0);

		PlayerCircleProgressbarTextDraw[playerid][14] = CreatePlayerTextDraw(playerid, 308.000000, 357.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][14], 0);

		PlayerCircleProgressbarTextDraw[playerid][15] = CreatePlayerTextDraw(playerid, 314.000000, 357.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][15], 0);

		PlayerCircleProgressbarTextDraw[playerid][16] = CreatePlayerTextDraw(playerid, 319.000000, 356.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][16], 0);

		PlayerCircleProgressbarTextDraw[playerid][17] = CreatePlayerTextDraw(playerid, 325.000000, 354.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][17], 0);

		PlayerCircleProgressbarTextDraw[playerid][18] = CreatePlayerTextDraw(playerid, 328.000000, 351.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][18], 0);

		PlayerCircleProgressbarTextDraw[playerid][19] = CreatePlayerTextDraw(playerid, 331.000000, 348.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][19], 0);

		PlayerCircleProgressbarTextDraw[playerid][20] = CreatePlayerTextDraw(playerid, 335.000000, 344.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][20], 0);

		PlayerCircleProgressbarTextDraw[playerid][21] = CreatePlayerTextDraw(playerid, 338.000000, 338.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][21], 0);

		PlayerCircleProgressbarTextDraw[playerid][22] = CreatePlayerTextDraw(playerid, 339.000000, 333.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][22], 0);

		PlayerCircleProgressbarTextDraw[playerid][23] = CreatePlayerTextDraw(playerid, 340.000000, 327.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][23], 0);

		PlayerCircleProgressbarTextDraw[playerid][24] = CreatePlayerTextDraw(playerid, 338.000000, 321.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][24], 0);

		PlayerCircleProgressbarTextDraw[playerid][25] = CreatePlayerTextDraw(playerid, 336.000000, 316.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][25], 0);

		PlayerCircleProgressbarTextDraw[playerid][26] = CreatePlayerTextDraw(playerid, 334.000000, 312.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][26], 0);

		PlayerCircleProgressbarTextDraw[playerid][27] = CreatePlayerTextDraw(playerid, 329.000000, 307.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][27], 0);

		PlayerCircleProgressbarTextDraw[playerid][28] = CreatePlayerTextDraw(playerid, 325.000000, 304.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][28], 0);

		PlayerCircleProgressbarTextDraw[playerid][29] = CreatePlayerTextDraw(playerid, 319.000000, 301.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 14.500000, 14.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 0x000000FF);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][29], 0);

		PlayerCircleProgressbarTextDraw[playerid][30] = CreatePlayerTextDraw(playerid, 285.000000, 301.000000, "HUD:radardisc");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 34.000000, 35.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 255);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][30], 0);

		PlayerCircleProgressbarTextDraw[playerid][31] = CreatePlayerTextDraw(playerid, 353.000000, 301.000000, "HUD:radardisc");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][31], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][31], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][31], -34.000000, 35.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][31], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][31], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][31], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][31], 255);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][31], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][31], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][31], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][31], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][31], 0);

		PlayerCircleProgressbarTextDraw[playerid][32] = CreatePlayerTextDraw(playerid, 285.000000, 372.000000, "HUD:radardisc");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 34.000000, -35.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 255);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][32], 0);

		PlayerCircleProgressbarTextDraw[playerid][33] = CreatePlayerTextDraw(playerid, 353.000000, 372.000000, "HUD:radardisc");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][33], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][33], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][33], -34.000000, -35.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][33], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][33], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][33], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][33], 255);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][33], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][33], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][33], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][33], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][33], 0);

		PlayerCircleProgressbarTextDraw[playerid][34] = CreatePlayerTextDraw(playerid, 294.000000, 310.000000, "HUD:radardisc");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 25.500000, 28.000000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 255);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][34], 0);

		PlayerCircleProgressbarTextDraw[playerid][35] = CreatePlayerTextDraw(playerid, 344.000000, 310.000000, "HUD:radardisc");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][35], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][35], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][35], -25.500000, 28.000000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][35], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][35], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][35], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][35], 255);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][35], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][35], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][35], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][35], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][35], 0);

		PlayerCircleProgressbarTextDraw[playerid][36] = CreatePlayerTextDraw(playerid, 294.000000, 362.000000, "HUD:radardisc");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 25.500000, -27.500000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 255);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][36], 0);

		PlayerCircleProgressbarTextDraw[playerid][37] = CreatePlayerTextDraw(playerid, 344.000000, 362.000000, "HUD:radardisc");
		PlayerTextDrawFont(playerid, PlayerCircleProgressbarTextDraw[playerid][37], 4);
		PlayerTextDrawLetterSize(playerid, PlayerCircleProgressbarTextDraw[playerid][37], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, PlayerCircleProgressbarTextDraw[playerid][37], -25.500000, -28.000000);
		PlayerTextDrawSetOutline(playerid, PlayerCircleProgressbarTextDraw[playerid][37], 1);
		PlayerTextDrawSetShadow(playerid, PlayerCircleProgressbarTextDraw[playerid][37], 0);
		PlayerTextDrawAlignment(playerid, PlayerCircleProgressbarTextDraw[playerid][37], 1);
		PlayerTextDrawColor(playerid, PlayerCircleProgressbarTextDraw[playerid][37], 255);
		PlayerTextDrawBackgroundColor(playerid, PlayerCircleProgressbarTextDraw[playerid][37], 255);
		PlayerTextDrawBoxColor(playerid, PlayerCircleProgressbarTextDraw[playerid][37], 50);
		PlayerTextDrawUseBox(playerid, PlayerCircleProgressbarTextDraw[playerid][37], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCircleProgressbarTextDraw[playerid][37], 1);
		PlayerTextDrawSetSelectable(playerid, PlayerCircleProgressbarTextDraw[playerid][37], 0);

		playerShowProgressbarCircle[playerid] = true;
		for(new i=0; i<MAX_PROGRESSCIRCLE_TEXTDRAW; i++){
			PlayerTextDrawShow(playerid, PlayerCircleProgressbarTextDraw[playerid][i]);
		}

		playerProgressingCircle[playerid] = repeat UpdatePlayerCircleProgress(playerid);
	}
}