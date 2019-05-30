//main.cpp
#include"Types.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>


FILE *criarArquivo(char nome[]){
	FILE * arq;
	PLAYER aux;
	int resp;
	strcpy(aux.nome,"---");aux.pont=0;
	arq = fopen(nome, "r+b");
	if (arq == NULL){
		arq = fopen(nome, "w+b");
		for(int i =0 ; i<5;i++){
			resp=fwrite(&aux,sizeof(PLAYER),1,arq);
			if(resp!=1){
				printf("Erro ao escrever no arquivo!\n");
			}
		}
	}
	return arq;
}

void arq_open(PLAYER score[],FILE *arq)  {
	int resp;
	PLAYER aux;
	fseek(arq,0,0);
	for(int i =0 ; i<5;i++){
		resp = fread (&score[i], sizeof(PLAYER),1,arq);
		if(resp!=1){
			fprintf(stderr, "Falha na leitura do arquivo!\n");
		}
	}
}

void arq_close(PLAYER score[],FILE *arq){
	int resp,i;
	PLAYER aux;
	fseek(arq,0,0);
	for(int i =0 ; i<5;i++){
		resp=fwrite(&score[i],sizeof(PLAYER),1,arq);
		if(resp!=1){
			fprintf(stderr, "Falha na leitura do arquivo!\n");
		}
	}
}

void push(PLAYER score[],char nome[],int pont){
	PLAYER aux,aux2;
	int i=4;
	strcpy(aux.nome,nome);aux.pont=pont;
	while(aux.pont > score[i].pont && i>=0){
		score[i+1]=score[i];
		score[i]=aux;
		i--;
	}
}

void destroy(){
	if(janela)al_destroy_display(janela);
	if(fonte)al_destroy_font(fonte);
	if(fonte_1)al_destroy_font(fonte_1);
	if(fila_eventos)al_destroy_event_queue(fila_eventos);
	if(area_central)al_destroy_bitmap(area_central);
	if(fundo)al_destroy_bitmap(fundo);
	if(sample)al_destroy_sample(sample);
	if(musica)al_destroy_audio_stream(musica);
	if(sampleSelect)al_destroy_sample(sampleSelect);
	if(boneco)al_destroy_bitmap(boneco);
	if(imagemplay)al_destroy_bitmap(imagemplay);
	if(timer)al_destroy_timer(timer);
	if(musicaplay)al_destroy_audio_stream(musicaplay);
	if(boneco_regador[0])al_destroy_bitmap(boneco_regador[0]);
	if(boneco_regador[1])al_destroy_bitmap(boneco_regador[1]);
	if(boneco_vidro)al_destroy_bitmap(boneco_vidro);
	if(garrafa)al_destroy_bitmap(garrafa);
	if(flor[0])al_destroy_bitmap(flor[0]);
	if(flor[1])al_destroy_bitmap(flor[1]);
	if(flor[2])al_destroy_bitmap(flor[2]);
	if(flor[3])al_destroy_bitmap(flor[3]); 
	if(regador)al_destroy_bitmap(regador);
	if(lixo[0])al_destroy_bitmap(lixo[0]);
	if(lixo[1])al_destroy_bitmap(lixo[1]);
	if(lixo[2])al_destroy_bitmap(lixo[2]);
	if(lixo[3])al_destroy_bitmap(lixo[3]);
	if(samplePontuacao)al_destroy_sample(samplePontuacao);
	if(lixos[0])al_destroy_bitmap(lixos[0]);
	if(lixos[1])al_destroy_bitmap(lixos[1]);
	if(mar[0])al_destroy_bitmap(mar[0]);
	if(mar[1])al_destroy_bitmap(mar[1]);
	if(mar[2])al_destroy_bitmap(mar[2]);
	if(torneira[0])al_destroy_bitmap(torneira[0]);
	if(torneira[1])al_destroy_bitmap(torneira[1]);
	if(torneira[2])al_destroy_bitmap(torneira[2]);
	if(baleia[0])al_destroy_bitmap(baleia[0]);
	if(baleia[1])al_destroy_bitmap(baleia[1]);
	if(baleia[2])al_destroy_bitmap(baleia[2]);
	if(baleia[3])al_destroy_bitmap(baleia[3]);
	if(ceringa)al_destroy_bitmap(ceringa);
	if(boneco_ceringa)al_destroy_bitmap(boneco_ceringa);
	if(boneco_lata)al_destroy_bitmap(boneco_lata);
	if(lata)al_destroy_bitmap(lata);
	if(informacao)al_destroy_bitmap(informacao);
}

