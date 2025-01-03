#pragma once

#include "Geometries/TextureRect.h"
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

class ObjectGraphic {
public:
  enum Slot { NORMAL = 0, LOWER, UPPER }; // ���� ���� (�⺻, ��ü, ��ü)
  enum class Type { TEXTURE, ANIMATION }; // Ÿ�� ���� (�ؽ���, �ִϸ��̼�)

  ObjectGraphic(class GameObject* object);
  ~ObjectGraphic();

  void Update();
  void Render();

  // Ȱ��ȭ ���� ����
  void SetVisible(bool visible, Type type, Slot slot = Slot::NORMAL);

  // ������Ʈ�� �ʱ�ȭ
  bool InitTexture(std::wstring path, Slot slot = Slot::NORMAL);
  bool InitAnimation(Animator* animator, Slot slot = Slot::NORMAL);

  // ������Ʈ�� ����
  void DeleteGraphic(Type type, Slot slot);

  // �ִϸ��̼� ���� ���
  void SetCurrentAnimation(std::wstring name, Slot slot = Slot::NORMAL);
  void SetCurrentFrame(UINT index, Slot slot = Slot::NORMAL);

  std::wstring GetCurrentAnimationName(Slot slot = Slot::NORMAL);
  bool GetIsAnimationFinish(Slot slot = Slot::NORMAL);

  // ������Ʈ�� �߽��� ����
  void SetAnchorPoint(AnchorPoint anchorPoint) { this->anchorPoint = anchorPoint; }

  // UV ����
  void SetUV(Vector2 startUV, Vector2 endUV, Slot slot = Slot::NORMAL);
  
  // ȸ��
  void AddRotation(float rotation, Type type, Slot slot = Slot::NORMAL);

  // ���̵�ƿ�
  void FadeOut(float duration, Type type, Slot slot = Slot::NORMAL);

  // �ִϸ����� 
  // Animator* GetAnimator(Slot slot = Slot::NORMAL);

protected:
  class GameObject* object; // �׷��� ������Ʈ�� ��ü
  AnchorPoint anchorPoint = AnchorPoint::MID_BOT;

  bool texVisible[3]; // �ؽ��� ������Ʈ�� Ȱ�� ����
  bool texFading[3] = {}; // �ؽ��� ������Ʈ�� ���� ���̵� ������
  float texFadeSpeed[3] = {};

  std::vector<TextureRect*> texRects;

  bool animVisible[3]; // �ִϸ��̼� ������Ʈ�� Ȱ�� ����
  bool animFading[3] = {}; // �ִϸ��̼� ������Ʈ�� ���� ���̵� ������
  float animFadeSpeed[3] = {};

  std::vector<AnimationRect*> animRects; // �ִϸ��̼� ��Ʈ
  std::vector<Animator*> animators; // �ִϸ�����
};