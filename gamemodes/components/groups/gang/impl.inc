#if defined _inc_impl
	#undef _inc_impl
#endif

ShowPlayerLockerGang(playerid, id){
	new caption[128], string[128];
	format(caption, sizeof(caption), "Locker ของ %s", GroupData[id][groupName]);
	format(string, sizeof(string), "- คลังเงินเขียว\n- คลังเงินแดง\n- คลัง ไม้, ดินปืน, เหล็ก\n- บัพแก๊ง\n- สกินแก๊ง\n- คลังอาวุธแก๊ง");
	Dialog_ShowEasy(playerid, LockerGang, DIALOG_STYLE_LIST, caption, string, "เลือก", "ยกเลิก");
	return 1;
}

Dialog:LockerGang(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    new string[256];
    if(response){
        if(listitem == 0){
            if(GetGroupType(playerid) == GROUP_GANG){
                if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                    format(string, sizeof(string), "เงินในคลัง: %s", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
                    Dialog_ShowEasy(playerid, MoneyLockerGangShow, DIALOG_STYLE_LIST, "คลังเงิน", string, "ตกลง", "ยกเลิก");
                }
                else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                    format(string, sizeof(string), "เงินในคลัง: %s", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
                    Dialog_ShowEasy(playerid, MoneyLockerGang, DIALOG_STYLE_LIST, "คลังเงิน", string, "ตกลง", "ยกเลิก");
                }
            }
        }
        if(listitem == 1){
            if(GetGroupType(playerid) == GROUP_GANG){
                if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                    format(string, sizeof(string), "เงินแดงในคลัง: %s", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupRedMoney]));
                    Dialog_ShowEasy(playerid, RedMoneyLockerGangShow, DIALOG_STYLE_LIST, "คลังเงินแดง", string, "ตกลง", "ยกเลิก");
                }
                else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                    format(string, sizeof(string), "เงินแดงในคลัง: %s", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupRedMoney]));
                    Dialog_ShowEasy(playerid, RedMoneyLockerGang, DIALOG_STYLE_LIST, "คลังเงินแดง", string, "ตกลง", "ยกเลิก");
                }
            }
        }
        if(listitem == 2){
            if(GetGroupType(playerid) == GROUP_GANG){
                if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                    format(string, sizeof string, "- ไม้ในคลัง: %s\
                    \n- ดินปืนในคลัง: %s\
                    \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                    Dialog_ShowEasy(playerid, GroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
                }
                else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                    format(string, sizeof string, "- ไม้ในคลัง: %s\
                    \n- ดินปืนในคลัง: %s\
                    \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                    Dialog_ShowEasy(playerid, LeadGroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
                }
            }
        }
        if(listitem == 3){
            new skill1[32], skill2[32], skill3[32], skill4[32], skill5[32];
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][0] == 1) skill1 = "มีแล้ว";
            else skill1 = "ยังไม่มี";
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][1] == 1) skill2 = "มีแล้ว";
            else skill2 = "ยังไม่มี";
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][2] == 1) skill3 = "มีแล้ว";
            else skill3 = "ยังไม่มี";
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][3] == 1) skill4 = "มีแล้ว";
            else skill4 = "ยังไม่มี";
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][4] == 1) skill5 = "มีแล้ว";
            else skill5 = "ยังไม่มี";

            format(string, sizeof(string), "- บัพสกิล Level 1 [%s]\
            \n- บัพสกิล Level 2 [%s]\
            \n- บัพสกิล Level 3 [%s]\
            \n- บัพสกิล Level 4 [%s]\
            \n- บัพสกิล Level 5 [%s]", skill1, skill2, skill3, skill4, skill5);

            if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                Dialog_ShowEasy(playerid, SkillsGangShow, DIALOG_STYLE_LIST, "สกิลบัพสำหรับแก๊ง", string, "เลือก", "ยกเลิก");
            }
            else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                Dialog_ShowEasy(playerid, SkillsGang, DIALOG_STYLE_LIST, "สกิลบัพสำหรับแก๊ง", string, "เลือก", "ยกเลิก");
            }
        }
        if(listitem == 4){
            ShowGroupSkin(playerid, PlayerData[playerid][pGroup]);
        }
        if(listitem == 5){
            if(ServerData[ServerCanWdWeaponGang]) return ErrorMsg(playerid, "ระบบนี้ถูกปิดใช้งานอยู่");
            new groupid = PlayerData[playerid][pGroup];
            for (new i = 0; i < 10; i ++){
                if (GroupData[groupid][groupWeapons][i])
                    format(string, sizeof(string), "%sอาวุธ %d: %s (%d)\n", string, i + 1, ReturnWeaponName(GroupData[groupid][groupWeapons][i]), GroupData[groupid][groupAmmo][i]);
                else format(string, sizeof(string), "%sว่าง\n", string);
            }
            Dialog_ShowEasy(playerid, LockerGangWeapons, DIALOG_STYLE_LIST, "คลังอาวุธแก๊ง", string, "เลือก", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:LockerGangWeapons(playerid, response, listitem, inputtext[]){
	new groupid = PlayerData[playerid][pGroup];
	if (groupid == -1) return 0;
	if (response){
	    new
	        weaponid = GroupData[groupid][groupWeapons][listitem],
	        ammo = GroupData[groupid][groupAmmo][listitem];

	    if (weaponid != 0){  

            if(ServerData[ServerWeaponGangNotItem] == 0){
                if(PlayerData[playerid][pGroupRank] < 3) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติให้เบิกอาวุธแก๊ง");
                if(GroupData[groupid][groupWood] < 50) return ErrorMsg(playerid, "จำนวนไม้ในคลังไม่เพียงพอ (50)");
                if(GroupData[groupid][groupPowder] < 10) return ErrorMsg(playerid, "จำนวนดินปืนในคลังไม่เพียงพอ (10)");
                if(GroupData[groupid][groupOre] < 50) return ErrorMsg(playerid, "จำนวนเหล็กในคลังไม่เพียงพอ (50)");
                if(GroupData[groupid][groupRedMoney] < 1000) return ErrorMsg(playerid, "จำนวนเงินแดงในคลังไม่เพียงพอ ($1,000)");
                if(GetMoney(playerid) < 3000) return ErrorMsg(playerid, "จำนวนเงินเขียวในตัวคุณไม่เพียงพอ ($1,000)");
                
                GroupData[groupid][groupWood] -= 50;
                GroupData[groupid][groupPowder] -= 10;
                GroupData[groupid][groupOre] -= 50;
                GroupData[groupid][groupRedMoney] -= 1000;
                GiveMoney(playerid, -3000, "Take Gun Gang");
                Group_Save(groupid);
            }
            GivePlayerWeapon(playerid, weaponid, ammo);
            SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้หยิบอาวุธ %s ออกจากคลังแก๊ง ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid), ReturnWeaponName(weaponid));
		}
	}
	return 1;
}

