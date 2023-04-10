#include "stdafx.h"
#include "Level.h"

Level::~Level() {
  for (auto bg : backgrounds) {
    SAFE_DELETE(bg);
  }
  for (auto deco : decos) {
    SAFE_DELETE(deco);
  }
  for (auto terr : terrains) {
    SAFE_DELETE(terr);
  }
  for (auto obj : objects) {
    SAFE_DELETE(obj);
  }
  backgrounds.clear();
  decos.clear();
  terrains.clear();
  objects.clear();
}
