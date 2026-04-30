#if defined _inc_impl
	#undef _inc_impl
#endif

ResetOrangeJob(playerid){
    PlayerIsCarryCrate[playerid] = false;
    Player_GetID_Orange[playerid] = -1;
    KillTimer(Player_Orange_Time[playerid]);
    Player_Orange_Point[playerid] = 0;
    Player_Orange_InCrate[playerid] = false;
    Player_Orange_StartChecking[playerid] = false;
    return 1;
}

Start_Pickup_Orange(playerid){
    if(PlayerIsCarryCrate[playerid] && Player_GetID_Orange[playerid] != -1){
        new orange_id = Player_GetID_Orange[playerid];
        OrangeData[orange_id][orangePlayerUse] = true;
        LoadPlayerNewProgress(playerid);
        ShowPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
        PlayerTextDrawShow(playerid, NewProgressText[playerid][0]);
        ClearAnimations(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
        TogglePlayerControllable(playerid, 0);
        Player_Orange_Point[playerid] = 0;
        Player_Orange_InCrate[playerid] = false;
        Player_Orange_Time[playerid] = SetTimerEx("PickingUp_Orange", 1000, false, "i", playerid);
    }
    return 1;
}

Start_Check_Orange(playerid){
    LoadPlayerNewProgress(playerid);
    ShowPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    PlayerTextDrawShow(playerid, NewProgressText[playerid][0]);
    TogglePlayerControllable(playerid, 0);
    Player_Orange_Point[playerid] = 0;
    Player_Orange_StartChecking[playerid] = true;
    Player_Orange_Time[playerid] = SetTimerEx("Checking_Orange", 1000, false, "i", playerid);
    return 1;
}

forward Checking_Orange(playerid);
public Checking_Orange(playerid){
    new string[128];
    if(PlayerIsCarryCrate[playerid] && Player_Orange_InCrate[playerid]){
        if(Player_Orange_Point[playerid] < 100){
            Player_Orange_Point[playerid]++;
            format(string, sizeof(string), "Checking Orange %d/100", Player_Orange_Point[playerid]);
            PlayerTextDrawSetString(playerid, NewProgressText[playerid][0], string);
            SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], Player_Orange_Point[playerid]);
            Player_Orange_Time[playerid] = SetTimerEx("Checking_Orange", 200, false, "i", playerid);
        }
        else{
            KillTimer(Player_Orange_Time[playerid]);
            Player_Orange_Point[playerid] = 0;
            Player_Orange_InCrate[playerid] = 0;
            Player_Orange_StartChecking[playerid] = false;
            TogglePlayerControllable(playerid, 1);
            ClearAnimations(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            HidePlayerProgressBar(playerid, NewProgressBar[playerid][0]);
            PlayerTextDrawHide(playerid, NewProgressText[playerid][0]);

            DestroyPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
            PlayerTextDrawDestroy(playerid, NewProgressText[playerid][0]);
            PlayerData[playerid][pStress]++;
            if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
            SendClientMessage(playerid, COLOR_ORANGE, "- คุณได้รับ 'Orange (ส้ม)' + 5");
            new itemid = PlayerInventory_AddItem(playerid, "Orange", 19574, 5);
            if(itemid == -1) return ErrorMsg(playerid, "กระเป๋าของคุณเต็มไม่สามารถเก็บไอเท็มได้อีก");

            SetPlayerAttachedObject(playerid,CARRY_ORANGE_SLOT,19639,6,0.105999,0.012000,-0.180999,-110.799987,-9.199998,-5.499994,1.000000,1.000000,1.000000);
            ClearAnimations(playerid);
            PlayerIsCarryCrate[playerid] = true;
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
        }
    }
    return 1;
}

