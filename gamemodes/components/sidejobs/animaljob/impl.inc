#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetPlayerCow(playerid){
    PlayerGetCowObject[playerid] = false;
    PlayerHarvestNewCow[playerid] = false;
    PlayerGetCowMilk[playerid] = -1;
    stop PlayerHarvestMilkCowTime[playerid];
    return 1;
}

task CheckUpdateNewCow[600000](){
    foreach(new i : Iter_NewCow){
        if(NewCowData[i][newcowActive]){
            NewCowData[i][newcowActive] = false;

            if(NewCowData[i][newcowHungry] > 0){
                NewCowData[i][newcowHungry] -= 30;
                if(NewCowData[i][newcowHungry] < 0){
                    NewCowData[i][newcowHungry] = 0;
                }
                Update_NewCowObject(i);
                NewCow_Save(i);
            }

        }
        else if(!NewCowData[i][newcowActive]){
            NewCowData[i][newcowActive] = false;
            NewCowData[i][newcowGrowth] = 0;
            NewCowData[i][newcowHungry] = 0;
            NewCowData[i][newcowStill] = 0;
            NewCowData[i][newcowOwner] = 0;
            NewCowData[i][newcowRounds] = 0;
            format(NewCowData[i][newcowOwnerName], 64, "NULL");
            Update_NewCowObject(i);
            NewCow_Save(i);
        }
    }
}

NewCow_Save(cowid){
    if(cowid != -1 && Iter_Contains(Iter_NewCow, cowid)){
        new
            query[256];

        mysql_format(dbCon, query, sizeof(query), "UPDATE `newcows` SET `newcowOwner` = '%d', `newcowOwnerName` = '%e', `newcowHungry` = '%d', `newcowGrowth` = '%d', `newcowStill` = '%d', `newcowRounds` = '%d' WHERE `newcowID` = '%d'",
            NewCowData[cowid][newcowOwner],
            NewCowData[cowid][newcowOwnerName],
            NewCowData[cowid][newcowHungry],
            NewCowData[cowid][newcowGrowth],
            NewCowData[cowid][newcowStill],
            NewCowData[cowid][newcowRounds],
            NewCowData[cowid][newcowID]
        );
        return mysql_tquery(dbCon, query);
    }
    return 1;
}

forward NewCow_Load();
public NewCow_Load(){
    new rows;
    cache_get_row_count(rows);
    for (new i = 0; i < rows; i ++) if (i < MAX_NEWCOW){
        cache_get_value_name_int(i, "newcowID", NewCowData[i][newcowID]);
        cache_get_value_name_int(i, "newcowOwner", NewCowData[i][newcowOwner]);
        cache_get_value_name(i, "newcowOwnerName", NewCowData[i][newcowOwnerName], 64);
        cache_get_value_name_int(i, "newcowGrowth", NewCowData[i][newcowGrowth]);
        cache_get_value_name_int(i, "newcowHungry", NewCowData[i][newcowHungry]);
        cache_get_value_name_int(i, "newcowStill", NewCowData[i][newcowStill]);
        cache_get_value_name_int(i, "newcowRounds", NewCowData[i][newcowRounds]);
        cache_get_value_name_float(i, "newcowPosX", NewCowData[i][newcowPos][0]);
        cache_get_value_name_float(i, "newcowPosY", NewCowData[i][newcowPos][1]);
        cache_get_value_name_float(i, "newcowPosZ", NewCowData[i][newcowPos][2]);
        cache_get_value_name_float(i, "newcowPosA", NewCowData[i][newcowPos][3]);

        NewCowData[i][newcowActive] = true;
        NewCowData[i][newcowIsPicking] = false;

        Iter_Add(Iter_NewCow, i);
        FirstLoad_NewCowObject(i);
    }
    printf("(( [MYSQL]: Load %d NewCows Successfully ))", Iter_Count(Iter_NewCow));
    return 1;
}

