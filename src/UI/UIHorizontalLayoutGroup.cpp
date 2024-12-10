#include <Supergoon/UI/UIHorizontalLayoutGroup.hpp>
#include <Supergoon/pch.hpp>

using namespace Supergoon;

UIHorizontalLayoutGroup::UIHorizontalLayoutGroup(UIObject* parent, std::string name) : UIObject(parent) {
	WidgetType = (int)BuiltinWidgetTypes::HorizontalLayoutGroup;
	parent->Children[name] = std::shared_ptr<UIObject>(this);
}
void UIHorizontalLayoutGroup::OnDirty() {
	int i = 0;
	for (auto& [name, uiObject] : Children) {
		uiObject->LayoutGroupOffset.X = i * XSpaceBetweenElements;
		uiObject->DirtyInternal();
		++i;
	}
}
