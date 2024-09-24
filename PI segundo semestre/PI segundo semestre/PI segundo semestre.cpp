#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h> // contes TrueType
#include <allegro5/allegro_image.h> //addon para colocar imagens

int main() {
    ALLEGRO_DISPLAY* janelaJogo = NULL; // criação da variável de display

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

    al_init_font_addon();  // inicializa o sistema de fontes
    al_init_ttf_addon();   // inicializa o suporte para fontes TTF

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

    // controle do loop
    bool done = false;

    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        // se o evento for fechar a janela
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
        }

        // limpa a tela
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // desenha o texto na tela
        al_draw_text(font, al_map_rgb(255, 255, 255), 800 / 2, 500 - 100,
            ALLEGRO_ALIGN_CENTER, "Lorem ipsum dolor sit amet. Eos nisi rerum est facilis cupiditate a illo voluptatem et");

        // atualiza o display
        al_flip_display();
    }


    // destroi os recursos para poupar memoria
    al_destroy_display(janelaJogo);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);

    return 0;
}
