#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

Reset_SharkJob(playerid){
    StartFishingShark[playerid] = false;
    KillTimer(TimeFishingShark[playerid]);
    SharkOnRod[playerid] = false;
    DisablePlayerCheckpoint(playerid);
    PointToFishShark[playerid] = false;
    return 1;
}

LoadShark_Object(){
    tmpobjid = CreateDynamicObject(3861, -2903.100585, 1245.595581, 7.171562, 0.000000, 0.000000, 44.799961, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1290, -2900.900390, 1247.740722, 11.028849, 0.000000, 0.000000, 35.099990, -1, -1, -1, 300.00, 300.00); 

    Shark_Object[0] = CreateDynamicObject(1608, -2898.533935, 1675.383911, -7.603221, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    Shark_Object[1] = CreateDynamicObject(1608, -2935.391601, 1680.818725, -7.868283, 0.000000, 0.000000, -69.000007, -1, -1, -1, 300.00, 300.00); 
    Shark_Object[2] = CreateDynamicObject(1608, -2910.493652, 1710.065795, -9.466331, 0.000000, 0.000000, 75.699996, -1, -1, -1, 300.00, 300.00); 
    Shark_Object[3] = CreateDynamicObject(1608, -2913.369873, 1641.935424, -10.486139, 0.000000, 0.000000, 53.800006, -1, -1, -1, 300.00, 300.00); 
    return 1;
}

hook OnGameModeInit(){
    LoadShark_Object();
    return 1;
}

SetPlayerToFishSharkPoint(playerid){
    new idx = GetClosestJobPoint(playerid, PlayerData[playerid][pJob]);
    if (idx != -1)
    {
        if(JobData[idx][jobPoint][0] == 0.0 && JobData[idx][jobPoint][1] == 0.0 && JobData[idx][jobPoint][2] == 0.0)
            return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

        SetPlayerCheckpoint(playerid, JobData[idx][jobPoint][0], JobData[idx][jobPoint][1], JobData[idx][jobPoint][2],60.0);
        SendClientMessage(playerid, -1,"- ไปยังจุดสีแดงเพื่อเริ่มตกปลาฉลาม");
        PointToFishShark[playerid] = true;
    }
    return 1;
}

StartFishingSharkJob(playerid){
    StartFishingShark[playerid] = true;

    new randoms = random(50000);
    if(randoms < 10000) randoms = 10000;

    TimeFishingShark[playerid] = SetTimerEx("FishShark", 5000+randoms, false, "i", playerid);
    SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เริ่มตกปลาฉลามแล้ว");
    ClearAnimations(playerid);
    ApplyAnimation(playerid,"SWORD","sword_block",50.0,0,1,0,1,1);
    SetPlayerAttachedObject(playerid, 7, 18632, 6,0.079376,0.037070,0.007706,181.482910,0.000000,0.000000,1.000000,1.000000,1.000000);
    SetCameraBehindPlayer(playerid);
    return 1;
}

GetRodOnHand(playerid){
    SharkOnRod[playerid] = false;
    StartFishingShark[playerid] = false;
    ClearAnimations(playerid);
    Reset_SharkJob(playerid);
    RemovePlayerAttachedObject(playerid, 7);

    new amount, string[128];
    if(PlayerData[playerid][pSharkJobLevel] >= 0 && PlayerData[playerid][pSharkJobLevel] <= 5) amount = 1;
    else if(PlayerData[playerid][pSharkJobLevel] >= 6 && PlayerData[playerid][pSharkJobLevel] <= 10) amount = 2;
    else if(PlayerData[playerid][pSharkJobLevel] >= 11 && PlayerData[playerid][pSharkJobLevel] <= 15) amount = 3;
    else if(PlayerData[playerid][pSharkJobLevel] >= 16 && PlayerData[playerid][pSharkJobLevel] <= 20) amount = 4; 
    PlayerData[playerid][pStress]++;
    if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
    new itemid = PlayerInventory_AddItem(playerid, "Shark Fish", 1608, amount);
    if(itemid == -1) {
        ClearAnimations(playerid);
        Reset_SharkJob(playerid);
        RemovePlayerAttachedObject(playerid, 7);
        return ErrorMsg(playerid, "กระเป๋าของคุณมีพื้นที่ไม่พอที่จะเก็บ 'Shark Fish'");
    }

    SendClientMessageEx(playerid, COLOR_ORANGE, "+ คุณได้รับ 'Shark Fish (ปลาฉลาม) + %d", amount);

    format(string,sizeof(string),"~n~~n~~n~~n~~n~~n~~n~~n~~g~Get Shark Fish");
    GameTextForPlayer(playerid, string, 1000, 3);
    SendClientMessage(playerid, COLOR_YELLOW, "- หากต้องการตกอีกครั้งให้กดปุ่ม 'Y' เพื่อเริ่มตกอีกครั้ง");

    PlayerData[playerid][pSharkJobExp]++;

    new nxtlevel = PlayerData[playerid][pSharkJobLevel]+1;
    new expamount = nxtlevel*levelexpshark;
    if(PlayerData[playerid][pSharkJobExp] >= expamount){
        if(PlayerData[playerid][pSharkJobLevel] < 20){
            PlayerData[playerid][pSharkJobExp] -= expamount;
            PlayerData[playerid][pSharkJobLevel]++;
            SendClientMessageEx(playerid, COLOR_GREY, "- ยินดีด้วยเลเวลตกปลาฉลามของคุณอัพเป็น %d แล้ว", PlayerData[playerid][pSharkJobLevel]);
        }
        else if(PlayerData[playerid][pSharkJobLevel] >= 20) SendClientMessageEx(playerid, COLOR_GREY, "- คุณมีเลเวล ตกปลาฉลาม %d แล้ว!", PlayerData[playerid][pSharkJobLevel]);
    }
    return 1;
}

timer ReCallTimeFishShark[5000](playerid){
    if(SharkOnRod[playerid]){
        SharkOnRod[playerid] = false;
        StartFishingShark[playerid] = false;
        ClearAnimations(playerid);
        Reset_SharkJob(playerid);
        RemovePlayerAttachedObject(playerid, 7);
        ErrorMsg(playerid, "ปลาฉลามของคุณหลุดออกจากเบ็ดไปแล้ว");
    }
}

forward FishShark(playerid);
public FishShark(playerid){
    if(!LoggedIn[playerid]) return 1;
    new string[128];
    if(StartFishingShark[playerid]){
        if(Job_NearestPointFishShark(playerid) != -1){
            SharkOnRod[playerid] = true;
            format(string,sizeof(string),"~n~~n~~n~~n~~n~~n~~n~~n~~r~Shark Fish Hooked~n~~y~'Press 'FIRE' Get Rod'");
            GameTextForPlayer(playerid, string, 5000, 3);
            defer ReCallTimeFishShark(playerid);
        }   
        else{
            KillTimer(TimeFishingShark[playerid]);
            StartFishingShark[playerid] = false;
            ClearAnimations(playerid);
            RemovePlayerAttachedObject(playerid, 7);
            return ErrorMsg(playerid, "การตกปลาฉลามถูกยกเลิกเนื่องจากคุณออกจากขอบเขตการตกปลา");
        }
    }
    return 1;
}

ShowDialogSellFishShark(playerid){
    new string[128];
    new count = PlayerInventory_AllCount(playerid, "Shark Fish");
    format(string, sizeof(string), "คุณมีปลาฉลามอยู่: %d\nกรอกจำนวนที่ต้องการจะขาย", count);
    Dialog_ShowEasy(playerid, Dialog_SellFishShark, DIALOG_STYLE_INPUT, "ขายปลาฉลาม", string, "ขาย", "ยกเลิก");
    return 1;
}

Dialog:Dialog_SellFishShark(playerid, response, listitem, inputtext[]){
    if(!response){
        GetJobID[playerid] = -1;
        return 1;
    }

    if(response){
        new amount = strval(inputtext);

        if(amount > PlayerInventory_AllCount(playerid, "Shark Fish"))
            return ErrorMsg(playerid, "คุณมีปลาฉลามไม่พอกับจำนวนที่คุณจะขาย");

        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนที่จะขายให้มากกว่า 0");

        new price = amount * JobData[GetJobID[playerid]][jobDeliverPrice];
        GiveMoney(playerid, price, "sell shark fish");
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Shark Fish (ปลาฉลาม)' จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
        PlayerInventory_Remove(playerid, "Shark Fish", amount);
    }
    return 1;
}