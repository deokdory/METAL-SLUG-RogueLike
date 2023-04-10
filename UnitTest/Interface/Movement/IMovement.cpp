#include "stdafx.h"
#include "IMovement.h"

IMovement::IMovement(GameObject* object) : object(object) {}

void IMovement::update() {
  Vector3 move = {xSpeed, ySpeed, 0.f};
  object->move(move);

  auto& terrains = level->GetTerrains();
  auto& objects = level->GetObjects();

  for (auto ter : terrains) {
  }

  for (auto obj : objects) {
  }
}

void IMovement::moveLeft() { xSpeed -= accel; }

void IMovement::moveRight() { xSpeed += accel; }

void IMovement::jump() { ySpeed = jumpPower; }
