#if defined _inc_impl
	#undef _inc_impl
#endif

Dialog:DIALOGHELPMENU(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    new string[256];
    if(response){
        if(listitem == 0){
            if(!PlayerInventoryStatus[playerid]) OnPlayerInventory_Open(playerid);
        }
        if(listitem == 1){
            ShowStatsForPlayer(playerid, playerid);
        }
        if(listitem == 2){
            ShowResultVipMember(playerid);
        }
        if(listitem == 3){
            new
            Float:fX,
            Float:fY,
            Float:fZ,
            count = 1;

            SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");

            for(new i=0; i<MAX_DYNAMIC_CARS; i++) if(CarData[i][carHave]){
                if (Car_IsOwner(playerid, i)) {
                    GetVehiclePos(CarData[i][carVehicle], fX, fY, fZ);

                    new lockstats[24];
                    new tracker[24];

                    if(CarData[i][carLocked] == 0)
                        lockstats = "ปลดล็อค";
                    else
                        lockstats = "ล็อค";

                    if(CarData[i][carGPS] == 1) tracker = "มี";
                    else tracker = "ไม่มี";

                    if(CarData[i][carInsideGarage] == 0){
                        if(CarData[i][carDestroyed] == 0){
                            SendClientMessageEx(playerid, COLOR_WHITE, "กุญแจยานพาหนะ: [%d] ช่อง #%d: ยานพาหนะ:[%s] สถานะล็อค:[%s] สถานที่รถของคุณ:[%s]",CarData[i][carVehicle],count,ReturnVehicleModelName(CarData[i][carModel]),lockstats,GetLocation(fX, fY, fZ));
                            SendClientMessageEx(playerid, COLOR_WHITE, "ป้ายทะเบียน:[%s] ระบบติดตาม:[%s]", CarData[i][carPlate], tracker);
                        }
                        else if(CarData[i][carDestroyed] == 1){
                            if(CarData[i][carVehicle] == INVALID_VEHICLE_ID){
                                SendClientMessageEx(playerid, COLOR_WHITE, "[ถูกทำลาย] กุญแจยานพาหนะ: [#] ช่อง #%d: ยานพาหนะ:[%s] (สามารถไปกู้คืนได้โดยพิมพ์ '/gps > ค้นหา จุดกู้คืนยานพาหนะ)",count,ReturnVehicleModelName(CarData[i][carModel]));
                                SendClientMessageEx(playerid, COLOR_WHITE, "ป้ายทะเบียน:[%s] ระบบติดตาม:[%s]", CarData[i][carPlate], tracker);
                            }
                            else{
                                SendClientMessageEx(playerid, COLOR_WHITE, "[ถูกทำลาย] กุญแจยานพาหนะ: [%d] ช่อง #%d: ยานพาหนะ:[%s] (สามารถไปกู้คืนได้โดยพิมพ์ '/gps > ค้นหา จุดกู้คืนยานพาหนะ)", CarData[i][carVehicle],count,ReturnVehicleModelName(CarData[i][carModel]));
                                SendClientMessageEx(playerid, COLOR_WHITE, "ป้ายทะเบียน:[%s] ระบบติดตาม:[%s]", CarData[i][carPlate], tracker);
                            }
                        }
                        count++;
                    }
                }
            }
            if (count < 2) SendClientMessage(playerid, COLOR_WHITE, "ไม่มียานพาหนะของคุณที่จอดอยู่บนพื้น...");
            SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
        }
        if(listitem == 4){
            callcmd::tickets(playerid, "\1");
        }
        if(listitem == 5){
            Dialog_ShowEasy(playerid, ShowLicenses, DIALOG_STYLE_LIST, "บัตรประจำตัวต่างๆ", "- บัตรประชาชน\n- บัตรประจำตัวหน่วยงาน\n- ใบขับขี่", "เลือก", "ยกเลิก");
        }
        if(listitem == 6){
            ShowMenuAnimation(playerid);
        }
        if(listitem == 7){
            ShowMenuMic(playerid);
        }
        /*if(listitem == 8){
            ShowPartyMenu(playerid);
        }*/
        if(listitem == 8){

            if(PlayerEnterWarFlag[playerid]) return 1;

            if(!PlayerIsDropMap[playerid]){
                if(GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) != 0){
                    SetPlayerPosEx(playerid, 1120.4299,-1378.5870,14.2879, 0, 0);
                    format(string, sizeof(string), "ผู้เล่น %s(%d) ได้ถูกส่งไปยังตลาดกลางเรียบร้อยโดยระบบแจ้งตกแมพ", ReturnRoleplayName(playerid), playerid);
                    SendAdminsMessage(1, 0xFF0066AA, string);
                    return 1;
                }

                PlayerIsDropMap[playerid] = true;
                format(string, sizeof(string), "ผู้เล่น %s ได้ทำการแจ้งว่าเขาตกแมพ (/sm [%d])", ReturnRoleplayName(playerid), playerid);
                SendAdminsMessage(1, 0xFF0066AA, string);
            }
        }
        if(listitem == 9){
            ShowPlayerSkills(playerid);
        }
        if(listitem == 10){
            if(!PlayerData[playerid][pChayaHead]) return ErrorMsg(playerid, "คุณไม่มีฉายาบนหัว");
            Dialog_ShowEasy(playerid, SetChayaHead, DIALOG_STYLE_INPUT, "ตั้งฉายาบนหัว", "กรอกข้อความสำหรับฉายาบนหัวของคุณตั้งแต่ 1-64 ตัวอักษร", "ตกลง", "ยกเลิก");
        }
        if(listitem == 11){
            if(PlayerData[playerid][pPlayerhour] < 5) return ErrorMsg(playerid, "คุณไม่สามารถใช้ระบบนี้ได้เนื่องจากคุณเป็นผู้เล่นใหม่ คุณจะต้องมีชั่วโมงออนไลน์ 5 ชม. ขึ้นไป");
            if(ServerData[ServerCanTrade] == 1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ระบบแลกเปลี่ยนถูกปิดใช้งานอยู่", "ตกลง", "");
            if(CheckPlayerCanTradeZone(playerid) == -1) return ErrorMsg(playerid, "คุณไม่ได้อยู่ในโซนที่สามารถเทรดได้, กรุณาไปเทรดที่ ตลาดกลาง LS หรือ SF เท่านั้น");
            else Dialog_ShowEasy(playerid, InputIDTrade, DIALOG_STYLE_INPUT, "กรอกไอดีผู้เล่นที่ต้องการ", "กรอกไอดีหรือชื่อผู้เล่นที่ต้องการจะแลกเปลี่ยนด้วย: ", "ตกลง", "ยกเลิก");
        }
        if(listitem == 12){
            if(!PlayerData[playerid][pChayaLogin]) return ErrorMsg(playerid, "คุณไม่มีฉายา Login");
            Dialog_ShowEasy(playerid, SetChayaLogin, DIALOG_STYLE_INPUT, "ตั้งฉายา Login", "กรอกข้อความสำหรับฉายา Login ของคุณตั้งแต่ 1-64 ตัวอักษร", "ตกลง", "ยกเลิก");
        }
        if(listitem == 13){
            if(PlayerCheckSleepOnBed[playerid]) return 1;
            if(PlayerData[playerid][pAdmin] <= 0){
                if(TimeCountLogout[playerid] == 0 && CheckingLogout[playerid] == 0){
                    TogglePlayerControllable(playerid, 0);
                    CheckingLogout[playerid] = 1;
                    TimeCountLogout[playerid] = 10;
                    GameTextForPlayer(playerid,"~n~~n~~y~Logout In 10 seconds",1000,3);
                } 
            }   
            else PlayerLogout(playerid);
        }
    }
    return 1;
}

Dialog:SelectTypeRacing(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){  
            if(!LoggedIn[playerid]) return 1;
            if(!PlayerEnterRacing[playerid]){
                LoadRacingPlayerTextDraw(playerid);
                format(PlayerRacing[playerid][RacingCodeRoom], 64, RandomRacingCodeRoom());
                new Float:x, Float:y, Float:z;
                GetPlayerPos(playerid, x, y, z);
                PlayerRacingGetPlayerPos[playerid][0] = x;
                PlayerRacingGetPlayerPos[playerid][1] = y;
                PlayerRacingGetPlayerPos[playerid][2] = z;
                PlayerRacingGetInterior[playerid] = GetPlayerInterior(playerid);
                PlayerRacingGetWorld[playerid] = GetPlayerVirtualWorld(playerid);
                PlayerRacing_Render(playerid);
            }
        }
        if(listitem == 1){
            if(!LoggedIn[playerid]) return 1;
            if(!PlayerEnterRacing[playerid]) Dialog_ShowEasy(playerid, InputCodeRacingRoom, DIALOG_STYLE_INPUT, "Code Room", "กรุณากรอก Code Room Racing ที่ต้องการจะเข้า:", "ตกลง", "ปิด");
        }
    }
    return 1;
}

Dialog:SetChayaLogin(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(isnull(inputtext)) return Dialog_ShowEasy(playerid, SetChayaLogin, DIALOG_STYLE_INPUT, "ตั้งฉายา Login", "* คุณจำเป็นต้องกรอกข้อความ\nกรอกข้อความสำหรับฉายา Login ของคุณตั้งแต่ 1-64 ตัวอักษร", "ตกลง", "ยกเลิก");
        if(strlen(inputtext) < 1 || strlen(inputtext) > 64) return Dialog_ShowEasy(playerid, SetChayaLogin, DIALOG_STYLE_INPUT, "ตั้งฉายา Login", "* คุณต้องกรอกจำนวนตัวอักษร 1-64 ตัวเท่านั้น\nกรอกข้อความสำหรับฉายา Login ของคุณตั้งแต่ 1-64 ตัวอักษร", "ตกลง", "ยกเลิก");
        format(PlayerData[playerid][pChayaLoginMessage], 64, inputtext);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ตั้งฉายา Login ของคุณเป็น: %s", PlayerData[playerid][pChayaLoginMessage]);
        SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: ฉายาจะแสดงเมื่อคุณเข้าสู่ระบบตัวละครเท่านั้น");
    }
    return 1;
}

Dialog:SetChayaHead(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(isnull(inputtext)) return Dialog_ShowEasy(playerid, SetChayaHead, DIALOG_STYLE_INPUT, "ตั้งฉายาบนหัว", "* คุณจำเป็นต้องกรอกข้อความ\nกรอกข้อความสำหรับฉายาบนหัวของคุณตั้งแต่ 1-64 ตัวอักษร", "ตกลง", "ยกเลิก");
        if(strlen(inputtext) < 1 || strlen(inputtext) > 64) return Dialog_ShowEasy(playerid, SetChayaHead, DIALOG_STYLE_INPUT, "ตั้งฉายาบนหัว", "* คุณต้องกรอกจำนวนตัวอักษร 1-64 ตัวเท่านั้น\nกรอกข้อความสำหรับฉายาบนหัวของคุณตั้งแต่ 1-64 ตัวอักษร", "ตกลง", "ยกเลิก");
        format(PlayerData[playerid][pChayaHeadMessage], 64, inputtext);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ตั้งฉายาบนหัวของคุณเป็น: %s", PlayerData[playerid][pChayaHeadMessage]);
    }
    return 1;
}

Dialog:ShowLicenses(playerid, response, listitem, inputtext[]){
    if(!response) {
        return 1;
    }
    if(response){
        if(listitem == 0){
            if(PlayerInventory_AllCount(playerid, "Id Card") <= 0)
                return ErrorMsg(playerid, "คุณไม่มีบัตรประจำตัวประชาชน");

            Dialog_ShowEasy(playerid, MyIdCard, DIALOG_STYLE_LIST, "บัตรประจำตัวประชาชน", "- ดูบัตรประจำตัวประชาชน\n- ให้ผู้เล่นอื่นดู", "เลือก", "ยกเลิก");
        }
        if(listitem == 1){

            if(GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_MEDIC && GetGroupType(playerid) != GROUP_NATIONAL)
                return ErrorMsg(playerid, "คุณไม่ได้เป็นสมาชิกในหน่วยงานใดๆ");

            if(PlayerInventory_AllCount(playerid, "Agency Card") <= 0)
                return ErrorMsg(playerid, "คุณไม่มีบัตรประจำตัวเจ้าหน้าที่");

            Dialog_ShowEasy(playerid, MyAgencyCard, DIALOG_STYLE_LIST, "บัตรประจำตัวหน่วยงาน", "- ดูบัตรประจำตัวหน่วยงาน\n- ให้ผู้เล่นอื่นดู", "เลือก", "ยกเลิก");
        }
        if(listitem == 2){
            if(PlayerInventory_AllCount(playerid, "Driving Card") <= 0) return ErrorMsg(playerid, "คุณไม่มีใบขับขี่");
            Dialog_ShowEasy(playerid, MyDrivingCard, DIALOG_STYLE_LIST, "ใบขับขี่", "- ดูใบขับขี่\n- ให้ผู้เล่นอื่นดู", "เลือก", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:MyIdCard(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(IsShowCard[playerid] == 0)
                ShowIdCardForPlayer(playerid, playerid);
            else if(IsShowCard[playerid] == 1)
                HideIdCardForPlayer(playerid);
        }
        if(listitem == 1){
            ShowIdCardToPlayer(playerid);
        }
    }
    return 1;
}

ShowIdCardToPlayer(playerid){
    new stringplayer[1024];
    new count;
    new menu[20];
    foreach(new x : Player){
        if(!LoggedIn[x]) continue;
        if(x == playerid) continue;
        if(IsPlayerNearPlayer(playerid, x, 5.0)){
            format(menu, 20, "menu%d", count++);
            SetPVarInt(playerid, menu, x);
            format(stringplayer, sizeof(stringplayer), "%s %s(%d)\n", stringplayer, ReturnRoleplayName(x), x);
        }
        if(count >= 20) break;
    }
    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "[เลือกผู้เล่นที่จะโชว์บัตรประชาชนให้ดู]", "ไม่มีใครอยู่ใกล้คุณเลย", "ตกลง", "ยกเลิก");
    else Dialog_ShowEasy(playerid, ShowTargetIDCard, DIALOG_STYLE_LIST, "[เลือกผู้เล่นที่จะโชว์บัตรประชาชนให้ดู]", stringplayer, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:ShowTargetIDCard(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "playerID", GetPVarInt(playerid, str_biz));
			ShowIDCardToUserid(playerid);
			return 1;
		}
    }
    return 1;
}

