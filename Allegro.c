#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#define TAMANHO_TELA_X 1080
#define TAMANHO_TELA_Y 600
#define PI 3.1415
#define TAMANHO_ARCO 60
#define METADE_TELA_X (TAMANHO_TELA_X/2)
#define METADE_TELA_Y (TAMANHO_TELA_Y/2)
#define INIMIGO 1
#define ALIADO 0
#define X_INICIO (METADE_TELA_X+25)

struct posicao{
    double x, y;
};

struct entidades {
    double spawn_x;
    double spawn_y;
    double cat_adj;
    double cat_opo;
    int tamanho;
    int tipo;
};

struct canhao {
    double spawn_x;
    double spawn_y;
    double mouseX;
    double mouseY;
    double dir;
    int tamanho;
};

void Game_over(ALLEGRO_FONT *font, int mouseX, int mouseY, int pontos, int flag, int *pontuacao_maxima){
    al_draw_filled_rectangle(0, 0 ,TAMANHO_TELA_X, TAMANHO_TELA_Y, al_map_rgb(0,0,0));

    al_draw_textf(font, al_map_rgb(255,255,255), X_INICIO, TAMANHO_TELA_Y/2-190, ALLEGRO_ALIGN_CENTER, "Sua pontuacao foi de: %d pontos!", pontos);

    if(flag==0){
        char acabou[20]="VOCE PERDEU!";
        al_draw_text(font,al_map_rgb(255,255,255),X_INICIO,TAMANHO_TELA_Y/2-200,ALLEGRO_ALIGN_CENTER,acabou);
    }

    if(flag==1){
        char acabou[20]="VOCE GANHOU!";
        al_draw_text(font,al_map_rgb(255,255,255),X_INICIO,TAMANHO_TELA_Y/2-200,ALLEGRO_ALIGN_CENTER,acabou);
    }

    if(pontos>*pontuacao_maxima){
        char pontuacao[30]="NOVA PONTUACAO MAXIMA!";
        al_draw_text(font,al_map_rgb(255,255,255),X_INICIO,TAMANHO_TELA_Y/2-250,ALLEGRO_ALIGN_CENTER,pontuacao);
        *pontuacao_maxima=pontos;
    }

    al_draw_textf(font, al_map_rgb(255,255,255), X_INICIO, TAMANHO_TELA_Y/2-180, ALLEGRO_ALIGN_CENTER, "Sua pontuacao maxima e de: %d pontos!", *pontuacao_maxima);


    char reiniciar[20]="Reiniciar";
    al_draw_filled_rectangle(TAMANHO_TELA_X/2-150,TAMANHO_TELA_Y/2-150, TAMANHO_TELA_X/2+200,TAMANHO_TELA_Y/2-50,al_map_rgb(255,255,255));
    al_draw_text(font,al_map_rgb(0,0,0),X_INICIO,TAMANHO_TELA_Y/2-100,ALLEGRO_ALIGN_CENTER,reiniciar);

    char menu_principal[20]="Menu principal";
    al_draw_filled_rectangle(TAMANHO_TELA_X/2-150,TAMANHO_TELA_Y/2, TAMANHO_TELA_X/2+200,TAMANHO_TELA_Y/2+100,al_map_rgb(255,255,255));
    al_draw_text(font,al_map_rgb(0,0,0),X_INICIO,TAMANHO_TELA_Y/2+50,ALLEGRO_ALIGN_CENTER,menu_principal);

    char sair[20]="Sair do jogo";
    al_draw_filled_rectangle(TAMANHO_TELA_X/2-150, TAMANHO_TELA_Y/2+150, TAMANHO_TELA_X/2+200, TAMANHO_TELA_Y/2+250, al_map_rgb(255,255,255));
    al_draw_text(font,al_map_rgb(0,0,0),X_INICIO,TAMANHO_TELA_Y/2+200,ALLEGRO_ALIGN_CENTER,sair);

}

