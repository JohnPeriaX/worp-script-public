#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_DONATEITEM (1000)
enum donateitemdata{
    donateitemID,
    donateitemEx,
    donateitemName[32],
    donateitemModel,
    donateitemInfo[64],
    donateitemPrice
};
new DonateItemData[MAX_DONATEITEM][donateitemdata], Count_DonateItem;

new PlayerGetAmountBuyDonate[MAX_PLAYERS];