ShowIDCardToUserid(playerid){
    new targetid = GetPVarInt(playerid, "playerID");
    if(targetid == INVALID_PLAYER_ID){
        ErrorMsg(playerid, "ไอดีผู้เล่นผิดพลาด");
        return ShowIdCardToPlayer(playerid);
    }

    if(!LoggedIn[targetid]){
        ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        return ShowIdCardToPlayer(playerid);
    }

    if (!IsPlayerNearPlayer(playerid, targetid, 5.0)){
        ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้นหรือผู้เล่นนั้นห่างคุณออกไป");
        return ShowIdCardToPlayer(playerid);
    }

    SendClientMessageEx(playerid, -1, "คุณได้โชว์บัตรประชาชนให้กับ %s", ReturnRoleplayName(targetid));
    ShowIdCardForPlayer(targetid, playerid);
    SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้หยิบบัตรประชาชนขึ้นมาและโชว์ให้กับ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(targetid));
    return 1;
}

Dialog:MyAgencyCard(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(IsShowCard[playerid] == 0)
                ShowBadgeForPlayer(playerid, playerid);
            else if(IsShowCard[playerid] == 1)
                HideBadgeForPlayer(playerid);
        }
        if(listitem == 1){
            ShowAgencyCardToPlayer(playerid);
        }
    }
    return 1;
}

ShowAgencyCardToPlayer(playerid){
    new stringplayer[1024];
    new count;
    new menu[20];
    foreach(new x : Player){
        if(!LoggedIn[x]) continue;
        if(x == playerid) continue;
        if(IsPlayerNearPlayer(playerid, x, 5.0)){
            format(menu, 20, "menu%d", count++);
            SetPVarInt(playerid, menu, x);
            format(stringplayer, sizeof(stringplayer), "%s %s(%d)\n", stringplayer, ReturnRoleplayName(x), x);
        }
        if(count >= 20) break;
    }
    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "[เลือกผู้เล่นที่จะโชว์บัตรประจำตำแหน่ง]", "ไม่มีใครอยู่ใกล้คุณเลย", "ตกลง", "ยกเลิก");
    else Dialog_ShowEasy(playerid, ShowBadgeToPlayer, DIALOG_STYLE_LIST, "[เลือกผู้เล่นที่จะโชว์บัตรประจำตำแหน่ง]", stringplayer, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:ShowBadgeToPlayer(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "playerID", GetPVarInt(playerid, str_biz));
			ShowBadgeToUserid(playerid);
			return 1;
		}
    }
    return 1;
}

ShowBadgeToUserid(playerid){
    new targetid = GetPVarInt(playerid, "playerID");
    if(targetid == INVALID_PLAYER_ID){
        ErrorMsg(playerid, "ไอดีผู้เล่นผิดพลาด");
        return ShowAgencyCardToPlayer(playerid);
    }

    if(!LoggedIn[targetid]){
        ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        return ShowAgencyCardToPlayer(playerid);
    }

    if (!IsPlayerNearPlayer(playerid, targetid, 5.0)){
        ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้นหรือผู้เล่นนั้นห่างคุณออกไป");
        return ShowAgencyCardToPlayer(playerid);
    }

    SendClientMessageEx(playerid, -1, "คุณได้โชว์บัตรประจำตัวหน่วยงานให้กับ %s", ReturnRoleplayName(targetid));
    ShowBadgeForPlayer(targetid, playerid);
    SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้หยิบบัตรประจำตัวหน่วยงานขึ้นมาและโชว์ให้กับ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(targetid));
    return 1;
}

Dialog:MyDrivingCard(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(IsShowCard[playerid] == 0) ShowDrivingForPlayer(playerid, playerid);
            else if(IsShowCard[playerid] == 1) HideDrivingForPlayer(playerid);
        }
        if(listitem == 1){
            ShowDrivingCardToPlayer(playerid);
        }
    }
    return 1;
}

ShowDrivingCardToPlayer(playerid){
    new stringplayer[1024];
    new count;
    new menu[20];
    foreach(new x : Player){
        if(!LoggedIn[x]) continue;
        if(x == playerid) continue;
        if(IsPlayerNearPlayer(playerid, x, 5.0)){
            format(menu, 20, "menu%d", count++);
            SetPVarInt(playerid, menu, x);
            format(stringplayer, sizeof(stringplayer), "%s %s(%d)\n", stringplayer, ReturnRoleplayName(x), x);
        }
        if(count >= 20) break;
    }
    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "[เลือกผู้เล่นที่จะโชว์ใบขับขี่]", "ไม่มีใครอยู่ใกล้คุณเลย", "ตกลง", "ยกเลิก");
    else Dialog_ShowEasy(playerid, ShowDrivingToPlayer, DIALOG_STYLE_LIST, "[เลือกผู้เล่นที่จะโชว์ใบขับขี่]", stringplayer, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:ShowDrivingToPlayer(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "playerID", GetPVarInt(playerid, str_biz));
			ShowDrivingToUserid(playerid);
			return 1;
		}
    }
    return 1;
}

ShowDrivingToUserid(playerid){
    new targetid = GetPVarInt(playerid, "playerID");
    if(targetid == INVALID_PLAYER_ID){
        ErrorMsg(playerid, "ไอดีผู้เล่นผิดพลาด");
        return ShowDrivingCardToPlayer(playerid);
    }

    if(!LoggedIn[targetid]){
        ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        return ShowDrivingCardToPlayer(playerid);
    }

    if (!IsPlayerNearPlayer(playerid, targetid, 5.0)){
        ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้นหรือผู้เล่นนั้นห่างคุณออกไป");
        return ShowDrivingCardToPlayer(playerid);
    }

    SendClientMessageEx(playerid, -1, "คุณได้โชว์ใบขับขี่ให้กับ %s", ReturnRoleplayName(targetid));
    ShowDrivingForPlayer(targetid, playerid);
    SendNearbyMessage(playerid, 30.0, COLOR_RP, "* %s ได้หยิบใบขับขี่ขึ้นมาและโชว์ให้กับ %s", ReturnRoleplayName(playerid), ReturnRoleplayName(targetid));
    return 1;
}

ShowDrivingForPlayer(playerid, targetid){
    IsShowCard[playerid] = 1;
    LoadTextDrawPlayerShowBadge(playerid);

    PlayerTextDrawSetPreviewModel(playerid, ShowBadgeTextDraw[playerid][4], PlayerData[targetid][pSkin]);

    new string[128];

    PlayerTextDrawSetString(playerid, ShowBadgeTextDraw[playerid][2], "Driving License");

    format(string, sizeof(string), "Name: %s", ReturnRoleplayName(targetid));
    PlayerTextDrawSetString(playerid, ShowBadgeTextDraw[playerid][5], string);

    format(string, sizeof(string), "Age: %d", PlayerData[playerid][pAge]);
    PlayerTextDrawSetString(playerid, ShowBadgeTextDraw[playerid][6], string);

    format(string, sizeof(string), "Status: ~g~Pass");
    PlayerTextDrawSetString(playerid, ShowBadgeTextDraw[playerid][7], string);

    PlayerTextDrawBoxColor(playerid, ShowBadgeTextDraw[playerid][1], 0x00CDFFAA);

    for(new i=0; i<9; i++) PlayerTextDrawShow(playerid, ShowBadgeTextDraw[playerid][i]);

    SelectTextDraw(playerid, 0xFFB900AA);
    return 1;
}

HideDrivingForPlayer(playerid){
    IsShowCard[playerid] = 0;
    for(new i=0; i<9; i++){
        PlayerTextDrawHide(playerid, ShowBadgeTextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, ShowBadgeTextDraw[playerid][i]);
    }
    CancelSelectTextDraw(playerid);
    return 1;
}

Dialog:DIALOGVIPMEMBER(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    if(response){
        new userid;

        if (sscanf(inputtext, "u", userid))
            return Dialog_ShowEasy(playerid, DIALOGVIPMEMBER, DIALOG_STYLE_INPUT, "จัดการระดับผู้บริจาค", "กรอก ID ผู้เล่นที่ต้องการจะให้ Vip", "ตกลง", "ยกเลิก");

        if(userid == INVALID_PLAYER_ID)
            return Dialog_ShowEasy(playerid, DIALOGVIPMEMBER, DIALOG_STYLE_INPUT, "จัดการระดับผู้บริจาค", "* ไอดีผู้เล่นเล่นผิดพลาด *\nกรอก ID ผู้เล่นที่ต้องการจะให้ Vip", "ตกลง", "ยกเลิก");

        IDPlayerGetVIP[playerid] = userid;
        Dialog_ShowEasy(playerid, DIALOGVIPMEMBER2, DIALOG_STYLE_INPUT, "จัดการระดับผู้บริจาค", "กรอก ระดับผู้บริจาค และ จำนวนวันของ VIP\nเช่น [3] = ระดับ VIP [30] = จำนวนวัน", "ตกลง", "ยกเลิก");
    }
	return 1;
}

