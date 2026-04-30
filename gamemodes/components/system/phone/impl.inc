#if defined _inc_impl
	#undef _inc_impl
#endif

LoadPlayerPhoneTD(playerid){
    PlayerPhoneTD[playerid][0] = CreatePlayerTextDraw(playerid, 322.000000, 112.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][0], 0.600000, 28.099998);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][0], 298.500000, 134.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][0], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][0], 255);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][0], 0);

    PlayerPhoneTD[playerid][1] = CreatePlayerTextDraw(playerid, 322.000000, 117.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][1], 0.600000, 26.900016);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][1], 298.500000, 123.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][1], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][1], -1);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][1], 0);

    PlayerPhoneTD[playerid][2] = CreatePlayerTextDraw(playerid, 322.000000, 339.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][2], 0.600000, 2.250015);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][2], 298.500000, 123.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][2], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][2], -1094795521);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][2], 0);

    PlayerPhoneTD[playerid][3] = CreatePlayerTextDraw(playerid, 279.000000, 343.000000, "CALL");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][3], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][3], 0.229166, 1.299998);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][3], 16.500000, 30.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][3], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][3], 9109704);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][3], 1);

    PlayerPhoneTD[playerid][4] = CreatePlayerTextDraw(playerid, 363.000000, 343.000000, "CLOSE");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][4], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][4], 0.229166, 1.299998);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][4], 16.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][4], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][4], -1962934072);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][4], 1);

    PlayerPhoneTD[playerid][5] = CreatePlayerTextDraw(playerid, 275.000000, 139.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][5], 0.600000, 2.000004);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][5], 298.500000, 18.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][5], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][5], 135);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][5], 0);

    PlayerPhoneTD[playerid][6] = CreatePlayerTextDraw(playerid, 266.000000, 139.000000, "HUD:radar_gangN");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][6], 4);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][6], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][6], 17.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][6], 1);

    PlayerPhoneTD[playerid][7] = CreatePlayerTextDraw(playerid, 275.000000, 160.000000, "Contacts");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][7], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][7], 0.116664, 0.850000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][7], 400.000000, 25.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][7], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][7], 255);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][7], 135);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][7], 0);

    PlayerPhoneTD[playerid][8] = CreatePlayerTextDraw(playerid, 322.000000, 117.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][8], 0.600000, 0.950016);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][8], 298.500000, 123.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][8], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][8], -1094795521);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][8], 0);

    PlayerPhoneTD[playerid][9] = CreatePlayerTextDraw(playerid, 262.000000, 117.000000, "20:00");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][9], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][9], 0.129166, 0.850000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][9], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][9], 255);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][9], 50);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][9], 0);

    PlayerPhoneTD[playerid][10] = CreatePlayerTextDraw(playerid, 376.000000, 120.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][10], 0.600000, 0.250001);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][10], 298.500000, 9.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][10], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][10], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][10], 852308735);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][10], 255);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][10], 0);

    PlayerPhoneTD[playerid][11] = CreatePlayerTextDraw(playerid, 376.000000, 121.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][11], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][11], 0.600000, 0.050002);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][11], 298.500000, 7.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][11], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][11], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][11], 852308735);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][11], 9109759);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][11], 0);

    PlayerPhoneTD[playerid][12] = CreatePlayerTextDraw(playerid, 368.000000, 118.000000, "100%");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][12], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][12], 0.120833, 0.750000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][12], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][12], 3);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][12], 255);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][12], 50);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][12], 0);

    PlayerPhoneTD[playerid][13] = CreatePlayerTextDraw(playerid, 308.000000, 139.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][13], 0.600000, 2.000004);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][13], 298.500000, 18.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][13], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][13], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][13], 135);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][13], 0);

    PlayerPhoneTD[playerid][14] = CreatePlayerTextDraw(playerid, 301.000000, 141.000000, "HUD:radar_SWEET");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][14], 4);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][14], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][14], 13.500000, 14.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][14], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][14], 1);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][14], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][14], 50);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][14], 1);

    PlayerPhoneTD[playerid][15] = CreatePlayerTextDraw(playerid, 308.000000, 160.000000, "SMS");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][15], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][15], 0.116664, 0.850000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][15], 400.000000, 25.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][15], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][15], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][15], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][15], 255);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][15], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][15], 135);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][15], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][15], 0);

    PlayerPhoneTD[playerid][16] = CreatePlayerTextDraw(playerid, 322.000000, 117.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][16], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][16], 0.600000, 26.900016);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][16], 298.500000, 123.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][16], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][16], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][16], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][16], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][16], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][16], 1296911871);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][16], 0);

    PlayerPhoneTD[playerid][17] = CreatePlayerTextDraw(playerid, 285.000000, 140.000000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][17], 4);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][17], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][17], 69.500000, 77.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][17], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][17], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][17], 1);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][17], -1094795521);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][17], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][17], 50);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][17], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][17], 0);

    PlayerPhoneTD[playerid][18] = CreatePlayerTextDraw(playerid, 322.000000, 225.000000, "UNKNOW");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][18], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][18], 0.141666, 0.900000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][18], 400.000000, 117.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][18], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][18], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][18], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][18], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][18], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][18], 50);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][18], 0);

    PlayerPhoneTD[playerid][19] = CreatePlayerTextDraw(playerid, 290.000000, 301.000000, "ACCEPT");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][19], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][19], 0.220832, 1.699997);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][19], 16.500000, 50.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][19], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][19], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][19], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][19], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][19], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][19], 9109704);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][19], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][19], 1);

    PlayerPhoneTD[playerid][20] = CreatePlayerTextDraw(playerid, 354.000000, 301.000000, "Decline");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][20], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][20], 0.220832, 1.699997);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][20], 16.500000, 50.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][20], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][20], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][20], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][20], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][20], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][20], -1962934072);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][20], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][20], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][20], 1);

    PlayerPhoneTD[playerid][21] = CreatePlayerTextDraw(playerid, 320.000000, 157.000000, "U");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][21], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][21], 0.741666, 3.950000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][21], 400.000000, 117.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][21], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][21], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][21], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][21], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][21], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][21], 50);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][21], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][21], 0);

    PlayerPhoneTD[playerid][22] = CreatePlayerTextDraw(playerid, 322.000000, 244.000000, "94856");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][22], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][22], 0.320833, 1.450000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][22], 400.000000, 117.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][22], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][22], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][22], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][22], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][22], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][22], 50);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][22], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][22], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][22], 0);

    PlayerPhoneTD[playerid][23] = CreatePlayerTextDraw(playerid, 337.000000, 139.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][23], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][23], 0.600000, 2.000004);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][23], 298.500000, 18.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][23], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][23], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][23], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][23], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][23], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][23], 135);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][23], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][23], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][23], 0);

    PlayerPhoneTD[playerid][24] = CreatePlayerTextDraw(playerid, 330.000000, 141.000000, "HUD:radar_CATALINAPINK");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][24], 4);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][24], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][24], 13.500000, 14.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][24], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][24], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][24], 1);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][24], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][24], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][24], -741092558);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][24], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][24], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][24], 1);

    PlayerPhoneTD[playerid][25] = CreatePlayerTextDraw(playerid, 337.000000, 160.000000, "CAMERA");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][25], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][25], 0.116663, 0.850000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][25], 400.000000, 25.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][25], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][25], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][25], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][25], 255);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][25], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][25], 135);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][25], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][25], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][25], 0);

    PlayerPhoneTD[playerid][26] = CreatePlayerTextDraw(playerid, 368.000000, 139.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][26], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][26], 0.600000, 2.000004);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][26], 298.500000, 18.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][26], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][26], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][26], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][26], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][26], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][26], 135);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][26], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][26], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][26], 0);

    PlayerPhoneTD[playerid][27] = CreatePlayerTextDraw(playerid, 361.000000, 141.000000, "HUD:radar_cash");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][27], 4);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][27], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][27], 13.500000, 14.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][27], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][27], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][27], 1);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][27], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][27], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][27], -741092558);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][27], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][27], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][27], 1);

    PlayerPhoneTD[playerid][28] = CreatePlayerTextDraw(playerid, 368.000000, 160.000000, "BANK");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][28], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][28], 0.116663, 0.850000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][28], 400.000000, 25.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][28], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][28], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][28], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][28], 255);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][28], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][28], 135);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][28], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][28], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][28], 0);

    PlayerPhoneTD[playerid][29] = CreatePlayerTextDraw(playerid, 275.000000, 177.000000, "_");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][29], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][29], 0.600000, 2.000004);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][29], 298.500000, 18.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][29], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][29], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][29], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][29], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][29], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][29], 135);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][29], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][29], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][29], 0);

    PlayerPhoneTD[playerid][30] = CreatePlayerTextDraw(playerid, 266.000000, 177.000000, "HUD:radar_mafiaCasino");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][30], 4);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][30], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][30], 17.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][30], 1);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][30], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][30], 1);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][30], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][30], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][30], 50);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][30], 1);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][30], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][30], 1);

    PlayerPhoneTD[playerid][31] = CreatePlayerTextDraw(playerid, 275.000000, 198.000000, "ECONOMY");
    PlayerTextDrawFont(playerid, PlayerPhoneTD[playerid][31], 2);
    PlayerTextDrawLetterSize(playerid, PlayerPhoneTD[playerid][31], 0.116663, 0.850000);
    PlayerTextDrawTextSize(playerid, PlayerPhoneTD[playerid][31], 400.000000, 25.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPhoneTD[playerid][31], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPhoneTD[playerid][31], 0);
    PlayerTextDrawAlignment(playerid, PlayerPhoneTD[playerid][31], 2);
    PlayerTextDrawColor(playerid, PlayerPhoneTD[playerid][31], 255);
    PlayerTextDrawBackgroundColor(playerid, PlayerPhoneTD[playerid][31], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPhoneTD[playerid][31], 135);
    PlayerTextDrawUseBox(playerid, PlayerPhoneTD[playerid][31], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPhoneTD[playerid][31], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPhoneTD[playerid][31], 0);
    return 1;
}

