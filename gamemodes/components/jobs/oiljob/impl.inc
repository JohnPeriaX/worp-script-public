#if defined _inc_impl
	#undef _inc_impl
#endif

ResetOilJob(playerid){
    DrillPoint[playerid] = 0;
    StartDrill[playerid] = 0;
    OilGetID[playerid] = -1;
    KillTimer(DrillTime[playerid]);
    DrillTime[playerid] = 0;
    StartProcessOil[playerid] = 0;
    KillTimer(ProcessOilTime[playerid]);
    ProcessOilTime[playerid] = 0;
    ProcessOilPoint[playerid] = 0;
    RemoveAttachedObject(playerid, 8);
    RemoveAttachedObject(playerid, 7);
    return 1;
}

forward Oil_Load();
public Oil_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_OILS)
	{
	    OilData[i][oilStill] = true;

	    cache_get_value_name_int(i, "oilID", OilData[i][oilID]);
	    cache_get_value_name_int(i, "oilAmount", OilData[i][oilAmount]);
	    cache_get_value_name_float(i, "oilPosX", OilData[i][oilPos][0]);
        cache_get_value_name_float(i, "oilPosY", OilData[i][oilPos][1]);
        cache_get_value_name_float(i, "oilPosZ", OilData[i][oilPos][2]);

        Oil_RenderRefresh(i);
 	    Oil_Refresh(i);
        Oil_Count++;

	}
	printf("(( [MYSQL]: Load %d Oil Successfully ))", Oil_Count);
	return 1;
}

Oil_Save(oilid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `oil` SET `oilPosX` = '%f', `oilPosY` = '%f', `oilPosZ` = '%f', `oilAmount` = '%d'  WHERE `oilID` = '%d'",
        OilData[oilid][oilPos][0],
        OilData[oilid][oilPos][1],
        OilData[oilid][oilPos][2],
        OilData[oilid][oilAmount],
	    OilData[oilid][oilID]
	);
	return mysql_tquery(dbCon, query);
}

