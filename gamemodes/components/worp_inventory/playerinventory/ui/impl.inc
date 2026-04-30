#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerClickTextDraw(playerid, Text:clickedid){
	if(LoggedIn[playerid]){
		if(PlayerInventoryTextDrawShow[playerid]){
			if(clickedid == Text:INVALID_TEXT_DRAW){
				DestroyPlayerInventoryTextDraw(playerid);
				return true;
			}
		}
	}
	return true;
}

void:ResetPlayerInventoryTextDraw(playerid){
	PlayerInventoryTextDrawShow[playerid] = false;
	Player_Inventory_Couting_TD[playerid] = 0;
}

void:DestroyPlayerInventorySlotTD(playerid){
	if(PlayerInventoryTextDrawShow[playerid]){
		for(new i=0; i<Player_Inventory_Couting_TD[playerid]; i++){
			if(IsPlayerTextDrawVisible(playerid, Player_Inventory_Slot_TD[playerid][i])){
				PlayerTextDrawHide(playerid, Player_Inventory_Slot_TD[playerid][i]);
			}

			PlayerTextDrawDestroy(playerid, Player_Inventory_Slot_TD[playerid][i]);
		}
		Player_Inventory_Couting_TD[playerid] = 0;

		if(PlayerSafeTextDrawShow[playerid]){
			DestroyPlayerSafeTextDraw(playerid);
		}
	}
	return true;
}

