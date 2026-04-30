#if defined _inc_impl
	#undef _inc_impl
#endif

ResetFishJob(playerid){
    KillTimer(FishJobTimer[playerid]);
    FishJobTimer[playerid] = 0;
    FishPoint[playerid] = 0;
    PlayerCanFishing[playerid] = 0;
    PlayerPressYToFishing[playerid] = 0;
    return 1;
}

SetPlayerToFishPoint(playerid){
    new idx = GetClosestJobPoint2(playerid, PlayerData[playerid][pJob]);
    if (idx != -1)
    {
        if(JobData[idx][jobPoint2][0] == 0.0 && JobData[idx][jobPoint2][1] == 0.0 && JobData[idx][jobPoint2][2] == 0.0)
            return ErrorMsg(playerid, "ไม่สามารถค้นหาจุดนี้ได้");

        SetPlayerCheckpoint(playerid, JobData[idx][jobPoint2][0], JobData[idx][jobPoint2][1], JobData[idx][jobPoint2][2],60.0);
        SendClientMessage(playerid, -1,"- ไปยังจุดสีแดงเพื่อเริ่มตกปลา");
    }
    return 1;
}

forward Fishing(playerid);
public Fishing(playerid)
{
    new string[64];
	if(LoggedIn[playerid])
	{
        if(PlayerCanFishing[playerid] == 1){
            if(Job_NearestPoint2Fish(playerid) != -1){
                FishPoint[playerid] += 1;
                SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], FishPoint[playerid]);
                format(string,sizeof(string),"Fishing: (%d KG)", FishPoint[playerid]);
                PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
                //GameTextForPlayer(playerid, string, 3000, 3);
                Streamer_Update(playerid);
            }
            else{
                KillTimer(FishJobTimer[playerid]);
                PlayerPressYToFishing[playerid] = 0;
                FishJobTimer[playerid] = 0;
                TogglePlayerControllable(playerid, 1);
                ClearAnimations(playerid);
                RemovePlayerAttachedObject(playerid, 7);
                DestroyPlayerProgressbar_Job(playerid);
                ErrorMsg(playerid, "คุณได้ออกจากพื้นที่ตกปลาทำให้คุณหยุดตกปลาในทันที");
                DisablePlayerCheckpoint(playerid);
                FishPoint[playerid] = 0;
            }
            if(FishPoint[playerid] < 100 && FishJobTimer[playerid] != 0)
            {
                FishJobTimer[playerid] = SetTimerEx("Fishing", 1200, 0, "i", playerid);
            }

            else if(FishPoint[playerid] >= 100){
                /*if(PlayerInventory_AllCount(playerid, "Raw Fish") + 25 > PlayerData[playerid][pItemAmount]){
                    KillTimer(FishJobTimer[playerid]);
                    PlayerPressYToFishing[playerid] = 0;
                    FishJobTimer[playerid] = 0;
                    TogglePlayerControllable(playerid, 1);
                    ClearAnimations(playerid);
                    RemovePlayerAttachedObject(playerid, 7);
                    HidePlayerProgressBar(playerid, ProgressbarJob[playerid]);
                    DestroyPlayerProgressBar(playerid, ProgressbarJob[playerid]);
                    SendClientMessage(playerid, COLOR_YELLOW, "- คุณมีช่องเก็บของไม่พอที่จะเก็บปลาอีก 20 ตัว ดังนั้นคุณจำเป็นต้องไปขายก่อน");
                    DisablePlayerCheckpoint(playerid);
                    FishPoint[playerid] = 0;
                }*/

                KillTimer(FishJobTimer[playerid]);
                PlayerPressYToFishing[playerid] = 0;
                FishJobTimer[playerid] = 0;
                TogglePlayerControllable(playerid, 1);
                ClearAnimations(playerid);
                RemovePlayerAttachedObject(playerid, 7);
                DestroyPlayerProgressbar_Job(playerid);
                    
                SendClientMessage(playerid, COLOR_YELLOW, "- คุณสามารถตกต่ออีกได้โดยการกดปุ่ม 'Y' หรือคุณต้องการจะไปขายก็ให้ขับเรือเข้าฝั่ง");
                DisablePlayerCheckpoint(playerid);
                FishPoint[playerid] = 0;
                PlayerData[playerid][pStress]++;
                if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;

                new id = PlayerInventory_AddItem(playerid, "Raw Fish", 19630, 25);

                if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

                SendClientMessageEx(playerid, COLOR_ORANGE, "- คุณได้รับ 'Raw Fish' + 25");  
            }
        }
	}
	return 1;
}

ShowDialogSellFish(playerid){
    new string[128];
    new count = PlayerInventory_AllCount(playerid, "Raw Fish");
    format(string, sizeof(string), "คุณมีปลาอยู่: %d\nกรอกจำนวนที่ต้องการจะขาย", count);
    Dialog_ShowEasy(playerid, Dialog_SellFish, DIALOG_STYLE_INPUT, "ขายปลา", string, "ขาย", "ยกเลิก");
    return 1;
}

Dialog:Dialog_SellFish(playerid, response, listitem, inputtext[]){
    if(!response){
        GetJobID[playerid] = -1;
        return 1;
    }

    if(response){
        new amount = strval(inputtext);

        if(amount > PlayerInventory_AllCount(playerid, "Raw Fish"))
            return ErrorMsg(playerid, "คุณมีปลาไม่พอกับจำนวนที่คุณจะขาย");

        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนที่จะขายให้มากกว่า 0");

        new price = amount * JobData[GetJobID[playerid]][jobDeliverPrice];
        GiveMoney(playerid, price, "sell fish");
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Raw Fish (ปลา)' จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
        PlayerInventory_Remove(playerid, "Raw Fish", amount);
    }
    return 1;
}