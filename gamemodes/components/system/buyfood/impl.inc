#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
    CreateDynamic3DTextLabel("[โต๊ะรับประทานอาหาร]\nกดปุ่ม 'Y' เพื่อใช้งาน", 0xFF3600FF, 378.1715,-122.2264,1001.4922, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
    CreateDynamic3DTextLabel("[โต๊ะรับประทานอาหาร]\nกดปุ่ม 'Y' เพื่อใช้งาน", 0xFF3600FF, 378.1715,-125.4046,1001.4922, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
    CreateDynamic3DTextLabel("[โต๊ะรับประทานอาหาร]\nกดปุ่ม 'Y' เพื่อใช้งาน", 0xFF3600FF, 378.1699,-128.4687,1001.4922, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
    CreateDynamic3DTextLabel("[โต๊ะรับประทานอาหาร]\nกดปุ่ม 'Y' เพื่อใช้งาน", 0xFF3600FF, 378.1716,-131.4947,1001.4922, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
    CreateDynamic3DTextLabel("[ร้านอาหาร]\nกดปุ่ม 'Y' เพื่อเลือกเมนู", 0xFF3600FF, 373.6984,-119.1718,1001.4922, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(!LoggedIn[playerid]) return 1;
    if(newkeys & KEY_YES){
        new string[128];
        if(IsPlayerInRangeOfPoint(playerid, 3.5, 373.6984,-119.1718,1001.4922) && !PlayerOpenFoodShop[playerid]){
            PlayerFoodShopMenu_Show(playerid);
        }

        new doorid = -1;
        if((doorid = Entrance_Inside(playerid)) != -1){
            if(IsPlayerInRangeOfPoint(playerid, 1.0, 378.1715,-122.2264,1001.4922)){
                if(PlayerSitTable[playerid] == -1 && PlayerTable[playerid] == 0){
                    new sit1[32], sit2[32], sit3[32], sit4[32];

                    if(EntranceData[doorid][entranceTable1][0]) sit1 = "ไม่ว่าง";
                    else sit1 = "ว่าง";

                    if(EntranceData[doorid][entranceTable1][1]) sit2 = "ไม่ว่าง";
                    else sit2 = "ว่าง";

                    if(EntranceData[doorid][entranceTable1][2]) sit3 = "ไม่ว่าง";
                    else sit3 = "ว่าง";

                    if(EntranceData[doorid][entranceTable1][3]) sit4 = "ไม่ว่าง";
                    else sit4 = "ว่าง";

                    format(string, sizeof string, "ที่นั่งที่ 1: %s\
                    \nที่นั่งที่ 2: %s\
                    \nที่นั่งที่ 3: %s\
                    \nที่นั่งที่ 4: %s", sit1, sit2, sit3, sit4);
                    Dialog_ShowEasy(playerid, Table1, DIALOG_STYLE_LIST, "โต๊ะที่ 1", string, "เลือก", "ยกเลิก");
                }
            }

            if(IsPlayerInRangeOfPoint(playerid, 1.0, 378.1715,-125.4046,1001.4922)){
                if(PlayerSitTable[playerid] == -1 && PlayerTable[playerid] == 0){
                    new sit1[32], sit2[32], sit3[32], sit4[32];
                    
                    if(EntranceData[doorid][entranceTable2][0]) sit1 = "ไม่ว่าง";
                    else sit1 = "ว่าง";

                    if(EntranceData[doorid][entranceTable2][1]) sit2 = "ไม่ว่าง";
                    else sit2 = "ว่าง";

                    if(EntranceData[doorid][entranceTable2][2]) sit3 = "ไม่ว่าง";
                    else sit3 = "ว่าง";

                    if(EntranceData[doorid][entranceTable2][3]) sit4 = "ไม่ว่าง";
                    else sit4 = "ว่าง";

                    format(string, sizeof string, "ที่นั่งที่ 1: %s\
                    \nที่นั่งที่ 2: %s\
                    \nที่นั่งที่ 3: %s\
                    \nที่นั่งที่ 4: %s", sit1, sit2, sit3, sit4);
                    Dialog_ShowEasy(playerid, Table2, DIALOG_STYLE_LIST, "โต๊ะที่ 2", string, "เลือก", "ยกเลิก");
                }
            }

            if(IsPlayerInRangeOfPoint(playerid, 1.0, 378.1699,-128.4687,1001.4922)){
                if(PlayerSitTable[playerid] == -1 && PlayerTable[playerid] == 0){
                    new sit1[32], sit2[32], sit3[32], sit4[32];

                    if(EntranceData[doorid][entranceTable3][0]) sit1 = "ไม่ว่าง";
                    else sit1 = "ว่าง";

                    if(EntranceData[doorid][entranceTable3][1]) sit2 = "ไม่ว่าง";
                    else sit2 = "ว่าง";

                    if(EntranceData[doorid][entranceTable3][2]) sit3 = "ไม่ว่าง";
                    else sit3 = "ว่าง";

                    if(EntranceData[doorid][entranceTable3][3]) sit4 = "ไม่ว่าง";
                    else sit4 = "ว่าง";

                    format(string, sizeof string, "ที่นั่งที่ 1: %s\
                    \nที่นั่งที่ 2: %s\
                    \nที่นั่งที่ 3: %s\
                    \nที่นั่งที่ 4: %s", sit1, sit2, sit3, sit4);
                    Dialog_ShowEasy(playerid, Table3, DIALOG_STYLE_LIST, "โต๊ะที่ 3", string, "เลือก", "ยกเลิก");
                }
            }

            if(IsPlayerInRangeOfPoint(playerid, 1.0, 378.1716,-131.4947,1001.4922)){
                if(PlayerSitTable[playerid] == -1 && PlayerTable[playerid] == 0){
                    new sit1[32], sit2[32], sit3[32], sit4[32];

                    if(EntranceData[doorid][entranceTable4][0]) sit1 = "ไม่ว่าง";
                    else sit1 = "ว่าง";

                    if(EntranceData[doorid][entranceTable4][1]) sit2 = "ไม่ว่าง";
                    else sit2 = "ว่าง";

                    if(EntranceData[doorid][entranceTable4][2]) sit3 = "ไม่ว่าง";
                    else sit3 = "ว่าง";

                    if(EntranceData[doorid][entranceTable4][3]) sit4 = "ไม่ว่าง";
                    else sit4 = "ว่าง";

                    format(string, sizeof string, "ที่นั่งที่ 1: %s\
                    \nที่นั่งที่ 2: %s\
                    \nที่นั่งที่ 3: %s\
                    \nที่นั่งที่ 4: %s", sit1, sit2, sit3, sit4);
                    Dialog_ShowEasy(playerid, Table4, DIALOG_STYLE_LIST, "โต๊ะที่ 4", string, "เลือก", "ยกเลิก");
                }
            }
        }
    }
    if(newkeys & KEY_NO){
        if(PlayerCarryFood[playerid]){
            PlayerCarryFood[playerid] = false;
            PlayerCarryFoodType[playerid] = 0;
            RemoveAttachedObject(playerid, 9);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        }
        if(PlayerSitTable[playerid] != -1 && PlayerTable[playerid] != 0){
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            if(IsValidDynamicObject(TablePizza[playerid]) && TablePizza[playerid] != -1) DestroyDynamicObject(TablePizza[playerid]);
            TablePizza[playerid] = -1;


            if(PlayerTable[playerid] == 1){
                EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][PlayerSitTable[playerid]] = false;
            }
            else if(PlayerTable[playerid] == 2){
                EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][PlayerSitTable[playerid]] = false;
            }
            else if(PlayerTable[playerid] == 3){
                EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][PlayerSitTable[playerid]] = false;
            }
            else if(PlayerTable[playerid] == 4){
                EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][PlayerSitTable[playerid]] = false;
            }

            stop PlayerUpdateFood[playerid];

            TogglePlayerControllable(playerid, 1);

            PlayerTempHunger[playerid] = 0;
            PlayerTempWater[playerid] = 0;

            PlayerCarryFood[playerid] = false;
            PlayerCarryFoodType[playerid] = 0;
            PlayerSitTable[playerid] = -1;
            PlayerTable[playerid] = 0;
        }
    }
    return 1;
}

