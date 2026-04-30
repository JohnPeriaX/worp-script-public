#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetPlayerQuest(playerid){
    PlayerQuestAccept[playerid] = false;
    PlayerQuestState[playerid] = 0;

    PlayerQuest_Count2[playerid] = 0;
    PlayerQuest_Count3[playerid] = 0;
    PlayerQuest_Count4[playerid] = 0;
    PlayerQuest_Count5[playerid] = 0;
    PlayerQuest_Count6[playerid] = 0;
    PlayerQuest_Count7[playerid] = 0;
    PlayerQuest_Count8[playerid] = 0;
    PlayerQuest_Count9[playerid] = 0;
    PlayerQuest_Count10[playerid] = 0;
    PlayerQuest_Count11[playerid] = 0;
    PlayerQuest_Count12[playerid] = 0;
    PlayerQuest_Count13[playerid] = 0;
    return 1;
}

Dialog:AcceptQuest(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        PlayerQuestAccept[playerid] = true;
        PlayerQuestState[playerid] = 1;
        new string[256];
        format(string, sizeof string, "- คุณได้รับเควสเป็นที่เรียบร้อยแล้ว\
        \n- คุณสามารถเช็ครายละเอียดเควสได้ที่เมนูกระเป๋าของคุณและ 'Quest' เพื่อดูรายละเอียดเพิ่มเติม");
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
    }
    return 1;
}

ShowPlayerQuest(playerid){
    Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส", "คุณยังไม่มีเควสใดๆ", "ตกลง", "");
    /*if(!PlayerQuestAccept[playerid]) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส", "คุณยังไม่มีเควสใดๆ", "ตกลง", "");
    new string[256];
    if(PlayerQuestAccept[playerid] && PlayerQuestState[playerid] > 0){
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส", "รอการอัพเดท", "ตกลง", "");
        if(PlayerQuestState[playerid] == 1){    
            format(string, sizeof string, "สิ่งที่ต้องทำ: ฆ่านักเลง 1 คน (โซนสีเขียวบน Map)\n[รางวัล]: ได้รับ 'ไม้' จำนวน 20 ชิ้น");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 2){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ขโมยสายไฟ 20 ครั้ง\n[รางวัล]: ได้รับ 'เงินแดง' จำนวน $5,000\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 3){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ทำอาหารกินเองจำนวน 5 ครั้ง\n[รางวัล]: ได้รับ 'เหล็ก' จำนวน 20 ชิ้น\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 4){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ตกปลาธรรมดาครับ 50 ตัว\n[รางวัล]: ได้รับ 'ไม้' จำนวน 20 ชิ้น\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 5){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ฆ่านักเลง 5 คน (โซนสีเขียวบน Map)\n[รางวัล]: ได้รับ 'ดินปืน' จำนวน 10 ชิ้น\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 6){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ตกปลาฉลาม 100 ตัว\n[รางวัล]: ได้รับ 'ไม้' จำนวน 20 ชิ้น และ เหล็ก 20 ชิ้น\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 7){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ฆ่าวัวครบ 50 ตัว\n[รางวัล]: ได้รับ 'ดินปืน' จำนวน 10 ชิ้น\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 8){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ขนส่งแก๊สสำเร็จ 20 ครั้ง\n[รางวัล]: ได้รับ 'เหล็ก' จำนวน 50 ชิ้น\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 9){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ทำงานเก็บขยะ 10 ครั้ง\n[รางวัล]: ได้รับ 'ไม้' จำนวน 50 ชิ้น\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 10){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ฆ่านักเลง 20 คน (โซนสีเขียวบน Map)\n[รางวัล]: ได้รับ 'เงินเขียว' $10,000\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 11){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ทำงานก่อสร้างครบ 30 ครั้ง\n[รางวัล]: ได้รับ 'ดินปืน' จำนวน 20 ชิ้น\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 12){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ซ่อมเสาร์ไฟฟ้าครับ 20 ต้น\n[รางวัล]: ได้รับ 'ดินปืน' จำนวน 30 ชิ้น\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 13){
            format(string, sizeof string, "สิ่งที่ต้องทำ: ขนดินปืนครบ 10 ครั้ง\n[รางวัล]: ได้รับ 'ดินปืน' จำนวน 10 ชิ้น\n[คำเตือน]: หากคุณออกเกมหรือหลุดคุณจะต้องเริ่มทำใหม่");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
        else if(PlayerQuestState[playerid] == 14){
            format(string, sizeof string, "[!] คุณได้ทำเควส เควส คริสต์มาส สำเร็จแล้ว โปรดติดตามเควสใน Season ถัดไป...");
            Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควส คริสต์มาส", string, "ตกลง", "");
        }
    }*/
    return 1;
}

/*
    if(PlayerQuestAccept[playerid] && PlayerQuestState[playerid] == 1){
        new itemid = PlayerInventory_AddItem(playerid, "Wood", 19793, 20);
        if(itemid == -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] กระเป๋าของคุณเต็มไม่สามารถเก็บ ไม้ อีก 20 ชิ้นได้", "ตกลง", "");
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เควสสำเร็จ", "คุณได้สำเร็จเควส คริสต์มาส เรียบร้อยแล้ว\
        \nและได้รับ 'ไม้' จำนวน 20 ชิ้น\n[!] โปรดเช็คเควสถัดไปของคุณได้ที่เมนู H", "ตกลง", "");
        PlayerQuestState[playerid] = 2;
    }
*/