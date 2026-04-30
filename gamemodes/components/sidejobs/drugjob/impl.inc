#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetDrugPlayer(playerid){
    StartPickupDrug[playerid] = 0;
    KillTimer(DrugTimer[playerid]);
    DrugTimer[playerid] = 0;
    DrugPoint[playerid] = 0;
    PlayerGetDrug[playerid] = 0;
    StartProcessDrug[playerid] = 0;
    TradeTimer[playerid] = 0;
    KillTimer(TradeTimer[playerid]);
    TradePoint[playerid] = 0;
    StartTradeMoney[playerid] = 0;
    OpenMenuCraftDrug[playerid] = 0;
    StartCraftMixedDrug[playerid] = 0;
    CraftDrugTimer[playerid] = 0;
    KillTimer(CraftDrugTimer[playerid]);
    PlayerGetDrugType[playerid] = -1;
    return 1;
}

DrugCraft_Hide(playerid){
    HidePlayerProgressBar(playerid, CraftDrugProgress[playerid][0]);
    DestroyPlayerProgressBar(playerid, CraftDrugProgress[playerid][0]);
    for(new i=0; i<7; i++){
        PlayerTextDrawHide(playerid, CraftDrug[playerid][i]);
        PlayerTextDrawDestroy(playerid, CraftDrug[playerid][i]);
    }
    CancelSelectTextDraw(playerid);
    OpenMenuCraftDrug[playerid] = 0;
    return 1;
}

ShowMenuCraftDrug(playerid){
    CraftDrugProgress[playerid][0] = CreatePlayerProgressBar(playerid, 203.000000, 360.000000, 11.000000, 208.500000, -16776961, 100.000000, 2);
    ShowPlayerProgressBar(playerid, CraftDrugProgress[playerid][0]);
    for(new i=0; i<7; i++){
        PlayerTextDrawShow(playerid, CraftDrug[playerid][i]);
    }
    new string[128];
    format(string, sizeof(string), "Pack Weed %d EA", PlayerInventory_AllCount(playerid, "Pack Weed"));
    PlayerTextDrawSetString(playerid, CraftDrug[playerid][2], string);

    format(string, sizeof(string), "Pack Cocain %d EA", PlayerInventory_AllCount(playerid, "Pack Cocain"));
    PlayerTextDrawSetString(playerid, CraftDrug[playerid][4], string);
    SelectTextDraw(playerid, 0x46F301AA);
    OpenMenuCraftDrug[playerid] = 1;
    return 1;
}

Dialog:SelectTypeMixedDrug(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        /*if(listitem == 0){
            if(PlayerInventory_AllCount(playerid, "Red Plant of Roger") < 3) return ErrorMsg(playerid, "คุณมีพืชสีแดงไม่พอ");

            SetPVarInt(playerid, "TypeMixedDrug", 1);
            StartCraftMixedDrug[playerid] = 1;
            CraftMixedDrugPoint[playerid] = 0;
            TogglePlayerControllable(playerid, 0);
            CraftDrugTimer[playerid] = SetTimerEx("CraftingDrug", 500, 0, "i", playerid);
        }*/
        if(listitem == 0){
            if(PlayerInventory_AllCount(playerid, "Pack Weed") < 20)
                return ErrorMsg(playerid, "คุณมีแพ็คกัญชาไม่พอ");
            
            if(PlayerInventory_AllCount(playerid, "Pack Cocain") < 20)
                return ErrorMsg(playerid, "คุณมีแพ็คโคเคนไม่พอ");

            SetPVarInt(playerid, "TypeMixedDrug", 2);
            StartCraftMixedDrug[playerid] = 1;
            CraftMixedDrugPoint[playerid] = 0;
            TogglePlayerControllable(playerid, 0);
            CraftDrugTimer[playerid] = SetTimerEx("CraftingDrug", 500, 0, "i", playerid);
        }
    }
    return 1;
}

forward CraftingDrug(playerid);
public CraftingDrug(playerid){
    if(LoggedIn[playerid]){
        if(OpenMenuCraftDrug[playerid] == 1 && StartCraftMixedDrug[playerid] == 1){
            if(CraftMixedDrugPoint[playerid] < 100){
                CraftMixedDrugPoint[playerid] += 1;
                SetPlayerProgressBarValue(playerid, CraftDrugProgress[playerid][0], CraftMixedDrugPoint[playerid]);
                new string[128];
                format(string, sizeof(string), "Processing: %d", CraftMixedDrugPoint[playerid]);
                PlayerTextDrawSetString(playerid, CraftDrug[playerid][0], string);
                CraftDrugTimer[playerid] = SetTimerEx("CraftingDrug", 500, 0, "i", playerid);
            }
            else if(CraftMixedDrugPoint[playerid] >= 100){
                KillTimer(CraftDrugTimer[playerid]);
                CraftDrugTimer[playerid] = 0;
                CraftMixedDrugPoint[playerid] = 0;
                StartCraftMixedDrug[playerid] = 0;

                new type = GetPVarInt(playerid, "TypeMixedDrug");

                /*if(type == 1){
                    if(PlayerInventory_AllCount(playerid, "Red Plant of Roger") < 3) return ErrorMsg(playerid, "คุณมีพืชสีแดงไม่พอ");

                    PlayerInventory_Remove(playerid, "Red Plant of Roger", 3);

                    SendClientMessage(playerid, COLOR_DARKGREEN, "|====================================================|");
                    SendClientMessage(playerid, -1, "- Red Plant of Roger - 3 ea");
                    SendClientMessage(playerid, -1, "- Mixed Drug + 1 ea");
                    SendClientMessage(playerid, COLOR_DARKGREEN, "|====================================================|");
                }*/
                if(type == 2){
                    if(PlayerInventory_AllCount(playerid, "Pack Weed") < 20)
                        return ErrorMsg(playerid, "คุณมีแพ็คกัญชาไม่พอ");
                    
                    if(PlayerInventory_AllCount(playerid, "Pack Cocain") < 20)
                        return ErrorMsg(playerid, "คุณมีแพ็คโคเคนไม่พอ");

                    PlayerInventory_Remove(playerid, "Pack Weed", 20);
                    PlayerInventory_Remove(playerid, "Pack Cocain", 20);

                    SendClientMessage(playerid, COLOR_DARKGREEN, "|====================================================|");
                    SendClientMessage(playerid, -1, "- Pack Weed - 20 ea");
                    SendClientMessage(playerid, -1, "- Pack Cocain - 20 ea");
                    SendClientMessage(playerid, -1, "- Mixed Drug + 1 ea");
                    SendClientMessage(playerid, COLOR_DARKGREEN, "|====================================================|");
                }

                new string[128];
                format(string, sizeof(string), "Pack Weed %d EA", PlayerInventory_AllCount(playerid, "Pack Weed"));
                PlayerTextDrawSetString(playerid, CraftDrug[playerid][2], string);

                format(string, sizeof(string), "Pack Cocain %d EA", PlayerInventory_AllCount(playerid, "Pack Cocain"));
                PlayerTextDrawSetString(playerid, CraftDrug[playerid][4], string);

                PlayerTextDrawHide(playerid, CraftDrug[playerid][2]);
                PlayerTextDrawHide(playerid, CraftDrug[playerid][4]);

                PlayerTextDrawShow(playerid, CraftDrug[playerid][2]);
                PlayerTextDrawShow(playerid, CraftDrug[playerid][4]);

                SetPlayerProgressBarValue(playerid, CraftDrugProgress[playerid][0], CraftMixedDrugPoint[playerid]);
                format(string, sizeof(string), "Processing: %d", CraftMixedDrugPoint[playerid]);
                PlayerTextDrawSetString(playerid, CraftDrug[playerid][0], string);

                new id = PlayerInventory_AddItem(playerid, "Mixed Drug", 1577, 1);

                if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            }
        }
    }
    return 1;
}

