#pragma once
#include <Supergoon/Primitives/Rectangle.hpp>
#include <memory>
#include <string>
#include <functional>
namespace Supergoon {
class AsepriteDocument;
class AsepriteAnimation {
public:
  AsepriteAnimation(std::string n);
  std::string Filename();
  void Load();
  // Updates an anim, and returns if it is finished or not.
  void UpdateAnimation(double d);
  std::function<void(AsepriteAnimation* anim,  std::string)> OnAnimationEnd = nullptr;

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
