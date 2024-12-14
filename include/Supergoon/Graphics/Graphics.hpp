#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <Supergoon/Primitives/Color.hpp>
#include <Supergoon/Primitives/Rectangle.hpp>
#include <string>
namespace Supergoon {

class Image;

class Graphics {
public:
  inline Graphics() { _instance = this; }
  ~Graphics();
  void CreateWindow(int width, int height, std::string name);
  void InitializeImGui();
  void CloseImGui();
  void DrawStart();
  void DrawEnd();
  void DrawImGui();
  void DrawImage(Image &image, RectangleF *srcR, RectangleF *dstR);

  void DrawImageToImage(Image &src, Image &dst, RectangleF *srcR, RectangleF *dstR);
  SDL_Texture *CreateTextureFromSurface(SDL_Surface *surface);
  SDL_Texture *CreateRenderTargetTexture(int width, int height, sgColor color = {0, 0, 0, 255});
  void ClearRenderTargetTexture(SDL_Texture *texture, sgColor color = {0, 0, 0, 255});
  void SetTextureColor(SDL_Texture *texture, sgColor color);
  void SetTextureAlpha(SDL_Texture *texture, int alpha);
  void DrawRect(RectangleF &dstRect, sgColor color);
  inline int WindowHeight() { return _windowHeight; }
  inline int WindowWidth() { return _windowWidth; }
  inline int LogicalHeight() { return _logicalHeight; }
  inline int LogicalWidth() { return _logicalWidth; }

  void SetWindowScaling(int worldx, int worldY);
#ifdef imgui
  inline void *ImGuiTexture() { return _imguiGameTexture; }
#endif

  inline static Graphics *Instance() { return _instance; }

private:
#ifdef imgui
  SDL_Texture *_imguiGameTexture;
#endif
  int _windowWidth;
  int _windowHeight;
  int _logicalWidth;
  int _logicalHeight;
  // int _refreshRate;
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  static Graphics *_instance;
};
} // namespace Supergoon
