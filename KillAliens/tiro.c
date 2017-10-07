#include "tiro.h"
#include <stdlib.h>

#include <math.h>
Tiro tiro_criar(Par pos, Par tam, char tecla){
    Tiro t;
    t.power = 2;

    t.rect = (Rect){pos, tam, True};
    double angle;
    if(tecla == 'w')
        angle = 90;
    if(tecla == 'a')
        angle = 210;
    if(tecla == 'd')
        angle = 330;


    angle = (angle * M_PI) / 180.0; //graus para radianos
    t.vel = (Par){cos(angle), -sin(angle)};

    return t;
}

void tiro_update(Tiro * tiro){
    tiro->vel.y *= 1.2;
    tiro->vel.x *= 1.2;
    tiro->rect.pos.y += tiro->vel.y;
    tiro->rect.pos.x += tiro->vel.x;
}
