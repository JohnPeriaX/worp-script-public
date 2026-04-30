#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_ORANGE  (15)
#define CARRY_ORANGE_SLOT (9)


enum orangedata{
    orangeID,
    orangeEx,
    Float:orangePos[3],
    orangeHealth,
    orangePlayerUse,
    STREAMER_TAG_3D_TEXT_LABEL:orangeText3D
};
new OrangeData[MAX_ORANGE][orangedata];

new PlayerIsCarryCrate[MAX_PLAYERS];
new Player_GetID_Orange[MAX_PLAYERS];
new Player_Orange_Time[MAX_PLAYERS];
new Player_Orange_Point[MAX_PLAYERS];
new Player_Orange_InCrate[MAX_PLAYERS];
new Player_Orange_StartChecking[MAX_PLAYERS];