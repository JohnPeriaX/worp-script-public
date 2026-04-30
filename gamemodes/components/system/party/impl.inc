#if defined _inc_impl
	#undef _inc_impl
#endif

ResetPartyPlayer(playerid){
    PlayerInParty[playerid] = 0;
    PlayerPartyGetID[playerid] = -1;
    PlayerPartyInviteID[playerid] = -1;
    PlayerManagePlayerParty[playerid] = -1;
    return 1;
}

ShowPartyMenu(playerid){
    if(!LoggedIn[playerid]) return 1;
    if(!PlayerInParty[playerid] && PlayerPartyGetID[playerid] == -1){
        Dialog_ShowEasy(playerid, CreateParty, DIALOG_STYLE_MSGBOX, "สร้างปาร์ตี้", "คุณยังไม่มีปาร์ตี้\nคุณต้องการสร้างหรือไม่?", "สร้าง", "ยกเลิก");
    }
    else{   
        if(PlayerPartyGetID[playerid] == -1 && !PartyData[PlayerPartyGetID[playerid]][partyEx]) return ErrorMsg(playerid, "คุณไม่มีปาร์ตี้ หรือ ปาร์ตี้ยังไม่ได้ถูกสร้าง");
        new string[128], caption[128];
        if(PartyData[PlayerPartyGetID[playerid]][partyMember][0] != playerid){
            format(caption, sizeof(caption), "ปาร์ตี้ของ %s", ReturnRoleplayName(PartyData[PlayerPartyGetID[playerid]][partyMember][0]));
            format(string, sizeof(string), "- ดูสมาชิกในปาร์ตี้\n- ออกจากปาร์ตี้");
            Dialog_ShowEasy(playerid, MyParty, DIALOG_STYLE_LIST, caption, string, "เลือก", "ปิด");
        }
        else{
            format(caption, sizeof(caption), "ปาร์ตี้ของคุณ", ReturnRoleplayName(PartyData[PlayerPartyGetID[playerid]][partyMember][0]));
            format(string, sizeof(string), "- ดูสมาชิกในปาร์ตี้\n- เชิญสมาชิกเข้าปาร์ตี้\n- ออกจากปาร์ตี้");
            Dialog_ShowEasy(playerid, MyPartyLeader, DIALOG_STYLE_LIST, caption, string, "เลือก", "ปิด");
        }
    }
    return 1;
}

Dialog:MyParty(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(PlayerPartyGetID[playerid] != -1){
                new string[500];
                new stringrole[32];
                new partyid = PlayerPartyGetID[playerid];
                if(PartyData[partyid][partyMember][0] != playerid){
                    for(new i=0; i<MAX_PARTY; i++){
                        if(i == 0) stringrole = "หัวหน้าปาร์ตี้";
                        else stringrole = "สมาชิกปาร์ตี้";
                        format(string, sizeof(string), "%s [%d] %s(%d) (%s)\n", string, i+1, ReturnRoleplayName(PartyData[partyid][partyMember][i]), PartyData[partyid][partyMember][i], stringrole);
                    }
                    Dialog_ShowEasy(playerid, PlayerParty, DIALOG_STYLE_LIST, "สมาชิกปาร์ตี้", string, "เลือก", "ย้อนกลับ");
                }
                else{                
                    for(new i=0; i<MAX_PARTY; i++){
                        if(i == 0) stringrole = "หัวหน้าปาร์ตี้";
                        else stringrole = "สมาชิกปาร์ตี้";
                        format(string, sizeof(string), "%s [%d] %s(%d) (%s)\n", string, i+1, ReturnRoleplayName(PartyData[partyid][partyMember][i]), PartyData[partyid][partyMember][i], stringrole);
                    }
                    Dialog_ShowEasy(playerid, ManagePlayerParty, DIALOG_STYLE_LIST, "สมาชิกปาร์ตี้", string, "เลือก", "ย้อนกลับ");
                }
            }
        }
        if(listitem == 1){
            if(PlayerPartyGetID[playerid] != -1){
                if(PartyData[PlayerPartyGetID[playerid]][partyEx]){
                    PlayerLeaveParty(playerid);
                }
            }
        }
    }
    return 1;
}

