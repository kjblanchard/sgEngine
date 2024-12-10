#include <Supergoon/Graphics/Graphics.hpp>
#include <Supergoon/UI/Panel.hpp>
#include <Supergoon/UI/UI.hpp>
#include <Supergoon/UI/UIHorizontalLayoutGroup.hpp>
#include <Supergoon/UI/UIImage.hpp>
#include <Supergoon/UI/UIText.hpp>
#include <Supergoon/UI/UIVerticalLayoutGroup.hpp>
#include <Supergoon/Widgets/UIWidget.hpp>
#include <Supergoon/Widgets/Widgets.hpp>
#ifdef imgui
#include <SupergoonEngine/imgui/imgui.h>
#endif
using namespace Supergoon;
static bool shouldDrawDebugBox = false;

void UIWidget::DrawUIObjects(UIObject *panel, std::string panelName) {
	if (ImGui::TreeNode((panelName).c_str())) {
		auto panelLayerLabel = "Layer ##" + panelName;
		auto panelOffsetLabel = "Offset X ##" + panelName;
		auto panelOffsetYLabel = "Offset Y ##" + panelName;
		ImGui::BeginDisabled();
		ImGui::Text("Layout Group X: %f, LayoutGroup Y: %f ##%s", panel->LayoutGroupOffset.X, panel->LayoutGroupOffset.Y, panelName.c_str());
		ImGui::EndDisabled();
		auto panelTransparencyLabel = "Transparency ##" + panelName;
		auto visibleLable = "Visible ##" + panelName;
		auto text = "Type: " + GetWidgetTypeName((BuiltinWidgetTypes)panel->WidgetType);
		ImGui::Text("%s", text.c_str());
		if (ImGui::DragInt(panelLayerLabel.c_str(), &panel->_layer, 1, 0, 100)) {
			panel->Dirty = true;
		}
		if (ImGui::Checkbox(visibleLable.c_str(), &panel->_visible)) {
			panel->Dirty = true;
		}
		if (ImGui::DragFloat(panelOffsetLabel.c_str(), &panel->Offset.X, 1.0f)) {
			panel->Dirty = true;
		}
		if (ImGui::DragFloat(panelOffsetYLabel.c_str(), &panel->Offset.Y, 1.0f)) {
			panel->Dirty = true;
		}
		if (ImGui::DragInt(panelTransparencyLabel.c_str(), panel->AlphaHandle(), 1, 0, 255, "%d")) {
			panel->Dirty = true;
		}
		if (panel->WidgetType == (int)BuiltinWidgetTypes::Image) {
			auto imageObject = dynamic_cast<UIImage *>(panel);
			std::string childLayerLabel = "Layer##" + panelName;
			std::string childX_label = "Offset X##" + panelName;
			std::string childY_label = "Offset Y##" + panelName;
			std::string childWLabel = "Child W##" + panelName;
			std::string childHLabel = "Child H##" + panelName;
			std::string transLabel = "Child Transparency##" + panelName;
			if (ImGui::TreeNode((panelName + "- image").c_str())) {
				if (ImGui::DragInt(childLayerLabel.c_str(), &panel->_layer, 1, 0, 100)) {
					panel->Dirty = true;
					if (panel->Parent) {
						panel->Dirty = true;
					}
				}
				if (ImGui::DragFloat(childX_label.c_str(), &panel->Offset.X, 1.0f)) {
					panel->Dirty = true;
				}
				if (ImGui::DragFloat(childY_label.c_str(), &imageObject->Offset.Y, 1.0f)) {
					panel->Dirty = true;
				}
				if (ImGui::DragFloat(childWLabel.c_str(), &imageObject->Bounds.W, 1.0f)) {
					panel->Dirty = true;
				}
				if (ImGui::DragFloat(childHLabel.c_str(), &imageObject->Bounds.H, 1.0f)) {
					panel->Dirty = true;
				}
				if (ImGui::DragInt(transLabel.c_str(), imageObject->AlphaHandle(), 1, 0, 255, "%d", ImGuiSliderFlags_WrapAround)) {
					panel->Dirty = true;
				}
				ImGui::TreePop();
			}
		} else if (panel->WidgetType == (int)BuiltinWidgetTypes::Text) {
			assert((UIText *)panel);
			auto textUIObject = (UIText *)panel;
			std::string childLayerLabel = "Layer##" + panelName;
			std::string childX_label = "Offset X##" + panelName;
			std::string childY_label = "Offset Y##" + panelName;
			std::string childW_label = "Width##" + panelName;
			std::string childH_label = "Height##" + panelName;
			std::string childXBounds = "TextBoundsX##" + panelName;
			std::string childYBounds = "TextBoundsY##" + panelName;
			std::string childWordWrapLabel = "WordWrap##" + panelName;
			std::string childCenterLabel = "Center##" + panelName;
			std::string childCenterLabelY = "CenterY##" + panelName;
			std::string childLettersToDraw = "Letters To Draw##" + panelName;
			std::string childDebugBoxCheckbox = "DebugBox##" + panelName;
			if (ImGui::TreeNode((panelName + "- text").c_str())) {
				if (ImGui::DragInt(childLayerLabel.c_str(), &panel->_layer, 1, 0, 100)) {
					panel->Dirty = true;
					panel->Dirty = true;
				}
				if (ImGui::DragFloat(childX_label.c_str(), &panel->Offset.X, 1.0f)) {
					panel->Dirty = true;
				}
				if (ImGui::DragFloat(childY_label.c_str(), &panel->Offset.Y, 1.0f)) {
					panel->Dirty = true;
				}
				if (ImGui::DragFloat(childW_label.c_str(), &panel->Bounds.W, 1.0f, 0.0f, FLT_MAX)) {
					panel->Dirty = true;
				}
				if (ImGui::DragFloat(childH_label.c_str(), &panel->Bounds.H, 1.0f, 0.0f, FLT_MAX)) {
					panel->Dirty = true;
				}
				if (ImGui::Checkbox(childWordWrapLabel.c_str(), &textUIObject->WordWrap)) {
					panel->Dirty = true;
				};
				ImGui::SameLine();
				if (ImGui::Checkbox(childCenterLabel.c_str(), &textUIObject->CenterTextX)) {
					panel->Dirty = true;
				};
				ImGui::SameLine();
				if (ImGui::Checkbox(childCenterLabelY.c_str(), &textUIObject->_centerTextY)) {
					panel->Dirty = true;
				};
				ImGui::SameLine();
				ImGui::Checkbox(childDebugBoxCheckbox.c_str(), &shouldDrawDebugBox);

				if (shouldDrawDebugBox) {
					// auto color = Color{255,0,0,255};
					Graphics::Instance()->DrawRect(textUIObject->Bounds, Color{255, 0, 0, 255});
				}
				if (ImGui::DragInt(childLettersToDraw.c_str(), &textUIObject->_currentLetters, 1, 0, textUIObject->TextPtr->_text.length())) {
					panel->Dirty = true;
				}
				ImGui::TreePop();
			}
		} else if (panel->WidgetType == (int)BuiltinWidgetTypes::HorizontalLayoutGroup) {
			assert((UIHorizontalLayoutGroup *)panel);
			auto horiGroup = (UIHorizontalLayoutGroup *)panel;
			std::string childLayerLabel = "Layer##" + panelName;
			std::string childXLabel = "Offset X##" + panelName;
			std::string childYLabel = "Offset Y##" + panelName;
			std::string childSpaceLabel = "Space Y##" + panelName;
			if (ImGui::TreeNode((panelName + "- text").c_str())) {
				if (ImGui::DragInt(childLayerLabel.c_str(), &panel->_layer, 1, 0, 100)) {
					panel->Dirty = true;
					if (panel->Parent) {
						panel->Dirty = true;
					}
				}
				if (ImGui::DragFloat(childXLabel.c_str(), &panel->Offset.X, 1.0f)) {
					panel->Dirty = true;
				}
				if (ImGui::DragFloat(childYLabel.c_str(), &panel->Offset.Y, 1.0f)) {
					panel->Dirty = true;
				}
				if (ImGui::DragFloat(childSpaceLabel.c_str(), &horiGroup->XSpaceBetweenElements, 1.0f, -255, 255)) {
					panel->Dirty = true;
				}
				ImGui::BeginDisabled();
				ImGui::Text("Layout Group X: %f, LayoutGroup Y: %f ##%s", panel->LayoutGroupOffset.X, panel->LayoutGroupOffset.Y, panelName.c_str());
				ImGui::EndDisabled();
				ImGui::TreePop();
			}

			// ImGui::End();
		} else if (panel->WidgetType == (int)BuiltinWidgetTypes::VerticalLayoutGroup) {
			assert((UIVerticalLayoutGroup *)panel);
			auto horiGroup = (UIVerticalLayoutGroup *)panel;
			std::string childLayerLabel = "Layer##" + panelName;
			std::string childXLabel = "Offset X##" + panelName;
			std::string childYLabel = "Offset Y##" + panelName;
			std::string childSpaceLabel = "Space Y##" + panelName;
			if (ImGui::TreeNode((panelName + "- text").c_str())) {
				if (ImGui::DragInt(childLayerLabel.c_str(), &panel->_layer, 1, 0, 100)) {
					panel->Dirty = true;
					if (panel->Parent) {
						panel->Dirty = true;
					}
				}
				if (ImGui::DragFloat(childXLabel.c_str(), &panel->Offset.X, 1.0f)) {
					panel->Dirty = true;
				}
				if (ImGui::DragFloat(childYLabel.c_str(), &panel->Offset.Y, 1.0f)) {
					panel->Dirty = true;
				}
				if (ImGui::DragFloat(childSpaceLabel.c_str(), &horiGroup->YSpaceBetweenElements, 1.0f, -255, 255)) {
					panel->Dirty = true;
				}
				ImGui::TreePop();
			}

			// ImGui::End();
		}
		for (auto &[panelName, value] : panel->Children) {
			DrawUIObjects(value.get(), panelName);
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
		for (auto &&[key, value] : UI::UIInstance->Children) {
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
