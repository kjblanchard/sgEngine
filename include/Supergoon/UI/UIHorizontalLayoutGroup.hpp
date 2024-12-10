#pragma once
#include <Supergoon/UI/UIObject.hpp>
namespace Supergoon {
class Panel;
class UIHorizontalLayoutGroup : public UIObject {
   public:
	UIHorizontalLayoutGroup(UIObject* parent, std::string id);
	virtual void OnDirty() override;
	float XSpaceBetweenElements = 0;

   private:
	friend UIWidget;
};
}  // namespace Supergoon
