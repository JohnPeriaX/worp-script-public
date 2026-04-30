#if defined _inc_impl
	#undef _inc_impl
#endif

ResetCutWoodJob(playerid){
    ChangeSkinCutWood[playerid] = 0;
    GetToolCutWood[playerid] = 0;
    RemoveAttachedObject(playerid, 7);
    RemoveAttachedObject(playerid, 8);
    CheckEnterCutWood[playerid] = 0;
    CutWoodPoint[playerid] = 0;
    CutWoodTimer[playerid] = 0;
    StartingCutWood[playerid] = 0;
    return 1;
}

#define MAX_WOODS (10)
enum wooddata{
    woodID,
    woodStill,
    Float:woodPos[3],
    woodAmount,
    STREAMER_TAG_3D_TEXT_LABEL:woodText3D
};
new WoodData[MAX_WOODS][wooddata], Wood_Count;

forward Wood_Load();
public Wood_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_WOODS)
	{
	    WoodData[i][woodStill] = 1;
	    cache_get_value_name_int(i, "woodID", WoodData[i][woodID]);
	    cache_get_value_name_float(i, "woodPosX", WoodData[i][woodPos][0]);
	    cache_get_value_name_float(i, "woodPosY", WoodData[i][woodPos][1]);
	    cache_get_value_name_float(i, "woodPosZ", WoodData[i][woodPos][2]);
	    cache_get_value_name_int(i, "woodAmount", WoodData[i][woodAmount]);

        Wood_Count++;

        Wood_RenderRefresh(i);
 	    Wood_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d Wood Successfully ))", Wood_Count);
	return 1;
}

Wood_Nearest(playerid, Float:radius = 3.0)
{
    for (new i = 0; i != MAX_WOODS; i ++) if (WoodData[i][woodStill] && IsPlayerInRangeOfPoint(playerid, radius, WoodData[i][woodPos][0], WoodData[i][woodPos][1], WoodData[i][woodPos][2])) {
		return i;
	}
	return -1;
}