timer UpdateFoodPlayer[1000](playerid){
    if(PlayerSitTable[playerid] != -1 && PlayerTable[playerid] != 0){
        if(PlayerCarryFoodType[playerid] == 1){
            new maxvalue = 30;

            if(PlayerTempHunger[playerid] < maxvalue){
                PlayerTempHunger[playerid] += 2;
                PlayerData[playerid][pHunger] += 2;
            }

            if(PlayerTempWater[playerid] < maxvalue){
                PlayerTempWater[playerid] += 2;
                PlayerData[playerid][pWater] += 2;
            }

            if(PlayerTempHunger[playerid] >= maxvalue && PlayerTempWater[playerid] >= maxvalue){
                if(PlayerSitTable[playerid] != -1 && PlayerTable[playerid] != 0){
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                    ClearAnimations(playerid);
                    if(IsValidDynamicObject(TablePizza[playerid]) && TablePizza[playerid] != -1) DestroyDynamicObject(TablePizza[playerid]);
                    TablePizza[playerid] = -1;

                    if(PlayerTable[playerid] == 1){
                        EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][PlayerSitTable[playerid]] = false;
                    }
                    else if(PlayerTable[playerid] == 2){
                        EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][PlayerSitTable[playerid]] = false;
                    }
                    else if(PlayerTable[playerid] == 3){
                        EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][PlayerSitTable[playerid]] = false;
                    }
                    else if(PlayerTable[playerid] == 4){
                        EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][PlayerSitTable[playerid]] = false;
                    }

                    stop PlayerUpdateFood[playerid];

                    TogglePlayerControllable(playerid, 1);

                    PlayerTempHunger[playerid] = 0;
                    PlayerTempWater[playerid] = 0;

                    PlayerCarryFood[playerid] = false;
                    PlayerCarryFoodType[playerid] = 0;
                    PlayerSitTable[playerid] = -1;
                    PlayerTable[playerid] = 0;
                }
            }

            if(PlayerData[playerid][pHunger] >= 100) PlayerData[playerid][pHunger] = 100;
            if(PlayerData[playerid][pWater] >= 100) PlayerData[playerid][pWater] = 100;
        }
        else if(PlayerCarryFoodType[playerid] == 2){
            new maxvalue = 40;

            if(PlayerTempHunger[playerid] < maxvalue){
                PlayerTempHunger[playerid] += 2;
                PlayerData[playerid][pHunger] += 2;
            }

            if(PlayerTempWater[playerid] < maxvalue){
                PlayerTempWater[playerid] += 2;
                PlayerData[playerid][pWater] += 2;
            }

            if(PlayerTempHunger[playerid] >= maxvalue && PlayerTempWater[playerid] >= maxvalue){
                if(PlayerSitTable[playerid] != -1 && PlayerTable[playerid] != 0){
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                    ClearAnimations(playerid);
                    if(IsValidDynamicObject(TablePizza[playerid]) && TablePizza[playerid] != -1) DestroyDynamicObject(TablePizza[playerid]);
                    TablePizza[playerid] = -1;

                    if(PlayerTable[playerid] == 1){
                        EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][PlayerSitTable[playerid]] = false;
                    }
                    else if(PlayerTable[playerid] == 2){
                        EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][PlayerSitTable[playerid]] = false;
                    }
                    else if(PlayerTable[playerid] == 3){
                        EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][PlayerSitTable[playerid]] = false;
                    }
                    else if(PlayerTable[playerid] == 4){
                        EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][PlayerSitTable[playerid]] = false;
                    }

                    stop PlayerUpdateFood[playerid];

                    TogglePlayerControllable(playerid, 1);

                    PlayerCarryFood[playerid] = false;
                    PlayerCarryFoodType[playerid] = 0;
                    PlayerSitTable[playerid] = -1;
                    PlayerTable[playerid] = 0;
                }
            }

            if(PlayerData[playerid][pHunger] >= 100) PlayerData[playerid][pHunger] = 100;
            if(PlayerData[playerid][pWater] >= 100) PlayerData[playerid][pWater] = 100;
        }
    }
}

