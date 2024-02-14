#include "joguinho/ecs.h"

#include <stdbool.h>
#include <stdio.h>

#define MAX_ENTITIES 32
#define MAX_COMPONENTS 4

typedef enum { POSITION_COMPONENT = 0, LAST_COMPONENT } Component;

/* Entity */
typedef int Entity;
bool available_entities[MAX_ENTITIES];
bool entity_components[MAX_ENTITIES][LAST_COMPONENT] = {0};

/* PositionComponent */
typedef struct {
    double x;
    double y;
} PositionComponent;

#define component_count(component) components.component##_components_len

#define get_component(component, idx) components.component##_components[idx]

#define register_component(component)                                          \
    component component##_components[MAX_ENTITIES];                            \
    int component##_components_len;                                            \
    Entity component##_component_idx_to_entity[MAX_ENTITIES];                  \
    int entity_to_##component##_component_idx[MAX_ENTITIES]

#define add_component(entity, component)                                       \
    &components.component##_components[components.component##_components_len]; \
    do {                                                                       \
        Entity __entity__ = (entity);                                          \
        int idx = components.component##_components_len;                       \
                                                                               \
        components.component##_component_idx_to_entity[idx] = __entity__;      \
        components.entity_to_##component##_component_idx[__entity__] = idx;    \
                                                                               \
        components.component##_components_len++;                               \
    } while (false)

#define remove_component(entity, component)                                    \
    do {                                                                       \
        int last_component_idx = components.component##_components_len - 1;    \
        Entity last_component_entity =                                         \
            components                                                         \
                .component##_component_idx_to_entity[last_component_idx];      \
                                                                               \
        int component_idx =                                                    \
            components.entity_to_##component##_component_idx[(entity)];        \
                                                                               \
        /* Invalidate old component idx */                                     \
        components.entity_to_##component##_component_idx[(entity)] = -1;       \
                                                                               \
        /* Copy last component to old */                                       \
        components.component##_components[component_idx] =                     \
            components.component##_components[last_component_idx];             \
                                                                               \
        /* Update mappings */                                                  \
        components.component##_component_idx_to_entity[component_idx] =        \
            last_component_entity;                                             \
        components                                                             \
            .entity_to_##component##_component_idx[last_component_entity] =    \
            component_idx;                                                     \
                                                                               \
        components.component##_components_len--;                               \
        /* Remove component from entity signature */                           \
        /*entity_components[entity][*/                                         \
    } while (false)

struct {
    register_component(PositionComponent);
} components = {0};

void remove_all_components(Entity e) { remove_component(e, PositionComponent); }

void destroy_entity(Entity e) {
    remove_all_components(e);
    available_entities[e] = true;
}

Entity create_entity() {
    for (Entity i = 0; i < MAX_ENTITIES; ++i) {
        if (available_entities[i]) {
            available_entities[i] = false;
            return i;
        }
    }

    return -1;
}

/* Init */
void init() {
    for (int i = 0; i < MAX_ENTITIES; ++i) {
        available_entities[i] = true;
    }
}

int main(void) {
    init();

    Entity e = create_entity();
    PositionComponent *pos = add_component(e, PositionComponent);
    pos->x = 32;
    pos->y = 55;

    Entity e2 = create_entity();
    PositionComponent *pos2 = add_component(e2, PositionComponent);
    pos2->x = 39;
    pos2->y = 42;

    Entity e3 = create_entity();
    PositionComponent *pos3 = add_component(e3, PositionComponent);
    pos3->x = 420;
    pos3->y = 69;

    remove_component(e, PositionComponent);
    remove_component(e2, PositionComponent);
    remove_component(e3, PositionComponent);

    for (int i = 0; i < component_count(PositionComponent); ++i) {
        PositionComponent pos = get_component(PositionComponent, i);
        printf("%f, %f\n", pos.x, pos.y);
    }

    return 0;
}
