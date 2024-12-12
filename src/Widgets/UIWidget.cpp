#include <Supergoon/Graphics/Graphics.hpp>
#include <Supergoon/UI/Panel.hpp>
#include <Supergoon/UI/UI.hpp>
#include <Supergoon/UI/UIHorizontalLayoutGroup.hpp>
#include <Supergoon/UI/UIImage.hpp>
#include <Supergoon/UI/UIText.hpp>
#include <Supergoon/UI/UIVerticalLayoutGroup.hpp>
#include <Supergoon/Widgets/UIWidget.hpp>
#include <Supergoon/Widgets/Widgets.hpp>
#include <Supergoon/pch.hpp>
using namespace Supergoon;
static bool shouldDrawDebugBox = false;

void UIWidget::DrawUIObjects(UIObject *uiObject, std::string panelName) {
  if (ImGui::TreeNode((panelName).c_str())) {
    auto panelLayerLabel = "Layer ##" + panelName;
    auto panelOffsetLabel = "Offset X ##" + panelName;
    auto panelOffsetYLabel = "Offset Y ##" + panelName;
    ImGui::BeginDisabled();
    ImGui::Text("Layout Group X: %f, LayoutGroup Y: %f ##%s", uiObject->LayoutGroupOffset.X, uiObject->LayoutGroupOffset.Y, panelName.c_str());
    ImGui::EndDisabled();
    auto panelTransparencyLabel = "Transparency ##" + panelName;
    auto visibleLable = "Visible ##" + panelName;
    auto text = "Type: " + GetWidgetTypeName((BuiltinWidgetTypes)uiObject->WidgetType);
    ImGui::Text("%s", text.c_str());
    if (ImGui::DragInt(panelLayerLabel.c_str(), &uiObject->_layer, 1, 0, 100)) {
      uiObject->SetDirty();
    }
    if (ImGui::Checkbox(visibleLable.c_str(), &uiObject->_visible)) {
      uiObject->SetDirty();
    }
    if (ImGui::DragFloat(panelOffsetLabel.c_str(), &uiObject->Offset.X, 1.0f)) {
      uiObject->SetDirty();
    }
    if (ImGui::DragFloat(panelOffsetYLabel.c_str(), &uiObject->Offset.Y, 1.0f)) {
      uiObject->SetDirty();
    }
    if (ImGui::DragInt(panelTransparencyLabel.c_str(), uiObject->AlphaHandle(), 1, 0, 255, "%d")) {
      uiObject->SetDirty();
    }
    if (uiObject->WidgetType == (int)BuiltinWidgetTypes::Image) {
      auto imageObject = dynamic_cast<UIImage *>(uiObject);
      std::string childLayerLabel = "Layer##" + panelName;
      std::string childWLabel = "Child W##" + panelName;
      std::string childHLabel = "Child H##" + panelName;
      if (ImGui::DragInt(childLayerLabel.c_str(), &uiObject->_layer, 1, 0, 100)) {
        uiObject->SetDirty();
        if (uiObject->Parent) {
          uiObject->SetDirty();
        }
      }
      if (ImGui::DragFloat(childWLabel.c_str(), &imageObject->Bounds.W, 1.0f)) {
        uiObject->SetDirty();
      }
      if (ImGui::DragFloat(childHLabel.c_str(), &imageObject->Bounds.H, 1.0f)) {
        uiObject->SetDirty();
      }
    } else if (uiObject->WidgetType == (int)BuiltinWidgetTypes::Text) {
      assert((UIText *)uiObject);
      auto textUIObject = (UIText *)uiObject;
      std::string childLayerLabel = "Layer##" + panelName;
      std::string childW_label = "Width##" + panelName;
      std::string childH_label = "Height##" + panelName;
      std::string childXBounds = "TextBoundsX##" + panelName;
      std::string childYBounds = "TextBoundsY##" + panelName;
      std::string childWordWrapLabel = "WordWrap##" + panelName;
      std::string childCenterLabel = "Center##" + panelName;
      std::string childCenterLabelY = "CenterY##" + panelName;
      std::string childLettersToDraw = "Letters To Draw##" + panelName;
      std::string childDebugBoxCheckbox = "DebugBox##" + panelName;
      if (ImGui::DragInt(childLayerLabel.c_str(), &uiObject->_layer, 1, 0, 100)) {
        uiObject->SetDirty();
        uiObject->SetDirty();
      }
      if (ImGui::DragFloat(childW_label.c_str(), &uiObject->Bounds.W, 1.0f, 0.0f, FLT_MAX)) {
        uiObject->SetDirty();
      }
      if (ImGui::DragFloat(childH_label.c_str(), &uiObject->Bounds.H, 1.0f, 0.0f, FLT_MAX)) {
        uiObject->SetDirty();
      }
      if (ImGui::Checkbox(childWordWrapLabel.c_str(), &textUIObject->WordWrap)) {
        uiObject->SetDirty();
      };
      ImGui::SameLine();
      if (ImGui::Checkbox(childCenterLabel.c_str(), &textUIObject->CenterTextX)) {
        uiObject->SetDirty();
      };
      ImGui::SameLine();
      if (ImGui::Checkbox(childCenterLabelY.c_str(), &textUIObject->_centerTextY)) {
        uiObject->SetDirty();
      };
      ImGui::SameLine();
      ImGui::Checkbox(childDebugBoxCheckbox.c_str(), &shouldDrawDebugBox);

      if (shouldDrawDebugBox) {
        // auto color = Color{255,0,0,255};
        Graphics::Instance()->DrawRect(textUIObject->Bounds, Color{255, 0, 0, 255});
      }
      if (ImGui::DragInt(childLettersToDraw.c_str(), &textUIObject->_currentLetters, 1, 0, textUIObject->TextPtr->_text.length())) {
        uiObject->SetDirty();
      }
    } else if (uiObject->WidgetType == (int)BuiltinWidgetTypes::HorizontalLayoutGroup) {
      assert((UIHorizontalLayoutGroup *)uiObject);
      auto horiGroup = (UIHorizontalLayoutGroup *)uiObject;
      std::string childSpaceLabel = "Space Y##" + panelName;
      if (ImGui::DragFloat(childSpaceLabel.c_str(), &horiGroup->XSpaceBetweenElements, 1.0f, -255, 255)) {
        uiObject->SetDirty();
      }
      // ImGui::End();
    } else if (uiObject->WidgetType == (int)BuiltinWidgetTypes::VerticalLayoutGroup) {
      assert((UIVerticalLayoutGroup *)uiObject);
      auto horiGroup = (UIVerticalLayoutGroup *)uiObject;
      std::string childSpaceLabel = "Space Y##" + panelName;
      if (ImGui::DragFloat(childSpaceLabel.c_str(), &horiGroup->YSpaceBetweenElements, 1.0f, -255, 255)) {
        uiObject->SetDirty();
      }
    }
    ImGui::Text("Object Children__");
    for (auto &value : uiObject->Children) {
      DrawUIObjects(value.get(), value->Name);
    }
    ImGui::TreePop();
  }
}

