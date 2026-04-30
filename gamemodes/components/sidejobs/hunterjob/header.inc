#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_DEERS (15)

enum deerinfo{
    deerEx,
    deerScared,
    deerIsDead,
    deerIsPickup,
    deerDeathTime,
    STREAMER_TAG_OBJECT:deerObject,
    deerTimer,
    Float:deerPos[4],
};

new DeerData[MAX_DEERS][deerinfo], Deer_Count;
new Deer_Price = 0;
new PlayerPickingupDeer[MAX_PLAYERS];