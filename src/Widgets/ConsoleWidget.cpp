#include <Supergoon/Events.hpp>
#include <Supergoon/Graphics/Graphics.hpp>
#include <Supergoon/Log.hpp>
#include <Supergoon/Widgets/ConsoleWidget.hpp>
#include <Supergoon/Widgets/Game.hpp>
#include <Supergoon/Widgets/Widgets.hpp>
#include <Supergoon/pch.hpp>
using namespace Supergoon;

static const int MAX_MESSAGES = 999;
static bool scrollToBottom = false;
static bool autoScroll = true;
std::deque<std::pair<int, std::string>> consoleMessages;

static void engineLogFunc(const char *time, const char *message, int logLevel) {
  if (consoleMessages.size() >= MAX_MESSAGES) {
    consoleMessages.pop_front();
  }
  consoleMessages.push_back({logLevel, time + std::string(" ") + std::string(message)});
  scrollToBottom = true;
}

void ConsoleWidget::ShowConsoleWidget() {
  auto window_flags = Widgets::GetDefaultWindowFlags();
  bool p_open;
  if (!ImGui::Begin("Console", &p_open, window_flags)) {
    // Early out if the window is collapsed, as an optimization.
    ImGui::End();
    return;
  }
  ImGui::Checkbox("Autoscroll", &autoScroll);
  ImGui::SameLine();
  if (ImGui::Button("Clear Logs")) {
    consoleMessages.clear();
  }
  ImGui::BeginChild("##log", ImVec2(0.0f, 0.0f), ImGuiChildFlags_Borders, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar);
  for (auto message : consoleMessages) {
    sgColor color = {255, 255, 255, 255};
    std::string typeText = "Info - ";
    if (message.first == Log_LWarn) {
      color.B = 0;
      typeText = "Warning - ";
    } else if (message.first == Log_LError) {
      typeText = "Error - ";
      color.G = 0;
      color.B = 0;
    }
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(color.R, color.G, color.B, 255));
    ImGui::Text("%s %s", typeText.c_str(), message.second.c_str());
    ImGui::PopStyleColor();
  }
  if (autoScroll && scrollToBottom) {
    ImGui::SetScrollHereY(1.0);
  }
  scrollToBottom = false;
  ImGui::EndChild();

  ImGui::End();
}
void ConsoleWidget::InitializeConsoleWidget() {
  sgSetDebugFunction(engineLogFunc);
}
