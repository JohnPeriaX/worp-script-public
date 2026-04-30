#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetPlayerStory(playerid){
    PlayerStoryGang[playerid][story_Enemy] = -1;
    format(PlayerStoryGang[playerid][story_EnemyName], 64, "NULL");
    PlayerStoryGang[playerid][story_Days] = 0;
    format(PlayerStoryGang[playerid][story_TimeStart], 32, "00:00");
    format(PlayerStoryGang[playerid][story_TimeEnd], 32, "00:00");
    PlayerStoryGang[playerid][story_Label] = 0;
    PlayerStoryGang[playerid][story_Bigcar] = 0;
    PlayerStoryGang[playerid][story_Pushhome] = 0;
    PlayerStoryGang[playerid][story_Hidebody] = 0;
    PlayerStoryGang[playerid][story_Skingang] = 0;
    PlayerStoryGang[playerid][story_Weapon] = 0;
    PlayerStoryGang[playerid][story_Money] = 0;
    format(PlayerStoryGang[playerid][story_Details], 256, "NULL");
    return 1;
}

PlayerSetVariableStory(playerid){
    if(PlayerData[playerid][pGroup] == -1) return 1;
    new story_id = -1;
    for(new i=0; i<MAX_STORY_GANG; i++){
        if(Story_Gang[i][story_Mygang] == PlayerData[playerid][pGroup]){
            story_id = i;
            break;
        }
        
        if(Story_Gang[i][story_Enemy] == PlayerData[playerid][pGroup]){
            story_id = i;
            break;
        }
    }

    if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
        PlayerHaveStoryID[playerid] = story_id;
    }
    return 1;
}

/*CMD:story(playerid, params[]){
    StoryMenu_Open(playerid);
    return 1;
}*/

hook OnGameModeInit(){
    CreateDynamic3DTextLabel("[จุดเปิดสตอรี่แก๊ง]\nกด 'Y' เพื่อใช้งาน", 0xFF8049FF, 1125.1279,-2037.1230,69.8821, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(!LoggedIn[playerid]) return 1;
    if(newkeys & KEY_YES){
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 1125.1279,-2037.1230,69.8821)){
            StoryMenu_Open(playerid);
        }
    }
    return 1;
}

StoryMenu_Open(playerid){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pGroup] == -1) return 1;
    if (PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]-1) return SendClientMessageEx(playerid, -1, "คุณต้องมียศอย่างต่ำ %d", GroupData[PlayerData[playerid][pGroup]][groupRanks]-1);
    
    new processing = -1, havestory = -1, isalliance = -1;
    for(new i=0; i<MAX_STORY_GANG; i++){
        if(Story_Gang[i][story_Mygang] == PlayerData[playerid][pGroup]){
            processing = i;
            break;
        }
        
        if(Story_Gang[i][story_Enemy] == PlayerData[playerid][pGroup]){
            havestory = i;
            break;
        }
    }

    new string[1024];
    if(havestory != -1){
        if(Story_Gang[havestory][story_State] == Story_Wait){
            SetPVarInt(playerid, "Story_ID", havestory);
            format(string, sizeof string, "แก๊ง '%s' ได้ยื่นทำสตอรี่มายังแก๊งของคุณ '%s'", Story_Gang[havestory][story_MygangName], Story_Gang[havestory][story_EnemyName]);
            Dialog_ShowEasy(playerid, NextDialogStory, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "ต่อไป", "ปิด");
        }
        else if(Story_Gang[havestory][story_State] == Story_Cancel){
            format(string, sizeof string, "{FC2B2B}| คุณได้ปฏิเสธการทำสตอรี่กับแก๊ง [%s] ไปแล้วกรุณารอการยืนยันจากแก๊ง [%s]", Story_Gang[havestory][story_MygangName], Story_Gang[havestory][story_MygangName]);
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "ตกลง", "");
        }
        else if(Story_Gang[havestory][story_State] == Story_Confirm){
            SetPVarInt(playerid, "Story_ID", havestory);
            format(string, sizeof string, "แก๊ง '%s' ได้เริ่มทำสตอรี่กับแก๊ง '%s' ของคุณแล้ว", Story_Gang[havestory][story_MygangName], Story_Gang[havestory][story_EnemyName]);
            Dialog_ShowEasy(playerid, ConfirmStoryEnemy, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "ต่อไป", "ปิด");
        }
        else if(Story_Gang[havestory][story_State] == Story_Finish){
            SetPVarInt(playerid, "Story_ID", havestory);
            if(GroupData[Story_Gang[havestory][story_Enemy]][groupKill] >= Story_Gang[havestory][story_Hidebody]){
                format(string, sizeof string, "แก๊ง '%s' ของคุณได้ชนะสตอรี่กับแก๊ง '%s' แล้ว ยินดีด้วย!!", Story_Gang[havestory][story_EnemyName], Story_Gang[havestory][story_MygangName]);
                Dialog_ShowEasy(playerid, ConfirmStoryEnemy, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "ต่อไป", "ปิด");
            }
            else{
                format(string, sizeof string, "แก๊งของคุณได้พ่ายแพ้การเล่นสตอรี่ให้กับ '%s' และคุณจะต้องเสียเงินจำนวน '%s' ให้กับแก๊ง '%s'\nโปรดรอ '%s' ยืนยันการสำเร็จสตอรี่เพื่อรับเงิน...", Story_Gang[havestory][story_MygangName], FormatNumber(Story_Gang[havestory][story_Money]), Story_Gang[havestory][story_MygangName], Story_Gang[havestory][story_MygangName]);
                Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "ตกลง", "");
            }
        }
    }
    else if(processing != -1){
        if(Story_Gang[processing][story_State] == Story_Wait){
            SetPVarInt(playerid, "Story_ID", processing);
            format(string, sizeof string, "แก๊ง '%s' ของคุณกำลังรอการตอบกลับของแก๊ง '%s' อยู่...", Story_Gang[processing][story_MygangName], Story_Gang[processing][story_EnemyName]);
            Dialog_ShowEasy(playerid, NextDialogMygangStory, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "เพิ่มเติม", "ปิด");
        }
        else if(Story_Gang[processing][story_State] == Story_Cancel){
            SetPVarInt(playerid, "Story_ID", processing);
            format(string, sizeof string, "แก๊ง '%s' ได้ทำการปฏิเสธคำขอเปิดสตอรี่ของคุณ.", Story_Gang[processing][story_EnemyName]);
            Dialog_ShowEasy(playerid, NextDialogMygangStory, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "เพิ่มเติม", "ปิด");
        }
        else if(Story_Gang[processing][story_State] == Story_Confirm){
            SetPVarInt(playerid, "Story_ID", processing);
            format(string, sizeof string, "แก๊ง '%s' ของคุณกับ '%s' ได้เริ่มทำสตอรี่กันแล้ว", Story_Gang[processing][story_MygangName], Story_Gang[processing][story_EnemyName]);
            Dialog_ShowEasy(playerid, NextDialogMygangStory, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "เพิ่มเติม", "ปิด");
        }
        else if(Story_Gang[processing][story_State] == Story_Finish){
            SetPVarInt(playerid, "Story_ID", processing);
            if(GroupData[Story_Gang[processing][story_Mygang]][groupKill] >= Story_Gang[processing][story_Hidebody]){
                format(string, sizeof string, "แก๊ง '%s' ของคุณได้ชนะสตอรี่กับแก๊ง '%s' แล้ว ยินดีด้วย!!", Story_Gang[processing][story_MygangName], Story_Gang[processing][story_EnemyName]);
                Dialog_ShowEasy(playerid, NextDialogMygangStory, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "ต่อไป", "ปิด");
            }
            else{
                format(string, sizeof string, "แก๊งของคุณได้พ่ายแพ้การเล่นสตอรี่ให้กับ '%s' และคุณจะต้องเสียเงินจำนวน '%s' ให้กับแก๊ง '%s'\nโปรดรอ '%s' ยืนยันการสำเร็จสตอรี่เพื่อรับเงิน...", Story_Gang[processing][story_EnemyName], FormatNumber(Story_Gang[processing][story_Money]), Story_Gang[processing][story_EnemyName], Story_Gang[processing][story_EnemyName]);
                Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "ตกลง", "");
            }
        }
    }
    else if(processing == -1 && havestory == -1 && isalliance == -1){
        ShowPlayerInputStory(playerid);
    }
    return 1;
}

