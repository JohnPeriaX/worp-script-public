#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_PARTY    (5)
#define MAX_PARTY_DYNAMIC   (50)
#define MAX_PARTY_TEXTDRAW  (20)

#define COMMAND_PARY_LEVEL (3)

enum partydata{
    partyID,
    partyEx,
    partyMember[5]
};
new PartyData[MAX_PARTY_DYNAMIC][partydata];

new PlayerText:PartyTextDraw[MAX_PLAYERS][MAX_PARTY_TEXTDRAW];
new PlayerBar:PartyProgress[MAX_PLAYERS][5];

new PlayerInParty[MAX_PLAYERS];
new PlayerPartyGetID[MAX_PLAYERS];
new PlayerPartyInviteID[MAX_PLAYERS];
new PlayerManagePlayerParty[MAX_PLAYERS];