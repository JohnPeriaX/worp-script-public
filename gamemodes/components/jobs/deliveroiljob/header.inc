#if defined _inc_header
	#undef _inc_header
#endif

new PlayerStartDeliverOil[MAX_PLAYERS];
new PlayerGetOilDeliver[MAX_PLAYERS];
new Timer:OilDeliverLoadTime[MAX_PLAYERS];
new PlayerCheckDeliverOilPoint[MAX_PLAYERS];
new PlayerGetPumpID[MAX_PLAYERS];