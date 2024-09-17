#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

int main() {

    // verifica se tudo inicializou corretamente
    if (!al_init()) {
        fprintf(stderr, "Erro inicializando Allegro!\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "Erro inicializando teclado!\n");
        return
            -1;
    }

    if (!al_install_mouse()) {
        fprintf(stderr, "Erro inicializando mouse!\n");
        return
            -1;
    }

    // constante do tamanho da tela em pixels
    const int WIDTH = 1920;
    const int HEIGHT = 1080;

    // cria uma janela e armazena informação com ponteiro para uso futuro
    ALLEGRO_DISPLAY* display = al_create_display(WIDTH, HEIGHT);

    if (!display) {
        fprintf(stderr, "Erro inicializando display!\n");
        return -1;

    }
    // cria uma fila de eventos e registra os eventos relacionados ao display
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));

    // enquanto o programa não terminar, aguarda um evento e o guarda na variavel "ev"
    bool done = false;
    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        // se fechar a janela o loop termina
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;

        }
    }
    // destroi o display e a fila de eventos
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

}