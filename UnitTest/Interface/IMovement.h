#pragma once

class IMovement {
 public:
  IMovement();
  
  virtual void update(GameObject& object,
                      std::vector<GameObject*>& objects) = 0;

 protected:

  float ySpeed = 0.0f;
  float gravity = 20.0f;

};