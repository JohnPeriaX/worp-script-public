#if defined _inc_header
	#undef _inc_header
#endif

new PlayerText:CharSelect[MAX_PLAYERS][15];
new PlayerText:VehSpeedo[MAX_PLAYERS][16];
new PlayerBar:VehSpeedoBar[MAX_PLAYERS][2];
new Text:LogoServer[3];
new PlayerText:CraftDrug[MAX_PLAYERS][7];
new PlayerBar:CraftDrugProgress[MAX_PLAYERS][1];

new PlayerText:TextDrawJobTypeTwo[MAX_PLAYERS][1];
new PlayerBar:ProgressBarJobTypeTwo[MAX_PLAYERS][1];

new PlayerText:ScreenTextDraw[MAX_PLAYERS][5];

new Text:RestartServer;
