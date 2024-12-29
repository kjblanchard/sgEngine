#pragma once
#include <Supergoon/Primitives/Rectangle.hpp>
#include <functional>
#include <memory>
#include <string>
namespace Supergoon {
class AsepriteDocument;
class AsepriteAnimation {
public:
  AsepriteAnimation(std::string n);
  std::string Filename();
  void Load();
  // TODO Updates an anim, and returns if it progressed a frame for the UI, but its not even used.. so it can prolly turn to void
  bool UpdateAnimation(double d);
  std::function<void(AsepriteAnimation *anim, std::string)> OnAnimationEnd = nullptr;

  void PlayAnimation(std::string a);
  RectangleF &FrameCoords();

private:
  void UpdateRect();
  std::string _filePath;
  int _animNum;
  int _frame;
  int _nextFrame;
  float _frameTime;
  bool _reverse = false; // pingpong
  int _repeats = -1;
  RectangleF _rect;
  std::shared_ptr<AsepriteDocument> _aseDocument;
};
} // namespace Supergoon
