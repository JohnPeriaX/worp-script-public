#if defined _inc_header
	#undef _inc_header
#endif

enum coreVehicles {
	vehRespawn,
	vehTemporary,
	vehSirenOn,
	vehURL[128 char],
	Float:vehLoadHealth,
 	Float:vehLoadPos[3],
	vehGas,
	vehCloth,
	vehJunk,
	vehNeonStatus,
	vehNeonColor
};
new CoreVehicles[MAX_VEH][coreVehicles];

new STREAMER_TAG_OBJECT:NeonVehicle[MAX_VEH][4];

enum carData {
	carID,
	carHave,
	carModel,
	carOwner,
	Float:carPos[4],
	carColor1,
	carColor2,
	carPaintjob,
	carLocked,
	carMods[14],
	carGroup,
	carJob,
	carWeapons[5],
	carAmmo[5],
	carVehicle,
	carFuel,
	carLock,
	carInsurance,
	carDamage[4],
	Float:carHealth,
	carDestroyed,
	carGPS,
	carPlate[32],
	carInsideGarage,
	carRealSiren,
	carNeonStatus,
	carNeonColor,
	carDrivingLicense
};

new CarData[MAX_DYNAMIC_CARS][carData], Total_Car;

new vehiclecallsign[MAX_VEH];
new Text3D:vehicle3Dtext[MAX_VEH];

new fuel_interval[MAX_VEH];

new GetCarIDDestroy[MAX_PLAYERS][MAX_OWNABLE_CARS];
new GetCarIDDestroyConfirm[MAX_PLAYERS];

new TrackerTime[MAX_PLAYERS];
new TrackerPoint[MAX_PLAYERS];
new GetCarIDTracker[MAX_PLAYERS][MAX_OWNABLE_CARS];