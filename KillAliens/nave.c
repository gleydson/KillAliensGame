#include "nave.h"

Nave nave_criar(Par tam){
    Nave nave;
    nave.power = 2;
    nave.life = 10;

    nave.rect = (Rect) {{360, 540}, tam, True};
    nave.vel = (Par){5, 5};
    nave.ind = 0;
    return nave;
}

void nave_update(Nave * nave){
    static long ciclo = 0;
    ciclo++;

    if(ciclo > 5){
        ciclo = 0;
        nave->ind = ++nave->ind % QTD_TNAVES;
    }

    (void) nave;
//    nave->rect.pos.x += nave->vel.x;
//    nave->rect.pos.y += nave->vel.y;
}

void nave_processar_entrada(Nave * nave){
    int power = 20;
    Par * pos = &nave->rect.pos;
    if(sfKeyboard_isKeyPressed(sfKeyLeft))
        pos->x -= power;
    if(sfKeyboard_isKeyPressed(sfKeyRight))
        pos->x += power;
    if(sfKeyboard_isKeyPressed(sfKeyUp))
        pos->y -= power;
    if(sfKeyboard_isKeyPressed(sfKeyDown))
        pos->y += power;
}
