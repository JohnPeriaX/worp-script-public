#if defined _inc_header
	#undef _inc_header
#endif


enum damagedata {
	dExists,
	dSec,
	dShotType,
	dWeaponid,
	Float:dDamage,
	dArmour
};

#define MAX_DAMAGES 10

new DamageData[MAX_PLAYERS][MAX_DAMAGES][damagedata];

new STREAMER_TAG_3D_TEXT_LABEL:TextDrawBed[3];