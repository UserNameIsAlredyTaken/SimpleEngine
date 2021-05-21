#pragma once
#include "BaseComponent.h"
#include <boost/signals2/signal.hpp>
#include <boost/signals2.hpp>

class ColliderComponent : public BaseComponent
{
private:
    float radius = 1;
    
public:
    ColliderComponent(GameObject* gameObject);
    void Start() override;
    void Update(const GameTimer& gt) override;
    //boost::signal<void()> OnPressed;
    boost::signals2<void()> OnPressed;
};