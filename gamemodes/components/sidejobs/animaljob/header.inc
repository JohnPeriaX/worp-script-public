#if defined _inc_header
	#undef _inc_header
#endif

#define COW_PRICE       (500)
#define MAX_NEWCOW      (16)
#define NEWCOW_OBJECT   (19833)

new STREAMER_TAG_OBJECT:CowObject_Vehicle[MAX_VEH];
new CarHas_CowObject[MAX_VEH];
new PlayerGetCowObject[MAX_PLAYERS];
new PlayerHarvestNewCow[MAX_PLAYERS];
new Timer:PlayerHarvestMilkCowTime[MAX_PLAYERS];
new PlayerGetCowMilk[MAX_PLAYERS];

enum newcowdata{
    newcowID,
    Float:newcowPos[4],
    newcowOwner,
    newcowOwnerName[64],
    newcowStill,
    newcowGrowth,
    newcowHungry,
    newcowActive,
    newcowRounds,
    newcowIsPicking,
    STREAMER_TAG_OBJECT:newcowObject,
    STREAMER_TAG_3D_TEXT_LABEL:newcow3DText
};
new NewCowData[MAX_NEWCOW][newcowdata];
new Iterator:Iter_NewCow<MAX_NEWCOW>;