Dialog:MyPartyLeader(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(PlayerPartyGetID[playerid] != -1){
                new string[500];
                new stringrole[32];
                new partyid = PlayerPartyGetID[playerid];
                if(PartyData[partyid][partyMember][0] != playerid){
                    for(new i=0; i<MAX_PARTY; i++){
                        if(i == 0) stringrole = "หัวหน้าปาร์ตี้";
                        else stringrole = "สมาชิกปาร์ตี้";
                        format(string, sizeof(string), "%s [%d] %s(%d) (%s)\n", string, i+1, ReturnRoleplayName(PartyData[partyid][partyMember][i]), PartyData[partyid][partyMember][i], stringrole);
                    }
                    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_LIST, "สมาชิกปาร์ตี้", "ไม่มีสมาชิกในปาร์ตี้", "เลือก", "ปิด");
                }
                else{                
                    for(new i=0; i<MAX_PARTY; i++){
                        if(i == 0) stringrole = "หัวหน้าปาร์ตี้";
                        else stringrole = "สมาชิกปาร์ตี้";
                        format(string, sizeof(string), "%s [%d] %s(%d) (%s)\n", string, i+1, ReturnRoleplayName(PartyData[partyid][partyMember][i]), PartyData[partyid][partyMember][i], stringrole);
                    }
                    Dialog_ShowEasy(playerid, ManagePlayerParty, DIALOG_STYLE_LIST, "สมาชิกปาร์ตี้", string, "เลือก", "ย้อนกลับ");
                }
            }
        }
        if(listitem == 1){
            callcmd::inviteparty(playerid, "\1");
        }
        if(listitem == 2){
            if(PlayerPartyGetID[playerid] != -1){
                if(PartyData[PlayerPartyGetID[playerid]][partyEx]){
                    PlayerLeaveParty(playerid);
                }
            }
        }
    }
    return 1;
}

Dialog:PlayerParty(playerid, response, listitem, inputtext[]){
    if(!response){
        return ShowPartyMenu(playerid);
    }
    if(response){
        if(listitem >= 0 && listitem <= 4){
            return 1;
        }
    }
    return 1;
}

Dialog:ManagePlayerParty(playerid, response, listitem, inputtext[]){
    if(!response){
        return ShowPartyMenu(playerid);
    }
    if(response){
        new string[500];
        new stringrole[32];
        if(PlayerPartyGetID[playerid] == -1 && !PartyData[PlayerPartyGetID[playerid]][partyEx]) return ErrorMsg(playerid, "คุณไม่มีปาร์ตี้ หรือ ปาร์ตี้ยังไม่ได้ถูกสร้าง");
        new partyid = PlayerPartyGetID[playerid];
        if(listitem == 0){
            for(new i=0; i<MAX_PARTY; i++){
                if(i == 0) stringrole = "หัวหน้าปาร์ตี้";
                else stringrole = "สมาชิกปาร์ตี้";
                format(string, sizeof(string), "%s [%d] %s(%d) (%s)\n", string, i+1, ReturnRoleplayName(PartyData[partyid][partyMember][i]), PartyData[partyid][partyMember][i], stringrole);
            }
            Dialog_ShowEasy(playerid, ManagePlayerParty, DIALOG_STYLE_LIST, "สมาชิกปาร์ตี้", string, "เลือก", "ย้อนกลับ");
        }
        if(listitem == 1){
            if(PartyData[partyid][partyMember][1] != -1){
                PlayerManagePlayerParty[playerid] = PartyData[partyid][partyMember][1];
                format(string, sizeof(string), "สมาชิกปาร์ตี้: %s(%d) >> เตะออกจากปาร์ตี้ <<", ReturnRoleplayName(PartyData[partyid][partyMember][1]), PartyData[partyid][partyMember][1]);
                Dialog_ShowEasy(playerid, SelectManagePartyPlayer, DIALOG_STYLE_LIST, "จัดการสมาชิกปาร์ตี้", string, "เลือก", "ย้อนกลับ");
            }
        }
        if(listitem == 2){
            if(PartyData[partyid][partyMember][2] != -1){
                PlayerManagePlayerParty[playerid] = PartyData[partyid][partyMember][2];
                format(string, sizeof(string), "สมาชิกปาร์ตี้: %s(%d) >> เตะออกจากปาร์ตี้ <<", ReturnRoleplayName(PartyData[partyid][partyMember][2]), PartyData[partyid][partyMember][2]);
                Dialog_ShowEasy(playerid, SelectManagePartyPlayer, DIALOG_STYLE_LIST, "จัดการสมาชิกปาร์ตี้", string, "เลือก", "ย้อนกลับ");
            }
        }
        if(listitem == 3){
            if(PartyData[partyid][partyMember][3] != -1){
                PlayerManagePlayerParty[playerid] = PartyData[partyid][partyMember][3];
                format(string, sizeof(string), "สมาชิกปาร์ตี้: %s(%d) >> เตะออกจากปาร์ตี้ <<", ReturnRoleplayName(PartyData[partyid][partyMember][3]), PartyData[partyid][partyMember][3]);
                Dialog_ShowEasy(playerid, SelectManagePartyPlayer, DIALOG_STYLE_LIST, "จัดการสมาชิกปาร์ตี้", string, "เลือก", "ย้อนกลับ");
            }
        }
        if(listitem == 4){
            if(PartyData[partyid][partyMember][4] != -1){
                PlayerManagePlayerParty[playerid] = PartyData[partyid][partyMember][4];
                format(string, sizeof(string), "สมาชิกปาร์ตี้: %s(%d) >> เตะออกจากปาร์ตี้ <<", ReturnRoleplayName(PartyData[partyid][partyMember][4]), PartyData[partyid][partyMember][4]);
                Dialog_ShowEasy(playerid, SelectManagePartyPlayer, DIALOG_STYLE_LIST, "จัดการสมาชิกปาร์ตี้", string, "เลือก", "ย้อนกลับ");
            }
        }
    }
    return 1;
}

