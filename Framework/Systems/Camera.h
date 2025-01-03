#pragma once

class Camera : public SingletonBase<Camera> {
 public:
  friend class SingletonBase<Camera>;

  void Update();
  void Render();

  void UpdateView();

  void SetPosition(Vector3 position);

  void UnProjection(Vector3* out, Vector3 source, Matrix world);

  const Vector3 GetPosition() { return position; }

 private:
  Camera();
  ~Camera();

 private:
  VPBuffer* vpb = nullptr;
  Matrix view, proj, prevView;

  Vector3 position = Values::ZeroVec3;
  float cameraSpeed = 100.0f;

  float viewAdjust = 0.0f;
};