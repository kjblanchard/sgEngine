#pragma once
// #include <Supergoon/Primitives/Rectangle.hpp>
#include <Supergoon/Primitives/Vector2.h>
#include <Supergoon/UI/UIObject.hpp>
namespace Supergoon {
class Panel;
// class UIImage;
class UIAnimation;
class UIProgressBar : public UIObject {
public:
  UIProgressBar(UIObject *parent, std::string id, std::string imageName);
  // UIImage *ProgressBarImage = nullptr;
  UIAnimation *ProgressBarAnimation = nullptr;
  inline void SetBarPercent(unsigned int percent) {
    BarPercent = percent;
    SetDirty(true);
  }
  sgColor ProgressBarColor = {255, 255, 255, 255};
  sgVector2 BarOffset = {0, 0};
  sgVector2 BarSize = {0, 0};
  int BarPercent = 0;
  virtual void Draw() override;
  virtual void OnDirty() override;

private:
};
} // namespace Supergoon
