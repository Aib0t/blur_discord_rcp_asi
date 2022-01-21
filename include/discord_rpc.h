#pragma once
#include <stdint.h>

typedef struct DiscordRichPresence {
	const char* state;   /* max 128 bytes */
	const char* details; /* max 128 bytes */
	int64_t startTimestamp;
	int64_t endTimestamp;
	const char* largeImageKey;  /* max 32 bytes */
	const char* largeImageText; /* max 128 bytes */
	const char* smallImageKey;  /* max 32 bytes */
	const char* smallImageText; /* max 128 bytes */
	const char* partyId;        /* max 128 bytes */
	int partySize;
	int partyMax;
	const char* matchSecret;    /* max 128 bytes */
	const char* joinSecret;     /* max 128 bytes */
	const char* spectateSecret; /* max 128 bytes */
	int8_t instance;
} DiscordRichPresence;

typedef struct DiscordUser {
	const char* userId;
	const char* username;
	const char* discriminator;
	const char* avatar;
} DiscordUser;

typedef struct DiscordEventHandlers {
	void (*ready)(const DiscordUser* request);
	void (*disconnected)(int errorCode, const char* message);
	void (*errored)(int errorCode, const char* message);
	void (*joinGame)(const char* joinSecret);
	void (*spectateGame)(const char* spectateSecret);
	void (*joinRequest)(const DiscordUser* request);
} DiscordEventHandlers;

#define DISCORD_REPLY_NO 0
#define DISCORD_REPLY_YES 1
#define DISCORD_REPLY_IGNORE 2

__declspec(dllimport) void Discord_Initialize(const char* applicationId, DiscordEventHandlers* handlers, int autoRegister, const char* optionalSteamId);
__declspec(dllimport) void Discord_Shutdown(void);
__declspec(dllimport) void Discord_RunCallbacks(void);
__declspec(dllimport) void Discord_UpdateConnection(void);
__declspec(dllimport) void Discord_UpdatePresence(const DiscordRichPresence* presence);
__declspec(dllimport) void Discord_ClearPresence(void);
__declspec(dllimport) void Discord_Respond(const char* userid, /* DISCORD_REPLY_ */ int reply);
__declspec(dllimport) void Discord_UpdateHandlers(DiscordEventHandlers* handlers);

