#if defined _inc_impl
	#undef _inc_impl
#endif

void:ResetPlayerCircleProgressbar(playerid){
	stop playerProgressingCircle[playerid];
	playerShowProgressbarCircle[playerid] = false;
	playerCountingTextDrawCircle[playerid] = 29;
	playerCountTimeCircle[playerid] = 50;
	playerCircleProgressColor[playerid] = 0xBD00FFFF;
	format(playerCircleProgressCallback[playerid], 32, "NULL");
}

OP_PlayerStartCircleProgressbar(playerid, time = 50, color = 0xBD00FFFF, const callback[]){
	playerCountTimeCircle[playerid] = time;
	playerCircleProgressColor[playerid] = color;
	format(playerCircleProgressCallback[playerid], 32, callback);
	OP_CreateProgressbarCircle(playerid);
	return true;
}