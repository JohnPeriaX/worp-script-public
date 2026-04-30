#if defined _inc_header
	#undef _inc_header
#endif

enum boomboxData {
	boomboxPlaced,
	Float:boomboxPos[3],
	boomboxInterior,
	boomboxWorld,
	STREAMER_TAG_OBJECT:boomboxObject,
	boomboxURL[128 char],
	STREAMER_TAG_3D_TEXT_LABEL:boomboxText3D
};

new BoomboxData[MAX_PLAYERS][boomboxData];