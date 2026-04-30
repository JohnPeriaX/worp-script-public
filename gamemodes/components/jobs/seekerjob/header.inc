#if defined _inc_header
	#undef _inc_header
#endif

new PlayerText:TreasureTextDraw[MAX_PLAYERS][1];
new PlayerBar:TreasureProgress[MAX_PLAYERS][1];

#define MAX_TREASURE (10)
enum treasuredata{
    treasureID,
    treasureStill,
    Float:treasurePos[3],
    treasureInt,
    treasureWorld,
    STREAMER_TAG_PICKUP:treasurePickup
};
new TreasureData[MAX_TREASURE][treasuredata];

new GetToolAndClothSeeker[MAX_PLAYERS];
new OxygenSeeker[MAX_PLAYERS];
new StartingWashTreasure[MAX_PLAYERS];
new ProcessWashPoint[MAX_PLAYERS];

new CleanTreasureTime[MAX_PLAYERS];

new TimeOxygen[MAX_PLAYERS];