Dialog:SelectManagePartyPlayer(playerid, response, listitem, inputtext[]){
    if(!response){
        new string[500];
        new stringrole[32];
        if(PlayerPartyGetID[playerid] == -1 && !PartyData[PlayerPartyGetID[playerid]][partyEx]) return ErrorMsg(playerid, "คุณไม่มีปาร์ตี้ หรือ ปาร์ตี้ยังไม่ได้ถูกสร้าง");
        new partyid = PlayerPartyGetID[playerid];
        for(new i=0; i<MAX_PARTY; i++){
            if(i == 0) stringrole = "หัวหน้าปาร์ตี้";
            else stringrole = "สมาชิกปาร์ตี้";
            format(string, sizeof(string), "%s [%d] %s(%d) (%s)\n", string, i+1, ReturnRoleplayName(PartyData[partyid][partyMember][i]), PartyData[partyid][partyMember][i], stringrole);
        }
        Dialog_ShowEasy(playerid, ManagePlayerParty, DIALOG_STYLE_LIST, "สมาชิกปาร์ตี้", string, "เลือก", "ย้อนกลับ");
        return 1;
    }
    if(response){
        if(PlayerPartyGetID[playerid] == -1) return ErrorMsg(playerid, "คุณไม่มีปาร์ตี้");
        if(PlayerManagePlayerParty[playerid] != -1){
            if(PartyData[PlayerPartyGetID[playerid]][partyEx]){
                PlayerLeaveParty(PlayerManagePlayerParty[playerid]);
            }
        }   
    }
    return 1;
}

Dialog:CreateParty(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        callcmd::makeparty(playerid, "\1");
    }
    return 1;
}

Party_Create(playerid){
    for(new i=0; i<MAX_PARTY_DYNAMIC; i++) if(!PartyData[i][partyEx]){
        PartyData[i][partyEx] = true;
        PartyData[i][partyMember][0] = playerid;
        PartyData[i][partyMember][1] = -1;
        PartyData[i][partyMember][2] = -1;
        PartyData[i][partyMember][3] = -1;
        PartyData[i][partyMember][4] = -1;
        return i;
    }
    return -1;
}

Party_Delete(partyid){
    if(partyid != -1 && PartyData[partyid][partyEx]){
        PartyData[partyid][partyID] = 0;
        PartyData[partyid][partyEx] = false;
        PartyData[partyid][partyMember][0] = -1;
        PartyData[partyid][partyMember][1] = -1;
        PartyData[partyid][partyMember][2] = -1;
        PartyData[partyid][partyMember][3] = -1;
        PartyData[partyid][partyMember][4] = -1;
    }
    return 1;
}

