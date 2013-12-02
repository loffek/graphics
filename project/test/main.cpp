#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum
{
    COMPONENT_NONE = 0,
    COMPONENT_DISPLACEMENT = 1 << 0,
    COMPONENT_VELOCITY = 1 << 1,
    COMPONENT_APPEARANCE = 1 << 2
} Component;

typedef struct
{
    float x;
    float y;
} Displacement;

typedef struct
{
    float x;
    float y;
} Velocity;

typedef struct
{
    char name[100];
} Appearance;

typedef struct
{
    int mask;
    int displacement;
    int velocity;
    int appearance;
} Entity;


#define ENTITY_COUNT 100
#define NUM_RUNS 1000000

#define MOVEMENT_MASK (COMPONENT_DISPLACEMENT | COMPONENT_VELOCITY)

typedef struct
{
    Displacement displacement[ENTITY_COUNT];
    Entity entity[ENTITY_COUNT];
    Appearance appearance[ENTITY_COUNT];
    int mask[ENTITY_COUNT];
    Velocity velocity[ENTITY_COUNT];
} World;


unsigned int createEntity(World *world);
void destroyEntity(World *world, unsigned int entity);
unsigned int createApple(World *world, float x, float y);
void movementFunction(World *world);

int main()
{
    /* initialize random seed: */
    srand (time(NULL));

    World world;

    for (int i=0; i<ENTITY_COUNT; i++)
    {
        world.mask[i] = COMPONENT_NONE;
    }

    for (int i=0; i<ENTITY_COUNT; i++)
    {
        createApple(&world, rand() % 100 + 1, rand() % 100 + 1);
    }

    clock_t begin=clock();

    for (int i=0; i<NUM_RUNS; i++)
    {
        movementFunction(&world);
    }

    clock_t end=clock();
    double diffms=((double)(end-begin)*1000)/CLOCKS_PER_SEC;

    fprintf( stderr, "time: %f\n", diffms);
    fprintf( stderr, "memory: %d\n", sizeof(world));


    for (int i=0; i<ENTITY_COUNT; i++)
    {
        fprintf( stderr, "%3d: %f, %f\n", i, world.displacement[i].x, world.displacement[i].y);
    }

    return 0;
}

unsigned int createEntity(World *world)
{
    unsigned int entity;
    for(entity = 0; entity < ENTITY_COUNT; ++entity)
    {
        if(world->mask[entity] == COMPONENT_NONE)
        {
            return(entity);
        }
    }

    fprintf( stderr, "Error!  No more entities left!\n");
    return(ENTITY_COUNT);
}

void destroyEntity(World *world, unsigned int entity)
{
    world->mask[entity] = COMPONENT_NONE;
}

unsigned int createApple(World *world, float x, float y)
{
    unsigned int entity_id = createEntity(world);

    world->mask[entity_id] = COMPONENT_DISPLACEMENT | COMPONENT_APPEARANCE | COMPONENT_VELOCITY;

    world->displacement[entity_id].x = x;
    world->displacement[entity_id].y = y;

    memcpy ( world->appearance[entity_id].name, "Apple", 6);

    world->velocity[entity_id].x = 0;
    world->velocity[entity_id].y = 0;

    world->entity[entity_id].displacement = entity_id;
    world->entity[entity_id].velocity = entity_id;
    world->entity[entity_id].appearance = entity_id;
    world->entity[entity_id].mask = entity_id;

    return(entity_id);
}

void movementFunction(World *world)
{
    Displacement *d;
    Velocity *v;

    for(int i = 0; i < ENTITY_COUNT; ++i)
    {
        if((world->mask[i] & MOVEMENT_MASK) == MOVEMENT_MASK)
        {
            d = &(world->displacement[world->entity[i].displacement]);
            v = &(world->velocity[world->entity[i].velocity]);

            v->y -= 0.98f;

            d->x += v->x;
            d->y += v->y;

            if (d->y < 0)
                d->y = -(d->y);
        }
    }
}
