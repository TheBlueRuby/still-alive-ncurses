#include <curses.h>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>

using std::this_thread::sleep_for;
using std::chrono::milliseconds;

void lyricprint(const char* line);

int main(void)
{
    initscr();

    addstr("Still Alive with NCurses\n");
    refresh();

    lyricprint("This was a triumph");

    getch();
    endwin();
    return EXIT_SUCCESS;
}

void lyricprint(const char* line)
{
    for (unsigned int i = 0; i < strlen(line); i++)
    {
        addch(line[i]);
        refresh();
        sleep_for(milliseconds(50));
    }
    return;
}
