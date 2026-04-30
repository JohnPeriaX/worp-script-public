#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_PLAYER_SAFE        (108)

enum playersafeData{
    itemID,
    itemModel,
    itemName[64],
    itemOwner,
    itemQuantity,
    itemLevel,
    itemAmmo,
    Float:itemWeight,
    itemSlot
};
new PlayerSafeData[MAX_PLAYERS][MAX_PLAYER_SAFE][playersafeData];