#if defined _inc_header
	#undef _inc_header
#endif

#define 	WAR_CITY_INT 	(14)

new Text3D:openWarText3D;
new bool:openWarLS = false, bool:openWarSF = false;
new gangHoldingWarLS = -1, gangHoldingWarSF = -1;
new gangHoldingWarLSBy = INVALID_PLAYER_ID, gangHoldingWarSFBy = INVALID_PLAYER_ID;
new gangHoldingWarLS_Time = 0, gangHoldingWarSF_Time = 0;
new PlayerEnterWarCity[MAX_PLAYERS];

new Float:PlayerLastPositionWarCity[MAX_PLAYERS][4];
new PlayerLastIntWarCity[MAX_PLAYERS], PlayerLastWorldWarCity[MAX_PLAYERS];
new PlayerDelayWarCity[MAX_PLAYERS], PlayerIsHoldingWarCity[MAX_PLAYERS];

new gangHoldLS = -1, gangHoldSF = -1;

new Float:PlayerSpawnPointWarCity[][] = {
	{-1464.6310,1555.9185,1052.5313,175.1059},
	{-1457.1248,1654.5236,1052.5313,173.1189},
	{-1349.6667,1633.7881,1052.5313,268.5117},
	{-1352.7114,1563.3103,1052.5313,181.1825}
};