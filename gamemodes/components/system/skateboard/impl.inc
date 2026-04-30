#if defined _inc_impl
	#undef _inc_impl
#endif

// 19878

ResetSkateBoard(playerid){
    InfoSkate[playerid][sActive] = false;
    SkateChangeAction[playerid] = false;
    ClearAnimations(playerid);
    SkatePlayerUsing[playerid] = false;
    KillTimer(PlayerTimerSkate[playerid]);
    return 1;
}

ptask UpdateSkateBoard[1000](playerid){
    if(LoggedIn[playerid]){
        
    }
}

forward ChangeRunAnimSkate(playerid);
public ChangeRunAnimSkate(playerid){
    SkateChangeAction[playerid] = true;
    ApplyAnimation(playerid, "SKATE","skate_sprint",4.1,1,1,1,1,1,1);
    return 1;
}

forward FixAnimationPickupSkate(playerid);
public FixAnimationPickupSkate(playerid){
    ApplyAnimation(playerid, "CARRY", "liftup05", 4.1, 0, 0, 0, 0, 0, 1);
    return 1;
}