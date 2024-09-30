/*
** EPITECH PROJECT, 2024
** B-CPP-500-RUN-5-1-rtype-romain.nacaouele
** File description:
** ECS
*/

/// \file ECS.hpp
/// \author PAG_Y0Z
/// \brief ECS Class implementation
/// \date 19-09-2024
/// \version 1.0
///
/// This file contains the definition of an Entity-Component-System (ECS) class
/// that provides a way to create, manage, and update entities and components in
/// a game engine. The ECS class uses a component-based architecture to separate
/// the data and logic of game objects, making it easier to manage and update
/// game entities. The ECS class provides methods to create and destroy entities,
/// add and remove components from entities, and update the game state using
/// systems. The ECS class is designed to be flexible and extensible, allowing
/// developers to create custom components and systems to suit their needs.
///
/// \details The ECS class template provides a way to create, manage, and update
/// entities and components in a game engine. The ECS class uses a component-based
/// architecture to separate the data and logic of game objects, making it easier
/// to manage and update game entities. The ECS class provides methods to create
/// and destroy entities, add and remove components from entities, and update the
/// game state using systems. The ECS class is designed to be flexible and extensible,
/// allowing developers to create custom components and systems to suit their needs.
///
/// \par Example:
/// \code
/// #include "Library.hpp"
///
/// typedef struct Position
/// {
///     double x;
///     double y;
/// } Position;
///
/// typedef struct Velocity
/// {
///     double x;
///     double y;
/// } Velocity;
///
/// class MovementSystem : public Library::DesignPatterns::ECS::ISystem
/// {
/// public:
///     MovementSystem(Library::DesignPatterns::ECS &ecs)
///         : Library::DesignPatterns::ECS::ISystem(ecs) {}
///     void Update(double delta_time) override
///     {
///         Library::Utils::Profiler::GetInstance().Start("MovementSystem::Update");
///         auto entities = __ecs.GetEntitiesWithComponents<Position, Velocity>();
///
///         #pragma omp parallel for
///         for (int i = 0; i < entities.size(); ++i)
///         {
///             auto entity   = entities[i];
///             auto position = __ecs.GetComponent<Position>(entity);
///             auto velocity = __ecs.GetComponent<Velocity>(entity);
///             if (position && velocity)
///             {
///                 position->x += velocity->x * delta_time;
///                 position->y += velocity->y * delta_time;
///             }
///         }
///         Library::Utils::Profiler::GetInstance().Stop("MovementSystem::Update");
///     }
/// };
///
/// int main()
/// {
///     Library::DesignPatterns::ECS             ecs;
///     GameEngine::ECS::Systems::MovementSystem movementSystem(ecs);
///     for (int i = 0; i < 1000000; i++)
///     {
///         Library::DesignPatterns::ECS::EntityID entity = ecs.CreateEntity();
///
///         ecs.AddComponent(entity, GameEngine::ECS::Components::Position{0.0f, 0.0f});
///         ecs.AddComponent(entity, GameEngine::ECS::Components::Velocity{1.0f, 1.0f});
///     }
///
///     for (int i = 0; i < 10000; i++)
///     {
///         movementSystem.Update(1.0f);
///     }
///     return 0;
/// }
/// \endcode
///
/// \see ECS.hpp
/// \see Profiler.hpp
///
/// ## Quotes
///
/// > Oh come on ! Update the damm Entity Already ! You are so slow ! I've seen snails faster than you !
/// >
/// > Freaking dumb-fuck ECS !
/// *- PAGY0Z*

#ifndef ECS_HPP_
#define ECS_HPP_

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <limits>
#include <stack>
#include <unordered_map>
#include <vector>

