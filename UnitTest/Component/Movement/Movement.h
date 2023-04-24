#pragma once

class MovementSpeedBox
{
public:
  enum class Slot
  {
    LEFT, RIGHT, TOP, BOTTOM
  };

  MovementSpeedBox(class GameObject* object);
  ~MovementSpeedBox();

  void Update(float xSpeed, float ySpeed);
  void Render();

  const BoundingBox* GetBox(Slot slot);

private:
  // 스피드 확인 및 연산 위한 바운딩박스
  BoundingBox* speedBoxL = nullptr;
  BoundingBox* speedBoxR = nullptr;
  BoundingBox* speedBoxT = nullptr;
  BoundingBox* speedBoxB = nullptr;

  class GameObject* object;
};

class Movement
{
public:
  Movement(class GameObject* object);
  virtual ~Movement();

  virtual void Update();
  virtual void Render();
  virtual void GUI();

  virtual void MoveLeft();
  virtual void MoveRight();
  virtual void SlowDown();

  virtual void Jump();

protected:
  void collisionCheck();

protected:
  bool isFalling = false; // 떨어지고 있는가

  float ySpeed = 0; // 수직 속도
  float gravityOffset = 0; // 객체의 중력값 보정 ( 기본 중력값 + )
  float jumpPower = 2.5f; // 점프 세기

  float fallingSpeedMax = -10.f; // 수직 낙하 속도 한계값

  float xSpeed = 0; // 수평 속도
  float xSpeedMax = 4; // 수평 속도 한계값

  float accel = 0; // 상황별 가속도 보정 위함 
  float accelOrigin = 0.2f; // 기본 가속도 값

  class GameObject* object; // 움직일 객체
  MovementSpeedBox* speedBox; // 속도 기반 가변충돌체
};