#include "stdafx.h"
#include "Agent.h"

#include "Component/Collision/Collision.h"

#include "Component/Input/AgentInput.h"
#include "Component/Graphic/ObjectGraphic.h"


Agent::Agent(Vector3 position, Vector3 size)
  : Character(position, size) {

  movement = new AgentInput(this);

  graphic->SetAnchorPoint(MID_BOT, ObjectGraphic::Type::ANIMATION, ObjectGraphic::Slot::LOWER);
  graphic->SetAnchorPoint(MID_BOT, ObjectGraphic::Type::ANIMATION, ObjectGraphic::Slot::UPPER);

  collision->InitializeBase();
  collision->InitializeBottom();
  collision->InitializeTop();

} 

Agent::~Agent() {
  SAFE_DELETE(movement);
}

void Agent::Update() 
{
  //movement->Update();
  graphic->Update();
  collision->Update();
}

void Agent::Render() 
{
  Camera::Get()->SetPosition(position);

  graphic->Render();
  collision->Render();
  //movement->Render();
}

void Agent::GUI()
{
  movement->GUI();
}