forward PickingUp_Orange(playerid);
public PickingUp_Orange(playerid){
    new string[128];
    if(PlayerIsCarryCrate[playerid] && Player_GetID_Orange[playerid] != -1 && !Player_Orange_InCrate[playerid]){
        if(Player_Orange_Point[playerid] < 100){
            Player_Orange_Point[playerid]++;
            format(string, sizeof(string), "Pickup Orange %d/100", Player_Orange_Point[playerid]);
            PlayerTextDrawSetString(playerid, NewProgressText[playerid][0], string);
            SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], Player_Orange_Point[playerid]);
            ApplyAnimation(playerid, "CARRY", "liftup105", 4.1, 0, 0, 0, 0, 0, 1);
            Player_Orange_Time[playerid] = SetTimerEx("PickingUp_Orange", 200, false, "i", playerid);
        }
        else{
            KillTimer(Player_Orange_Time[playerid]);
            Player_Orange_Point[playerid] = 0;

            OrangeData[Player_GetID_Orange[playerid]][orangePlayerUse] = false;
            OrangeData[Player_GetID_Orange[playerid]][orangeHealth] -= 5;
            Refresh_Orange(Player_GetID_Orange[playerid]);

            Player_GetID_Orange[playerid] = -1;

            TogglePlayerControllable(playerid, 1);
            ClearAnimations(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            HidePlayerProgressBar(playerid, NewProgressBar[playerid][0]);
            PlayerTextDrawHide(playerid, NewProgressText[playerid][0]);

            DestroyPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
            PlayerTextDrawDestroy(playerid, NewProgressText[playerid][0]);

            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
            SetPlayerAttachedObject(playerid,CARRY_ORANGE_SLOT,19638,6,0.105999,0.012000,-0.180999,-110.799987,-9.199998,-5.499994,1.000000,1.000000,1.000000);
            Player_Orange_InCrate[playerid] = true;
        }
    }
    return 1;
}

ShowDialogSellOrange(playerid){
    new string[128];
    new count = PlayerInventory_AllCount(playerid, "Orange");
    format(string, sizeof(string), "คุณมีส้มอยู่: %d\nกรอกจำนวนที่ต้องการจะขาย", count);
    Dialog_ShowEasy(playerid, Dialog_SellOrange, DIALOG_STYLE_INPUT, "ขายส้ม", string, "ขาย", "ยกเลิก");
    return 1;
}

Dialog:Dialog_SellOrange(playerid, response, listitem, inputtext[]){
    if(!response){
        GetJobID[playerid] = -1;
        return 1;
    }

    if(response){
        new amount = strval(inputtext);

        if(amount > PlayerInventory_AllCount(playerid, "Orange"))
            return ErrorMsg(playerid, "คุณมีส้มไม่พอกับจำนวนที่ใส่");

        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนที่จะขายให้มากกว่า 0");

        new price = amount * JobData[GetJobID[playerid]][jobDeliverPrice];
        GiveMoney(playerid, price, "sell orange");
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Orange (ส้ม)' จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
        PlayerInventory_Remove(playerid, "Orange", amount);
    }
    return 1;
}

Orange_Nearest(playerid, Float:radius = 2.5)
{
    for (new i = 0; i != MAX_ORANGE; i ++) if (OrangeData[i][orangeEx] && IsPlayerInRangeOfPoint(playerid, radius, OrangeData[i][orangePos][0], OrangeData[i][orangePos][1], OrangeData[i][orangePos][2])) {
		return i;
	}
	return -1;
}

