#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_RACINGTEXTDRAW  (16)
#define OWNER_ROOM          (1)
#define PLAYER_ROOM         (2)

#define INFERNUS_MODEL            (411)
#define SULTAN_MODEL              (560)
#define RACER_MODEL               (494)
#define KART_MODEL                (571)

new PlayerText:RacingPlayerTextDraw[MAX_PLAYERS][MAX_RACINGTEXTDRAW];
new bool:PlayerEnterRacing[MAX_PLAYERS];
new PlayerGetDuel[MAX_PLAYERS];
new bool:PlayerRacingReady[MAX_PLAYERS];
new PlayerRacingTypeInRoom[MAX_PLAYERS];
new PlayerRacingModelCar[MAX_PLAYERS];
new PlayerRacingTimeStart[MAX_PLAYERS];
new PlayerRacingStartTimeCount[MAX_PLAYERS];
new PlayerRacingCar[MAX_PLAYERS];
new PlayerRacingStarted[MAX_PLAYERS];
new PlayerRacingRacePoint[MAX_PLAYERS];

new Float:PlayerRacingGetPlayerPos[MAX_PLAYERS][3];
new PlayerRacingGetInterior[MAX_PLAYERS];
new PlayerRacingGetWorld[MAX_PLAYERS];

enum playercoderoom{
    RacingCodeRoom[64]
};
new PlayerRacing[MAX_PLAYERS][playercoderoom];

#define MODEL_CAESIZE (4)
new Model_Car[MODEL_CAESIZE] = {INFERNUS_MODEL, SULTAN_MODEL, RACER_MODEL, KART_MODEL};
new Model_CarName[MODEL_CAESIZE][64] = {"Infernus", "Sultan", "Hotring Racer", "Kart"};