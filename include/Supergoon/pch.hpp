#pragma once
// sdl
#include <SDL3/SDL.h>
// 3rd party
#include <SupergoonEngine/nlohmann/json.hpp>
// std
#include <algorithm>
#include <fstream>
#include <istream>
#include <memory>
#include <optional>
#include <string>
// engine
#include <Supergoon/Aseprite/AsepriteAnimation.hpp>
#include <Supergoon/Content/AsepriteDocument.hpp>
#include <Supergoon/Content/Content.hpp>
#include <Supergoon/Content/ContentRegistry.hpp>
#include <Supergoon/Content/Font.hpp>
#include <Supergoon/Content/Image.hpp>
#include <Supergoon/Content/Sfx.hpp>
#include <Supergoon/Content/Text.hpp>
#include <Supergoon/ECS/Components/AnimationComponent.hpp>
#include <Supergoon/ECS/Components/CameraComponent.hpp>
#include <Supergoon/ECS/Components/GameStateComponent.hpp>
#include <Supergoon/ECS/Components/ImageComponent.hpp>
#include <Supergoon/ECS/Components/LocationComponent.hpp>
#include <Supergoon/ECS/Components/SolidComponent.hpp>
#include <Supergoon/ECS/Gameobject.hpp>
#include <Supergoon/Events.hpp>
#include <Supergoon/Game.hpp>
#include <Supergoon/Graphics/Graphics.hpp>
#include <Supergoon/Input.hpp>
#include <Supergoon/Interfaces/Loader.hpp>
#include <Supergoon/Interfaces/Unloader.hpp>
#include <Supergoon/Log.hpp>
#include <Supergoon/Physics/AABB.hpp>
#include <Supergoon/Physics/Directions.hpp>
#include <Supergoon/Physics/Physics.hpp>
#include <Supergoon/Primitives/Color.hpp>
#include <Supergoon/Primitives/Rectangle.hpp>
#include <Supergoon/Primitives/Vector2.hpp>
#include <Supergoon/Sound.hpp>
#include <Supergoon/Tween/Sequence.hpp>
#include <Supergoon/Tween/Tween.hpp>
#include <Supergoon/Video.hpp>
#include <Supergoon/World/Level.hpp>
#include <Supergoon/World/TiledMap.hpp>
#include <Supergoon/World/World.hpp>

#ifdef experimentalPCH

#include <Supergoon/UI/Panel.hpp>
#include <Supergoon/UI/UI.hpp>
#include <Supergoon/UI/UIHorizontalLayoutGroup.hpp>
#include <Supergoon/UI/UIImage.hpp>
#include <Supergoon/UI/UIObject.hpp>
#include <Supergoon/UI/UIObjectAnimator.hpp>
#include <Supergoon/UI/UIText.hpp>
#endif

#ifdef imgui
#include <SupergoonEngine/imgui/imgui.h>

#include <Supergoon/Widgets/ContentWidget.hpp>
#include <Supergoon/Widgets/Game.hpp>
#include <Supergoon/Widgets/Global.hpp>
#include <Supergoon/Widgets/SoundWidget.hpp>
#include <Supergoon/Widgets/Widgets.hpp>
#endif
