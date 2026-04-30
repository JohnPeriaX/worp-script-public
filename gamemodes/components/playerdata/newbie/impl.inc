#if defined _inc_impl
	#undef _inc_impl
#endif

//QuestionOne
ShowTestingOne(playerid){
    new string[512];
    format(string, sizeof(string), "ก. การจำลองบทบาทจากชีวิตจริงมาใช้ในเกม\
    \nข. การทำร้ายคนอื่นโดยไม่มีเหตุผล\
    \nค. การปล้นผู้เล่นอื่น\
    \nง. การขอยืมตังผู้เล่นอื่น");
    Dialog_ShowEasy(playerid, QuestionOne, DIALOG_STYLE_LIST, "คำถามที่ 1: คำว่า Roleplay หมายถึงอะไร?", string, "ต่อไป", "");
    return 1;
}

Dialog:QuestionOne(playerid, response, listitem, inputtext[]){
    if(!response) return ShowTestingOne(playerid);
    if(response){
        if(listitem == 0){
            TestingScore[playerid] += 1;
            ShowTestingTwo(playerid);
        }
        if(listitem == 1){
            ShowTestingTwo(playerid);
        }
        if(listitem == 2){
            ShowTestingTwo(playerid);
        }
        if(listitem == 3){
            ShowTestingTwo(playerid);
        }
    }
    return 1;
}

//QuestionTwo
ShowTestingTwo(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "ก. คือการขับยานพาหนะจงใจที่จะทำดาเมจกับผู้เล่นอื่น ( ไม่ควรทำ )\
    \nข. คือการกระทำเกินความเป็นจริง เช่น ไม่กลัวปืนของเจ้าหน้าที่ตำรวจ ( ไม่ควรทำ )\
    \nค. คือการฆ่าผู้เล่นอื่นหรือทำร้ายผู้เล่นอื่นโดยไม่มีบทบาทหรือสตอรี่ใดๆเลย ( ไม่ควรทำ )\
    \nง. คือการกระโดดติดต่อกันเป็นจำนวนหลายๆครั้ง ( ควรทำ )");
    Dialog_ShowEasy(playerid, QuestionTwo, DIALOG_STYLE_LIST, "คำถามที่ 2: Deathmatching (DM) คืออะไรควรทำหรือไม่?", string, "ต่อไป", "");
    return 1;
}

Dialog:QuestionTwo(playerid, response, listitem, inputtext[]){
    if(!response) return ShowTestingTwo(playerid);
    if(response){
        if(listitem == 0){
            ShowTestingThree(playerid);
        }
        if(listitem == 1){
            ShowTestingThree(playerid);
        }
        if(listitem == 2){
            TestingScore[playerid] += 1;
            ShowTestingThree(playerid);
        }
        if(listitem == 3){
            ShowTestingThree(playerid);
        }
    }
    return 1;
}

//QuestionThree
ShowTestingThree(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "ก. คือการฆ่าผู้เล่นอื่นหรือทำร้ายผู้เล่นอื่นโดยไม่มีบทบาทหรือสตอรี่ใดๆเลย ( ไม่ควรทำ )\
    \nข. คือการกระโดดติดต่อกันเป็นจำนวนหลายๆครั้ง ( ควรทำ )\
    \nค. คือการขับยานพาหนะจงใจที่จะทำดาเมจกับผู้เล่นอื่น ( ไม่ควรทำ )\
    \nง. คือการกระทำเกินความเป็นจริง เช่น ไม่กลัวปืนของเจ้าหน้าที่ตำรวจ ( ไม่ควรทำ )");
    Dialog_ShowEasy(playerid, QuestionThree, DIALOG_STYLE_LIST, "คำถามที่ 3: Powergaming (PG) คืออะไรควรทำหรือไม่?", string, "ต่อไป", "");
    return 1;
}

Dialog:QuestionThree(playerid, response, listitem, inputtext[]){
    if(!response) return ShowTestingThree(playerid);
    if(response){
        if(listitem == 0){
            ShowTestingFour(playerid);
        }
        if(listitem == 1){
            ShowTestingFour(playerid);
        }
        if(listitem == 2){
            ShowTestingFour(playerid);
        }
        if(listitem == 3){
            TestingScore[playerid] += 1;
            ShowTestingFour(playerid);
        }
    }
    return 1;
}

