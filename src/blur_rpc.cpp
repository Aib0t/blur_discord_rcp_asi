#include <ctime> // time() func
#include <string>
#include <vadefs.h>
//#include <inttypes.h>
//#include <stdint.h>
//#include <vadefs.h>

extern "C" {
	#include "discord_rpc.h"
	#include "discord_register.h"
}
#include "blur_rpc.h"
#include "config.h"


//DEBUG STUFF: TODO RM ME
//#include <Windows.h> // OutputDebugString()
#include <iostream>
#include <fstream>
//#include <stdio.h>
//IDK


/*
static void format_state (char* state, char length) {
	if (*C_CAR_PTR < 0) {
		state[0] = 0;
		return;
	}
	const int car_addr = (*CARS_ADDR_PTR + (*C_CAR_PTR * 0x890));
	const char* const car_name = (char*)(car_addr + 0x20);
	const auto car_itr = CAR_TABLE.find(car_name);
	if (car_itr != CAR_TABLE.end()) {
		sprintf_s(state, length, "%s", car_itr->second);
	} else {
		const char* const car_brand = (char*)(car_addr + 0xC0);
		sprintf_s(state, length, "%s %s", car_brand, car_name);
	}
}
*/


// lil logger to debug some errors, maybe RM later
void log(std::string output) {
	static std::ofstream log_file("blur_rpc.log");
	log_file << std::to_string(time(0)).append(": ") << output << std::endl;
	log_file.flush();
	//OutputDebugString(output.c_str());
}


// you can make an offset 0 too
// if you pass an empty vec, you can just just use it to read the start ptr
uintptr_t follow_offsets(uintptr_t ptr_start, std::vector<uintptr_t> offsets) {
	uintptr_t moduleBase = (uintptr_t) GetModuleHandle(NULL);
	uintptr_t addr = moduleBase + ptr_start;
	for (uintptr_t offset : offsets) {
		if (addr == NULL) break; // The most basic of checks, but might save us from a few segfaults :: TODO fantastik chek
		addr = *(uintptr_t*) addr; // TODO consider checking if we are reading some bad mem here?
		if (addr == NULL) break; // The most basic of checks, but might save us from a few segfaults :: TODO fantastik chek
		addr += offset;
	}
	return addr;
}


int get_rp_state() {
	int rp_state = -1;
	uintptr_t ptr = follow_offsets(ADDY_BLUR_STATE, OFFSETS_BLUR_STATE);
	if (ptr != NULL) rp_state = *(uintptr_t*) ptr;
	return rp_state;
}


void format_details(int rp_state, char* sz_details, const size_t len) {
	switch (rp_state) {
		case BLUR_STATE_MAIN:
			sprintf_s(sz_details, len, "(Main menu)");
			break;

		case BLUR_STATE_MENU_MAIN: // what?
			sprintf_s(sz_details, len, "Main menu");
			break;

		case BLUR_STATE_MENU_STICKERS:
			sprintf_s(sz_details, len, "Stickers");
			break;

		case BLUR_STATE_MENU_LEADERBOARDS:
			sprintf_s(sz_details, len, "Leaderboards");
			break;

		case BLUR_STATE_MENU_HELP:
			sprintf_s(sz_details, len, "Reading help");
			break;

		case BLUR_STATE_GARAGE:
			sprintf_s(sz_details, len, "Garage");
			break;

		//
		case BLUR_STATE_SINGLEPLAYER:
			sprintf_s(sz_details, len, "Singleplayer");
			break;

		case BLUR_STATE_PHOTOS:
			sprintf_s(sz_details, len, "Photos (singleplayer)");
			break;

		case BLUR_STATE_CHALLENGES_FRIENDS:
			sprintf_s(sz_details, len, "Friends challenges");
			break;

		case BLUR_STATE_CAREER:
			sprintf_s(sz_details, len, "Career");
			break;

		//

		case BLUR_STATE_MENU_MULTIPLAYER:
			sprintf_s(sz_details, len, "Multiplayer menu");
			break;

		//

		case BLUR_STATE_MENU_HISTORY:
			sprintf_s(sz_details, len, "Race history");
			break;

		case BLUR_STATE_MENU_LAN:
			sprintf_s(sz_details, len, "In LAN menu");
			break;

		case BLUR_STATE_MENU_ONLINE:
			sprintf_s(sz_details, len, "Online menu");
			break;

		case BLUR_STATE_MENU_MODS:
			sprintf_s(sz_details, len, "In mods menu");
			break;

		case BLUR_STATE_CHALLENGES_ONLINE:
			sprintf_s(sz_details, len, "Online challenges");
			break;

		case BLUR_STATE_ONLINE_LOBBY:
			sprintf_s(sz_details, len, "In online lobby");
			break;

		//..

		case BLUR_STATE_RACE:
			sprintf_s(sz_details, len, "In race");
			break;

		case BLUR_STATE_MOTOR_MASH:
			sprintf_s(sz_details, len, "In Motor Mash");
			break;

		case BLUR_STATE_PRIVATE_LOBBY:
			sprintf_s(sz_details, len, "In private lobby");
			break;

		default:
			sprintf_s(sz_details, len, "Unknown %d", rp_state);
			break;
	}
}