Dialog:DIALOGVIPMEMBER2(playerid, response, listitem, inputtext[])
{
    if(!response){
        IDPlayerGetVIP[playerid] = -1;
        return 1;
    }

    if(response){
       if (response)
        {
            new userid = IDPlayerGetVIP[playerid];
            new vipstr[64];

            new tmp[2][32];
            strexplode(tmp, inputtext, " ");

            new vip = strval(tmp[0]), viptime = strval(tmp[1]);

            if (isnull(inputtext))
                return Dialog_ShowEasy(playerid, DIALOGVIPMEMBER2, DIALOG_STYLE_INPUT, "จัดการระดับผู้บริจาค", "กรอก ID ระดับผู้บริจาค และ จำนวนวันของ VIP\nเช่น ระดับ VIP [30] = จำนวนวัน", "ตกลง", "ยกเลิก");

            if(vip < 0 || vip > 3)
                return Dialog_ShowEasy(playerid, DIALOGVIPMEMBER2, DIALOG_STYLE_INPUT, "จัดการระดับผู้บริจาค", "* ระดับผู้บริจาคผิดพลาด *\nกรอก ระดับผู้บริจาค และ จำนวนวันของ VIP\nเช่น [3] = ระดับ VIP [30] = จำนวนวัน", "ตกลง", "ยกเลิก");

            if(viptime < 0)
                return Dialog_ShowEasy(playerid, DIALOGVIPMEMBER2, DIALOG_STYLE_INPUT, "จัดการระดับผู้บริจาค", "* จำนวนอายุของระดับผู้บริจาคต้องมากกว่าหรือเท่ากับ 0 *\nกรอก ระดับผู้บริจาค และ จำนวนวันของ VIP\nเช่น [3] = ระดับ VIP [30] = จำนวนวัน", "ตกลง", "ยกเลิก");

            new string[128];

            if(userid != -1){
                if(vip == 0){
                    PlayerData[userid][pVip] = 0;
                    PlayerData[userid][pVipDay] = 0;
                    PlayerData[userid][pVipMonth] = 0;
                    PlayerData[userid][pVipHour] = 0;
                    format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับให้ ระดับผู้บริจาคของ %s เป็นปกติ", ReturnRoleplayName(playerid), ReturnRoleplayName(userid));
                    SendAdminsMessage(1, COLOR_GRAY, string);
                    SendClientMessage(userid, 0x2F91FFAA, "ผู้ดูแลได้ให้ ระดับบริจาค ของคุณเป็น เป็นปกติ");
                }
                else{
                    if(vip == 1) vipstr = "Bronze Member";
                    else if(vip == 2) vipstr = "Silver Member";
                    else if(vip == 3) vipstr = "Gold Member";

                    new Year, Month, Day;
                    new Hour, Minute, Second;
                    gettime(Hour, Minute, Second);
                    getdate(Year, Month, Day);

                    new TotalDay = 0, ActualDay;
                    if(Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12){
                        TotalDay = 31;
                        if(Day+viptime > 31){
                            if(Month + 1 > 12){
                                Month = 1;
                            }
                            else{
                                Month++;
                            }
                            
                            ActualDay = viptime - (TotalDay-Day);
                            if(ActualDay == 0) ActualDay = 1;

                            if(Month == 2){
                                if(ActualDay >= 29){
                                    if(ActualDay == 29) ActualDay = 1;
                                    else if(ActualDay == 30) ActualDay = 2;
                                    Month++;
                                    PlayerData[userid][pVipDay] = ActualDay;
                                    PlayerData[userid][pVipMonth] = Month;
                                    PlayerData[userid][pVipHour] = Hour;
                                }
                                else{
                                    PlayerData[userid][pVipDay] = ActualDay;
                                    PlayerData[userid][pVipMonth] = Month;
                                    PlayerData[userid][pVipHour] = Hour;
                                }
                            }
                            else if(Month == 3){
                                ActualDay = viptime - (TotalDay-Day);
                                PlayerData[userid][pVipDay] = ActualDay;
                                PlayerData[userid][pVipMonth] = Month;
                                PlayerData[userid][pVipHour] = Hour;
                            }
                            else{
                                PlayerData[userid][pVipDay] = ActualDay;
                                PlayerData[userid][pVipMonth] = Month;
                                PlayerData[userid][pVipHour] = Hour;
                            }
                        }
                        else{
                            PlayerData[userid][pVipDay] = Day+viptime;
                            PlayerData[userid][pVipMonth] = Month;
                            PlayerData[userid][pVipHour] = Hour;
                        }
                    } 
                    else if(Month == 4 || Month == 6 || Month == 9 || Month == 11){
                        TotalDay = 30;
                        if(Day+viptime > 30){
                            if(Month + 1 > 12){
                                Month = 1;
                            }
                            else{
                                Month++;
                            }
                            ActualDay = viptime - (TotalDay-Day);
                            if(ActualDay == 0) ActualDay = 1;
                            if(Month == 2){
                                if(ActualDay > 28){
                                    if(ActualDay == 29) ActualDay = 2;
                                    else if(ActualDay == 30) ActualDay = 3;
                                    else if(ActualDay == 31) ActualDay = 4;
                                    Month++;
                                    PlayerData[userid][pVipDay] = ActualDay;
                                    PlayerData[userid][pVipMonth] = Month;
                                    PlayerData[userid][pVipHour] = Hour;
                                }
                                else{
                                    PlayerData[userid][pVipDay] = ActualDay;
                                    PlayerData[userid][pVipMonth] = Month;
                                    PlayerData[userid][pVipHour] = Hour;
                                }
                            }
                            else{
                                PlayerData[userid][pVipDay] = ActualDay;
                                PlayerData[userid][pVipMonth] = Month;
                                PlayerData[userid][pVipHour] = Hour;
                            }
                        }
                        else{
                            PlayerData[userid][pVipDay] = Day+viptime;
                            PlayerData[userid][pVipMonth] = Month;
                            PlayerData[userid][pVipHour] = Hour;
                        }
                    } 
                    else{
                        TotalDay = 28;

                        ActualDay = viptime - (TotalDay-Day);
                        if(ActualDay == 0) ActualDay = 1;

                        if(ActualDay >= 29){
                            Month++;
                            PlayerData[userid][pVipDay] = Day+viptime;
                            PlayerData[userid][pVipMonth] = Month;
                            PlayerData[userid][pVipHour] = Hour;
                        }
                        else{
                            PlayerData[userid][pVipDay] = Day+viptime;
                            PlayerData[userid][pVipMonth] = Month;
                            PlayerData[userid][pVipHour] = Hour;
                        }
                    }

                    if(Month == 12) {
                        if(PlayerData[playerid][pVipDay] >= 1 && PlayerData[playerid][pVipDay] < 31){
                            PlayerData[playerid][pVipYear] = Year++;
                        }
                        else{
                            PlayerData[playerid][pVipYear] = Year;
                        }
                    }
	                else PlayerData[playerid][pVipYear] = Year;
            
                    PlayerData[userid][pVip] = vip;
                    format(string, sizeof(string), "ผู้ดูแล %s ได้ให้ ระดับผู้บริจาคกับ %s เป็น %s จำนวน %d วัน", ReturnRoleplayName(playerid), ReturnRoleplayName(userid), vipstr, viptime);
                    SendAdminsMessage(1, COLOR_GRAY, string);
                    SendClientMessageEx(userid, 0x2F91FFAA, "ผู้ดูแลได้ให้ ระดับบริจาค ของคุณเป็น %s จำนวน %d วัน", vipstr, viptime);
                }
            }
        }
    }
	return 1;
}

Dialog:GpsMenu(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(listitem == 0){
            ViewJob(playerid);
        }
        if(listitem == 1){
            ViewSideJob(playerid);
        }
        if(listitem == 2){
            PlayerEnterCheckPoint[playerid] = 1;
            SetPlayerCheckpoint(playerid, 1129.1898,-1413.6749,13.6062, 5.0);
            GPSNavigateToPoint(playerid, 1129.1898,-1413.6749,13.6062);
        }
        if(listitem == 3){
            ViewCraft(playerid);
        }
        if(listitem == 4){
            ViewGarage(playerid);
        }
        if(listitem == 5){
            ViewFoodShop(playerid);
        }
        if(listitem == 6){
            PlayerEnterCheckPoint[playerid] = 1;
            SetPlayerCheckpoint(playerid, 2413.9641,-2469.0508,13.6250, 3.0);
            GPSNavigateToPoint(playerid, 2413.9641,-2469.0508,13.6250);
        }
        if(listitem == 7){
            ViewBuyVeh(playerid);
        }
        if(listitem == 8){
            PlayerEnterCheckPoint[playerid] = 1;
            SetPlayerCheckpoint(playerid, 1988.0581,-2062.1467,13.3710, 5.0);
            GPSNavigateToPoint(playerid, 1988.0581,-2062.1467,13.3710);
        }
        if(listitem == 9){
            PlayerEnterCheckPoint[playerid] = 1;
            SetPlayerCheckpoint(playerid, -2233.4194,536.2463,35.1719, 5.0);
            GPSNavigateToPoint(playerid, -2233.4194,536.2463,35.1719);
        }
        if(listitem == 10){
            PlayerEnterCheckPoint[playerid] = 1;
            SetPlayerCheckpoint(playerid, 125.9490,-1815.0796,0.4441, 3.0);
            GPSNavigateToPoint(playerid, 125.9490,-1815.0796,0.4441);
        }
        if(listitem == 11){
            SendClientMessage(playerid, COLOR_RED, "รออัพเดท");
            /*PlayerEnterCheckPoint[playerid] = 1;
            SetPlayerCheckpoint(playerid, -1434.6483,-964.3401,201.0015, 3.0);
            GPSNavigateToPoint(playerid, -1434.6483,-964.3401,201.0015);*/
        }
        if(listitem == 12){
            PlayerEnterCheckPoint[playerid] = 1;
            SetPlayerCheckpoint(playerid, 2045.9137,-1908.1089,13.5469, 3.0);
            GPSNavigateToPoint(playerid, 2045.9137,-1908.1089,13.5469);
        }
    }
    return 1;
}

ViewCraft(playerid){
	new string[2048], menu[20], count;

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

	SetPVarInt(playerid, "page", 1);

	for(new i=0; i<MAX_CRAFT_DYNAMIC; i++)
	{
	    if(CraftData[i][craftExists])
	    {
            if(count == 20)
            {
                format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                break;
            }
            format(menu, 20, "menu%d", ++count);
            SetPVarInt(playerid, menu, i);
            format(string, sizeof(string), "%s จุดคราฟใกล้คุณ (%.2f เมตร)\n", string, GetPlayerDistanceFromPoint(playerid, CraftData[i][craftPos][0], CraftData[i][craftPos][1], CraftData[i][craftPos][2]));
        }
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "จุดคราฟ", "ไม่พบจุดคราฟ..", "ปิด", "");
	else Dialog_ShowEasy(playerid, CraftPointDialog, DIALOG_STYLE_LIST, "จุดคราฟ", string, "ตกลง", "กลับ");
	return 1;
}

SetPlayerPointToCraftPoint(playerid)
{
	new craftid = GetPVarInt(playerid, "CraftPointID");
	PlayerEnterCheckPoint[playerid] = 1;
	SendClientMessage(playerid, COLOR_YELLOW, "[ระบบนำทาง]: GPS ได้นำทางคุณไปยังจุดคราฟที่คุณเลือกแล้ว!");
	SetPlayerCheckpoint(playerid, CraftData[craftid][craftPos][0], CraftData[craftid][craftPos][1], CraftData[craftid][craftPos][2], 5.0);
    GPSNavigateToPoint(playerid, CraftData[craftid][craftPos][0], CraftData[craftid][craftPos][1], CraftData[craftid][craftPos][2]);
}

Dialog:CraftPointDialog(playerid, response, listitem, inputtext[]){
	if(response) {
		new menu[20];
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "CraftPointID", GetPVarInt(playerid, str_biz));
			SetPlayerPointToCraftPoint(playerid);
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

		for(new i=0; i<MAX_CRAFT_DYNAMIC; i++)
	    {   
            if(CraftData[i][craftExists])
            {
                if(skipitem)
                {
                    skipitem--;
                    continue;
                }
                if(count == 20)
                {
                    format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                    break;
                }
                format(menu, 20, "menu%d", ++count);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s จุดคราฟใกล้คุณ (%.2f เมตร)\n", string, GetPlayerDistanceFromPoint(playerid, CraftData[i][craftPos][0], CraftData[i][craftPos][1], CraftData[i][craftPos][2]));
			}
		}

		Dialog_ShowEasy(playerid, CraftPointDialog, DIALOG_STYLE_LIST, "จุดคราฟ", string, "ตกลง", "กลับ");
	}
	return 1;
}

ViewFoodShop(playerid)
{
	new string[2048], menu[20], count;

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

	SetPVarInt(playerid, "page", 1);

	for(new i=0; i<MAX_ENTRANCES; i++)
	{
	    if(EntranceData[i][entranceExists])
	    {
            if(EntranceData[i][entranceType] == 1){
                if(count == 20)
                {
                    format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                    break;
                }
                format(menu, 20, "menu%d", ++count);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s %s (%.2f เมตร)\n", string, EntranceData[i][entranceName], GetPlayerDistanceFromPoint(playerid, EntranceData[i][entrancePos][0], EntranceData[i][entrancePos][1], EntranceData[i][entrancePos][2]));
            }
        }
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ร้านอาหาร", "ไม่พบร้านอาหาร..", "ปิด", "");
	else Dialog_ShowEasy(playerid, FoodShopDialog, DIALOG_STYLE_LIST, "ร้านอาหาร", string, "ตกลง", "กลับ");
	return 1;
}

SetPlayerPointToFoodShop(playerid)
{
	new foodshopid = GetPVarInt(playerid, "EntranceID");
	PlayerEnterCheckPoint[playerid] = 1;
	SendClientMessage(playerid, COLOR_YELLOW, "[ระบบนำทาง]: GPS ได้นำทางคุณไปยังร้านอาหารที่คุณเลือกแล้ว!");
	SetPlayerCheckpoint(playerid, EntranceData[foodshopid][entrancePos][0], EntranceData[foodshopid][entrancePos][1], EntranceData[foodshopid][entrancePos][2], 5.0);
    GPSNavigateToPoint(playerid, EntranceData[foodshopid][entrancePos][0], EntranceData[foodshopid][entrancePos][1], EntranceData[foodshopid][entrancePos][2]);
}

Dialog:FoodShopDialog(playerid, response, listitem, inputtext[])
{
	if(response) {

		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "EntranceID", GetPVarInt(playerid, str_biz));
			SetPlayerPointToFoodShop(playerid);
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

		for(new i=0; i<MAX_ENTRANCES; i++)
		{
		    if(EntranceData[i][entranceExists])
            {
                if(EntranceData[i][entranceType] == 1){
                    if(skipitem)
                    {
                        skipitem--;
                        continue;
                    }
                    if(count == 20)
                    {
                        format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                        break;
                    }
                    format(menu, 20, "menu%d", ++count);
                    SetPVarInt(playerid, menu, i);
                    format(string, sizeof(string), "%s %s (%.2f เมตร)\n", string, EntranceData[i][entranceName], GetPlayerDistanceFromPoint(playerid, EntranceData[i][entrancePos][0], EntranceData[i][entrancePos][1], EntranceData[i][entrancePos][2]));
                }
            }
		}

		Dialog_ShowEasy(playerid, FoodShopDialog, DIALOG_STYLE_LIST, "ร้านอาหาร", string, "ตกลง", "กลับ");
	}
	return 1;
}

