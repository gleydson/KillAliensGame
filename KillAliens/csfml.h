#ifndef CSFML_H
#define CSFML_H


// Bibliotecas CSFML
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include "nave.h"
#include "global.h"

sfRenderWindow * criar_janela(int width, int height);

void csfml_destruir_elementos(sfClock * clock, sfClock * tempoTiro, sfClock * tempoSom,
                              sfTexture * tbackground,
                              sfSprite * sbackground,
                              sfTexture ** tnave, sfSprite ** snave,
                              sfTexture * talien, sfSprite * salien,
                              sfTexture * talienMorto, sfSprite * salienMorto,
                              sfTexture * ttiro, sfSprite * stiro,
                              sfRenderWindow * janela);

void csfml_sprite_setSize(sfSprite *sprite, float largura, float altura);

void csfml_background_desenhar(sfRenderWindow * janela, sfSprite * sbackground);

void csfml_rect_desenhar(Rect * rect, sfRenderWindow * janela, sfSprite * sprite);

void csfml_rotate_desenhar(Rect *rect, Par vel, sfRenderWindow *janela, sfSprite *sprite);

void csfml_placar_desenhar(sfRenderWindow * janela, int acertos, int vida);

void csfml_gameOver_desenhar(sfRenderWindow * janela);

void csfml_tiro_play(char * path);

void csfml_start_play(char * path);

#endif // CSFML_H