forward ShowMobilePhone(playerid);
public ShowMobilePhone(playerid){
    PlayerUsingPhone[playerid] = 1;

    for(new i=0; i<16; i++)
        PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][i]);

    for(new i=23; i<MAX_PHONETEXT; i++)
        PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][i]);

    SelectTextDraw(playerid, 0x00BC1AAA);
    return 1;
}

forward ShowCallInPhone(playerid);
public ShowCallInPhone(playerid){
    PlayerUsingPhone[playerid] = 1;

    new string[128], name[128];
    new count = 0;

    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][0]);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][16]);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][17]);

    for (new i = 0; i != MAX_CONTACTS; i ++)
    {
        if (ContactData[playerid][i][contactExists])
        {
            if(ContactData[playerid][i][contactNumber] == PlayerData[playerid][pNumberPhoneCall])
                count++;
        }   
    }

    if(count){
        format(name, sizeof(name), "%s", ReturnRoleplayName(PlayerData[playerid][pCallLine]));
    }
    else{
        format(name, sizeof(name), "UNKNOW");
    }

    PlayerTextDrawSetString(playerid, PlayerPhoneTD[playerid][18], name);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][18]);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][19]);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][20]);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][21]);

    format(string, sizeof(string), "%d", PlayerData[playerid][pNumberPhoneCall]);
    PlayerTextDrawSetString(playerid, PlayerPhoneTD[playerid][22], string);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][22]);

    SelectTextDraw(playerid, 0x00BC1AAA);
    return 1;
}

