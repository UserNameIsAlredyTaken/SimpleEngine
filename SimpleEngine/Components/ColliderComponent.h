#pragma once
#include "BaseComponent.h"
#include <boost/signals2/signal.hpp>
#include <boost/signals2.hpp>


class ColliderComponent : public BaseComponent
{
private:
    float radius = 1;
    
    static std::vector<ColliderComponent*> Colliders; //static vector of all colliders
    
public:
    ColliderComponent(GameObject* gameObject);
    void Start() override;
    void Update(const GameTimer& gt) override;
    
    static void UpdateCollisionSystem();
    
    boost::signals2::signal<void(ColliderComponent*)> OnCollide;
};


