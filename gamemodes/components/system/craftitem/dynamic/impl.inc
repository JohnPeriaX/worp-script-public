#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
	for(new i=0; i<MAX_CRAFT_TYPE; i++){
		for(new j=0; j<MAX_CATEGORY_CRAFT; j++){
			format(CraftCategoryName[i][j], 64, "NULL");
			CraftCoutingItem[i][j] = 0;
		}
	}
	mysql_tquery(dbCon, "SELECT * FROM `crafts_category`", "Craft_Category_Load", "");

	for(new i=0; i<MAX_CRAFT_TYPE; i++){
		for(new j=0; j<MAX_CATEGORY_CRAFT; j++){
			for(new k=0; k<MAX_DYNAMIC_ITEMCRAFT; k++){
				CraftItemDynamic[i][j][k][craftItemID] = 0;
				CraftItemDynamic[i][j][k][craftItemModel] = MODEL_NULL;
				format(CraftItemDynamic[i][j][k][craftItemName], 64, "NULL");
				CraftItemDynamic[i][j][k][craftItemAmount] = 0;
				CraftItemDynamic[i][j][k][craftItemLevel] = 0;

				CraftItemDynamic[i][j][k][craftItemRandomPercent] = 0;

				CraftItemDynamic[i][j][k][craftItemDetailModel1] = MODEL_NULL;
				format(CraftItemDynamic[i][j][k][craftItemDetailName1], 64, "NULL");
				CraftItemDynamic[i][j][k][craftItemDetailAmount1] = 0;
				CraftItemDynamic[i][j][k][craftItemDetailModel2] = MODEL_NULL;
				format(CraftItemDynamic[i][j][k][craftItemDetailName2], 64, "NULL");
				CraftItemDynamic[i][j][k][craftItemDetailAmount2] = 0;
				CraftItemDynamic[i][j][k][craftItemDetailModel3] = MODEL_NULL;
				format(CraftItemDynamic[i][j][k][craftItemDetailName3], 64, "NULL");
				CraftItemDynamic[i][j][k][craftItemDetailAmount3] = 0;
				CraftItemDynamic[i][j][k][craftItemDetailModel4] = MODEL_NULL;
				format(CraftItemDynamic[i][j][k][craftItemDetailName4], 64, "NULL");
				CraftItemDynamic[i][j][k][craftItemDetailAmount4] = 0;
				CraftItemDynamic[i][j][k][craftItemDetailModel5] = MODEL_NULL;
				format(CraftItemDynamic[i][j][k][craftItemDetailName5], 64, "NULL");
				CraftItemDynamic[i][j][k][craftItemDetailAmount5] = 0;
				CraftItemDynamic[i][j][k][craftItemDetailModel6] = MODEL_NULL;
				format(CraftItemDynamic[i][j][k][craftItemDetailName6], 64, "NULL");
				CraftItemDynamic[i][j][k][craftItemDetailAmount6] = 0;
				CraftItemDynamic[i][j][k][craftItemDetailModel7] = MODEL_NULL;
				format(CraftItemDynamic[i][j][k][craftItemDetailName7], 64, "NULL");
				CraftItemDynamic[i][j][k][craftItemDetailAmount7] = 0;
				CraftItemDynamic[i][j][k][craftItemDetailModel8] = MODEL_NULL;
				format(CraftItemDynamic[i][j][k][craftItemDetailName8], 64, "NULL");
				CraftItemDynamic[i][j][k][craftItemDetailAmount8] = 0;

				CraftItemDynamic[i][j][k][craftItemGreenCash] = 0;
				CraftItemDynamic[i][j][k][craftItemRedCash] = 0;
			}
		}
	}
	mysql_tquery(dbCon, "SELECT * FROM `crafts_items`", "Craft_Items_Load", "");
	return true;
}

//OnPlayerCreateCraftMenu(playerid, CraftDynamic[craftid][craftType]);

