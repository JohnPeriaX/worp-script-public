#if defined _inc_impl
	#undef _inc_impl
#endif

stock Boombox_Place(playerid)
{
	new
	    Float:angle;

	GetPlayerFacingAngle(playerid, angle);

	strpack(BoomboxData[playerid][boomboxURL], "", 128 char);
	GetPlayerPos(playerid, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2]);

	BoomboxData[playerid][boomboxPlaced] = true;
	BoomboxData[playerid][boomboxInterior] = GetPlayerInterior(playerid);
	BoomboxData[playerid][boomboxWorld] = GetPlayerVirtualWorld(playerid);

	BoomboxData[playerid][boomboxObject] = CreateDynamicObjectEx(2226, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2] - 0.9, 0.0, 0.0, angle, -1, -1);
    BoomboxData[playerid][boomboxText3D] = CreateDynamic3DTextLabel("[Boombox]\nใช้ '/boombox' เพื่อใช้งาน", COLOR_WHITE, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2] - 0.7, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, BoomboxData[playerid][boomboxWorld], BoomboxData[playerid][boomboxInterior]);

	return 1;
}

Boombox_Nearest(playerid){
	foreach (new i : Player) if(LoggedIn[i]){
		if(!BoomboxData[i][boomboxPlaced]) continue;
		if (GetPlayerInterior(playerid) != BoomboxData[i][boomboxInterior] && GetPlayerVirtualWorld(playerid) != BoomboxData[i][boomboxWorld]) continue;
		if(IsPlayerInRangeOfPoint(playerid, 30.0, BoomboxData[i][boomboxPos][0], BoomboxData[i][boomboxPos][1], BoomboxData[i][boomboxPos][2])){
			return i;
		}
	}
	return INVALID_PLAYER_ID;
}

stock Boombox_SetURL(playerid, const url[])
{
	if (BoomboxData[playerid][boomboxPlaced]){
	    strpack(BoomboxData[playerid][boomboxURL], url, 128 char);

	    foreach (new i : Player) if(LoggedIn[i]){
			if (PlayerData[i][pBoombox] == playerid) {
				StopAudioStreamForPlayer(i);
				PlayAudioStreamForPlayer(i, url, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2], 30.0, 1);
			}
		}
	}
	return 1;
}

stock Boombox_Destroy(playerid){
	if (BoomboxData[playerid][boomboxPlaced]){
		if (IsValidDynamicObject(BoomboxData[playerid][boomboxObject]) && BoomboxData[playerid][boomboxObject] != -1) DestroyDynamicObject(BoomboxData[playerid][boomboxObject]);
		if (IsValidDynamic3DTextLabel(BoomboxData[playerid][boomboxText3D]) && BoomboxData[playerid][boomboxText3D]) DestroyDynamic3DTextLabel(BoomboxData[playerid][boomboxText3D]);
		BoomboxData[playerid][boomboxObject] = -1;
		Streamer_Update(playerid);
		foreach (new i : Player) if (LoggedIn[i] && PlayerData[i][pBoombox] == playerid) {
		    StopAudioStreamForPlayer(i);
		}

        BoomboxData[playerid][boomboxPlaced] = false;
        BoomboxData[playerid][boomboxInterior] = 0;
        BoomboxData[playerid][boomboxWorld] = 0;
	}
	return 1;
}