#if defined _inc_impl
	#undef _inc_impl
#endif

ResetPlayerRacing(playerid){
    PlayerEnterRacing[playerid] = false;
    PlayerGetDuel[playerid] = INVALID_PLAYER_ID;
    PlayerRacingReady[playerid] = false;  
    PlayerRacingTypeInRoom[playerid] = 0;
    PlayerRacingModelCar[playerid] = 0;
    PlayerRacingTimeStart[playerid] = 10;
    PlayerRacingCar[playerid] = INVALID_VEHICLE_ID;
    format(PlayerRacing[playerid][RacingCodeRoom], 64, "NULL");
    PlayerRacingStarted[playerid] = false;
    PlayerRacingRacePoint[playerid] = 0;

    PlayerRacingGetPlayerPos[playerid][0] = 0.0;
    PlayerRacingGetPlayerPos[playerid][1] = 0.0;
    PlayerRacingGetPlayerPos[playerid][2] = 0.0;
    PlayerRacingGetInterior[playerid] = 0;
    PlayerRacingGetWorld[playerid] = 0;
    PlayerRacingStartTimeCount[playerid] = false;
    return 1;
}

Dialog:InputCodeRacingRoom(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(isnull(inputtext)) return Dialog_ShowEasy(playerid, InputCodeRacingRoom, DIALOG_STYLE_INPUT, "Code Room", "* คุณจำเป็นต้องกรอก Code Room *\nกรุณากรอก Code Room Racing ที่ต้องการจะเข้า:", "ตกลง", "ปิด");
        new bool:checked = false, duelid;
        foreach(new i : Player) if(LoggedIn[i]){
            if(!PlayerEnterRacing[i]) continue;
            if(PlayerGetDuel[i] != INVALID_PLAYER_ID) continue;
            if(!strcmp(PlayerRacing[i][RacingCodeRoom], inputtext, true)){
                checked = true;
                duelid = i;
            }
        }

        if(!checked) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ไม่พบ Code Room Racing ดังกล่าว", "ตกลง", "");
        LoadRacingPlayerTextDraw(playerid);
        PlayerGetDuel[playerid] = duelid;
        PlayerEnterRacing[playerid] = true;
        PlayerRacingTypeInRoom[playerid] = PLAYER_ROOM;
        PlayerDuelRacing_Render(playerid);
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        PlayerRacingGetPlayerPos[playerid][0] = x;
        PlayerRacingGetPlayerPos[playerid][1] = y;
        PlayerRacingGetPlayerPos[playerid][2] = z;
        PlayerRacingGetInterior[playerid] = GetPlayerInterior(playerid);
        PlayerRacingGetWorld[playerid] = GetPlayerVirtualWorld(playerid);

        PlayerGetDuel[duelid] = playerid;
        PlayerRacing_Render(duelid);
    }
    return 1;
}

