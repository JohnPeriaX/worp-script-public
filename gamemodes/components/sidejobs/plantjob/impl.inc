#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetPlayerPlant(playerid){
    Player_GetWater[playerid] = false;
    Player_WaterCount[playerid] = 0;
    Player_Watering[playerid] = false;
    stop PlayerWaterTime[playerid];
    Player_HarvestPlant[playerid] = false;
    PlayerStartCraftFruitjuice[playerid] = false;
    return 1;
}

hook OnGameModeInit(){
    LoadPlantZoneObject();
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(newkeys & KEY_YES){

        if(IsPlayerInRangeOfPoint(playerid, 3.0, -2266.8472,522.2110,35.0238)){
            if(!PlayerStartCraftFruitjuice[playerid]){
                PlayerStartCraftFruitjuice[playerid] = true;
                Dialog_ShowEasy(playerid, CraftFruitjuice, DIALOG_STYLE_LIST, "ทำน้ำผลไม้", "- ทำน้ำส้ม [ใช้ส้ม 4 ผล/ 1 กล่อง]\
                \n- ทำน้ำแอปเปิ้ลเขียว [ใช้แอปเปิ้ลเขียว 5 ผล/ 1 กล่อง]\
                \n- ทำไวน์แอปเปิ้ลแดง [ใช้แอปเปิ้ลแดง 4 ผล และ Beer 1 ขวด/ 1 ขวด]\
                \n- ทำไวน์แอปเปิ้ลเขียว [ใช้แอปเปิ้ลเขียว 4 ผล และ Beer 1 ขวด/ 1 ขวด]", "เลือก", "ยกเลิก");
            }
        }

        new id = -1, string[128];
        if((id = Sidejob_Nearest(playerid)) != -1){
            if(SideJobData[id][sidejobType] == 4){
                if(!Player_GetWater[playerid]){
                    SetPlayer_GetWaterPlant(playerid);
                }
                else{
                    Player_GetWater[playerid] = false;
                    Player_WaterCount[playerid] = 0;
                    RemoveAttachedObject(playerid, 9);
                }
            }
        }

        new plantid = -1;
        if((plantid = Plant_Nearest(playerid, 2)) != -1){
            SetPVarInt(playerid, "PlayerGetPlantID", plantid);
            format(string, sizeof string, "รดน้ำต้นพืชนี้\nเก็บเกี่ยวต้นพืชนี้");
            Dialog_ShowEasy(playerid, PlantDialog, DIALOG_STYLE_LIST, "ต้นพืช", string, "เลือก", "ปิด");
        }
    }
    return 1;
}

