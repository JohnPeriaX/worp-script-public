#if defined _inc_header
	#undef _inc_header
#endif

#define     MAX_BIZS        (100)
#define     MAX_TYPE_BIZS   (2)
#define     WORLD_BIZ       (9000)

#define     MAX_ITEMS_BIZ   (5)

enum biz_data{
    bizID,
    bizOwner,
    bizOwnerName[64],
    bizType,
    Float:bizPosEnter[4],
    Float:bizPosExit[4],
    bizInfo[64],
    bizPrice,
    bool:bizLocked,
    bizIntEnter,
    bizWorldEnter,
    bizIntExit,
    bizWorldExit,
    bizPickupEnter,
    bizPickupExit,
    bizAreaEnter,
    bizAreaExit,
    bizTotalMoney,
    bizUrlMp3[128],
    bizBarDJ,
    bizEnterPrice,
    Float:bizSelling[3],
    bizSellingInt,
    bizSellingWorld,
    Text3D:bizSellingText3D,
    bizItems[5],
    bizItemsAmount[5],
    bizItemsPrice[5]
};
new Biz_Data[MAX_BIZS][biz_data];
new Iterator:Iter_Biz<MAX_BIZS>;

new nearBiz_var[MAX_PLAYERS];

new PlayerGetItemIndexBiz[MAX_PLAYERS][20];

enum playergetitemdata{
    ItemIndexBiz,
    ItemNameBiz[64],
    ItemKeyBiz,
    ItemAmountBiz,
    ItemPriceBiz
};
new ItemBiz[MAX_PLAYERS][playergetitemdata];