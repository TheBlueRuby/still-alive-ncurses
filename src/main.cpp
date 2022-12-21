#include <curses.h>
#include <stdlib.h>

int main(void)
{
    initscr();

    addstr("Still Alive with NCurses");
    refresh();

    getch();
    endwin();
    return EXIT_SUCCESS;
}