forward Craft_Items_Load();
public Craft_Items_Load(){
	new rows, type, category[64], kk = 0, ii = 0, jj = 0;
	cache_get_row_count(rows);
	for(new k=0; k<rows && k<MAX_DYNAMIC_ITEMCRAFT; k++){
		cache_get_value_name_int(k, "craftItemType", type);
		for(new i=0; i<MAX_CRAFT_TYPE; i++) if(type == i){
			if(i > 0 && i != i-1) kk = 0;
			cache_get_value_name(k, "craftItemCategory", category, 64);
			for(new j=0; j<MAX_CATEGORY_CRAFT; j++){
				if(!strcmp(category, CraftCategoryName[i][j], true)){
					if(j > 0 && j != j-1) kk = 0;
					if(CraftCoutingItem[i][j] > 0 && ii != i && jj != j) kk = CraftCoutingItem[i][j];
					cache_get_value_name_int(k, "craftItemID", CraftItemDynamic[i][j][kk][craftItemID]);
					cache_get_value_name_int(k, "craftItemType", CraftItemDynamic[i][j][kk][craftItemType]);
					cache_get_value_name(k, "craftItemCategory", CraftItemDynamic[i][j][kk][craftItemCategoryName], 64);
					cache_get_value_name_int(k, "craftItemModel", CraftItemDynamic[i][j][kk][craftItemModel]);
					cache_get_value_name(k, "craftItemName", CraftItemDynamic[i][j][kk][craftItemName], 64);
					cache_get_value_name_int(k, "craftItemAmount", CraftItemDynamic[i][j][kk][craftItemAmount]);
					cache_get_value_name_int(k, "craftItemLevel", CraftItemDynamic[i][j][k][craftItemLevel]);
					cache_get_value_name_int(k, "craftItemRandomPercent", CraftItemDynamic[i][j][kk][craftItemRandomPercent]);

					cache_get_value_name_int(k, "craftItemDetailModel1", CraftItemDynamic[i][j][kk][craftItemDetailModel1]);
					cache_get_value_name(k, "craftItemDetailName1", CraftItemDynamic[i][j][kk][craftItemDetailName1], 64);
					cache_get_value_name_int(k, "craftItemDetailAmount1", CraftItemDynamic[i][j][kk][craftItemDetailAmount1]);
					cache_get_value_name_int(k, "craftItemDetailModel2", CraftItemDynamic[i][j][kk][craftItemDetailModel2]);
					cache_get_value_name(k, "craftItemDetailName2", CraftItemDynamic[i][j][kk][craftItemDetailName2], 64);
					cache_get_value_name_int(k, "craftItemDetailAmount2", CraftItemDynamic[i][j][kk][craftItemDetailAmount2]);
					cache_get_value_name_int(k, "craftItemDetailModel3", CraftItemDynamic[i][j][kk][craftItemDetailModel3]);
					cache_get_value_name(k, "craftItemDetailName3", CraftItemDynamic[i][j][kk][craftItemDetailName3], 64);
					cache_get_value_name_int(k, "craftItemDetailAmount3", CraftItemDynamic[i][j][kk][craftItemDetailAmount3]);
					cache_get_value_name_int(k, "craftItemDetailModel4", CraftItemDynamic[i][j][kk][craftItemDetailModel4]);
					cache_get_value_name(k, "craftItemDetailName4", CraftItemDynamic[i][j][kk][craftItemDetailName4], 64);
					cache_get_value_name_int(k, "craftItemDetailAmount4", CraftItemDynamic[i][j][kk][craftItemDetailAmount4]);
					cache_get_value_name_int(k, "craftItemDetailModel5", CraftItemDynamic[i][j][kk][craftItemDetailModel5]);
					cache_get_value_name(k, "craftItemDetailName5", CraftItemDynamic[i][j][kk][craftItemDetailName5], 64);
					cache_get_value_name_int(k, "craftItemDetailAmount5", CraftItemDynamic[i][j][kk][craftItemDetailAmount5]);
					cache_get_value_name_int(k, "craftItemDetailModel6", CraftItemDynamic[i][j][kk][craftItemDetailModel6]);
					cache_get_value_name(k, "craftItemDetailName6", CraftItemDynamic[i][j][kk][craftItemDetailName6], 64);
					cache_get_value_name_int(k, "craftItemDetailAmount6", CraftItemDynamic[i][j][kk][craftItemDetailAmount6]);
					cache_get_value_name_int(k, "craftItemDetailModel7", CraftItemDynamic[i][j][kk][craftItemDetailModel7]);
					cache_get_value_name(k, "craftItemDetailName7", CraftItemDynamic[i][j][kk][craftItemDetailName7], 64);
					cache_get_value_name_int(k, "craftItemDetailAmount7", CraftItemDynamic[i][j][kk][craftItemDetailAmount7]);
					cache_get_value_name_int(k, "craftItemDetailModel8", CraftItemDynamic[i][j][kk][craftItemDetailModel8]);
					cache_get_value_name(k, "craftItemDetailName8", CraftItemDynamic[i][j][kk][craftItemDetailName8], 64);
					cache_get_value_name_int(k, "craftItemDetailAmount8", CraftItemDynamic[i][j][kk][craftItemDetailAmount8]);

					cache_get_value_name_int(k, "craftItemGreenCash", CraftItemDynamic[i][j][kk][craftItemGreenCash]);
					cache_get_value_name_int(k, "craftItemRedCash", CraftItemDynamic[i][j][kk][craftItemRedCash]);
					printf("[i: %d] [j: %d] [k: %d] %s", i, j, kk, CraftItemDynamic[i][j][kk][craftItemName]);
					ii = i; jj = j;
					CraftCoutingItem[i][j]++;
					kk++;
				}
			}
		}
	}
    return true;
}

