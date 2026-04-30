
#if defined _inc_impl
	#undef _inc_impl
#endif

ResetCowJob(playerid){
    KillTimer(CowJobTimer[playerid]);
    CheckPlayerChangeSkin[playerid] = 0;
    CowJobTimer[playerid] = 0;
    CowPoint[playerid] = 0;
    PickingUpCow[playerid] = 0;
    CowGetID[playerid] = -1;
    PlayerUseKnife[playerid] = 0;
    StartProcessMeat[playerid] = 0;
    return 1;
}

SetPlayerSkinToCowJob(playerid){
    if(CheckPlayerChangeSkin[playerid] == 0){
        
        CheckPlayerChangeSkin[playerid] = 1;

        if(PlayerData[playerid][pGender] == 1)
            SetPlayerSkin(playerid, SKIN_MALE);

        else if(PlayerData[playerid][pGender] == 2)
            SetPlayerSkin(playerid, SKIN_FEMALE);

        SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เปลี่ยนชุดทำงานเรียบร้อยแล้ว, สามารถเริ่มงานได้เลย");
        SendClientMessage(playerid, COLOR_YELLOW, "- กรุณาหยิบ 'Knife' ออกมาก่อนจะทำการฆ่าวัว");
    }
    else if(CheckPlayerChangeSkin[playerid] == 1){
        CheckPlayerChangeSkin[playerid] = 0;

        SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
        SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เปลี่ยนชุดกลับมาเป็นชุดเดิมของคุณแล้ว");
    }
    return 1;
}

forward Cow_Load();
public Cow_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_COWS)
	{
	    CowData[i][cowStill] = true;

	    cache_get_value_name_int(i, "cowID", CowData[i][cowID]);
	    cache_get_value_name_float(i, "cowPosX", CowData[i][cowPos][0]);
	    cache_get_value_name_float(i, "cowPosY", CowData[i][cowPos][1]);
	    cache_get_value_name_float(i, "cowPosZ", CowData[i][cowPos][2]);
        cache_get_value_name_float(i, "cowPosA", CowData[i][cowPos][3]);

        cache_get_value_name_float(i, "cowPosMoveX", CowData[i][cowPosMove][0]);
        cache_get_value_name_float(i, "cowPosMoveY", CowData[i][cowPosMove][1]);
        cache_get_value_name_float(i, "cowPosMoveZ", CowData[i][cowPosMove][2]);

        Cow_Count++;
        CreateCow(i, CowData[i][cowPos][0], CowData[i][cowPos][1], CowData[i][cowPos][3]);
        CowMoving(i);

	}
	printf("(( [MYSQL]: Load %d Cow Successfully ))", Cow_Count);
	return 1;
}

stock CreateCow(cowid, Float:X, Float:Y, Float:A){
    new Float:Z;
    MapAndreas_FindZ_For2DCoord(X,Y,Z);
    CowData[cowid][cowObject] = CreateDynamicObject(19833,X,Y,Z+2.1,0,0,A,-1,-1,-1,300);
}

CowMoving(cowid){
    if(CowData[cowid][cowDeath] == 1)
        return SetTimerEx("CowMoving", 1000, 0, "d", cowid);

    if(CowData[cowid][cowMoving] == 1)
        return SetTimerEx("CowMoving", 1000, 0, "d", cowid);

    if(CowData[cowid][cowMove] == 0){
        SetMoveBack(cowid);
    }
    else if(CowData[cowid][cowMove] == 1){
        SetMoveFront(cowid);
    }
    return 1;
}

forward SetMoveBack(cowid);
public SetMoveBack(cowid){

    if(CowData[cowid][cowDeath] == 1)
        return SetTimerEx("SetMoveBack", 1000, 0, "d", cowid);

    if(CowData[cowid][cowMoving] == 1)
        return SetTimerEx("SetMoveBack", 1000, 0, "d", cowid);

    new count = random(5000);
    CowData[cowid][cowMoving] = 1;
    MoveDynamicObject(CowData[cowid][cowObject], CowData[cowid][cowPosMove][0], CowData[cowid][cowPosMove][1], CowData[cowid][cowPosMove][2], 8.0, 0.00000, 0.00000, CowData[cowid][cowPos][3]);
    CowData[cowid][cowMoving] = 0;
    CowData[cowid][cowMove] = 1;
    SetTimerEx("SetMoveFront", 1000+count, 0, "d", cowid);
    return 1;
}

