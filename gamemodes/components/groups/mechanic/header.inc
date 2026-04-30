#if defined _inc_header
	#undef _inc_header
#endif

new RepairTimer[MAX_PLAYERS];
new RefillTime[MAX_PLAYERS];
new MechanicRepairPoint[MAX_PLAYERS];
new RefillPoint[MAX_PLAYERS];
new StartRepair[MAX_PLAYERS];
new StartRefill[MAX_PLAYERS];

#define MAX_CARTUNE (50)

enum cartunedata{
    cartuneID,
    cartuneEx,
    Float:cartunePos[3],
    cartuneInt,
    cartuneWorld,
    STREAMER_TAG_3D_TEXT_LABEL:cartuneText3D
};
new CarTuneData[MAX_CARTUNE][cartunedata], count_cartune;