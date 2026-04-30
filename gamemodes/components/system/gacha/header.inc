#if defined _inc_header
	#undef _inc_header
#endif

#define GACHA_NORMAL (0xC2C2C2AA)
#define GACHA_RANK1  (0x009BFFAA)
#define GACHA_RARE   (0xFFA200AA)

new PlayerText:GaCha[MAX_PLAYERS][14];
new GaChaColor[MAX_PLAYERS][14];

new IsOpeningGaCha[MAX_PLAYERS];
new GaChaTime[MAX_PLAYERS];
new GaChaPoint[MAX_PLAYERS];
new GetLastColor[MAX_PLAYERS];
new GaChaMaxPoint[MAX_PLAYERS];
new GetLastItem[MAX_PLAYERS];
new GetValueItem[MAX_PLAYERS];
new GetValueItemAmount[MAX_PLAYERS];
new GetValueItemLevel[MAX_PLAYERS];
new GetLastItemAmount[MAX_PLAYERS];
new GetLastItemLevel[MAX_PLAYERS];

#define MAX_GACHA (100)

enum gachaboxdata{
    gachaID,
    gachaEx,
    gachaType,
    gachaItem[7],
    gachaItemAmount[7],
    gachaItemLevel[7]
};
new GaChaData[MAX_GACHA][gachaboxdata], Count_GaCha;
new GaChaGetItem[MAX_PLAYERS][14];
new GaChaGetItemAmount[MAX_PLAYERS][14];
new GaChaGetItemLevel[MAX_PLAYERS][14];