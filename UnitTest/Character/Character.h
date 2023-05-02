#pragma once
#include "Game/GameObject.h"

class Character : public GameObject {
 public:
  Character(Vector3 position, Vector3 size);
  virtual ~Character();

  virtual void Update();
  virtual void Render();

  void Damaged(float damage);
  void Healed(float damage);

protected:
  float hp = 10.0f;

};