FirstLoad_NewCowObject(cowid){
    if(cowid != -1 && Iter_Contains(Iter_NewCow, cowid)){
        new string[256];
        if(NewCowData[cowid][newcowStill]){
            if(NewCowData[cowid][newcowGrowth] < 100){
                NewCowData[cowid][newcowObject] = CreateDynamicObject(NEWCOW_OBJECT, NewCowData[cowid][newcowPos][0], NewCowData[cowid][newcowPos][1], NewCowData[cowid][newcowPos][2], 0.000000, 0.000000, NewCowData[cowid][newcowPos][3], -1, -1, -1, 300.00, 300.00);
                format(string, sizeof string, "[วัวที่ถูกเลี้ยงดู]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]\nค่าความหิว: [%d]", NewCowData[cowid][newcowOwnerName], NewCowData[cowid][newcowGrowth], NewCowData[cowid][newcowHungry]);
                NewCowData[cowid][newcow3DText] = CreateDynamic3DTextLabel(string, COLOR_ORANGE, NewCowData[cowid][newcowPos][0], NewCowData[cowid][newcowPos][1], NewCowData[cowid][newcowPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
            }
            else{
                NewCowData[cowid][newcowObject] = CreateDynamicObject(NEWCOW_OBJECT, NewCowData[cowid][newcowPos][0], NewCowData[cowid][newcowPos][1], NewCowData[cowid][newcowPos][2], 0.000000, 0.000000, NewCowData[cowid][newcowPos][3], -1, -1, -1, 300.00, 300.00);
                format(string, sizeof string, "[วัวที่ถูกเลี้ยงดู]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]\nค่าความหิว: [%d]", NewCowData[cowid][newcowOwnerName], NewCowData[cowid][newcowGrowth], NewCowData[cowid][newcowHungry]);
                NewCowData[cowid][newcow3DText] = CreateDynamic3DTextLabel(string, COLOR_ORANGE, NewCowData[cowid][newcowPos][0], NewCowData[cowid][newcowPos][1], NewCowData[cowid][newcowPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
            }
        }
        else{
            NewCowData[cowid][newcowObject] = CreateDynamicObject(NEWCOW_OBJECT, NewCowData[cowid][newcowPos][0], NewCowData[cowid][newcowPos][1], NewCowData[cowid][newcowPos][2]-7.0, 0.000000, 0.000000, NewCowData[cowid][newcowPos][3], -1, -1, -1, 300.00, 300.00);
            format(string, sizeof string, "[วัวที่ถูกเลี้ยงดู]\nพื้นที่ว่างพร้อมเลี้ยง");
            NewCowData[cowid][newcow3DText] = CreateDynamic3DTextLabel(string, COLOR_ORANGE, NewCowData[cowid][newcowPos][0], NewCowData[cowid][newcowPos][1], NewCowData[cowid][newcowPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
        }
    }
    return 1;
}

Update_NewCowObject(cowid){
    if(cowid != -1 && Iter_Contains(Iter_NewCow, cowid)){
        new string[256];
        if(NewCowData[cowid][newcowStill]){
            if(NewCowData[cowid][newcowGrowth] < 100){
                MoveDynamicObject(NewCowData[cowid][newcowObject], NewCowData[cowid][newcowPos][0], NewCowData[cowid][newcowPos][1], NewCowData[cowid][newcowPos][2], 2.5, 0.000000, 0.000000, NewCowData[cowid][newcowPos][3]);
                format(string, sizeof string, "[วัวที่ถูกเลี้ยงดู]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]\nค่าความหิว: [%d]", NewCowData[cowid][newcowOwnerName], NewCowData[cowid][newcowGrowth], NewCowData[cowid][newcowHungry]);
                UpdateDynamic3DTextLabelText(NewCowData[cowid][newcow3DText], COLOR_ORANGE, string);
            }
            else{
                MoveDynamicObject(NewCowData[cowid][newcowObject], NewCowData[cowid][newcowPos][0], NewCowData[cowid][newcowPos][1], NewCowData[cowid][newcowPos][2], 2.5, 0.000000, 0.000000, NewCowData[cowid][newcowPos][3]);
                format(string, sizeof string, "[วัวที่ถูกเลี้ยงดู]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]\nค่าความหิว: [%d]", NewCowData[cowid][newcowOwnerName], NewCowData[cowid][newcowGrowth], NewCowData[cowid][newcowHungry]);
                UpdateDynamic3DTextLabelText(NewCowData[cowid][newcow3DText], COLOR_ORANGE, string);
            }
        }
        else{
            MoveDynamicObject(NewCowData[cowid][newcowObject], NewCowData[cowid][newcowPos][0], NewCowData[cowid][newcowPos][1], NewCowData[cowid][newcowPos][2]-7.0, 2.5, 0.000000, 0.000000, NewCowData[cowid][newcowPos][3]);
            format(string, sizeof string, "[วัวที่ถูกเลี้ยงดู]\nพื้นที่ว่างพร้อมเลี้ยง");
            UpdateDynamic3DTextLabelText(NewCowData[cowid][newcow3DText], COLOR_ORANGE, string);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(LoggedIn[playerid]){
        if(newkeys & KEY_YES){
            new string[128];
            if(IsPlayerInRangeOfPoint(playerid, 5.0, -186.7936,-17.9054,3.1172)){
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
                    new vehid = GetPlayerVehicleID(playerid);
                    if(CarHas_CowObject[vehid]) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "ยานพาหนะคันนี้มีวัวอยู่แล้ว!", "ตกลง", "");
                    if(GetVehicleModel(vehid) == 478){
                        format(string, sizeof(string), "คุณต้องการที่จะซื้อวัวในราคา %s หรือไม่?", FormatNumber(COW_PRICE));
                        Dialog_ShowEasy(playerid, BuyCowOnDrive, DIALOG_STYLE_MSGBOX, "ซื้อวัว", string, "ซื้อ", "ยกเลิก");
                    }
                }
                else if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
                    if(!PlayerGetCowObject[playerid]){
                        format(string, sizeof(string), "คุณต้องการที่จะซื้อวัวในราคา %s หรือไม่?", FormatNumber(COW_PRICE));
                        Dialog_ShowEasy(playerid, BuyCowOnFoot, DIALOG_STYLE_MSGBOX, "ซื้อวัว", string, "ซื้อ", "ยกเลิก");
                    }
                }
            }

            new id = -1;
            if((id = Car_NearestIsJob(playerid)) != -1){
                if(CarData[id][carModel] == 478){
                    if (IsPlayerNearBoot(playerid, CarData[id][carVehicle])){
                        if(CarHas_CowObject[CarData[id][carVehicle]]){
                            if(!PlayerGetCowObject[playerid]){
                                CarHas_CowObject[CarData[id][carVehicle]] = false;
                                if(IsValidDynamicObject(CowObject_Vehicle[CarData[id][carVehicle]]) && CowObject_Vehicle[CarData[id][carVehicle]] != -1) DestroyDynamicObject(CowObject_Vehicle[CarData[id][carVehicle]]);
                                CowObject_Vehicle[CarData[id][carVehicle]] = -1;
                                SetPlayerAttachedObject(playerid,9,19833,1,-1.357000,0.000000,-0.569000,0.000000,88.099983,-177.600006,1.000000,1.000000,1.000000);
                                PlayerGetCowObject[playerid] = true;
                                ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
                            }
                        }
                        else{
                            if(PlayerGetCowObject[playerid]){
                                CarHas_CowObject[CarData[id][carVehicle]] = true;
                                PlayerGetCowObject[playerid] = false;
                                RemoveAttachedObject(playerid, 9);
                                ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
                                CowObject_Vehicle[CarData[id][carVehicle]] = CreateDynamicObject(19833, 0, 0, 0, 0, 0, 0);
                                AttachDynamicObjectToVehicle(CowObject_Vehicle[CarData[id][carVehicle]], CarData[id][carVehicle], 0.2, -1.5, -0.1, 0.0, 0.0, 150.0);
                            }
                        }
                    }
                }
            }

            if((id = NewCow_Nearest(playerid, 1)) != -1){
                if(PlayerGetCowObject[playerid]){
                    SetPlayerPlaceCow(playerid, id);
                }
            }
            else if((id = NewCow_Nearest(playerid, 2)) != -1){
                SetPVarInt(playerid, "NewCowID", id);
                Dialog_ShowEasy(playerid, NewCowAction, DIALOG_STYLE_LIST, "วัวที่ถูกเลี้ยงดู", "- ให้อาหาร\n- รีดนม", "เลือก", "ยกเลิก");
            }
        }
    }
    return 1;
}

forward RemoveObjectRice(playerid);
public RemoveObjectRice(playerid){
    RemoveAttachedObject(playerid, 9);
    return 1;
}

CMD:setcow(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1337) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    new type, amount, id = -1;
    if(sscanf(params, "dI(1)", type, amount)){
        SystemMsg(playerid, "/setcow [cowid] [OPTION] [Amount]");
        SystemMsg(playerid, "[OPTION]: [1]: การเจริญเติบโต, [2]: ค่าความหิว");
        return 1;
    }

    if((id = NewCow_Nearest(playerid, 2)) != -1){
        if(type == 1){
            NewCowData[id][newcowGrowth] += amount;
            SendClientMessage(playerid, -1, "คุณได้เพิ่มค่าเจริญเติบโตของวัวสำเร็จ");
        }
        if(type == 2){
            NewCowData[id][newcowHungry] += amount;
            SendClientMessage(playerid, -1, "คุณได้เพิ่มค่าความหิวของวัวสำเร็จ");
        }
        Update_NewCowObject(id);
        NewCow_Save(id);
    }
    return 1;
}

Dialog:NewCowAction(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new cowid = GetPVarInt(playerid, "NewCowID");
        if(cowid != -1 && Iter_Contains(Iter_NewCow, cowid)){
            if(listitem == 0){

                if(NewCowData[cowid][newcowHungry] >= 100){
                    DeletePVar(playerid, "NewCowID");
                    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "วัวตัวนี้อิ่มแล้ว, ยังไม่สามารถป้อนอาหารเพิ่มได้!", "ตกลง", "");
                    return 1;
                }

                if(NewCowData[cowid][newcowGrowth] >= 100){
                    DeletePVar(playerid, "NewCowID");
                    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "วัวตัวนี้เจริญเติบโตเต็มที่แล้ว!", "ตกลง", "");
                    return 1;
                }

                if(PlayerInventory_AllCount(playerid, "Rice") < 1){
                    DeletePVar(playerid, "NewCowID");
                    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "คุณไม่มีฟางข้าวที่จะเลี้ยงวัว!", "ตกลง", "");
                    return 1;
                }

                PlayerInventory_Remove(playerid, "Rice", 1);
                Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ให้อาหารวัวสำเร็จ", "คุณได้ทำการให้ฟางข้าวกับวัวเรียบร้อยแล้ว", "ตกลง", "");    
                SetPlayerAttachedObject(playerid,9,806,6,0.164000,0.274999,0.068999,-31.199998,0.000000,0.000000,0.405000,0.166000,0.220000);
                ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
                SetTimerEx("RemoveObjectRice", 1000, false, "i", playerid);

                new growth = jdzrandom(5, 10);
                new hungry = jdzrandom(30, 50);

                NewCowData[cowid][newcowGrowth] += growth;
                NewCowData[cowid][newcowActive] = true;

                if(NewCowData[cowid][newcowGrowth] >= 100){
                    NewCowData[cowid][newcowGrowth] = 100;
                } 

                NewCowData[cowid][newcowHungry] += hungry;

                if(NewCowData[cowid][newcowHungry] >= 100){
                    NewCowData[cowid][newcowHungry] = 100;
                } 

                Update_NewCowObject(cowid);
                NewCow_Save(cowid);
            }

            if(listitem == 1){

                if(NewCowData[cowid][newcowGrowth] < 100){
                    DeletePVar(playerid, "NewCowID");
                    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "วัวตัวนี้ยังเจริญเติบโตไม่เต็มที่!", "ตกลง", "");
                    return 1;
                }

                if(NewCowData[cowid][newcowOwner] != PlayerData[playerid][pID]){
                    DeletePVar(playerid, "NewCowID");
                    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "วัวตัวนี้ไม่ใช่ของคุณ!", "ตกลง", "");
                    return 1;
                }

                if(!PlayerHarvestNewCow[playerid]){
                    SetPlayerHarvestNewCow(playerid);
                }
            }
        }
    }
    return 1;
}

