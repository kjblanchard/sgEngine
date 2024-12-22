#pragma once
#include <Supergoon/Primitives/Vector2.h>
#include <string>
namespace Supergoon {
struct GameState {
  // struct Battle {
  //   int BattleID;
  //   int CurrentBattler;
  //   bool BattleVictory = false;
  // };
  // Battle BattleData;
  float DeltaTime = 0;
  int PlayerSpawnLocation;
  int WindowHeight;
  int WindowWidth;
  bool Loading;
  bool CameraFollowTarget;
  // bool EnteringBattle;
  bool Interacting;
  // bool InBattle;
  std::string PlayerLoadLevel = "";
  sgVector2 PlayerLoadLocation = {0, 0};
  int PlayerLoadDirection;
};
} // namespace Supergoon
