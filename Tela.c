//Tela.c

#include "Types.h"

void telas(){
	al_draw_bitmap(fundo, 0, 0, 0);
			
            switch (tela){
			case 0:
				al_draw_filled_rectangle(88.0, 10.0, 340.0, 77.0, al_map_rgb(0, 255, 255));
 
				al_draw_text(fonte, al_map_rgb(0, 255, 0), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_RIGHT, "ECO");
                al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 125,ALLEGRO_ALIGN_LEFT, "play");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 210,ALLEGRO_ALIGN_CENTRE, "PLAY");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_CENTRE, "SCORE");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 290,ALLEGRO_ALIGN_CENTRE, "EXIT");
                break;
            case 1:
				al_draw_text(fonte, al_map_rgb(0, 255, 0), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_RIGHT, "ECO");
                al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 125,ALLEGRO_ALIGN_LEFT, "play");
				al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 210,ALLEGRO_ALIGN_CENTRE, "PLAY");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_CENTRE, "SCORE");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 290,ALLEGRO_ALIGN_CENTRE, "EXIT");
                break;
            case 2:
                al_draw_text(fonte, al_map_rgb(0, 255, 0), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_RIGHT, "ECO");
                al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 125,ALLEGRO_ALIGN_LEFT, "play");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 210,ALLEGRO_ALIGN_CENTRE, "PLAY");
				al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_CENTRE, "SCORE");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 290,ALLEGRO_ALIGN_CENTRE, "EXIT");
                break;
            case 3:
                al_draw_text(fonte, al_map_rgb(0, 255, 0), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_RIGHT, "ECO");
                al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 125,ALLEGRO_ALIGN_LEFT, "play");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 210,ALLEGRO_ALIGN_CENTRE, "PLAY");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_CENTRE, "SCORE");
				al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 290,ALLEGRO_ALIGN_CENTRE, "EXIT");
                break;
			case 4://SCORE
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
			case 5://cadastro
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_CENTRE, "PLAYER");
				al_draw_text(fonte_1, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 160,ALLEGRO_ALIGN_CENTRE, "Digite um nome de ate 3 letras");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_RIGHT,"NOME-");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_LEFT,".");
				Sleep(500);tela=6;
				break;
			case 6://cadastro
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 120,ALLEGRO_ALIGN_CENTRE, "PLAYER");
				al_draw_text(fonte_1, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 160,ALLEGRO_ALIGN_CENTRE, "Digite um nome de ate 3 letras");
				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 250,ALLEGRO_ALIGN_RIGHT,"NOME-");
				Sleep(500);tela=5;
				break;
			case 7://prototipo de animacao;

				al_draw_bitmap(fundo, 0, 0, 0);
				//al_draw_filled_circle(x, y, raio, al_map_rgb(0, 255, 0));
				al_draw_bitmap(boneco,x,y,0);
				al_flip_display();
				switch(op){
				case 1:y += -5.0 * dir_y;break;//up
				case 2:y += 5.0 * dir_y;break;//down
				case 3:x += -5.0 * dir_x;break;//left
				case 4:x += 5.0 * dir_x;break;//right
				case 0:break;
				}

				al_rest(0.005);
				break;
            }
        
        al_flip_display();
}