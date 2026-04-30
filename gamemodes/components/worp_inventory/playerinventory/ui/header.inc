#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_PLAYERINV_TD 			(50)
#define MAX_PLAYERINV_SLOT_TD 		(150)
#define MAX_INV_SLOT_ROWS 			(6)
#define MAX_INV_SLOT_COLUMN			(6)

//UI
new PlayerText:Player_Inventory_TextDraw[MAX_PLAYERS][MAX_PLAYERINV_TD];
new PlayerBar:PlayerInventoryWeightBar[MAX_PLAYERS];

//SLOT
new PlayerText:Player_Inventory_Slot_TD[MAX_PLAYERS][MAX_PLAYERINV_SLOT_TD];
new Player_Inventory_Model[MAX_PLAYERS][MAX_INV_SLOT_ROWS][MAX_INV_SLOT_COLUMN];
new Player_Inventory_Name[MAX_PLAYERS][MAX_INV_SLOT_ROWS][MAX_INV_SLOT_COLUMN];
new Player_Inventory_Amount[MAX_PLAYERS][MAX_INV_SLOT_ROWS][MAX_INV_SLOT_COLUMN];
new Player_Inventory_Couting_TD[MAX_PLAYERS];

new Player_Inventory_Select_Rows[MAX_PLAYERS], Player_Inventory_Select_Column[MAX_PLAYERS], Player_Inventory_Select_Index[MAX_PLAYERS];
new PlayerBlockSelectInventory[MAX_PLAYERS];
new PlayerInventoryTextDrawShow[MAX_PLAYERS];