//QuestionFour
ShowTestingFour(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "ก. คือการกระทำเกินความเป็นจริง เช่น ไม่กลัวปืนของเจ้าหน้าที่ตำรวจ ( ไม่ควรทำ )\
    \nข. คือการขับยานพาหนะจงใจที่จะทำดาเมจกับผู้เล่นอื่น ( ไม่ควรทำ )\
    \nค. คือการขับยานพาหนะจงใจที่จะทำดาเมจกับผู้เล่นอื่น ( ควรทำ )\
    \nง. คือการฆ่าผู้เล่นอื่นหรือทำร้ายผู้เล่นอื่นโดยไม่มีบทบาทหรือสตอรี่ใดๆเลย ( ไม่ควรทำ )");
    Dialog_ShowEasy(playerid, QuestionFour, DIALOG_STYLE_LIST, "คำถามที่ 4: Driver By (DB) คืออะไรควรทำหรือไม่?", string, "ต่อไป", "");
    return 1;
}

Dialog:QuestionFour(playerid, response, listitem, inputtext[]){
    if(!response) return ShowTestingFour(playerid);
    if(response){
        if(listitem == 0){
            ShowTestingFive(playerid);
        }
        if(listitem == 1){
            TestingScore[playerid] += 1;
            ShowTestingFive(playerid);
        }
        if(listitem == 2){
            ShowTestingFive(playerid);
        }
        if(listitem == 3){
            ShowTestingFive(playerid);
        }
    }
    return 1;
}

//QuestionFive
ShowTestingFive(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "ก. คือการขับรถชนผู้เล่นอื่นโดยไม่มีบทบาท\
    \nข. คือการล้างแค้นโดยไม่มีที่สิ้นสุด\
    \nค. คือการนำเรื่อง OOC และ IC มาผสมกัน ( ไม่ควรทำอย่างยิ่ง )\
    \nง. คือการฆ่าผู้เล่นอื่นหรือทำร้ายผู้เล่นอื่นโดยไม่มีบทบาทหรือสตอรี่ใดๆเลย ( ไม่ควรทำ )");
    Dialog_ShowEasy(playerid, QuestionFive, DIALOG_STYLE_LIST, "คำถามที่ 5: Metagaming(MG) คืออะไร?", string, "ต่อไป", "");
    return 1;
}

Dialog:QuestionFive(playerid, response, listitem, inputtext[]){
    if(!response) return ShowTestingFive(playerid);
    if(response){
        if(listitem == 0){
            ShowTestingSix(playerid);
        }
        if(listitem == 1){
            ShowTestingSix(playerid);
        }
        if(listitem == 2){
            TestingScore[playerid] += 1;
            ShowTestingSix(playerid);
        }
        if(listitem == 3){
            ShowTestingSix(playerid);
        }
    }
    return 1;
}

//QuestionSix
ShowTestingSix(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "ก. คือการออกเกมหนีบทบาท เช่น กำลังโดนจับตรวจไล่แล้วหนีออกเกม\
    \nข. คือการใช้โปรแกรมช่วยเล่นต่างๆ\
    \nค. คือการมีเรื่องกันในสถานที่ต้องห้าม\
    \nง. คือการนำเรื่อง OOC และ IC มาผสมกัน ( ไม่ควรทำอย่างยิ่ง )");
    Dialog_ShowEasy(playerid, QuestionSix, DIALOG_STYLE_LIST, "คำถามที่ 6: Quit Game (QG) คืออะไร?", string, "ต่อไป", "");
    return 1;
}

Dialog:QuestionSix(playerid, response, listitem, inputtext[]){
    if(!response) return ShowTestingSix(playerid);
    if(response){
        if(listitem == 0){
            TestingScore[playerid] += 1;
            ShowTestingSeven(playerid);
        }
        if(listitem == 1){
            ShowTestingSeven(playerid);
        }
        if(listitem == 2){
            ShowTestingSeven(playerid);
        }
        if(listitem == 3){
            ShowTestingSeven(playerid);
        }
    }
    return 1;
}

