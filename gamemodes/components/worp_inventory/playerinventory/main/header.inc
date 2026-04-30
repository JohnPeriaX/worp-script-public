#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_PLAYER_INVENTORY        (108)

enum playerinventoryData{
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
new PlayerInventoryData[MAX_PLAYERS][MAX_PLAYER_INVENTORY][playerinventoryData];
new PlayerInventory_Page[MAX_PLAYERS];
new PlayerInventory_MoveItem[MAX_PLAYERS];
new PlayerInventory_Type[MAX_PLAYERS];