void format_state(int rp_state, char* sz_playlist, const size_t len_playlist, char* sz_small_img_key, const size_t len_small_img_key) {
	unsigned int playlist_id = BLUR_PLAYLIST_NONE;
	/*
	if (rp_state == BLUR_STATE_ONLINE_LOBBY) {
		//playlist_id = *(unsigned int*) ADDY_BLUR_PLAYLIST_ONLINE;
		//playlist_id = *(unsigned int*) follow_offsets(ADDY_BLUR_PLAYLIST_ONLINE, OFFSETS_BLUR_PLAYLIST_ONLINE);
	} else if (rp_state == BLUR_STATE_PRIVATE_LOBBY) {
		//playlist_id = *(unsigned int*) ADDY_BLUR_PLAYLIST_PRIVATE;
		//playlist_id = *(unsigned int*) follow_offsets(ADDY_BLUR_PLAYLIST_PRIVATE, OFFSETS_BLUR_PLAYLIST_PRIVATE);
	*/
	if ((rp_state == BLUR_STATE_ONLINE_LOBBY) || (rp_state == BLUR_STATE_PRIVATE_LOBBY)) {
		//playlist_id = *(unsigned int*) follow_offsets(ADDY_BLUR_PLAYLIST_PRIVATE, OFFSETS_BLUR_PLAYLIST_PRIVATE);
		uintptr_t ptr = follow_offsets(ADDY_BLUR_PLAYLIST, OFFSETS_BLUR_PLAYLIST); //TODO NOTE: for me, this one is [always] correct (?)
		if (ptr != NULL) playlist_id = *(unsigned int*) ptr;
	}
	switch (playlist_id) {
		case BLUR_PLAYLIST_COMMUNITY_EVENTS:
			sprintf_s(sz_playlist, len_playlist, "Community Events");
			sprintf_s(sz_small_img_key, len_small_img_key, "community_events");
			break;

		case BLUR_PLAYLIST_TEAM_RACING:
			sprintf_s(sz_playlist, len_playlist, "Team Racing");
			sprintf_s(sz_small_img_key, len_small_img_key, "team_racing");
			break;

		case BLUR_PLAYLIST_TEAM_MOTOR_MASH:
			sprintf_s(sz_playlist, len_playlist, "Team Motor Mash");
			sprintf_s(sz_small_img_key, len_small_img_key, "team_motor_mash");
			break;

		case BLUR_PLAYLIST_MOTOR_MASH:
			sprintf_s(sz_playlist, len_playlist, "Motor mash");
			sprintf_s(sz_small_img_key, len_small_img_key, "motor_mash");
			break;

		case BLUR_PLAYLIST_WORLD_TOUR:
			sprintf_s(sz_playlist, len_playlist, "World Tour");
			sprintf_s(sz_small_img_key, len_small_img_key, "world_tour");
			break;

		case BLUR_PLAYLIST_HARDCORE:
			sprintf_s(sz_playlist, len_playlist, "Hardcore Racing");
			sprintf_s(sz_small_img_key, len_small_img_key, "hardcore");
			break;

		case BLUR_PLAYLIST_POWERED_UP_RACING:
			sprintf_s(sz_playlist, len_playlist, "Powered-up racing");
			sprintf_s(sz_small_img_key, len_small_img_key, "powered_up_racing");
			break;

		case BLUR_PLAYLIST_SKIRMISH_RACING:
			sprintf_s(sz_playlist, len_playlist, "Skirmish racing");
			sprintf_s(sz_small_img_key, len_small_img_key, "skirmish_racing");
			break;

		case BLUR_PLAYLIST_DRIVING_SCHOOL:
			sprintf_s(sz_playlist, len_playlist, "Driving school");
			sprintf_s(sz_small_img_key, len_small_img_key, "driving_school");
			break;

		case BLUR_PLAYLIST_CUSTOM_GAME:
			sprintf_s(sz_playlist, len_playlist, "Custom game");
			sprintf_s(sz_small_img_key, len_small_img_key, "custom_game");
			break;

		case BLUR_PLAYLIST_NONE: // prob means we didnt read a playlist_id
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "");
			break;

		default:
			sprintf_s(sz_playlist, len_playlist, "Unknown game type: %d", playlist_id);
			break;
	}
}

