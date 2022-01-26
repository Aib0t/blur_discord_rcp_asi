#include <ctime>

extern "C" {
	#include "discord_rpc.h"
	#include "discord_register.h"
}
#include "blur_rpc.h"
#include "config.h"


//TODO rm me (DEBUG STUFF)
//#include <Windows.h> // OutputDebugString()
//#include <stdio.h>
#include <iostream>
#include <fstream>




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
	else log("follow_offsets(ADDY_BLUR_STATE, OFFSETS_BLUR_STATE) returned NULL");
	return rp_state;
}


void format_state(int rp_state, char* sz_state, const size_t len) {
	switch (rp_state) {
		case BLUR_STATE_MAIN:
			sprintf_s(sz_state, len, "Main menu");
			break;

		case BLUR_STATE_MENU_MAIN: // what?
			sprintf_s(sz_state, len, "Main menu");
			break;

		case BLUR_STATE_MENU_STICKERS:
			sprintf_s(sz_state, len, "Stickers");
			break;

		case BLUR_STATE_MENU_LEADERBOARDS:
			sprintf_s(sz_state, len, "Leaderboards");
			break;

		case BLUR_STATE_MENU_HELP:
			sprintf_s(sz_state, len, "Reading help");
			break;

		case BLUR_STATE_GARAGE:
			sprintf_s(sz_state, len, "Garage");
			break;

		// 6 ?

		case BLUR_STATE_SINGLEPLAYER:
			sprintf_s(sz_state, len, "Singleplayer");
			break;

		case BLUR_STATE_PHOTOS:
			sprintf_s(sz_state, len, "Photos");
			break;

		case BLUR_STATE_CHALLENGES_FRIENDS:
			sprintf_s(sz_state, len, "Friends challenges");
			break;

		case BLUR_STATE_CAREER:
			sprintf_s(sz_state, len, "Career");
			break;

		case BLUR_STATE_CAREER_MENU:
			sprintf_s(sz_state, len, "Career");
			break;

		case BLUR_STATE_MENU_MULTIPLAYER:
			sprintf_s(sz_state, len, "Multiplayer menu");
			break;

		case BLUR_STATE_SPLITSCREEN:
			sprintf_s(sz_state, len, "Splitscreen");
			break;

		case BLUR_STATE_MENU_HISTORY:
			sprintf_s(sz_state, len, "Race history");
			break;

		case BLUR_STATE_MENU_LAN:
			sprintf_s(sz_state, len, "Playing on LAN");
			break;

		case BLUR_STATE_MENU_ONLINE:
			sprintf_s(sz_state, len, "Online menu");
			break;

		case BLUR_STATE_MENU_MODS:
			sprintf_s(sz_state, len, "In mods menu");
			break;

		case BLUR_STATE_CHALLENGES_ONLINE:
			sprintf_s(sz_state, len, "Online challenges");
			break;

		case BLUR_STATE_ONLINE_LOBBY:
			sprintf_s(sz_state, len, "In online lobby");
			break;

		case BLUR_STATE_SINGLEPLAYER_ONE_ON_ONE:
			//sprintf_s(sz_details, len, "Singleplayer: One-on-One");
			sprintf_s(sz_state, len, "Singleplayer");
			break;
		case BLUR_STATE_SINGLEPLAYER_RACE:
			//sprintf_s(sz_details, len, "Singleplayer: Race");
			sprintf_s(sz_state, len, "Singleplayer");
			break;
		case BLUR_STATE_SINGLEPLAYER_DESTRUCTION:
			//sprintf_s(sz_details, len, "Singleplayer: Destruction");
			sprintf_s(sz_state, len, "Singleplayer");
			break;
		case BLUR_STATE_SINGLEPLAYER_CHECKPOINT:
			//sprintf_s(sz_details, len, "Singleplayer: Checkpoint");
			sprintf_s(sz_state, len, "Singleplayer");
			break;

		// 24..26 ?

		case BLUR_STATE_RACE:
			sprintf_s(sz_state, len, "Racing");
			break;

		case BLUR_STATE_MOTOR_MASH:
			sprintf_s(sz_state, len, "Motor Mash");
			break;

		case BLUR_STATE_PRIVATE_LOBBY:
			sprintf_s(sz_state, len, "Private lobby");
			break;

		default:
			sprintf_s(sz_state, len, "Unknown %d", rp_state);
			break;
	}
}


