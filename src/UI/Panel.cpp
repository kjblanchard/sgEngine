#include <Supergoon/UI/Panel.hpp>
#include <algorithm>
#include <cassert>
using namespace Supergoon;
Panel::Panel() : UIObject() {
}
Panel::Panel(UIObject* parent, std::string name) : UIObject(parent) {
	WidgetType = (int)BuiltinWidgetTypes::Panel;
	parent->Children[name] = std::shared_ptr<UIObject>(this);
}