namespace Library
{
    namespace DesignPatterns
    {
        /// \brief ECS Class
        ///
        /// The ECS class is a core part of the Entity-Component-System architecture,
        /// providing the mechanisms to create, manage, and update entities and their
        /// associated components. Each entity is identified by a unique `EntityID`,
        /// and components can be added, removed, or retrieved for each entity. The ECS
        /// class also offers a system for querying entities that possess specific
        /// components and handles the storage of components in an efficient and cache-friendly
        /// manner.
        ///
        /// \details
        /// The ECS class ensures efficient memory access by organizing component storage
        /// in a contiguous manner, improving cache utilization and reducing memory fragmentation.
        /// It also supports querying entities based on component masks, making it fast and
        /// scalable for large numbers of entities.
        ///
        /// \par Key Features:
        /// - Supports the creation and destruction of entities, ensuring IDs are reused efficiently.
        /// - Allows the addition, removal, and retrieval of components associated with entities.
        /// - Provides a mechanism to query entities with specific components.
        /// - Optimized for performance with bitmasks for quick component presence checks.
        /// - Cache-friendly design to support high-performance use cases, such as real-time game engines.
        ///
        /// \invariant Each entity is associated with at most one instance of each component type.
        /// \invariant Component IDs are unique and assigned at runtime for flexibility.
        class ECS
        {
        public:
            /// \brief The ID of an Entity of type `size_t`
            using EntityID = size_t;
            /// \brief The ID of the Type of the Component of type `size_t`
            using ComponentTypeID = size_t;
            /// \brief The ID of the NULL entity, should be returned if ever filled (`1 << 20` or `1 048 576`)
            static constexpr EntityID NULL_ENTITY = 1 << 20;
            /// \brief The Maximum amount of entities possible in the ECS (`1 << 20` or `1 048 576` or `NULL_ENTITY`)
            static constexpr size_t MAX_ENTITIES = NULL_ENTITY;
            /// \brief The Maximum amount of components an entity can posess (`1 << 7` or `128`)
            static constexpr size_t MAX_COMPONENTS = 1 << 7;

        public:
            /// \brief Component Storage Class
            ///
            /// The Component Storage class is a container that stores the components of a
            /// specific type for each entity in the ECS. The Component Storage class provides
            /// methods to add, remove, and retrieve components for entities, ensuring that
            /// components are stored efficiently and accessed quickly.
            ///
            /// \details The Component Storage class uses a vector to store the components
            /// for each entity, allowing for fast random access and iteration over the components.
            /// The Component Storage class also uses a bitset to track which entities have the
            /// component of the specified type, enabling quick checks for component presence.
            ///
            /// \tparam ComponentType The type of the Component
            template<typename ComponentType>
            class ComponentStorage
            {
            public:
                /// \brief Default Constructor
                ///
                /// This constructor creates a new Component Storage instance with default values.
                ComponentStorage() = default;

                /// \brief Default Destructor
                ///
                /// This destructor destroys the Component Storage instance and cleans up any resources.
                ~ComponentStorage() = default;

            public:
                /// \brief Add Component
                ///
                /// This method adds the component of the specified type to the given entity.
                /// The method takes the entity ID and the component as arguments and adds the
                /// component of the specified type to the entity.
                ///
                /// \param entity The ID of the Entity
                /// \param component The Component to add
                void AddComponent(ECS::EntityID entity, const ComponentType &component)
                {
                    if (entity >= __storage.size())
                    {
                        __storage.resize(entity + 1);
                    }
                    __storage[entity] = component;
                    __is_present.set(entity);
                }

                /// \brief Remove Component
                ///
                /// This method removes the component of the specified type from the given entity.
                /// The method takes the entity ID as an argument and removes the component of the
                /// specified type from the entity.
                ///
                /// \param entity The ID of the Entity
                void RemoveComponent(ECS::EntityID entity)
                {
                    __is_present.reset(entity);
                }

                /// \brief Get Component
                ///
                /// This method returns the component of the specified type for the given entity.
                /// The method takes the entity ID as an argument and returns a pointer to the
                /// component if it exists, or `nullptr` if the component does not exist for the entity.
                ///
                /// \param entity The ID of the Entity
                /// \return A pointer to the component of the specified type for the given entity
                ComponentType *GetComponent(ECS::EntityID entity)
                {
                    if (__is_present.test(entity))
                    {
                        return &__storage[entity];
                    }
                    return nullptr;
                }

