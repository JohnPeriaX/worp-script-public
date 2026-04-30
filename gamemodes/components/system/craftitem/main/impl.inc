#if defined _inc_impl
	#undef _inc_impl
#endif

void:ResetPlayerCrafting(playerid){
	playerOpenCraftingMenu[playerid] = false;
	playerOpenCraftingCategory[playerid] = false;
	playerOpenCraftingItem[playerid] = false;
	playerOpenCraftingDetailItem[playerid] = false;
	playerGetCraftingType[playerid] = -1;
	playerSelectCategoryID[playerid] = -1;
	CraftingItem_Couting[playerid] = 0;
	playerCraftingPages[playerid] = 1;
	playerCraftingMaxPages[playerid] = 1;
	playerCraftingCurrentPages[playerid] = 1;

	playerClickCraftItemRows[playerid] = -1;
	playerClickCraftItemColumn[playerid] = -1;
	playerClickCraftItemGetID[playerid] = -1;
	playerCraftingItemAmount[playerid] = 1;
	playerStartCraftingItem[playerid] = false;
}

void:OnPlayerCreateCraftMenu(playerid, type){
	PlayerCreateCraftingTD(playerid, true);
	playerGetCraftingType[playerid] = type;
	PlayerCreateCraftingCategoryTD(playerid, true);
}

