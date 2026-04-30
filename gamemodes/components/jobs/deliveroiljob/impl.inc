#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

//403 = รถขนน้ำมัน
//584 = พ่วงน้ำมัน

ResetPlayerDeliverOilJob(playerid){
	PlayerStartDeliverOil[playerid] = false;
	PlayerGetOilDeliver[playerid] = false;
	stop OilDeliverLoadTime[playerid];
	PlayerCheckDeliverOilPoint[playerid] = false;
	PlayerGetPumpID[playerid] = -1;
	DisablePlayerCheckpoint(playerid);
	ClearGPS(playerid);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate){
	if(newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_ONFOOT){
		new vehicleid = GetPlayerVehicleID(playerid);
		if(vehicleid != INVALID_VEHICLE_ID){
			if(PlayerData[playerid][pJob] == DELIOILJOB && GetVehicleModel(vehicleid) == 403 && !PlayerStartDeliverOil[playerid]){
				Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "[อาชีพส่งน้ำมัน]", "[!] ให้นำรถไปต่อพ่วงน้ำมันจากนั้นกดปุ่ม 'Y' เพื่อไปรับน้ำมัน", "ตกลง", "");
			}
		}
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
	if(LoggedIn[playerid]){
		if(newkeys & KEY_YES){
			if(PlayerData[playerid][pJob] == DELIOILJOB){
				new id = -1;
				if((id = Job_NearestPoint(playerid)) != -1){
					if(JobData[id][jobType] == DELIOILJOB){
						if(PlayerStartDeliverOil[playerid] && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !PlayerGetOilDeliver[playerid]){
							new vehicleid = GetPlayerVehicleID(playerid);
							if(vehicleid != INVALID_VEHICLE_ID){
								SetPVarInt(playerid, "GetJobIDOilDeliver", id);
								SetPlayerGetOilDeliver(playerid, vehicleid);
							}
							
						}
					}
				}
				else{
					if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
						new vehicleid = GetPlayerVehicleID(playerid);
						if(GetVehicleModel(vehicleid) == 403){
							if(IsTrailerAttachedToVehicle(vehicleid) && !PlayerStartDeliverOil[playerid]){
								PlayerStartDeliverOil[playerid] = true;
								SendClientMessage(playerid, COLOR_YELLOW, "[>] คุณได้เริ่มทำงานเรียบร้อยแล้ว, ไปยังจุดสีแดงเพื่อบรรจุน้ำมันใส่ถัง");
								new idjob = GetClosestJobPoint(playerid, PlayerData[playerid][pJob]);
								if (idjob != -1){
									if(JobData[idjob][jobPoint][0] == 0.0 && JobData[idjob][jobPoint][1] == 0.0 && JobData[idjob][jobPoint][2] == 0.0) return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");
									PlayerEnterCheckPoint[playerid] = true;
									SetPlayerCheckpoint(playerid, JobData[idjob][jobPoint][0], JobData[idjob][jobPoint][1], JobData[idjob][jobPoint][2], 5.0);
									GPSNavigateToPoint(playerid, JobData[idjob][jobPoint][0], JobData[idjob][jobPoint][1], JobData[idjob][jobPoint][2]);
								}
								
							}
							else if(IsTrailerAttachedToVehicle(vehicleid) && PlayerStartDeliverOil[playerid]){
								PlayerStartDeliverOil[playerid] = false;
								DetachTrailerFromVehicle(vehicleid);
								SendClientMessage(playerid, COLOR_YELLOW, "[>] คุณได้ยกเลิกทำงานเรียบร้อยแล้ว");
								PlayerEnterCheckPoint[playerid] = false;
								ResetPlayerDeliverOilJob(playerid);
							}
						}
						return 1;
					}
				}
			}
		}
	}
	return 1;
}