int  inicializar(){

	//inicializando 
	al_init();
	if (!al_init()){
		fprintf(stderr, "Falha ao inicializar a Allegro.\n");
		return false;
	}

	al_init_font_addon();
	if (!al_init_ttf_addon()){
		fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
		return false;
	}

	al_install_audio();
	if (!al_install_audio()){
		fprintf(stderr, "Falha ao inicializar áudio.\n");
		return false;
	}

	al_init_acodec_addon();
	if (!al_init_acodec_addon()){
		fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
		return false;
	}

	if (!al_reserve_samples(1)){
		fprintf(stderr, "Falha ao alocar canais de áudio.\n");
		return false;
	}

	al_init_image_addon();
	if (!al_init_image_addon()){
		fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
		return false;
	}

	al_install_keyboard();
	if (!al_install_keyboard()){
		fprintf(stderr, "Falha ao inicializar o teclado.\n");
		return false;
	}

	al_init_primitives_addon();
	if(!al_init_primitives_addon()){
		fprintf(stderr,"Falha no treco geometrico!\n");
		return false;
	}

	al_install_mouse();
	if (!al_install_mouse())
	{
		fprintf(stderr, "Falha ao inicializar o mouse.\n");
		return false;
	}


	// criacao dos objetos usados 
	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);// janela
	if (!janela){
		fprintf(stderr, "Falha ao criar janela.\n");
		return false;
	}
	al_set_window_title(janela, "ECO PLAY");

	fonte = al_load_font("Mario.ttf", 48, 0);// fonte 48
	if (!fonte){
		fprintf(stderr, "Falha ao carregar fonte 48\n");
		destroy();
		return false;
	}

	fonte_1 = al_load_font("Mario.ttf", 24, 0);// fonte 24
	if (!fonte_1){
		fprintf(stderr, "Falha ao carregar fonte 24.\n");
		destroy();
		return false;
	}

	fila_eventos = al_create_event_queue();// fila de eventos 
	if (!fila_eventos){
		fprintf(stderr, "Falha ao criar fila de eventos.\n");
		destroy();
		return false;
	}

	area_central = al_create_bitmap(LARGURA_TELA / 2, ALTURA_TELA / 2);
	if (!area_central)
	{
		fprintf(stderr, "Falha ao criar bitmap.\n");
		destroy();
		return -1;
	}

	fundo = al_load_bitmap("fundo_1.jpg");// tela de fundo
	if (!fundo){
		fprintf(stderr, "Falha ao carregar imagem de fundo.\n");
		destroy();
		return false;
	}

	sample = al_load_sample("TECLA.wav");// som de acao
	if (!sample){
		fprintf(stderr, "Falha ao carregar sample.\n");
		destroy();
		return false;
	}

	musica = al_load_audio_stream("MENU.wav", 4, 1024);// musica do menu 
	if (!musica){
		fprintf(stderr, "Falha ao carregar audio.\n");
		destroy();
		return false;
	}

	sampleSelect = al_load_sample("SELECT.wav"); // musica do delect 
	if (!sampleSelect){
		fprintf(stderr, "Falha ao carregar audio.\n");
		destroy();
		return false;
	}

	boneco=al_load_bitmap("boneco.png"); // sptrite boneco
	if(!boneco){
		fprintf(stderr,"Fudeu boneco\n!");
		destroy();
		return false;
	}

	imagemplay = al_load_bitmap("fundo_2.jpg");// tela de fundo das fases
	if (!imagemplay){
		fprintf(stderr, "Falha ao carregar imagem de fundo.\n");
		destroy();
		return false;
	}

	timer = al_create_timer(0.1); // timer contador 
	if (!timer){
		fprintf(stderr, "Falha ao criar timer.\n");//precisa colocar al_destroy_timer(timer);
		destroy();
		return false;
	}

	musicaplay = al_load_audio_stream("playaudio.wav", 4, 1024); //musica  de fases 
	if (!musicaplay){
		fprintf(stderr, "Falha ao carregar audio.\n");
		destroy();
		return false;
	}

	samplePontuacao = al_load_sample("PONTUACAO.wav"); // musica de pontuacao
	if (!samplePontuacao){
		fprintf(stderr, "Falha ao carregar audio de pontuacao.\n");
		destroy();
		return false;
	}

	// sprites de acao

	boneco_regador[0]=al_load_bitmap("boneco_regador_1.png");
	if(!boneco_regador[0]){
		fprintf(stderr,"Fudeu boneco_regador_1\n!");
		destroy();
		return false;
	}

	boneco_regador[1]=al_load_bitmap("boneco_regador_2.png");
	if(!boneco_regador[1]){
		fprintf(stderr,"Fudeu boneco_regador_2\n!");
		destroy();
		return false;
	}

	boneco_vidro=al_load_bitmap("boneco_vidro.png");
	if(!boneco_vidro){
		fprintf(stderr,"Fudeu boneco_vidro\n!");
		destroy();
		return false;
	}

	garrafa=al_load_bitmap("garrafa.png");
	if(!garrafa){
		fprintf(stderr,"Fudeu garrafa\n!");
		destroy();
		return false;
	}

	flor[0]=al_load_bitmap("flor0.png");
	if(!flor[0]){
		fprintf(stderr,"Fudeu flor0\n!");
		destroy();
		return false;
	}

	flor[1]=al_load_bitmap("flor1.png");
	if(!flor[1]){
		fprintf(stderr,"Fudeu flor1\n!");
		destroy();
		return false;
	}

	flor[2]=al_load_bitmap("flor2.png");
	if(!flor[2]){
		fprintf(stderr,"Fudeu flor2\n!");
		destroy();
		return false;
	}

	flor[3]=al_load_bitmap("flor3.png");
	if(!flor[3]){
		fprintf(stderr,"Fudeu flor3\n!");
		destroy();
		return false;
	}

	regador=al_load_bitmap("regador.png");
	if(!regador){
		fprintf(stderr,"Fudeu regador\n!");
		destroy();
		return false;
	}

	lixo[0]=al_load_bitmap("lixo_vermelho.png");
	if(!lixo[0]){
		fprintf(stderr,"Fudeu lixo_vermelho\n!");
		destroy();
		return false;
	}

	lixo[1]=al_load_bitmap("lixo_azul.png");
	if(!lixo[1]){
		fprintf(stderr,"Fudeu lixo_azul\n!");
		destroy();
		return false;
	}

	lixo[2]=al_load_bitmap("lixo_amarelo.png");
	if(!lixo[2]){
		fprintf(stderr,"Fudeu lixo_amarelo\n!");
		destroy();
		return false;
	}

	lixo[3]=al_load_bitmap("lixo_verde.png");
	if(!lixo[3]){
		fprintf(stderr,"Fudeu lixo_verde\n!");
		destroy();
		return false;
	}

	lixos[0]=al_load_bitmap("lixo_reciclavel.png");
	if(!lixos[0]){
		fprintf(stderr,"Fudeu lixo_reciclavel\n!");
		destroy();
		return false;
	}

	lixos[1]=al_load_bitmap("lixo_hosp.png");
	if(!lixos[1]){
		fprintf(stderr,"Fudeu lixo_hosp\n!");
		destroy();
		return false;
	}

	mar[0]=al_load_bitmap("mar_0.png");
	if(!mar[0]){
		fprintf(stderr,"Fudeu mar_0\n!");
		destroy();
		return false;
	}

	mar[1]=al_load_bitmap("mar_1.png");
	if(!mar[1]){
		fprintf(stderr,"Fudeu mar_1\n!");
		destroy();
		return false;
	}

	mar[2]=al_load_bitmap("mar_2.png");
	if(!mar[2]){
		fprintf(stderr,"Fudeu mar_2\n!");
		destroy();
		return false;
	}

	torneira[0]=al_load_bitmap("torneira.png");
	if(!torneira[0]){
		fprintf(stderr,"Fudeu torneira\n!");
		destroy();
		return false;
	}

	torneira[1]=al_load_bitmap("torneira_pingo_0.png");
	if(!torneira[1]){
		fprintf(stderr,"Fudeu torneira_pingo_0\n!");
		destroy();
		return false;
	}

	torneira[2]=al_load_bitmap("torneira_pingo_1.png");
	if(!torneira[2]){
		fprintf(stderr,"Fudeu torneira_pingo_1\n!");
		destroy();
		return false;
	}

	baleia[0]=al_load_bitmap("baleia_0.png");
	if(!baleia[0]){
		fprintf(stderr,"Fudeu baleia_0\n!");
		destroy();
		return false;
	}

	baleia[1]=al_load_bitmap("baleia_1.png");
	if(!baleia[1]){
		fprintf(stderr,"Fudeu baleia_1\n!");
		destroy();
		return false;
	}

	baleia[2]=al_load_bitmap("baleia_2.png");
	if(!baleia[2]){
		fprintf(stderr,"Fudeu baleia_2\n!");
		destroy();
		return false;
	}

	baleia[3]=al_load_bitmap("baleia_3.png");
	if(!baleia[3]){
		fprintf(stderr,"Fudeu baleia_3\n!");
		destroy();
		return false;
	}

	ceringa=al_load_bitmap("ceringa.png");
	if(!ceringa){
		fprintf(stderr,"Fudeu ceringa\n!");
		destroy();
		return false;
	}

	boneco_ceringa=al_load_bitmap("boneco_ceringa.png");
	if(!boneco_ceringa){
		fprintf(stderr,"Fudeu boneco_ceringa\n!");
		destroy();
		return false;
	}

	boneco_lata=al_load_bitmap("boneco_lata.png");
	if(!boneco_lata){
		fprintf(stderr,"Fudeu boneco_lata\n!");
		destroy();
		return false;
	}

	lata=al_load_bitmap("lata.png");
	if(!lata){
		fprintf(stderr,"Fudeu lata\n!");
		destroy();
		return false;
	}

	informacao=al_load_bitmap("informacao.png");
	if(!informacao){
		fprintf(stderr,"Fudeu informacao\n!");
		destroy();
		return false;
	}

	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	return true;
}

