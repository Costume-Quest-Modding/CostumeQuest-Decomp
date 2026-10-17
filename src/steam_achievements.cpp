#include "steam_achievements.hpp"

#include <tools/unimplemented.hpp>

// 0x00401b80
CSteamAchievements::CSteamAchievements()
    : callback_user_stats_received(this, &CSteamAchievements::OnUserStatsReceived),
      callback_user_stats_stored(this, &CSteamAchievements::OnUserStatsStored),
      callback_user_achievement_stored(this, &CSteamAchievements::OnUserAchievementStored)
{
    ISteamUtils* steam_utils = SteamUtils();
    this->app_id = steam_utils->GetAppID();
    this->unk2_0x4 = 0;
    this->unk3_0x8 = NULL; // TODO: &DAT_00a2aed0
    this->unk4_0xc = 0x15;

    ISteamUserStats* user_stats = SteamUserStats();
    ISteamUser* steam_user = SteamUser();
    if (user_stats != NULL && steam_user != NULL) {
        if (steam_user->BLoggedOn()) {
            user_stats->RequestCurrentStats();
        }
    }

}

// 0x00402310
CSteamAchievements::~CSteamAchievements() {

}

// TODO: Decompile
// 0x00401c60
void CSteamAchievements::OnUserStatsReceived(UserStatsReceived_t* stats) {
    UNIMPLEMENTED();
}

// TODO: Decompile
// 0x00401d90
void CSteamAchievements::OnUserStatsStored(UserStatsStored_t* stats) {
    UNIMPLEMENTED();
}

// TODO: Decompile
// 0x00401df0
void CSteamAchievements::OnUserAchievementStored(UserAchievementStored_t* achievment) {
    UNIMPLEMENTED();
}