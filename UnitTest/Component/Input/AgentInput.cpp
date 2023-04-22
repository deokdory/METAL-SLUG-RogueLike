#include "stdafx.h"
#include "AgentInput.h"

#include <Windows.h>

#include "Geometries/TextureRect.h"
#include "Level/Level.h"

#include "Component/Collision/Collision.h"
#include "Character/Agent.h"

#include "Component/Gun/Gun.h"

AgentInput::AgentInput(Agent* agent) :agent(agent)
{
  auto mousePos = Mouse::Get()->GetPosition() + Camera::Get()->GetPosition();

  crosshair = new TextureRect(mousePos, Vector3(72, 72, 0), 0.f, TexturePath + L"crosshair003.png");
  agentSize = agent->GetSize();

  Vector3 left, right, top, bottom;
  left = right = top = bottom = agent->GetPosition();

  left.x   -= agentSize.x / 2;
  right.x  += agentSize.x / 2;
  top.y    += agentSize.y / 2;
  bottom.y -= agentSize.y / 2;

  xSpeedBoxL = new BoundingBox(left, Values::ZeroVec3, agent->GetRotation(), Color(0, 1, 0, 0.25f));
  xSpeedBoxR = new BoundingBox(right, Values::ZeroVec3, agent->GetRotation(), Color(0, 1, 0, 0.25f));
  ySpeedBoxT = new BoundingBox(top, Values::ZeroVec3, agent->GetRotation(), Color(0, 1, 0, 0.25f));
  ySpeedBoxB = new BoundingBox(bottom, Values::ZeroVec3, agent->GetRotation(), Color(0, 1, 0, 0.25f));

  xSpeedBoxL->SetAnchorPoint(5);
  xSpeedBoxR->SetAnchorPoint(4);

  ySpeedBoxT->SetAnchorPoint(7);
  ySpeedBoxB->SetAnchorPoint(2);

  //mainGun = Gun::HeavyMachinegun();
}

