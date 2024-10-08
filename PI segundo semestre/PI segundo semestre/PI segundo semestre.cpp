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

    al_draw_scaled_bitmap(imagem, 0, 0, al_get_bitmap_width(imagem), al_get_bitmap_height(imagem), x, y, largura, altura, flags);
    al_destroy_bitmap(imagem);

    return true;
}

int main() {
    ALLEGRO_DISPLAY* janelaJogo = nullptr; // criação da variável de display

    // verifica a inicialização
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

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Erro inicializando addon de primitivas!\n");
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

    // variáveis para o botão
    int botaoX = 620; // posição X do botão
    int botaoY = 530; // posição Y do botão
    int botaoLargura = 100; // largura do botão
    int botaoAltura = 40; // altura do botão

    // texto atual da caixa de diálogo
    std::string textoDialogo = "Texto dentro da caixa de diálogo";

    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
        }

        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            // verifica se o clique do mouse está dentro do botão
            if (ev.mouse.button == 1) {
                if (ev.mouse.x >= botaoX && ev.mouse.x <= botaoX + botaoLargura &&
                    ev.mouse.y >= botaoY && ev.mouse.y <= botaoY + botaoAltura) {
                    // rroca o texto ao clicar no botão
                    textoDialogo = "deve ter uma forma de fazer isso sem essa desenrolagem inteira";
                }
            }

            // verifica se o clique está sobre o objeto (drag and drop)
            if (ev.mouse.x >= objetoX && ev.mouse.x <= objetoX + objetoLarg &&
                ev.mouse.y >= objetoY && ev.mouse.y <= objetoY + objetoAlt) {
                arrastando = true;
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

        // limpa a tela com uma cor (fundo preto)
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Desenha a imagem
        carregar_e_desenhar_imagem("imagens/pera.jpeg", objetoX, objetoY, objetoLarg, objetoAlt, 0, 0);

        // Desenha a caixa de diálogo
        int caixaX = 50;
        int caixaY = 500;
        int caixaLargura = 700;
        int caixaAltura = 80;
        al_draw_filled_rectangle(caixaX, caixaY, caixaX + caixaLargura, caixaY + caixaAltura, al_map_rgb(50, 50, 50));
        al_draw_rectangle(caixaX, caixaY, caixaX + caixaLargura, caixaY + caixaAltura, al_map_rgb(255, 255, 255), 2);

        // desenha o texto dentro da caixa de diálogo
        al_draw_text(font, al_map_rgb(255, 255, 255), caixaX + 20, caixaY + 25, 0, textoDialogo.c_str());

        // desenha o botão no canto inferior direito da caixa de diálogo
        al_draw_filled_rectangle(botaoX, botaoY, botaoX + botaoLargura, botaoY + botaoAltura, al_map_rgb(100, 100, 100));
        al_draw_rectangle(botaoX, botaoY, botaoX + botaoLargura, botaoY + botaoAltura, al_map_rgb(255, 255, 255), 2);
        al_draw_text(font, al_map_rgb(255, 255, 255), botaoX + botaoLargura / 2, botaoY + 10, ALLEGRO_ALIGN_CENTER, "Trocar");

        // atualiza a tela
        al_flip_display();
    }

    // destroi os recursos para poupar memoria
    al_destroy_display(janelaJogo);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);

    return 0;
}
