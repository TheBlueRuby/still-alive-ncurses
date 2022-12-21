#include <curses.h>
#include <cstdlib>
#include <cstring>

void initWindow(WINDOW *win);
void lyrics(WINDOW *lyricWin);
void lyricprint(const char *line, WINDOW *lyricWin, int row);

int main(void)
{
    // ncurses init
    initscr();
    
    WINDOW *lyricWin = newwin(28, 48, 0, 0);
    initWindow(lyricWin);

    lyrics(lyricWin);

    getch();
    endwin();
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
    int row = 1;

    lyricprint("This was a triumph.", lyricWin, row);
    row++;
    lyricprint("I'm making a note here:\n|HUGE SUCCESS", lyricWin, row);
    row++;

    return;
}

void lyricprint(const char *line, WINDOW *lyricWin, int row)
{
    wmove(lyricWin, row, 1);
    for (unsigned int i = 0; i < strlen(line); i++)
    {
        waddch(lyricWin, line[i]);
        wrefresh(lyricWin);
        napms(100);
    }
    
    napms(2000);

    return;
}
