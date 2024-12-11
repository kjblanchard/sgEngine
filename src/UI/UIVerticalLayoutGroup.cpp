#include <Supergoon/UI/UIVerticalLayoutGroup.hpp>
#include <Supergoon/pch.hpp>

using namespace Supergoon;

UIVerticalLayoutGroup::UIVerticalLayoutGroup(UIObject* parent, std::string name) : UIObject(parent, name) {
	WidgetType = (int)BuiltinWidgetTypes::VerticalLayoutGroup;
}
void UIVerticalLayoutGroup::OnDirty() {
	int i = 0;
	for (auto& uiObject : Children) {
		uiObject->LayoutGroupOffset.Y = i * YSpaceBetweenElements;
		uiObject->DirtyInternal();
		++i;
	}
}
