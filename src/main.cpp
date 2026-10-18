#include <windows.h>

#include <cstdint>

#include <steam/steam_api.h>

#include "allocator.hpp"
#include "steam_achievements.hpp"

bool G_steam_init = false; // 0x00a8f860
ISteamRemoteStorage* G_steam_storage = NULL; // 0x00a8f86c
CSteamAchievements* G_steam_achievements = NULL; // 0x00a8f868

// 0x00402180
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    bool needs_restart = SteamAPI_RestartAppIfNecessary(115100);
    if ((!needs_restart) && (G_steam_init = SteamAPI_Init(), G_steam_init)) {
        G_steam_storage = SteamRemoteStorage();

        G_steam_achievements = new(ALLOCTAG_3) CSteamAchievements();

        int32_t total_bytes, available_bytes;

        G_steam_storage->GetFileCount();
        G_steam_storage->GetQuota(&total_bytes, &available_bytes);

        ISteamApps* steam_apps = SteamApps();
        if (steam_apps->BIsSubscribed()) {
            // TODO: SeedApp is not implemented yet
            // NOTE: SeedApp has an overwritten delete operator.
            // G_seed_app = new(ALLOCTAG_4) SeedApp();
            // if (G_seed_app) {
            //     G_seed_app->ParseCommandLine();
            //     FUN_00719310();
            //     delete G_seed_app;
            // }

            SteamAPI_Shutdown();

            if (G_steam_achievements != NULL) {
                delete G_steam_achievements;
            }
        }
    }

    return 0;
}
