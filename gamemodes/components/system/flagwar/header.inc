#if defined _inc_header
	#undef _inc_header
#endif

new bool:WarFlagOpen;
new bool:PlayerGetFlag[MAX_PLAYERS];
new FlagPickup = -1, bool:FlagDrill = false;
new Float:GetPositionBeforeFlagWar[MAX_PLAYERS][4];
new GetIntBeforeFlagWar[MAX_PLAYERS];
new GetWorldBeforeFlagWar[MAX_PLAYERS];
new PlayerDelayFlagWar[MAX_PLAYERS];
new WarFlagTime;
new bool:WarFinish = false;