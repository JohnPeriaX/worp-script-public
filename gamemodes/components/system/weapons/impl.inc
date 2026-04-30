#if defined _inc_impl
	#undef _inc_impl
#endif

OnPlayerReloadAmmo1(playerid, weaponid){
    if(weaponid == 31){
        if(PlayerData[playerid][pMyAmmo][0] == 0){
            if(PlayerInventory_AllCount(playerid, "5.56x45mm") > 0){
                PlayerInventory_Remove(playerid, "5.56x45mm", 1);
                PlayerData[playerid][pMyAmmo][0] = 30;
                RemoveAttachedObject(playerid, 5);
                GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][0], PlayerData[playerid][pMyAmmo][0]);
                PlayerPlaySoundEx(playerid, 36401);
                PlayReloadAnimation(playerid, weaponid);
            }
        }
    }
    return 1;
}

OnPlayerReloadAmmo2(playerid, weaponid){
    if(weaponid == 22){
        if(PlayerData[playerid][pMyAmmo][1] == 0){
            if(PlayerInventory_AllCount(playerid, "9mm") > 0){
                PlayerInventory_Remove(playerid, "9mm", 1);
                PlayerData[playerid][pMyAmmo][1] = 17;
                RemoveAttachedObject(playerid, 6);
                GivePlayerWeapon(playerid, PlayerData[playerid][pMyWeapon][1], PlayerData[playerid][pMyAmmo][1]);
                PlayerPlaySoundEx(playerid, 36401);
                PlayReloadAnimation(playerid, weaponid);
            }
        }
    }
    return 1;
}

//เพิ่มอาวุธ
OnPlayerStoreWeapon1(playerid, weaponid){

    if(weaponid != 0){

        if(PlayerData[playerid][pDelayWeapon][0] > 0)
            return SendClientMessageEx(playerid, COLOR_RED, "- คุณต้องรอเวลาอีก %d วินาที ถึงจะเก็บอาวุธ %s ได้", PlayerData[playerid][pDelayWeapon][0], ReturnWeaponName(PlayerData[playerid][pMyWeapon][0]));

        if(weaponid == 31){

            new id = PlayerInventory_AddItem(playerid, "M4A1", 356, 1, PlayerData[playerid][pMyAmmo][0], PlayerData[playerid][pMyWeaponLevel][0]);
            if (id == -1){
                return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            }
        }

        Log_Write("logs/storeweapon.txt", "[%s] %s Store Weapon %s", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][0]));
        PlayerData[playerid][pMyWeapon][0] = 0;
        PlayerData[playerid][pMyAmmo][0] = 0;
        PlayerData[playerid][pMyWeaponLevel][0] = 0;
        ResetWeapon(playerid);  
        Character_Save(playerid);
        if(PlayerInventoryStatus[playerid]) {
            OnPlayerInventory_Render(playerid);
            RemoveUseInfoButton(playerid);
        }
        if(PlayerCharacterShow[playerid]) PlayerCharacterTD_Render(playerid);
    }
    else{
        ErrorMsg(playerid, "เกิดข้อผิดพลาด");
        PlayerData[playerid][pMyWeapon][0] = 0;
        PlayerData[playerid][pMyAmmo][0] = 0;
        PlayerData[playerid][pMyWeaponLevel][0] = 0;
        ResetWeapon(playerid);
        Character_Save(playerid);
        return 1;
    }
    return 1;
}

