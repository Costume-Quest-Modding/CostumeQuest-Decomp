#include <windows.h>

#include <cstdint>
#include <new>

#include <steam/steam_api.h>

#include "allocator.hpp"
#include "steam_achievements.hpp"

bool G_steam_init = false;
ISteamRemoteStorage* G_steam_storage = NULL;
CSteamAchievements* G_steam_achievements = NULL;

// 0x00402180
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    bool needs_restart = SteamAPI_RestartAppIfNecessary(115100);
    if ((!needs_restart) && (G_steam_init = SteamAPI_Init(), G_steam_init)) {
        G_steam_storage = SteamRemoteStorage();

        // TODO:
        // FUN_00711c20();

        void* steam_achievements_mem = tracked_malloc(sizeof(CSteamAchievements), 0x10, ALLOCTAG_3);
        if (steam_achievements_mem == NULL) {
            // TODO:
            // if (DAT_00a8ff38 != (code *)0x0) {
            //     (*DAT_00a8ff38)();
            // }
            G_steam_achievements = NULL;
        }
        else {
            G_steam_achievements = new (steam_achievements_mem) CSteamAchievements();
        }

        int32_t total_bytes, available_bytes;

        G_steam_storage->GetFileCount();
        G_steam_storage->GetQuota(&total_bytes, &available_bytes);

        ISteamApps* steam_apps = SteamApps();
        if (steam_apps->BIsSubscribed()) {
            // TODO:
            // G_seed_app = new (ALLOCTAG_4) SeedApp();
            // if (G_seed_app) {
            //     G_seed_app->ParseCommandLine();

            //     FUN_00719310(G_seed_app);

            // }

            SteamAPI_Shutdown();

            if (G_steam_achievements != NULL) {
                G_steam_achievements->~CSteamAchievements();
                // TODO:
                // FUN_00711c20();
                tracked_free(G_steam_achievements);
            }
        }
    }

    return 0;
}
