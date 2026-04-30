#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_DYNAMIC_ITEMCRAFT 	(100)

#define MAX_CRAFT_TYPE 		(4)

#define CRAFT_NORMAL 		(0)
#define CRAFT_WEAPON 		(1)
#define CRAFT_FOOD   		(2)
#define CRAFT_FASHION 		(3)

#define MAX_CATEGORY_CRAFT		(6)

enum craftItemCategory{
	craftItemID,
	craftItemType,
	craftItemCategoryName[64],
	craftItemModel,
	craftItemName[64],
	craftItemAmount,
	craftItemLevel,
	craftItemRandomPercent,
	craftItemDetailModel1,
	craftItemDetailName1[64],
	craftItemDetailAmount1,
	craftItemDetailModel2,
	craftItemDetailName2[64],
	craftItemDetailAmount2,
	craftItemDetailModel3,
	craftItemDetailName3[64],
	craftItemDetailAmount3,
	craftItemDetailModel4,
	craftItemDetailName4[64],
	craftItemDetailAmount4,
	craftItemDetailModel5,
	craftItemDetailName5[64],
	craftItemDetailAmount5,
	craftItemDetailModel6,
	craftItemDetailName6[64],
	craftItemDetailAmount6,
	craftItemDetailModel7,
	craftItemDetailName7[64],
	craftItemDetailAmount7,
	craftItemDetailModel8,
	craftItemDetailName8[64],
	craftItemDetailAmount8,
	craftItemGreenCash,
	craftItemRedCash
};
new CraftItemDynamic[MAX_CRAFT_TYPE][MAX_CATEGORY_CRAFT][MAX_DYNAMIC_ITEMCRAFT][craftItemCategory];

new CraftCategoryName[MAX_CRAFT_TYPE][MAX_CATEGORY_CRAFT][32];
new CraftCoutingItem[MAX_CRAFT_TYPE][MAX_CATEGORY_CRAFT];