forward Craft_Category_Load();
public Craft_Category_Load(){
    new rows, str[32];
    cache_get_row_count(rows);
    for (new i = 0; i < rows; i ++) if (i < MAX_CRAFT_TYPE){
		for(new j=0; j<MAX_CATEGORY_CRAFT; j++){
			format(str, sizeof(str), "craftGategoryName%d", j + 1);
			cache_get_value_name(i, str, CraftCategoryName[i][j], 32);
			printf("[i: %d] [j: %d] %s", i, j, CraftCategoryName[i][j]);
		}
	}
    return true;
}

CMD:recraft(playerid, params[]){
	if(LoggedIn[playerid] && PlayerData[playerid][pAdmin] >= 1337){
		for(new i=0; i<MAX_CRAFT_TYPE; i++){
			for(new j=0; j<MAX_CATEGORY_CRAFT; j++){
				format(CraftCategoryName[i][j], 64, "NULL");
				CraftCoutingItem[i][j] = 0;
			}
		}

		for(new i=0; i<MAX_CRAFT_TYPE; i++){
			for(new j=0; j<MAX_CATEGORY_CRAFT; j++){
				for(new k=0; k<MAX_DYNAMIC_ITEMCRAFT; k++){
					CraftItemDynamic[i][j][k][craftItemID] = 0;
					CraftItemDynamic[i][j][k][craftItemModel] = MODEL_NULL;
					format(CraftItemDynamic[i][j][k][craftItemName], 64, "NULL");
					CraftItemDynamic[i][j][k][craftItemAmount] = 0;
					CraftItemDynamic[i][j][k][craftItemLevel] = 0;

					CraftItemDynamic[i][j][k][craftItemRandomPercent] = 0;

					CraftItemDynamic[i][j][k][craftItemDetailModel1] = MODEL_NULL;
					format(CraftItemDynamic[i][j][k][craftItemDetailName1], 64, "NULL");
					CraftItemDynamic[i][j][k][craftItemDetailAmount1] = 0;
					CraftItemDynamic[i][j][k][craftItemDetailModel2] = MODEL_NULL;
					format(CraftItemDynamic[i][j][k][craftItemDetailName2], 64, "NULL");
					CraftItemDynamic[i][j][k][craftItemDetailAmount2] = 0;
					CraftItemDynamic[i][j][k][craftItemDetailModel3] = MODEL_NULL;
					format(CraftItemDynamic[i][j][k][craftItemDetailName3], 64, "NULL");
					CraftItemDynamic[i][j][k][craftItemDetailAmount3] = 0;
					CraftItemDynamic[i][j][k][craftItemDetailModel4] = MODEL_NULL;
					format(CraftItemDynamic[i][j][k][craftItemDetailName4], 64, "NULL");
					CraftItemDynamic[i][j][k][craftItemDetailAmount4] = 0;
					CraftItemDynamic[i][j][k][craftItemDetailModel5] = MODEL_NULL;
					format(CraftItemDynamic[i][j][k][craftItemDetailName5], 64, "NULL");
					CraftItemDynamic[i][j][k][craftItemDetailAmount5] = 0;
					CraftItemDynamic[i][j][k][craftItemDetailModel6] = MODEL_NULL;
					format(CraftItemDynamic[i][j][k][craftItemDetailName6], 64, "NULL");
					CraftItemDynamic[i][j][k][craftItemDetailAmount6] = 0;
					CraftItemDynamic[i][j][k][craftItemDetailModel7] = MODEL_NULL;
					format(CraftItemDynamic[i][j][k][craftItemDetailName7], 64, "NULL");
					CraftItemDynamic[i][j][k][craftItemDetailAmount7] = 0;
					CraftItemDynamic[i][j][k][craftItemDetailModel8] = MODEL_NULL;
					format(CraftItemDynamic[i][j][k][craftItemDetailName8], 64, "NULL");
					CraftItemDynamic[i][j][k][craftItemDetailAmount8] = 0;

					CraftItemDynamic[i][j][k][craftItemGreenCash] = 0;
					CraftItemDynamic[i][j][k][craftItemRedCash] = 0;
				}
			}
		}
		
		mysql_tquery(dbCon, "SELECT * FROM `crafts_category`", "Craft_Category_Load", "");
		mysql_tquery(dbCon, "SELECT * FROM `crafts_items`", "Craft_Items_Load", "");

		SendClientMessage(playerid, -1, "Success");
	}
	return true;
}