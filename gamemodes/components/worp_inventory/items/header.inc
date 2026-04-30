#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_SERVER_ITEMS (100)

enum serveritems{
	serveritemName[64],
	serveritemModel,
	Float:serveritemWeight,
	serveritemDetail[128]
}
new ServerItems[MAX_SERVER_ITEMS][serveritems];
new CountServerItem = 0;