PlayerCheckDuel_Disconnect(playerid){
    if(PlayerGetDuel[playerid] != INVALID_PLAYER_ID){
        if(PlayerRacingCar[playerid] != INVALID_VEHICLE_ID && PlayerRacingStarted[playerid]){
            new string[128];
            format(string, sizeof string, "[!] คู่แข่ง %s ของคุณได้หลุดหรือออกจากเกมไปแล้ว", ReturnRoleplayName(playerid));
            Dialog_ShowEasy(PlayerGetDuel[playerid], ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", string, "ตกลง", "");

            CoreVehicles[PlayerRacingCar[PlayerGetDuel[playerid]]][vehTemporary] = false;
            TRP_DestroyVehicle(PlayerRacingCar[PlayerGetDuel[playerid]]);
            ResetVehicle(PlayerRacingCar[PlayerGetDuel[playerid]]);

            CoreVehicles[PlayerRacingCar[playerid]][vehTemporary] = false;
            TRP_DestroyVehicle(PlayerRacingCar[playerid]);
            ResetVehicle(PlayerRacingCar[PlayerGetDuel[playerid]]);

            SetPlayerPosEx(PlayerGetDuel[playerid], PlayerRacingGetPlayerPos[PlayerGetDuel[playerid]][0], PlayerRacingGetPlayerPos[PlayerGetDuel[playerid]][1], PlayerRacingGetPlayerPos[PlayerGetDuel[playerid]][2], PlayerRacingGetInterior[PlayerGetDuel[playerid]], PlayerRacingGetWorld[PlayerGetDuel[playerid]]);
            SetPlayerPosEx(playerid, PlayerRacingGetPlayerPos[playerid][0], PlayerRacingGetPlayerPos[playerid][1], PlayerRacingGetPlayerPos[playerid][2], PlayerRacingGetInterior[playerid], PlayerRacingGetWorld[playerid]);
            SetCameraBehindPlayer(playerid);
            SetCameraBehindPlayer(PlayerGetDuel[playerid]);

            ResetPlayerRacing(PlayerGetDuel[playerid]);
            ResetPlayerRacing(playerid);
        }
    }
    return 1;
}

PlayerDuelRacing_Render(playerid){
    new string[128];

    PlayerEnterRacing[playerid] = true;

    PlayerTextDrawSetPreviewModel(playerid, RacingPlayerTextDraw[playerid][3], GetPlayerSkin(PlayerGetDuel[playerid]));
    format(string, sizeof string, "%s", ReturnRoleplayName(PlayerGetDuel[playerid]));
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][4], string);
    format(string, sizeof string, "Win: %s, Lose: %s", FormatNumberNotMoney(PlayerData[PlayerGetDuel[playerid]][pRacingWin]), FormatNumberNotMoney(PlayerData[PlayerGetDuel[playerid]][pRacingLose]));
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][5], string);
    if(!PlayerRacingReady[PlayerGetDuel[playerid]]) format(string, sizeof string, "NOT READY");
    else format(string, sizeof string, "READY");
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][6], string);
    format(string, sizeof string, "CodeRoom: %s", PlayerRacing[PlayerGetDuel[playerid]][RacingCodeRoom]);
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][15], string);

    PlayerTextDrawHide(playerid, RacingPlayerTextDraw[playerid][11]);
    PlayerTextDrawSetPreviewModel(playerid, RacingPlayerTextDraw[playerid][11], Model_Car[PlayerRacingModelCar[PlayerGetDuel[playerid]]]);
    PlayerTextDrawShow(playerid, RacingPlayerTextDraw[playerid][11]);

    format(string, sizeof string, "%s", Model_CarName[PlayerRacingModelCar[PlayerGetDuel[playerid]]]);
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][12], string);

    PlayerTextDrawSetPreviewModel(playerid, RacingPlayerTextDraw[playerid][7], GetPlayerSkin(playerid));
    format(string, sizeof string, "%s", ReturnRoleplayName(playerid));
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][8], string);
    format(string, sizeof string, "Win: %s, Lose: %s", FormatNumberNotMoney(PlayerData[playerid][pRacingWin]), FormatNumberNotMoney(PlayerData[playerid][pRacingLose]));
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][9], string);
    if(!PlayerRacingReady[playerid]) format(string, sizeof string, "NOT READY");
    else format(string, sizeof string, "READY");
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][10], string);

    for(new i=0; i<MAX_RACINGTEXTDRAW; i++) PlayerTextDrawShow(playerid, RacingPlayerTextDraw[playerid][i]);

    TogglePlayerControllable(playerid, 0);
    SelectTextDraw(playerid, 0x27FF00AA);
    return 1;
}

