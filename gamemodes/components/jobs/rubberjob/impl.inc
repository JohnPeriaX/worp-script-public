#if defined _inc_impl
	#undef _inc_impl
#endif

ResetRubberJob(playerid){
    PlayerGetToolRubber[playerid] = 0;
    RubberPoint[playerid] = 0;
    RubberStarting[playerid] = 0;
    KillTimer(RubberTime[playerid]);
    RubberTime[playerid] = 0;
    RubberProcessPoint[playerid] = 0;
    RemoveAttachedObject(playerid, 8);
	RemoveAttachedObject(playerid, 7);
    KillTimer(RubberProcessTime[playerid]);
    RubberProcessTime[playerid] = 0;
    return 1;
}

LoadTextDrawBarRubber(playerid){
    RubberTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 391.000000, 233.000000, "Water Rubber 100%");
    PlayerTextDrawFont(playerid, RubberTextDraw[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, RubberTextDraw[playerid][0], 0.200000, 1.000000);
    PlayerTextDrawTextSize(playerid, RubberTextDraw[playerid][0], 466.000000, 21.000000);
    PlayerTextDrawSetOutline(playerid, RubberTextDraw[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, RubberTextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, RubberTextDraw[playerid][0], 1);
    PlayerTextDrawColor(playerid, RubberTextDraw[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, RubberTextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, RubberTextDraw[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, RubberTextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, RubberTextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, RubberTextDraw[playerid][0], 0);

    RubberProgressBar[playerid][0] = CreatePlayerProgressBar(playerid, 390.000000, 351.000000, 7.500000, 129.500000, 0xFFBE3DAA, 100.000000, 2);
    return 1;
}

forward Rubber_Load();
public Rubber_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_RUBBERTREE)
	{
	    RubberData[i][rubberEx] = true;

	    cache_get_value_name_int(i, "rubberID", RubberData[i][rubberID]);
	    cache_get_value_name_float(i, "rubberPosX", RubberData[i][rubberPos][0]);
	    cache_get_value_name_float(i, "rubberPosY", RubberData[i][rubberPos][1]);
	    cache_get_value_name_float(i, "rubberPosZ", RubberData[i][rubberPos][2]);
	    cache_get_value_name_int(i, "rubberInt", RubberData[i][rubberInt]);
	    cache_get_value_name_int(i, "rubberWorld", RubberData[i][rubberWorld]);
        cache_get_value_name_int(i, "rubberHealth", RubberData[i][rubberHealth]);

        RubberData[i][rubberObject] = CreateDynamicObject(777, RubberData[i][rubberPos][0], RubberData[i][rubberPos][1], RubberData[i][rubberPos][2], 0.0, 0.0, 0.0);
        Count_Rubber++;

        Rubber_RenderRefresh(i);
 	    Rubber_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d Rubbers Successfully ))", Count_Rubber);
	return 1;
}

Rubber_RenderRefresh(rubberid){
    if (rubberid != -1 && RubberData[rubberid][rubberEx]){
        if (IsValidDynamic3DTextLabel(RubberData[rubberid][rubberText3D]))
            DestroyDynamic3DTextLabel(RubberData[rubberid][rubberText3D]);

        new string[64];

        format(string, sizeof(string), "[ต้นยาง]\n>> %s <<", FormatNumberNotMoney(RubberData[rubberid][rubberHealth]));
        RubberData[rubberid][rubberText3D] = CreateDynamic3DTextLabel(string, 0xFFBE3DFF, RubberData[rubberid][rubberPos][0], RubberData[rubberid][rubberPos][1], RubberData[rubberid][rubberPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, RubberData[rubberid][rubberWorld], RubberData[rubberid][rubberInt]);
    }
    return 1;
}

Rubber_Refresh(rubberid){
    if (rubberid != -1 && RubberData[rubberid][rubberEx]){
        new string[64];

        format(string, sizeof(string), "[ต้นยาง]\n>> %s <<", FormatNumberNotMoney(RubberData[rubberid][rubberHealth]));
        UpdateDynamic3DTextLabelText(RubberData[rubberid][rubberText3D], 0xFFBE3DFF, string);
    }
    return 1;
}

Rubber_Nearest(playerid)
{
    for (new i = 0; i != MAX_RUBBERTREE; i ++) if (RubberData[i][rubberEx] && IsPlayerInRangeOfPoint(playerid, 2.0, RubberData[i][rubberPos][0], RubberData[i][rubberPos][1], RubberData[i][rubberPos][2]))
	{
		if (GetPlayerInterior(playerid) == RubberData[i][rubberInt] && GetPlayerVirtualWorld(playerid) == RubberData[i][rubberWorld])
			return i;
	}
	return -1;
}

forward StartProcessRubber(playerid);
public StartProcessRubber(playerid){
    new string[128];
    if(RubberProcessPoint[playerid] < 100){
        TogglePlayerControllable(playerid, 0);
        ClearAnimations(playerid);
        ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
        RubberProcessPoint[playerid] += 1;
        SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], RubberProcessPoint[playerid]);
        format(string,sizeof(string),"~n~~n~~n~~n~~n~~n~~n~~n~~y~Processing: %d/100", RubberProcessPoint[playerid]);
        GameTextForPlayer(playerid, string, 1200, 3);
        RubberPoint[playerid] -= 1;
        format(string, sizeof(string), "Water Rubber: %d", RubberPoint[playerid]);
        PlayerTextDrawSetString(playerid, RubberTextDraw[playerid][0], string);
        SetPlayerProgressBarValue(playerid, RubberProgressBar[playerid][0], RubberPoint[playerid]);

        RubberProcessTime[playerid] = SetTimerEx("StartProcessRubber", 1000, false, "i", playerid);
    }
    else if(RubberProcessPoint[playerid] >= 100 && RubberPoint[playerid] <= 0){
        KillTimer(RubberProcessTime[playerid]);
        ResetRubberJob(playerid);
        TogglePlayerControllable(playerid, 1);
        ClearAnimations(playerid);

        HidePlayerProgressBar(playerid, ProgressbarJob[playerid]);

        PlayerTextDrawHide(playerid, RubberTextDraw[playerid][0]);
        PlayerTextDrawDestroy(playerid, RubberTextDraw[playerid][0]);
        HidePlayerProgressBar(playerid, RubberProgressBar[playerid][0]);
        DestroyPlayerProgressBar(playerid, RubberProgressBar[playerid][0]);
        PlayerData[playerid][pStress]++;
        if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
        new id = PlayerInventory_AddItem(playerid, "Raw Rubber Sheet", 2468, 10);
        if (id == -1){
            return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
        }
        SendClientMessage(playerid, 0xFFBE3DFF, "- คุณได้รับ 'ยางแผ่น' + 10");
    }
    return 1;
}

