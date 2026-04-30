#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
    TreasureData[0][treasurePos][0] = -1291.2335;
    TreasureData[0][treasurePos][1] = 2513.1626;
    TreasureData[0][treasurePos][2] = 87.0404;
    TreasureData[0][treasureStill] = 1;

    TreasureData[1][treasurePos][0] = -1291.4222;
    TreasureData[1][treasurePos][1] = 2533.6655;
    TreasureData[1][treasurePos][2] = 87.7422;
    TreasureData[1][treasureStill] = 1;

    TreasureData[2][treasurePos][0] = -1304.1874;
    TreasureData[2][treasurePos][1] = 2525.9678;
    TreasureData[2][treasurePos][2] = 87.5304;
    TreasureData[2][treasureStill] = 1;

    TreasureData[3][treasurePos][0] = -1311.2144;
    TreasureData[3][treasurePos][1] = 2549.2620;
    TreasureData[3][treasurePos][2] = 87.7111;
    TreasureData[3][treasureStill] = 1;

    TreasureData[4][treasurePos][0] = -1324.6700;
    TreasureData[4][treasurePos][1] = 2532.8252;
    TreasureData[4][treasurePos][2] = 87.5737;
    TreasureData[4][treasureStill] = 1;

    TreasureData[5][treasurePos][0] = -1315.8301;
    TreasureData[5][treasurePos][1] = 2524.3201;
    TreasureData[5][treasurePos][2] = 87.4656;
    TreasureData[5][treasureStill] = 1;

    TreasureData[6][treasurePos][0] = -1313.8695;
    TreasureData[6][treasurePos][1] = 2504.1580;
    TreasureData[6][treasurePos][2] = 87.0420;
    TreasureData[6][treasureStill] = 1;

    TreasureData[7][treasurePos][0] = -1326.4902;
    TreasureData[7][treasurePos][1] = 2506.6826;
    TreasureData[7][treasurePos][2] = 87.0469;
    TreasureData[7][treasureStill] = 1;

    TreasureData[8][treasurePos][0] = -1333.8534;
    TreasureData[8][treasurePos][1] = 2525.5710;
    TreasureData[8][treasurePos][2] = 87.0469;
    TreasureData[8][treasureStill] = 1;

    TreasureData[9][treasurePos][0] = -1307.4043;
    TreasureData[9][treasurePos][1] = 2553.6177;
    TreasureData[9][treasurePos][2] = 87.4169;
    TreasureData[9][treasureStill] = 1;

    for(new i=0; i<10; i++){
        Treasure_Refresh(i);
    }
    return 1;
}

Treasure_Refresh(treasureid){
    if(treasureid != -1){
        if(IsValidDynamicPickup(TreasureData[treasureid][treasurePickup]))
            DestroyDynamicPickup(TreasureData[treasureid][treasurePickup]);

        if(TreasureData[treasureid][treasureStill]){
            TreasureData[treasureid][treasurePickup] = CreateDynamicPickup(1276, 23, TreasureData[treasureid][treasurePos][0], TreasureData[treasureid][treasurePos][1], TreasureData[treasureid][treasurePos][2], 0, 0);
        }
    }
    return 1;
}

ResetSeekerJob(playerid){
    GetToolAndClothSeeker[playerid] = 0;
    RemoveAttachedObject(playerid, 9);
    RemoveAttachedObject(playerid, 8);

    if(OxygenSeeker[playerid] == 1){
        PlayerTextDrawHide(playerid, TreasureTextDraw[playerid][0]);
        PlayerTextDrawDestroy(playerid, TreasureTextDraw[playerid][0]);
        HidePlayerProgressBar(playerid, TreasureProgress[playerid][0]);
        DestroyPlayerProgressBar(playerid, TreasureProgress[playerid][0]);
    }
    
    OxygenSeeker[playerid] = 0;
    StartingWashTreasure[playerid] = 0;
    ProcessWashPoint[playerid] = 0;
    KillTimer(TimeOxygen[playerid]);
    TimeOxygen[playerid] = 0;
    KillTimer(CleanTreasureTime[playerid]);
    CleanTreasureTime[playerid] = 0;
    return 1;
}

Seeker_Near(playerid, Float:radius = 2.0){
    for (new i = 0; i != MAX_TREASURE; i ++) {
        if(!TreasureData[i][treasureStill]) continue;
        if (IsPlayerInRangeOfPoint(playerid, radius, TreasureData[i][treasurePos][0], TreasureData[i][treasurePos][1], TreasureData[i][treasurePos][2]))
		    return i;
    }
	return -1;
}