ResetCowPickingup(playerid){
    if(PlayerGetCowMilk[playerid] != -1){
        NewCowData[PlayerGetCowMilk[playerid]][newcowIsPicking] = false;
    }
    return 1;
}

timer SetPlayerCowMilk[500](playerid){
    if(PlayerHarvestNewCow[playerid]){
        new Float:CowMilkPoint = GetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0]);
        if(CowMilkPoint < 100.0){
            CowMilkPoint += 5;
            SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], CowMilkPoint);
            ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
        }
        else{
            new cowid = GetPVarInt(playerid, "NewCowID");
            if(cowid != -1 && Iter_Contains(Iter_NewCow, cowid) && PlayerHarvestNewCow[playerid]){
                PlayerHarvestNewCow[playerid] = false;
                NewCowData[cowid][newcowRounds] ++;
                new milk = jdzrandom(3, 5);
                new string[128];
                PlayerData[playerid][pStress]++;
                if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
                new itemid = PlayerInventory_AddItem(playerid, "Cow Milk", 19570, milk);
                if(itemid == -1) return ErrorMsg(playerid, "คุณไม่มีช่องว่างพอที่จะเก็บไอเท็มนี้ชิ้นนี้");

                format(string, sizeof string, "คุณได้รับ 'นมวัว' + %d", milk);
                Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การได้รับ", string, "ตกลง", "");

                if(NewCowData[cowid][newcowRounds] >= 2){
                    NewCowData[cowid][newcowStill] = false;
                    NewCowData[cowid][newcowGrowth] = 0;
                    NewCowData[cowid][newcowRounds] = 0;
                    NewCowData[cowid][newcowHungry] = 0;
                    NewCowData[cowid][newcowOwner] = 0;
                    format(NewCowData[cowid][newcowOwnerName], 64, "NULL");
                }
                else{
                    NewCowData[cowid][newcowGrowth] = 0;
                    NewCowData[cowid][newcowHungry] = 0;
                }

                PlayerGetCowMilk[playerid] = -1;
                NewCowData[cowid][newcowIsPicking] = false;

                Update_NewCowObject(cowid);
                DeletePVar(playerid, "NewCowID");

                stop PlayerHarvestMilkCowTime[playerid];
                HidePlayerProgressBar(playerid, NewProgressBar[playerid][0]);
                PlayerTextDrawHide(playerid, NewProgressText[playerid][0]);
                DestroyPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
                PlayerTextDrawDestroy(playerid, NewProgressText[playerid][0]);
                TogglePlayerControllable(playerid, 1);
            }
        }
    }
    return 1;
}

