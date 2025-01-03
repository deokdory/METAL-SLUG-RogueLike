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
  // ���ǵ� Ȯ�� �� ���� ���� �ٿ���ڽ�
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

  // ���� ����
  virtual void Falling();

  virtual void MoveLeft();
  virtual void MoveRight();
  virtual void SlowDown();

  virtual void Jump();
  virtual void DropDown();

  void Stop();

  // ���ӵ� ����
  virtual void UpdateAccel();

  void SetIsDirectingDown(bool isDirectingDown = true) { this->isDirectingDown = isDirectingDown; }
  void SetIsDirectingUp(bool isDirectingUp = true) { this->isDirectingUp = isDirectingUp; }

  bool GetIsFalling() { return isFalling; }

  void SetAccel(float accel) { this->accelOrigin = accel; }

  float GetXSpeed() { return xSpeed; }
  float GetYSpeed() { return ySpeed; }

  void SetXSpeedMax(float xSpeedMax) { this->xSpeedMaxOrigin = xSpeedMax; }

  float GetXSpeedOrigin() { return xSpeedOrigin; }
  float GetYSpeedOrigin() { return ySpeedOrigin; }

  float GetGravityOffset() { return gravityOffset; }
  float GetFallingSpeedMax() { return fallingSpeedMax; }

  Terrain* GetLastStanded() { return lastStanded; }

protected:
  virtual void terrainCollisionCheck();
  virtual void terrainCollisionCheck(std::vector<Terrain*>& terrains); // ��, �Ʒ�, �翷�� �浹�� ������ �ִ���,
                                        // �ִٸ� ���� ����� ������ � ������ üũ

  virtual void interaction(); // �浹�� �� ��ü����� ��ȣ�ۿ��� ����

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

  bool isFalling = false; // �������� �ִ°�
  bool isDropping = false;
  
  bool isDirectingUp = false;   // ���� ���ϴ°�
  bool isDirectingDown = false; // �Ʒ��� ���ϴ°�

  float ySpeed = 0; // ���� �ӵ�
  float ySpeedOrigin = 0;
  float gravityOffset = 0; // ��ü�� �߷°� ���� ( �⺻ �߷°� + )
  float jumpPower = 5.f; // ���� ����

  float fallingSpeedMax = -20.f; // ���� ���� �ӵ� ����

  float xSpeed = 0; // ���� �ӵ�
  float xSpeedOrigin = 0; // ���� ���� �ӵ�
  float xSpeedMaxOrigin = 5; // ���� �ִ� ���� �ӵ�
  float xSpeedMax = xSpeedMaxOrigin; // ���� �ӵ� ����

  float accel = 0; // ��Ȳ�� ���ӵ� ���� ���� 
  float accelOrigin = 0.3f; // �⺻ ���ӵ� ��

  class GameObject* object; // ������ ��ü
  MovementSpeedBox* speedBox; // �ӵ� ��� �����浹ü
};