Dialog:UseMixedDrug(playerid, response, listitem, inputtext[]){
    if(!response) return 0;
    if(response){
        new message[128];

        new itemid = GetPVarInt(playerid, "itemMixedid");
        if(itemid != -1){
            if(isnull(inputtext)){
                format(message, sizeof(message), "* คุณจำเป็นต้องกรอกจำนวน *\nคุณมี Mixed Drug จำนวน: %d\nกรอกจำนวนที่คุณต้องการจะใช้:", PlayerInventory_CountEx(playerid, itemid));
                return Dialog_ShowEasy(playerid, UseMixedDrug, DIALOG_STYLE_INPUT, "กรอกจำนวนยาที่จะใช้", message, "ตกลง", "ยกเลิก");
            }

            new amount = strval(inputtext);
            if(amount > PlayerInventory_CountEx(playerid, itemid)){
                format(message, sizeof(message), "* คุณมีจำนวนยาไม่มากพอ *\nคุณมี Mixed Drug จำนวน: %d\nกรอกจำนวนที่คุณต้องการจะใช้:", PlayerInventory_CountEx(playerid, itemid));
                return Dialog_ShowEasy(playerid, UseMixedDrug, DIALOG_STYLE_INPUT, "กรอกจำนวนยาที่จะใช้", message, "ตกลง", "ยกเลิก");
            }

            if(amount == 0){
                format(message, sizeof(message), "* คุณจำเป็นต้องกรอกจำนวน *\nคุณมี Mixed Drug จำนวน: %d\nกรอกจำนวนที่คุณต้องการจะใช้:", PlayerInventory_CountEx(playerid, itemid));
                return Dialog_ShowEasy(playerid, UseMixedDrug, DIALOG_STYLE_INPUT, "กรอกจำนวนยาที่จะใช้", message, "ตกลง", "ยกเลิก");
            }

            new Float:am;
            GetPlayerArmour(playerid, am);
            new Float:amplus = 25*amount;
            if(am + amplus > 100) return ErrorMsg(playerid, "คุณจะใช้ยาเพื่อเพิ่มเกราะเกิน 100 ไม่ได้");
            PlayerInventory_RemoveEx(playerid, itemid, amount);
            SetPlayerArmour(playerid, am+amplus);
            DeletePVar(playerid, "itemMixedid");
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้รับเกราะ +%.0f", amplus);
        }
    }
    return 1;
}

StartTradeRedMoney(playerid){
    if(PlayerData[playerid][pRedMoney] <= 0)
        return ErrorMsg(playerid, "คุณไม่มีเงินแดง");

    if(PlayerData[playerid][pLevel] < 2)
        return ErrorMsg(playerid, "คุณต้องมีเลเวล 2 ขึ้นไป");

    SendClientMessage(playerid, COLOR_RED, "[คำเตือน]: คุณสามารถกด 'N' เพื่อยกเลิกการการแลกเงินได้");
    TogglePlayerControllable(playerid, 0);
    //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0xC1FF00AA, 100.000000, 0);
    CreatePlayerProgressbar_Job(playerid, 0xC1FF00AA);
    StartTradeMoney[playerid] = 1;
    TradeTimer[playerid] = SetTimerEx("TradeRedMoney", 1000, 0, "ii", playerid);
    return 1;
}

