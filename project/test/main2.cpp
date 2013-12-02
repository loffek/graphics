#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>

#define ENTITY_COUNT 1000000
#define NUM_RUNS 1000

typedef struct
{
    std::vector<float> pos_x;
    std::vector<float> pos_y;
    std::vector<float> pos_z;

    std::vector<float> vel_x;
    std::vector<float> vel_y;
    std::vector<float> vel_z;

    std::vector<float> mass;
} Quantities;


size_t add_object(Quantities *q, float _pos_x, float _pos_y, float _pos_z, float _mass);
void run(Quantities *q, float delta_t);

int main()
{
    Quantities q;

    fprintf( stderr, "%lu", sizeof(q) );
    for(unsigned int i; i < ENTITY_COUNT; i++){
        add_object( &q, 0, 0, 0, 0 );
    }

    clock_t begin=clock();
    for(unsigned int i; i < NUM_RUNS; i++)
    {
        run(&q,0.0001);
    }
    clock_t end=clock();
    double diffms=((double)(end-begin)*1000)/CLOCKS_PER_SEC;

    fprintf( stderr, "time: %f\n", diffms);


    return 0;
}

size_t add_object(Quantities *q, float _pos_x, float _pos_y, float _pos_z, float _mass)
{
    q->pos_x.push_back(_pos_x);
    q->pos_y.push_back(_pos_y);
    q->pos_z.push_back(_pos_z);

    q->vel_x.push_back(0);
    q->vel_y.push_back(0);
    q->vel_z.push_back(0);

    q->mass.push_back(_mass);
    return q->pos_x.size()-1;
}

void run(Quantities *q, float delta_t)
{
    size_t len = q->pos_x.size();

    for (size_t i; i < len; i++){
        // gravity
        q->vel_y[i] -= 9.82 * delta_t;
    }
    // component wise integration
    for (size_t i; i < len; i++){
        q->pos_x[i] += q->vel_x[i] * delta_t;
    }
    for (size_t i; i < len; i++){
        q->pos_y[i] += q->vel_y[i] * delta_t;
    }
    for (size_t i; i < len; i++){
        q->pos_z[i] += q->vel_z[i] * delta_t;
    }
}