Dialog:Table1(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][0]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE1_1);
            SetPlayerFacingAngle(playerid, ANGTABLE1_1);

            SetPlayerPos(playerid, POSTABLE1_1);
            SetPlayerFacingAngle(playerid, ANGTABLE1_1);

            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,379.7999900,-122.0000000,1001.4000200,334.6030000,26.7600000,258.2030000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,379.7999900,-122.0000000,1001.4000200,334.6030000,26.7600000,258.2030000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 0;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 1;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 1){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][1]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE1_2);
            SetPlayerFacingAngle(playerid, ANGTABLE1_2);
            SetPlayerPos(playerid, POSTABLE1_2);
            SetPlayerFacingAngle(playerid, ANGTABLE1_2);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,378.8999900,-122.0000000,1001.4000200,334.6000000,26.7570000,258.2010000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,378.8999900,-122.0000000,1001.4000200,334.6000000,26.7570000,258.2010000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 1;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 1;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 2){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][2]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE1_3);
            SetPlayerFacingAngle(playerid, ANGTABLE1_3);
            SetPlayerPos(playerid, POSTABLE1_3);
            SetPlayerFacingAngle(playerid, ANGTABLE1_3);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,380.2999900,-122.6000000,1001.4000200,334.6000000,26.7570000,74.2010000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,380.2999900,-122.6000000,1001.4000200,334.6000000,26.7570000,74.2010000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 2;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 1;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 3){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][3]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE1_4);
            SetPlayerFacingAngle(playerid, ANGTABLE1_4);
            SetPlayerPos(playerid, POSTABLE1_4);
            SetPlayerFacingAngle(playerid, ANGTABLE1_4);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,379.5000000,-122.6000000,1001.4000200,334.6000000,26.7570000,74.1960000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,379.5000000,-122.6000000,1001.4000200,334.6000000,26.7570000,74.1960000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 3;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable1][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 1;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
    }
    return 1;
}