forward ShowCallingPhone(playerid);
public ShowCallingPhone(playerid){
    PlayerUsingPhone[playerid] = 1;
    new string[128], name[128];

    new count = 0;

    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][0]);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][16]);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][17]);

    for (new i = 0; i != MAX_CONTACTS; i ++)
    {
        if (ContactData[playerid][i][contactExists])
        {
            if(ContactData[playerid][i][contactNumber] == PlayerData[playerid][pNumberPhoneCall])
                count++;
        }   
    }

    if(count){
        format(name, sizeof(name), "%s", ReturnRoleplayName(PlayerData[playerid][pCallLine]));
    }
    else{
        format(name, sizeof(name), "UNKNOW");
    }


    PlayerTextDrawSetString(playerid, PlayerPhoneTD[playerid][18], name);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][18]);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][20]);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][21]);

    format(string, sizeof(string), "%d", PlayerData[playerid][pNumberPhoneCall]);
    PlayerTextDrawSetString(playerid, PlayerPhoneTD[playerid][22], string);
    PlayerTextDrawShow(playerid, PlayerPhoneTD[playerid][22]);

    SelectTextDraw(playerid, 0x00BC1AAA);
    return 1;
}

HideMobilePhone(playerid){
    PlayerUsingPhone[playerid] = 0;
    RemoveAttachedObject(playerid, 7);
    for(new i=0; i<MAX_PHONETEXT; i++){
        PlayerTextDrawHide(playerid, PlayerPhoneTD[playerid][i]);
        PlayerTextDrawDestroy(playerid, PlayerPhoneTD[playerid][i]);
    }

    CancelSelectTextDraw(playerid);
    return 1;
}

ShowCallPhone(playerid){
    new
	    str[64];

	format(str, sizeof(str), "โทรศัพท์ (เบอร์ของคุณคือ: %d)", PlayerData[playerid][pNumberPhone]);

    Dialog_ShowEasy(playerid, PhoneCall, DIALOG_STYLE_INPUT, str, "กรอกเบอร์โทรศัพท์ที่ต้องการจะโทรหา:", "เลือก", "ยกเลิก");
    return 1;
}

stock ShowContacts(playerid)
{
	new
	    string[32 * MAX_CONTACTS],
		count = 0;

	string = "เพิ่มรายชื่อ\n";

	for (new i = 0; i != MAX_CONTACTS; i ++) if (ContactData[playerid][i][contactExists]) {
	    format(string, sizeof(string), "%s%s - #%d\n", string, ContactData[playerid][i][contactName], ContactData[playerid][i][contactNumber]);

		ListedContacts[playerid][count++] = i;
	}
	Dialog_ShowEasy(playerid, Contacts, DIALOG_STYLE_LIST, "รายชื่อผู้ติดต่อของคุณ", string, "เลือก", "ยกเลิก");
	return 1;
}

