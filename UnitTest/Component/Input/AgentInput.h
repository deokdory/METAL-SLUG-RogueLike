#pragma once

class AgentInput {
public:
  AgentInput(class Agent* agent);

  void Update();
  void GUI();

  void MoveLeft();
  void MoveRight();
  void SlowDown();
  void Stop();

  void JumpBegin();
  void Jumping();
  void JumpEnd();

  void Render();

  void SetLevel(class Level* level) { this->level = level; }

  void CollisionCheck();

  void SpeedBoxUpdate();
protected:
  class Agent* agent = nullptr;
  class Level* level = nullptr;

  class TextureRect* crosshair = nullptr;

  BoundingBox* xSpeedBoxL = nullptr;
  BoundingBox* xSpeedBoxR = nullptr;

  BoundingBox* ySpeedBoxT = nullptr;
  BoundingBox* ySpeedBoxB = nullptr;

  Vector3 agentSize;

  class Gun* mainGun = nullptr;
  class Gun* subGun = nullptr;

  double delta = 0.0;

  bool isFalling = false;

  float ySpeed = 0.0f;
  float gravity = 0.1f;
  float jumpPower = 2.5f;

  float fallingSpeedMax = -10.f;

  float xSpeedMax = 4;
  float xSpeed = 0.f;

  float accelOrigin = 0.2f;
  float accel = 0.f;

  bool isJumping = false;
  double jumpedTime = 0.f;
};