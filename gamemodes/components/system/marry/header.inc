#if defined _inc_header
	#undef _inc_header
#endif

#define TEXTMARRY (12)
new PlayerText:MarryText[MAX_PLAYERS][TEXTMARRY];
new PlayerBar:MarryBar[MAX_PLAYERS][1];

new MarryID[MAX_PLAYERS];
new OnPlayerShowMarryCard[MAX_PLAYERS];