forward TradeRedMoney(playerid);
public TradeRedMoney(playerid){
    new string[128];
    if(LoggedIn[playerid]){
        if(StartTradeMoney[playerid] == 1 && TradePoint[playerid] < 100){
            TradePoint[playerid] += 1;
            SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], TradePoint[playerid]);
            format(string,sizeof(string),"Trading... (%d)", TradePoint[playerid]);
            PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
            //GameTextForPlayer(playerid, string, 1500, 3);
            TogglePlayerControllable(playerid, 0);
            ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
            TradeTimer[playerid] = SetTimerEx("TradeRedMoney", 1000, 0, "ii", playerid);
        }
        else if(StartTradeMoney[playerid] == 1 && TradePoint[playerid] >= 100){
            StartTradeMoney[playerid] = 0;
            TradePoint[playerid] = 0;
            KillTimer(TradeTimer[playerid]);
            TradeTimer[playerid] = 0;
            TogglePlayerControllable(playerid, 1);
            ClearAnimations(playerid);
            DestroyPlayerProgressbar_Job(playerid);

            new rate = (PlayerData[playerid][pRedMoney] * 3) / 2;
            GiveMoney(playerid, rate, "change red to green money");
            PlayerData[playerid][pRedMoney] = 0;
            SendClientMessageEx(playerid, COLOR_GREEN, "- คุณได้ทำการแลกเงินแดงและได้รับเงินเขียวจำนวน %s", FormatNumber(rate));
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(!LoggedIn[playerid]) return 1;
    if(newkeys & KEY_NO){
        new string[128];
        if(PlayerStartProgressbar[playerid] && StartPickupDrug[playerid] && DrugData[PlayerGetDrugType[playerid]][drugType] == 5){
            if(PlayerProgressbar_CheckResult(playerid) == 1){
                new number = jdzrandom(1, 3);
                new id = PlayerInventory_AddItem(playerid, "Wire", 19087, number);
                if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

                DrugData[PlayerGetDrugType[playerid]][drugAmount] -= number;
                if(DrugData[PlayerGetDrugType[playerid]][drugAmount] <= 0) DrugData[PlayerGetDrugType[playerid]][drugAmount] = 0;

                format(string, sizeof string, "คุณได้รับ 'Wire (สายไฟ) + %d", number);
                Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การได้รับ", string, "ตกลง", "");

                SetPlayerProgressbarV2_Hide(playerid);
                PlayerProgressbar_ResetMaxPoint(playerid);
                ResetPlayerProgressbarV2(playerid);

                StartPickupDrug[playerid] = false;
                PlayerGetDrug[playerid] = 0;
                StartProcessDrug[playerid] = false;
                PlayerGetDrugType[playerid] = -1;
                ClearAnimations(playerid);
            }
            else if(PlayerProgressbar_CheckResult(playerid) == 0){
                PlayerMissPoint[playerid]++;
                format(string, sizeof string, "~r~~h~Fail %d/%d", PlayerMissPoint[playerid], PlayerProgressbar_GetMaxPoint(playerid));
                GameTextForPlayer(playerid, string, 2000, 5);
                if(PlayerMissPoint[playerid] < PlayerProgressbar_GetMaxPoint(playerid)){
                    PlayerGetPoint[playerid] = 0.0;
                    SetPlayerProgressBarValue(playerid, ProgressBarV2_Progressbar[playerid][0], 0.0);
                    new number = jdzrandom(20, 80);
                    SetPlayerProgressbar_UpdateP(playerid, number);
                }
                else{
                    SetPlayerProgressbarV2_Hide(playerid);
                    PlayerProgressbar_ResetMaxPoint(playerid);
                    ResetPlayerProgressbarV2(playerid);

                    StartPickupDrug[playerid] = false;
                    PlayerGetDrug[playerid] = 0;
                    StartProcessDrug[playerid] = false;
                    ClearAnimations(playerid);

                    new number = jdzrandom(1, 2);
                    if(number == 1){
                        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "พลาด", "คุณได้พลาดการขโมยสายไฟไปแล้ว, โปรดลองใหม่อีกครั้ง", "ตกลง", "");
                    }   
                    else if(number == 2){
                        SendGroupMessageEx(GROUP_POLICE, COLOR_RADIO, "911 CALL (ผู้แจ้งความ: พลเมืองดี) (%s)", GetPlayerLocation(playerid));
                        SendGroupMessageEx(GROUP_POLICE, COLOR_RADIO, "รายละเอียด: พบเจอคนกำลังขโมยสายไฟ ( ผู้ต้องสงสัย: %s(%d) )", ReturnRoleplayName(playerid), playerid);
                        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "พลาด", "[!] คนแถวระแวกที่คุณอยู่โทรแจ้งเจ้าหน้าที่ตำรวจ หนีเร็ว!!!!\nคุณได้พลาดการขโมยสายไฟไปแล้ว, โปรดลองใหม่อีกครั้ง", "ตกลง", "");
                    }
                }
            }
        }
    }
    return 1;
}

timer ProgressbarV2_UpdateWire[10](playerid){
    if(PlayerStartProgressbar[playerid]){
        new string[128];
        PlayerGetPoint[playerid] = GetPlayerProgressBarValue(playerid, ProgressBarV2_Progressbar[playerid][0]);
        if(PlayerGetPoint[playerid] < 100.0){
            PlayerGetPoint[playerid] += 1.0;
            SetPlayerProgressBarValue(playerid, ProgressBarV2_Progressbar[playerid][0], PlayerGetPoint[playerid]);
        }
        else{
            PlayerMissPoint[playerid]++;
            format(string, sizeof string, "~r~~h~Fail %d/%d", PlayerMissPoint[playerid], PlayerProgressbar_GetMaxPoint(playerid));
            GameTextForPlayer(playerid, string, 2000, 5);
            if(PlayerMissPoint[playerid] < PlayerProgressbar_GetMaxPoint(playerid)){
                PlayerGetPoint[playerid] = 0.0;
                SetPlayerProgressBarValue(playerid, ProgressBarV2_Progressbar[playerid][0], 0.0);
                new number = jdzrandom(20, 80);
                SetPlayerProgressbar_UpdateP(playerid, number);
            }
            else{
                SetPlayerProgressbarV2_Hide(playerid);
                PlayerProgressbar_ResetMaxPoint(playerid);
                ResetPlayerProgressbarV2(playerid);

                StartPickupDrug[playerid] = false;
                PlayerGetDrug[playerid] = 0;
                StartProcessDrug[playerid] = false;
                ClearAnimations(playerid);

                new number = jdzrandom(1, 2);
                if(number == 1){
                    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "พลาด", "คุณได้พลาดการขโมยสายไฟไปแล้ว, โปรดลองใหม่อีกครั้ง", "ตกลง", "");
                }   
                else if(number == 2){
                    SendGroupMessageEx(GROUP_POLICE, COLOR_RADIO, "911 CALL (ผู้แจ้งความ: พลเมืองดี) (%s)", GetPlayerLocation(playerid));
                    SendGroupMessageEx(GROUP_POLICE, COLOR_RADIO, "รายละเอียด: พบเจอคนกำลังขโมยสายไฟ ( ผู้ต้องสงสัย: %s(%d) )", ReturnRoleplayName(playerid), playerid);
                    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "พลาด", "[!] คนแถวระแวกที่คุณอยู่โทรแจ้งเจ้าหน้าที่ตำรวจ หนีเร็ว!!!!\nคุณได้พลาดการขโมยสายไฟไปแล้ว, โปรดลองใหม่อีกครั้ง", "ตกลง", "");
                }
            }
        }
    }   
}

StartPickupWire(playerid, drugid){
    stop Progressbar_Timer[playerid];
    StartPickupDrug[playerid] = true;
    PlayerGetDrugType[playerid] = drugid;
    PlayerProgressbar_SetMaxPoint(playerid, 3);
    SetPlayerProgressbarV2_Color(playerid, 0xFFF4A2FF);
    SetPlayerProgressbarV2(playerid, 50);
    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 1, 0, 1);
    SendClientMessage(playerid, COLOR_YELLOW, "| [แนะนำ] กดปุ่ม 'N' เพื่อหยุดเช็คพ้อย");
    Progressbar_Timer[playerid] = repeat ProgressbarV2_UpdateWire(playerid);
    return 1;
}

StartPickingUpDrug(playerid, drugid){
    StartPickupDrug[playerid] = true;
    //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0xC1FF00AA, 100.000000, 0);
    CreatePlayerProgressbar_Job(playerid, 0xC1FF00AA);
    TogglePlayerControllable(playerid, 0);
    DrugTimer[playerid] = SetTimerEx("PickingDrug", 1000, 0, "ii", playerid, drugid);
    return 1;
}