Dialog:NextDialogMygangStory(playerid, response, listitem, inputtext[]){
    if(!response) return DeletePVar(playerid, "Story_ID");
    if(response){
        new string[128], status[32];
        new story_id = GetPVarInt(playerid, "Story_ID");
        if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
            if(Story_Gang[story_id][story_State] == Story_Wait) {
                status = "{FCB32B}รอการยืนยัน{FFFFFF}";
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[%s]", status);
            }
            else if(Story_Gang[story_id][story_State] == Story_Cancel) {
                status = "{FC2B2B}ถูกยกเลิก{FFFFFF}";
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[%s]\nยืนยันการปฏิเสธ (ลบคำขอทิ้ง)", status);
            }
            else if(Story_Gang[story_id][story_State] == Story_Confirm) {
                status = "{2BFC2B}ยืนยันแล้ว{FFFFFF}";
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[%s]", status);
            }
            else if(Story_Gang[story_id][story_State] == Story_Finish){
                status = "{2BFC2B}สำเร็จแล้ว{FFFFFF}";
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[%s]\nยืนยันการจบสตอรี่และรับเงินจำนวน '%s'", status, FormatNumber(Story_Gang[story_id][story_Money]));
            }
            Dialog_ShowEasy(playerid, TypeStoryMyGang, DIALOG_STYLE_LIST, "การทำสตอรี่", string, "เลือก", "ปิด");
        }
    }
    return 1;
}

Dialog:ConfirmStoryEnemy(playerid, response, listitem, inputtext[]){
    if(!response) return DeletePVar(playerid, "Story_ID");
    if(response){
        new story_id = GetPVarInt(playerid, "Story_ID");
        new string[256];
        if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
            if(GroupData[Story_Gang[story_id][story_Enemy]][groupKill] >= Story_Gang[story_id][story_Hidebody] && Story_Gang[story_id][story_State] == Story_Finish){
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[{03EC30}สำเร็จแล้ว{FFFFFF}]\nยืนยันการจบสตอรี่และรับเงินจำนวน '%s'", FormatNumber(Story_Gang[story_id][story_Money]));
                Dialog_ShowEasy(playerid, TypeConfirmStoryEnemy, DIALOG_STYLE_LIST, "การทำสตอรี่", string, "เลือก", "ปิด");
            }
            else{
                Dialog_ShowEasy(playerid, TypeConfirmStoryEnemy, DIALOG_STYLE_LIST, "การทำสตอรี่", "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[{03EC30}ยืนยันแล้ว{FFFFFF}]", "เลือก", "ปิด");
            }
        }  
    }
    return 1;
}

Dialog:NextDialogStory(playerid, response, listitem, inputtext[]){
    if(!response) return DeletePVar(playerid, "Story_ID");
    if(response){
        Dialog_ShowEasy(playerid, TypeStoryEnemyGang, DIALOG_STYLE_LIST, "การทำสตอรี่", "ดูรายละเอียดการทำสตอรี่\n{2AD800}ยอมรับ\n{F10707}ปฏิเสธ", "เลือก", "ปิด");
    }
    return 1;
}

Dialog:TypeStoryMyGang(playerid, response, listitem, inputtext[]){
    if(!response) {
        return DeletePVar(playerid, "Story_ID");
    }
    if(response){
        new story_id = GetPVarInt(playerid, "Story_ID");
        if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
            if(listitem == 0){
                if(listitem == 0){
                    new string[1024];
                    new label[32], bigcar[32], pushhome[32], skingang[32], weapon[32];
                    if(!Story_Gang[story_id][story_Label]) label = "ปิด";
                    else label = "เปิด";

                    if(!Story_Gang[story_id][story_Bigcar]) bigcar = "ปิด";
                    else bigcar = "เปิด";

                    if(!Story_Gang[story_id][story_Pushhome]) pushhome = "ปิด";
                    else pushhome = "เปิด";

                    if(!Story_Gang[story_id][story_Skingang]) skingang = "ปิด";
                    else skingang = "เปิด";

                    if(Story_Gang[story_id][story_Weapon] == 66535) weapon = "ไม่จำกัดอาวุธ";
                    else format(weapon, sizeof weapon, ReturnWeaponName(Story_Gang[story_id][story_Weapon]));

                    if(Story_Gang[story_id][story_Mygang] == PlayerData[playerid][pGroup]){
                        format(string, sizeof string, "แก๊งที่จะทำสตอรี่ด้วย: [%s]\
                        \nจำนวนวันที่เล่น: [%d]\
                        \nเวลาที่เล่น: [%s-%s]\
                        \nเลเบล: [%s]\
                        \nรถใหญ่เท่านั้น: [%s]\
                        \nบุกบ้าน: [%s]\
                        \nจำนวนศพ: [%d]\
                        \nใช้สกินแก๊งตลอดการเล่น: [%s]\
                        \nอาวุธที่ใช้: [%s]\
                        \nเงินเดิมพัน: [%s]", Story_Gang[story_id][story_EnemyName], Story_Gang[story_id][story_Days], Story_Gang[story_id][story_TimeStart], Story_Gang[story_id][story_TimeEnd]
                        , label, bigcar, pushhome, Story_Gang[story_id][story_Hidebody], skingang, weapon, FormatNumber(Story_Gang[story_id][story_Money]));
                        Dialog_ShowEasy(playerid, EnemyShowDetails3, DIALOG_STYLE_LIST, "การทำสตอรี่", string, "กลับ", "");
                    }
                }
            }
            if(listitem == 2){
                if(Story_Gang[story_id][story_State] == Story_Cancel){
                    Story_Delete(playerid, story_id);
                }
                else if(Story_Gang[story_id][story_State] == Story_Finish){
                    new string[256];
                    if(GroupData[Story_Gang[story_id][story_Enemy]][groupMoney] < Story_Gang[story_id][story_Money]){
                        format(string, sizeof string, "แก๊ง '%s' มีเงินในคลังไม่พอกับจำนวนเงินที่เดิมพัน, โปรดติดต่อแอดมินหรือเคลียร์กับหลีดของ '%s'", Story_Gang[story_id][story_EnemyName], Story_Gang[story_id][story_EnemyName]);
                        return Dialog_ShowEasy(playerid, ErrorMoneyFinishEnemy, DIALOG_STYLE_MSGBOX, "การยืนยันจบสตอรี่", string, "ตกลง", "");
                    }
                    else{
                        GroupData[Story_Gang[story_id][story_Enemy]][groupMoney] -= Story_Gang[story_id][story_Money];
                        GroupData[Story_Gang[story_id][story_Mygang]][groupMoney] += Story_Gang[story_id][story_Money];
                        SendFactionMessage(Story_Gang[story_id][story_Mygang], 0x00AAFFAA, "(( แก๊งของคุณได้รับเงินเดิมพัน '%s' จากการชนะสตอรี่กับแก๊ง '%s' ))", FormatNumber(Story_Gang[story_id][story_Money]), Story_Gang[story_id][story_EnemyName]);
                        SendFactionMessage(Story_Gang[story_id][story_Enemy], 0x00AAFFAA, "(( แก๊งของคุณเสียเงินเดิมพัน '%s' จากการแพ้สตอรี่กับแก๊ง '%s' ))", FormatNumber(Story_Gang[story_id][story_Money]), Story_Gang[story_id][story_MygangName]);
                        
                        Group_Save(Story_Gang[story_id][story_Mygang]);
                        Group_Save(Story_Gang[story_id][story_Enemy]);

                        format(Story_Gang[story_id][story_GangWinName], 64, Story_Gang[story_id][story_MygangName]);
                        Story_Save(story_id);
                        
                        ResetPlayerStory(playerid);
                        Story_FinishState(story_id);
                    }
                }
            }
        }
    }
    return 1;
}

