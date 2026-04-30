#if defined _inc_header
	#undef _inc_header
#endif

enum serverdata{
    serverID,
    Float:ServerNewbiePosLS[4],
    Float:ServerNewbiePosSF[4],
    Float:ServerNewbiePosLV[4],
    ServerCanAttack,
    ServerCanHoldGangZone,
    ServerExp,
    ServerTax,
    ServerUseWeapon,
    ServerCanGiveMoney,
    ServerCanGiveWeapon,
    ServerCanDropItem,
    ServerCanStoreHome,
    ServerSkillGang,
    ServerCanTrade,
    ServerCanTradeSpecial,
    ServerCanWdWeaponGang,
    ServerWeaponGangNotItem,
    ServerLocked,
    ServerPassword[64],
    ServerWarCityTime
};
new ServerData[serverdata];
