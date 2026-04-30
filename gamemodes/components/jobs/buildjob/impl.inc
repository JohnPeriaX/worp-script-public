#if defined _inc_impl
	#undef _inc_impl
#endif

ResetBuildJob(playerid){
    StartChangeSkinBuildJob[playerid] = 0;
    StartBuildJob[playerid] = 0;
    BuilddingGetID[playerid] = -1;
    return 1;
}