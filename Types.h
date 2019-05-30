//Types.h
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define false 0;
#define true 1;

#ifndef ESTRUTURAS
#define ESTRUTURAS

const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_BITMAP *fundo = NULL,* imagemplay =NULL;
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_AUDIO_STREAM *musica = NULL,* musicaplay=NULL;
ALLEGRO_SAMPLE *sample = NULL,*samplePontuacao=NULL;
ALLEGRO_SAMPLE *sampleSelect = NULL;
ALLEGRO_FONT *fonte_1 = NULL;
ALLEGRO_BITMAP *area_central = 0,*garrafa = NULL,*flor[4] ={NULL,NULL,NULL,NULL},*regador =NULL , * lixo[4] = {NULL,NULL,NULL,NULL};//fase 1
ALLEGRO_BITMAP *ceringa=NULL,*baleia[4]={NULL,NULL,NULL,NULL},*lixos[2]={NULL,NULL},*mar[3]={NULL,NULL,NULL},*torneira[3]={NULL,NULL,NULL},*lata=NULL;//fases 2 e 3
ALLEGRO_BITMAP *boneco = NULL,*boneco_regador[2]={NULL,NULL},*boneco_vidro=NULL,*boneco_ceringa=NULL,*boneco_lata=NULL,*informacao=NULL;// boneco e suas interacoes 
ALLEGRO_TIMER *timer =NULL;

int tela=0;
int  inicializar();

typedef struct PLAYER{
	char nome[4];
	int pont;
}PLAYER;
#endif