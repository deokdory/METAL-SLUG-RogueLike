#include "stdafx.h"
#include "IPlayerMovement.h"

IPlayerMovement::IPlayerMovement(GameObject* object) : IMovement(object) {}

void IPlayerMovement::update() {

  if (Keyboard::Get()->Press('A') && !Keyboard::Get()->Press('D')) {
    moveLeft();
  } else if (Keyboard::Get()->Press('D') && !Keyboard::Get()->Press('A')) {
    moveRight();
  }

  if (Keyboard::Get()->Down(VK_SPACE)) {
    jump();
  }
  __super::update();
}
    


