#if defined _inc_impl
	#undef _inc_impl
#endif

ptask UpdaateWeightOverload[5000](playerid){
    if(LoggedIn[playerid] && !IsPlayerNPC(playerid)){
        if(PlayerInvWeightTemp[playerid] > PlayerData[playerid][pInvMaxWeight]){
            SendClientMessageEx(playerid, COLOR_RED, "[!] น้ำหนักกระเป๋าของคุณเกิน (%.1f/%.1f)", PlayerInvWeightTemp[playerid], PlayerData[playerid][pInvMaxWeight]);
            ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1, 1, 0, 0, 0, 0, 1);
            FixJump[playerid] = SetTimerEx("Jumper", 3000, false, "i", playerid);
        }
    }
}