void format_playlist(int rp_state, char* sz_playlist, const size_t len_playlist, char* sz_small_img_key, const size_t len_small_img_key) {
	switch (rp_state) {
		case BLUR_STATE_MAIN: case BLUR_STATE_MENU_MAIN:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_power");
			break;
		case BLUR_STATE_MENU_STICKERS:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_stickers");
			break;
		case BLUR_STATE_MENU_LEADERBOARDS:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_leaderboards");
			break;
		case BLUR_STATE_MENU_HELP:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_help");
			break;
		case BLUR_STATE_GARAGE:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_garage");
			break;

		// 6 ?

		case BLUR_STATE_SINGLEPLAYER:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_singleplayer");
			break;

		case BLUR_STATE_PHOTOS:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_photos");
			break;

		case BLUR_STATE_CHALLENGES_FRIENDS:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_challenges_friends");
			break;

		case BLUR_STATE_CAREER: case BLUR_STATE_CAREER_MENU:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_career");
			break;

		case BLUR_STATE_MENU_MULTIPLAYER:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_multiplayer");
			break;

		case BLUR_STATE_SPLITSCREEN:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_splitscreen");
			break;

		case BLUR_STATE_MENU_HISTORY:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_history");
			break;

		case BLUR_STATE_MENU_LAN:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_lan");
			break;

		case BLUR_STATE_MENU_ONLINE:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_menu_online");
			break;

		case BLUR_STATE_MENU_MODS:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_mod_shop");
			break;

		case BLUR_STATE_CHALLENGES_ONLINE:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_challenges_online");
			break;

		case BLUR_STATE_ONLINE_LOBBY: case BLUR_STATE_PRIVATE_LOBBY: {
			unsigned int playlist_id = BLUR_PLAYLIST_NONE;
			uintptr_t ptr = follow_offsets(ADDY_BLUR_PLAYLIST, OFFSETS_BLUR_PLAYLIST); //TODO NOTE: (on my machine), this one is [always] correct (?)
			if (ptr != NULL) playlist_id = *(unsigned int*) ptr;
			else log("follow_offsets(ADDY_BLUR_PLAYLIST) returned NULL");
			switch (playlist_id) {
				case BLUR_PLAYLIST_COMMUNITY_EVENTS:
					sprintf_s(sz_playlist, len_playlist, "Community Events");
					sprintf_s(sz_small_img_key, len_small_img_key, "icon_playlist_community_events");
					break;

				case BLUR_PLAYLIST_TEAM_RACING:
					sprintf_s(sz_playlist, len_playlist, "Team Racing");
					sprintf_s(sz_small_img_key, len_small_img_key, "icon_playlist_team_racing");
					break;

				case BLUR_PLAYLIST_TEAM_MOTOR_MASH:
					sprintf_s(sz_playlist, len_playlist, "Team Motor Mash");
					sprintf_s(sz_small_img_key, len_small_img_key, "icon_playlist_team_motor_mash");
					break;

				case BLUR_PLAYLIST_MOTOR_MASH:
					sprintf_s(sz_playlist, len_playlist, "Motor mash");
					sprintf_s(sz_small_img_key, len_small_img_key, "icon_playlist_motor_mash");
					break;

				case BLUR_PLAYLIST_WORLD_TOUR:
					sprintf_s(sz_playlist, len_playlist, "World Tour");
					sprintf_s(sz_small_img_key, len_small_img_key, "icon_playlist_world_tour");
					break;

				case BLUR_PLAYLIST_HARDCORE:
					sprintf_s(sz_playlist, len_playlist, "Hardcore Racing");
					sprintf_s(sz_small_img_key, len_small_img_key, "icon_playlist_hardcore");
					break;

				case BLUR_PLAYLIST_POWERED_UP_RACING:
					sprintf_s(sz_playlist, len_playlist, "Powered-up racing");
					sprintf_s(sz_small_img_key, len_small_img_key, "icon_playlist_powered_up_racing");
					break;

				case BLUR_PLAYLIST_SKIRMISH_RACING:
					sprintf_s(sz_playlist, len_playlist, "Skirmish racing");
					sprintf_s(sz_small_img_key, len_small_img_key, "icon_playlist_skirmish_racing");
					break;

				case BLUR_PLAYLIST_DRIVING_SCHOOL:
					sprintf_s(sz_playlist, len_playlist, "Driving school");
					sprintf_s(sz_small_img_key, len_small_img_key, "icon_playlist_driving_school");
					break;

				case BLUR_PLAYLIST_CUSTOM_GAME:
					sprintf_s(sz_playlist, len_playlist, "Custom game");
					sprintf_s(sz_small_img_key, len_small_img_key, "icon_playlist_custom_game");
					break;

				case BLUR_PLAYLIST_NONE: // prob means we didnt read a playlist_id
					sprintf_s(sz_playlist, len_playlist, "");
					sprintf_s(sz_small_img_key, len_small_img_key, "");
					break;

				default:
					sprintf_s(sz_playlist, len_playlist, "Unknown playlist: %d", playlist_id);
					sprintf_s(sz_small_img_key, len_small_img_key, "icon_question_mark");
					break;
			}
			break;
		}

		case BLUR_STATE_SINGLEPLAYER_ONE_ON_ONE:
			sprintf_s(sz_playlist, len_playlist, "One-on-One");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_event_one_on_one");
			break;
		case BLUR_STATE_SINGLEPLAYER_RACE:
			sprintf_s(sz_playlist, len_playlist, "Racing");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_event_race");
			break;
		case BLUR_STATE_SINGLEPLAYER_DESTRUCTION:
			sprintf_s(sz_playlist, len_playlist, "Destruction");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_event_destruction");
			break;
		case BLUR_STATE_SINGLEPLAYER_CHECKPOINT:
			sprintf_s(sz_playlist, len_playlist, "Checkpoint");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_event_checkpoint");
			break;


		case BLUR_STATE_RACE:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_race");
			break;

		case BLUR_STATE_MOTOR_MASH:
			sprintf_s(sz_playlist, len_playlist, "");
			sprintf_s(sz_small_img_key, len_small_img_key, "icon_motor_mash");
			break;

		default: // there is nothing that this rp_state should express do
			sprintf_s(sz_playlist, len_playlist, "");
			//sprintf_s(sz_small_img_key, len_small_img_key, "icon_question_mark");
			break;
	}
}

