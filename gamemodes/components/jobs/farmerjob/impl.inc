#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
    for(new i = 0; i< MAX_GREENFARM; i++){
		CreateGreenFarm(i);
	}
    return 1;
}

ResetFarmerJob(playerid){
    KillTimer(HarvestTimer[playerid]);
    if(StartFarmerJob[playerid] == 1){
        DestroyPlayerProgressbar_Job(playerid);
    }
    StartFarmerJob[playerid] = 0;
    HarvestVehID[playerid] = 0;
    HarvestTimer[playerid] = 0;
    HarvestID[playerid] = 0;
    HarvestPont[playerid] = 0;
    StartProcessFarmer[playerid] = 0;
    ProcessFarmerPoint[playerid] = 0;
    KillTimer(ProcessFarmerTime[playerid]);
    ProcessFarmerTime[playerid] = 0;
    return 1;
}

stock CreateGreenFarm(farmid)
{
    FarmGreen[farmid][FarmEx] = true;

    FarmGreen[farmid][FarmID] = farmid;
    FarmGreen[farmid][FarmTaken] = 0;

    FarmGreen[farmid][FarmPos][0] = FarmGreenPos[farmid][0];
    FarmGreen[farmid][FarmPos][1] = FarmGreenPos[farmid][1];
    FarmGreen[farmid][FarmPos][2] = FarmGreenPos[farmid][2];

    FarmGreen[farmid][FarmScale][0] = FarmGreenPos[farmid][3];
    FarmGreen[farmid][FarmScale][1] = FarmGreenPos[farmid][4];
    FarmGreen[farmid][FarmScale][2] = FarmGreenPos[farmid][5];


    FarmGreen[farmid][FarmObject] = CreateDynamicObject(824,FarmGreenPos[farmid][0],FarmGreenPos[farmid][1],FarmGreenPos[farmid][2],FarmGreenPos[farmid][3],FarmGreenPos[farmid][4],FarmGreenPos[farmid][5]);
	return 1;
}

CMD:refarm(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] >= 1338){
        for(new i=0; i< MAX_GREENFARM; i++){
            FarmGreen[i][FarmTaken] = 0;
            Farm_Refresh(i);
        }
    }
    return 1;
}

Farm_Refresh(farmid){
    if(farmid != -1){
        if(FarmGreen[farmid][FarmTaken] == 1){
            MoveDynamicObject(FarmGreen[farmid][FarmObject], FarmGreenPos[farmid][0],FarmGreenPos[farmid][1],FarmGreenPos[farmid][2]-5.0, 3.0, FarmGreenPos[farmid][3],FarmGreenPos[farmid][4],FarmGreenPos[farmid][5]);
        }
        else{
            MoveDynamicObject(FarmGreen[farmid][FarmObject], FarmGreenPos[farmid][0],FarmGreenPos[farmid][1],FarmGreenPos[farmid][2], 3.0, FarmGreenPos[farmid][3],FarmGreenPos[farmid][4],FarmGreenPos[farmid][5]);
        }
    }
    return 1;
}

forward StartingProcessRice(playerid, point);
public StartingProcessRice(playerid, point){
    new string[128];
    if(StartProcessFarmer[playerid] == 1){
        if(HarvestPont[playerid] >= 50){
            ProcessFarmerPoint[playerid] += 5;
            SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], ProcessFarmerPoint[playerid]);
            format(string,sizeof(string),"Rice Processing... (%d)", ProcessFarmerPoint[playerid]);
            PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
            //GameTextForPlayer(playerid, string, 1000, 3);
            ProcessFarmerTime[playerid] = SetTimerEx("StartingProcessRice", 1000, false, "ii", playerid, ProcessFarmerPoint[playerid]);
            if(ProcessFarmerPoint[playerid] >= 100){
                new veh = Car_GetID(HarvestVehID[playerid]);
                TRP_DestroyVehicle(CarData[veh][carVehicle], true);
                CarData[veh][carVehicle] = INVALID_VEHICLE_ID;
                Car_Spawn(veh);
                DestroyPlayerProgressbar_Job(playerid);
                TogglePlayerControllable(playerid, 1);

                new ricecount = HarvestPont[playerid] / 2;
                new id = PlayerInventory_AddItem(playerid, "Rice", 806, ricecount);


                if (id == -1){
                    ResetFarmerJob(playerid);
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }
                SendClientMessageEx(playerid, COLOR_YELLOW, "[กระเป๋า]: คุณได้รับ 'Rice' + %d", ricecount);
                SendClientMessage(playerid, COLOR_YELLOW, "- หากคุณต้องการเกี่ยวข้าวต่อการุณากดเริ่มทำงานใหม่อีกครั้ง");
                PlayerData[playerid][pStress]++;
                if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
                ResetFarmerJob(playerid);
            }
        }
    }
    return 1;
}

