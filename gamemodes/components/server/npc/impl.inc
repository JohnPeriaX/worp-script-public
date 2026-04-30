#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
    MonsterLv1_Spawn();
    return 1;
}

LoadNpc(){
    ConnectNPC("NPCBUSNO1", "BusRed");
    ConnectNPC("NPCBUSNO2", "BusYellow");
    BusRed = CreateVehicle(431, 0.0, 0.0, 5.0, 0.0, 3, 3, -1);
    BusYellow = CreateVehicle(431, 0.0, 0.0, 5.0, 0.0, 6, 6, -1);

    NPCPUBLICGIRL = FCNPC_Create("Susan_Cotner");
	FCNPC_Spawn(NPCPUBLICGIRL,151 ,1129.0079,-1449.5337,15.7969);
	FCNPC_SetAngle(NPCPUBLICGIRL, 359.7365);
	SetPlayerColor(NPCPUBLICGIRL, 0xFFFFFF00);
    return 1;
}

public FCNPC_OnCreate(npcid) {
	printf("NPC %d CREATE", npcid);
	return 1;
}

Npc_IsValid(npcid){
    if(!strcmp(ReturnName(npcid), "Susan_Cotner", true)
    || !strcmp(ReturnName(npcid), "Monster1_1", true) || !strcmp(ReturnName(npcid), "Monster1_2", true)
    || !strcmp(ReturnName(npcid), "Monster1_3", true) || !strcmp(ReturnName(npcid), "Monster1_4", true)
    || !strcmp(ReturnName(npcid), "Monster1_5", true) || !strcmp(ReturnName(npcid), "Monster1_6", true)
    || !strcmp(ReturnName(npcid), "Monster1_7", true) || !strcmp(ReturnName(npcid), "Monster1_8", true)
    || !strcmp(ReturnName(npcid), "Monster1_9", true) || !strcmp(ReturnName(npcid), "Monster1_10", true)) return 1;
    return -1;
}

public FCNPC_OnTakeDamage(npcid, issuerid, Float:amount, weaponid, bodypart){
    if(npcid == NPCPUBLICGIRL) {
        new Float:hp;
        GetPlayerHealth(issuerid, hp);
        SetPlayerHealth(issuerid, hp-10);
        FCNPC_SetHealth(npcid, 100);
    }

    if(issuerid != INVALID_PLAYER_ID && npcid != INVALID_PLAYER_ID){

        if(MonsterIs_Level1(issuerid) != -1 && MonsterIs_Level1(npcid) != -1){
            FCNPC_SetHealth(npcid, 100);
            return 1;
        }

        if(PlayerData[issuerid][pMyWeapon][2] != 0 && PlayerData[issuerid][pMyWeaponLevel][2] != 0){
            if(GetPlayerWeapon(issuerid) == PlayerData[issuerid][pMyWeapon][2]){
                new levelweapon = PlayerData[issuerid][pMyWeaponLevel][2];
                if(PlayerData[issuerid][pMyWeapon][2] == 1 || PlayerData[issuerid][pMyWeapon][2] == 8){
                    if(levelweapon == 1) amount += 4.0;
                    else if(levelweapon == 2) amount += 8.0;
                    else if(levelweapon == 3) amount += 12.0;
                    else if(levelweapon == 4) amount += 16.0;
                    else if(levelweapon == 5) amount += 20.0;
                }
                else{
                    if(levelweapon == 1) amount += 2.0;
                    else if(levelweapon == 2) amount += 4.0;
                    else if(levelweapon == 3) amount += 6.0;
                    else if(levelweapon == 4) amount += 8.0;
                    else if(levelweapon == 5) amount += 10.0;
                }
            }	
        }

        new Float:hp = FCNPC_GetHealth(npcid);
        FCNPC_SetHealth(npcid, hp-amount);

        if(MonsterIs_Level1(npcid) != -1){
            if(IsPlayerNearPlayer(npcid, issuerid, 10.0)){
                PlayerGetAttackNpc[issuerid] = npcid;
                FCNPC_StopAttack(npcid);
                FCNPC_AimAtPlayer(npcid, issuerid);
                FCNPC_MeleeAttack(npcid, 800);
                FCNPC_GoToPlayer(npcid, issuerid, FCNPC_MOVE_TYPE_AUTO, FCNPC_MOVE_SPEED_AUTO);
            }
        }
    }
	return 1;
}

public FCNPC_OnDeath(npcid, killerid, reason){
    if(npcid == NPCPUBLICGIRL){
		FCNPC_Stop(NPCPUBLICGIRL);
		FCNPC_StopAim(NPCPUBLICGIRL);
        FCNPC_StopAttack(NPCPUBLICGIRL);
        FCNPC_Respawn(NPCPUBLICGIRL);
		FCNPC_Spawn(NPCPUBLICGIRL,151 ,1129.0079,-1449.5337,15.7969);
	    FCNPC_SetAngle(NPCPUBLICGIRL,359.7365);
	}

    if(killerid != INVALID_PLAYER_ID && npcid != INVALID_PLAYER_ID){
        if(npcid == NPCPUBLICGIRL) return 1;

        PlayerGetAttackNpc[killerid] = INVALID_PLAYER_ID;
        if(MonsterIs_Level1(npcid) != -1){
            RandomItemMonster_Level1(npcid);
        }
        SetTimerEx("SetNpcToRespawn", 60000, false, "i", npcid);
    }
	return 1;
}

