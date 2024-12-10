#pragma once
#include <Supergoon/Primitives/Rectangle.hpp>
#include <Supergoon/Primitives/Vector2.hpp>
#include <Supergoon/UI/UIObjectAnimator.hpp>
#include <cassert>
#include <map>
namespace Supergoon {
class UIWidget;
enum class BuiltinWidgetTypes {
	Image = 1,
	Text,
	Panel,
	HorizontalLayoutGroup,
	VerticalLayoutGroup,
};
static std::string GetWidgetTypeName(BuiltinWidgetTypes widget) {
	switch (widget) {
		case BuiltinWidgetTypes::Image:
			return "Image";
		case BuiltinWidgetTypes::Text:
			return "Text";
		case BuiltinWidgetTypes::Panel:
			return "Panel";
		case BuiltinWidgetTypes::HorizontalLayoutGroup:
			return "HLG";
		case BuiltinWidgetTypes::VerticalLayoutGroup:
			return "VLG";
		default:
			return "";
	}
}
class UIObject {
   public:
	inline UIObject() = default;
	inline UIObject(UIObject* parent, bool enabled = true, bool visible = true) : Enabled(enabled), Parent(parent), _visible(visible) {}
	virtual ~UIObject() = default;
	bool Enabled = true;
	bool Dirty = true;
	inline void SetVisible(bool visible) {
		_visible = visible;
		Dirty = true;
	}
	inline void SetAlpha(int alpha) {
		alpha < 0 ? _alpha = 0 : alpha > 255 ? _alpha = 255
											 : _alpha = alpha;
		Dirty = true;
	}
	inline unsigned int Layer() { return _layer; }
	inline void SetLayer(unsigned int layer) {
		_layer = layer;
		if (Parent) {
			Parent->Dirty = true;
		}
		Dirty = true;
	}
	// TODO Used for tweening alpha.. probably isn't great
	inline int* AlphaHandle() { return &_alpha; }
	UIObject* Parent = nullptr;
	RectangleF Bounds = {0, 0, 0, 0};
	// std::unordered_map<std::string, std::shared_ptr<UIObject>> Children;
	// TODO, using ordered map here for hori layout groups.. is it best?
	std::map<std::string, std::shared_ptr<UIObject>> Children;
	Vector2 Offset = {0, 0};
	Vector2 LayoutGroupOffset = {0, 0};
	// Get the effective alpha for this object, taking the parents into consideration.
	inline int EffectiveAlpha() { return Parent ? (int)((Parent->EffectiveAlpha() / 255.0) * (_alpha / 255.0) * 255) : _alpha; }
	inline bool Visible() { return Parent ? Parent->Visible() ? _visible : false : _visible; }
	int WidgetType = 0;
	std::vector<std::shared_ptr<UIObjectAnimatorBase>> Animators;
	inline virtual void OnDirty() {
	}
	inline void DirtyInternal() {
		const auto parentX = Parent ? Parent->Bounds.X : 0;
		const auto parentY = Parent ? Parent->Bounds.Y : 0;
		Bounds.X = Offset.X + LayoutGroupOffset.X + parentX;
		Bounds.Y = Offset.Y + LayoutGroupOffset.Y + parentY;
		_drawOrder.clear();
		for (auto& [name, uiObject] : Children) {
			_drawOrder.push_back(uiObject.get());
		}
		std::sort(_drawOrder.begin(), _drawOrder.end(), [](UIObject* lhs, UIObject* rhs) {
			return lhs->Layer() <= rhs->Layer();
		});
		for (auto& [name, uiObject] : Children) {
			uiObject->DirtyInternal();
		}
		OnDirty();
	}
	inline void UpdateInternal() {
		if (!Enabled) {
			return;
		}
		if (Dirty) {
			DirtyInternal();
			Dirty = false;
		}
		Update();
		for (auto& [name, uiObject] : Children) {
			if (!uiObject) {
				continue;
			}
			uiObject->UpdateInternal();
		}
		for (auto&& animator : Animators) {
			animator->Update();
		}
	}
	inline void DrawInternal() {
		if (!Visible()) {
			return;
		}
		Draw();
		for (auto child : _drawOrder) {
			assert(child);
			child->DrawInternal();
		}
	}
	friend UIWidget;

   protected:
	int _alpha = 255;
	bool _visible = true;
	int _layer = 0;
	std::vector<UIObject*> _drawOrder;
	virtual void Update() {}
	virtual void Draw() {}
};

}  // namespace Supergoon