forward HarvestingFarm(playerid);
public HarvestingFarm(playerid)
{
    new string[64];
    new vehicleid = GetPlayerVehicleID(playerid);
	if(LoggedIn[playerid])
	{
		for(new g = 0; g < MAX_GREENFARM; g++) if(FarmGreen[g][FarmEx]){
            if(FarmGreen[g][FarmTaken] == 1) continue;
			if(IsPlayerInRangeOfObject(playerid, FarmGreen[g][FarmObject], 3.0)){
				if(HarvestID[playerid] == FarmGreen[g][FarmObject]){
				    HarvestPont[playerid] += 1;
                    SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], HarvestPont[playerid]);
				    format(string,sizeof(string),"Harvesting: (%d KG)", HarvestPont[playerid]);
                    PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
				    //GameTextForPlayer(playerid, string, 1500, 3);
                    FarmGreen[g][FarmTaken] = 1;
					Farm_Refresh(g);
					Streamer_Update(playerid);
				}
				HarvestID[playerid] = FarmGreen[g][FarmObject];
				break;
			}
		}
	}
	if(StartFarmerJob[playerid] == 1 && HarvestPont[playerid] < 50 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetVehicleModel(vehicleid) == 532){
	    HarvestTimer[playerid] = SetTimerEx("HarvestingFarm", 1000, 0, "i", playerid);
	}
	else
	{
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetVehicleModel(vehicleid) == 532){
            KillTimer(HarvestTimer[playerid]);
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เก็บเกี่ยวข้าวจนเต็มรถแล้ว, ไปยังจุดสีแดงเพื่อส่งข้าว");

            new id = GetClosestJobPoint2(playerid, PlayerData[playerid][pJob]);
            if (id != -1)
            {
                if(JobData[id][jobPoint2][0] == 0.0 && JobData[id][jobPoint2][1] == 0.0 && JobData[id][jobPoint2][2] == 0.0)
                    return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

                EnterCheckPointJob[playerid] = 1;

                SetPlayerCheckpoint(playerid, JobData[id][jobPoint2][0], JobData[id][jobPoint2][1], JobData[id][jobPoint2][2],7.0);
                SendClientMessage(playerid, -1,"คุณได้เปิด GPS ไปยัง จุดส่งข้าว");
            }
        }
	}
	return 1;
}

ShowDialogSellRice(playerid){
    new string[128];
    new count = PlayerInventory_AllCount(playerid, "Rice");
    format(string, sizeof(string), "คุณมีข้าวอยู่: %d\nกรอกจำนวนที่ต้องการจะขาย", count);
    Dialog_ShowEasy(playerid, Dialog_SellRice, DIALOG_STYLE_INPUT, "ขายข้าว", string, "ขาย", "ยกเลิก");
    return 1;
}

Dialog:Dialog_SellRice(playerid, response, listitem, inputtext[]){
    if(!response){
        GetJobID[playerid] = -1;
        return 1;
    }

    if(response){
        new amount = strval(inputtext);

        if(amount > PlayerInventory_AllCount(playerid, "Rice"))
            return ErrorMsg(playerid, "คุณมีข้าวไม่พอกับจำนวนที่คุณจะขาย");

        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนที่จะขายให้มากกว่า 0");

        new price = amount * JobData[GetJobID[playerid]][jobDeliverPrice];
        GiveMoney(playerid, price, "sell rice");
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Rice (ข้าว)' จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
        PlayerInventory_Remove(playerid, "Rice", amount);
    }
    return 1;
}