void Pause(ALLEGRO_FONT *font, int mouseX, int mouseY){
    char jogar[20]="Continuar";
    al_draw_filled_rectangle(TAMANHO_TELA_X/2-150,TAMANHO_TELA_Y/2-150, TAMANHO_TELA_X/2+200,TAMANHO_TELA_Y/2-50,al_map_rgb(255,255,255));
    al_draw_text(font,al_map_rgb(0,0,0),X_INICIO,TAMANHO_TELA_Y/2-100,ALLEGRO_ALIGN_CENTER,jogar);

    char tutorial[20]="Menu principal";
    al_draw_filled_rectangle(TAMANHO_TELA_X/2-150,TAMANHO_TELA_Y/2, TAMANHO_TELA_X/2+200,TAMANHO_TELA_Y/2+100,al_map_rgb(255,255,255));
    al_draw_text(font,al_map_rgb(0,0,0),X_INICIO,TAMANHO_TELA_Y/2+50,ALLEGRO_ALIGN_CENTER,tutorial);

    char sair[20]="Sair do jogo";
    al_draw_filled_rectangle(TAMANHO_TELA_X/2-150, TAMANHO_TELA_Y/2+150, TAMANHO_TELA_X/2+200, TAMANHO_TELA_Y/2+250, al_map_rgb(255,255,255));
    al_draw_text(font,al_map_rgb(0,0,0),X_INICIO,TAMANHO_TELA_Y/2+200,ALLEGRO_ALIGN_CENTER,sair);

}

int Hipotenusa(double cateto_adj, double cateto_opo){
    return sqrt((pow(cateto_adj, 2)+pow(cateto_opo, 2)));
}

int Catetos(double spawn_x, double tamanho){
    return spawn_x-tamanho;
}

void Menu(ALLEGRO_FONT *font, int mouseX, int mouseY){
    al_draw_filled_rectangle(0, 0, TAMANHO_TELA_X, TAMANHO_TELA_Y, al_map_rgb(0,0,0));
    al_draw_filled_circle(X_INICIO, TAMANHO_TELA_Y/2-250, 8, al_map_rgb(0,255,0));

    char titulo[10]="CORE 2.0";
    al_draw_text(font,al_map_rgb(255,255,255),X_INICIO,TAMANHO_TELA_Y/2-200,ALLEGRO_ALIGN_CENTER,titulo);

    char jogar[20]="Jogar";
    al_draw_filled_rectangle(TAMANHO_TELA_X/2-150,TAMANHO_TELA_Y/2-150, TAMANHO_TELA_X/2+200,TAMANHO_TELA_Y/2-50,al_map_rgb(255,255,255));
    al_draw_text(font,al_map_rgb(0,0,0),X_INICIO,TAMANHO_TELA_Y/2-100,ALLEGRO_ALIGN_CENTER,jogar);

    char tutorial[20]="Tutorial";
    al_draw_filled_rectangle(TAMANHO_TELA_X/2-150,TAMANHO_TELA_Y/2, TAMANHO_TELA_X/2+200,TAMANHO_TELA_Y/2+100,al_map_rgb(255,255,255));
    al_draw_text(font,al_map_rgb(0,0,0),X_INICIO,TAMANHO_TELA_Y/2+50,ALLEGRO_ALIGN_CENTER,tutorial);

    char sair[20]="Sair";
    al_draw_filled_rectangle(TAMANHO_TELA_X/2-150, TAMANHO_TELA_Y/2+150, TAMANHO_TELA_X/2+200, TAMANHO_TELA_Y/2+250, al_map_rgb(255,255,255));
    al_draw_text(font,al_map_rgb(0,0,0),X_INICIO,TAMANHO_TELA_Y/2+200,ALLEGRO_ALIGN_CENTER,sair);


}

