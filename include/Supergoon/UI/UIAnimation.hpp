#pragma once
// #include <Supergoon/Primitives/Rectangle.hpp>
#include <Supergoon/Aseprite/AsepriteAnimation.hpp>
#include <Supergoon/Content/Image.hpp>
#include <Supergoon/Primitives/Point.h>
#include <Supergoon/Primitives/Vector2.h>
#include <Supergoon/UI/UIObject.hpp>
namespace Supergoon {
class UIImage;
class UIAnimation : public UIObject {
public:
  UIAnimation(UIObject *parent, std::string id, std::string imageName);
  virtual void Draw() override;
  virtual void OnDirty() override;
  virtual void Update() override;
  std::string AnimationName = "";
  sgVector2 OverrideDrawSize = {0, 0};
  bool Playing = false;
  std::shared_ptr<AsepriteAnimation> Animation;
  std::shared_ptr<Image> AnimationImage;
  std::function<void(AsepriteAnimation *anim, std::string)> OnAnimationEnd = nullptr;

private:
};
} // namespace Supergoon