//QuestionSeven
ShowTestingSeven(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "ก. การปล้นจะต้องรวมกลุ่มมากกว่า 5 คนขึ้นไป\
    \nข. การปล้นจะต้องรวมกลุ่มมากกว่า 7 คนขึ้นไป\
    \nค. การปล้นจะต้องรวมกลุ่มมากกว่า 3 คนขึ้นไป\
    \nง. การปล้นจะต้องรวมกลุ่มมากกว่า 2 คนขึ้นไป");
    Dialog_ShowEasy(playerid, QuestionSeven, DIALOG_STYLE_LIST, "คำถามที่ 7: การปล้นจะต้องรวมกลุ่มกี่คน?", string, "ต่อไป", "");
    return 1;
}

Dialog:QuestionSeven(playerid, response, listitem, inputtext[]){
    if(!response) return ShowTestingSeven(playerid);
    if(response){
        if(listitem == 0){
            ShowTestingEight(playerid);
        }
        if(listitem == 1){
            ShowTestingEight(playerid);
        }
        if(listitem == 2){
            ShowTestingEight(playerid);
        }
        if(listitem == 3){
            TestingScore[playerid] += 1;
            ShowTestingEight(playerid);
        }
    }
    return 1;
}

//QuestionEight
ShowTestingEight(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "ก. สามารถปล้นเงินเขียวได้สูงสุด $10,000 เท่านั้น\
    \nข. สามารถปล้นเงินเขียวได้สูงสุด $5,000 เท่านั้น\
    \nค. สามารถปล้นเงินเขียวได้สูงสุด $6,000 เท่านั้น\
    \nง. สามารถปล้นเงินเขียวได้สูงสุด $9,000 เท่านั้น");
    Dialog_ShowEasy(playerid, QuestionEight, DIALOG_STYLE_LIST, "คำถามที่ 8: สามารถปล้นเงินเขียวได้สูงสุดเท่าไหร่?", string, "ต่อไป", "");
    return 1;
}

Dialog:QuestionEight(playerid, response, listitem, inputtext[]){
    if(!response) return ShowTestingEight(playerid);
    if(response){
        if(listitem == 0){
            ShowTestingNine(playerid);
        }
        if(listitem == 1){
            TestingScore[playerid] += 1;
            ShowTestingNine(playerid);
        }
        if(listitem == 2){
            ShowTestingNine(playerid);
        }
        if(listitem == 3){
            ShowTestingNine(playerid);
        }
    }
    return 1;
}

//QuestionNine
ShowTestingNine(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "ก. จะต้องมี ตำรวจ 3 คน, หมอ 5 คน\
    \nข. จะต้องมี ตำรวจ 2 คน, หมอ 1 คน\
    \nค. จะต้องมี ตำรวจ 1 คน, หมอ 2 คน\
    \nง. จะต้องมี ตำรวจ 4 คน, หมอ 2 คน");
    Dialog_ShowEasy(playerid, QuestionNine, DIALOG_STYLE_LIST, "คำถามที่ 9: ลักพาตัวประชาชน หน่วยรัฐต้องมีกี่คน?", string, "ต่อไป", "");
    return 1;
}

Dialog:QuestionNine(playerid, response, listitem, inputtext[]){
    if(!response) return ShowTestingNine(playerid);
    if(response){
        if(listitem == 0){
            ShowTestingTen(playerid);
        }
        if(listitem == 1){
            ShowTestingTen(playerid);
        }
        if(listitem == 2){
            ShowTestingTen(playerid);
        }
        if(listitem == 3){
            TestingScore[playerid] += 1;
            ShowTestingTen(playerid);
        }
    }
    return 1;
}

//QuestionTen
ShowTestingTen(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "ก. จะต้องมีความสัมพันธ์กับตัวประกัน เรียกได้สูงสุด $10,000\
    \nข. จะต้องมีความสัมพันธ์กับตัวประกัน เรียกได้สูงสุด $20,000\
    \nค. ไม่ต้องมีความสัมพันธ์กับตัวประกัน เรียกได้สูงสุด $20,000\
    \nง. ไม่ต้องมีความสัมพันธ์กับตัวประกัน เรียกได้สูงสุด $10,000");
    Dialog_ShowEasy(playerid, QuestionTen, DIALOG_STYLE_LIST, "คำถามที่ 10: ลักพาตัวประชาชน เรียกค่าไถ่ได้สูงสุดเท่าไหร่?", string, "ต่อไป", "");
    return 1;
}