LoadTextDrawTreasure(playerid){
    TreasureTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 343.000000, 314.000000, "Oxygen 100%");
    PlayerTextDrawFont(playerid, TreasureTextDraw[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, TreasureTextDraw[playerid][0], 0.195833, 1.000000);
    PlayerTextDrawTextSize(playerid, TreasureTextDraw[playerid][0], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, TreasureTextDraw[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, TreasureTextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, TreasureTextDraw[playerid][0], 3);
    PlayerTextDrawColor(playerid, TreasureTextDraw[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, TreasureTextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, TreasureTextDraw[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, TreasureTextDraw[playerid][0], 0);
    PlayerTextDrawSetProportional(playerid, TreasureTextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, TreasureTextDraw[playerid][0], 0);
    return 1;
}

OnPlayerStartJobSeeker(playerid){
    if(GetToolAndClothSeeker[playerid] == 0){
        new string[64];
        LoadTextDrawTreasure(playerid);
        SendClientMessage(playerid, COLOR_YELLOW, "คุณได้รับอุปกรณ์กันรังสีเรียบร้อยแล้ว");
        GetToolAndClothSeeker[playerid] = 1;
        SetPlayerAttachedObject(playerid,9,19472,2,-0.000000,0.132999,0.001999,2.799999,84.099998,93.400016,1.000000,1.090000,1.037000);
        SetPlayerAttachedObject(playerid,8,1008,1,0.189000,-0.025999,-0.040000,-82.500000,-174.599945,-32.100017,1.000000,1.000000,1.000000);
        TreasureProgress[playerid][0] = CreatePlayerProgressBar(playerid, 345.000000, 314.000000, 8.000000, 94.000000, -2016478465, 100.000000, 2);
        PlayerTextDrawShow(playerid, TreasureTextDraw[playerid][0]);
        ShowPlayerProgressBar(playerid, TreasureProgress[playerid][0]);
        OxygenSeeker[playerid] = 100;
        ClearAnimations(playerid);
        ApplyAnimation(playerid, "goggles", "goggles_put_on", 4.0, 0, 0, 0, 0, 0);

        format(string, sizeof(string), "Oxygen %d", OxygenSeeker[playerid]);
        PlayerTextDrawSetString(playerid, TreasureTextDraw[playerid][0], string);
        SetPlayerProgressBarValue(playerid, TreasureProgress[playerid][0], OxygenSeeker[playerid]);

        TimeOxygen[playerid] = SetTimerEx("RemoveOxygen", 60000, false, "i", playerid);
    }
    else if(GetToolAndClothSeeker[playerid] == 1){
        GetToolAndClothSeeker[playerid] = 0;
        RemoveAttachedObject(playerid, 9);
        RemoveAttachedObject(playerid, 8);
        KillTimer(TimeOxygen[playerid]);
        TimeOxygen[playerid] = 0;
        ClearAnimations(playerid);
        ApplyAnimation(playerid, "goggles", "goggles_put_on", 4.0, 0, 0, 0, 0, 0);
        SendClientMessage(playerid, COLOR_YELLOW, "คุณได้คืนอุปกรณ์กันรังสีเรียบร้อยแล้ว");
        PlayerTextDrawHide(playerid, TreasureTextDraw[playerid][0]);
        PlayerTextDrawDestroy(playerid, TreasureTextDraw[playerid][0]);
        HidePlayerProgressBar(playerid, TreasureProgress[playerid][0]);
        DestroyPlayerProgressBar(playerid, TreasureProgress[playerid][0]);
        OxygenSeeker[playerid] = 0;
    }
    return 1;
}

OnPlayerWashTreasure(playerid){
    StartingWashTreasure[playerid] = 1;
    TogglePlayerControllable(playerid, 0);
    ProcessWashPoint[playerid] = 0;
    //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0xFF4848AA, 500.000000, 0);
    CreatePlayerProgressbar_Job(playerid, 0xFF4848AA);
    CleanTreasureTime[playerid] = SetTimerEx("CleanTreasure", 100, false, "i", playerid);
    /*else {
        StartingWashTreasure[playerid] = 0;
        KillTimer(CleanTreasureTime[playerid]);
        CleanTreasureTime[playerid] = 0;
        TogglePlayerControllable(playerid, 1);
        HidePlayerProgressBar(playerid, ProgressbarJob[playerid]);
        DestroyPlayerProgressBar(playerid, ProgressbarJob[playerid]);
        ProcessWashPoint[playerid] = 0;
    }*/
    return 1;
}

task ReloadSeeker[300000](){
    for(new i=0; i<MAX_TREASURE; i++){
        if(TreasureData[i][treasureStill] == 0){
            TreasureData[i][treasureStill] = 1;
            Treasure_Refresh(i);
        }
    }
    return 1;
}

forward RemoveOxygen(playerid);
public RemoveOxygen(playerid){
    if(LoggedIn[playerid]){
        new string[32];
        if(PlayerData[playerid][pJob] == SEEKERJOB){
            if(GetToolAndClothSeeker[playerid]){
                if(OxygenSeeker[playerid] > 5){
                    OxygenSeeker[playerid] -= 5;
                    format(string, sizeof(string), "Oxygen %d", OxygenSeeker[playerid]);
					PlayerTextDrawSetString(playerid, TreasureTextDraw[playerid][0], string);
					SetPlayerProgressBarValue(playerid, TreasureProgress[playerid][0], OxygenSeeker[playerid]);
                    TimeOxygen[playerid] = SetTimerEx("RemoveOxygen", 60000, false, "i", playerid);
                }
            }
        }  
    }
    return 1;
}

forward CleanTreasure(playerid);
public CleanTreasure(playerid){
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pJob] == SEEKERJOB){
            if(StartingWashTreasure[playerid]){
                if(ProcessWashPoint[playerid] >= 500){
                    if(PlayerInventory_AllCount(playerid, "Dirty Treasure") > 0){
                        PlayerData[playerid][pStress]++;
                        if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
                        new itemid = PlayerInventory_AddItem(playerid, "Clean Treasure", 2710, 1);
                        if (itemid == -1){
                            return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                        }
                        PlayerInventory_Remove(playerid, "Dirty Treasure", 1);
                        SendClientMessage(playerid, COLOR_YELLOW, "| - สมบัติที่ล้างรังสี (Clean Treasure) + 1 ชิ้น |");
                        SendClientMessage(playerid, COLOR_YELLOW, "| - สมบัติเจือปนรังสี (Dirty Treasure) - 1 ชิ้น |");
                        StartingWashTreasure[playerid] = 0;
                        TogglePlayerControllable(playerid, 1);
                        DestroyPlayerProgressbar_Job(playerid);
                        ProcessWashPoint[playerid] = 0;
                        KillTimer(CleanTreasureTime[playerid]);
                        CleanTreasureTime[playerid] = 0;
                        ClearAnimations(playerid);
                    }
                    else{
                        StartingWashTreasure[playerid] = 0;
                        TogglePlayerControllable(playerid, 1);
                        DestroyPlayerProgressbar_Job(playerid);
                        ProcessWashPoint[playerid] = 0;
                        KillTimer(CleanTreasureTime[playerid]);
                        CleanTreasureTime[playerid] = 0;
                        ClearAnimations(playerid);
                    }
                }
                else{

                    new string[128];

                    ProcessWashPoint[playerid]++;
                    SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], ProcessWashPoint[playerid]);
                    format(string, sizeof string, "Processing... (%d)", ProcessWashPoint[playerid]);
                    PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
                    CleanTreasureTime[playerid] = SetTimerEx("CleanTreasure", 100, false, "i", playerid);
                }
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
            }
        }
    }
    return 1;
}

