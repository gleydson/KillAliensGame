
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Bibliotecas CSFML
#include <SFML/System.h>
#include <SFML/Graphics.h>

// Bibliotecas Criadas
#include "aliens.h"
#include "csfml.h"


Alien alien_criar(Par tam){
    Alien alien;
    alien.life = 1;
    alien.power = 1;
    alien.vel = (Par){1.1, 1.1};

    alien.rect.pos = (Par){rand() % (int)tam.x, 0};
    alien.rect.tam = tam;
    alien.rect.exist = True;

    return alien;
}

void alien_update(Alien * alien){
    if(alien->rect.exist == True){
        alien->rect.pos.x += alien->vel.x;
        alien->rect.pos.y += alien->vel.y;
    }
}


void alien_update_mortos(Alien * alien){
    if(alien->rect.exist == False){
        if(rand() % 2 == 0){
           alien->rect.pos.x += 5;
        }else{
           alien->rect.pos.x -= 5;
        }
        if((rand() % 2) + 2 == 2){
            alien->rect.pos.y += 5;
        }else{
            alien->rect.pos.y -= 5;
        }
    }
}

void alien_perseguir(Alien * alien, Nave * nave){
    if(alien->rect.exist == True){
        float acc = 0.3;
        if(nave->rect.pos.x - alien->rect.pos.x > 0)
            alien->vel.x += acc;
        if(nave->rect.pos.x - alien->rect.pos.x < 0)
            alien->vel.x -= acc;
        if(nave->rect.pos.y - alien->rect.pos.y > 0)
            alien->vel.y += acc;
        if(nave->rect.pos.y - alien->rect.pos.y < 0)
            alien->vel.y -= acc;

        alien->vel.x += ((rand() % (11)) - 5.0)/10.0;
        alien->vel.y += ((rand() % (11)) - 5.0)/10.0;
    }
}


