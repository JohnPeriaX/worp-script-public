#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_SAFEZONES 500

enum safezoneData {
	safezoneID,
	safezoneExists,
	Float:safezonePos[3],
	safezoneInterior,
	safezoneWorld,
	STREAMER_TAG_3D_TEXT_LABEL:safezoneText3D,
	STREAMER_TAG_PICKUP:safezonePickup,
	safezoneRadius,
	safezoneType
};

new SafeZoneData[MAX_SAFEZONES][safezoneData],Total_Safezones_Created;