CMD:setoxygen(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] >= 1338){
        new userid, amount;
        if(sscanf(params, "uI(0)", userid, amount)) return SystemMsg(playerid, "/setoxygen [playerid] [amount]");
        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
        if(userid != INVALID_PLAYER_ID && LoggedIn[userid]){
            OxygenSeeker[userid] = amount;
        }
    }
    return 1;
}

ShowDialogSellSeeker(playerid){
    new string[128];
    new count = PlayerInventory_AllCount(playerid, "Clean Treasure");
    format(string, sizeof(string), "คุณมีสมบัติล้างรังสี: %d\nกรอกจำนวนที่ต้องการจะขาย", count);
    Dialog_ShowEasy(playerid, Dialog_SellSeeker, DIALOG_STYLE_INPUT, "ขายสมบัติ", string, "ขาย", "ยกเลิก");
    return 1;
}

Dialog:Dialog_SellSeeker(playerid, response, listitem, inputtext[]){
    if(!response){
        GetJobID[playerid] = -1;
        return 1;
    }

    if(response){
        new amount = strval(inputtext);

        if(amount > PlayerInventory_AllCount(playerid, "Clean Treasure"))
            return ErrorMsg(playerid, "คุณมีสมบัติล้างรังสีไม่พอกับจำนวนที่กรอก");

        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนที่จะขายให้มากกว่า 0");

        new price = amount * JobData[GetJobID[playerid]][jobDeliverPrice];
        GiveMoney(playerid, price, "sell clean treasure");
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Clean Treasure (สมบัติล้างรังสี)' จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
        PlayerInventory_Remove(playerid, "Clean Treasure", amount);
    }
    return 1;
}