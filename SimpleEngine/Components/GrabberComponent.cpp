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
    collider->OnCollide.connect(boost::bind(&GrabberComponent::Grabb, this));
}

void GrabberComponent::Grabb()
{
    printf("grab!\n");
}

void GrabberComponent::Update(const GameTimer& gt)
{
}