void:CreatePlayerInventorySlotTD(playerid){
	if(PlayerInventory_Type[playerid] == INVENTORY_DEFAULT){
		new Float:ModelX = 171.0, Float:NameX = 193.0, Float:AmountX = 193.0;
		new Float:ModelY = 128.0, Float:NameY = 164.0, Float:AmountY = 130.0;

		for(new i=0; i<MAX_INV_SLOT_ROWS; i++){
			for(new j=0; j<MAX_INV_SLOT_COLUMN; j++){
				Player_Inventory_Model[playerid][i][j] = Player_Inventory_Couting_TD[playerid];
				Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]] = CreatePlayerTextDraw(playerid, ModelX, ModelY, "Preview_Model");
				PlayerTextDrawFont(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 5);
				PlayerTextDrawLetterSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0.600000, 2.000000);
				PlayerTextDrawTextSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 44.000000, 46.500000);
				PlayerTextDrawSetOutline(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawAlignment(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 370546371);
				PlayerTextDrawBoxColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 255);
				PlayerTextDrawUseBox(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawSetPreviewModel(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], MODEL_NULL);
				PlayerTextDrawSetPreviewRot(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0.000000, 0.000000, 0.000000, 0.000000);
				// PlayerTextDrawSetPreviewRot(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], -28.000000, 0.000000, -20.000000, 1.000000);
				PlayerTextDrawSetPreviewVehCol(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]++], 1, 1);

				Player_Inventory_Name[playerid][i][j] = Player_Inventory_Couting_TD[playerid];
				Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]] = CreatePlayerTextDraw(playerid, NameX, NameY, "None");
				PlayerTextDrawFont(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawLetterSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0.183332, 0.899999);
				PlayerTextDrawTextSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 400.000000, 40.500000);
				PlayerTextDrawSetOutline(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawAlignment(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 2);
				PlayerTextDrawColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 255);
				PlayerTextDrawBoxColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], -1061109710);
				PlayerTextDrawUseBox(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]++], 0);

				Player_Inventory_Amount[playerid][i][j] = Player_Inventory_Couting_TD[playerid];
				Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]] = CreatePlayerTextDraw(playerid, AmountX, AmountY, "10,000,000");
				PlayerTextDrawFont(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawLetterSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0.137500, 0.800000);
				PlayerTextDrawTextSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 400.000000, 40.500000);
				PlayerTextDrawSetOutline(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawAlignment(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 2);
				PlayerTextDrawColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 255);
				PlayerTextDrawBoxColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], -1061109710);
				PlayerTextDrawUseBox(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]++], 0);

				ModelX += 49.0;
				NameX += 49.0;
				AmountX += 49.0;
			}

			ModelX = 171.0;
			NameX = 193.0;
			AmountX = 193.0;

			ModelY += 52.0;
			NameY += 52.0;
			AmountY += 52.0;
		}
	}
	else if(PlayerInventory_Type[playerid] == INVENTORY_SAFE){
		new Float:ModelX = 62.0, Float:NameX = 80.0, Float:AmountX = 79.5;
		new Float:ModelY = 165.0, Float:NameY = 193.0, Float:AmountY = 167.0;

		for(new i=0; i<MAX_INV_SLOT_ROWS; i++){
			for(new j=0; j<MAX_INV_SLOT_COLUMN; j++){
				Player_Inventory_Model[playerid][i][j] = Player_Inventory_Couting_TD[playerid];
				Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]] = CreatePlayerTextDraw(playerid, ModelX, ModelY, "Preview_Model");
				PlayerTextDrawFont(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 5);
				PlayerTextDrawLetterSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0.600000, 2.000000);
				PlayerTextDrawTextSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 35.000000, 38.000000);
				PlayerTextDrawSetOutline(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawAlignment(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 370546371);
				PlayerTextDrawBoxColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 255);
				PlayerTextDrawUseBox(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawSetPreviewModel(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], MODEL_NULL);
				PlayerTextDrawSetPreviewRot(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0.000000, 0.000000, 0.000000, 0.000000);
				PlayerTextDrawSetPreviewVehCol(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]++], 1, 1);

				Player_Inventory_Name[playerid][i][j] = Player_Inventory_Couting_TD[playerid];
				Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]] = CreatePlayerTextDraw(playerid, NameX, NameY, "None");
				PlayerTextDrawFont(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawLetterSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0.183329, 0.899999);
				PlayerTextDrawTextSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 400.000000, 30.500000);
				PlayerTextDrawSetOutline(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawAlignment(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 2);
				PlayerTextDrawColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 255);
				PlayerTextDrawBoxColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], -1061109710);
				PlayerTextDrawUseBox(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]++], 0);

				Player_Inventory_Amount[playerid][i][j] = Player_Inventory_Couting_TD[playerid];
				Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]] = CreatePlayerTextDraw(playerid, AmountX, AmountY, "10,000,000");
				PlayerTextDrawFont(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawLetterSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0.137500, 0.800000);
				PlayerTextDrawTextSize(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 400.000000, 31.000000);
				PlayerTextDrawSetOutline(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawAlignment(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 2);
				PlayerTextDrawColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 255);
				PlayerTextDrawBoxColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], -1061109710);
				PlayerTextDrawUseBox(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Couting_TD[playerid]++], 0);

				ModelX += 41.0;
				NameX += 41.0;
				AmountX += 41.0;
			}

			ModelX = 62.0;
			NameX = 80.0;
			AmountX = 79.5;

			ModelY += 44.0;
			NameY += 44.0;
			AmountY += 44.0;
		}
	}

	SetPlayerProgressBarMaxValue(playerid, PlayerInventoryWeightBar[playerid], PlayerData[playerid][pInvMaxWeight]);
	Player_Inventory_Render_Slot(playerid);
}

void:DestroyPlayerInventoryTextDraw(playerid){
	if(PlayerInventoryTextDrawShow[playerid]){
		DestroyPlayerInventorySlotTD(playerid);

		for(new i=0; i<MAX_PLAYERINV_TD; i++){
			if(IsPlayerTextDrawVisible(playerid, Player_Inventory_TextDraw[playerid][i])) PlayerTextDrawHide(playerid, Player_Inventory_TextDraw[playerid][i]);
			PlayerTextDrawDestroy(playerid, Player_Inventory_TextDraw[playerid][i]);
		}

		HidePlayerProgressBar(playerid, PlayerInventoryWeightBar[playerid]);
		DestroyPlayerProgressBar(playerid, PlayerInventoryWeightBar[playerid]);

		PlayerInventoryTextDrawShow[playerid] = false;
		CancelSelectTextDraw(playerid);
		TogglePlayerControllable(playerid, 1);
	}
}

