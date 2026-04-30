#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_GAS_PUMPS 50
#define MAX_FUEL_GAS (5000)

enum pumpData {
	pumpID,
	pumpExists,
	Float:pumpPos[4],
	pumpFuel,
	pumpPrice,
	STREAMER_TAG_OBJECT:pumpObject,
	STREAMER_TAG_3D_TEXT_LABEL:pumpText3D
};

new PumpData[MAX_GAS_PUMPS][pumpData],Total_Pumps_Created;