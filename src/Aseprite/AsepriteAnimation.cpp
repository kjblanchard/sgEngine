#include "SupergoonEngine/log.h"
#include <SDL3/SDL.h>
#include <Supergoon/Aseprite/AsepriteAnimation.hpp>
#include <Supergoon/Content/AsepriteDocument.hpp>
#include <Supergoon/Content/ContentRegistry.hpp>
#include <Supergoon/Log.hpp>

using namespace Supergoon;

AsepriteAnimation::AsepriteAnimation(std::string n) : _animNum(0), _frame(0), _nextFrame(0), _frameTime(0), _aseDocument(nullptr) {
  _filePath = n;
  Load();
}

std::string AsepriteAnimation::Filename() {
  return std::string(SDL_GetBasePath()) + "assets/img/" + _aseDocument->meta.image;
}

void AsepriteAnimation::Load() {
  _aseDocument = ContentRegistry::CreateContent<AsepriteDocument>(std::string(SDL_GetBasePath()) + "assets/aseprite/" + _filePath + ".json");
  _aseDocument->Load();
  UpdateRect();
}

void AsepriteAnimation::UpdateAnimation(double d) {
  if (_repeats == 0) {
    // return false;
    return;
  }
  auto justFinished = false;
  _frameTime += d;
  auto frameData = _aseDocument->frames[_frame];
  auto animData = _aseDocument->meta.frameTags[_animNum];
  auto progressed = false;
  // use a while loop incase the deltat time is long
  while (_frameTime >= frameData.duration) {
    progressed = true;
    _frameTime -= frameData.duration;
    if (animData.direction == "pingpong") {
      if (_reverse) {
        _nextFrame = _frame - 1;
        if (_nextFrame < animData.from) {
          if (_repeats != -1) {
            --_repeats;
          }
          // _repeats = _repeats == -1 ? -1 : --_repeats;
          _nextFrame = animData.from + 1;
          justFinished = true;
          _reverse = false;
        }
      } else {
        _nextFrame = _frame + 1;
        if (_nextFrame > animData.to) {
          if (_repeats != -1) {
            --_repeats;
          }
          // _repeats = _repeats == -1 ? -1 : --_repeats;
          _nextFrame = animData.to - 1;
          justFinished = true;
          _reverse = true;
        }
      }
    } else {
      if (animData.direction == "forward") {
        // If the next frame is longer than the end, loop to the beginning, else increment it
        _nextFrame = (_frame + 1 > animData.to) ? animData.from : _frame + 1;
        // If this would cause us to loop to the beginning, we should set just finished and decrement repeats
        if (_nextFrame == animData.from) {
          _repeats = _repeats == -1 ? -1 : _repeats - 1;
          justFinished = true;
        }
      } else if (animData.direction == "reverse") {
        _nextFrame = (_frame - 1 < animData.from) ? animData.to : _frame - 1;
        if (_nextFrame == animData.to) {
          _repeats = _repeats == -1 ? -1 : _repeats - 1;
          justFinished = true;
        }
      }
    }
    if (justFinished && OnAnimationEnd) {
      OnAnimationEnd(this, animData.name);
    }
    // We should only update the rect, if we have any repeats left.
    if (_repeats == 0) {
      // return false;
      return;
    }
    _frame = _nextFrame;
    frameData = _aseDocument->frames[_frame];
    UpdateRect();
    sgLogDebug("Animation progressed = %d ", progressed);
    // return progressed;
  }
}

void AsepriteAnimation::PlayAnimation(std::string a) {
  for (size_t i = 0; i < _aseDocument->meta.frameTags.size(); i++) {
    auto &anim = _aseDocument->meta.frameTags[i];
    if (anim.name == a) {
      _animNum = i;
      _frame = anim.from;
      _frameTime = 0;
      _repeats = anim.repeat;
      UpdateRect();
      return;
    }
  }
  sgLogError("Could not find animation for %s", a.c_str());
}
void AsepriteAnimation::UpdateRect() {
  _rect.X = _aseDocument->frames[_frame].frame.x;
  _rect.Y = _aseDocument->frames[_frame].frame.y;
  _rect.W = _aseDocument->frames[_frame].frame.w;
  _rect.H = _aseDocument->frames[_frame].frame.h;
}

RectangleF &AsepriteAnimation::FrameCoords() {
  return _rect;
}
