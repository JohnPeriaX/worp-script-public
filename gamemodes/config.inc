//-----------------[ MYSQL ]--------------------//
#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASS ""
#define MYSQL_DB "worpth"

// #define MYSQL_HOST "localhost"
// #define MYSQL_USER "root"
// #define MYSQL_PASS "Mzb2S8r7fQZreL4D"
// #define MYSQL_DB "worpth"
//----------------------------------------------//

//-----------------[ การตั้งค่า ]--------------------//

#define SERVER_NAME "Gta Worp City 5.0"
#define SERVER_SHORTNAME "V.2.5.0"
#define SERVER_VERSION "V.2.5.0"

//----------------------------------------------//

#define COLOR_SERVER 0x23D101AA

//JOB
#define FARMERJOB (1)
#define BUILDJOB  (2)
#define FISHJOB   (3)
#define GASJOB    (4)
#define COWJOB    (5)
#define ENGJOB    (6)
#define JELLYJOB  (7)
#define WEAPONDEALERJOB  (8)
#define GARBAGEJOB  (9)
#define RUBBERJOB   (10)
#define CLOTHJOB    (11)
#define SEEKERJOB   (12)
#define GARDENER    (13)
#define OILJOB  	(14)
#define SHELLJOB	(15)
#define ORANGEJOB	(16)
#define SHARKJOB    (17)
#define PIZZAJOB    (18)
#define DELIOILJOB	(19)

#define TEAM_RED 0xFF0000FF
#define TEAM_YELLOW 0xFFE800FF
#define TEAM_GREEN 0x00FF0FFF
#define TEAM_ORANGE 0xFF8700FF
#define TEAM_PINK 0xFF7DC4FF

#define GROUP_POLICE     1
#define GROUP_MEDIC      2
#define GROUP_GOV        3
#define GROUP_MECHANIC   4
#define GROUP_GANG       5
#define GROUP_NATIONAL   6
#define GROUP_NEWS		 7

#define                 NTABLE1									378.1715,-122.2264,1001.4922
#define                 NTABLE2									378.1715,-125.4046,1001.4922
#define                 NTABLE3									378.1699,-128.4687,1001.4922
#define                 NTABLE4									378.1716,-131.4947,1001.4922

#define                 POSTABLE1_1								380.0248,-121.3773,1002.0259
#define                 ANGTABLE1_1								180.8184
#define                 POSTABLE1_2								379.0375,-121.3711,1002.0259
#define                 ANGTABLE1_2								181.1083
#define                 POSTABLE1_3								380.2073,-123.1895,1001.9310
#define                 ANGTABLE1_3								354.0699
#define                 POSTABLE1_4								379.2819,-123.0403,1001.9310
#define                 ANGTABLE1_4								0.0233

#define                 POSTABLE2_1								380.0463,-124.5039,1001.9310
#define                 ANGTABLE2_1								177.3251
#define                 POSTABLE2_2								379.1240,-124.4780,1001.9310
#define                 ANGTABLE2_2								177.3251
#define                 POSTABLE2_3        						380.1512,-126.2182,1001.9310
#define                 ANGTABLE2_3								358.1202
#define                 POSTABLE2_4								378.8937,-126.0965,1001.9310
#define                 ANGTABLE2_4								358.1202

#define                 POSTABLE3_1								379.9493,-127.7161,1001.9310
#define                 ANGTABLE3_1								178.5785
#define                 POSTABLE3_2								378.9901,-127.7296,1001.9310
#define                 ANGTABLE3_2								182.0252
#define                 POSTABLE3_3								380.1278,-129.3799,1001.9310
#define                 ANGTABLE3_3								358.5785
#define                 POSTABLE3_4								378.9283,-129.3798,1001.9310
#define                 ANGTABLE3_4								358.5785

#define                 POSTABLE4_1								380.0059,-130.6832,1001.9310
#define                 ANGTABLE4_1								177.0118
#define                 POSTABLE4_2								379.0063,-130.7694,1001.9310
#define                 ANGTABLE4_2								177.0118
#define                 POSTABLE4_3								380.2360,-132.4676,1002.0422
#define                 ANGTABLE4_3								356.0718
#define                 POSTABLE4_4								379.2849,-132.3236,1002.0422
#define                 ANGTABLE4_4								357.9518

