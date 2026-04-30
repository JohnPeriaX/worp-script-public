#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetPlayerDrivingTest(playerid){
    PlayerQuizDrivingScore[playerid] = 0;
    PlayerStepDrivingTest[playerid] = 0;
    return 1;
}

hook OnGameModeInit(){
    CreateDynamic3DTextLabel("[ทำแบบทดสอบใบขับขี่ $1,000]\nกด 'Y' เพื่อเริ่มทำ", 0x8AFF06FF, 2045.9137,-1908.1089,13.5469, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(!LoggedIn[playerid]) return 1;
    if(newkeys & KEY_YES){
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 2045.9137,-1908.1089,13.5469)){
            PlayerStartQuizDrivingTest(playerid);
        }
    }
    return 1;
}

hook OnPlayerEnterCheckpoint(playerid){
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
        new vehid = GetPlayerVehicleID(playerid);
        if(vehid != INVALID_VEHICLE_ID){
            if(GetVehicleModel(vehid) == 401){
                if(PlayerStepDrivingTest[playerid] == 1){
                    SetPlayerCheckpoint(playerid, 2083.7969,-1827.0465,13.1623, 8.0);
                    PlayerStepDrivingTest[playerid] = 2;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[1/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 2){
                    SetPlayerCheckpoint(playerid, 1975.2369,-1810.2504,13.1623, 8.0);
                    PlayerStepDrivingTest[playerid] = 3;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[2/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 3){
                    SetPlayerCheckpoint(playerid, 1964.3162,-1765.4357,13.1621, 8.0);
                    PlayerStepDrivingTest[playerid] = 4;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[3/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 4){
                    SetPlayerCheckpoint(playerid, 1944.7349,-1679.1068,13.1621, 8.0);
                    PlayerStepDrivingTest[playerid] = 5;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[4/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 5){
                    SetPlayerCheckpoint(playerid, 1835.4358,-1609.5809,13.1623, 8.0);
                    PlayerStepDrivingTest[playerid] = 6;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[5/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 6){
                    SetPlayerCheckpoint(playerid, 1545.5938,-1589.5424,13.1619, 8.0);
                    PlayerStepDrivingTest[playerid] = 7;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[6/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 7){
                    SetPlayerCheckpoint(playerid, 1527.3627,-1718.8357,13.1623, 8.0);
                    PlayerStepDrivingTest[playerid] = 8;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[7/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 8){
                    SetPlayerCheckpoint(playerid, 1566.6732,-1847.8877,13.1621, 8.0);
                    PlayerStepDrivingTest[playerid] = 9;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[8/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 9){
                    SetPlayerCheckpoint(playerid, 1648.3096,-1874.5798,13.1654, 8.0);
                    PlayerStepDrivingTest[playerid] = 10;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[9/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 10){
                    SetPlayerCheckpoint(playerid, 1691.8005,-1831.4537,13.1625, 8.0);
                    PlayerStepDrivingTest[playerid] = 11;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[10/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 11){
                    SetPlayerCheckpoint(playerid, 1805.6388,-1835.1091,13.1643, 8.0);
                    PlayerStepDrivingTest[playerid] = 12;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[11/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 12){
                    SetPlayerCheckpoint(playerid, 1818.7977,-1924.2445,13.1649, 8.0);
                    PlayerStepDrivingTest[playerid] = 13;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[12/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 13){
                    SetPlayerCheckpoint(playerid, 1943.7776,-1935.0211,13.1621, 8.0);
                    PlayerStepDrivingTest[playerid] = 14;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[13/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 14){
                    SetPlayerCheckpoint(playerid, 2063.4287,-1940.1475,13.1204, 8.0);
                    PlayerStepDrivingTest[playerid] = 15;
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[14/15]");
                }
                else if(PlayerStepDrivingTest[playerid] == 15){
                    SendClientMessage(playerid, COLOR_YELLOW, "โปรดขับอย่างระมัดระวัง, และขับช้าๆ");
                    SendClientMessage(playerid, COLOR_YELLOW, "[15/15]");
                    SetPlayerFinishDrvingTest(playerid);
                }
            }
        }
    }
    return 1;
}

SetPlayerFinishDrvingTest(playerid){
    DisablePlayerCheckpoint(playerid);
    new vehid = GetPlayerVehicleID(playerid);
    new carid = Car_GetID(vehid);
    if(carid != -1){
        TRP_DestroyVehicle(CarData[carid][carVehicle], true);
        CarData[carid][carVehicle] = INVALID_VEHICLE_ID;
        Car_Spawn(carid);
    }
    SendClientMessage(playerid, COLOR_GREEN, "- ยินดีด้วย, คุณได้ผ่านการทดสอบเรียบร้อยแล้ว");
    SendClientMessage(playerid, COLOR_YELLOW, "[พนักงาน]: ขอให้คุณขับรถอย่างปลอดภัยและระมัดระวัง");
    new id = PlayerInventory_AddItem(playerid, "Driving Card", 1581, 1);
    if(id == -1) return ErrorMsg(playerid, "กระเป๋าของคุณเต็มไม่สามารถเก็บใบขับขี่ได้");
    SendClientMessage(playerid, COLOR_YELLOW, "- ใบขับขี่ (Driving Card) + 1");
    PlayerStepDrivingTest[playerid] = 0;
    return 1;
}

SetPlayerStartCheckpointDrving(playerid){
    SetPlayerCheckpoint(playerid, 2084.2246,-1908.4266,13.1619, 8.0);
    PlayerStepDrivingTest[playerid] = 1;
    return 1;
}

PlayerStartQuizDrivingTest(playerid){
    if(PlayerData[playerid][pPassDrivingTest]) return ErrorMsg(playerid, "คุณได้ทำใบขับขี่ไปแล้ว");
    if(GetMoney(playerid) < 1000) return ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะทำแบบทดสอบ");
    Dialog_ShowEasy(playerid, ConfirmDrivingTest, DIALOG_STYLE_MSGBOX, "คุณต้องการที่จะทำแบบทดสอบหรือไม่?", "คุณจะต้องเสียเงิน $1,000 ในการทำแบบทดสอบครั้งนี้", "ตกลง", "ยกเลิก");
    return 1;
}

Dialog:ConfirmDrivingTest(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        GiveMoney(playerid, -1000, "Driving Test");
        Dialog_ShowEasy(playerid, DringTest1, DIALOG_STYLE_LIST, "การขับรถจะต้องขับอยู่ในเลนไหน?", "1. เลนซ้าย\n2. เลนขวา", "เลือก", "");
    }
    return 1;
}

Dialog:DringTest1(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            Dialog_ShowEasy(playerid, DringTest2, DIALOG_STYLE_LIST, "การจอดรถข้างที่ถูกต้องควรจอดแบบใด?", "1. จอดกลางถนน\n2. จอดเทียบฟุตบาท", "เลือก", "");
        }
        if(listitem == 1){
            PlayerQuizDrivingScore[playerid]++;
            Dialog_ShowEasy(playerid, DringTest2, DIALOG_STYLE_LIST, "การจอดรถข้างที่ถูกต้องควรจอดแบบใด?", "1. จอดกลางถนน\n2. จอดเทียบฟุตบาท", "เลือก", "");
        }
    }
    return 1;
}

Dialog:DringTest2(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            Dialog_ShowEasy(playerid, DringTest3, DIALOG_STYLE_LIST, "เมื่อคุณเกิดอุบัติเหตุบนถนนคุณต้องทำอย่างไร?", "1. ขับรถเข้าข้างทางและโทรแจ้งเจ้าหน้าที่\n2. ลงแล้วรถใส่แมร่งเลย!", "เลือก", "");
        }
        if(listitem == 1){
            PlayerQuizDrivingScore[playerid]++;
            Dialog_ShowEasy(playerid, DringTest3, DIALOG_STYLE_LIST, "เมื่อคุณเกิดอุบัติเหตุบนถนนคุณต้องทำอย่างไร?", "1. ขับรถเข้าข้างทางและโทรแจ้งเจ้าหน้าที่\n2. ลงแล้วรถใส่แมร่งเลย!", "เลือก", "");
        }
    }
    return 1;
}

Dialog:DringTest3(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            PlayerQuizDrivingScore[playerid]++;
            Dialog_ShowEasy(playerid, DringTest4, DIALOG_STYLE_LIST, "หากรถของคุณใกล้จะพังคุณควรทำอย่างไร?", "1. ขับไปที่อู่ หรือ จอดข้างทางและโทรแจ้งช่างยนต์\n2. ขับไปเลยดิ, ไม่สนใจ", "เลือก", "");
        }
        if(listitem == 1){
            Dialog_ShowEasy(playerid, DringTest4, DIALOG_STYLE_LIST, "หากรถของคุณใกล้จะพังคุณควรทำอย่างไร?", "1. ขับไปที่อู่ หรือ จอดข้างทางและโทรแจ้งช่างยนต์\n2. ขับไปเลยดิ, ไม่สนใจ", "เลือก", "");
        }
    }
    return 1;
}

Dialog:DringTest4(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            PlayerQuizDrivingScore[playerid]++;
            Dialog_ShowEasy(playerid, DringTest5, DIALOG_STYLE_LIST, "หากคุณเจอตำรวจตั้งด่านตรวจคุณควรทำอย่างไร?", "1. ค่อยๆ ชะลอรถ และขับตรงไป\n2. เหยียบให้มิดแล้วพุ่งแหกด่านไปเลย", "เลือก", "");
        }
        if(listitem == 1){
            Dialog_ShowEasy(playerid, DringTest5, DIALOG_STYLE_LIST, "หากคุณเจอตำรวจตั้งด่านตรวจคุณควรทำอย่างไร?", "1. ค่อยๆ ชะลอรถ และขับตรงไป\n2. เหยียบให้มิดแล้วพุ่งแหกด่านไปเลย, ไม่สนใจ", "เลือก", "");
        }
    }
    return 1;
}

Dialog:DringTest5(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            PlayerQuizDrivingScore[playerid]++;
            CheckResultQuiz(playerid);
        }
        if(listitem == 1){
            CheckResultQuiz(playerid);
        }
    }
    return 1;
}

CheckResultQuiz(playerid){
    if(PlayerQuizDrivingScore[playerid] >= 5){
        SendClientMessage(playerid, COLOR_GREEN, "- ยินดีด้วย, คุณได้ทำแบบทดสอบคำถามการสอบใบขับขี่ผ่านแล้ว");
        SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: ขั้นตอนต่อไปให้คุณไปขึ้นรถทำใบขับขี่ที่อยู่ใกล้ๆ เพื่อเริ่มทดสอบปฏิบัติ");
        PlayerData[playerid][pPassDrivingTest] = true;
    }
    else{
        SendClientMessage(playerid, COLOR_RED, "[!] เสียใจด้วย, คุณทำแบบทดสอบไม่ผ่านไว้มาทดสอบใหม่ภายหลัง");
    }
    return 1;
}