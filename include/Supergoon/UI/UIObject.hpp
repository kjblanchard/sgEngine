#pragma once
#include <Supergoon/Primitives/Rectangle.hpp>
#include <Supergoon/Primitives/Vector2.hpp>
#include <memory>
#include <string>
#include <vector>

namespace Supergoon {

class UIWidget;

enum class BuiltinWidgetTypes {
  Image = 1,
  Text,
  Panel,
  HorizontalLayoutGroup,
  VerticalLayoutGroup,
};

std::string GetWidgetTypeName(BuiltinWidgetTypes widget);

struct UIObjectAnimatorBase;

class UIObject {
public:
  UIObject();
  UIObject(UIObject *parent, std::string name = "", bool enabled = true, bool visible = true);
  virtual ~UIObject() = default;

  void SetDirty(bool parentSet = false);
  void AddChild(UIObject *child);
  void AddChild(std::shared_ptr<UIObject> child);
  void RemoveChild(const std::string &name);
  void SetVisible(bool visible);
  void SetAlpha(int alpha);
  unsigned int Layer();
  void SetLayer(unsigned int layer);
  Vector2* DrawOverrideHandle();
  float* DrawOverrideXHandle();
  int *AlphaHandle();
  int EffectiveAlpha();
  bool Visible();
  UIObject *GetChildByName(const std::string &name);
  virtual void OnDirty();

  void DirtyInternal();
  void UpdateInternal();
  void DrawInternal();
  void SetDrawOverride(Vector2 loc);

  std::string Name;
  // When one of the children of this object are dirty, should we dirty too?  This is for HLG, VLG mainly.
  bool ParentDirtyWithChildren = false;
  bool Enabled = true;
  UIObject *Parent = nullptr;
  RectangleF Bounds = {0, 0, 0, 0};
  std::vector<std::shared_ptr<UIObject>> Children;
  Vector2 Offset = {0, 0};
  Vector2 LayoutGroupOffset = {0, 0};
  int WidgetType = 0;
  std::vector<std::shared_ptr<UIObjectAnimatorBase>> Animators;

protected:
  bool Dirty = true;
  Vector2 _drawOverride;
  int _alpha = 255;
  bool _visible = true;
  int _layer = 0;
  std::vector<UIObject *> _drawOrder;

  virtual void Update();
  virtual void Draw();
  friend UIWidget;
};

} // namespace Supergoon
