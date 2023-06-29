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

  BoundingBox* GetBox(Slot slot);

private:
  // 스피드 확인 및 연산 위한 바운딩박스
  BoundingBox* speedBoxL = nullptr;
  BoundingBox* speedBoxR = nullptr;
  BoundingBox* speedBoxT = nullptr;
  BoundingBox* speedBoxB = nullptr;

  class GameObject* object;
  AnchorPoint anchorPoint = AnchorPoint::MID_BOT;
};

class Movement
{
public:
  Movement(class GameObject* object);
  virtual ~Movement();

  virtual void Update();
  virtual void Render();
  virtual void GUI();

  // 낙하 설정
  virtual void Falling();

  virtual void MoveLeft();
  virtual void MoveRight();
  virtual void SlowDown();

  virtual void Jump();
  virtual void Drop();

  void Stop();

  // 가속도 설정
  virtual void UpdateAccel();

  void SetIsDirectingDown(bool isDirectingDown = true) { this->isDirectingDown = isDirectingDown; }
  void SetIsDirectingUp(bool isDirectingUp = true) { this->isDirectingUp = isDirectingUp; }

  bool GetIsFalling() { return isFalling; }

  void SetAccel(float accel) { this->accelOrigin = accel; }

  float GetXSpeed() { return xSpeed; }
  float GetYSpeed() { return ySpeed; }

  void SetXSpeedMax(float xSpeedMax) { this->xSpeedMax = xSpeedMax; }

  float GetXSpeedOrigin() { return xSpeedOrigin; }
  float GetYSpeedOrigin() { return ySpeedOrigin; }

  float GetGravityOffset() { return gravityOffset; }
  float GetFallingSpeedMax() { return fallingSpeedMax; }

protected:
  virtual void terrainCollisionCheck();
  virtual void terrainCollisionCheck(std::vector<Terrain*>& terrains); // 위, 아래, 양옆의 충돌한 지형이 있는지,
                                        // 있다면 가장 가까운 지형이 어떤 것인지 체크

  virtual void interaction(); // 충돌한 각 객체들과의 상호작용을 수행

protected:
  Terrain* nearestFootholder = nullptr;
  Terrain* nearestTerrainR   = nullptr;
  Terrain* nearestTerrainL   = nullptr;

  Terrain* nearestStair = nullptr;

  float nearestPositionX = 0.0f;
  float nearestPositionY = 0.0f;

  Terrain* standOn = nullptr;
  Terrain* lastStanded = nullptr;

  AnchorPoint anchorPoint = AnchorPoint::MID_BOT;

  bool isFalling = false; // 떨어지고 있는가
  bool isDropping = false;
  
  bool isDirectingUp = false;   // 위로 향하는가
  bool isDirectingDown = false; // 아래로 향하는가

  float ySpeed = 0; // 수직 속도
  float ySpeedOrigin = 0;
  float gravityOffset = 0; // 객체의 중력값 보정 ( 기본 중력값 + )
  float jumpPower = 5.f; // 점프 세기

  float fallingSpeedMax = -20.f; // 수직 낙하 속도 제한

  float xSpeed = 0; // 수평 속도
  float xSpeedOrigin = 0; // 원래 수평 속도
  float xSpeedMax = 5; // 수평 속도 제한

  float accel = 0; // 상황별 가속도 보정 위함 
  float accelOrigin = 0.3f; // 기본 가속도 값

  class GameObject* object; // 움직일 객체
  MovementSpeedBox* speedBox; // 속도 기반 가변충돌체
};