ViewBuyVeh(playerid)
{
	new string[2048], menu[20], count;

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

	SetPVarInt(playerid, "page", 1);

	for(new i=0; i<MAX_ENTRANCES; i++)
	{
	    if(EntranceData[i][entranceExists] && EntranceData[i][entranceType] == 2)
	    {
            if(count == 20)
            {
                format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                break;
            }
            format(menu, 20, "menu%d", ++count);
            SetPVarInt(playerid, menu, i);
            format(string, sizeof(string), "%s ร้านรถใกล้ตัวคุณ (%.2f เมตร)\n", string, GetPlayerDistanceFromPoint(playerid, EntranceData[i][entrancePos][0], EntranceData[i][entrancePos][1], EntranceData[i][entrancePos][2]));
        }
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ร้านรถ", "ไม่พบร้านรถ..", "ปิด", "");
	else Dialog_ShowEasy(playerid, BuyVehDialog, DIALOG_STYLE_LIST, "ร้านรถ", string, "ตกลง", "กลับ");
	return 1;
}

SetPlayerPointToBuyVeh(playerid)
{
	new doorid = GetPVarInt(playerid, "buyvehID");
	PlayerEnterCheckPoint[playerid] = 1;
	SendClientMessage(playerid, COLOR_YELLOW, "[ระบบนำทาง]: GPS ได้นำทางคุณไปยังการาจที่คุณเลือกแล้ว!");
	SetPlayerCheckpoint(playerid, EntranceData[doorid][entrancePos][0], EntranceData[doorid][entrancePos][1], EntranceData[doorid][entrancePos][2], 5.0);
    GPSNavigateToPoint(playerid, EntranceData[doorid][entrancePos][0], EntranceData[doorid][entrancePos][1], EntranceData[doorid][entrancePos][2]);
}

Dialog:BuyVehDialog(playerid, response, listitem, inputtext[])
{
	if(response) {

		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "buyvehID", GetPVarInt(playerid, str_biz));
			SetPlayerPointToBuyVeh(playerid);
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

		for(new i=0; i<MAX_ENTRANCES; i++)
        {
            if(EntranceData[i][entranceExists] && EntranceData[i][entranceType] == 2)
            {
                if(skipitem)
                {
                    skipitem--;
                    continue;
                }
                if(count == 20)
                {
                    format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                    break;
                }
                format(menu, 20, "menu%d", ++count);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s ร้านรถใกล้ตัวคุณ (%.2f เมตร)\n", string, GetPlayerDistanceFromPoint(playerid, EntranceData[i][entrancePos][0], EntranceData[i][entrancePos][1], EntranceData[i][entrancePos][2]));
			}
		}

		Dialog_ShowEasy(playerid, BuyVehDialog, DIALOG_STYLE_LIST, "ร้านรถ", string, "ตกลง", "กลับ");
	}
	return 1;
}

ViewGarage(playerid)
{
	new string[2048], menu[20], count;

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

	SetPVarInt(playerid, "page", 1);

	for(new i=0; i<MAX_GARAGE; i++)
	{
	    if(GarageData[i][garageExists])
	    {
            if(count == 20)
            {
                format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                break;
            }
            format(menu, 20, "menu%d", ++count);
            SetPVarInt(playerid, menu, i);
            format(string, sizeof(string), "%s การาจใกล้ตัวคุณ (%.2f เมตร)\n", string, GetPlayerDistanceFromPoint(playerid, GarageData[i][garageGetCar][0], GarageData[i][garageGetCar][1], GarageData[i][garageGetCar][2]));
        }
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การาจ", "ไม่พบการาจ..", "ปิด", "");
	else Dialog_ShowEasy(playerid, GarageDialog, DIALOG_STYLE_LIST, "การาจ", string, "ตกลง", "กลับ");
	return 1;
}

SetPlayerPointToGarage(playerid)
{
	new garageid = GetPVarInt(playerid, "GarageID");
	PlayerEnterCheckPoint[playerid] = 1;
	SendClientMessage(playerid, COLOR_YELLOW, "[ระบบนำทาง]: GPS ได้นำทางคุณไปยังการาจที่คุณเลือกแล้ว!");
	SetPlayerCheckpoint(playerid, GarageData[garageid][garageGetCar][0], GarageData[garageid][garageGetCar][1], GarageData[garageid][garageGetCar][2], 5.0);
    GPSNavigateToPoint(playerid, GarageData[garageid][garageGetCar][0], GarageData[garageid][garageGetCar][1], GarageData[garageid][garageGetCar][2]);
}

Dialog:GarageDialog(playerid, response, listitem, inputtext[])
{
	if(response) {

		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "GarageID", GetPVarInt(playerid, str_biz));
			SetPlayerPointToGarage(playerid);
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

		for(new i=0; i<MAX_GARAGE; i++)
		{
		    if(GarageData[i][garageExists])
	    	{
                if(skipitem)
                {
                    skipitem--;
                    continue;
                }
                if(count == 20)
                {
                    format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                    break;
                }
                format(menu, 20, "menu%d", ++count);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s การาจใกล้ตัวคุณ (%.2f เมตร)\n", string, GetPlayerDistanceFromPoint(playerid, GarageData[i][garageGetCar][0], GarageData[i][garageGetCar][1], GarageData[i][garageGetCar][2]));
			}
		}

		Dialog_ShowEasy(playerid, GarageDialog, DIALOG_STYLE_LIST, "การาจ", string, "ตกลง", "กลับ");
	}
	return 1;
}

ViewJob(playerid)
{
	new string[2048], menu[20], count;

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

	SetPVarInt(playerid, "page", 1);

	for(new i=0; i<MAX_DYNAMIC_JOBS; i++)
	{
	    if(JobData[i][jobExists])
	    {
            if(count == 20)
            {
                format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                break;
            }
            format(menu, 20, "menu%d", ++count);
            SetPVarInt(playerid, menu, i);
            format(string, sizeof(string), "%s [%d]\t%s [ สำหรับ Level: %d ]\n", string, i+1, Job_GetName(i+1), JobData[i][jobLevel]);
		}
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ", "ไม่พบข้อมูลอาชีพ..", "ปิด", "");
	else Dialog_ShowEasy(playerid, JobGps, DIALOG_STYLE_LIST, "อาชีพ", string, "เลือก", "ปิด");
	return 1;
}

Dialog:JobGps(playerid, response, listitem, inputtext[])
{
	if(response) {

		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);
			SetPVarInt(playerid, "jobID", GetPVarInt(playerid, str_biz));
			SetPlayerPointToJob(playerid);
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

		for(new i=0; i<MAX_DYNAMIC_JOBS; i++)
		{
		    if(JobData[i][jobExists])
	    	{
                if(skipitem)
                {
                    skipitem--;
                    continue;
                }
                if(count == 20)
                {
                    format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                    break;
                }
                format(menu, 20, "menu%d", ++count);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s [%d]\t%s [ สำหรับ Level: %d ]\n", string, i+1, Job_GetName(i+1), JobData[i][jobLevel]);
			}
		}
		Dialog_ShowEasy(playerid, JobGps, DIALOG_STYLE_LIST, "อาชีพ", string, "เลือก", "ปิด");
	}
	return 1;
}

SetPlayerPointToJob(playerid){
    new jobid = GetPVarInt(playerid, "jobID")+1;
    new id = GetClosestJob(playerid, jobid);
    if (id != -1)
    {
        if(JobData[id][jobType] == OILJOB){
            PlayerGetJobGPSID[playerid] = id;
            Dialog_ShowEasy(playerid, ShowGpsOilJob, DIALOG_STYLE_LIST, "อาชีพ ขุดบ่อน้ำมัน", "- จุดสมัครอาชีพ\n- จุดแปรรูปน้ำมันดิบ\n- จุดขายน้ำมันแปรรูป", "เลือก", "ยกเลิก");
        }
        else{
            if(JobData[id][jobPos][0] == 0.0 && JobData[id][jobPos][1] == 0.0 && JobData[id][jobPos][2] == 0.0)
                return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

            EnterCheckPointJob[playerid] = 1;

            SetPlayerCheckpoint(playerid, JobData[id][jobPos][0], JobData[id][jobPos][1], JobData[id][jobPos][2], 3.0);
            GPSNavigateToPoint(playerid, JobData[id][jobPos][0], JobData[id][jobPos][1], JobData[id][jobPos][2]);
            SendClientMessageEx(playerid, -1,"คุณได้เปิด GPS ไปยัง จุดสมัครอาชีพ %s", JobData[id][jobName]);
        }
    }
    return 1;
}

ViewSideJob(playerid)
{
	new string[2048], menu[20], count;

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

	SetPVarInt(playerid, "pagesidejob", 1);

	for(new i=0; i<MAX_SIDEJOB; i++)
	{
	    if(SideJobData[i][sidejobExists])
	    {
            if(count == 20)
            {
                format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                break;
            }
            format(menu, 20, "menusidejob%d", ++count);
            SetPVarInt(playerid, menu, i);
            format(string, sizeof(string), "%s [%d]\t%s\n", string, i+1, SideJob_GetName(i+1));
		}
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพเสริม", "ไม่พบข้อมูลอาชีพ..", "ปิด", "");
	else Dialog_ShowEasy(playerid, SideJobGps, DIALOG_STYLE_LIST, "อาชีพเสริม", string, "เลือก", "ปิด");
	return 1;
}

Dialog:SideJobGps(playerid, response, listitem, inputtext[])
{
	if(response) {

		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menusidejob%d", listitem);

			SetPVarInt(playerid, "sidejobID", GetPVarInt(playerid, str_biz));
			SetPlayerPointToSideJob(playerid);
			return 1;
		}

		new currentPage = GetPVarInt(playerid, "pagesidejob");
		if(listitem==0) {
			if(currentPage>1) currentPage--;
		}
		else if(listitem == 21) currentPage++;

		new string[2048], count;
		format(string, sizeof(string), "%s{B4B5B7}หน้า %d\n", string, (currentPage==1) ? 1 : currentPage-1);

		SetPVarInt(playerid, "pagesidejob", currentPage);

		new skipitem = (currentPage-1) * 20;

		for(new i=0; i<MAX_SIDEJOB; i++)
		{
		    if(SideJobData[i][sidejobExists])
	    	{
                if(skipitem)
                {
                    skipitem--;
                    continue;
                }
                if(count == 20)
                {
                    format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                    break;
                }
                format(menu, 20, "menusidejob%d", ++count);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s [%d]\t%s\n", string, i+1, SideJobData[i][sidejobName]);
			}
		}

		Dialog_ShowEasy(playerid, SideJobGps, DIALOG_STYLE_LIST, "อาชีพเสริม", string, "เลือก", "ปิด");
	}
	return 1;
}

SetPlayerPointToSideJob(playerid){
    new jobid = GetPVarInt(playerid, "sidejobID")+1;
    new id = GetClosestSideJob(playerid, jobid);
    if (id != -1)
    {
        if(SideJobData[id][sidejobPos][0] == 0.0 && SideJobData[id][sidejobPos][1] == 0.0 && SideJobData[id][sidejobPos][2] == 0.0)
            return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

        EnterCheckPointJob[playerid] = 1;

        SetPlayerCheckpoint(playerid, SideJobData[id][sidejobPos][0], SideJobData[id][sidejobPos][1], SideJobData[id][sidejobPos][2],3.0);
        GPSNavigateToPoint(playerid, SideJobData[id][sidejobPos][0], SideJobData[id][sidejobPos][1], SideJobData[id][sidejobPos][2]);
        SendClientMessageEx(playerid, -1,"คุณได้เปิด GPS ไปยัง จุดอาชีพเสริม %s", SideJobData[id][sidejobName]);
    }
    return 1;
}

//-------------------------------------------------------------------//

ShowHelpMenu(playerid){
	new string[150];
	format(string, sizeof(string), "- เกี่ยวกับอาชีพ\n- เกี่ยวกับอาชีพเสริม\n- การหาอาชีพ\n- เกี่ยวกับการคราฟไอเท็ม\n- เกี่ยวกับ กลุ่ม\n- เกี่ยวกับ คำสั่งทั่วไป");
	Dialog_ShowEasy(playerid, HelpMenuForPlayer, DIALOG_STYLE_LIST, "เมนูสำหรับช่วยเหลือผู้เล่นใหม่", string, "เลือก", "ยกเลิก");
	return 1;
}

