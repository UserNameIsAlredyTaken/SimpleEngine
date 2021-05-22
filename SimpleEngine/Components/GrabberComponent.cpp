#include "GrabberComponent.h"
#include "../GameObject.h"
#include <boost/signals2/signal.hpp>
#include <boost/signals2.hpp>
#include "ColliderComponent.h"

GrabberComponent::GrabberComponent(GameObject* gameObject) : BaseComponent(gameObject)
{
}

void GrabberComponent::Start()
{
    collider = gameObject->GetComponent<ColliderComponent>();
    // collider->OnCollide.connect(boost::bind(&GrabberComponent::Grabb, this));
    // collider->OnCollide.connect(this->Grabb);
    collider->OnCollide.connect(boost::bind(&GrabberComponent::Grabb, this, boost::placeholders::_1));
}

void GrabberComponent::Grabb(ColliderComponent* other)
{
    gameObject->AddChild(other->GetGameObject());
    printf("grab!\n");
}

void GrabberComponent::Update(const GameTimer& gt)
{
}
