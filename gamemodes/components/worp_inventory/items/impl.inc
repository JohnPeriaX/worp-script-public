#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){

	for(new item=0; item<MAX_SERVER_ITEMS; item++){
		format(ServerItems[item][serveritemName], 64, "NULL");
		ServerItems[item][serveritemModel] = MODEL_NULL;
		ServerItems[item][serveritemWeight] = 0.00;
		format(ServerItems[item][serveritemDetail], 128, "NULL");
	}

	mysql_tquery(dbCon, "SELECT * FROM `serveritems`", "ServerItems_Load", "");
	return 1;
}

forward ServerItems_Load();
public ServerItems_Load(){
	new rows;
    cache_get_row_count(rows);
	for (new i=0; i < rows && i < MAX_SERVER_ITEMS; i++) {
		cache_get_value_name(i, "itemName", ServerItems[i][serveritemName], 64);
		cache_get_value_name_int(i, "itemModel", ServerItems[i][serveritemModel]);
		cache_get_value_name_float(i, "itemWeight", ServerItems[i][serveritemWeight]);
		cache_get_value_name(i, "itemDetail", ServerItems[i][serveritemDetail], 128);
		CountServerItem++;
	}
	Logger_Dbg(PLAYER_DEBUG_HANDLER, "[components/player_inventory/items_drop/impl : ServerItems_Load]",
		Logger_I("serverItemLoaded", CountServerItem)
	);
	return 1;
}