void:CreatePlayerInventoryTextDraw(playerid){
	if(!PlayerInventoryTextDrawShow[playerid]){
		if(PlayerInventory_Type[playerid] == INVENTORY_DEFAULT){
			Player_Inventory_TextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 316.000000, -11.000000, "_"); // background
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][0], 1);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][0], 0.600000, 54.800003);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][0], 298.500000, 685.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][0], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][0], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][0], 2);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][0], -1);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][0], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][0], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][0], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][0], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][0], 0);

			Player_Inventory_TextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 315.000000, 111.000000, "_");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][1], 1);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][1], 0.604165, 36.499969);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][1], 298.500000, 306.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][1], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][1], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][1], 2);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][1], -1);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][1], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][1], 95);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][1], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][1], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][1], 0);

			Player_Inventory_TextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 315.000000, 106.000000, "_");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][2], 1);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][2], 0.612500, 1.500002);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][2], 298.500000, 295.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][2], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][2], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][2], 2);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][2], -1);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][2], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][2], 852308735);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][2], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][2], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][2], 0);

			Player_Inventory_TextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 152.000000, 99.500000, "ld_beat:chit");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][3], 4);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][3], 0.600000, 2.000000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][3], 26.000000, 26.500000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][3], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][3], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][3], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][3], 852308735);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][3], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][3], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][3], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][3], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][3], 0);

			Player_Inventory_TextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 452.000000, 99.500000, "ld_beat:chit");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][4], 4);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][4], 0.600000, 2.000000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][4], 27.000000, 26.600000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][4], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][4], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][4], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][4], 852308735);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][4], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][4], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][4], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][4], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][4], 0);

			Player_Inventory_TextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 167.000000, 104.000000, "Inventory");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][5], 1);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][5], 0.295832, 1.649999);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][5], 400.000000, 17.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][5], 0);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][5], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][5], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][5], -1);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][5], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][5], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][5], 0);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][5], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][5], 0);

			PlayerInventoryWeightBar[playerid] = CreatePlayerProgressBar(playerid, 389.000000, 109.000000, 78.500000, 7.500000, 370546371, 100.000000, 0);

			Player_Inventory_TextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 460.000000, 108.800003, "100.0/100.0");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][6], 1);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][6], 0.154165, 0.800000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][6], 400.000000, 72.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][6], 0);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][6], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][6], 3);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][6], -1);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][6], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][6], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][6], 0);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][6], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][6], 0);

			Player_Inventory_TextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 473.000000, 127.000000, "ld_beat:chit");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][7], 4);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][7], 0.600000, 2.000000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][7], 11.000000, 12.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][7], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][7], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][7], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][7], 852308735);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][7], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][7], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][7], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][7], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][7], 1);

			Player_Inventory_TextDraw[playerid][8] = CreatePlayerTextDraw(playerid, 473.000000, 141.000000, "ld_beat:chit");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][8], 4);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][8], 0.600000, 2.000000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][8], 11.000000, 12.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][8], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][8], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][8], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][8], 1296911871);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][8], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][8], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][8], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][8], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][8], 1);

			Player_Inventory_TextDraw[playerid][9] = CreatePlayerTextDraw(playerid, 473.000000, 156.000000, "ld_beat:chit");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][9], 4);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][9], 0.600000, 2.000000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][9], 11.000000, 12.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][9], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][9], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][9], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][9], 1296911871);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][9], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][9], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][9], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][9], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][9], 1);
		}
		else if(PlayerInventory_Type[playerid] == INVENTORY_SAFE){
			Player_Inventory_TextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 316.000000, -11.000000, "_");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][0], 1);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][0], 0.600000, 54.800003);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][0], 298.500000, 685.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][0], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][0], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][0], 2);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][0], -1);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][0], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][0], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][0], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][0], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][0], 0);

			Player_Inventory_TextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 182.000000, 151.000000, "_");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][1], 1);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][1], 0.604165, 31.100021);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][1], 296.000000, 252.500000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][1], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][1], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][1], 2);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][1], -1);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][1], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][1], 95);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][1], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][1], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][1], 0);

			Player_Inventory_TextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 182.000000, 144.000000, "_");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][2], 1);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][2], 0.612500, 1.500002);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][2], 299.500000, 253.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][2], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][2], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][2], 2);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][2], -1);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][2], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][2], 852308735);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][2], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][2], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][2], 0);

			Player_Inventory_TextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 40.000000, 137.500000, "ld_beat:chit");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][3], 4);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][3], 0.600000, 2.000000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][3], 26.500000, 26.500000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][3], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][3], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][3], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][3], 852308735);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][3], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][3], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][3], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][3], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][3], 0);

			Player_Inventory_TextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 296.000000, 137.500000, "ld_beat:chit");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][4], 4);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][4], 0.600000, 2.000000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][4], 27.000000, 26.600000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][4], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][4], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][4], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][4], 852308735);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][4], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][4], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][4], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][4], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][4], 0);

			Player_Inventory_TextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 54.000000, 142.000000, "Inventory");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][5], 1);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][5], 0.295832, 1.649999);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][5], 400.000000, 17.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][5], 0);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][5], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][5], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][5], -1);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][5], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][5], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][5], 0);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][5], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][5], 0);

			PlayerInventoryWeightBar[playerid] = CreatePlayerProgressBar(playerid, 230.000000, 147.000000, 78.500000, 7.500000, 370546371, 100.000000, 0);

			Player_Inventory_TextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 301.000000, 146.800003, "100.0/100.0");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][6], 1);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][6], 0.154164, 0.800000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][6], 400.000000, 72.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][6], 0);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][6], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][6], 3);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][6], -1);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][6], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][6], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][6], 0);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][6], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][6], 0);

			Player_Inventory_TextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 312.000000, 163.000000, "ld_beat:chit");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][7], 4);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][7], 0.600000, 2.000000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][7], 11.000000, 12.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][7], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][7], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][7], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][7], 852308735);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][7], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][7], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][7], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][7], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][7], 1);

			Player_Inventory_TextDraw[playerid][8] = CreatePlayerTextDraw(playerid, 312.000000, 178.000000, "ld_beat:chit");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][8], 4);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][8], 0.600000, 2.000000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][8], 11.000000, 12.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][8], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][8], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][8], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][8], 1296911871);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][8], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][8], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][8], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][8], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][8], 1);

			Player_Inventory_TextDraw[playerid][9] = CreatePlayerTextDraw(playerid, 312.000000, 194.000000, "ld_beat:chit");
			PlayerTextDrawFont(playerid, Player_Inventory_TextDraw[playerid][9], 4);
			PlayerTextDrawLetterSize(playerid, Player_Inventory_TextDraw[playerid][9], 0.600000, 2.000000);
			PlayerTextDrawTextSize(playerid, Player_Inventory_TextDraw[playerid][9], 11.000000, 12.000000);
			PlayerTextDrawSetOutline(playerid, Player_Inventory_TextDraw[playerid][9], 1);
			PlayerTextDrawSetShadow(playerid, Player_Inventory_TextDraw[playerid][9], 0);
			PlayerTextDrawAlignment(playerid, Player_Inventory_TextDraw[playerid][9], 1);
			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][9], 1296911871);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_TextDraw[playerid][9], 255);
			PlayerTextDrawBoxColor(playerid, Player_Inventory_TextDraw[playerid][9], 50);
			PlayerTextDrawUseBox(playerid, Player_Inventory_TextDraw[playerid][9], 1);
			PlayerTextDrawSetProportional(playerid, Player_Inventory_TextDraw[playerid][9], 1);
			PlayerTextDrawSetSelectable(playerid, Player_Inventory_TextDraw[playerid][9], 1);

			CreatePlayerSafeTextDraw(playerid);
		}

		for(new i=0; i<MAX_PLAYERINV_TD; i++) PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][i]);
		ShowPlayerProgressBar(playerid, PlayerInventoryWeightBar[playerid]);

		PlayerInventoryTextDrawShow[playerid] = true;
		SelectTextDraw(playerid, 852308735);
	}
}