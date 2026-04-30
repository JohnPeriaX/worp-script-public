#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_AIR_DROPS (10)

enum AIR_BOX_DATA{
    Float:AirDropPos[3],
    AirDropInt,
    AirDropWorld,
    ObjectBox,
    ObjectFlash,
    Text3D:TextAirDrop,
    AirDropCoolDown,
    AirDropState[64],
    AirDropPlayerGet,
    AirDropMaxTime,
    AirDropItemName1[64],
    AirDropItemName2[64],
    AirDropItemName3[64],
    AirDropItemModel[3],
    AirDropItemAmount[3]
};
new AirDropData[MAX_AIR_DROPS][AIR_BOX_DATA];
new Iterator:Iter_Airdrop<MAX_AIR_DROPS>;
new PlayerIsCheckpointAirDrop[MAX_PLAYERS];
new PlayerCarryAirDrop[MAX_PLAYERS];

new PlayerTrackAirDropPlayerID[MAX_PLAYERS];
new PlayerGetTrackAirDropList[MAX_PLAYERS][MAX_AIR_DROPS];
new PlayerGetAirDropList[MAX_PLAYERS][MAX_AIR_DROPS];
new PlayerStartTimeAirDrop[MAX_PLAYERS];

new PlayerGetModelRewardAirDrop[MAX_PLAYERS];

new PlayerText:AirDropTimeTextDraw[MAX_PLAYERS][1];
new PlayerText:ModelItemAirDrop[MAX_PLAYERS][8];