Dialog:MoneyFailEnemyGang(playerid, response, listitem, inputtext[]){
    if(!response || response) return Dialog_ShowEasy(playerid, TypeStoryEnemyGang, DIALOG_STYLE_LIST, "การทำสตอรี่", "ดูรายละเอียดการทำสตอรี่\n{2AD800}ยอมรับ\n{F10707}ปฏิเสธ", "เลือก", "ปิด");
    return 1;
}

Dialog:TypeConfirmStoryEnemy(playerid, response, listitem, inputtext[]){
    if(!response) return DeletePVar(playerid, "Story_ID");
    if(response){
        new story_id = GetPVarInt(playerid, "Story_ID");
        if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
            if(listitem == 0){
                new string[1024];
                new label[32], bigcar[32], pushhome[32], skingang[32], weapon[32];
                if(!Story_Gang[story_id][story_Label]) label = "ปิด";
                else label = "เปิด";

                if(!Story_Gang[story_id][story_Bigcar]) bigcar = "ปิด";
                else bigcar = "เปิด";

                if(!Story_Gang[story_id][story_Pushhome]) pushhome = "ปิด";
                else pushhome = "เปิด";

                if(!Story_Gang[story_id][story_Skingang]) skingang = "ปิด";
                else skingang = "เปิด";

                if(Story_Gang[story_id][story_Weapon] == 66535) weapon = "ไม่จำกัดอาวุธ";
                else format(weapon, sizeof weapon, ReturnWeaponName(Story_Gang[story_id][story_Weapon]));

                if(Story_Gang[story_id][story_Enemy] == PlayerData[playerid][pGroup]){
                    format(string, sizeof string, "แก๊งที่จะทำสตอรี่ด้วย: [%s]\
                    \nจำนวนวันที่เล่น: [%d]\
                    \nเวลาที่เล่น: [%s-%s]\
                    \nเลเบล: [%s]\
                    \nรถใหญ่เท่านั้น: [%s]\
                    \nบุกบ้าน: [%s]\
                    \nจำนวนศพ: [%d]\
                    \nใช้สกินแก๊งตลอดการเล่น: [%s]\
                    \nอาวุธที่ใช้: [%s]\
                    \nเงินเดิมพัน: [%s]", Story_Gang[story_id][story_MygangName], Story_Gang[story_id][story_Days], Story_Gang[story_id][story_TimeStart], Story_Gang[story_id][story_TimeEnd]
                    , label, bigcar, pushhome, Story_Gang[story_id][story_Hidebody], skingang, weapon, FormatNumber(Story_Gang[story_id][story_Money]));
                    Dialog_ShowEasy(playerid, EnemyShowDetails2, DIALOG_STYLE_LIST, "การทำสตอรี่", string, "กลับ", "");
                }
            }
            if(listitem == 2){
                new string[256];
                if(GroupData[Story_Gang[story_id][story_Mygang]][groupMoney] < Story_Gang[story_id][story_Money]){
                    format(string, sizeof string, "แก๊ง '%s' มีเงินในคลังไม่พอกับจำนวนเงินที่เดิมพัน, โปรดติดต่อแอดมินหรือเคลียร์กับหลีดของ '%s'", Story_Gang[story_id][story_MygangName], Story_Gang[story_id][story_MygangName]);
                    return Dialog_ShowEasy(playerid, ErrorMoneyFinishEnemy, DIALOG_STYLE_MSGBOX, "การยืนยันจบสตอรี่", string, "ตกลง", "");
                }
                else{
                    GroupData[Story_Gang[story_id][story_Enemy]][groupMoney] += Story_Gang[story_id][story_Money];
                    GroupData[Story_Gang[story_id][story_Mygang]][groupMoney] -= Story_Gang[story_id][story_Money];
                    SendFactionMessage(Story_Gang[story_id][story_Enemy], 0x00AAFFAA, "(( แก๊งของคุณได้รับเงินเดิมพัน '%s' จากการชนะสตอรี่กับแก๊ง '%s' ))", FormatNumber(Story_Gang[story_id][story_Money]), Story_Gang[story_id][story_MygangName]);
                    SendFactionMessage(Story_Gang[story_id][story_Mygang], 0x00AAFFAA, "(( แก๊งของคุณเสียเงินเดิมพัน '%s' จากการแพ้สตอรี่กับแก๊ง '%s' ))", FormatNumber(Story_Gang[story_id][story_Money]), Story_Gang[story_id][story_EnemyName]);
                    
                    Group_Save(Story_Gang[story_id][story_Mygang]);
                    Group_Save(Story_Gang[story_id][story_Enemy]);

                    format(Story_Gang[story_id][story_GangWinName], 64, Story_Gang[story_id][story_EnemyName]);
                    Story_Save(story_id);

                    ResetPlayerStory(playerid);
                    Story_FinishState(story_id);
                }
            }
        }
    }
    return 1;
}

Dialog:ErrorMoneyFinishEnemy(playerid, response, listitem, inputtext[]){
    if(!response || response){
        new story_id = GetPVarInt(playerid, "Story_ID");
        new string[256];
        if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
            if(GroupData[Story_Gang[story_id][story_Enemy]][groupKill] >= Story_Gang[story_id][story_Hidebody] && Story_Gang[story_id][story_State] == Story_Finish){
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[{03EC30}สำเร็จแล้ว{FFFFFF}]\nยืนยันการจบสตอรี่และรับเงินจำนวน '%s'", FormatNumber(Story_Gang[story_id][story_Money]));
                Dialog_ShowEasy(playerid, TypeConfirmStoryEnemy, DIALOG_STYLE_LIST, "การทำสตอรี่", string, "เลือก", "ปิด");
            }
            else{
                Dialog_ShowEasy(playerid, TypeConfirmStoryEnemy, DIALOG_STYLE_LIST, "การทำสตอรี่", "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[{03EC30}ยืนยันแล้ว{FFFFFF}]", "เลือก", "ปิด");
            }
        }  
        return 1;
    }
    return 1;
}

Dialog:EnemyShowDetails3(playerid, response, listitem, inputtext[]){
    if(!response || response) {
        new story_id = GetPVarInt(playerid, "Story_ID");
        new string[128], status[32];
        if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
            if(Story_Gang[story_id][story_State] == Story_Wait) {
                status = "{FCB32B}รอการยืนยัน{FFFFFF}";
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[%s]", status);
            }
            else if(Story_Gang[story_id][story_State] == Story_Cancel) {
                status = "{FC2B2B}ถูกยกเลิก{FFFFFF}";
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[%s]\nยืนยันการปฏิเสธ (ลบคำขอทิ้ง)", status);
            }
            else if(Story_Gang[story_id][story_State] == Story_Confirm) {
                status = "{2BFC2B}ยืนยันแล้ว{FFFFFF}";
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[%s]", status);
            }
            else if(Story_Gang[story_id][story_State] == Story_Finish){
                status = "{2BFC2B}สำเร็จแล้ว{FFFFFF}";
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[%s]\nยืนยันการจบสตอรี่และรับเงินจำนวน '%s'", status, FormatNumber(Story_Gang[story_id][story_Money]));
            }
            Dialog_ShowEasy(playerid, TypeStoryMyGang, DIALOG_STYLE_LIST, "การทำสตอรี่", string, "เลือก", "ปิด");
        }
        
    }
    return 1;
}

Dialog:EnemyShowDetails2(playerid, response, listitem, inputtext[]){
    if(!response || response) {
        new story_id = GetPVarInt(playerid, "Story_ID");
        new string[128];
        if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
            if(Story_Gang[story_id][story_State] == Story_Finish){
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[{03EC30}สำเร็จแล้ว{FFFFFF}]\nยืนยันการจบสตอรี่และรับเงินจำนวน '%s'", FormatNumber(Story_Gang[story_id][story_Money]));
                Dialog_ShowEasy(playerid, TypeConfirmStoryEnemy, DIALOG_STYLE_LIST, "การทำสตอรี่", string, "เลือก", "ปิด");
            }
            else{
                return Dialog_ShowEasy(playerid, TypeConfirmStoryEnemy, DIALOG_STYLE_LIST, "การทำสตอรี่", "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[{03EC30}ยืนยันแล้ว{FFFFFF}]", "เลือก", "ปิด");
            }
            
        }
        
    }
    return 1;
}