PlayerLeaveParty(playerid){
    if(PlayerInParty[playerid] && PlayerPartyGetID[playerid] != -1){
        if(PartyData[PlayerPartyGetID[playerid]][partyEx]){
            new partyid = PlayerPartyGetID[playerid];
    
            if(PartyData[PlayerPartyGetID[playerid]][partyMember][0] != playerid){
                for(new i=0; i<MAX_PARTY; i++){
                    if(i > 0 && i < MAX_PARTY){
                        if(i == 4){
                            if(PartyData[PlayerPartyGetID[playerid]][partyMember][i] == playerid){
                                PartyData[PlayerPartyGetID[playerid]][partyMember][i] = -1;
                            }
                        }
                        else{
                            if(PartyData[PlayerPartyGetID[playerid]][partyMember][i] == playerid){
                                PartyData[PlayerPartyGetID[playerid]][partyMember][i] = PartyData[PlayerPartyGetID[playerid]][partyMember][i+1];
                                PartyData[PlayerPartyGetID[playerid]][partyMember][i+1] = -1;
                            } 
                        }
                        
                    }
                }

                foreach(new i : Player){
                    if(!LoggedIn[i]) continue;
                    if(PlayerPartyGetID[i] == PlayerPartyGetID[playerid]){
                        RemoveMarkers(i);
                        SendClientMessageEx(i, COLOR_YELLOW, "- ผู้เล่น %s ได้ออกจากปาร์ตี้แล้ว", ReturnRoleplayName(playerid));
                        UpdatePartyTextDrawForPlayer(i, PlayerPartyGetID[playerid]);
                    }
                }
                RemoveMarkers(playerid);
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ออกจากปาร์ตี้แล้ว", ReturnRoleplayName(playerid));
                HideAndDestroyPartyText(playerid);
                ResetPartyPlayer(playerid);
            }
            else if(PartyData[PlayerPartyGetID[playerid]][partyMember][0] == playerid){
                foreach(new i : Player) {
                    if(!LoggedIn[i]) continue;
                    if(PlayerPartyGetID[i] == partyid){
                        RemoveMarkers(i);
                        SendClientMessage(i, COLOR_YELLOW, "- ปาร์ตี้ของคุณถูกยุบแล้ว");
                        HideAndDestroyPartyText(i);
                        ResetPartyPlayer(i);
                    }
                }
                Party_Delete(partyid);
            }
        }
    }
    return 1;
}

HideAndDestroyPartyText(playerid){
    if(LoggedIn[playerid]){
        for(new i=0; i<MAX_PARTY_TEXTDRAW; i++){
            PlayerTextDrawHide(playerid, PartyTextDraw[playerid][i]);
            PlayerTextDrawDestroy(playerid, PartyTextDraw[playerid][i]);
        }

        for(new i=0; i<5; i++){
            HidePlayerProgressBar(playerid, PartyProgress[playerid][i]);
            DestroyPlayerProgressBar(playerid, PartyProgress[playerid][i]);
        }
    }
    return 1;
}

UpdatePartyTextDrawForPlayer(playerid, partyid){
    new string[128];
    if(PlayerInParty[playerid] && PlayerPartyGetID[playerid] != -1){
        if(PartyData[PlayerPartyGetID[playerid]][partyEx]){
            foreach(new i : Player) {
                if(!LoggedIn[i]) continue;
                if(PlayerPartyGetID[i] == partyid){
                    if(PartyData[partyid][partyMember][0] != -1){
                        PlayerTextDrawShow(i, PartyTextDraw[i][0]);
                        PlayerTextDrawShow(i, PartyTextDraw[i][1]);
                        PlayerTextDrawShow(i, PartyTextDraw[i][2]);

                        format(string, sizeof(string), "%s", ReturnRoleplayName(PartyData[partyid][partyMember][0]));
                        PlayerTextDrawSetString(i, PartyTextDraw[i][3], string);

                        PlayerTextDrawShow(i, PartyTextDraw[i][3]);
                        ShowPlayerProgressBar(i, PartyProgress[i][0]);
                    }
                    else if(PartyData[partyid][partyMember][0] == -1){
                        PlayerTextDrawHide(i, PartyTextDraw[i][0]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][1]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][2]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][3]);
                        HidePlayerProgressBar(i, PartyProgress[i][0]);
                    }

                    if(PartyData[partyid][partyMember][1] != -1){
                        PlayerTextDrawShow(i, PartyTextDraw[i][4]);
                        PlayerTextDrawShow(i, PartyTextDraw[i][5]);
                        PlayerTextDrawShow(i, PartyTextDraw[i][6]);

                        format(string, sizeof(string), "%s", ReturnRoleplayName(PartyData[partyid][partyMember][1]));
                        PlayerTextDrawSetString(i, PartyTextDraw[i][7], string);

                        PlayerTextDrawShow(i, PartyTextDraw[i][7]);
                        ShowPlayerProgressBar(i, PartyProgress[i][1]);
                    }
                    else if(PartyData[partyid][partyMember][1] == -1){
                        PlayerTextDrawHide(i, PartyTextDraw[i][4]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][5]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][6]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][7]);
                        HidePlayerProgressBar(i, PartyProgress[i][1]);
                    }

                    if(PartyData[partyid][partyMember][2] != -1){
                        PlayerTextDrawShow(i, PartyTextDraw[i][8]);
                        PlayerTextDrawShow(i, PartyTextDraw[i][9]);
                        PlayerTextDrawShow(i, PartyTextDraw[i][10]);

                        format(string, sizeof(string), "%s", ReturnRoleplayName(PartyData[partyid][partyMember][2]));
                        PlayerTextDrawSetString(i, PartyTextDraw[i][11], string);

                        PlayerTextDrawShow(i, PartyTextDraw[i][11]);
                        ShowPlayerProgressBar(i, PartyProgress[i][2]);
                    }
                    else if(PartyData[partyid][partyMember][2] == -1){
                        PlayerTextDrawHide(i, PartyTextDraw[i][8]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][9]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][10]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][11]);
                        HidePlayerProgressBar(i, PartyProgress[i][2]);
                    }

                    if(PartyData[partyid][partyMember][3] != -1){
                        PlayerTextDrawShow(i, PartyTextDraw[i][12]);
                        PlayerTextDrawShow(i, PartyTextDraw[i][13]);
                        PlayerTextDrawShow(i, PartyTextDraw[i][14]);

                        format(string, sizeof(string), "%s", ReturnRoleplayName(PartyData[partyid][partyMember][3]));
                        PlayerTextDrawSetString(i, PartyTextDraw[i][15], string);

                        PlayerTextDrawShow(i, PartyTextDraw[i][15]);
                        ShowPlayerProgressBar(i, PartyProgress[i][3]);
                    }
                    else if(PartyData[partyid][partyMember][3] == -1){
                        PlayerTextDrawHide(i, PartyTextDraw[i][12]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][13]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][14]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][15]);
                        HidePlayerProgressBar(i, PartyProgress[i][3]);
                    }

                    if(PartyData[partyid][partyMember][4] != -1){
                        PlayerTextDrawShow(i, PartyTextDraw[i][16]);
                        PlayerTextDrawShow(i, PartyTextDraw[i][17]);
                        PlayerTextDrawShow(i, PartyTextDraw[i][18]);

                        format(string, sizeof(string), "%s", ReturnRoleplayName(PartyData[partyid][partyMember][4]));
                        PlayerTextDrawSetString(i, PartyTextDraw[i][19], string);

                        PlayerTextDrawShow(i, PartyTextDraw[i][19]);
                        ShowPlayerProgressBar(i, PartyProgress[i][4]);
                    }
                    else if(PartyData[partyid][partyMember][4] == -1){
                        PlayerTextDrawHide(i, PartyTextDraw[i][16]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][17]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][18]);
                        PlayerTextDrawHide(i, PartyTextDraw[i][19]);
                        HidePlayerProgressBar(i, PartyProgress[i][4]);
                    }

                    UpdatePlayerMarker(i);
                }
            }
        } 
    }
    return 1;
}