hook OnPlayerEnterCheckpoint(playerid){
	if(LoggedIn[playerid]){
		if(PlayerCheckDeliverOilPoint[playerid] && PlayerStartDeliverOil[playerid]){
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
				new vehicleid = GetPlayerVehicleID(playerid);
				if(vehicleid != INVALID_VEHICLE_ID){
					if(!IsTrailerAttachedToVehicle(vehicleid)){
						ResetPlayerDeliverOilJob(playerid);
						DisablePlayerCheckpoint(playerid);
						ClearGPS(playerid);
						return ErrorMsg(playerid, "คุณไม่มีพ่วงน้ำมันไม่สามารถส่งน้ำมันได้, กรุณาต่อพ่วงและกด Y เพื่อเริ่มทำงานใหม่");
					}
				}

				PlayerCheckDeliverOilPoint[playerid] = false;
				new jobid = GetPVarInt(playerid, "GetJobIDOilDeliver");
				if(jobid != -1 && PlayerGetPumpID[playerid] != -1){
					PumpData[PlayerGetPumpID[playerid]][pumpFuel] += 200;
					if(PumpData[PlayerGetPumpID[playerid]][pumpFuel] >= MAX_FUEL_GAS) PumpData[PlayerGetPumpID[playerid]][pumpFuel] = MAX_FUEL_GAS;
					Pump_Refresh(PlayerGetPumpID[playerid]);
					GiveMoney(playerid, JobData[jobid][jobDeliverPrice], "Deliver Oil to Pump");
					new string[256];
					PlayerData[playerid][pStress]++;
					if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
					format(string, sizeof string, "[>] ยินดีด้วยคุณได้ส่งน้ำมันถึงปั้มสำเร็จแล้ว, และคุณได้รับเงินตอบแทนจำนวน %s\n[!] หากคุณต้องการทำงานใหม่อีกครั้งให้ต่อพ่วงถังน้ำมันและกด 'Y' เพื่อเริ่มทำงานอีกครั้ง", FormatNumber(JobData[jobid][jobDeliverPrice]));
					Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ส่งน้ำมันสำเร็จ", string, "ตกลง", "");
				}
				ResetPlayerDeliverOilJob(playerid);
				DisablePlayerCheckpoint(playerid);
				ClearGPS(playerid);
			}
		}
	}
	return 1;
}

timer LoadOilTimer[100](playerid){
    if(PlayerGetOilDeliver[playerid]){
        new Float:currentValueLoadOil = GetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0]);
        if(currentValueLoadOil < 100.0){
            currentValueLoadOil++;
            SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], currentValueLoadOil);
        }
        else{
            LoadOil_Success(playerid);
        }
    }
    return 1;
}

SetPlayerGetOilDeliver(playerid, vehicleid){

	if(!IsTrailerAttachedToVehicle(vehicleid)){
		ResetPlayerDeliverOilJob(playerid);
		ErrorMsg(playerid, "คุณไม่มีพ่วงถังน้ำมัน");
		return 1;
	}

	PlayerGetOilDeliver[playerid] = true;
	TogglePlayerControllable(playerid, 0);
    LoadPlayerNewProgress(playerid);
	ShowPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
	SetPlayerProgressBarColour(playerid, NewProgressBar[playerid][0], 0xFFB23BAA);
	OilDeliverLoadTime[playerid] = repeat LoadOilTimer(playerid);
	return 1;
}

LoadOil_Success(playerid){
	stop OilDeliverLoadTime[playerid];
	TogglePlayerControllable(playerid, 1);
	SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], 0.0);
    HidePlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    PlayerTextDrawHide(playerid, NewProgressText[playerid][0]);
    DestroyPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    PlayerTextDrawDestroy(playerid, NewProgressText[playerid][0]);
	Dialog_ShowEasy(playerid, ConfirmDeliverOil, DIALOG_STYLE_MSGBOX, "บรรจุน้ำมัน", "[!] คุณได้บรรจุน้ำมันสำเร็จแล้ว\n[>] กรุณากด 'ตกลง' เพื่อเลือกสถานที่ ที่จะไปส่ง", "ตกลง", "");
	return 1;
}

Dialog:ConfirmDeliverOil(playerid, response, listitem, inputtext[]){
	if(!response){
		return Dialog_ShowEasy(playerid, ConfirmDeliverOil, DIALOG_STYLE_MSGBOX, "บรรจุน้ำมัน", "[!] คุณได้บรรจุน้ำมันสำเร็จแล้ว\n[>] กรุณากด 'ตกลง' เพื่อเลือกสถานที่ ที่จะไปส่ง", "ตกลง", "");
	}
	if(response){
		ViewPump(playerid);
	}
	return 1;
}

