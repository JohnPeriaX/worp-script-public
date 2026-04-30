#if defined _inc_header
	#undef _inc_header
#endif

new PlayerText:PizzaTextDraw[MAX_PLAYERS][22];
new PlayerBar:PizzaProgressBar[MAX_PLAYERS][1];

new PlayerOpenPizzaMenu[MAX_PLAYERS];
new CowmeatAmount[MAX_PLAYERS], CowmeatMax[MAX_PLAYERS];
new TomatoAmount[MAX_PLAYERS], TomatoMax[MAX_PLAYERS];
new TomatoSaiceAmount[MAX_PLAYERS], TomatoSaiceMax[MAX_PLAYERS];
new MayonnaiseSaiceAmount[MAX_PLAYERS], MayonnaiseSaiceMax[MAX_PLAYERS];
new PizzaBakedTime[MAX_PLAYERS];
new PizzaBakedPoint[MAX_PLAYERS];
new StartBakedPizza[MAX_PLAYERS];