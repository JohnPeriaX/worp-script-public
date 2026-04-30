#if defined _inc_impl
	#undef _inc_impl
#endif

LoadTextDrawPlayerMarry(playerid){
    MarryText[playerid][0] = CreatePlayerTextDraw(playerid, 318.000000, 116.000000, "_");
    PlayerTextDrawFont(playerid, MarryText[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][0], 0.641666, 29.800003);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][0], 298.500000, 320.000000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][0], 2);
    PlayerTextDrawColor(playerid, MarryText[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][0], -4984893);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][0], 0);

    MarryText[playerid][1] = CreatePlayerTextDraw(playerid, 315.000000, 125.000000, "Love License");
    PlayerTextDrawFont(playerid, MarryText[playerid][1], 2);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][1], 0.325000, 2.100003);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][1], 298.500000, 235.000000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][1], 1);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][1], 2);
    PlayerTextDrawColor(playerid, MarryText[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][1], 135);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][1], 0);

    MarryText[playerid][2] = CreatePlayerTextDraw(playerid, 457.000000, 99.000000, "CLOSE");
    PlayerTextDrawFont(playerid, MarryText[playerid][2], 2);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][2], 0.204166, 1.350000);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][2], 16.500000, 40.000000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][2], 2);
    PlayerTextDrawColor(playerid, MarryText[playerid][2], -16776961);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][2], 200);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][2], 1);

    MarryText[playerid][3] = CreatePlayerTextDraw(playerid, 179.000000, 158.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, MarryText[playerid][3], 5);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][3], 87.500000, 110.000000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][3], 1);
    PlayerTextDrawColor(playerid, MarryText[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][3], 125);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][3], 255);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][3], 1);
    PlayerTextDrawSetPreviewModel(playerid, MarryText[playerid][3], 0);
    PlayerTextDrawSetPreviewRot(playerid, MarryText[playerid][3], -9.000000, 0.000000, -2.000000, 0.900000);
    PlayerTextDrawSetPreviewVehCol(playerid, MarryText[playerid][3], 1, 1);

    MarryText[playerid][4] = CreatePlayerTextDraw(playerid, 223.000000, 257.000000, "Jonathan_Freshy");
    PlayerTextDrawFont(playerid, MarryText[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][4], 0.162500, 1.000003);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][4], 298.500000, 84.500000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][4], 2);
    PlayerTextDrawColor(playerid, MarryText[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][4], 135);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][4], 0);

    MarryText[playerid][5] = CreatePlayerTextDraw(playerid, 294.000000, 188.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, MarryText[playerid][5], 5);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][5], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][5], 48.500000, 50.000000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][5], 1);
    PlayerTextDrawColor(playerid, MarryText[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][5], -2016478720);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][5], 255);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][5], 0);
    PlayerTextDrawSetPreviewModel(playerid, MarryText[playerid][5], 1316);
    PlayerTextDrawSetPreviewRot(playerid, MarryText[playerid][5], -93.000000, 1.000000, -65.000000, 1.000000);
    PlayerTextDrawSetPreviewVehCol(playerid, MarryText[playerid][5], 1, 1);

    MarryText[playerid][6] = CreatePlayerTextDraw(playerid, 311.000000, 183.000000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, MarryText[playerid][6], 4);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][6], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][6], 13.500000, 16.500000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][6], 1);
    PlayerTextDrawColor(playerid, MarryText[playerid][6], -2686721);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][6], 0);

    MarryText[playerid][7] = CreatePlayerTextDraw(playerid, 369.000000, 158.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, MarryText[playerid][7], 5);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][7], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][7], 87.500000, 110.000000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][7], 1);
    PlayerTextDrawColor(playerid, MarryText[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][7], 125);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][7], 255);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][7], 1);
    PlayerTextDrawSetPreviewModel(playerid, MarryText[playerid][7], 0);
    PlayerTextDrawSetPreviewRot(playerid, MarryText[playerid][7], -9.000000, 0.000000, -2.000000, 0.900000);
    PlayerTextDrawSetPreviewVehCol(playerid, MarryText[playerid][7], 1, 1);

    MarryText[playerid][8] = CreatePlayerTextDraw(playerid, 413.000000, 257.000000, "Sarah_Samatah");
    PlayerTextDrawFont(playerid, MarryText[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][8], 0.162500, 1.000003);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][8], 298.500000, 84.500000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][8], 2);
    PlayerTextDrawColor(playerid, MarryText[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][8], 135);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][8], 0);

    MarryText[playerid][9] = CreatePlayerTextDraw(playerid, 318.000000, 279.000000, "_");
    PlayerTextDrawFont(playerid, MarryText[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][9], 0.600000, 10.300003);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][9], 298.500000, 275.000000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][9], 2);
    PlayerTextDrawColor(playerid, MarryText[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][9], 135);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][9], 0);

    MarryText[playerid][10] = CreatePlayerTextDraw(playerid, 318.000000, 281.000000, "Marry Date: 01/12/2000");
    PlayerTextDrawFont(playerid, MarryText[playerid][10], 2);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][10], 0.200000, 1.150000);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][10], 455.500000, 262.000000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][10], 1);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][10], 2);
    PlayerTextDrawColor(playerid, MarryText[playerid][10], -16776961);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][10], 50);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][10], 0);

    MarryText[playerid][11] = CreatePlayerTextDraw(playerid, 318.000000, 298.000000, "Couple Level: 100");
    PlayerTextDrawFont(playerid, MarryText[playerid][11], 2);
    PlayerTextDrawLetterSize(playerid, MarryText[playerid][11], 0.200000, 1.150000);
    PlayerTextDrawTextSize(playerid, MarryText[playerid][11], 455.500000, 262.000000);
    PlayerTextDrawSetOutline(playerid, MarryText[playerid][11], 1);
    PlayerTextDrawSetShadow(playerid, MarryText[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, MarryText[playerid][11], 2);
    PlayerTextDrawColor(playerid, MarryText[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, MarryText[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, MarryText[playerid][11], 50);
    PlayerTextDrawUseBox(playerid, MarryText[playerid][11], 0);
    PlayerTextDrawSetProportional(playerid, MarryText[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, MarryText[playerid][11], 0);
    return 1;
}

CreateMarryBarPlayer(playerid){
    MarryBar[playerid][0] = CreatePlayerProgressBar(playerid, 237.000000, 318.000000, 167.000000, 9.000000, -8323073, 100.000000, 0);
    return 1;
}

/*Dialog:MarrySelect(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new userid = strval(inputtext);
        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
        if(!LoggedIn[userid]) return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        if(userid == playerid) return ErrorMsg(playerid, "คุณไม่สามารถขอตัวเองแต่งงานได้");

        if(PlayerData[userid][pMarrySQLID] != 0) return ErrorMsg(playerid, "ผู้เล่นนั้นได้แต่งงานแล้ว");

        if(!IsPlayerNearPlayer(playerid, userid, 5.0)) return ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้น");
        new string[128];
        format(string, sizeof(string), "กำลังการตอบรับจาก %s .....", ReturnRoleplayName(userid));
        Dialog_ShowEasy(playerid, ShowMarry, DIALOG_STYLE_MSGBOX, "การขอแต่งงาน", string, "ตกลง", "");

        MarryID[userid] = playerid;
        format(string, sizeof(string), "ผู้เล่น %s ได้ทำการขอคุณแต่งงาน\nหากคุณยินยอมให้กด 'ยอมรับ'\nหากคุณไม่ยินยอมให้คุณกด 'ปฏิเสธ'", ReturnRoleplayName(playerid));
        Dialog_ShowEasy(userid, MarryType, DIALOG_STYLE_MSGBOX, "การขอแต่งงาน", string, "ยอมรับ", "ปฏิเสธ");
    }
    return 1;
}*/

Dialog:MarryType(playerid, response, listitem, inputtext[]){
    if(!response){
        if(MarryID[playerid] == -1) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
        if(!LoggedIn[MarryID[playerid]]) return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        new string[128];
        format(string, sizeof(string), "{FF0000}คุณได้ปฏิเสธการขอแต่งงานของ %s เรียบร้อยแล้ว", ReturnRoleplayName(MarryID[playerid]));
        Dialog_ShowEasy(playerid, ShowMarry, DIALOG_STYLE_MSGBOX, "การขอแต่งงาน", string, "ตกลง", "");
        format(string, sizeof(string), "{FF0000}เสียใจด้วย %s ได้ปฏิเสธการขอแต่งงาน", ReturnRoleplayName(playerid));
        Dialog_ShowEasy(MarryID[playerid], ShowMarry, DIALOG_STYLE_MSGBOX, "การขอแต่งงาน", string, "ตกลง", "");
        MarryID[playerid] = -1;
    }
    if(response){
        if(MarryID[playerid] == -1) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
        if(!LoggedIn[MarryID[playerid]]) return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        new string[128];
        format(string, sizeof(string), "{FFB1EF}ยินดีด้วยคุณได้แต่งงานกับ %s เป็นที่เรียบร้อยแล้ว", ReturnRoleplayName(MarryID[playerid]));
        Dialog_ShowEasy(playerid, ShowMarry, DIALOG_STYLE_MSGBOX, "การขอแต่งงาน", string, "ตกลง", "");
        format(string, sizeof(string), "{FFB1EF}ยินดีด้วยคุณได้แต่งงานกับ %s เป็นที่เรียบร้อยแล้ว", ReturnRoleplayName(playerid));
        Dialog_ShowEasy(MarryID[playerid], ShowMarry, DIALOG_STYLE_MSGBOX, "การขอแต่งงาน", string, "ตกลง", "");

        PlayerData[playerid][pMarrySQLID] = PlayerData[MarryID[playerid]][pID];
        PlayerData[MarryID[playerid]][pMarrySQLID] = PlayerData[playerid][pID];

        format(PlayerData[playerid][pMarryName], 64, ReturnName(MarryID[playerid]));
        format(PlayerData[MarryID[playerid]][pMarryName], 64, ReturnName(playerid));

        PlayerData[playerid][pMarryLevel] = 0;
        PlayerData[MarryID[playerid]][pMarryLevel] = 0;

        format(PlayerData[playerid][pMarryDate], 64, ReturnDate());
        format(PlayerData[MarryID[playerid]][pMarryDate], 64, ReturnDate());

        PlayerInventory_AddItem(playerid, "Marry Ring", 1316, 1);
        PlayerInventory_AddItem(playerid, "Marry Card", 19194, 1);
        PlayerInventory_AddItem(playerid, "Marry Flower", 325, 1);
        PlayerInventory_AddItem(MarryID[playerid], "Marry Flower", 325, 1);
        PlayerInventory_AddItem(MarryID[playerid], "Marry Ring", 1316, 1);

        SendClientMessage(playerid, COLOR_DARKGREEN, "======================================================");
        SendClientMessage(playerid, -1, "- ได้รับ 'Marry Ring' + 1");
        SendClientMessage(playerid, -1, "- ได้รับ 'Marry Card' + 1");
        SendClientMessage(playerid, -1, "- ได้รับ 'Marry Flower' + 1");
        SendClientMessage(playerid, COLOR_DARKGREEN, "======================================================");

        SendClientMessage(MarryID[playerid], COLOR_DARKGREEN, "======================================================");
        SendClientMessage(MarryID[playerid], -1, "- ได้รับ 'Marry Ring' + 1");
        SendClientMessage(MarryID[playerid], -1, "- ได้รับ 'Marry Flower' + 1");
        SendClientMessage(MarryID[playerid], COLOR_DARKGREEN, "======================================================");

        if(PlayerData[playerid][pGender] == 1) {
            PlayerInventory_AddItem(playerid, "240", 2384, 1);
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้รับชุด '240' + 1");
            PlayerData[playerid][pMarrySkin] = 2;
        }
        else if(PlayerData[playerid][pGender] == 2) {
            PlayerInventory_AddItem(playerid, "91", 2384, 1);
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้รับชุด '91' + 1");
            PlayerData[playerid][pMarrySkin] = 1;
        }
        if(PlayerData[MarryID[playerid]][pGender] == 1) {
            PlayerInventory_AddItem(MarryID[playerid], "240", 2384, 1);
            SendClientMessage(MarryID[playerid], COLOR_YELLOW, "- คุณได้รับชุด '240' + 1");
            PlayerData[MarryID[playerid]][pMarrySkin] = 2;
        }
        else if(PlayerData[MarryID[playerid]][pGender] == 2){
            PlayerInventory_AddItem(MarryID[playerid], "91", 2384, 1);
            SendClientMessage(MarryID[playerid], COLOR_YELLOW, "- คุณได้รับชุด '91' + 1");
            PlayerData[MarryID[playerid]][pMarrySkin] = 1;
        } 

        SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: ใช้ '/kiss 2' เพื่อเพิ่มเลเวลคู่รักได้");
        SendClientMessage(MarryID[playerid], COLOR_YELLOW, "[คำแนะนำ]: ใช้ '/kiss 2' เพื่อเพิ่มเลเวลคู่รักได้");

        SendClientMessageToAllEx(0xFFB1EFAA, "[การแต่งงาน]: ยินดีด้วย คุณ %s กับ คุณ %s ได้แต่งงานกันเรียบร้อยแล้ว ฉลองกันเร็ว", ReturnRoleplayName(MarryID[playerid]), ReturnRoleplayName(playerid));
    }
    return 1;
}

Dialog:ShowCardMarry(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            LoadTextDrawPlayerMarry(playerid);
            CreateMarryBarPlayer(playerid);

            OnPlayerShowMarryCard[playerid] = 1;

            new string[128];

            SelectTextDraw(playerid, 0xFFD100FF);

            if(PlayerData[playerid][pGender] == 1){ //ชาย
                PlayerTextDrawSetPreviewModel(playerid, MarryText[playerid][3], 240);
                format(string, sizeof(string), "%s", ReturnName(playerid));
                PlayerTextDrawSetString(playerid, MarryText[playerid][4], string);
            }
            else if(PlayerData[playerid][pGender] == 2){ //หญิง
                PlayerTextDrawSetPreviewModel(playerid, MarryText[playerid][3], 91);
                format(string, sizeof(string), "%s", ReturnName(playerid));
                PlayerTextDrawSetString(playerid, MarryText[playerid][4], string);
            }
            
            if(PlayerData[playerid][pMarrySkin] == 1){ //ชาย
                PlayerTextDrawSetPreviewModel(playerid, MarryText[playerid][7], 240);
                format(string, sizeof(string), "%s", PlayerData[playerid][pMarryName]);
                PlayerTextDrawSetString(playerid, MarryText[playerid][8], string);
            }
            else if(PlayerData[playerid][pMarrySkin] == 2){ //หญิง
                PlayerTextDrawSetPreviewModel(playerid, MarryText[playerid][7], 91);
                format(string, sizeof(string), "%s", PlayerData[playerid][pMarryName]);
                PlayerTextDrawSetString(playerid, MarryText[playerid][8], string);
            }

            format(string, sizeof(string), "Marry Date: %s", PlayerData[playerid][pMarryDate]);
            PlayerTextDrawSetString(playerid, MarryText[playerid][10], string);

            format(string, sizeof(string), "Couple Level: %s", FormatNumberNotMoney(PlayerData[playerid][pMarryLevel]));
            PlayerTextDrawSetString(playerid, MarryText[playerid][11], string);

            for(new i=0; i<TEXTMARRY; i++){
                PlayerTextDrawShow(playerid, MarryText[playerid][i]);
            }

            ShowPlayerProgressBar(playerid, MarryBar[playerid][0]);
            SetPlayerProgressBarValue(playerid, MarryBar[playerid][0], PlayerData[playerid][pMarryLevel]);
        }   
        if(listitem == 1){
            Dialog_ShowEasy(playerid, InterIDShowMarry, DIALOG_STYLE_INPUT, "โชว์บัตรแต่งงาน", "กรอก 'ชื่อ' หรือ 'ไอดี' ผู้เล่นที่จะต้องการโชว์", "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:InterIDShowMarry(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new userid = strval(inputtext);
        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
        if(!LoggedIn[userid]) return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        if(!IsPlayerNearPlayer(playerid, userid, 5.0)) return ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้น");
        LoadTextDrawPlayerMarry(userid);
        CreateMarryBarPlayer(userid);

        OnPlayerShowMarryCard[userid] = 1;

        new string[128];

        SelectTextDraw(userid, 0xFFD100FF);

        if(PlayerData[playerid][pGender] == 1){ //ชาย
            PlayerTextDrawSetPreviewModel(userid, MarryText[userid][3], 240);
            format(string, sizeof(string), "%s", ReturnName(playerid));
            PlayerTextDrawSetString(userid, MarryText[userid][4], string);
        }
        else if(PlayerData[playerid][pGender] == 2){ //หญิง
            PlayerTextDrawSetPreviewModel(userid, MarryText[userid][3], 91);
            format(string, sizeof(string), "%s", ReturnName(playerid));
            PlayerTextDrawSetString(userid, MarryText[userid][4], string);
        }

        if(PlayerData[playerid][pMarrySkin] == 1){ //ชาย
            PlayerTextDrawSetPreviewModel(userid, MarryText[userid][7], 240);
            format(string, sizeof(string), "%s", PlayerData[playerid][pMarryName]);
            PlayerTextDrawSetString(userid, MarryText[userid][8], string);
        }
        else if(PlayerData[playerid][pMarrySkin] == 2){ //หญิง
            PlayerTextDrawSetPreviewModel(userid, MarryText[userid][7], 91);
            format(string, sizeof(string), "%s", PlayerData[playerid][pMarryName]);
            PlayerTextDrawSetString(userid, MarryText[userid][8], string);
        }

        

        format(string, sizeof(string), "Marry Date: %s", PlayerData[playerid][pMarryDate]);
        PlayerTextDrawSetString(userid, MarryText[userid][10], string);

        format(string, sizeof(string), "Couple Level: %s", FormatNumberNotMoney(PlayerData[playerid][pMarryLevel]));
        PlayerTextDrawSetString(userid, MarryText[userid][11], string);

        for(new i=0; i<TEXTMARRY; i++){
            PlayerTextDrawShow(userid, MarryText[userid][i]);
        }

        ShowPlayerProgressBar(userid, MarryBar[userid][0]);
        SetPlayerProgressBarValue(userid, MarryBar[userid][0], PlayerData[playerid][pMarryLevel]);
    }
    return 1;
}

ShowTargetUseMarry(playerid){
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
    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "[เลือกผู้เล่นที่คุณจะแต่งงานด้วย]", "ไม่มีใครอยู่ใกล้คุณเลย", "ตกลง", "ยกเลิก");
    else Dialog_ShowEasy(playerid, SendInviteToMarry, DIALOG_STYLE_LIST, "[เลือกผู้เล่นที่คุณจะแต่งงานด้วย]", stringplayer, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:SendInviteToMarry(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "playerID", GetPVarInt(playerid, str_biz));
			ShowPlayerMarry(playerid);
			return 1;
		}
    }
    return 1;
}

ShowPlayerMarry(playerid){
    new targetid = GetPVarInt(playerid, "playerID");
    if(targetid == INVALID_PLAYER_ID){
        ErrorMsg(playerid, "ไอดีผู้เล่นผิดพลาด");
        return ShowTargetUseMarry(playerid);
    }

    if(!LoggedIn[targetid]){
        ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        return ShowTargetUseMarry(playerid);
    }

    if (!IsPlayerNearPlayer(playerid, targetid, 5.0)){
        ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้นหรือผู้เล่นนั้นห่างคุณออกไป");
        return ShowTargetUseMarry(playerid);
    }

    if(PlayerData[targetid][pMarrySQLID] != 0) return ErrorMsg(playerid, "ผู้เล่นนั้นได้แต่งงานแล้ว");

    if(!IsPlayerNearPlayer(playerid, targetid, 5.0)) return ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้น");
    new string[128];
    format(string, sizeof(string), "กำลังการตอบรับจาก %s .....", ReturnRoleplayName(targetid));
    Dialog_ShowEasy(playerid, ShowMarry, DIALOG_STYLE_MSGBOX, "การขอแต่งงาน", string, "ตกลง", "");

    MarryID[targetid] = playerid;
    format(string, sizeof(string), "ผู้เล่น %s ได้ทำการขอคุณแต่งงาน\nหากคุณยินยอมให้กด 'ยอมรับ'\nหากคุณไม่ยินยอมให้คุณกด 'ปฏิเสธ'", ReturnRoleplayName(playerid));
    Dialog_ShowEasy(targetid, MarryType, DIALOG_STYLE_MSGBOX, "การขอแต่งงาน", string, "ยอมรับ", "ปฏิเสธ");
    return 1;
}

DivorcedMenu(playerid){

    if(GetMoney(playerid) < 80000) return ErrorMsg(playerid, "ต้องการเงิน 80k ในการหย่าร้าง");
    ShowMenuSelectDivorced(playerid);
    return 1;
}

ShowMenuSelectDivorced(playerid){
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
    if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "[เลือกผู้เล่นที่เป็นคู่รักของคุณเพื่อหย่าร้าง]", "ไม่มีใครอยู่ใกล้คุณเลย", "ตกลง", "ยกเลิก");
    else Dialog_ShowEasy(playerid, SendInvitetoDivorced, DIALOG_STYLE_LIST, "[เลือกผู้เล่นที่เป็นคู่รักของคุณเพื่อหย่าร้าง]", stringplayer, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:SendInvitetoDivorced(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem >= 0 && listitem <= 20) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);

			SetPVarInt(playerid, "playerID", GetPVarInt(playerid, str_biz));
			Divorceding(playerid);
			return 1;
		}
    }
    return 1;
}