Dialog:TypeStoryEnemyGang(playerid, response, listitem, inputtext[]){
    if(!response) return DeletePVar(playerid, "Story_ID");
    if(response){
        new story_id = GetPVarInt(playerid, "Story_ID");
        if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
            if(listitem == 0){
                ShowDetailsStory(playerid, story_id);
            }
            if(listitem == 1){
                if(GroupData[Story_Gang[story_id][story_Enemy]][groupMoney] >= Story_Gang[story_id][story_Money]){
                    Story_ConfirmState(playerid, story_id);
                }else{
                    Dialog_ShowEasy(playerid, MoneyFailEnemyGang, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", "| เงินในคลังแก๊งของคุณมีไม่พอ, กรุณาลองใหม่อีกครั้ง", "ตกลง", "");
                }
            }
            if(listitem == 2){
                Story_CancelState(playerid, story_id);
            }
        }
    }
    return 1;
}

ShowDetailsStory(playerid, story_id){
    new string[1024];

    new label[32], bigcar[32], pushhome[32], skingang[32], weapon[32];
    if(!Story_Gang[story_id][story_Label]) label = "ปิด";
    else label = "เปิด";

    if(!Story_Gang[story_id][story_Bigcar]) bigcar = "ปิด";
    else bigcar = "เปิด";

    if(!Story_Gang[story_id][story_Pushhome]) pushhome = "ปิด";
    else pushhome = "เปิด";

    if(!Story_Gang[story_id][story_Skingang]) skingang = "ปิด";
    else skingang = "เปิด";

    if(Story_Gang[story_id][story_Weapon] == 66535) weapon = "ไม่จำกัดอาวุธ";
    else format(weapon, sizeof weapon, ReturnWeaponName(Story_Gang[story_id][story_Weapon]));

    if(Story_Gang[story_id][story_Enemy] == PlayerData[playerid][pGroup]){
        format(string, sizeof string, "แก๊งที่จะทำสตอรี่ด้วย: [%s]\
        \nจำนวนวันที่เล่น: [%d]\
        \nเวลาที่เล่น: [%s-%s]\
        \nเลเบล: [%s]\
        \nรถใหญ่เท่านั้น: [%s]\
        \nบุกบ้าน: [%s]\
        \nจำนวนศพ: [%d]\
        \nใช้สกินแก๊งตลอดการเล่น: [%s]\
        \nอาวุธที่ใช้: [%s]\
        \nเงินเดิมพัน: [%s]", Story_Gang[story_id][story_MygangName], Story_Gang[story_id][story_Days], Story_Gang[story_id][story_TimeStart], Story_Gang[story_id][story_TimeEnd]
        , label, bigcar, pushhome, Story_Gang[story_id][story_Hidebody], skingang, weapon, FormatNumber(Story_Gang[story_id][story_Money]));
        Dialog_ShowEasy(playerid, EnemyShowDetails, DIALOG_STYLE_LIST, "การทำสตอรี่", string, "กลับ", "");
    }
    
    if(Story_Gang[story_id][story_Mygang] == PlayerData[playerid][pGroup]){
        format(string, sizeof string, "แก๊งที่จะทำสตอรี่ด้วย: [%s]\
        \nจำนวนวันที่เล่น: [%d]\
        \nเวลาที่เล่น: [%s-%s]\
        \nเลเบล: [%s]\
        \nรถใหญ่เท่านั้น: [%s]\
        \nบุกบ้าน: [%s]\
        \nจำนวนศพ: [%d]\
        \nใช้สกินแก๊งตลอดการเล่น: [%s]\
        \nอาวุธที่ใช้: [%s]\
        \nเงินเดิมพัน: [%s]", Story_Gang[story_id][story_EnemyName], Story_Gang[story_id][story_Days], Story_Gang[story_id][story_TimeStart], Story_Gang[story_id][story_TimeEnd]
        , label, bigcar, pushhome, Story_Gang[story_id][story_Hidebody], skingang, weapon, FormatNumber(Story_Gang[story_id][story_Money]));
        Dialog_ShowEasy(playerid, MygangShowDetails, DIALOG_STYLE_LIST, "การทำสตอรี่", string, "กลับ", "");
    }
    return 1;
}

Dialog:MygangShowDetails(playerid, response, listitem, inputtext[]){
    if(!response || response){
        new string[128], status[64];
        new story_id = GetPVarInt(playerid, "Story_ID");
        if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
            if(Story_Gang[story_id][story_State] == Story_Wait) {
                status = "{FCB32B}รอการยืนยัน{FFFFFF}";
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[%s]", status);
            }
            else if(Story_Gang[story_id][story_State] == Story_Cancel) {
                status = "{FC2B2B}ถูกยกเลิก{FFFFFF}";
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[%s]\nยืนยันการปฏิเสธ (ลบคำขอทิ้ง)", status);
            }
            else if(Story_Gang[story_id][story_State] == Story_Confirm) {
                status = "{2BFC2B}ยืนยันแล้ว{FFFFFF}";
                format(string, sizeof string, "ดูรายละเอียดการทำสตอรี่\nสถานะ\t[%s]", status);
            }
            Dialog_ShowEasy(playerid, TypeStoryMyGang, DIALOG_STYLE_LIST, "การทำสตอรี่", string, "เลือก", "ปิด");
        }
        return 1;
    }
    return 1;
}

Dialog:EnemyShowDetails(playerid, response, listitem, inputtext[]){
    if(!response || response) return Dialog_ShowEasy(playerid, TypeStoryEnemyGang, DIALOG_STYLE_LIST, "การทำสตอรี่", "ดูรายละเอียดการทำสตอรี่\n{2AD800}ยอมรับ\n{F10707}ปฏิเสธ", "เลือก", "ปิด");
    return 1;
}

CheckGang_IsStory(groupid){
    for(new i=0; i<MAX_STORY_GANG; i++){
        if(Story_Gang[i][story_Mygang] == groupid) return i;
        if(Story_Gang[i][story_Enemy] == groupid) return i;
    }
    return -1;
}

CheckGang_IsSelect(playerid, groupid){
    if(PlayerData[playerid][pGroup] == groupid) return groupid;
    if(PlayerStoryGang[playerid][story_Enemy] == groupid) return groupid;
    return -1;
}