UpdatePlayerMarker(playerid){
    if(PlayerInParty[playerid] && PlayerPartyGetID[playerid] != -1){
        new partyid = PlayerPartyGetID[playerid];
        if(PartyData[partyid][partyMember][0] != -1){
            SetPlayerMarkerForPlayer(playerid, PartyData[partyid][partyMember][0], TEAM_RED);
        }
        if(PartyData[partyid][partyMember][1] != -1){
            SetPlayerMarkerForPlayer(playerid, PartyData[partyid][partyMember][1], TEAM_YELLOW);
        }
        if(PartyData[partyid][partyMember][2] != -1){
            SetPlayerMarkerForPlayer(playerid, PartyData[partyid][partyMember][2], TEAM_GREEN);
        }
        if(PartyData[partyid][partyMember][3] != -1){
            SetPlayerMarkerForPlayer(playerid, PartyData[partyid][partyMember][3], TEAM_ORANGE);
        }
        if(PartyData[partyid][partyMember][4] != -1){
            SetPlayerMarkerForPlayer(playerid, PartyData[partyid][partyMember][4], TEAM_PINK);
        }
    }    
    return 1;
}

RemoveMarkers(playerid){
 	foreach(new i : Player){
        if(!LoggedIn[i]) continue;
        if(PlayerEnterCheckPoint[playerid] == 0 && EnterCheckPointJob[playerid] == 0){
            //SetPlayerMarkerForPlayer(playerid, i, 0xFFFFFF00);

            if(ServerData[ServerCanHoldGangZone] == 1 && GetGroupType(i) == GROUP_GANG){
                SetGroupColor(i);
            }

            if((PlayerData[i][pOnPlayerDuty] && GetGroupType(i) == GROUP_POLICE)){
                SetGroupColor(i);
            }

            if((PlayerData[i][pOnPlayerDuty] && GetGroupType(i) == GROUP_MEDIC)){
                SetGroupColor(i);
            }

            if((GetGroupType(i) == GROUP_MECHANIC)){
                SetGroupColor(i);
            }
        }
   	}
}

