#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerClickTextDraw(playerid, Text:clickedid){
	if(LoggedIn[playerid]){
		if(clickedid == Text:INVALID_TEXT_DRAW){
			if(playerOpenCraftingCategory[playerid] && playerOpenCraftingMenu[playerid]){
				if(!playerStartCraftingItem[playerid]){
					PlayerCreateCraftingItemTD(playerid, false);
					PlayerCreateCraftingDTItemTD(playerid, false);
					PlayerCreateCraftingCategoryTD(playerid, false);
					PlayerCreateCraftingTD(playerid, false);
				}
				else {
					SelectTextDraw(playerid, 0x0096FFFF);
				}
				return true;	
			}
		}
	}
	return true;
}

hook OP_ClickPlayerTextDraw(playerid, PlayerText:playertextid){
	if(LoggedIn[playerid]){
		if(playerOpenCraftingMenu[playerid]){
			new string[128];
			if(playertextid == CraftingTD[playerid][4] && !playerStartCraftingItem[playerid]){
				PlayerCreateCraftingItemTD(playerid, false);
				PlayerCreateCraftingDTItemTD(playerid, false);
				PlayerCreateCraftingCategoryTD(playerid, false);
				PlayerCreateCraftingTD(playerid, false);
				return true;
			}

			if(playerSelectCategoryID[playerid] != -1){
				if(playertextid == CraftingTD[playerid][21]){ //เลื่อนขึ้น
					if(playerCraftingPages[playerid] > 1) {
						if(playerClickCraftItemRows[playerid] != -1 && playerClickCraftItemColumn[playerid] != -1 && playerClickCraftItemGetID[playerid] != -1){
							PlayerTextDrawBackgroundColor(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][playerClickCraftItemRows[playerid]][playerClickCraftItemColumn[playerid]]], 1296911741);
							playerClickCraftItemRows[playerid] = -1;
							playerClickCraftItemColumn[playerid] = -1;
							playerClickCraftItemGetID[playerid] = -1;
						}
						playerCraftingPages[playerid]--;
						OP_RenderCraftItemPage(playerid);
					}
				}

				if(playertextid == CraftingTD[playerid][23]){ //เลื่อนลง
					if(playerCraftingPages[playerid] < playerCraftingMaxPages[playerid]){
						if(playerClickCraftItemRows[playerid] != -1 && playerClickCraftItemColumn[playerid] != -1 && playerClickCraftItemGetID[playerid] != -1){
							PlayerTextDrawBackgroundColor(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][playerClickCraftItemRows[playerid]][playerClickCraftItemColumn[playerid]]], 1296911741);
							playerClickCraftItemRows[playerid] = -1;
							playerClickCraftItemColumn[playerid] = -1;
							playerClickCraftItemGetID[playerid] = -1;
						}
						playerCraftingPages[playerid]++;
						OP_RenderCraftItemPage(playerid);
					}
				}

				if(playertextid == CraftingTD[playerid][18]){ //เริ่มคราฟ
					if(playerClickCraftItemRows[playerid] != -1 && playerClickCraftItemColumn[playerid] != -1 && playerClickCraftItemGetID[playerid] != -1){
						if(playerGetCraftingType[playerid] != -1 && playerSelectCategoryID[playerid] != -1){
							if(playerCraftingItemAmount[playerid] >= 1 && playerCraftingItemAmount[playerid] <= 50){
								return OP_StartCrafting(playerid);
							}
						}
					}
				}

				if(playertextid == CraftingTD[playerid][11]){
					if(playerClickCraftItemRows[playerid] != -1 && playerClickCraftItemColumn[playerid] != -1 && playerClickCraftItemGetID[playerid] != -1){
						if(playerGetCraftingType[playerid] != -1 && playerSelectCategoryID[playerid] != -1){
							if(playerCraftingItemAmount[playerid] > 1){
								playerCraftingItemAmount[playerid]--;
								format(string, sizeof string, "%d", playerCraftingItemAmount[playerid]);
								PlayerTextDrawSetString(playerid, CraftingTD[playerid][12], string);

								format(string, sizeof string, "%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemAmount] * playerCraftingItemAmount[playerid]);
								PlayerTextDrawSetString(playerid, CraftingTD[playerid][10], string);
							
								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][0]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName1], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][0], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][0]);
								}
								
								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][1]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName2], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][1], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][1]);
								}

								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][2]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName3], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][2], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][2]);
								}	

								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][3]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName4], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][3], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][3]);
								}

								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][4]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName5], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][4], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][4]);
								}
								
								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][5]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName6], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][5], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][5]);
								}

								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][6]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName7], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][6], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][6]);
								}

								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][7]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName8], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][7], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][7]);
								}

								format(string, sizeof string, "%s", FormatNumber(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemGreenCash] * playerCraftingItemAmount[playerid]));
								PlayerTextDrawSetString(playerid, CraftingTD[playerid][15], string);
								format(string, sizeof string, "%s", FormatNumber(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRedCash] * playerCraftingItemAmount[playerid]));
								PlayerTextDrawSetString(playerid, CraftingTD[playerid][17], string);
							}
						}
					}
				}

				if(playertextid == CraftingTD[playerid][13]){
					if(playerClickCraftItemRows[playerid] != -1 && playerClickCraftItemColumn[playerid] != -1 && playerClickCraftItemGetID[playerid] != -1){
						if(playerGetCraftingType[playerid] != -1 && playerSelectCategoryID[playerid] != -1){
							if(playerCraftingItemAmount[playerid] < 50){
								playerCraftingItemAmount[playerid]++;
								format(string, sizeof string, "%d", playerCraftingItemAmount[playerid]);
								PlayerTextDrawSetString(playerid, CraftingTD[playerid][12], string);

								format(string, sizeof string, "%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemAmount] * playerCraftingItemAmount[playerid]);
								PlayerTextDrawSetString(playerid, CraftingTD[playerid][10], string);

								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][0]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName1], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][0], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][0]);
								}
								
								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][1]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName2], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][1], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][1]);
								}

								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][2]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName3], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][2], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][2]);
								}	

								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][3]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName4], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][3], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][3]);
								}

								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][4]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName5], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][4], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][4]);
								}
								
								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][5]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName6], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][5], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][5]);
								}

								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][6]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName7], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][6], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][6]);
								}

								if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] <= 0){
									PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][7]);
								} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] > 0){
									format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName8], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] * playerCraftingItemAmount[playerid]);
									PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][7], string);
									PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][7]);
								}

								format(string, sizeof string, "%s", FormatNumber(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemGreenCash] * playerCraftingItemAmount[playerid]));
								PlayerTextDrawSetString(playerid, CraftingTD[playerid][15], string);
								format(string, sizeof string, "%s", FormatNumber(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRedCash] * playerCraftingItemAmount[playerid]));
								PlayerTextDrawSetString(playerid, CraftingTD[playerid][17], string);
							}
						}
					}
				}
			}

			if(playerOpenCraftingCategory[playerid] && playerGetCraftingType[playerid] != -1){
				new index = 18 * (playerCraftingPages[playerid] - 1);
				for(new i=0; i<MAX_CRAFTITEM_ROWS; i++){
					for(new j=0; j<MAX_CRAFTITEM_COLUMN; j++){
						if(playertextid == CraftingItemSlot[playerid][CraftingItemModel[playerid][i][j]]){
							if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][index][craftItemModel] != MODEL_NULL){
								if(playerClickCraftItemRows[playerid] != -1 && playerClickCraftItemColumn[playerid] != -1 && playerClickCraftItemGetID[playerid] != -1){
									PlayerTextDrawBackgroundColor(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][playerClickCraftItemRows[playerid]][playerClickCraftItemColumn[playerid]]], 1296911741);
									PlayerTextDrawShow(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][playerClickCraftItemRows[playerid]][playerClickCraftItemColumn[playerid]]]);
								}

								playerClickCraftItemRows[playerid] = i;
								playerClickCraftItemColumn[playerid] = j;
								playerClickCraftItemGetID[playerid] = index;
								playerCraftingCurrentPages[playerid] = playerCraftingPages[playerid];
								PlayerTextDrawBackgroundColor(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][playerClickCraftItemRows[playerid]][playerClickCraftItemColumn[playerid]]], 0x0080DAFF);
								PlayerTextDrawShow(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][playerClickCraftItemRows[playerid]][playerClickCraftItemColumn[playerid]]]);
								playerCraftingItemAmount[playerid] = 1;
								format(string, sizeof string, "%d", playerCraftingItemAmount[playerid]);
								PlayerTextDrawSetString(playerid, CraftingTD[playerid][12], string);
								OP_RenderCraftItemDetail(playerid);
							}
						}
						index++;
					}
				}

				for(new i=0; i<MAX_CATEGORY_CRAFT; i++) if(strcmp(CraftCategoryName[playerGetCraftingType[playerid]][i], "NULL", true)){
					if(playertextid == CraftingCategoryTD[playerid][i]){
						
						if(playerClickCraftItemRows[playerid] != -1 && playerClickCraftItemColumn[playerid] != -1 && playerClickCraftItemGetID[playerid] != -1){
							PlayerTextDrawBackgroundColor(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][playerClickCraftItemRows[playerid]][playerClickCraftItemColumn[playerid]]], 1296911741);
							playerClickCraftItemRows[playerid] = -1;
							playerClickCraftItemColumn[playerid] = -1;
							playerClickCraftItemGetID[playerid] = -1;
						}

						if(playerSelectCategoryID[playerid] != -1){
							if(PlayerTextDrawGetBoxColor(playerid, CraftingCategoryTD[playerid][playerSelectCategoryID[playerid]]) == 0x0080DAFF){
								PlayerTextDrawBoxColor(playerid, CraftingCategoryTD[playerid][playerSelectCategoryID[playerid]], 1296911811);
								PlayerTextDrawShow(playerid, CraftingCategoryTD[playerid][playerSelectCategoryID[playerid]]);
								playerSelectCategoryID[playerid] = -1;
							}
						}

						PlayerTextDrawBoxColor(playerid, CraftingCategoryTD[playerid][i], 0x0080DAFF);
						PlayerTextDrawShow(playerid, CraftingCategoryTD[playerid][i]);

						for(new k=0; k<MAX_CRAFTING_ITEM; k++){
							if(IsPlayerTextDrawVisible(playerid, CraftingItemModelTD[playerid][k])){
								PlayerTextDrawHide(playerid, CraftingItemModelTD[playerid][k]);
							}

							if(IsPlayerTextDrawVisible(playerid, CraftingItemAmountTD[playerid][k])){
								PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][k]);
							}
						}

						for(new u=7; u<21; u++) PlayerTextDrawHide(playerid, CraftingTD[playerid][u]);

						playerSelectCategoryID[playerid] = i;
						playerCraftingItemAmount[playerid] = 1;
						OP_RenderCraftItemPage(playerid);
						return true;
					}
				}
			}
		}
	}
	return true;
}

