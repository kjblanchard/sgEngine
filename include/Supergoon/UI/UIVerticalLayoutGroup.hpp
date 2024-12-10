#pragma once
#include <Supergoon/UI/UIObject.hpp>
namespace Supergoon {
class Panel;
class UIVerticalLayoutGroup : public UIObject {
   public:
	UIVerticalLayoutGroup(UIObject* parent, std::string id);
	virtual void OnDirty() override;
	float YSpaceBetweenElements = 0;

   private:
	friend UIWidget;
};
}  // namespace Supergoon
