#if defined _inc_header
	#undef _inc_header
#endif

#define     BANANA_OBJECT       (892)   
#define     PUMPKIN_OBJECT      (810)
#define     APPLE_OBJECT        (892)
#define     GREENAPPLE_OBJECT   (892)

#define     BANANATYPE          (1)
#define     PUMPKINTYPE         (2)
#define     APPLETYPE           (3)
#define     GREENAPPLETYPE      (4)

#define     MAX_PLANTS          (100)

new RandomPriceBanana, RandomPricePumpkin, RandomPriceApple, RandomPriceGreenApple;

enum plantData{
    plantID,
    plantType,
    Float:plantPos[3],
    plantOwner,
    plantOwnerName[64],
    plantWater,
    plantStill,
    plantActive,
    STREAMER_TAG_OBJECT:plantObject,
    STREAMER_TAG_3D_TEXT_LABEL:plant3DText
};
new PlantData[MAX_PLANTS][plantData];
new Iterator:Iter_Plant<MAX_PLANTS>;

new Player_GetWater[MAX_PLAYERS];
new Player_WaterCount[MAX_PLAYERS];
new Player_Watering[MAX_PLAYERS];
new Timer:PlayerWaterTime[MAX_PLAYERS];
new Player_HarvestPlant[MAX_PLAYERS];

new PlayerStartCraftFruitjuice[MAX_PLAYERS];