forward PickingDrug(playerid, drugid);
public PickingDrug(playerid, drugid){
    new string[128];
    if(LoggedIn[playerid]){
        if(StartPickupDrug[playerid] == 1 && DrugPoint[playerid] < 100 && PlayerGetDrug[playerid] == 0){
            DrugPoint[playerid] += 2;
            SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], DrugPoint[playerid]);
            format(string,sizeof(string),"Picking... (%d)", DrugPoint[playerid]);
            PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
            //GameTextForPlayer(playerid, string, 1500, 3);
            Streamer_Update(playerid);
            TogglePlayerControllable(playerid, 0);
            ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
            DrugTimer[playerid] = SetTimerEx("PickingDrug", 1000, 0, "ii", playerid, drugid);
        }
        else if(StartPickupDrug[playerid] == 1 && DrugPoint[playerid] >= 100 && PlayerGetDrug[playerid] == 0){
            if(DrugData[drugid][drugAmount] >= 10){
                StartPickupDrug[playerid] = 0;
                DrugPoint[playerid] = 0;
                KillTimer(DrugTimer[playerid]);
                DrugTimer[playerid] = 0;
                TogglePlayerControllable(playerid, 1);
                ClearAnimations(playerid);
                DestroyPlayerProgressbar_Job(playerid);

                DrugData[drugid][drugAmount] -= 10;

                Drug_RenderRefresh(drugid);
                //Drug_Refresh(drugid);
                Drug_Save(drugid);

                if(DrugData[drugid][drugType] == 1){
                    SetPlayerAttachedObject(playerid,8,1578,1,0.027000,-0.034999,-0.014000,96.600013,-13.300009,0.000000,1.000000,1.000000,1.000000);
                    SendClientMessage(playerid, COLOR_YELLOW, "[ระบบ]: ไปยังจุดต่อไปเพื่อ Process กัญชา");
                    PlayerGetDrug[playerid] = 1;
                }
                if(DrugData[drugid][drugType] == 2){
                    SetPlayerAttachedObject(playerid,8,1579,1,0.027000,-0.034999,-0.014000,96.600013,-13.300009,0.000000,1.000000,1.000000,1.000000);
                    SendClientMessage(playerid, COLOR_YELLOW, "[ระบบ]: ไปยังจุดต่อไปเพื่อ Process โคเคน");
                    PlayerGetDrug[playerid] = 2;
                }
                if(DrugData[drugid][drugType] == 4){
                    SetPlayerAttachedObject(playerid,8,1279,1,0.052999,-0.161999,-0.073000,0.000000,42.499996,0.000000,0.510000,0.503000,0.657999);
                    SendClientMessage(playerid, COLOR_YELLOW, "[ระบบ]: ไปยังจุดต่อไปเพื่อ Process ปูนขาว");
                    PlayerGetDrug[playerid] = 4;
                }
            }
            else if(DrugData[drugid][drugAmount] < 10){
                StartPickupDrug[playerid] = 0;
                DrugPoint[playerid] = 0;
                KillTimer(DrugTimer[playerid]);
                DrugTimer[playerid] = 0;
                TogglePlayerControllable(playerid, 1);
                ClearAnimations(playerid);
                DestroyPlayerProgressbar_Job(playerid);
                PlayerGetDrug[playerid] = 0;
                return ErrorMsg(playerid, "ยาชนิดนี้มีไม่พอให้คุณเก็บ");
            }
        }
    }
    return 1;
}

StartProcessingDrug(playerid, drugid){
    StartProcessDrug[playerid] = 1;
    //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0xC1FF00AA, 100.000000, 0);
    CreatePlayerProgressbar_Job(playerid, 0xC1FF00AA);
    TogglePlayerControllable(playerid, 0);
    DrugTimer[playerid] = SetTimerEx("ProcessingDrug", 1000, 0, "ii", playerid, drugid);
    return 1;
}

forward ProcessingDrug(playerid, drugid);
public ProcessingDrug(playerid, drugid){
    new string[128];
    if(LoggedIn[playerid]){
        if(DrugPoint[playerid] < 100 && PlayerGetDrug[playerid] != 0 && StartProcessDrug[playerid] != 0){
            DrugPoint[playerid] += 1;
            SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], DrugPoint[playerid]);
            format(string,sizeof(string),"Processing... (%d)", DrugPoint[playerid]);
            PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
            //GameTextForPlayer(playerid, string, 1500, 3);
            Streamer_Update(playerid);
            TogglePlayerControllable(playerid, 0);
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
            DrugTimer[playerid] = SetTimerEx("ProcessingDrug", 1000, 0, "ii", playerid, drugid);
        }
        else if(DrugPoint[playerid] >= 100 && PlayerGetDrug[playerid] != 0 && StartProcessDrug[playerid] != 0){
            PlayerGetDrug[playerid] = 0;
            StartProcessDrug[playerid] = 0;
            DrugPoint[playerid] = 0;
            KillTimer(DrugTimer[playerid]);
            DrugTimer[playerid] = 0;
            TogglePlayerControllable(playerid, 1);
            ClearAnimations(playerid);
            DestroyPlayerProgressbar_Job(playerid);

            if(DrugData[drugid][drugType] == 1){
                SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้รับ 'Pack Weed' + 5");
                new id = PlayerInventory_AddItem(playerid, "Pack Weed", 1578, 5);

                if (id == -1)
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

                RemoveAttachedObject(playerid, 8);
            }

            if(DrugData[drugid][drugType] == 2){
                SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้รับ 'Pack Cocain' + 5");
                new id = PlayerInventory_AddItem(playerid, "Pack Cocain", 1579, 5);

                if (id == -1)
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

                RemoveAttachedObject(playerid, 8);
            }

            if(DrugData[drugid][drugType] == 4){
                SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้รับ 'Pack Cement' + 5");
                new id = PlayerInventory_AddItem(playerid, "Pack Cement", 1576, 5);

                if (id == -1)
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

                RemoveAttachedObject(playerid, 8);
            }
        }
    }
    return 1;
}