OP_RenderCraftItemDetail(playerid){
	if(playerClickCraftItemRows[playerid] != -1 && playerClickCraftItemColumn[playerid] != -1 && playerClickCraftItemGetID[playerid] != -1){
		if(playerGetCraftingType[playerid] != -1 && playerSelectCategoryID[playerid] != -1){
			new string[128];
			format(string, sizeof string, "%s", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemName]);
			PlayerTextDrawSetString(playerid, CraftingTD[playerid][20], string);

			PlayerTextDrawSetPreviewModel(playerid, CraftingTD[playerid][9], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemModel]);
			format(string, sizeof string, "%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemAmount] * playerCraftingItemAmount[playerid]);
			PlayerTextDrawSetString(playerid, CraftingTD[playerid][10], string);


			if(!playerOpenCraftingDetailItem[playerid]) {
				PlayerCreateCraftingDTItemTD(playerid, true);
				OP_RenderCraftItemDetailLoad(playerid);
			}
			else {
				OP_RenderCraftItemDetailLoad(playerid);
			}

			for(new i=7; i<21; i++) PlayerTextDrawShow(playerid, CraftingTD[playerid][i]);
		}
	}
	return true;
}

OP_RenderCraftItemDetailLoad(playerid){
	if(playerGetCraftingType[playerid] != -1 && playerSelectCategoryID[playerid] != -1 && playerClickCraftItemGetID[playerid] != -1){
		if(playerOpenCraftingDetailItem[playerid]){
			new string[128];
			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel1] != MODEL_NULL){
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][0], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel1]);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][0], -10.000000, 0.000000, -20.000000, 1.000000);
				PlayerTextDrawShow(playerid, CraftingItemModelTD[playerid][0]);
			} else {
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][0], MODEL_NULL);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][0], 0.000000, 0.000000, 0.000000, 0.000000);
				PlayerTextDrawHide(playerid, CraftingItemModelTD[playerid][0]);
			}
			
			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel2] != MODEL_NULL){
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][1], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel2]);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][1], -10.000000, 0.000000, -20.000000, 1.000000);
				PlayerTextDrawShow(playerid, CraftingItemModelTD[playerid][1]);
			} else {
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][1], MODEL_NULL);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][1], 0.000000, 0.000000, 0.000000, 0.000000);
				PlayerTextDrawHide(playerid, CraftingItemModelTD[playerid][1]);
			}

			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel3] != MODEL_NULL){
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][2], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel3]);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][2], -10.000000, 0.000000, -20.000000, 1.000000);
				PlayerTextDrawShow(playerid, CraftingItemModelTD[playerid][2]);
			} else {
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][2], MODEL_NULL);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][2], 0.000000, 0.000000, 0.000000, 0.000000);
				PlayerTextDrawHide(playerid, CraftingItemModelTD[playerid][2]);
			}
			
			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel4] != MODEL_NULL){
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][3], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel4]);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][3], -10.000000, 0.000000, -20.000000, 1.000000);
				PlayerTextDrawShow(playerid, CraftingItemModelTD[playerid][3]);
			} else {
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][3], MODEL_NULL);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][3], 0.000000, 0.000000, 0.000000, 0.000000);
				PlayerTextDrawHide(playerid, CraftingItemModelTD[playerid][3]);
			}
			
			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel5] != MODEL_NULL){
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][4], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel5]);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][4], -10.000000, 0.000000, -20.000000, 1.000000);
				PlayerTextDrawShow(playerid, CraftingItemModelTD[playerid][4]);
			} else {
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][4], MODEL_NULL);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][4], 0.000000, 0.000000, 0.000000, 0.000000);
				PlayerTextDrawHide(playerid, CraftingItemModelTD[playerid][4]);
			}

			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel6] != MODEL_NULL){
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][5], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel6]);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][5], -10.000000, 0.000000, -20.000000, 1.000000);
				PlayerTextDrawShow(playerid, CraftingItemModelTD[playerid][5]);
			} else {
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][5], MODEL_NULL);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][5], 0.000000, 0.000000, 0.000000, 0.000000);
				PlayerTextDrawHide(playerid, CraftingItemModelTD[playerid][5]);
			}
			
			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel7] != MODEL_NULL){
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][6], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel7]);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][6], -10.000000, 0.000000, -20.000000, 1.000000);
				PlayerTextDrawShow(playerid, CraftingItemModelTD[playerid][6]);
			} else {
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][6], MODEL_NULL);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][6], 0.000000, 0.000000, 0.000000, 0.000000);
				PlayerTextDrawHide(playerid, CraftingItemModelTD[playerid][6]);
			}

			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel8] != MODEL_NULL){
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][7], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailModel8]);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][7], -10.000000, 0.000000, -20.000000, 1.000000);
				PlayerTextDrawShow(playerid, CraftingItemModelTD[playerid][7]);
			} else {
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][7], MODEL_NULL);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][7], 0.000000, 0.000000, 0.000000, 0.000000);
				PlayerTextDrawHide(playerid, CraftingItemModelTD[playerid][7]);
			}
		

			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] <= 0){
				PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][0]);
			} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] > 0){
				format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName1], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount1] * playerCraftingItemAmount[playerid]);
				PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][0], string);
				PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][0]);
			}
			
			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] <= 0){
				PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][1]);
			} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] > 0){
				format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName2], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount2] * playerCraftingItemAmount[playerid]);
				PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][1], string);
				PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][1]);
			}

			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] <= 0){
				PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][2]);
			} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] > 0){
				format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName3], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount3] * playerCraftingItemAmount[playerid]);
				PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][2], string);
				PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][2]);
			}	

			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] <= 0){
				PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][3]);
			} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] > 0){
				format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName4], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount4] * playerCraftingItemAmount[playerid]);
				PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][3], string);
				PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][3]);
			}

			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] <= 0){
				PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][4]);
			} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] > 0){
				format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName5], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount5] * playerCraftingItemAmount[playerid]);
				PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][4], string);
				PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][4]);
			}
			
			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] <= 0){
				PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][5]);
			} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] > 0){
				format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName6], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount6] * playerCraftingItemAmount[playerid]);
				PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][5], string);
				PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][5]);
			}

			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] <= 0){
				PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][6]);
			} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] > 0){
				format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName7], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount7] * playerCraftingItemAmount[playerid]);
				PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][6], string);
				PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][6]);
			}

			if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] <= 0){
				PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][7]);
			} else if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] > 0){
				format(string, sizeof string, "%s x%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailName8], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemDetailAmount8] * playerCraftingItemAmount[playerid]);
				PlayerTextDrawSetString(playerid, CraftingItemAmountTD[playerid][7], string);
				PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][7]);
			}

			format(string, sizeof string, "%s", FormatNumber(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemGreenCash] * playerCraftingItemAmount[playerid]));
			PlayerTextDrawSetString(playerid, CraftingTD[playerid][15], string);
			format(string, sizeof string, "%s", FormatNumber(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][playerClickCraftItemGetID[playerid]][craftItemRedCash] * playerCraftingItemAmount[playerid]));
			PlayerTextDrawSetString(playerid, CraftingTD[playerid][17], string);
		}
	}
	return true;
}