Dialog:GroupStorageOther(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[128];
        new groupid = PlayerData[playerid][pGroup];
        if(listitem == 0){
            format(string, sizeof string, "ไม้ในคลัง: %s\nไม้ในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupWood]), PlayerInventory_AllCount(playerid, "Wood"));
            Dialog_ShowEasy(playerid, InputWoodGang, DIALOG_STYLE_INPUT, "คลังไม้", string, "ตกลง", "กลับ");
        }
        if(listitem == 1){
            format(string, sizeof string, "ดินปืนในคลัง: %s\nดินปืนในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupPowder]), PlayerInventory_AllCount(playerid, "Gun Powder"));
            Dialog_ShowEasy(playerid, InputPowderGang, DIALOG_STYLE_INPUT, "คลังดินปืน", string, "ตกลง", "กลับ");
        }
        if(listitem == 2){
            format(string, sizeof string, "เหล็กในคลัง: %s\nเหล็กในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupOre]), PlayerInventory_AllCount(playerid, "Ore"));
            Dialog_ShowEasy(playerid, InputOreGang, DIALOG_STYLE_INPUT, "คลังเหล็ก", string, "ตกลง", "กลับ");
        }
    }
    return 1;
}

Dialog:LeadGroupStorageOther(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[128];
        new groupid = PlayerData[playerid][pGroup];
        if(listitem == 0){
            format(string, sizeof string, "ไม้ในคลัง: %s", FormatNumberNotMoney(GroupData[groupid][groupWood]));
            Dialog_ShowEasy(playerid, LeaderWoodGang, DIALOG_STYLE_LIST, string, "- ฝากไม้เข้าคลัง\n- ถอนไม้ออกจากคลัง", "เลือก", "กลับ");
        }
        if(listitem == 1){  
            format(string, sizeof string, "ดินปืนในคลัง: %s", FormatNumberNotMoney(GroupData[groupid][groupPowder]));
            Dialog_ShowEasy(playerid, LeaderPowderGang, DIALOG_STYLE_LIST, string, "- ฝากดินปืนเข้าคลัง\n- ถอนดินปืนออกจากคลัง", "เลือก", "กลับ");
        }
        if(listitem == 2){
            format(string, sizeof string, "เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[groupid][groupOre]));
            Dialog_ShowEasy(playerid, LeaderOreGang, DIALOG_STYLE_LIST, string, "- ฝากเหล็กเข้าคลัง\n- ถอนเหล็กออกจากคลัง", "เลือก", "กลับ");
        }
    }
    return 1;
}

Dialog:LeaderOreGang(playerid, response, listitem, inputtext[]){
    new string[128];
    if(!response){
        if(GetGroupType(playerid) == GROUP_GANG){
            if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, GroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
            else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, LeadGroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
        }
        return 1;
    }
    if(response){
        new groupid = PlayerData[playerid][pGroup];
        if(listitem == 0){
            format(string, sizeof string, "เหล็กในคลัง: %s\nเหล็กในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupOre]), PlayerInventory_AllCount(playerid, "Ore"));
            Dialog_ShowEasy(playerid, InputOreGang, DIALOG_STYLE_INPUT, "คลังเหล็ก", string, "ตกลง", "กลับ");
        }
        if(listitem == 1){
            format(string, sizeof string, "เหล็กในคลัง: %s\nกรอกจำนวนที่ต้องการจะถอนออกจากคลัง", FormatNumberNotMoney(GroupData[groupid][groupOre]));
            Dialog_ShowEasy(playerid, LeaderWithdrawOre, DIALOG_STYLE_INPUT, "คลังเหล็ก", string, "ตกลง", "กลับ");
        }
    }
    return 1;
}

Dialog:LeaderWithdrawOre(playerid, response, listitem, inputtext[]){
    new string[128];
    if(!response){
        if(GetGroupType(playerid) == GROUP_GANG){
            if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, GroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
            else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, LeadGroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
        }
        return 1;
    }
    if(response){
        new groupid = PlayerData[playerid][pGroup];
        new amount = strval(inputtext);
        
        if(amount <= 0){
            format(string, sizeof string, "[!] คุณต้องกรอกจำนวนที่มากกว่า 0 \nเหล็กในคลัง: %s\nกรอกจำนวนที่ต้องการจะถอนออกจากคลัง", FormatNumberNotMoney(GroupData[groupid][groupOre]));
            Dialog_ShowEasy(playerid, LeaderWithdrawOre, DIALOG_STYLE_INPUT, "คลังเหล็ก", string, "ตกลง", "กลับ");
            return 1;
        }

        if(amount > GroupData[groupid][groupOre]){
            format(string, sizeof string, "[!] เหล็กในคลังกลุ่มของคุณมีไม่เพียงพอ \nเหล็กในคลัง: %s\nกรอกจำนวนที่ต้องการจะถอนออกจากคลัง", FormatNumberNotMoney(GroupData[groupid][groupOre]));
            Dialog_ShowEasy(playerid, LeaderWithdrawOre, DIALOG_STYLE_INPUT, "คลังเหล็ก", string, "ตกลง", "กลับ");
            return 1;
        }

        new additem = PlayerInventory_AddItem(playerid, "Ore", 19941, amount);
        if(additem == -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "{FF0000}[!] เกิดข้อผิดพลาด", "{FF0000}กระเป๋าของคุณเต็มไม่สามารถเก็บไอเท็มนี้ได้", "ตกลง", "");
        GroupData[groupid][groupOre] -= amount;
        Group_Save(groupid);
        SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้ทำการถอน เหล็ก จำนวน %d ออกจากคลังกลุ่มแล้ว ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid), amount);
    }
    return 1;
}

Dialog:LeaderPowderGang(playerid, response, listitem, inputtext[]){
    new string[128];
    if(!response){
        if(GetGroupType(playerid) == GROUP_GANG){
            if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, GroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
            else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, LeadGroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
        }
        return 1;
    }
    if(response){
        new groupid = PlayerData[playerid][pGroup];
        if(listitem == 0){
            format(string, sizeof string, "ดินปืนในคลัง: %s\nดินปืนในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupPowder]), PlayerInventory_AllCount(playerid, "Gun Powder"));
            Dialog_ShowEasy(playerid, InputPowderGang, DIALOG_STYLE_INPUT, "คลังดินปืน", string, "ตกลง", "กลับ");
        }
        if(listitem == 1){
            format(string, sizeof string, "ดินปืนในคลัง: %s\nกรอกจำนวนที่ต้องการจะถอนออกจากคลัง", FormatNumberNotMoney(GroupData[groupid][groupPowder]));
            Dialog_ShowEasy(playerid, LeaderWithdrawPowder, DIALOG_STYLE_INPUT, "คลังดินปืน", string, "ตกลง", "กลับ");
        }
    }
    return 1;
}

Dialog:LeaderWithdrawPowder(playerid, response, listitem, inputtext[]){
    new string[128];
    if(!response){
        if(GetGroupType(playerid) == GROUP_GANG){
            if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, GroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
            else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, LeadGroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
        }
        return 1;
    }
    if(response){
        new groupid = PlayerData[playerid][pGroup];
        new amount = strval(inputtext);
        
        if(amount <= 0){
            format(string, sizeof string, "[!] คุณต้องกรอกจำนวนที่มากกว่า 0 \nดินปืนในคลัง: %s\nกรอกจำนวนที่ต้องการจะถอนออกจากคลัง", FormatNumberNotMoney(GroupData[groupid][groupPowder]));
            Dialog_ShowEasy(playerid, LeaderWithdrawPowder, DIALOG_STYLE_INPUT, "คลังดินปืน", string, "ตกลง", "กลับ");
            return 1;
        }

        if(amount > GroupData[groupid][groupPowder]){
            format(string, sizeof string, "[!] ดินปืนในคลังกลุ่มของคุณมีไม่เพียงพอ \nดินปืนในคลัง: %s\nกรอกจำนวนที่ต้องการจะถอนออกจากคลัง", FormatNumberNotMoney(GroupData[groupid][groupPowder]));
            Dialog_ShowEasy(playerid, LeaderWithdrawPowder, DIALOG_STYLE_INPUT, "คลังดินปืน", string, "ตกลง", "กลับ");
            return 1;
        }

        new additem = PlayerInventory_AddItem(playerid, "Gun Powder", 2057, amount);
        if(additem == -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "{FF0000}[!] เกิดข้อผิดพลาด", "{FF0000}กระเป๋าของคุณเต็มไม่สามารถเก็บไอเท็มนี้ได้", "ตกลง", "");
        GroupData[groupid][groupPowder] -= amount;
        Group_Save(groupid);
        SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้ทำการถอน ดินปืน จำนวน %d ออกจากคลังกลุ่มแล้ว ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid), amount);
    }
    return 1;
}