void format_party(int rp_state, char* party_size, char* party_max, char* sz_party_id, const size_t len_party_id) {
	// sprintf_s(partyId, length, "12222222");
	//FIXME changed offsets, revise on other clients
	// TODO revise!
	*party_size = 0;
	*party_max = 0;
	// find lan values maybe?
	if (rp_state == BLUR_STATE_ONLINE_LOBBY) {
		uintptr_t ptr = follow_offsets(ADDY_BLUR_PARTY_MAX_PLAYERS, OFFSETS_BLUR_PARTY_MAX_PLAYERS_ONLINE);
		if (ptr != NULL) *party_max = *(short*) ptr;
		else log("follow_offsets(ADDY_BLUR_PARTY_MAX_PLAYERS, OFFSETS_BLUR_PARTY_MAX_PLAYERS_ONLINE) returned NULL");
		sprintf_s(sz_party_id, len_party_id, "party_id_BLUR_STATE_ONLINE_LOBBY");
	} else if (rp_state == BLUR_STATE_PRIVATE_LOBBY) {
		uintptr_t ptr = follow_offsets(ADDY_BLUR_PARTY_MAX_PLAYERS, OFFSETS_BLUR_PARTY_MAX_PLAYERS_PRIVATE);
		if (ptr != NULL) *party_max = *(short*) ptr;
		else log("follow_offsets(ADDY_BLUR_PARTY_MAX_PLAYERS, OFFSETS_BLUR_PARTY_MAX_PLAYERS_PRIVATE) returned NULL");
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
	else log("follow_offsets(ADDY_BLUR_PARTY_N_PLAYERS, OFFSETS_BLUR_PARTY_N_PLAYERS) returned NULL");
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

		} else if ((rp_state == BLUR_STATE_SINGLEPLAYER_ONE_ON_ONE)
				|| (rp_state == BLUR_STATE_SINGLEPLAYER_RACE)
				|| (rp_state == BLUR_STATE_SINGLEPLAYER_DESTRUCTION)
				|| (rp_state == BLUR_STATE_SINGLEPLAYER_CHECKPOINT)) {
			// we just entered this singleplayer ace or something, we can display the amount of time that the user has been racing
			*start_time = time(0);
		} else if (rp_state == BLUR_STATE_SPLITSCREEN) { // meh
			*start_time = 0; // nothing, dont display, cause this would display total time spent in splitscreen, just the current not race time -_-
			//TODO FIXME
			//*start_time = time(0);
		} else {
			// we could come up with other things that we might want to display elapsed time for?
			*start_time = 0; // nothing, dont display
		}
		log("prev_state != rp_state: " + std::to_string(prev_state) + " -> " + std::to_string(rp_state) + " @ " + std::to_string(*start_time));
	}
	prev_state = rp_state;
}


static DWORD WINAPI ThreadEntry(LPVOID lpParam) {
	unsigned int rp_state = NULL;
	char sz_playlist[LEN_STATE_BUFFER] = "";
	char sz_state[LEN_DETAILS_BUFFER] = "";
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
			format_state(rp_state, sz_state, sizeof(sz_state)); // What is the user doing? (Menu / Race / Career / ... )
			format_playlist(rp_state, sz_playlist, sizeof(sz_playlist), sz_small_img_key, sizeof(sz_small_img_key)); // What playlist is the user playing? (Skirmish / Team / ... ) // (Destruction / Checkpoint / ... )
			format_party(rp_state, &party_size, &party_max, party_id, sizeof(party_id)); // How many other players? ( <party> / 20 )
			format_time(rp_state, &start_time); // How long has the user been doing that?

			dp.details = sz_state;

			dp.state = sz_playlist;

			dp.smallImageKey = sz_small_img_key;
			dp.smallImageText = sz_state; //TODO (maybe display better info about the playlist here)

			dp.largeImageKey = "logo";
			dp.largeImageText = "Blur"; //TODO (maybe display user:name here?)

			dp.partyId = party_id; // TODO: suppport actual party stuff,
			dp.partySize = party_size; //or, if user is not in a party, display lobby player numbers
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