Divorceding(playerid){
    new targetid = GetPVarInt(playerid, "playerID");
    if(targetid == INVALID_PLAYER_ID){
        ErrorMsg(playerid, "ไอดีผู้เล่นผิดพลาด");
        return ShowTargetUseMarry(playerid);
    }

    if(!LoggedIn[targetid]){
        ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ");
        return ShowTargetUseMarry(playerid);
    }

    if (!IsPlayerNearPlayer(playerid, targetid, 5.0)){
        ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้นหรือผู้เล่นนั้นห่างคุณออกไป");
        return ShowTargetUseMarry(playerid);
    }

    if(targetid == playerid) return ErrorMsg(playerid, "คุณไม่สามารถใช้กับตัวเองได้");
    if(PlayerData[playerid][pMarrySQLID] != PlayerData[targetid][pID])
        return ErrorMsg(playerid, "ผู้เล่นนั้นไม่ใช่คู่รักของคุณ");

    PlayerData[playerid][pMarrySQLID] = 0;
    PlayerData[targetid][pMarrySQLID] = 0;

    format(PlayerData[playerid][pMarryName], 64, "NULL");
    format(PlayerData[targetid][pMarryName], 64, "NULL");

    PlayerData[playerid][pMarryLevel] = 0;
    PlayerData[targetid][pMarryLevel] = 0;
    
    PlayerData[playerid][pMarryKissed] = 0;
    PlayerData[targetid][pMarryKissed] = 0;

    PlayerData[playerid][pMarryGetGift] = 0;
    PlayerData[targetid][pMarryGetGift] = 0;

    format(PlayerData[playerid][pMarryDate], 64, "NULL");
    format(PlayerData[targetid][pMarryDate], 64, "NULL");

    PlayerInventory_Remove(playerid, "Marry Ring", 1);
    PlayerInventory_Remove(playerid, "Marry Card", 1);
    PlayerInventory_Remove(targetid, "Marry Ring", 1);
    PlayerInventory_Remove(targetid, "Marry Card", 1);

    RemoveAttachedObject(playerid, 4);
    RemoveAttachedObject(targetid, 4);

    GiveMoney(playerid, -80000, "divorce");

    new string[128];
    format(string, sizeof(string), "คุณได้หย่าร้างกับ %s เรียบร้อยแล้ว", ReturnRoleplayName(targetid));
    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การหย่าร้าง", string, "ตกลง", "");

    format(string, sizeof(string), "คุณได้หย่าร้างกับ %s เรียบร้อยแล้ว", ReturnRoleplayName(playerid));
    Dialog_ShowEasy(targetid, ShowOnly, DIALOG_STYLE_MSGBOX, "การหย่าร้าง", string, "ตกลง", "");

    SendClientMessageToAllEx(COLOR_RED, "[การหย่าร้าง]: คุณ %s กับ คุณ %s ได้ทำการหย่าร้างกันเรียบร้อยแล้ว, เสียใจด้วย", ReturnRoleplayName(playerid), ReturnRoleplayName(targetid));
    return 1;
}