forward Drug_Load();
public Drug_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_DRUGPOINT)
	{
	    DrugData[i][drugEx] = true;
	    cache_get_value_name_int(i, "drugID", DrugData[i][drugID]);
        cache_get_value_name_int(i, "drugType", DrugData[i][drugType]);
	    cache_get_value_name_float(i, "drugPosX", DrugData[i][drugPos][0]);
	    cache_get_value_name_float(i, "drugPosY", DrugData[i][drugPos][1]);
	    cache_get_value_name_float(i, "drugPosZ", DrugData[i][drugPos][2]);
        cache_get_value_name_float(i, "drugProcessX", DrugData[i][drugProcessPos][0]);
	    cache_get_value_name_float(i, "drugProcessY", DrugData[i][drugProcessPos][1]);
	    cache_get_value_name_float(i, "drugProcessZ", DrugData[i][drugProcessPos][2]);
        cache_get_value_name_int(i, "drugWorld", DrugData[i][drugWorld]);
        cache_get_value_name_int(i, "drugInt", DrugData[i][drugInt]);
        cache_get_value_name_int(i, "drugProcessWorld", DrugData[i][drugProcessWorld]);
        cache_get_value_name_int(i, "drugProcessInt", DrugData[i][drugProcessInt]);
	    cache_get_value_name_int(i, "drugAmount", DrugData[i][drugAmount]);
        cache_get_value_name_int(i, "drugPrice", DrugData[i][drugPrice]);

        cache_get_value_name_float(i, "drugDeliverX", DrugData[i][drugDeliverPos][0]);
	    cache_get_value_name_float(i, "drugDeliverY", DrugData[i][drugDeliverPos][1]);
	    cache_get_value_name_float(i, "drugDeliverZ", DrugData[i][drugDeliverPos][2]);
        cache_get_value_name_int(i, "drugDeliverWorld", DrugData[i][drugDeliverWorld]);
        cache_get_value_name_int(i, "drugDeliverInt", DrugData[i][drugDeliverInt]);

        drug_count++;

        DrugData[i][drugAmount] = 200;
        Drug_RenderRefresh(i);
 	    //Drug_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d DrugPoint Successfully ))", drug_count);
	return 1;
}


