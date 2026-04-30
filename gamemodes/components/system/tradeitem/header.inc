#if defined _inc_header
	#undef _inc_header
#endif

#define     MAX_TRADETEXT       (74)
#define     MAX_ITEM_TRADE      (10)

new PlayerText:PlayerTDTradeItem[MAX_PLAYERS][MAX_TRADETEXT];
new PlayerTradingTargetID[MAX_PLAYERS];
new PlayerStateRoleTrade[MAX_PLAYERS];
new PlayerStateTrading[MAX_PLAYERS];
new PlayerTradeMoney[MAX_PLAYERS];
new PlayerSelectingItem[MAX_PLAYERS];
new PlayerConfirmTrade[MAX_PLAYERS];

enum itemtradedata{
    itemID,
    itemName[64],
    itemModel,
    itemQuantity,
    itemLevel,
    itemAmmo
};
new Trade_Item[MAX_PLAYERS][MAX_ITEM_TRADE][itemtradedata];