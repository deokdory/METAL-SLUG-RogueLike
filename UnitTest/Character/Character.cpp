#include "stdafx.h"
#include "Character.h"

Character::Character(Vector3 position, Vector3 size) 
: GameObject(position, size) {

  movement = new IMovement(this);
}

Character::~Character() { SAFE_DELETE(movement); }

void Character::update() { 
  movement->update();
  __super::update(); 
}

void Character::render() {
  movement->render();
  __super::render(); 
}
