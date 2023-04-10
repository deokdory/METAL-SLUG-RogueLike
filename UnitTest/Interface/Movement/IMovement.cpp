#include "stdafx.h"
#include "IMovement.h"

IMovement::IMovement(GameObject* object) : object(object) {}

void IMovement::update() {

  Vector3 move = {xSpeed, ySpeed, 0.f};
  object->move(move);

  //auto* terrains = level->GetTerrains();
  auto& objects = level->GetObjects();

  //for (auto ter : terrains) {
  //}

  //for (auto obj : objects) {
  //
  //}
}

void IMovement::moveLeft() {
  if (xSpeed > -xSpeedMax) {
    if (xSpeed > 0) breaking();
    xSpeed -= accel;
  } else
    xSpeed = -xSpeedMax;
}

void IMovement::moveRight() {
  if (xSpeed < xSpeedMax) {
    if (xSpeed < 0) breaking();
    xSpeed += accel;
  } else
    xSpeed = xSpeedMax;
}

void IMovement::breaking() {
  if (xSpeed > 0.5f)
    xSpeed -= accel;
  else if (xSpeed < -0.5f)
    xSpeed += accel;
  else
    xSpeed = 0.f;
}

void IMovement::jump() { ySpeed = jumpPower; }