forward StartingRubber(playerid, rubberid);
public StartingRubber(playerid, rubberid){
    new string[128];
    RubberPoint[playerid] += 5;

    if(RubberPoint[playerid] >= 100){
        SendClientMessage(playerid, 0xFFBE3DFF, "- น้ำยางของคุณเต็มแล้ว ไปยัง 'เครื่องแปรรูป' เพื่อทำการแปรรูปเป็น ยางแผ่น");
    }

    RubberData[rubberid][rubberHealth] -= 5;
    Rubber_Refresh(rubberid);

    format(string, sizeof(string), "Water Rubber: %d", RubberPoint[playerid]);
    PlayerTextDrawSetString(playerid, RubberTextDraw[playerid][0], string);
    SetPlayerProgressBarValue(playerid, RubberProgressBar[playerid][0], RubberPoint[playerid]);
    Streamer_Update(playerid);
    ClearAnimations(playerid);
    RubberStarting[playerid] = 0;
    return 1;
}

SetPlayerToolRubber(playerid){
    if(PlayerGetToolRubber[playerid] == 0){
        PlayerGetToolRubber[playerid] = 1;
        LoadTextDrawBarRubber(playerid);
        PlayerTextDrawShow(playerid, RubberTextDraw[playerid][0]);
        ShowPlayerProgressBar(playerid, RubberProgressBar[playerid][0]);

        new string[128];

        format(string, sizeof(string), "Water Rubber: %d", RubberPoint[playerid]);
        PlayerTextDrawSetString(playerid, RubberTextDraw[playerid][0], string);
        SetPlayerProgressBarValue(playerid, RubberProgressBar[playerid][0], RubberPoint[playerid]);

        SendClientMessage(playerid, 0xFFBE3DFF, "- คุณได้รับ 'มีดกรีดยาง' เรียบร้อยแล้ว");
        SetPlayerAttachedObject(playerid,8,18633,6,0.071999,0.007999,0.089999,98.799980,0.000000,0.000000,0.713000,0.706999,1.386000);
        SetPlayerAttachedObject(playerid,7,19812,1,0.097000,-0.248999,0.000000,0.000000,86.799957,0.000000,0.553999,0.564999,0.620999);
    }
    else if(PlayerGetToolRubber[playerid] == 1){
        PlayerGetToolRubber[playerid] = 0;
        SendClientMessage(playerid, 0xFFBE3DFF, "- คุณได้เก็บ 'มีดกรีดยาง' เรียบร้อยแล้ว");
        RemoveAttachedObject(playerid, 8);
        RemoveAttachedObject(playerid, 7);
        PlayerTextDrawHide(playerid, RubberTextDraw[playerid][0]);
        PlayerTextDrawDestroy(playerid, RubberTextDraw[playerid][0]);
        HidePlayerProgressBar(playerid, RubberProgressBar[playerid][0]);
        DestroyPlayerProgressBar(playerid, RubberProgressBar[playerid][0]);
    }
    return 1;
}

ShowDialogSellRubber(playerid){
    new string[128];
    new count = PlayerInventory_AllCount(playerid, "Raw Rubber Sheet");
    format(string, sizeof(string), "คุณมียางแผ่นอยู่: %d\nกรอกจำนวนที่ต้องการจะขาย", count);
    Dialog_ShowEasy(playerid, Dialog_SellRubber, DIALOG_STYLE_INPUT, "ขายยางแผ่น", string, "ขาย", "ยกเลิก");
    return 1;
}

Dialog:Dialog_SellRubber(playerid, response, listitem, inputtext[]){
    if(!response){
        GetJobID[playerid] = -1;
        return 1;
    }

    if(response){
        new amount = strval(inputtext);

        if(amount > PlayerInventory_AllCount(playerid, "Raw Rubber Sheet"))
            return ErrorMsg(playerid, "คุณมียางแผ่นไม่พอกับจำนวนที่คุณจะขาย");

        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนที่จะขายให้มากกว่า 0");

        new price = amount * JobData[GetJobID[playerid]][jobDeliverPrice];
        GiveMoney(playerid, price, "sell raw rubber sheet");
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Raw Rubber Sheet (ยางแผ่น)' จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
        PlayerInventory_Remove(playerid, "Raw Rubber Sheet", amount);
    }
    return 1;
}