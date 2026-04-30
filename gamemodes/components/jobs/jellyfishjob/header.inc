#if defined _inc_header
	#undef _inc_header
#endif

//1602 jellyfish
#define MAX_JELLYFISH (30)
enum jellyfishdata{
    jellyfishID,
    jellyfishEx,
    Float:jellyfishPos[3],
    jellyfishInt,
    jellyfishWorld,
    jellyfishStill,
    jellyfishPicking,
    jellyfishDelay,
    STREAMER_TAG_OBJECT:jellyfishObject,
    STREAMER_TAG_3D_TEXT_LABEL:jellyfishText3D
};
new JellyFishData[MAX_JELLYFISH][jellyfishdata], count_jellyfish;

new JellyFishPoint[MAX_PLAYERS];
new JellyFishTimer[MAX_PLAYERS];
new JellyFishStartPickup[MAX_PLAYERS];

new WearLifeVest[MAX_PLAYERS];