Dialog:Table2(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][0]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE2_1);
            SetPlayerFacingAngle(playerid, ANGTABLE2_1);
            SetPlayerPos(playerid, POSTABLE2_1);
            SetPlayerFacingAngle(playerid, ANGTABLE2_1);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,379.7000100,-125.1000000,1001.4000200,334.6030000,26.7600000,258.2030000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,379.7000100,-125.1000000,1001.4000200,334.6030000,26.7600000,258.2030000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 0;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 2;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 1){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][1]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE2_2);
            SetPlayerFacingAngle(playerid, ANGTABLE2_2);
            SetPlayerPos(playerid, POSTABLE2_2);
            SetPlayerFacingAngle(playerid, ANGTABLE2_2);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,378.8999900,-125.1000000,1001.4000200,334.6000000,26.7570000,254.2010000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,378.8999900,-125.1000000,1001.4000200,334.6000000,26.7570000,254.2010000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 1;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 2;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 2){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][2]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE2_3);
            SetPlayerFacingAngle(playerid, ANGTABLE2_3);
            SetPlayerPos(playerid, POSTABLE2_3);
            SetPlayerFacingAngle(playerid, ANGTABLE2_3);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,380.2999900,-125.7000000,1001.4000200,334.6000000,26.7570000,74.2010000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,380.2999900,-125.7000000,1001.4000200,334.6000000,26.7570000,74.2010000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 2;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 2;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 3){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][3]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE2_4);
            SetPlayerFacingAngle(playerid, ANGTABLE2_4);
            SetPlayerPos(playerid, POSTABLE2_4);
            SetPlayerFacingAngle(playerid, ANGTABLE2_4);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,379.3999900,-125.7000000,1001.4000200,334.6000000,26.7570000,74.1960000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,379.3999900,-125.7000000,1001.4000200,334.6000000,26.7570000,74.1960000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 3;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable2][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 2;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
    }
    return 1;
}

Dialog:Table3(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][0]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE3_1);
            SetPlayerFacingAngle(playerid, ANGTABLE3_1);
            SetPlayerPos(playerid, POSTABLE3_1);
            SetPlayerFacingAngle(playerid, ANGTABLE3_1);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,379.7000100,-128.1000100,1001.4000200,334.6030000,26.7600000,254.7030000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,379.7000100,-128.1000100,1001.4000200,334.6030000,26.7600000,254.7030000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 0;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 3;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 1){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][1]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE3_2);
            SetPlayerFacingAngle(playerid, ANGTABLE3_2);
            SetPlayerPos(playerid, POSTABLE3_2);
            SetPlayerFacingAngle(playerid, ANGTABLE3_2);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,378.8999900,-128.1000100,1001.4000200,334.6000000,26.7570000,254.2010000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,378.8999900,-128.1000100,1001.4000200,334.6000000,26.7570000,254.2010000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 1;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 3;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 2){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][2]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE3_3);
            SetPlayerFacingAngle(playerid, ANGTABLE3_3);
            SetPlayerPos(playerid, POSTABLE3_3);
            SetPlayerFacingAngle(playerid, ANGTABLE3_3);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,380.2000100,-128.8000000,1001.4000200,334.6000000,26.7570000,74.2010000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,380.2000100,-128.8000000,1001.4000200,334.6000000,26.7570000,74.2010000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            PlayerSitTable[playerid] = 2;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 3;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 3){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][3]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE3_4);
            SetPlayerFacingAngle(playerid, ANGTABLE3_4);
            SetPlayerPos(playerid, POSTABLE3_4);
            SetPlayerFacingAngle(playerid, ANGTABLE3_4);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,379.3999900,-128.8000000,1001.4000200,334.6000000,26.7570000,72.1960000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,379.3999900,-128.8000000,1001.4000200,334.6000000,26.7570000,72.1960000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 3;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable3][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 3;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
    }
    return 1;
}

