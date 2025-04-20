#pragma once
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>
#include "Transform.h"
class Entity {
public:
    Transform transform;
    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *comp;

        comp->owner = this;

        std::type_index index(typeid(T));
        components[index] = std::move(comp);
        orderedComponents.push_back(components[index].get());

        return ref;
    }
    template <typename T>
    T& AddComponent(T& existingComponent) {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

        std::type_index index(typeid(T));
        auto comp = std::make_unique<T>(std::move(existingComponent));
        T& ref = *comp;

        comp->owner = this;

        components[index] = std::move(comp);
        orderedComponents.push_back(components[index].get());

        return ref;
    }

    template <typename T>
    T* GetComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end())
            return static_cast<T*>(it->second.get());
        return nullptr;
    }

    const std::vector<Component*>& GetAllComponents() const {
        return orderedComponents;
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
    std::vector<Component*> orderedComponents;
};