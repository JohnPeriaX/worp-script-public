#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_GARAGE (50)

enum garagedata{
    garageID,
    garageExists,
    Float:garageGetCar[3],
    garageGetCarInt,
    garageGetCarWorld,
    Float:garageStoreCar[3],
    garageStoreCarInt,
    garageStoreCarWorld,
    STREAMER_TAG_PICKUP:garagePickup[2],
    garageMapIcon,
	garageType,
    STREAMER_TAG_3D_TEXT_LABEL:garageText3D[2]
};
new GarageData[MAX_GARAGE][garagedata], Garage_Count;