#define MAX_VEH          (5000)
#define MAX_DYNAMIC_CARS (5000)
#define MAX_DYNAMIC_JOBS (25)
#define MAX_GATES (100)

#define MAX_NAME (64)

#define BitFlag_On(%0,%1)             ((%0) |= (%1))
#define BitFlag_Off(%0,%1)            ((%0) &= ~(%1))
#define BitFlag_Get(%0,%1)            ((%0) & (%1)) 

#define SECONDS(%0)             (%0*1000)
#define MINUTES(%0)             (%0*SECONDS(60))
#define HOURS(%0)               (%0*MINUTES(60))

#define HOLDING(%0) \
    ((newkeys & (%0)) == (%0))

#define Range_VShort                                                            4.0
#define Range_Short                                                             15.0
#define Range_Normal                                                            20.0
#define Range_Long                                                              40.0
#define Range_VLong                                                             100.0  

#define Cheat_Version "Anti-Cheat V.1.0"

#define SPLITLENGTH 118

#define         MODEL_NULL 			(18700)

#define ErrorMsg(%0,%1) \
    SendClientMessageEx(%0, COLOR_RED, "[ข้อผิดพลาด]:{FFFFFF} "%1)
#define SystemMsg(%0,%1) \
    SendClientMessageEx(%0, COLOR_ORANGE, "[คำแนะนำ]:{FFFFFF} "%1)


#define MAX_ADMIN_VEHICLES (100)
#define MAX_OWNABLE_CARS   (10)

#define THREAD_LOAD_TICKETS (12)
#define THREAD_LOAD_CONTACTS (10)

#define MODEL_SELECTION_SKIN (1)

#define LEVEL_MONEY (100)

#define                 DIALOG_CARMOD1			 				(114)
#define                 DIALOG_CARMOD2			 				(115)
#define                 DIALOG_CARMOD3			 				(116)
#define                 DIALOG_CARMOD4			 				(117)
#define                 DIALOG_CARMOD5			 				(118)
#define                 DIALOG_CARMOD6			 				(119)
#define                 DIALOG_CARMOD7			 				(120)
#define                 DIALOG_CARMODCOLOR1			 			(121)
#define                 DIALOG_CARMODCOLOR2			 			(122)
#define                 DIALOG_CARMODMAX			 			(123)
#define                 DIALOG_CARMODPAINTJOB1		 			(124)
#define                 DIALOG_CARMODPAINTJOB2		 			(125)
#define                 DIALOG_CARMODPAINTJOB3		 			(126)
#define                 DIALOG_CARMODPAINTJOBEND		 		(127)
#define                 DIALOG_CARMODCHO1			 			(128)
#define                 DIALOG_CARMODCHO2			 			(129)
#define                 DIALOG_CARMODCHO3			 			(130)
#define                 DIALOG_CARMODCHO4			 			(131)

//COLOR

#define COLOR_TREE        (0x50B228FF)
#define COLOR_ALLDEPT 0xFF8282AA
#define COLOR_DEPARTMENT  (0xFFD7004A)
#define COLOR_GRAD1 0xB4B5B7FF
#define COLOR_GRAD2 0xBFC0C2FF
#define COLOR_GRAD3 0xCBCCCEFF
#define COLOR_GRAD4 0xD8D8D8FF
#define COLOR_GRAD5 0xE3E3E3FF
#define COLOR_GRAD6 0xF0F0F0FF
#define COLOR_HOSPITAL    (0xFF8282FF)
#define DEFAULT_COLOR     (0xFFFFFFFF)
#define COLOR_CLIENT      (0xAAC4E5FF)
#define COLOR_RADIOEX     (0xFFEC8BFF)
#define COLOR_RADIO		  (0x8D8DFFFF)
#define COL_WHITE                                                               "{FFFFFF}"
#define COLOR_HOTORANGE 						                                 0xF97804FF
#define COL_RED                                                                 "{F81414}"
#define COL_GREEN                                                               "{00FF22}"
#define COL_BLUE                                                                "{00C0FF}"
#define COL_LBLUE                                                               "{D3DCE3}"
#define COL_ORANGE                                                              "{FFAF00}"
#define COL_CYAN                                                                "{00FFEE}"
#define COL_BLACK                                                               "{0E0101}"
#define COL_GRAY                                                                "{C3C3C3}"
#define COL_DGREEN                                                              "{336633}"
#define COLOR_SUPERRED 	0xFF0000FF

