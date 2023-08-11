#include <curses.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define MINIAUDIO_IMPLEMENTATION
#include "../includes/miniaudio.h"
#include "text.h"

void initWindow(WINDOW *win, bool drawBox);
void lyrics(WINDOW *lyricWin, WINDOW *artWin);
void checkArt(WINDOW *artWin, int row);
void lyricprint(const char *line, WINDOW *lyricWin, int row, int napMs, int linewaitms);
void lyricprint(const char *line, WINDOW *lyricWin, int row);

int main(void)
{
    // ncurses init
    initscr();

    // sound init
    ma_result maResult;
    ma_engine maEngine;

    FILE *audioFile;
    if (!(audioFile = fopen("stillalive.mp3", "r")))
    {
        printf("File not found!");
        return 2;
    }

    maResult = ma_engine_init(NULL, &maEngine);
    if (maResult != MA_SUCCESS)
    {
        printf("Could not init audio!");
        return -1;
    }

    WINDOW *lyricWin = newwin(38, 48, 0, 0);
    initWindow(lyricWin, true);

    WINDOW *artWin = newwin(19, 48, 19, 48);
    initWindow(artWin, false);

    WINDOW *creditsWin = newwin(19, 48, 0, 48);
    initWindow(creditsWin, true);

    ma_engine_play_sound(&maEngine, "stillalive.mp3", NULL);
    lyrics(lyricWin, artWin);

    endwin();
    ma_engine_uninit(&maEngine);

    return EXIT_SUCCESS;
}

void initWindow(WINDOW *win, bool drawBox)
{

    // color init
    if (has_colors())
    {
        if (start_color() == OK)
        {
            init_pair(1, COLOR_YELLOW, COLOR_BLACK);
            wattrset(win, COLOR_PAIR(1));
        }
        else
        {
            addstr("Could not init colors!\n");
            refresh();
        }
    }
    else
    {
        addstr("No colors capable!\n");
        refresh();
    }

    if (drawBox)
    {
        box(win, '|', '-');
    }
    wrefresh(win);

    return;
}

void lyrics(WINDOW *lyricWin, WINDOW *artWin)
{
    for(int page = 0; page <= 2; page++)
    {
        for (int row = 1; row <= 24; row++)
        {
            int line = row + (page*24);
            checkArt(artWin, row);
            lyricprint(lyricList[line], lyricWin, row, letterDelays[line], lineDelays[line]);
        }
        wclear(lyricWin);
        box(lyricWin, '|', '-');
        wrefresh(lyricWin);
    }

    return;
}

void checkArt(WINDOW *artWin, int row)
{
    if(row >= 11)
    {
        wclear(artWin);
        waddstr(artWin, "Aperture logo here!");
        wrefresh(artWin);
    }
}

void lyricprint(const char *lyric, WINDOW *lyricWin, int row, int charWaitMs, int linewaitms)
{
    wmove(lyricWin, row, 1);
    for (unsigned int i = 0; i < strlen(lyric); i++)
    {
        waddch(lyricWin, lyric[i]);
        wrefresh(lyricWin);
        napms(charWaitMs);
    }

    napms(linewaitms);

    return;
}
