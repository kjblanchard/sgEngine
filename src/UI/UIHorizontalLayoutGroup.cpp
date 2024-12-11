#include <Supergoon/UI/UIHorizontalLayoutGroup.hpp>
#include <Supergoon/pch.hpp>

using namespace Supergoon;

UIHorizontalLayoutGroup::UIHorizontalLayoutGroup(UIObject* parent, std::string name) : UIObject(parent, name) {
	WidgetType = (int)BuiltinWidgetTypes::HorizontalLayoutGroup;
}
void UIHorizontalLayoutGroup::OnDirty() {
	int i = 0;
	for (auto& uiObject : Children) {
		uiObject->LayoutGroupOffset.X = i * XSpaceBetweenElements;
		uiObject->DirtyInternal();
		++i;
	}
}