Dialog:Contacts(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
	if (response)
	{
	    if (!listitem) {
	        Dialog_ShowEasy(playerid, NewContact, DIALOG_STYLE_INPUT, "เพิ่มผู้ติดต่อใหม่", "โปรดป้อนชื่อผู้ติดต่อด้านล่าง:", "ตกลง", "ยกเลิก");
	    }
	    else {
		    PlayerData[playerid][pContact] = ListedContacts[playerid][listitem - 1];

	        Dialog_ShowEasy(playerid, ContactInfo, DIALOG_STYLE_LIST, ContactData[playerid][PlayerData[playerid][pContact]][contactName], "โทรหาผู้ติดต่อนี้\nส่งข้อความ\nลบผู้ติดต่อ", "เลือก", "กลับ");
	    }
	}

	for (new i = 0; i != MAX_CONTACTS; i ++) {
	    ListedContacts[playerid][i] = -1;
	}
	return 1;
}

Dialog:NewContact(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (isnull(inputtext))
			return Dialog_ShowEasy(playerid, NewContact, DIALOG_STYLE_INPUT, "เพิ่มผู้ติดต่อใหม่", "ข้อผิดพลาด: โปรดป้อนชื่อผู้ติดต่อ\n\nโปรดป้อนชื่อผู้ติดต่อด้านล่าง:", "ตกลง", "กลับ");

	    if (strlen(inputtext) > 32)
	        return Dialog_ShowEasy(playerid, NewContact, DIALOG_STYLE_INPUT, "เพิ่มผู้ติดต่อใหม่", "ข้อผิดพลาด: ชื่อผู้ติดต่อไม่ควรเกิน 32 ตัวอักษร\n\nโปรดป้อนชื่อผู้ติดต่อด้านล่าง:", "ตกลง", "กลับ");

		strpack(PlayerData[playerid][pEditingItem], inputtext, 32);

	    Dialog_ShowEasy(playerid, EnterNumber, DIALOG_STYLE_INPUT, "เพิ่มผู้ติดต่อใหม่", "ชื่อผู้ติดต่อ: %s\n\nโปรดป้อนเบอร์โทรศัพท์ของผู้ติดต่อ:", "ตกลง", "กลับ", inputtext);
	}
	else return 1;
	return 1;
}

Dialog:EnterNumber(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new
	        name[32],
			string[128];

		strunpack(name, PlayerData[playerid][pEditingItem]);

	    if (isnull(inputtext) || !IsNumeric(inputtext))
	        return Dialog_ShowEasy(playerid, EnterNumber, DIALOG_STYLE_INPUT, "เพิ่มผู้ติดต่อใหม่", "ชื่อผู้ติดต่อ: %s\n\nโปรดระบุเบอร์โทรศัพท์สำหรับผู้ติดต่อนี้:", "ตกลง", "กลับ", name);

		for (new i = 0; i != MAX_CONTACTS; i ++)
		{
			if (!ContactData[playerid][i][contactExists])
			{
            	ContactData[playerid][i][contactExists] = true;
            	ContactData[playerid][i][contactNumber] = strval(inputtext);

				format(ContactData[playerid][i][contactName], 32, name);

				format(string, sizeof(string), "INSERT INTO `contacts` (`ID`, `contactName`, `contactNumber`) VALUES('%d', '%s', '%d')", PlayerData[playerid][pID], SQL_ReturnEscaped(name), ContactData[playerid][i][contactNumber]);
				mysql_tquery(dbCon, string, "OnContactAdd", "dd", playerid, i);

                SendClientMessageEx(playerid, -1, "คุณได้เพิ่ม \"%s\" ในรายชื่อผู้ติดต่อของคุณ", name);
                return 1;
			}
	    }
	    ErrorMsg(playerid, "ไม่มีที่ว่างในรายชื่อีกแล้ว");
	}
	else {
		ShowContacts(playerid);
	}
	return 1;
}

forward OnContactAdd(playerid, id);
public OnContactAdd(playerid, id)
{
	ContactData[playerid][id][contactID] = cache_insert_id();
	return 1;
}