void AgentInput::Update() {
  //delta = Time::Get()->GetTimerDelta("game");

  auto mousePos = Mouse::Get()->GetPosition() + Camera::Get()->GetPosition();
  mousePos.z = 0;

  crosshair->SetPosition(mousePos);
  crosshair->Update();
  {
    auto mouseDist = mousePos - agent->GetPosition();

    Vector3 agentAxisTop, agentAxisRight, agentAxisMouse;

    //D3DXVec3TransformNormal(&agentAxisTop, &Values::UpVec, &agent->GetGraphic()->GetWorld(IGraphic::Slot::UPPER));
    //D3DXVec3TransformNormal(&agentAxisRight, &Values::RightVec, &agent->GetGraphic()->GetWorld(IGraphic::Slot::UPPER));

    //D3DXVec3TransformNormal(&agentAxisMouse, &mouseDist, &agent->GetGraphic()->GetWorld(IGraphic::Slot::UPPER));

    //D3DXVec3Normalize(&agentAxisTop, &agentAxisTop);
    //D3DXVec3Normalize(&agentAxisRight, &agentAxisRight);
    D3DXVec3Normalize(&agentAxisMouse, &mouseDist);

    auto aimAngle = D3DXVec3Dot(&Values::UpVec, &agentAxisMouse);
    auto rightAngle = D3DXVec3Dot(&Values::RightVec, &agentAxisMouse);

    aimAngle = std::acos(aimAngle);
    aimAngle = D3DXToDegree(aimAngle);

    if (rightAngle < 0)
    {
      agent->SetFliped(true);
    }
    else agent->SetFliped(false);

    //std::cout << aimAngle << std::endl;
    if      (abs(aimAngle) < 10.f)  agent->GetGraphic()->SetCurrentFrame(9, IGraphic::Slot::UPPER);
    else if (abs(aimAngle) < 25.f)  agent->GetGraphic()->SetCurrentFrame(8, IGraphic::Slot::UPPER);
    else if (abs(aimAngle) < 35.f)  agent->GetGraphic()->SetCurrentFrame(7, IGraphic::Slot::UPPER);
    else if (abs(aimAngle) < 55.f)  agent->GetGraphic()->SetCurrentFrame(6, IGraphic::Slot::UPPER);
    else if (abs(aimAngle) < 90.f)  agent->GetGraphic()->SetCurrentFrame(5, IGraphic::Slot::UPPER);
    else if (abs(aimAngle) < 115.f) agent->GetGraphic()->SetCurrentFrame(4, IGraphic::Slot::UPPER);
    else if (abs(aimAngle) < 145.f) agent->GetGraphic()->SetCurrentFrame(3, IGraphic::Slot::UPPER);
    else if (abs(aimAngle) < 160.f) agent->GetGraphic()->SetCurrentFrame(2, IGraphic::Slot::UPPER);
    else if (abs(aimAngle) < 170.f) agent->GetGraphic()->SetCurrentFrame(1, IGraphic::Slot::UPPER);
    else if (abs(aimAngle) < 180.f) agent->GetGraphic()->SetCurrentFrame(0, IGraphic::Slot::UPPER);

    if (Mouse::Get()->Down(0))
    {
      level->PushObject(new Bullet(agent, Bullet::Side::PLAYER, agentAxisMouse));
      POINT point = { 0, 0 };

      GetCursorPos(&point);
      SetCursorPos(point.x, point.y - 7);
    }
  }
  agentSize = agent->GetSize();
  auto state = agent->GetState();

  accel = accelOrigin;

  if (Keyboard::Get()->Press('A') && !Keyboard::Get()->Press('D')) {
    MoveLeft();
  }
  else if (Keyboard::Get()->Press('D') && !Keyboard::Get()->Press('A')) {
    MoveRight();
  }
  else {
    SlowDown();
  }

  //if (Mouse::Get()->Down(VK_RBUTTON))
  //{
  //  if (state != Agent::State::SLIDING)
  //  {
  //    agent->GetGraphic()->SetCurrentAnimation(L"knife1_rifle", IGraphic::Slot::UPPER);
  //    state = Agent::State::MELEE_ATTACK;
  //  }
  //}

  if (Keyboard::Get()->Down(VK_SPACE)) JumpBegin();
  else if (Keyboard::Get()->Press(VK_SPACE)) Jumping();
  else JumpEnd();

  if (isFalling) {
    if (ySpeed > fallingSpeedMax) ySpeed -= gravity;

    if (ySpeed < 0)
      if (agent->GetGraphic()->GetAnimator(IGraphic::Slot::LOWER)->GetCurrentAnimClipName() == L"jumpBegin_run")
        agent->GetGraphic()->SetCurrentAnimation(L"jumpEnd_run", IGraphic::Slot::LOWER);
      else if (agent->GetGraphic()->GetAnimator(IGraphic::Slot::LOWER)->GetCurrentAnimClipName() == L"jumpBegin_stand")
        agent->GetGraphic()->SetCurrentAnimation(L"jumpEnd_stand", IGraphic::Slot::LOWER);
  }
  CollisionCheck();

  auto move = Vector3(xSpeed, ySpeed, 0);
  agent->Move(move);

  Vector3 leftPos, rightPos, topPos, bottomPos;
  leftPos = rightPos = topPos = bottomPos = agent->GetPosition();

  topPos.y += agentSize.y / 2;
  leftPos.x -= agentSize.x / 2;
  rightPos.x += agentSize.x / 2;
  bottomPos.y -= agentSize.y / 2;

  Vector3 leftSize, rightSize, topSize, bottomSize;
  leftSize = rightSize = topSize = bottomSize = agentSize;
  leftSize.y = rightSize.y = agentSize.y;
  topSize.x = bottomSize.x = agentSize.x;

  if (ySpeed > 0) {
    topSize.y = ySpeed;
    bottomSize.y = 0;
  }
  else {
    topSize.y = 0;
    bottomSize.y = -ySpeed;
  }

  if (xSpeed > 0) {
    leftSize.x = 0;
    rightSize.x = xSpeed;
  }
  else {
    leftSize.x = -xSpeed;
    rightSize.x = 0;
  }

  ySpeedBoxT->Update(topPos, topSize, 0);
  ySpeedBoxB->Update(bottomPos, bottomSize, 0);

  xSpeedBoxL->Update(leftPos, leftSize, 0);
  xSpeedBoxR->Update(rightPos, rightSize, 0);
}

void AgentInput::MoveLeft() {
  if (isFalling == false) agent->GetGraphic()->SetCurrentAnimation(L"run", IGraphic::Slot::LOWER);
  auto speedMax = xSpeedMax;
  if (agent->GetFliped() == false) speedMax = xSpeedMax / 2;

  if (xSpeed > -speedMax) {
    if (xSpeed > 0) SlowDown();
    xSpeed -= accel;
  }
  else
    xSpeed = -speedMax;
}

void AgentInput::MoveRight() {
  auto speedMax = xSpeedMax;
    if (agent->GetFliped() == true) speedMax = xSpeedMax / 2;

  if (isFalling == false) agent->GetGraphic()->SetCurrentAnimation(L"run", IGraphic::Slot::LOWER);

  if (xSpeed < speedMax) {
    if (xSpeed < 0) SlowDown();
    xSpeed += accel;
  }
  else
    xSpeed = speedMax;
}

