#include <QCoreApplication>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "maze.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Maze *test = new Maze();


    //test algo
    qDebug("%d", test->pathFinding(test->entities[0], test->entities[0]->x, test->entities[0]->y, KEY));

    //test matrice mémoire
    for(int i=0;i<test->size1;i++)
    {
        printf("|");

        for(int j=0;j<test->size2;j++)
        {
            printf(" %d", test->entities[0]->mem[i][j]);
        }

        puts(" |");
    }


    while(test->opened())
    {
        test->keyboard();

        test->animation();
    }


    // L'application se termine sans erreur
    return EXIT_SUCCESS;
}
