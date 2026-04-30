#if defined _inc_header
	#undef _inc_header
#endif

new Float:AccessoryData[MAX_PLAYERS][4][9];

#define MAX_MOVEOBJECT_TEXT (23)

new PlayerText:MoveObjectTextDraw[MAX_PLAYERS][MAX_MOVEOBJECT_TEXT];

new PlayerEditingObject[MAX_PLAYERS];
new PlayerEditObjectSlot[MAX_PLAYERS];
new PlayerEditObjectType[MAX_PLAYERS];

new PlayerOpenAccessoryMenu[MAX_PLAYERS];