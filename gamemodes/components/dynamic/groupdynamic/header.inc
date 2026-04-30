#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_GROUPS (100)
enum groupdata{
    groupID,
    groupExists,
    groupName[64],
    groupType,
    groupColor,
    groupRanks,
    Float:groupLockerPos[3],
    groupLockerInt,
    groupLockerWorld,
    Float:groupLocker2Pos[3],
    groupLocker2Int,
    groupLocker2World,
    Float:groupLocker3Pos[3],
    groupLocker3Int,
    groupLocker3World,
	groupWeapons[10],
	groupAmmo[10],
    groupSkin[8],
    STREAMER_TAG_PICKUP:groupLockerPickup[3],
    STREAMER_TAG_3D_TEXT_LABEL:groupLockerText3D[3],
	groupMoney,
	groupHoldZonePoint,
	groupSkills[5],
    groupWood,
    groupPowder,
    groupOre,
    groupRedMoney,
    groupKill
};
new GroupData[MAX_GROUPS][groupdata], Group_Count;
new GroupRanks[MAX_GROUPS][16][32];