Drug_RenderRefresh(drugid){
    if (drugid != -1 && DrugData[drugid][drugEx]){

        for(new i=0; i<3; i++){
            if (IsValidDynamic3DTextLabel(DrugData[drugid][drugText3D][i]) && DrugData[drugid][drugText3D][i])
                DestroyDynamic3DTextLabel(DrugData[drugid][drugText3D][i]);
        }

        new string[128];
        new string2[128];
        if(DrugData[drugid][drugType] == 1){
            format(string, sizeof(string), "[จุดเก็บกัญชา]\nกด 'Y' เพื่อเก็บ\nจำนวน: %d", DrugData[drugid][drugAmount]);
            DrugData[drugid][drugText3D][0] = CreateDynamic3DTextLabel(string, 0xFFF000FF, DrugData[drugid][drugPos][0], DrugData[drugid][drugPos][1], DrugData[drugid][drugPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugWorld], DrugData[drugid][drugInt]);

            format(string2, sizeof(string2), "[จุดแพ็คกัญชา]\nกด 'Y' เพื่อแพ็คกัญชา");
            DrugData[drugid][drugText3D][1] = CreateDynamic3DTextLabel(string2, 0xFFF000FF, DrugData[drugid][drugProcessPos][0], DrugData[drugid][drugProcessPos][1], DrugData[drugid][drugProcessPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugProcessWorld], DrugData[drugid][drugProcessInt]);

            format(string2, sizeof(string2), "[ขายแพ็คกัญชา]\nกด 'Y' เพื่อเก็บ\nกด 'Y' เพื่อขายกัญชา");
            DrugData[drugid][drugText3D][2] = CreateDynamic3DTextLabel(string2, 0xFFF000FF, DrugData[drugid][drugDeliverPos][0], DrugData[drugid][drugDeliverPos][1], DrugData[drugid][drugDeliverPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugDeliverWorld], DrugData[drugid][drugDeliverInt]);
        }
        else if(DrugData[drugid][drugType] == 2){
            format(string, sizeof(string), "[จุดเก็บโคเคน]\nกด 'Y' เพื่อเก็บ\nจำนวน: %d", DrugData[drugid][drugAmount]);
            DrugData[drugid][drugText3D][0] = CreateDynamic3DTextLabel(string, 0xFFF000FF, DrugData[drugid][drugPos][0], DrugData[drugid][drugPos][1], DrugData[drugid][drugPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugWorld], DrugData[drugid][drugInt]);
        
            format(string2, sizeof(string2), "[จุดแพ็คโคเคน]\nกด 'Y' เพื่อแพ็คโคเคน");
            DrugData[drugid][drugText3D][1] = CreateDynamic3DTextLabel(string2, 0xFFF000FF, DrugData[drugid][drugProcessPos][0], DrugData[drugid][drugProcessPos][1], DrugData[drugid][drugProcessPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugProcessWorld], DrugData[drugid][drugProcessInt]);

            format(string2, sizeof(string2), "[ขายแพ็คโคเคน]\nกด 'Y' เพื่อขายโคเคน");
            DrugData[drugid][drugText3D][2] = CreateDynamic3DTextLabel(string2, 0xFFF000FF, DrugData[drugid][drugDeliverPos][0], DrugData[drugid][drugDeliverPos][1], DrugData[drugid][drugDeliverPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugDeliverWorld], DrugData[drugid][drugDeliverInt]);
        }
        else if(DrugData[drugid][drugType] == 3){
            format(string, sizeof(string), "[จุดสำหรับผลิตยาผสม]\nกด 'Y' เพื่อใช้งาน\n* ยาผสมสามารถใช้เพิ่มเกราะได้ *");
            DrugData[drugid][drugText3D][0] = CreateDynamic3DTextLabel(string, 0xFFF000FF, DrugData[drugid][drugPos][0], DrugData[drugid][drugPos][1], DrugData[drugid][drugPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugWorld], DrugData[drugid][drugInt]);
        }
        else if(DrugData[drugid][drugType] == 4){
            format(string, sizeof(string), "[จุดจกปูน]\nกด 'Y' เพื่อเก็บ\nจำนวนปูนที่จกได้: %d", DrugData[drugid][drugAmount]);
            DrugData[drugid][drugText3D][0] = CreateDynamic3DTextLabel(string, 0xFFF000FF, DrugData[drugid][drugPos][0], DrugData[drugid][drugPos][1], DrugData[drugid][drugPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugWorld], DrugData[drugid][drugInt]);
            
            format(string2, sizeof(string2), "[จุดแพ็คปูนขาว]\nกด 'Y' เพื่อแพ็คปูน");
            DrugData[drugid][drugText3D][1] = CreateDynamic3DTextLabel(string2, 0xFFF000FF, DrugData[drugid][drugProcessPos][0], DrugData[drugid][drugProcessPos][1], DrugData[drugid][drugProcessPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugProcessWorld], DrugData[drugid][drugProcessInt]);
           
            format(string2, sizeof(string2), "[จุดขายแพ็คปูน]\nกด 'Y' เพื่อขายปูน");
            DrugData[drugid][drugText3D][2] = CreateDynamic3DTextLabel(string2, 0xFFF000FF, DrugData[drugid][drugDeliverPos][0], DrugData[drugid][drugDeliverPos][1], DrugData[drugid][drugDeliverPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugDeliverWorld], DrugData[drugid][drugDeliverInt]);
        }
        else if(DrugData[drugid][drugType] == 5){
            format(string, sizeof(string), "[จุดขโมยสายไฟ]\nกด 'Y' เพื่อเริ่มทำการขโมยสายไฟ\nจำนวนสายไฟที่ขโมยได้: %d", DrugData[drugid][drugAmount]);
            DrugData[drugid][drugText3D][0] = CreateDynamic3DTextLabel(string, 0xFFF000FF, DrugData[drugid][drugPos][0], DrugData[drugid][drugPos][1], DrugData[drugid][drugPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugWorld], DrugData[drugid][drugInt]);
            
            format(string2, sizeof(string2), "[จุดขโมยสายไฟ]\nกด 'Y' เพื่อขายสายไฟ");
            DrugData[drugid][drugText3D][2] = CreateDynamic3DTextLabel(string2, 0xFFF000FF, DrugData[drugid][drugDeliverPos][0], DrugData[drugid][drugDeliverPos][1], DrugData[drugid][drugDeliverPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DrugData[drugid][drugDeliverWorld], DrugData[drugid][drugDeliverInt]);
        }
    }
    return 1;
}

/*Drug_Refresh(drugid){
    if (drugid != -1 && DrugData[drugid][drugEx]){
        new string[128];
        new string2[128];
        new string3[128];
        if(DrugData[drugid][drugType] == 1){
            format(string, sizeof(string), "[จุดเก็บกัญชา]\nกด 'Y' เพื่อเก็บ\nจำนวน: %d", DrugData[drugid][drugAmount]);
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][0], 0xFFF000FF, string);
            format(string2, sizeof(string2), "[จุดแพ็คกัญชา]\nกด 'Y' เพื่อแพ็คกัญชา");
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][1], 0xFFF000FF, string2);
            format(string3, sizeof(string3), "[ขายแพ็คกัญชา]\nกด 'Y' เพื่อเก็บ\nกด 'Y' เพื่อขายกัญชา");
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][2], 0xFFF000FF, string3);
        }
        else if(DrugData[drugid][drugType] == 2){
            format(string, sizeof(string), "[จุดเก็บโคเคน]\nกด 'Y' เพื่อเก็บ\nจำนวน: %d", DrugData[drugid][drugAmount]);
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][0], 0xFFF000FF, string);
            format(string2, sizeof(string2), "[จุดแพ็คโคเคน]\nกด 'Y' เพื่อแพ็คโคเคน");
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][1], 0xFFF000FF, string2);
            format(string3, sizeof(string3), "[ขายแพ็คโคเคน]\nกด 'Y' เพื่อขายโคเคน");
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][2], 0xFFF000FF, string3);
        }
        else if(DrugData[drugid][drugType] == 3){
            format(string, sizeof(string), "[จุดสำหรับผลิตยาผสม]\nกด 'Y' เพื่อใช้งาน\n* ยาผสมสามารถใช้เพิ่มเกราะได้ *");
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][1], 0xFFF000FF, string);
        }
        else if(DrugData[drugid][drugType] == 4){
            format(string, sizeof(string), "[จุดจกปูน]\nกด 'Y' เพื่อเก็บ\nจำนวนปูนที่จกได้: %d", DrugData[drugid][drugAmount]);
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][0], 0xFFF000FF, string);
            format(string2, sizeof(string2), "[จุดแพ็คปูนขาว]\nกด 'Y' เพื่อแพ็คปูน");
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][1], 0xFFF000FF, string2);
            format(string3, sizeof(string3), "[จุดขายแพ็คปูน]\nกด 'Y' เพื่อขายปูน");
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][2], 0xFFF000FF, string3);
        }
        else if(DrugData[drugid][drugType] == 5){
            format(string, sizeof(string), "[จุดขโมยสายไฟ]\nกด 'Y' เพื่อเริ่มทำการขโมยสายไฟ\nจำนวนสายไฟที่ขโมยได้: %d", DrugData[drugid][drugAmount]);
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][0], 0xFFF000FF, string);
            format(string3, sizeof(string3), "[จุดขโมยสายไฟ]\nกด 'Y' เพื่อขายสายไฟ");
            UpdateDynamic3DTextLabelText(DrugData[drugid][drugText3D][2], 0xFFF000FF, string3);
        }
    }
    return 1;
}*/

Drug_GetName(type)
{
	new
	    str[32];

	switch (type)
	{
		case 1: str = "กัญชา";
        case 2: str = "โคเคน";
        case 3: str = "ยาผสม";
        case 4: str = "จกปูน";
        case 5: str = "ขโมยสายไฟ";
	    default: str = "ผิดพลาด";
	}
	return str;
}

Drug_Nearest(playerid, Float:radius = 2.0)
{
    for (new i = 0; i != MAX_DRUGPOINT; i ++) if (DrugData[i][drugEx] && IsPlayerInRangeOfPoint(playerid, radius, DrugData[i][drugPos][0], DrugData[i][drugPos][1], DrugData[i][drugPos][2]) && GetPlayerInterior(playerid) == DrugData[i][drugInt] && GetPlayerVirtualWorld(playerid) == DrugData[i][drugWorld]) {
		return i;
	}
	return -1;
}

Drug_DeliverNearest(playerid, Float:radius = 1.0)
{
    for (new i = 0; i != MAX_DRUGPOINT; i ++) if (DrugData[i][drugEx] && IsPlayerInRangeOfPoint(playerid, radius, DrugData[i][drugDeliverPos][0], DrugData[i][drugDeliverPos][1], DrugData[i][drugDeliverPos][2]) && GetPlayerInterior(playerid) == DrugData[i][drugDeliverInt] && GetPlayerVirtualWorld(playerid) == DrugData[i][drugDeliverWorld]) {
		return i;
	}
	return -1;
}

Drug_ProcessNearest(playerid, Float:radius = 2.0)
{
    for (new i = 0; i != MAX_DRUGPOINT; i ++) if (DrugData[i][drugEx] && IsPlayerInRangeOfPoint(playerid, radius, DrugData[i][drugProcessPos][0], DrugData[i][drugProcessPos][1], DrugData[i][drugProcessPos][2]) && GetPlayerInterior(playerid) == DrugData[i][drugProcessInt] && GetPlayerVirtualWorld(playerid) == DrugData[i][drugProcessWorld]) {
		return i;
	}
	return -1;
}

Drug_Create(playerid, type){
    new Float:x, Float:y, Float:z;
    if (GetPlayerPos(playerid, x, y, z)){
        for (new i = 0; i != MAX_DRUGPOINT; i ++) if(!DrugData[i][drugEx]){
            DrugData[i][drugEx] = true;
            DrugData[i][drugType] = type;
            DrugData[i][drugPos][0] = x;
            DrugData[i][drugPos][1] = y;
            DrugData[i][drugPos][2] = z;

            DrugData[i][drugAmount] = 200;
            
            DrugData[i][drugProcessPos][0] = 0.0;
            DrugData[i][drugProcessPos][1] = 0.0;
            DrugData[i][drugProcessPos][2] = 0.0;

            DrugData[i][drugInt] = GetPlayerInterior(playerid);
            DrugData[i][drugWorld] = GetPlayerVirtualWorld(playerid);

            DrugData[i][drugProcessInt] = 0;
            DrugData[i][drugProcessWorld] = 0;

            Drug_RenderRefresh(i);
            //Drug_Refresh(i);
            mysql_tquery(dbCon, "INSERT INTO `drugpoints` (`drugInt`) VALUES(0)", "OnDrugCreated", "d", i);
            return i;
        }
    }
    return -1;
}

forward OnDrugCreated(drugid);
public OnDrugCreated(drugid)
{
	if (drugid == -1 || !DrugData[drugid][drugEx])
	    return 0;

	DrugData[drugid][drugID] = cache_insert_id();
	Drug_Save(drugid);

	return 1;
}

Drug_Save(drugid){
    new
	    query[1536];

	format(query, sizeof(query), "UPDATE `drugpoints` SET `drugType` = '%d', `drugPosX` = '%.4f', `drugPosY` = '%.4f', `drugPosZ` = '%.4f', `drugWorld` = '%d', `drugInt` = '%d', `drugProcessX` = '%.4f', `drugProcessY` = '%.4f', `drugProcessZ` = '%.4f', `drugProcessInt` = '%d', `drugProcessWorld` = '%d', `drugPrice` = '%d'",
		DrugData[drugid][drugType],
		DrugData[drugid][drugPos][0],
	    DrugData[drugid][drugPos][1],
	    DrugData[drugid][drugPos][2],
        DrugData[drugid][drugWorld],
	    DrugData[drugid][drugInt],
	    DrugData[drugid][drugProcessPos][0],
	    DrugData[drugid][drugProcessPos][1],
	    DrugData[drugid][drugProcessPos][2],
        DrugData[drugid][drugProcessInt],
	    DrugData[drugid][drugProcessWorld],
        DrugData[drugid][drugPrice]
	);

    format(query, sizeof(query), "%s, `drugDeliverX` = '%.4f', `drugDeliverY` = '%.4f', `drugDeliverZ` = '%.4f', `drugDeliverWorld` = '%d', `drugDeliverInt` = '%d' WHERE `drugID` = '%d'",
		query,
		DrugData[drugid][drugDeliverPos][0],
	    DrugData[drugid][drugDeliverPos][1],
	    DrugData[drugid][drugDeliverPos][2],
	    DrugData[drugid][drugDeliverWorld],
	    DrugData[drugid][drugDeliverInt],
	    DrugData[drugid][drugID]
	);
	return mysql_tquery(dbCon, query);
}

Drug_Delete(drugid){
    if (drugid != -1 && DrugData[drugid][drugEx])
	{
	    new
	        string[64];

        drug_count--;

		format(string, sizeof(string), "DELETE FROM `drugpoints` WHERE `drugID` = '%d'", DrugData[drugid][drugID]);
		mysql_tquery(dbCon, string);

        for(new i=0; i<3; i++){
            if (IsValidDynamic3DTextLabel(DrugData[drugid][drugText3D][i]))
                DestroyDynamic3DTextLabel(DrugData[drugid][drugText3D][i]);
        }

		DrugData[drugid][drugEx] = false;
		DrugData[drugid][drugType] = 0;
	    DrugData[drugid][drugID] = 0;
	}
    return 1;
}

CMD:drugcmds(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[DRUGCMDS]: /makedrug, /removedrug, /editdrug, /gotodrug, /gotodrugprocess, /gotodrugdeliver, /redrug");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

CMD:gotodrug(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	new
		id;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/gotodrug [drug ID]");

	if ((id < 0 || id >= MAX_DRUGPOINT) || !DrugData[id][drugEx])
		return SendClientMessage(playerid, -1, "คุณระบุ Drug ID ไม่ถูกต้อง");

	SetPlayerPosEx(playerid, DrugData[id][drugPos][0], DrugData[id][drugPos][1], DrugData[id][drugPos][2], DrugData[id][drugInt], DrugData[id][drugWorld]);
	SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ Drug ID: %d", id);
	return 1;
}

CMD:gotodrugprocess(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	new
		id;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/gotodrugprocess [drug ID]");

	if ((id < 0 || id >= MAX_DRUGPOINT) || !DrugData[id][drugEx])
		return SendClientMessage(playerid, -1, "คุณระบุ Drug ID ไม่ถูกต้อง");

	SetPlayerPosEx(playerid, DrugData[id][drugProcessPos][0], DrugData[id][drugProcessPos][1], DrugData[id][drugProcessPos][2], DrugData[id][drugProcessInt], DrugData[id][drugProcessWorld]);
	SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ Process Drug ID: %d", id);
	return 1;
}

CMD:gotodrugdeliver(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	new
		id;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/gotodrugdeliver [drug ID]");

	if ((id < 0 || id >= MAX_DRUGPOINT) || !DrugData[id][drugEx])
		return SendClientMessage(playerid, -1, "คุณระบุ Drug ID ไม่ถูกต้อง");

	SetPlayerPosEx(playerid, DrugData[id][drugDeliverPos][0], DrugData[id][drugDeliverPos][1], DrugData[id][drugDeliverPos][2], DrugData[id][drugDeliverInt], DrugData[id][drugDeliverWorld]);
	SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ Deliver Drug ID: %d", id);
	return 1;
}

CMD:makedrug(playerid, params[]){
    new string[128];
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pAdmin] >= 1338){
            new type, id = -1;
            if(sscanf(params, "d", type))
                return SystemMsg(playerid, "/makedrug [type]");

            if(type <= 0)
                return ErrorMsg(playerid, "คุณต้องกรอกมากกว่า 0");

            id = Drug_Create(playerid, type);
        
            if(id == -1)
                return ErrorMsg(playerid, "เซิฟเวอร์ได้สร้างจุดขนยาเต็มแล้ว");

            format(string, sizeof(string), "ผู้ดูแล %s ประสบความสำเร็จในการสร้างจุดขนยาไอดี: %d", ReturnRoleplayName(playerid), id);
		    SendAdminsMessage(1, COLOR_YELLOW, string);
        }
    }
    return 1;
}