Dialog:QuestionTen(playerid, response, listitem, inputtext[]){
    if(!response) return ShowTestingTen(playerid);
    if(response){
        new string[256];
        if(listitem == 0){
            TestingScore[playerid] += 1;
            format(string, sizeof(string), "{12EA00}- คุณได้ทำแบบทดสอบที่ 1 เสร็จสิ้นแล้ว\
            \n=============================================================\
            \n- หากคุณพร้อมที่จะทำบททดสอบต่อไปให้คุณกดปุ่ม 'ต่อไป' เพื่อดำเนินการต่อ");
            Dialog_ShowEasy(playerid, ServerTestingTwo, DIALOG_STYLE_MSGBOX, "ผ่านการทดสอบครั้งที่ 1", string, "ต่อไป", "");
            
        }
        if(listitem == 1){
            format(string, sizeof(string), "{12EA00}- คุณได้ทำแบบทดสอบที่ 1 เสร็จสิ้นแล้ว\
            \n=============================================================\
            \n- หากคุณพร้อมที่จะทำบททดสอบต่อไปให้คุณกดปุ่ม 'ต่อไป' เพื่อดำเนินการต่อ");
            Dialog_ShowEasy(playerid, ServerTestingTwo, DIALOG_STYLE_MSGBOX, "ผ่านการทดสอบครั้งที่ 1", string, "ต่อไป", "");
        }
        if(listitem == 2){
            format(string, sizeof(string), "{12EA00}- คุณได้ทำแบบทดสอบที่ 1 เสร็จสิ้นแล้ว\
            \n=============================================================\
            \n- หากคุณพร้อมที่จะทำบททดสอบต่อไปให้คุณกดปุ่ม 'ต่อไป' เพื่อดำเนินการต่อ");
            Dialog_ShowEasy(playerid, ServerTestingTwo, DIALOG_STYLE_MSGBOX, "ผ่านการทดสอบครั้งที่ 1", string, "ต่อไป", "");
        }
        if(listitem == 3){
            format(string, sizeof(string), "{12EA00}- คุณได้ทำแบบทดสอบที่ 1 เสร็จสิ้นแล้ว\
            \n=============================================================\
            \n- หากคุณพร้อมที่จะทำบททดสอบต่อไปให้คุณกดปุ่ม 'ต่อไป' เพื่อดำเนินการต่อ");
            Dialog_ShowEasy(playerid, ServerTestingTwo, DIALOG_STYLE_MSGBOX, "ผ่านการทดสอบครั้งที่ 1", string, "ต่อไป", "");
        }
    }
    return 1;
}

//ServerTestingTwo

SetPlayerQuestionTwo(playerid){
    SendClientMessage(playerid, COLOR_YELLOW, ">> ไปยังจุดสีแดงเพื่อทดสอบแบบทดสอบต่อไป <<");
    SetPlayerCheckpoint(playerid, 1491.0980,1307.6014,1093.2891, 1.0);
    TestingRules[playerid] = 2;
    return 1;
}

Dialog:ServerTestingTwo(playerid, response, listitem, inputtext[]){
    if(!response) return SetPlayerQuestionTwo(playerid);
    if(response){
        SetPlayerQuestionTwo(playerid);
    }
    return 1;
}

ShowServerTestingOne(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "1. ขับรถ เลนซ้าย\
    \n2. ขับรถ เลนขวา");
    Dialog_ShowEasy(playerid, ServerQuestionOne, DIALOG_STYLE_LIST, "คำถามที่ 1: เซิฟเวอร์ของเราขับรถเลนใด?", string, "ต่อไป", "");
    return 1;
}

Dialog:ServerQuestionOne(playerid, response, listitem, inputtext[]){
    if(!response) return ShowServerTestingOne(playerid);
    if(response){
        if(listitem == 0){
            ShowServerTestingTwo(playerid);
        }
        if(listitem == 1){
            TestingScoreTwo[playerid] += 1;
            ShowServerTestingTwo(playerid);
        }
    }
    return 1;
}

