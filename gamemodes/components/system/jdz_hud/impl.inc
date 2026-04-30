#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetPlayerJdzHud(playerid){
    Jdz_Hunger_Bar_Show[playerid] = false;
    Jdz_Water_Bar_Show[playerid] = false;
    Jdz_Stamina_Bar_Show[playerid] = false;
    Jdz_Shower_Bar_Show[playerid] = false;
    Jdz_Stress_Bar_Show[playerid] = false;
    Jdz_Exp_Show[playerid] = false;
    return 1;
}

hook OnPlayerSpawn(playerid){
    if(LoggedIn[playerid]){
        Jdz_Hunger_Show(playerid);
        Jdz_Water_Show(playerid);
        Jdz_Stamina_Show(playerid);
        Jdz_Shower_Show(playerid);
        Jdz_Stress_Show(playerid);
        Jdz_Exp_Hud_Show(playerid);
    }
    return 1;
}

ptask Jdz_Update_Hud[1000](playerid){
    //Hunger
    if(LoggedIn[playerid]){
        if(Jdz_Hunger_Bar_Show[playerid]){
            if(PlayerData[playerid][pHunger] >= 0 && PlayerData[playerid][pHunger] <= 5){
                PlayerTextDrawHide(playerid, Jdz_Hunger_Bar[playerid][1]);
            }
            else if(PlayerData[playerid][pHunger] > 5 && PlayerData[playerid][pHunger] <= 10){
                Jdz_Hunger_Bar_PositionX[playerid] = 614.2;
                Jdz_Hunger_Bar_PositionY[playerid] = 436.5;
                Jdz_Hunger_Bar_ValueX[playerid] = 13.5;
                Jdz_Hunger_Bar_ValueY[playerid] = 7.5;
            }
            else if(PlayerData[playerid][pHunger] >= 11 && PlayerData[playerid][pHunger] <= 20){
                Jdz_Hunger_Bar_PositionX[playerid] = 613.2;
                Jdz_Hunger_Bar_PositionY[playerid] = 433.5;
                Jdz_Hunger_Bar_ValueX[playerid] = 15.5;
                Jdz_Hunger_Bar_ValueY[playerid] = 10.5;
            }
            else if(PlayerData[playerid][pHunger] >= 21 && PlayerData[playerid][pHunger] <= 30){
                Jdz_Hunger_Bar_PositionX[playerid] = 612.4;
                Jdz_Hunger_Bar_PositionY[playerid] = 431.0;
                Jdz_Hunger_Bar_ValueX[playerid] = 17.0;
                Jdz_Hunger_Bar_ValueY[playerid] = 13.0;
            }
            else if(PlayerData[playerid][pHunger] >= 31 && PlayerData[playerid][pHunger] <= 40){
                Jdz_Hunger_Bar_PositionX[playerid] = 612.0;
                Jdz_Hunger_Bar_PositionY[playerid] = 429.5;
                Jdz_Hunger_Bar_ValueX[playerid] = 18.0;
                Jdz_Hunger_Bar_ValueY[playerid] = 14.5;
            }
            else if(PlayerData[playerid][pHunger] >= 41 && PlayerData[playerid][pHunger] <= 50){
                Jdz_Hunger_Bar_PositionX[playerid] = 611.5;
                Jdz_Hunger_Bar_PositionY[playerid] = 428.0;
                Jdz_Hunger_Bar_ValueX[playerid] = 19.0;
                Jdz_Hunger_Bar_ValueY[playerid] = 16.0;
            }
            else if(PlayerData[playerid][pHunger] >= 51 && PlayerData[playerid][pHunger] <= 60){
                Jdz_Hunger_Bar_PositionX[playerid] = 611.3;
                Jdz_Hunger_Bar_PositionY[playerid] = 427.2;
                Jdz_Hunger_Bar_ValueX[playerid] = 19.5;
                Jdz_Hunger_Bar_ValueY[playerid] = 17.0;
            }
            else if(PlayerData[playerid][pHunger] >= 61 && PlayerData[playerid][pHunger] <= 70){
                Jdz_Hunger_Bar_PositionX[playerid] = 611.0;
                Jdz_Hunger_Bar_PositionY[playerid] = 425.4;
                Jdz_Hunger_Bar_ValueX[playerid] = 20.0;
                Jdz_Hunger_Bar_ValueY[playerid] = 18.5;
            }
            else if(PlayerData[playerid][pHunger] >= 71 && PlayerData[playerid][pHunger] <= 80){
                Jdz_Hunger_Bar_PositionX[playerid] = 611.0;
                Jdz_Hunger_Bar_PositionY[playerid] = 425.2;
                Jdz_Hunger_Bar_ValueX[playerid] = 20.0;
                Jdz_Hunger_Bar_ValueY[playerid] = 19.0;
            }
            else if(PlayerData[playerid][pHunger] >= 81 && PlayerData[playerid][pHunger] <= 90){
                Jdz_Hunger_Bar_PositionX[playerid] = 611.0;
                Jdz_Hunger_Bar_PositionY[playerid] = 423.5;
                Jdz_Hunger_Bar_ValueX[playerid] = 20.0;
                Jdz_Hunger_Bar_ValueY[playerid] = 20.5;
            }
            else if(PlayerData[playerid][pHunger] >= 91){
                Jdz_Hunger_Bar_PositionX[playerid] = 610.8;
                Jdz_Hunger_Bar_PositionY[playerid] = 421.5;
                Jdz_Hunger_Bar_ValueX[playerid] = 20.5;
                Jdz_Hunger_Bar_ValueY[playerid] = 22.5;
            }

            if(PlayerData[playerid][pHunger] > 5){
                PlayerTextDrawHide(playerid, Jdz_Hunger_Bar[playerid][1]);
                PlayerTextDrawSetPos(playerid, Jdz_Hunger_Bar[playerid][1], Jdz_Hunger_Bar_PositionX[playerid], Jdz_Hunger_Bar_PositionY[playerid]);
                PlayerTextDrawTextSize(playerid, Jdz_Hunger_Bar[playerid][1], Jdz_Hunger_Bar_ValueX[playerid], Jdz_Hunger_Bar_ValueY[playerid]);
                PlayerTextDrawShow(playerid, Jdz_Hunger_Bar[playerid][1]);
            }
        }

        if(Jdz_Water_Bar_Show[playerid]){
            //Water
            if(PlayerData[playerid][pWater] >= 0 && PlayerData[playerid][pWater] <= 5){
                PlayerTextDrawHide(playerid, Jdz_Water_Bar[playerid][1]);
            }
            else if(PlayerData[playerid][pWater] > 5 && PlayerData[playerid][pWater] <= 10){
                Jdz_Water_Bar_PositionX[playerid] = 614.2-27.0;
                Jdz_Water_Bar_PositionY[playerid] = 436.5;
                Jdz_Water_Bar_ValueX[playerid] = 13.5;
                Jdz_Water_Bar_ValueY[playerid] = 7.5;
            }
            else if(PlayerData[playerid][pWater] >= 11 && PlayerData[playerid][pWater] <= 20){
                Jdz_Water_Bar_PositionX[playerid] = 613.2-27.0;
                Jdz_Water_Bar_PositionY[playerid] = 433.5;
                Jdz_Water_Bar_ValueX[playerid] = 15.5;
                Jdz_Water_Bar_ValueY[playerid] = 10.5;
            }
            else if(PlayerData[playerid][pWater] >= 21 && PlayerData[playerid][pWater] <= 30){
                Jdz_Water_Bar_PositionX[playerid] = 612.4-27.0;
                Jdz_Water_Bar_PositionY[playerid] = 431.0;
                Jdz_Water_Bar_ValueX[playerid] = 17.0;
                Jdz_Water_Bar_ValueY[playerid] = 13.0;
            }
            else if(PlayerData[playerid][pWater] >= 31 && PlayerData[playerid][pWater] <= 40){
                Jdz_Water_Bar_PositionX[playerid] = 612.0-27.0;
                Jdz_Water_Bar_PositionY[playerid] = 429.5;
                Jdz_Water_Bar_ValueX[playerid] = 18.0;
                Jdz_Water_Bar_ValueY[playerid] = 14.5;
            }
            else if(PlayerData[playerid][pWater] >= 41 && PlayerData[playerid][pWater] <= 50){
                Jdz_Water_Bar_PositionX[playerid] = 611.5-27.0;
                Jdz_Water_Bar_PositionY[playerid] = 428.0;
                Jdz_Water_Bar_ValueX[playerid] = 19.0;
                Jdz_Water_Bar_ValueY[playerid] = 16.0;
            }
            else if(PlayerData[playerid][pWater] >= 51 && PlayerData[playerid][pWater] <= 60){
                Jdz_Water_Bar_PositionX[playerid] = 611.3-27.0;
                Jdz_Water_Bar_PositionY[playerid] = 427.2;
                Jdz_Water_Bar_ValueX[playerid] = 19.5;
                Jdz_Water_Bar_ValueY[playerid] = 17.0;
            }
            else if(PlayerData[playerid][pWater] >= 61 && PlayerData[playerid][pWater] <= 70){
                Jdz_Water_Bar_PositionX[playerid] = 611.0-27.0;
                Jdz_Water_Bar_PositionY[playerid] = 425.4;
                Jdz_Water_Bar_ValueX[playerid] = 20.0;
                Jdz_Water_Bar_ValueY[playerid] = 18.5;
            }
            else if(PlayerData[playerid][pWater] >= 71 && PlayerData[playerid][pWater] <= 80){
                Jdz_Water_Bar_PositionX[playerid] = 611.0-27.0;
                Jdz_Water_Bar_PositionY[playerid] = 425.2;
                Jdz_Water_Bar_ValueX[playerid] = 20.0;
                Jdz_Water_Bar_ValueY[playerid] = 19.0;
            }
            else if(PlayerData[playerid][pWater] >= 81 && PlayerData[playerid][pWater] <= 90){
                Jdz_Water_Bar_PositionX[playerid] = 611.0-27.0;
                Jdz_Water_Bar_PositionY[playerid] = 423.5;
                Jdz_Water_Bar_ValueX[playerid] = 20.0;
                Jdz_Water_Bar_ValueY[playerid] = 20.5;
            }
            else if(PlayerData[playerid][pWater] >= 91){
                Jdz_Water_Bar_PositionX[playerid] = 610.8-27.0;
                Jdz_Water_Bar_PositionY[playerid] = 421.5;
                Jdz_Water_Bar_ValueX[playerid] = 20.5;
                Jdz_Water_Bar_ValueY[playerid] = 22.5;
            }

            if(PlayerData[playerid][pWater] > 5){
                PlayerTextDrawHide(playerid, Jdz_Water_Bar[playerid][1]);
                PlayerTextDrawSetPos(playerid, Jdz_Water_Bar[playerid][1], Jdz_Water_Bar_PositionX[playerid], Jdz_Water_Bar_PositionY[playerid]);
                PlayerTextDrawTextSize(playerid, Jdz_Water_Bar[playerid][1], Jdz_Water_Bar_ValueX[playerid], Jdz_Water_Bar_ValueY[playerid]);
                PlayerTextDrawShow(playerid, Jdz_Water_Bar[playerid][1]);
            }
        }

        if(Jdz_Stamina_Bar_Show[playerid]){
            //Stamina
            if(PlayerData[playerid][pEnergy] >= 0 && PlayerData[playerid][pEnergy] <= 5){
                PlayerTextDrawHide(playerid, Jdz_Stamina_Bar[playerid][1]);
            }
            else if(PlayerData[playerid][pEnergy] > 5 && PlayerData[playerid][pEnergy] <= 10){
                Jdz_Stamina_Bar_PositionX[playerid] = 614.2-54.0;
                Jdz_Stamina_Bar_PositionY[playerid] = 436.5;
                Jdz_Stamina_Bar_ValueX[playerid] = 13.5;
                Jdz_Stamina_Bar_ValueY[playerid] = 7.5;
            }
            else if(PlayerData[playerid][pEnergy] >= 11 && PlayerData[playerid][pEnergy] <= 20){
                Jdz_Stamina_Bar_PositionX[playerid] = 613.2-54.0;
                Jdz_Stamina_Bar_PositionY[playerid] = 433.5;
                Jdz_Stamina_Bar_ValueX[playerid] = 15.5;
                Jdz_Stamina_Bar_ValueY[playerid] = 10.5;
            }
            else if(PlayerData[playerid][pEnergy] >= 21 && PlayerData[playerid][pEnergy] <= 30){
                Jdz_Stamina_Bar_PositionX[playerid] = 612.4-54.0;
                Jdz_Stamina_Bar_PositionY[playerid] = 431.0;
                Jdz_Stamina_Bar_ValueX[playerid] = 17.0;
                Jdz_Stamina_Bar_ValueY[playerid] = 13.0;
            }
            else if(PlayerData[playerid][pEnergy] >= 31 && PlayerData[playerid][pEnergy] <= 40){
                Jdz_Stamina_Bar_PositionX[playerid] = 612.0-54.0;
                Jdz_Stamina_Bar_PositionY[playerid] = 429.5;
                Jdz_Stamina_Bar_ValueX[playerid] = 18.0;
                Jdz_Stamina_Bar_ValueY[playerid] = 14.5;
            }
            else if(PlayerData[playerid][pEnergy] >= 41 && PlayerData[playerid][pEnergy] <= 50){
                Jdz_Stamina_Bar_PositionX[playerid] = 611.5-54.0;
                Jdz_Stamina_Bar_PositionY[playerid] = 428.0;
                Jdz_Stamina_Bar_ValueX[playerid] = 19.0;
                Jdz_Stamina_Bar_ValueY[playerid] = 16.0;
            }
            else if(PlayerData[playerid][pEnergy] >= 51 && PlayerData[playerid][pEnergy] <= 60){
                Jdz_Stamina_Bar_PositionX[playerid] = 611.3-54.0;
                Jdz_Stamina_Bar_PositionY[playerid] = 427.2;
                Jdz_Stamina_Bar_ValueX[playerid] = 19.5;
                Jdz_Stamina_Bar_ValueY[playerid] = 17.0;
            }
            else if(PlayerData[playerid][pEnergy] >= 61 && PlayerData[playerid][pEnergy] <= 70){
                Jdz_Stamina_Bar_PositionX[playerid] = 611.0-54.0;
                Jdz_Stamina_Bar_PositionY[playerid] = 425.4;
                Jdz_Stamina_Bar_ValueX[playerid] = 20.0;
                Jdz_Stamina_Bar_ValueY[playerid] = 18.5;
            }
            else if(PlayerData[playerid][pEnergy] >= 71 && PlayerData[playerid][pEnergy] <= 80){
                Jdz_Stamina_Bar_PositionX[playerid] = 611.0-54.0;
                Jdz_Stamina_Bar_PositionY[playerid] = 425.2;
                Jdz_Stamina_Bar_ValueX[playerid] = 20.0;
                Jdz_Stamina_Bar_ValueY[playerid] = 19.0;
            }
            else if(PlayerData[playerid][pEnergy] >= 81 && PlayerData[playerid][pEnergy] <= 90){
                Jdz_Stamina_Bar_PositionX[playerid] = 611.0-54.0;
                Jdz_Stamina_Bar_PositionY[playerid] = 423.5;
                Jdz_Stamina_Bar_ValueX[playerid] = 20.0;
                Jdz_Stamina_Bar_ValueY[playerid] = 20.5;
            }
            else if(PlayerData[playerid][pEnergy] >= 91){
                Jdz_Stamina_Bar_PositionX[playerid] = 610.8-54.0;
                Jdz_Stamina_Bar_PositionY[playerid] = 421.5;
                Jdz_Stamina_Bar_ValueX[playerid] = 20.5;
                Jdz_Stamina_Bar_ValueY[playerid] = 22.5;
            }

            if(PlayerData[playerid][pEnergy] > 5){
                PlayerTextDrawHide(playerid, Jdz_Stamina_Bar[playerid][1]);
                PlayerTextDrawSetPos(playerid, Jdz_Stamina_Bar[playerid][1], Jdz_Stamina_Bar_PositionX[playerid], Jdz_Stamina_Bar_PositionY[playerid]);
                PlayerTextDrawTextSize(playerid, Jdz_Stamina_Bar[playerid][1], Jdz_Stamina_Bar_ValueX[playerid], Jdz_Stamina_Bar_ValueY[playerid]);
                PlayerTextDrawShow(playerid, Jdz_Stamina_Bar[playerid][1]);
            }
            
        }
        
        if(Jdz_Shower_Bar_Show[playerid]){
            //Shower
            if(PlayerData[playerid][pShower] >= 0 && PlayerData[playerid][pShower] <= 5){
                PlayerTextDrawHide(playerid, Jdz_Shower_Bar[playerid][1]);
            }
            else if(PlayerData[playerid][pShower] > 5 && PlayerData[playerid][pShower] <= 10){
                Jdz_Shower_Bar_PositionX[playerid] = 614.2-81.0;
                Jdz_Shower_Bar_PositionY[playerid] = 436.5;
                Jdz_Shower_Bar_ValueX[playerid] = 13.5;
                Jdz_Shower_Bar_ValueY[playerid] = 7.5;
            }
            else if(PlayerData[playerid][pShower] >= 11 && PlayerData[playerid][pShower] <= 20){
                Jdz_Shower_Bar_PositionX[playerid] = 613.2-81.0;
                Jdz_Shower_Bar_PositionY[playerid] = 433.5;
                Jdz_Shower_Bar_ValueX[playerid] = 15.5;
                Jdz_Shower_Bar_ValueY[playerid] = 10.5;
            }
            else if(PlayerData[playerid][pShower] >= 21 && PlayerData[playerid][pShower] <= 30){
                Jdz_Shower_Bar_PositionX[playerid] = 612.4-81.0;
                Jdz_Shower_Bar_PositionY[playerid] = 431.0;
                Jdz_Shower_Bar_ValueX[playerid] = 17.0;
                Jdz_Shower_Bar_ValueY[playerid] = 13.0;
            }
            else if(PlayerData[playerid][pShower] >= 31 && PlayerData[playerid][pShower] <= 40){
                Jdz_Shower_Bar_PositionX[playerid] = 612.0-81.0;
                Jdz_Shower_Bar_PositionY[playerid] = 429.5;
                Jdz_Shower_Bar_ValueX[playerid] = 18.0;
                Jdz_Shower_Bar_ValueY[playerid] = 14.5;
            }
            else if(PlayerData[playerid][pShower] >= 41 && PlayerData[playerid][pShower] <= 50){
                Jdz_Shower_Bar_PositionX[playerid] = 611.5-81.0;
                Jdz_Shower_Bar_PositionY[playerid] = 428.0;
                Jdz_Shower_Bar_ValueX[playerid] = 19.0;
                Jdz_Shower_Bar_ValueY[playerid] = 16.0;
            }
            else if(PlayerData[playerid][pShower] >= 51 && PlayerData[playerid][pShower] <= 60){
                Jdz_Shower_Bar_PositionX[playerid] = 611.3-81.0;
                Jdz_Shower_Bar_PositionY[playerid] = 427.2;
                Jdz_Shower_Bar_ValueX[playerid] = 19.5;
                Jdz_Shower_Bar_ValueY[playerid] = 17.0;
            }
            else if(PlayerData[playerid][pShower] >= 61 && PlayerData[playerid][pShower] <= 70){
                Jdz_Shower_Bar_PositionX[playerid] = 611.0-81.0;
                Jdz_Shower_Bar_PositionY[playerid] = 425.4;
                Jdz_Shower_Bar_ValueX[playerid] = 20.0;
                Jdz_Shower_Bar_ValueY[playerid] = 18.5;
            }
            else if(PlayerData[playerid][pShower] >= 71 && PlayerData[playerid][pShower] <= 80){
                Jdz_Shower_Bar_PositionX[playerid] = 611.0-81.0;
                Jdz_Shower_Bar_PositionY[playerid] = 425.2;
                Jdz_Shower_Bar_ValueX[playerid] = 20.0;
                Jdz_Shower_Bar_ValueY[playerid] = 19.0;
            }
            else if(PlayerData[playerid][pShower] >= 81 && PlayerData[playerid][pShower] <= 90){
                Jdz_Shower_Bar_PositionX[playerid] = 611.0-81.0;
                Jdz_Shower_Bar_PositionY[playerid] = 423.5;
                Jdz_Shower_Bar_ValueX[playerid] = 20.0;
                Jdz_Shower_Bar_ValueY[playerid] = 20.5;
            }
            else if(PlayerData[playerid][pShower] >= 91){
                Jdz_Shower_Bar_PositionX[playerid] = 610.8-81.0;
                Jdz_Shower_Bar_PositionY[playerid] = 421.5;
                Jdz_Shower_Bar_ValueX[playerid] = 20.5;
                Jdz_Shower_Bar_ValueY[playerid] = 22.5;
            }

            if(PlayerData[playerid][pShower]){
                PlayerTextDrawHide(playerid, Jdz_Shower_Bar[playerid][1]);
                PlayerTextDrawSetPos(playerid, Jdz_Shower_Bar[playerid][1], Jdz_Shower_Bar_PositionX[playerid], Jdz_Shower_Bar_PositionY[playerid]);
                PlayerTextDrawTextSize(playerid, Jdz_Shower_Bar[playerid][1], Jdz_Shower_Bar_ValueX[playerid], Jdz_Shower_Bar_ValueY[playerid]);
                PlayerTextDrawShow(playerid, Jdz_Shower_Bar[playerid][1]);
            }
        }

        if(Jdz_Stress_Bar_Show[playerid]){
            //Stress
            if(PlayerData[playerid][pStress] >= 0 && PlayerData[playerid][pStress] <= 5){
                PlayerTextDrawHide(playerid, Jdz_Stress_Bar[playerid][1]);
            }
            else if(PlayerData[playerid][pStress] > 5 && PlayerData[playerid][pStress] <= 10){
                Jdz_Stress_Bar_PositionX[playerid] = 614.2-108.0;
                Jdz_Stress_Bar_PositionY[playerid] = 436.5;
                Jdz_Stress_Bar_ValueX[playerid] = 13.5;
                Jdz_Stress_Bar_ValueY[playerid] = 7.5;
            }
            else if(PlayerData[playerid][pStress] >= 11 && PlayerData[playerid][pStress] <= 20){
                Jdz_Stress_Bar_PositionX[playerid] = 613.2-108.0;
                Jdz_Stress_Bar_PositionY[playerid] = 433.5;
                Jdz_Stress_Bar_ValueX[playerid] = 15.5;
                Jdz_Stress_Bar_ValueY[playerid] = 10.5;
            }
            else if(PlayerData[playerid][pStress] >= 21 && PlayerData[playerid][pStress] <= 30){
                Jdz_Stress_Bar_PositionX[playerid] = 612.4-108.0;
                Jdz_Stress_Bar_PositionY[playerid] = 431.0;
                Jdz_Stress_Bar_ValueX[playerid] = 17.0;
                Jdz_Stress_Bar_ValueY[playerid] = 13.0;
            }
            else if(PlayerData[playerid][pStress] >= 31 && PlayerData[playerid][pStress] <= 40){
                Jdz_Stress_Bar_PositionX[playerid] = 612.0-108.0;
                Jdz_Stress_Bar_PositionY[playerid] = 429.5;
                Jdz_Stress_Bar_ValueX[playerid] = 18.0;
                Jdz_Stress_Bar_ValueY[playerid] = 14.5;
            }
            else if(PlayerData[playerid][pStress] >= 41 && PlayerData[playerid][pStress] <= 50){
                Jdz_Stress_Bar_PositionX[playerid] = 611.5-108.0;
                Jdz_Stress_Bar_PositionY[playerid] = 428.0;
                Jdz_Stress_Bar_ValueX[playerid] = 19.0;
                Jdz_Stress_Bar_ValueY[playerid] = 16.0;
            }
            else if(PlayerData[playerid][pStress] >= 51 && PlayerData[playerid][pStress] <= 60){
                Jdz_Stress_Bar_PositionX[playerid] = 611.3-108.0;
                Jdz_Stress_Bar_PositionY[playerid] = 427.2;
                Jdz_Stress_Bar_ValueX[playerid] = 19.5;
                Jdz_Stress_Bar_ValueY[playerid] = 17.0;
            }
            else if(PlayerData[playerid][pStress] >= 61 && PlayerData[playerid][pStress] <= 70){
                Jdz_Stress_Bar_PositionX[playerid] = 611.0-108.0;
                Jdz_Stress_Bar_PositionY[playerid] = 425.4;
                Jdz_Stress_Bar_ValueX[playerid] = 20.0;
                Jdz_Stress_Bar_ValueY[playerid] = 18.5;
            }
            else if(PlayerData[playerid][pStress] >= 71 && PlayerData[playerid][pStress] <= 80){
                Jdz_Stress_Bar_PositionX[playerid] = 611.0-108.0;
                Jdz_Stress_Bar_PositionY[playerid] = 425.2;
                Jdz_Stress_Bar_ValueX[playerid] = 20.0;
                Jdz_Stress_Bar_ValueY[playerid] = 19.0;
            }
            else if(PlayerData[playerid][pStress] >= 81 && PlayerData[playerid][pStress] <= 90){
                Jdz_Stress_Bar_PositionX[playerid] = 611.0-108.0;
                Jdz_Stress_Bar_PositionY[playerid] = 423.5;
                Jdz_Stress_Bar_ValueX[playerid] = 20.0;
                Jdz_Stress_Bar_ValueY[playerid] = 20.5;
            }
            else if(PlayerData[playerid][pStress] >= 91){
                Jdz_Stress_Bar_PositionX[playerid] = 610.8-108.0;
                Jdz_Stress_Bar_PositionY[playerid] = 421.5;
                Jdz_Stress_Bar_ValueX[playerid] = 20.5;
                Jdz_Stress_Bar_ValueY[playerid] = 22.5;
            }

            if(PlayerData[playerid][pStress] > 5){
                PlayerTextDrawHide(playerid, Jdz_Stress_Bar[playerid][1]);
                PlayerTextDrawSetPos(playerid, Jdz_Stress_Bar[playerid][1], Jdz_Stress_Bar_PositionX[playerid], Jdz_Stress_Bar_PositionY[playerid]);
                PlayerTextDrawTextSize(playerid, Jdz_Stress_Bar[playerid][1], Jdz_Stress_Bar_ValueX[playerid], Jdz_Stress_Bar_ValueY[playerid]);
                PlayerTextDrawShow(playerid, Jdz_Stress_Bar[playerid][1]);
            }
        }
    }
}

