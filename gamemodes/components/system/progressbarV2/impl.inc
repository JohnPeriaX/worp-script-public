#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetPlayerProgressbarV2(playerid){
    PlayerProgress_Color[playerid] = -2016478465;
    PlayerGetPoint[playerid] = 0.0;
    PlayerRealPoint[playerid] = 0.0;
    PlayerPointSpace[playerid] = 0.0;
    PlayerStartProgressbar[playerid] = false;
    stop Progressbar_Timer[playerid];
    PlayerMissPoint[playerid] = 0;
    PlayerMaxMissPoint[playerid] = 0;
    return 1;
}

forward SetPlayerProgressbarV2(playerid, Float:point);
forward SetPlayerProgressbarV2_Color(playerid, color);
forward SetPlayerProgressbarV2_Hide(playerid);
forward SetPlayerProgressbar_UpdateP(playerid, Float:point);

CMD:progressbarv2(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] < 1337) return 1;
    new Float:point, color = -2016478465;
    if(sscanf(params, "fx", point, color)) return SystemMsg(playerid, "/progressbarv2 [point] [color]");
    if(point < 0 || point > 100) return ErrorMsg(playerid, "ต้องกรอกมากกว่า 0 และไม่เกิน 100");
    SetPlayerProgressbarV2_Color(playerid, color);
    SetPlayerProgressbarV2(playerid, point);
    return 1;
}

public SetPlayerProgressbarV2_Color(playerid, color){
    PlayerProgress_Color[playerid] = color;
    return 1;
}

public SetPlayerProgressbarV2(playerid, Float:point){
    PlayerStartProgressbar[playerid] = true;
    PlayerRealPoint[playerid] = point;
    PlayerPointSpace[playerid] = ((414.0 * point) / 220) + 3;
    PlayerLoadProgressbarV2(playerid);
    PlayerLoadProgressbarV2Point(playerid);
    PlayerTextDrawShow(playerid, ProgressBarV2_Text[playerid][0]);
    PlayerTextDrawShow(playerid, ProgressBarV2_Text[playerid][1]);
    ShowPlayerProgressBar(playerid, ProgressBarV2_Progressbar[playerid][0]);
    return 1;
}

public SetPlayerProgressbar_UpdateP(playerid, Float:point){
    PlayerRealPoint[playerid] = point;
    PlayerPointSpace[playerid] = ((414.0 * point) / 220) + 3;
    PlayerTextDrawHide(playerid, ProgressBarV2_Text[playerid][1]);
    PlayerTextDrawDestroy(playerid, ProgressBarV2_Text[playerid][1]);
    PlayerLoadProgressbarV2Point(playerid);
    PlayerTextDrawShow(playerid, ProgressBarV2_Text[playerid][1]);
    return 1;
}

public SetPlayerProgressbarV2_Hide(playerid){
    PlayerTextDrawHide(playerid, ProgressBarV2_Text[playerid][0]);
    PlayerTextDrawDestroy(playerid, ProgressBarV2_Text[playerid][0]);
    PlayerTextDrawHide(playerid, ProgressBarV2_Text[playerid][1]);
    PlayerTextDrawDestroy(playerid, ProgressBarV2_Text[playerid][1]);
    HidePlayerProgressBar(playerid, ProgressBarV2_Progressbar[playerid][0]);
    DestroyPlayerProgressBar(playerid, ProgressBarV2_Progressbar[playerid][0]);
    return 1;
}

PlayerProgressbar_ResetMaxPoint(playerid){
    PlayerMaxMissPoint[playerid] = 0;
    PlayerMissPoint[playerid] = 0;
    return 1;
}

PlayerProgressbar_GetMaxPoint(playerid){
    return PlayerMaxMissPoint[playerid];
}

PlayerProgressbar_SetMaxPoint(playerid, maxpoint = 1){
    PlayerMaxMissPoint[playerid] = maxpoint;
    return 1;
}

PlayerProgressbar_CheckResult(playerid){
    if(PlayerStartProgressbar[playerid]){
        if(PlayerGetPoint[playerid] >= PlayerRealPoint[playerid]-2.0 && PlayerGetPoint[playerid] <= PlayerRealPoint[playerid]+2.0) return 1;
        else return 0;
    }
    return -1;
}