CMD:removedrug(playerid, params[]){
    new string[128];
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pAdmin] >= 1338){
            new id = -1;
            if(sscanf(params, "d", id))
                return SystemMsg(playerid, "/removedrug [id]");

            if ((id < 0 || id >= MAX_DRUGPOINT) || !DrugData[id][drugEx])
                return SendClientMessage(playerid, -1, "คุณระบุไอดีขนยาผิดพลาด");

            Drug_Delete(id);
            format(string, sizeof(string), "ผู้ดูแล %s ประสบความสำเร็จในการทำล้ายจุดขนยาไอดี: %d", ReturnRoleplayName(playerid), id);
		    SendAdminsMessage(1, COLOR_YELLOW, string);
        }
    }
    return 1;
}

forward RandomPriceRedMoney();
public RandomPriceRedMoney(){
	for(new i=0; i<MAX_DRUGPOINT; i++) if(DrugData[i][drugEx]){
		new RandomEco[4] = {100,200,300,400};
		new randomprice = random(sizeof(RandomEco));
		if(DrugData[i][drugType] == 1){
			DrugData[i][drugPrice] = RandomEco[randomprice];
		}
        if(DrugData[i][drugType] == 2){
			DrugData[i][drugPrice] = RandomEco[randomprice];
		}
        new RandomEco2[3] = {100,200,300};
        new randomprice2 = random(sizeof(RandomEco2));
        if(DrugData[i][drugType] == 4){
			DrugData[i][drugPrice] = RandomEco2[randomprice2];
		}
        new RandomEco3[4] = {10,20,30,40};
        new randomprice3 = random(sizeof(RandomEco3));
        if(DrugData[i][drugType] == 5){
			DrugData[i][drugPrice] = RandomEco3[randomprice3];
		}
		Drug_Save(i);
	}
	SendClientMessageToAll(0xA20000AA, "[ตลาดมืด]: ราคาตลาดมืดมีการปรับเปลี่ยน");
	return 1;
}