            private:
                /// \brief The storage for the components
                std::vector<ComponentType> __storage;
                /// \brief A bitset to check if the component is present in the entity
                std::bitset<MAX_ENTITIES> __is_present;
            };

        public:
            /// \brief The ISystem Interface
            ///
            /// The ISystem Interface is an abstract class that defines the interface
            /// for a system in the ECS. A system is responsible for updating the game
            /// state by processing entities and components in the ECS. The ISystem
            /// Interface provides a method to update the system with the given delta
            /// time, allowing the system to perform any necessary calculations or
            /// modifications to the game state.
            class ISystem
            {
            public:
                /// \brief Default Constructor
                ///
                /// This constructor creates a new ISystem instance with default values.
                ///
                /// \param ecs The ECS instance
                ISystem(ECS &ecs)
                    : __ecs(ecs) {}

                /// \brief Default Destructor
                ///
                /// This destructor destroys the ISystem instance and cleans up any resources.
                virtual ~ISystem() = default;

                virtual void Update(double delta_time) = 0;

            protected:
                /// \brief The ECS instance
                ECS &__ecs;
            };

        public:
            /// \brief Default Constructor
            ///
            /// This constructor creates a new ECS instance with default values.
            ECS() = default;

            /// \brief Default Destructor
            ///
            /// This destructor destroys the ECS instance and cleans up any resources.
            ~ECS() = default;

        public:
            /// \brief Create Entity
            ///
            /// This method creates a new entity in the ECS and returns the ID of the
            /// newly created entity. The method allocates a new entity ID and adds the
            /// entity to the ECS, making it active and ready to be used.
            ///
            /// \return The ID of the newly created Entity
            EntityID CreateEntity()
            {
                if (!__free_entities_ids.empty())
                {
                    EntityID reused_id = __free_entities_ids.top();
                    __free_entities_ids.pop();
                    __active_entities.push_back(reused_id);
                    return reused_id;
                }

                if (__next_entity_id >= MAX_ENTITIES)
                    return NULL_ENTITY;

                EntityID new_entity_id = __next_entity_id++;
                __active_entities.push_back(new_entity_id);
                return new_entity_id;
            }

            /// \brief Destroy Entity
            ///
            /// This method destroys the entity with the given ID. The method takes the
            /// entity ID as an argument and removes the entity from the ECS, freeing up
            /// the entity ID for reuse.
            ///
            /// \param entity_to_destroy The ID of the Entity to destroy
            void DestroyEntity(EntityID entity_to_destroy)
            {
                auto it = std::find(__active_entities.begin(), __active_entities.end(), entity_to_destroy);
                if (it != __active_entities.end())
                {
                    __active_entities.erase(it);
                    __entity_component_masks.erase(entity_to_destroy);
                    __free_entities_ids.push(entity_to_destroy);
                }
            }

            /// \brief Is Active
            ///
            /// This method returns `true` if the entity with the given ID is active,
            /// or `false` if the entity is not active.
            ///
            /// \param entity_id The ID of the Entity
            /// \return `true` if the entity is active, `false` otherwise
            bool IsActive(EntityID entity_id)
            {
                return std::find(__active_entities.begin(), __active_entities.end(), entity_id) != __active_entities.end();
            }

            /// \brief Add Component
            ///
            /// This method adds the component of the specified type to the given entity.
            /// The method takes the entity ID and the component as arguments and adds the
            /// component of the specified type to the entity.
            ///
            /// \tparam ComponentType The type of the Component
            /// \param entity The ID of the Entity
            /// \param component The Component to add
            template<typename ComponentType>
            void AddComponent(EntityID entity, const ComponentType &component)
            {
                GetComponentStorage<ComponentType>().AddComponent(entity, component);
                __entity_component_masks[entity].set(GetComponentTypeID<ComponentType>());
                __query_cache.clear();
            }

