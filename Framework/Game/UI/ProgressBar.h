#pragma once
#include "Utilities/UI.h"

class ProgressBuffer : public ShaderBuffer {
 public:

 public:
  ProgressBuffer(UINT type) : ShaderBuffer(&data, sizeof(data)) {
    data.percent = 1.0f;
    data.type = type;
  }
  void UpdateProgressPercent(float percent) { data.percent = percent; }


 private:
  struct Data {
    float percent;
    UINT type;
    Vector2 dummy;
  } data;
};

class ProgressBar : public UI {
 public:
  ProgressBar(Vector3 position, Vector3 size, float rotation, Color color,
              FillType type = NONE);
  ProgressBar(Vector3 position, Vector3 size, float rotation, std::wstring path,
              FillType type = NONE);
  ProgressBar(Vector3 position, Vector3 size, float rotation,
              FillType type = NONE);

  virtual ~ProgressBar() override;

  virtual void Update() override;
  virtual void Render() override;

  void UpdateProgressBar(float percent);

 protected:
  float percent = 1.0f;

 private:
  ProgressBuffer* pb = nullptr;
};
