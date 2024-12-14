#pragma once
#include <Supergoon/Content/Content.hpp>
#include <Supergoon/Content/Font.hpp>
#include <Supergoon/Primitives/Color.hpp>
#include <Supergoon/Primitives/Point.hpp>
#include <Supergoon/Primitives/Rectangle.hpp>
#include <memory>
#include <vector>
namespace Supergoon {
class Image;
class Text : public Content {
public:
  Text(std::string text, std::string fontName, int size);
  ~Text();
  void Draw(RectangleF &src, RectangleF &dst);
  inline Point Size() { return _textSize; }
  virtual void Load() override;
  virtual void Unload() override;
  void SetTextBounds(Point bounds);
  void SetLetterCount(int letters);
  void SetWordWrap(bool wordWrap);
  void SetAlpha(int alpha);
  inline Point TextBounds() { return _textBounds; }
  inline virtual std::string Type() override { return "Text"; }

private:
  void MeasureText();
  int GetLetterWidth(FT_Face fontFace, char letter);
  bool CheckShouldWrap(int x, int wordLength, int glyphWidth, int maxX);
  void AddWordToLetterPoints(FT_Face fontFace, int wordEndPos, int wordLength, int penX, int penY);
  int GetKerning(FT_Face fontFace, int i);
  int GetLetterYBearing(FT_Face fontFace, char letter);
  void CreateSurfaceForLetter(std::string name, FT_Face fontFace, int r, int g, int b);
  void DrawLettersToTextImage(int startLoc = 0);
  std::string _text;
  int _fontSize;
  bool _wordWrap = false;
  int _lettersToDraw;
  int _paddingL = 0, _paddingR = 0, _paddingT = 0; //,_paddingB = 0;
  int _alpha = 255;
  std::vector<std::shared_ptr<Image>> _letterImages;
  std::shared_ptr<Font> _font;
  std::shared_ptr<Image> _image;
  // We will keep the text within this space
  Point _textBounds = {0, 0};
  // The actual size of the text
  Point _textSize = {0, 0};
  sgColor _backgroundColor = {0, 0, 0, 0};
  // Where we will draw each letter in the text.
  std::vector<Point> _letterPoints;
  // For debugging
  friend class UIWidget;
  // For control of the text.
  friend class UIText;
};
} // namespace Supergoon
