#pragma once

enum slot { LOWER = 1, UPPER };
enum IGraphicType { TEXTURE_GRAPHIC = 0, ANIMATION_GRAPHIC, AGENT_GRAPHIC };

class IGraphic {
 public:
  IGraphic(class GameObject* object);
  virtual ~IGraphic();

  virtual void update() = 0;
  virtual void render() = 0;

  virtual void setResource(class Animator* animator, UINT slot = 0) {}
  virtual void setResource(std::wstring path) {}

  protected:
  class GameObject* object = nullptr;
};

class AnimatedGraphic : public IGraphic {
 public:
  AnimatedGraphic(class GameObject* object);
  ~AnimatedGraphic();

  virtual void update();
  virtual void render();

  virtual void setResource(class Animator* animator, UINT slot = 0);

 private:
  class AnimationRect* animRect = nullptr;
  class Animator* animator = nullptr;
};

class TexturedGraphic : public IGraphic {
 public:
  TexturedGraphic(class GameObject* object);
  ~TexturedGraphic();

  virtual void update();
  virtual void render();

  virtual void setResource(std::wstring path);

 private:
  class TextureRect* textureRect = nullptr;
};

class AgentGraphic : public IGraphic {
 public:
  AgentGraphic(class GameObject* object);
  ~AgentGraphic();

  virtual void update();
  virtual void render();

  virtual void setResource(class Animator* animator, UINT slot = 0);

  private:
  class AnimationRect* lowerRect = nullptr;
  class AnimationRect* upperRect = nullptr;

  class Animator* lowerAnim = nullptr;
  class Animator* upperAnim = nullptr;
};