Dialog:HelpMenuForPlayer(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    new string[1024];

    if(response){
        if(listitem == 0){
            ShowHelpForJobPlayer(playerid);
        }
        if(listitem == 1){
            ShowHelpForSideJobPlayer(playerid);
        }
        if(listitem == 2){
            format(string, sizeof(string), "[การทำงาน]\n- ให้คุณพิมพ์ '/gps' เพื่อหางานทำโดยจะมีให้เลือก 'อาชีพหลัก' กับ 'อาชีพเสริม'\n- ในการทำ 'อาชีพเสริม' คุณไม่จำเป็นต้องสมัครงาน และในการทำอาชีพหลัก คุณจะต้องเสียค่าสมัครงานเป็นจำนวนเงิน $500 ต่อการเข้าทำงาน 1 ครั้ง\
            \n- แต่ถ้าหากคุณยังไม่ออกจากงานก็จะสามารถทำงานต่อได้อีกครั้งโดยไม่เสียเงินใดๆ\n[การขายของอาชีพ]\n- การขายของอาชีพคุณจะต้องไปยังตลาดกลาง LS ที่ใกล้กับโรงพยาบาล ที่นั่นจะเป็นจุดรวมสินค้าต่างๆของเซิฟเวอร์เอาไว้\n[การเช็คราคาตลาด]\n- การเช็คราคาตลาดคุณจะต้องไปยังตลาดกลางเช่นกันและจะมีจุดเช็คราคาตลาดอยู่");
            Dialog_ShowEasy(playerid, HelpFindJob, DIALOG_STYLE_MSGBOX, "วิธีการหาอาชีพทำหรืออาชีพเสริมทำ", string, "ตกลง", "");
        }
        if(listitem == 3){
            format(string, sizeof(string), "[การคราฟไอเท็มต่างๆ]\n- การคราฟไอเท็มคุณจะต้องไปที่ตลาดกลางเมือง LS เพื่อไปยังจุดคราฟของต่างๆที่อยู่ในตลาดนั้น\n[ตารางการคราฟไอเท็ม]\
            \n- 'Fishing Rod (เบ็ดตกปลา)' จะต้องใช้ >> 'Ore (แร่เหล็ก) จำนวน 10 ชิ้น' + 'Wood (ไม้) จำนวน 15 ชิ้น'\
            \n- 'Short Knife (ชิ้นส่วนมีด)' จะต้องใช้ >> 'Ore (แร่เหล็ก) จำนวน 10 ชิ้น' + 'Ore (แร่เหล็ก) จำนวน 10 ชิ้น'\
            \n- 'Knife (มีด) จะต้องใช้ >> 'Short Knife (ชิ้นส่วนมีด) จำนวน 1 ชิ้น' + 'Wood (ไม้) จำนวน 20 ชิ้น'\
            \n- 'Wrench (ประแจ) จะต้องใช้ >> 'Ore (แร่เหล็ก) จำนวน 4 ชิ้น' + 'Ore (แร่เหล็ก) จำนวน 4 ชิ้น'\
            \n- 'Repair Kit (กล่องซ่อม) จะต้องใช้ >> 'Wrench (ประแจ) จำนวน 1 ชิ้น' + 'Wrench (ประแจ) จำนวน 1 ชิ้น'\
            \n- 'Wheel Car (ล้อรถยนต์) จะต้องใช้ >> 'Raw Rubber Sheet (ยางแผ่น) จำนวน 20 ชิ้น' + 'Raw Rubber Sheet (ยางแผ่น) จำนวน 20 ชิ้น'\
            \n- 'Drill Tool (เครื่องขุดบ่อน้ำมัน) จะต้องใช้ >> 'Drill Tool Blueprint (พิมพ์เขียวเครื่องขุด) จำนวน 1 ชิ้น' + 'ไม้ (Wood) จำนวน 10 ชิ้น'\
            \n- 'ลังไม้ (Wooden Crate) จะต้องใช้ >> 'Wood (ไม้) จำนวน 5 ชิ้น' + 'Wood (ไม้) จำนวน 5 ชิ้น'\
            \n- 'น้ำผลไม้แอปเปิ้ลเขียว (Green Apple Juice) จะต้องใช้ >> 'Green Apple (แอปเปิ้ลเขียว) จำนวน 1 ชิ้น' + 'Green Apple (แอปเปิ้ลเขียว) จำนวน 1 ชิ้น'");
            Dialog_ShowEasy(playerid, DIALOGCRAFTHELP, DIALOG_STYLE_MSGBOX, "การคราฟไอเท็ม", string, "ตกลง", "");
        }
        if(listitem == 4){
            if(GetGroupType(playerid) == GROUP_MEDIC){
                format(string, sizeof(string), "[คำสั่งหมอ]: /r, /d, /f, /chm, /dischm, /ticket, /gov, /siren, /siren2");
                Dialog_ShowEasy(playerid, DIALOGSHOWGROUPHELP, DIALOG_STYLE_MSGBOX, "กลุ่ม แพทย์/หมอ", string, "ตกลง", "");
            }
            else if(GetGroupType(playerid) == GROUP_POLICE){
                format(string, sizeof(string), "[คำสั่งตำรวจ]: /r, /d, /f, /chm, /ticket, /frisk, /taser, /cuff, /uncuff, /mdc\
                \n/jailtime, /unjail, /gov, /lspd, /rb, /rrb, /rrball, /checkdv, /beanbag, /friskhome, /breakhome\
                \n/summons (/หมายเรียก) - (หากใช้มั่วจะทำการลบระบบนี้ออกทันที), /siren, /siren2, /removenitro");
                Dialog_ShowEasy(playerid, DIALOGSHOWGROUPHELP, DIALOG_STYLE_MSGBOX, "กลุ่ม ตำรวจ", string, "ตกลง", "");
            }
            else if(GetGroupType(playerid) == GROUP_NATIONAL){
                format(string, sizeof(string), "[คำสั่งตำรวจ]: /r, /d, /f, /chm, /ticket, /frisk, /taser, /cuff, /uncuff, /mdc\
                \n/jailtime, /unjail, /gov, /siren, /siren2, /removenitro");
                Dialog_ShowEasy(playerid, DIALOGSHOWGROUPHELP, DIALOG_STYLE_MSGBOX, "กลุ่ม ตำรวจ", string, "ตกลง", "");
            }
            else if(GetGroupType(playerid) == GROUP_GANG){
                
            }
            else if(GetGroupType(playerid) == GROUP_MECHANIC){
                format(string, sizeof(string), "[คำสั่งช่างยนต์]: /chm, /clearmods");
                Dialog_ShowEasy(playerid, DIALOGSHOWGROUPHELP, DIALOG_STYLE_MSGBOX, "กลุ่ม รัฐบาล", string, "ตกลง", "");
            }
            else if(GetGroupType(playerid) == GROUP_GOV){
                format(string, sizeof(string), "[คำสั่งรัฐบาล]: /r, /d, /f, /chm");
                Dialog_ShowEasy(playerid, DIALOGSHOWGROUPHELP, DIALOG_STYLE_MSGBOX, "กลุ่ม รัฐบาล", string, "ตกลง", "");
            }
            else{
                format(string, sizeof(string), "คุณไม่มีกลุ่ม...");
                Dialog_ShowEasy(playerid, DIALOGSHOWGROUPHELP, DIALOG_STYLE_MSGBOX, "กลุ่ม", string, "ตกลง", "");
            }
        }
        if(listitem == 5){
            format(string, sizeof(string), "[คำสั่งทั่วไป]: /o, /tw, /animcmds, /me, /do, /drag, /detain, /eject, /tickets\
            \n[คำสั่งเกี่ยวกับบ้าน]: /thouse, /givekeyhome (/gkh), /cancelhomerent (/cchr), /findmyhome, /viewrents, /doorbell\
            \n[คำสั่งเกี่ยวกับยานพาหนะ]: /gtk");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "คำสั่งทั่วไป", string, "ตกลง", "");
        }
    }
    return 1;
}

