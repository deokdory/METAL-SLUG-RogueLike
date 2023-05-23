#pragma once

class LevelEditor
{
public:
  LevelEditor();
  ~LevelEditor();

  void Init();
  void Update();
  void Render();
  void GUI();

  Vector3 GetTileCenterPosition(Vector3 position); // 현재 위치를 각 타일 기반 중앙 포지션으로 반환

private:
  void save();
  void load();

  std::vector<Room*> rooms;
};