#if defined _inc_impl
	#undef _inc_impl
#endif

ResetJellyFish(playerid){
    JellyFishPoint[playerid] = 0;
    KillTimer(JellyFishTimer[playerid]);
    JellyFishTimer[playerid] = 0;
    JellyFishStartPickup[playerid] = 0;
    WearLifeVest[playerid] = 0;
    return 1;
}

forward JellyFish_Load();
public JellyFish_Load(){

    static
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_JELLYFISH)
	{
	    JellyFishData[i][jellyfishEx] = true;

	    cache_get_value_name_int(i, "jellyfishID", JellyFishData[i][jellyfishID]);
	    cache_get_value_name_float(i, "jellyfishPosX", JellyFishData[i][jellyfishPos][0]);
	    cache_get_value_name_float(i, "jellyfishPosY", JellyFishData[i][jellyfishPos][1]);
	    cache_get_value_name_float(i, "jellyfishPosZ", JellyFishData[i][jellyfishPos][2]);
	    cache_get_value_name_int(i, "jellyfishInt", JellyFishData[i][jellyfishInt]);
	    cache_get_value_name_int(i, "jellyfishWorld", JellyFishData[i][jellyfishWorld]);
	    cache_get_value_name_int(i, "jellyfishStill", JellyFishData[i][jellyfishStill]);

        count_jellyfish++;
        JellyFish_RenderRefresh(i);
 	    JellyFish_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d JellyFish Successfully ))", count_jellyfish);
	return 1;
}

JellyFish_RenderRefresh(jellyfishid){
    if (jellyfishid != -1 && JellyFishData[jellyfishid][jellyfishEx])
	{
	    new string[64];

        if(JellyFishData[jellyfishid][jellyfishStill] == 1){
            format(string, sizeof(string), "[แมงกระพรุน]\n( พร้อมเก็บ )\nกด 'Y' เพื่อเก็บ");
        }
        else if(JellyFishData[jellyfishid][jellyfishStill] == 0)
            format(string, sizeof(string), "[แมงกระพรุน]\n( ยังไม่พร้อมเก็บ )");

        JellyFishData[jellyfishid][jellyfishObject] = CreateDynamicObject(1602, JellyFishData[jellyfishid][jellyfishPos][0], JellyFishData[jellyfishid][jellyfishPos][1], JellyFishData[jellyfishid][jellyfishPos][2], 0.0, 0.0, 0.0);
		JellyFishData[jellyfishid][jellyfishText3D] = CreateDynamic3DTextLabel(string, 0xDCFF00FF, JellyFishData[jellyfishid][jellyfishPos][0], JellyFishData[jellyfishid][jellyfishPos][1], JellyFishData[jellyfishid][jellyfishPos][2], 2.0);
	}
    return 1;
}

JellyFish_Refresh(jellyfishid){
    if (jellyfishid != -1 && JellyFishData[jellyfishid][jellyfishEx]){
	    new
	        string[64];

        if(JellyFishData[jellyfishid][jellyfishStill] == 1){
            format(string, sizeof(string), "[แมงกระพรุน]\n( พร้อมเก็บ )\nกด 'Y' เพื่อเก็บ");
            MoveDynamicObject(JellyFishData[jellyfishid][jellyfishObject], JellyFishData[jellyfishid][jellyfishPos][0], JellyFishData[jellyfishid][jellyfishPos][1], JellyFishData[jellyfishid][jellyfishPos][2], 3.0, 0.0, 0.0, 0.0);
        }
        else if(JellyFishData[jellyfishid][jellyfishStill] == 0){
            format(string, sizeof(string), "[แมงกระพรุน]\n( ยังไม่พร้อมเก็บ )");
            MoveDynamicObject(JellyFishData[jellyfishid][jellyfishObject], JellyFishData[jellyfishid][jellyfishPos][0], JellyFishData[jellyfishid][jellyfishPos][1], JellyFishData[jellyfishid][jellyfishPos][2]-15.0, 3.0, 0.0, 0.0, 0.0);
        }

        UpdateDynamic3DTextLabelText(JellyFishData[jellyfishid][jellyfishText3D], 0xDCFF00FF, string);
	}
    return 1;
}

JellyFish_Nearest(playerid)
{
    for (new i = 0; i != MAX_JELLYFISH; i ++) if (JellyFishData[i][jellyfishEx] && IsPlayerInRangeOfPoint(playerid, 2.0, JellyFishData[i][jellyfishPos][0], JellyFishData[i][jellyfishPos][1], JellyFishData[i][jellyfishPos][2]))
	{
		if (GetPlayerInterior(playerid) == JellyFishData[i][jellyfishInt] && GetPlayerVirtualWorld(playerid) == JellyFishData[i][jellyfishWorld])
			return i;
	}
	return -1;
}

