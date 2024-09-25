#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h> // contes TrueType
#include <allegro5/allegro_image.h> //addon para colocar imagens

bool carregar_e_desenhar_imagem(const char* caminho_imagem, int x, int y, int largura, int altura, float angulo, int flags) {
    ALLEGRO_BITMAP* imagem = al_load_bitmap(caminho_imagem);

    if (!imagem) {
        fprintf(stderr, "Erro ao carregar a imagem");
        return false;
    }

    if (imagem) {
        al_draw_scaled_bitmap(imagem, 0, 0, al_get_bitmap_width(imagem), al_get_bitmap_height(imagem), x, y, largura, altura, flags);
        al_destroy_bitmap(imagem);
    }

    return true;
}

int main() {
    ALLEGRO_DISPLAY* janelaJogo = nullptr; // criação da variável de display

    // verifica a inicilaização
    if (!al_init()) {
        fprintf(stderr, "Erro inicializando Allegro!\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "Erro inicializando teclado!\n");
        return -1;
    }

    if (!al_install_mouse()) {
        fprintf(stderr, "Erro inicializando mouse!\n");
        return -1;
    }

    if (!al_init_image_addon()) {
        fprintf(stderr, "Erro inicializando addon de imagem!\n");
        return -1;
    }

    al_init_font_addon();  // inicializa o sistema de fontes
    al_init_ttf_addon();   // inicializa o suporte para fontes TTF
    al_install_mouse();

    janelaJogo = al_create_display(800, 600); //criação da janela do jogo
    al_set_window_position(janelaJogo, 400, 200); //posição da janela na tela
    al_set_window_title(janelaJogo, "Tela teste"); //nome da janela

    if (!janelaJogo) {
        fprintf(stderr, "Erro inicializando display!\n");
        return -1;
    }

    ALLEGRO_FONT* font = al_load_ttf_font("fonte.ttf", 16, 0); // carrega a fonte
    
    if (!font) {
        fprintf(stderr, "Erro carregando fonte!\n");
        al_destroy_display(janelaJogo);
        return -1;
    }
    
    // criação da fila de eventos e registra os eventos do display
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(janelaJogo));
    al_register_event_source(event_queue, al_get_mouse_event_source());


    int objetoX = 400;
    int objetoY = 300;
    int objetoAlt = 50;
    int objetoLarg = 50;
    bool arrastando = false;


    // controle do loop
    bool done = false;

    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        // if the event is to close the window
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
        }

        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (ev.mouse.button == 1) {
                if (ev.mouse.x >= objetoX && ev.mouse.x <= objetoX + objetoLarg &&
                    ev.mouse.y >= objetoY && ev.mouse.y <= objetoY + objetoAlt) {
                    arrastando = true;
                }
            }
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if (ev.mouse.button == 1) {
                arrastando = false;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if (arrastando) {
                objetoX = ev.mouse.x;
                objetoY = ev.mouse.y;
            }
        }

        // limpa a tela
        al_clear_to_color(al_map_rgb(0, 0, 0));

        carregar_e_desenhar_imagem("imagens/pera.jpeg", objetoX, objetoY,objetoLarg,objetoAlt, 0, 0);


        // Desenha o texto
        al_draw_text(font, al_map_rgb(255, 255, 255), 800 / 2, 500 - 100,
            ALLEGRO_ALIGN_CENTER, "teste");

        // Atualiza a tela
        al_flip_display();

    }
    // destroi os recursos para poupar memoria
    al_destroy_display(janelaJogo);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);

    return 0;
}
