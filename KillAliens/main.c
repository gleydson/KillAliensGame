//Biblioteca incluidas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Bibliotecas CSFML
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>

// Bibliotecas Criadas
#include "cenario.h"
#include "nave.h"
#include "tiro.h"
#include "aliens.h"
#include "csfml.h"

static sfClock * myclock;
static sfClock * tempoTiro;
static sfClock * tempoSom;
static sfTexture * tbackground, * tnave[QTD_TNAVES], * ttiro, *talien, *talienMorto;
static sfSprite * sbackground, * snave[QTD_TNAVES], *stiro, *salien, *salienMorto;

void main_iniciar_elementos();

int main(){

    srand(time(NULL));

    int acertos = 0;
    int width = 800;
    int height = 600;

    sfRenderWindow * janela = criar_janela(width, height);
    Cenario * cenario = cenario_criar(width, height);

    main_iniciar_elementos(myclock, tempoTiro, tempoSom,
                           tbackground, sbackground,
                           tnave, snave,  talien,
                           salien, ttiro, stiro, talienMorto, salienMorto);

    csfml_start_play("../music/start.wav");

    // Eventos da Janela
    while(sfRenderWindow_isOpen(janela)){
        sfEvent evento;

        while(sfRenderWindow_pollEvent(janela,&evento)){
            if(evento.type == sfEvtClosed)
                sfRenderWindow_close(janela);
            if(evento.type == sfEvtResized){
                sfFloatRect frect = {0, 0, evento.size.width, evento.size.height};
                sfView * view = sfView_createFromRect(frect);
                sfRenderWindow_setView(janela, view);
                sfView_destroy(view);
            }
            if(evento.type == sfEvtKeyPressed){
                cenario_atirar(cenario, evento.key.code, tempoTiro);
            }
        }

        if(cenario->nave.rect.exist){

            if(sfClock_getElapsedTime(tempoSom).microseconds > sfMilliseconds(6000).microseconds) {
                csfml_start_play("../music/start.wav");
                sfClock_restart(tempoSom);
            }

            //ENTRADA
            nave_processar_entrada(&cenario->nave);
            cenario_update_elementos(cenario);
            cenario_update_vida_nave(cenario);

            //Tempo de aparicao dos aliens
            cenario_gerador_aliens(cenario, myclock);

            //COLISOES
            if (cenario_colisao_tiro_aliens(cenario)){acertos += 1;}
            cenario_colisao_nave_aliens(cenario);
            cenario_colisao_nave_aliens_mortos(cenario);
            rect_keep_inside_wall(&cenario->nave.rect, cenario->dim);
            cenario_colisao_aliens_parede(cenario);
            cenario_colisao_tiros_parede(cenario);

            //REMOCOES
            cenario_remove_elements(cenario);

            //*********************************************

            sfRenderWindow_clear(janela, sfBlack);

            //desenhos
            cenario_desenhar(cenario, janela, sbackground, snave, stiro, salien);
            cenario_desenhar_mortos(cenario, janela, salienMorto);
            csfml_placar_desenhar(janela, acertos, cenario->nave.life);

        }
        if(!cenario->nave.rect.exist){
            csfml_start_play("../music/game_over.wav");
            csfml_gameOver_desenhar(janela);
            if(sfKeyboard_isKeyPressed(sfKeyR)){
                cenario->tam_nave = (Par) {45, 45};
                cenario->nave = nave_criar(cenario->tam_nave);
                cenario->qtd_tiros = 0;
                cenario->qtd_aliens = 0;
                cenario->qtd_aliens_mortos = 0;
                acertos = 0;
                continue;
            }
            if(sfKeyboard_isKeyPressed(sfKeyQ)){
                break;
            }
        }

        sfRenderWindow_display(janela);
    }

    cenario_destruir(cenario);
    csfml_destruir_elementos(myclock, tempoTiro, tempoSom,
                             tbackground, sbackground,
                             tnave, snave,  talien, salien,
                             talienMorto, salienMorto,
                             ttiro, stiro,
                             janela);


    return 0;
}

void main_iniciar_elementos(){

    myclock = sfClock_create();
    (void) myclock;
    tempoTiro = sfClock_create();
    (void) tempoTiro;
    tempoSom = sfClock_create();
    (void) tempoSom;

    //BACKGROUND
    tbackground = sfTexture_createFromFile("../images/background.png", NULL);
    sbackground = sfSprite_create();
    sfSprite_setTexture(sbackground,tbackground,0);

    //NAVE
//    int i = 0;
//    while(i <= 3){
//        tnave[i] = sfTexture_createFromFile("../imagens/nave_final"&(char)i&".png", NULL);
//        snave[i] = sfSprite_create();
//        sfSprite_setTexture(snave[i],tnave[i],i);
//        i++;
//    }

    tnave[0] = sfTexture_createFromFile("../images/nave_final0.png", NULL);
    snave[0] = sfSprite_create();
    sfSprite_setTexture(snave[0],tnave[0],0);

    tnave[1] = sfTexture_createFromFile("../images/nave_final1.png", NULL);
    snave[1] = sfSprite_create();
    sfSprite_setTexture(snave[1],tnave[1],0);

    tnave[2] = sfTexture_createFromFile("../images/nave_final2.png", NULL);
    snave[2] = sfSprite_create();
    sfSprite_setTexture(snave[2],tnave[2],0);

    //TIRO
    ttiro = sfTexture_createFromFile("../images/missil.png", NULL);
    stiro = sfSprite_create();
    sfSprite_setTexture(stiro,ttiro,0);

    //ALIEN
    talien = sfTexture_createFromFile("../images/inimigo.png", NULL);
    salien = sfSprite_create();
    sfSprite_setTexture(salien, talien, 0);

    //ALIEN MORTO
    talienMorto = sfTexture_createFromFile("../images/inimigo_morto.png", NULL);
    salienMorto = sfSprite_create();
    sfSprite_setTexture(salienMorto, talienMorto, 0);

}
