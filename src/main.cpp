#include <curses.h>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>

using std::chrono::milliseconds;
using std::this_thread::sleep_for;

void init();
void lyricprint(const char *line);

int main(void)
{
    init();

    addstr("Still Alive with NCurses\n");
    refresh();

    lyricprint("This was a triumph");

    getch();
    endwin();
    return EXIT_SUCCESS;
}

void init()
{
    initscr();

    if (has_colors())
    {
        if (start_color() == OK)
        {
            init_pair(1, COLOR_YELLOW, COLOR_BLACK);
            attrset(COLOR_PAIR(1));
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
}

void lyricprint(const char *line)
{
    for (unsigned int i = 0; i < strlen(line); i++)
    {
        addch(line[i]);
        refresh();
        sleep_for(milliseconds(50));
    }
    return;
}
