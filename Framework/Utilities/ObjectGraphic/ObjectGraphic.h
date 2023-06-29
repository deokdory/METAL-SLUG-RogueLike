#pragma once

#include "Geometries/TextureRect.h"
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

class ObjectGraphic {
public:
  enum Slot { NORMAL = 0, LOWER, UPPER }; // 슬롯 구분 (기본, 상체, 하체)
  enum class Type { TEXTURE, ANIMATION }; // 타입 구분 (텍스쳐, 애니메이션)

  ObjectGraphic(class GameObject* object);
  ~ObjectGraphic();

  void Update();
  void Render();

  // 활성화 여부 변경
  void SetVisible(bool visible, Type type, Slot slot = Slot::NORMAL);

  // 지오메트리 초기화
  bool InitTexture(std::wstring path, Slot slot = Slot::NORMAL);
  bool InitAnimation(Animator* animator, Slot slot = Slot::NORMAL);

  // 지오메트리 삭제
  void DeleteGraphic(Type type, Slot slot);

  // 애니메이션 관련 기능
  void SetCurrentAnimation(std::wstring name, Slot slot = Slot::NORMAL);
  void SetCurrentFrame(UINT index, Slot slot = Slot::NORMAL);
  bool IsAnimationFinish(Slot slot = Slot::NORMAL);

  // 지오메트리 중심점 설정
  void SetAnchorPoint(AnchorPoint anchorPoint) { this->anchorPoint = anchorPoint; }

  // UV 설정
  void SetUV(Vector2 startUV, Vector2 endUV, Slot slot = Slot::NORMAL);
  
  // 회전
  void AddRotation(float rotation, Type type, Slot slot = Slot::NORMAL);

  // 페이드아웃
  void FadeOut(float duration, Type type, Slot slot = Slot::NORMAL);

  // 애니메이터 
  // Animator* GetAnimator(Slot slot = Slot::NORMAL);

protected:
  class GameObject* object; // 그래픽 컴포넌트의 주체
  AnchorPoint anchorPoint = AnchorPoint::MID_BOT;

  bool texVisible[3]; // 텍스쳐 지오메트리 활성 여부
  bool texFading[3] = {}; // 텍스쳐 지오메트리 투명도 페이드 중인지
  float texFadeSpeed[3] = {};

  std::vector<TextureRect*> texRects;

  bool animVisible[3]; // 애니메이션 지오메트리 활성 여부
  bool animFading[3] = {}; // 애니메이션 지오메트리 투명도 페이드 중인지
  float animFadeSpeed[3] = {};

  std::vector<AnimationRect*> animRects; // 애니메이션 렉트
  std::vector<Animator*> animators; // 애니메이터
};