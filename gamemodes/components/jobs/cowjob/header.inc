#if defined _inc_header
	#undef _inc_header
#endif

#define SKIN_MALE   (161)
#define SKIN_FEMALE (157)

#define MAX_COWS (12)

new CheckPlayerChangeSkin[MAX_PLAYERS];
new CowJobTimer[MAX_PLAYERS];
new CowPoint[MAX_PLAYERS];
new PickingUpCow[MAX_PLAYERS];
new CowGetID[MAX_PLAYERS];
new PlayerUseKnife[MAX_PLAYERS];

new StartProcessMeat[MAX_PLAYERS];

enum cowdata{
    cowID,
    cowStill,
    Float:cowPos[4],
    Float:cowPosMove[3],
    STREAMER_TAG_OBJECT:cowObject,
    cowMove,
    cowMoving,
    cowDeath,
    Float:cowFixPos[4],
    cowPicking
}
new CowData[MAX_COWS][cowdata], Cow_Count;