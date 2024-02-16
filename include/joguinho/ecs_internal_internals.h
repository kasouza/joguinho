#ifndef KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_INCLUDE_JOGUINHO_ECS_INTERNAL_INTERNALS_H
#define KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_INCLUDE_JOGUINHO_ECS_INTERNAL_INTERNALS_H

#include <assert.h>
#include <stdbool.h>

typedef int Entity;

struct components_and_groups_t;
extern struct components_and_groups_t __GLOBAL_COMPONENTS_AND_GROUPS__;

#define count(component_or_group)                                              \
    __GLOBAL_COMPONENTS_AND_GROUPS__.component_or_group##_components_len

#define get_entity_component(entity, component)                                \
    __GLOBAL_COMPONENTS_AND_GROUPS__.component##_components                    \
        [__GLOBAL_COMPONENTS_AND_GROUPS__                                      \
             .entity_to_##component##_component_idx[entity]];

#define get_component(component, idx)                                          \
    __GLOBAL_COMPONENTS_AND_GROUPS__.component##_components[idx]

#define get_entity(component_or_group, component_or_group_idx)                 \
    __GLOBAL_COMPONENTS_AND_GROUPS__                                           \
        .component_or_group##_component_idx_to_entity[component_or_group_idx]

#define register_component(component)                                          \
    component component##_components[MAX_ENTITIES];                            \
    int component##_components_len;                                            \
    Entity component##_component_idx_to_entity[MAX_ENTITIES];                  \
    int entity_to_##component##_component_idx[MAX_ENTITIES]

#define register_group(group)                                                  \
    int group##_components_len;                                                \
    Entity group##_component_idx_to_entity[MAX_ENTITIES];                      \
    int entity_to_##group##_component_idx[MAX_ENTITIES];

#define add_component(entity, component)                                       \
    &__GLOBAL_COMPONENTS_AND_GROUPS__.component##_components                   \
         [__GLOBAL_COMPONENTS_AND_GROUPS__.component##_components_len];        \
    do {                                                                       \
        Entity __entity__ = (entity);                                          \
        int idx = __GLOBAL_COMPONENTS_AND_GROUPS__.component##_components_len; \
                                                                               \
        __GLOBAL_COMPONENTS_AND_GROUPS__                                       \
            .component##_component_idx_to_entity[idx] = __entity__;            \
        __GLOBAL_COMPONENTS_AND_GROUPS__                                       \
            .entity_to_##component##_component_idx[__entity__] = idx;          \
                                                                               \
        __GLOBAL_COMPONENTS_AND_GROUPS__.component##_components_len++;         \
    } while (false)

#define add_group(entity, group)                                               \
    do {                                                                       \
        Entity __entity__ = (entity);                                          \
        int idx = __GLOBAL_COMPONENTS_AND_GROUPS__.group##_components_len;     \
                                                                               \
        __GLOBAL_COMPONENTS_AND_GROUPS__                                       \
            .group##_component_idx_to_entity[idx] = __entity__;                \
        __GLOBAL_COMPONENTS_AND_GROUPS__                                       \
            .entity_to_##group##_component_idx[__entity__] = idx;              \
                                                                               \
        __GLOBAL_COMPONENTS_AND_GROUPS__.group##_components_len++;             \
    } while (false)

#define remove_component(entity, component)                                    \
    do {                                                                       \
        int last_component_idx =                                               \
            __GLOBAL_COMPONENTS_AND_GROUPS__.component##_components_len - 1;   \
        Entity last_component_entity =                                         \
            __GLOBAL_COMPONENTS_AND_GROUPS__                                   \
                .component##_component_idx_to_entity[last_component_idx];      \
                                                                               \
        int component_idx =                                                    \
            __GLOBAL_COMPONENTS_AND_GROUPS__                                   \
                .entity_to_##component##_component_idx[(entity)];              \
                                                                               \
        /* Invalidate old component idx */                                     \
        __GLOBAL_COMPONENTS_AND_GROUPS__                                       \
            .entity_to_##component##_component_idx[(entity)] = -1;             \
                                                                               \
        /* Copy last component to old */                                       \
        __GLOBAL_COMPONENTS_AND_GROUPS__                                       \
            .component##_components[component_idx] =                           \
            __GLOBAL_COMPONENTS_AND_GROUPS__                                   \
                .component##_components[last_component_idx];                   \
                                                                               \
        /* Update mappings */                                                  \
        __GLOBAL_COMPONENTS_AND_GROUPS__                                       \
            .component##_component_idx_to_entity[component_idx] =              \
            last_component_entity;                                             \
        __GLOBAL_COMPONENTS_AND_GROUPS__                                       \
            .entity_to_##component##_component_idx[last_component_entity] =    \
            component_idx;                                                     \
                                                                               \
        __GLOBAL_COMPONENTS_AND_GROUPS__.component##_components_len--;         \
        /* Remove component from entity signature */                           \
        /*entity_components[entity][*/                                         \
    } while (false)

#define remove_group(entity, group)                                            \
    do {                                                                       \
        int last_component_idx =                                               \
            __GLOBAL_COMPONENTS_AND_GROUPS__.group##_components_len - 1;       \
        Entity last_component_entity =                                         \
            __GLOBAL_COMPONENTS_AND_GROUPS__                                   \
                .group##_component_idx_to_entity[last_component_idx];          \
                                                                               \
        int component_idx = __GLOBAL_COMPONENTS_AND_GROUPS__                   \
                                .entity_to_##group##_component_idx[(entity)];  \
                                                                               \
        /* Invalidate old component idx */                                     \
        __GLOBAL_COMPONENTS_AND_GROUPS__                                       \
            .entity_to_##group##_component_idx[(entity)] = -1;                 \
                                                                               \
        /* Update mappings */                                                  \
        __GLOBAL_COMPONENTS_AND_GROUPS__                                       \
            .group##_component_idx_to_entity[component_idx] =                  \
            last_component_entity;                                             \
        __GLOBAL_COMPONENTS_AND_GROUPS__                                       \
            .entity_to_##group##_component_idx[last_component_entity] =        \
            component_idx;                                                     \
                                                                               \
        __GLOBAL_COMPONENTS_AND_GROUPS__.group##_components_len--;             \
    } while (false)

void init_ecs();
void destroy_entity(Entity e);
Entity create_entity();

#endif
