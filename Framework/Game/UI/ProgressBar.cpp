#include "Framework.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar(Vector3 position, Vector3 size, float rotation,
                         Color color, FillType type) {

  Init(position, size, rotation, color, type);
}

ProgressBar::ProgressBar(Vector3 position, Vector3 size, float rotation,
                         std::wstring path, FillType type) {

  Init(position, size, rotation, path, type);

  pb = new ProgressBuffer(type);
}

ProgressBar::ProgressBar(Vector3 position, Vector3 size, float rotation,
                         FillType type) {

  Init(position, size, rotation, type);
}

ProgressBar::~ProgressBar() { SAFE_DELETE(pb); }

void ProgressBar::Update() {
  UI::Update();
}

void ProgressBar::Render() {

  if (pb) pb->SetPSBuffer(2);
  UI::Render();

}

void ProgressBar::UpdateProgressBar(float percent) {

  this->percent = percent;
  
  if (!pb) {
    Vector3 changeSize = originSize;
    switch (type) {
      case UI::NONE: {
        changeSize.x *= percent;
        changeSize.y *= percent;
        break;
      }
      case UI::LEFT_TO_RIGHT:
      case UI::RIGHT_TO_LEFT: {
        changeSize.x *= percent;
        break;
      }
      case UI::UP_TO_DOWN:
      case UI::DOWN_TO_UP: {
        changeSize.y *= percent;
        break;
      }
      default:
        break;
    }
    size = changeSize;
  }
  else
  {
    pb->UpdateProgressPercent(percent);
  }
}
