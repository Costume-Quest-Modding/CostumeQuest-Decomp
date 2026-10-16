#ifndef HPP_CQ_STEAM_ACHIEVEMENTS
#define HPP_CQ_STEAM_ACHIEVEMENTS

#include <cstdint>

#include <steam/steam_api.h>

class CSteamAchievements {
public:
    uint32_t app_id = 0;
    uint32_t unk2_0x4 = 0;
    void* unk3_0x8;
    int unk4_0xc;
    bool unk5_0x10 = false;
    CCallback<CSteamAchievements, UserStatsReceived_t, false> callback_user_stats_received;
    CCallback<CSteamAchievements, UserStatsStored_t, false> callback_user_stats_stored;
    CCallback<CSteamAchievements, UserAchievementStored_t, false> callback_user_achievement_stored;

    CSteamAchievements();
    ~CSteamAchievements();

    void OnUserStatsReceived(UserStatsReceived_t* stats);
    void OnUserStatsStored(UserStatsStored_t* stats);
    void OnUserAchievementStored(UserAchievementStored_t* achievment);
};

#endif