void UIWidget::ShowUiDebugWindow() {
  auto rootPanel = UI::UIInstance.get();
  if (!rootPanel) {
    return;
  }
  auto window_flags = Widgets::GetDefaultWindowFlags();
  bool p_open;
  if (!ImGui::Begin("UI", &p_open, window_flags)) {
    // Early out if the window is collapsed, as an optimization.
    ImGui::End();
    return;
  }

  if (ImGui::CollapsingHeader("UI Elements")) {
    DrawUIObjects(rootPanel, "Root");
  }

  if (ImGui::CollapsingHeader("UI Animators")) {
    // We will need to loop over all panels animators
    for (auto &value : UI::UIInstance->Children) {
      for (auto &&animator : value->Animators) {
        if (ImGui::TreeNode(animator->Name.c_str())) {
          auto name = std::string("Play ##") + animator->Name;
          auto valueText = animator->IsPlaying() ? "True" : "False";
          // auto playingText = std::string("Is Playing ") + valueText + "## " + animator->Name;
          auto playingText = std::string("Is Playing ") + valueText;
          ImGui::Text("%s", playingText.c_str());
          ImGui::SameLine();
          auto percentText = std::string("Percent: ") + std::to_string(animator->SequenceToPlay->Percent());
          ImGui::Text("%s", percentText.c_str());

          if (ImGui::Button(name.c_str())) {
            animator->Play();
          }
          ImGui::SameLine();
          auto stop = std::string("Stop ##") + animator->Name;
          if (ImGui::Button(stop.c_str())) {
            animator->Stop();
          }
          ImGui::SameLine();
          auto pause = std::string("Pause ##") + animator->Name;
          if (ImGui::Button(pause.c_str())) {
            animator->Pause();
          }
          ImGui::TreePop();
        }
      }
    }
  }
  ImGui::End();
}
