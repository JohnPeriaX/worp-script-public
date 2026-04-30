#if defined _inc_header
	#undef _inc_header
#endif

#define max_upgradetextdraw (17)
#define max_upgradetextdrawsuc (12)

new PlayerText:UpgradeWeapon_TextDraw[MAX_PLAYERS][max_upgradetextdraw];
new PlayerBar:UpgradeWeapon_Bar[MAX_PLAYERS][1];

new PlayerText:UpgradeWeapon_TextDrawSuc[MAX_PLAYERS][max_upgradetextdrawsuc];

#define PRICE_UPGRADEWEAPON (50000)

#define MAX_UPGRADEWEAPON (10)
enum upgradeweapon_data{
    upgradeweaponID,
    upgradeweaponEx,
    Float:upgradeweaponPos[3],
    upgradeweaponInt,
    upgradeweaponWorld,
    STREAMER_TAG_3D_TEXT_LABEL:upgradeweaponText,
    upgradeweaponPickup
};
new UpgradeWeaponData[MAX_UPGRADEWEAPON][upgradeweapon_data], Count_UpgradeWeapon;

enum weaponnamedata{
    weaponMainName[32],
    weaponSecondName[32]
};
new WeaponNameData[MAX_PLAYERS][weaponnamedata];

new PlayerUpgradeWeaponTimer[MAX_PLAYERS];

new Open_UpgradeMenu[MAX_PLAYERS];
new Open_UpgradeMenuFinish[MAX_PLAYERS];
new Can_CloseUpgradeFinish[MAX_PLAYERS];
new Weapon_MainModel[MAX_PLAYERS];
new Weapon_MainLevel[MAX_PLAYERS];
new Weapon_MainIndex[MAX_PLAYERS];
new Weapon_SecondIndex[MAX_PLAYERS];
new Weapon_UpgradeStats[MAX_PLAYERS];

new UpgradeWeapon_GetStatus[MAX_PLAYERS];

new Weapon_SecondModel[MAX_PLAYERS];

new PlayerStart_UpgradeWeapon[MAX_PLAYERS];
new PlayerUpgradeWeapon_Point[MAX_PLAYERS];

new UnBorkenCardIndex[MAX_PLAYERS];
new UnBorkenCardModel[MAX_PLAYERS];