void Tutorial(ALLEGRO_FONT *font, int mouseX, int mouseY){
    al_draw_filled_rectangle(0, 0, TAMANHO_TELA_X, TAMANHO_TELA_Y, al_map_rgb(0,0,0));

    al_draw_rectangle(200, 20, TAMANHO_TELA_X-200, TAMANHO_TELA_Y-40, al_map_rgb(255,255,255), 4);

    char texto1[40] = "USE O MOUSE PARA MOVIMENTAR O ESCUDO";
    al_draw_text(font,al_map_rgb(255,255,255),X_INICIO-350,TAMANHO_TELA_Y/2-275,ALLEGRO_ALIGN_LEFT,texto1);

    char texto2[50] = "PARA ATIRAR APERTE O BOTAO ESQUERDO DO MOUSE";
    al_draw_text(font,al_map_rgb(255,255,255), X_INICIO-350,TAMANHO_TELA_Y/2-250,ALLEGRO_ALIGN_LEFT,texto2);

    char texto3[60] = "PARA ATIVAR O ESCUDO TEMPORARIO APERTE A TECLA ESPACO";
    al_draw_text(font,al_map_rgb(255,255,255),X_INICIO-350,TAMANHO_TELA_Y/2-225,ALLEGRO_ALIGN_LEFT,texto3);

    char texto4[70]= "Esse jogo foi baseado no jogo CORE, o qual o jogador e um circulo,";
    al_draw_text(font,al_map_rgb(0,255,0),X_INICIO-350,TAMANHO_TELA_Y/2-100,ALLEGRO_ALIGN_LEFT,texto4);

    char texto5[70]="o qual tem que se defender por meio de seu escudo e seus tiros.";
    al_draw_text(font,al_map_rgb(0,255,0),X_INICIO-350,TAMANHO_TELA_Y/2-90,ALLEGRO_ALIGN_LEFT,texto5);

    char voltar[20] = "Voltar";
    al_draw_filled_rectangle(TAMANHO_TELA_X/2-150, TAMANHO_TELA_Y/2+150, TAMANHO_TELA_X/2+200, TAMANHO_TELA_Y/2+250, al_map_rgb(255,255,255));
    al_draw_text(font,al_map_rgb(0,0,0),X_INICIO,TAMANHO_TELA_Y/2+200,ALLEGRO_ALIGN_CENTER,voltar);
}


void Criar_tiro(struct canhao tiros[1], int *quantidade_de_tiros, double dir, double mouseX, double mouseY, int *pontos){
    struct canhao novo_tiro;
    novo_tiro.spawn_y=METADE_TELA_Y;
    novo_tiro.spawn_x=METADE_TELA_X;

    if(*pontos==50){
        novo_tiro.tamanho=8;
    }
    else{
        novo_tiro.tamanho=2;
    }
    novo_tiro.dir=dir;
    novo_tiro.mouseX=mouseX;
    novo_tiro.mouseY=mouseY;
    tiros[0]=novo_tiro;
    *quantidade_de_tiros=*quantidade_de_tiros+1;

}

void Deletar_entidade(struct entidades bichos[100], int *quantidade_de_entidades, int pos_inimigo){
    int i;

    for(i=pos_inimigo; i<*quantidade_de_entidades-1; i++){
        bichos[i]=bichos[i+1];
    }

    bichos[*quantidade_de_entidades-1].spawn_y=0;
    bichos[*quantidade_de_entidades-1].spawn_x=0;

    *quantidade_de_entidades = *quantidade_de_entidades-1;
}


void Back_end_canhao(struct canhao tiros[1], int *quantidade_de_tiros, double variacao_tempo, struct entidades bichos[100], int *quantidade_de_entidades, int *pontos, float *tamanho_jogador, double velocidade, int *ricochetes){
    int i;

    double cateto_oposto;
    double cateto_adjacente;
    double hipotenusa;

    if(*quantidade_de_tiros!=0){
        tiros[0].spawn_y = tiros[0].spawn_y+(METADE_TELA_Y-tiros[0].mouseY)*variacao_tempo;
        tiros[0].spawn_x = tiros[0].spawn_x+(METADE_TELA_X-tiros[0].mouseX)*variacao_tempo;


        al_draw_circle(tiros[0].spawn_x, tiros[0].spawn_y, tiros[0].tamanho, al_map_rgb(0, 0, 255), tiros[0].tamanho * 2);

        for(i=0; i<*quantidade_de_entidades; i++){
            cateto_oposto=Catetos(tiros[0].spawn_y, bichos[i].spawn_y);
            cateto_adjacente=Catetos(tiros[0].spawn_x, bichos[i].spawn_x);
            hipotenusa = Hipotenusa(cateto_adjacente, cateto_oposto);

            if(hipotenusa <= bichos[i].tamanho + tiros[0].tamanho){
                if (bichos[i].tipo==INIMIGO){
                    *pontos = *pontos + 2;
                }
                Deletar_entidade(bichos, quantidade_de_entidades, i);
                *quantidade_de_tiros-=1;
                *tamanho_jogador=*tamanho_jogador + 2*(*tamanho_jogador/100);
            }
        }
        if(tiros[0].tamanho==8){
            if(tiros[0].spawn_x>TAMANHO_TELA_X || tiros[0].spawn_x<0 || tiros[0].spawn_y>TAMANHO_TELA_Y || tiros[0].spawn_y<0){
                *ricochetes=*ricochetes+1;
                cateto_oposto=Catetos(METADE_TELA_Y, tiros[0].spawn_y);
                cateto_adjacente=Catetos(METADE_TELA_X, tiros[0].spawn_x);
                hipotenusa=Hipotenusa(cateto_adjacente, cateto_oposto);

                tiros[0].spawn_x=tiros[0].spawn_x+velocidade*(cateto_adjacente)*variacao_tempo;
                tiros[0].spawn_y=tiros[0].spawn_y+velocidade*(cateto_oposto)*variacao_tempo;

                cateto_oposto=Catetos(METADE_TELA_Y, tiros[0].spawn_y);
                cateto_adjacente=Catetos(METADE_TELA_X, tiros[0].spawn_x);

                al_draw_circle(tiros[0].spawn_x, tiros[0].spawn_y, tiros[0].tamanho, al_map_rgb(0, 0, 255), tiros[0].tamanho * 2);

            }
        }
        else{
            if (((tiros[0].spawn_x>TAMANHO_TELA_X) || (tiros[0].spawn_x<0) || (tiros[0].spawn_y>TAMANHO_TELA_Y) || (tiros[0].spawn_y<0)) && (*quantidade_de_tiros==1)) {
                *quantidade_de_tiros -= 1;
            }
        }
    }
}

