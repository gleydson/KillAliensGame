#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Bibliotecas CSFML
#include <SFML/System.h>
#include <SFML/Graphics.h>

// Bibliotecas Criadas
#include "cenario.h"
#include "nave.h"
#include "tiro.h"
#include "aliens.h"
#include "csfml.h"
#include "global.h"


// variaveis "for"
int i = 0, j = 0, aliens_mortos = 0;

//void cenario_add_alien(Cenario * cenario);
void remover_alien(Cenario *cenario, int i);
void remover_tiro(Cenario * cenario, int ind);
void remover_alien_mortos(Cenario * cenario, int i);

Cenario * cenario_criar(float width, float height){
    Cenario * cenario = malloc(sizeof(Cenario));

    cenario->qtd_aliens = 0;
    cenario->max_aliens = MAX_ALIENS;
    cenario->tam_aliens = (Par){50, 40};
    //cenario->vetAliens = malloc(sizeof(Alien) * max_aliens);

    cenario->qtd_aliens_mortos = 0;
    cenario->max_aliens_mortos = MAX_ALIENS_MORTOS;
    cenario->tam_aliens_mortos = (Par){50, 40};


    cenario->qtd_tiros = 0;
    cenario->max_tiros = MAX_TIROS;
    cenario->tam_tiros = (Par){20, 30};
    //cenario->vetTiro = malloc(sizeof(Tiro) * max_tiro);

    cenario->tam_nave = (Par){45, 45};
    cenario->nave = nave_criar(cenario->tam_nave);

    cenario->dim = (Par) {width, height};

    return cenario;
}
void cenario_destruir(Cenario * cenario){
    free(cenario);
}

void cenario_desenhar(Cenario * cenario, sfRenderWindow * janela, sfSprite *sbackground, sfSprite **snave, sfSprite *stiro, sfSprite *salien){
    csfml_background_desenhar(janela, sbackground);
    for(i = 0; i < cenario->qtd_aliens;i++)
        csfml_rotate_desenhar(&cenario->aliens[i].rect, cenario->aliens[i].vel, janela, salien);
    for(i = 0; i < cenario->qtd_tiros; i++)
        csfml_rotate_desenhar(&cenario->tiros[i].rect, cenario->tiros[i].vel, janela, stiro);
    csfml_rect_desenhar(&cenario->nave.rect, janela, snave[cenario->nave.ind]);
}

void cenario_desenhar_mortos(Cenario * cenario, sfRenderWindow * janela, sfSprite * salienMorto){
    for(i = 0; i < cenario->qtd_aliens_mortos;i++)
        csfml_rotate_desenhar(&cenario->aliens_mortos[i].rect, cenario->aliens_mortos[i].vel, janela, salienMorto);
    cenario_update_aliens_mortos(cenario);
}


void cenario_gerador_aliens(Cenario * cenario, sfClock * clock){
    if(sfClock_getElapsedTime(clock).microseconds > sfMilliseconds(500).microseconds){
        sfClock_restart(clock);
        if(cenario->qtd_aliens < cenario->max_aliens){
            Alien x = alien_criar(cenario->tam_aliens);
            cenario->aliens[cenario->qtd_aliens] = x;
            cenario->qtd_aliens += 1;
        }
    }
}

void cenario_atirar(Cenario * cenario, sfKeyCode code, sfClock * tempoTiro){
    if(cenario->qtd_tiros < cenario->max_tiros){
        if(code == sfKeyW || code == sfKeyA || code == sfKeyD){
            sfClock_restart(tempoTiro);
            Par pos = cenario->nave.rect.pos;
            pos.x += cenario->nave.rect.tam.x/2;
            pos.y += cenario->nave.rect.tam.y/2;

            Tiro tiro;
            if(sfKeyboard_isKeyPressed(sfKeyW))
                tiro = tiro_criar(pos, cenario->tam_tiros, 'w');
            if(sfKeyboard_isKeyPressed(sfKeyA))
                tiro = tiro_criar(pos, cenario->tam_tiros, 'a');
            if(sfKeyboard_isKeyPressed(sfKeyD))
                tiro = tiro_criar(pos, cenario->tam_tiros, 'd');

            cenario->tiros[cenario->qtd_tiros] = tiro;
            cenario->qtd_tiros += 1;
            csfml_tiro_play("../music/shot.ogg");

        }
    }
}

//################  COLISOES  #####################

void cenario_colisao_nave_aliens(Cenario * cenario){
    for(i = 0; i < cenario->qtd_aliens; i++){
        Alien * alien = &cenario->aliens[i];
        Nave * nave = &cenario->nave;
        if(rect_intersect(nave->rect, alien->rect)){
            nave->life -= alien->life;
            alien->rect.exist = False;
            if(nave->life == 0){
                nave->rect.exist = False;
            }
//        csfml_tiro_play("../music/explosion.wav");
        }

    }
}