Dialog:ContactInfo(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new
			id = PlayerData[playerid][pContact],
			string[72];

		switch (listitem)
		{
		    case 0:
		    {
		        format(string, 32, "%d", ContactData[playerid][id][contactNumber]);
				callcmd::call(playerid, string);
		    }
            case 1:{
                new caption[128];
                PlayerGetNumberSMS[playerid] = ContactData[playerid][id][contactNumber];
                format(caption, sizeof(caption), "ส่งข้อความถึง: #%d", ContactData[playerid][id][contactNumber]);
                Dialog_ShowEasy(playerid, SendMessageSms, DIALOG_STYLE_INPUT, caption, "พิมพ์ข้อความที่คุณต้องการจะส่ง:", "ตกลง", "ยกเลิก");
            }
		    case 2:
		    {
		        format(string, sizeof(string), "DELETE FROM `contacts` WHERE `ID` = '%d' AND `contactID` = '%d'", PlayerData[playerid][pID], ContactData[playerid][id][contactID]);
		        mysql_tquery(dbCon, string);

                SendClientMessageEx(playerid, -1, "คุณได้ลบ \"%s\" ออกจากรายชื่อผู้ติดต่อ", ContactData[playerid][id][contactName]);

		        ContactData[playerid][id][contactExists] = false;
		        ContactData[playerid][id][contactNumber] = 0;
		        ContactData[playerid][id][contactID] = 0;

		        ShowContacts(playerid);
		    }
		}
	}
	else {
	    ShowContacts(playerid);
	}
	return 1;
}

Dialog:PhoneCall(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new
	        string[32],
	        str[64];

	    if (isnull(inputtext) || !IsNumeric(inputtext)){
            format(str, sizeof(str), "โทรศัพท์ (เบอร์ของคุณคือ: %d)", PlayerData[playerid][pNumberPhone]);
            return Dialog_ShowEasy(playerid, PhoneCall, DIALOG_STYLE_INPUT, str, "* คุณกรอกเบอร์ไม่ถูกต้อง *\nกรอกเบอร์โทรศัพท์ที่ต้องการจะโทรหา:", "เลือก", "ยกเลิก");
        }

        format(string, sizeof(string), "%d", strval(inputtext));
		callcmd::call(playerid, string);
    }
    return 1;
}

CMD:getangle(playerid, params[]){
    new Float:ang;
    GetPlayerFacingAngle(playerid, ang);
    printf("%.2f", ang);
    return 1;
}

SetPlayerEnterCamera(playerid){

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ErrorMsg(playerid, "คุณต้องไม่อยู่บนรถ");

    if(PlayerEnterCamera[playerid] == 0){
        if(!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_FPS)) {
            SetPVarInt(playerid, "DisableFPS", 1);
            if(IsValidObject(PlayerData[playerid][pCameraFPS]) && PlayerData[playerid][pCameraFPS]) DestroyObject(PlayerData[playerid][pCameraFPS]);
            PlayerData[playerid][pCameraFPS] = CreateObject(19300, 0.0, 0.0, 5.0, 0.0, 0.0, 0.0);
            SetCameraBehindPlayer(playerid);
            SyncCamera(playerid);
            BitFlag_On(g_PlayerFlags[playerid], PLAYER_FPS);
            PlayerEnterCamera[playerid] = 1;
            SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: กดปุ่ม 'ALT' เพื่อออกจากมุมกล้อง");
            SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: กดปุ่ม 'ต่อย' เพื่อเปลี่ยนมุมกล้อง");
            HideMobilePhone(playerid);
            TogglePlayerControllable(playerid, 0);
        } 
    }
    else if(PlayerEnterCamera[playerid] == 1){
        if(BitFlag_Get(g_PlayerFlags[playerid], PLAYER_FPS)) {
            SetPVarInt(playerid, "DisableFPS", 0);
            if(IsValidObject(PlayerData[playerid][pCameraFPS]) && PlayerData[playerid][pCameraFPS]) DestroyObject(PlayerData[playerid][pCameraFPS]);
            SetCameraBehindPlayer(playerid);
            BitFlag_Off(g_PlayerFlags[playerid], PLAYER_FPS);
            PlayerEnterCamera[playerid] = 0;
            PlayerCameraType[playerid] = 0;
            ClearAnimations(playerid);
            HideMobilePhone(playerid);
            TogglePlayerControllable(playerid, 1);
        }
    }
    return 1;
}