            /// \brief Remove Component
            ///
            /// This method removes the component of the specified type from the given entity.
            /// The method takes the entity ID and the component type as arguments and removes
            /// the component of the specified type from the entity.
            ///
            /// \tparam ComponentType The type of the Component
            /// \param entity The ID of the Entity
            template<typename ComponentType>
            void RemoveComponent(EntityID entity)
            {
                GetComponentStorage<ComponentType>().RemoveComponent(entity);
                __entity_component_masks[entity].reset(GetComponentTypeID<ComponentType>());
                __query_cache.clear();
            }

            /// \brief Get Component
            ///
            /// This method returns the component of the specified type for the given entity.
            /// The method takes the entity ID and the component type as arguments and returns
            /// a pointer to the component if it exists, or `nullptr` if the component does not
            /// exist for the entity.
            ///
            /// \tparam ComponentType The type of the Component
            /// \param entity The ID of the Entity
            /// \return A pointer to the component of the specified type for the given entity
            template<typename ComponentType>
            ComponentType *GetComponent(EntityID entity)
            {
                return GetComponentStorage<ComponentType>().GetComponent(entity);
            }

            /// \brief Get Entities with Components
            ///
            /// This method returns a list of entities that have all the specified
            /// components. The method takes a variadic list of Component Types and
            /// returns a list of entities that have all the specified components.
            ///
            /// \tparam ComponentTypes The types of the Components
            /// \return A list of entities that have all the specified components as a `std::vector<EntityID>`
            template<typename... ComponentTypes>
            std::vector<EntityID> GetEntitiesWithComponents()
            {
                std::vector<EntityID>       entities_with_components;
                std::bitset<MAX_COMPONENTS> component_mask;
                ((component_mask.set(GetComponentTypeID<ComponentTypes>()), ...));

                if (__query_cache.find(component_mask) != __query_cache.end())
                {
                    return __query_cache[component_mask];
                }

                for (auto &[entity, mask] : __entity_component_masks)
                {
                    if ((mask & component_mask) == component_mask)
                        entities_with_components.push_back(entity);
                }

                __query_cache[component_mask] = entities_with_components;

                return entities_with_components;
            }

        private:
            /// \brief Get the Component Storage
            ///
            /// This method returns the Component Storage for the given Component Type.
            /// The Component Storage is a container that stores the components of a
            /// specific type for each entity in the ECS.
            ///
            /// \tparam ComponentType The type of the Component
            /// \return The Component Storage for the given Component Type as a `ComponentStorage<ComponentType>`
            template<typename ComponentType>
            ComponentStorage<ComponentType> &GetComponentStorage()
            {
                static ComponentStorage<ComponentType> storage;
                return storage;
            }

            /// \brief Get the Component Type ID
            ///
            /// This method returns the ID of the given Component Type. The ID is
            /// unique for each Component Type and is used to identify the Component
            /// Type in the ECS.
            ///
            /// \tparam ComponentType The type of the Component
            /// \return The ID of the Component Type as a `ComponentTypeID`
            template<typename ComponentType>
            ComponentTypeID GetComponentTypeID()
            {
                static ComponentTypeID id = __next_component_type_id++;
                return id;
            }

        private:
            /// \brief The next Entity ID
            EntityID __next_entity_id = 0;
            /// \brief The next Component Type ID
            ComponentTypeID __next_component_type_id = 0;
            /// \brief The Entity Component Masks
            std::unordered_map<EntityID, std::bitset<MAX_COMPONENTS>> __entity_component_masks;
            /// \brief The Active Entities
            std::vector<EntityID> __active_entities;
            /// \brief The Free Entities IDs
            std::stack<EntityID> __free_entities_ids;
            /// \brief The Query Cache
            std::unordered_map<std::bitset<MAX_COMPONENTS>, std::vector<EntityID>> __query_cache;
        };
    }    // namespace DesignPatterns
}    // namespace Library

#endif /* !ECS_HPP_ */
