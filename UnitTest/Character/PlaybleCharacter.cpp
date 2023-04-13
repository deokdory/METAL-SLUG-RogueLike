#include "stdafx.h"
#include "PlaybleCharacter.h"

Agent::Agent(Vector3 position, Vector3 size) 
: Character(position, size) {
  
  movement = new IPlayerMovement(this);

  collision->InitializeBase();
  collision->InitializeBottom();
  collision->InitializeTop();
}

Agent::~Agent() {}

void Agent::update() {
  movement->update();
  graphic->update();
  collision->update();
}

void Agent::render() {
  Camera::Get()->SetPosition(position);

  movement->render();
  graphic->render();
  collision->render();
}