Jdz_Hunger_Show(playerid){
    if(!Jdz_Hunger_Bar_Show[playerid]){
        Jdz_Hunger_Load(playerid);
        for(new i=0; i<3; i++){
            PlayerTextDrawShow(playerid, Jdz_Hunger_Bar[playerid][i]);
        }
        Jdz_Hunger_Bar_Show[playerid] = true;
    }
    return 1;
}

Jdz_Hunger_Hide(playerid){
    if(Jdz_Hunger_Bar_Show[playerid]){
        for(new i=0; i<3; i++){
            if(IsPlayerTextDrawVisible(playerid, Jdz_Hunger_Bar[playerid][i])){
                PlayerTextDrawHide(playerid, Jdz_Hunger_Bar[playerid][i]);
            }
            
            PlayerTextDrawDestroy(playerid, Jdz_Hunger_Bar[playerid][i]);
        }
        Jdz_Hunger_Bar_Show[playerid] = false;
    }
    return 1;
}

Jdz_Water_Show(playerid){
    if(!Jdz_Water_Bar_Show[playerid]){
        Jdz_Water_Load(playerid);
        for(new i=0; i<3; i++){
            PlayerTextDrawShow(playerid, Jdz_Water_Bar[playerid][i]);
        }
        Jdz_Water_Bar_Show[playerid] = true;
    }
    return 1;
}