public FCNPC_OnSpawn(npcid) {
	return 1;
}

public FCNPC_OnGiveDamage(npcid, damagedid, Float:amount, weaponid, bodypart){
    if(damagedid != INVALID_PLAYER_ID && npcid != INVALID_PLAYER_ID){
        if(MonsterIs_Level1(npcid) != -1) amount = monsterlevel1_damage;
        new Float:HP;
        GetPlayerHealth(damagedid, HP);
        SetPlayerHealth(damagedid, HP-amount);
    }
    return 1;
}

Dialog:DialogNPCHELP(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            Dialog_ShowEasy(playerid, ShowMessageNpcGirl, DIALOG_STYLE_MSGBOX, "ตลาดกลาง คืออะไร?", "ตลาดกลางเป็นสถานที่ ที่ผู้คนต่างก็หลั่งไหลกันเข้ามาซึ่งเป็นสถานที่รวมหรือชุมนุมกันเลยก็ว่าได้\
            \nตลาดกลางเป็นสถานที่ซื้อขายของหรือแลกเปลี่ยนของต่างๆ รวมไปถึงการขายของที่ได้จากการทำอาชีพต่างๆอีกด้วย", "ตกลง", "");
        }
        if(listitem == 1){
            Dialog_ShowEasy(playerid, ChangeHourtoExp, DIALOG_STYLE_INPUT, "แลกชั่วโมงออนไลน์ เป็น EXP", "| 100 ชั่วโมงออนไลน์จะสามารถแลกได้ EXP + 1\nกรอกจำนวน EXP ที่คุณต้องการจะแลก:", "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:ChangeHourtoExp(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new exp = strval(inputtext);
        if(exp <= 0) return Dialog_ShowEasy(playerid, ChangeHourtoExp, DIALOG_STYLE_INPUT, "แลกชั่วโมงออนไลน์ เป็น EXP", "[!] กรุณาลองใหม่อีกครั้ง\n| 100 ชั่วโมงออนไลน์จะสามารถแลกได้ EXP + 1\n| กรอกจำนวน EXP ที่คุณต้องการจะแลก:", "ตกลง", "ยกเลิก");
        
        new checkexp = exp * 100;
        if(PlayerData[playerid][pPlayerhour] < checkexp) return Dialog_ShowEasy(playerid, ChangeHourtoExp, DIALOG_STYLE_INPUT, "แลกชั่วโมงออนไลน์ เป็น EXP", "[!] คุณมีชั่วโมงออนไลน์ไม่เพียงพอกับจำนวน EXP ที่ต้องการแลก\n| 100 ชั่วโมงออนไลน์จะสามารถแลกได้ EXP + 1\n| กรอกจำนวน EXP ที่คุณต้องการจะแลก:", "ตกลง", "ยกเลิก");
    
        PlayerData[playerid][pPlayerhour] -= checkexp;
        PlayerData[playerid][pExp] += exp;
        Character_Save(playerid);
        new string[128];
        format(string, sizeof string, "| คุณได้แลกชั่วโมงออนไลน์ของคุณ จำนวน %s ชั่วโมง เป็น EXP จำนวน +%d เรียบร้อยแล้ว", FormatNumberNotMoney(checkexp), exp);
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "แลกชั่วโมงออนไลน์ เป็น EXP", string, "ตกลง", "");
    }
    return 1;
}

//eventmonster

new Float:RandomMonsterLv1_Spawn[][] = {
    {2557.6816,2770.8796,10.8203},
    {2570.9839,2786.3564,10.8203},
    {2581.7859,2769.1917,10.8203},
    {2562.4233,2751.2200,10.8203},
    {2559.1821,2735.3528,10.8130}
};

MonsterLv1_Spawn(){
    monsterlevel1[0] = FCNPC_Create("Monster1_1");
    monsterlevel1[1] = FCNPC_Create("Monster1_2");
    monsterlevel1[2] = FCNPC_Create("Monster1_3");
    monsterlevel1[3] = FCNPC_Create("Monster1_4");
    monsterlevel1[4] = FCNPC_Create("Monster1_5");
    monsterlevel1[5] = FCNPC_Create("Monster1_6");
    monsterlevel1[6] = FCNPC_Create("Monster1_7");
    monsterlevel1[7] = FCNPC_Create("Monster1_8");
    monsterlevel1[8] = FCNPC_Create("Monster1_9");
    monsterlevel1[9] = FCNPC_Create("Monster1_10");
    for(new i=0; i<10; i++){
        new randomspawn = jdzrandom(0, 4);
        FCNPC_Spawn(monsterlevel1[i], 19, RandomMonsterLv1_Spawn[randomspawn][0], RandomMonsterLv1_Spawn[randomspawn][1], RandomMonsterLv1_Spawn[randomspawn][2]);
	    SetPlayerColor(monsterlevel1[i], 0xFFFFFF00);
    }
}