Dialog:LeaderWoodGang(playerid, response, listitem, inputtext[]){
    new string[128];
    if(!response){
        if(GetGroupType(playerid) == GROUP_GANG){
            if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, GroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
            else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, LeadGroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
        }
        return 1;
    }
    if(response){
        new groupid = PlayerData[playerid][pGroup];
        if(listitem == 0){
            format(string, sizeof string, "ไม้ในคลัง: %s\nไม้ในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupWood]), PlayerInventory_AllCount(playerid, "Wood"));
            Dialog_ShowEasy(playerid, InputWoodGang, DIALOG_STYLE_INPUT, "คลังไม้", string, "ตกลง", "กลับ");
        }
        if(listitem == 1){
            format(string, sizeof string, "ไม้ในคลัง: %s\nกรอกจำนวนที่ต้องการจะถอนออกจากคลัง", FormatNumberNotMoney(GroupData[groupid][groupWood]));
            Dialog_ShowEasy(playerid, LeaderWithdrawWood, DIALOG_STYLE_INPUT, "คลังไม้", string, "ตกลง", "กลับ");
        }
    }
    return 1;
}

Dialog:LeaderWithdrawWood(playerid, response, listitem, inputtext[]){
    new string[128];
    if(!response){
        if(GetGroupType(playerid) == GROUP_GANG){
            if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, GroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
            else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, LeadGroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
        }
        return 1;
    }
    if(response){
        new groupid = PlayerData[playerid][pGroup];
        new amount = strval(inputtext);
        
        if(amount <= 0){
            format(string, sizeof string, "[!] คุณต้องกรอกจำนวนที่มากกว่า 0 \nไม้ในคลัง: %s\nกรอกจำนวนที่ต้องการจะถอนออกจากคลัง", FormatNumberNotMoney(GroupData[groupid][groupWood]));
            Dialog_ShowEasy(playerid, LeaderWithdrawWood, DIALOG_STYLE_INPUT, "คลังไม้", string, "ตกลง", "กลับ");
            return 1;
        }

        if(amount > GroupData[groupid][groupWood]){
            format(string, sizeof string, "[!] ไม้ในคลังกลุ่มของคุณมีไม่เพียงพอ \nไม้ในคลัง: %s\nกรอกจำนวนที่ต้องการจะถอนออกจากคลัง", FormatNumberNotMoney(GroupData[groupid][groupWood]));
            Dialog_ShowEasy(playerid, LeaderWithdrawWood, DIALOG_STYLE_INPUT, "คลังไม้", string, "ตกลง", "กลับ");
            return 1;
        }

        new additem = PlayerInventory_AddItem(playerid, "Wood", 19793, amount);
        if(additem == -1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "{FF0000}[!] เกิดข้อผิดพลาด", "{FF0000}กระเป๋าของคุณเต็มไม่สามารถเก็บไอเท็มนี้ได้", "ตกลง", "");
        GroupData[groupid][groupWood] -= amount;
        Group_Save(groupid);
        SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้ทำการถอน ไม้ จำนวน %d ออกจากคลังกลุ่มแล้ว ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid), amount);
    }
    return 1;
}

