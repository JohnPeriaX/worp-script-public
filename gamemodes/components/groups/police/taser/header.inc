#if defined _inc_header
	#undef _inc_header
#endif

#define TASER_WEAPON 		(23)
#define TASER_OBJECT        (347)
#define TASER_EFFECT_TIME	(10000)
#define TASER_USE_TIME		(5000)

new GiveTaserAgainTimer[MAX_PLAYERS];
new GiveTaserAgainTimerEx[MAX_PLAYERS];
new lastWeapon[MAX_PLAYERS];
new PoliceLastWeapon[MAX_PLAYERS];
new PoliceLastAmmo[MAX_PLAYERS];
new bool:taser[MAX_PLAYERS];
new TaserTime[MAX_PLAYERS];
new TaserTimeAG[MAX_PLAYERS];
new IsPlayerTaser[MAX_PLAYERS];
new TaserShoot[MAX_PLAYERS];