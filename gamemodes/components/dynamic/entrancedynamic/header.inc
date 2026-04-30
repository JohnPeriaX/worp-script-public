#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_ENTRANCES 500
#define MAX_PRODUCTS  200

#define WORLD_ENTRANCE (7000)

enum entranceData {
	entranceID,
	entranceExists,
	entranceName[32],
	entranceIcon,
	entranceLocked,
	Float:entrancePos[4],
	Float:entranceInt[4],
	entranceInterior,
	entranceExterior,
	entranceExteriorVW,
	entranceType,
	entranceCustom,
	entranceWorld,
	entranceForklift[7],
	STREAMER_TAG_3D_TEXT_LABEL:entranceText3D[2],
	STREAMER_TAG_PICKUP:entrancePickup[2],
	entranceMapIcon,
	entranceMessage[64],
	entranceFaction,
	entranceProducts,
	entranceTable1[4],
	entranceTable2[4],
	entranceTable3[4],
	entranceTable4[4]
};

new EntranceData[MAX_ENTRANCES][entranceData];
new Total_Entrances_Created;