OP_RenderCraftItemPage(playerid){
	if(playerGetCraftingType[playerid] != -1 && playerSelectCategoryID[playerid] != -1){
		CraftingItem_Couting[playerid] = 0;
		if(!playerOpenCraftingItem[playerid]) PlayerCreateCraftingItemTD(playerid, true);
		playerCraftingMaxPages[playerid] = (CraftCoutingItem[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]] / 18) + 1;
		new index = 18 * (playerCraftingPages[playerid] - 1), string[128];
		for(new i=0; i<MAX_CRAFTITEM_ROWS; i++){
			for(new j=0; j<MAX_CRAFTITEM_COLUMN; j++){
				if(CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][index][craftItemModel] != MODEL_NULL){
					PlayerTextDrawSetPreviewModel(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][i][j]], CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][index][craftItemModel]);
					PlayerTextDrawSetPreviewRot(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][i][j]], -10.000000, 0.000000, -20.000000, 1.000000);
					PlayerTextDrawSetSelectable(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][i][j]], true);
					PlayerTextDrawShow(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][i][j]]);

					format(string, sizeof string, "%d", CraftItemDynamic[playerGetCraftingType[playerid]][playerSelectCategoryID[playerid]][index][craftItemAmount]);
					PlayerTextDrawSetString(playerid, CraftingItemSlot[playerid][CraftingItemAmount[playerid][i][j]], string);
					PlayerTextDrawShow(playerid, CraftingItemSlot[playerid][CraftingItemAmount[playerid][i][j]]);
				} else {
					PlayerTextDrawSetSelectable(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][i][j]], false);
					PlayerTextDrawHide(playerid, CraftingItemSlot[playerid][CraftingItemModel[playerid][i][j]]);
					PlayerTextDrawHide(playerid, CraftingItemSlot[playerid][CraftingItemAmount[playerid][i][j]]);
				}
				index++;
			}
		}

		format(string, sizeof string, "%d", playerCraftingPages[playerid]);
		PlayerTextDrawSetString(playerid, CraftingTD[playerid][22], string);

		for(new i=21; i<MAX_CRAFT_TD; i++){
			PlayerTextDrawShow(playerid, CraftingTD[playerid][i]);
		}
	}
	return true;
}

void:PlayerCreateCraftingItemTD(playerid, flag = true){
	if(!playerOpenCraftingItem[playerid] && flag) {
		new Float:modelX = 226.000000, Float:modelY = 148.000000;
		new Float:amountX = 262.000000, Float:amountY = 149.000000;

		for(new i=0; i<MAX_CRAFTITEM_ROWS; i++){
			for(new j=0; j<MAX_CRAFTITEM_COLUMN; j++){
				CraftingItemModel[playerid][i][j] = CraftingItem_Couting[playerid];
				CraftingItemSlot[playerid][CraftingItem_Couting[playerid]] = CreatePlayerTextDraw(playerid, modelX, modelY, "Preview_Model");
				PlayerTextDrawFont(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 5);
				PlayerTextDrawLetterSize(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 0.600000, 2.000000);
				PlayerTextDrawTextSize(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 38.000000, 41.000000);
				PlayerTextDrawSetOutline(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 0);
				PlayerTextDrawAlignment(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 1);
				PlayerTextDrawColor(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 1296911741);
				PlayerTextDrawBoxColor(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 255);
				PlayerTextDrawUseBox(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], false);
				PlayerTextDrawSetPreviewModel(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], MODEL_NULL);
				PlayerTextDrawSetPreviewRot(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 0.000000, 0.000000, 0.000000, 0.000000);
				// PlayerTextDrawSetPreviewRot(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], -10.000000, 0.000000, -20.000000, 1.000000);
				PlayerTextDrawSetPreviewVehCol(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]++], 1, 1);

				CraftingItemAmount[playerid][i][j] = CraftingItem_Couting[playerid];
				CraftingItemSlot[playerid][CraftingItem_Couting[playerid]] = CreatePlayerTextDraw(playerid, amountX, amountY, "1");
				PlayerTextDrawFont(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 2);
				PlayerTextDrawLetterSize(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 0.179166, 0.900000);
				PlayerTextDrawTextSize(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 400.000000, 17.000000);
				PlayerTextDrawSetOutline(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 0);
				PlayerTextDrawAlignment(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 3);
				PlayerTextDrawColor(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 255);
				PlayerTextDrawBoxColor(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 50);
				PlayerTextDrawUseBox(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, CraftingItemSlot[playerid][CraftingItem_Couting[playerid]++], 0);

				modelX += 44.00;
				amountX += 44.00;
			}	

			modelX = 226.000000;
			amountX = 262.000000;

			modelY += 47.00;
			amountY += 47.00;
		}

		playerOpenCraftingItem[playerid] = true;

	} else if(playerOpenCraftingItem[playerid] && !flag){
		for(new i=0; i<MAX_CRAFTITEM_TD; i++){
			if(IsPlayerTextDrawVisible(playerid, CraftingItemSlot[playerid][i])){
				PlayerTextDrawHide(playerid, CraftingItemSlot[playerid][i]);
			}

			PlayerTextDrawDestroy(playerid, CraftingItemSlot[playerid][i]);
		}
		CraftingItem_Couting[playerid] = 0;
		playerOpenCraftingItem[playerid] = false;
	}
}

