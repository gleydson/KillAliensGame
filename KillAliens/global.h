#ifndef GLOBAL_H
#define GLOBAL_H

typedef enum{True = 1, False = 0}Boolean;

enum{QTD_TNAVES = 3};

typedef struct{
    float x, y;
}Par;


typedef struct{
    Par pos;
    Par tam;
    Boolean exist;
}Rect;

Boolean rect_is_inside(float x, float y, Rect r);
Boolean rect_intersect(Rect a, Rect b);
Boolean rect_keep_inside_wall(Rect *rect, Par wall_tam);

#endif // GLOBAL_H
