#pragma once
#include <Supergoon/Primitives/Vector2.hpp>
#include <string>
namespace Supergoon {
struct GameState {
	struct Battle {
		int BattleID;
		int CurrentBattler;
		bool BattleVictory = false;
	};
	Battle BattleData;
	float DeltaTime = 0;
	int PlayerSpawnLocation;
	int WindowHeight;
	int WindowWidth;
	bool Loading;
	bool CameraFollowTarget;
	bool EnteringBattle;
	bool ExitingBattle;
	bool Interacting;
	bool InBattle;
	std::string PlayerLoadLevel = "";
	Vector2 PlayerLoadLocation = Vector2();
	int PlayerLoadDirection;
};
}  // namespace Supergoon