CMD:makeparty(playerid, const params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pLevel] < COMMAND_PARY_LEVEL) return ErrorMsg(playerid, "คุณต้องมีเลเวลมากกว่า 5 ขึ้นไป");
    if(PlayerInParty[playerid] || PlayerPartyGetID[playerid] != -1) return ErrorMsg(playerid, "คุณมีปาร์ตี้อยู่แล้ว");
    new id = Party_Create(playerid);
    if(id == -1) return ErrorMsg(playerid, "เซิฟเวอร์ได้สร้างปาร์ตี้จนเต็มแล้ว");
    SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ประสบความสำเร็จในการสร้างปาร์ตี้ ID: %d เรียบร้อยแล้ว", id);
    PlayerPartyGetID[playerid] = id;
    PlayerInParty[playerid] = 1;
    LoadPartyTextDrawPlayer(playerid);
    UpdatePartyTextDrawForPlayer(playerid, id);
    return 1;
}

CMD:leaveparty(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pLevel] < COMMAND_PARY_LEVEL) return ErrorMsg(playerid, "คุณต้องมีเลเวลมากกว่า 5 ขึ้นไป");
    if(!PlayerInParty[playerid] || PlayerPartyGetID[playerid] == -1) return ErrorMsg(playerid, "คุณยังไม่มีปาร์ตี้");
    if(PartyData[PlayerPartyGetID[playerid]][partyEx]){
        PlayerLeaveParty(playerid);
    }
    return 1;
}

/*CMD:checkmyparty(playerid, params[]){
    new partyid = PlayerPartyGetID[playerid];
    if(partyid != -1){
        if(PartyData[partyid][partyEx]){
            for(new i=0; i<MAX_PARTY; i++){
                SendClientMessageEx(playerid, COLOR_YELLOW, "[%d] %s", PartyData[partyid][partyMember][i], ReturnRoleplayName(PartyData[partyid][partyMember][i]));
            }
        }
    }
    return 1;
}*/

CMD:inviteparty(playerid, const params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pLevel] < COMMAND_PARY_LEVEL) return ErrorMsg(playerid, "คุณต้องมีเลเวลมากกว่า 5 ขึ้นไป");
    if(!PlayerInParty[playerid] || PlayerPartyGetID[playerid] == -1) return ErrorMsg(playerid, "คุณยังไม่มีปาร์ตี้");
    if(PartyData[PlayerPartyGetID[playerid]][partyEx]){
        if(PartyData[PlayerPartyGetID[playerid]][partyMember][0] != playerid) return ErrorMsg(playerid, "คุณไม่ใช่หัวหน้าปาร์ตี้");

        if(PartyData[PlayerPartyGetID[playerid]][partyMember][0] != -1 &&
           PartyData[PlayerPartyGetID[playerid]][partyMember][1] != -1 &&
           PartyData[PlayerPartyGetID[playerid]][partyMember][2] != -1 &&
           PartyData[PlayerPartyGetID[playerid]][partyMember][3] != -1 &&
           PartyData[PlayerPartyGetID[playerid]][partyMember][4] != -1){
               return ErrorMsg(playerid, "ปราตี้ของคุณเต็มแล้ว");
           }

        Dialog_ShowEasy(playerid, DialogInviteParty, DIALOG_STYLE_INPUT, "เชิญเข้าปาร์ตี้", "กรอกชื่อหรือไอดีผู้เล่นที่ต้องการจะชวนเข้าปาร์ตี้:", "ตกลง", "ยกเลิก");
    }
    return 1;
}

Dialog:DialogInviteParty(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new userid = strval(inputtext);
        new string[128];
        if(!LoggedIn[userid]) return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
        if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นไม่ถูกต้อง");
        if(userid == playerid) return ErrorMsg(playerid, "คุณไม่สามารถใช้กับตัวเองได้");
        if(PlayerInParty[userid] || PlayerPartyGetID[userid] != -1) return ErrorMsg(playerid, "ผู้เล่นนั้นมีปาร์ตี้อยู่แล้ว");
        if(!IsPlayerNearPlayer(playerid, userid, 5.0)) return ErrorMsg(playerid, "คุณไม่ได้อยู่ใกล้ผู้เล่นนั้น");
        PlayerPartyInviteID[userid] = playerid;
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ส่งคำเชิญเข้าร่วมปาร์ตี้ไปยัง %s เรียบร้อยแล้ว", ReturnRoleplayName(userid));
        format(string, sizeof(string), "%s ได้เชิญคุณเข้าร่วมปาร์ตี้", ReturnRoleplayName(playerid));
        Dialog_ShowEasy(userid, UserInviteParty, DIALOG_STYLE_MSGBOX, "เชิญเข้าปาร์ตี้", string, "ยอมรับ", "ปฏิเสธ");
    }
    return 1;
}