Dialog:Table4(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][0]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE4_1);
            SetPlayerFacingAngle(playerid, ANGTABLE4_1);
            SetPlayerPos(playerid, POSTABLE4_1);
            SetPlayerFacingAngle(playerid, ANGTABLE4_1);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,379.7000100,-131.2000000,1001.4000200,334.6030000,26.7600000,254.7030000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,379.7000100,-131.2000000,1001.4000200,334.6030000,26.7600000,254.7030000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 0;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 4;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 1){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][1]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE4_2);
            SetPlayerFacingAngle(playerid, ANGTABLE4_2);
            SetPlayerPos(playerid, POSTABLE4_2);
            SetPlayerFacingAngle(playerid, ANGTABLE4_2);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,378.7999900,-131.2000000,1001.4000200,334.6000000,26.7570000,254.2010000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,378.7999900,-131.2000000,1001.4000200,334.6000000,26.7570000,254.2010000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 1;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 4;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 2){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][2]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE4_3);
            SetPlayerFacingAngle(playerid, ANGTABLE4_3);
            SetPlayerPos(playerid, POSTABLE4_3);
            SetPlayerFacingAngle(playerid, ANGTABLE4_3);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,380.1000100,-131.8999900,1001.4000200,334.6000000,26.7570000,74.2010000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,380.1000100,-131.8999900,1001.4000200,334.6000000,26.7570000,74.2010000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 2;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 4;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
        if(listitem == 3){
            if(EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][3]) return ErrorMsg(playerid, "ที่นั่งนี้ไม่ว่าง");
            SetPlayerPos(playerid, POSTABLE4_4);
            SetPlayerFacingAngle(playerid, ANGTABLE4_4);
            SetPlayerPos(playerid, POSTABLE4_4);
            SetPlayerFacingAngle(playerid, ANGTABLE4_4);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ClearAnimations(playerid);
            
            if(PlayerCarryFood[playerid]){
                RemoveAttachedObject(playerid, 9);
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Eat1", 3.0, 1, 0, 0, 1, 0);
                if(PlayerCarryFoodType[playerid] == 1){
                    TablePizza[playerid] = CreateDynamicObjectEx(2218,379.2999900,-131.8999900,1001.4000200,334.6000000,26.7570000,72.1960000);
                }
                else if(PlayerCarryFoodType[playerid] == 2){
                    TablePizza[playerid] = CreateDynamicObjectEx(2217,379.2999900,-131.8999900,1001.4000200,334.6000000,26.7570000,72.1960000);
                }
                PlayerUpdateFood[playerid] = repeat UpdateFoodPlayer(playerid);
            }
            else{
                ApplyAnimation(playerid, "FOOD", "FF_Sit_Look", 3.0, 1, 0, 0, 1, 0);
            }
            
            PlayerSitTable[playerid] = 3;
            EntranceData[PlayerData[playerid][pEntranceIndex]][entranceTable4][PlayerSitTable[playerid]] = true;
            PlayerTable[playerid] = 4;
            SendClientMessage(playerid, COLOR_YELLOW, "กดปุ่ม 'N' เพื่อลุกจากที่นั่ง และ ยกเลิกการรับประทาน");
        }
    }
    return 1;
}