PlayerRacing_Render(playerid){
    new string[128];
        
    PlayerEnterRacing[playerid] = true;
    PlayerRacingTypeInRoom[playerid] = OWNER_ROOM;

    PlayerTextDrawSetPreviewModel(playerid, RacingPlayerTextDraw[playerid][3], GetPlayerSkin(playerid));
    format(string, sizeof string, "%s", ReturnRoleplayName(playerid));
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][4], string);
    format(string, sizeof string, "Win: %s, Lose: %s", FormatNumberNotMoney(PlayerData[playerid][pRacingWin]), FormatNumberNotMoney(PlayerData[playerid][pRacingLose]));
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][5], string);
    if(!PlayerRacingReady[playerid]) format(string, sizeof string, "NOT READY");
    else format(string, sizeof string, "READY");
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][6], string);
    format(string, sizeof string, "CodeRoom: %s", PlayerRacing[playerid][RacingCodeRoom]);
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][15], string);

    PlayerTextDrawHide(playerid, RacingPlayerTextDraw[playerid][11]);
    PlayerTextDrawSetPreviewModel(playerid, RacingPlayerTextDraw[playerid][11], Model_Car[PlayerRacingModelCar[playerid]]);
    PlayerTextDrawShow(playerid, RacingPlayerTextDraw[playerid][11]);

    format(string, sizeof string, "%s", Model_CarName[PlayerRacingModelCar[playerid]]);
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][12], string);

    if(PlayerGetDuel[playerid] == INVALID_PLAYER_ID){
        PlayerTextDrawSetPreviewModel(playerid, RacingPlayerTextDraw[playerid][7], 18631);
        format(string, sizeof string, "None");
        PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][8], string);
        format(string, sizeof string, "None");
        PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][9], string);
        format(string, sizeof string, "NOT READY");
        PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][10], string);
    }
    else{
        PlayerTextDrawSetPreviewModel(playerid, RacingPlayerTextDraw[playerid][7], GetPlayerSkin(PlayerGetDuel[playerid]));
        format(string, sizeof string, "%s", ReturnRoleplayName(PlayerGetDuel[playerid]));
        PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][8], string);
        format(string, sizeof string, "Win: %s, Lose: %s", FormatNumberNotMoney(PlayerData[PlayerGetDuel[playerid]][pRacingWin]), FormatNumberNotMoney(PlayerData[PlayerGetDuel[playerid]][pRacingLose]));
        PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][9], string);
        if(!PlayerRacingReady[PlayerGetDuel[playerid]]) format(string, sizeof string, "NOT READY");
        else format(string, sizeof string, "READY");
        PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][10], string);
    }

    for(new i=0; i<MAX_RACINGTEXTDRAW; i++) PlayerTextDrawShow(playerid, RacingPlayerTextDraw[playerid][i]);

    TogglePlayerControllable(playerid, 0);
    SelectTextDraw(playerid, 0x27FF00AA);
    return 1;
}