ShowHelpForJobPlayer(playerid){
    new type = PlayerData[playerid][pJob];
    new string[1024];
    switch(type){
        case FARMERJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก อาชีพชาวนา\
            \n  หลังจากกดเลือก GPS แล้วระบบจะแสดงตำแหน่งจุดที่ทำงาน ของอาชีพชาวนาตามไปยังจุดสีแดงในแมพ\
            \n  เมื่อมาถึงจุดหมายแล้ว ให้ไปตรงจุด สมัครงานชาวนา กด Y เพื่อสมัคร เสียค่าสมัคร 500 บาทต่อครั้งหากไม่ได้\
            \n  ออกจากงานคุณสามารถกลับมาทำงานได้อีกโดยไม่ต้องเสียเงิน  หลังจากนั้นให้ผู้เล่นเดินไปตรงจุดเพื่อเริ่มทำงาน\
            \n  โดยการกด Y ระบบจะแจ้งว่าให้ผู้เล่นไปขึ้นรถไถนา  เพื่อทำการเก็บเกี่ยวข้าวเมื่อขึ้นรถเกี่ยวข้าว\
            \n  กด Y สตาร์ทรถแล้วให้ผู้เล่น ขับรถเข้าไปเหยียบข้าว โดยการขับรถเข้าไปแล้วจอดอยู่กับที่จะมีข้อความขึ้นว่าเราเก็บได้ 1/50KG\
            \n  เมื่อผู้เล่น เก็บเกี่ยวข้าวครบ 50/50KG ระบบจะนำพาคุณไปยังจุดโพดเสด เมื่อถึงจุดโพเสดแล้ว\
            \n  ให้กด Y และรอการโพเสด เราจะได้ไอเทม Rice(ข้าว)  เพื่อนำไปขายที่ตลาด LS\
            \n  * หมายเหตุ ผู้เล่นไม่จำเป็นต้องเก็บเต็มจำนวน 50/50 เราสามารถนำไปโพเสดได้ตามจำนวนที่ท่านต้องการ *");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ชาวนา", string, "ตกลง", "");
        }
        case BUILDJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก อาชีพก่อสร้าง\
            \n  หลังจากกดเลือก GPS แล้วระบบจะแสดงตำแหน่งจุดที่ทำงานของ อาชีพก่อสร้างตามไปยังจุดสีแดงในแมพ\
            \n  เมื่อคุณถึงจุดหมายแล้ว ให้ไปตรงจุด สมัครงานก่อสร้าง กด Y เพื่อสมัคร เสียค่าสมัคร 500 บาท ต่อครั้ง\
            \n  หากไม่ได้ออกจากงานคุณสามารถกลับมาทำงานได้อีกโดยไม่เสียเงิน เมื่อสมัครเสร็จแล้วก่อนที่จะเริ่มทำงาน\
            \n  ให้คุณเดินไปตรงจุดเปลี่ยนชุดทำงานก่อน โดยทำการกด Y ที่จุดเปลี่ยนชุดท่านสามารถเริ่มงานได้ทันที\
            \n  โดยการ ไปเบิกกระสอบปูน กด Y เพื่อเบิกกระสอบปูนและเดินขึ้นไปส่งตามจุดสีแดงในแมพอยู่\
            \n  ภายในอาคารก่อสร้าง เมื่อไปถึงเป็นอันเสร็จสิ้น การแบกปูน 1 รอบได้รับค่าจ้างตามที่กำหนด\
            \n  คุณสามารถทำการแบกปูนได้เรื่อยๆ ตามที่คุณต้องการ");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ก่อสร้าง", string, "ตกลง", "");
        }
        case FISHJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก อาชีพชาวประมง\
            \n  ** อาชีพนี้คุณต้องมี 'เบ็ดตกปลา' อุปกรณ์ในการทำงานถึงจะทำได้ ** คุณสามารถดูวิธีการหาได้ในเมนู /help\
            \n  หลังจากกดเลือก GPS แล้วระบบจะแสดงตำแหน่งจุดที่ทำงานของ อาชีพชาวประมงตามไปยังจุดสีแดงในแมพ\
            \n  หากไม่ได้ออกจากงานคุณสามารถกลับมาทำงานได้อีกโดยไม่เสียเงิน\
            \n  หลังจากนั้นขับเรือไปยังจุด สีแดงกลางทะเล เมื่อถึงแล้วให้จอด หรือ ดับเรือ แล้วเดินมาหลังเรือ กด Y เพื่อทำการตกปลาตก\
            \n  ตกปลา 1 ครั้ง คุณจะได้รับ ปลาจำนวน 20 ตัว เมื่อคุณตกปลาเสร็จแล้ว ให้นำปลาไปขายที่ตลาดกลางเมือง LS\
            \n  * หมายเหตุ Fish(ปลา) Fishing Rod (เบ็ดตกปลา) *");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ชาวประมง", string, "ตกลง", "");
        }
        case GASJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก อาชีพขนส่งแก๊ส\
            \n  หลังจากกดเลือก GPS แล้วระบบจะแสดงตำแหน่งจุดที่ทำงานของอาชีพส่งแก๊สตามไปยังจุดสีแดงในแมพเมื่อคุณถึงจุดหมายแล้ว\
            \n  ให้ไปที่จุดสมัครงานขนส่งแก๊ส กด Y เพื่อสมัครเสียค่าสมัคร 500 บาท ต่อครั้ง หากไม่ได้ออกจากงานคุณสามารถกลับมาทำงานได้อีกโดยไม่เสียเงิน\
            \n  เมื่อสมัครเสร็จแล้วให้คุณ ไปยังจุดจอดรถสำหรับส่งแก๊สเมื่อขึ้นรถแล้วให้ขับไปยันโกดังที่อยู่ข้างหน้าเพื่อเข้าไป หยิบแก๊สใส่หลังรถของคุณ\
            \n  ขึ้นรถและกดเปิด Trunk และเดินไปยังจุดที่มีถึงแก๊สกด Y เพื่อหยิบแก๊ส และเดินมาที่หลังรถและกดต่อย\
            \n  เพื่อวางถังแก๊สใส่หลังรถ หลังจากนั้นให้คุณ ขึ้นรถและกดเปิด Trunk ปิดท้ายรถและขึ้นรถ ระบบจะบอกจุดหมายจุดที่คุณต้องไปส่ง และขับไปยังจุดสีแดงในแมพ\
            \n  เมื่อถึงจุดหมายส่งแล้วให้คุณทำการเปิดท้ายรถกระบะ กดต่อยอีกครั้งเพื่อทำการหยิบถังแก๊สลงจากรถ และเดินเข้าไปยังจุดสีแดงเพื่อส่งแก๊ส\
            \n  * เป็นอันเสร็จสิ้นการขนส่งแก๊ส 1 รอบและได้รับค่าจ้าง *");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ขนส่งแก๊ส", string, "ตกลง", "");
        }
        case COWJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก อาชีพฆ่าวัว\
            \n  ** อาชีพนี้คุณจำเป็นต้องมี 'มีด' อุปกรณ์ในการทำงานถึงจะทำได้ ** คุณสามารถดูวิธีการหาอุปกรณ์ได้ในเมนู /help\
            \n  หลังจากกดเลือก GPS แล้วระบบจะแสดงตำแหน่งจุดที่ทำงานของอาชีพฆ่าวัวตามไปยังจุดสีแดงในแมพเมื่อคุณถึงจุดหมายแล้ว\
            \n  ให้ไปที่จุด สมัครงานฆ่าวัว กดYเพื่อสมัครเสียค่าสมัคร 500 บาท ต่อครั้ง หากไม่ได้ออกจากงานคุณสามารถกลับมาทำงานได้อีกโดยไม่เสียเงิน\
            \n  เมื่อสมัครเสร็จแล้วให้คุณไปยังจุดเปลี่ยนชุด โดยการกด Y เพื่อเปลี่ยนชุดทำงานหลังจากนั้นให้คุณกดไปที่กระเป๋าสัมภาระและเรียกกดใช้งาน\
            \n  Knife(มีด) เพื่อใช้อุปกรณ์ในการฆ่าวัว เมื่อเข้าไปถึงในคอกแล้วให้ทำการ วิ่งไล่ฆ่าวัว เมื่อวัวล้วให้ทำการกดแทงวัวให้ล้ม  เมื่อวัวล้มแล้ว\
            \n  ให้คุณทำการกด Y เมื่อทำการเก็บเนื้อวัวสด[Raw จากซากศพวัว 1 ตัวคุณจะได้รับ เนื้อวัว จำนวน 10 ชิ้น คุณสามารถเก็บจนกว่ากระเป๋าเต็ม\
            \n  เมื่อแปรรูปเสร็จแล้วคุณสามารถนำไปขายที่ตลาดกลางเมือง LS ได้\
            \n  * หมายเหตุ RawCowMeat(เนื้อวัวสด) PackCowmeat(แพ็คเนื้อวัว) *");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ฆ่าวัว", string, "ตกลง", "");
        }
        case ENGJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก อาชีพช่างไฟ\
            \n  หลังจากคุณไปยังจุดสมัครอาชีพ เมื่อสมัครอาชีพเสร็จเรียบร้อย คุณจะต้องไปยังจุดเปลี่ยนชุด\
            \n  จากนั้นให้คุณเปลี่ยนชุดเป็นชุดทำงาน แล้วคุณจะได้รับกล่องซ่อมมาด้วย ให้คุณไปขึ้นรถทำงาน\
            \n  จากนั้นจะมี Checkpoint สีแดงที่ระบบได้ทำการค้นหาจุดเสาร์ไฟที่เสีย ให้คุณไปยังจุดนั้นเพื่อทำการซ่อมมัน\
            \n  หลังจากคุณซ่อมเสร็จคุณจะได้รับค่าตอบแทนเลยทันที จากนั้นระบบจะทำการค้นหาเสาร์ไฟต้นต่อไปที่คุณจะต้องไปซ่อม\
            \n  หากคุณต้องการเลิกทำงานให้ขับรถกลับไปยังจุดเปลี่ยนชุดแล้วเปลี่ยนชุดกลับ");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ช่างไฟ", string, "ตกลง", "");
        }
        case JELLYJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก เก็บแมงกระพรุน\
            \n  * คุณจำเป็นต้องมี เสื้อชูชีพ ในการทำอาชีพนี้ โดยการไปซื้อได้ที่ร้านสะดวกซื้อที่ ตลาดกลาง\
            \n  เมื่อคุณไปถึงจุดสมัครงานให้คุณสมัครงานจากนั้นให้กดใช้ไอเท็มเสื้อชูชีพในกระเป๋าเพื่อใส่\
            \n  และให้คุณกระโดดลงน้ำเพื่อหาแมงกระพรุนและเก็บมัน จากนั้นให้คุณนำมันไปขายที่ตลาดกลาง");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ เก็บแมงกระพรุน", string, "ตกลง", "");
        }
        case WEAPONDEALERJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก พ่อค้าอาวุธ\
            \n  * คุณจะต้องวิ่งดินปืนเพื่อเก็บ Skills การคราฟอาวุธ โดยเริ่มจากไปที่หลังร้านอาวุธเพื่อทำการเริ่มวิ่งดินปืน\
            \n  เมื่อคุณได้วัตถุในการคราฟครบแล้วให้มาหน้าร้านอาวุธจะมี Icon ตัว I ข้างๆจุดสมัคร\
            \n  และคุณสามารถคราฟได้จากที่นั่น คุณจะต้องฝากวัตถุเข้าไปในคลังก่อนจะคราฟ");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ พ่อค้าอาวุธ", string, "ตกลง", "");
        }
        case GARBAGEJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก คนเก็บขยะ\
            \n  * เมื่อคุณสมัครงานเสร็จให้คุณเปลี่ยนชุดเพื่อเริ่มทำงาน จากนั้นให้คุณไปขึ้นรถ\
            \n  ระบบจะทำการ Mark Checkpoint สีแดงให้คุณและให้คุณไปยังตำแหน่งนั้นเพื่อเก็บขยะ\
            \n  และเมื่อคุณได้ถุงขยะมาอยู่ในมือให้คุณเดินไปหลังรถเก็บขยะและกด 'ต่อย' เพื่อใส่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ คนเก็บขยะ", string, "ตกลง", "");
        }
        case RUBBERJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก กรีดยาง\
            \n  * เมื่อคุณสมัครงานเสร็จคุณจะต้องไปยังตำแหน่ง I ที่อยู่ข้างๆจุดสมัครงาน เพื่อรับอุปกรณ์\
            \n  จากนั้นให้คุณเดินไปที่ต้นยางและกด 'ต่อย' เพื่อเริ่มกรีดยาง จากนั้นเมื่อน้ำยางคุณเต็มถัง\
            \n  ให้คุณเดินมายังโกดังใกล้ๆจุดสมัคร เพื่อเริ่มทำการ Process น้ำยางให้เป็นแผ่น");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ กรีดยาง", string, "ตกลง", "");
        }
        case CLOTHJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก ขนเสื้อผ้า\
            \n  * เมื่อคุณสมัครงานเสร็จให้คุณขึ้นรถขนเสื้อผ้าและจะมี Checkpoint สีแดงขึ้นให้คุณไปยังจุดนั้นเพื่อรับเสื้อผ้า\
            \n  เมื่อรับเสื้อผ้าคุณจะได้กล่องเสื้อผ้า และให้เดินไปหลังรถเสื้อผ้าให้กด 'ต่อย' เพื่อทำการเอากล่องใส่หลังรถ เต็ม 5 กล่อง\
            \n  เมื่อใส่จนเต็มให้คุณขึ้นรถจากนั้นจะมี Dialog ให้คุณเลือกร้านค้าที่ขาดสินค้า และไปส่งยังร้านนั้น");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ขนเสื้อผ้า", string, "ตกลง", "");
        }
        case SEEKERJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก หาสมบัติ\
            \n  * เมื่อคุณสมัครงานเสร็จแล้วคุณจะต้องรับอุปกรณ์กันรังสีและอุปกรณ์หาสมบัติก่อน\
            \n  หาก คุณเข้าไปโดยได้ไม่ได้รับอุปกรณ์ คุณอาจจะได้รับอันตรายจากรังสีภายในบริเวณนั้น สามารถถึงแก่ชีวิตได้\
            \n  เมื่อคุณตรวจหาเจอให้คุณกด 'Y' เพื่อเก็บและเมื่อเก็บจนพอใจแล้วก็สามารถนำมาล้างได้ที่หลังจุดสมัครงาน จากนั้นก็เอาไปขายที่ตลาด");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ขนเสื้อผ้า", string, "ตกลง", "");
        }
        case GARDENER:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก คนดูแลสวน\
            \n  * เมื่อคุณสมัครงานแล้วให้คุณไปที่จุดเริ่มทำงานจากนั้นคุณจะได้รับบัวรดน้ำ\
            \n  ให้คุณลงไปยังสวนด้านล่างเพื่อทำการรดน้ำให้ครบตามจำนวนที่กำหนด\
            \n  เมื่อคุณรดน้ำครบแล้วจะต้องขึ้นมารับเงินด้านบน หากต้องการทำอีกครั้งก็สามารถลงไปรดน้ำต้นไม้ได้อีก");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ขนเสื้อผ้า", string, "ตกลง", "");
        }
        case OILJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก ขุดน้ำมัน\
            \n  * อาชีพนี้คุณจะต้องมี Drill Tool หรืออุปกรณ์ขุดน้ำมัน โดยสามารถคราฟได้ที่ตลาดกลาง\
            \n  เมื่อถึงจุดก็สมัครอาชีพและเดินหาบ่อน้ำมันแล้วเริ่มขุดได้เลย จากนั้นเมื่อได้น้ำมันดิบครบแล้วให้ไปยังจุด แปรรูปน้ำมันดิบ และเริ่มแปรรูป\
            \n  เมื่อแปรรูปน้ำมันดิบเป็นน้ำมันแปรรูปเสร็จ ให้นำไปขายยังพ่อค้าที่รับซื้อน้ำมันแปรรูป");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ขุดน้ำมัน", string, "ตกลง", "");
        }
        case SHELLJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก เก็บหอย\
            \n  * อาชีพนี้คุณจำเป็นต้องมี 'Knife' เพื่อทำการแร่หอยออกมา โดยคุณสามารถไปคราฟได้ที่ตลาดกลาง\
            \n  เมื่อได้มีดมาแล้วให้ทำการกดใช้มีดจากนั้นก็เดินหาหอยแล้วเก็บได้เลย\
            \n  เมื่อเก็บจนเต็มกระเป๋าคุณสามารถนำหอยไปขายที่ตลาดกลางได้");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ เก็บหอย", string, "ตกลง", "");
        }
        case ORANGEJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก เก็บส้ม\
            \n  * อาชีพนี้คุณจำเป็นต้องมี 'Wooden Crate' เพื่อที่จะนำส้มให้ลังของคุณ สามารถคราฟได้ที่ตลาดกลาง\
            \n  เมื่อคุณมาถึงที่ทำงานแล้วให้กดใช้งาน 'Wooden Crate' แล้วจากนั้นไปกด 'ต่อย' ที่ต้นส้ม แล้วจะทำการเก็บส้มทันที\
            \n  หลังจากได้ส้มมาอยู่ในลังแล้วให้เดินออกมาเพื่อนำส้มไปชั่งน้ำหนัก หลังจากนั้นเมื่อได้ส้มเต็มกระเป๋าก็สามารถนำไปขายได้ทีตลาดกลาง");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ เก็บหอย", string, "ตกลง", "");
        }
        case SHARKJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก ตกปลาฉลาม\
            \n  * อาชีพนี้จำเป็นต้องใช้ เบ็ดตกปลา (Fishing Rod)\
            \n  เมื่อคุณสมัครงานเสร็จหากคุณมีเรือส่วนตัวก็ให้ทำการขึ้นเรือส่วนตัวจากนั้นจะ Checkpoint นำทางไปยังจุดตก\
            \n  เมื่อเข้าไปภายในวงให้ทำการกด 'ต่อย' เพื่อเริ่มตก\
            \n  เมื่อคุณกด 'ต่อย' ตกแล้วจะรอเวลาที่ปลาฉลามติดเบ็ดจากนั้นจะมีข้อความแจ้งเตือนให้คุณกด 'ต่อย' เพื่อดึงเบ็ดขึ้นมา\
            \n  หากปลาติดเบ็ดแล้วและได้ดึงเบ็ดขึ้นในเวลาที่กำหนดปลาก็จะหลุดออกจากเบ็ดไป\
            \n  ปลาฉลามก็จะสามารถนำไปขายที่ตลาดกลางของเมือง SF ได้");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ตกปลาฉลาม", string, "ตกลง", "");
        }
        case PIZZAJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก ทำพิซซ่า\
            \n  * อาชีพนี้คุณจำเป็นจะต้องมีวัตถุดิบในการทำพิซซ่า\
            \n  1. เนื้อวัวสด (Raw Cow Meat) | 2. มะเขือเทศ (Tomato) > ซื้อได้ที่ตลาดสดที่ตลาดกลาง\
            \n  โดยทางร้านพิซซ่าจะมี ซอสมะเขือเทส และ มายองเนสให้ฟรี\
            \n  เมื่อคุณสมัครงานแล้วให้คุณเข้าไปภายในร้านเพื่อสามารถทำพิซซ่าตามที่ Order สั่งได้");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ทำพิซซ่า", string, "ตกลง", "");
        }
        case DELIOILJOB:{
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพ > เลือก ขนส่งน้ำมัน\
            \n  * อาชีพนี้เมื่อคุณสมัครงานแล้วให้คุณขึ้นรถบรรทุกจากนั้นทำไปต่อพ่วงน้ำมันและกด 'Y' เพื่อไปรับน้ำมัน\
            \n  หลังจากรับน้ำมันเรียบร้อยระบบจะให้คุณเลือกปั้มน้ำมันที่จะไปส่ง\
            \n  เมื่อคุณเลือกเรียบร้อยก็ขับรถไปยังจุดสีแดง และ เมื่อถึงจุดแดงคุณก็จะได้รับเงินตอบแทน");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพ ทำพิซซ่า", string, "ตกลง", "");
        }
        default:{
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "คุณไม่มีอาชีพ", "คุณไม่ได้สมัครอาชีพอะไรอยู่เลย...", "ตกลง", "");
        }
    }
    return 1;
}

