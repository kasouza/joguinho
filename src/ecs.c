#include "joguinho/ecs.h"

#include <stdbool.h>

typedef enum { POSITION_COMPONENT = 0, LAST_COMPONENT } Component;

bool available_entities[MAX_ENTITIES];
bool entity_components[MAX_ENTITIES][LAST_COMPONENT] = {0};

ComponentsAndGroups __GLOBAL_COMPONENTS_AND_GROUPS__ = {0};

void destroy_entity(Entity e) {
    remove_all_components(e);
    remove_all_groups(e);
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

void init_ecs() {
    for (int i = 0; i < MAX_ENTITIES; ++i) {
        available_entities[i] = true;
    }
}