ptask UpdateRacingTime[1000](playerid){
    if(PlayerEnterRacing[playerid]){
        if(PlayerGetDuel[playerid] != INVALID_PLAYER_ID){
            if(PlayerRacingTypeInRoom[playerid] == OWNER_ROOM && PlayerRacingTypeInRoom[PlayerGetDuel[playerid]] == PLAYER_ROOM){
                if(PlayerRacingReady[playerid] && PlayerRacingReady[PlayerGetDuel[playerid]] && PlayerRacingTimeStart[playerid] > 0){
                    new string[128];
                    PlayerRacingTimeStart[playerid]--;
                    if(!PlayerRacingStartTimeCount[playerid]) PlayerRacingStartTimeCount[playerid] = true;
                    if(!PlayerRacingStartTimeCount[PlayerGetDuel[playerid]]) PlayerRacingStartTimeCount[PlayerGetDuel[playerid]] = true;
                    format(string, sizeof string, "~W~START IN ~Y~%d", PlayerRacingTimeStart[playerid]);
                    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][2], string);
                    PlayerTextDrawSetString(PlayerGetDuel[playerid], RacingPlayerTextDraw[playerid][2], string);

                    if(PlayerRacingTimeStart[playerid] == 5){
                        PlayerRacingCar[playerid] = CreateVehicle(Model_Car[PlayerRacingModelCar[playerid]], -1400.9020,-212.1008,1050.9313, 356.6687, 1, 1, 0);
                        CoreVehicles[PlayerRacingCar[playerid]][vehTemporary] = true;
                        SetEngineStatus(PlayerRacingCar[playerid], true);
                        SetLightStatus(PlayerRacingCar[playerid], true);
                        SetPlayerInterior(playerid, 7);
                        SetPlayerVirtualWorld(playerid, playerid+1);
                        SetVehiclePos(PlayerRacingCar[playerid], -1400.9020,-212.1008,1050.9313);
                        SetVehicleZAngle(PlayerRacingCar[playerid], 356.6687);
                        LinkVehicleToInterior(PlayerRacingCar[playerid], 7);
                        SetVehicleVirtualWorld(PlayerRacingCar[playerid], playerid+1);
                        PutPlayerInVehicle(playerid, PlayerRacingCar[playerid], 0);

                        PlayerRacingCar[PlayerGetDuel[playerid]] = CreateVehicle(Model_Car[PlayerRacingModelCar[playerid]], -1395.0625,-212.7404,1050.9224, 358.5127, 0, 0, 0);
                        CoreVehicles[PlayerRacingCar[PlayerGetDuel[playerid]]][vehTemporary] = true;
                        SetEngineStatus(PlayerRacingCar[PlayerGetDuel[playerid]], true);
                        SetLightStatus(PlayerRacingCar[PlayerGetDuel[playerid]], true);
                        SetPlayerInterior(PlayerGetDuel[playerid], 7);
                        SetPlayerVirtualWorld(PlayerGetDuel[playerid], playerid+1);
                        SetVehiclePos(PlayerRacingCar[PlayerGetDuel[playerid]], -1395.0625,-212.7404,1050.9224);
                        SetVehicleZAngle(PlayerRacingCar[PlayerGetDuel[playerid]], 358.5127);
                        LinkVehicleToInterior(PlayerRacingCar[PlayerGetDuel[playerid]], 7);
                        SetVehicleVirtualWorld(PlayerRacingCar[PlayerGetDuel[playerid]], playerid+1);
                        PutPlayerInVehicle(PlayerGetDuel[playerid], PlayerRacingCar[PlayerGetDuel[playerid]], 0);
                    }
                    else if(PlayerRacingTimeStart[playerid] > 0 && PlayerRacingTimeStart[playerid] < 5){

                        PlayerRacingStarted[playerid] = true;
                        PlayerRacingStarted[PlayerGetDuel[playerid]] = true;

                        format(string, sizeof string, "~W~START IN ~Y~%d", PlayerRacingTimeStart[playerid]);
                        GameTextForPlayer(playerid, string, 1000, 5);
                        GameTextForPlayer(PlayerGetDuel[playerid], string, 1000, 5);

                        for(new i=0; i<MAX_RACINGTEXTDRAW; i++){
                            PlayerTextDrawHide(PlayerGetDuel[playerid], RacingPlayerTextDraw[PlayerGetDuel[playerid]][i]);
                            PlayerTextDrawDestroy(PlayerGetDuel[playerid], RacingPlayerTextDraw[PlayerGetDuel[playerid]][i]);
                        }
                        CancelSelectTextDraw(PlayerGetDuel[playerid]);

                        for(new i=0; i<MAX_RACINGTEXTDRAW; i++){
                            PlayerTextDrawHide(playerid, RacingPlayerTextDraw[playerid][i]);
                            PlayerTextDrawDestroy(playerid, RacingPlayerTextDraw[playerid][i]);
                        }
                        CancelSelectTextDraw(playerid);
                    }
                    else if(PlayerRacingTimeStart[playerid] == 0){
                        format(string, sizeof string, "~Y~GO GO GO");
                        GameTextForPlayer(playerid, string, 1000, 5);
                        GameTextForPlayer(PlayerGetDuel[playerid], string, 1000, 5);
                        TogglePlayerControllable(playerid, 1);
                        TogglePlayerControllable(PlayerGetDuel[playerid], 1);
                        CancelSelectTextDraw(playerid);
                        CancelSelectTextDraw(PlayerGetDuel[playerid]);

                        PlayerRacingRacePoint[playerid] = 0;
                        SetPlayerRaceCheckpoint(playerid,0, -1310.6257,-140.9307,1050.1255, -1313.9750,-274.9555,1047.7542, 10.0);

                        PlayerRacingRacePoint[PlayerGetDuel[playerid]] = 0;
                        SetPlayerRaceCheckpoint(PlayerGetDuel[playerid],0, -1310.6257,-140.9307,1050.1255, -1313.9750,-274.9555,1047.7542, 10.0);

                        PlayerRacingTimeStart[playerid] = 0;
                    }
                }
            } 
        }
    }
}