Dialog:CraftFruitjuice(playerid, response, listitem, inputtext[]){
    if(!response) return PlayerStartCraftFruitjuice[playerid] = false;
    if(response){
        if(listitem == 0){
            Dialog_ShowEasy(playerid, InputAmountOrange, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "ใส่จำนวน 'น้ำส้ม' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            Dialog_ShowEasy(playerid, InputAmountGrennApple, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "ใส่จำนวน 'น้ำแอปเปิ้ลเขียว' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }
        if(listitem == 2){
            Dialog_ShowEasy(playerid, InputAmountWineRedApple, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "ใส่จำนวน 'ไวน์แอปเปิ้ลแดง' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }
        if(listitem == 3){
            Dialog_ShowEasy(playerid, InputAmountWineGApple, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "ใส่จำนวน 'ไวน์แอปเปิ้ลเขียว' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:InputAmountWineGApple(playerid, response, listitem, inputtext[]){
    if(!response) return PlayerStartCraftFruitjuice[playerid] = false;
    if(response){
        new amount = strval(inputtext);
        
        if(amount < 1 || amount > 50){
            return Dialog_ShowEasy(playerid, InputAmountWineGApple, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "[!] คุณต้องใส่จำนวนมากกว่า 1 และไม่เกิน 50\nใส่จำนวน 'ไวน์แอปเปิ้ลเขียว' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }

        new checkamountapple = amount * 4;
        if(PlayerInventory_AllCount(playerid, "Green Apple") < checkamountapple){
            return Dialog_ShowEasy(playerid, InputAmountWineGApple, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "[!] คุณมีจำนวน 'แอปเปิ้ลเขียว' ไม่พอกับการทำน้ำไวน์แอปเปิ้ลเขียวตามจำนวนที่ใส่\nใส่จำนวน 'ไวน์แอปเปิ้ลเขียว' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }

        new checkamountbeer = amount * 1;
        if(PlayerInventory_AllCount(playerid, "Beer") < checkamountbeer){
            return Dialog_ShowEasy(playerid, InputAmountWineGApple, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "[!] คุณมีจำนวน 'เบียร์' ไม่พอกับการทำน้ำไวน์แอปเปิ้ลเขียวตามจำนวนที่ใส่\nใส่จำนวน 'ไวน์แอปเปิ้ลเขียว' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }

        new id = PlayerInventory_AddItem(playerid, "Green Apple Wine", 1669, amount);
        if(id == -1) {
            PlayerStartCraftFruitjuice[playerid] = false;
            return ErrorMsg(playerid, "เกิดข้อผิดพลาด กระเป๋าของคุณไม่มีที่ว่างพอ");
        }

        new string[128];
        ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
        PlayerInventory_Remove(playerid, "Green Apple", checkamountapple);
        PlayerInventory_Remove(playerid, "Beer", checkamountbeer);
        format(string, sizeof string, "คุณได้รับ 'ไวน์แอปเปิ้ลเขียว' + %d\
        \nคุณได้เสีย 'แอปเปิ้ลเขียว' - %d\
        \nคุณได้เสีย 'เบียร์' - %d", amount, checkamountapple, checkamountbeer);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ทำน้ำผลไม้", string, "ตกลง", "");
        PlayerStartCraftFruitjuice[playerid] = false;
    }
    return 1;
}

Dialog:InputAmountWineRedApple(playerid, response, listitem, inputtext[]){
    if(!response) return PlayerStartCraftFruitjuice[playerid] = false;
    if(response){
        new amount = strval(inputtext);
        
        if(amount < 1 || amount > 50){
            return Dialog_ShowEasy(playerid, InputAmountWineRedApple, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "[!] คุณต้องใส่จำนวนมากกว่า 1 และไม่เกิน 50\nใส่จำนวน 'ไวน์แอปเปิ้ลแดง' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }

        new checkamountapple = amount * 4;
        if(PlayerInventory_AllCount(playerid, "Apple") < checkamountapple){
            return Dialog_ShowEasy(playerid, InputAmountWineRedApple, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "[!] คุณมีจำนวน 'แอปเปิ้ลแดง' ไม่พอกับการทำน้ำไวน์แอปเปิ้ลแดงตามจำนวนที่ใส่\nใส่จำนวน 'ไวน์แอปเปิ้ลแดง' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }

        new checkamountbeer = amount * 1;
        if(PlayerInventory_AllCount(playerid, "Beer") < checkamountbeer){
            return Dialog_ShowEasy(playerid, InputAmountWineRedApple, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "[!] คุณมีจำนวน 'เบียร์' ไม่พอกับการทำน้ำไวน์แอปเปิ้ลแดงตามจำนวนที่ใส่\nใส่จำนวน 'ไวน์แอปเปิ้ลแดง' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }

        new id = PlayerInventory_AddItem(playerid, "Red Apple Wine", 1669, amount);
        if(id == -1) {
            PlayerStartCraftFruitjuice[playerid] = false;
            return ErrorMsg(playerid, "เกิดข้อผิดพลาด กระเป๋าของคุณไม่มีที่ว่างพอ");
        }

        new string[128];
        ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
        PlayerInventory_Remove(playerid, "Apple", checkamountapple);
        PlayerInventory_Remove(playerid, "Beer", checkamountbeer);
        format(string, sizeof string, "คุณได้รับ 'ไวน์แอปเปิ้ลแดง' + %d\
        \nคุณได้เสีย 'แอปเปิ้ลแดง' - %d\
        \nคุณได้เสีย 'เบียร์' - %d", amount, checkamountapple, checkamountbeer);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ทำน้ำผลไม้", string, "ตกลง", "");
        PlayerStartCraftFruitjuice[playerid] = false;
    }
    return 1;
}

Dialog:InputAmountGrennApple(playerid, response, listitem, inputtext[]){
    if(!response) return PlayerStartCraftFruitjuice[playerid] = false;
    if(response){
        new amount = strval(inputtext);
        
        if(amount < 1 || amount > 50){
            return Dialog_ShowEasy(playerid, InputAmountGrennApple, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "[!] คุณต้องใส่จำนวนมากกว่า 1 และไม่เกิน 50\nใส่จำนวน 'น้ำแอปเปิ้ลเขียว' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }

        new checkamount = amount * 5;
        if(PlayerInventory_AllCount(playerid, "Green Apple") < checkamount){
            return Dialog_ShowEasy(playerid, InputAmountGrennApple, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "[!] คุณมีจำนวน 'แอปเปิ้ลเขียว' ไม่พอกับการทำน้ำแอปเปิ้ลเขียวตามจำนวนที่ใส่\nใส่จำนวน 'น้ำแอปเปิ้ลเขียว' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }

        new id = PlayerInventory_AddItem(playerid, "Green Apple Juice", 19564, amount);
        if(id == -1) {
            PlayerStartCraftFruitjuice[playerid] = false;
            return ErrorMsg(playerid, "เกิดข้อผิดพลาด กระเป๋าของคุณไม่มีที่ว่างพอ");
        }

        new string[128];
        ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
        PlayerInventory_Remove(playerid, "Green Apple", checkamount);
        format(string, sizeof string, "คุณได้รับ 'น้ำแอปเปิ้ลเขียว' + %d\
        \nคุณได้เสีย 'แอปเปิ้ลเขียว' - %d", amount, checkamount);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ทำน้ำผลไม้", string, "ตกลง", "");
        PlayerStartCraftFruitjuice[playerid] = false;
    }
    return 1;
}

Dialog:InputAmountOrange(playerid, response, listitem, inputtext[]){
    if(!response) return PlayerStartCraftFruitjuice[playerid] = false;
    if(response){
        new amount = strval(inputtext);
        
        if(amount < 1 || amount > 50){
            return Dialog_ShowEasy(playerid, InputAmountOrange, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "[!] คุณต้องใส่จำนวนมากกว่า 1 และไม่เกิน 50\nใส่จำนวน 'น้ำส้ม' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }

        new checkamount = amount * 4;
        if(PlayerInventory_AllCount(playerid, "Orange") < checkamount){
            return Dialog_ShowEasy(playerid, InputAmountOrange, DIALOG_STYLE_INPUT, "ทำน้ำผลไม้", "[!] คุณมีจำนวน 'ส้ม' ไม่พอกับการทำน้ำส้มตามจำนวนที่ใส่\nใส่จำนวน 'น้ำส้ม' ที่ต้องการจะทำ: ", "ตกลง", "ยกเลิก");
        }

        new id = PlayerInventory_AddItem(playerid, "Orange juice", 19563, amount);
        if(id == -1) {
            PlayerStartCraftFruitjuice[playerid] = false;
            return ErrorMsg(playerid, "เกิดข้อผิดพลาด กระเป๋าของคุณไม่มีที่ว่างพอ");
        }

        new string[128];
        ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
        PlayerInventory_Remove(playerid, "Orange", checkamount);
        format(string, sizeof string, "คุณได้รับ 'น้ำส้ม' + %d\
        \nคุณได้เสีย 'ส้ม' - %d", amount, checkamount);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ทำน้ำผลไม้", string, "ตกลง", "");
        PlayerStartCraftFruitjuice[playerid] = false;
    }
    return 1;
}

Dialog:PlantDialog(playerid, response, listitem, inputtext[]){
    if(!response){
        DeletePVar(playerid, "PlayerGetPlantID");
        return 1;
    }
    if(response){
        new plantid = GetPVarInt(playerid, "PlayerGetPlantID");
        if(listitem == 0){
            if(Player_GetWater[playerid] && Player_WaterCount[playerid] >= 1){
                if(plantid != -1 && Iter_Contains(Iter_Plant, plantid)){
                    if(PlantData[plantid][plantWater] >= 100){
                        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ต้นพืชนี้โตเต็มที่แล้วไม่สามารถรดน้ำได้", "ตกลง", "");
                        DeletePVar(playerid, "PlayerGetPlantID");
                        return 1;
                    }
                    if(!Player_Watering[playerid]) SetPlayerWaterPlant(playerid);
                }
            }
        }
        if(listitem == 1){
            if(plantid != -1 && Iter_Contains(Iter_Plant, plantid)){
                if(PlantData[plantid][plantOwner] == PlayerData[playerid][pID]){
                    if(!Player_HarvestPlant[playerid]) SetPlayerHarvestPlant(playerid);
                }
            }
        }
    }
    return 1;
}

SetPlayerHarvestPlant(playerid){
    new plantid = GetPVarInt(playerid, "PlayerGetPlantID");
    if(plantid != -1 && Iter_Contains(Iter_Plant, plantid)){

        if(PlantData[plantid][plantWater] < 100) {
            DeletePVar(playerid, "PlayerGetPlantID");
            return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] พืชต้นนี้ยังโตไม่เต็มที่", "ตกลง", "");
        }
        PlayerData[playerid][pStress]++;
        if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
        Player_HarvestPlant[playerid] = true;
        ClearAnimations(playerid);
        ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);

        if(PlantData[plantid][plantType] == BANANATYPE){
            new itemid = PlayerInventory_AddItem(playerid, "Banana", 19578, 10);
            if(itemid == -1) {
                Player_HarvestPlant[playerid] = false;
                return ErrorMsg(playerid, "กระเป๋าของคุณเต็มไม่สามารถเก็บเพิ่มได้อีก");
            }
            SendClientMessage(playerid, COLOR_YELLOW, "[ได้รับ]: คุณได้รับ (Banana)' + 10");
        }

        else if(PlantData[plantid][plantType] == PUMPKINTYPE){
            new itemid = PlayerInventory_AddItem(playerid, "Pumpkin", 19320, 10);
            if(itemid == -1) {
                Player_HarvestPlant[playerid] = false;
                return ErrorMsg(playerid, "กระเป๋าของคุณเต็มไม่สามารถเก็บเพิ่มได้อีก");
            }
            SendClientMessage(playerid, COLOR_ORANGE, "[ได้รับ]: คุณได้รับ (Pumpkin)' + 10");
        }

        else if(PlantData[plantid][plantType] == APPLETYPE){
            new itemid = PlayerInventory_AddItem(playerid, "Apple", 19575, 10);
            if(itemid == -1) {
                Player_HarvestPlant[playerid] = false;
                return ErrorMsg(playerid, "กระเป๋าของคุณเต็มไม่สามารถเก็บเพิ่มได้อีก");
            }
            SendClientMessage(playerid, COLOR_ORANGE, "[ได้รับ]: คุณได้รับ (Apple)' + 10");
        }

        else if(PlantData[plantid][plantType] == GREENAPPLETYPE){
            new itemid = PlayerInventory_AddItem(playerid, "Green apple", 19576, 10);
            if(itemid == -1) {
                Player_HarvestPlant[playerid] = false;
                return ErrorMsg(playerid, "กระเป๋าของคุณเต็มไม่สามารถเก็บเพิ่มได้อีก");
            }
            SendClientMessage(playerid, COLOR_ORANGE, "[ได้รับ]: คุณได้รับ (Green apple)' + 10");
        }

        Player_HarvestPlant[playerid] = false;

        PlantData[plantid][plantStill] = false;
        PlantData[plantid][plantWater] = 0;
        PlantData[plantid][plantOwner] = 0;
        format(PlantData[plantid][plantOwnerName], 64, "NULL");

        Update_PlantObject(plantid);
        DeletePVar(playerid, "PlayerGetPlantID");
    }
    return 1;
}

task CheckUpdatePlant[600000](){
    foreach(new i : Iter_Plant){
        if(PlantData[i][plantActive]){
            PlantData[i][plantActive] = false;
        }
        else if(!PlantData[i][plantActive]){
            PlantData[i][plantActive] = false;
            PlantData[i][plantWater] = 0;
            PlantData[i][plantStill] = 0;
            PlantData[i][plantOwner] = 0;
            format(PlantData[i][plantOwnerName], 64, "NULL");
            Update_PlantObject(i);
            Plant_Save(i);
        }
    }
}

timer OnPlayerWaterPlant[500](playerid){
    if(Player_Watering[playerid]){
        new Float:WaterPoint = GetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0]);
        if(WaterPoint < 100.0){
            if(PlayerData[playerid][pPlantJobLevel] >= 0 && PlayerData[playerid][pPlantJobLevel] < 5) WaterPoint += 3;
            else if(PlayerData[playerid][pPlantJobLevel] >= 5 && PlayerData[playerid][pPlantJobLevel] < 10) WaterPoint += 5;
            else if(PlayerData[playerid][pPlantJobLevel] >= 10 && PlayerData[playerid][pPlantJobLevel] < 15) WaterPoint += 8;
            else if(PlayerData[playerid][pPlantJobLevel] >= 15 && PlayerData[playerid][pPlantJobLevel] <= 20) WaterPoint += 10;
            SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], WaterPoint);
        }
        else{
            PlayerData[playerid][pPlantJobExp]++;
            new nxtlevel = PlayerData[playerid][pPlantJobLevel]+1;
            new expamount = nxtlevel*levelexpplant;
            if(PlayerData[playerid][pPlantJobExp] >= expamount){
                if(PlayerData[playerid][pPlantJobLevel] < 20){
                    PlayerData[playerid][pPlantJobExp] -= expamount;
                    PlayerData[playerid][pPlantJobLevel]++;
                    SendClientMessageEx(playerid, COLOR_GREY, "- ยินดีด้วยเลเวลปลูกพืชของคุณเลื่อนเป็น %d เรียบร้อยแล้ว", PlayerData[playerid][pPlantJobLevel]);
                }
                else if(PlayerData[playerid][pPlantJobLevel] >= 20) SendClientMessageEx(playerid, COLOR_GREY, "- คุณมีเลเวลปลูกพืชเป็น %d ซึ่งตันแล้ว", PlayerData[playerid][pPlantJobLevel]);
            }

            SendClientMessage(playerid, COLOR_YELLOW, "> คุณได้รดน้ำต้นพืชนี้เรียบร้อยแล้ว");

            new plantid = GetPVarInt(playerid, "PlayerGetPlantID");
            PlantData[plantid][plantWater] += 10;
            PlantData[plantid][plantActive] = true;
            Update_PlantObject(plantid);
            Plant_Save(plantid);
            DeletePVar(playerid, "PlayerGetPlantID");

            TogglePlayerControllable(playerid, 1);
            ClearAnimations(playerid);

            Player_WaterCount[playerid]--;
            SetPlayerAttachedObject(playerid,9,19621,6,0.000000,0.000000,0.000000,110.899971,96.700103,104.199974,1.000000,1.000000,1.000000);
            if(Player_WaterCount[playerid] <= 0){
                RemoveAttachedObject(playerid, 9);
                Player_GetWater[playerid] = false;
            }
            RemoveAttachedObject(playerid, 8);

            SendClientMessageEx(playerid, COLOR_YELLOW, "[บัวรดน้ำ]: คุณจะสามารถรดน้ำได้อีก [%d/3]", Player_WaterCount[playerid]);

            HidePlayerProgressBar(playerid, NewProgressBar[playerid][0]);
            PlayerTextDrawHide(playerid, NewProgressText[playerid][0]);
            DestroyPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
            PlayerTextDrawDestroy(playerid, NewProgressText[playerid][0]);

            Player_Watering[playerid] = false;
            stop PlayerWaterTime[playerid];
        }
    }
}

SetPlayerWaterPlant(playerid){
    Player_Watering[playerid] = true;
    SetPlayerAttachedObject(playerid,8,18676,6,0.088999,0.247999,-1.433998,0.000000,0.000000,94.099998,1.000000,1.000000,1.000000);
    SetPlayerAttachedObject(playerid,9,19621,6,0.000000,0.000000,0.000000,110.899971,96.700103,104.199974,1.000000,1.000000,1.000000);
    LoadPlayerNewProgress(playerid);
    ShowPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    SetPlayerProgressBarColour(playerid, NewProgressBar[playerid][0], 0xFFD74EAA);
    TogglePlayerControllable(playerid, 0);
    ClearAnimations(playerid);
    ApplyAnimation(playerid, "SHOP", "ROB_Loop_Threat", 4.1, 1, 0, 0, 0, 0, 1);
    SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], 0.0);
    PlayerWaterTime[playerid] = repeat OnPlayerWaterPlant(playerid);
    return 1;
}

SetPlayer_GetWaterPlant(playerid){
    Player_GetWater[playerid] = true;
    Player_WaterCount[playerid] = 3;
    SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้บัวรดน้ำแล้ว, คุณสามารถรดน้ำได้จำนวน 3 ครั้ง");
    ApplyAnimationEx(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
    SetPlayerAttachedObject(playerid, 9, 19621, 6, 0.047000,0.012000,0.046999,-158.800079,-144.299972,-99.000000,1.000000,1.000000,1.000000);
    return 1;
}

RandomPlantPrice(){
    new RandomPlant1[4] = {10,15,18,20};
    new randombanana = random(sizeof(RandomPlant1));
    RandomPriceBanana = RandomPlant1[randombanana];

    new RandomPlant2[4] = {17,18,19,25};
    new randompumpkin = random(sizeof(RandomPlant2));
    RandomPricePumpkin = RandomPlant2[randompumpkin];

    new RandomPlant3[4] = {20,22,25,28};
    new randomapple = random(sizeof(RandomPlant3));
    RandomPriceApple = RandomPlant3[randomapple];

    new RandomPlant4[4] = {20,22,25,28};
    new randomgreenapple = random(sizeof(RandomPlant4));
    RandomPriceGreenApple = RandomPlant4[randomgreenapple];

    new RandomCowMilk[4] = {200,210,220,250};
    new randomcowmilk = random(sizeof(RandomCowMilk));
    RandomPriceCowMilk = RandomCowMilk[randomcowmilk];
	SendClientMessageToAll(0x97FF00AA, "[ตลาด]: ราคาตลาดพืชมีการเปลี่ยนแปลง");
    return 1;
}

CMD:reloadplant(playerid, params[]){
    if(PlayerData[playerid][pAdmin] <= 0) return 1;
    mysql_tquery(dbCon, "SELECT * FROM `plants`", "Plant_Load", "");
    return 1;
}

CMD:makeplant(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new type;
    if(sscanf(params, "d", type)) return SystemMsg(playerid, "/makeplant [type]");
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x ,y ,z);

    for(new i=0; i<MAX_PLANTS; i++){
        if(!Iter_Contains(Iter_Plant, i)){
            PlantData[i][plantType] = type;
            PlantData[i][plantPos][0] = x;
            PlantData[i][plantPos][1] = y;
            PlantData[i][plantPos][2] = z;
            PlantData[i][plantOwner] = 0;
            format(PlantData[i][plantOwnerName], 64, "NULL");
            PlantData[i][plantWater] = 0;
            PlantData[i][plantStill] = 0;
            PlantData[i][plantActive] = true;
            Iter_Add(Iter_Plant, i);
            FirstLoad_PlantObject(i);

            new query[500];

            mysql_format(dbCon, query, sizeof query, "INSERT INTO `plants` (`plantType`, `plantOwner`, `plantOwnerName`, `plantWater`, `plantStill`, `plantPosX`, `plantPosY`, `plantPosZ`) VALUES(%d, %d, '%e', %d, %d, %f, %f, %f)",
            type, PlantData[i][plantOwner], PlantData[i][plantOwnerName], PlantData[i][plantWater], PlantData[i][plantStill], x, y, z);
		    mysql_tquery(dbCon, query, "OnPlantCreated", "i", i);
            break;
        }
    }
    return 1;
}

forward OnPlantCreated(bizid);
public OnPlantCreated(bizid){
	cache_insert_id();
	return 1;
}

CMD:setplantnull(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new id = -1;
    if((id = Plant_Nearest(playerid, 2)) != -1){
        PlantData[id][plantWater] = 0;
        PlantData[id][plantStill] = 0;
        PlantData[id][plantOwner] = 0;
        format(PlantData[id][plantOwnerName], 64, "NULL");
        Update_PlantObject(id);
        Plant_Save(id);
    }
    return 1;
}

CMD:setplantfull(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    new id = -1;
    if((id = Plant_Nearest(playerid, 2)) != -1){
        PlantData[id][plantWater] = 100;
        Update_PlantObject(id);
        Plant_Save(id);
    }
    return 1;
}

forward Plant_Load();
public Plant_Load(){
    new rows;
    cache_get_row_count(rows);
    for (new i = 0; i < rows; i ++) if (i < MAX_PLANTS){
        if(!Iter_Contains(Iter_Plant, i)){
            cache_get_value_name_int(i, "plantID", PlantData[i][plantID]);
            cache_get_value_name_int(i, "plantType", PlantData[i][plantType]);
            cache_get_value_name_int(i, "plantOwner", PlantData[i][plantOwner]);
            cache_get_value_name(i, "plantOwnerName", PlantData[i][plantOwnerName], 64);
            cache_get_value_name_int(i, "plantWater", PlantData[i][plantWater]);
            cache_get_value_name_int(i, "plantStill", PlantData[i][plantStill]);
            cache_get_value_name_float(i, "plantPosX", PlantData[i][plantPos][0]);
            cache_get_value_name_float(i, "plantPosY", PlantData[i][plantPos][1]);
            cache_get_value_name_float(i, "plantPosZ", PlantData[i][plantPos][2]);

            PlantData[i][plantActive] = true;

            Iter_Add(Iter_Plant, i);
            FirstLoad_PlantObject(i);
        }
    }
    printf("(( [MYSQL]: Load %d Plants Successfully ))", Iter_Count(Iter_Plant));
    return 1;
}

Plant_Save(plantid){
    if(plantid != -1 && Iter_Contains(Iter_Plant, plantid)){
        new
            query[256];

        mysql_format(dbCon, query, sizeof(query), "UPDATE `plants` SET `plantOwner` = '%d', `plantOwnerName` = '%e', `plantWater` = '%d', `plantStill` = '%d' WHERE `plantID` = '%d'",
            PlantData[plantid][plantOwner],
            PlantData[plantid][plantOwnerName],
            PlantData[plantid][plantWater],
            PlantData[plantid][plantStill],
            PlantData[plantid][plantID]
        );
        return mysql_tquery(dbCon, query);
    }
    return 1;
}

FirstLoad_PlantObject(plantid){
    if(plantid != -1 && Iter_Contains(Iter_Plant, plantid)){
        new string[256];
        if(PlantData[plantid][plantStill]){
            if(PlantData[plantid][plantWater] < 100){
                if(PlantData[plantid][plantType] == BANANATYPE){
                    PlantData[plantid][plantObject] = CreateDynamicObject(BANANA_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-5.0, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                    format(string, sizeof string, "[ต้นกล้วย]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_YELLOW, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
                }
                else if(PlantData[plantid][plantType] == PUMPKINTYPE){
                    PlantData[plantid][plantObject] = CreateDynamicObject(PUMPKIN_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-0.5, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                    format(string, sizeof string, "[ต้นฟักทอง]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_ORANGE, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
                }
                else if(PlantData[plantid][plantType] == APPLETYPE){
                    PlantData[plantid][plantObject] = CreateDynamicObject(APPLE_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-5.0, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                    format(string, sizeof string, "[ต้นแอปเปิ้ล]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_RED, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
                }
                else if(PlantData[plantid][plantType] == GREENAPPLETYPE){
                    PlantData[plantid][plantObject] = CreateDynamicObject(GREENAPPLE_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-5.0, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                    format(string, sizeof string, "[ต้นแอปเปิ้ลเขียว]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_GREEN, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
                }
            }
            else{
                if(PlantData[plantid][plantType] == BANANATYPE){
                    PlantData[plantid][plantObject] = CreateDynamicObject(BANANA_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2], 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                    format(string, sizeof string, "[ต้นกล้วย]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_YELLOW, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
                }
                else if(PlantData[plantid][plantType] == PUMPKINTYPE){
                    PlantData[plantid][plantObject] = CreateDynamicObject(PUMPKIN_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2], 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                    format(string, sizeof string, "[ต้นฟักทอง]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_ORANGE, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
                }
                else if(PlantData[plantid][plantType] == APPLETYPE){
                    PlantData[plantid][plantObject] = CreateDynamicObject(APPLE_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2], 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                    format(string, sizeof string, "[ต้นแอปเปิ้ล]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_RED, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0); 
                }
                else if(PlantData[plantid][plantType] == GREENAPPLETYPE){
                    PlantData[plantid][plantObject] = CreateDynamicObject(GREENAPPLE_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2], 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                    format(string, sizeof string, "[ต้นแอปเปิ้ลเขียว]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_GREEN, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
                }
            }
        }
        else{
            if(PlantData[plantid][plantType] == BANANATYPE){
                PlantData[plantid][plantObject] = CreateDynamicObject(BANANA_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-7.0, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                format(string, sizeof string, "[ที่ปลูกกล้วย]\nพื้นที่ว่างพร้อมปลูก");
                PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_YELLOW, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+0.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
            }
            else if(PlantData[plantid][plantType] == PUMPKINTYPE){
                PlantData[plantid][plantObject] = CreateDynamicObject(PUMPKIN_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-7.0, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                format(string, sizeof string, "[ที่ปลูกฟักทอง]\nพื้นที่ว่างพร้อมปลูก");
                PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_ORANGE, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+0.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
            }
            else if(PlantData[plantid][plantType] == APPLETYPE){
                PlantData[plantid][plantObject] = CreateDynamicObject(APPLE_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-9.0, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                format(string, sizeof string, "[ที่ปลูกแอปเปิ้ล]\nพื้นที่ว่างพร้อมปลูก");
                PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_RED, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+0.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
            }
            else if(PlantData[plantid][plantType] == GREENAPPLETYPE){
                PlantData[plantid][plantObject] = CreateDynamicObject(GREENAPPLE_OBJECT, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-9.0, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
                format(string, sizeof string, "[ที่ปลูกแอปเปิ้ลเขียว]\nพื้นที่ว่างพร้อมปลูก");
                PlantData[plantid][plant3DText] = CreateDynamic3DTextLabel(string, COLOR_GREEN, PlantData[plantid][plantPos][0]-0.5, PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]+0.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
            }
        }
    }
}

Update_PlantObject(plantid){
    if(plantid != -1 && Iter_Contains(Iter_Plant, plantid)){
        new string[256];
        if(PlantData[plantid][plantStill]){
            if(PlantData[plantid][plantWater] < 100){
                if(PlantData[plantid][plantType] == BANANATYPE){
                    MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-5.0, 2.5, 0.000000, 0.000000, 0.000000);
                    format(string, sizeof string, "[ต้นกล้วย]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_YELLOW, string);
                }
                else if(PlantData[plantid][plantType] == PUMPKINTYPE){
                    MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-0.5, 2.5, 0.000000, 0.000000, 0.000000);
                    format(string, sizeof string, "[ต้นฟักทอง]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_ORANGE, string);
                }
                else if(PlantData[plantid][plantType] == APPLETYPE){
                    MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-5.0, 2.5, 0.000000, 0.000000, 0.000000);
                    format(string, sizeof string, "[ต้นแอปเปิ้ล]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_RED, string);
                }
                else if(PlantData[plantid][plantType] == GREENAPPLETYPE){
                    MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-5.0, 2.5, 0.000000, 0.000000, 0.000000);
                    format(string, sizeof string, "[ต้นแอปเปิ้ลเขียว]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_GREEN, string);
                }
            }   
            else{
                if(PlantData[plantid][plantType] == BANANATYPE){
                    MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2], 2.5, 0.000000, 0.000000, 0.000000);
                    format(string, sizeof string, "[ต้นกล้วย]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_YELLOW, string);
                }
                else if(PlantData[plantid][plantType] == PUMPKINTYPE){
                    MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2], 2.5, 0.000000, 0.000000, 0.000000);
                    format(string, sizeof string, "[ต้นฟักทอง]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_ORANGE, string);
                }
                else if(PlantData[plantid][plantType] == APPLETYPE){
                    MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2], 2.5, 0.000000, 0.000000, 0.000000);
                    format(string, sizeof string, "[ต้นแอปเปิ้ล]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_RED, string);
                }
                else if(PlantData[plantid][plantType] == GREENAPPLETYPE){
                    MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2], 2.5, 0.000000, 0.000000, 0.000000);
                    format(string, sizeof string, "[ต้นแอปเปิ้ลเขียว]\nเจ้าของ: [%s]\nระดับความเจริญเติบโต: [%d]", PlantData[plantid][plantOwnerName], PlantData[plantid][plantWater]);
                    UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_GREEN, string);
                }
            }
        }
        else{
            if(PlantData[plantid][plantType] == BANANATYPE){
                MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-7.0, 2.5, 0.000000, 0.000000, 0.000000);
                format(string, sizeof string, "[ที่ปลูกกล้วย]\nพื้นที่ว่างพร้อมปลูก");
                UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_YELLOW, string);
            }
            else if(PlantData[plantid][plantType] == PUMPKINTYPE){
                MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-7.0, 2.5, 0.000000, 0.000000, 0.000000);
                format(string, sizeof string, "[ที่ปลูกฟักทอง]\nพื้นที่ว่างพร้อมปลูก");
                UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_ORANGE, string);
            }
            else if(PlantData[plantid][plantType] == APPLETYPE){
                MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-7.0, 2.5, 0.000000, 0.000000, 0.000000);
                format(string, sizeof string, "[ที่ปลูกแอปเปิ้ล]\nพื้นที่ว่างพร้อมปลูก");
                UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_RED, string);
            }
            else if(PlantData[plantid][plantType] == GREENAPPLETYPE){
                MoveDynamicObject(PlantData[plantid][plantObject], PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2]-7.0, 2.5, 0.000000, 0.000000, 0.000000);
                format(string, sizeof string, "[ที่ปลูกแอปเปิ้ลเขียว]\nพื้นที่ว่างพร้อมปลูก");
                UpdateDynamic3DTextLabelText(PlantData[plantid][plant3DText], COLOR_GREEN, string);
            }
        }
    }
    return 1;
}

Plant_Nearest(playerid, flag = 1){
    foreach(new i : Iter_Plant){
        if(flag == 1){
            if(PlantData[i][plantStill]) continue;
            if(IsPlayerInRangeOfPoint(playerid, 2.5, PlantData[i][plantPos][0], PlantData[i][plantPos][1], PlantData[i][plantPos][2])){
                return i;
            }
        }
        else if(flag == 2){
            if(!PlantData[i][plantStill]) continue;
            if(IsPlayerInRangeOfPoint(playerid, 2.5, PlantData[i][plantPos][0], PlantData[i][plantPos][1], PlantData[i][plantPos][2])){
                return i;
            }
        }
    }
	return -1;
}

timer SetPlayerBombPlant[1000](playerid){
    ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
}


PlayerIsPlanting(playerid, type){
    new plantid = Plant_Nearest(playerid, 1);
    if(plantid == -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "[!] ไม่สามารถปลูกได้\nเนื่องจาก คุณอาจจะไม่ได้อยู่ในพื้นที่ปลูกหรือมีคนปลูกตรงนี้แล้ว", "ตกลง", "");
    if(PlantData[plantid][plantType] == type){

        if(type == BANANATYPE) {
            SendClientMessage(playerid, COLOR_YELLOW, "[!] Banana Seed -1");
            PlayerInventory_Remove(playerid, "Banana Seed", 1);
        }
        else if(type == PUMPKINTYPE) {
            SendClientMessage(playerid, COLOR_ORANGE, "[!] Pumpkin Seed -1");
            PlayerInventory_Remove(playerid, "Pumpkin Seed", 1);
        }
        else if(type == APPLETYPE){
            SendClientMessage(playerid, COLOR_YELLOW, "[!] Apple Seed -1");
            PlayerInventory_Remove(playerid, "Apple Seed", 1);
        }
        else if(type == GREENAPPLETYPE){
            SendClientMessage(playerid, COLOR_YELLOW, "[!] Green Apple Seed -1");
            PlayerInventory_Remove(playerid, "Green Apple Seed", 1);
        }

        ClearAnimations(playerid);
        defer SetPlayerBombPlant(playerid);
        format(PlantData[plantid][plantOwnerName], 64, ReturnRoleplayName(playerid));
        PlantData[plantid][plantOwner] = PlayerData[playerid][pID];
        PlantData[plantid][plantWater] = 0;
        PlantData[plantid][plantStill] = true;
        Update_PlantObject(plantid);
        Plant_Save(plantid);
    }
    return 1;
}

LoadPlantZoneObject(){

    tmpobjid = CreateDynamicObject(19482, -1107.482543, -989.097839, 132.228607, 0.000000, 0.000000, -89.999931, -1, -1, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    SetDynamicObjectMaterialText(tmpobjid, 0, "{000000}สวนฟักทอง", 90, "Calibri", 35, 1, 0x00000000, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19482, -1077.935424, -989.104431, 132.228607, 0.000000, 0.000000, -90.299926, -1, -1, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    SetDynamicObjectMaterialText(tmpobjid, 0, "{000000}สวนกล้วย", 90, "Calibri", 35, 1, 0x00000000, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19482, -1077.892089, -1003.885192, 132.178619, 0.000000, 0.000000, 89.700073, -1, -1, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    SetDynamicObjectMaterialText(tmpobjid, 0, "{000000}เลี้ยงวัว", 90, "Calibri", 35, 1, 0x00000000, 0x00000000, 1);

    tmpobjid = CreateDynamicObject(12921, -1195.310913, -996.257202, 131.567886, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(17324, -1029.781738, -996.210510, 128.218750, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(9339, -1194.647705, -1016.861633, 128.878784, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(9339, -1194.647705, -1042.910766, 128.878784, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1453, -1194.770874, -989.014221, 128.736099, 0.000000, -15.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(9339, -1194.647705, -975.340759, 128.878784, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(9339, -1194.647705, -949.231018, 128.878784, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(9339, -1184.056884, -928.708129, 128.878784, 0.000000, 0.000000, -54.599910, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(9339, -1166.873168, -916.496459, 128.878784, 0.000000, 0.000000, -54.599910, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1193.436157, -988.928955, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(9339, -1194.647705, -1058.352294, 128.878784, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1193.436157, -1003.699462, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1119.799560, -1026.761718, 127.658470, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1143.463623, -1004.156005, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(16281, -1177.625854, -1004.196716, 130.988815, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1119.799560, -1044.171875, 127.658470, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1087.358520, -1026.791625, 127.658470, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1153.204101, -1003.699462, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1144.851074, -988.928955, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1059.260498, -988.655944, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1132.320922, -1003.699462, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1122.129638, -1003.699462, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1112.040283, -1003.699462, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1103.290161, -1003.699462, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1087.358520, -1044.191650, 127.658470, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1056.656738, -1026.770629, 127.658470, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1132.037597, -988.928955, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1082.638183, -1003.699462, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1122.172729, -988.928955, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1111.728759, -988.928955, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1073.235717, -1003.699462, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1102.915039, -988.928955, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19543, -1048.550537, -996.406555, 128.228652, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1056.656738, -1044.171752, 127.658470, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1082.247802, -988.928955, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1073.097290, -988.928955, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1162.130493, -935.323059, 127.658470, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1059.330566, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1122.129638, -1025.230346, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1137.391235, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1134.859252, -966.032836, 127.658470, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1122.129638, -1043.451782, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1132.320922, -1025.222045, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1132.320922, -1043.367187, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1122.172729, -969.048461, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1132.037597, -968.467224, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1122.172729, -949.317749, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1132.037597, -948.706237, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1122.172729, -931.197448, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1134.859252, -930.971923, 127.658470, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1132.037597, -931.133361, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19543, -1163.382812, -996.406555, 128.238647, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19543, -1100.892578, -996.406555, 128.238647, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19543, -1127.242065, -1029.673583, 128.248641, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(19543, -1127.242065, -959.024902, 128.278625, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(16281, -1107.404541, -988.976196, 130.988815, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(16281, -1077.789428, -988.976196, 130.988815, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1119.799560, -966.072021, 127.658470, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1087.358520, -966.072021, 127.658470, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1087.518676, -931.021667, 127.658470, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1119.799560, -930.991394, 127.658470, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1114.225219, -988.806091, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1117.656127, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1056.656738, -966.072021, 127.658470, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1100.363769, -988.806091, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1095.813232, -988.806091, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1091.311889, -988.806091, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1089.930786, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1056.656738, -931.021911, 127.658470, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1084.710693, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1070.350952, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1065.881225, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1061.311767, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1064.000122, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1068.640136, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1070.299682, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1084.590209, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1089.999877, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1094.649658, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1099.239868, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1100.400512, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1114.660156, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1117.010620, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1134.799560, -1026.761718, 127.658470, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1134.799560, -1044.162475, 127.658470, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(16281, -1148.965332, -988.976196, 130.988815, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1162.130493, -1026.761718, 127.658470, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1162.130493, -1044.572753, 127.658470, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(7191, -1162.130493, -966.032836, 127.658470, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1152.871582, -988.928955, 128.158645, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(16281, -1148.965332, -1004.196716, 130.988815, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1145.134765, -1003.699462, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1141.932250, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1154.443847, -1003.975830, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1158.374145, -1004.045898, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1159.684082, -1004.156005, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1137.587890, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1173.694702, -1003.699462, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1142.167724, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1154.909790, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1181.934570, -1003.699462, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1159.479125, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1164.714721, -1004.156005, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(16281, -1177.625854, -988.485717, 130.988815, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1169.284423, -1004.156005, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1171.855102, -1004.226074, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1183.415161, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1187.925292, -1004.005859, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1181.934570, -989.109741, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1192.105102, -1004.045898, 128.918609, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1164.798950, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1169.339477, -988.756042, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1172.030151, -988.655944, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3508, -1173.805175, -989.109741, 128.158645, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1183.612304, -988.766052, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1188.162475, -988.766052, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1192.233154, -988.625915, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(16281, -1107.404541, -1004.017517, 130.988815, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(16281, -1077.922729, -1004.017517, 130.988815, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3252, -1053.538085, -987.032470, 128.118652, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3252, -1045.947509, -987.032470, 128.078659, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1162.076293, -1003.496337, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1054.270751, -983.536560, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1040.589721, -983.536560, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1049.719360, -983.536560, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1045.139404, -983.536560, 128.918609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1038.240478, -985.856872, 128.918609, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1456, -1038.150390, -987.066894, 128.918609, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1163.027221, -1022.136779, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1163.027221, -1040.158691, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1163.027221, -1059.278442, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1135.715942, -1022.136779, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1135.276977, -1040.158691, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1135.317016, -1059.278442, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1194.128173, -1022.136779, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1194.206665, -1040.158691, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1194.017822, -1059.278442, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1180.946777, -1003.496337, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1194.557739, -1003.496337, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1194.557739, -989.096618, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1180.946777, -989.206115, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1162.137207, -989.206115, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1145.837280, -989.206115, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1134.216796, -989.206115, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1120.736450, -989.206115, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1110.746337, -989.206115, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1087.354736, -989.206115, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1074.224609, -989.206115, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1056.714233, -989.206115, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1056.714233, -1003.395996, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1074.344238, -1003.395996, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1087.274780, -1003.395996, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1110.945068, -1003.395996, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1120.824584, -1003.395996, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1133.435058, -1003.395996, 128.283355, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1194.557739, -968.695861, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1194.557739, -947.135498, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1161.697753, -947.135498, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1161.697753, -968.855407, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1161.697753, -924.385131, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1135.347167, -924.385131, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1135.347167, -946.825256, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1135.347167, -968.575378, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1119.376708, -968.575378, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1119.376708, -946.275085, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1119.376708, -924.484924, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1087.896240, -924.484924, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1087.896240, -945.595520, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1087.896240, -968.275634, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1056.995971, -968.275634, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1056.995971, -945.134643, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1056.995971, -924.544433, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1118.875610, -1022.136779, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1118.875610, -1039.667358, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1118.875610, -1059.137573, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1482, -1003.125793, -1017.071899, 129.482635, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1086.815673, -1059.137573, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1482, -1003.125793, -1023.751953, 129.482635, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1086.815673, -1039.517456, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1482, -1003.125793, -1030.452392, 129.482635, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1482, -1003.125793, -1037.173217, 129.482635, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1086.815673, -1022.377624, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1482, -1003.125793, -1043.852416, 129.482635, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1482, -1003.125793, -1050.552612, 129.482635, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1056.013793, -1022.377624, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1056.013793, -1039.678222, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1568, -1056.013793, -1059.118652, 128.263366, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(12918, -1029.420532, -1003.516174, 128.218750, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1458, -1039.244262, -1005.686462, 128.361846, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1453, -1018.327819, -1003.762329, 128.752563, -17.100002, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    return 1;
}