#include <Supergoon/UI/UIObject.hpp>
#include <Supergoon/UI/UIObjectAnimator.hpp>
#include <algorithm>
#include <cassert>
using namespace Supergoon;
using namespace std;

string Supergoon::GetWidgetTypeName(BuiltinWidgetTypes widget) {
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

UIObject::UIObject() = default;

UIObject::UIObject(UIObject* parent, string name, bool enabled, bool visible)
	: Name(name), Enabled(enabled), Parent(parent), _visible(visible) {
	if (parent) {
		parent->AddChild(this);
	}
}

void UIObject::RemoveChild(const std::string& name) {
	Children.erase(std::remove_if(Children.begin(), Children.end(),
								  [name](const auto& obj) {
									  return obj->Name == name;
								  }),
				   Children.end());
}
UIObject* UIObject::GetChildByName(const string& name) {
	if (Children.empty()) {
		return nullptr;
	}
	auto it = find_if(
		Children.begin(), Children.end(), [name](const shared_ptr<UIObject>& obj) {
			return obj->Name == name;
		});
	return it == Children.end() ? nullptr : (*it).get();
}

void UIObject::AddChild(UIObject* child) {
	Children.push_back(shared_ptr<UIObject>(child));
}

void UIObject::AddChild(shared_ptr<UIObject> child) {
	Children.push_back(child);
}

void UIObject::SetVisible(bool visible) {
	_visible = visible;
	Dirty = true;
}

void UIObject::SetAlpha(int alpha) {
	_alpha = clamp(alpha, 0, 255);
	Dirty = true;
}

unsigned int UIObject::Layer() {
	return _layer;
}

void UIObject::SetLayer(unsigned int layer) {
	_layer = layer;
	if (Parent) {
		Parent->Dirty = true;
	}
	Dirty = true;
}

int* UIObject::AlphaHandle() {
	return &_alpha;
}

int UIObject::EffectiveAlpha() {
	return Parent ? static_cast<int>((Parent->EffectiveAlpha() / 255.0) * (_alpha / 255.0) * 255) : _alpha;
}

bool UIObject::Visible() {
	return Parent ? Parent->Visible() ? _visible : false : _visible;
}

void UIObject::OnDirty() {}

void UIObject::DirtyInternal() {
	const auto parentX = Parent ? Parent->Bounds.X : 0;
	const auto parentY = Parent ? Parent->Bounds.Y : 0;
	Bounds.X = Offset.X + LayoutGroupOffset.X + parentX;
	Bounds.Y = Offset.Y + LayoutGroupOffset.Y + parentY;
	_drawOrder.clear();
	for (auto& uiObject : Children) {
		_drawOrder.push_back(uiObject.get());
	}
	sort(_drawOrder.begin(), _drawOrder.end(), [](UIObject* lhs, UIObject* rhs) {
		return lhs->Layer() <= rhs->Layer();
	});
	for (auto& uiObject : Children) {
		uiObject->DirtyInternal();
	}
	OnDirty();
}

void UIObject::UpdateInternal() {
	if (!Enabled) {
		return;
	}
	if (Dirty) {
		DirtyInternal();
		Dirty = false;
	}
	Update();
	for (auto& uiObject : Children) {
		if (!uiObject) {
			continue;
		}
		uiObject->UpdateInternal();
	}
	for (auto&& animator : Animators) {
		animator->Update();
	}
}

void UIObject::DrawInternal() {
	if (!Visible()) {
		return;
	}
	Draw();
	for (auto child : _drawOrder) {
		assert(child);
		child->DrawInternal();
	}
}

void UIObject::Update() {}

void UIObject::Draw() {}