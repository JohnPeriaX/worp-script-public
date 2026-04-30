#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_SHOWER (50)

enum showerData{
    showerID,
    Float:showerPos[3],
    showerInterior,
    showerWorld,
    STREAMER_TAG_3D_TEXT_LABEL:showerText3D,
	STREAMER_TAG_PICKUP:showerPickup
};
new ShowerData[MAX_SHOWER][showerData];
new Iterator:Iter_Shower<MAX_SHOWER>;

new Timer:PlayerShower[MAX_PLAYERS];
new PlayerStartShower[MAX_PLAYERS];