#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_CARSELL (100)

enum carselldata{
    carsellID,
    carsellExists,
    carsellModel,
    carsellPriceType,
    carsellPrice,
    carsellVipLevel,
    carsellType
};
new CarSellData[MAX_CARSELL][carselldata], Carsell_Count;