#include "stdafx.h"
#include "Character.h"

Character::Character(Vector3 position, Vector3 size) 
: GameObject(position, size) {}

Character::~Character() {}

void Character::update() { __super::update(); }

void Character::render() { __super::render(); }
