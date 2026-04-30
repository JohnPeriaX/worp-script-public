#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_CAMP   (100)
#define MAX_CAMP_OBJECT (80)

new CampingZone;

enum campdata{
    campIsPlace,
    campOwnerID,
    campOwnerName[64],
    Float:campPos[4],
    campInt,
    campWorld,
    STREAMER_TAG_3D_TEXT_LABEL:campText3D
};
new CampData[MAX_CAMP][campdata], Count_Camp, CampDataObject[MAX_CAMP][MAX_CAMP_OBJECT];
new PlayerIsPlaceCamping[MAX_PLAYERS];
new PlayerCampingProcessTimer[MAX_PLAYERS];
new PlayerCampingProcessPoint[MAX_PLAYERS];
new PlayerUsingCamping[MAX_PLAYERS];