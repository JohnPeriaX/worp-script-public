#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_STORY_GANG (30)

#define Story_Wait    (1)
#define Story_Cancel  (2)
#define Story_Confirm (3)
#define Story_Finish  (4)
#define Story_Timeout (5)

enum story_gang{
    story_ID,
    story_Mygang,
    story_MygangName[64],
    story_Enemy,
    story_EnemyName[64],
    story_Days,
    story_TimeStart[32],
    story_TimeEnd[32],
    story_Label,
    story_Bigcar,
    story_Pushhome,
    story_Hidebody,
    story_Skingang,
    story_Weapon,
    story_Money,
    story_Details[256],
    story_State,
    story_TimeHour,
    story_GangWinName[64]
};
new Story_Gang[MAX_STORY_GANG][story_gang];
new Iterator:Iter_Story<MAX_STORY_GANG>;

enum story_player{
    story_Enemy,
    story_EnemyName[64],
    story_Days,
    story_TimeStart[32],
    story_TimeEnd[32],
    story_Label,
    story_Bigcar,
    story_Pushhome,
    story_Hidebody,
    story_Skingang,
    story_Weapon,
    story_Money,
    story_Details[256]
};
new PlayerStoryGang[MAX_PLAYERS][story_player];