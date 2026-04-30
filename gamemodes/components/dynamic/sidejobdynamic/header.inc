#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_SIDEJOB (50)

enum sidejobdata{
    sidejobID,
    sidejobExists,
    sidejobType,
    sidejobName[32],
    Float:sidejobPos[3],
    Float:sidejobPoint[3],
    sidejobWorld,
    sidejobInt,
    sidejobPointWorld,
    sidejobPointInt,
    STREAMER_TAG_PICKUP:sidejobPickup[2],
    STREAMER_TAG_3D_TEXT_LABEL:sidejobText3D[2]
};
new SideJobData[MAX_SIDEJOB][sidejobdata], Sidejob_Count;