#pragma once
#include <Supergoon/UI/UIObject.hpp>
#include <memory>
#include <string>
#include <unordered_map>
namespace Supergoon {
class UIWidget;
class Panel : public UIObject {
   public:
	Panel();
	Panel(UIObject* parent, std::string name);

   private:
	friend UIWidget;
};
}  // namespace Supergoon