stock RandomRacingCodeRoom(){
	const len = 7, hyphenpos = 4;
	new code[len+1];
	for (new i = 0; i < len; i++){
	    if (i < hyphenpos) code[i] = 'A' + random(26);
	    else code[i] = '0' + random(10);
	}
	return code;
}

PlayerRacing_UpdateModelCar(playerid){
    new string[128];
    PlayerRacingModelCar[playerid]++;

    if(PlayerRacingModelCar[playerid] >= MODEL_CAESIZE){
        PlayerRacingModelCar[playerid] = 0;
    }

    PlayerTextDrawHide(playerid, RacingPlayerTextDraw[playerid][11]);
    PlayerTextDrawSetPreviewModel(playerid, RacingPlayerTextDraw[playerid][11], Model_Car[PlayerRacingModelCar[playerid]]);
    PlayerTextDrawShow(playerid, RacingPlayerTextDraw[playerid][11]);

    format(string, sizeof string, "%s", Model_CarName[PlayerRacingModelCar[playerid]]);
    PlayerTextDrawSetString(playerid, RacingPlayerTextDraw[playerid][12], string);

    if(PlayerGetDuel[playerid] != INVALID_PLAYER_ID){
        PlayerTextDrawHide(PlayerGetDuel[playerid], RacingPlayerTextDraw[PlayerGetDuel[playerid]][11]);
        PlayerTextDrawSetPreviewModel(PlayerGetDuel[playerid], RacingPlayerTextDraw[PlayerGetDuel[playerid]][11], Model_Car[PlayerRacingModelCar[playerid]]);
        PlayerTextDrawShow(PlayerGetDuel[playerid], RacingPlayerTextDraw[PlayerGetDuel[playerid]][11]);

        format(string, sizeof string, "%s", Model_CarName[PlayerRacingModelCar[playerid]]);
        PlayerTextDrawSetString(PlayerGetDuel[playerid], RacingPlayerTextDraw[PlayerGetDuel[playerid]][12], string);
    }
    return 1;
}

