#pragma once
class IGraphic {
 public:
  IGraphic(class GameObject* object);
  virtual ~IGraphic();

  virtual void update() = 0;
  virtual void render() = 0;

  virtual class Animator* getAnimator() { return nullptr; }

  virtual class Animator* getUpperAnimator() { return nullptr; }
  virtual class Animator* getLowerAnimator() { return nullptr; }

  protected:
  class GameObject* object = nullptr;
};

class AnimatedGraphic : public IGraphic {
 public:
  AnimatedGraphic(class GameObject* object, class Animator* animator);
  ~AnimatedGraphic();

  virtual void update();
  virtual void render();

  virtual class Animator* getAnimator() { return animator; }

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

class AgentGraphic : public IGraphic {
 public:
  AgentGraphic(class GameObject* object, class Animator* lowerAnim,
               class Animator* upperAnim);
  ~AgentGraphic();

  virtual void update();
  virtual void render();

  virtual class Animator* getLowerAnimator() { return lowerAnim; }
  virtual class Animator* getUpperAnimator() { return upperAnim; }

  private:
  class AnimationRect* lowerRect = nullptr;
  class AnimationRect* upperRect = nullptr;

  class Animator* lowerAnim = nullptr;
  class Animator* upperAnim = nullptr;
};