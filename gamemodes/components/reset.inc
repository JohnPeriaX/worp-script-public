ResetPlayer(playerid)
{
    PlayerData[playerid][pFirstAid] = false;
	KillTimer(PlayerData[playerid][pAidTimer]);

    if (FishJobTimer[playerid])
	    KillTimer(FishJobTimer[playerid]);

  	if (HarvestTimer[playerid])
	 	KillTimer(HarvestTimer[playerid]);

	BitFlag_Off(g_PlayerFlags[playerid], PLAYER_DRIVING_TEST);
	BitFlag_Off(g_PlayerFlags[playerid], PLAYER_MINING);
	BitFlag_Off(g_PlayerFlags[playerid], PLAYER_CRAFTING);
	BitFlag_Off(g_PlayerFlags[playerid], PLAYER_HARVESTING);
	BitFlag_Off(g_PlayerFlags[playerid], PLAYER_PICKUPING);
	BitFlag_Off(g_PlayerFlags[playerid], PLAYER_COOKMEAT);
	BitFlag_Off(g_PlayerFlags[playerid], PLAYER_CUFFED);
	BitFlag_Off(g_PlayerFlags[playerid], PLAYER_PICKING);
	BitFlag_Off(g_PlayerFlags[playerid], PLAYER_CAN_TELEPORT);
	BitFlag_Off(g_PlayerFlags[playerid], PLAYER_FPS);
    
    PlayerData[playerid][pInHospital] = 0;
	PlayerData[playerid][pFirstAid] = 0;
	PlayerData[playerid][pAidTimer] = 0;

	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	DisablePlayerCheckpoint(playerid);
	GameTextForPlayer(playerid, " ", 1, 3);
}