void cenario_colisao_nave_aliens_mortos(Cenario * cenario){
    for(i = 0; i < cenario->qtd_aliens_mortos; i++){
        Alien * alien = &cenario->aliens_mortos[i];
        Nave * nave = &cenario->nave;
        if(rect_intersect(nave->rect, alien->rect)){
            if(nave->rect.pos.x <= alien->rect.pos.x || nave->rect.pos.y <= alien->rect.pos.y){
                cenario->nave.life -= 1;
                if(nave->life == 0){
                    nave->rect.exist = False;
                }
                if(cenario->aliens_mortos[i].rect.exist == False){
                    remover_alien_mortos(cenario, i);
                    return;
                }

            }
//        csfml_tiro_play("../music/explosion.wav");
        }

    }
}

void cenario_colisao_aliens_parede(Cenario * cenario){
    for(i = 0; i < cenario->qtd_aliens; i++){
        Alien * alien = &cenario->aliens[i];
        if(rect_keep_inside_wall(&alien->rect, cenario->dim)){
            int chance = 50;
            if(rand() % chance == 0){
                cenario->aliens[i].vel.x *= -1;
                cenario->aliens[i].vel.y *= -1;
            }
        }

    }
}

void cenario_colisao_aliens_mortos_parede(Cenario * cenario){
    for(i = 0; i < cenario->qtd_aliens_mortos; i++){
        Alien * alien = &cenario->aliens_mortos[i];
        rect_keep_inside_wall(&alien->rect, cenario->dim);
    }
}

void cenario_colisao_tiros_parede(Cenario * cenario){
    for(i = 0; i < cenario->qtd_tiros; i++){
        Tiro * tiro = &cenario->tiros[i];
        Par center = (Par){tiro->rect.pos.x + tiro->rect.tam.x/2,
                           tiro->rect.pos.y + tiro->rect.tam.y/2};
        if(!rect_is_inside(center.x, center.y, (Rect){{0, 0}, cenario->dim, False}))
            tiro->rect.exist = False;
    }
}

Boolean cenario_colisao_tiro_aliens(Cenario * cenario){
    for(i = 0; i < cenario->qtd_aliens; i++){
        for(j = 0; j < cenario->qtd_tiros; j++){
            Alien * alien = &cenario->aliens[i];
            Tiro * tiro = &cenario->tiros[j];

            if(rect_intersect(alien->rect, tiro->rect)){
                    alien->rect.exist = False;
                    cenario->aliens_mortos[cenario->qtd_aliens_mortos] = cenario->aliens[i];
                    cenario->qtd_aliens_mortos += 1;
                    aliens_mortos++;



                tiro->power--;
                if(tiro->power <= 0)
                    tiro->rect.exist = False;

                return True;
            }
        }
    }
    return False;
}



//################  REMOCOES #####################

void remover_alien(Cenario * cenario, int i){
    Alien aux = cenario->aliens[i];
    cenario->aliens[i] = cenario->aliens[cenario->qtd_aliens - 1];
    cenario->aliens[cenario->qtd_aliens - 1] = aux;
    cenario->qtd_aliens -= 1;
}
void remover_alien_mortos(Cenario * cenario, int i){
    Alien aux = cenario->aliens_mortos[i];
    cenario->aliens_mortos[i] = cenario->aliens_mortos[cenario->qtd_aliens_mortos - 1];
    cenario->aliens_mortos[cenario->qtd_aliens_mortos - 1] = aux;
    cenario->qtd_aliens_mortos -= 1;
}

void remover_tiro(Cenario * cenario, int i){
    Tiro aux = cenario->tiros[i];
    cenario->tiros[i] = cenario->tiros[cenario->qtd_tiros - 1];
    cenario->tiros[cenario->qtd_tiros - 1] = aux;
    cenario->qtd_tiros -= 1;
}

void cenario_remove_elements(Cenario * cenario){
    for(i = cenario->qtd_aliens - 1; i >= 0; i--){
        if(cenario->aliens[i].rect.exist == False){
            remover_alien(cenario, i);
            return;
        }
    }
    for(i = cenario->qtd_tiros - 1; i >= 0; i--){
        if(cenario->tiros[i].rect.exist == False){
            remover_tiro(cenario, i);
            return;
        }
    }
}

//################  UPDATE #####################

void cenario_update_elementos(Cenario * cenario){
    for(i = 0;i<cenario->qtd_aliens;i++){
        alien_perseguir(&cenario->aliens[i],&cenario->nave);
        alien_update(&cenario->aliens[i]);
    }
    for(i = 0; i < cenario->qtd_aliens; i++)
        alien_update(&cenario->aliens[i]);
    for(i = 0; i < cenario->qtd_tiros; i++)
        tiro_update(&cenario->tiros[i]);
    nave_update(&cenario->nave);
}

void cenario_update_aliens_mortos(Cenario * cenario){
    for(i = 0;i < cenario->qtd_aliens_mortos; i++){
        alien_update_mortos(&cenario->aliens_mortos[i]);
    }
}

void cenario_update_vida_nave(Cenario * cenario){
    if(aliens_mortos == 10){
        cenario->nave.life++;
        aliens_mortos = 0;
    }
}