Dialog:InputOreGang(playerid, response, listitem, inputtext[]){
    new string[128];
    if(!response){
        if(GetGroupType(playerid) == GROUP_GANG){
            if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, GroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
            else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, LeadGroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
        }
        return 1;
    }
    if(response){
        new groupid = PlayerData[playerid][pGroup];
        new amount = strval(inputtext);
        if(amount <= 0){
            format(string, sizeof string, "[!] คุณต้องกรอกจำนวนมากกว่า 0 \nเหล็กในคลัง: %s\nเหล็กในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupOre]), PlayerInventory_AllCount(playerid, "Ore"));
            Dialog_ShowEasy(playerid, InputOreGang, DIALOG_STYLE_INPUT, "คลังเหล็ก", string, "ตกลง", "กลับ");
            return 1;
        }

        if(amount > PlayerInventory_AllCount(playerid, "Ore")){
            format(string, sizeof string, "[!] คุณมีจำนวนเหล็กในกระเป๋าไม่เพียงพอ \nเหล็กในคลัง: %s\nเหล็กในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupOre]), PlayerInventory_AllCount(playerid, "Ore"));
            Dialog_ShowEasy(playerid, InputOreGang, DIALOG_STYLE_INPUT, "คลังเหล็ก", string, "ตกลง", "กลับ");
            return 1;
        }

        PlayerInventory_Remove(playerid, "Ore", amount);
        GroupData[PlayerData[playerid][pGroup]][groupOre] += amount;
        Group_Save(groupid);
        SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้ทำการฝาก เหล็ก จำนวน %d เข้าคลังกลุ่มแล้ว ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid), amount);
    }
    return 1;
}

Dialog:InputPowderGang(playerid, response, listitem, inputtext[]){
    new string[128];
    if(!response){
        if(GetGroupType(playerid) == GROUP_GANG){
            if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, GroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
            else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, LeadGroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
        }
        return 1;
    }
    if(response){
        new groupid = PlayerData[playerid][pGroup];
        new amount = strval(inputtext);
        if(amount <= 0){
            format(string, sizeof string, "[!] คุณต้องกรอกจำนวนมากกว่า 0 \nดินปืนในคลัง: %s\nดินปืนในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupPowder]), PlayerInventory_AllCount(playerid, "Gun Powder"));
            Dialog_ShowEasy(playerid, InputPowderGang, DIALOG_STYLE_INPUT, "คลังดินปืน", string, "ตกลง", "กลับ");
            return 1;
        }

        if(amount > PlayerInventory_AllCount(playerid, "Gun Powder")){
            format(string, sizeof string, "[!] คุณมีจำนวนดินปืนในกระเป๋าไม่เพียงพอ \nดินปืนในคลัง: %s\nดินปืนในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupPowder]), PlayerInventory_AllCount(playerid, "Gun Powder"));
            Dialog_ShowEasy(playerid, InputPowderGang, DIALOG_STYLE_INPUT, "คลังดินปืน", string, "ตกลง", "กลับ");
            return 1;
        }

        PlayerInventory_Remove(playerid, "Gun Powder", amount);
        GroupData[PlayerData[playerid][pGroup]][groupPowder] += amount;
        Group_Save(groupid);
        SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้ทำการฝาก ดินปืน จำนวน %d เข้าคลังกลุ่มแล้ว ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid), amount);
    }
    return 1;
}

