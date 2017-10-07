#ifndef ALIENS_H
#define ALIENS_H

// Bibliotecas Criadas
#include "global.h"
#include "nave.h"

typedef struct{
    Rect rect;
    Par vel;

    int power;
    int life;
}Alien;

Alien alien_criar(Par tam);

void alien_perseguir(Alien * alien, Nave * nave);

void alien_update(Alien * alien);

void alien_update_mortos(Alien * alien);


#endif // ALIENS_H
