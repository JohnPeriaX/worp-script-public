#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_PLAYER_TICKETS (50)

enum ticketData {
	ticketID,
	ticketExists,
	ticketFee,
	ticketGroupID,
    ticketBy[64],
	ticketDate[36],
	ticketReason[64]
};
new TicketData[MAX_PLAYERS][MAX_PLAYER_TICKETS][ticketData];