void Geracao_entidade(struct entidades bichos[100], int *quantidade_de_entidades, int tipo, float *tamanho_jogador) {
    if (*quantidade_de_entidades<100) {
        struct entidades nova_entidade;
        nova_entidade.tamanho =(rand()%3)+1;
        int local=rand()%4;
        int escolha;

        switch(local){
            case 0:
                nova_entidade.spawn_x=0;
            break;

            case 1:
                nova_entidade.spawn_x=TAMANHO_TELA_X;
            break;

            case 2:
            case 3:
                nova_entidade.spawn_x=rand()%TAMANHO_TELA_X+1;
            break;
        }

        if(nova_entidade.spawn_x==0){
            nova_entidade.spawn_y=rand()%TAMANHO_TELA_Y-1;
        }

        else if(nova_entidade.spawn_x==TAMANHO_TELA_X){
            nova_entidade.spawn_y=rand()%TAMANHO_TELA_Y-1;
        }

        else{
            escolha=rand()%2;
            if(escolha==0){
                nova_entidade.spawn_y=0;
            }
            else{
                nova_entidade.spawn_y=TAMANHO_TELA_Y;
            }

        }
        nova_entidade.cat_adj=METADE_TELA_X-nova_entidade.spawn_x+(rand()%(int)*tamanho_jogador*2);
        nova_entidade.cat_opo=METADE_TELA_Y-nova_entidade.spawn_y+(rand()%(int)*tamanho_jogador*2);
        if(tipo==INIMIGO){
            nova_entidade.tipo=INIMIGO;
        }
        else{
            nova_entidade.tipo=ALIADO;
        }

        bichos[*quantidade_de_entidades]=nova_entidade;
        *quantidade_de_entidades=*quantidade_de_entidades + 1;
    }
}

int Verificacao_angulo(float conversao_inimigo, float inicio_arco, float fim_arco) {
    if(inicio_arco<fim_arco)
        return inicio_arco<=conversao_inimigo && conversao_inimigo<=fim_arco;
    return inicio_arco<=conversao_inimigo || conversao_inimigo<=fim_arco;
}