#define COLOR_GRAPE (0x7E06FEFF)
#define COLOR_BLUE                                                              0x0000FFFF
#define COLOR_LGREEN                                                            0x00FF00FF
#define COLOR_YELLOW                                                            0xFFFF00FF
#define COLOR_BLACK                                                             0x000000FF
#define COLOR_GRAY                                                              0xC0C0C0FF
#define COLOR_WHITE                                                             0xFFFFFFFF
#define COLOR_GREY                                                              0xAFAFAFAA
#define COLOR_LBLUE                                                             0x3C3176AA
#define COLOR_MBLUE                                                             0x2E37FEAA
#define COLOR_DGREEN                                                            0x007200AA
#define COLOR_RP                                                                0xC2A2DAAA


#define COLOR_AQUA                                                               0x00FFFFFF
#define COLOR_AQUAMARINE                                                         0x7FFFD4FF
#define COLOR_AZURE                                                              0xF0FFFFFF
#define COLOR_BEIGE                                                              0xF5F5DCFF
#define COLOR_BISQUE                                                             0xFFE4C4FF
#define COLOR_BLACK                                                              0x000000FF
#define COLOR_BLANCHEDALMOND                                                     0xFFEBCDFF
#define COLOR_BLUE                                                               0x0000FFFF
#define COLOR_BLUEVIOLET                                                         0x8A2BE2FF
#define COLOR_BROWN                                                              0xA52A2AFF
#define COLOR_BURLYWOOD                                                          0xDEB887FF
#define COLOR_BUTTONFACE                                                         0xF0F0F0FF
#define COLOR_BUTTONHIGHLIGHT                                                    0xFFFFFFFF
#define COLOR_BUTTONSHADOW                                                       0xA0A0A0FF
#define COLOR_CADETBLUE                                                          0x5F9EA0FF
#define COLOR_CHARTREUSE                                                         0x7FFF00FF
#define COLOR_CHOCOLATE                                                          0xD2691EFF
#define COLOR_CORAL                                                              0xFF7F50FF
#define COLOR_CORNFLOWERBLUE                                                     0x6495EDFF
#define COLOR_CORNSILK                                                           0xFFF8DCFF
#define COLOR_CRIMSON                                                            0xDC143CFF
#define COLOR_CYAN                                                               0x00FFFFFF
#define COLOR_DARKBLUE                                                           0x00008BFF
#define COLOR_DARKCYAN                                                           0x008B8BFF
#define COLOR_DARKGOLDENROD                                                      0xB8860BFF
#define COLOR_DARKGRAY                                                           0xA9A9A9FF
#define COLOR_DARKGREEN                                                          0x006400FF
#define COLOR_DARKKHAKI                                                          0xBDB76BFF
#define COLOR_DARKMAGENTA                                                        0x8B008BFF
#define COLOR_DARKOLIVEGREEN                                                     0x556B2FFF
#define COLOR_DARKORANGE                                                         0xFF8C00FF
#define COLOR_DARKORCHID                                                         0x9932CCFF
#define COLOR_DARKRED                                                            0x8B0000FF
#define COLOR_DARKSALMON                                                         0xE9967AFF
#define COLOR_DARKSEAGREEN                                                       0x8FBC8BFF
#define COLOR_DARKSLATEBLUE                                                      0x483D8BFF
#define COLOR_DARKSLATEGRAY                                                      0x2F4F4FFF
#define COLOR_DARKTURQUOISE                                                      0x00CED1FF
#define COLOR_DARKVIOLET                                                         0x9400D3FF
#define COLOR_DEEPPINK                                                           0xFF1493FF
#define COLOR_DEEPSKYBLUE                                                        0x00BFFFFF
#define COLOR_DESKTOP                                                            0x000000FF
#define COLOR_DIMGRAY                                                            0x696969FF
#define COLOR_DODGERBLUE                                                         0x1E90FFFF
#define COLOR_FIREBRICK                                                          0xB22222FF
#define COLOR_FLORALWHITE                                                        0xFFFAF0FF
#define COLOR_FORESTGREEN                                                        0x228B22FF
#define COLOR_FUCHSIA                                                            0xFF00FFFF
#define COLOR_GAINSBORO                                                          0xDCDCDCFF
#define COLOR_GHOSTWHITE                                                         0xF8F8FFFF
#define COLOR_GOLD                                                               0xFFD700FF
#define COLOR_GOLDENROD                                                          0xDAA520FF
#define COLOR_GRAYTEXT                                                           0x808080FF
#define COLOR_GREEN                                                              0x008000FF
#define COLOR_GREENYELLOW                                                        0xADFF2FFF
#define COLOR_HIGHLIGHT                                                          0x3399FFFF
#define COLOR_HIGHLIGHTTEXT                                                      0xFFFFFFFF
#define COLOR_HONEYDEW                                                           0xF0FFF0FF
#define COLOR_HOTPINK                                                            0xFF69B4FF
#define COLOR_HOTTRACK                                                           0x0066CCFF
#define COLOR_INDIANRED                                                          0xCD5C5CFF
#define COLOR_INDIGO                                                             0x4B0082FF
#define COLOR_INFO                                                               0xFFFFE1FF
#define COLOR_INFOTEXT                                                           0x000000FF
#define COLOR_IVORY                                                              0xFFFFF0FF
#define COLOR_KHAKI                                                              0xF0E68CFF
#define COLOR_LAVENDER                                                           0xE6E6FAFF
#define COLOR_LAVENDERBLUSH                                                      0xFFF0F5FF
#define COLOR_LAWNGREEN                                                          0x7CFC00FF
#define COLOR_LEMONCHIFFON                                                       0xFFFACDFF
#define COLOR_LIGHTBLUE                                                          0xADD8E6FF
#define COLOR_LIGHTCORAL                                                         0xF08080FF
#define COLOR_LIGHTCYAN                                                          0xE0FFFFFF
#define COLOR_LIGHTGOLDENRODYELLOW                                               0xFAFAD2FF
#define COLOR_LIGHTGRAY                                                          0xD3D3D3FF
#define COLOR_LIGHTGREEN                                                         0x90EE90FF
#define COLOR_LIGHTPINK                                                          0xFFB6C1FF
#define COLOR_LIGHTSALMON                                                        0xFFA07AFF
#define COLOR_LIGHTSEAGREEN                                                      0x20B2AAFF
#define COLOR_LIGHTSKYBLUE                                                       0x87CEFAFF
#define COLOR_LIGHTSLATEGRAY                                                     0x778899FF
#define COLOR_LIGHTSTEELBLUE                                                     0xB0C4DEFF
#define COLOR_LIGHTYELLOW                                                        0xFFFFE0FF
#define COLOR_LIME                                                               0x00FF00FF
#define COLOR_LIMEGREEN                                                          0x32CD32FF
#define COLOR_LINEN                                                              0xFAF0E6FF
#define COLOR_MAGENTA                                                            0xFF00FFFF
#define COLOR_MAROON                                                             0x800000FF
#define COLOR_MEDIUMAQUAMARINE                                                   0x66CDAAFF
#define COLOR_MEDIUMBLUE                                                         0x0000CDFF
#define COLOR_MEDIUMORCHID                                                       0xBA55D3FF
#define COLOR_MEDIUMPURPLE                                                       0x9370DBFF
#define COLOR_MEDIUMSEAGREEN                                                     0x3CB371FF
#define COLOR_MEDIUMSLATEBLUE                                                    0x7B68EEFF
#define COLOR_MEDIUMSPRINGGREEN                                                  0x00FA9AFF
#define COLOR_MEDIUMTURQUOISE                                                    0x48D1CCFF
#define COLOR_MEDIUMVIOLETRED                                                    0xC71585FF
#define COLOR_MIDNIGHTBLUE                                                       0x191970FF
#define COLOR_MINTCREAM                                                          0xF5FFFAFF
#define COLOR_MISTYROSE                                                          0xFFE4E1FF
#define COLOR_MOCCASIN                                                           0xFFE4B5FF
#define COLOR_NAVAJOWHITE                                                        0xFFDEADFF
#define COLOR_NAVY                                                               0x000080FF
#define COLOR_OLDLACE                                                            0xFDF5E6FF
#define COLOR_OLIVE                                                              0x808000FF
#define COLOR_OLIVEDRAB                                                          0x6B8E23FF
#define COLOR_ORANGE                                                             0xFFA500FF
#define COLOR_ORANGERED                                                          0xFF4500FF
#define COLOR_ORCHID                                                             0xDA70D6FF
#define COLOR_PALEGOLDENROD                                                      0xEEE8AAFF
#define COLOR_PALEGREEN                                                          0x98FB98FF
#define COLOR_PALETURQUOISE                                                      0xAFEEEEFF
#define COLOR_PALEVIOLETRED                                                      0xDB7093FF
#define COLOR_PAPAYAWHIP                                                         0xFFEFD5FF
#define COLOR_PEACHPUFF                                                          0xFFDAB9FF
#define COLOR_PERU                                                               0xCD853FFF
#define COLOR_PINK                                                               0xFFC0CBFF
#define COLOR_PLUM                                                               0xDDA0DDFF
#define COLOR_POWDERBLUE                                                         0xB0E0E6FF
#define COLOR_PURPLE                                                             0x800080FF
#define COLOR_RED                                                                0xFF0000FF
#define COLOR_ROSYBROWN                                                          0xBC8F8FFF
#define COLOR_ROYALBLUE                                                          0x4169E1FF
#define COLOR_SADDLEBROWN                                                        0x8B4513FF
#define COLOR_SALMON                                                             0xFA8072FF
#define COLOR_SANDYBROWN                                                         0xF4A460FF
#define COLOR_SEAGREEN                                                           0x2E8B57FF
#define COLOR_SEASHELL                                                           0xFFF5EEFF
#define COLOR_SIENNA                                                             0xA0522DFF
#define COLOR_SILVER                                                             0xC0C0C0FF
#define COLOR_SKYBLUE                                                            0x87CEEBFF
#define COLOR_SLATEBLUE                                                          0x6A5ACDFF
#define COLOR_SLATEGRAY                                                          0x708090FF
#define COLOR_SNOW                                                               0xFFFAFAFF
#define COLOR_SPRINGGREEN                                                        0x00FF7FFF
#define COLOR_STEELBLUE                                                          0x4682B4FF
#define COLOR_TAN                                                                0xD2B48CFF
#define COLOR_TEAL                                                               0x008080FF
#define COLOR_THISTLE                                                            0xD8BFD8FF
#define COLOR_TOMATO                                                             0xFF6347FF
#define COLOR_TRANSPARENT                                                        0xFFFFFF00
#define COLOR_TURQUOISE                                                          0x40E0D0FF
#define COLOR_VIOLET                                                             0xEE82EEFF
#define COLOR_WHEAT                                                              0xF5DEB3FF
#define COLOR_WHITE                                                              0xFFFFFFFF
#define COLOR_WINDOWTEXT                                                         0x000000FF
#define COLOR_YELLOW                                                             0xFFFF00FF
#define COLOR_YELLOWGREEN                                                        0x9ACD32FF
#define STEALTH_ORANGE                                                           0xFF880000
#define STEALTH_OLIVE                                                            0x66660000
#define STEALTH_GREEN                                                            0x33DD1100
#define STEALTH_PINK                                                             0xFF22EE00
#define STEALTH_BLUE                                                             0x0077BB00