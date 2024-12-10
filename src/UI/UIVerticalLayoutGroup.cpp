#include <Supergoon/UI/UIVerticalLayoutGroup.hpp>
#include <Supergoon/pch.hpp>

using namespace Supergoon;

UIVerticalLayoutGroup::UIVerticalLayoutGroup(UIObject* parent, std::string name) : UIObject(parent) {
	WidgetType = (int)BuiltinWidgetTypes::VerticalLayoutGroup;
	parent->Children[name] = std::shared_ptr<UIObject>(this);
}
void UIVerticalLayoutGroup::OnDirty() {
	int i = 0;
	for (auto& [name, uiObject] : Children) {
		uiObject->LayoutGroupOffset.Y = i * YSpaceBetweenElements;
		uiObject->DirtyInternal();
		++i;
	}
}
