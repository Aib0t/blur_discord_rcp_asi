#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <discord_rpc.h>
#include <vector>
#include <inttypes.h>
#include <stdint.h>
#include <iostream>
#include <ctime>

#include <config.h>

using namespace std;

#define C_RP_STATUS_PTR 0x00D5F39C

uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{

  uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);
  uintptr_t addr = moduleBase + ptr;
  for (unsigned int i = 0; i < offsets.size(); ++i)
  {

    addr = *(uintptr_t *)addr;

    addr += offsets[i];
  }

  return addr;
}

// static void format_state (char* state, char length) {
//   if (*C_CAR_PTR < 0) {
//     state[0] = 0;
//     return;
//   }

//   const int car_addr = (*CARS_ADDR_PTR + (*C_CAR_PTR * 0x890));
//   const char* const car_name = (char*)(car_addr + 0x20);

//   const auto car_itr = CAR_TABLE.find(car_name);
//   if (car_itr != CAR_TABLE.end()) {
//     sprintf_s(state, length, "%s", car_itr->second);
//   } else {
//     const char* const car_brand = (char*)(car_addr + 0xC0);
//     sprintf_s(state, length, "%s %s", car_brand, car_name);
//   }
// }

static void format_details(unsigned int *rp_state, char *details, char length)
{

  uintptr_t ptr2 = 0x00CE6B60;
  uintptr_t ammoAddr2 = FindDMAAddy(ptr2, {4});
  unsigned int test = *(uintptr_t *)ammoAddr2;
  *rp_state = test;
  switch (test)
  {
  case 0:
    sprintf_s(details, length, "Main menu");
    break;
  case 1:
    sprintf_s(details, length, "Main menu");
    break;
  case 2:
    sprintf_s(details, length, "Stickers");
    break;
  case 3:
    sprintf_s(details, length, "Leaderboards");
    break;
  case 4:
    sprintf_s(details, length, "Reading help");
    break;
  case 5:
    sprintf_s(details, length, "Garage");
    break;
  case 7:
    sprintf_s(details, length, "Singleplayer");
    break;
  case 8:
    sprintf_s(details, length, "Photos (singleplayer)");
    break;
  case 9:
    sprintf_s(details, length, "Friends challenges");
    break;
  case 10:
    sprintf_s(details, length, "Career");
    break;
  case 12:
    sprintf_s(details, length, "Multiplayer menu");
    break;
  case 14:
    sprintf_s(details, length, "Race history");
    break;
  case 15:
    sprintf_s(details, length, "In LAN menu");
    break;
  case 16:
    sprintf_s(details, length, "Online menu");
    break;
  case 17:
    sprintf_s(details, length, "In mods menu");
    break;
  case 18:
    sprintf_s(details, length, "Online challenges");
    break;
  case 19:
    sprintf_s(details, length, "In online lobby");
    break;
  case 27:
    sprintf_s(details, length, "In race");
    break;
  case 28:
    sprintf_s(details, length, "In Motor Mash");
    break;
  case 29:
    sprintf_s(details, length, "In private lobby");
    break;
  default:
    sprintf_s(details, length, "Unknown %d", test);
  }
}

static void format_state_2(unsigned int* game_type,char* state, char length,char* smallLogo, char smallLogoLength) //when 1 is not enough
{
      switch (*game_type)
    {
    case 24392580:
      sprintf_s(state, length, "Community Events");
      sprintf_s(smallLogo, smallLogoLength, "community_events");
      break;
    case 2288498497:
      sprintf_s(state, length, "Team Racing");
      sprintf_s(smallLogo, smallLogoLength, "team_racing");
      break;
    case 2366728894:
      sprintf_s(state, length, "Team Motor Mash");
      sprintf_s(smallLogo, smallLogoLength, "team_motor_mash");
      break;
    case 3468808035:
      sprintf_s(state, length, "Motor mash");
      sprintf_s(smallLogo, smallLogoLength, "motor_mash");
      break;
    case 1527855959:
      sprintf_s(state, length, "World Tour");
      sprintf_s(smallLogo, smallLogoLength, "world_tour");
      break;
    case 3131866246:
      sprintf_s(state, length, "Hardcore Racing");
      sprintf_s(smallLogo, smallLogoLength, "hardcore");
      break;
    case 1647796835:
      sprintf_s(state, length, "Powered-up racing");
      sprintf_s(smallLogo, smallLogoLength, "powered_up_racing");
      break;
    case 1786934394:
      sprintf_s(state, length, "Skirmish racing");
      sprintf_s(smallLogo, smallLogoLength, "skirmish_racing");
      break;
    case 0:
      sprintf_s(state, length, "Custom game");
      sprintf_s(smallLogo, smallLogoLength, "custom_game");
      break;
    default:
      sprintf_s(state, length, "Unknown game type - %d", *game_type);
    }
}

static void format_state(unsigned int* rp_state, char* state, char length,char* smallLogo, char smallLogoLength)
{

  if (*rp_state == 19)
  {

    uintptr_t ptr2 = 0xD022F0;
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);
    uintptr_t addr = moduleBase + ptr2;
    unsigned int test = *(uintptr_t *)addr;

    format_state_2(&test, state ,length,smallLogo,smallLogoLength);
  }
  else if (*rp_state == 29)
  {
    uintptr_t ptr2 = 0xE35C54;
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);
    uintptr_t addr = moduleBase + ptr2;
    unsigned int test = *(uintptr_t *)addr;

   format_state_2(&test, state ,length,smallLogo,smallLogoLength);

  }
  else
  {
    sprintf_s(state, length, "");
    sprintf_s(smallLogo, smallLogoLength, "");
  }
}

