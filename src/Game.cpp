
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SupergoonEngine/Bgm.h>
#include <SupergoonEngine/Sfx.h>
#include <SupergoonEngine/clock.h>
#include <SupergoonEngine/input/joystick.h>
#include <SupergoonEngine/input/keyboard.h>
#ifdef imgui
#include <Supergoon/Widgets/Widgets.hpp>
#endif
#include <Supergoon/Content/ContentRegistry.hpp>
#include <Supergoon/Coroutine.h>
#include <Supergoon/Events.hpp>
#include <Supergoon/Filesystem.hpp>
#include <Supergoon/Game.hpp>
#include <Supergoon/Graphics/Graphics.hpp>
#include <Supergoon/Log.hpp>
// #include <Supergoon/Lua.h>
#include <Supergoon/Sound.hpp>
#include <Supergoon/UI/UI.hpp>
#include <Supergoon/pch.hpp>
#include <thread>

using json = nlohmann::json;
using namespace std;
using namespace Supergoon;
json configData;

SDL_AppResult SDL_AppInit(void **appState, int, char *[]) {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't initialize SDL!", SDL_GetError(), NULL);
    return SDL_APP_FAILURE;
  }
  sgInitializeDebugLogFile();
#ifdef imgui
  Widgets::InitializeWidgets();
#endif
  geInitializeKeyboard();
  geInitializeJoysticks();
  // sgInitializeLua();

  auto game = sgRegisterGame();
  *appState = game;
  game->InternalReset();
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appState, SDL_Event *event) {
  return (SDL_AppResult)((Game *)appState)->HandleEvent(event);
}

SDL_AppResult SDL_AppIterate(void *appState) {
  geUpdateKeyboard();
  auto game = (Game *)appState;
  game->InternalUpdate();
  game->InternalDraw();
  geUpdateControllerLastFrame();
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appState, SDL_AppResult) {
  auto game = (Game *)appState;
  game->Reset();
}

Game::~Game() {
  sgCloseDebugLogFile();
  _graphics->CloseImGui();
}
void Game::Initialize() {
  std::string filename = SDL_GetBasePath() + std::string("assets/config.json");
  auto fileStream = SafeLoadFile(filename);
  configData = json::parse(fileStream);

  int windowWidth = configData["window"]["x"];
  int windowHeight = configData["window"]["y"];
  int worldWidth = configData["world"]["x"];
  int worldHeight = configData["world"]["y"];
  std::string windowTitle = configData["window"]["title"];
  _events = std::make_shared<Events>(this);
  _sound = std::make_shared<Sound>();
  _graphics = std::make_shared<Graphics>();
  _graphics->CreateWindow(windowWidth, windowHeight, windowTitle);
  _graphics->SetWindowScaling(worldWidth, worldHeight);
  geClockStart(&_clock);
  InitializeImGui();
  _graphics->InitializeImGui();
  _sound->InitializeSound();
  _initialized = true;
}

int Game::HandleEvent(SDL_Event *event) {
  return _events->HandleEvent(event);
}

void Game::InitializeImGui() {
#ifdef imgui
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // IF using Docking Branch
  static auto thing = std::string(SDL_GetPrefPath("Supergoon Games", "EscapeTheFate")) + "debug.ini";
  io.IniFilename = thing.c_str();
#endif
}
static void threadSound(Sound *sound) {
  sound->Update();
}

void Game::InternalUpdate() {
  geClockUpdate(&_clock);
#ifndef __EMSCRIPTEN__
  std::thread t1(threadSound, _sound.get());
#else
  _sound->Update();
#endif
  sgUpdateCoroutines(DeltaTime());
  Update();
#ifndef __EMSCRIPTEN__
  t1.join();
#endif
}

void Game::InternalDraw() {
  _graphics->DrawStart();
  Draw();
  _graphics->DrawImGui();
  _graphics->DrawEnd();
}

void Game::InternalReset() {
  Reset();
  UI::Reset();
  GameObject::ClearGameObjects();
  ContentRegistry::DestroyAllContent();
  if (!_initialized) {
    Initialize();
  }
  UI::Initialize();
  Start();
}

double Game::DeltaTime() {
  return geClockGetUpdateTimeSeconds();
}

double Game::DeltaTimeMS() {
  return geClockGetUpdateTimeMilliseconds();
}
