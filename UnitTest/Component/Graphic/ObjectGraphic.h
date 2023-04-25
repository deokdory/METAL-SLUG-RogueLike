#pragma once

#include "Geometries/TextureRect.h"
#include "Utilities/Animator.h"
#include "Geometries/AnimationRect.h"

class ObjectGraphic {
public:
  enum class Slot { NORMAL, LOWER, UPPER };
  enum class Type { TEXTURE, ANIMATION };


  ObjectGraphic(class GameObject* object);
  ~ObjectGraphic();

  void Update();
  void Render();

  Vector3 GetRectPosition(Type type, Slot slot = Slot::NORMAL);
  Vector3 GetRectSize(Type type, Slot slot = Slot::NORMAL);
  Matrix GetRectWorld(Type type, Slot slot = Slot::NORMAL);

  bool InitTexture(std::wstring path, Slot slot = Slot::NORMAL);
  bool InitAnimation(Animator* animator, Slot slot = Slot::NORMAL);

  void DeleteGraphic(Type type, Slot slot);

  void SetCurrentAnimation(std::wstring name, Slot slot = Slot::NORMAL);
  void SetCurrentFrame(UINT index, Slot slot = Slot::NORMAL);

  void SetAnchorPoint(AnchorPoint anchor, Type type, Slot slot = Slot::NORMAL);

  Animator* GetAnimator(Slot slot = Slot::NORMAL);


protected:
  class GameObject* object;

  std::vector<TextureRect*> texRects = {};
  std::vector<AnimationRect*> animRects = {};
  std::vector<Animator*> animators = {};
};