#include <Supergoon/Content/ContentRegistry.hpp>
#include <Supergoon/Graphics/Graphics.hpp>
#include <Supergoon/UI/UIImage.hpp>
#include <Supergoon/UI/UIProgressBar.hpp>
using namespace Supergoon;
using namespace std;
UIProgressBar::UIProgressBar(UIObject *parent, string id, string imageName) : UIObject(parent, id) {
  WidgetType = (int)BuiltinWidgetTypes::ProgressBar;
  auto path = std::string(SDL_GetBasePath()) + "assets/img/" + imageName + ".png";
  auto image = ContentRegistry::CreateContent<Image>(path);
  image->LoadContent();
  ProgressBarImage = new UIImage(this, imageName + "progressBar");
  ProgressBarImage->ImagePtr = image;
}

void UIProgressBar::Draw() {
  auto dest = RectangleF(ProgressBarImage->Offset.X + Bounds.X + BarOffset.X, ProgressBarImage->Offset.Y + Bounds.Y + BarOffset.Y, BarSize.X * BarPercent / 100, BarSize.Y);
  //   auto dest = RectangleF(BarOffset.X, BarOffset.Y, BarSize.X * BarPercent / 100, BarSize.Y);
  Graphics::Instance()->DrawFilledRect(dest, ProgressBarColor);
}
void UIProgressBar::OnDirty() {
}