PlayerBuyFoodShop(playerid, type = 1){
    new string[128];
    if(type == 1){
        for(new i=0; i<14; i++){
            PlayerTextDrawHide(playerid, FoodShop[playerid][i]);
            PlayerTextDrawDestroy(playerid, FoodShop[playerid][i]);
        }
        CancelSelectTextDraw(playerid);
        format(string, sizeof string, "คุณแน่ใจหรือไม่ที่ต้องการซื้ออาหารเซ็ตนี้ในราคา %s", FormatNumber(Food1));
        Dialog_ShowEasy(playerid, BuyFood1, DIALOG_STYLE_MSGBOX, "ซื้อ Food Set 1", string, "ซื้อ", "ยกเลิก");
    }
    else if(type == 2){
        for(new i=0; i<14; i++){
            PlayerTextDrawHide(playerid, FoodShop[playerid][i]);
            PlayerTextDrawDestroy(playerid, FoodShop[playerid][i]);
        }
        CancelSelectTextDraw(playerid);
        format(string, sizeof string, "คุณแน่ใจหรือไม่ที่ต้องการซื้ออาหารเซ็ตนี้ในราคา %s", FormatNumber(Food2));
        Dialog_ShowEasy(playerid, BuyFood2, DIALOG_STYLE_MSGBOX, "ซื้อ Food Set 2", string, "ซื้อ", "ยกเลิก");
    }
    else if(type == 3){
        for(new i=0; i<14; i++){
            PlayerTextDrawHide(playerid, FoodShop[playerid][i]);
            PlayerTextDrawDestroy(playerid, FoodShop[playerid][i]);
        }
        CancelSelectTextDraw(playerid);
        format(string, sizeof string, "ราคา Energy Drink ขวดละ $%d\nกรอกจำนวนที่คุณต้องการจะซื้อ:", EnergyDrink);
        Dialog_ShowEasy(playerid, BuyEnergyDrink, DIALOG_STYLE_INPUT, "ซื้อ Energy Drink", string, "ตกลง", "ยกเลิก");
    }
    return 1;
}

Dialog:BuyFood1(playerid, response, listitem, inputtext[]){
    if(!response){
        return 1;
    }
    if(response){
        if(GetMoney(playerid) < Food1){
            ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะซื้ออาหารเซ็ตนี้");
            return 1;
        }

        GiveMoney(playerid, -Food1, "Buy Food1");
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
        SetPlayerAttachedObject(playerid,9,2218,6,0.017000,0.119000,0.064000,-122.000053,19.900026,-27.699998,1.000000,1.000000,1.000000);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ซื้ออาหารเซ็ตที่ 1 ในราคา %s เรียบร้อยแล้ว", FormatNumber(Food1));
        SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: ให้คุณเดินไปที่โต๊ะจากนั้นกด Y เพื่อเลือกที่นั่งรับประทานได้เลย");
        SendClientMessage(playerid, COLOR_RED, "[คำเตือน]: กดปุ่ม 'N' เพื่อทิ้งถาดอาหาร");
        PlayerCarryFood[playerid] = true;
        PlayerOpenFoodShop[playerid] = false;
        PlayerCarryFoodType[playerid] = 1;
    }
    return 1;
}

Dialog:BuyFood2(playerid, response, listitem, inputtext[]){
    if(!response){
        return 1;
    }
    if(response){
        if(GetMoney(playerid) < Food2){
            ErrorMsg(playerid, "คุณมีเงินไม่พอที่จะซื้ออาหารเซ็ตนี้");
            return 1;
        }

        GiveMoney(playerid, -Food2, "Buy Food2");
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
        SetPlayerAttachedObject(playerid,9,2217,6,0.034000,0.174000,0.108999,-122.800025,20.500038,-32.800010,1.000000,1.000000,1.000000);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ซื้ออาหารเซ็ตที่ 2 ในราคา %s เรียบร้อยแล้ว", FormatNumber(Food2));
        SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: ให้คุณเดินไปที่โต๊ะจากนั้นกด Y เพื่อเลือกที่นั่งรับประทานได้เลย");
        SendClientMessage(playerid, COLOR_RED, "[คำเตือน]: กดปุ่ม 'N' เพื่อทิ้งถาดอาหาร");
        PlayerCarryFood[playerid] = true;
        PlayerOpenFoodShop[playerid] = false;
        PlayerCarryFoodType[playerid] = 2;
    }
    return 1;
}

