#ifndef NAVE_H
#define NAVE_H
#include <SFML/Graphics.h>
#include "global.h"
typedef struct{
    Rect rect;
    Par vel;

    int power;
    int life;
    int ind;
}Nave;


Nave nave_criar(Par tam);

void nave_update(Nave * nave);

void nave_processar_entrada(Nave * nave);

#endif // NAVE_H
