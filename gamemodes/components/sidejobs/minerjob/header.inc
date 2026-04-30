#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_MINE  (15)
#define MINE_OBJ  (3930)

#define COPPER_PRICE      (5)
#define GOLDMINE_PRICE    (10)
#define DIAMOND_PRICE     (100)

#define DELAY_MINESPAWN   (120)

enum minedata{
    mineStill,
    Float:minePos[3],
    STREAMER_TAG_OBJECT:mineObject,
    mineUsed,
    mineDelay
};
new MineData[MAX_MINE][minedata];

new PlayerStartMine[MAX_PLAYERS];
new PlayerGetMineID[MAX_PLAYERS];

new PlayerStartProcessMine[MAX_PLAYERS];

new Timer:MineTime[MAX_PLAYERS];
new Timer:ProcessMineTime[MAX_PLAYERS];