ShowPlayerInputStory(playerid){
    new string[1024];
    new enemy[64], label[32], bigcar[32], pushhome[32], skingang[32], weapon[32];
    if(PlayerStoryGang[playerid][story_Enemy] == -1) format(enemy, 64, "โปรดเลือก");
    else format(enemy, 64, PlayerStoryGang[playerid][story_EnemyName]);

    if(!PlayerStoryGang[playerid][story_Label]) label = "ปิด";
    else label = "เปิด";

    if(!PlayerStoryGang[playerid][story_Bigcar]) bigcar = "ปิด";
    else bigcar = "เปิด";

    if(!PlayerStoryGang[playerid][story_Pushhome]) pushhome = "ปิด";
    else pushhome = "เปิด";

    if(!PlayerStoryGang[playerid][story_Skingang]) skingang = "ปิด";
    else skingang = "เปิด";

    if(PlayerStoryGang[playerid][story_Weapon] == 66535) weapon = "ไม่จำกัดอาวุธ";
    else format(weapon, sizeof weapon, ReturnWeaponName(PlayerStoryGang[playerid][story_Weapon]));

    format(string, sizeof string, "แก๊งที่จะทำสตอรี่ด้วย: [%s]\
    \nจำนวนวันที่เล่น: [%d]\
    \nเวลาที่เล่น: [%s-%s]\
    \nเลเบล: [%s]\
    \nรถใหญ่เท่านั้น: [%s]\
    \nบุกบ้าน: [%s]\
    \nจำนวนศพ: [%d]\
    \nใช้สกินแก๊งตลอดการเล่น: [%s]\
    \nอาวุธที่ใช้: [%s]\
    \nเงินเดิมพัน: [%s]\
    \n>> ยื่นเรื่องทำสตอรี่ <<", enemy, PlayerStoryGang[playerid][story_Days], PlayerStoryGang[playerid][story_TimeStart], PlayerStoryGang[playerid][story_TimeEnd]
    , label, bigcar, pushhome, PlayerStoryGang[playerid][story_Hidebody], skingang, weapon, FormatNumber(PlayerStoryGang[playerid][story_Money]));
    Dialog_ShowEasy(playerid, MakeStoryMenu, DIALOG_STYLE_LIST, "การทำสตอรี่", string, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:MakeStoryMenu(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            SelectEnemyStory(playerid);
        }
        if(listitem == 1){
            Dialog_ShowEasy(playerid, Input_StoryDays, DIALOG_STYLE_INPUT, "จำนวนวันที่ต้องการเล่น", "ใส่จำนวนวันที่คุณต้องการจะเล่นสตอรี่:", "ตกลง", "กลับ");
        }
        if(listitem == 2){
            new string[128];
            format(string, sizeof string, "เวลาเริ่ม: [%s]\nเวลาจบ: [%s]", PlayerStoryGang[playerid][story_TimeStart], PlayerStoryGang[playerid][story_TimeEnd]);
            Dialog_ShowEasy(playerid, Input_StoryTime, DIALOG_STYLE_LIST, "เลือกเวลาที่ต้องการเล่น", string, "เลือก", "กลับ");
        }
        if(listitem == 3){
            if(!PlayerStoryGang[playerid][story_Label]) PlayerStoryGang[playerid][story_Label] = true;
            else PlayerStoryGang[playerid][story_Label] = false;
            return ShowPlayerInputStory(playerid);
        }
        if(listitem == 4){
            if(!PlayerStoryGang[playerid][story_Bigcar]) PlayerStoryGang[playerid][story_Bigcar] = true;
            else PlayerStoryGang[playerid][story_Bigcar] = false;
            return ShowPlayerInputStory(playerid);
        }
        if(listitem == 5){
            if(!PlayerStoryGang[playerid][story_Pushhome]) PlayerStoryGang[playerid][story_Pushhome] = true;
            else PlayerStoryGang[playerid][story_Pushhome] = false;
            return ShowPlayerInputStory(playerid);
        }
        if(listitem == 6){
            Dialog_ShowEasy(playerid, Input_StoryHidebody, DIALOG_STYLE_INPUT, "จำนวนศพ", "ใส่จำนวนศพที่ต้องการ:", "ตกลง", "กลับ");
        }
        if(listitem == 7){
            if(!PlayerStoryGang[playerid][story_Skingang]) PlayerStoryGang[playerid][story_Skingang] = true;
            else PlayerStoryGang[playerid][story_Skingang] = false;
            return ShowPlayerInputStory(playerid);
        }
        if(listitem == 8){
            Dialog_ShowEasy(playerid, Input_StoryWeapon, DIALOG_STYLE_LIST, "เลือกอาวุธที่ใช้ในการเล่นสตอรี่", "หมัด\nสนับมือ\nไม้กอล์ฟ\nไม้เท้า\nไม้พลู\nไม้เบสบอล\nดาบคาตานะ\nไม่จำกัดอาวุธ", "เลือก", "กลับ");
        }
        if(listitem == 9){
            Dialog_ShowEasy(playerid, Input_StoryMoney, DIALOG_STYLE_INPUT, "จำนวนเงินที่คุณต้องการเดิมพัน", "ใส่จำนวนเงินที่คุณต้องการจะเดิมพัน: ", "ตกลง", "กลับ");
        }
        if(listitem == 10){
            CheckConfirmStory(playerid);
        }
    }
    return 1;
}

CheckConfirmStory(playerid){
    if(PlayerStoryGang[playerid][story_Enemy] == -1 || PlayerStoryGang[playerid][story_Days] <= 0 || PlayerStoryGang[playerid][story_Hidebody] <= 0 || !strcmp(PlayerStoryGang[playerid][story_TimeStart], "00:00", true) || !strcmp(PlayerStoryGang[playerid][story_TimeEnd], "00:00", true)){
        return Dialog_ShowEasy(playerid, ReConfirmStory, DIALOG_STYLE_MSGBOX, "ไม่สามารถยื่นเรื่องสตอรี่ได้", "[!] คุณกรอกเงื่อนไขไม่ครบตามกำหนด, โปรดลองใหม่อีกครั้ง", "ตกลง", "");
    }

    if(PlayerStoryGang[playerid][story_Money] > GroupData[PlayerData[playerid][pGroup]][groupMoney]){
        return Dialog_ShowEasy(playerid, ReConfirmStory, DIALOG_STYLE_MSGBOX, "ไม่สามารถยื่นเรื่องสตอรี่ได้", "[!] เงินในคลังของคุณไม่พอกับจำนวนที่จะเดิมพัน, โปรดลองใหม่อีกครั้ง", "ตกลง", "");
    }

    new story_id = -1;
    if((story_id = Iter_Free(Iter_Story)) != -1){
        Story_Gang[story_id][story_Mygang] = PlayerData[playerid][pGroup];
        format(Story_Gang[story_id][story_MygangName], 64, GroupData[PlayerData[playerid][pGroup]][groupName]);
        Story_Gang[story_id][story_Enemy] = PlayerStoryGang[playerid][story_Enemy];
        format(Story_Gang[story_id][story_EnemyName], 64, PlayerStoryGang[playerid][story_EnemyName]);
        Story_Gang[story_id][story_Days] = PlayerStoryGang[playerid][story_Days];
        format(Story_Gang[story_id][story_TimeStart], 32, PlayerStoryGang[playerid][story_TimeStart]);
        format(Story_Gang[story_id][story_TimeEnd], 32, PlayerStoryGang[playerid][story_TimeEnd]);
        Story_Gang[story_id][story_Label] = PlayerStoryGang[playerid][story_Label];
        Story_Gang[story_id][story_Bigcar] = PlayerStoryGang[playerid][story_Bigcar];
        Story_Gang[story_id][story_Pushhome] = PlayerStoryGang[playerid][story_Pushhome];
        Story_Gang[story_id][story_Hidebody] = PlayerStoryGang[playerid][story_Hidebody];
        Story_Gang[story_id][story_Skingang] = PlayerStoryGang[playerid][story_Skingang];
        Story_Gang[story_id][story_Weapon] = PlayerStoryGang[playerid][story_Weapon];
        Story_Gang[story_id][story_Money] = PlayerStoryGang[playerid][story_Money];
        format(Story_Gang[story_id][story_Details], 256, PlayerStoryGang[playerid][story_Details]);
        Story_Gang[story_id][story_State] = Story_Wait;
        format(Story_Gang[story_id][story_GangWinName], 64, "NULL");

        new tmphour, tmpminute, tmpsecond;
        gettime(tmphour, tmpminute, tmpsecond);

        Story_Gang[story_id][story_TimeHour] = tmphour;

        new query[256];
        mysql_format(dbCon, query, sizeof query, "INSERT INTO `story_gangs` (`story_Mygang`) VALUES(%d)", Story_Gang[story_id][story_Mygang]);
		mysql_tquery(dbCon, query, "OnStoryCreated", "ii", playerid, story_id);
    }
    return 1;
}