OnPlayerStoreWeapon2(playerid, weaponid){

    if(weaponid != 0){
        if(PlayerData[playerid][pDelayWeapon][1] > 0)
            return SendClientMessageEx(playerid, COLOR_RED, "- คุณต้องรอเวลาอีก %d วินาที ถึงจะเก็บอาวุธ %s ได้", PlayerData[playerid][pDelayWeapon][1], ReturnWeaponName(PlayerData[playerid][pMyWeapon][1]));

        if(weaponid == 22){
            new id = PlayerInventory_AddItem(playerid, "Clot 45", 346, 1, PlayerData[playerid][pMyAmmo][1], PlayerData[playerid][pMyWeaponLevel][1]);
            if (id == -1){
                return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
            }
        }
        Log_Write("logs/storeweapon.txt", "[%s] %s Store Weapon %s", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][1]));
        PlayerData[playerid][pMyWeapon][1] = 0;
        PlayerData[playerid][pMyAmmo][1] = 0;
        PlayerData[playerid][pMyWeaponLevel][1] = 0;
        ResetWeapon(playerid);
        RemoveAttachedObject(playerid, 6);
        Character_Save(playerid);
        if(PlayerInventoryStatus[playerid]) {
            OnPlayerInventory_Render(playerid);
            RemoveUseInfoButton(playerid);
        }
        if(PlayerCharacterShow[playerid]) PlayerCharacterTD_Render(playerid);
    }
    else{
        ErrorMsg(playerid, "เกิดข้อผิดพลาด");
        PlayerData[playerid][pMyWeapon][1] = 0;
        PlayerData[playerid][pMyAmmo][1] = 0;
        PlayerData[playerid][pMyWeaponLevel][1] = 0;
        ResetWeapon(playerid);
        RemoveAttachedObject(playerid, 6);
        Character_Save(playerid);
        return 1;
    }
    return 1;
}