void format_party(int rp_state, char* party_size, char* party_max, char* sz_party_id, const size_t len_party_id) {
	// sprintf_s(partyId, length, "12222222");
	// *partyMax = 20;
	// *partySize = 1;
	//FIXME changed offsets, revise on other clients
	// TODO revise!
	*party_max = 8; // changed to 8 cause thats what the ingame menu menu says...
	// find lan values maybe?
	if (rp_state == BLUR_STATE_ONLINE_LOBBY) {
		uintptr_t ptr = follow_offsets(ADDY_BLUR_PARTY_MAX_PLAYERS, OFFSETS_BLUR_PARTY_MAX_PLAYERS_ONLINE);
		if (ptr != NULL) *party_max = *(short*) ptr;
		sprintf_s(sz_party_id, len_party_id, "party_id_BLUR_STATE_ONLINE_LOBBY");
	} else if (rp_state == BLUR_STATE_PRIVATE_LOBBY) {
		uintptr_t ptr = follow_offsets(ADDY_BLUR_PARTY_MAX_PLAYERS, OFFSETS_BLUR_PARTY_MAX_PLAYERS_PRIVATE);
		if (ptr != NULL) *party_max = *(short*) ptr;
		//*party_max = *(short*) follow_offsets(ADDY_BLUR_PARTY_MAX_PLAYERS_PRIVATE, OFFSETS_BLUR_PARTY_MAX_PLAYERS_PRIVATE);
		sprintf_s(sz_party_id, len_party_id, "party_id_BLUR_STATE_PRIVATE_LOBBY");
	} else {
		// if there is no sz_party_id, does that mean the game wont print anything?
		// cause if that is the case, calculationg party_size is redundant
		sprintf_s(sz_party_id, len_party_id, "");
		return;
	}

	//works when user is actually in party. (even if solo party @ 1/8)
	uintptr_t ptr = follow_offsets(ADDY_BLUR_PARTY_N_PLAYERS, OFFSETS_BLUR_PARTY_N_PLAYERS);
	if (ptr != NULL) *party_size = *(char*) ptr;
	//*party_size = 0; //still need to test this one
}