forward SetMoveFront(cowid);
public SetMoveFront(cowid){
    if(CowData[cowid][cowDeath] == 1)
        return SetTimerEx("SetMoveFront", 1000, 0, "d", cowid);

    if(CowData[cowid][cowMoving] == 1)
        return SetTimerEx("SetMoveFront", 1000, 0, "d", cowid);

    new count = random(5000);
    CowData[cowid][cowMoving] = 1;
    MoveDynamicObject(CowData[cowid][cowObject], CowData[cowid][cowPos][0], CowData[cowid][cowPos][1], CowData[cowid][cowPos][2], 8.0, 0.00000, 0.00000, CowData[cowid][cowPos][3]);
    CowData[cowid][cowMoving] = 0;
    CowData[cowid][cowMove] = 0;
    SetTimerEx("SetMoveBack", 1000+count, 0, "d", cowid);
    return 1;
}

Cow_Nearest(playerid, Float:radius = 3.5)
{
    for (new i = 0; i != MAX_COWS; i ++) if (CowData[i][cowStill] && IsPlayerInRangeOfPoint(playerid, radius, CowData[i][cowFixPos][0], CowData[i][cowFixPos][1], CowData[i][cowFixPos][2])) {
		return i;
	}
	return -1;
}

forward PickingupMeat(playerid);
public PickingupMeat(playerid)
{
    new string[64];
	if(LoggedIn[playerid])
	{
        if(PickingUpCow[playerid] == 1){
            CowPoint[playerid] += 2;
            SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], CowPoint[playerid]);
            format(string,sizeof(string),"PickingUp... (%d)", CowPoint[playerid]);
            PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
            //GameTextForPlayer(playerid, string, 1500, 3);
            Streamer_Update(playerid);
        }

        if(PickingUpCow[playerid] != 0 && CowPoint[playerid] < 100 && CowJobTimer[playerid] != 0)
        {
            TogglePlayerControllable(playerid, 0);
            ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
            CowJobTimer[playerid] = SetTimerEx("PickingupMeat", 1000, 0, "i", playerid);
        }

        if(PickingUpCow[playerid] != 0 && CowPoint[playerid] >= 100)
        {
            KillTimer(CowJobTimer[playerid]);
            PickingUpCow[playerid] = 0;
            CowJobTimer[playerid] = 0;
            TogglePlayerControllable(playerid, 1);
            ClearAnimations(playerid);
            DestroyPlayerProgressbar_Job(playerid);
            
            CowPoint[playerid] = 0;

            SetDynamicObjectPos(CowData[CowGetID[playerid]][cowObject], CowData[CowGetID[playerid]][cowPos][0], CowData[CowGetID[playerid]][cowPos][1], CowData[CowGetID[playerid]][cowPos][2]);
            MoveDynamicObject(CowData[CowGetID[playerid]][cowObject], CowData[CowGetID[playerid]][cowPos][0], CowData[CowGetID[playerid]][cowPos][1], CowData[CowGetID[playerid]][cowPos][2], 2.0, 0.00000, 0.00000, CowData[CowGetID[playerid]][cowPos][3]);
            CowData[CowGetID[playerid]][cowDeath] = 0;
            CowData[CowGetID[playerid]][cowPicking] = 0;
            CowGetID[playerid] = -1;

            new id = PlayerInventory_AddItem(playerid, "Raw Cow Meat", 19582, 10);

            if (id == -1){
                return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            }

            PlayerData[playerid][pStress]++;
            if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;

            SendClientMessage(playerid, COLOR_ORANGE, "- คุณได้รับ เนื้อวัว + 10");
        }
	}
	return 1;
}