Dialog:UserInviteParty(playerid, response, listitem, inputtext[]){
    new string[128];
    if(!response){
        if(PlayerPartyInviteID[playerid] != -1){
            format(string, sizeof(string), "คุณได้ปฏิเสธการเข้าร่วมปาร์ตี้ของ %s เรียบร้อยแล้ว", ReturnRoleplayName(PlayerPartyInviteID[playerid]));
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การปฏิเสธเข้าร่วมปาร์ตี้", string, "ตกลง", "");

            format(string, sizeof(string), "ผู้เล่น %s ได้ปฏิเสธการเข้าร่วมปาร์ตี้ของคุณ", ReturnRoleplayName(playerid));
            Dialog_ShowEasy(PlayerPartyInviteID[playerid], ShowOnly, DIALOG_STYLE_MSGBOX, "การปฏิเสธเข้าร่วมปาร์ตี้", string, "ตกลง", "");
        }
        PlayerPartyInviteID[playerid] = -1;
    }
    if(response){
        new leaderid = PlayerPartyInviteID[playerid];
        if(leaderid != -1){
            if(PartyData[PlayerPartyGetID[leaderid]][partyEx]){
                for(new i=0; i<MAX_PARTY; i++){
                    if(PartyData[PlayerPartyGetID[leaderid]][partyMember][i] == -1){
                        PartyData[PlayerPartyGetID[leaderid]][partyMember][i] = playerid;
                        break;
                    }
                }
                PlayerInParty[playerid] = 1;
                PlayerPartyGetID[playerid] = PlayerPartyGetID[leaderid];
                LoadPartyTextDrawPlayer(playerid);
                UpdatePartyTextDrawForPlayer(playerid, PlayerPartyGetID[playerid]);
                foreach(new i : Player){
                    if(!LoggedIn[i]) continue;
                    if(PlayerPartyGetID[i] == PlayerPartyGetID[leaderid]){
                        SendClientMessageEx(i, COLOR_YELLOW, "- ผู้เล่น %s(%d) ได้เข้าร่วมปาร์ตี้ของคุณแล้ว", ReturnRoleplayName(playerid), playerid);
                    }
                }
                PlayerPartyInviteID[playerid] = -1;
            }
        }
    }
    return 1;
}

