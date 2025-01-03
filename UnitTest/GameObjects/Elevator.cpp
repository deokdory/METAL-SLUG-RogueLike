#include "stdafx.h"
#include "Elevator.h"

#include "Character/Animations.h"
#include "Character/Agent.h"

Elevator::Elevator(Vector3 position)
  : GameObject(position, Vector3(318, 192, 0))
{
  objectType = GameObject::Type::ELEVATOR;
  InitGraphic(Animations::GetElevator(), ObjectGraphic::Slot::NORMAL);
}

Elevator::~Elevator()
{
}

void Elevator::Update()
{
  if (GameManager::Get()->GetPlayerCurrentRoom() != nullptr && status != Status::MOVING)
  {
    int playerCurrentFloor = GameManager::Get()->GetPlayerCurrentRoom()->GetFloor();
    if (currentRoom->GetFloor() != playerCurrentFloor)
    {
      position.y = playerCurrentFloor * 960 - 64;
    }
  }

  elevatorTopPos = position + Vector3(0, 62, 0);

  if (justGetOn == false)
  {
    __super::Update();

    if (agent != nullptr)
    {
      switch (status)
      {
      case Elevator::Status::GETTING_ON:
      {
          status = Elevator::Status::WAITING;
      }
      case Elevator::Status::WAITING:
      {
        agent->SetPositionForce(elevatorTopPos);

        if (Keyboard::Get()->Down('E')) getOff(agent);
        if (Keyboard::Get()->Down('W')) elevate(Direction::UP);
        if (Keyboard::Get()->Down('S')) elevate(Direction::DOWN);

        break;
      }
      case Elevator::Status::MOVING:
        if (position.y != destPositionY)
        {
          agent->SetPositionForce(elevatorTopPos);
          Move({ 0, (destPositionY - prevPositionY) / 60, 0 });
        }
        else
        {
          status = Status::WAITING;
        }
        break;

      default:
        break;
      }
    }
  }
  else
    justGetOn = false;
}

void Elevator::Interaction(GameObject* object)
{
  getOn(object);
}

void Elevator::getOn(GameObject* object)
{
  if (object->GetObjectType() == GameObject::Type::PLAYER)
  {
    if (agent == nullptr || agent != object)
      agent = dynamic_cast<Agent*>(object);

    agent->SetCanMove(false);

    prevPlayerPosition = object->GetPosition();

    agent->GetMovement()->Jump();
    justGetOn = true;

    status = Status::GETTING_ON;
  }
}

void Elevator::getOff(GameObject* object)
{
  if (agent)
  {
    agent->SetCanMove(true);
    agent->GetMovement()->Jump();
    agent = nullptr;
  }
}

void Elevator::elevate(Direction direction)
{
  switch (direction)
  {
  case Direction::UP:
  {
    if (currentRoom->GetLinkedRoom(Direction::UP) == nullptr)
      std::cout << "ELEVATOR::already top" << std::endl;
    else
    {
      status = Status::MOVING;
      prevPositionY = position.y;
      destPositionY = position.y + 960.0f;
    }
  }
    break;
  case Direction::DOWN:
  {
    if (currentRoom->GetLinkedRoom(Direction::DOWN) == nullptr) 
      std::cout << "ELEVATOR::already bottom" << std::endl;
    else
    {
      status = Status::MOVING;
      prevPositionY = position.y;
      destPositionY = position.y - 960.0f;
    }
  }
    break;
  default:
    break;
  }
}
