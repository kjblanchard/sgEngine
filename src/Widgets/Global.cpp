#include <Supergoon/ECS/Components/AnimationComponent.hpp>
#include <Supergoon/ECS/Gameobject.hpp>
#include <Supergoon/Events.hpp>
#include <Supergoon/Widgets/Global.hpp>
#include <Supergoon/Widgets/Widgets.hpp>
#include <Supergoon/pch.hpp>
using namespace Supergoon;

bool GlobalWidget::ShowDebugBoxSolid = false;

void GlobalWidget::ShowGlobalDebugWindow() {
  auto window_flags = Widgets::GetDefaultWindowFlags();
  bool p_open;
  if (!ImGui::Begin("Global", &p_open, window_flags)) {
    // Early out if the window is collapsed, as an optimization.
    ImGui::End();
    return;
  }
  if (ImGui::Button("Reset##globalreset")) {
    Events::PushEvent(Events::BuiltinEvents.ResetGameEvent, 0);
  }
  // TODO this is very ineffieicnt, yes.
  ImGui::Text("Total number of gameobjects %d", GameObject::NumberGameObjects());
  // Show animation component stuff.
  if (ImGui::TreeNode("AnimationComponents")) {
    GameObject::ForEach<AnimationComponent>([](GameObject, AnimationComponent &anim) {
      auto last = anim.Animation->Filename().rfind('/');
      assert(last != std::string::npos);
      if (ImGui::TreeNode(anim.Animation->Filename().substr(last + 1).c_str())) {
        auto x = std::string("X: ##") + anim.Animation->Filename().c_str();
        auto y = std::string("Y: ##") + anim.Animation->Filename().c_str();
        auto width = std::string("Width: ##") + anim.Animation->Filename().c_str();
        auto height = std::string("Height: ##") + anim.Animation->Filename().c_str();
        auto playing = std::string("Playing: ##") + anim.Animation->Filename().c_str();
        auto speed = std::string("Speed: ##") + anim.Animation->Filename().c_str();
        auto animColorString = std::string("Color: ##") + anim.Animation->Filename().c_str();
        //   Why do we need the handle?
        auto animColor = anim.AnimationImage->GetColorHandle();
        int colors[4] = {animColor->R, animColor->G, animColor->B, animColor->A};

        ImGui::SliderInt(x.c_str(), &anim.Offset.X, -200, 200);
        ImGui::SliderInt(y.c_str(), &anim.Offset.Y, -200, 200);
        ImGui::SliderInt(width.c_str(), &anim.OverrideDrawSize.X, 0, 400);
        ImGui::SliderInt(height.c_str(), &anim.OverrideDrawSize.Y, 0, 400);
        ImGui::Checkbox(playing.c_str(), &anim.Playing);
        ImGui::SliderFloat(speed.c_str(), &anim.AnimationSpeed, 0, 5.0f);
        if (ImGui::SliderInt4(animColorString.c_str(), colors, 0, 255)) {
          anim.AnimationImage->SetImageColor(sgColor{(uint8_t)colors[0], (uint8_t)colors[1], (uint8_t)(uint8_t)colors[2], (uint8_t)colors[3]});
          //   animColor->R = colors[0];
          //   animColor->G = colors[1];
          //   animColor->B = colors[2];
          //   animColor->A = colors[3];
        }
        ImGui::TreePop();
      }
    });
    ImGui::TreePop();
  }
  ImGui::Checkbox("Show Static Debug Colliders", &ShowDebugBoxSolid);
  ImGui::End();
}
