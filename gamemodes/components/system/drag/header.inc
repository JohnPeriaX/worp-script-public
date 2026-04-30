#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_PLAYER_WARRANTS (50)

new playerIsDraging[MAX_PLAYERS];
new playerIsDraged[MAX_PLAYERS];
new playerGetDragID[MAX_PLAYERS];
new playerDragIdle[MAX_PLAYERS];

new Timer:playerDragTimer[MAX_PLAYERS];