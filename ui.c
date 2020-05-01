#include "tinyfiledialogs.h"
#include <time.h>
#include <stdlib.h>

static void ui_win_simple(struct nk_context *ctx, int x, int y, int w, int h)
{
    enum {EASY, HARD};
    static int op = EASY;
    static float value = 0.6f;
    static int i =  20;
    static char path[256];

#define ROWS    100
#define COLS    100
    static int SIZE = 2;
    static char grids[ROWS][COLS] = {0};
    static int _init = 0;
    static unsigned _loop = 0;
    if (_init == 0) {
        _init = 1;
        srand(time(NULL));
    }
    if (_loop % 10 == 0) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                int r = random() % 20;
                grids[i][j] = (r == 0);
            }
        }
    }
    _loop++;


    if (nk_begin(ctx, "Show", nk_rect(x, x, w, h),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE|NK_WINDOW_SCALABLE)) {
        /* fixed widget pixel width */
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button")) {
            /* event handling */
            int r = tinyfd_messageBox("Continue?", "If continue?", "okcancel", "question", 1);
        }

        /* fixed widget window ratio width */
        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;

        /* custom widget pixel width */
        nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
        {
            nk_layout_row_push(ctx, 50);
            nk_label(ctx, "Volume:", NK_TEXT_LEFT);
            nk_layout_row_push(ctx, 110);
            nk_slider_float(ctx, 0, &value, 1.0f, 0.1f);
        }
        nk_layout_row_end(ctx);
        nk_layout_row(ctx, NK_DYNAMIC, 30, 3, (float []){0.1, 0.7, 0.2});
        nk_label(ctx, "path", NK_TEXT_LEFT);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, path, sizeof(path), nk_filter_ascii);
        if (nk_button_label(ctx, "select")) {
#ifdef _WIN32
            tinyfd_winUtf8 = 0;
#endif
            char *save = tinyfd_saveFileDialog(
                        "select save path",
                        "",
                        1,
                        (const char *[]){"*.txt"},
                        NULL);
            if (save) {
                snprintf(path, sizeof(path), "%s", save);
            }
        }
        nk_layout_row_dynamic(ctx, 30, 2);
        nk_label(ctx, "size", NK_TEXT_LEFT);
        nk_slider_int(ctx, 1, &SIZE, 5, 1);
        struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);
        struct nk_rect org = nk_window_get_content_region(ctx);
        org.x += 10;
        org.y += 200;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                int x = j * SIZE + org.x;
                int y = i * SIZE + org.y;
                if (grids[i][j]) nk_fill_rect(canvas, nk_rect(x, y, SIZE, SIZE), 0.0f, nk_green);
            }
        }


    }
    nk_end(ctx);
}


int ui_run(struct nk_context *ctx, int width, int height)
{
    ui_win_simple(ctx, 20, 20, 480, 480);
}