CMD:editdrug(playerid, params[]){
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pAdmin] >= 1338){
            new
                id,
                type[24],
                string[128];
            if (sscanf(params, "ds[24]S()[128]", id, type, string))
            {
                SystemMsg(playerid, "/editdrug [id] [name]");
                SystemMsg(playerid, "[ตัวเลือก]:{FFFFFF} location, process, amount, type, price, deliver");
                return 1;
            }
            if ((id < 0 || id >= MAX_DRUGPOINT) || !DrugData[id][drugEx])
                return SendClientMessage(playerid, -1, "คุณระบุไอดีขนยาผิดพลาด");

            if (!strcmp(type, "location", true)){
                new
                    Float:x,
                    Float:y,
                    Float:z;

                GetPlayerPos(playerid, x, y, z);

                DrugData[id][drugPos][0] = x;
                DrugData[id][drugPos][1] = y;
                DrugData[id][drugPos][2] = z;

                DrugData[id][drugInt] = GetPlayerInterior(playerid);
                DrugData[id][drugWorld] = GetPlayerVirtualWorld(playerid);

                Drug_RenderRefresh(id);
                //Drug_Refresh(id);
                Drug_Save(id);

                format(string, sizeof(string), "%s ได้ปรับตำแหน่งจุดเก็บยา ไอดี: %d", ReturnRoleplayName(playerid), id);
                SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            else if (!strcmp(type, "process", true)){
                new
                    Float:x,
                    Float:y,
                    Float:z;

                GetPlayerPos(playerid, x, y, z);

                DrugData[id][drugProcessPos][0] = x;
                DrugData[id][drugProcessPos][1] = y;
                DrugData[id][drugProcessPos][2] = z;
                DrugData[id][drugProcessInt] = GetPlayerInterior(playerid);
                DrugData[id][drugProcessWorld] = GetPlayerVirtualWorld(playerid);

                Drug_RenderRefresh(id);
                //Drug_Refresh(id);
                Drug_Save(id);

                format(string, sizeof(string), "%s ได้ปรับตำแหน่ง Process ยา ไอดี: %d", ReturnRoleplayName(playerid), id);
                SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            else if (!strcmp(type, "deliver", true)){
                new
                    Float:x,
                    Float:y,
                    Float:z;

                GetPlayerPos(playerid, x, y, z);

                DrugData[id][drugDeliverPos][0] = x;
                DrugData[id][drugDeliverPos][1] = y;
                DrugData[id][drugDeliverPos][2] = z;
                DrugData[id][drugDeliverInt] = GetPlayerInterior(playerid);
                DrugData[id][drugDeliverWorld] = GetPlayerVirtualWorld(playerid);

                Drug_RenderRefresh(id);
                //Drug_Refresh(id);
                Drug_Save(id);

                format(string, sizeof(string), "%s ได้ปรับตำแหน่ง ขาย ยา ไอดี: %d", ReturnRoleplayName(playerid), id);
                SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            else if(!strcmp(type, "amount", true)){
                new amount;

                if (sscanf(string, "d", amount))
                    return SendClientMessage(playerid, -1, "/editjob [id] [amount] [amount]");

                DrugData[id][drugAmount] = amount;

                Drug_RenderRefresh(id);
                //Drug_Refresh(id);
                Drug_Save(id);

                format(string, sizeof(string), "%s ได้ปรับจำนวน ยา ไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, amount);
                SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            else if(!strcmp(type, "type", true)){
                new typeint;
                if (sscanf(string, "d", typeint))
                    return SendClientMessage(playerid, -1, "/editjob [id] [type] [type]");

                DrugData[id][drugType] = typeint;

                Drug_RenderRefresh(id);
                //Drug_Refresh(id);
                Drug_Save(id);

                format(string, sizeof(string), "%s ได้ปรับจำนวน ประเภท ขนยา ไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, typeint);
                SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            else if(!strcmp(type, "price", true)){
                new price;

                if (sscanf(string, "d", price))
                    return SendClientMessage(playerid, -1, "/editjob [id] [price] [price]");

                DrugData[id][drugPrice] = price;

                Drug_RenderRefresh(id);
                //Drug_Refresh(id);
                Drug_Save(id);

                format(string, sizeof(string), "%s ได้ปรับราคา ยา ไอดี: %d เป็น %s", ReturnRoleplayName(playerid), id, FormatNumber(price));
                SendAdminsMessage(1, COLOR_YELLOW, string);
            }
        }
    }
    return 1;
}

CMD:redrug(playerid, params[]){
    if(LoggedIn[playerid]){
        if(PlayerData[playerid][pAdmin] >= 1338){
            for(new i=0; i<MAX_DRUGPOINT; i++) if(DrugData[i][drugEx]){
                Drug_RenderRefresh(i);
                //Drug_Refresh(i);
            }
        }
    }
    return 1;
}