void:PlayerCreateCraftingCategoryTD(playerid, flag = true){
	if(!playerOpenCraftingCategory[playerid] && flag){
		CraftingCategoryTD[playerid][0] = CreatePlayerTextDraw(playerid, 184.000000, 151.000000, "None");
		PlayerTextDrawFont(playerid, CraftingCategoryTD[playerid][0], 1);
		PlayerTextDrawLetterSize(playerid, CraftingCategoryTD[playerid][0], 0.216666, 1.400000);
		PlayerTextDrawTextSize(playerid, CraftingCategoryTD[playerid][0], 16.500000, 62.500000);
		PlayerTextDrawSetOutline(playerid, CraftingCategoryTD[playerid][0], 0);
		PlayerTextDrawSetShadow(playerid, CraftingCategoryTD[playerid][0], 0);
		PlayerTextDrawAlignment(playerid, CraftingCategoryTD[playerid][0], 2);
		PlayerTextDrawColor(playerid, CraftingCategoryTD[playerid][0], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingCategoryTD[playerid][0], 255);
		PlayerTextDrawBoxColor(playerid, CraftingCategoryTD[playerid][0], 1296911811);
		PlayerTextDrawUseBox(playerid, CraftingCategoryTD[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, CraftingCategoryTD[playerid][0], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingCategoryTD[playerid][0], 1);

		CraftingCategoryTD[playerid][1] = CreatePlayerTextDraw(playerid, 184.000000, 170.000000, "None");
		PlayerTextDrawFont(playerid, CraftingCategoryTD[playerid][1], 1);
		PlayerTextDrawLetterSize(playerid, CraftingCategoryTD[playerid][1], 0.216666, 1.400000);
		PlayerTextDrawTextSize(playerid, CraftingCategoryTD[playerid][1], 16.500000, 62.500000);
		PlayerTextDrawSetOutline(playerid, CraftingCategoryTD[playerid][1], 0);
		PlayerTextDrawSetShadow(playerid, CraftingCategoryTD[playerid][1], 0);
		PlayerTextDrawAlignment(playerid, CraftingCategoryTD[playerid][1], 2);
		PlayerTextDrawColor(playerid, CraftingCategoryTD[playerid][1], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingCategoryTD[playerid][1], 255);
		PlayerTextDrawBoxColor(playerid, CraftingCategoryTD[playerid][1], 1296911811);
		PlayerTextDrawUseBox(playerid, CraftingCategoryTD[playerid][1], 1);
		PlayerTextDrawSetProportional(playerid, CraftingCategoryTD[playerid][1], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingCategoryTD[playerid][1], 1);

		CraftingCategoryTD[playerid][2] = CreatePlayerTextDraw(playerid, 184.000000, 189.000000, "None");
		PlayerTextDrawFont(playerid, CraftingCategoryTD[playerid][2], 1);
		PlayerTextDrawLetterSize(playerid, CraftingCategoryTD[playerid][2], 0.216666, 1.400000);
		PlayerTextDrawTextSize(playerid, CraftingCategoryTD[playerid][2], 16.500000, 62.500000);
		PlayerTextDrawSetOutline(playerid, CraftingCategoryTD[playerid][2], 0);
		PlayerTextDrawSetShadow(playerid, CraftingCategoryTD[playerid][2], 0);
		PlayerTextDrawAlignment(playerid, CraftingCategoryTD[playerid][2], 2);
		PlayerTextDrawColor(playerid, CraftingCategoryTD[playerid][2], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingCategoryTD[playerid][2], 255);
		PlayerTextDrawBoxColor(playerid, CraftingCategoryTD[playerid][2], 1296911811);
		PlayerTextDrawUseBox(playerid, CraftingCategoryTD[playerid][2], 1);
		PlayerTextDrawSetProportional(playerid, CraftingCategoryTD[playerid][2], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingCategoryTD[playerid][2], 1);

		CraftingCategoryTD[playerid][3] = CreatePlayerTextDraw(playerid, 184.000000, 208.000000, "None");
		PlayerTextDrawFont(playerid, CraftingCategoryTD[playerid][3], 1);
		PlayerTextDrawLetterSize(playerid, CraftingCategoryTD[playerid][3], 0.216666, 1.400000);
		PlayerTextDrawTextSize(playerid, CraftingCategoryTD[playerid][3], 16.500000, 62.500000);
		PlayerTextDrawSetOutline(playerid, CraftingCategoryTD[playerid][3], 0);
		PlayerTextDrawSetShadow(playerid, CraftingCategoryTD[playerid][3], 0);
		PlayerTextDrawAlignment(playerid, CraftingCategoryTD[playerid][3], 2);
		PlayerTextDrawColor(playerid, CraftingCategoryTD[playerid][3], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingCategoryTD[playerid][3], 255);
		PlayerTextDrawBoxColor(playerid, CraftingCategoryTD[playerid][3], 1296911811);
		PlayerTextDrawUseBox(playerid, CraftingCategoryTD[playerid][3], 1);
		PlayerTextDrawSetProportional(playerid, CraftingCategoryTD[playerid][3], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingCategoryTD[playerid][3], 1);

		CraftingCategoryTD[playerid][4] = CreatePlayerTextDraw(playerid, 184.000000, 227.000000, "None");
		PlayerTextDrawFont(playerid, CraftingCategoryTD[playerid][4], 1);
		PlayerTextDrawLetterSize(playerid, CraftingCategoryTD[playerid][4], 0.216666, 1.400000);
		PlayerTextDrawTextSize(playerid, CraftingCategoryTD[playerid][4], 16.500000, 62.500000);
		PlayerTextDrawSetOutline(playerid, CraftingCategoryTD[playerid][4], 0);
		PlayerTextDrawSetShadow(playerid, CraftingCategoryTD[playerid][4], 0);
		PlayerTextDrawAlignment(playerid, CraftingCategoryTD[playerid][4], 2);
		PlayerTextDrawColor(playerid, CraftingCategoryTD[playerid][4], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingCategoryTD[playerid][4], 255);
		PlayerTextDrawBoxColor(playerid, CraftingCategoryTD[playerid][4], 1296911811);
		PlayerTextDrawUseBox(playerid, CraftingCategoryTD[playerid][4], 1);
		PlayerTextDrawSetProportional(playerid, CraftingCategoryTD[playerid][4], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingCategoryTD[playerid][4], 1);

		CraftingCategoryTD[playerid][5] = CreatePlayerTextDraw(playerid, 184.000000, 246.000000, "None");
		PlayerTextDrawFont(playerid, CraftingCategoryTD[playerid][5], 1);
		PlayerTextDrawLetterSize(playerid, CraftingCategoryTD[playerid][5], 0.216666, 1.400000);
		PlayerTextDrawTextSize(playerid, CraftingCategoryTD[playerid][5], 16.500000, 62.500000);
		PlayerTextDrawSetOutline(playerid, CraftingCategoryTD[playerid][5], 0);
		PlayerTextDrawSetShadow(playerid, CraftingCategoryTD[playerid][5], 0);
		PlayerTextDrawAlignment(playerid, CraftingCategoryTD[playerid][5], 2);
		PlayerTextDrawColor(playerid, CraftingCategoryTD[playerid][5], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingCategoryTD[playerid][5], 255);
		PlayerTextDrawBoxColor(playerid, CraftingCategoryTD[playerid][5], 1296911811);
		PlayerTextDrawUseBox(playerid, CraftingCategoryTD[playerid][5], 1);
		PlayerTextDrawSetProportional(playerid, CraftingCategoryTD[playerid][5], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingCategoryTD[playerid][5], 1);

		if(playerGetCraftingType[playerid] != -1){
			for(new i=0; i<MAX_CRAFT_CATEGORY_TD; i++) if(strcmp(CraftCategoryName[playerGetCraftingType[playerid]][i], "NULL", true)){
				PlayerTextDrawShow(playerid, CraftingCategoryTD[playerid][i]);
			}

			playerOpenCraftingCategory[playerid] = true;

			new type = playerGetCraftingType[playerid];
			for(new i=0; i<MAX_CATEGORY_CRAFT; i++){
				if(strcmp(CraftCategoryName[type][i], "NULL", true)){
					PlayerTextDrawSetString(playerid, CraftingCategoryTD[playerid][i], CraftCategoryName[type][i]);
				}
			}
		}
	} else if(playerOpenCraftingCategory[playerid] && !flag){
		for(new i=0;i <MAX_CRAFT_CATEGORY_TD; i++){
			if(IsPlayerTextDrawVisible(playerid, CraftingCategoryTD[playerid][i])){
				PlayerTextDrawHide(playerid, CraftingCategoryTD[playerid][i]);
			}

			PlayerTextDrawDestroy(playerid, CraftingCategoryTD[playerid][i]);
		}

		playerOpenCraftingCategory[playerid] = false;
		playerGetCraftingType[playerid] = -1;
	}
}

void:PlayerCreateCraftingDTItemTD(playerid, flag = true){
	if(!playerOpenCraftingDetailItem[playerid] && flag){
		CraftingItemModelTD[playerid][0] = CreatePlayerTextDraw(playerid, 222.000000, 309.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, CraftingItemModelTD[playerid][0], 5);
		PlayerTextDrawLetterSize(playerid, CraftingItemModelTD[playerid][0], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingItemModelTD[playerid][0], 15.500000, 18.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemModelTD[playerid][0], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemModelTD[playerid][0], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemModelTD[playerid][0], 1);
		PlayerTextDrawColor(playerid, CraftingItemModelTD[playerid][0], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemModelTD[playerid][0], 1296911616);
		PlayerTextDrawBoxColor(playerid, CraftingItemModelTD[playerid][0], 255);
		PlayerTextDrawUseBox(playerid, CraftingItemModelTD[playerid][0], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemModelTD[playerid][0], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemModelTD[playerid][0], false);
		PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][0], MODEL_NULL);
		PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][0], 0.000000, 0.000000, 0.000000, 0.000000);
		// PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][0], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, CraftingItemModelTD[playerid][0], 1, 1);

		CraftingItemAmountTD[playerid][0] = CreatePlayerTextDraw(playerid, 240.000000, 313.000000, "NULL");
		PlayerTextDrawFont(playerid, CraftingItemAmountTD[playerid][0], 1);
		PlayerTextDrawLetterSize(playerid, CraftingItemAmountTD[playerid][0], 0.200000, 1.049998);
		PlayerTextDrawTextSize(playerid, CraftingItemAmountTD[playerid][0], 311.500000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemAmountTD[playerid][0], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemAmountTD[playerid][0], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemAmountTD[playerid][0], 1);
		PlayerTextDrawColor(playerid, CraftingItemAmountTD[playerid][0], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemAmountTD[playerid][0], 255);
		PlayerTextDrawBoxColor(playerid, CraftingItemAmountTD[playerid][0], -206);
		PlayerTextDrawUseBox(playerid, CraftingItemAmountTD[playerid][0], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemAmountTD[playerid][0], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemAmountTD[playerid][0], 0);

		CraftingItemModelTD[playerid][1] = CreatePlayerTextDraw(playerid, 222.000000, 327.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, CraftingItemModelTD[playerid][1], 5);
		PlayerTextDrawLetterSize(playerid, CraftingItemModelTD[playerid][1], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingItemModelTD[playerid][1], 15.500000, 18.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemModelTD[playerid][1], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemModelTD[playerid][1], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemModelTD[playerid][1], 1);
		PlayerTextDrawColor(playerid, CraftingItemModelTD[playerid][1], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemModelTD[playerid][1], 1296911616);
		PlayerTextDrawBoxColor(playerid, CraftingItemModelTD[playerid][1], 255);
		PlayerTextDrawUseBox(playerid, CraftingItemModelTD[playerid][1], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemModelTD[playerid][1], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemModelTD[playerid][1], false);
		PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][1], MODEL_NULL);
		PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][1], 0.000000, 0.000000, 0.000000, 0.000000);
		// PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][1], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, CraftingItemModelTD[playerid][1], 1, 1);

		CraftingItemAmountTD[playerid][1] = CreatePlayerTextDraw(playerid, 240.000000, 332.000000, "NULL");
		PlayerTextDrawFont(playerid, CraftingItemAmountTD[playerid][1], 1);
		PlayerTextDrawLetterSize(playerid, CraftingItemAmountTD[playerid][1], 0.200000, 1.049998);
		PlayerTextDrawTextSize(playerid, CraftingItemAmountTD[playerid][1], 311.500000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemAmountTD[playerid][1], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemAmountTD[playerid][1], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemAmountTD[playerid][1], 1);
		PlayerTextDrawColor(playerid, CraftingItemAmountTD[playerid][1], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemAmountTD[playerid][1], 255);
		PlayerTextDrawBoxColor(playerid, CraftingItemAmountTD[playerid][1], -206);
		PlayerTextDrawUseBox(playerid, CraftingItemAmountTD[playerid][1], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemAmountTD[playerid][1], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemAmountTD[playerid][1], 0);

		CraftingItemModelTD[playerid][2] = CreatePlayerTextDraw(playerid, 222.000000, 346.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, CraftingItemModelTD[playerid][2], 5);
		PlayerTextDrawLetterSize(playerid, CraftingItemModelTD[playerid][2], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingItemModelTD[playerid][2], 15.500000, 18.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemModelTD[playerid][2], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemModelTD[playerid][2], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemModelTD[playerid][2], 1);
		PlayerTextDrawColor(playerid, CraftingItemModelTD[playerid][2], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemModelTD[playerid][2], 1296911616);
		PlayerTextDrawBoxColor(playerid, CraftingItemModelTD[playerid][2], 255);
		PlayerTextDrawUseBox(playerid, CraftingItemModelTD[playerid][2], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemModelTD[playerid][2], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemModelTD[playerid][2], false);
		PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][2], MODEL_NULL);
		PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][2], 0.000000, 0.000000, 0.000000, 0.000000);
		// PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][2], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, CraftingItemModelTD[playerid][2], 1, 1);

		CraftingItemAmountTD[playerid][2] = CreatePlayerTextDraw(playerid, 240.000000, 351.000000, "NULL");
		PlayerTextDrawFont(playerid, CraftingItemAmountTD[playerid][2], 1);
		PlayerTextDrawLetterSize(playerid, CraftingItemAmountTD[playerid][2], 0.200000, 1.049998);
		PlayerTextDrawTextSize(playerid, CraftingItemAmountTD[playerid][2], 311.500000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemAmountTD[playerid][2], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemAmountTD[playerid][2], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemAmountTD[playerid][2], 1);
		PlayerTextDrawColor(playerid, CraftingItemAmountTD[playerid][2], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemAmountTD[playerid][2], 255);
		PlayerTextDrawBoxColor(playerid, CraftingItemAmountTD[playerid][2], -206);
		PlayerTextDrawUseBox(playerid, CraftingItemAmountTD[playerid][2], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemAmountTD[playerid][2], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemAmountTD[playerid][2], 0);

		CraftingItemModelTD[playerid][3] = CreatePlayerTextDraw(playerid, 222.000000, 364.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, CraftingItemModelTD[playerid][3], 5);
		PlayerTextDrawLetterSize(playerid, CraftingItemModelTD[playerid][3], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingItemModelTD[playerid][3], 15.500000, 18.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemModelTD[playerid][3], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemModelTD[playerid][3], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemModelTD[playerid][3], 1);
		PlayerTextDrawColor(playerid, CraftingItemModelTD[playerid][3], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemModelTD[playerid][3], 1296911616);
		PlayerTextDrawBoxColor(playerid, CraftingItemModelTD[playerid][3], 255);
		PlayerTextDrawUseBox(playerid, CraftingItemModelTD[playerid][3], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemModelTD[playerid][3], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemModelTD[playerid][3], false);
		PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][3], MODEL_NULL);
		PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][3], 0.000000, 0.000000, 0.000000, 0.000000);
		// PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][3], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, CraftingItemModelTD[playerid][3], 1, 1);

		CraftingItemAmountTD[playerid][3] = CreatePlayerTextDraw(playerid, 240.000000, 369.000000, "NULL");
		PlayerTextDrawFont(playerid, CraftingItemAmountTD[playerid][3], 1);
		PlayerTextDrawLetterSize(playerid, CraftingItemAmountTD[playerid][3], 0.200000, 1.049998);
		PlayerTextDrawTextSize(playerid, CraftingItemAmountTD[playerid][3], 311.500000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemAmountTD[playerid][3], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemAmountTD[playerid][3], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemAmountTD[playerid][3], 1);
		PlayerTextDrawColor(playerid, CraftingItemAmountTD[playerid][3], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemAmountTD[playerid][3], 255);
		PlayerTextDrawBoxColor(playerid, CraftingItemAmountTD[playerid][3], -206);
		PlayerTextDrawUseBox(playerid, CraftingItemAmountTD[playerid][3], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemAmountTD[playerid][3], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemAmountTD[playerid][3], 0);

		CraftingItemModelTD[playerid][4] = CreatePlayerTextDraw(playerid, 319.000000, 309.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, CraftingItemModelTD[playerid][4], 5);
		PlayerTextDrawLetterSize(playerid, CraftingItemModelTD[playerid][4], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingItemModelTD[playerid][4], 15.500000, 18.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemModelTD[playerid][4], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemModelTD[playerid][4], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemModelTD[playerid][4], 1);
		PlayerTextDrawColor(playerid, CraftingItemModelTD[playerid][4], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemModelTD[playerid][4], 1296911616);
		PlayerTextDrawBoxColor(playerid, CraftingItemModelTD[playerid][4], 255);
		PlayerTextDrawUseBox(playerid, CraftingItemModelTD[playerid][4], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemModelTD[playerid][4], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemModelTD[playerid][4], false);
		PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][4], MODEL_NULL);
		PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][4], 0.000000, 0.000000, 0.000000, 0.000000);
		// PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][4], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, CraftingItemModelTD[playerid][4], 1, 1);

		CraftingItemAmountTD[playerid][4] = CreatePlayerTextDraw(playerid, 336.000000, 313.000000, "NULL");
		PlayerTextDrawFont(playerid, CraftingItemAmountTD[playerid][4], 1);
		PlayerTextDrawLetterSize(playerid, CraftingItemAmountTD[playerid][4], 0.200000, 1.049998);
		PlayerTextDrawTextSize(playerid, CraftingItemAmountTD[playerid][4], 408.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemAmountTD[playerid][4], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemAmountTD[playerid][4], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemAmountTD[playerid][4], 1);
		PlayerTextDrawColor(playerid, CraftingItemAmountTD[playerid][4], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemAmountTD[playerid][4], 255);
		PlayerTextDrawBoxColor(playerid, CraftingItemAmountTD[playerid][4], -206);
		PlayerTextDrawUseBox(playerid, CraftingItemAmountTD[playerid][4], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemAmountTD[playerid][4], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemAmountTD[playerid][4], 0);

		CraftingItemModelTD[playerid][5] = CreatePlayerTextDraw(playerid, 319.000000, 327.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, CraftingItemModelTD[playerid][5], 5);
		PlayerTextDrawLetterSize(playerid, CraftingItemModelTD[playerid][5], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingItemModelTD[playerid][5], 15.500000, 18.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemModelTD[playerid][5], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemModelTD[playerid][5], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemModelTD[playerid][5], 1);
		PlayerTextDrawColor(playerid, CraftingItemModelTD[playerid][5], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemModelTD[playerid][5], 1296911616);
		PlayerTextDrawBoxColor(playerid, CraftingItemModelTD[playerid][5], 255);
		PlayerTextDrawUseBox(playerid, CraftingItemModelTD[playerid][5], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemModelTD[playerid][5], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemModelTD[playerid][5], false);
		PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][5], MODEL_NULL);
		PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][5], 0.000000, 0.000000, 0.000000, 0.000000);
		// PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][5], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, CraftingItemModelTD[playerid][5], 1, 1);

		CraftingItemAmountTD[playerid][5] = CreatePlayerTextDraw(playerid, 336.000000, 332.000000, "NULL");
		PlayerTextDrawFont(playerid, CraftingItemAmountTD[playerid][5], 1);
		PlayerTextDrawLetterSize(playerid, CraftingItemAmountTD[playerid][5], 0.200000, 1.049998);
		PlayerTextDrawTextSize(playerid, CraftingItemAmountTD[playerid][5], 408.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemAmountTD[playerid][5], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemAmountTD[playerid][5], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemAmountTD[playerid][5], 1);
		PlayerTextDrawColor(playerid, CraftingItemAmountTD[playerid][5], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemAmountTD[playerid][5], 255);
		PlayerTextDrawBoxColor(playerid, CraftingItemAmountTD[playerid][5], -206);
		PlayerTextDrawUseBox(playerid, CraftingItemAmountTD[playerid][5], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemAmountTD[playerid][5], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemAmountTD[playerid][5], 0);

		CraftingItemModelTD[playerid][6] = CreatePlayerTextDraw(playerid, 319.000000, 346.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, CraftingItemModelTD[playerid][6], 5);
		PlayerTextDrawLetterSize(playerid, CraftingItemModelTD[playerid][6], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingItemModelTD[playerid][6], 15.500000, 18.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemModelTD[playerid][6], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemModelTD[playerid][6], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemModelTD[playerid][6], 1);
		PlayerTextDrawColor(playerid, CraftingItemModelTD[playerid][6], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemModelTD[playerid][6], 1296911616);
		PlayerTextDrawBoxColor(playerid, CraftingItemModelTD[playerid][6], 255);
		PlayerTextDrawUseBox(playerid, CraftingItemModelTD[playerid][6], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemModelTD[playerid][6], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemModelTD[playerid][6], false);
		PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][6], MODEL_NULL);
		PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][6], 0.000000, 0.000000, 0.000000, 0.000000);
		// PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][6], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, CraftingItemModelTD[playerid][6], 1, 1);

		CraftingItemAmountTD[playerid][6] = CreatePlayerTextDraw(playerid, 336.000000, 351.000000, "NULL");
		PlayerTextDrawFont(playerid, CraftingItemAmountTD[playerid][6], 1);
		PlayerTextDrawLetterSize(playerid, CraftingItemAmountTD[playerid][6], 0.200000, 1.049998);
		PlayerTextDrawTextSize(playerid, CraftingItemAmountTD[playerid][6], 408.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemAmountTD[playerid][6], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemAmountTD[playerid][6], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemAmountTD[playerid][6], 1);
		PlayerTextDrawColor(playerid, CraftingItemAmountTD[playerid][6], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemAmountTD[playerid][6], 255);
		PlayerTextDrawBoxColor(playerid, CraftingItemAmountTD[playerid][6], -206);
		PlayerTextDrawUseBox(playerid, CraftingItemAmountTD[playerid][6], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemAmountTD[playerid][6], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemAmountTD[playerid][6], 0);

		CraftingItemModelTD[playerid][7] = CreatePlayerTextDraw(playerid, 319.000000, 364.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, CraftingItemModelTD[playerid][7], 5);
		PlayerTextDrawLetterSize(playerid, CraftingItemModelTD[playerid][7], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingItemModelTD[playerid][7], 15.500000, 18.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemModelTD[playerid][7], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemModelTD[playerid][7], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemModelTD[playerid][7], 1);
		PlayerTextDrawColor(playerid, CraftingItemModelTD[playerid][7], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemModelTD[playerid][7], 1296911616);
		PlayerTextDrawBoxColor(playerid, CraftingItemModelTD[playerid][7], 255);
		PlayerTextDrawUseBox(playerid, CraftingItemModelTD[playerid][7], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemModelTD[playerid][7], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemModelTD[playerid][7], false);
		PlayerTextDrawSetPreviewModel(playerid, CraftingItemModelTD[playerid][7], MODEL_NULL);
		PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][7], 0.000000, 0.000000, 0.000000, 0.000000);
		// PlayerTextDrawSetPreviewRot(playerid, CraftingItemModelTD[playerid][7], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, CraftingItemModelTD[playerid][7], 1, 1);

		CraftingItemAmountTD[playerid][7] = CreatePlayerTextDraw(playerid, 336.000000, 369.000000, "NULL");
		PlayerTextDrawFont(playerid, CraftingItemAmountTD[playerid][7], 1);
		PlayerTextDrawLetterSize(playerid, CraftingItemAmountTD[playerid][7], 0.200000, 1.049998);
		PlayerTextDrawTextSize(playerid, CraftingItemAmountTD[playerid][7], 408.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingItemAmountTD[playerid][7], 0);
		PlayerTextDrawSetShadow(playerid, CraftingItemAmountTD[playerid][7], 0);
		PlayerTextDrawAlignment(playerid, CraftingItemAmountTD[playerid][7], 1);
		PlayerTextDrawColor(playerid, CraftingItemAmountTD[playerid][7], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingItemAmountTD[playerid][7], 255);
		PlayerTextDrawBoxColor(playerid, CraftingItemAmountTD[playerid][7], -206);
		PlayerTextDrawUseBox(playerid, CraftingItemAmountTD[playerid][7], 0);
		PlayerTextDrawSetProportional(playerid, CraftingItemAmountTD[playerid][7], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingItemAmountTD[playerid][7], 0);

		playerOpenCraftingDetailItem[playerid] = true;
		for(new i=0; i<MAX_CRAFTING_ITEM; i++){
			PlayerTextDrawShow(playerid, CraftingItemModelTD[playerid][i]);
			PlayerTextDrawShow(playerid, CraftingItemAmountTD[playerid][i]);
		}
	} else if(playerOpenCraftingDetailItem[playerid] && !flag){
		playerOpenCraftingDetailItem[playerid] = false;
		for(new i=0; i<MAX_CRAFTING_ITEM; i++){
			if(IsPlayerTextDrawVisible(playerid, CraftingItemModelTD[playerid][i])){
				PlayerTextDrawHide(playerid, CraftingItemModelTD[playerid][i]);
			}
			PlayerTextDrawDestroy(playerid, CraftingItemModelTD[playerid][i]);

			if(IsPlayerTextDrawVisible(playerid, CraftingItemAmountTD[playerid][i])){
				PlayerTextDrawHide(playerid, CraftingItemAmountTD[playerid][i]);
			}
			PlayerTextDrawDestroy(playerid, CraftingItemAmountTD[playerid][i]);
		}
	}
}