MonsterIs_Level1(monsterid){
    if(IsPlayerNPC(monsterid)){
        for(new i=0; i<10; i++){
            if(monsterid == monsterlevel1[i]) return 1;
        }
    }
    return -1;
}

forward SetNpcToRespawn(npcid);
public SetNpcToRespawn(npcid){
    if(MonsterIs_Level1(npcid) != -1){
        FCNPC_Respawn(npcid);
        FCNPC_SetHealth(npcid, 100);
        new randomspawn = jdzrandom(0, 4);
        FCNPC_SetPosition(npcid, RandomMonsterLv1_Spawn[randomspawn][0], RandomMonsterLv1_Spawn[randomspawn][1], RandomMonsterLv1_Spawn[randomspawn][2]);
        FCNPC_StopAttack(npcid);
        FCNPC_StopAim(npcid);
        FCNPC_Stop(npcid);
    }
    return 1;
}

ptask UpdateMonster[1000](monsterid){
    if(IsPlayerNPC(monsterid)){
        if(MonsterIs_Level1(monsterid) != -1){
            foreach(new i : Player) if(!IsPlayerNPC(i)){
                new Float:x, Float:y, Float:z;
                FCNPC_GetPosition(monsterid, x, y, z);
                if(x > 2504 && x < 2742 && y > 2670.5 && y < 2855.5){
                    if(FCNPC_IsAimingAtPlayer(monsterid, i)){
                        if(!IsPlayerNearPlayer(monsterid, i, 10.0)){
                            FCNPC_StopAttack(monsterid);
                            FCNPC_StopAim(monsterid);
                            FCNPC_Stop(monsterid);
                            PlayerGetAttackNpc[i] = INVALID_PLAYER_ID;
                        }
                        else if(IsPlayerNearPlayer(monsterid, i, 10.0)){
                            FCNPC_GoToPlayer(monsterid, i, FCNPC_MOVE_TYPE_AUTO, FCNPC_MOVE_SPEED_AUTO);
                        }
                    }
                }
                else{
                    FCNPC_StopAttack(monsterid);
                    FCNPC_StopAim(monsterid);
                    FCNPC_Stop(monsterid);
                    PlayerGetAttackNpc[i] = INVALID_PLAYER_ID;
                    SetTimerEx("SetNpcToRespawn", 3000, false, "i", monsterid);
                }
            }
        }
    }
}

ptask UpdateMonsterMove[5000](monsterid){
    if(IsPlayerNPC(monsterid)){
        if(MonsterIs_Level1(monsterid) != -1){
            foreach(new i : Player) if(!IsPlayerNPC(i)){
                if(!FCNPC_IsAimingAtPlayer(monsterid, i)){
                    new Float:x, Float:y, Float:z;
                    FCNPC_GetPosition(monsterid, x, y, z);
                    new randoms = random(5);

                    if(randoms == 0){
                        FCNPC_GoTo(monsterid, x+2.0, y-1.5, z);
                    }

                    if(randoms == 1){
                        FCNPC_GoTo(monsterid, x+1.0, y+3.0, z);
                    }

                    if(randoms == 2){
                        FCNPC_GoTo(monsterid, x+1.5, y-2.5, z);
                    }

                    if(randoms == 4){
                        FCNPC_GoTo(monsterid, x-2.5, y+2.5, z);
                    }

                    if(randoms == 5){
                        FCNPC_GoTo(monsterid, x-2.0, y+1.5, z);
                    }
                }
            }
        }
    }
    return 1;
}

RandomItemMonster_Level1(npcid){
    new Float:x, Float:y, Float:z;
    FCNPC_GetPosition(npcid, x, y, z);
    new randoms = jdzrandom(1, 6);
    if(randoms == 1) Drop_Item("Orange juice", 19563, 1, 0, 0, x, y, z- 0.9, FCNPC_GetAngle(npcid), FCNPC_GetInterior(npcid), FCNPC_GetVirtualWorld(npcid));
    else if(randoms == 2) Drop_Item("Burger", 2663, 2, 0, 0, x, y, z- 0.9, FCNPC_GetAngle(npcid), FCNPC_GetInterior(npcid), FCNPC_GetVirtualWorld(npcid));
    else if(randoms == 3) return 1;
    else if(randoms == 4) Drop_Item("Energy Drink", 1544, 1, 0, 0, x, y, z- 0.9, FCNPC_GetAngle(npcid), FCNPC_GetInterior(npcid), FCNPC_GetVirtualWorld(npcid));
    else if(randoms == 5) return 1;
    else if(randoms == 6) return 1;
    return 1;
}