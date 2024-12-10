
#include <Supergoon/pch.hpp>
#include <Supergoon/Widgets/ConsoleWidget.hpp>
#include <Supergoon/Widgets/ContentWidget.hpp>
#include <Supergoon/Widgets/Game.hpp>
#include <Supergoon/Widgets/Global.hpp>
#include <Supergoon/Widgets/LevelWidget.hpp>
#include <Supergoon/Widgets/SoundWidget.hpp>
#include <Supergoon/Widgets/UIWidget.hpp>
#include <Supergoon/Widgets/Widgets.hpp>
#ifdef imgui
#include <SupergoonEngine/imgui/imgui.h>
#endif
namespace Supergoon {
void Widgets::ShowWidgets(Game*) {
	ContentWidget::ShowContentDebugWindow();
	SoundWidget::ShowSoundDebugWindow();
	GameWidget::ShowGameDebugWindow();
	UIWidget::ShowUiDebugWindow();
	LevelWidget::ShowLevelWidget();
	GlobalWidget::ShowGlobalDebugWindow();
	ConsoleWidget::ShowConsoleWidget();
}
int Widgets::GetDefaultWindowFlags() {
	// static bool p_open = true;
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	// static bool no_close = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;
	static bool no_docking = false;
	static bool unsaved_document = false;
	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar) window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu) window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move) window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize) window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse) window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav) window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background) window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front) window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (no_docking) window_flags |= ImGuiWindowFlags_NoDocking;
	if (unsaved_document) window_flags |= ImGuiWindowFlags_UnsavedDocument;
	// if (no_close) p_open = NULL;  // Don't pass our bool* to Begin
	return window_flags;
}
void Widgets::InitializeWidgets() {
	ConsoleWidget::InitializeConsoleWidget();
}

}  // namespace Supergoon