forward OnStoryCreated(playerid, story_id);
public OnStoryCreated(playerid, story_id){
	new insert_id = cache_insert_id();
	if(insert_id) {
        new string[128];
		Iter_Add(Iter_Story, story_id);
		Story_Gang[story_id][story_ID] = insert_id;
		Story_Save(story_id);

        format(string, sizeof string, "| คุณได้ยื่นเรื่องการทำสตอรี่ไปยังแก๊ง '%s' เรียบร้อยแล้ว", Story_Gang[story_id][story_EnemyName]);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "ตกลง", "");

		format(string, sizeof(string), "แก๊ง '%s' ได้ทำการยื่นเรื่องเปิดสตอรี่ให้กับแก๊ง '%s'", Story_Gang[story_id][story_MygangName], Story_Gang[story_id][story_EnemyName]);
        SendAdminsMessage(1, COLOR_GRAY, string);
        ResetPlayerStory(playerid);
	}
	else {
        ResetPlayerStory(playerid);
		SendClientMessage(playerid, -1, "[!] ไม่สามารถเปิดสตอรี่ได้ในขณะนี้");
	}
	return 1;
}

Story_FinishState(story_id){
    if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
        new string[256];
        format(string, sizeof string, "[StoryGang]: '%s' VS '%s' >> Close!", Story_Gang[story_id][story_MygangName], Story_Gang[story_id][story_EnemyName]);
        DCC_SendChannelMessage(StoryGangChannel, string);
        format(string, sizeof string, "%d", Story_Gang[story_id][story_ID]);
        DCC_SendChannelMessage(StoryGangChannel, string);

        GroupData[Story_Gang[story_id][story_Mygang]][groupKill] = 0;
        GroupData[Story_Gang[story_id][story_Enemy]][groupKill] = 0;
        Group_Save(Story_Gang[story_id][story_Mygang]);
        Group_Save(Story_Gang[story_id][story_Enemy]);

        foreach(new i : Player) if(LoggedIn[i]){
            if(PlayerData[i][pGroup] == Story_Gang[story_id][story_Mygang]){
                PlayerHaveStoryID[i] = -1;
            }
            else if(PlayerData[i][pGroup] == Story_Gang[story_id][story_Enemy]){
                PlayerHaveStoryID[i] = -1;
            }
        }

        Story_Gang[story_id][story_ID] = 0;
        Story_Gang[story_id][story_Mygang] = -1;
        format(Story_Gang[story_id][story_MygangName], 64, "NULL");
        Story_Gang[story_id][story_Enemy] = -1;
        format(Story_Gang[story_id][story_EnemyName], 64, "NULL");
        Story_Gang[story_id][story_Days] = 0;
        format(Story_Gang[story_id][story_TimeStart], 32, "00:00");
        format(Story_Gang[story_id][story_TimeEnd], 32, "00:00");
        Story_Gang[story_id][story_Label] = 0;
        Story_Gang[story_id][story_Bigcar] = 0;
        Story_Gang[story_id][story_Pushhome] = 0;
        Story_Gang[story_id][story_Hidebody] = 0;
        Story_Gang[story_id][story_Skingang] = 0;
        Story_Gang[story_id][story_Weapon] = 0;
        Story_Gang[story_id][story_Money] = 0;
        format(Story_Gang[story_id][story_Details], 256, "NULL");
        Story_Gang[story_id][story_State] = 0;
        Story_Gang[story_id][story_TimeHour] = 0;
        format(Story_Gang[story_id][story_GangWinName], 64, "NULL");
        Iter_Remove(Iter_Story, story_id);
    }
    return 1;   
}

Story_TimeoutState(story_id){
    if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
        new string[256];
        format(string, sizeof string, "[StoryGang]: '%s' VS '%s' >> Timeout!", Story_Gang[story_id][story_MygangName], Story_Gang[story_id][story_EnemyName]);
        DCC_SendChannelMessage(StoryGangChannel, string);
        format(string, sizeof string, "%d", Story_Gang[story_id][story_ID]);
        DCC_SendChannelMessage(StoryGangChannel, string);

        GroupData[Story_Gang[story_id][story_Mygang]][groupKill] = 0;
        GroupData[Story_Gang[story_id][story_Enemy]][groupKill] = 0;
        Group_Save(Story_Gang[story_id][story_Mygang]);
        Group_Save(Story_Gang[story_id][story_Enemy]);

        foreach(new i : Player) if(LoggedIn[i]){
            if(PlayerData[i][pGroup] == Story_Gang[story_id][story_Mygang]){
                PlayerHaveStoryID[i] = -1;
            }
            else if(PlayerData[i][pGroup] == Story_Gang[story_id][story_Enemy]){
                PlayerHaveStoryID[i] = -1;
            }
        }

        Story_Gang[story_id][story_ID] = 0;
        Story_Gang[story_id][story_Mygang] = -1;
        format(Story_Gang[story_id][story_MygangName], 64, "NULL");
        Story_Gang[story_id][story_Enemy] = -1;
        format(Story_Gang[story_id][story_EnemyName], 64, "NULL");
        Story_Gang[story_id][story_Days] = 0;
        format(Story_Gang[story_id][story_TimeStart], 32, "00:00");
        format(Story_Gang[story_id][story_TimeEnd], 32, "00:00");
        Story_Gang[story_id][story_Label] = 0;
        Story_Gang[story_id][story_Bigcar] = 0;
        Story_Gang[story_id][story_Pushhome] = 0;
        Story_Gang[story_id][story_Hidebody] = 0;
        Story_Gang[story_id][story_Skingang] = 0;
        Story_Gang[story_id][story_Weapon] = 0;
        Story_Gang[story_id][story_Money] = 0;
        format(Story_Gang[story_id][story_Details], 256, "NULL");
        Story_Gang[story_id][story_State] = 0;
        Story_Gang[story_id][story_TimeHour] = 0;
        format(Story_Gang[story_id][story_GangWinName], 64, "NULL");
        Iter_Remove(Iter_Story, story_id);
    }
    return 1;
}

StoryGang_Finish(story_id){
    if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
        Story_Gang[story_id][story_State] = Story_Finish;
        Story_Save(story_id);
    }
    return 1;
}

Story_Delete(playerid, story_id){
    if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){

        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", "| คุณได้ลบคำขอทำสตอรี่ทิ้งเรียบร้อยแล้ว", "ตกลง", "");

        new query[128];

        mysql_format(dbCon, query, sizeof query, "DELETE FROM story_gangs WHERE story_ID = '%d'", Story_Gang[story_id][story_ID]);
        mysql_query(dbCon, query);

        Story_Gang[story_id][story_ID] = 0;
        Story_Gang[story_id][story_Mygang] = -1;
        format(Story_Gang[story_id][story_MygangName], 64, "NULL");
        Story_Gang[story_id][story_Enemy] = -1;
        format(Story_Gang[story_id][story_EnemyName], 64, "NULL");
        Story_Gang[story_id][story_Days] = 0;
        format(Story_Gang[story_id][story_TimeStart], 32, "00:00");
        format(Story_Gang[story_id][story_TimeEnd], 32, "00:00");
        Story_Gang[story_id][story_Label] = 0;
        Story_Gang[story_id][story_Bigcar] = 0;
        Story_Gang[story_id][story_Pushhome] = 0;
        Story_Gang[story_id][story_Hidebody] = 0;
        Story_Gang[story_id][story_Skingang] = 0;
        Story_Gang[story_id][story_Weapon] = 0;
        Story_Gang[story_id][story_Money] = 0;
        format(Story_Gang[story_id][story_Details], 256, "NULL");
        Story_Gang[story_id][story_State] = 0;
        Story_Gang[story_id][story_TimeHour] = 0;
        format(Story_Gang[story_id][story_GangWinName], 64, "NULL");
        Iter_Remove(Iter_Story, story_id);
    }
    return 1;
}

