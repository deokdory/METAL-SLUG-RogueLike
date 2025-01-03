#pragma once

class Values {
 public:
  const static float PI;

  const static Vector3 ZeroVec3;
  const static Vector3 OneVec3;
  const static Vector3 LeftVec;
  const static Vector3 RightVec;
  const static Vector3 UpVec;
  const static Vector3 DownVec;
  const static Vector3 FwdVec;
  const static Vector3 ScreenSize;
  const static Vector3 CenterOfScreen;

  const static Vector2 ZeroVec2;
  const static Vector2 OneVec2;
  const static Vector2 uvLT;
  const static Vector2 uvLB;
  const static Vector2 uvRT;
  const static Vector2 uvRB;

  const static Color Red;
  const static Color Green;
  const static Color Blue;
  const static Color Magenta;
  const static Color Black;
  const static Color White;
  const static Color ClearColor;

  const static Matrix Identity;

  static Direction GetDirectionOtherSide(Direction direction)
  {
    switch (direction)
    {
    case Direction::UP: return Direction::DOWN;
      break;

    case Direction::DOWN: return Direction::UP;
      break;

    case Direction::LEFT: return Direction::RIGHT;
      break;

    case Direction::RIGHT: return Direction::LEFT;
      break;

    case Direction::NONE:
    default: return Direction::NONE;
      break;
    }
  }
}; 

class DXMath {
 public:
  static Matrix Translation(const Vector3 position) {
    Matrix m;
    D3DXMatrixTranslation(&m, position.x, position.y, position.z);
    return m;
  }

  static Matrix TranslationX(const float& x) {
    return Translation(Vector3(x, 0, 0));
  }

  static Matrix TranslationY(const float& y) {
    return Translation(Vector3(0, y, 0));
  }

  static Matrix Scaling(const Vector3 size) {
    Matrix m;
    D3DXMatrixScaling(&m, size.x, size.y, size.z);
    return m;
  }

  static Matrix ScalingX(const float& x) { return Scaling(Vector3(x, 1, 1)); }

  static Matrix ScalingY(const float& y) { return Scaling(Vector3(1, y, 1)); }

  static Matrix RotationInDegree(const float& rotation) {
    Matrix m;
    D3DXMatrixRotationZ(&m, (float)D3DXToRadian(rotation));
    return m;
  }

  static Matrix RotationInRadian(const float& rotation) {
    Matrix m;
    D3DXMatrixRotationZ(&m, rotation);
    return m;
  }

  static Vector3 GetDistance(Vector3 positionA, Vector3 positionB)
  {
    Vector3 distance = { 0,0,0 };

    distance.x = std::abs(positionA.x - positionB.x);
    distance.y = std::abs(positionA.y - positionB.y);

    return distance;
  }
};