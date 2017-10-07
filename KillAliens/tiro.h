#ifndef TIRO_H
#define TIRO_H

#include "global.h"
#include <SFML/Graphics.h>

typedef struct{
    Rect rect;
    Par vel;
    int power;
}Tiro;

Tiro tiro_criar(Par pos, Par tam, char code);

void tiro_update(Tiro * tiro);

#endif // TIRO_H
