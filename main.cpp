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
        test->keyboard();

        test->playerVision();

        test->animation();
    }

    test->printMaze();
    printf("\n");
    test->printMemPlayer();

    // L'application se termine sans erreur
    return EXIT_SUCCESS;
}