CMD:recow(playerid, params[]){
    if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        for(new i=0; i<MAX_COWS; i++){
            if(CowData[i][cowStill]){
                SetDynamicObjectPos(CowData[i][cowObject], CowData[i][cowPos][0], CowData[i][cowPos][1], CowData[i][cowPos][2]);
                MoveDynamicObject(CowData[i][cowObject], CowData[i][cowPos][0], CowData[i][cowPos][1], CowData[i][cowPos][2], 2.0, 0.00000, 0.00000, CowData[i][cowPos][3]);
                CowData[i][cowDeath] = 0;
                CowData[i][cowPicking] = 0;
            }
        }
    }
    return 1;
}

forward ProcessMeat(playerid);
public ProcessMeat(playerid)
{
    new string[64];
	if(LoggedIn[playerid])
	{
        if(StartProcessMeat[playerid] == 1){
            CowPoint[playerid] += 2;
            SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], CowPoint[playerid]);
            format(string,sizeof(string),"Meat Packing... (%d)", CowPoint[playerid]);
            PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
            //GameTextForPlayer(playerid, string, 1500, 3);
            Streamer_Update(playerid);
        }

        if(StartProcessMeat[playerid] != 0 && CowPoint[playerid] < 100 && CowJobTimer[playerid] != 0)
        {
            TogglePlayerControllable(playerid, 0);
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
            CowJobTimer[playerid] = SetTimerEx("ProcessMeat", 1000, 0, "i", playerid);
        }

        if(StartProcessMeat[playerid] != 0 && CowPoint[playerid] >= 100)
        {
            KillTimer(CowJobTimer[playerid]);
            StartProcessMeat[playerid] = 0;
            CowJobTimer[playerid] = 0;
            TogglePlayerControllable(playerid, 1);
            ClearAnimations(playerid);
            DestroyPlayerProgressbar_Job(playerid);
            new count = PlayerInventory_AllCount(playerid, "Raw Cow Meat");

            new id = PlayerInventory_AddItem(playerid, "Pack Cow Meat", 19567, count/2);

            if (id == -1)
                return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            
            PlayerInventory_Remove(playerid, "Raw Cow Meat", count);
            SendClientMessage(playerid, COLOR_DARKGREEN, "|------------------------------------------|");
            SendClientMessageEx(playerid, COLOR_WHITE, "- คุณได้รับ แพ็คเนื้อวัว + %d", count/2);
            SendClientMessageEx(playerid, COLOR_WHITE, "- คุณเสีย เนื้อวัว - %d", count);
            SendClientMessage(playerid, COLOR_DARKGREEN, "|------------------------------------------|");
            CowPoint[playerid] = 0;
        }
	}
	return 1;
}

ShowDialogSellCow(playerid){
    new string[128];
    new count = PlayerInventory_AllCount(playerid, "Pack Cow Meat");
    format(string, sizeof(string), "คุณมีแพ็คเนื้อวัวอยู่: %d\nกรอกจำนวนที่ต้องการจะขาย", count);
    Dialog_ShowEasy(playerid, Dialog_SellCow, DIALOG_STYLE_INPUT, "ขายแพ็คเนื้อวัว", string, "ขาย", "ยกเลิก");
    return 1;
}

Dialog:Dialog_SellCow(playerid, response, listitem, inputtext[]){
    if(!response){
        GetJobID[playerid] = -1;
        return 1;
    }

    if(response){
        new amount = strval(inputtext);

        if(amount > PlayerInventory_AllCount(playerid, "Pack Cow Meat"))
            return ErrorMsg(playerid, "คุณมีแพ็คเนื้อวัวไม่พอกับจำนวนที่คุณจะขาย");

        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนที่จะขายให้มากกว่า 0");

        new price = amount * JobData[GetJobID[playerid]][jobDeliverPrice];
        GiveMoney(playerid, price, "sell Pack cow meat");
        SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ขาย 'Pack Cow Meat (แพ็คเนื้อวัว)' จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
        PlayerInventory_Remove(playerid, "Pack Cow Meat", amount);
    }
    return 1;
}