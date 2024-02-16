#ifndef KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_INCLUDE_JOGUINHO_ECS_H
#define KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_INCLUDE_JOGUINHO_ECS_H

#include "joguinho/components.h"
#include "joguinho/ecs_internal_internals.h"

#define MAX_ENTITIES 32
#define MAX_COMPONENTS 4

typedef struct components_and_groups_t {
    register_component(PositionComponent);
    register_component(HealthComponent);
    register_group(PositionGroup);
} ComponentsAndGroups;

static inline void remove_all_components(Entity e) {
    remove_component(e, HealthComponent);
    remove_component(e, PositionComponent);
}

static inline void remove_all_groups(Entity e) {
    remove_group(e, PositionGroup);
}

#endif