Dialog:InputWoodGang(playerid, response, listitem, inputtext[]){
    new string[128];
    if(!response){
        if(GetGroupType(playerid) == GROUP_GANG){
            if(PlayerData[playerid][pGroupRank] < GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, GroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
            else if(PlayerData[playerid][pGroupRank] >= GroupData[PlayerData[playerid][pGroup]][groupRanks]){
                format(string, sizeof string, "- ไม้ในคลัง: %s\
                \n- ดินปืนในคลัง: %s\
                \n- เหล็กในคลัง: %s", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupWood]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupPowder]), FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupOre]));
                Dialog_ShowEasy(playerid, LeadGroupStorageOther, DIALOG_STYLE_LIST, "คลัง ไม้, ดินปืน, เหล็ก", string, "ตกลง", "ยกเลิก");
            }
        }
        return 1;
    }
    if(response){
        new groupid = PlayerData[playerid][pGroup];
        new amount = strval(inputtext);
        if(amount <= 0){
            format(string, sizeof string, "[!] คุณต้องกรอกจำนวนมากกว่า 0 \nไม้ในคลัง: %s\nไม้ในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupWood]), PlayerInventory_AllCount(playerid, "Wood"));
            Dialog_ShowEasy(playerid, InputWoodGang, DIALOG_STYLE_INPUT, "คลังไม้", string, "ตกลง", "กลับ");
            return 1;
        }

        if(amount > PlayerInventory_AllCount(playerid, "Wood")){
            format(string, sizeof string, "[!] คุณมีจำนวนไม้ในกระเป๋าไม่เพียงพอ \nไม้ในคลัง: %s\nไม้ในตัวของคุณ: %d\nกรอกจำนวนที่คุณต้องการจะฝากเข้าคลัง", FormatNumberNotMoney(GroupData[groupid][groupWood]), PlayerInventory_AllCount(playerid, "Wood"));
            Dialog_ShowEasy(playerid, InputWoodGang, DIALOG_STYLE_INPUT, "คลังไม้", string, "ตกลง", "กลับ");
            return 1;
        }

        PlayerInventory_Remove(playerid, "Wood", amount);
        GroupData[PlayerData[playerid][pGroup]][groupWood] += amount;
        Group_Save(groupid);
        SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้ทำการฝาก ไม้ จำนวน %d เข้าคลังกลุ่มแล้ว ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid), amount);
    }
    return 1;
}

Dialog:SkillsGangShow(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[256];
        if(listitem == 0){
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][0] == 0){
                format(string, sizeof(string), "- สกิลบัพ Level 1\
                \n เมื่อแก๊งคุณมีบัพ Level 1 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 1.0 ดาเมจกับทุกอาวุธทุกการโจมตี\
                \n [ ยังไม่มี ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 1", string, "ตกลง", "");
            }
            else{
                format(string, sizeof(string), "- สกิลบัพ Level 1\
                \n เมื่อแก๊งคุณมีบัพ Level 1 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 1.0 ดาเมจกับทุกอาวุธทุกการโจมตี\
                \n [ มีแล้ว ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 1", string, "ตกลง", "");
            }
        }
        if(listitem == 1){
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][1] == 0){
                format(string, sizeof(string), "- สกิลบัพ Level 2\
                \n เมื่อแก๊งคุณมีบัพ Level 2 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 1.5 ดาเมจกับทุกอาวุธทุกการโจมตี\
                \n [ ยังไม่มี ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 2", string, "ตกลง", "");
            }
            else{
                format(string, sizeof(string), "- สกิลบัพ Level 2\
                \n เมื่อแก๊งคุณมีบัพ Level 2 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 1.5 ดาเมจกับทุกอาวุธทุกการโจมตี\
                \n [ มีแล้ว ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 2", string, "ตกลง", "");
            }
        }
        if(listitem == 2){
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][2] == 0){
                format(string, sizeof(string), "- สกิลบัพ Level 3\
                \n เมื่อแก๊งคุณมีบัพ Level 3 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 2.0 ดาเมจกับอาวุธเท่านั้น ยกเว้นหมัดธรรมดา\
                \n [ ยังไม่มี ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 3", string, "ตกลง", "");
            }
            else{
                format(string, sizeof(string), "- สกิลบัพ Level 3\
                \n เมื่อแก๊งคุณมีบัพ Level 3 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 2.0 ดาเมจกับอาวุธเท่านั้น ยกเว้นหมัดธรรมดา\
                \n [ มีแล้ว ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 3", string, "ตกลง", "");
            }
        }
        if(listitem == 3){
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][3] == 0){
                format(string, sizeof(string), "- สกิลบัพ Level 4\
                \n เมื่อแก๊งคุณมีบัพ Level 4 ทุกคนในแก๊งเมื่อครบเวลา PayCheck จะได้ EXP + 1\
                \n [ ยังไม่มี ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 4", string, "ตกลง", "");
            }
            else{
                format(string, sizeof(string), "- สกิลบัพ Level 3\
                \n เมื่อแก๊งคุณมีบัพ Level 4 ทุกคนในแก๊งเมื่อครบเวลา PayCheck จะได้ EXP + 1\
                \n [ มีแล้ว ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 4", string, "ตกลง", "");
            }
        }
        if(listitem == 4){
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][4] == 0){
                format(string, sizeof(string), "- สกิลบัพ Level 5\
                \n เมื่อแก๊งคุณมีบัพ Level 5 ทุกคนในแก๊งเมื่อครบเวลา PayCheck จะได้ EXP + 2\
                \n [ ยังไม่มี ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 5", string, "ตกลง", "");
            }
            else{
                format(string, sizeof(string), "- สกิลบัพ Level 5\
                \n เมื่อแก๊งคุณมีบัพ Level 5 ทุกคนในแก๊งเมื่อครบเวลา PayCheck จะได้ EXP + 2\
                \n [ มีแล้ว ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 5", string, "ตกลง", "");
            }
        }
    }
    return 1;
}

