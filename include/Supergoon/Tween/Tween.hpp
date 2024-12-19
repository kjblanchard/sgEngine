#pragma once
#include <functional>
#include <variant>
namespace Supergoon {
enum class Easings {
  Linear,
  QuadEaseIn,
  QuadEaseOut,
  QuadEaseInOut,
  CubicEaseIn,
  CubicEaseOut,
  CubicEaseInOut,
  QuarticEaseIn,
  QuarticEaseOut,
  QuarticEaseInOut,
  QuinticEaseIn,
  QuinticEaseOut,
  QuinticEaseInOut,
  SineEaseIn,
  SineEaseOut,
  SineEaseInOut,
  CircularEaseIn,
  CircularEaseOut,
  CircularEaseInOut,
  ExponentialEaseIn,
  ExponentialEaseOut,
  ExponentialEaseInOut,
  ElasticEaseIn,
  ElasticEaseOut,
  ElasticEaseInOut,
  BackEaseIn,
  BackEaseOut,
  BackEaseInOut,
  BounceEaseIn,
  BounceEaseOut,
  BounceEaseInOut,
};

class Tween {
public:
  // Start value, end value,
  Tween(float start, float end, float duration, float *value, Easings ease, int loops = 0);
  Tween(float start, float end, float duration, int *value, Easings ease, int loops = 0);
  Tween(float waitTime);
  // Returns if this tween is complete or not, and also updates properly.
  bool Update();
  inline float CurrentLength() { return _currentDuration; }
  inline float TotalLength() { return _duration; }
  inline void Start() { _started = true; }
  inline void Restart() {
    _currentDuration = 0;
    _started = true;
  }
  inline bool Complete() { return _currentDuration >= _duration; }
  inline float Percent() { return _currentDuration / _duration; }
  inline void SetAutostart(bool autostart) {
    _autostart = autostart;
    Restart();
  }
  std::function<void()> StartFunc = nullptr;
  std::function<void()> UpdateFunc = nullptr;
  std::function<void()> EndFunc = nullptr;

private:
  void UpdateInternal();
  std::variant<std::monostate, float *, int *> value;
  float _begin = 0, _end = 0, _currentDuration = 0, _duration = 0;
  bool _started = false;
  bool _autostart = true;
  Easings _easeType;
  int _loops = 0;
};

} // namespace Supergoon
