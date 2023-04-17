#include "stdafx.h"
#include "Agent.h"

#include "Component/Collision/Collision.h"

#include "Component/Input/AgentInput.h"
#include "Component/Graphic/IGraphic.h"


Agent::Agent(Vector3 position, Vector3 size)
  : Character(position, size) {

  movement = new AgentInput(this);

  collision->InitializeBase();
  collision->InitializeBottom();
  collision->InitializeTop();

} 

Agent::~Agent() {}

void Agent::Update() 
{
  movement->Update();
  graphic->Update();
  collision->Update();
}

void Agent::Render() 
{
  Camera::Get()->SetPosition(position);

  graphic->Render();
  collision->Render();
  movement->Render();
}