PlayerRacing_Hide(playerid){
    if(PlayerGetDuel[playerid] != INVALID_PLAYER_ID){
        if(PlayerRacingTypeInRoom[playerid] == OWNER_ROOM){

            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ห้องแข่งขันถูกยกเลิก", "[!] คุณได้ยกเลิกห้องแข่งขันแล้ว", "ตกลง", "");
            Dialog_ShowEasy(PlayerGetDuel[playerid], ShowOnly, DIALOG_STYLE_MSGBOX, "ห้องแข่งขันถูกยกเลิก", "[!] เจ้าของห้องได้ทำการปิดห้องแข่งขันแล้ว", "ตกลง", "");

            for(new i=0; i<MAX_RACINGTEXTDRAW; i++){
                PlayerTextDrawHide(PlayerGetDuel[playerid], RacingPlayerTextDraw[PlayerGetDuel[playerid]][i]);
                PlayerTextDrawDestroy(PlayerGetDuel[playerid], RacingPlayerTextDraw[PlayerGetDuel[playerid]][i]);
            }

            PlayerEnterRacing[PlayerGetDuel[playerid]] = false;
            TogglePlayerControllable(PlayerGetDuel[playerid], 1);
            CancelSelectTextDraw(PlayerGetDuel[playerid]);
            ResetPlayerRacing(PlayerGetDuel[playerid]);

            for(new i=0; i<MAX_RACINGTEXTDRAW; i++){
                PlayerTextDrawHide(playerid, RacingPlayerTextDraw[playerid][i]);
                PlayerTextDrawDestroy(playerid, RacingPlayerTextDraw[playerid][i]);
            }

            PlayerEnterRacing[playerid] = false;
            TogglePlayerControllable(playerid, 1);
            CancelSelectTextDraw(playerid);
            ResetPlayerRacing(playerid);
        }
        else if(PlayerRacingTypeInRoom[playerid] == PLAYER_ROOM){
            PlayerGetDuel[PlayerGetDuel[playerid]] = INVALID_PLAYER_ID;
            PlayerRacing_Render(PlayerGetDuel[playerid]);

            for(new i=0; i<MAX_RACINGTEXTDRAW; i++){
                PlayerTextDrawHide(playerid, RacingPlayerTextDraw[playerid][i]);
                PlayerTextDrawDestroy(playerid, RacingPlayerTextDraw[playerid][i]);
            }

            TogglePlayerControllable(playerid, 1);
            CancelSelectTextDraw(playerid);
            PlayerEnterRacing[playerid] = false;
            PlayerGetDuel[playerid] = INVALID_PLAYER_ID;
            PlayerRacingReady[playerid] = false;   
            PlayerRacingTypeInRoom[playerid] = 0;
        }
    }
    else{
        for(new i=0; i<MAX_RACINGTEXTDRAW; i++){
            PlayerTextDrawHide(playerid, RacingPlayerTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, RacingPlayerTextDraw[playerid][i]);
        }

        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ห้องแข่งขันถูกยกเลิก", "[!] คุณได้ยกเลิกห้องแข่งขันแล้ว", "ตกลง", "");

        PlayerEnterRacing[playerid] = false;
        TogglePlayerControllable(playerid, 1);
        CancelSelectTextDraw(playerid);
        ResetPlayerRacing(playerid);
    }
    return 1;
}

CMD:checkracing(playerid, params[]){
    printf("%d | %s", PlayerEnterRacing[playerid], PlayerRacing[playerid][RacingCodeRoom]);
    return 1;
}

