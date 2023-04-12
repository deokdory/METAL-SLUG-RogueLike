#pragma once
class IGraphic {
 public:
  IGraphic(class GameObject* object);
  virtual ~IGraphic();

  virtual void update() = 0;
  virtual void render() = 0;

  virtual void getAnimator(class Animator** animator) { return; }

  protected:
  class GameObject* object = nullptr;
};

class AnimatedGraphic : public IGraphic {
 public:
  AnimatedGraphic(class GameObject* object, class Animator* animator);
  ~AnimatedGraphic();

  virtual void update();
  virtual void render();

  virtual void getAnimator(class Animator** animator);

  private:
  class AnimationRect* animRect = nullptr;
  class Animator* animator = nullptr;
};

class TexturedGraphic : public IGraphic {
 public:
  TexturedGraphic(class GameObject* object, std::wstring path);
  ~TexturedGraphic();

  virtual void update();
  virtual void render();

 private:
  class TextureRect* textureRect = nullptr;
};