CMD:sms(playerid, params[]){

    if(!LoggedIn[playerid]) return 1;

    new number, stringsms[128];
    new targetid;

    if (PlayerInventory_AllCount(playerid, "Mobile Phone") <= 0) return ErrorMsg(playerid, "คุณไม่ได้เป็นเจ้าของโทรศัพท์มือถือใดๆ");

    if(PlayerData[playerid][pNumberPhone] == 0) return 1;

    if (PlayerData[playerid][pInHospital] == 1 || BitFlag_Get(g_PlayerFlags[playerid], PLAYER_CUFFED) || PlayerData[playerid][pInjured]) return ErrorMsg(playerid, "คุณไม่สามารถใช้คำสั่งได้ในขณะนี้");

    if (BitFlag_Get(g_PlayerFlags[playerid],PLAYER_PHONE_OFF)) return ErrorMsg(playerid, "โปรดเปิดโทรศัพท์มือถือของท่านก่อน");

    if(sscanf(params, "ds[128]", number, stringsms))
        return SystemMsg(playerid, "/sms [เบอร์โทรศัพท์ที่ต้องการส่ง] [ข้อความ]");

    if (GetNumberOwner(number) == INVALID_PLAYER_ID)
        return ErrorMsg(playerid, "ไม่พบเบอร์ติดต่อ");

    if (isnull(stringsms))
        return ErrorMsg(playerid, "คุณจำเป็นต้องกรอกข้อความ");

    if(GetMoney(playerid) < 5)
        return ErrorMsg(playerid, "คุณมีเงินไม่ในการส่งข้อความ");
        
    targetid = GetNumberOwner(number);

    if (BitFlag_Get(g_PlayerFlags[targetid], PLAYER_PHONE_OFF)) return ErrorMsg(playerid, "ปลายสายได้ปิดโทรศัพทของเขา");

    GiveMoney(playerid, -5, "send messagephone");
    SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ส่งข้อความหาเบอร์ #%d ว่า: %s", number, stringsms);
    SendClientMessageEx(targetid, COLOR_YELLOW, "คุณได้รับข้อความจาก #%d ว่า: %s", PlayerData[playerid][pNumberPhone], stringsms);
    return 1;
}

CMD:call(playerid, const params[]){
    if(!LoggedIn[playerid]) return 1;
    if (PlayerInventory_AllCount(playerid, "Mobile Phone") <= 0) return ErrorMsg(playerid, "คุณไม่ได้เป็นเจ้าของโทรศัพท์มือถือใดๆ");

    if(PlayerData[playerid][pNumberPhone] == 0) return 1;

    if (BitFlag_Get(g_PlayerFlags[playerid],PLAYER_PHONE_OFF)) return ErrorMsg(playerid, "โปรดเปิดโทรศัพท์มือถือของท่านก่อน");

    if (PlayerData[playerid][pInHospital] == 1 || BitFlag_Get(g_PlayerFlags[playerid], PLAYER_CUFFED) || PlayerData[playerid][pInjured]) return ErrorMsg(playerid, "คุณไม่สามารถใช้คำสั่งได้ในขณะนี้");

	new
	    targetid,
		number;

	if (sscanf(params, "d", number)){
        SystemMsg(playerid, "/call [หมายเลขโทรศัพท์]");
        return SystemMsg(playerid, "(911 = เพื่อเหตุด่วน) (112 = ช่างยนต์)");
    }

    if(PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID) return ErrorMsg(playerid, "เบอร์ที่คุณติดต่อกำลังติดสายอื่นอยู่");

	if (!number)
	    return ErrorMsg(playerid, "หมายเลขนี้ยังไม่เปิดใช้บริการ");

	if (number == 911)
	{
		PlayerData[playerid][pEmergency] = 1;
		PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
		ApplyAnimationEx(playerid, "PED", "phone_in", 4.1, 0, 0, 0, 0, 0, 1);

		SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s หยิบโทรศัพท์ออกมาและโทรออก", ReturnRoleplayName(playerid));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "[OPERATOR]:{FFFFFF} คุณต้องการรับบริการใด?: \"ตำรวจ\" หรือ \"หมอ\"?");

        HideMobilePhone(playerid);
        SetPlayerAttachedObject(playerid,7,18872,6,0.080999,0.001000,0.018000,-98.399986,0.000000,168.799987,1.000000,1.000000,1.000000);
	}
    else if(number == 112){
        PlayerData[playerid][pMechanicCall] = 1;
		PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
		ApplyAnimationEx(playerid, "PED", "phone_in", 4.1, 0, 0, 0, 0, 0, 1);

		SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s หยิบโทรศัพท์ออกมาและโทรออก", ReturnRoleplayName(playerid));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "[OPERATOR]:{FFFFFF} กรุณาพิมพ์รายละเอียดให้ช่างยนต์ทราบ?");

        HideMobilePhone(playerid);
        SetPlayerAttachedObject(playerid,7,18872,6,0.080999,0.001000,0.018000,-98.399986,0.000000,168.799987,1.000000,1.000000,1.000000);
    }
	else if ((targetid = GetNumberOwner(number)) != INVALID_PLAYER_ID)
	{
	    if (targetid == playerid)
	        return ErrorMsg(playerid, "คุณไม่สามารถโทรหาตัวเองได้!");

		if (BitFlag_Get(g_PlayerFlags[targetid], PLAYER_PHONE_OFF))
		    return ErrorMsg(playerid, "ปลายสายได้ปิดโทรศัพทของเขา");

        if(PlayerData[targetid][pCallLine] != INVALID_PLAYER_ID) return ErrorMsg(playerid, "หมายเลขปลายทางที่คุณเรียกกำลังติดสายอยู่");

		PlayerData[targetid][pIncomingCall] = 1;
		PlayerData[playerid][pIncomingCall] = 1;

		PlayerData[targetid][pCallLine] = playerid;
		PlayerData[playerid][pCallLine] = targetid;

        PlayerData[targetid][pNumberPhoneCall] = PlayerData[playerid][pNumberPhone];
        PlayerData[playerid][pNumberPhoneCall] = PlayerData[targetid][pNumberPhone];

		SendClientMessageEx(playerid, COLOR_YELLOW, "[PHONE]:{FFFFFF} กำลังโทรหา #%d, โปรดรอปลายสายรับ...", number);
		SendClientMessageEx(targetid, COLOR_YELLOW, "[PHONE]:{FFFFFF} สายเข้าจาก #%d", PlayerData[targetid][pNumberPhoneCall]);

        if(PlayerUsingPhone[targetid] == 1){
            HideMobilePhone(targetid);
        }

        LoadPlayerPhoneTD(targetid);
        SetTimerEx("ShowCallInPhone", 500, false, "d", targetid);

        PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
        PlayerPlaySoundEx(targetid, 23000);
        ApplyAnimation(playerid, "PED", "phone_in", 4.1, 0, 0, 0, 0, 0, 1);

		SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s หยิบโทรศัพท์ออกมาและโทรออก", ReturnRoleplayName(playerid));
        HideMobilePhone(playerid);
        SetPlayerAttachedObject(playerid,7,18872,6,0.080999,0.001000,0.018000,-98.399986,0.000000,168.799987,1.000000,1.000000,1.000000);
	}
	else
	{
	    ErrorMsg(playerid, "หมายเลขโทรศัพท์นี้ไม่ได้เปิดใช้บริการ");
	}
	return 1;
}