Jdz_Water_Hide(playerid){
    if(Jdz_Water_Bar_Show[playerid]){
        for(new i=0; i<3; i++){
            if(IsPlayerTextDrawVisible(playerid, Jdz_Water_Bar[playerid][i])){
                PlayerTextDrawHide(playerid, Jdz_Water_Bar[playerid][i]);
            }
            PlayerTextDrawDestroy(playerid, Jdz_Water_Bar[playerid][i]);
        }
        Jdz_Water_Bar_Show[playerid] = false;
    }
    return 1;
}

Jdz_Stamina_Show(playerid){
    if(!Jdz_Stamina_Bar_Show[playerid]){
        Jdz_Stamina_Load(playerid);
        for(new i=0; i<3; i++){
            PlayerTextDrawShow(playerid, Jdz_Stamina_Bar[playerid][i]);
        }
        Jdz_Stamina_Bar_Show[playerid] = true;
    }
    return 1;
}

Jdz_Stamina_Hide(playerid){
    if(Jdz_Stamina_Bar_Show[playerid]){
        for(new i=0; i<3; i++){
            if(IsPlayerTextDrawVisible(playerid, Jdz_Stamina_Bar[playerid][i])){
                PlayerTextDrawHide(playerid, Jdz_Stamina_Bar[playerid][i]);
            }
            PlayerTextDrawDestroy(playerid, Jdz_Stamina_Bar[playerid][i]);
        }
        Jdz_Stamina_Bar_Show[playerid] = false;
    }
    return 1;
}