Story_ConfirmState(playerid, story_id){
    if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
        new string[256];
        format(string, sizeof string, "{03EC30}| คุณได้ทำการยืนยันการทำสตอรี่กับแก๊ง '%s' เรียบร้อยแล้ว\n| เช็ครายละเอียดได้ที่ Discord ห้อง ประกาศเปิดสอตรี่-จบสตอรี่", Story_Gang[story_id][story_MygangName]);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "ตกลง", "");
        format(string, sizeof string, "[StoryGang]: '%s' VS '%s' >> Open!", Story_Gang[story_id][story_MygangName], Story_Gang[story_id][story_EnemyName]);
        DCC_SendChannelMessage(StoryGangChannel, string);
        format(string, sizeof string, "%d", Story_Gang[story_id][story_ID]);
        DCC_SendChannelMessage(StoryGangChannel, string);
        Story_Gang[story_id][story_State] = Story_Confirm;
        Story_Save(story_id);

        foreach(new i : Player) if(LoggedIn[i]){
            if(PlayerData[i][pGroup] == Story_Gang[story_id][story_Mygang]){
                PlayerHaveStoryID[i] = story_id;
            }
            else if(PlayerData[i][pGroup] == Story_Gang[story_id][story_Enemy]){
                PlayerHaveStoryID[i] = story_id;
            }
        }
    }
    return 1;
}

Story_CancelState(playerid, story_id){
    if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
        new string[128];
        format(string, sizeof string, "| คุณได้ปฏิเสธการทำสตอรี่กับแก๊ง '%s' เรียบร้อยแล้ว", Story_Gang[story_id][story_MygangName]);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การทำสตอรี่", string, "ตกลง", "");
        Story_Gang[story_id][story_State] = Story_Cancel;
        Story_Save(story_id);
    }
    return 1;
}

forward StoryGang_Load();
public StoryGang_Load(){
    new rows;
    cache_get_row_count(rows);
    for (new i = 0; i < rows; i ++) if (i < MAX_STORY_GANG){
        cache_get_value_name_int(i, "story_ID", Story_Gang[i][story_ID]);
        cache_get_value_name_int(i, "story_Mygang", Story_Gang[i][story_Mygang]);
        cache_get_value_name(i, "story_MygangName", Story_Gang[i][story_MygangName], 64);
        cache_get_value_name_int(i, "story_Enemy", Story_Gang[i][story_Enemy]);
        cache_get_value_name(i, "story_EnemyName", Story_Gang[i][story_EnemyName], 64);
        cache_get_value_name_int(i, "story_Days", Story_Gang[i][story_Days]);
        cache_get_value_name(i, "story_TimeStart", Story_Gang[i][story_TimeStart], 32);
        cache_get_value_name(i, "story_TimeEnd", Story_Gang[i][story_TimeEnd], 32);
        cache_get_value_name_int(i, "story_Label", Story_Gang[i][story_Label]);
        cache_get_value_name_int(i, "story_Bigcar", Story_Gang[i][story_Bigcar]);
        cache_get_value_name_int(i, "story_Pushhome", Story_Gang[i][story_Pushhome]);
        cache_get_value_name_int(i, "story_Hidebody", Story_Gang[i][story_Hidebody]);
        cache_get_value_name_int(i, "story_Skingang", Story_Gang[i][story_Skingang]);
        cache_get_value_name_int(i, "story_Weapon", Story_Gang[i][story_Weapon]);
        cache_get_value_name_int(i, "story_Money", Story_Gang[i][story_Money]);
        cache_get_value_name_int(i, "story_State", Story_Gang[i][story_State]);
        cache_get_value_name_int(i, "story_TimeHour", Story_Gang[i][story_TimeHour]);
        cache_get_value_name(i, "story_GangWinName", Story_Gang[i][story_GangWinName], 64);

        Iter_Add(Iter_Story, i);
    }
    printf("(( [MYSQL]: Load %d StoryGang Successfully ))", Iter_Count(Iter_Story));
    return 1;
}

Story_Save(story_id){
    if(story_id != -1 && Iter_Contains(Iter_Story, story_id)){
        new query[1024];
        mysql_format(dbCon, query, sizeof(query), "UPDATE `story_gangs` SET story_Mygang = '%d', story_MygangName = '%e', story_Enemy = '%d', story_EnemyName = '%e', story_Days = '%d', story_TimeStart = '%e', story_TimeEnd = '%e'",
            Story_Gang[story_id][story_Mygang],
            Story_Gang[story_id][story_MygangName],
            Story_Gang[story_id][story_Enemy],
            Story_Gang[story_id][story_EnemyName],
            Story_Gang[story_id][story_Days],
            Story_Gang[story_id][story_TimeStart],
            Story_Gang[story_id][story_TimeEnd]
        );

        mysql_format(dbCon, query, sizeof(query), "%s, story_Label = '%d', story_Bigcar = '%d', story_Pushhome = '%d', story_Hidebody = '%d', story_Skingang = '%d', story_Weapon = '%d', story_Money = '%d', story_State = '%d', story_TimeHour = '%d', story_GangWinName = '%e' WHERE `story_ID` = %d",
            query,
            Story_Gang[story_id][story_Label],
            Story_Gang[story_id][story_Bigcar],
            Story_Gang[story_id][story_Pushhome],
            Story_Gang[story_id][story_Hidebody],
            Story_Gang[story_id][story_Skingang],
            Story_Gang[story_id][story_Weapon],
            Story_Gang[story_id][story_Money],
            Story_Gang[story_id][story_State],
            Story_Gang[story_id][story_TimeHour],
            Story_Gang[story_id][story_GangWinName],
            Story_Gang[story_id][story_ID]
        );
        return mysql_tquery(dbCon, query);
    }
    return 1;
}

Dialog:ReConfirmStory(playerid, response, listitem, inputtext[]){
    if(!response || response) return ShowPlayerInputStory(playerid);
    return 1;
}

Dialog:Input_StoryMoney(playerid, response, listitem, inputtext[]){
    if(!response) return ShowPlayerInputStory(playerid);
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0) return Dialog_ShowEasy(playerid, Input_StoryMoney, DIALOG_STYLE_INPUT, "จำนวนเงินที่คุณต้องการเดิมพัน", "[!] คุณจะต้องใส่จำนวนเงินมากกว่า 0\nใส่จำนวนเงินที่คุณต้องการจะเดิมพัน: ", "ตกลง", "กลับ");
    
        if(amount > GroupData[PlayerData[playerid][pGroup]][groupMoney]){
            return Dialog_ShowEasy(playerid, Input_StoryMoney, DIALOG_STYLE_INPUT, "จำนวนเงินที่คุณต้องการเดิมพัน", "[!] เงินในคลังแก๊งของคุณไม่พอกับจำนวนที่จะเดิมพัน\nใส่จำนวนเงินที่คุณต้องการจะเดิมพัน: ", "ตกลง", "กลับ");
        }

        PlayerStoryGang[playerid][story_Money] = amount;
        return ShowPlayerInputStory(playerid);
    }
    return 1;
}

Dialog:Input_StoryTimeEnd(playerid, response, listitem, inputtext[]){
    if(!response){
        new string[128];
        format(string, sizeof string, "เวลาเริ่ม: [%s]\nเวลาจบ: [%s]", PlayerStoryGang[playerid][story_TimeStart], PlayerStoryGang[playerid][story_TimeEnd]);
        Dialog_ShowEasy(playerid, Input_StoryTime, DIALOG_STYLE_LIST, "เลือกเวลาที่ต้องการเล่น", string, "เลือก", "กลับ");
        return 1;
    }
    if(response){
        if(!CheckPatternTime(inputtext)) return Dialog_ShowEasy(playerid, Input_StoryTimeEnd, DIALOG_STYLE_INPUT, "ใส่เวลาเริ่มเล่นสตอรี่", "[!] รูปแบบเวลาไม่ถูกต้อง\nกรุณาใส่เวลาจบสตอรี่ เช่น 12:00 เป็นต้น", "ตกลง", "กลับ");
        format(PlayerStoryGang[playerid][story_TimeEnd], 32, inputtext);
        new string[128];
        format(string, sizeof string, "เวลาเริ่ม: [%s]\nเวลาจบ: [%s]", PlayerStoryGang[playerid][story_TimeStart], PlayerStoryGang[playerid][story_TimeEnd]);
        Dialog_ShowEasy(playerid, Input_StoryTime, DIALOG_STYLE_LIST, "เลือกเวลาที่ต้องการเล่น", string, "เลือก", "กลับ");
        return 1;
    }
    return 1;
}

