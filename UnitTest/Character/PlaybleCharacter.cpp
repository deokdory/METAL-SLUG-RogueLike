#include "stdafx.h"
#include "PlaybleCharacter.h"

PlaybleCharacter::PlaybleCharacter(Vector3 position, Vector3 size) 
: Character(position, size) {
  
  movement = new IPlayerMovement(this);
}

PlaybleCharacter::~PlaybleCharacter() {}
