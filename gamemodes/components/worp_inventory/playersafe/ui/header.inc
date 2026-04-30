#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_PLAYERSAFE_TD 			(50)

//UI
new PlayerText:Player_Safe_TextDraw[MAX_PLAYERS][MAX_PLAYERSAFE_TD];
new PlayerSafeTextDrawShow[MAX_PLAYERS];