Jdz_Shower_Show(playerid){
    if(!Jdz_Shower_Bar_Show[playerid]){
        Jdz_Shower_Load(playerid);
        for(new i=0; i<3; i++){
            PlayerTextDrawShow(playerid, Jdz_Shower_Bar[playerid][i]);
        }
        Jdz_Shower_Bar_Show[playerid] = true;
    }
    return 1;
}

Jdz_Shower_Hide(playerid){
    if(Jdz_Shower_Bar_Show[playerid]){
        for(new i=0; i<3; i++){
            if(IsPlayerTextDrawVisible(playerid, Jdz_Shower_Bar[playerid][i])){
                PlayerTextDrawHide(playerid, Jdz_Shower_Bar[playerid][i]);
            }
            PlayerTextDrawDestroy(playerid, Jdz_Shower_Bar[playerid][i]);
        }
        Jdz_Shower_Bar_Show[playerid] = false;
    }
    return 1;
}

Jdz_Stress_Show(playerid){
    if(!Jdz_Stress_Bar_Show[playerid]){
        Jdz_Stress_Load(playerid);
        for(new i=0; i<3; i++){
            PlayerTextDrawShow(playerid, Jdz_Stress_Bar[playerid][i]);
        }
        Jdz_Stress_Bar_Show[playerid] = true;
    }
    return 1;
}