Dialog:UpSkillsLevel1(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(GroupData[PlayerData[playerid][pGroup]][groupSkills][0] == 1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 1", "แก๊งคุณมี บัพสกิล Level 1 อยู่แล้ว", "ตกลง", "");
        if(GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint] < 100) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 1", "คุณมี พ้อยแห่งความสำเร็จแก๊ง ไม่พอ (100)", "ตกลง", "");
        GroupData[PlayerData[playerid][pGroup]][groupSkills][0] = 1;
        GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint] -= 100;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้ทำการอัพเกรด บัพสกิล Level 1 ของแก๊งแล้ว ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid));
    }
    return 1;
}

Dialog:UpSkillsLevel2(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(GroupData[PlayerData[playerid][pGroup]][groupSkills][1] == 1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 2", "แก๊งคุณมี บัพสกิล Level 2 อยู่แล้ว", "ตกลง", "");
        if(GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint] < 200) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 2", "คุณมี พ้อยแห่งความสำเร็จแก๊ง ไม่พอ (200)", "ตกลง", "");
        GroupData[PlayerData[playerid][pGroup]][groupSkills][1] = 1;
        GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint] -= 200;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้ทำการอัพเกรด บัพสกิล Level 2 ของแก๊งแล้ว ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid));
    }
    return 1;
}

Dialog:UpSkillsLevel3(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(GroupData[PlayerData[playerid][pGroup]][groupSkills][2] == 1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 3", "แก๊งคุณมี บัพสกิล Level 3 อยู่แล้ว", "ตกลง", "");
        if(GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint] < 300) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 3", "คุณมี พ้อยแห่งความสำเร็จแก๊ง ไม่พอ (300)", "ตกลง", "");
        GroupData[PlayerData[playerid][pGroup]][groupSkills][2] = 1;
        GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint] -= 300;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้ทำการอัพเกรด บัพสกิล Level 3 ของแก๊งแล้ว ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid));
    }
    return 1;
}

Dialog:UpSkillsLevel4(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(GroupData[PlayerData[playerid][pGroup]][groupSkills][3] == 1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 4", "แก๊งคุณมี บัพสกิล Level 4 อยู่แล้ว", "ตกลง", "");
        if(GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint] < 400) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 4", "คุณมี พ้อยแห่งความสำเร็จแก๊ง ไม่พอ (400)", "ตกลง", "");
        GroupData[PlayerData[playerid][pGroup]][groupSkills][3] = 1;
        GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint] -= 400;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้ทำการอัพเกรด บัพสกิล Level 4 ของแก๊งแล้ว ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid));
    }
    return 1;
}

Dialog:UpSkillsLevel5(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(GroupData[PlayerData[playerid][pGroup]][groupSkills][4] == 1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 5", "แก๊งคุณมี บัพสกิล Level 5 อยู่แล้ว", "ตกลง", "");
        if(GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint] < 500) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 5", "คุณมี พ้อยแห่งความสำเร็จแก๊ง ไม่พอ (500)", "ตกลง", "");
        GroupData[PlayerData[playerid][pGroup]][groupSkills][4] = 1;
        GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint] -= 500;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], 0x00AAFFAA, "(( (%d) %s %s: ได้ทำการอัพเกรด บัพสกิล Level 5 ของแก๊งแล้ว ))", PlayerData[playerid][pGroupRank], Group_GetRank(playerid), ReturnRoleplayName(playerid));
    }
    return 1;
}