ShowServerTestingTwo(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "1. จอดเทียบฟุตบาท\
    \n2. จอดกลางถนน");
    Dialog_ShowEasy(playerid, ServerQuestionTwo, DIALOG_STYLE_LIST, "คำถามที่ 2: การจอดรถที่ถูกต้องควรจอดแบบใด?", string, "ต่อไป", "");
    return 1;
}

Dialog:ServerQuestionTwo(playerid, response, listitem, inputtext[]){
    if(!response) return ShowServerTestingTwo(playerid);
    if(response){
        if(listitem == 0){
            TestingScoreTwo[playerid] += 1;
            ShowServerTestingThree(playerid);
        }
        if(listitem == 1){
            ShowServerTestingThree(playerid);
        }
    }
    return 1;
}

ShowServerTestingThree(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "1. ไม่สามารถขโมยได้ หากต้องการขโมยควรจะมีบทบาทในการขโมยก่อน\
    \n2. สามารถขโมยได้ No สน No แคร์");
    Dialog_ShowEasy(playerid, ServerQuestionThree, DIALOG_STYLE_LIST, "คำถามที่ 3: เราสามารถขโมยรถผู้เล่นอื่นโดยไม่มีบทบาทได้หรือไม่?", string, "ต่อไป", "");
    return 1;
}

Dialog:ServerQuestionThree(playerid, response, listitem, inputtext[]){
    if(!response) return ShowServerTestingThree(playerid);
    if(response){
        if(listitem == 0){
            TestingScoreTwo[playerid] += 1;
            ShowServerTestingFour(playerid);
        }
        if(listitem == 1){
            ShowServerTestingFour(playerid);
        }
    }
    return 1;
}

ShowServerTestingFour(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "1. ไม่ยอมรับ\
    \n2. ยอมรับ");
    Dialog_ShowEasy(playerid, ServerQuestionFour, DIALOG_STYLE_LIST, "คำถามที่ 4: ไม่ดูถูกเหยียดหยามกันภายในเซิฟเวอร์?", string, "ต่อไป", "");
    return 1;
}

Dialog:ServerQuestionFour(playerid, response, listitem, inputtext[]){
    if(!response) return ShowServerTestingFour(playerid);
    if(response){
        if(listitem == 0){
            ShowServerTestingFive(playerid);
        }
        if(listitem == 1){
            TestingScoreTwo[playerid] += 1;
            ShowServerTestingFive(playerid);
        }
    }
    return 1;
}

ShowServerTestingFive(playerid){
    new string[512];
    SendClientMessage(playerid, COLOR_YELLOW, "- คำถามข้อต่อไป >>");
    format(string, sizeof(string), "1. ไม่ยอมรับ\
    \n2. ยอมรับ");
    Dialog_ShowEasy(playerid, ServerQuestionFive, DIALOG_STYLE_LIST, "คำถามที่ 5: ไม่ด่าบุพการีกันภายในเซิฟเวอร์?", string, "ต่อไป", "");
    return 1;
}

Dialog:ServerQuestionFive(playerid, response, listitem, inputtext[]){
    if(!response) return ShowServerTestingFive(playerid);
    if(response){
        new string[512];
        if(listitem == 0){
            format(string, sizeof(string), "{12EA00}- คุณได้ทำแบบทดสอบที่ 2 เสร็จสิ้นแล้ว\
            \n=============================================================\
            \n- หากคุณพร้อมที่จะทำบททดสอบต่อไปให้คุณกดปุ่ม 'ต่อไป' เพื่อดำเนินการต่อ");
            Dialog_ShowEasy(playerid, ConfirmQuestion, DIALOG_STYLE_MSGBOX, "ผ่านการทดสอบครั้งที่ 2", string, "ต่อไป", "");
        }
        if(listitem == 1){
            TestingScoreTwo[playerid] += 1;
            format(string, sizeof(string), "{12EA00}- คุณได้ทำแบบทดสอบที่ 2 เสร็จสิ้นแล้ว\
            \n=============================================================\
            \n- หากคุณพร้อมที่จะทำบททดสอบต่อไปให้คุณกดปุ่ม 'ต่อไป' เพื่อดำเนินการต่อ");
            Dialog_ShowEasy(playerid, ConfirmQuestion, DIALOG_STYLE_MSGBOX, "ผ่านการทดสอบครั้งที่ 2", string, "ต่อไป", "");
        }
    }
    return 1;
}

