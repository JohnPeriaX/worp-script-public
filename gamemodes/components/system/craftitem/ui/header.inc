#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_CRAFT_TD (24)
#define MAX_CRAFT_CATEGORY_TD (6)
#define MAX_CRAFTITEM_TD (50)

#define MAX_CRAFTITEM_ROWS 		(3)
#define MAX_CRAFTITEM_COLUMN 	(6)

#define MAX_CRAFTING_ITEM       (8)

new PlayerText:CraftingTD[MAX_PLAYERS][MAX_CRAFT_TD];
new PlayerText:CraftingCategoryTD[MAX_PLAYERS][MAX_CRAFT_CATEGORY_TD];

new PlayerText:CraftingItemSlot[MAX_PLAYERS][MAX_CRAFTITEM_TD];
new CraftingItemModel[MAX_PLAYERS][MAX_CRAFTITEM_ROWS][MAX_CRAFTITEM_COLUMN];
new CraftingItemAmount[MAX_PLAYERS][MAX_CRAFTITEM_ROWS][MAX_CRAFTITEM_COLUMN];
new CraftingItem_Couting[MAX_PLAYERS];

new PlayerText:CraftingItemModelTD[MAX_PLAYERS][MAX_CRAFTING_ITEM];
new PlayerText:CraftingItemAmountTD[MAX_PLAYERS][MAX_CRAFTING_ITEM];