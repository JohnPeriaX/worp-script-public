#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_ARRESTS (50)
#define MAX_ROADBLOCKS 	(85)

enum arrestdata{
    arrestID,
    arrestEx,
    Float:arrestPos[3],
    arrestInt,
    arrestWorld,
    arrestPickup,
    STREAMER_TAG_3D_TEXT_LABEL:arrestText3D
};
new ArrestData[MAX_ARRESTS][arrestdata], count_arrest;

//RoadBlock
enum rInfo
{
    sCreated,
    Float:sX,
    Float:sY,
    Float:sZ,
    sObject,
};
new Roadblocks[MAX_ROADBLOCKS][rInfo];

new GetPlayerPrisonID[MAX_PLAYERS];
new GetPlayerSuspectID[MAX_PLAYERS];
new GetPlayerFriskID[MAX_PLAYERS];

new PoliceGetSupID[MAX_PLAYERS];

new LastShotgunWeapon[MAX_PLAYERS];
new LastShotgunAmmo[MAX_PLAYERS];