void Back_end_entidades(struct entidades bichos[100], int *quantidade_de_entidades, double variacao_tempo, double velocidade, int *pontos, double angulo_mouse, float *tamanho_jogador, int escudo_especial) {
    int i;

    double angulo_inimigo;
    double cateto_adjacente_att;
    double cateto_oposto_att;
    double hipotenusa;

    double hipotenusa_arco;
    double conversao_mouse;
    double conversao_inimigo;
    double inicio_arco;
    double fim_arco;


    for(i=0; i<*quantidade_de_entidades; i++){
        angulo_inimigo=atan2(bichos[i].spawn_y-METADE_TELA_Y, bichos[i].spawn_x-METADE_TELA_X);

        cateto_oposto_att=Catetos(METADE_TELA_Y, bichos[i].spawn_y);
        cateto_adjacente_att=Catetos(METADE_TELA_X, bichos[i].spawn_x);
        hipotenusa=Hipotenusa(cateto_adjacente_att, cateto_oposto_att);

        bichos[i].spawn_x=bichos[i].spawn_x+velocidade*bichos[i].cat_adj*variacao_tempo;
        bichos[i].spawn_y=bichos[i].spawn_y+velocidade*bichos[i].cat_opo*variacao_tempo;

        cateto_oposto_att=Catetos(METADE_TELA_Y, bichos[i].spawn_y);
        cateto_adjacente_att=Catetos(METADE_TELA_X, bichos[i].spawn_x);

        hipotenusa_arco=Hipotenusa(cateto_adjacente_att, cateto_oposto_att);


        if(angulo_mouse>=0){
            conversao_mouse=((angulo_mouse*180)/PI);
        }
        else{
            conversao_mouse=360-(((angulo_mouse*180)/PI)*-1);
        }


        if(angulo_inimigo>=0){
            conversao_inimigo=((angulo_inimigo*180)/PI);
        }
        else{
            conversao_inimigo=360-((angulo_inimigo*180/PI)*-1);
        }

        inicio_arco=conversao_mouse-90;
        fim_arco=conversao_mouse+90;

        if(fim_arco>=360){
            fim_arco=fim_arco-360;
        }

        if(inicio_arco<0){
            inicio_arco=inicio_arco-360;
        }
        int inimigo_no_angulo_do_escudo=Verificacao_angulo(conversao_inimigo, inicio_arco, fim_arco);


        if(escudo_especial==1){
            if(hipotenusa_arco<TAMANHO_ARCO){
                if (bichos[i].tipo==INIMIGO){
                    *pontos=*pontos+3;
                }
                Deletar_entidade(bichos, quantidade_de_entidades, i);
            }
        }
        else{
            if(hipotenusa>=38 && hipotenusa_arco<TAMANHO_ARCO && inimigo_no_angulo_do_escudo) {
                if(bichos[i].tipo==INIMIGO){
                    *pontos=*pontos+1;
                }
                else if(bichos[i].tipo==ALIADO){}

                Deletar_entidade(bichos, quantidade_de_entidades, i);
            }
            if(bichos[i].tipo==INIMIGO)
                al_draw_circle(bichos[i].spawn_x, bichos[i].spawn_y, bichos[i].tamanho, al_map_rgb(255, 0, 0), bichos[i].tamanho*2);
            else
                al_draw_circle(bichos[i].spawn_x, bichos[i].spawn_y, bichos[i].tamanho, al_map_rgb(0, 255, 0), bichos[i].tamanho*2);
            }
    }
}

void Colisao_entidades(struct entidades bichos[100], int *quantidade_de_entidades, float *tamanho_jogador, int *pontos){
    int i;

    double cateto_oposto_att;
    double cateto_adjacente_att;
    double hipotenusa_att;

    for(i=0; i<*quantidade_de_entidades; i++) {
        cateto_oposto_att=METADE_TELA_Y-bichos[i].spawn_y;
        cateto_adjacente_att=METADE_TELA_X-bichos[i].spawn_x;
        hipotenusa_att=Hipotenusa(cateto_adjacente_att, cateto_oposto_att);

        if(hipotenusa_att<*tamanho_jogador*2){
            if(bichos[i].tipo==INIMIGO){
                *tamanho_jogador=*tamanho_jogador-(float)bichos[i].tamanho/2;
                *pontos=*pontos-1;
            }
            else if (bichos[i].tipo==ALIADO) {
                *tamanho_jogador=*tamanho_jogador+(float)bichos[i].tamanho/2;
                *pontos=*pontos+1;
            }
            Deletar_entidade(bichos, quantidade_de_entidades, i);
            }
        }

}