Dialog:BuyEnergyDrink(playerid, response, listitem, inputtext[]){
    if(!response){
        PlayerOpenFoodShop[playerid] = false;
        return 1;
    }
    if(response){
        new string[128];
        new amount = strval(inputtext);
        if(amount <= 0 || amount > 50){
            format(string, sizeof string, "[!] คุณต้องกรอกจำนวนมากกว่า 0 และไม่มากกว่า 50 ขวด\nราคา Energy Drink ขวดละ $%d\nกรอกจำนวนที่คุณต้องการจะซื้อ:", EnergyDrink);
            Dialog_ShowEasy(playerid, BuyEnergyDrink, DIALOG_STYLE_INPUT, "ซื้อ Energy Drink", string, "ตกลง", "ยกเลิก");
            return 1;
        }

        new price = amount * EnergyDrink;
        if(GetMoney(playerid) < price){
            format(string, sizeof string, "[!] คุณมีเงินไม่พอกับจำนวนที่กรอก (ขาดอีก: %s)\nราคา Energy Drink ขวดละ $%d\nกรอกจำนวนที่คุณต้องการจะซื้อ:", FormatNumber(price - GetMoney(playerid)), EnergyDrink);
            Dialog_ShowEasy(playerid, BuyEnergyDrink, DIALOG_STYLE_INPUT, "ซื้อ Energy Drink", string, "ตกลง", "ยกเลิก");
            return 1;
        }

        new id = PlayerInventory_AddItem(playerid, "Energy Drink", 1544, amount);
        if (id == -1) return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
        GiveMoney(playerid, -price, "Buy Energy Drink");
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ซื้อ 'Energy Drink' จำนวน %d ขวดในราคา %s เรียบร้อยแล้ว", amount, FormatNumber(price));
        PlayerOpenFoodShop[playerid] = false;
    }
    return 1;
}

PlayerFoodShopMenu_Show(playerid){
    LoadPlayerFoodShopTextDraw(playerid);

    new string[128];

    format(string, sizeof string, "$%d", Food1);
    PlayerTextDrawSetString(playerid, FoodShop[playerid][4], string);

    format(string, sizeof string, "$%d", Food2);
    PlayerTextDrawSetString(playerid, FoodShop[playerid][7], string);

    format(string, sizeof string, "%d", EnergyDrink);
    PlayerTextDrawSetString(playerid, FoodShop[playerid][11], string);

    for(new i=0; i<14; i++){
        PlayerTextDrawShow(playerid, FoodShop[playerid][i]);
    }

    SelectTextDraw(playerid, 0xFF3600AA);
    PlayerOpenFoodShop[playerid] = true;
    return 1;
}

PlayerFoodShopMenu_Hide(playerid){
    for(new i=0; i<14; i++){
        PlayerTextDrawHide(playerid, FoodShop[playerid][i]);
        PlayerTextDrawDestroy(playerid, FoodShop[playerid][i]);
    }
    CancelSelectTextDraw(playerid);
    PlayerOpenFoodShop[playerid] = false;
    return 1;
}