SetPlayerHarvestNewCow(playerid){
    new cowid = GetPVarInt(playerid, "NewCowID");
    if(cowid != -1 && Iter_Contains(Iter_NewCow, cowid)){
        if(!NewCowData[cowid][newcowIsPicking]){
            NewCowData[cowid][newcowIsPicking] = true;
            PlayerGetCowMilk[playerid] = cowid;
            PlayerHarvestNewCow[playerid] = true;
            ClearAnimations(playerid);
            ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
            LoadPlayerNewProgress(playerid);
            TogglePlayerControllable(playerid, 0);
            ShowPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
            SetPlayerProgressBarColour(playerid, NewProgressBar[playerid][0], 0xFFD74EAA);
            SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], 0.0);
            PlayerHarvestMilkCowTime[playerid] = repeat SetPlayerCowMilk(playerid);
        }
    }
    return 1;
}

NewCow_Nearest(playerid, flag = 1){
    foreach(new i : Iter_NewCow){
        if(flag == 1){
            if(NewCowData[i][newcowStill]) continue;
            if(IsPlayerInRangeOfPoint(playerid, 2.5, NewCowData[i][newcowPos][0], NewCowData[i][newcowPos][1], NewCowData[i][newcowPos][2])){
                return i;
            }
        }
        else if(flag == 2){
            if(!NewCowData[i][newcowStill]) continue;
            if(IsPlayerInRangeOfPoint(playerid, 2.5, NewCowData[i][newcowPos][0], NewCowData[i][newcowPos][1], NewCowData[i][newcowPos][2])){
                return i;
            }
        }
    }
	return -1;
}

