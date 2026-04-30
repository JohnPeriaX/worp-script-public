#if defined _inc_impl
	#undef _inc_impl
#endif

ResetEngjob(playerid){
    ChangeSkinEngJob[playerid] = 0;
    CheckEnterPointEngJob[playerid] = 0;
    RepairTime[playerid] = 0;
    RepairPoint[playerid] = 0;
    GetSumEngRandom[playerid] = -1;
    return 1;
}

new Float:RandomPointEngJob[][] = {
    {2404.0833,-1741.0732,13.5469},
    {2299.3918,-1722.7158,13.5469},
    {2092.0859,-1716.1841,13.5563},
    {2138.3184,-1467.4784,23.9813},
    {2166.3022,-1200.4297,24.0292},
    {2057.5896,-1093.8960,24.6866},
    {1959.4064,-1037.0370,24.3202},
    {1332.5162,-1414.2394,13.5429},
    {1040.6986,-1414.3494,13.3924},
    {816.4960,-1417.2468,14.6449}
};

StartPointEngJob(playerid){
    new rand = random(sizeof(RandomPointEngJob));
    
    SetPlayerCheckpoint(playerid, RandomPointEngJob[rand][0], RandomPointEngJob[rand][1], RandomPointEngJob[rand][2], 2.0);
    CheckEnterPointEngJob[playerid] = 1;
    GetSumEngRandom[playerid] = rand;
    SendClientMessage(playerid, COLOR_YELLOW, "- ไปยังจุดสีแดง เพื่อซ่อมเสาร์ไฟ");
    return 1;
}

StartRepairEngJob(playerid){
    TogglePlayerControllable(playerid, 0);
    SendClientMessage(playerid, COLOR_YELLOW, "- คุณกำลังซ่อมเสาร์ไฟฟ้าต้นนี้");
    //ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 0.000000, 428.000000, 644.500000, 20.500000, 0xFFF300AA, 100.000000, 0);
    CreatePlayerProgressbar_Job(playerid, 0xFFF300AA);
    RepairTime[playerid] = SetTimerEx("RepairingEng", 1000, 0, "i", playerid);
    return 1;
}

forward RepairingEng(playerid);
public RepairingEng(playerid){
    new string[128];
    if(LoggedIn[playerid]){
        RepairPoint[playerid] += 10;
        SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], RepairPoint[playerid]);
        format(string,sizeof(string),"Repairing... (%d)", RepairPoint[playerid]);
        PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
        //GameTextForPlayer(playerid, string, 1500, 3);
        Streamer_Update(playerid);
    }
    if(RepairPoint[playerid] < 100){
        if(!IsPlayerInAnyVehicle(playerid) && ChangeSkinEngJob[playerid] == 1){

            TogglePlayerControllable(playerid, 0);
            ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
            RepairTime[playerid] = SetTimerEx("RepairingEng", 1000, 0, "i", playerid);
        }
    }
    else if(RepairPoint[playerid] >= 100){
        if(!IsPlayerInAnyVehicle(playerid) && ChangeSkinEngJob[playerid] == 1){
            KillTimer(RepairTime[playerid]);
            TogglePlayerControllable(playerid, 1);
            ClearAnimations(playerid);
            DestroyPlayerProgressbar_Job(playerid);
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้ซ่อมเสาร์ไฟฟ้าต้นนี้สำเร็จแล้ว");
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้รับเงิน %s จากการซ่อมเสาร์ไฟ", FormatNumber(JobData[GetJobID[playerid]][jobDeliverPrice]));
            GiveMoney(playerid, JobData[GetJobID[playerid]][jobDeliverPrice], "Repair engjob");
            RepairPoint[playerid] = 0;
            StartPointEngJob(playerid);
            PlayerData[playerid][pStress]++;
            if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
        }
    }
    return 1;
}