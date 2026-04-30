#if defined _inc_impl
	#undef _inc_impl
#endif

hook Character_Reset(playerid){
	ResetPlayerSafeTextDraw(playerid);
	return true;
}

void:ResetPlayerSafeTextDraw(playerid){
	PlayerSafeTextDrawShow[playerid] = false;
}

void:DestroyPlayerSafeTextDraw(playerid){
	if(PlayerSafeTextDrawShow[playerid]){
		for(new i=0; i<MAX_PLAYERSAFE_TD; i++){
			if(IsPlayerTextDrawVisible(playerid, Player_Safe_TextDraw[playerid][i])){
				PlayerTextDrawHide(playerid, Player_Safe_TextDraw[playerid][i]);
			}

			PlayerTextDrawDestroy(playerid, Player_Safe_TextDraw[playerid][i]);
		}

		PlayerSafeTextDrawShow[playerid] = false;

		Jdz_Hunger_Show(playerid);
		Jdz_Water_Show(playerid);
		Jdz_Stamina_Show(playerid);
		Jdz_Shower_Show(playerid);
		Jdz_Stress_Show(playerid);
	}
}

void:CreatePlayerSafeTextDraw(playerid){
	if(!PlayerSafeTextDrawShow[playerid]){
		Player_Safe_TextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 182.000000 + 276.00, 151.000000, "_");
		PlayerTextDrawFont(playerid, Player_Safe_TextDraw[playerid][0], 1);
		PlayerTextDrawLetterSize(playerid, Player_Safe_TextDraw[playerid][0], 0.604165, 31.100021);
		PlayerTextDrawTextSize(playerid, Player_Safe_TextDraw[playerid][0], 296.000000, 252.500000);
		PlayerTextDrawSetOutline(playerid, Player_Safe_TextDraw[playerid][0], 1);
		PlayerTextDrawSetShadow(playerid, Player_Safe_TextDraw[playerid][0], 0);
		PlayerTextDrawAlignment(playerid, Player_Safe_TextDraw[playerid][0], 2);
		PlayerTextDrawColor(playerid, Player_Safe_TextDraw[playerid][0], -1);
		PlayerTextDrawBackgroundColor(playerid, Player_Safe_TextDraw[playerid][0], 255);
		PlayerTextDrawBoxColor(playerid, Player_Safe_TextDraw[playerid][0], 95);
		PlayerTextDrawUseBox(playerid, Player_Safe_TextDraw[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, Player_Safe_TextDraw[playerid][0], 1);
		PlayerTextDrawSetSelectable(playerid, Player_Safe_TextDraw[playerid][0], 0);

		Player_Safe_TextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 182.000000 + 276.00, 144.000000, "_");
		PlayerTextDrawFont(playerid, Player_Safe_TextDraw[playerid][1], 1);
		PlayerTextDrawLetterSize(playerid, Player_Safe_TextDraw[playerid][1], 0.612500, 1.500002);
		PlayerTextDrawTextSize(playerid, Player_Safe_TextDraw[playerid][1], 299.500000, 253.000000);
		PlayerTextDrawSetOutline(playerid, Player_Safe_TextDraw[playerid][1], 1);
		PlayerTextDrawSetShadow(playerid, Player_Safe_TextDraw[playerid][1], 0);
		PlayerTextDrawAlignment(playerid, Player_Safe_TextDraw[playerid][1], 2);
		PlayerTextDrawColor(playerid, Player_Safe_TextDraw[playerid][1], -1);
		PlayerTextDrawBackgroundColor(playerid, Player_Safe_TextDraw[playerid][1], 255);
		PlayerTextDrawBoxColor(playerid, Player_Safe_TextDraw[playerid][1], 852308735);
		PlayerTextDrawUseBox(playerid, Player_Safe_TextDraw[playerid][1], 1);
		PlayerTextDrawSetProportional(playerid, Player_Safe_TextDraw[playerid][1], 1);
		PlayerTextDrawSetSelectable(playerid, Player_Safe_TextDraw[playerid][1], 0);

		Player_Safe_TextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 40.000000 + 276.00, 137.500000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, Player_Safe_TextDraw[playerid][2], 4);
		PlayerTextDrawLetterSize(playerid, Player_Safe_TextDraw[playerid][2], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, Player_Safe_TextDraw[playerid][2], 26.500000, 26.500000);
		PlayerTextDrawSetOutline(playerid, Player_Safe_TextDraw[playerid][2], 1);
		PlayerTextDrawSetShadow(playerid, Player_Safe_TextDraw[playerid][2], 0);
		PlayerTextDrawAlignment(playerid, Player_Safe_TextDraw[playerid][2], 1);
		PlayerTextDrawColor(playerid, Player_Safe_TextDraw[playerid][2], 852308735);
		PlayerTextDrawBackgroundColor(playerid, Player_Safe_TextDraw[playerid][2], 255);
		PlayerTextDrawBoxColor(playerid, Player_Safe_TextDraw[playerid][2], 50);
		PlayerTextDrawUseBox(playerid, Player_Safe_TextDraw[playerid][2], 1);
		PlayerTextDrawSetProportional(playerid, Player_Safe_TextDraw[playerid][2], 1);
		PlayerTextDrawSetSelectable(playerid, Player_Safe_TextDraw[playerid][2], 0);

		Player_Safe_TextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 296.000000 + 276.00, 137.500000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, Player_Safe_TextDraw[playerid][3], 4);
		PlayerTextDrawLetterSize(playerid, Player_Safe_TextDraw[playerid][3], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, Player_Safe_TextDraw[playerid][3], 27.000000, 26.600000);
		PlayerTextDrawSetOutline(playerid, Player_Safe_TextDraw[playerid][3], 1);
		PlayerTextDrawSetShadow(playerid, Player_Safe_TextDraw[playerid][3], 0);
		PlayerTextDrawAlignment(playerid, Player_Safe_TextDraw[playerid][3], 1);
		PlayerTextDrawColor(playerid, Player_Safe_TextDraw[playerid][3], 852308735);
		PlayerTextDrawBackgroundColor(playerid, Player_Safe_TextDraw[playerid][3], 255);
		PlayerTextDrawBoxColor(playerid, Player_Safe_TextDraw[playerid][3], 50);
		PlayerTextDrawUseBox(playerid, Player_Safe_TextDraw[playerid][3], 1);
		PlayerTextDrawSetProportional(playerid, Player_Safe_TextDraw[playerid][3], 1);
		PlayerTextDrawSetSelectable(playerid, Player_Safe_TextDraw[playerid][3], 0);

		Player_Safe_TextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 54.000000 + 276.00, 142.000000, "Safe");
		PlayerTextDrawFont(playerid, Player_Safe_TextDraw[playerid][4], 1);
		PlayerTextDrawLetterSize(playerid, Player_Safe_TextDraw[playerid][4], 0.295832, 1.649999);
		PlayerTextDrawTextSize(playerid, Player_Safe_TextDraw[playerid][4], 400.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, Player_Safe_TextDraw[playerid][4], 0);
		PlayerTextDrawSetShadow(playerid, Player_Safe_TextDraw[playerid][4], 0);
		PlayerTextDrawAlignment(playerid, Player_Safe_TextDraw[playerid][4], 1);
		PlayerTextDrawColor(playerid, Player_Safe_TextDraw[playerid][4], -1);
		PlayerTextDrawBackgroundColor(playerid, Player_Safe_TextDraw[playerid][4], 255);
		PlayerTextDrawBoxColor(playerid, Player_Safe_TextDraw[playerid][4], 50);
		PlayerTextDrawUseBox(playerid, Player_Safe_TextDraw[playerid][4], 0);
		PlayerTextDrawSetProportional(playerid, Player_Safe_TextDraw[playerid][4], 1);
		PlayerTextDrawSetSelectable(playerid, Player_Safe_TextDraw[playerid][4], 0);

		Player_Safe_TextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 312.000000 + 276.00, 163.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, Player_Safe_TextDraw[playerid][5], 4);
		PlayerTextDrawLetterSize(playerid, Player_Safe_TextDraw[playerid][5], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, Player_Safe_TextDraw[playerid][5], 11.000000, 12.000000);
		PlayerTextDrawSetOutline(playerid, Player_Safe_TextDraw[playerid][5], 1);
		PlayerTextDrawSetShadow(playerid, Player_Safe_TextDraw[playerid][5], 0);
		PlayerTextDrawAlignment(playerid, Player_Safe_TextDraw[playerid][5], 1);
		PlayerTextDrawColor(playerid, Player_Safe_TextDraw[playerid][5], 852308735);
		PlayerTextDrawBackgroundColor(playerid, Player_Safe_TextDraw[playerid][5], 255);
		PlayerTextDrawBoxColor(playerid, Player_Safe_TextDraw[playerid][5], 50);
		PlayerTextDrawUseBox(playerid, Player_Safe_TextDraw[playerid][5], 1);
		PlayerTextDrawSetProportional(playerid, Player_Safe_TextDraw[playerid][5], 1);
		PlayerTextDrawSetSelectable(playerid, Player_Safe_TextDraw[playerid][5], 1);

		Player_Safe_TextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 312.000000 + 276.00, 178.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, Player_Safe_TextDraw[playerid][6], 4);
		PlayerTextDrawLetterSize(playerid, Player_Safe_TextDraw[playerid][6], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, Player_Safe_TextDraw[playerid][6], 11.000000, 12.000000);
		PlayerTextDrawSetOutline(playerid, Player_Safe_TextDraw[playerid][6], 1);
		PlayerTextDrawSetShadow(playerid, Player_Safe_TextDraw[playerid][6], 0);
		PlayerTextDrawAlignment(playerid, Player_Safe_TextDraw[playerid][6], 1);
		PlayerTextDrawColor(playerid, Player_Safe_TextDraw[playerid][6], 1296911871);
		PlayerTextDrawBackgroundColor(playerid, Player_Safe_TextDraw[playerid][6], 255);
		PlayerTextDrawBoxColor(playerid, Player_Safe_TextDraw[playerid][6], 50);
		PlayerTextDrawUseBox(playerid, Player_Safe_TextDraw[playerid][6], 1);
		PlayerTextDrawSetProportional(playerid, Player_Safe_TextDraw[playerid][6], 1);
		PlayerTextDrawSetSelectable(playerid, Player_Safe_TextDraw[playerid][6], 1);

		Player_Safe_TextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 312.000000 + 276.00, 194.000000, "ld_beat:chit");
		PlayerTextDrawFont(playerid, Player_Safe_TextDraw[playerid][7], 4);
		PlayerTextDrawLetterSize(playerid, Player_Safe_TextDraw[playerid][7], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, Player_Safe_TextDraw[playerid][7], 11.000000, 12.000000);
		PlayerTextDrawSetOutline(playerid, Player_Safe_TextDraw[playerid][7], 1);
		PlayerTextDrawSetShadow(playerid, Player_Safe_TextDraw[playerid][7], 0);
		PlayerTextDrawAlignment(playerid, Player_Safe_TextDraw[playerid][7], 1);
		PlayerTextDrawColor(playerid, Player_Safe_TextDraw[playerid][7], 1296911871);
		PlayerTextDrawBackgroundColor(playerid, Player_Safe_TextDraw[playerid][7], 255);
		PlayerTextDrawBoxColor(playerid, Player_Safe_TextDraw[playerid][7], 50);
		PlayerTextDrawUseBox(playerid, Player_Safe_TextDraw[playerid][7], 1);
		PlayerTextDrawSetProportional(playerid, Player_Safe_TextDraw[playerid][7], 1);
		PlayerTextDrawSetSelectable(playerid, Player_Safe_TextDraw[playerid][7], 1);

		for(new i=0; i<MAX_PLAYERINV_TD; i++) PlayerTextDrawShow(playerid, Player_Safe_TextDraw[playerid][i]);
		PlayerSafeTextDrawShow[playerid] = true;
	}
}