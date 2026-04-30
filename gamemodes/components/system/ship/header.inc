#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_ROGERPLANT (5)

new Ship, ShipStep = 1, ShipMoving = false, ShipStop = false;

enum rogerPlant{
    rogerPlantStill,
    rogerPlantUsing,
    Float:rogerPlantPos[3],
    rogerPlantObject
};
new RogerPlant[MAX_ROGERPLANT][rogerPlant];

new PlayerHarvesrRogerPlant[MAX_PLAYERS];
new Timer:HarvestRogerPlantTime[MAX_PLAYERS];

LoadShipObject(){
    Ship = CreateDynamicObject(8493, 2281.021484, 517.242187, 15.994377, 0.000000, 0.000000, 89.900047, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(8614, 2292.794189, 522.570617, 2.474375, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    return 1;
}