LoadPartyTextDrawPlayer(playerid){
    PartyTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 557.000000, 138.000000, "_");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][0], 0.600000, 0.949999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][0], 323.500000, 95.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][0], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][0], 135);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][0], 0);

    PartyTextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 514.000000, 138.000000, "_");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][1], 0.600000, 0.949999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][1], 323.500000, 10.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][1], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][1], -16777016);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][1], 0);

    PartyTextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 514.000000, 135.000000, "1");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][2], 2);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][2], 0.266665, 1.399999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][2], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][2], 1);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][2], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][2], 0);

    PartyTextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 524.000000, 136.000000, "Jonathan_Smither");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][3], 2);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][3], 0.116667, 0.899999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][3], 603.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][3], 1);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][3], 1);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][3], 0);

    PartyTextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 557.000000, 152.000000, "_");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][4], 0.600000, 0.949999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][4], 323.500000, 95.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][4], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][4], 135);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][4], 0);

    PartyTextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 514.000000, 152.000000, "_");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][5], 0.600000, 0.949999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][5], 323.500000, 10.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][5], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][5], -65336);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][5], 0);

    PartyTextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 514.000000, 149.000000, "2");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][6], 2);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][6], 0.266665, 1.399999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][6], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][6], 1);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][6], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][6], 0);

    PartyTextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 524.000000, 150.000000, "Jonathan_Smither");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][7], 2);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][7], 0.116667, 0.899999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][7], 603.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][7], 1);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][7], 1);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][7], 0);

    PartyTextDraw[playerid][8] = CreatePlayerTextDraw(playerid, 557.000000, 166.000000, "_");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][8], 0.600000, 0.949999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][8], 323.500000, 95.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][8], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][8], 135);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][8], 0);

    PartyTextDraw[playerid][9] = CreatePlayerTextDraw(playerid, 514.000000, 166.000000, "_");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][9], 0.600000, 0.949999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][9], 323.500000, 10.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][9], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][9], 16711880);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][9], 0);

    PartyTextDraw[playerid][10] = CreatePlayerTextDraw(playerid, 514.000000, 163.000000, "3");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][10], 2);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][10], 0.266665, 1.399999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][10], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][10], 1);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][10], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][10], 50);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][10], 0);

    PartyTextDraw[playerid][11] = CreatePlayerTextDraw(playerid, 524.000000, 164.000000, "Jonathan_Smither");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][11], 2);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][11], 0.116667, 0.899999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][11], 603.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][11], 1);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][11], 1);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][11], 50);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][11], 0);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][11], 0);

    PartyTextDraw[playerid][12] = CreatePlayerTextDraw(playerid, 557.000000, 180.000000, "_");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][12], 1);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][12], 0.600000, 0.949999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][12], 323.500000, 95.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][12], 1);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][12], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][12], 135);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][12], 0);

    PartyTextDraw[playerid][13] = CreatePlayerTextDraw(playerid, 514.000000, 180.000000, "_");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][13], 0.600000, 0.949999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][13], 323.500000, 10.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][13], 1);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][13], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][13], -8388408);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][13], 0);

    PartyTextDraw[playerid][14] = CreatePlayerTextDraw(playerid, 514.000000, 176.000000, "4");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][14], 2);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][14], 0.266665, 1.399999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][14], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][14], 0);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][14], 1);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][14], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][14], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][14], 50);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][14], 0);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][14], 0);

    PartyTextDraw[playerid][15] = CreatePlayerTextDraw(playerid, 524.000000, 178.000000, "Jonathan_Smither");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][15], 2);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][15], 0.116667, 0.899999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][15], 603.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][15], 0);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][15], 1);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][15], 1);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][15], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][15], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][15], 50);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][15], 0);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][15], 0);

    PartyTextDraw[playerid][16] = CreatePlayerTextDraw(playerid, 557.000000, 194.000000, "_");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][16], 1);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][16], 0.600000, 0.949999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][16], 323.500000, 95.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][16], 1);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][16], 0);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][16], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][16], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][16], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][16], 135);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][16], 0);

    PartyTextDraw[playerid][17] = CreatePlayerTextDraw(playerid, 514.000000, 194.000000, "_");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][17], 1);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][17], 0.600000, 0.949999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][17], 323.500000, 10.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][17], 1);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][17], 0);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][17], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][17], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][17], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][17], -8323128);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][17], 1);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][17], 0);

    PartyTextDraw[playerid][18] = CreatePlayerTextDraw(playerid, 514.000000, 190.000000, "5");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][18], 2);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][18], 0.266665, 1.399999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][18], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][18], 0);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][18], 1);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][18], 2);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][18], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][18], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][18], 50);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][18], 0);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][18], 0);

    PartyTextDraw[playerid][19] = CreatePlayerTextDraw(playerid, 524.000000, 192.000000, "Jonathan_Smither");
    PlayerTextDrawFont(playerid, PartyTextDraw[playerid][19], 2);
    PlayerTextDrawLetterSize(playerid, PartyTextDraw[playerid][19], 0.116667, 0.899999);
    PlayerTextDrawTextSize(playerid, PartyTextDraw[playerid][19], 603.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PartyTextDraw[playerid][19], 0);
    PlayerTextDrawSetShadow(playerid, PartyTextDraw[playerid][19], 1);
    PlayerTextDrawAlignment(playerid, PartyTextDraw[playerid][19], 1);
    PlayerTextDrawColor(playerid, PartyTextDraw[playerid][19], -1);
    PlayerTextDrawBackgroundColor(playerid, PartyTextDraw[playerid][19], 255);
    PlayerTextDrawBoxColor(playerid, PartyTextDraw[playerid][19], 50);
    PlayerTextDrawUseBox(playerid, PartyTextDraw[playerid][19], 0);
    PlayerTextDrawSetProportional(playerid, PartyTextDraw[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, PartyTextDraw[playerid][19], 0);

    PartyProgress[playerid][0] = CreatePlayerProgressBar(playerid, 522.000000, 146.000000, 86.500000, 0.500000, -16776961, 100.000000, 0);

    PartyProgress[playerid][1] = CreatePlayerProgressBar(playerid, 522.000000, 160.000000, 86.500000, 0.500000, -16776961, 100.000000, 0);

    PartyProgress[playerid][2] = CreatePlayerProgressBar(playerid, 522.000000, 174.000000, 86.500000, 0.500000, -16776961, 100.000000, 0);

    PartyProgress[playerid][3] = CreatePlayerProgressBar(playerid, 522.000000, 188.000000, 86.500000, 0.500000, -16776961, 100.000000, 0);

    PartyProgress[playerid][4] = CreatePlayerProgressBar(playerid, 522.000000, 201.000000, 86.500000, 1.000000, -16776961, 100.000000, 0);
    return 1;
}