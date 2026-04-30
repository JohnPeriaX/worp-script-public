#if defined _inc_header
	#undef _inc_header
#endif

new Jdz_Hunger_Bar_Show[MAX_PLAYERS];
new PlayerText:Jdz_Hunger_Bar[MAX_PLAYERS][3];
new Float:Jdz_Hunger_Bar_ValueX[MAX_PLAYERS];
new Float:Jdz_Hunger_Bar_ValueY[MAX_PLAYERS];
new Float:Jdz_Hunger_Bar_PositionX[MAX_PLAYERS];
new Float:Jdz_Hunger_Bar_PositionY[MAX_PLAYERS];

new Jdz_Water_Bar_Show[MAX_PLAYERS];
new PlayerText:Jdz_Water_Bar[MAX_PLAYERS][3];
new Float:Jdz_Water_Bar_ValueX[MAX_PLAYERS];
new Float:Jdz_Water_Bar_ValueY[MAX_PLAYERS];
new Float:Jdz_Water_Bar_PositionX[MAX_PLAYERS];
new Float:Jdz_Water_Bar_PositionY[MAX_PLAYERS];

new Jdz_Stamina_Bar_Show[MAX_PLAYERS];
new PlayerText:Jdz_Stamina_Bar[MAX_PLAYERS][3];
new Float:Jdz_Stamina_Bar_ValueX[MAX_PLAYERS];
new Float:Jdz_Stamina_Bar_ValueY[MAX_PLAYERS];
new Float:Jdz_Stamina_Bar_PositionX[MAX_PLAYERS];
new Float:Jdz_Stamina_Bar_PositionY[MAX_PLAYERS];

new Jdz_Shower_Bar_Show[MAX_PLAYERS];
new PlayerText:Jdz_Shower_Bar[MAX_PLAYERS][3];
new Float:Jdz_Shower_Bar_ValueX[MAX_PLAYERS];
new Float:Jdz_Shower_Bar_ValueY[MAX_PLAYERS];
new Float:Jdz_Shower_Bar_PositionX[MAX_PLAYERS];
new Float:Jdz_Shower_Bar_PositionY[MAX_PLAYERS];

new Jdz_Stress_Bar_Show[MAX_PLAYERS];
new PlayerText:Jdz_Stress_Bar[MAX_PLAYERS][3];
new Float:Jdz_Stress_Bar_ValueX[MAX_PLAYERS];
new Float:Jdz_Stress_Bar_ValueY[MAX_PLAYERS];
new Float:Jdz_Stress_Bar_PositionX[MAX_PLAYERS];
new Float:Jdz_Stress_Bar_PositionY[MAX_PLAYERS];

new PlayerText:Exp_Hud[MAX_PLAYERS][3];
new Jdz_Exp_Show[MAX_PLAYERS];