ViewPump(playerid){
	new string[2048], menu[20], count;
	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);
	SetPVarInt(playerid, "page", 1);
	for(new i=0; i<MAX_GAS_PUMPS; i++){
	    if(PumpData[i][pumpExists]){
			if(count == 20){
				format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
				break;
			}
			format(menu, 20, "menu%d", ++count);
			SetPVarInt(playerid, menu, i);
			format(string, sizeof(string), "%s ปั้มน้ำมัน %d (จำนวนน้ำมัน: %s) (%.2f เมตร)\n", string, i, FormatNumberNotMoney(PumpData[i][pumpFuel]), GetPlayerDistanceFromPoint(playerid, PumpData[i][pumpPos][0], PumpData[i][pumpPos][1], PumpData[i][pumpPos][2]));
        }
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ปั้มน้ำมัน", "ไม่พบปั้มน้ำมัน..", "ปิด", "");
	else Dialog_ShowEasy(playerid, PumpViewDialog, DIALOG_STYLE_LIST, "ปั้มน้ำมัน", string, "ตกลง", "");
	return 1;
}

SetPlayerPointToPump(playerid){
	new pumpid = GetPVarInt(playerid, "ViewPumpID");

	if(pumpid != -1){

		if(PumpData[pumpid][pumpFuel] >= MAX_FUEL_GAS){
			ErrorMsg(playerid, "ปั้มน้ำมันที่คุณเลือกมีจำนวนน้ำมันเต็มแล้ว");
			return ViewPump(playerid);
		}

		PlayerGetPumpID[playerid] = pumpid;
		PlayerCheckDeliverOilPoint[playerid] = true;
		SendClientMessage(playerid, COLOR_YELLOW, "[ระบบนำทาง]: GPS ได้นำทางไปยังปั้มน้ำมันที่คุณเลือกเรียบร้อยแล้ว!");
		SetPlayerCheckpoint(playerid, PumpData[pumpid][pumpPos][0], PumpData[pumpid][pumpPos][1], PumpData[pumpid][pumpPos][2], 10.0);
		GPSNavigateToPoint(playerid, PumpData[pumpid][pumpPos][0], PumpData[pumpid][pumpPos][1], PumpData[pumpid][pumpPos][2]);
	}
	return 1;
}

Dialog:PumpViewDialog(playerid, response, listitem, inputtext[]){

	if(!response){
		return ViewPump(playerid);
	}

	if(response) {
		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);
			SetPVarInt(playerid, "ViewPumpID", GetPVarInt(playerid, str_biz));
			SetPlayerPointToPump(playerid);
			return 1;
		}

		new currentPage = GetPVarInt(playerid, "page");
		if(listitem==0) {
			if(currentPage>1) currentPage--;
		}
		else if(listitem == 21) currentPage++;
		new string[2048], count;
		format(string, sizeof(string), "%s{B4B5B7}หน้า %d\n", string, (currentPage==1) ? 1 : currentPage-1);
		SetPVarInt(playerid, "page", currentPage);
		new skipitem = (currentPage-1) * 20;
		for(new i=0; i<MAX_GAS_PUMPS; i++){
		    if(PumpData[i][pumpExists]){
				if(skipitem){
					skipitem--;
					continue;
				}
				if(count == 20){
					format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
					break;
				}
				format(menu, 20, "menu%d", ++count);
				SetPVarInt(playerid, menu, i);
				format(string, sizeof(string), "%s ปั้มน้ำมัน %d (จำนวนน้ำมัน: %s) (%.2f เมตร)\n", string, i, FormatNumberNotMoney(PumpData[i][pumpFuel]), GetPlayerDistanceFromPoint(playerid, PumpData[i][pumpPos][0], PumpData[i][pumpPos][1], PumpData[i][pumpPos][2]));
            }
		}

		Dialog_ShowEasy(playerid, PumpViewDialog, DIALOG_STYLE_LIST, "ปั้มน้ำมัน", string, "ตกลง", "");
	}
	return 1;
}