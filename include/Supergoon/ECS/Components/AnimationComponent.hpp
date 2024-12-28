#pragma once

#include <Supergoon/Aseprite/AsepriteAnimation.hpp>
#include <Supergoon/Content/Image.hpp>
#include <Supergoon/Primitives/Point.h>
namespace Supergoon {
struct AnimationComponent {
  std::string AnimationName;
  float AnimationSpeed;
  sgPoint Offset = {0, 0};
  sgPoint OverrideDrawSize = {0, 0};
  bool Playing;
  bool Visible = true;
  // Currently only supports 2 layers, 0 and 1.
  unsigned int Layer = 0;
  std::shared_ptr<AsepriteAnimation> Animation;
  std::shared_ptr<Image> AnimationImage;
  std::function<void(AsepriteAnimation *anim, std::string)> OnAnimationEnd = nullptr;
};
} // namespace Supergoon
