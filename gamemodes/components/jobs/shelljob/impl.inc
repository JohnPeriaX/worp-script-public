#if defined _inc_impl
	#undef _inc_impl
#endif

ResetShellJob(playerid){
    KillTimer(ShellTimer[playerid]);
    ShellTimer[playerid] = 0;
    PlayerPickingUpShell[playerid] = 0;
    ShellPoint[playerid] = 0;

    if(PlayerGetShellID[playerid] != -1){
        ShellData[PlayerGetShellID[playerid]][shellPlayerUse] = 0;
    }

    PlayerGetShellID[playerid] = -1;
    if(PlayerPickingUpShell[playerid] == 1){
        DestroyPlayerProgressbar_Job(playerid);
    }

    return 1;
}

LoadShell(){

    for(new i=0; i<MAX_SHELLS; i++) if(!ShellData[i][shellEx]){
        ShellData[i][shellEx] = 1;
        ShellData[i][shellAlive] = 1;
        ShellData[i][shellPlayerUse] = 0;
    }

    ShellData[0][shellPos][0] = -2011.5286;
    ShellData[0][shellPos][1] = -948.3765;
    ShellData[0][shellPos][2] = 30.1719;

    ShellData[1][shellPos][0] = -2023.8120;
    ShellData[1][shellPos][1] = -945.1390;
    ShellData[1][shellPos][2] = 30.1793;

    ShellData[2][shellPos][0] = -2020.7333;
    ShellData[2][shellPos][1] = -934.9216;
    ShellData[2][shellPos][2] = 30.1719;

    ShellData[3][shellPos][0] = -2028.7532;
    ShellData[3][shellPos][1] = -924.2628;
    ShellData[3][shellPos][2] = 30.1719;

    ShellData[4][shellPos][0] = -2021.9172;
    ShellData[4][shellPos][1] = -914.4306;
    ShellData[4][shellPos][2] = 30.1793;

    ShellData[5][shellPos][0] = -2013.2246;
    ShellData[5][shellPos][1] = -917.6225;
    ShellData[5][shellPos][2] = 30.1793;

    ShellData[6][shellPos][0] = -2011.5028;
    ShellData[6][shellPos][1] = -905.4935;
    ShellData[6][shellPos][2] = 30.1793;

    ShellData[7][shellPos][0] = -2024.0305;
    ShellData[7][shellPos][1] = -896.9882;
    ShellData[7][shellPos][2] = 30.1793;

    ShellData[8][shellPos][0] = -2017.7891;
    ShellData[8][shellPos][1] = -886.7633;
    ShellData[8][shellPos][2] = 30.1793;

    ShellData[9][shellPos][0] = -2028.5786;
    ShellData[9][shellPos][1] = -880.7407;
    ShellData[9][shellPos][2] = 30.1719;

    ShellData[10][shellPos][0] = -2017.9717;
    ShellData[10][shellPos][1] = -873.5216;
    ShellData[10][shellPos][2] = 30.171;

    ShellData[11][shellPos][0] = -2029.4390;
    ShellData[11][shellPos][1] = -871.1998;
    ShellData[11][shellPos][2] = 30.1719;

    ShellData[12][shellPos][0] = -2011.478;
    ShellData[12][shellPos][1] = -881.6219;
    ShellData[12][shellPos][2] = 30.1719;

    for(new i=0; i<MAX_SHELLS; i++) if(ShellData[i][shellEx]){
        Shell_RenderRefresh(i);
        Shell_Refresh(i);
    }
    return 1;
}