int main(void){// como funciona a fila ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	float raio = 0, x=300 , y=220;
	int dir_x = 1, dir_y = 1, pont=1000, op=0, sair = false;
	int acao=0,seg=0,cont=30,concluido=0,transicao=0,contt=0,level=0,personagem=3,opp=0,opr=0,opv=0,pontuacao=0,animacaop3=0,trasicaomenu=0,p=0;
	char str[4],nome[4];
	PLAYER score[6];
	FILE *arq=NULL;
	strcpy(str,"");
	x = raio; 
	y = raio;

	arq=criarArquivo("score.txt");
	arq_open(score,arq);

	/*
	strcpy(score[0].nome,"---");score[0].pont=0;
	strcpy(score[1].nome,"---");score[1].pont=0;
	strcpy(score[2].nome,"---");score[2].pont=0;
	strcpy(score[3].nome,"---");score[3].pont=0;
	strcpy(score[4].nome,"---");score[4].pont=0;
	*/

	if (!inicializar()){
		return 0;
	}

	al_draw_bitmap(fundo, 0, 0, 0);

	al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());//setar a musica no mixer 

	al_set_audio_stream_playing(musica, 1);//play na musica (1 play 0 pausa)
	al_start_timer(timer);//star do contador 

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++CONTROLE DE TELAS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	while (!sair){
		while(!al_is_event_queue_empty(fila_eventos)){// se nao tem evento na fila
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);// verifica a fila de ventos e deposita o prox evento em "evento"
			if(tela>=0 && tela<=5){// ****************************************** controle do menu  *********************************************
				if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){ // controle do mouse
					if(evento.mouse.x >= 250 && evento.mouse.x <= 384 && evento.mouse.y >= 212 && evento.mouse.y <= 248){
						if(tela==0 || tela ==1 || tela==2 || tela==3){
							al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=1;
						}
					}
					else if(evento.mouse.x >= 235 && evento.mouse.x <= 400 && evento.mouse.y >= 250 && evento.mouse.y <= 290){
						if(tela==0 || tela ==1 || tela==2 || tela==3){
							al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=2;
						}
					}
					else if(evento.mouse.x >= 262 && evento.mouse.x <= 380 && evento.mouse.y >= 292 && evento.mouse.y <= 329){
						if(tela==0 || tela ==1 || tela==2 || tela==3){
							al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=3;
						}
					}else if(evento.mouse.x >= 262 && evento.mouse.x <= 380 && evento.mouse.y >= 292 && evento.mouse.y <= 329){
						if(tela==0 || tela ==1 || tela==2 || tela==3){
							al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=3;
						}
					}else if(evento.mouse.x >= 255 && evento.mouse.x <= 380 && evento.mouse.y >= 390 && evento.mouse.y <= 430){
						if(tela==4){
							al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=5;
						}
					}else if(evento.mouse.x >= 590 && evento.mouse.x <= 622 && evento.mouse.y >= 430 && evento.mouse.y <= 462){
						if(tela==0 || tela ==1 || tela==2 || tela==3){
							al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						}
					}
				}
				else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
					if (evento.mouse.x >= 250 && evento.mouse.x <= 384 && evento.mouse.y >= 212 && evento.mouse.y <= 248 ){
						if(tela==0 || tela ==1 || tela==2 || tela==3){
							al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=6;
						}
					}
					else if(evento.mouse.x >= 235 && evento.mouse.x <= 400 && evento.mouse.y >= 250 && evento.mouse.y <= 290){
						if(tela==0 || tela ==1 || tela==2 || tela==3){
							al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=4;
						}

					}
					else if(evento.mouse.x >= 262 && evento.mouse.x <= 380 && evento.mouse.y >= 292 && evento.mouse.y <= 329){
						if(tela==0 || tela ==1 || tela==2 || tela==3){
							al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							sair=true;
						}
					}else if(evento.mouse.x >= 255 && evento.mouse.x <= 380 && evento.mouse.y >= 390 && evento.mouse.y <= 430){
						if(tela==5){
							al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=0;
						}
					}else if(evento.mouse.x >= 590 && evento.mouse.x <= 622 && evento.mouse.y >= 430 && evento.mouse.y <= 462){
						if(tela==0 || tela ==1 || tela==2 || tela==3){
							al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=20;
						}
					}

				}
				else if (evento.type == ALLEGRO_EVENT_KEY_DOWN){// se esta tendo evento no teclado // controle do teclado 

					switch(evento.keyboard.keycode){	
					case ALLEGRO_KEY_UP:
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						switch (tela){
						case 0:tela=1;break;
						case 1:tela=3;break;
						case 2:tela=1;break;
						case 3:tela=2;break;
						case 4:tela=5;break;
						case 5:tela=5;break;
						case 6:tela=6;break;
						}
						break;
					case ALLEGRO_KEY_DOWN:
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						switch (tela){
						case 0:tela=1;break;
						case 1:tela=2;break;
						case 2:tela=3;break;
						case 3:tela=1;break;
						case 4:tela=5;break;
						case 5:tela=5;break;
						case 6:tela=6;break;

						}
						break;
					case ALLEGRO_KEY_RIGHT:
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						switch (tela){
						case 0:tela=1;break;
						case 1:tela=1;break;
						case 2:tela=2;break;
						case 3:tela=3;break;
						case 4:tela=5;break;
						case 5:tela=5;break;
						case 6:tela=6;break;

						}
						break;
					case ALLEGRO_KEY_LEFT:
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						switch (tela){
						case 0:tela=1;break;
						case 1:tela=1;break;
						case 2:tela=2;break;
						case 3:tela=3;break;
						case 4:tela=5;break;
						case 5:tela=5;break;
						case 6:tela=6;break;

						}
						break;
					case ALLEGRO_KEY_SPACE:
						al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						switch (tela){
						case 0:tela=1;break;
						case 1:tela=6;break;
						case 2:tela=4;break;
						case 3:sair=true;break;
						case 4:tela=5;al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);break;
						case 5:tela=0;al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);break;
						case 6:tela=6;break;

						}
						break;
					default:break;
					}
				}else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					sair = true;
			}else if(tela>=6 && tela<=8){ // ************************************************  controle da tela de cadastro ***********************
				if (evento.type == ALLEGRO_EVENT_KEY_CHAR){
					if(!concluido){

						char temp[] = {evento.keyboard.unichar, '\0'};

						if (evento.keyboard.unichar >= '0' &&
							evento.keyboard.unichar <= '9'){
								strcat(str, temp);
						}
						else if (evento.keyboard.unichar >= 'A' &&
							evento.keyboard.unichar <= 'Z'){
								strcat(str, temp);
						}
						else if (evento.keyboard.unichar >= 'a' &&
							evento.keyboard.unichar <= 'z'){
								strcat(str, temp);
						}


						if ( strlen(str)==3 ){
							concluido = true;strcpy(nome,str);
						}
					}
					if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0){
						str[strlen(str) - 1] = '\0';concluido=0;
					}
				}else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
					if(evento.mouse.x >= 140 && evento.mouse.x <= 260 && evento.mouse.y >= 340 && evento.mouse.y <= 380){//
						if(tela==6 || tela ==7 || tela==8){
							al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=7;
						}
					}else if(evento.mouse.x >= 360 && evento.mouse.x <= 500 && evento.mouse.y >= 340 && evento.mouse.y <= 380){//
						if(tela==6 || tela ==7 || tela==8){
							al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=8;
						}
					}
				}else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
					if(evento.mouse.x >= 140 && evento.mouse.x <= 260 && evento.mouse.y >= 340 && evento.mouse.y <= 380){//
						if(tela==6 || tela ==7 || tela==8){
							al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							tela=0;str[0]='\0';
						}
					}else if(evento.mouse.x >= 360 && evento.mouse.x <= 500 && evento.mouse.y >= 340 && evento.mouse.y <= 380){//
						if(tela==6 || tela ==7 || tela==8){
							al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							if(strlen(str)>0){
								al_set_audio_stream_playing(musica, 0);
								al_set_audio_stream_playing(musicaplay, 1);
								x=290;y=210;
								strcpy(nome,str);
								tela=10;seg=0;level=1;str[0]='\0';
							}
						}
					}

				}else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
					switch (evento.keyboard.keycode){
					case ALLEGRO_KEY_UP:
						switch (tela){
						case 6:tela=7;break;
						case 7:tela=7;break;
						case 8:tela=8;break;
						}
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;
					case ALLEGRO_KEY_DOWN:
						switch (tela){
						case 6:tela=7;break;
						case 7:tela=7;break;
						case 8:tela=8;break;
						}
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;
					case ALLEGRO_KEY_LEFT:
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						switch (tela){
						case 6:tela=7;break;
						case 7:tela=8;break;
						case 8:tela=7;break;
						}
						break;
					case ALLEGRO_KEY_RIGHT:
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						switch (tela){
						case 6:tela=7;break;
						case 7:tela=8;break;
						case 8:tela=7;break;
						}
						break;
					case ALLEGRO_KEY_SPACE:
						al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						switch (tela){
						case 6:al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);tela=7;break;
						case 7:al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);tela=0;str[0]='\0';break;
						case 8:al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							if(strlen(str)>0){
								strcpy(nome,str);
								tela=10;level=1;seg=0;x=290;y=210;str[0]='\0';
								al_set_audio_stream_playing(musica, 0);
							}
							break;
						}
						break;

					}
				}else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					sair = true;

			}else if(tela==20 || tela==21){//255,420,380,460 ************************************************  controle da tela de instrucoes ***********************
				if(evento.mouse.x >= 255 && evento.mouse.x <= 380 && evento.mouse.y >= 420 && evento.mouse.y <= 460 && evento.type == ALLEGRO_EVENT_MOUSE_AXES){
					if(tela==20){
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						tela=21;
					}
				}else if(evento.mouse.x >= 255 && evento.mouse.x <= 380 && evento.mouse.y >= 420 && evento.mouse.y <= 460 && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
					if(tela==21){
						al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						tela=0;
					}
				}
				else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
					switch (evento.keyboard.keycode){
					case ALLEGRO_KEY_UP:
						switch (tela){
						case 20:tela=21;break;
						case 21:tela=21;break;
						}
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;
					case ALLEGRO_KEY_DOWN:
						switch (tela){
						case 20:tela=21;break;
						case 21:tela=21;break;
						}
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;
					case ALLEGRO_KEY_LEFT:
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						switch (tela){
						case 20:tela=21;break;
						case 21:tela=21;break;
						}
						break;
					case ALLEGRO_KEY_RIGHT:
						al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						switch (tela){
						case 20:tela=21;break;
						case 21:tela=21;break;
						}
						break;
					case ALLEGRO_KEY_SPACE:
						al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						switch (tela){
						case 20:al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);tela=21;break;
						case 21:al_play_sample(sampleSelect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);tela=0;break;

							break;

						}
					}


				}else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					sair = true;

			}else if(tela==9){// *************************************************  controles da fase 1  ******************************************
				if(evento.type == ALLEGRO_EVENT_TIMER){
					seg++;
				}
				if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
					if(evento.keyboard.keycode == ALLEGRO_KEY_UP){
						op=1;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_DOWN){
						op=2;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_LEFT){
						op=3;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_RIGHT){
						op=4;
					}else if(evento.keyboard.keycode==ALLEGRO_KEY_SPACE){
						if(personagem == 0){
							personagem = 1;
						}
						if(acao==3 && cont==0){
							strcpy(str,"");
							//al_set_audio_stream_playing(musica, 1);
							//al_set_audio_stream_playing(musicaplay, 0);
							x=300;y=220;acao=0;cont=30;pontuacao=0;
							personagem=3;opv=0;opr=0;acao=0;opp=0; 
						}
					}
				}else if(evento.type== ALLEGRO_EVENT_KEY_UP){
					if(evento.keyboard.keycode == ALLEGRO_KEY_UP){
						op=0;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_DOWN){
						op=0;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_LEFT){
						op=0;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_RIGHT){
						op=0;
					}else if(evento.keyboard.keycode==ALLEGRO_KEY_SPACE){
						if(personagem == 1){
							personagem = 0;
						}
						if(x>= 100 && x<= 170 && y>= 40 && y<= 120 && personagem == 3 && opr == 0){ 
							personagem = 0;opr=1;
						}else if (x>= 390 && y>= 300 && x<= 440 && y<= 350 && personagem == 3 && opv == 0 ){
							personagem = 2;opv=1;
						}else if (x>= 100 && y>= 300 && x<= 200 && y<= 350 && (personagem == 1 || personagem ==0 ) ){
							opp++;
							if(opp==3){
								personagem = 3;
								if(acao==0){
									al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
									pontuacao=pontuacao + (cont * 5);
									acao=1;
								}else if(acao==2){
									al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
									pontuacao=pontuacao + (cont * 5);
									acao=3;
								}
							}
						}else if (x>= 490 && y>= 50 && x<= 540 && y<= 100 && personagem == 2){
							personagem=3;
							if(acao==0){
								al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								pontuacao=pontuacao + (cont * 5);
								acao=2;
							}else if(acao==1){
								al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								pontuacao=pontuacao + (cont * 5);
								acao=3;
							}
						}

					}
				}
				if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					sair = true;
				}

			}else if (tela == 11 ){// *************************************************  controles da fase 2  ******************************************
				if(evento.type == ALLEGRO_EVENT_TIMER){
					seg++;
				}
				if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
					if(evento.keyboard.keycode == ALLEGRO_KEY_UP){
						op=1;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_DOWN){
						op=2;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_LEFT){
						op=3;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_RIGHT){
						op=4;
					}else if(evento.keyboard.keycode==ALLEGRO_KEY_SPACE){
						if(acao==3 && cont==0){
							strcpy(str,"");
							al_set_audio_stream_playing(musica, 1);
							al_set_audio_stream_playing(musicaplay, 0);
							x=300;y=220;acao=0;cont=30;tela=10;pontuacao=0;
							personagem=3;opv=0;opr=0;acao=0;opp=0;level=10;
						}
					}
				}else if(evento.type== ALLEGRO_EVENT_KEY_UP){
					if(evento.keyboard.keycode == ALLEGRO_KEY_UP){
						op=0;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_DOWN){
						op=0;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_LEFT){
						op=0;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_RIGHT){
						op=0;
					}else if(evento.keyboard.keycode==ALLEGRO_KEY_SPACE){

						if (x>= 130 && y>= 240 && x<= 515 && y<= 445 && opp<3){
							opp++;
							if(opp==3){
								if(opp==3){
									personagem = 3;
									if(acao==0){
										al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
										pontuacao=pontuacao + (cont * 5);
										acao=1;
									}else if(acao==2){
										al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
										pontuacao=pontuacao + (cont * 5);
										acao=3;
									}
								}
							}
						}else if (x>= 100 && x<= 170 && y>= 40 && y<= 120 && personagem == 3 && opr == 0){
							personagem=0;opr=1;
						}else if(x>= 360 && y>= 40 && x<= 430 && y<= 100 && personagem == 0){
							personagem=3;
							if(acao==0){
								al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								pontuacao=pontuacao + (cont * 5);
								acao=2;
							}else if(acao==1){
								al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								pontuacao=pontuacao + (cont * 5);
								acao=3;
							}
						}

					}
				}
				if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					sair = true;
				}
			}else if(tela==12){// *************************************************  controles da fase 3  ******************************************
				if(evento.type == ALLEGRO_EVENT_TIMER){
					seg++;
				}
				if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
					if(evento.keyboard.keycode == ALLEGRO_KEY_UP){
						op=1;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_DOWN){
						op=2;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_LEFT){
						op=3;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_RIGHT){
						op=4;
					}else if(evento.keyboard.keycode==ALLEGRO_KEY_SPACE){
						if(acao==3 && cont==0){
							strcpy(str,"");
							al_set_audio_stream_playing(musica, 1);
							al_set_audio_stream_playing(musicaplay, 0);
							x=300;y=220;acao=0;cont=30;tela=10;pontuacao=0;
							personagem=3;opv=0;opr=0;acao=0;opp=0; level=10;
						}
					}
				}else if(evento.type== ALLEGRO_EVENT_KEY_UP){
					if(evento.keyboard.keycode == ALLEGRO_KEY_UP){
						op=0;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_DOWN){
						op=0;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_LEFT){
						op=0;
					}else if(evento.keyboard.keycode== ALLEGRO_KEY_RIGHT){
						op=0;
					}else if(evento.keyboard.keycode==ALLEGRO_KEY_SPACE){

						if (x>= 140 && y>= 170 && x<= 240 && y<= 250 && opp<3){
							opp++;
							if(opp==3){
								opr=0;
								personagem = 3;
								if(acao==0){
									al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
									pontuacao=pontuacao + (cont * 5);
									acao=1;
								}else if(acao==2){
									al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
									pontuacao=pontuacao + (cont * 5);
									acao=3;
								}

							}
						}else if (x>= 390 && y>= 300 && x<= 440 && y<= 350 && personagem == 3 && opv == 0 ){
							personagem = 2;opv=1;
						}else if (x>= 430 && y>= 50 && x<= 480 && y<= 100 && personagem == 2){
							personagem=3;
							if(acao==0){
								al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								pontuacao=pontuacao + (cont * 5);
								acao=2;
							}else if(acao==1){
								al_play_sample(samplePontuacao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
								pontuacao=pontuacao + (cont * 5);
								acao=3;
							}
						}

					}
				}
				if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					sair = true;
				}
			}else if(tela==10){
				if(evento.type == ALLEGRO_EVENT_TIMER){
					seg++;
				}
			}
		}

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++TELAS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		al_draw_bitmap(fundo, 0, 0, 0);
		switch (tela){
		case 0:// -----------------------------------------------  MENU  ------------------------------------------------------------
			acao=0;al_set_audio_stream_playing(musicaplay, 0);concluido=0;
			if(trasicaomenu){
				if(raio>0)
					raio=raio-10;
			}
			al_set_audio_stream_playing(musica, 1);
			al_draw_bitmap(informacao,590,430,0);
			al_draw_text(fonte, al_map_rgb(0, 255, 0), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_RIGHT, "ECO");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 125,ALLEGRO_ALIGN_LEFT, "play");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 210,ALLEGRO_ALIGN_CENTRE, "PLAY");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_CENTRE, "SCORE");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 290,ALLEGRO_ALIGN_CENTRE, "EXIT");
			if(raio==0){trasicaomenu=0;}
			al_draw_filled_circle(320,240,raio,al_map_rgb(0,0,0));
			break;
		case 1://play selecionado 
			al_draw_bitmap(informacao,590,430,0);
			al_draw_text(fonte, al_map_rgb(0, 255, 0), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_RIGHT, "ECO");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 125,ALLEGRO_ALIGN_LEFT, "play");
			al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 210,ALLEGRO_ALIGN_CENTRE, "PLAY");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_CENTRE, "SCORE");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 290,ALLEGRO_ALIGN_CENTRE, "EXIT");
			break;
		case 2://score selecionado 
			al_draw_bitmap(informacao,590,430,0);
			al_draw_text(fonte, al_map_rgb(0, 255, 0), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_RIGHT, "ECO");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 125,ALLEGRO_ALIGN_LEFT, "play");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 210,ALLEGRO_ALIGN_CENTRE, "PLAY");
			al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_CENTRE, "SCORE");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 290,ALLEGRO_ALIGN_CENTRE, "EXIT");
			break;
		case 3://exit selecionado 
			al_draw_bitmap(informacao,590,430,0);
			al_draw_text(fonte, al_map_rgb(0, 255, 0), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_RIGHT, "ECO");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 125,ALLEGRO_ALIGN_LEFT, "play");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 210,ALLEGRO_ALIGN_CENTRE, "PLAY");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_CENTRE, "SCORE");
			al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 290,ALLEGRO_ALIGN_CENTRE, "EXIT");
			break;
		case 4:// -----------------------------------------------  SCORE  ------------------------------------------------------------
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 60,ALLEGRO_ALIGN_CENTRE, "SCORE");

			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 265, 140,ALLEGRO_ALIGN_RIGHT, "1-%s",score[0].nome);
			al_draw_text(fonte, al_map_rgb(225, 225, 255), LARGURA_TELA / 2, 140,ALLEGRO_ALIGN_CENTRE, "-");
			al_draw_textf(fonte, al_map_rgb(225, 225, 255), 365, 140,ALLEGRO_ALIGN_LEFT, "%d",score[0].pont);

			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 265, 190,ALLEGRO_ALIGN_RIGHT, "2-%s",score[1].nome);
			al_draw_text(fonte, al_map_rgb(225, 225, 255), LARGURA_TELA / 2, 190,ALLEGRO_ALIGN_CENTRE, "-");
			al_draw_textf(fonte, al_map_rgb(225, 225, 255), 365, 190,ALLEGRO_ALIGN_LEFT, "%d",score[1].pont);

			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 265, 240,ALLEGRO_ALIGN_RIGHT, "3-%s",score[2].nome);
			al_draw_text(fonte, al_map_rgb(225, 225, 255), LARGURA_TELA / 2, 240,ALLEGRO_ALIGN_CENTRE, "-");
			al_draw_textf(fonte, al_map_rgb(225, 225, 255), 365, 240,ALLEGRO_ALIGN_LEFT, "%d",score[2].pont);

			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 265, 290,ALLEGRO_ALIGN_RIGHT, "4-%s",score[3].nome);
			al_draw_text(fonte, al_map_rgb(225, 225, 255), LARGURA_TELA / 2, 290,ALLEGRO_ALIGN_CENTRE, "-");
			al_draw_textf(fonte, al_map_rgb(225, 225, 255), 365, 290,ALLEGRO_ALIGN_LEFT, "%d",score[3].pont);

			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 265, 340,ALLEGRO_ALIGN_RIGHT, "5-%s",score[4].nome);
			al_draw_text(fonte, al_map_rgb(225, 225, 255), LARGURA_TELA / 2, 340,ALLEGRO_ALIGN_CENTRE, "-");
			al_draw_textf(fonte, al_map_rgb(225, 225, 255), 365, 340,ALLEGRO_ALIGN_LEFT, "%d",score[4].pont);

			al_draw_text(fonte, al_map_rgb(225, 225, 255), LARGURA_TELA / 2, 390,ALLEGRO_ALIGN_CENTRE, "EXIT");
			break;
		case 5://exit selecionado
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 60,ALLEGRO_ALIGN_CENTRE, "SCORE");

			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 265, 140,ALLEGRO_ALIGN_RIGHT, "1-%s",score[0].nome);
			al_draw_text(fonte, al_map_rgb(225, 225, 255), LARGURA_TELA / 2, 140,ALLEGRO_ALIGN_CENTRE, "-");
			al_draw_textf(fonte, al_map_rgb(225, 225, 255), 365, 140,ALLEGRO_ALIGN_LEFT, "%d",score[0].pont);

			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 265, 190,ALLEGRO_ALIGN_RIGHT, "2-%s",score[1].nome);
			al_draw_text(fonte, al_map_rgb(225, 225, 255), LARGURA_TELA / 2, 190,ALLEGRO_ALIGN_CENTRE, "-");
			al_draw_textf(fonte, al_map_rgb(225, 225, 255), 365, 190,ALLEGRO_ALIGN_LEFT, "%d",score[1].pont);

			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 265, 240,ALLEGRO_ALIGN_RIGHT, "3-%s",score[2].nome);
			al_draw_text(fonte, al_map_rgb(225, 225, 255), LARGURA_TELA / 2, 240,ALLEGRO_ALIGN_CENTRE, "-");
			al_draw_textf(fonte, al_map_rgb(225, 225, 255), 365, 240,ALLEGRO_ALIGN_LEFT, "%d",score[2].pont);

			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 265, 290,ALLEGRO_ALIGN_RIGHT, "4-%s",score[3].nome);
			al_draw_text(fonte, al_map_rgb(225, 225, 255), LARGURA_TELA / 2, 290,ALLEGRO_ALIGN_CENTRE, "-");
			al_draw_textf(fonte, al_map_rgb(225, 225, 255), 365, 290,ALLEGRO_ALIGN_LEFT, "%d",score[3].pont);

			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 265, 340,ALLEGRO_ALIGN_RIGHT, "5-%s",score[4].nome);
			al_draw_text(fonte, al_map_rgb(225, 225, 255), LARGURA_TELA / 2, 340,ALLEGRO_ALIGN_CENTRE, "-");
			al_draw_textf(fonte, al_map_rgb(225, 225, 255), 365, 340,ALLEGRO_ALIGN_LEFT, "%d",score[4].pont);

			al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 390,ALLEGRO_ALIGN_CENTRE, "EXIT");
			break;
		case 6:// -----------------------------------------------  CADASTRO  ------------------------------------------------------------
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_CENTRE, "PLAYER");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 160,ALLEGRO_ALIGN_CENTRE, "Digite um nome de ate 3 letras");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_RIGHT,"NOME-");	
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_LEFT,str);	
			al_draw_text(fonte, al_map_rgb(255, 255, 255), 265, 340,ALLEGRO_ALIGN_RIGHT, "EXIT");
			al_draw_text(fonte, al_map_rgb(225, 225, 255), 365, 340,ALLEGRO_ALIGN_LEFT, "PLAY");				
			break;
		case 7://exit selecionado
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_CENTRE, "PLAYER");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 160,ALLEGRO_ALIGN_CENTRE, "Digite um nome de ate 3 letras");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_RIGHT,"NOME-");	
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_LEFT,str);	
			al_draw_text(fonte, al_map_rgb(0, 0, 255), 265, 340,ALLEGRO_ALIGN_RIGHT, "EXIT");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), 365, 340,ALLEGRO_ALIGN_LEFT, "PLAY");
			break;
		case 8://play selecionado
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_CENTRE, "PLAYER");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 160,ALLEGRO_ALIGN_CENTRE, "Digite um nome de ate 3 letras");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_RIGHT,"NOME-");	
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_LEFT,str);	
			al_draw_text(fonte, al_map_rgb(255, 255, 255), 265, 340,ALLEGRO_ALIGN_RIGHT, "EXIT");
			al_draw_text(fonte, al_map_rgb(0, 0, 255), 365, 340,ALLEGRO_ALIGN_LEFT, "PLAY");
			break;
		case 20:// -----------------------------------------------  INSTRUCOES  ------------------------------------------------------------
			al_draw_text(fonte, al_map_rgb(255, 255, 255), 320, 20,ALLEGRO_ALIGN_CENTER, "INSTRUCOES");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 70,ALLEGRO_ALIGN_CENTER, "-jogue apenas com setas e espaco-");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), 320, 100,ALLEGRO_ALIGN_CENTER, "FASE 1");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 150,ALLEGRO_ALIGN_CENTER, "- Regue a planta e jogue o lixo na lixeira correta");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), 320, 190,ALLEGRO_ALIGN_CENTER, "FASE 2");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 240,ALLEGRO_ALIGN_CENTER, "- Salve a baleia -clique dentro da agua-");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 270,ALLEGRO_ALIGN_CENTER, "jogue o lixo na lixeira correta");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), 320, 310,ALLEGRO_ALIGN_CENTER, "FASE 3");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 360,ALLEGRO_ALIGN_CENTER, "- Feche a torneira -clique 3 vezes-");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 390,ALLEGRO_ALIGN_CENTER, "jogue o lixo na lixeira correta");
			al_draw_text(fonte, al_map_rgb(255,255, 255), 320, 420,ALLEGRO_ALIGN_CENTER, "EXIT");
			break;
		case 21:
			al_draw_text(fonte, al_map_rgb(255, 255, 255), 320, 20,ALLEGRO_ALIGN_CENTER, "INSTRUCOES");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 70,ALLEGRO_ALIGN_CENTER, "-jogue apenas com setas e espaco-");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), 320, 100,ALLEGRO_ALIGN_CENTER, "FASE 1");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 150,ALLEGRO_ALIGN_CENTER, "- Regue a planta e jogue o lixo na lixeira correta");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), 320, 190,ALLEGRO_ALIGN_CENTER, "FASE 2");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 240,ALLEGRO_ALIGN_CENTER, "- Salve a baleia -clique dentro da agua-");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 270,ALLEGRO_ALIGN_CENTER, "jogue o lixo na lixeira correta");
			al_draw_text(fonte, al_map_rgb(255, 255, 255), 320, 310,ALLEGRO_ALIGN_CENTER, "FASE 3");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 360,ALLEGRO_ALIGN_CENTER, "- Feche a torneira -clique 3 vezes-");
			al_draw_text(fonte_1, al_map_rgb(255, 255, 255), 320, 390,ALLEGRO_ALIGN_CENTER, "jogue o lixo na lixeira correta");
			al_draw_text(fonte, al_map_rgb(0,0, 255), 320, 420,ALLEGRO_ALIGN_CENTER, "EXIT");
			break;



			//************************************************************ tela fase 1 ***********************************************************************
		case 9://primeira fase
			if(raio>0)
				raio=raio-10;
			al_draw_bitmap(imagemplay, 0, 0, 0);
			switch (acao){// tela verde
			case 0:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(255,0,0));
				break;
			case 1:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(0,225,32));
				al_draw_filled_rectangle(320,35,605,445,al_map_rgb(255,0,0));
				break;
			case 2:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(0,225,32));
				al_draw_filled_rectangle(35,35,320,445,al_map_rgb(225,0,0));
				break;
			case 3:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(0,225,32));
				break;
			}

			// spritees da fase 
			al_draw_bitmap(flor[opp],140,335,0);//planta
			if(opr==0)
				al_draw_bitmap(regador,140,85,0);//regador
			al_draw_bitmap(lixo[0],315,85,0);//lixo
			al_draw_bitmap(lixo[1],385,85,0);
			al_draw_bitmap(lixo[2],455,85,0);
			al_draw_bitmap(lixo[3],525,85,0);
			if(opv==0)
				al_draw_bitmap(garrafa,430,335,0);//vidro

			//plataformas para contador e pontuacao
			al_draw_filled_ellipse(320, 0, 100, 55, al_map_rgb(0, 255, 225));
			al_draw_filled_ellipse(320, 0, 95, 50, al_map_rgb(0, 255, 32));
			al_draw_filled_ellipse(320, 480, 100, 55, al_map_rgb(0, 255, 225));
			al_draw_filled_ellipse(320, 480, 95, 50, al_map_rgb(0, 255, 32));

			//controle do contador
			if(seg==10 && cont!=0 && acao!=3){
				seg=0;
				cont--;
			}else if(cont == 0 ){//o tempo acabou 
				pontuacao=0;
				al_set_audio_stream_playing(musicaplay, 0);
				strcpy(str,"");
				level=10;tela=10;cont=30;acao=0;opp=0;
				personagem=3;opv=0;opr=0;

			}
			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 320, 5,ALLEGRO_ALIGN_CENTRE, "%d",cont);
			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 320, 435,ALLEGRO_ALIGN_CENTRE, "%d",pontuacao);

			//printando personagem
			if(personagem == 0){
				al_draw_bitmap(boneco_regador[0],x,y, 0); 
			}else if(personagem == 1){
				al_draw_bitmap(boneco_regador[1],x,y, 0); 
			}else if(personagem == 2){
				al_draw_bitmap(boneco_vidro,x,y, 0); 
			}else if(personagem == 3){
				al_draw_bitmap(boneco,x,y, 0); 
			}


			//passou de fase
			if(acao==3 && cont!=0){
				if(seg==10){
					strcpy(str,"");
					concluido=0;tela=10;level=2;seg=0;x=290;y=210;cont=30;acao=0;opp=0;personagem=3;opv=0;opr=0;seg=0;
				}
			}

			al_draw_filled_circle(320,240,raio,al_map_rgb(0,0,0));
			al_flip_display();

			//movimentacao
			switch(op){
			case 1:if(y>30) y += -3.0 * dir_y;break;//up//30,30,610,450
			case 2:if(y<380) y += 3.0 * dir_y;break;//down
			case 3:if(x>25) x += -3.0 * dir_x;break;//left
			case 4:if(x<555) x += 3.0 * dir_x;break;//right
			case 0:break;
			}
			/*
			al_draw_filled_rectangle(150,350,200,400,al_map_rgb(255,255,255));//flor
			al_draw_filled_rectangle(440,350,490,400,al_map_rgb(255,255,255));//vidro
			al_draw_filled_rectangle(150,100,200,150,al_map_rgb(255,255,255));//regador
			al_draw_filled_rectangle(330,100,380,150,al_map_rgb(255,255,255));//lixos
			al_draw_filled_rectangle(400,100,450,150,al_map_rgb(255,255,255));
			al_draw_filled_rectangle(470,100,520,150,al_map_rgb(255,255,255));
			al_draw_filled_rectangle(540,100,590,150,al_map_rgb(255,255,255));
			*/

			al_rest(0.005);
			break;
			//************************************************************ tela fase 2 ***********************************************************************
		case 11://segunda fase 
			if(raio>0)
				raio=raio-10;
			al_draw_bitmap(imagemplay, 0, 0, 0);
			switch (acao){// tela verde
			case 0:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(255,0,0));
				break;
			case 1:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(0,225,32));
				al_draw_filled_rectangle(35,35,605,240,al_map_rgb(225,0,0));
				break;
			case 2:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(0,225,32));
				al_draw_filled_rectangle(35,240,605,445,al_map_rgb(255,0,0));
				break;
			case 3:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(0,225,32));
				break;
			}

			//animacao do mar
			if(seg==10){
				if(animacaop3==2)
					animacaop3=0;
				else
					animacaop3++;
			}
			al_draw_bitmap(mar[animacaop3],130,245, 0);

			//sprites
			al_draw_bitmap(baleia[opp],130,245, 0);//baleia
			al_draw_bitmap(lixos[1],385,85,0);//lixo hospitalar 
			al_draw_bitmap(lixos[0],455,85,0);//lixo reciclavel 

			if(opr==0)
				al_draw_bitmap(ceringa,140,85,0);//ceringa

			//al_draw_filled_rectangle(360,40,430,100,al_map_rgb(255,255,255)); //rage da agua 

			//plataformas para contador e pontuacao
			al_draw_filled_ellipse(320, 0, 100, 55, al_map_rgb(0, 255, 225));
			al_draw_filled_ellipse(320, 0, 95, 50, al_map_rgb(0, 255, 32));
			al_draw_filled_ellipse(320, 480, 100, 55, al_map_rgb(0, 255, 225));
			al_draw_filled_ellipse(320, 480, 95, 50, al_map_rgb(0, 255, 32));

			//controle do contador
			if(seg==10 && cont!=0 && acao!=3){
				seg=0;
				cont--;
			}else if(cont == 0 ){//o tempo acabou 
				strcpy(str,"");
				pontuacao=0;
				al_set_audio_stream_playing(musicaplay, 0);
				tela=10;cont=30;acao=0;opp=0;level=10;
				personagem=3;opv=0;opr=0;

			}
			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 320, 5,ALLEGRO_ALIGN_CENTRE, "%d",cont);
			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 320, 435,ALLEGRO_ALIGN_CENTRE, "%d",pontuacao);

			//printando personagem
			if(personagem == 0){
				al_draw_bitmap(boneco_ceringa,x,y, 0); 
			}else if(personagem == 3){
				al_draw_bitmap(boneco,x,y, 0); 
			}


			//passou de fase
			if(acao==3 && cont!=0){
				if(seg==10){
					strcpy(str,"");
					concluido=0;cont=30;acao=0;opp=0;personagem=3;opv=0;opr=1;level=3;tela=10;seg=0;x=290;y=210;seg=0;
				}
			}

			al_draw_filled_circle(320,240,raio,al_map_rgb(0,0,0));
			al_flip_display();

			//movimentacao
			switch(op){
			case 1:if(y>30) y += -3.0 * dir_y;break;//up//30,30,610,450
			case 2:if(y<380) y += 3.0 * dir_y;break;//down
			case 3:if(x>25) x += -3.0 * dir_x;break;//left
			case 4:if(x<555) x += 3.0 * dir_x;break;//right
			case 0:break;
			}

			al_rest(0.005);
			break;
			//************************************************************ tela fase 3  ***********************************************************************
		case 12:
			if(raio>0)
				raio=raio-10;
			al_draw_bitmap(imagemplay, 0, 0, 0);
			switch (acao){// tela verde
			case 0:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(255,0,0));
				break;
			case 1:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(0,225,32));
				al_draw_filled_rectangle(320,35,605,445,al_map_rgb(255,0,0));
				break;
			case 2:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(0,225,32));
				al_draw_filled_rectangle(35,35,320,445,al_map_rgb(225,0,0));
				break;
			case 3:
				al_draw_filled_rectangle(30,30,610,450,al_map_rgb(0, 255, 225));
				al_draw_filled_rectangle(35,35,605,445,al_map_rgb(0,225,32));
				break;
			}

			//animacao da torneira
			if(opr!=0){
				if(seg==10 && opr==2){
					opr=1;
				}else if(seg==10 && opr==1){
					opr=2;
				}
			}
			al_draw_bitmap(torneira[opr],140,220,0);


			//sprites
			al_draw_bitmap(lixo[0],315,85,0);//lixo
			al_draw_bitmap(lixo[1],385,85,0);
			al_draw_bitmap(lixo[2],455,85,0);
			al_draw_bitmap(lixo[3],525,85,0);

			if(opv==0)
				al_draw_bitmap(lata,430,335,0);//vidro

			//al_draw_filled_rectangle(360,40,430,100,al_map_rgb(255,255,255)); //rage da agua 

			//plataformas para contador e pontuacao
			al_draw_filled_ellipse(320, 0, 100, 55, al_map_rgb(0, 255, 225));
			al_draw_filled_ellipse(320, 0, 95, 50, al_map_rgb(0, 255, 32));
			al_draw_filled_ellipse(320, 480, 100, 55, al_map_rgb(0, 255, 225));
			al_draw_filled_ellipse(320, 480, 95, 50, al_map_rgb(0, 255, 32));

			//controle do contador
			if(seg==10 && cont!=0 && acao!=3){
				seg=0;
				cont--;
			}else if(cont == 0 ){//o tempo acabou 

				al_set_audio_stream_playing(musicaplay, 0);
				strcpy(str,"");
				tela=10;cont=30;acao=0;opp=0;level=10;
				personagem=3;opv=0;opr=0;

			}
			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 320, 5,ALLEGRO_ALIGN_CENTRE, "%d",cont);
			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 320, 435,ALLEGRO_ALIGN_CENTRE, "%d",pontuacao);

			//printando personagem
			if(personagem == 2){
				al_draw_bitmap(boneco_lata,x,y, 0); 
			}else if(personagem == 3){
				al_draw_bitmap(boneco,x,y, 0); 
			}


			//atualizacao do score 
			if(acao==3 && cont!=0){
				if(seg==10){
					p=pontuacao;
					push(score,nome,pontuacao);strcpy(str,"");concluido=0;cont=30;acao=0;opp=0;personagem=3;opv=0;opr=0;level=4;tela=10;seg=0;x=290;y=210;
				}
			}

			//al_draw_filled_rectangle(140,190,240,250,al_map_rgb(255,255,255)); rage da torneira
			//al_draw_filled_rectangle(430,50,480,100,al_map_rgb(255,255,255)); rage lixo amarelo 

			al_draw_filled_circle(320,240,raio,al_map_rgb(0,0,0));
			al_flip_display();

			//movimentacao
			switch(op){
			case 1:if(y>30) y += -3.0 * dir_y;break;//up//30,30,610,450
			case 2:if(y<380) y += 3.0 * dir_y;break;//down
			case 3:if(x>25) x += -3.0 * dir_x;break;//left
			case 4:if(x<555) x += 3.0 * dir_x;break;//right
			case 0:break;
			}

			al_rest(0.005);
			break;
		case 10:
			//transicao
			al_attach_audio_stream_to_mixer(musicaplay, al_get_default_mixer());
			al_set_audio_stream_playing(musicaplay, 1);
			if(raio<500)
				raio++;
			al_draw_filled_circle(320,240,raio,al_map_rgb(0,0,0));
			if(seg>5 && seg<30)
				if(level >=1 && level<=3)
					al_draw_textf(fonte,al_map_rgb(255,255,0),LARGURA_TELA/2,200,ALLEGRO_ALIGN_CENTER,"LEVEL - %d",level);
				else if(level==10)
					al_draw_text(fonte,al_map_rgb(255,32,0),LARGURA_TELA/2,200,ALLEGRO_ALIGN_CENTER,"O TEMPO ACABOU");
				else{
					al_draw_textf(fonte,al_map_rgb(255,255,0),LARGURA_TELA/2,200,ALLEGRO_ALIGN_CENTER,"PARABENS %s!!!",nome);
					al_draw_textf(fonte,al_map_rgb(255,255,0),LARGURA_TELA/2,250,ALLEGRO_ALIGN_CENTER,"pontuacao - %d",p);
					pontuacao=0;
				}
				if(seg==30){
					if(level==1){
						seg=0;tela=9;
					}else if(level==2){
						seg=0;tela=11;
					}else if(level == 3){
						seg=0;tela=12;
					}else if(level == 10 || level==4){
						al_set_audio_stream_playing(musica, 1);
						trasicaomenu=1;
						tela=0;level=1;
					}
				}
				break;

		}


		al_flip_display();
	}

	destroy();
	arq_close(score,arq);
	fclose(arq);
	return 0;
}

