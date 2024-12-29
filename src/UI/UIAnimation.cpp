#include <Supergoon/Content/ContentRegistry.hpp>
#include <Supergoon/Game.hpp>
#include <Supergoon/UI/UIAnimation.hpp>
#include <memory>
using namespace Supergoon;
using namespace std;

UIAnimation::UIAnimation(UIObject *parent, std::string id, std::string imageName) : UIObject(parent, id) {

  AnimationName = imageName;
  Animation = make_shared<AsepriteAnimation>(imageName);
  auto path = std::string(SDL_GetBasePath()) + "assets/img/" + imageName + ".png";
  AnimationImage = ContentRegistry::CreateContent<Image>(path);
  AnimationImage->LoadContent();
}

void UIAnimation::OnDirty() {
}

void UIAnimation ::Update() {
  if (!Playing) {
    return;
  }
  auto msTime = Game::DeltaTimeMS();
  Animation->UpdateAnimation(msTime);
}

void UIAnimation::Draw() {
  if (!Animation) {
    sgLogError("Animation not loaded for %s", AnimationName.c_str());
    return;
  }

  auto srcRect = Animation->FrameCoords();
  auto dWidth = OverrideDrawSize.X ? OverrideDrawSize.X : srcRect.W;
  auto dHeight = OverrideDrawSize.Y ? OverrideDrawSize.Y : srcRect.H;
  auto d = RectangleF{Bounds.X,
                      Bounds.Y,
                      (float)dWidth,
                      (float)dHeight};
  AnimationImage->Draw(srcRect, d);
}