Jdz_Stress_Hide(playerid){
    if(Jdz_Stress_Bar_Show[playerid]){
        for(new i=0; i<3; i++){
            if(IsPlayerTextDrawVisible(playerid, Jdz_Stress_Bar[playerid][i])){
                PlayerTextDrawHide(playerid, Jdz_Stress_Bar[playerid][i]);
            }
            PlayerTextDrawDestroy(playerid, Jdz_Stress_Bar[playerid][i]);
        }
        Jdz_Stress_Bar_Show[playerid] = false;
    }
    return 1;
}

Jdz_Exp_Hud_Show(playerid){
    if(!Jdz_Exp_Show[playerid]){
        if(PlayerData[playerid][pUseExpx2] > 0){
            Jdz_Exp_Load(playerid);
            for(new i=0; i<3; i++){
                PlayerTextDrawShow(playerid, Exp_Hud[playerid][i]);
            }
            Jdz_Exp_Show[playerid] = true;

            new expstring[64];
            format(expstring, sizeof expstring, "%d H", PlayerData[playerid][pUseExpx2]);
            PlayerTextDrawSetString(playerid, Exp_Hud[playerid][2], expstring);
        }
    }
    return 1;
}

Jdz_Exp_Hud_Hide(playerid){
    if(Jdz_Exp_Show[playerid]){
        for(new i=0; i<3; i++){
            if(IsPlayerTextDrawVisible(playerid, Exp_Hud[playerid][i])){
                PlayerTextDrawHide(playerid, Exp_Hud[playerid][i]);
            }
            PlayerTextDrawDestroy(playerid, Exp_Hud[playerid][i]);
        }
        Jdz_Exp_Show[playerid] = false;
    }
    return 1;
}

