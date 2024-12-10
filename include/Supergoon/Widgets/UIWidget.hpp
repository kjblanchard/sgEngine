#pragma once
#include <string>
namespace Supergoon {
class UIObject;
class UIWidget {
   public:
	static void ShowUiDebugWindow();

   private:
	static void DrawUIObjects(UIObject* obj, std::string objName);
};

}  // namespace Supergoon