Refresh_RenderOrange(orangeid){
    if(orangeid != -1 && OrangeData[orangeid][orangeEx]){
        if(IsValidDynamic3DTextLabel(OrangeData[orangeid][orangeText3D]))
            DestroyDynamic3DTextLabel(OrangeData[orangeid][orangeText3D]);

        new string[80];
        format(string, sizeof(string), "[ ต้นส้ม ]\n[ ผลผลิต: %d ลูก]\nกด 'ต่อย' เพื่อเก็บ", OrangeData[orangeid][orangeHealth]);
        OrangeData[orangeid][orangeText3D] = CreateDynamic3DTextLabel(string, 0xFF6203FF, OrangeData[orangeid][orangePos][0], OrangeData[orangeid][orangePos][1], OrangeData[orangeid][orangePos][2]+1.2, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
    }
    return 1;
}

Refresh_Orange(orangeid){
    if(orangeid != -1 && OrangeData[orangeid][orangeEx]){
        new string[80];
        format(string, sizeof(string), "[ ต้นส้ม ]\n[ ผลผลิต: %d ลูก]\nกด 'ต่อย' เพื่อเก็บ", OrangeData[orangeid][orangeHealth]);
        UpdateDynamic3DTextLabelText(OrangeData[orangeid][orangeText3D], 0xFF6203FF, string);
    }
    return 1;
}

Create_Orange(){
    OrangeData[0][orangeEx] = true;
    OrangeData[0][orangePos][0] = 293.934509;
    OrangeData[0][orangePos][1] = -734.683532;
    OrangeData[0][orangePos][2] = 3.731542;

    OrangeData[1][orangeEx] = true;
    OrangeData[1][orangePos][0] = 306.994506;
    OrangeData[1][orangePos][1] = -734.683532;
    OrangeData[1][orangePos][2] = 4.871539;

    OrangeData[2][orangeEx] = true;
    OrangeData[2][orangePos][0] = 306.094573;
    OrangeData[2][orangePos][1] = -746.913757;
    OrangeData[2][orangePos][2] = 4.671536;

    OrangeData[3][orangeEx] = true;
    OrangeData[3][orangePos][0] = 295.804656;
    OrangeData[3][orangePos][1] = -746.913757;
    OrangeData[3][orangePos][2] = 3.991529;

    OrangeData[4][orangeEx] = true;
    OrangeData[4][orangePos][0] = 286.464874;
    OrangeData[4][orangePos][1] = -746.283508;
    OrangeData[4][orangePos][2] = 3.591529;

    OrangeData[5][orangeEx] = true;
    OrangeData[5][orangePos][0] = 281.974884;
    OrangeData[5][orangePos][1] = -735.393554;
    OrangeData[5][orangePos][2] = 3.471529;

    OrangeData[6][orangeEx] = true;
    OrangeData[6][orangePos][0] = 289.271911;
    OrangeData[6][orangePos][1] = -722.956176;
    OrangeData[6][orangePos][2] = 3.921528;

    OrangeData[7][orangeEx] = true;
    OrangeData[7][orangePos][0] = 303.678375;
    OrangeData[7][orangePos][1] = -715.587158;
    OrangeData[7][orangePos][2] = 4.491522;

    OrangeData[8][orangeEx] = true;
    OrangeData[8][orangePos][0] = 314.680328;
    OrangeData[8][orangePos][1] = -715.364929;
    OrangeData[8][orangePos][2] = 5.331522;

    OrangeData[9][orangeEx] = true;
    OrangeData[9][orangePos][0] = 324.186859;
    OrangeData[9][orangePos][1] = -727.338439;
    OrangeData[9][orangePos][2] = 6.431519;

    OrangeData[10][orangeEx] = true;
    OrangeData[10][orangePos][0] = 319.236083;
    OrangeData[10][orangePos][1] = -739.779541;
    OrangeData[10][orangePos][2] = 5.821516;

    OrangeData[11][orangeEx] = true;
    OrangeData[11][orangePos][0] = 318.764404;
    OrangeData[11][orangePos][1] = -749.267211;
    OrangeData[11][orangePos][2] = 5.481513;

    OrangeData[12][orangeEx] = true;
    OrangeData[12][orangePos][0] = 309.534637;
    OrangeData[12][orangePos][1] = -724.617553;
    OrangeData[12][orangePos][2] = 5.011512;

    OrangeData[13][orangeEx] = true;
    OrangeData[13][orangePos][0] = 314.420379;
    OrangeData[13][orangePos][1] = -734.840820;
    OrangeData[13][orangePos][2] = 5.541512;

    OrangeData[14][orangeEx] = true;
    OrangeData[14][orangePos][0] = 298.619110;
    OrangeData[14][orangePos][1] = -721.840026;
    OrangeData[14][orangePos][2] = 4.421505;

    for(new i=0; i<MAX_ORANGE; i++) if(OrangeData[i][orangeEx]){
        OrangeData[i][orangeHealth] = 50;
        Refresh_RenderOrange(i);
        Refresh_Orange(i);
    }
    return 1;
}

LoadMapOrangeJob(){
    tmpobjid = CreateDynamicObject(655, 293.934509, -734.683532, 3.731542, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 306.994506, -734.683532, 4.871539, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 306.094573, -746.913757, 4.671536, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 295.804656, -746.913757, 3.991529, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 286.464874, -746.283508, 3.591529, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 281.974884, -735.393554, 3.471529, 0.000000, 0.000000, -30.399999, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 289.271911, -722.956176, 3.921528, 0.000000, 0.000000, -44.800003, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 303.678375, -715.587158, 4.491522, 0.000000, 0.000000, -44.800003, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 314.680328, -715.364929, 5.331522, 0.000000, 0.000000, -111.699996, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 324.186859, -727.338439, 6.431519, 0.000000, 0.000000, -111.699996, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 319.236083, -739.779541, 5.821516, 0.000000, 0.000000, -111.699996, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 318.764404, -749.267211, 5.481513, 0.000000, 0.000000, -111.699996, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 309.534637, -724.617553, 5.011512, 0.000000, 0.000000, 164.300018, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 314.420379, -734.840820, 5.541512, 0.000000, 0.000000, 164.300018, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(655, 298.619110, -721.840026, 4.421505, 0.000000, 0.000000, 91.400024, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(834, 335.673400, -721.901611, 9.794764, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(834, 333.973449, -740.311645, 9.484763, 0.000000, 0.000000, 73.499992, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 326.754364, -710.482421, 6.191780, 0.000000, 0.000000, -14.500000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 319.086730, -708.500427, 5.591767, 0.000000, 0.000000, -14.500000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 311.536010, -706.548522, 4.831756, 0.000000, 0.000000, -14.500000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 303.936370, -704.584106, 4.341745, 0.000000, 0.000000, -14.500000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 296.336791, -702.619506, 4.001738, 0.000000, 0.000000, -14.500000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 288.717651, -700.649902, 3.591738, 0.000000, 0.000000, -14.500000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 283.895019, -703.482910, 3.441739, 0.000000, 0.000000, 75.500000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 281.929840, -711.083007, 3.281739, 0.000000, 0.000000, 75.500000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 279.976776, -718.634399, 3.261739, 0.000000, 0.000000, 75.500000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 278.021362, -726.195434, 3.261739, 0.000000, 0.000000, 75.500000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 276.075897, -733.717651, 3.081739, 0.000000, 0.000000, 75.500000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 275.363616, -741.408752, 2.991739, 0.000000, 0.000000, 94.099967, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 278.481689, -748.002685, 2.941739, 0.000000, 0.000000, 136.300003, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 284.135223, -753.405639, 2.941739, 0.000000, 0.000000, 136.300003, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 290.921020, -756.266418, 2.941739, 0.000000, 0.000000, 178.100265, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 298.745788, -756.525817, 3.641739, 0.000000, 0.000000, 178.100265, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 306.580444, -756.784729, 4.011736, 0.000000, 0.000000, 178.100265, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 314.395568, -757.043701, 4.711737, 0.000000, 0.000000, 178.100265, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 322.240844, -757.304138, 5.411729, 0.000000, 0.000000, 178.100265, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 326.388763, -753.489379, 6.271730, 0.000000, 0.000000, 268.100280, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 326.647308, -745.694335, 6.271730, 0.000000, 0.000000, 268.100280, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 326.910064, -737.769165, 6.271730, 0.000000, 0.000000, 268.100280, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 329.917480, -715.353881, 6.271730, 0.000000, 0.000000, -98.899726, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19641, 328.755432, -723.027587, 6.271730, 0.000000, 0.000000, -98.699676, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3463, 333.683258, -730.665527, 6.622334, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3861, 330.032501, -739.215576, 8.089617, 0.000000, 4.099999, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19638, 329.020477, -738.543945, 7.626621, 0.000000, -4.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19638, 329.709045, -738.543945, 7.674757, 0.000000, -4.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19638, 330.387542, -738.543945, 7.722193, 0.000000, -4.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19638, 331.095886, -738.543945, 7.771720, 0.000000, -4.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 289.367401, -724.011535, 3.903005, 0.000000, 0.000000, -21.299997, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 289.962982, -722.483459, 3.923005, 0.000000, 0.000000, -21.299997, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 288.314086, -721.839782, 3.853005, 0.000000, 0.000000, -21.299997, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 292.133666, -734.902160, 4.010896, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 310.997222, -736.697875, 5.235048, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 317.696502, -744.845214, 5.677084, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 300.777587, -747.749389, 4.246239, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 288.888336, -742.673706, 3.759545, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 280.315246, -732.923706, 3.437013, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 300.515167, -718.329833, 4.456176, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 309.618774, -714.935180, 5.103561, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 318.593658, -715.789184, 5.966910, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19574, 312.190704, -728.295288, 5.406982, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    return 1;
}