static void format_party(unsigned int* rp_state, unsigned int* partySize, unsigned int* partyMax, char* partyId, char length)
{

  // sprintf_s(partyId, length, "12222222");
  // *partyMax = 20;
  // *partySize = 1;

  if (*rp_state == 19)
  {

    uintptr_t max_players_online_base_ptr = 0x00DEB9C8;
    uintptr_t max_players_online_ptr = FindDMAAddy(max_players_online_base_ptr, {188});

    uintptr_t current_players_online_base_ptr = 0x00DB4530;
    uintptr_t current_players_online_ptr = FindDMAAddy(current_players_online_base_ptr, {20});

    unsigned int max_players = *(uintptr_t *)max_players_online_ptr;
    unsigned int current_players = *(uintptr_t *)current_players_online_ptr;
    sprintf_s(partyId, length, "1111111111111111111111111111111111111112");
    *partyMax = 0;
    *partySize = 0; //still need to test this one
  }
  else if (*rp_state == 29)
  {

    uintptr_t max_players_private_base_ptr = 0x00DB4548;
    uintptr_t max_players_private_ptr = FindDMAAddy(max_players_private_base_ptr, {18});

    uintptr_t current_players_online_base_ptr = 0x00DB4530;
    uintptr_t current_players_online_ptr = FindDMAAddy(current_players_online_base_ptr, {20});

    unsigned int max_players = *(uintptr_t *)max_players_private_ptr;
    unsigned int current_players = *(uintptr_t *)current_players_online_ptr;
    sprintf_s(partyId, length, "1111111111111111111111111111111111111112");

    *partyMax = 0;
    *partySize = 0;
  }
  else
  {
    sprintf_s(partyId, length, "");
    *partyMax = 0;
    *partySize = 0;
  }
}

static void format_time(unsigned int* rp_state, uint64_t* racetime, bool* timeDisplayed)
{

  if (*timeDisplayed == false)
  {
    if (*rp_state == 27 || *rp_state == 28)
    {
      *racetime = time(0);
      *timeDisplayed = true;
    }
    else if (*rp_state == 19 || *rp_state == 29)
    {
      *racetime = time(0);
      *timeDisplayed = true;
    } else {
      *racetime = 0;
    }
  }
  else
  {

    // wchar_t buffer[255];
    // wsprintfW(buffer, L"%d", *rp_state);

    // MessageBoxW(nullptr, buffer, buffer, MB_ICONWARNING);

    if (*rp_state == 27U || *rp_state == 28U || *rp_state == 19U || *rp_state == 29U)
    {
      //honestly, I have no idea why it fails if I use !=. tobii, pls fix!
    } else {
      *racetime = 0;
      *timeDisplayed = false;
    }
  }
}

static DWORD WINAPI ThreadEntry(LPVOID lpParam)
{

  char state[64];
  char details[64];
  unsigned int rp_state;
  unsigned int partySize;
  unsigned int partyMax;
  char smallLogo[64];
  char partyId[64];
  uint64_t racetime;
  bool timeDisplayed = false;

  Discord_Initialize(APP_ID, 0, 0, 0);

  DiscordRichPresence discord_presence;
  memset(&discord_presence, 0, sizeof(discord_presence));




  // discord_presence.matchSecret = "4b2fdce12f639de8bfa7e3591b71a0d679d7c93f";
  // discord_presence.spectateSecret = "e7eb30d2ee025ed05c71ea495f770b76454ee4e0";

  // sprintf_s(partyId, sizeof(partyId), "12222222");
  // partyMax = 20;
  // partySize = 1;
  //racetime = time(0);

  Sleep(1000);
  while (1)
  {
    format_details(&rp_state, details, sizeof(details));
    format_state(&rp_state,state, sizeof(state), smallLogo , sizeof(smallLogo));
    format_party(&rp_state, &partySize, &partyMax, partyId, sizeof(partyId));
    format_time(&rp_state, &racetime, &timeDisplayed);

    discord_presence.state = state;
    discord_presence.details = details;
    discord_presence.smallImageKey = smallLogo;
    discord_presence.smallImageText = details;
    discord_presence.largeImageKey = "logo";
    discord_presence.largeImageText = "Blur";
    discord_presence.partyId = partyId;
    discord_presence.partySize = partySize;
    discord_presence.partyMax = partyMax;
    discord_presence.startTimestamp = racetime;

    Discord_UpdatePresence(&discord_presence);
    Discord_RunCallbacks();
    Sleep(UPD_INTVL);
  }
}

extern "C" __declspec(dllexport)
    BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
  switch (fdwReason)
  {
  case DLL_PROCESS_ATTACH:
    Discord_Shutdown();
    DisableThreadLibraryCalls(hinstDLL);
    CreateThread(0, 0, ThreadEntry, 0, 0, 0);
    break;
  case DLL_PROCESS_DETACH:
    Discord_Shutdown();
    break;
  }

  return 1;
}
