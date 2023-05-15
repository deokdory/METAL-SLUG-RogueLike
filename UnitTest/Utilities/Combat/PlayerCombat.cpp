#include "stdafx.h"
#include "PlayerCombat.h"

#include "Character/Agent.h"
#include "Utilities/Input/Input.h"

//#include "Level/Level.h"


PlayerCombat::PlayerCombat(GameObject& agent)
{
  rifle = Gun::InitHMG(&agent);
  throwable = Throwable::InitGrenade(&agent);
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

  rifle->Update(agent.GetPosition() + agent.GetSize() / 2, agent.GetAgentLookAtAxis());
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
    ImVec4 gray = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
    ImVec4 red = ImVec4(1, 0, 0, 1);

    ImVec4 color;

    if (grenadeCount == 0) color = red;
    else color = gray;

    ImGui::TextColored(color, grenadeStr.c_str());

  }
  ImGui::End();
}

void PlayerCombat::ThrowGrenade(Vector3 position, Vector3 axis, float strength)
{
  grenadeCount--;
  isThrowing = true;
  throwProgress = 0.0;

  GameManager::Get()->GetCurrentLevel()->PushObject(throwable->NewThrowable(position, axis, strength));
}
