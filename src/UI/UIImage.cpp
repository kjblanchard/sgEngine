#include <Supergoon/Content/ContentRegistry.hpp>
#include <Supergoon/UI/UIImage.hpp>
#include <Supergoon/pch.hpp>
using namespace Supergoon;
using json = nlohmann::json;

void UIImage::OnDirty() {
  ImagePtr->SetAlpha(EffectiveAlpha());
}
UIImage::UIImage(UIObject *parent, std::string id) : UIObject(parent, id) {
  WidgetType = (int)BuiltinWidgetTypes::Image;
}

UIImage::UIImage(UIObject *parent, json &imageJson) : UIObject(parent, imageJson["name"].get<std::string>()) {
  WidgetType = (int)BuiltinWidgetTypes::Image;
  _visible = imageJson["visible"].get<bool>();
  _alpha = imageJson["alpha"].get<float>();
  auto name = imageJson["name"].get<std::string>();
  auto sourceData = imageJson["source"];
  auto destinationData = imageJson["destination"];
  auto imageName = sourceData["name"].get<std::string>();
  Name = name;
  auto fullPath = std::string(SDL_GetBasePath()) + "assets/img/" + imageName + ".png";
  ImagePtr = ContentRegistry::CreateContent<Image>(fullPath);
  Offset.X = destinationData["x"].get<float>();
  Offset.Y = destinationData["y"].get<float>();
  auto x = sourceData["x"].get<float>();
  auto y = sourceData["y"].get<float>();
  auto w = sourceData["width"].get<float>();
  auto h = sourceData["height"].get<float>();
  // Set the source rect, if it is all 0 use the full image, but it must be loaded to get size
  if (w == 0 && h == 0) {
    ImagePtr->Load();
    w = ImagePtr->Width();
    h = ImagePtr->Height();
  }
  ImageSourceRect = RectangleF{x, y, w, h};
  Bounds.W = destinationData["width"].get<float>();
  Bounds.H = destinationData["height"].get<float>();
};

void UIImage::Draw() {
  ImagePtr->Draw(ImageSourceRect, Bounds);
}
