#include "joguinho/components.h"
#include "joguinho/ecs.h"
#include "joguinho/renderer/gl.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {
    init_ecs();

    Entity e = create_entity();
    add_group(e, PositionGroup);
    HealthComponent *h1 = add_component(e, HealthComponent);
    h1->hp = 52;

    PositionComponent *pos = add_component(e, PositionComponent);
    pos->x = 32;
    pos->y = 55;

    Entity e2 = create_entity();
    add_group(e2, PositionGroup);
    HealthComponent *h2 = add_component(e2, HealthComponent);
    h2->hp = 222;

    PositionComponent *pos2 = add_component(e2, PositionComponent);
    pos2->x = 39;
    pos2->y = 42;

    Entity e3 = create_entity();
    add_group(e3, PositionGroup);
    HealthComponent *h3 = add_component(e3, HealthComponent);
    h3->hp = 233;

    PositionComponent *pos3 = add_component(e3, PositionComponent);
    pos3->x = 420;
    pos3->y = 69;

    for (int i = 0; i < count(PositionGroup); ++i) {
        Entity e = get_entity(PositionGroup, i);
        PositionComponent pos = get_entity_component(e, PositionComponent);
        HealthComponent health = get_entity_component(e, HealthComponent);

        printf("E: %d\n", e);
        printf("%f, %f\n", pos.x, pos.y);
        printf("%f\n\n", health.hp);
    }

    return 0;
}
