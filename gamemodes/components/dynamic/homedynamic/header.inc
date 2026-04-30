#if defined _inc_header
	#undef _inc_header
#endif

#define     MAX_HOME                    (1000)
#define     MAX_HOME_PLAYERS            (1)
#define     USEWOOD                     (400)
#define     USEORE                      (300)
#define     MAX_HOUSE_STORAGE           (32)
#define     MAX_HOME_SLOTPAGE           (36)
#define     MAX_HOME_INV                (108)
#define     MAX_RENT_AMOUNT             (5)
#define     WORLD_HOME                  (5000)

enum homedata{
    homeID,
    homeEx,
    homeOwner,
    homeOwnerName[64],
    homeName[64],
    homePrice,
    Float:homeEnterPos[4],
    homeEnterInt,
    homeEnterWorld,
    Float:homeExitPos[4],
    homeExitInt,
    STREAMER_TAG_PICKUP:homePickup,
    homeBuild,
    homeLocked,
    homeMaxItem,
    homeItemAmount,
    homeRentAmount,
    homeNewInv,
    homeStorageUsing,
    homeResetInv,
    STREAMER_TAG_3D_TEXT_LABEL:homeText3D
};
new HomeData[MAX_HOME][homedata], count_home;

new GetHomeOwnerIndex[MAX_PLAYERS];

enum houseInteriors {
	eHouseInterior,
	Float:eHouseX,
	Float:eHouseY,
	Float:eHouseZ,
	Float:eHouseAngle
};

new const Float:arrHouseInteriors[20][houseInteriors] = {
	{10, 2269.8772, -1210.3240, 1047.5625, 90.0000},
    {2, 2468.2576, -1698.2361, 1013.5078, 90.0000},
	{3, 2495.8711, -1693.0996, 1014.7422, 180.0000},
	{5, 2233.7888, -1114.2689, 1050.8828, 0.0000},
	{9, 2317.8015, -1026.2113, 1050.2178, 0.0000},
	{3, 235.2923, 1187.3684, 1080.2578, 0.0000},
	{2, 226.2912, 1240.0554, 1082.1406, 90.0000},
	{1, 223.1618, 1287.5175, 1082.1406, 0.0000},
	{5, 226.9281, 1114.2813, 1080.9962, 270.0000},
	{15, 295.1485, 1473.1080, 1080.2578, 0.0000},
	{10, 23.9584, 1340.6075, 1084.3750, 0.0000},
	{4, 222.0425, 1140.7565, 1082.6094, 0.0000},
	{12, 2324.4209, -1148.9365, 1050.7101, 0.0000},
	{4, -261.1430, 1456.6396, 1084.3672, 90.0000},
	{5, 22.9676, 1403.8368, 1084.4297, 0.0000},
	{5, 140.3088, 1366.8196, 1083.8594, 0.0000},
	{6, 234.3149, 1064.2772, 1084.2114, 0.0000},
	{7, 225.7000, 1022.0012, 1084.0161, 0.0000},
	{5, 1298.9750, -796.4567, 1084.0078, 0.0000},
	{15, -283.8687, 1471.1174, 1084.3750, 90.0000}
};

enum houseStorage {
	hItemID,
	hItemExists,
	hItemName[64],
	hItemModel,
	hItemQuantity,
    hItemAmmo,
    hItemLevel,
    hItemSlot
};
new HouseStorage[MAX_HOME][MAX_HOME_INV][houseStorage];