#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// Bibliotecas CSFML
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "global.h"


static sfFont * _fonte;
static sfText * _texto;
static sfText * _game_over;
static sfText * _mensagem;
static sfMusic * _som;
static sfMusic * _som_start;


sfRenderWindow * criar_janela(int width, int height){
    sfVideoMode mode = {width, height, 32};
    sfRenderWindow * _janela = sfRenderWindow_create(mode," KillAliens ", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(_janela, 20);
    return _janela;
}

void csfml_destruir_elementos(sfClock * clock, sfClock * tempoTiro, sfClock * tempoSom,
                              sfTexture * tbackground,
                              sfSprite * sbackground,
                              sfTexture ** tnave, sfSprite ** snave,
                              sfTexture * talien, sfSprite * salien,
                              sfTexture * talienMorto, sfSprite * salienMorto,
                              sfTexture * ttiro, sfSprite * stiro,
                              sfRenderWindow * janela){
    sfClock_destroy(clock);
    sfClock_destroy(tempoTiro);
    sfClock_destroy(tempoSom);

    sfTexture_destroy(tbackground);
    sfSprite_destroy(sbackground);

    sfTexture_destroy(tnave[0]);
    sfSprite_destroy(snave[0]);
    sfTexture_destroy(tnave[1]);
    sfSprite_destroy(snave[1]);
    sfTexture_destroy(tnave[2]);
    sfSprite_destroy(snave[2]);

    sfTexture_destroy(talien);
    sfSprite_destroy(salien);

    sfTexture_destroy(talienMorto);
    sfSprite_destroy(salienMorto);

    sfTexture_destroy(ttiro);
    sfSprite_destroy(stiro);

    sfFont_destroy(_fonte);
    sfText_destroy(_texto);
    sfText_destroy(_game_over);
    sfText_destroy(_mensagem);
    sfMusic_destroy(_som);
    sfMusic_destroy(_som_start);

    sfRenderWindow_destroy(janela);
}


void csfml_sprite_setSize(sfSprite * sprite, float largura, float altura){
    sfFloatRect rect = sfSprite_getLocalBounds(sprite);
    sfSprite_setScale(sprite,(sfVector2f){largura / rect.width,
                                          altura / rect.height});
}

void csfml_background_desenhar(sfRenderWindow * janela, sfSprite * sbackground){
    csfml_sprite_setSize(sbackground, 800, 600);
    sfRenderWindow_drawSprite(janela, sbackground, NULL);
}

void csfml_rect_desenhar(Rect *rect, sfRenderWindow *janela, sfSprite *sprite){
    sfSprite_setPosition(sprite,(sfVector2f){rect->pos.x, rect->pos.y});
    csfml_sprite_setSize(sprite, rect->tam.x, rect->tam.y);
    sfRenderWindow_drawSprite(janela,sprite,NULL);
}

void csfml_rotate_desenhar(Rect *rect, Par vel, sfRenderWindow *janela, sfSprite * sprite){
    sfSprite_setPosition(sprite,(sfVector2f){rect->pos.x, rect->pos.y});

    sfFloatRect srect = sfSprite_getLocalBounds(sprite);
    sfSprite_setOrigin(sprite, (sfVector2f){srect.width/2, srect.height/2});
    csfml_sprite_setSize(sprite, rect->tam.x, rect->tam.y);

    sfSprite_setRotation(sprite, atan2(vel.y, vel.x) * 180.0/M_PI + 90);

    sfRenderWindow_drawSprite(janela,sprite,NULL);
    sfSprite_setOrigin(sprite, (sfVector2f){0, 0});
}

void csfml_placar_desenhar(sfRenderWindow * janela, int acertos, int vida){

    _fonte = sfFont_createFromFile("../font/arcade.ttf");
    _texto = sfText_create();
    sfText_setFont(_texto, _fonte);

    char texto[10];
    sprintf(texto, "SCORE: %d - LIFE: %d ", acertos, vida);
    sfText_setRotation(_texto, 0);
    sfText_setString(_texto, texto);
    sfText_setColor(_texto, sfWhite);
    sfText_setPosition(_texto, (sfVector2f){270, 0});
    sfText_setCharacterSize(_texto, 25);
    sfRenderWindow_drawText(janela, _texto, NULL);
}

void csfml_gameOver_desenhar(sfRenderWindow * janela){

    _fonte = sfFont_createFromFile("../font/arcade.ttf");
    _game_over = sfText_create();
    _mensagem = sfText_create();
    sfText_setFont(_game_over, _fonte);
    sfText_setFont(_mensagem, _fonte);

    char game_over[20];
    char mensagem[50];
    sprintf(game_over, "GAME OVER");
    sprintf(mensagem, "Aperte R para RENICIAR ou Q para SAIR");
    sfText_setRotation(_game_over, 0);
    sfText_setRotation(_mensagem, 0);
    sfText_setString(_game_over, game_over);
    sfText_setString(_mensagem, mensagem);
    sfText_setColor(_game_over, sfRed);
    sfText_setColor(_mensagem, sfWhite);
    sfText_setPosition(_game_over, (sfVector2f){180, 200});
    sfText_setPosition(_mensagem, (sfVector2f){177, 300});
    sfText_setCharacterSize(_game_over, 100);
    sfText_setCharacterSize(_mensagem, 25);
    sfRenderWindow_drawText(janela, _game_over, NULL);
    sfRenderWindow_drawText(janela, _mensagem, NULL);
}

void csfml_start_play(char * path){
    _som_start = sfMusic_createFromFile(path);
    sfMusic_play(_som_start);
}

void csfml_tiro_play(char * path){
//    if(_som != NULL)
//        sfMusic_destroy(_som);
    _som = sfMusic_createFromFile(path);
    sfMusic_play(_som);
}