ShowDialogGiftMarry(playerid){
    if(PlayerData[playerid][pMarrySQLID] == 0)
        return ErrorMsg(playerid, "คุณไม่มีคู่แต่งงานไม่สามารถใช้งานได้");

    if(PlayerData[playerid][pMarryLevel] <= 0) return ErrorMsg(playerid, "เลเวลคู่รักของคุณต้องมากกว่า 0 ถึงจะรับรางวัลได้");

    if(PlayerData[playerid][pMarryLevel] > 0 && PlayerData[playerid][pMarryLevel] <= 100){
        if(PlayerData[playerid][pMarryGetGift] == 0){
            GiveMoney(playerid, 2500, "item marry");
            SendClientMessageEx(playerid, -1, "{FFA3F5}- คุณได้รับเงินจำนวน 2,500 ของเลเวลคู่รัก %d เรียบร้อยแล้ว", PlayerData[playerid][pMarryLevel]);
            PlayerData[playerid][pMarryGetGift] = 1;
        }
        else return SendClientMessageEx(playerid, COLOR_RED, "คุณได้รับรางวัลคู่รักของเลเวล %d ไปแล้ว", PlayerData[playerid][pMarryLevel]);
    }
    return 1;
}

CMD:resetkiss(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1339) return 1;
    foreach(new i : Player){
        if(!LoggedIn[i]) continue;
        PlayerData[i][pMarryKissed] = 0;
    }
    mysql_tquery(dbCon, "UPDATE `characters` SET `MarryKissed` = '0'");
    SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้อัพเดท MarryKissed ของทุกคนเป็น 0 แล้ว");
    return 1;
}