ShowHelpForSideJobPlayer(playerid){
    Dialog_ShowEasy(playerid, DIALOGSIDEJOBHELP, DIALOG_STYLE_LIST, "อาชีพเสริม", "- ตัดไม้\n- ขุดเหมือง\n- ขนพัสดุ\n- ปลูกพืช", "เลือก", "ยกเลิก");
}

Dialog:DIALOGSIDEJOBHELP(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    new string[1024];
    if(response){
        if(listitem == 0){
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพเสริม > เลือก ตัดไม้\
            \n  เมื่อคุณกดเปิด GPS ระบบจะนำทางคุณไปยังจุดเริ่มทำงานจากนั้นให้กด Y เพื่อเปลี่ยนชุดและรับอุปกรณ์ให้เรียบร้อย\
            \n  หลังจากเปลี่ยนชุดและรับอุปกรณ์เรียบร้อยแล้ว จะมี Checkpoint สีแดงขึ้นใน Map ให้คุณเดินไปยังจุดนั้น\
            \n  เมื่อไปถึงจุดที่ขึ้นใน Map ของคุณจะเป็นต้นไม้ที่คุณจะต้องเข้าไปตัด โดยวิธีคือเดินเข้าไปในวง Checkpoint แดงเพื่อเริ่มตัด\
            \n  เมื่อตัดเสร็จคุณจะได้รับ Wood (ไม้) + 2 จากนั้นระบบจะสุ่มต้นไม้ที่คุณสามารถตัดได้ให้\
            \n  ถ้าหากคุณต้องการจะเลิกตัดไม้ให้เดินกลับไปจุดที่เริ่มงานและคืนอุปกรณ์และเปลี่ยนชุดกลับ\
            \n  * เมื่อต้นไม้ต้นนั้นหมดคุณจะไม่สามารถตัดได้ ต้องรอ 1 ชม. เพื่อให้ระบบรีต้นไม้ *");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพเสริม ตัดไม้", string, "ตกลง", "");
        }
        if(listitem == 1){
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพเสริม > เลือก ขุดเหมือง\
            \n  เมื่อคุณกดเปิด GPS ระบบจะนำทางคุณไปยังจุดเริ่มทำงานจากนั้นให้กด Y เพื่อเปลี่ยนชุดและรับอุปกรณ์ให้เรียบร้อย\
            \n  หลังจากเปลี่ยนชุดและรับอุปกรณ์เรียบร้อยแล้ว ระบบจะสุ่มจุดที่คุณสามารถขุดเหมืองได้ จากนั้นให้คุณเดินไปที่ Checkpoint สีแดง เพื่อเริ่มขุด\
            \n  เมื่อคุณขุดจนเสร็จจะมีกองแร่ใส่ในรถเข็นของคุณ จากนั้นคุณจะต้องไปส่งแร่ตามจุด Checkpoint สีแดง และคุณจะได้รับ Ore (แร่) + 2\
            \n  หลังจากคุณส่งแร่เสร็จเรียบร้อยแล้วระบบจะสุ่มจุดที่คุณสามารถขุดได้อีกครั้ง และคุณก็ทำแบบเดิมไปเรื่อยๆ\
            \n  ถ้าหากต้องการเลิกขุดให้คุณกลับไปที่จุดเริ่มงานและคืนอุปกรณ์และเปลี่ยนชุดกลับเป็นเหมือนเดิม\
            \n  * หากจุดแร่นั้นแร่หมดคุณจะไม่สามารถขุดได้ *");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพเสริม ขุดเหมือง", string, "ตกลง", "");
        }
        if(listitem == 2){
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพเสริม > เลือก ขนพัสดุ\
            \n  อาชีพนี้จะเป็นอาชีพสำหรับนักโทษที่อยู่เรือนจำ คนภายนอกจะไม่สามารถเข้าไปทำได้");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพเสริม ขนพัสดุ", string, "ตกลง", "");
        }
        if(listitem == 3){
            format(string, sizeof(string), "- /gps > ค้นหาอาชีพเสริม > เลือก ปลูกพืช\
            \n  คุณสามารถไปซื้อเมล็ดพืชจากตลาดสด SF มาปลูกได้ที่โซน\
            \n  โดยการปลูกเพียงเข้ามาในโซนก็จะสามารถกดใช้งานเมล็ดเพื่อปลูกได้\
            \n  และผลผลิตคุณสามารถนำไปขายยังตลาดได้");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "อาชีพเสริม ปลูกพืช", string, "ตกลง", "");
        }
    }
    return 1;
}

//-------------------------------------------------------------------//
Dialog:PASSADMIN(playerid, response, listitem, inputtext[]){
    if(!response)
        return Dialog_ShowEasy(playerid, PASSADMIN, DIALOG_STYLE_INPUT, "รหัสลับ", "* คุณจำเป็นต้องกรอกรหัสลับแอดมิน *\nกรุณาตั้งรหัสลับแอดมินของคุณ:", "ตกลง", "ยกเลิก");

    if(response){
        if (isnull(inputtext))
            return Dialog_ShowEasy(playerid, PASSADMIN, DIALOG_STYLE_INPUT, "รหัสลับ", "* คุณจำเป็นต้องกรอกรหัสลับแอดมิน *\nกรุณาตั้งรหัสลับแอดมินของคุณ:", "ตกลง", "ยกเลิก");

        strmid(PlayerData[playerid][pPassAdmin], inputtext, 0, strlen(inputtext), 64);
        PlayerData[playerid][pIsPassAdmin] = 1;
        SendClientMessage(playerid, COLOR_YELLOW, "คุณได้ตั้งรหัสผ่านแอดมินเรียบร้อยแล้ว");
    }
    return 1;
}

Dialog:INPUTPASSADMIN(playerid, response, listitem, inputtext[]){
    if(!response)
        return Kick(playerid);

    if(response){
        if (isnull(inputtext))
            return Dialog_ShowEasy(playerid, INPUTPASSADMIN, DIALOG_STYLE_PASSWORD, "รหัสลับ", "* คุณจำเป็นต้องกรอกรหัสลับแอดมิน *\nกรุณากรอกรหัสลับสำหรับแอดมิน:", "ตกลง", "ยกเลิก");

        if(!strcmp(inputtext, PlayerData[playerid][pPassAdmin], true)){
            SendClientMessage(playerid, COLOR_SERVER, "{23D101}| {FFFFFF}คุณได้ยืนยันตัวแอดมินสำเร็จ");
        }
        else{
            return Dialog_ShowEasy(playerid, INPUTPASSADMIN, DIALOG_STYLE_PASSWORD, "รหัสลับ", "* คุณกรอกรหัสผิดพลาด *\nกรุณากรอกรหัสลับสำหรับแอดมิน:", "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:DialogCheckCrm(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;
    if(response){
        if(listitem == 0){
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "5 อันดับการเงินสูงสุด", TopRankMoney, "ตกลง", "");
        }
        if(listitem == 1){
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "5 อันดับเลเวลสูงสุด", TopRankLevel, "ตกลง", "");
        }
        if(listitem == 2){
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "5 อันดับชั่วโมงออนไลน์สูงสุด", TopRankHour, "ตกลง", "");
        }
        if(listitem == 3){
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "5 อันดับ แก๊งที่มีเงิน สูงสุด", TopRankGangMoney, "ตกลง", "");
        }
        if(listitem == 4){
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "5 อันดับการเงินในธนาคารสูงสุด", TopRankBank, "ตกลง", "");
        }
        if(listitem == 5){
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "5 อันดับการเงินแดงสูงสุด", TopRankRedMoney, "ตกลง", "");
        }
        if(listitem == 6){
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "5 อันดับ พ้อยแห่งความสำเร็จแก๊ง สูงสุด", TopRankPointGang, "ตกลง", "");
        }
        if(listitem == 7){
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "5 อันดับ ชนะการแข่งขัน Racing", TopRankRacingWin, "ตกลง", "");
        }
        if(listitem == 8){
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "5 อันดับ แพ้การแข่งกัน Racing", TopRankRacingLose, "ตกลง", "");
        }
    }
    return 1;
}

Dialog:GroupLocker(playerid, response, listitem, const inputtext[]){
    if (PlayerData[playerid][pGroupEdit] == -1)
	    return 0;

    if(response){
        if(listitem == 0){
            new
                string[256];

            string[0] = 0;

            for (new i = 0; i < 10; i ++){
                if (GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][i])
                    format(string, sizeof(string), "%sอาวุธ %d: %s\n", string, i + 1, ReturnWeaponName(GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][i]));

                else format(string, sizeof(string), "%sว่าง\n", string);
            }
            Dialog_ShowEasy(playerid, GroupWeapons, DIALOG_STYLE_LIST, "Locker Weapons", string, "เลือก", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:GroupWeapons(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pGroupEdit] == -1)
	    return 0;

	if (response)
	{
	    PlayerData[playerid][pSelectedSlot] = listitem;
	    Dialog_ShowEasy(playerid, GroupWeapon, DIALOG_STYLE_LIST, "แก้ไขอาวุธ", "ตั้งค่าอาวุธ (%d)\nตั้งค่ากระสุน (%d)\nลบล้างช่อง", "เลือก", "ยกเลิก", GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][PlayerData[playerid][pSelectedSlot]], GroupData[PlayerData[playerid][pGroupEdit]][groupAmmo][PlayerData[playerid][pSelectedSlot]]);
	}
	return 1;
}

Dialog:GroupWeapon(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pGroupEdit] == -1)
	    return 0;

	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        	Dialog_ShowEasy(playerid, GroupWeaponID, DIALOG_STYLE_INPUT, "ตั้งค่าอาวุธ", "อาวุธในปัจจุบัน: %s (%d)\n\nโปรดป้อนไอดีอาวุธใหม่สำหรับช่อง %d:", "ตกลง", "ยกเลิก", ReturnWeaponName(GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][PlayerData[playerid][pSelectedSlot]]), GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

			case 1:
	            Dialog_ShowEasy(playerid, GroupWeaponAmmo, DIALOG_STYLE_INPUT, "ตั้งค่ากระสุน", "กระสุนในปัจจุบัน: %d\n\nโปรดป้อนกระสุนใหม่สำหรับช่อง %d:", "ตกลง", "ยกเลิก", GroupData[PlayerData[playerid][pGroupEdit]][groupAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

			case 2:
			{
			    GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][PlayerData[playerid][pSelectedSlot]] = 0;
				GroupData[PlayerData[playerid][pGroupEdit]][groupAmmo][PlayerData[playerid][pSelectedSlot]] = 0;

				Group_Save(PlayerData[playerid][pGroupEdit]);

				dialog_GroupLocker(playerid, 1, 1, "\1");
				SendClientMessageEx(playerid, -1, "คุณได้ลบล้างอาวุธในช่องที่ %d", PlayerData[playerid][pSelectedSlot] + 1);
			}
	    }
	}
	else {
	    dialog_GroupLocker(playerid, 1, 1, "\1");
	}
	return 1;
}

Dialog:GroupWeaponID(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pGroupEdit] == -1)
	    return 0;

	if (response)
	{
	    new weaponid = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_ShowEasy(playerid, GroupWeaponID, DIALOG_STYLE_INPUT, "ตั้งค่าอาวุธ", "อาวุธในปัจจุบัน: %s (%d)\n\nโปรดป้อนไอดีอาวุธใหม่สำหรับช่อง %d:", "ตกลง", "ยกเลิก", ReturnWeaponName(GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][PlayerData[playerid][pSelectedSlot]]), GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

		if (weaponid < 0 || weaponid > 46)
		    return Dialog_ShowEasy(playerid, GroupWeaponID, DIALOG_STYLE_INPUT, "ตั้งค่าอาวุธ", "ข้อผิดพลาด: ไอดีอาวุธต้องไม่ต่ำกว่า 0 หรือมากกว่า 46\n\nอาวุธในปัจจุบัน: %s (%d)\n\nโปรดป้อนไอดีอาวุธใหม่สำหรับช่อง %d:", "ตกลง", "ยกเลิก", ReturnWeaponName(GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][PlayerData[playerid][pSelectedSlot]]), GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

        GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][PlayerData[playerid][pSelectedSlot]] = weaponid;
        Group_Save(PlayerData[playerid][pGroupEdit]);

		Dialog_ShowEasy(playerid, GroupWeapon, DIALOG_STYLE_LIST, "ตั้งค่าอาวุธ", "ตั้งค่าอาวุธ (%d)\nตั้งค่ากระสุน (%d)\nลบล้างช่อง", "เลือก", "ยกเลิก", GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][PlayerData[playerid][pSelectedSlot]], GroupData[PlayerData[playerid][pGroupEdit]][groupAmmo][PlayerData[playerid][pSelectedSlot]]);

	    if (weaponid) {
		    SendClientMessageEx(playerid, -1, "คุณตั้งค่าอาวุธในช่องที่ %d เป็น %s", PlayerData[playerid][pSelectedSlot] + 1, ReturnWeaponName(weaponid));
		}
		else {
		    SendClientMessageEx(playerid, -1, "คุณลบอาวุธในช่องที่ %d", PlayerData[playerid][pSelectedSlot] + 1);
		}
	}
	return 1;
}

