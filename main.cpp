#include <QCoreApplication>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "maze.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Maze *test = new Maze();

    while(test->opened())
    {
        test->playerVision();

        test->keyboard();

        test->animation();

        test->search(test->entities[test->player]->x, test->entities[test->player]->y);
    }

    test->printMaze();
    printf("\n");
    test->printMemPlayer();

    // L'application se termine sans erreur
    return EXIT_SUCCESS;
}