void AgentInput::SlowDown() {

  if (xSpeed > 0.5f)
    xSpeed -= accel * 2;
  else if (xSpeed < -0.5f)
    xSpeed += accel * 2;
  else {
    if (isFalling == false) agent->GetGraphic()->SetCurrentAnimation(L"idle", IGraphic::Slot::LOWER);
    xSpeed = 0.f;
  }
}

void AgentInput::Stop() {
  xSpeed = 0.f;
}

void AgentInput::JumpBegin() {

  auto currTime = Time::Get()->Running();
  // 땅에 있다면 점프
  if (isFalling == false) {
    if (xSpeed > 0.5 || xSpeed < -0.5) agent->GetGraphic()->SetCurrentAnimation(L"jumpBegin_run", IGraphic::Slot::LOWER);
    else agent->GetGraphic()->SetCurrentAnimation(L"jumpBegin_stand", IGraphic::Slot::LOWER);

    jumpedTime = currTime;  // 점프키 누르는 길이 측정 시작
    isJumping = true;     // 점프키를 누르고 있음
    ySpeed = jumpPower;     // 점프 ( 최소 점프 단위 )
    isFalling = true;
  }
}

void AgentInput::Jumping() {
  auto currTime = Time::Get()->Running();
  // 공중에 있고 아직 스페이스바를 누르고 있음
  if (isFalling) {
    // 스페이스바를 누르고 있는 시간이 0.2초 이내라면
    if (currTime - jumpedTime <= 0.2) {
      ySpeed = jumpPower;  // 점프 위력 유지
    }
  }
}

void AgentInput::JumpEnd()
{
  if (isJumping)
  {
    isJumping = false;
  }
}

void AgentInput::Render() {
  xSpeedBoxL->Render();
  xSpeedBoxR->Render();
  ySpeedBoxT->Render();
  ySpeedBoxB->Render();
  crosshair->Render();
}

void AgentInput::CollisionCheck() {

  isFalling = true;

  auto& terrains = level->GetTerrains();

  auto bottom = agent->GetCollision()->GetBottom();
  auto top = agent->GetCollision()->GetTop();
  auto base = agent->GetCollision()->GetBase();

  auto objPos = agent->GetPosition();
  auto objSize = agent->GetSize();

  Vector3 terrPos;
  Vector3 terrSize;

  BoundingBox* terrTop, * terrBottom, * terrBase;
  for (auto terr : terrains) {
    terrTop = terr->GetCollision()->GetTop();
    terrBase = terr->GetCollision()->GetBase();
    terrBottom = terr->GetCollision()->GetBottom();

    terrPos = terr->GetPosition();
    terrSize = terr->GetSize();

    if (ySpeed <= 0) {
      if (BoundingBox::AABB(bottom, terrTop)) {
        isFalling = false;
        ySpeed = 0;

        float depth = (terrPos.y + terrSize.y / 2) - (objPos.y - objSize.y / 2);
        if (depth > 0) {
          agent->Move({ 0, depth, 0 });
        }
      }
    }

    if (ySpeed >= 0) {
      if (BoundingBox::AABB(top, terrBottom)) {
        ySpeed = 0;
      }
    }

    if (BoundingBox::AABB(base, terrBase) == true) {
      if (objPos.x < terrPos.x) {
        float depth = (objPos.x + objSize.x / 2) - (terrPos.x - terrSize.x / 2);
        agent->Move({ -depth, 0, 0 });
        if (xSpeed > 0) xSpeed = 0;
      }
      else if (objPos.x > terrPos.x) {
        float depth = (terrPos.x + terrSize.x / 2) - (objPos.x - objSize.x / 2);
        agent->Move({ depth, 0, 0 });
        if (xSpeed < 0) xSpeed = 0;
      }
    }
  }
}

void AgentInput::SpeedBoxUpdate()
{
  Vector3 xSpeedBoxPos, ySpeedBoxPos;
  Vector3 xSpeedBoxSize, ySpeedBoxSize;

  auto agentPos = agent->GetPosition();
  auto agentSize = agent->GetSize();

  xSpeedBoxPos.x = agentPos.x + agentSize.x / 2;
  xSpeedBoxPos.x = agentPos.x - agentSize.x / 2;

  if(ySpeed)
  ySpeedBoxPos.y = agent->GetPosition().y - agent->GetSize().y / 2;


}