Oil_RenderRefresh(oilid){
    if(oilid != -1 && OilData[oilid][oilStill]){
        new string[128];

        format(string, sizeof(string), "[บ่อน้ำมันดิบ]\n>> %s <<", FormatNumberNotMoney(OilData[oilid][oilAmount]));
        OilData[oilid][oilText] = CreateDynamic3DTextLabel(string, 0xFF5500FF, OilData[oilid][oilPos][0], OilData[oilid][oilPos][1], OilData[oilid][oilPos][2]+0.5, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
        OilData[oilid][oilObject] = CreateDynamicObject(19898, OilData[oilid][oilPos][0], OilData[oilid][oilPos][1], OilData[oilid][oilPos][2],   0.00000, 0.00000, 0.00000);
    }
    return 1;
}

Oil_Refresh(oilid){
    if(oilid != -1 && OilData[oilid][oilStill]){
        new string[128];
        format(string, sizeof(string), "[บ่อน้ำมันดิบ]\n>> %s <<", FormatNumberNotMoney(OilData[oilid][oilAmount]));
        UpdateDynamic3DTextLabelText(OilData[oilid][oilText], 0xFF5500FF, string);
    }
    return 1;
}

Oil_Near(playerid, Float:radius = 2.0)
{
    for (new i = 0; i != MAX_OILS; i ++) if (OilData[i][oilStill] && IsPlayerInRangeOfPoint(playerid, radius, OilData[i][oilPos][0], OilData[i][oilPos][1], OilData[i][oilPos][2])) {
		return i;
	}
	return -1;
}

forward DrillingOil(playerid);
public DrillingOil(playerid){
    if(LoggedIn[playerid]){
        new string[128];
        if(OilGetID[playerid] != -1){
            if(DrillPoint[playerid] < 100 && StartDrill[playerid] == 1){
                DrillPoint[playerid]++;
                SetPlayerProgressBarValue(playerid, ProgressBarJobTypeTwo[playerid][0], DrillPoint[playerid]);
                format(string, sizeof(string), "Drilling >> %d <<", DrillPoint[playerid]);
                PlayerTextDrawSetString(playerid, TextDrawJobTypeTwo[playerid][0], string);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
                DrillTime[playerid] = SetTimerEx("DrillingOil", 500, 0, "i", playerid);
            }
            else if(DrillPoint[playerid] >= 100 && StartDrill[playerid] == 1){
                TogglePlayerControllable(playerid, 1);
                StartDrill[playerid] = 0;
                KillTimer(DrillTime[playerid]);
                DrillTime[playerid] = 0;
                DrillPoint[playerid] = 0;
                ClearAnimations(playerid);
                RemoveAttachedObject(playerid, 8);
                RemoveAttachedObject(playerid, 7);
                PlayerData[playerid][pStress]++;
                if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
                if(OilGetID[playerid] != -1){
                    OilData[OilGetID[playerid]][oilAmount] -= 10;
                    Oil_Refresh(OilGetID[playerid]);
                    Oil_Save(OilGetID[playerid]);
                    OilData[OilGetID[playerid]][oilUse] = 0;
                }   

                new id = PlayerInventory_AddItem(playerid, "Crude Oil", 2062, 5);
                if (id == -1){
                    PlayerTextDrawHide(playerid, TextDrawJobTypeTwo[playerid][0]);
                    HidePlayerProgressBar(playerid, ProgressBarJobTypeTwo[playerid][0]);
                    DestroyPlayerProgressBar(playerid, ProgressBarJobTypeTwo[playerid][0]);
                    PlayerTextDrawDestroy(playerid, TextDrawJobTypeTwo[playerid][0]);
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }

                SendClientMessage(playerid, COLOR_YELLOW, "=======================================");
                SendClientMessage(playerid, -1, "- คุณได้รับ Crude Oil (น้ำมันดิบ) + 5");
                SendClientMessage(playerid, COLOR_YELLOW, "=======================================");

                PlayerTextDrawHide(playerid, TextDrawJobTypeTwo[playerid][0]);
                HidePlayerProgressBar(playerid, ProgressBarJobTypeTwo[playerid][0]);
                DestroyPlayerProgressBar(playerid, ProgressBarJobTypeTwo[playerid][0]);
                PlayerTextDrawDestroy(playerid, TextDrawJobTypeTwo[playerid][0]);
            }
        }
    }
    return 1;
}

StartPlayerProcessOil(playerid){
    if(LoggedIn[playerid]){
        if(StartProcessOil[playerid] == 0 && StartDrill[playerid] == 0){
            if(PlayerInventory_AllCount(playerid, "Crude Oil") < 2) return ErrorMsg(playerid, "คุณไม่มี น้ำมันดิบ ไม่พอ");
            StartProcessOil[playerid] = 1;
            ProcessOilPoint[playerid] = 0;
            ProgressBarJobTypeTwo[playerid][0] = CreatePlayerProgressBar(playerid, 185.000000, 372.000000, 261.500000, 9.000000, 0xFF5500AA, 100.000000, 0);
            LoadPlayerJobTypeTwo(playerid);
            TogglePlayerControllable(playerid, 0);
            PlayerTextDrawShow(playerid, TextDrawJobTypeTwo[playerid][0]);
            ShowPlayerProgressBar(playerid, ProgressBarJobTypeTwo[playerid][0]);
            ProcessOilTime[playerid] = SetTimerEx("ProcessingOil", 1000, 0, "i", playerid);
        }
    }
    return 1;
}

forward ProcessingOil(playerid);
public ProcessingOil(playerid){
    if(LoggedIn[playerid]){
        new string[128];
        if(ProcessOilPoint[playerid] < 100 && StartProcessOil[playerid] == 1){
            ProcessOilPoint[playerid]++;
            SetPlayerProgressBarValue(playerid, ProgressBarJobTypeTwo[playerid][0], ProcessOilPoint[playerid]);
            format(string, sizeof(string), "Processing >> %d <<", ProcessOilPoint[playerid]);
            PlayerTextDrawSetString(playerid, TextDrawJobTypeTwo[playerid][0], string);
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
            ProcessOilTime[playerid] = SetTimerEx("ProcessingOil", 1000, 0, "i", playerid);
        }
        else if(ProcessOilPoint[playerid] >= 100 && StartProcessOil[playerid] == 1){
            TogglePlayerControllable(playerid, 1);
            StartProcessOil[playerid] = 0;
            KillTimer(ProcessOilTime[playerid]);
            ProcessOilTime[playerid] = 0;
            ProcessOilPoint[playerid] = 0;
            ClearAnimations(playerid);

            new amountoil = PlayerInventory_AllCount(playerid, "Crude Oil") / 2;

            new id = PlayerInventory_AddItem(playerid, "Processed Oil", 3632, amountoil);
            if (id == -1){
                PlayerTextDrawHide(playerid, TextDrawJobTypeTwo[playerid][0]);
                HidePlayerProgressBar(playerid, ProgressBarJobTypeTwo[playerid][0]);
                DestroyPlayerProgressBar(playerid, ProgressBarJobTypeTwo[playerid][0]);
                PlayerTextDrawDestroy(playerid, TextDrawJobTypeTwo[playerid][0]);
                return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            }

            SendClientMessage(playerid, COLOR_YELLOW, "=======================================");
            SendClientMessageEx(playerid, -1, "- คุณได้รับ Processed Oil (น้ำมันแปรรูป) + %d", amountoil);
            SendClientMessageEx(playerid, -1, "- คุณเสีย Crude Oil (น้ำมันดิบ) - %d", PlayerInventory_AllCount(playerid, "Crude Oil"));
            SendClientMessage(playerid, COLOR_YELLOW, "=======================================");

            PlayerInventory_Remove(playerid, "Crude Oil", PlayerInventory_AllCount(playerid, "Crude Oil"));

            PlayerTextDrawHide(playerid, TextDrawJobTypeTwo[playerid][0]);
            HidePlayerProgressBar(playerid, ProgressBarJobTypeTwo[playerid][0]);
            DestroyPlayerProgressBar(playerid, ProgressBarJobTypeTwo[playerid][0]);
            PlayerTextDrawDestroy(playerid, TextDrawJobTypeTwo[playerid][0]);
        }
    }
    return 1;
}

ShowDialogSellOil(playerid){
    new string[128];
    new count = PlayerInventory_AllCount(playerid, "Processed Oil");
    format(string, sizeof(string), "คุณมีน้ำมันแปรรูป: %d\nกรอกจำนวนที่ต้องการจะขาย", count);
    Dialog_ShowEasy(playerid, Dialog_SellOil, DIALOG_STYLE_INPUT, "ขายน้ำมันแปรรูป", string, "ขาย", "ยกเลิก");
    return 1;
}

Dialog:Dialog_SellOil(playerid, response, listitem, inputtext[]){
    if(!response){
        GetJobID[playerid] = -1;
        return 1;
    }

    if(response){
        new amount = strval(inputtext);

        if(amount > PlayerInventory_AllCount(playerid, "Processed Oil"))
            return ErrorMsg(playerid, "คุณมีสมบัติล้างรังสีไม่พอกับจำนวนที่กรอก");

        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนที่จะขายให้มากกว่า 0");

        new price = amount * JobData[GetJobID[playerid]][jobDeliverPrice];
        GiveMoney(playerid, price, "sell processed oil");
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Processed Oil (น้ำมันแปรรูป)' จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
        PlayerInventory_Remove(playerid, "Processed Oil", amount);
        SendOilToPump();
    }
    return 1;
}

SendOilToPump(){
    for(new i=0; i<MAX_GAS_PUMPS; i++) if(PumpData[i][pumpExists]){
        if(PumpData[i][pumpFuel] >= 3000) continue;
        else if(PumpData[i][pumpFuel] < 3000){
            PumpData[i][pumpFuel] += 50;
            Pump_Refresh(i);
            Pump_Save(i);
        }
    }
    return 1;
}

Dialog:ShowGpsOilJob(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new id = PlayerGetJobGPSID[playerid];
        if(listitem == 0){
            if(JobData[id][jobPos][0] == 0.0 && JobData[id][jobPos][1] == 0.0 && JobData[id][jobPos][2] == 0.0)
                return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

            EnterCheckPointJob[playerid] = 1;

            SetPlayerCheckpoint(playerid, JobData[id][jobPos][0], JobData[id][jobPos][1], JobData[id][jobPos][2],3.0);
            SendClientMessageEx(playerid, -1,"คุณได้เปิด GPS ไปยัง จุดสมัครอาชีพ %s", JobData[id][jobName]);
        }

        if(listitem == 1){
            if(JobData[id][jobPoint][0] == 0.0 && JobData[id][jobPoint][1] == 0.0 && JobData[id][jobPoint][2] == 0.0)
                return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

            EnterCheckPointJob[playerid] = 1;

            SetPlayerCheckpoint(playerid, JobData[id][jobPoint][0], JobData[id][jobPoint][1], JobData[id][jobPoint][2],3.0);
            SendClientMessageEx(playerid, -1,"คุณได้เปิด GPS ไปยัง จุด แปรรูปน้ำมันดิบ ของอาชีพ %s", JobData[id][jobName]);
        }

        if(listitem == 2){
            if(JobData[id][jobDeliver][0] == 0.0 && JobData[id][jobDeliver][1] == 0.0 && JobData[id][jobDeliver][2] == 0.0)
                return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

            EnterCheckPointJob[playerid] = 1;

            SetPlayerCheckpoint(playerid, JobData[id][jobDeliver][0], JobData[id][jobDeliver][1], JobData[id][jobDeliver][2],3.0);
            SendClientMessageEx(playerid, -1,"คุณได้เปิด GPS ไปยัง จุด ขายน้ำมันแปรรูป ของอาชีพ %s", JobData[id][jobName]);
        }
        PlayerGetJobGPSID[playerid] = -1;
    }
    return 1;
}