#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_RUBBERTREE (20)
enum rubbertreedata{
    rubberID,
    rubberEx,
    Float:rubberPos[3],
    rubberInt,
    rubberWorld,
    rubberHealth,
    STREAMER_TAG_OBJECT:rubberObject,
    STREAMER_TAG_3D_TEXT_LABEL:rubberText3D
};
new RubberData[MAX_RUBBERTREE][rubbertreedata], Count_Rubber;

new PlayerGetToolRubber[MAX_PLAYERS];
new PlayerText:RubberTextDraw[MAX_PLAYERS][1];
new PlayerBar:RubberProgressBar[MAX_PLAYERS][1];
new RubberPoint[MAX_PLAYERS];
new RubberStarting[MAX_PLAYERS];
new RubberTime[MAX_PLAYERS];
new RubberProcessPoint[MAX_PLAYERS];
new RubberProcessTime[MAX_PLAYERS];