alias:hangup("h")
CMD:hangup(playerid, const params[])
{
    if(!LoggedIn[playerid]) return ErrorMsg(playerid, "อย่าเสือกกดไอสัส");

	if (PlayerData[playerid][pEmergency]){
	    PlayerData[playerid][pEmergency] = 0;
        RemoveAttachedObject(playerid, 7);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้วางสายโทรศัพท์ของเขา", ReturnRoleplayName(playerid));
        ApplyAnimationEx(playerid, "PED", "phone_out", 4.1, 0, 0, 0, 0, 0, 1);
		return 0;
	}

    if(PlayerData[playerid][pMechanicCall] == 1){
        PlayerData[playerid][pMechanicCall] = 0;
        RemoveAttachedObject(playerid, 7);
        SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้วางสายโทรศัพท์ของเขา", ReturnRoleplayName(playerid));
        ApplyAnimationEx(playerid, "PED", "phone_out", 4.1, 0, 0, 0, 0, 0, 1);
		return 0;
    }

    new targetid = PlayerData[playerid][pCallLine];

	if (targetid == INVALID_PLAYER_ID)
	    return ErrorMsg(playerid, "ไม่มีใครโทรหาคุณ");

	if (PlayerData[playerid][pIncomingCall])
	{
	    SendClientMessage(playerid, COLOR_YELLOW, "[PHONE]:{FFFFFF} คุณตัดสายเรียกเข้า");
	    SendClientMessage(targetid, COLOR_YELLOW, "[PHONE]:{FFFFFF} สายปลายทางตัดสายทิ้ง");
        ApplyAnimationEx(playerid, "PED", "phone_out", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

		SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้ตัดสายเรียกเข้า", ReturnRoleplayName(playerid));
        RemoveAttachedObject(playerid, 7);
	}
	else
	{
        SendClientMessage(playerid, COLOR_YELLOW, "[PHONE]:{FFFFFF} คุณวางสายการโทร");
	    SendClientMessage(targetid, COLOR_YELLOW, "[PHONE]:{FFFFFF} สายปลายทางได้วางจากการโทรแล้ว");

        ApplyAnimationEx(playerid, "PED", "phone_out", 4.1, 0, 0, 0, 0, 0, 1);

	    SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้วางสายโทรศัพท์ของเขา", ReturnRoleplayName(playerid));
	    SendNearbyMessage(targetid, 30.0, COLOR_RP, "** %s ได้วางสายโทรศัพท์ของเขา", ReturnRoleplayName(targetid));

        if (OnPhone[targetid] && PlayerData[targetid][pCallLine] != INVALID_PLAYER_ID) {
            SvDetachSpeakerFromStream(OnPhone[targetid], targetid);
        }

        if(OnPhone[targetid] && PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID){
            SvDetachSpeakerFromStream(OnPhone[targetid], playerid);
        }

        if(OnPhone[targetid]){
            SvDetachListenerFromStream(OnPhone[targetid], targetid);
            SvDetachListenerFromStream(OnPhone[targetid], playerid);
            SvDeleteStream(OnPhone[targetid]);
            OnPhone[targetid] = SV_NULL;
        }

        if (OnPhone[playerid] && PlayerData[targetid][pCallLine] != INVALID_PLAYER_ID) {
            SvDetachSpeakerFromStream(OnPhone[playerid], targetid);
        }

        if(OnPhone[playerid] && PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID){
            SvDetachSpeakerFromStream(OnPhone[playerid], playerid);
        }

        if(OnPhone[playerid]){
            SvDetachListenerFromStream(OnPhone[playerid], targetid);
            SvDetachListenerFromStream(OnPhone[playerid], playerid);
            SvDeleteStream(OnPhone[playerid]);
            OnPhone[playerid] = SV_NULL;
        }

        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);

        RemoveAttachedObject(playerid, 7);
        RemoveAttachedObject(targetid, 7);

	}

	PlayerData[playerid][pIncomingCall] = 0;
	PlayerData[targetid][pIncomingCall] = 0;

	PlayerData[playerid][pCallLine] = INVALID_PLAYER_ID;
	PlayerData[targetid][pCallLine] = INVALID_PLAYER_ID;

	return 1;
}

