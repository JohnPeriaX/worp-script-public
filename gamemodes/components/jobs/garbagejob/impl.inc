#if defined _inc_impl
	#undef _inc_impl
#endif

ResetGarbageJob(playerid){
    ChangeSkinGarbage[playerid] = 0;
    PlayerHoldJunk[playerid] = 0;
    GetSumRan[playerid] = -1;
    CheckEnterPointGarbageJob[playerid] = 0;
    CheckEnterDeliverPoint[playerid] = 0;
    KillTimer(GarbageTime[playerid]);
    GarbageTime[playerid] = 0;
    
    GarbagePoint[playerid] = 0;
    SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
    RemoveAttachedObject(playerid, 7);
    return 1;
}

new Float:RandomPointGarbageJob[][] = {
    {1148.5884,-1386.2263,13.8286},
    {949.0806,-1382.3976,13.3438},
    {2186.0210,-1260.3982,23.9503},
    {2491.2324,-1654.7123,13.3603},
    {2223.7783,-1470.6163,24.0092},
    {1536.3022,-1479.3708,9.5000},
    {1322.3051,-1237.3699,13.5469}
};

SetPlayerSkinGarbage(playerid){
    if(ChangeSkinGarbage[playerid] == 0){
        SetPlayerSkin(playerid, 79);
        ChangeSkinGarbage[playerid] = 1;
    }
    else if(ChangeSkinGarbage[playerid] == 1){
        SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
        ChangeSkinGarbage[playerid] = 0;
    }
    return 1;
}

forward LoadingJunkOut(playerid, vehicleid);
public LoadingJunkOut(playerid, vehicleid){
    new string[128];
    if(CoreVehicles[vehicleid][vehJunk] >= 10){
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
            if(GarbagePoint[playerid] < 100){
                GarbagePoint[playerid] += 10;
                SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], GarbagePoint[playerid]);
                format(string,sizeof(string),"Junk Loading... (%d)", GarbagePoint[playerid]);
                PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
                //GameTextForPlayer(playerid, string, 1500, 3);
                Streamer_Update(playerid);
                GarbageTime[playerid] = SetTimerEx("LoadingJunkOut", 1000, 0, "ii", playerid, vehicleid);
            }
            else if(GarbagePoint[playerid] >= 100){
                KillTimer(GarbageTime[playerid]);
                GarbagePoint[playerid] = 0;
                TogglePlayerControllable(playerid, 1);
                DestroyPlayerProgressbar_Job(playerid);
                PlayerData[playerid][pStress]++;
                if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
                new price;
                for(new i=0; i<MAX_DYNAMIC_JOBS; i++) if(JobData[i][jobExists]){
                    if(JobData[i][jobType] != GARBAGEJOB) continue;
                    else{
                        price = CoreVehicles[vehicleid][vehJunk] * JobData[i][jobDeliverPrice];
                    }
                }

                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ส่งขยะสำเร็จแล้วและได้รับเงิน %s", FormatNumber(price));
                GiveMoney(playerid, price, "send junk");
                CoreVehicles[vehicleid][vehJunk] = 0;
            }
        }
    }
    return 1;
}

SetPlayerGarbageCheckPoint(playerid){
    if(ChangeSkinGarbage[playerid] == 1 && PlayerHoldJunk[playerid] == 0 && CheckEnterPointGarbageJob[playerid] == 0){
        new rand = random(sizeof(RandomPointGarbageJob));
        GetSumRan[playerid] = rand;
        SetPlayerCheckpoint(playerid, RandomPointGarbageJob[rand][0], RandomPointGarbageJob[rand][1], RandomPointGarbageJob[rand][2], 3.0);
        CheckEnterPointGarbageJob[playerid] = 1;
        SendClientMessage(playerid, COLOR_YELLOW, "- ไปยังจุดสีแดง เพื่อเก็บขยะ");
    }
    return 1;
}