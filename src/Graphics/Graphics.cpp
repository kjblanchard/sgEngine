#include <SDL3/SDL.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_rect.h>
#include <SupergoonEngine/log.h>

#include <Supergoon/Content/Image.hpp>
#ifdef imgui
#include <SupergoonEngine/imgui/imgui_impl_sdl3.h>
#include <SupergoonEngine/imgui/imgui_impl_sdlrenderer3.h>
#endif

#include <Supergoon/Graphics/Graphics.hpp>
using namespace Supergoon;
Graphics *Graphics::_instance = nullptr;

void Graphics::DrawRect(RectangleF &dstRect, Color color) {
  SDL_SetRenderDrawColor(_renderer, color.R, color.G, color.B, color.A);
  SDL_RenderRect(_renderer, (SDL_FRect *)&dstRect);
  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

Graphics::~Graphics() {
#ifdef imgui
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
#endif
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
}

// void geUtilsDrawRectF(geRectangleF* dstRect, geColor* color) {
// 	SDL_Renderer* r = geGlobalRenderer();
// 	SDL_SetRenderDrawColor(r, color->R, color->G, color->B, color->A);
// 	SDL_RenderDrawRectF(r, (SDL_FRect*)dstRect);
// 	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
// }

// void geUtilsDrawFilledRect(geRectangle* dstRect, geColor* color) {
// 	SDL_Renderer* r = geGlobalRenderer();
// 	SDL_SetRenderDrawColor(r, color->R, color->G, color->B, color->A);
// 	SDL_RenderFillRect(r, (SDL_Rect*)dstRect);
// 	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
// }
void Graphics::CreateWindow(int width, int height, std::string name) {
  _windowWidth = width;
  _windowHeight = height;
  SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
#ifdef imgui
  // Make the window start bigger if we are debugging.
  width *= 2;
  height *= 2;
#endif
  auto flags = SDL_WINDOW_RESIZABLE;
  if (!SDL_CreateWindowAndRenderer(name.c_str(), width, height, flags, &_window, &_renderer)) {
    sgLogCritical("Could not load window, error, %s", SDL_GetError());
  }
}
void Graphics::InitializeImGui() {
#ifdef imgui
  ImGui_ImplSDL3_InitForSDLRenderer(_window, _renderer);
  ImGui_ImplSDLRenderer3_Init(_renderer);
  _imguiGameTexture = CreateRenderTargetTexture(_logicalWidth, _logicalHeight);
#endif
}

void Graphics::CloseImGui() {
#ifdef imgui
  ImGuiIO &io = ImGui::GetIO();
  SDL_free((void *)io.IniFilename);
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
#endif
}

void Graphics::DrawStart() {
  SDL_RenderClear(_renderer);
#ifdef imgui
  ClearRenderTargetTexture(_imguiGameTexture);
  // Draw everything to this target instead when building with imgui.
  SDL_SetRenderTarget(_renderer, _imguiGameTexture);
  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
#endif
}

void Graphics::DrawImGui() {
#ifdef imgui
  SDL_SetRenderTarget(_renderer, NULL);
  ImGui::ShowDemoWindow();
  ImGui::Render();
  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), _renderer);
#endif
}

void Graphics::SetWindowScaling(int worldx, int worldY) {
  _logicalWidth = worldx;
  _logicalHeight = worldY;
#ifndef imgui
  auto display = SDL_GetPrimaryDisplay();
  auto mode = SDL_GetCurrentDisplayMode(display);
  if (!mode) {
    sgLogWarn("Could not get display info for some reason!");
  }
  // SDL_SetRenderScale(_renderer, 2.0, 2.0);
  // _refreshRate = mode->refresh_rate ? mode->refresh_rate : 60;
  // SDL_SetRenderLogicalPresentation(_renderer, worldx, worldY, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE, SDL_SCALEMODE_NEAREST);
  SDL_SetRenderLogicalPresentation(_renderer, worldx, worldY, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
#endif
}
void Graphics::DrawEnd() {
  SDL_RenderPresent(_renderer);
}
void Graphics::DrawImage(Image &image, RectangleF *srcR, RectangleF *dstR) {
  if (srcR->Zero()) {
    SDL_RenderTexture(_renderer, image._image, nullptr, (SDL_FRect *)dstR);

  } else {
    SDL_RenderTexture(_renderer, image._image, (SDL_FRect *)srcR, (SDL_FRect *)dstR);
  }
}
SDL_Texture *Graphics::CreateRenderTargetTexture(int width, int height, Color color) {
  auto image = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
  SDL_SetRenderTarget(_renderer, image);
  if (SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND) != true) {
    sgLogError("Error setting blend mode: %s", SDL_GetError());
  }
  SDL_SetTextureScaleMode(image, SDL_SCALEMODE_NEAREST);
  SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(_renderer, color.R, color.G, color.B, color.A);
  SDL_RenderClear(_renderer);
  SDL_SetRenderTarget(_renderer, NULL);
  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
  return image;
}
void Graphics::SetTextureColor(SDL_Texture *texture, Color color) {
  SDL_SetTextureColorMod(texture, color.R, color.G, color.B);
}

void Graphics::SetTextureAlpha(SDL_Texture *texture, int alpha) {
  SDL_SetTextureAlphaMod(texture, alpha);
}

void Graphics::ClearRenderTargetTexture(SDL_Texture *texture, Color color) {
  SDL_SetRenderTarget(_renderer, texture);
  SDL_SetRenderDrawColor(_renderer, color.R, color.G, color.B, color.A);
  if (!SDL_RenderClear(_renderer)) {
    sgLogWarn("Could not clear texture, %s", SDL_GetError());
  }
  SDL_SetRenderTarget(_renderer, NULL);
  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

void Graphics::DrawImageToImage(Image &src, Image &dst, RectangleF *srcR, RectangleF *dstR) {
  SDL_SetRenderTarget(_renderer, dst._image);
  if (srcR->Zero()) {
    if (!SDL_RenderTexture(_renderer, src._image, nullptr, (SDL_FRect *)dstR)) {
      sgLogWarn("Could not draw image to image, %s", SDL_GetError());
    }
  } else {
    SDL_RenderTexture(_renderer, src._image, (SDL_FRect *)srcR, (SDL_FRect *)dstR);
  }
  SDL_SetRenderTarget(_renderer, NULL);
}

SDL_Texture *Graphics::CreateTextureFromSurface(SDL_Surface *surface) {
  SDL_Texture *t = SDL_CreateTextureFromSurface(_renderer, surface);
#ifndef imgui
  // TODO, not sure why this is, but there is a pixel bug when using imgui and scaling.  Have texted on linux and mac and get this, but software renderer works fine.
  SDL_SetTextureScaleMode(t, SDL_SCALEMODE_NEAREST);
#endif
  SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
  if (t == NULL) {
    sgLogError("Could not create texture, Error: %s", SDL_GetError());
    return NULL;
  }
  SDL_DestroySurface(surface);
  return t;
}
