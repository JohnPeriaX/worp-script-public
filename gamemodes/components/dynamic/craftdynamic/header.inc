#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_CRAFT_DYNAMIC (50)

enum craftdata{
    craftID,
    craftExists,
    Float:craftPos[3],
    craftWorld,
    craftInt,
    craftType,
    STREAMER_TAG_PICKUP:craftPickup,
    STREAMER_TAG_3D_TEXT_LABEL:craftText3D
};
new CraftData[MAX_CRAFT_DYNAMIC][craftdata], Craft_Count;