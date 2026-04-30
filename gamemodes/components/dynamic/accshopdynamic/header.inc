#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_ACSHOP (50)
enum accShop{
    accShopID,
    accShopEx,
    Float:accShopPos[3],
    accShopInt,
    accShopWorld,
    accShopCheckPoint,
    STREAMER_TAG_3D_TEXT_LABEL:accShopText
};
new AccDataShop[MAX_ACSHOP][accShop];

new AccShopCount = 0;

#define MODEL_BUY_HAT (9)
#define MODEL_BUY_GLASSES (8)
#define MODEL_BUY_BODY (7)
#define MODEL_BUY_HANDS (6)