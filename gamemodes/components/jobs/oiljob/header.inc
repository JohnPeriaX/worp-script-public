#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_OILS (10)

enum oildata{
    oilID,
    oilStill,
    Float:oilPos[3],
    oilAmount,
    STREAMER_TAG_OBJECT:oilObject,
    oilUse,
    STREAMER_TAG_3D_TEXT_LABEL:oilText
};
new OilData[MAX_OILS][oildata];
new Oil_Count = 0;

new DrillPoint[MAX_PLAYERS];
new StartDrill[MAX_PLAYERS];
new DrillTime[MAX_PLAYERS];
new OilGetID[MAX_PLAYERS];
new StartProcessOil[MAX_PLAYERS];
new ProcessOilTime[MAX_PLAYERS];
new ProcessOilPoint[MAX_PLAYERS];