//ConfirmQuestion
ServerConfirmQuestion(playerid){
    SendClientMessage(playerid, COLOR_YELLOW, ">> ไปยังจุดสีแดงเพื่อตรวจเช็คคำตอบของคุณ <<");
    SetPlayerCheckpoint(playerid, 1497.1893,1306.4036,1093.2891, 1.0);
    TestingRules[playerid] = 3;
    return 1;
}

Dialog:ConfirmQuestion(playerid, response, listitem, inputtext[]){
    if(!response) return ServerConfirmQuestion(playerid);
    if(response){
        ServerConfirmQuestion(playerid);
    }
    return 1;
}

CheckConfirmQuestion(playerid){
    new string[512];

    new stringconfirm[128];
    if(TestingScore[playerid] >= 10){
        format(stringconfirm, sizeof(stringconfirm), "[%d/10]", TestingScore[playerid]);
    }
    else{
        format(stringconfirm, sizeof(stringconfirm), "[%d/10]", TestingScore[playerid]);
    }

    new stringconfirm2[128];
    if(TestingScoreTwo[playerid] >= 10){
        format(stringconfirm2, sizeof(stringconfirm2), "[%d/5]", TestingScoreTwo[playerid]);
    }
    else{
        format(stringconfirm2, sizeof(stringconfirm2), "[%d/5]", TestingScoreTwo[playerid]);
    }


    if(TestingScore[playerid] >= 10 && TestingScoreTwo[playerid] >= 5){
        format(string, sizeof(string), "{12EA00}[ ประกาศผลคะแนนแบบทดสอบ ]\
        \n - แบบทดสอบที่ 1 ทำคะแนนได้ %s\
        \n - แบบทดสอบที่ 2 ทำคะแนนได้ %s\
        \n===============================================\
        \n - ยินดีด้วย, คุณผ่านการทดสอบแล้วกดปุ่ม 'ตกลง' เพื่อไปยังลำดับต่อไป -", stringconfirm, stringconfirm2);
    }
    else{
        format(string, sizeof(string), "{EA0000}[ ประกาศผลคะแนนแบบทดสอบ ]\
        \n - แบบทดสอบที่ 1 ทำคะแนนได้ %s\
        \n - แบบทดสอบที่ 2 ทำคะแนนได้ %s\
        \n===============================================\
        \n - เสียใจด้วย, คุณไม่ผ่านการทดสอบของเซิฟเวอร์ ไว้มาลองใหม่อีกครั้งนะ -", stringconfirm, stringconfirm2);

        KickPlayer(playerid);
    }
    Dialog_ShowEasy(playerid, FinishQuestion, DIALOG_STYLE_MSGBOX, "สิ้นสุดการทดสอบ", string, "ตกลง", "");
    
    return 1;
}

Dialog:FinishQuestion(playerid, response, listitem, inputtext[]){
    if(!response || response) return Dialog_ShowEasy(playerid, SelectCity, DIALOG_STYLE_LIST, "เลือกเมืองเกิด", "- Los Santos (LS)\n- San Fierro (SF)\n- Las Venturas (LV)", "เลือก", "");
    return 1;
}

Dialog:MessageWelcome(playerid, response, listitem, inputtext[]){
    if(!response) return Kick(playerid);
    if(response){
        SendClientMessage(playerid, COLOR_YELLOW, ">> ไปยังจุดสีแดงเพื่อเริ่มทำแบบทดสอบ <<");
        SetCameraBehindPlayer(playerid);
        SetPlayerPosEx(playerid, 1494.4642, 1303.8282, 1093.2891, 3, playerid+1);
        SetPlayerFacingAngle(playerid, 357.9944);
        SetPlayerCheckpoint(playerid, 1490.3594,1305.6996,1093.2964, 1.0);
        TestingRules[playerid] = 1;
    }
    return 1;
}