void:PlayerCreateCraftingTD(playerid, flag = true){
	if(!playerOpenCraftingMenu[playerid] && flag){
		CraftingTD[playerid][0] = CreatePlayerTextDraw(playerid, 354.000000, 145.000000, "_");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][0], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][0], 0.600000, 15.850005);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][0], 298.500000, 270.500000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][0], 1);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][0], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][0], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][0], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][0], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][0], 135);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][0], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][0], 0);

		CraftingTD[playerid][1] = CreatePlayerTextDraw(playerid, 319.000000, 127.000000, "_");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][1], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][1], 0.600000, 1.649995);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][1], 298.500000, 340.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][1], 1);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][1], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][1], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][1], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][1], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][1], 1296911751);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][1], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][1], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][1], 0);

		CraftingTD[playerid][2] = CreatePlayerTextDraw(playerid, 182.500000, 145.000000, "_");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][2], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][2], 0.600000, 28.950004);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][2], 298.500000, 66.500000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][2], 1);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][2], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][2], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][2], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][2], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][2], 774778538);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][2], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][2], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][2], 0);

		CraftingTD[playerid][3] = CreatePlayerTextDraw(playerid, 354.000000, 291.000000, "_");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][3], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][3], 0.600000, 10.399990);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][3], 298.500000, 270.500000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][3], 1);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][3], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][3], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][3], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][3], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][3], 120);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][3], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][3], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][3], 0);

		CraftingTD[playerid][4] = CreatePlayerTextDraw(playerid, 480.000000, 126.000000, "X");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][4], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][4], 0.399999, 1.700000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][4], 16.500000, 20.500000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][4], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][4], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][4], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][4], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][4], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][4], 200);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][4], 0);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][4], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][4], 1);

		CraftingTD[playerid][5] = CreatePlayerTextDraw(playerid, 151.000000, 127.000000, "CRAFTING MENU");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][5], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][5], 0.312500, 1.550000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][5], 400.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][5], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][5], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][5], 1);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][5], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][5], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][5], 50);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][5], 0);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][5], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][5], 0);

		CraftingTD[playerid][6] = CreatePlayerTextDraw(playerid, 354.000000, 388.500000, "_");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][6], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][6], 0.600000, 1.849989);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][6], 298.500000, 270.500000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][6], 1);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][6], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][6], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][6], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][6], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][6], 589505450);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][6], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][6], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][6], 0);

		CraftingTD[playerid][7] = CreatePlayerTextDraw(playerid, 316.000000, 312.000000, "_");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][7], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][7], 0.600000, 7.499992);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][7], 298.500000, -2.500000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][7], 1);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][7], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][7], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][7], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][7], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][7], -121);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][7], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][7], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][7], 0);

		CraftingTD[playerid][8] = CreatePlayerTextDraw(playerid, 452.000000, 312.000000, "Receive");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][8], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][8], 0.291666, 1.450000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][8], 410.000000, 67.500000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][8], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][8], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][8], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][8], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][8], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][8], 50);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][8], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][8], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][8], 0);

		CraftingTD[playerid][9] = CreatePlayerTextDraw(playerid, 433.000000, 334.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][9], 5);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][9], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][9], 38.000000, 41.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][9], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][9], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][9], 1);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][9], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][9], 1296911741);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][9], 255);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][9], 0);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][9], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][9], false);
		PlayerTextDrawSetPreviewModel(playerid, CraftingTD[playerid][9], 19579);
		PlayerTextDrawSetPreviewRot(playerid, CraftingTD[playerid][9], -10.000000, 0.000000, -20.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, CraftingTD[playerid][9], 1, 1);

		CraftingTD[playerid][10] = CreatePlayerTextDraw(playerid, 469.000000, 335.000000, "1");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][10], 2);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][10], 0.179166, 0.900000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][10], 400.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][10], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][10], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][10], 3);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][10], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][10], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][10], 50);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][10], 0);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][10], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][10], 0);

		CraftingTD[playerid][11] = CreatePlayerTextDraw(playerid, 228.000000, 389.000000, "-");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][11], 2);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][11], 0.387499, 1.650000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][11], 16.500000, 16.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][11], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][11], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][11], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][11], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][11], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][11], 1296911816);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][11], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][11], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][11], 1);

		CraftingTD[playerid][12] = CreatePlayerTextDraw(playerid, 251.000000, 389.000000, "1");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][12], 2);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][12], 0.341666, 1.650000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][12], 16.500000, 22.500000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][12], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][12], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][12], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][12], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][12], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][12], 200);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][12], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][12], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][12], 1);

		CraftingTD[playerid][13] = CreatePlayerTextDraw(playerid, 274.500000, 389.000000, "+");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][13], 2);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][13], 0.387499, 1.650000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][13], 16.500000, 16.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][13], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][13], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][13], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][13], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][13], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][13], 1296911816);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][13], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][13], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][13], 1);

		CraftingTD[playerid][14] = CreatePlayerTextDraw(playerid, 287.000000, 384.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][14], 5);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][14], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][14], 14.500000, 15.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][14], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][14], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][14], 1);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][14], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][14], 0);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][14], 0);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][14], 0);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][14], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][14], 0);
		PlayerTextDrawSetPreviewModel(playerid, CraftingTD[playerid][14], 1212);
		PlayerTextDrawSetPreviewRot(playerid, CraftingTD[playerid][14], -41.000000, 15.000000, -27.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, CraftingTD[playerid][14], 1, 1);

		CraftingTD[playerid][15] = CreatePlayerTextDraw(playerid, 302.000000, 388.000000, "$0");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][15], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][15], 0.162500, 0.800000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][15], 359.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][15], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][15], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][15], 1);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][15], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][15], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][15], 50);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][15], 0);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][15], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][15], 0);

		CraftingTD[playerid][16] = CreatePlayerTextDraw(playerid, 287.000000, 392.000000, "Preview_Model");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][16], 5);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][16], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][16], 14.500000, 15.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][16], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][16], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][16], 1);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][16], -16776961);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][16], 0);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][16], 0);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][16], 0);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][16], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][16], 0);
		PlayerTextDrawSetPreviewModel(playerid, CraftingTD[playerid][16], 1212);
		PlayerTextDrawSetPreviewRot(playerid, CraftingTD[playerid][16], -41.000000, 15.000000, -27.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, CraftingTD[playerid][16], 1, 1);

		CraftingTD[playerid][17] = CreatePlayerTextDraw(playerid, 302.000000, 396.000000, "$0");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][17], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][17], 0.162500, 0.800000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][17], 359.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][17], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][17], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][17], 1);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][17], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][17], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][17], 50);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][17], 0);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][17], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][17], 0);

		CraftingTD[playerid][18] = CreatePlayerTextDraw(playerid, 457.000000, 389.000000, "CRAFT");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][18], 2);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][18], 0.274999, 1.700000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][18], 31.500000, 60.500000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][18], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][18], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][18], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][18], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][18], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][18], 200);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][18], 0);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][18], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][18], 1);

		CraftingTD[playerid][19] = CreatePlayerTextDraw(playerid, 412.000000, 312.000000, "_");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][19], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][19], 0.600000, 7.499992);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][19], 298.500000, -2.500000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][19], 1);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][19], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][19], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][19], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][19], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][19], -121);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][19], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][19], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][19], 0);

		CraftingTD[playerid][20] = CreatePlayerTextDraw(playerid, 225.000000, 291.000000, "ItemName");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][20], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][20], 0.304166, 1.750000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][20], 486.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][20], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][20], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][20], 1);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][20], -2686721);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][20], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][20], 50);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][20], 0);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][20], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][20], 0);

		CraftingTD[playerid][21] = CreatePlayerTextDraw(playerid, 497.000000, 144.000000, "ld_beat:up");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][21], 4);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][21], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][21], 17.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][21], 1);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][21], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][21], 1);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][21], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][21], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][21], 50);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][21], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][21], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][21], 1);

		CraftingTD[playerid][22] = CreatePlayerTextDraw(playerid, 506.000000, 166.000000, "100");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][22], 1);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][22], 0.270833, 1.400000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][22], 400.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][22], 0);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][22], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][22], 2);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][22], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][22], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][22], 50);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][22], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][22], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][22], 0);

		CraftingTD[playerid][23] = CreatePlayerTextDraw(playerid, 497.000000, 184.000000, "ld_beat:down");
		PlayerTextDrawFont(playerid, CraftingTD[playerid][23], 4);
		PlayerTextDrawLetterSize(playerid, CraftingTD[playerid][23], 0.600000, 2.000000);
		PlayerTextDrawTextSize(playerid, CraftingTD[playerid][23], 17.000000, 17.000000);
		PlayerTextDrawSetOutline(playerid, CraftingTD[playerid][23], 1);
		PlayerTextDrawSetShadow(playerid, CraftingTD[playerid][23], 0);
		PlayerTextDrawAlignment(playerid, CraftingTD[playerid][23], 1);
		PlayerTextDrawColor(playerid, CraftingTD[playerid][23], -1);
		PlayerTextDrawBackgroundColor(playerid, CraftingTD[playerid][23], 255);
		PlayerTextDrawBoxColor(playerid, CraftingTD[playerid][23], 50);
		PlayerTextDrawUseBox(playerid, CraftingTD[playerid][23], 1);
		PlayerTextDrawSetProportional(playerid, CraftingTD[playerid][23], 1);
		PlayerTextDrawSetSelectable(playerid, CraftingTD[playerid][23], 1);

		for(new i=0; i<MAX_CRAFT_TD; i++){
			PlayerTextDrawShow(playerid, CraftingTD[playerid][i]);
		}

		for(new i=7; i<MAX_CRAFT_TD; i++){
			PlayerTextDrawHide(playerid, CraftingTD[playerid][i]);
		}

		playerOpenCraftingMenu[playerid] = true;
		SelectTextDraw(playerid, 0x0096FFFF);
	} else if(playerOpenCraftingMenu[playerid] && !flag){
		for(new i=0; i<MAX_CRAFT_TD; i++){
			if(IsPlayerTextDrawVisible(playerid, CraftingTD[playerid][i])){
				PlayerTextDrawHide(playerid, CraftingTD[playerid][i]);
			}

			PlayerTextDrawDestroy(playerid, CraftingTD[playerid][i]);
		}

		playerOpenCraftingMenu[playerid] = false;
		CancelSelectTextDraw(playerid);
	}
}