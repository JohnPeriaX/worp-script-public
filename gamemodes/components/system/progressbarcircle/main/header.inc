#if defined _inc_header
	#undef _inc_header
#endif

new Timer:playerProgressingCircle[MAX_PLAYERS];
new playerCountingTextDrawCircle[MAX_PLAYERS];
new playerCountTimeCircle[MAX_PLAYERS];
new playerCircleProgressColor[MAX_PLAYERS];
new playerCircleProgressCallback[MAX_PLAYERS][32];