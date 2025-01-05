#pragma once
#include <Supergoon/Primitives/Rectangle.hpp>
#include <Supergoon/Primitives/Vector2.h>
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
  ProgressBar,
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
  sgVector2 *DrawOverrideHandle();
  float *DrawOverrideXHandle();
  float *DrawOverrideYHandle();
  int *AlphaHandle();
  int EffectiveAlpha();
  bool Visible();
  UIObject *GetChildByName(const std::string &name);
  virtual void OnDirty();

  void DirtyInternal();
  void UpdateInternal();
  void DrawInternal();
  void SetDrawOverride(sgVector2 loc);

  std::string Name;
  // When one of the children of this object are dirty, should we dirty too?  This is for HLG, VLG mainly.
  bool ParentDirtyWithChildren = false;
  bool Enabled = true;
  UIObject *Parent = nullptr;
  RectangleF Bounds = {0, 0, 0, 0};
  std::vector<std::shared_ptr<UIObject>> Children;
  sgVector2 Offset = {0, 0};
  sgVector2 LayoutGroupOffset = {0, 0};
  int WidgetType = 0;
  std::vector<std::shared_ptr<UIObjectAnimatorBase>> Animators;

protected:
  bool Dirty = true;
  sgVector2 _drawOverride = {0, 0};
  int _alpha = 255;
  bool _visible = true;
  int _layer = 0;
  std::vector<UIObject *> _drawOrder;

  virtual void Update();
  virtual void Draw();
  friend UIWidget;
};

} // namespace Supergoon