Wood_RenderRefresh(woodid){
    if (woodid != -1){

        if (IsValidDynamic3DTextLabel(WoodData[woodid][woodText3D]))
            DestroyDynamic3DTextLabel(WoodData[woodid][woodText3D]);

        new string[128];
        format(string, sizeof(string), "[ต้นไม้]\nจำนวน: %d", WoodData[woodid][woodAmount]);
        WoodData[woodid][woodText3D] = CreateDynamic3DTextLabel(string, 0x0DD800FF, WoodData[woodid][woodPos][0], WoodData[woodid][woodPos][1], WoodData[woodid][woodPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
    }
}

Wood_Refresh(woodid){
    if (woodid != -1){
        new string[128];
        format(string, sizeof(string), "[ต้นไม้]\nจำนวน: %d", WoodData[woodid][woodAmount]);
        UpdateDynamic3DTextLabelText(WoodData[woodid][woodText3D], 0x0DD800FF, string);
    }
}

new Float:RandomPointCutWood[][] = {
    {-609.2039,-163.7666,74.7726},
    {-610.7103,-148.8013,73.2731},
    {-622.0439,-158.6236,70.0729},
    {-624.6700,-124.1680,66.5649},
    {-610.1867,-110.9436,66.3789},
    {-626.7664,-110.8601,65.5250},
    {-616.1936,-99.9119,65.2076},
    {-628.6956,-89.6217,65.422},
    {-638.5845,-102.3377,64.0895},
    {-638.5756,-119.6110,64.3277}
};

ShowDialogCutWood(playerid){
    new string[128];
    new string2[500];

    new strstatus[32];
    new strtool[32];

    if(ChangeSkinCutWood[playerid] == 0)
        strstatus = "ยังไม่ได้เปลี่ยนชุด";
    else
        strstatus = "เปลี่ยนชุดแล้ว";

    if(GetToolCutWood[playerid] == 0)
        strtool = "ยังไม่ได้รับ";
    else
        strtool = "รับไปแล้ว";

    format(string, sizeof(string), "> เปลี่ยนชุดทำงาน\t[%s]\n> รับอุปกรณ์\t[%s]", strstatus, strtool);
    format(string2, sizeof(string2), "รายการ\tสถานะ\n%s", string);
    Dialog_ShowEasy(playerid, Dialog_CutWood, DIALOG_STYLE_TABLIST_HEADERS, "อาชีพเสริม: ตัดไม้", string2, "เลือก", "ยกเลิก");
    return 1;
}


Dialog:Dialog_CutWood(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        if(listitem == 0){
            if(ChangeSkinCutWood[playerid] == 0){
                ChangeSkinCutWood[playerid] = 1;
                if(PlayerData[playerid][pGender] == 1)
                    SetPlayerSkin(playerid, 158);
                else if(PlayerData[playerid][pGender] == 2)
                    SetPlayerSkin(playerid, 198);
            }
            else{
                if(GetToolCutWood[playerid] == 1){
                    ErrorMsg(playerid, "คุณต้องคืนอุปกรณ์ตัดไม้ก่อน");
                    return ShowDialogCutWood(playerid);
                }

                ChangeSkinCutWood[playerid] = 0;
                SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
                ResetCutWoodJob(playerid);

            }
            return ShowDialogCutWood(playerid);
        }
        if(listitem == 1){
            if(ChangeSkinCutWood[playerid] == 0){
                ErrorMsg(playerid, "คุณจำเป็นต้องเปลี่ยนชุดทำงานก่อน");
                return ShowDialogCutWood(playerid);
            }

            if(GetToolCutWood[playerid] == 0){
                GetToolCutWood[playerid] = 1;
                CheckEnterMine[playerid] = 0;
                SetPlayerAttachedObject(playerid,8,341,6,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
                StartPointCutWood(playerid);
                //SetPlayerAttachedObject(playerid,7,18717,6,0.835000,0.042999,-1.337999,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
            }
            else{
                GetToolCutWood[playerid] = 0;
                CheckEnterCutWood[playerid] = 0;
                StartingCutWood[playerid] = 0;
                CutWoodPoint[playerid] = 0;
                CutWoodTimer[playerid] = 0;
                DisablePlayerCheckpoint(playerid);
                RemoveAttachedObject(playerid, 7);
                RemoveAttachedObject(playerid, 8);
            }
            return ShowDialogCutWood(playerid);
        }
    }
    return 1;
}

StartCutWood(playerid){

    new idx = -1;
    if((idx = Wood_Nearest(playerid)) != -1){
        if(WoodData[idx][woodAmount] <= 0){
            ErrorMsg(playerid, "ต้นไม้ต้นนี้ไม่เหลือไม้ให้คุณตัดแล้ว");
            return StartPointCutWood(playerid);
        }
    }

    StartingCutWood[playerid] = 1;
    //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0x0AA700AA, 100.000000, 0);
    CreatePlayerProgressbar_Job(playerid, 0x0AA700AA);
    TogglePlayerControllable(playerid, 0);
    SetPlayerAttachedObject(playerid,7,18717,6,0.835000,0.042999,-1.337999,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
    CutWoodTimer[playerid] = SetTimerEx("CutingWood", 1000, 0, "i", playerid);
    return 1;
}

forward CutingWood(playerid);
public CutingWood(playerid)
{
    new string[64];
	if(LoggedIn[playerid])
	{
        if(StartingCutWood[playerid] == 1){
            CutWoodPoint[playerid] += 5;
            SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], CutWoodPoint[playerid]);
            format(string,sizeof(string),"Cutting... (%d)", CutWoodPoint[playerid]);
            PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
            //GameTextForPlayer(playerid, string, 1500, 3);
            Streamer_Update(playerid);
        }

        if(StartingCutWood[playerid] != 0 && CutWoodPoint[playerid] < 100 && CutWoodTimer[playerid] != 0)
        {
            TogglePlayerControllable(playerid, 0);
            ApplyAnimation(playerid, "CHAINSAW", "weapon_csaw", 4.1, 0, 0, 0, 0, 0, 1);
            CutWoodTimer[playerid] = SetTimerEx("CutingWood", 1000, 0, "i", playerid);
        }

        if(StartingCutWood[playerid] != 0 && CutWoodPoint[playerid] >= 100)
        {
            KillTimer(CutWoodTimer[playerid]);
            StartingCutWood[playerid] = 0;
            CutWoodTimer[playerid] = 0;
            TogglePlayerControllable(playerid, 1);
            ClearAnimations(playerid);
            DestroyPlayerProgressbar_Job(playerid);
            PlayerData[playerid][pStress]++;
            if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
            new id = PlayerInventory_AddItem(playerid, "Wood", 19793, 2);

            if (id == -1)
                return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);

            SendClientMessage(playerid, COLOR_WHITE, "- คุณได้รับ 'Wood (ไม้)' + 2");
            //SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: หากคุณต้องการเลิกตัดไม้ ให้กลับไปเก็บอุปกรณ์และเปลี่ยนชุดกลับ");
            StartPointCutWood(playerid);
            RemoveAttachedObject(playerid, 7);
            new idx = -1;
            if((idx = Wood_Nearest(playerid)) != -1){
                WoodData[idx][woodAmount] -= 2;
                Wood_Refresh(idx);
            }
            CutWoodPoint[playerid] = 0;
        }
	}
	return 1;
}

StartPointCutWood(playerid){
    new rand = random(sizeof(RandomPointCutWood));
    
    SetPlayerCheckpoint(playerid, RandomPointCutWood[rand][0], RandomPointCutWood[rand][1], RandomPointCutWood[rand][2], 1.0);
    CheckEnterCutWood[playerid] = 1;
    CheckEnterMine[playerid] = 0;
    SendClientMessage(playerid, COLOR_YELLOW, "- ไปยังจุดสีแดง เพื่อเริ่มทำการตัดไม้");
    return 1;
}