Dialog:SkillsGang(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[256];
        if(listitem == 0){
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][0] == 0){
                format(string, sizeof(string), "- สกิลบัพ Level 1\
                \n เมื่อแก๊งคุณมีบัพ Level 1 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 1.0 ดาเมจกับทุกอาวุธทุกการโจมตี\
                \n [ ยังไม่มี ]\
                \n [ ใช้ 'พ้อยแห่งความสำเร็จของแก๊ง' จำนวน [100] พ้อย ]\
                \n [ แก๊งของคุณมี 'พ้อยแห่งความสำเร็จ' อยู่ [%s] พ้อย ]", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint]));
                Dialog_ShowEasy(playerid, UpSkillsLevel1, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 1", string, "อัพเกรด", "ยกเลิก");
            }
            else{
                format(string, sizeof(string), "- สกิลบัพ Level 1\
                \n เมื่อแก๊งคุณมีบัพ Level 1 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 1.0 ดาเมจกับทุกอาวุธทุกการโจมตี\
                \n [ มีแล้ว ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 1", string, "ตกลง", "");
            }
        }
        if(listitem == 1){
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][1] == 0){
                format(string, sizeof(string), "- สกิลบัพ Level 2\
                \n เมื่อแก๊งคุณมีบัพ Level 2 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 1.5 ดาเมจกับทุกอาวุธทุกการโจมตี\
                \n [ ยังไม่มี ]\
                \n [ ใช้ 'พ้อยแห่งความสำเร็จของแก๊ง' จำนวน [200] พ้อย ]\
                \n [ แก๊งของคุณมี 'พ้อยแห่งความสำเร็จ' อยู่ [%s] พ้อย ]", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint]));
                Dialog_ShowEasy(playerid, UpSkillsLevel2, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 2", string, "อัพเกรด", "ยกเลิก");
            }
            else{
                format(string, sizeof(string), "- สกิลบัพ Level 2\
                \n เมื่อแก๊งคุณมีบัพ Level 2 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 1.5 ดาเมจกับทุกอาวุธทุกการโจมตี\
                \n [ มีแล้ว ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 2", string, "ตกลง", "");
            }
        }
        if(listitem == 2){
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][2] == 0){
                format(string, sizeof(string), "- สกิลบัพ Level 3\
                \n เมื่อแก๊งคุณมีบัพ Level 3 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 2.0 ดาเมจกับอาวุธเท่านั้น ยกเว้นหมัดธรรมดา\
                \n [ ยังไม่มี ]\
                \n [ ใช้ 'พ้อยแห่งความสำเร็จของแก๊ง' จำนวน [300] พ้อย ]\
                \n [ แก๊งของคุณมี 'พ้อยแห่งความสำเร็จ' อยู่ [%s] พ้อย ]", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint]));
                Dialog_ShowEasy(playerid, UpSkillsLevel3, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 3", string, "อัพเกรด", "ยกเลิก");
            }
            else{
                format(string, sizeof(string), "- สกิลบัพ Level 3\
                \n เมื่อแก๊งคุณมีบัพ Level 3 ทุกคนในแก๊งของคุณจะมีการเพิ่ม 2.0 ดาเมจกับอาวุธเท่านั้น ยกเว้นหมัดธรรมดา\
                \n [ มีแล้ว ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 3", string, "ตกลง", "");
            }
        }
        if(listitem == 3){
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][3] == 0){
                format(string, sizeof(string), "- สกิลบัพ Level 4\
                \n เมื่อแก๊งคุณมีบัพ Level 4 ทุกคนในแก๊งเมื่อครบเวลา PayCheck จะได้ EXP + 1\
                \n [ ยังไม่มี ]\
                \n [ ใช้ 'พ้อยแห่งความสำเร็จของแก๊ง' จำนวน [400] พ้อย ]\
                \n [ แก๊งของคุณมี 'พ้อยแห่งความสำเร็จ' อยู่ [%s] พ้อย ]", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint]));
                Dialog_ShowEasy(playerid, UpSkillsLevel4, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 4", string, "อัพเกรด", "ยกเลิก");
            }
            else{
                format(string, sizeof(string), "- สกิลบัพ Level 4\
                \n เมื่อแก๊งคุณมีบัพ Level 4 ทุกคนในแก๊งเมื่อครบเวลา PayCheck จะได้ EXP + 1\
                \n [ มีแล้ว ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 4", string, "ตกลง", "");
            }
        }
        if(listitem == 4){
            if(GroupData[PlayerData[playerid][pGroup]][groupSkills][4] == 0){
                format(string, sizeof(string), "- สกิลบัพ Level 5\
                \n เมื่อแก๊งคุณมีบัพ Level 5 ทุกคนในแก๊งเมื่อครบเวลา PayCheck จะได้ EXP + 2\
                \n [ ยังไม่มี ]\
                \n [ ใช้ 'พ้อยแห่งความสำเร็จของแก๊ง' จำนวน [500] พ้อย ]\
                \n [ แก๊งของคุณมี 'พ้อยแห่งความสำเร็จ' อยู่ [%s] พ้อย ]", FormatNumberNotMoney(GroupData[PlayerData[playerid][pGroup]][groupHoldZonePoint]));
                Dialog_ShowEasy(playerid, UpSkillsLevel5, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 5", string, "อัพเกรด", "ยกเลิก");
            }
            else{
                format(string, sizeof(string), "- สกิลบัพ Level 5\
                \n เมื่อแก๊งคุณมีบัพ Level 5 ทุกคนในแก๊งเมื่อครบเวลา PayCheck จะได้ EXP + 2\
                \n [ มีแล้ว ]");
                Dialog_ShowEasy(playerid, UpSkillsLevelShow, DIALOG_STYLE_MSGBOX, "บัพสกิล Level 5", string, "ตกลง", "");
            }
        }
    }
    return 1;
}

Dialog:RedMoneyLockerGangShow(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new string[128];
            format(string, sizeof(string), "เงินแดงในคลัง: %s\nกรอกจำนวนที่ต้องการจะฝาก:", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupRedMoney]));
            Dialog_ShowEasy(playerid, DepoRedMoneyLockerGang, DIALOG_STYLE_INPUT, "คลังเงินแดง > ฝาก", string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:DepoRedMoneyLockerGang(playerid, response, listitem, inputtext[]){
    if(!response)   return 1;
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนเงินมากกว่า 0");

        if(amount > PlayerData[playerid][pRedMoney])
            return ErrorMsg(playerid, "คุณมีเงินแดงไม่พอ");

        PlayerData[playerid][pRedMoney] -= amount;
        GroupData[PlayerData[playerid][pGroup]][groupRedMoney] += amount;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], COLOR_YELLOW, "(( [%s] %s(%d) ได้ทำการฝาก เงินแดง เข้าแก๊งจำนวน: %s ))", Group_GetRank(playerid), ReturnRoleplayName(playerid), playerid, FormatNumber(amount));
    }
    return 1;
}

Dialog:MoneyLockerGangShow(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new string[128];
            format(string, sizeof(string), "เงินในคลัง: %s\nกรอกจำนวนที่ต้องการจะฝาก:", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
            Dialog_ShowEasy(playerid, DepositMoneyLockerGang, DIALOG_STYLE_INPUT, "คลังเงิน > ฝาก", string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:DepositMoneyLockerGang(playerid, response, listitem, inputtext[]){
    if(!response)   return 1;
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนเงินมากกว่า 0");

        if(amount > GetMoney(playerid))
            return ErrorMsg(playerid, "คุณมีเงินไม่พอ");

        GiveMoney(playerid, -amount, "deposit gang");
        GroupData[PlayerData[playerid][pGroup]][groupMoney] += amount;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], COLOR_YELLOW, "(( [%s] %s(%d) ได้ทำการฝากเงินเข้าแก๊งจำนวน: %s ))", Group_GetRank(playerid), ReturnRoleplayName(playerid), playerid, FormatNumber(amount));
    }
    return 1;
}

