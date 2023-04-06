#include "stdafx.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size) : Character(position, size) {
  // Animator Init
  {
    Texture2D* srcTex = new Texture2D(TexturePath + L"Ye_Oldy_Knight_Guy.png");

    Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

    AnimationClip* Idle =
        new AnimationClip(L"Idle", srcTex, 4, Vector2(0, 0), Vector2(64, 19),
                          false, 1.0f / 3.0f);  // 16, 20

    AnimationClip* Run =
        new AnimationClip(L"Run", srcTex, 6, Vector2(0, 21), Vector2(96, 41),
                          false, 1.0f / 6.0f);  // 16, 21

    AnimationClip* Jump = new AnimationClip(L"Jump", srcTex, 1, Vector2(0, 42),
                                            Vector2(16, 63));  // 17, 22

    AnimationClip* Sword = new AnimationClip(
        L"Sword", srcTex, 1, Vector2(18, 44), Vector2(33, 63));  // 16, 20

    AnimationClip* Guard = new AnimationClip(
        L"Guard", srcTex, 1, Vector2(18, 114), Vector2(33, 133));  // 16 x 20

    AnimationClip* Hit = new AnimationClip(L"Hit", srcTex, 1, Vector2(64, 0),
                                           Vector2(85, 19));  // 22 x 20

    animator->AddAnimClip(Idle);
    animator->AddAnimClip(Run);
    animator->AddAnimClip(Jump);
    animator->AddAnimClip(Sword);
    animator->AddAnimClip(Guard);
    animator->AddAnimClip(Hit);

    animator->SetCurrentAnimClip(L"Idle");

    animRect->SetAnimator(animator);

    SAFE_DELETE(srcTex);
  }

  // Equip Init
  {
    shield.rect = new TextureRect(Vector3(position.x + size.x / 2, position.y - size.y / 2 / 2, 0),
                             Vector3(37.5f, 60, 0), 0.0f, TexturePath + L"shield.png");
    shield.collision = new BoundingBox();

    shield.collision->Init(Color(0, 1, 0, 0.3f));

    sword.rect = new TextureRect(
        Vector3(position.x + size.x / 2, position.y - size.y / 2 / 2, 0),
        Vector3(37.5f, 75, 0), 0.0f, TexturePath + L"sword.png");
    sword.rect->SetAnchorPoint(7);
    sword.collision = new BoundingBox();
    sword.collision->Init(Color(0, 1, 0, 0.3f));
    sword.rect->SetIsFliped();
  }

  // Collision Init
  { 
    foot = new BoundingBox();
    head = new BoundingBox();

    foot->Init(Color(0, 0, 1, 0.3f));
    head->Init(Color(0, 1, 0, 0.3f));
  }
}

Player::~Player() {
  SAFE_DELETE(head);
  SAFE_DELETE(foot);
  SAFE_DELETE(sword.rect);
  SAFE_DELETE(sword.collision);
  SAFE_DELETE(shield.rect);
  SAFE_DELETE(shield.collision);
}

void Player::Update() {
  collisionHeight = animRect->GetSize().y * 0.1f;

  globalSpeed = GameManager::Get()->GetGlobalSpeed();

  animator->Update();
  animRect->Update();

  Vector3 pos = animRect->GetPosition();

  Vector3 size, collisionSize;
  size = collisionSize = animRect->GetSize();
  collisionSize.y /= 10;

  Vector3* localPos = animRect->GetVerticesLocalPosition();

  
  foot->UpdateCollisionData(animRect->GetWorld(), localPos);
  head->UpdateCollisionData(animRect->GetWorld(), localPos);

  auto footCollisionPos = Vector3(0, -size.y / 2 + collisionSize.y / 2, 0);
  auto headCollisionPos = Vector3(0, size.y / 2 - collisionSize.y / 2, 0);

  foot->Update(collisionSize, footCollisionPos);
  head->Update(collisionSize, headCollisionPos);

  Vector3 equipPos;
  if (animRect->IsFliped()) {
    equipPos = Vector3(pos.x - size.x / 2.5f, pos.y - size.y / 4, 0);
    shield.rect->SetIsFliped();
    sword.rect->SetIsFliped(false);
  } else {
    equipPos = Vector3(pos.x + size.x / 2.5f, pos.y - size.y / 4, 0);
    shield.rect->SetIsFliped(false);
    sword.rect->SetIsFliped();
  }
  shield.rect->SetPosition(equipPos);
  shield.rect->Update();

  sword.rect->SetPosition(equipPos);
  sword.rect->Update();

  // 傍拜 or 规绢 贸府
  if (bGuarding) {
    auto rect = shield.rect;
    auto collision = shield.collision;

    collision->UpdateCollisionData(rect->GetWorld(),
                                   rect->GetVerticesLocalPosition());
    collision->Update(rect->GetSize());
  } else if (bAttacking) {
    auto rect = sword.rect;
    auto collision = sword.collision;
    collision->UpdateCollisionData(rect->GetWorld(),
                                   rect->GetVerticesLocalPosition());
    collision->Update(rect->GetSize(), Values::ZeroVec3, rect->GetRotation());
    if (timer < 0.25f) {
      timer += Time::Delta();
      if (animRect->IsFliped()) {
        rect->SetRotation(100.f * (timer * 4));
      } else {
        rect->SetRotation(-100.f * (timer * 4));
      }
    } else {
      bAttacking = false;
    }
  }

  // 吝仿 贸府
  if (isOnGround) {
    ySpeed = 0.0f;
  } else {
    Falling();
  }
  animRect->Move(Vector2(0, ySpeed));
}

void Player::Render() {
  if (bAttacking) {
    sword.Render();
  }

  animRect->Render();
  foot->Render();
  head->Render();

  if (bGuarding) {
    shield.Render();
  }
}

void Player::Idle() { 
  if (bAttacking || bGuarding || isOnGround == false) return;
 animator->SetCurrentAnimClip(L"Idle");
}

void Player::MoveLeft() { 
  if (bAttacking || bGuarding) return;

  animRect->SetIsFliped();
  if(isOnGround) animator->SetCurrentAnimClip(L"Run");
  Vector2 move = Vector2(-moveSpeed, 0.0f) /* globalSpeed */ * Time::Delta();
  animRect->Move(move);
}

void Player::MoveRight() {
  if (bAttacking || bGuarding) return;

  animRect->SetIsFliped(false);
  if (isOnGround) animator->SetCurrentAnimClip(L"Run");
  Vector2 move = Vector2(moveSpeed, 0.0f) /* globalSpeed */ * Time::Delta();
  animRect->Move(move);
}

void Player::Jump() {
  if (bAttacking || isOnGround == false) return;

  ySpeed = 7.f;
  isOnGround = false;
  animRect->Move(Vector2(0, ySpeed));
}

void Player::Sword() {
  if (bAttacking || bGuarding || isOnGround == false) return;

  sword.rect->SetRotation(0);
  bAttacking = true;
  animator->SetCurrentAnimClip(L"Sword");
  timer = 0.0f;
}

void Player::Guard(bool bGuarding) {
  if (bAttacking || isOnGround == false) return;
  this->bGuarding = bGuarding;

  if (bGuarding) {
    animator->SetCurrentAnimClip(L"Guard");
  }
}

void Player::Falling() {
  animator->SetCurrentAnimClip(L"Jump");
  ySpeed -= gravity * Time::Delta();
}