CMD:answer(playerid, const params[])
{
    if(!LoggedIn[playerid]) return ErrorMsg(playerid, "อย่าเสือกกดไอสัส");

	if (!PlayerData[playerid][pIncomingCall])
	    return ErrorMsg(playerid, "ไม่มีสายเรียกเข้าเพื่อรับสาย");

	if (BitFlag_Get(g_PlayerFlags[playerid], PLAYER_CUFFED))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้คำสั่งนี้ได้ในขณะนี้");

    if (BitFlag_Get(g_PlayerFlags[playerid],PLAYER_PHONE_OFF))
    	return ErrorMsg(playerid, "คุณต้องเปิดเครื่องโทรศัพท์ก่อน");

	new targetid = PlayerData[playerid][pCallLine];

	PlayerData[playerid][pIncomingCall] = 0;
	PlayerData[targetid][pIncomingCall] = 0;

    SetPlayerAttachedObject(playerid,7,18872,6,0.080999,0.001000,0.018000,-98.399986,0.000000,168.799987,1.000000,1.000000,1.000000);
    SetPlayerAttachedObject(targetid,7,18872,6,0.080999,0.001000,0.018000,-98.399986,0.000000,168.799987,1.000000,1.000000,1.000000);

	SendClientMessage(playerid, COLOR_YELLOW, "[SERVER]:{FFFFFF} คุณรับสายเรียกเข้าแล้ว");
	SendClientMessage(targetid, COLOR_YELLOW, "[SERVER]:{FFFFFF} สายปลายทางได้รับสายแล้ว");

	SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s ได้รับสายที่เรียกเข้า", ReturnRoleplayName(playerid));
    SendClientMessage(playerid, COLOR_YELLOW, "[แนะนำ]: สามารถกดปุ่มพูดเพื่อคุยกันได้");
    SendClientMessage(targetid, COLOR_YELLOW, "[แนะนำ]: สามารถกดปุ่มพูดเพื่อคุยกันได้");

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_USECELLPHONE);

    OnPhone[targetid] = SvCreateGStream(0xFFA200FF, "InPhone");

    if (OnPhone[targetid]) {
        SvAttachListenerToStream(OnPhone[targetid], targetid);
        SvAttachListenerToStream(OnPhone[targetid], playerid);
    }
    if (OnPhone[targetid] && PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID) {
        SvAttachSpeakerToStream(OnPhone[targetid], playerid);
    }

    if(OnPhone[targetid] && PlayerData[targetid][pCallLine] != INVALID_PLAYER_ID){
        SvAttachSpeakerToStream(OnPhone[targetid], targetid);
    }
	return 1;
}

CMD:togphone(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if (!BitFlag_Get(g_PlayerFlags[playerid],PLAYER_PHONE_OFF)){
        if(PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID){
            callcmd::hangup(playerid, "\1");
        }
        BitFlag_On(g_PlayerFlags[playerid],PLAYER_PHONE_OFF);
        SendClientMessage(playerid, COLOR_YELLOW, "คุณได้ปิดโทรศัพท์ของคุณแล้ว");
    }
    else{
        BitFlag_Off(g_PlayerFlags[playerid],PLAYER_PHONE_OFF);
        SendClientMessage(playerid, COLOR_YELLOW, "คุณได้เปิดโทรศัพท์ของคุณแล้ว");
    }
    return 1;
}

stock IsPlayerOnPhone(playerid)
{
	if (PlayerData[playerid][pEmergency] > 0 || PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID)
	    return 1;

	return 0;
}

GetNumberOwner(number)
{
	foreach (new i : Player) if (PlayerData[i][pNumberPhone] == number && PlayerInventory_AllCount(i, "Mobile Phone")) {
        if(LoggedIn[i])
		    return i;
	}
	return INVALID_PLAYER_ID;
}