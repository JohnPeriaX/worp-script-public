#if defined _inc_header
	#undef _inc_header
#endif

new Float:RamdomPointGarden[][] = {
    {-311.1380,-1412.5828,14.0780},
    {-306.0603,-1412.2191,14.0556},
    {-306.7277,-1430.5201,14.8079},
    {-310.7137,-1431.0906,14.8983},
    {-316.3196,-1430.5078,14.9851},
    {-320.8799,-1431.4258,15.1376},
    {-326.8374,-1430.5083,15.21156},
    {-326.9503,-1425.4048,14.9118},
    {-321.3944,-1424.6932,14.7500},
    {-316.3799,-1424.7614,14.6473},
    {-310.7601,-1425.5027,14.607},
    {-306.7875,-1425.0343,14.5828},
    {-306.1305,-1419.2985,14.3464},
    {-310.3062,-1419.0256,14.3413},
    {-314.9456,-1418.8142,14.3394},
    {-320.5792,-1419.3387,14.4107},
    {-326.6099,-1418.3364,14.4877},
    {-326.7769,-1413.0699,14.1745},
    {-321.0756,-1412.4252,14.0861},
    {-315.1573,-1412.1215,14.0649}
};

#define MAX_POINTGARDENER (20)

new StartGardenerJob[MAX_PLAYERS];
new GardenerPoint[MAX_PLAYERS];
new GardenerCount[MAX_PLAYERS];
new CheckLastRamdomGardener[MAX_PLAYERS];
new CheckPlayerEnterPointGarden[MAX_PLAYERS];
new FinishGardener[MAX_PLAYERS];
new StartingWater[MAX_PLAYERS];

new GardenerTime[MAX_PLAYERS];