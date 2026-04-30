#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_GANGZONE (50)

#define MAX_TIMEATTACK (600)

enum zonedata{
    zoneID,
    zoneEx,
    Float:zonePos[4],
    zoneOwner,
    zoneAttack,
    zoneLeaderAttack,
    zoneAttackTime,
    zoneDelay,
    zoneArea,
    zoneTimer,
    zoneTimerDelay
};
new GangZoneData[MAX_GANGZONE][zonedata], Count_Zone;