Dialog:Input_StoryTimeStart(playerid, response, listitem, inputtext[]){
    if(!response){
        new string[128];
        format(string, sizeof string, "เวลาเริ่ม: [%s]\nเวลาจบ: [%s]", PlayerStoryGang[playerid][story_TimeStart], PlayerStoryGang[playerid][story_TimeEnd]);
        Dialog_ShowEasy(playerid, Input_StoryTime, DIALOG_STYLE_LIST, "เลือกเวลาที่ต้องการเล่น", string, "เลือก", "กลับ");
        return 1;
    }
    if(response){
        if(!CheckPatternTime(inputtext)) return Dialog_ShowEasy(playerid, Input_StoryTimeStart, DIALOG_STYLE_INPUT, "ใส่เวลาเริ่มเล่นสตอรี่", "[!] รูปแบบเวลาไม่ถูกต้อง\nกรุณาใส่เวลาเริ่มเล่นสตอรี่ เช่น 06:00 เป็นต้น", "ตกลง", "กลับ");
        format(PlayerStoryGang[playerid][story_TimeStart], 32, inputtext);
        new string[128];
        format(string, sizeof string, "เวลาเริ่ม: [%s]\nเวลาจบ: [%s]", PlayerStoryGang[playerid][story_TimeStart], PlayerStoryGang[playerid][story_TimeEnd]);
        Dialog_ShowEasy(playerid, Input_StoryTime, DIALOG_STYLE_LIST, "เลือกเวลาที่ต้องการเล่น", string, "เลือก", "กลับ");
        return 1;
    }
    return 1;
}

Dialog:Input_StoryTime(playerid, response, listitem, inputtext[]){
    if(!response) return ShowPlayerInputStory(playerid);
    if(response){
        if(listitem == 0){
            Dialog_ShowEasy(playerid, Input_StoryTimeStart, DIALOG_STYLE_INPUT, "ใส่เวลาเริ่มเล่นสตอรี่", "กรุณาใส่เวลาเริ่มเล่นสตอรี่ เช่น 06:00 เป็นต้น", "ตกลง", "กลับ");
        }
        if(listitem == 1){
            Dialog_ShowEasy(playerid, Input_StoryTimeEnd, DIALOG_STYLE_INPUT, "ใส่เวลาจบสตอรี่", "กรุณาใส่เวลาจบสตอรี่ เช่น 12:00 เป็นต้น", "ตกลง", "กลับ");
        }
    }
    return 1;
}

Dialog:Input_StoryWeapon(playerid, response, listitem, inputtext[]){
    if(!response) return ShowPlayerInputStory(playerid);
    if(response){
        if(listitem == 0) PlayerStoryGang[playerid][story_Weapon] = 0;
        if(listitem == 1) PlayerStoryGang[playerid][story_Weapon] = 1;
        if(listitem == 2) PlayerStoryGang[playerid][story_Weapon] = 2;
        if(listitem == 3) PlayerStoryGang[playerid][story_Weapon] = 15;
        if(listitem == 4) PlayerStoryGang[playerid][story_Weapon] = 7;
        if(listitem == 5) PlayerStoryGang[playerid][story_Weapon] = 5;
        if(listitem == 6) PlayerStoryGang[playerid][story_Weapon] = 8;
        if(listitem == 7) PlayerStoryGang[playerid][story_Weapon] =  66535;
        return ShowPlayerInputStory(playerid);
    }
    return 1;
}

Dialog:Input_StoryHidebody(playerid, response, listitem, inputtext[]){
    if(!response) return ShowPlayerInputStory(playerid);
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0 || amount > 100) return Dialog_ShowEasy(playerid, Input_StoryHidebody, DIALOG_STYLE_INPUT, "จำนวนศพ", "[!] จำนวนศพสามารถเล่นได้ตั้งแต่ 1-100 เท่านั้น\nใส่จำนวนศพที่ต้องการ:", "ตกลง", "กลับ");
        PlayerStoryGang[playerid][story_Hidebody] = amount;
        return ShowPlayerInputStory(playerid);
    }
    return 1;
}

Dialog:Input_StoryDays(playerid, response, listitem, inputtext[]){
    if(!response) return ShowPlayerInputStory(playerid);
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0 || amount > 3) return Dialog_ShowEasy(playerid, Input_StoryDays, DIALOG_STYLE_INPUT, "จำนวนวันที่ต้องการเล่น", "[!] สตอรี่สามารถเล่นได้ตั้งแต่ 1-3 วันเท่านั้น\nใส่จำนวนวันที่คุณต้องการจะเล่นสตอรี่:", "ตกลง", "กลับ");
        PlayerStoryGang[playerid][story_Days] = amount;
        return ShowPlayerInputStory(playerid);
    }
    return 1;
}

Dialog:ShowOnlyHaveResponse(playerid, response, listitem, inputtext[]){
    if(!response || response) return ShowPlayerInputStory(playerid);
    return 1;
}

SelectEnemyStory(playerid){
	new string[2048], menu[20], count;
	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

	SetPVarInt(playerid, "page", 1);
	for(new i=0; i<MAX_GROUPS; i++){
        if(PlayerData[playerid][pGroup] == i) continue;
        if(GroupData[i][groupType] != GROUP_GANG) continue;
        if(CheckGang_IsStory(i) != -1) continue;
        if(CheckGang_IsSelect(playerid, i) != -1) continue;
        if(count == 20){
            format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
            break;
        }
        format(menu, 20, "menu%d", ++count);
        SetPVarInt(playerid, menu, i);
        format(string, sizeof(string), "%s%s\n", string, GroupData[i][groupName]);
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnlyHaveResponse, DIALOG_STYLE_MSGBOX, "เลือกแก๊งที่จะทำสตอรี่", "ไม่พบแก๊งที่สามารถทำสตอรี่ได้!..", "กลับ", "");
	else Dialog_ShowEasy(playerid, SearchGang_Story, DIALOG_STYLE_LIST, "เลือกแก๊งที่จะทำสตอรี่", string, "เลือก", "กลับ");
	return 1;
}

Dialog:SearchGang_Story(playerid, response, listitem, inputtext[]){
    if(!response) return ShowPlayerInputStory(playerid);
    if(response) {
		new menu[20];
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menu%d", listitem);
			SetPVarInt(playerid, "storyGroupID", GetPVarInt(playerid, str_biz));
			SetStoryGangEnemy(playerid);
			return 1;
		}

		new currentPage = GetPVarInt(playerid, "page");
		if(listitem==0) if(currentPage>1) currentPage--;
		else if(listitem == 21) currentPage++;

		new string[2048], count;
		format(string, sizeof(string), "%s{B4B5B7}หน้า %d\n", string, (currentPage==1) ? 1 : currentPage-1);

		SetPVarInt(playerid, "page", currentPage);

		new skipitem = (currentPage-1) * 20;

		for(new i=0; i<MAX_GROUPS; i++){
            if(PlayerData[playerid][pGroup] == i) continue;
            if(GroupData[i][groupType] != GROUP_GANG) continue;
            if(CheckGang_IsStory(i) != -1) continue;
            if(CheckGang_IsSelect(playerid, i) != -1) continue;
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
            format(string, sizeof(string), "%s%s\n", string, GroupData[i][groupName]);
		}
		Dialog_ShowEasy(playerid, SearchGang_Story, DIALOG_STYLE_LIST, "เลือกแก๊งที่จะทำสตอรี่", string, "เลือก", "กลับ");
	}
    return 1;
}

SetStoryGangEnemy(playerid){
    new gangstory = GetPVarInt(playerid, "storyGroupID");
    if(gangstory != -1){
        PlayerStoryGang[playerid][story_Enemy] = gangstory;
        format(PlayerStoryGang[playerid][story_EnemyName], 64, GroupData[gangstory][groupName]);
        return ShowPlayerInputStory(playerid);
    }
    return 1;
}