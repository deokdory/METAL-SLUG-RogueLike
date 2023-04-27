#include "stdafx.h"
#include "PlayerCombat.h"

#include "Character/Agent.h"
#include "Component/Input/Input.h"

PlayerCombat::PlayerCombat(GameObject& agent)
{
  rifle = Gun::InitHMG(&agent);
}

PlayerCombat::~PlayerCombat()
{
  SAFE_DELETE(rifle);
}

void PlayerCombat::Update(Agent& agent)
{
  if (isThrowing)
  {
    if (throwProgress > throwSpeed) isThrowing = false;
    else throwProgress += Time::Get()->WorldDelta();
  }

  rifle->Update(agent.GetPosition(), agent.GetAgentLookAtAxis());
}

void PlayerCombat::Render()
{
  rifle->Render();
}

void PlayerCombat::GUI()
{
  rifle->GUI();

  std::string grenadeStr = "grenade : " + std::to_string(grenadeCount);

  ImGui::Begin("Combat");
  {
    ImVec4 color = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
    if (grenadeCount == 0) color = ImVec4(1, 0, 0, 1);
    ImGui::TextColored(color, grenadeStr.c_str());
  }
  ImGui::End();
}

void PlayerCombat::ThrowGrenade()
{
  grenadeCount--;
  isThrowing = true;
  throwProgress = 0.0;
}