int main(void) {
    srand(time(0));

    ALLEGRO_FONT *font = NULL;
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_ttf_addon();


    fila_eventos = al_create_event_queue();

    janela = al_create_display(TAMANHO_TELA_X, TAMANHO_TELA_Y);
    font = al_create_builtin_font();

    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    al_register_event_source(fila_eventos, al_get_mouse_event_source());

    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    struct entidades bichos[100];
    struct canhao tiros[1];

    double lastTempo = 0, tempo = 0, variacao_tempo = 0, tempo2 = 0;
    double tempo_inicial2 = al_get_time(), tempo_canhao=0, tempo_escudo=0, tempo_inicial_escudo=0;
    double velocidade=0;
    double angulo_mouse=0;
    double angulo_canhao;
    double dir=0;
    double cronometro_pause=0;
    double last_hit=0;
    double cronometro_display=0;

    int pontos = 0;
    int nivel = 1;
    int vidas = 3;
    int cont_vidas_novas= 1;
    int renderizar_escudo_especial=0;
    int cont_escudo=1;
    int rodando = 1, mouseX = 0, mouseY = 0;
    int quantidade_de_entidades = 0;
    int quantidade_de_tiros = 0;
    int novos_bichos = 0;
    int menu=1;
    int Controle_menu=1;
    int pause=0;
    int tamanho_escudo_especial=60;
    int cont_parar_escudo=0;
    int duracao_escudo;
    int pode_pausar=1;
    int ricochetes=0;
    int perdeu=0;
    int pontuacao_maxima=0;

    float tamanho_jogador = 7;

    while (rodando) {

            if(tamanho_jogador>=TAMANHO_ARCO/2){
                Game_over(font, mouseX, mouseY, pontos, 1, &pontuacao_maxima);
                perdeu=1;
            }

            if(vidas==0){
                Game_over(font, mouseX, mouseY, pontos, 0, &pontuacao_maxima);
                perdeu=1;
            }

            if((int)tamanho_jogador<=0 && vidas>0){
                vidas--;
                tamanho_jogador=7;
            }

            if(menu==1){
                cronometro_pause=al_get_time();
                cronometro_display=tempo-cronometro_pause;

            }

            if(menu==0 && pause==0 && perdeu==0){
                angulo_mouse = atan2(mouseY - METADE_TELA_Y, mouseX - METADE_TELA_X);
                angulo_canhao = angulo_mouse + 2*PI;
                dir = angulo_canhao;

                cronometro_display=tempo-cronometro_pause;

                if(pontos>=30*nivel){
                    nivel++;
                    pode_pausar=1;
                }



                if(nivel==cont_vidas_novas*10){
                    vidas++;
                    cont_vidas_novas++;
                }


                lastTempo = tempo;
                tempo =al_get_time();

                variacao_tempo = (tempo - lastTempo);


                tempo2 = al_get_time();

                velocidade = 0.1+((float)nivel/100)*!pause;
            }

            while (!al_is_event_queue_empty(fila_eventos))
            {
                ALLEGRO_EVENT evento;
                al_wait_for_event(fila_eventos, &evento);

            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                rodando = 0;
            }

            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
                mouseX = evento.mouse.x;
                mouseY = evento.mouse.y;
            }

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if(menu==1 && pause==0){
                        if(Controle_menu == 1 && mouseX >= TAMANHO_TELA_X/2-150 && mouseX <= TAMANHO_TELA_X/2+200 && mouseY >= TAMANHO_TELA_Y/2-150 && mouseY <= TAMANHO_TELA_Y/2-50){
                            Controle_menu = 0;
                            lastTempo = 0;
                            tempo = 0;
                            variacao_tempo = 0;
                            tempo2 = 0;
                            tempo_inicial2 = al_get_time(), tempo_canhao=0, tempo_escudo=0, tempo_inicial_escudo=0;
                            velocidade=0;
                            angulo_mouse=0;
                            angulo_canhao=0;
                            dir=0;
                            cronometro_pause=0;
                            last_hit=0;
                            cronometro_display=0;
                            pontos = 0;
                            nivel = 3;
                            vidas = 3;
                            cont_vidas_novas= 1;
                            renderizar_escudo_especial=0;
                            cont_escudo=1;
                            quantidade_de_entidades = 0;
                            quantidade_de_tiros = 0;
                            novos_bichos = 0;
                            pause=0;
                            tamanho_escudo_especial=60;
                            cont_parar_escudo=0;
                            ricochetes=0;
                            tamanho_jogador=7;
                            pode_pausar=1;
                            perdeu=0;

                        }
                        if(Controle_menu == 1 && mouseX >= TAMANHO_TELA_X/2-150 && mouseX <= TAMANHO_TELA_X/2+200 && mouseY >= TAMANHO_TELA_Y/2 && mouseY <= TAMANHO_TELA_Y/2+100){
                            Controle_menu = 2;
                        }
                        if(Controle_menu==1 && mouseX >= TAMANHO_TELA_X/2-150 && mouseX <=TAMANHO_TELA_X/2+200 && mouseY>= TAMANHO_TELA_Y/2+150 && mouseY <= TAMANHO_TELA_Y/2+250){
                            exit(0);
                        }
                        if(Controle_menu==2 && mouseX >= TAMANHO_TELA_X/2-150 && mouseX <=TAMANHO_TELA_X/2+200 && mouseY>= TAMANHO_TELA_Y/2+150 && mouseY <= TAMANHO_TELA_Y/2+250){
                            Controle_menu=1;
                        }
                    }

                    if(pause==1){
                        if(mouseX >= TAMANHO_TELA_X/2-150 && mouseX <= TAMANHO_TELA_X/2+200 && mouseY >= TAMANHO_TELA_Y/2-150 && mouseY <= TAMANHO_TELA_Y/2-50){
                            pause = 0;
                        }
                        if(mouseX >= TAMANHO_TELA_X/2-150 && mouseX <= TAMANHO_TELA_X/2+200 && mouseY >= TAMANHO_TELA_Y/2 && mouseY <= TAMANHO_TELA_Y/2+100){
                            menu=1;
                            Controle_menu=1;
                        }
                        if(mouseX >= TAMANHO_TELA_X/2-150 && mouseX <=TAMANHO_TELA_X/2+200 && mouseY>= TAMANHO_TELA_Y/2+150 && mouseY <= TAMANHO_TELA_Y/2+250){
                            exit(0);
                        }
                    }

                    if(perdeu==1){
                        if(mouseX >= TAMANHO_TELA_X/2-150 && mouseX <= TAMANHO_TELA_X/2+200 && mouseY >= TAMANHO_TELA_Y/2-150 && mouseY <= TAMANHO_TELA_Y/2-50){
                            Controle_menu = 0;
                            lastTempo = 0;
                            tempo = 0;
                            variacao_tempo = 0;
                            tempo2 = 0;
                            tempo_inicial2 = al_get_time(), tempo_canhao=0, tempo_escudo=0, tempo_inicial_escudo=0;
                            velocidade=0;
                            angulo_mouse=0;
                            angulo_canhao=0;
                            dir=0;
                            cronometro_pause=0;
                            last_hit=0;
                            cronometro_display=0;
                            pontos = 0;
                            nivel = 1;
                            vidas = 3;
                            cont_vidas_novas= 1;
                            renderizar_escudo_especial=0;
                            cont_escudo=1;
                            quantidade_de_entidades = 0;
                            quantidade_de_tiros = 0;
                            novos_bichos = 0;
                            pause=0;
                            tamanho_escudo_especial=60;
                            cont_parar_escudo=0;
                            ricochetes=0;
                            tamanho_jogador=7;
                            pode_pausar=1;
                            perdeu=0;
                        }
                        if(mouseX >= TAMANHO_TELA_X/2-150 && mouseX <= TAMANHO_TELA_X/2+200 && mouseY >= TAMANHO_TELA_Y/2 && mouseY <= TAMANHO_TELA_Y/2+100){
                            menu=1;
                            Controle_menu=1;
                        }
                        if(mouseX >= TAMANHO_TELA_X/2-150 && mouseX <=TAMANHO_TELA_X/2+200 && mouseY>= TAMANHO_TELA_Y/2+150 && mouseY <= TAMANHO_TELA_Y/2+250){
                            exit(0);
                        }
                    }

                    tempo_canhao=al_get_time();
                    if(quantidade_de_tiros==0 && menu==0 && tempo_canhao-last_hit>1){
                        Criar_tiro(tiros, &quantidade_de_tiros, dir, mouseX, mouseY, &pontos);
                        last_hit=tempo;
                    }
            }


            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (evento.keyboard.keycode) {
                    case ALLEGRO_KEY_SPACE:
                        tempo_escudo=al_get_time();
                        if(nivel%3==0 && menu==0){
                            renderizar_escudo_especial=1;
                            cont_escudo++;
                            tempo_escudo=al_get_time();
                            tamanho_escudo_especial=60;
                            duracao_escudo=(rand()%10)+5;
                            if(duracao_escudo>10){
                                duracao_escudo=duracao_escudo-4;
                            };
                        }
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        if(menu==0 && pode_pausar==1){
                            if(pause==0){
                                pause=1;
                                cronometro_pause=al_get_time();
                                pode_pausar=0;
                            }
                            else{
                                pause=0;
                            }
                        }
                        break;
                }
            }

            if (evento.type == ALLEGRO_EVENT_KEY_UP) {
                switch (evento.keyboard.keycode) {
                }
            }
        }

        if(menu==0 && pause==0 && perdeu==0){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            }

        if(pause==1){
            tempo = lastTempo;
            cronometro_pause=al_get_time()-tempo;
            Pause(font, mouseX, mouseY);
        }

        if(pause==0 && perdeu==0){
            ALLEGRO_BITMAP *canhao_front = al_create_bitmap(30,30);
            al_set_target_bitmap(canhao_front);
            struct posicao v1={0, 30/2};
            struct posicao v2={30, 0};
            struct posicao v3={30, 30};
            al_draw_filled_triangle(v1.x,v1.y,v2.x,v2.y,v3.x,v3.y, al_map_rgb(255,255,0));
            al_set_target_backbuffer(janela);
            al_draw_rotated_bitmap(canhao_front, 65, 30/2, METADE_TELA_X, METADE_TELA_Y, angulo_mouse, 0);

            Colisao_entidades(bichos, &quantidade_de_entidades, &tamanho_jogador, &pontos);
            Back_end_canhao(tiros, &quantidade_de_tiros, variacao_tempo, bichos, &quantidade_de_entidades, &pontos, &tamanho_jogador, velocidade, &ricochetes);

            if ((tempo2 - tempo_inicial2)>(0.1/(velocidade/2))){
                novos_bichos=novos_bichos+rand()%5;
                Geracao_entidade(bichos, &quantidade_de_entidades, INIMIGO, &tamanho_jogador);
                if(novos_bichos >= 10){
                    Geracao_entidade(bichos, &quantidade_de_entidades, ALIADO, &tamanho_jogador);
                    novos_bichos=0;
                }
                tempo_inicial2=al_get_time();
            }

            al_draw_circle(METADE_TELA_X, METADE_TELA_Y, tamanho_jogador, al_map_rgb(0, 255, 0), tamanho_jogador*2);
            al_draw_arc(METADE_TELA_X, METADE_TELA_Y, TAMANHO_ARCO, angulo_mouse-PI/2, PI, al_map_rgb(255, 255, 255), 4);

            if((pause==0 || pause==1) && perdeu==0){
                Back_end_entidades(bichos, &quantidade_de_entidades, variacao_tempo, velocidade, &pontos, angulo_mouse, &tamanho_jogador, 0);
            }

            if(renderizar_escudo_especial==1){
                Back_end_entidades(bichos, &quantidade_de_entidades, variacao_tempo, velocidade, &pontos, angulo_mouse, &tamanho_jogador, 1);
                al_draw_circle(METADE_TELA_X, METADE_TELA_Y, tamanho_escudo_especial, al_map_rgb(255, 255, 255), 4);

                tempo_escudo=al_get_time();
                if(tempo_escudo-tempo_inicial_escudo>1){
                    tamanho_escudo_especial=tamanho_escudo_especial-(tamanho_escudo_especial/duracao_escudo);
                    cont_parar_escudo++;
                    tempo_inicial_escudo=tempo_escudo;
                    tamanho_jogador=tamanho_jogador-(tamanho_jogador*(1/100));
                }
                if(cont_parar_escudo==duracao_escudo){
                    renderizar_escudo_especial=0;
                    cont_parar_escudo=0;
                }

            }

            al_draw_filled_rectangle(0,0,TAMANHO_TELA_X, 20, al_map_rgb(0,0,0));
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 10, ALLEGRO_ALIGN_LEFT, "Pontuacao: %d", pontos);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 200, 10, ALLEGRO_ALIGN_LEFT, "Tamanho Jogador: %.2f", tamanho_jogador);
            al_draw_textf(font, al_map_rgb(255,255,255), 600, 10, ALLEGRO_ALIGN_LEFT, "Tempo: %.2f", cronometro_display);
            al_draw_textf(font, al_map_rgb(255,255,255), 800, 10, ALLEGRO_ALIGN_LEFT, "Nivel: %d", nivel);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 1000, 10, ALLEGRO_ALIGN_LEFT, "Vidas: %d", vidas);

            char texto_pause[20] = "Pause disponivel!!!";
            if(pode_pausar==1){
                al_draw_text(font, al_map_rgb(255,255,255), 420, 10, ALLEGRO_ALIGN_LEFT, texto_pause);
            }
        }

        if(menu==1){
            if(Controle_menu==2)
        {
            Tutorial(font,mouseX,mouseY);
        }
        if(Controle_menu==1)
        {
            Menu(font,mouseX,mouseY);
        }
        if(Controle_menu==0)
        {
            menu=0;

        }

        }

        al_flip_display();

    }

    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
