#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

CreatePlayerProgressbar_Job(playerid, color, Float:value = 100.0){
    PlayerTextDrawJob[playerid] = CreatePlayerTextDraw(playerid, 236.000000, 340.000000, "Loading... (100)");
    PlayerTextDrawFont(playerid, PlayerTextDrawJob[playerid], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTextDrawJob[playerid], 0.270833, 1.400000);
    PlayerTextDrawTextSize(playerid, PlayerTextDrawJob[playerid], 401.000000, 112.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTextDrawJob[playerid], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTextDrawJob[playerid], 0);
    PlayerTextDrawAlignment(playerid, PlayerTextDrawJob[playerid], 1);
    PlayerTextDrawColor(playerid, PlayerTextDrawJob[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextDrawJob[playerid], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTextDrawJob[playerid], 50);
    PlayerTextDrawUseBox(playerid, PlayerTextDrawJob[playerid], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTextDrawJob[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTextDrawJob[playerid], 0);

    ProgressbarJob[playerid] = CreatePlayerProgressBar(playerid, 235.000000, 357.000000, 171.500000, 14.500000, color, value, 0);

    PlayerTextDrawShow(playerid, PlayerTextDrawJob[playerid]);
    ShowPlayerProgressBar(playerid, ProgressbarJob[playerid]);
    return 1;
}

DestroyPlayerProgressbar_Job(playerid){
    HidePlayerProgressBar(playerid, ProgressbarJob[playerid]);
    DestroyPlayerProgressBar(playerid, ProgressbarJob[playerid]);

    PlayerTextDrawHide(playerid, PlayerTextDrawJob[playerid]);
    PlayerTextDrawDestroy(playerid, PlayerTextDrawJob[playerid]);
    return 1;
}