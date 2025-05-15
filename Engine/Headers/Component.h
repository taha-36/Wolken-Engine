#pragma once
class Entity;
class Component {
public:
    virtual ~Component() = default;

    virtual void Serialize()
    {

    };

    Entity* owner = nullptr;
};