LoadPlayerFoodShopTextDraw(playerid){
    FoodShop[playerid][0] = CreatePlayerTextDraw(playerid, 323.000000, 161.000000, "_");
    PlayerTextDrawFont(playerid, FoodShop[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][0], 1.474999, 20.250034);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][0], 298.500000, 390.000000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][0], 2);
    PlayerTextDrawColor(playerid, FoodShop[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][0], 135);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][0], 0);

    FoodShop[playerid][1] = CreatePlayerTextDraw(playerid, 324.000000, 148.000000, "Food Shop");
    PlayerTextDrawFont(playerid, FoodShop[playerid][1], 3);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][1], 0.566666, 2.649999);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][1], 400.000000, 137.000000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][1], 2);
    PlayerTextDrawColor(playerid, FoodShop[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][1], 0);

    FoodShop[playerid][2] = CreatePlayerTextDraw(playerid, 508.000000, 153.000000, "ld_chat:thumbdn");
    PlayerTextDrawFont(playerid, FoodShop[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][2], 17.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][2], 1);
    PlayerTextDrawColor(playerid, FoodShop[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][2], 1);

    FoodShop[playerid][3] = CreatePlayerTextDraw(playerid, 152.000000, 199.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, FoodShop[playerid][3], 5);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][3], 79.000000, 87.500000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][3], 1);
    PlayerTextDrawColor(playerid, FoodShop[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][3], -1094795726);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][3], -741092353);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][3], 1);
    PlayerTextDrawSetPreviewModel(playerid, FoodShop[playerid][3], 2218);
    PlayerTextDrawSetPreviewRot(playerid, FoodShop[playerid][3], -34.000000, 19.000000, -355.000000, 1.269999);
    PlayerTextDrawSetPreviewVehCol(playerid, FoodShop[playerid][3], 1, 1);

    FoodShop[playerid][4] = CreatePlayerTextDraw(playerid, 191.000000, 181.000000, "$100");
    PlayerTextDrawFont(playerid, FoodShop[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][4], 0.329166, 1.450000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][4], 400.000000, 76.000000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][4], 2);
    PlayerTextDrawColor(playerid, FoodShop[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][4], -1094795726);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][4], 0);

    FoodShop[playerid][5] = CreatePlayerTextDraw(playerid, 191.000000, 293.000000, "Hungry + 30");
    PlayerTextDrawFont(playerid, FoodShop[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][5], 0.245833, 1.350000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][5], 400.000000, 76.000000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][5], 2);
    PlayerTextDrawColor(playerid, FoodShop[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][5], -1094795726);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][5], 0);

    FoodShop[playerid][6] = CreatePlayerTextDraw(playerid, 191.000000, 314.000000, "Thirty + 30");
    PlayerTextDrawFont(playerid, FoodShop[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][6], 0.245833, 1.350000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][6], 400.000000, 76.000000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][6], 2);
    PlayerTextDrawColor(playerid, FoodShop[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][6], -1094795726);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][6], 0);

    FoodShop[playerid][7] = CreatePlayerTextDraw(playerid, 322.000000, 181.000000, "$200");
    PlayerTextDrawFont(playerid, FoodShop[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][7], 0.329166, 1.450000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][7], 400.000000, 76.000000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][7], 2);
    PlayerTextDrawColor(playerid, FoodShop[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][7], -1094795726);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][7], 0);

    FoodShop[playerid][8] = CreatePlayerTextDraw(playerid, 283.000000, 199.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, FoodShop[playerid][8], 5);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][8], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][8], 79.000000, 87.500000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][8], 1);
    PlayerTextDrawColor(playerid, FoodShop[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][8], -1094795726);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][8], -741092353);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][8], 1);
    PlayerTextDrawSetPreviewModel(playerid, FoodShop[playerid][8], 2217);
    PlayerTextDrawSetPreviewRot(playerid, FoodShop[playerid][8], -34.000000, 19.000000, -355.000000, 1.269999);
    PlayerTextDrawSetPreviewVehCol(playerid, FoodShop[playerid][8], 1, 1);

    FoodShop[playerid][9] = CreatePlayerTextDraw(playerid, 322.000000, 293.000000, "Hungry + 40");
    PlayerTextDrawFont(playerid, FoodShop[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][9], 0.245833, 1.350000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][9], 400.000000, 76.000000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][9], 2);
    PlayerTextDrawColor(playerid, FoodShop[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][9], -1094795726);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][9], 0);

    FoodShop[playerid][10] = CreatePlayerTextDraw(playerid, 322.000000, 314.000000, "Thirty + 40");
    PlayerTextDrawFont(playerid, FoodShop[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][10], 0.245833, 1.350000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][10], 400.000000, 76.000000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][10], 2);
    PlayerTextDrawColor(playerid, FoodShop[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][10], -1094795726);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][10], 0);

    FoodShop[playerid][11] = CreatePlayerTextDraw(playerid, 453.000000, 181.000000, "$100");
    PlayerTextDrawFont(playerid, FoodShop[playerid][11], 1);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][11], 0.329166, 1.450000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][11], 400.000000, 76.000000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][11], 2);
    PlayerTextDrawColor(playerid, FoodShop[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][11], -1094795726);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][11], 0);

    FoodShop[playerid][12] = CreatePlayerTextDraw(playerid, 414.000000, 199.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, FoodShop[playerid][12], 5);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][12], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][12], 79.000000, 87.500000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][12], 1);
    PlayerTextDrawColor(playerid, FoodShop[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][12], -1094795726);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][12], -741092353);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][12], 1);
    PlayerTextDrawSetPreviewModel(playerid, FoodShop[playerid][12], 1544);
    PlayerTextDrawSetPreviewRot(playerid, FoodShop[playerid][12], -5.000000, 1.000000, -357.000000, 1.269999);
    PlayerTextDrawSetPreviewVehCol(playerid, FoodShop[playerid][12], 1, 1);

    FoodShop[playerid][13] = CreatePlayerTextDraw(playerid, 453.500000, 293.000000, "Energry + 50");
    PlayerTextDrawFont(playerid, FoodShop[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, FoodShop[playerid][13], 0.245833, 1.350000);
    PlayerTextDrawTextSize(playerid, FoodShop[playerid][13], 400.000000, 76.000000);
    PlayerTextDrawSetOutline(playerid, FoodShop[playerid][13], 0);
    PlayerTextDrawSetShadow(playerid, FoodShop[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, FoodShop[playerid][13], 2);
    PlayerTextDrawColor(playerid, FoodShop[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, FoodShop[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, FoodShop[playerid][13], -1094795726);
    PlayerTextDrawUseBox(playerid, FoodShop[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, FoodShop[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, FoodShop[playerid][13], 0);
    return 1;
}