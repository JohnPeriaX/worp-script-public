#if defined _inc_header
	#undef _inc_header
#endif

#define InventoryAlert(%0,%1) \
    SendClientMessageEx(%0, COLOR_RED, "[Alert]:{FFFFFF} "%1)

#define InventoryHint(%0,%1) \
    SendClientMessageEx(%0, COLOR_SERVER, "[Inventory]:{FFFFFF} "%1)
    
#define CommandHintInventory(%0,%1) \
    SendClientMessageEx(%0, COLOR_SERVER, "[Commands]:{FFFFFF} "%1)

#define CommandFailInventory(%0,%1) \
    SendClientMessageEx(%0, COLOR_RED, "[Wrong]:{FFFFFF} "%1)

#define INVENTORY_DEFAULT (1)
#define INVENTORY_SAFE    (2)

#define INVENTORY_POSITION_LEFT (-150)
#define INVENTORY_POSITION_RIGHT (150)