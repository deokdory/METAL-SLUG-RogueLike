#include "stdafx.h"
#include "IGraphic.h"

#include "Game/GameObject.h"

IGraphic::IGraphic(GameObject* object)
  : object(object)
{
  
}

IGraphic::~IGraphic() {}