LoadRacingPlayerTextDraw(playerid){
    RacingPlayerTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 323.000000, 113.000000, "_");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][0], 1.183333, 33.800003);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][0], 313.500000, 545.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][0], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][0], 135);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][0], 0);

    RacingPlayerTextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 323.000000, 113.000000, "_");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][1], 1.183333, 1.800003);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][1], 313.500000, 545.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][1], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][1], 135);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][1], 0);

    RacingPlayerTextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 325.000000, 112.000000, "Racing");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][2], 0.412500, 1.800000);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][2], 410.000000, 162.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][2], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][2], 0);

    RacingPlayerTextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 86.000000, 165.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][3], 5);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][3], 99.000000, 105.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][3], 1);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][3], 1296911741);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][3], 255);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][3], 1);
    PlayerTextDrawSetPreviewModel(playerid, RacingPlayerTextDraw[playerid][3], 0);
    PlayerTextDrawSetPreviewRot(playerid, RacingPlayerTextDraw[playerid][3], 2.000000, 0.000000, 22.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, RacingPlayerTextDraw[playerid][3], 1, 1);

    RacingPlayerTextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 136.000000, 280.000000, "Alva Southern");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][4], 0.250000, 1.249999);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][4], 405.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][4], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][4], -1094795726);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][4], 0);

    RacingPlayerTextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 136.000000, 298.000000, "Win: 10, Lose: 5");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][5], 0.250000, 1.249999);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][5], 405.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][5], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][5], -1094795726);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][5], 0);

    RacingPlayerTextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 136.000000, 327.000000, "NOT READY");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][6], 0.250000, 1.249999);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][6], 405.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][6], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][6], -1094795726);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][6], 0);

    RacingPlayerTextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 462.000000, 165.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][7], 5);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][7], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][7], 99.000000, 105.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][7], 1);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][7], 1296911741);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][7], 255);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][7], 1);
    PlayerTextDrawSetPreviewModel(playerid, RacingPlayerTextDraw[playerid][7], 0);
    PlayerTextDrawSetPreviewRot(playerid, RacingPlayerTextDraw[playerid][7], 2.000000, 0.000000, -29.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, RacingPlayerTextDraw[playerid][7], 1, 1);

    RacingPlayerTextDraw[playerid][8] = CreatePlayerTextDraw(playerid, 511.000000, 280.000000, "Alva Southern");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][8], 0.250000, 1.249999);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][8], 405.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][8], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][8], -1094795726);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][8], 0);

    RacingPlayerTextDraw[playerid][9] = CreatePlayerTextDraw(playerid, 511.000000, 298.000000, "Win: 5, Lose: 10");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][9], 0.250000, 1.249999);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][9], 405.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][9], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][9], -1094795726);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][9], 0);

    RacingPlayerTextDraw[playerid][10] = CreatePlayerTextDraw(playerid, 511.000000, 327.000000, "NOT READY");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][10], 0.250000, 1.249999);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][10], 405.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][10], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][10], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][10], -1094795726);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][10], 0);

    RacingPlayerTextDraw[playerid][11] = CreatePlayerTextDraw(playerid, 275.000000, 165.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][11], 5);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][11], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][11], 99.000000, 105.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][11], 1);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][11], 1296911741);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][11], 255);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][11], 0);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][11], 1);
    PlayerTextDrawSetPreviewModel(playerid, RacingPlayerTextDraw[playerid][11], 411);
    PlayerTextDrawSetPreviewRot(playerid, RacingPlayerTextDraw[playerid][11], -9.000000, 0.000000, -29.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, RacingPlayerTextDraw[playerid][11], 1, 1);

    RacingPlayerTextDraw[playerid][12] = CreatePlayerTextDraw(playerid, 324.000000, 275.000000, "Infernus");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][12], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][12], 0.250000, 1.249999);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][12], 405.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][12], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][12], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][12], -1094795726);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][12], 0);

    RacingPlayerTextDraw[playerid][13] = CreatePlayerTextDraw(playerid, 320.000000, 356.000000, "Ready");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][13], 0.304166, 1.750000);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][13], 16.500000, 90.500000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][13], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][13], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][13], 9109704);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][13], 1);

    RacingPlayerTextDraw[playerid][14] = CreatePlayerTextDraw(playerid, 320.000000, 384.000000, "Exit Room");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][14], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][14], 0.304166, 1.750000);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][14], 16.500000, 90.500000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][14], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][14], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][14], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][14], -1962934072);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][14], 1);

    RacingPlayerTextDraw[playerid][15] = CreatePlayerTextDraw(playerid, 324.000000, 141.000000, "Room Code: 53421");
    PlayerTextDrawFont(playerid, RacingPlayerTextDraw[playerid][15], 1);
    PlayerTextDrawLetterSize(playerid, RacingPlayerTextDraw[playerid][15], 0.250000, 1.249999);
    PlayerTextDrawTextSize(playerid, RacingPlayerTextDraw[playerid][15], 405.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, RacingPlayerTextDraw[playerid][15], 1);
    PlayerTextDrawSetShadow(playerid, RacingPlayerTextDraw[playerid][15], 0);
    PlayerTextDrawAlignment(playerid, RacingPlayerTextDraw[playerid][15], 2);
    PlayerTextDrawColor(playerid, RacingPlayerTextDraw[playerid][15], -1);
    PlayerTextDrawBackgroundColor(playerid, RacingPlayerTextDraw[playerid][15], 255);
    PlayerTextDrawBoxColor(playerid, RacingPlayerTextDraw[playerid][15], -1094795726);
    PlayerTextDrawUseBox(playerid, RacingPlayerTextDraw[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, RacingPlayerTextDraw[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, RacingPlayerTextDraw[playerid][15], 0);

    return 1;
}