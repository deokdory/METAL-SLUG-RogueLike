#include "stdafx.h"
#include "Character.h"

Character::Character(Vector3 position, Vector3 size) 
: GameObject(position, size) 
{
  SetAnchorPoint(AnchorPoint::MID_BOT);

  objectType = Type::CHARACTER;
  hp = maxHP;

  //collision->InitializeBase();
  //collision->InitializeBottom();
  //collision->InitializeTop();
}

Character::~Character() {}

void Character::Update() 
{ 
  __super::Update(); 
}

void Character::Render() 
{
  __super::Render(); 
}

void Character::Damaged(float damage)
{
  if (damage < 0) std::cout << "damage�� 0���� ����" << std::endl;
  this->hp -= damage;
}

void Character::Healed(float heal)
{
  if (heal > 0) std::cout << "heal�� 0���� ����" << std::endl;
  this->hp += heal;
}