OP_StartCrafting(playerid){
	if(playerClickCraftItemRows[playerid] != -1 && playerClickCraftItemColumn[playerid] != -1 && playerClickCraftItemGetID[playerid] != -1){
		if(playerGetCraftingType[playerid] != -1 && playerSelectCategoryID[playerid] != -1){
			if(playerCraftingItemAmount[playerid] >= 1 && playerCraftingItemAmount[playerid] <= 50){
				new bool:checking[10] = false;

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] > 0){
					new itemamount = 0;
					if(( itemamount = PlayerInventory_AllCount(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName1])) < CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] * playerCraftingItemAmount[playerid]){
						SendClientMessageEx(playerid, COLOR_RED, "[!] คุณมีไอเท็ม '%s' ไม่เพียงพอ (ต้องการอีก %d)", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName1], (CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] * playerCraftingItemAmount[playerid]) - itemamount);
					} else checking[0] = true;
				} else checking[0] = true;
				
				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] > 0){
					new itemamount = 0;
					if(( itemamount = PlayerInventory_AllCount(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName2])) < CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] * playerCraftingItemAmount[playerid]){
						SendClientMessageEx(playerid, COLOR_RED, "[!] คุณมีไอเท็ม '%s' ไม่เพียงพอ (ต้องการอีก %d)", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName2], (CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] * playerCraftingItemAmount[playerid]) - itemamount);
					} else checking[1] = true;
				} else checking[1] = true;

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] > 0){
					new itemamount = 0;
					if(( itemamount = PlayerInventory_AllCount(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName3])) < CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] * playerCraftingItemAmount[playerid]){
						SendClientMessageEx(playerid, COLOR_RED, "[!] คุณมีไอเท็ม '%s' ไม่เพียงพอ (ต้องการอีก %d)", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName3], (CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] * playerCraftingItemAmount[playerid]) - itemamount);
					} else checking[2] = true;
				} else checking[2] = true;

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] > 0){
					new itemamount = 0;
					if(( itemamount = PlayerInventory_AllCount(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName4])) < CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] * playerCraftingItemAmount[playerid]){
						SendClientMessageEx(playerid, COLOR_RED, "[!] คุณมีไอเท็ม '%s' ไม่เพียงพอ (ต้องการอีก %d)", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName4], (CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] * playerCraftingItemAmount[playerid]) - itemamount);
					} else checking[3] = true;
				} else checking[3] = true;

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] > 0){
					new itemamount = 0;
					if(( itemamount = PlayerInventory_AllCount(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName5])) < CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] * playerCraftingItemAmount[playerid]){
						SendClientMessageEx(playerid, COLOR_RED, "[!] คุณมีไอเท็ม '%s' ไม่เพียงพอ (ต้องการอีก %d)", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName5], (CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] * playerCraftingItemAmount[playerid]) - itemamount);
					} else checking[4] = true;
				} else checking[4] = true;
				
				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] > 0){
					new itemamount = 0;
					if(( itemamount = PlayerInventory_AllCount(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName6])) < CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] * playerCraftingItemAmount[playerid]){
						SendClientMessageEx(playerid, COLOR_RED, "[!] คุณมีไอเท็ม '%s' ไม่เพียงพอ (ต้องการอีก %d)", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName6], (CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] * playerCraftingItemAmount[playerid]) - itemamount);
					} else checking[5] = true;
				} else checking[5] = true;

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] > 0){
					new itemamount = 0;
					if(( itemamount = PlayerInventory_AllCount(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName7])) < CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] * playerCraftingItemAmount[playerid]){
						SendClientMessageEx(playerid, COLOR_RED, "[!] คุณมีไอเท็ม '%s' ไม่เพียงพอ (ต้องการอีก %d)", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName7], (CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] * playerCraftingItemAmount[playerid]) - itemamount);
					} else checking[6] = true;
				} else checking[6] = true;

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] > 0){
					new itemamount = 0;
					if(( itemamount = PlayerInventory_AllCount(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName8])) < CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] * playerCraftingItemAmount[playerid]){
						SendClientMessageEx(playerid, COLOR_RED, "[!] คุณมีไอเท็ม '%s' ไม่เพียงพอ (ต้องการอีก %d)", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName8], (CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] * playerCraftingItemAmount[playerid]) - itemamount);
					} else checking[7] = true;
				} else checking[7] = true;

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemGreenCash] > 0){
					if(GetMoney(playerid) < CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemGreenCash] * playerCraftingItemAmount[playerid]){
						SendClientMessageEx(playerid, COLOR_RED, "[!] คุณมีเงินเขียวไม่เพียงพอ (ต้องการอีก %s)", FormatNumber((CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemGreenCash] * playerCraftingItemAmount[playerid]) - GetMoney(playerid)));
					} else checking[8] = true;
				} else checking[8] = true;

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRedCash] > 0){
					if(PlayerData[playerid][pRedMoney] < CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRedCash] * playerCraftingItemAmount[playerid]){
						SendClientMessageEx(playerid, COLOR_RED, "[!] คุณมีเงินแดงไม่เพียงพอ (ต้องการอีก %s)", FormatNumber((CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRedCash] * playerCraftingItemAmount[playerid]) - PlayerData[playerid][pRedMoney]));
					} else checking[9] = true;
				} else checking[9] = true;

				if(checking[0] && checking[1] && checking[2] && checking[3] && checking[4] && checking[5] && checking[6] && checking[7] && checking[8] && checking[9]){
					for(new i=0; i<MAX_CRAFTITEM_TD; i++) {
						if(IsPlayerTextDrawVisible(playerid, CraftingItemSlot[playerid][i])) PlayerTextDrawHide(playerid, CraftingItemSlot[playerid][i]);
					}
					for(new i=0;i <MAX_CRAFT_CATEGORY_TD; i++) {
						if(IsPlayerTextDrawVisible(playerid, CraftingCategoryTD[playerid][i])) PlayerTextDrawHide(playerid, CraftingCategoryTD[playerid][i]);
					}
					for(new i=0; i<MAX_CRAFTING_ITEM; i++){
						if(IsPlayerTextDrawVisible(playerid, CraftingItemModelTD[playerid][i])) PlayerTextDrawHide(playerid, CraftingItemModelTD[playerid][i]);
						if(IsPlayerTextDrawVisible(playerid, CraftingItemAmountTD[playerid][i])) PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][i]);
					}
					for(new i=0; i<MAX_CRAFT_TD; i++) {
						if(IsPlayerTextDrawVisible(playerid, CraftingTD[playerid][i])) PlayerTextDrawHide(playerid, CraftingTD[playerid][i]);
					}
					TogglePlayerControllable(playerid, 0);
					ClearAnimations(playerid);
					ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 1, 0, 1);
					playerStartCraftingItem[playerid] = true;
					OP_PlayerStartCircleProgressbar(playerid, 900, 0x0096FFFF, "OnPlayerCraftItemFinish");
					return true;
				}
			}
		}
	}
	return true;
}