SetPlayerSpawnNewbie(playerid){
    PlayerInventory_AddItem(playerid, "Box Level", 2969, 1);
    PlayerInventory_AddItem(playerid, "Burger", 2663, 5);
    PlayerInventory_AddItem(playerid, "Water Drink", 2647, 5);
    PlayerInventory_AddItem(playerid, "Energy Drink", 1544, 5);
    SendClientMessage(playerid, COLOR_WHITE, "- คุณได้รับ Bronze Member เวลาการใช้งาน 7 วัน");
	SendClientMessage(playerid, COLOR_WHITE, "- คุณได้รับเงินสดจำนวน $2,500 ติดตัวไว้");
	SendClientMessage(playerid, COLOR_WHITE, "- คุณได้รับ 'Box Level (กล่องเลเวล)' เพื่อใช้เปิดรับของรางวัลแต่ละเลเวล");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|--------------------------------------------------|");
    SendClientMessage(playerid, COLOR_YELLOW, "- ระบบได้นำคุณมายังจุดเกิดเด็กใหม่แล้ว, ขอให้สนุกกับเซิฟเวอร์ของเรา");
    
    SetPlayerColor(playerid, 0xFFFFFF00);
    SetPlayerHealth(playerid, 100);
    GivePlayerMoney(playerid, PlayerData[playerid][pCash]);
	SetPlayerScore(playerid, PlayerData[playerid][pSelectChar]);
    SetPlayerPosEx(playerid, PlayerData[playerid][pPosX], PlayerData[playerid][pPosY], PlayerData[playerid][pPosZ], PlayerData[playerid][pInterior], PlayerData[playerid][pWorld]);
    SetPlayerFacingAngle(playerid, PlayerData[playerid][pAngle]);
    SetCameraBehindPlayer(playerid);
    Character_Save(playerid);
    return true;
}

Dialog:SelectCity(playerid, response, listitem, inputtext[]){
    if(!response) return Dialog_ShowEasy(playerid, SelectCity, DIALOG_STYLE_LIST, "เลือกเมืองเกิด", "- Los Santos (LS)\n- San Fierro (SF)\n- Las Venturas (LV)", "เลือก", "");
    if(response){
        if(listitem == 0){
            for(new i=0; i<30; i++) SendClientMessage(playerid, -1, " ");
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เลือกจุดเกิดไปยังเมือง Los Santos (LS) เรียบร้อยแล้ว");
            PlayerData[playerid][pFirstTime] = 0;
            PlayerData[playerid][pPosX] = ServerData[ServerNewbiePosLS][0];
            PlayerData[playerid][pPosY] = ServerData[ServerNewbiePosLS][1];
            PlayerData[playerid][pPosZ] = ServerData[ServerNewbiePosLS][2];
            PlayerData[playerid][pAngle] = ServerData[ServerNewbiePosLS][3];
            PlayerData[playerid][pInterior] = 0;
            PlayerData[playerid][pWorld] = 0;
            SetPlayerSpawnNewbie(playerid);
        }
        if(listitem == 1){
            for(new i=0; i<30; i++) SendClientMessage(playerid, -1, " ");
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เลือกจุดเกิดไปยังเมือง San Fierro (SF) เรียบร้อยแล้ว");
            PlayerData[playerid][pFirstTime] = 0;
            PlayerData[playerid][pPosX] = ServerData[ServerNewbiePosSF][0];
            PlayerData[playerid][pPosY] = ServerData[ServerNewbiePosSF][1];
            PlayerData[playerid][pPosZ] = ServerData[ServerNewbiePosSF][2];
            PlayerData[playerid][pAngle] = ServerData[ServerNewbiePosSF][3];
            PlayerData[playerid][pInterior] = 0;
            PlayerData[playerid][pWorld] = 0;
            SetPlayerSpawnNewbie(playerid);
        }
        if(listitem == 2){
            for(new i=0; i<30; i++) SendClientMessage(playerid, -1, " ");
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เลือกจุดเกิดไปยังเมือง Las Venturas (LV) เรียบร้อยแล้ว");
            PlayerData[playerid][pFirstTime] = 0;
            PlayerData[playerid][pPosX] = ServerData[ServerNewbiePosLV][0];
            PlayerData[playerid][pPosY] = ServerData[ServerNewbiePosLV][1];
            PlayerData[playerid][pPosZ] = ServerData[ServerNewbiePosLV][2];
            PlayerData[playerid][pAngle] = ServerData[ServerNewbiePosLV][3];
            PlayerData[playerid][pInterior] = 0;
            PlayerData[playerid][pWorld] = 0;
            SetPlayerSpawnNewbie(playerid);
        }
    }
    return 1;
}