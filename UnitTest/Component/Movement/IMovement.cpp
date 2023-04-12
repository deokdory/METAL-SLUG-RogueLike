#include "stdafx.h"
#include "IMovement.h"

IMovement::IMovement(GameObject* object) : object(object) {}

void IMovement::update() {
  auto& state = object->GetState();

  if (isFalling) state = ObjState::FALLING;

  delta = Time::Get()->GetTimerDelta("game");
  accel = accelOrigin;

  switch (state) {
    case ObjState::FALLING:
      accel /= 2;
      break;

    default:
      break;
  }

    CollisionCheck();

  if (isFalling) {
    state = ObjState::FALLING;
    if (ySpeed > fallingSpeedMax)
      ySpeed -= gravity;
    else
      ySpeed = fallingSpeedMax;
  } else {
    ySpeed = 0;
    if (xSpeed == 0) {
      state = ObjState::IDLE;
    } else {
      state = ObjState::RUNNING;
    }
  }

  Vector3 move = {xSpeed, ySpeed, 0.f};
  object->move(move * delta);
}

void IMovement::moveLeft() {
  auto& state = object->GetState();
  if (state != ObjState::FALLING) state = ObjState::RUNNING;

  auto& terrains = level->GetTerrains();
  auto& objects = level->GetObjects();

  if (xSpeed > -xSpeedMax) {
    if (xSpeed > 0) SlowDown();
    xSpeed -= accel;
  } else
    xSpeed = -xSpeedMax;
}

void IMovement::moveRight() {
  auto& state = object->GetState();
  if (state != ObjState::FALLING) state = ObjState::RUNNING;

  auto& terrains = level->GetTerrains();
  auto& objects = level->GetObjects();

  if (xSpeed < xSpeedMax) {
    if (xSpeed < 0) SlowDown();
    xSpeed += accel;
  } else
    xSpeed = xSpeedMax;
}

void IMovement::SlowDown() {
  auto& state = object->GetState();
  if (state != ObjState::FALLING) state = ObjState::RUNNING; 

  if (xSpeed > 0.5f)
    xSpeed -= accel;
  else if (xSpeed < -0.5f)
    xSpeed += accel;
  else {
    state = ObjState::IDLE;
    xSpeed = 0.f;
  }
}

void IMovement::Stop() {
  auto& state = object->GetState();
  state = ObjState::IDLE;
  xSpeed = 0.f;
}

void IMovement::jump() {}

void IMovement::render() {}

void IMovement::CollisionCheck() {
  isFalling = true;

  auto& terrains = level->GetTerrains();

  auto bottom = object->GetCollision()->GetBottom();
  auto top = object->GetCollision()->GetTop();
  auto base = object->GetCollision()->GetBase();

  auto objPos = object->getPosition();
  auto objSize = object->getSize();

  Vector3 terrPos;
  Vector3 terrSize;

  BoundingBox *terrTop, *terrBottom, *terrBase;
  for (auto terr : terrains) {
    terrTop = terr->GetCollision()->GetTop();
    terrBase = terr->GetCollision()->GetBase();
    terrBottom = terr->GetCollision()->GetBottom();

    terrPos = terr->getPosition();
    terrSize = terr->getSize();

    if (ySpeed <= 0) {
      if (BoundingBox::AABB(bottom, terrTop)) {
        isFalling = false;

        float depth = (terrPos.y + terrSize.y / 2) - (objPos.y - objSize.y / 2);
        if (depth > 0) {
          object->move({0, depth, 0});
        }
      }
    }

    if (ySpeed >= 0) {
      if (BoundingBox::AABB(top, terrBottom)) {
        ySpeed = 0;
      }
    }

    if (BoundingBox::AABB(base, terrBase) == true) {
      if (objPos.x < terrPos.x) {
        float depth = (objPos.x + objSize.x / 2) - (terrPos.x - terrSize.x / 2);
        object->move({-depth, 0, 0});
        if (xSpeed > 0) xSpeed = 0;
      } else if (objPos.x > terrPos.x) {
        float depth = (terrPos.x + terrSize.x / 2) - (objPos.x - objSize.x / 2);
        object->move({depth, 0, 0});
        if (xSpeed < 0) xSpeed = 0;
      }
    }
    
    
    //if (BoundingBox::AABB(base, terrBase)) {
    //  auto objPos = object->getPosition();
    //  auto objSize = object->getSize();
    //
    //  auto terrPos = terr->getPosition();
    //  auto terrSize = terr->getSize();
    //
    //  float Rdepth = (objPos.x + objSize.x / 2) - (terrPos.x - terrSize.x / 2);
    //  float Ldepth = (objPos.x - objSize.x / 2) - (terrPos.x - terrSize.x / 2);
    //
    //  if (xSpeed > 0.5 && Rdepth > 0) {
    //    object->move({-Rdepth, 0, 0});
    //  } else if (xSpeed < 0.5 && Ldepth > 0)
    //    object->move({Ldepth, 0, 0});
    //}
  }
}