void format_time(int rp_state, int64_t* start_time) {
	//TODO I dont think this is right but I don't know anything...
	//// //honestly, I have no idea why it fails if I use !=. tobii, pls fix!
	// im keeping this comment for happy purposes later :D
	//if (!((*rp_state == 27U) || (*rp_state == 28U) || (*rp_state == 19U) || (*rp_state == 29U)))
	static int prev_state = rp_state;
	if (rp_state != prev_state) { // we just changed states, maybe we have to start (or remove) the timer
		if ((rp_state == BLUR_STATE_ONLINE_LOBBY) || (rp_state == BLUR_STATE_PRIVATE_LOBBY)) {
			// we just entered this lobby or something, maybe we can display the amount of time that the user has been waiting in this lobby
			*start_time = time(0);
		} else if ((rp_state == BLUR_STATE_RACE) || (rp_state == BLUR_STATE_MOTOR_MASH)) {
			// we just entered this race or something, we can display the amount of time that the user has been racing
			*start_time = time(0);

		} else if (rp_state == BLUR_STATE_CAREER) {
			// we could come up with other things that we might want to display elapsed time for?
			*start_time = time(0);
		} else {
			*start_time = 0; // nothing, dont display
		}
		log("rp_state: " + std::to_string(prev_state) + " -> " + std::to_string(rp_state) + " @ " + std::to_string(*start_time));
	}
	prev_state = rp_state;
}


static DWORD WINAPI ThreadEntry(LPVOID lpParam) {
	unsigned int rp_state = NULL;
	char sz_playlist[LEN_STATE_BUFFER] = "";
	char sz_details[LEN_DETAILS_BUFFER] = "";
	char party_size = 0;
	char party_max = 0;
	char sz_small_img_key[LEN_IMG_KEY_BUFFER];
	char party_id[LEN_PARTY_ID_BUFFER];
	int64_t start_time = 0;

	Discord_Initialize(APP_ID, 0, 0, 0);

	DiscordRichPresence dp;
	memset(&dp, 0, sizeof(dp));

	// discord_presence.matchSecret = "4b2fdce12f639de8bfa7e3591b71a0d679d7c93f";
	// discord_presence.spectateSecret = "e7eb30d2ee025ed05c71ea495f770b76454ee4e0";

	// sprintf_s(partyId, sizeof(partyId), "12222222");
	// partyMax = 20;
	// partySize = 1;
	//racetime = time(0);
	
	log("[blur_rpc] LOADED");
	do {
		Sleep(UPD_INTVL);
		if ((rp_state = get_rp_state()) != -1) {
			format_details(rp_state, sz_details, sizeof(sz_details)); // What is the user doing? (Menu / Race / Career / ... )
			format_state(rp_state, sz_playlist, sizeof(sz_playlist), sz_small_img_key, sizeof(sz_small_img_key)); // What playlist is the user playing? (Skirmish / Team / ... )
			format_party(rp_state, &party_size, &party_max, party_id, sizeof(party_id)); // How many other players? ( <party> / 20 )
			format_time(rp_state, &start_time); // How long has the user been doing that?

			dp.state = sz_playlist;
			dp.details = sz_details;
			dp.smallImageKey = sz_small_img_key;
			dp.smallImageText = sz_details;
			dp.largeImageKey = "logo";
			dp.largeImageText = "Blur";
			dp.partyId = party_id;
			dp.partySize = party_size;
			dp.partyMax = party_max;
			dp.startTimestamp = start_time;

			Discord_UpdatePresence(&dp);
			Discord_RunCallbacks(); // might crash if it cant find them?
		} else {
			log("[blur_rpc] Not updating RP because rp_state = " + std::to_string(rp_state));
		}
	} while (true);
	//TODO set hooks that tell us to upadte, instead of running this in a loop
}

extern "C" __declspec(dllexport) BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			Discord_Shutdown(); //TODO why?
			DisableThreadLibraryCalls(hinstDLL);
			CreateThread(0, 0, ThreadEntry, 0, 0, 0);
			break;

		case DLL_PROCESS_DETACH:
			log("[blur_rpc] Shutting down!");
			Discord_Shutdown();
			break;
	}
	return TRUE;
}
