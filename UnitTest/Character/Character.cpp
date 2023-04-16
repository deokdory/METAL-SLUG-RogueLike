#include "stdafx.h"
#include "Character.h"

Character::Character(Vector3 position, Vector3 size) 
: GameObject(position, size) {}

Character::~Character() { }

void Character::Update() { 
  __super::Update(); 
}

void Character::Render() {
  __super::Render(); 
}
