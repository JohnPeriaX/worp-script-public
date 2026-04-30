#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_ATM_MACHINES (50)

enum atmData {
	atmID,
	atmExists,
	Float:atmPos[4],
	atmInterior,
	atmWorld,
	STREAMER_TAG_OBJECT:atmObject,
	STREAMER_TAG_3D_TEXT_LABEL:atmText3D
};
new ATMData[MAX_ATM_MACHINES][atmData],Total_Atms_Created;

new EditATM[MAX_PLAYERS];