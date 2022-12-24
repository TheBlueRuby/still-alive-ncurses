#include <curses.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define MINIAUDIO_IMPLEMENTATION
#include "../includes/miniaudio.h"

void initWindow(WINDOW *win);
void lyrics(WINDOW *lyricWin);
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


    WINDOW *lyricWin = newwin(38, 50, 0, 0);
    initWindow(lyricWin);

    ma_engine_play_sound(&maEngine, "stillalive.mp3", NULL);
    lyrics(lyricWin);

    endwin();
    ma_engine_uninit(&maEngine);

    return EXIT_SUCCESS;
}

void initWindow(WINDOW *win)
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

    box(win, '|', '-');

    return;
}

void lyrics(WINDOW *lyricWin)
{
    int row = 0;

    row++;
    lyricprint("Forms FORM-29827281-12:", lyricWin, row, 30, 3000);
    row++;
    lyricprint("Test Assessment Report", lyricWin, row, 30, 3000);
    row++;
    row++;
    row++;

    row++;
    lyricprint("This was a triumph.", lyricWin, row);
    row++;
    lyricprint("I'm making a note here:\n HUGE SUCCESS", lyricWin, row);
    row++;
    row++;
    lyricprint("I'ts hard to overstate\n my satisfaction.", lyricWin, row, 100, 2500);
    row++;
    row++;
    lyricprint("Aperture Science.", lyricWin, row);
    row++;
    lyricprint("We do what we must\n because we can.", lyricWin, row);
    row++;
    row++;
    lyricprint("For the good of all of us,", lyricWin, row, 100, 1300);
    row++;
    lyricprint("Except the ones who are dead.", lyricWin, row, 50, 500);
    row++;
    napms(1000);
    row++;
    lyricprint("But there's no sense crying\n over every mistake.", lyricWin, row, 50, 750);
    row++;
    row++;
    lyricprint("You just keep on trying\n till you run out of cake.", lyricWin, row, 50, 750);
    row++;
    row++;
    lyricprint("And the Science gets done.", lyricWin, row, 50, 750);
    row++;
    lyricprint("And you make a neat gun.", lyricWin, row, 50, 750);
    row++;
    lyricprint("For the people who are.", lyricWin, row, 50, 750);
    row++;
    lyricprint("still alive.", lyricWin, row);
    row++;


    return;
}

void lyricprint(const char *line, WINDOW *lyricWin, int row, int napMs, int linewaitms)
{
    wmove(lyricWin, row, 1);
    for (unsigned int i = 0; i < strlen(line); i++)
    {
        waddch(lyricWin, line[i]);
        box(lyricWin, '|', '-');
        wrefresh(lyricWin);
        napms(napMs);
    }

    napms(linewaitms);

    return;
}

void lyricprint(const char *line, WINDOW *lyricWin, int row)
{
    lyricprint(line, lyricWin, row, 100, 2000);
}