Dialog:MoneyLockerGang(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new caption[128];
            new string[128];
            format(caption, sizeof(caption), "เงินในคลัง: %s", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
            format(string, sizeof(string), "ฝากเงิน\nถอนเงิน");
            Dialog_ShowEasy(playerid, TypeMoneyLockerGang, DIALOG_STYLE_LIST, caption, string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:TypeMoneyLockerGang(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[128];
        if(listitem == 0){
            format(string, sizeof(string), "เงินในคลัง: %s\nกรอกจำนวนที่ต้องการจะฝาก", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
            Dialog_ShowEasy(playerid, MoneyLeaderGangDeposit, DIALOG_STYLE_INPUT, "ฝากเงิน", string, "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            format(string, sizeof(string), "เงินในคลัง: %s\nกรอกจำนวนที่ต้องการจะถอน", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupMoney]));
            Dialog_ShowEasy(playerid, WithDrawMoneyLockerGang, DIALOG_STYLE_INPUT, "ถอนเงิน", string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:MoneyLeaderGangDeposit(playerid, response, listitem, inputtext[]){
    if(!response)   return 1;
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนเงินมากกว่า 0");

        if(amount > GetMoney(playerid))
            return ErrorMsg(playerid, "คุณมีเงินไม่พอ");

        GiveMoney(playerid, -amount, "deposit gang");
        GroupData[PlayerData[playerid][pGroup]][groupMoney] += amount;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], COLOR_YELLOW, "(( [%s] %s(%d) ได้ทำการฝากเงินเข้าแก๊งจำนวน: %s ))", Group_GetRank(playerid), ReturnRoleplayName(playerid), playerid, FormatNumber(amount));
    }
    return 1;
}

Dialog:WithDrawMoneyLockerGang(playerid, response, listitem, inputtext[]){
    if(!response)   return 1;
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนเงินมากกว่า 0");

        if(amount > GroupData[PlayerData[playerid][pGroup]][groupMoney])
            return ErrorMsg(playerid, "จำนวนเงินในคลังมีไม่เพียงพอ");

        GiveMoney(playerid, amount, "withdraw gang");
        GroupData[PlayerData[playerid][pGroup]][groupMoney] -= amount;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], COLOR_YELLOW, "(( [%s] %s(%d) ได้ทำการเบิกเงินคลังของกลุ่มออกมาจำนวน: %s ))", Group_GetRank(playerid), ReturnRoleplayName(playerid), playerid, FormatNumber(amount));
    }
    return 1;
}

Dialog:RedMoneyLockerGang(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            new caption[128];
            new string[128];
            format(caption, sizeof(caption), "เงินแดงในคลัง: %s", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupRedMoney]));
            format(string, sizeof(string), "ฝากเงินแดง\nถอนเงินแดง");
            Dialog_ShowEasy(playerid, TypeRedMoneyLockerGang, DIALOG_STYLE_LIST, caption, string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:TypeRedMoneyLockerGang(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[128];
        if(listitem == 0){
            format(string, sizeof(string), "เงินแดงในคลัง: %s\nเงินแดงในตัว: %s\nกรอกจำนวนที่ต้องการจะฝาก", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupRedMoney]), FormatNumber(PlayerData[playerid][pRedMoney]));
            Dialog_ShowEasy(playerid, RedMoneyLeaderGangDepo, DIALOG_STYLE_INPUT, "ฝากเงิน", string, "ตกลง", "ยกเลิก");
        }
        if(listitem == 1){
            format(string, sizeof(string), "เงินแดงในคลัง: %s\nกรอกจำนวนที่ต้องการจะถอน", FormatNumber(GroupData[PlayerData[playerid][pGroup]][groupRedMoney]));
            Dialog_ShowEasy(playerid, WdRedMoneyLockerGang, DIALOG_STYLE_INPUT, "ถอนเงิน", string, "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:RedMoneyLeaderGangDepo(playerid, response, listitem, inputtext[]){
    if(!response)   return 1;
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนเงินมากกว่า 0");

        if(amount > PlayerData[playerid][pRedMoney])
            return ErrorMsg(playerid, "คุณมีเงินแดงไม่พอ");

        PlayerData[playerid][pRedMoney] -= amount;
        GroupData[PlayerData[playerid][pGroup]][groupRedMoney] += amount;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], COLOR_YELLOW, "(( [%s] %s(%d) ได้ทำการฝาก เงินแดง เข้าแก๊งจำนวน: %s ))", Group_GetRank(playerid), ReturnRoleplayName(playerid), playerid, FormatNumber(amount));
    }
    return 1;
}

Dialog:WdRedMoneyLockerGang(playerid, response, listitem, inputtext[]){
    if(!response)   return 1;
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0)
            return ErrorMsg(playerid, "คุณต้องกรอกจำนวนเงินมากกว่า 0");

        if(amount > GroupData[PlayerData[playerid][pGroup]][groupRedMoney])
            return ErrorMsg(playerid, "จำนวนเงินแดงในคลังมีไม่เพียงพอ");

        PlayerData[playerid][pRedMoney] += amount;
        GroupData[PlayerData[playerid][pGroup]][groupRedMoney] -= amount;
        Group_Save(PlayerData[playerid][pGroup]);
        SendFactionMessage(PlayerData[playerid][pGroup], COLOR_YELLOW, "(( [%s] %s(%d) ได้ทำการเบิก เงินแดง คลังของกลุ่มออกมาจำนวน: %s ))", Group_GetRank(playerid), ReturnRoleplayName(playerid), playerid, FormatNumber(amount));
    }
    return 1;
}