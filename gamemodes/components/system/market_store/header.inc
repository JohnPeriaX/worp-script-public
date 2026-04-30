#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_MARKET_STORE_ITEM (50)

enum market_store{
    item_Have,
    item_Name[64],
    item_RealName[64],
    item_Model,
    item_Info[64],
    item_Price
};
new Market_Store[MAX_MARKET_STORE_ITEM][market_store];