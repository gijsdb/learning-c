#include <stdio.h>

enum shapes
{
    SQUARE,
    CIRCLE
};

#define COUNT 4
#define PI 3.14159

// Fields that apply to all shapes
#define SHAPE_HEAD              \
    int id;                     \
    enum shapes type;           \
    char name[20];              \
    double (*area)(void *this); \
    double (*perimeter)(void *this);

// Generic shape
typedef struct shape
{
    SHAPE_HEAD
} shape_t;

// Square shape
typedef struct square
{
    SHAPE_HEAD
    double s;
} square_t;

// Circle shape
typedef struct circle
{
    SHAPE_HEAD
    double r;
} circle_t;

/* Shape specific functions */

// void *this refers to the shape calling the function
double s_area(void *this)
{
    // casting to square pointer allowing us to access properties of the square
    square_t *me = (square_t *)this;
    return me->s * 4.0;
}

double s_perimeter(void *this)
{
    square_t *me = (square_t *)this;
    return me->s * 4.0;
}

double c_area(void *this)
{
    circle_t *me = (circle_t *)this;
    return me->r * me->r * PI;
}

double c_perimeter(void *this)
{
    circle_t *me = (circle_t *)this;
    return 2 * me->r * PI;
}

/* Helper macros */
/* Takes a shape parameter, casts it to a shape_t and returns a field or invokes function */
#define S_ID(s) (((shape_t *)(s))->id)
#define S_TYPE(s) (((shape_t *)(s))->type)
#define S_NAME(s) (((shape_t *)(s))->name)
#define S_AREA(s) (((shape_t *)(s))->area((s)))
#define S_PERIMETER(s) (((shape_t *)(s))->perimeter((s)))

int main()
{
    square_t s1 = {
        1,
        SQUARE,
        "square1",
        &s_area,
        &s_perimeter,
        3};

    square_t s2 = {
        2,
        SQUARE,
        "square2",
        &s_area,
        &s_perimeter,
        4};

    circle_t c1 = {
        3,
        CIRCLE,
        "circle1",
        &c_area,
        &c_perimeter,
        1};

    circle_t c2 = {
        4,
        CIRCLE,
        "circle2",
        &c_area,
        &c_perimeter,
        3};

    shape_t *shapes[COUNT];
    shape_t *curr;

    // casting specific shape back to shape_t pointer
    shapes[0] = (shape_t *)&s1;
    shapes[1] = (shape_t *)&s2;
    shapes[2] = (shape_t *)&c1;
    shapes[3] = (shape_t *)&c2;

    for (int i = 0; i < COUNT; i++)
    {
        curr = shapes[i];
        printf("%s: id=%d, type=%d, area=%f perimeter=%f\n", S_NAME(curr), S_ID(curr), S_TYPE(curr), S_AREA(curr), S_PERIMETER(curr));
    }

    return 0;
}