SetPlayerPlaceCow(playerid, cowid){
    if(cowid != -1 && Iter_Contains(Iter_NewCow, cowid)){
        PlayerGetCowObject[playerid] = false;
        RemoveAttachedObject(playerid, 9);
        ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
        format(NewCowData[cowid][newcowOwnerName], 64, ReturnRoleplayName(playerid));
        NewCowData[cowid][newcowOwner] = PlayerData[playerid][pID];
        NewCowData[cowid][newcowGrowth] = 0;
        NewCowData[cowid][newcowStill] = true;
        Update_NewCowObject(cowid);
        NewCow_Save(cowid);
    }
    return 1;
}

Dialog:BuyCowOnFoot(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(GetMoney(playerid) < COW_PRICE) return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะซื้อวัว");
        GiveMoney(playerid, -COW_PRICE, "Buy Cow");
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เสียเงิน %s จากการซื้อวัวเรียบร้อยแล้ว", FormatNumber(COW_PRICE));
        SetPlayerAttachedObject(playerid,9,19833,1,-1.357000,0.000000,-0.569000,0.000000,88.099983,-177.600006,1.000000,1.000000,1.000000);
        PlayerGetCowObject[playerid] = true;
    }
    return 1;
}

Dialog:BuyCowOnDrive(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new vehid = GetPlayerVehicleID(playerid);
        if(vehid != INVALID_VEHICLE_ID){
            if(GetMoney(playerid) < COW_PRICE) return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะซื้อวัว");

            GiveMoney(playerid, -COW_PRICE, "Buy Cow");
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เสียเงิน %s จากการซื้อวัวเรียบร้อยแล้ว", FormatNumber(COW_PRICE));
            CarHas_CowObject[vehid] = true;
            CowObject_Vehicle[vehid] = CreateDynamicObject(19833, 0, 0, 0, 0, 0, 0);
            AttachDynamicObjectToVehicle(CowObject_Vehicle[vehid], vehid, 0.2, -1.5, -0.1, 0.0, 0.0, 150.0);
        }
    }
    return 1;
}

CMD:reusecow(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new cowid = -1;
    if((cowid = NewCow_Nearest(playerid)) != -1){
        NewCowData[cowid][newcowIsPicking] = false;
        SendClientMessageEx(playerid, -1, "คุณประสบความสำเร็จในการ Reuse วัวไอดี %d", cowid);
    }
    return 1;
}

CMD:editcow(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz;
    if(sscanf(params, "ffffff", x, y, z, rx, ry, rz)) return 1;
    AttachDynamicObjectToVehicle(CowObject_Vehicle[GetPlayerVehicleID(playerid)], GetPlayerVehicleID(playerid), x, y, z, rx, ry, rz);
    return 1;
}