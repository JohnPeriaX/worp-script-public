#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
    g_ReplyChannel = DCC_FindChannelById("976800275711008848");
    UseWeaponChannel = DCC_FindChannelById("976799959577940008");
    MoneyLogChannel = DCC_FindChannelById("976800065316347955");
    StoryGangChannel = DCC_FindChannelById("923351362643828817");

    WithdrawPolice = DCC_FindChannelById("976800536785461278");
    WithdrawMedic = DCC_FindChannelById("976800562647564308");
    CraftWeapon = DCC_FindChannelById("976799312984047616");

    guildName = DCC_FindGuildById("976126324357861416");
    adminRole = DCC_FindRoleById("976127199805591603");
    new _message[128];
    format(_message, sizeof(_message), "``` - Discord-Bot V.2.0 | Developer by JustinzDev \
    \n Connected...\
    \n [Features]\
    \n - Logs Server\
    \n - Admin Commands```");
    DCC_SendChannelMessage(g_ReplyChannel, _message);
    return 1;
}

public DCC_OnMessageCreate(DCC_Message:message){

    new DCC_Channel:channel;
    DCC_GetMessageChannel(message, channel);

    if(channel != g_ReplyChannel) return 0;

    new DCC_User:author;
    DCC_GetMessageAuthor(message, author);

    new bool:hasRole;
    DCC_HasGuildMemberRole(guildName, author, adminRole, hasRole);

    if(!hasRole) return 0;

    new command[128], string[128], params[256], _message[128];

    DCC_GetMessageContent(message, params);

    sscanf(params, "s[128]s[128]", command, string);

    new bool:isBot;
    DCC_IsUserBot(author, isBot);

    if(isBot) return 1;

    if(!strcmp(command, "!savedata", true)){
        foreach (new i : Player) {
            if(LoggedIn[i] == true){
                StorePlayerWeapon(i);
                Character_Save(i);
            }
        }

        printf("Successfully Save!");
        format(_message, sizeof(_message), "` Save Player Data Successfully. `");
        DCC_SendChannelMessage(g_ReplyChannel, _message);
    }
    else if(!strcmp(command, "!sm", true)){
        new userid;
        sscanf(string, "u", userid);
        if(userid == INVALID_PLAYER_ID) return DCC_SendChannelMessage(channel, "PlayerId Not Correct!.");
        if(!LoggedIn[userid]) return DCC_SendChannelMessage(channel, "PlayerId Not Login!.");

        SetPlayerPosEx(userid, 1120.4299,-1378.5870,14.2879, 0, 0);
        format(_message, sizeof(_message), ":white_check_mark: Send [ %s ] >> Market.", ReturnRoleplayName(userid));
        DCC_SendChannelMessage(channel, _message);
    }
    else if(!strcmp(command, "!warn", true)){
        new userid, reason[128];
        sscanf(string, "uS(Not specified)[128]", userid, reason);
        if(userid == INVALID_PLAYER_ID) return DCC_SendChannelMessage(channel, "> PlayerId Not Correct!.");
        if(!LoggedIn[userid]) return DCC_SendChannelMessage(channel, "> PlayerId Not Login!.");

        PlayerData[userid][pWarn] += 1;
        SendClientMessageEx(userid, COLOR_RED, "- คุณได้รับการเตือนจากผู้ดูแล ตอนนี้คุณมี Warn อยู่ (%d/3)", PlayerData[userid][pWarn]);
        SendClientMessageToAllEx(0xFF0000AA, "ผู้ดูแลระบบ ได้ทำการ 'เตือน' ผู้เล่น '%s(%d)' สาเหตุ: %s", ReturnRoleplayName(userid), userid, reason);
        if(PlayerData[userid][pWarn] >= 3){
            PlayerData[userid][pBan] = 1;
            SendClientMessageToAllEx(0xFF6100AA, "ระบบ ได้ทำการ 'แบน' ผู้เล่น '%s(%d)' สาเหตุ: Warn ครบ 3 ครั้ง", ReturnRoleplayName(userid), userid);
            SetTimerEx("FixKick", 500, false, "d", userid);

            format(_message, sizeof(_message), "> :x: [ %s ] Has Ban Reason: Warn (3/3)", ReturnRoleplayName(userid));
            DCC_SendChannelMessage(channel, _message);
        }
        format(_message, sizeof(_message), "> :exclamation: Make Warn [ %s ] >> + 1 Total Warn: %d Reason: %s", ReturnRoleplayName(userid), PlayerData[userid][pWarn], reason);
        DCC_SendChannelMessage(channel, _message);
    }
    else if(!strcmp(command, "!anreserver", true)){
        SendClientMessageToAllEx(0xFF5B5BAA, "(( WO:RP-STAFF: อีก 10 นาทีจะทำการรีเซิฟเวอร์... ))");
        DCC_SendChannelMessage(channel, "** Reserver In 10 Mins... **");
    }
    else if(!strcmp(command, "!admins", true)){
        foreach(new x : Player) {
            if(!LoggedIn[x]) continue;
            if(PlayerData[x][pAdmin] > 0 && PlayerData[x][pAdmin] <= 1339){
                format(_message, sizeof(_message), "> ** [Admin Level: %d] %s (%s) **", PlayerData[x][pAdmin], ReturnRoleplayName(x), PlayerData[x][pAdminName]);
                DCC_SendChannelMessage(channel, _message);
            }
        }
    }
    else if(!strcmp(command, "!help", true)){
        DCC_SendChannelMessage(channel, "> **[Commands]:** !savedata, !sm [playerid/name], !warn [playerid/name] [reason], !admins, !togalert");
    }
    else if(!strcmp(command, "!togalert", true)){
        if(TogAlertLog){
            TogAlertLog = false;
            DCC_SendChannelMessage(channel, "> **[Alert-Logs]:** Off");
        }
        else{
            TogAlertLog = true;
            DCC_SendChannelMessage(channel, "> **[Alert-Logs]:** On");
        }
    }
    else return 1;
    return 1;
}