forward OnPlayerCraftItemFinish(playerid);
public OnPlayerCraftItemFinish(playerid){
	new query[512];
	if(playerClickCraftItemRows[playerid] != -1 && playerClickCraftItemColumn[playerid] != -1 && playerClickCraftItemGetID[playerid] != -1){
		if(playerGetCraftingType[playerid] != -1 && playerSelectCategoryID[playerid] != -1){
			if(playerCraftingItemAmount[playerid] >= 1 && playerCraftingItemAmount[playerid] <= 50){
				new caption[1024];
				playerStartCraftingItem[playerid] = false;

				inline const _response(response, listitem, string:inputtext[]){
					#pragma unused listitem, inputtext
					if(!response || response) @return true;
				}

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] > 0){
					format(caption, sizeof caption, "{FF0000}%s[-] %s - %d ชิ้น\n", caption, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName1], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] * playerCraftingItemAmount[playerid]);
					PlayerInventory_Remove(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName1], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] * playerCraftingItemAmount[playerid]);
				}
				
				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] > 0){
					format(caption, sizeof caption, "%s[-] %s - %d ชิ้น\n", caption, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName2], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] * playerCraftingItemAmount[playerid]);
					PlayerInventory_Remove(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName2], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] * playerCraftingItemAmount[playerid]);
				}

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] > 0){
					format(caption, sizeof caption, "%s[-] %s - %d ชิ้น\n", caption, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName3], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] * playerCraftingItemAmount[playerid]);
					PlayerInventory_Remove(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName3], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] * playerCraftingItemAmount[playerid]);
				} 

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] > 0){
					format(caption, sizeof caption, "%s[-] %s - %d ชิ้น\n", caption, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName4], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] * playerCraftingItemAmount[playerid]);
					PlayerInventory_Remove(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName4], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] * playerCraftingItemAmount[playerid]);
				} 

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] > 0){
					format(caption, sizeof caption, "%s[-] %s - %d ชิ้น\n", caption, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName5], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] * playerCraftingItemAmount[playerid]);
					PlayerInventory_Remove(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName5], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] * playerCraftingItemAmount[playerid]);
				} 
				
				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] > 0){
					format(caption, sizeof caption, "%s[-] %s - %d ชิ้น\n", caption, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName6], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] * playerCraftingItemAmount[playerid]);
					PlayerInventory_Remove(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName6], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] * playerCraftingItemAmount[playerid]);
				}

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] > 0){
					format(caption, sizeof caption, "%s[-] %s - %d ชิ้น\n", caption, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName7], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] * playerCraftingItemAmount[playerid]);
					PlayerInventory_Remove(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName7], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] * playerCraftingItemAmount[playerid]);
				} 

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] > 0){
					format(caption, sizeof caption, "%s[-] %s - %d ชิ้น\n", caption, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName8], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] * playerCraftingItemAmount[playerid]);
					PlayerInventory_Remove(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName8], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] * playerCraftingItemAmount[playerid]);
				} 

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemGreenCash] > 0){
					format(caption, sizeof caption, "%s[-] เงินเขียว - %s\n", caption, FormatNumber(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemGreenCash] * playerCraftingItemAmount[playerid]));
					GiveMoney(playerid, -CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemGreenCash] * playerCraftingItemAmount[playerid], "Craft Item");
				}

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRedCash] > 0){
					format(caption, sizeof caption, "%s[-] เงินแดง - %s\n", caption, FormatNumber(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRedCash] * playerCraftingItemAmount[playerid]));
					PlayerData[playerid][pRedMoney] -= CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRedCash] * playerCraftingItemAmount[playerid];
				} 

				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRandomPercent] > 0){
					new rand = jdzrandom(1, 100), successitem = false;
					if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRandomPercent] == 10){
						if(rand >= 30 && rand <= 35){
							successitem = true;
						} 

						if(rand >= 60 && rand <= 65){
							successitem = true;
						}
					} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRandomPercent] == 20){
						if(rand >= 30 && rand <= 35){
							successitem = true;
						} 

						if(rand >= 60 && rand <= 65){
							successitem = true;
						}

						if(rand >= 80 && rand <= 85){
							successitem = true;
						}

						if(rand >= 10 && rand <= 15){
							successitem = true;
						}
					} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRandomPercent] == 30){
						if(rand >= 10 && rand <= 25){
							successitem = true;
						}

						if(rand >= 50 && rand <= 65){
							successitem = true;
						}
					} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRandomPercent] == 40){
						if(rand >= 20 && rand <= 30){
							successitem = true;
						}

						if(rand >= 50 && rand <= 60){
							successitem = true;
						}

						if(rand >= 80 && rand <= 90){
							successitem = true;
						}

						if(rand >= 30 && rand <= 40){
							successitem = true;
						}
					} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRandomPercent] == 50){
						if(rand >= 1 && rand <= 25){
							successitem = true;
						}

						if(rand >= 75 && rand <= 100){
							successitem = true;
						}
					} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRandomPercent] == 60){
						if(rand >= 1 && rand <= 30){
							successitem = true;
						}

						if(rand >= 60 && rand <= 90){
							successitem = true;
						}
					} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRandomPercent] == 70){
						if(rand >= 1 && rand <= 40){
							successitem = true;
						}

						if(rand >= 60 && rand <= 90){
							successitem = true;
						}
					} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRandomPercent] == 80){
						if(rand >= 1 && rand <= 40){
							successitem = true;
						}

						if(rand >= 60 && rand <= 100){
							successitem = true;
						}
					} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRandomPercent] == 90){
						if(rand >= 1 && rand <= 50){
							successitem = true;
						}

						if(rand >= 60 && rand <= 100){
							successitem = true;
						}
					} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRandomPercent] == 100){
						successitem = true;
					}

					if(successitem){
						new additem = PlayerInventory_AddItem(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemName], 
						CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemModel], 
						CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemAmount] * playerCraftingItemAmount[playerid], 0,
						CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemLevel]);

						if(additem != -1){
							format(caption, sizeof caption, "%s{3BD501}[สำเร็จ]\n", caption);
							format(caption, sizeof caption, "%s[+] %s + %d ชิ้น\n", caption, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemName], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemAmount] * playerCraftingItemAmount[playerid]);
						}

						format(query, sizeof query, "INSERT INTO `craftitem_logs` (`Username`, `Itemname`, `Itemamount`, `Date`, `Status`) VALUES ('%s', '%s', '%d', '%s', '%d')",
							ReturnName(playerid),
							CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemName],
							CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemAmount] * playerCraftingItemAmount[playerid],
							ReturnDate(),
							1
						);
						mysql_query(dbCon, query);
					} else {
						format(caption, sizeof caption, "%s{FF1B00}[ล้มเหลว]\n", caption);
						format(caption, sizeof caption, "%s[+] คุณไม่ได้รับอะไรจากการคราฟเลย\n", caption);

						format(query, sizeof query, "INSERT INTO `craftitem_logs` (`Username`, `Itemname`, `Itemamount`, `Date`, `Status`) VALUES ('%s', '%s', '%d', '%s', '%d')",
							ReturnName(playerid),
							CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemName],
							CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemAmount] * playerCraftingItemAmount[playerid],
							ReturnDate(),
							0
						);
						mysql_query(dbCon, query);
					}
					
				} else {
					new additem = PlayerInventory_AddItem(playerid, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemName], 
					CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemModel], 
					CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemAmount] * playerCraftingItemAmount[playerid], 0,
					CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemLevel]);

					if(additem != -1){
						format(caption, sizeof caption, "%s{3BD501}[สำเร็จ]\n", caption);
						format(caption, sizeof caption, "%s[+] %s + %d ชิ้น\n", caption, CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemName], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemAmount] * playerCraftingItemAmount[playerid]);
					}

					format(query, sizeof query, "INSERT INTO `craftitem_logs` (`Username`, `Itemname`, `Itemamount`, `Date`, `Status`) VALUES ('%s', '%s', '%d', '%s', '%d')",
						ReturnName(playerid),
						CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemName],
						CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemAmount] * playerCraftingItemAmount[playerid],
						ReturnDate(),
						1
					);
					mysql_query(dbCon, query);
				}

				Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_MSGBOX, "การคราฟไอเท็ม", caption, "ตกลง", "");

				new string[128];
				format(string, sizeof string, "%s", ReturnName(playerid));
				DCC_SendChannelMessage(CraftWeapon, string);

				TogglePlayerControllable(playerid, 1);
				ClearAnimations(playerid);
				PlayerCreateCraftingItemTD(playerid, false);
				PlayerCreateCraftingDTItemTD(playerid, false);
				PlayerCreateCraftingCategoryTD(playerid, false);
				PlayerCreateCraftingTD(playerid, false);
				ResetPlayerCrafting(playerid);
			}
		}
	}
	return true;
}