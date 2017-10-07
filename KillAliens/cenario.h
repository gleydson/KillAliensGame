#ifndef CENARIO_H
#define CENARIO_H


// Bibliotecas CSFML
#include <SFML/System.h>
#include <SFML/Graphics.h>

// Bibliotecas Criadas
#include "nave.h"
#include "tiro.h"
#include "aliens.h"
#include "global.h"



enum{MAX_ALIENS = 5, MAX_ALIENS_MORTOS = 500, MAX_TIROS = 100};
typedef struct{

    Alien aliens[MAX_ALIENS];
    int qtd_aliens, max_aliens;
    Par tam_aliens;

    Alien aliens_mortos[MAX_ALIENS_MORTOS];
    int qtd_aliens_mortos, max_aliens_mortos;
    Par tam_aliens_mortos;

    Tiro  tiros[MAX_TIROS];
    int qtd_tiros, max_tiros;
    Par tam_tiros;

    Nave nave;
    Par tam_nave;

    Par dim; //dimensoes do cenario
}Cenario;

Cenario *cenario_criar(float width, float height);

void cenario_destruir(Cenario * cenario);

//colisoes
void cenario_colisao_nave_aliens(Cenario * cenario);
void cenario_colisao_nave_aliens_mortos(Cenario * cenario);
void cenario_colisao_aliens_parede(Cenario * cenario);
Boolean cenario_colisao_tiro_aliens(Cenario * cenario);
void cenario_colisao_tiros_parede(Cenario * cenario);
void cenario_colisao_aliens_mortos_parede(Cenario * cenario);

//novos elementos
void cenario_atirar(Cenario * cenario, sfKeyCode code, sfClock * tempoTiro);
void cenario_gerador_aliens(Cenario * cenario, sfClock * clock);

//desenho
void cenario_desenhar(Cenario * cenario, sfRenderWindow * janela,  sfSprite *sbackground,
                      sfSprite **snave, sfSprite *stiro, sfSprite *salien);
void cenario_desenhar_mortos(Cenario * cenario, sfRenderWindow * janela, sfSprite * salienMorto);

//remocao
void cenario_remove_elements(Cenario * cenario);

//atualizacao
void cenario_update_elementos(Cenario * cenario);
void cenario_update_vida_nave(Cenario * cenario);
void cenario_update_aliens_mortos(Cenario * cenario);


#endif // CENARIO_H