StartPickupJellyFish(playerid, jellyid){
    JellyFishStartPickup[playerid] = 1;

    //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0x008FFFAA, 100.000000, 0);
    CreatePlayerProgressbar_Job(playerid, 0x008FFFAA);
    JellyFishPoint[playerid] = 0;
    JellyFishTimer[playerid] = SetTimerEx("PickingupJelly", 1000, 0, "ii", playerid, jellyid);
    return 1;
}

forward PickingupJelly(playerid, jellyid);
public PickingupJelly(playerid, jellyid){
    if(!LoggedIn[playerid])
        return 0;

    new string[128];

    if(jellyid != -1){
        if(JellyFishStartPickup[playerid] == 1){
            if(JellyFishPoint[playerid] < 100){
                JellyFishPoint[playerid] += 20;
                TogglePlayerControllable(playerid, 0);
                ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
                SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], JellyFishPoint[playerid]);
                format(string,sizeof(string),"Picking... (%d)", JellyFishPoint[playerid]);
                PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
                //GameTextForPlayer(playerid, string, 1500, 3);
                Streamer_Update(playerid);
                JellyFishTimer[playerid] = SetTimerEx("PickingupJelly", 1000, 0, "ii", playerid, jellyid);
            }
            else if(JellyFishPoint[playerid] >= 100){
                JellyFishData[jellyid][jellyfishStill] = 0;
                JellyFishData[jellyid][jellyfishPicking] = 0;
                JellyFishData[jellyid][jellyfishDelay] = 20;
                JellyFish_Refresh(jellyid);

                KillTimer(JellyFishTimer[playerid]);
                JellyFishStartPickup[playerid] = 0;
                JellyFishTimer[playerid] = 0;
                TogglePlayerControllable(playerid, 1);
                ClearAnimations(playerid);
                DestroyPlayerProgressbar_Job(playerid);
                PlayerData[playerid][pStress]++;
                if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
                new id = PlayerInventory_AddItem(playerid, "Jelly Fish", 1602, 5);
                if (id == -1){
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }

                SendClientMessageEx(playerid, COLOR_GREENYELLOW, "- คุณได้รับ 'แมงกระพรุน' + 5");
            }
        }
    }
    return 1;
}

task UpdateJellyFish[1000](){
    for(new i=0; i<MAX_JELLYFISH; i++){
        if(JellyFishData[i][jellyfishEx]){
            if(JellyFishData[i][jellyfishDelay] > 0 && JellyFishData[i][jellyfishStill] == 0){
                JellyFishData[i][jellyfishDelay]--;
            }
            else if(JellyFishData[i][jellyfishDelay] <= 0 && JellyFishData[i][jellyfishStill] == 0){
                JellyFishData[i][jellyfishStill] = 1;
                JellyFish_Refresh(i);
            }
        }
    }
}

ShowDialogSellJellyFish(playerid){
    new string[128];
    new count = PlayerInventory_AllCount(playerid, "Jelly Fish");
    format(string, sizeof(string), "คุณมีแมงกระพรุนอยู่: %d\nกรอกจำนวนที่ต้องการจะขาย", count);
    Dialog_ShowEasy(playerid, Dialog_SellJellyFish, DIALOG_STYLE_INPUT, "ขายแมงกระพรุน", string, "ขาย", "ยกเลิก");
    return 1;
}

Dialog:Dialog_SellJellyFish(playerid, response, listitem, inputtext[]){
    if(!response){
        GetJobID[playerid] = -1;
        return 1;
    }

    if(response){
        new amount = strval(inputtext);

        if(amount > PlayerInventory_AllCount(playerid, "Jelly Fish"))
            return ErrorMsg(playerid, "คุณมีแมงกระพรุนไม่พอกับจำนวนที่คุณจะขาย");

        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนที่จะขายให้มากกว่า 0");

        new price = amount * JobData[GetJobID[playerid]][jobDeliverPrice];
        GiveMoney(playerid, price, "sell jelly fish");
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Jelly Fish (แมงกระพรุน)' จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
        PlayerInventory_Remove(playerid, "Jelly Fish", amount);
    }
    return 1;
}

CMD:rejellyfish(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] >= 1338){
        for(new i=0; i<MAX_JELLYFISH; i++){
            if(JellyFishData[i][jellyfishEx]){
                JellyFish_Refresh(i);
            }
        }
    }
    return 1;
}

CMD:reloadjellyfish(playerid, params[]){
    if(!LoggedIn[playerid])
        return 0;

    if(PlayerData[playerid][pAdmin] >= 1338){
        count_jellyfish = 0;
        mysql_tquery(dbCon, "SELECT * FROM `jellyfish`", "JellyFish_Load", "");
        SendClientMessage(playerid, -1, "คุณได้ทำการโหลด 'JellyFish'");
    }
    return 1;
}