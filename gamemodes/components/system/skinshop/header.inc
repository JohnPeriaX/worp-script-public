#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_SKINS (350)
enum skinmaledata{
    skinmaleID,
    skinmaleEx,
    skinmaleModel
};
new SkinMaleData[MAX_SKINS][skinmaledata], count_skinmale;

enum skinfemaledata{
    skinfemaleID,
    skinfemaleEx,
    skinfemaleModel
};
new SkinFeMaleData[MAX_SKINS][skinfemaledata], count_skinfemale;

new PlayerShowSkinShopMenu[MAX_PLAYERS];