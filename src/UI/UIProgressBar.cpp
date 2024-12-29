#include <Supergoon/Content/ContentRegistry.hpp>
#include <Supergoon/Graphics/Graphics.hpp>
// #include <Supergoon/UI/UIImage.hpp>
#include <Supergoon/UI/UIAnimation.hpp>
#include <Supergoon/UI/UIProgressBar.hpp>
using namespace Supergoon;
using namespace std;
UIProgressBar::UIProgressBar(UIObject *parent, string id, string imageName) : UIObject(parent, id) {
  WidgetType = (int)BuiltinWidgetTypes::ProgressBar;
  auto path = std::string(SDL_GetBasePath()) + "assets/img/" + imageName + ".png";
  auto image = ContentRegistry::CreateContent<Image>(path);
  image->LoadContent();
  ProgressBarAnimation = new UIAnimation(this, imageName + "progressBar", imageName);
}

void UIProgressBar::Draw() {
  auto dest = RectangleF(ProgressBarAnimation->Offset.X + Bounds.X + BarOffset.X, ProgressBarAnimation->Offset.Y + Bounds.Y + BarOffset.Y, BarSize.X * BarPercent / 100, BarSize.Y);
  Graphics::Instance()->DrawFilledRect(dest, ProgressBarColor);
}
void UIProgressBar::OnDirty() {
  // ProgressBarImage->OverrideDrawSize = OverrideDrawSize;
}
