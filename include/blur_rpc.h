#pragma once
#include <windows.h>
#include <string>
#include <vector>

#define LEN_STATE_BUFFER 128
#define LEN_DETAILS_BUFFER 128
#define LEN_IMG_KEY_BUFFER 32
#define LEN_IMG_TEXT_BUFFER 128
#define LEN_PARTY_ID_BUFFER 128


#define C_RP_STATUS_PTR 0x00D5F39C

#define ADDY_BLUR_STATE 0x00CE6B60
#define OFFSETS_BLUR_STATE {0x4}

#define ADDY_BLUR_PLAYLIST_ONLINE 0xD022F0
#define OFFSETS_BLUR_PLAYLIST_ONLINE {}

//#define ADDY_BLUR_PLAYLIST_PRIVATE 0xE35C54
//#define OFFSETS_BLUR_PLAYLIST_PRIVATE {}
#define ADDY_BLUR_PLAYLIST 0xE35C54
#define OFFSETS_BLUR_PLAYLIST {}



#define ADDY_BLUR_PARTY_MAX_PLAYERS 0x00DB4548
#define OFFSETS_BLUR_PARTY_MAX_PLAYERS_ONLINE {0x14} //20
#define OFFSETS_BLUR_PARTY_MAX_PLAYERS_PRIVATE {0x18} //20

//#define ADDY_BLUR_PARTY_MAX_PLAYERS_PRIVATE 0x00DEB9C8
//#define OFFSETS_BLUR_PARTY_MAX_PLAYERS_PRIVATE {0xBC} //188

#define ADDY_BLUR_PARTY_N_PLAYERS 0x00DB4530
#define OFFSETS_BLUR_PARTY_N_PLAYERS {0x14} //20



#define BLUR_STATE_MAIN 0
#define BLUR_STATE_MENU_MAIN 1
#define BLUR_STATE_MENU_STICKERS 2
#define BLUR_STATE_MENU_LEADERBOARDS 3
#define BLUR_STATE_MENU_HELP 4
#define BLUR_STATE_GARAGE 5
//6?
#define BLUR_STATE_SINGLEPLAYER 7
#define BLUR_STATE_PHOTOS 8
#define BLUR_STATE_CHALLENGES_FRIENDS 9
#define BLUR_STATE_CAREER 10
//11?
#define BLUR_STATE_MENU_MULTIPLAYER 12
//13?
#define BLUR_STATE_MENU_HISTORY 14
#define BLUR_STATE_MENU_LAN 15
#define BLUR_STATE_MENU_ONLINE 16
#define BLUR_STATE_MENU_MODS 17
#define BLUR_STATE_CHALLENGES_ONLINE 18
#define BLUR_STATE_ONLINE_LOBBY 19
//20--26BLUR
#define BLUR_STATE_RACE 27
#define BLUR_STATE_MOTOR_MASH 28
#define BLUR_STATE_PRIVATE_LOBBY 29


#define BLUR_PLAYLIST_COMMUNITY_EVENTS 24392580
#define BLUR_PLAYLIST_TEAM_RACING 2288498497
#define BLUR_PLAYLIST_TEAM_MOTOR_MASH 2366728894
#define BLUR_PLAYLIST_MOTOR_MASH 3468808035
#define BLUR_PLAYLIST_WORLD_TOUR 1527855959
#define BLUR_PLAYLIST_HARDCORE 3131866246
#define BLUR_PLAYLIST_POWERED_UP_RACING 1647796835
#define BLUR_PLAYLIST_SKIRMISH_RACING 1786934394
#define BLUR_PLAYLIST_DRIVING_SCHOOL 4114270737
#define BLUR_PLAYLIST_CUSTOM_GAME 0



uintptr_t follow_offsets(uintptr_t ptr_start, std::vector<uintptr_t> offsets);

int get_rp_state();

void format_details(int rp_state, char* sz_details, const size_t len);
//void format_playlist(unsigned int playlist_id, char* sz_playlist, char len_playlist, char* sz_small_img_key, char len_small_img_key); //legacy
void format_state(int rp_state, char* sz_playlist, const size_t len_playlist, char* sz_small_img_key, const size_t len_small_img_key);
void format_party(int rp_state, char* party_size, char* party_max, char* party_id, const size_t len_party_id);
void format_time(int rp_state, int64_t* race_start_time);