Dialog:GroupWeaponAmmo(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pGroupEdit] == -1)
	    return 0;

	if (response)
	{
	    new ammo = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_ShowEasy(playerid, GroupWeaponAmmo, DIALOG_STYLE_INPUT, "ตั้งค่ากระสุน", "โปรดป้อนกระสุนใหม่สำหรับช่อง: %d\n\nโปรดป้อนกระสุนใหม่สำหรับช่อง %d:", "ตกลง", "ยกเลิก", GroupData[PlayerData[playerid][pGroupEdit]][groupAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

		if (ammo < 1 || ammo > 15000)
		    return Dialog_ShowEasy(playerid, GroupWeaponAmmo, DIALOG_STYLE_INPUT, "ตั้งค่ากระสุน", "ข้อผิดพลาด: กระสุนต้องไม่ต่ำกว่า 1 หรือมากกว่า 15,000\n\nกระสุนในปัจจุบัน: %d\n\nโปรดป้อนกระสุนใหม่สำหรับช่อง %d:", "ตกลง", "ยกเลิก", GroupData[PlayerData[playerid][pGroupEdit]][groupAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

        GroupData[PlayerData[playerid][pGroupEdit]][groupAmmo][PlayerData[playerid][pSelectedSlot]] = ammo;
        Group_Save(PlayerData[playerid][pGroupEdit]);

		Dialog_ShowEasy(playerid, GroupWeapon, DIALOG_STYLE_LIST, "แก้ไขอาวุธ", "ตั้งค่าอาวุธ (%d)\nตั้งค่ากระสุน (%d)\nลบล้างช่อง", "เลือก", "ยกเลิก", GroupData[PlayerData[playerid][pGroupEdit]][groupWeapons][PlayerData[playerid][pSelectedSlot]], GroupData[PlayerData[playerid][pGroupEdit]][groupAmmo][PlayerData[playerid][pSelectedSlot]]);
		SendClientMessageEx(playerid, -1, "คุณตั้งค่ากระสุนในช่องที่ %d เป็น %d", PlayerData[playerid][pSelectedSlot] + 1, ammo);
	}
	return 1;
}

ShowMenuVip(playerid){
    new string[128];
    if(PlayerData[playerid][pVip] == 1){
        format(string, sizeof(string), "- สกินสำหรับ Bronze Member\n- สามารถใช้ /vad ประกาศสำหรับ IC เท่านั้น [สีส้มเข้ม]\n- ได้ส่วนลดสำหรับการซื้อใบประกันยานพาหนะ");
        Dialog_ShowEasy(playerid, BronzeVipMemu, DIALOG_STYLE_LIST, "Bronze Member Menu", string, "เลือก", "ยกเลิก");
    }
    if(PlayerData[playerid][pVip] == 2){
        format(string, sizeof(string), "- สกินสำหรับ Silver Member\n- สามารถใช้ /vad ประกาศสำหรับ IC เท่านั้น [สีเขียว]\n- ได้ส่วนลดสำหรับการซื้อใบประกันยานพาหนะ");
        Dialog_ShowEasy(playerid, SilverVipMemu, DIALOG_STYLE_LIST, "Silver Member Menu", string, "เลือก", "ยกเลิก");
    }
    if(PlayerData[playerid][pVip] == 3){
        format(string, sizeof(string), "- สกินสำหรับ Gold Member\n- เปลี่ยนข้อความ Twitter และ Vad\n- สามารถใช้ /vad ประกาศสำหรับ IC เท่านั้น [สีเหลืองทอง]\n- ได้ส่วนลดสำหรับการซื้อใบประกันยานพาหนะ");
        Dialog_ShowEasy(playerid, GoldVipMemu, DIALOG_STYLE_LIST, "Gold Member Menu", string, "เลือก", "ยกเลิก");
    }
    return 1;
}

Dialog:BronzeVipMemu(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(listitem == 0){
            if(PlayerData[playerid][pGender] == 1)
                SetPlayerSkin(playerid, 146);
            else if(PlayerData[playerid][pGender] == 2)
                SetPlayerSkin(playerid, 139);
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้ใช้สกินสำหรับ Bronze Member แล้ว");
        }
    }
    return 1;
}

Dialog:SilverVipMemu(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(listitem == 0){
            if(PlayerData[playerid][pGender] == 1)
                SetPlayerSkin(playerid, 45);
            else if(PlayerData[playerid][pGender] == 2)
                SetPlayerSkin(playerid, 140);
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้ใช้สกินสำหรับ Silver Member แล้ว");
        }
    }
    return 1;
}

Dialog:GoldVipMemu(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(listitem == 0){
            if(PlayerData[playerid][pGender] == 1) SetPlayerSkin(playerid, 97);
            else if(PlayerData[playerid][pGender] == 2) SetPlayerSkin(playerid, 138);
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้ใช้สกินสำหรับ Gold Member แล้ว");
        }
        if(listitem == 1){
            Dialog_ShowEasy(playerid, SelectTextColorGold, DIALOG_STYLE_LIST, "เลือกสีข้อความ Vad", "\n- สีปกติ\n- สีแดง\n- สีส้ม\n- สีเหลือง\n- สีเขียว\n- สีน้ำเงิน\n- สีคราม\n- สีม่วง", "เลือก", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:SelectTextColorGold(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            SendClientMessage(playerid, 0xFFC900AA, "คุณได้เปลี่ยนสีข้อความ Vad เป็น {FFC900}'สีปกติ'");
            PlayerTextColorGold[playerid] = 0;
            SendClientMessage(playerid, COLOR_RED, "[!]: เมื่อคุณออกจากเกมสีข้อความจะกลับเป็นสีปกติ");
        }
        if(listitem == 1){
            SendClientMessage(playerid, 0xFF0000AA, "คุณได้เปลี่ยนสีข้อความ Vad เป็น {FF0000}'สีแดง'");
            PlayerTextColorGold[playerid] = 1;
            SendClientMessage(playerid, COLOR_RED, "[!]: เมื่อคุณออกจากเกมสีข้อความจะกลับเป็นสีปกติ");
        }
        if(listitem == 2){
            SendClientMessage(playerid, 0xFF7F00AA, "คุณได้เปลี่ยนสีข้อความ Vad เป็น {FF7F00}'สีส้ม'");
            PlayerTextColorGold[playerid] = 2;
            SendClientMessage(playerid, COLOR_RED, "[!]: เมื่อคุณออกจากเกมสีข้อความจะกลับเป็นสีปกติ");
        }
        if(listitem == 3){
            SendClientMessage(playerid, 0xFFFF00AA, "คุณได้เปลี่ยนสีข้อความ Vad เป็น {FFFF00}'สีเหลือง'");
            PlayerTextColorGold[playerid] = 3;
            SendClientMessage(playerid, COLOR_RED, "[!]: เมื่อคุณออกจากเกมสีข้อความจะกลับเป็นสีปกติ");
        }
        if(listitem == 4){
            SendClientMessage(playerid, 0x00FF00AA, "คุณได้เปลี่ยนสีข้อความ Vad เป็น {00FF00}'สีเขียว'");
            PlayerTextColorGold[playerid] = 4;
            SendClientMessage(playerid, COLOR_RED, "[!]: เมื่อคุณออกจากเกมสีข้อความจะกลับเป็นสีปกติ");
        }
        if(listitem == 5){
            SendClientMessage(playerid, 0x0000FFAA, "คุณได้เปลี่ยนสีข้อความ Vad เป็น {0000FF}'สีน้ำเงิน'");
            PlayerTextColorGold[playerid] = 5;
            SendClientMessage(playerid, COLOR_RED, "[!]: เมื่อคุณออกจากเกมสีข้อความจะกลับเป็นสีปกติ");
        }
        if(listitem == 6){
            SendClientMessage(playerid, 0x4B0082AA, "คุณได้เปลี่ยนสีข้อความ Vad เป็น {4B0082}'สีคราม'");
            PlayerTextColorGold[playerid] = 6;
            SendClientMessage(playerid, COLOR_RED, "[!]: เมื่อคุณออกจากเกมสีข้อความจะกลับเป็นสีปกติ");
        }
        if(listitem == 7){
            SendClientMessage(playerid, 0x9400D3AA, "คุณได้เปลี่ยนสีข้อความ Vad เป็น {9400D3}'สีม่วง'");
            PlayerTextColorGold[playerid] = 7;
            SendClientMessage(playerid, COLOR_RED, "[!]: เมื่อคุณออกจากเกมสีข้อความจะกลับเป็นสีปกติ");
        }
    }
    return 1;
}

Dialog:ShareLocation(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new userid = GetPlayerShareLocation[playerid];
        if(userid != -1){
            new Float:x, Float:y, Float:z;
            GetPlayerPos(userid, x, y, z);
            SetPlayerCheckpoint(playerid, x, y, z, 5.0);
            PlayerEnterCheckPoint[playerid] = 1;
            SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้เปิดตำแหน่งไปยัง %s แล้ว", ReturnRoleplayName(userid));
            SendClientMessageEx(userid, COLOR_YELLOW, "%s ได้ตอบรับตำแหน่งของคุณแล้ว", ReturnRoleplayName(playerid));
        }
    }
    return 1;
}

Dialog:AdminManagePlayer(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[128];
        if(listitem == 0){
            if (AdminManagePlayerID[playerid] == INVALID_PLAYER_ID)
                return SendClientMessage(playerid, -1, "ไอดีผู้เล่นไม่ถูกต้องหรือผู้เล่นนั้นออกไปแล้ว");

	        SendPlayerToPlayer(playerid, AdminManagePlayerID[playerid]);
            AdminManagePlayerID[playerid] = INVALID_PLAYER_ID;
        }
        if(listitem == 1){
            if (AdminManagePlayerID[playerid] == INVALID_PLAYER_ID)
                return SendClientMessage(playerid, -1, "ไอดีผู้เล่นไม่ถูกต้องหรือผู้เล่นนั้นออกไปแล้ว");

	        SendPlayerToPlayer(AdminManagePlayerID[playerid], playerid);
            AdminManagePlayerID[playerid] = INVALID_PLAYER_ID;
        }
        if(listitem == 2){
            if(AdminManagePlayerID[playerid] == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้องหรือผู้เล่นนั้นออกไปแล้ว");

            if(!IsPlayerConnected(AdminManagePlayerID[playerid])) return ErrorMsg(playerid, "ไอดีผู้เล่นที่คุณระบุ ไม่ได้เชื่อต่อกับเซิฟเวอร์");
            
            if(PlayerData[playerid][pSpec] == INVALID_PLAYER_ID) {
                GetPlayerPos(playerid, PlayerData[playerid][pPosX], PlayerData[playerid][pPosY], PlayerData[playerid][pPosZ]);
                Character_Save(playerid);
                PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);
                PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
                GetPlayerHealth(playerid, PlayerData[playerid][pHP]);
                GetPlayerArmour(playerid, PlayerData[playerid][pAM]);
            }
            PlayerData[playerid][pSpec] = AdminManagePlayerID[playerid];
            TogglePlayerSpectating(playerid, true);
            SetPlayerColor(playerid, 0xFFFFFF00);
            SetPlayerInterior(playerid, GetPlayerInterior(AdminManagePlayerID[playerid]));
            SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(AdminManagePlayerID[playerid]));

            if(IsPlayerInAnyVehicle(AdminManagePlayerID[playerid])) {
                PlayerSpectateVehicle(playerid, GetPlayerVehicleID(AdminManagePlayerID[playerid]));
            }
            else {
                PlayerSpectatePlayer(playerid, AdminManagePlayerID[playerid]);
            }
        }
        if(listitem == 3){
            if(AdminManagePlayerID[playerid] == INVALID_PLAYER_ID) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
            if(!LoggedIn[AdminManagePlayerID[playerid]]) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
            if(PlayerData[AdminManagePlayerID[playerid]][pFirstTime] == 1) return ErrorMsg(playerid, "ผู้เล่นนั้นยังทำข้อสอบไม่เรียบร้อย");
            PlayerIsDropMap[AdminManagePlayerID[playerid]] = false;
            SetPlayerPosEx(AdminManagePlayerID[playerid], 1120.4299,-1378.5870,14.2879, 0, 0);
            SendClientMessageEx(playerid, -1, "- คุณได้ส่ง %s(%d) ไปยังหน้าตลาดกลางเรียบร้อยแล้ว", ReturnRoleplayName(AdminManagePlayerID[playerid]), AdminManagePlayerID[playerid]);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ส่ง %s ไปยังหน้าตลาดแล้ว", ReturnRoleplayName(playerid), ReturnRoleplayName(AdminManagePlayerID[playerid]));
            SendAdminsMessage(1, COLOR_GRAY, string);
        }
    }
    return 1;
}