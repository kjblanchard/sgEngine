#pragma once
#include <SupergoonEngine/Stream.h>

#include <Supergoon/Content/Sfx.hpp>
#include <memory>
#include <queue>
#include <string>
typedef struct sgBgm sgBgm;
typedef struct sgSfx sgSfx;
namespace Supergoon {
class Tween;
class Sound {
public:
  // inline Sound() { _instance = this; }
  Sound();
  ~Sound();
  //  Initializes the Supergoon Sound
  void InitializeSound();
  /**
   * @brief Loads a bgm into the main BGM slot of sound
   * @param filename name of the file to load, assumes .ogg
   * @param volume 0 - 1.0
   * @param loops -1 is infinite, else number of loops
   * @return true loaded successfully
   * @return false error
   */
  bool LoadBgm(std::string filename, float volume = 1.0, int loops = -1, int slot = 0);
  // TODO this needs to be cleaned up
  // Plays a bgm loaded into the bgm slot
  void PlayBgm(int slot = 0);
  // Pauses bgm in bgm slot
  void PauseBgm(int slot = 0);
  // Pauses bgm in bgm slot
  void StopBgm(int slot = 0);
  void StopBgmFadeout(int slot = 0, float fadeTime = 1.0);
  //  Sets current playing bgm volume, 0 - 1.0f
  void SetPlayingBgmVolume(float volume, int slot = 0);
  //  Sets the global volume multiplier for bgm, 0 - 1.0f
  void SetGlobalBgmVolume(float volume);
  inline void SetGlobalSfxVolume(float volume) { _globalSfxVolume = volume; };
  void PlaySfx(Sfx *sfx, float volume = 1.0);
  void PlaySfxOneShot(const char *name, float volume = 1.0);
  static inline Sound *Instance() { return _instance; }
  //  Updates all internal bgms
  // making public for now to test threading.
  void Update();

private:
  void CheckForStaleSfxStreams();
  void UpdatePlayingBgmVolume(int slot = 0);
  const size_t _totalSfxStreams = 4;
  float _globalBgmVolume = 1.0f;
  float _globalSfxVolume = 1.0f;
  std::vector<std::unique_ptr<sgStream>> _sfxStreams;
  std::vector<sgStream *> _playingStreams;
  std::queue<sgStream *> _usableSfxStreams;
  bool _fadingOut = false;
  // sgBgm* _bgm = nullptr;
  // sgBgm* _bgmSecondary = nullptr;
  const int _bgmSlots = 2;
  std::vector<sgBgm *> _bgms;
  std::vector<float> _playingBgmVolume;
  std::vector<float> _bgmOriginalVolume;
  std::vector<Tween *> _tweens;
  // Tween* _bgmTween = nullptr;
  static Sound *_instance;
  friend class Game;
  friend class SoundWidget;
};
} // namespace Supergoon