OnPlayerStoreWeapon3(playerid, weaponid){

    if(weaponid != 0){
        if(PlayerData[playerid][pDelayWeapon][2] > 0)
            return SendClientMessageEx(playerid, COLOR_RED, "- คุณต้องรอเวลาอีก %d วินาที ถึงจะเก็บอาวุธ %s ได้", PlayerData[playerid][pDelayWeapon][2], ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]));
    
        if(weaponid == 1){
            if(PlayerData[playerid][pMyAmmo][2] <= 0)
                return ErrorMsg(playerid, "เกิดบัคบางอย่างกรุณาแจ้งแอดมิน");

            if(PlayerData[playerid][pMyAmmo][2] >= 1){
                new id = PlayerInventory_AddItem(playerid, "Brass knuckles", 331, 1, 0, PlayerData[playerid][pMyWeaponLevel][2]);
                if (id == -1){
                    Log_Write("logs/storeweapon.txt", "[%s] %s Can't Add %s to Inv", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]));
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }
            }
        }
        if(weaponid == 2){
            if(PlayerData[playerid][pMyAmmo][2] <= 0)
                return ErrorMsg(playerid, "เกิดบัคบางอย่างกรุณาแจ้งแอดมิน");

            if(PlayerData[playerid][pMyAmmo][2] >= 1){
                new id = PlayerInventory_AddItem(playerid, "Golf Club", 333, 1, 0, PlayerData[playerid][pMyWeaponLevel][2]);
                if (id == -1){
                    Log_Write("logs/storeweapon.txt", "[%s] %s Can't Add %s to Inv", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]));
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }
            }
        }
        if(weaponid == 5){
            if(PlayerData[playerid][pMyAmmo][2] <= 0)
                return ErrorMsg(playerid, "เกิดบัคบางอย่างกรุณาแจ้งแอดมิน");

            if(PlayerData[playerid][pMyAmmo][2] >= 1){
                new id = PlayerInventory_AddItem(playerid, "Baseball bat", 336, 1, 0, PlayerData[playerid][pMyWeaponLevel][2]);
                if (id == -1){
                    Log_Write("logs/storeweapon.txt", "[%s] %s Can't Add %s to Inv", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]));
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }
            }
        }
        if(weaponid == 6){
            if(PlayerData[playerid][pMyAmmo][2] <= 0)
                return ErrorMsg(playerid, "เกิดบัคบางอย่างกรุณาแจ้งแอดมิน");

            if(PlayerData[playerid][pMyAmmo][2] >= 1){
                new id = PlayerInventory_AddItem(playerid, "Shovel", 337, 1, 0, PlayerData[playerid][pMyWeaponLevel][2]);
                if (id == -1){
                    Log_Write("logs/storeweapon.txt", "[%s] %s Can't Add %s to Inv", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]));
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }
            }
        }
        if(weaponid == 7){
            if(PlayerData[playerid][pMyAmmo][2] <= 0)
                return ErrorMsg(playerid, "เกิดบัคบางอย่างกรุณาแจ้งแอดมิน");

            if(PlayerData[playerid][pMyAmmo][2] >= 1){
                new id = PlayerInventory_AddItem(playerid, "Pool cue", 338, 1, 0, PlayerData[playerid][pMyWeaponLevel][2]);
                if (id == -1){
                    Log_Write("logs/storeweapon.txt", "[%s] %s Can't Add %s to Inv", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]));
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }
            }
        }
        if(weaponid == 8){
            if(PlayerData[playerid][pMyAmmo][2] <= 0)
                return ErrorMsg(playerid, "เกิดบัคบางอย่างกรุณาแจ้งแอดมิน");

            if(PlayerData[playerid][pMyAmmo][2] >= 1){
                new id = PlayerInventory_AddItem(playerid, "Katana", 339, 1, 0, PlayerData[playerid][pMyWeaponLevel][2]);
                if (id == -1){
                    Log_Write("logs/storeweapon.txt", "[%s] %s Can't Add %s to Inv", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]));
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }
            }
        }
        if(weaponid == 15){
            if(PlayerData[playerid][pMyAmmo][2] <= 0)
                return ErrorMsg(playerid, "เกิดบัคบางอย่างกรุณาแจ้งแอดมิน");

            if(PlayerData[playerid][pMyAmmo][2] >= 1){
                new id = PlayerInventory_AddItem(playerid, "Cane", 326, 1, 0, PlayerData[playerid][pMyWeaponLevel][2]);
                if (id == -1){
                    Log_Write("logs/storeweapon.txt", "[%s] %s Can't Add %s to Inv", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]));
                    return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
                }
            }
        }
        Log_Write("logs/storeweapon.txt", "[%s] %s Store Weapon %s Level %d", ReturnDate(), ReturnRoleplayName(playerid), ReturnWeaponName(PlayerData[playerid][pMyWeapon][2]), PlayerData[playerid][pMyWeaponLevel][2]);
        PlayerData[playerid][pMyWeapon][2] = 0;
        PlayerData[playerid][pMyAmmo][2] = 0;
        PlayerData[playerid][pMyWeaponLevel][2] = 0;
        RemoveAttachedObject(playerid, 4);
        ResetWeapon(playerid);
        Character_Save(playerid);
        if(PlayerInventoryStatus[playerid]) {
            OnPlayerInventory_Render(playerid);
            RemoveUseInfoButton(playerid);
        }
        if(PlayerCharacterShow[playerid]) PlayerCharacterTD_Render(playerid);
    }
    else{
        ErrorMsg(playerid, "เกิดข้อผิดพลาด");
        PlayerData[playerid][pMyWeapon][2] = 0;
        PlayerData[playerid][pMyAmmo][2] = 0;
        PlayerData[playerid][pMyWeaponLevel][2] = 0;
        RemoveAttachedObject(playerid, 4);
        ResetWeapon(playerid);
        Character_Save(playerid);
        return 1;
    }
    return 1;
}

SetPlayerObjectWeapon(playerid, weaponid){
    if(weaponid == 31){
        SetPlayerAttachedObject(playerid,5,356,6,-0.001999,0.000000,0.018999,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
    }
    if(weaponid == 22){
        SetPlayerAttachedObject(playerid,6,346,6,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
    }
    return 1;
}

CheckItemIsWeaponAssaultRifle(playerid, itemid){
    if(itemid != -1){
        if(!strcmp(Inventory_Player[playerid][itemid][itemName], "M4A1", true))
            return 1;
    }
    return -1;
}

CheckItemIsWeaponPistol(playerid, itemid){
    if(itemid != -1){
        if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Clot 45", true))
            return 1;
    }
    return -1;
}

CheckItemIsWeaponMelee(playerid, itemid){
    if(itemid != -1){
        if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Baseball bat", true))
            return 1;
        
        if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Pool cue", true))
            return 1;

        if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Cane", true))
            return 1;

        if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Katana", true))
            return 1;

        if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Golf Club", true))
            return 1;

        if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Shovel", true))
            return 1;

        if(!strcmp(Inventory_Player[playerid][itemid][itemName], "Brass knuckles", true))
            return 1;
    }
    return -1;
}