Shell_RenderRefresh(shellid){
    if(shellid != -1 && ShellData[shellid][shellEx]){
        if(ShellData[shellid][shellAlive] == 1){
            ShellData[shellid][shellText] = CreateDynamic3DTextLabel("[หอยสด]\nกด 'ต่อย' เพื่อเก็บ", 0x0FD7FFFF, ShellData[shellid][shellPos][0], ShellData[shellid][shellPos][1], ShellData[shellid][shellPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0,0);
        }
        else if(ShellData[shellid][shellAlive] == 0){
            ShellData[shellid][shellText] = CreateDynamic3DTextLabel("หอยกำลังเกิด...", 0x0FD7FFFF, ShellData[shellid][shellPos][0], ShellData[shellid][shellPos][1], ShellData[shellid][shellPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0,0);
        }
        ShellData[shellid][shellObject] = CreateDynamicObject(953, ShellData[shellid][shellPos][0], ShellData[shellid][shellPos][1], ShellData[shellid][shellPos][2],   0.0, 0.0, 0.0);
    }
    return 1;
}

Shell_Refresh(shellid){
    if(shellid != -1 && ShellData[shellid][shellEx]){

        new string[128];
        if(ShellData[shellid][shellAlive] == 1){
            format(string, sizeof(string), "[หอยสด]\nกด 'ต่อย' เพื่อเก็บ");
            MoveDynamicObject(ShellData[shellid][shellObject], ShellData[shellid][shellPos][0], ShellData[shellid][shellPos][1], ShellData[shellid][shellPos][2], 3.0, 0.0, 0.0, 0.0);
        }
        else if(ShellData[shellid][shellAlive] == 0){
            format(string, sizeof(string), "หอยกำลังเกิด...");
            MoveDynamicObject(ShellData[shellid][shellObject], ShellData[shellid][shellPos][0], ShellData[shellid][shellPos][1], ShellData[shellid][shellPos][2]-8.0, 3.0, 0.0, 0.0, 0.0);
        }
        UpdateDynamic3DTextLabelText(ShellData[shellid][shellText], 0x0FD7FFFF, string);
    }
    return 1;
}

Shell_Nearest(playerid, Float:radius = 3.0)
{
    for (new i = 0; i != MAX_SHELLS; i ++) if (ShellData[i][shellEx] && IsPlayerInRangeOfPoint(playerid, radius, ShellData[i][shellPos][0], ShellData[i][shellPos][1], ShellData[i][shellPos][2])) {
		return i;
	}
	return -1;
}

PlayerPickUpShell(playerid, shellid){
    if(shellid != -1){
        if(ShellData[shellid][shellAlive] == 1 && ShellData[shellid][shellPlayerUse] == 0 && PlayerGetShellID[playerid] == -1){
            if(PlayerPickingUpShell[playerid] == 0){
                ShellData[shellid][shellPlayerUse] = 1;
                PlayerPickingUpShell[playerid] = 1;
                ShellPoint[playerid] = 0;
                PlayerGetShellID[playerid] = shellid;
                //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0x00B6FFAA, 100.000000, 0);
                CreatePlayerProgressbar_Job(playerid, 0x00B6FFAA);
                TogglePlayerControllable(playerid, 0);
                ShellTimer[playerid] = SetTimerEx("PickupShell", 500, false, "ii", playerid, shellid);
            }
        }
    }
    return 1;
}

forward PickupShell(playerid, shellid);
public PickupShell(playerid, shellid){
    if(shellid != -1){
        new string[128];
        if(PlayerPickingUpShell[playerid] == 1 && PlayerGetShellID[playerid] != -1){
            ShellPoint[playerid] += 2;
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
            format(string,sizeof(string),"Shell Picking... (%d)", ShellPoint[playerid]);
            PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
            //GameTextForPlayer(playerid, string, 1000, 3);
            SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], ShellPoint[playerid]);
            ShellTimer[playerid] = SetTimerEx("PickupShell", 500, false, "ii", playerid, shellid);
            if(ShellPoint[playerid] >= 100){
                ShellData[shellid][shellPlayerUse] = 0;
                ShellData[shellid][shellAlive] = 0;
                ShellData[shellid][shellTimeAlive] = 60;
                Shell_Refresh(shellid);

                PlayerGetShellID[playerid] = -1;

                KillTimer(ShellTimer[playerid]);
                ShellTimer[playerid] = 0;
                ShellPoint[playerid] = 0;
                PlayerPickingUpShell[playerid] = 0;

                DestroyPlayerProgressbar_Job(playerid);
                ClearAnimations(playerid);
                TogglePlayerControllable(playerid, 1);
                PlayerData[playerid][pStress]++;
                if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
                new id = PlayerInventory_AddItem(playerid, "Raw Shell", 953, 4);
                if (id == -1){
                    DestroyPlayerProgressbar_Job(playerid);
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }

                SendClientMessage(playerid, -1, "===================================================");
                SendClientMessageEx(playerid, 0x00B6FFAA, "+ คุณได้รับ 'หอยสด' + 4");
                SendClientMessage(playerid, -1, "===================================================");
            }
        }
    }
    return 1;
}

task ReAliveShell[1000](){
    for(new i=0; i<MAX_SHELLS; i++) if(ShellData[i][shellEx]){
        if(ShellData[i][shellAlive] == 0){
            if(ShellData[i][shellTimeAlive] > 0){
                ShellData[i][shellTimeAlive]--;
            }
            if(ShellData[i][shellTimeAlive] <= 0){
                ShellData[i][shellAlive] = 1;
                Shell_Refresh(i);
            }
        }
    }
    return 1;
}

ShowDialogSellShell(playerid){
    new string[128];
    new count = PlayerInventory_AllCount(playerid, "Raw Shell");
    format(string, sizeof(string), "คุณมีหอยสด: %d\nกรอกจำนวนที่ต้องการจะขาย", count);
    Dialog_ShowEasy(playerid, Dialog_SellShell, DIALOG_STYLE_INPUT, "ขายหอยสด", string, "ขาย", "ยกเลิก");
    return 1;
}

Dialog:Dialog_SellShell(playerid, response, listitem, inputtext[]){
    if(!response){
        GetJobID[playerid] = -1;
        return 1;
    }

    if(response){
        new amount = strval(inputtext);

        if(amount > PlayerInventory_AllCount(playerid, "Raw Shell"))
            return ErrorMsg(playerid, "คุณมีหอยสดไม่พอกับจำนวนที่กรอก");

        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนที่จะขายให้มากกว่า 0");

        new price = amount * JobData[GetJobID[playerid]][jobDeliverPrice];
        GiveMoney(playerid, price, "sell raw shell");
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Raw Shell (หอยสด)' จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
        PlayerInventory_Remove(playerid, "Raw Shell", amount);
    }
    return 1;
}