Jdz_Exp_Load(playerid){
    Exp_Hud[playerid][0] = CreatePlayerTextDraw(playerid, 612.000000, 391.000000, "EXP");
    PlayerTextDrawFont(playerid, Exp_Hud[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, Exp_Hud[playerid][0], 0.249999, 1.149999);
    PlayerTextDrawTextSize(playerid, Exp_Hud[playerid][0], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, Exp_Hud[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, Exp_Hud[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, Exp_Hud[playerid][0], 2);
    PlayerTextDrawColor(playerid, Exp_Hud[playerid][0], -1962934017);
    PlayerTextDrawBackgroundColor(playerid, Exp_Hud[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, Exp_Hud[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, Exp_Hud[playerid][0], 0);
    PlayerTextDrawSetProportional(playerid, Exp_Hud[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, Exp_Hud[playerid][0], 0);

    Exp_Hud[playerid][1] = CreatePlayerTextDraw(playerid, 625.000000, 392.000000, "x2");
    PlayerTextDrawFont(playerid, Exp_Hud[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, Exp_Hud[playerid][1], 0.212498, 1.000000);
    PlayerTextDrawTextSize(playerid, Exp_Hud[playerid][1], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, Exp_Hud[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, Exp_Hud[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, Exp_Hud[playerid][1], 2);
    PlayerTextDrawColor(playerid, Exp_Hud[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, Exp_Hud[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, Exp_Hud[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, Exp_Hud[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, Exp_Hud[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, Exp_Hud[playerid][1], 0);

    Exp_Hud[playerid][2] = CreatePlayerTextDraw(playerid, 617.000000, 401.000000, "1 H");
    PlayerTextDrawFont(playerid, Exp_Hud[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, Exp_Hud[playerid][2], 0.162499, 0.899999);
    PlayerTextDrawTextSize(playerid, Exp_Hud[playerid][2], 400.000000, 43.000000);
    PlayerTextDrawSetOutline(playerid, Exp_Hud[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, Exp_Hud[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, Exp_Hud[playerid][2], 2);
    PlayerTextDrawColor(playerid, Exp_Hud[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, Exp_Hud[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, Exp_Hud[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, Exp_Hud[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, Exp_Hud[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, Exp_Hud[playerid][2], 0);
    return 1;
}

Jdz_Stress_Load(playerid){
    Jdz_Stress_Bar[playerid][0] = CreatePlayerTextDraw(playerid, 610.000000-108.0, 420.000000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, Jdz_Stress_Bar[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Stress_Bar[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Stress_Bar[playerid][0], 22.000000, 25.000000);
    PlayerTextDrawSetOutline(playerid, Jdz_Stress_Bar[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Stress_Bar[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Stress_Bar[playerid][0], 1);
    PlayerTextDrawColor(playerid, Jdz_Stress_Bar[playerid][0], 255);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Stress_Bar[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Stress_Bar[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, Jdz_Stress_Bar[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Stress_Bar[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Stress_Bar[playerid][0], 0);

    Jdz_Stress_Bar[playerid][1] = CreatePlayerTextDraw(playerid, 610.799987-108.0, 421.500000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, Jdz_Stress_Bar[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Stress_Bar[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Stress_Bar[playerid][1], 20.500000, 22.500000);
    PlayerTextDrawSetOutline(playerid, Jdz_Stress_Bar[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Stress_Bar[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Stress_Bar[playerid][1], 1);
    PlayerTextDrawColor(playerid, Jdz_Stress_Bar[playerid][1], 0x02B455FF);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Stress_Bar[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Stress_Bar[playerid][1], -294256590);
    PlayerTextDrawUseBox(playerid, Jdz_Stress_Bar[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Stress_Bar[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Stress_Bar[playerid][1], 0);

    Jdz_Stress_Bar[playerid][2] = CreatePlayerTextDraw(playerid, 616.200000-108.0, 427.000000, "HUD:radar_LocoSyndicate");
    PlayerTextDrawFont(playerid, Jdz_Stress_Bar[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Stress_Bar[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Stress_Bar[playerid][2], 9.500000, 10.000000);
    PlayerTextDrawSetOutline(playerid, Jdz_Stress_Bar[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Stress_Bar[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Stress_Bar[playerid][2], 1);
    PlayerTextDrawColor(playerid, Jdz_Stress_Bar[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Stress_Bar[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Stress_Bar[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, Jdz_Stress_Bar[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Stress_Bar[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Stress_Bar[playerid][2], 0);
    return 1;
}

Jdz_Shower_Load(playerid){
    Jdz_Shower_Bar[playerid][0] = CreatePlayerTextDraw(playerid, 610.000000-81.0, 420.000000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, Jdz_Shower_Bar[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Shower_Bar[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Shower_Bar[playerid][0], 22.000000, 25.000000);
    PlayerTextDrawSetOutline(playerid, Jdz_Shower_Bar[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Shower_Bar[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Shower_Bar[playerid][0], 1);
    PlayerTextDrawColor(playerid, Jdz_Shower_Bar[playerid][0], 255);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Shower_Bar[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Shower_Bar[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, Jdz_Shower_Bar[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Shower_Bar[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Shower_Bar[playerid][0], 0);

    Jdz_Shower_Bar[playerid][1] = CreatePlayerTextDraw(playerid, 610.799987-81.0, 421.500000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, Jdz_Shower_Bar[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Shower_Bar[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Shower_Bar[playerid][1], 20.500000, 22.500000);
    PlayerTextDrawSetOutline(playerid, Jdz_Shower_Bar[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Shower_Bar[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Shower_Bar[playerid][1], 1);
    PlayerTextDrawColor(playerid, Jdz_Shower_Bar[playerid][1], 0xEA77FFFF);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Shower_Bar[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Shower_Bar[playerid][1], -294256590);
    PlayerTextDrawUseBox(playerid, Jdz_Shower_Bar[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Shower_Bar[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Shower_Bar[playerid][1], 0);

    Jdz_Shower_Bar[playerid][2] = CreatePlayerTextDraw(playerid, 616.200000-81.0, 427.000000, "HUD:radar_tshirt");
    PlayerTextDrawFont(playerid, Jdz_Shower_Bar[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Shower_Bar[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Shower_Bar[playerid][2], 9.500000, 10.000000);
    PlayerTextDrawSetOutline(playerid, Jdz_Shower_Bar[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Shower_Bar[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Shower_Bar[playerid][2], 1);
    PlayerTextDrawColor(playerid, Jdz_Shower_Bar[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Shower_Bar[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Shower_Bar[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, Jdz_Shower_Bar[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Shower_Bar[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Shower_Bar[playerid][2], 0);
    return 1;
}

Jdz_Stamina_Load(playerid){
    Jdz_Stamina_Bar[playerid][0] = CreatePlayerTextDraw(playerid, 610.000000-54.0, 420.000000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, Jdz_Stamina_Bar[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Stamina_Bar[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Stamina_Bar[playerid][0], 22.000000, 25.000000);
    PlayerTextDrawSetOutline(playerid, Jdz_Stamina_Bar[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Stamina_Bar[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Stamina_Bar[playerid][0], 1);
    PlayerTextDrawColor(playerid, Jdz_Stamina_Bar[playerid][0], 255);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Stamina_Bar[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Stamina_Bar[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, Jdz_Stamina_Bar[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Stamina_Bar[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Stamina_Bar[playerid][0], 0);

    Jdz_Stamina_Bar[playerid][1] = CreatePlayerTextDraw(playerid, 610.799987-54.0, 421.500000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, Jdz_Stamina_Bar[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Stamina_Bar[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Stamina_Bar[playerid][1], 20.500000, 22.500000);
    PlayerTextDrawSetOutline(playerid, Jdz_Stamina_Bar[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Stamina_Bar[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Stamina_Bar[playerid][1], 1);
    PlayerTextDrawColor(playerid, Jdz_Stamina_Bar[playerid][1], 0xEEEEEEFF);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Stamina_Bar[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Stamina_Bar[playerid][1], -294256590);
    PlayerTextDrawUseBox(playerid, Jdz_Stamina_Bar[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Stamina_Bar[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Stamina_Bar[playerid][1], 0);

    Jdz_Stamina_Bar[playerid][2] = CreatePlayerTextDraw(playerid, 616.200000-54.0, 427.000000, "HUD:radar_gym");
    PlayerTextDrawFont(playerid, Jdz_Stamina_Bar[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Stamina_Bar[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Stamina_Bar[playerid][2], 9.500000, 10.000000);
    PlayerTextDrawSetOutline(playerid, Jdz_Stamina_Bar[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Stamina_Bar[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Stamina_Bar[playerid][2], 1);
    PlayerTextDrawColor(playerid, Jdz_Stamina_Bar[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Stamina_Bar[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Stamina_Bar[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, Jdz_Stamina_Bar[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Stamina_Bar[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Stamina_Bar[playerid][2], 0);
    return 1;
}

Jdz_Water_Load(playerid){
    Jdz_Water_Bar[playerid][0] = CreatePlayerTextDraw(playerid, 610.000000-27.0, 420.000000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, Jdz_Water_Bar[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Water_Bar[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Water_Bar[playerid][0], 22.000000, 25.000000);
    PlayerTextDrawSetOutline(playerid, Jdz_Water_Bar[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Water_Bar[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Water_Bar[playerid][0], 1);
    PlayerTextDrawColor(playerid, Jdz_Water_Bar[playerid][0], 255);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Water_Bar[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Water_Bar[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, Jdz_Water_Bar[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Water_Bar[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Water_Bar[playerid][0], 0);

    Jdz_Water_Bar[playerid][1] = CreatePlayerTextDraw(playerid, 610.799987-27, 421.500000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, Jdz_Water_Bar[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Water_Bar[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Water_Bar[playerid][1], 20.500000, 22.500000);
    PlayerTextDrawSetOutline(playerid, Jdz_Water_Bar[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Water_Bar[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Water_Bar[playerid][1], 1);
    PlayerTextDrawColor(playerid, Jdz_Water_Bar[playerid][1], 0x4FC4FFFF);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Water_Bar[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Water_Bar[playerid][1], -294256590);
    PlayerTextDrawUseBox(playerid, Jdz_Water_Bar[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Water_Bar[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Water_Bar[playerid][1], 0);

    Jdz_Water_Bar[playerid][2] = CreatePlayerTextDraw(playerid, 616.200000-27, 427.000000, "HUD:radar_diner");
    PlayerTextDrawFont(playerid, Jdz_Water_Bar[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Water_Bar[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Water_Bar[playerid][2], 9.500000, 10.000000);
    PlayerTextDrawSetOutline(playerid, Jdz_Water_Bar[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Water_Bar[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Water_Bar[playerid][2], 1);
    PlayerTextDrawColor(playerid, Jdz_Water_Bar[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Water_Bar[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Water_Bar[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, Jdz_Water_Bar[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Water_Bar[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Water_Bar[playerid][2], 0);
    return 1;
}

Jdz_Hunger_Load(playerid){
    Jdz_Hunger_Bar[playerid][0] = CreatePlayerTextDraw(playerid, 610.000000, 420.000000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, Jdz_Hunger_Bar[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Hunger_Bar[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Hunger_Bar[playerid][0], 22.000000, 25.000000);
    PlayerTextDrawSetOutline(playerid, Jdz_Hunger_Bar[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Hunger_Bar[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Hunger_Bar[playerid][0], 1);
    PlayerTextDrawColor(playerid, Jdz_Hunger_Bar[playerid][0], 255);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Hunger_Bar[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Hunger_Bar[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, Jdz_Hunger_Bar[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Hunger_Bar[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Hunger_Bar[playerid][0], 0);

    Jdz_Hunger_Bar[playerid][1] = CreatePlayerTextDraw(playerid, 610.799987, 421.500000, "ld_pool:ball");
    PlayerTextDrawFont(playerid, Jdz_Hunger_Bar[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Hunger_Bar[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Hunger_Bar[playerid][1], 20.500000, 22.500000);
    PlayerTextDrawSetOutline(playerid, Jdz_Hunger_Bar[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Hunger_Bar[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Hunger_Bar[playerid][1], 1);
    PlayerTextDrawColor(playerid, Jdz_Hunger_Bar[playerid][1], -294256385);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Hunger_Bar[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Hunger_Bar[playerid][1], -294256590);
    PlayerTextDrawUseBox(playerid, Jdz_Hunger_Bar[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Hunger_Bar[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Hunger_Bar[playerid][1], 0);

    Jdz_Hunger_Bar[playerid][2] = CreatePlayerTextDraw(playerid, 616.200000, 427.000000, "HUD:radar_burgerShot");
    PlayerTextDrawFont(playerid, Jdz_Hunger_Bar[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, Jdz_Hunger_Bar[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, Jdz_Hunger_Bar[playerid][2], 9.500000, 10.000000);
    PlayerTextDrawSetOutline(playerid, Jdz_Hunger_Bar[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, Jdz_Hunger_Bar[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, Jdz_Hunger_Bar[playerid][2], 1);
    PlayerTextDrawColor(playerid, Jdz_Hunger_Bar[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, Jdz_Hunger_Bar[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, Jdz_Hunger_Bar[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, Jdz_Hunger_Bar[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, Jdz_Hunger_Bar[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, Jdz_Hunger_Bar[playerid][2], 0);
    return 1;
}