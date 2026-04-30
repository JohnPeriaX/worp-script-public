#if defined _inc_impl
	#undef _inc_impl
#endif

forward PlayerInventoryUseItem(playerid, itemid);
public PlayerInventoryUseItem(playerid, itemid){
	if(itemid != -1){
		printf("[%s] Use Item [%s]", ReturnRoleplayName(playerid), PlayerInventoryData[playerid][itemid][itemName]);	
	}
	PlayerBlockSelectInventory[playerid] = false;
	return true;
}