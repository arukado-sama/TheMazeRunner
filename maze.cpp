#include "maze.h"

Maze::Maze()
{
    initMaze();

    initSquares();

    initEntities();
}


Maze::~Maze()
{
    for(int i=0; i<size1; i++) free(squares[i]);
    free(squares);

    for(int j=0; j<nbEntities; j++)
    {
        for(int i=0; i<size2; i++) free(entities[j]->mem[i]);
        free(entities[j]->mem);
    }

    free(walls);
    free(entities);
}

void Maze::initMaze()
{
    saveSizes();

    App = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "The Maze Runner");

    App->setFramerateLimit(60);

    path = QCoreApplication::applicationDirPath ()+"/img";

    maze = new Sprite((path+"/maze.png").toStdString().c_str());

    maze->setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);

    App->draw(*maze);
}


void Maze::initSquares()
{
    //allocations des cases du labyrinthe
    squares = (int**)malloc(size1*sizeof(*squares));
    for(int i=0 ; i<size1; i++) squares[i] = (int*)malloc(size2*sizeof(**squares));

    //initialisation des cases du labyrinthe
    for(int i=0; i<size1; i++)
        for(int j=0; j<size2; j++)
            squares[i][j] = 0;

    //allocations des sprites des murs
    walls = (Sprite*)calloc(size1*size2, sizeof(Sprite));

    saveSquares();

    drawWalls();
}


void Maze::initEntities()
{
    saveNbEntities();

    //allocations des entités
    entities = (Entity**)malloc(nbEntities*sizeof(*entities));
    for(int i=0 ; i<nbEntities; i++) entities[i] = (Entity*)malloc(sizeof(**entities));

    saveEntities();

    initMemEntities();

    //le joueur n'a pas encore trouvé les objectifs
    playerHasKey = false;
    playerHasDoor = false;
}


void Maze::initMemEntities()
{
    for(int k=0; k<nbEntities; k++)
    {
        //allocations des cases de la mémoire de l'entité
        entities[k]->mem = (int**)malloc(size1*sizeof(*entities[k]->mem));
        for(int i=0 ; i<size1; i++) entities[k]->mem[i] = (int*)malloc(size2*sizeof(**entities[k]->mem));

        //initialisation des cases de la mémoire de l'entité
        for(int i=0; i<size1; i++)
            for(int j=0; j<size2; j++)
                entities[k]->mem[i][j] = UNKNOWN;
    }

    initVisitedSquares();

    saveMonstersMem();
}


void Maze::initVisitedSquares()
{
    for(int k=0; k<nbEntities; k++)
    {
        //allocations des cases visitées par l'entité
        entities[k]->visited = (int**)malloc(size1*sizeof(*entities[k]->visited));
        for(int i=0 ; i<size1; i++) entities[k]->visited[i] = (int*)malloc(size2*sizeof(**entities[k]->visited));

        //initialisation des cases visitées par l'entité
        for(int i=0; i<size1; i++)
            for(int j=0; j<size2; j++)
                entities[k]->visited[i][j] = 0;
    }

    for(int k=0; k<nbEntities; k++)
        for(int i=0;i<size1;i++)
        {
            for(int j=0;j<size2;j++)
            {
                entities[k]->visited[i][j] = 0;
            }
        }
}


void Maze::keyboard()
{
    if (App->pollEvent(Event))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            App->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) entities[player]->move(LEFT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) entities[player]->move(RIGHT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) entities[player]->move(UP);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) entities[player]->move(DOWN);
    }
}


bool Maze::opened()
{
    if(App->isOpen()) return true;

    else return false;
}


void Maze::animation()
{
    App->clear();
    App->draw(*maze);
    drawWalls();


    for(int i=0; i<nbEntities; i++)
    {
        entities[i]->entity->setPosition(entities[i]->x*40+20, entities[i]->y*40+20);

        App->draw(*(entities[i]->entity));
    }

    App->display();
}


void Maze::drawWalls()
{
    int k = 0;

    Sprite *wall = new Sprite((path+"/wall.png").toStdString().c_str());
    Sprite *key = new Sprite((path+"/key.png").toStdString().c_str());
    Sprite *door = new Sprite((path+"/door.png").toStdString().c_str());

    for(int i=0; i<size1; i++)
    {
        for(int j=0; j<size2; j++)
        {
            switch(squares[i][j])
            {
                case WALL: walls[k] = *wall; break;
                case KEY: walls[k] = *key; break;
                case DOOR: walls[k] = *door; break;
            }

            walls[k].setPosition(j*40+20, i*40+20);

            if(playerHasKey && (squares[i][j] == KEY));
            else App->draw((Sprite)walls[k]);

            k++;
        }
    }

    App->display();
}


void Maze::saveSizes()
{
    char c = 0;
    int s1 = 0;
    int s2 = 0;

    FILE *data;

    //ouverture du fichier
    if((data = fopen("maze.txt","r")) == NULL) {
        fprintf(stderr, "Echec ouverture fichier. Fin de programme.\n");
        exit(1);
    }

    while(c!=EOF)
    {
        c=fgetc(data);

        if(c=='\n')
        {
            s1++;
        }
    }

    rewind(data);
    c = 0;

    while(c!='\n')
    {
        c=fgetc(data);

        if(isdigit(c)) s2++;
    }

    fclose(data);

    size1 = s1;
    size2 = s2;

    WINDOW_HEIGHT = (size1)*40;
    WINDOW_WIDTH = (size2)*40;

    qDebug("%d %d", size1, size2);
}


void Maze::saveSquares()
{
    FILE *data;
    //ouverture du fichier
    if((data = fopen("maze.txt","r")) == NULL) {
        fprintf(stderr, "Echec ouverture fichier. Fin de programme.\n");
        exit(1);
    }

    int s1=0, s2=0; //indices matrice
    char c;

    while(c!=EOF)
    {
        c=fgetc(data);

        if(c=='\n')
        {
            s1++;
            s2=0;
        }

        if(c!='\n')
        {
            if(isdigit(c))
            {
                squares[s1][s2] = atoi(&c);
            }

            s2++;
        }

    }

    fclose(data);
}


void Maze::saveNbEntities()
{
    char c = 0;
    int nb = 0;

    FILE *data;

    //ouverture du fichier
    if((data = fopen("entities.txt","r")) == NULL) {
        fprintf(stderr, "Echec ouverture fichier. Fin de programme.\n");
        exit(1);
    }

    while(c!=EOF)
    {
        c=fgetc(data);

        if(c=='\n')
        {
            nb++;
        }
    }

    fclose(data);

    nbEntities = nb;
}


void Maze::saveEntities()
{
    FILE *data;
    //ouverture du fichier
    if((data = fopen("entities.txt","r")) == NULL) {
        fprintf(stderr, "Echec ouverture fichier. Fin de programme.\n");
        exit(1);
    }

    char c;
    int n = 0;
    int x;
    int y;
    char ctype[8];
    int type = 0;

    while(c=fgetc(data)!=EOF)
    {
        fseek(data, -1, SEEK_CUR);

        fscanf(data, "%d %d %s", &x, &y, ctype);

        if(!strcmp(ctype, "PLAYER")){ type = PLAYER; player = n; }
        if(!strcmp(ctype, "GRIEVER")) type = GRIEVER;
        if(!strcmp(ctype, "SENTINEL")) type = SENTINEL;
        if(!strcmp(ctype, "GUARDIAN")){ type = GUARDIAN; guardian = n; }

        Entity *e = new Entity(x, y, type);

        entities[n] = e;

        n++;

        fseek(data, 1, SEEK_CUR);
    }

    fclose(data);
}


void Maze::saveMonstersMem()
{
    for(int i=0; i<nbEntities; i++)
    {
        if(entities[i]->type != PLAYER)
        {
            entities[i]->mem = squares;
        }
    }
}


void Maze::printMaze()
{
    for(int i=0;i<size1;i++)
    {
        printf("|");

        for(int j=0;j<size2;j++)
        {
            printf(" %2.d", squares[i][j]);
        }

        puts(" |");
    }
}


void Maze::playerVision()
{
    int y=entities[player]->x;
    int x=entities[player]->y;

    entities[player]->mem[x][y]=squares[x][y];

    if(entities[player]->mem[x][y] != WALL)
    {

    //vision en bas
    if(squares[x+1][y]==WALL)
        entities[player]->mem[x+1][y]=WALL;
    else
    {
        entities[player]->mem[x+1][y]=squares[x+1][y];

        if(squares[x+2][y]==WALL)
            entities[player]->mem[x+2][y]=WALL;

        else entities[player]->mem[x+2][y]=squares[x+2][y];
    }

    //vision en haut
    if(squares[x-1][y]==WALL)
        entities[player]->mem[x-1][y]=WALL;
    else
    {
        entities[player]->mem[x-1][y]=squares[x-1][y];

        if(squares[x-2][y]==WALL)
            entities[player]->mem[x-2][y]=WALL;

        else entities[player]->mem[x-2][y]=squares[x-2][y];
    }

    //vision à gauche
    if(squares[x][y-1]==WALL)
        entities[player]->mem[x][y-1]=WALL;
    else
    {
        entities[player]->mem[x][y-1]=squares[x][y-1];

        if(squares[x][y-2]==WALL)
            entities[player]->mem[x][y-2]=WALL;

        else entities[player]->mem[x][y-2]=squares[x][y-2];
    }

    //vision à droite
    if(squares[x][y+1]==WALL)
        entities[player]->mem[x][y+1]=WALL;
    else
    {
        entities[player]->mem[x][y+1]=squares[x][y+1];

        if(squares[x][y+2]==WALL)
            entities[player]->mem[x][y+2]=WALL;

        else entities[player]->mem[x][y+2]=squares[x][y+2];
    }

    //vision en haut à droite
    if(squares[x-1][y+1]==WALL)
        entities[player]->mem[x-1][y+1]=WALL;
    else
        entities[player]->mem[x-1][y+1]=squares[x-1][y+1];

    //vision en haut à gauche
    if(squares[x-1][y-1]==WALL)
        entities[player]->mem[x-1][y-1]=WALL;
    else
        entities[player]->mem[x-1][y-1]=squares[x-1][y-1];

    //vision en bas à droite
    if(squares[x+1][y+1]==WALL)
        entities[player]->mem[x+1][y+1]=WALL;
    else
        entities[player]->mem[x+1][y+1]=squares[x+1][y+1];

    //vision en bas à gauche
    if(squares[x+1][y-1]==WALL)
        entities[player]->mem[x+1][y-1]=WALL;
    else
        entities[player]->mem[x+1][y-1]=squares[x+1][y-1];

    }
}


void Maze::printMemPlayer()
{
    for(int i=0;i<size1;i++)
    {
        printf("|");

        for(int j=0;j<size2;j++)
        {
            printf(" %2.d", entities[player]->mem[i][j]);
        }

        puts(" |");
    }
}


void Maze::dijkstra()
{
    int xmin, ymin, distmin;
    node **route;

    //allocations des cases
    route = (node**)malloc(size1*sizeof(*route));
    for(int i=0 ; i<size1; i++) route[i] = (node*)malloc(size2*sizeof(**route));

    //initialisation des cases
    for(int i=0; i<size1; i++)
        for(int j=0; j<size2; j++)
        {
            route[i][j].dist = size1*size2;
            route[i][j].xpred = -1;
            route[i][j].ypred = -1;

            if(squares[i][j]!=WALL) route[i][j].todo = true;
            else
            {
                route[i][j].todo = false;
                route[i][j].dist = -1;
            }
        }

    route[entities[player]->y][entities[player]->x].dist = 0;
    route[entities[player]->y][entities[player]->x].xpred = entities[player]->y;
    route[entities[player]->y][entities[player]->x].ypred = entities[player]->x;

    xmin = entities[player]->y;
    ymin = entities[player]->x;

    qDebug("avant boucle");

    while(entities[player]->mem[xmin][ymin]!=DOOR)
    {
        distmin = size1*size2+1;

        for(int i=0; i<size1; i++)
            for(int j=0; j<size2; j++)
            {
                if((route[i][j].todo == true)&&(route[i][j].dist <= distmin))
                {
                    xmin = i;
                    ymin = j;
                    distmin = route[i][j].dist;
                }
            }

        route[xmin][ymin].todo = false;

        qDebug("xmin = %d, ymin = %d", xmin, ymin);

        if((route[xmin][ymin+1].dist > distmin+1))
        {
            qDebug("x=%d, y=%d", xmin, ymin+1);
            route[xmin][ymin+1].dist = distmin+1;
            route[xmin][ymin+1].xpred = xmin;
            route[xmin][ymin+1].ypred = ymin;
        }

        if((route[xmin+1][ymin].dist > distmin+1))
        {
            qDebug("x=%d, y=%d", xmin+1, ymin);
            route[xmin+1][ymin].dist = distmin+1;
            route[xmin+1][ymin].xpred = xmin;
            route[xmin+1][ymin].ypred = ymin;
        }

        if((route[xmin][ymin-1].dist > distmin+1))
        {
            qDebug("x=%d, y=%d", xmin, ymin-1);
            route[xmin][ymin-1].dist = distmin+1;
            route[xmin][ymin-1].xpred = xmin;
            route[xmin][ymin-1].ypred = ymin;
        }

        if((route[xmin-1][ymin].dist > distmin+1))
        {
            qDebug("x=%d, y=%d", xmin-1, ymin);
            route[xmin-1][ymin].dist = distmin+1;
            route[xmin-1][ymin].xpred = xmin;
            route[xmin-1][ymin].ypred = ymin;
        }
    }

    qDebug("après boucle");

//*
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<8; j++)
        {
            printf("(%2d,%2d) ", route[i][j].xpred, route[i][j].ypred);
        }

        printf("\n");
    }
//*/

    int solution[size1*size2];
    int sol = 0;
    int xsol = xmin, ysol = ymin;

    while(!((xsol==entities[player]->y)&&(ysol==entities[player]->x)))
    {
        int xtemps=xsol, ytemps=ysol;

        qDebug("xol=%d, ysol=%d ; xpred = %d, ypred = %d", xsol, ysol, route[xsol][ysol].xpred, route[xsol][ysol].ypred);

        if((route[xsol][ysol].xpred == xsol + 1)&&(route[xsol][ysol].ypred == ysol))
        {
            solution[sol] = UP;
            sol++;
            xsol = route[xtemps][ytemps].xpred;
            ysol = route[xtemps][ytemps].ypred;
        }

        if((route[xsol][ysol].xpred == xsol - 1)&&(route[xsol][ysol].ypred == ysol))
        {
            solution[sol] = DOWN;
            sol++;
            xsol = route[xtemps][ytemps].xpred;
            ysol = route[xtemps][ytemps].ypred;
        }

        if((route[xsol][ysol].xpred == xsol)&&(route[xsol][ysol].ypred == ysol + 1))
        {
            solution[sol] = LEFT;
            sol++;
            xsol = route[xtemps][ytemps].xpred;
            ysol = route[xtemps][ytemps].ypred;
        }

        if((route[xsol][ysol].xpred == xsol)&&(route[xsol][ysol].ypred == ysol - 1))
        {
            solution[sol] = RIGHT;
            sol++;
            xsol = route[xtemps][ytemps].xpred;
            ysol = route[xtemps][ytemps].ypred;
        }
    }

    qDebug("sol = %d",sol);

    for(int i=sol-1; i>=0; i--)
    {
        entities[player]->move(solution[i]);
        qDebug("%d", solution[i]);
        keyboard();
        animation();
        usleep(100000);
    }


    for(int i=0; i<size1; i++) free(route[i]); //fait planter
    free(route);
}


bool Maze::search(int X, int Y)
{
    static bool go = true;
    int vector = -1;
    int i = -1;
    int vectors[4];

    if(go)
    {
        entities[player]->route[entities[player]->index].x = entities[player]->x;
        entities[player]->route[entities[player]->index].y = entities[player]->y;

        entities[player]->index++;
    }

    go = true;

    entities[player]->x = X;
    entities[player]->y = Y;

    entities[player]->visited[Y][X] = 1;

    qDebug("x= %d  y= %d\n", entities[player]->x, entities[player]->y);

    playerVision();
    keyboard();
    animation();
    usleep(100000);

    if(!opened()) return false;

    if(squares[Y][X] == KEY) playerHasKey = true;

    if(squares[Y][X] == DOOR)
    {
        playerHasDoor = true;

        if(playerHasKey)
        {
            return false;
        }
    }

    if(playerHasDoor && playerHasKey)
    {
        dijkstra();
        return false;
    }

    if(canMove(X, Y, UP)){ i++; vectors[i] = UP; }
    if(canMove(X, Y, DOWN)){ i++; vectors[i] = DOWN; }
    if(canMove(X, Y, LEFT)){ i++; vectors[i] = LEFT; }
    if(canMove(X, Y, RIGHT)){ i++; vectors[i] = RIGHT; }

    for(int j=0; j<=i; j++) qDebug("%d", vectors[j]); //le qDebug est sur j

    if(i!=-1) vector = vectors[rand()%(i+1)];

    qDebug("vector = %d", vector);

    switch(vector)
    {
        case UP: if(search(X, Y - 1)) return true; break;
        case DOWN: if(search(X, Y + 1)) return true; break;
        case LEFT: if(search(X - 1, Y)) return true; break;
        case RIGHT: if(search(X + 1, Y)) return true; break;
        case -1: entities[player]->index--;

        if(entities[player]->index < 0)
        {
            App->close(); break;
        }

        go = false; if(search(entities[player]->route[entities[player]->index].x, entities[player]->route[entities[player]->index].y)) return true; break;
    }

    return false;
}


bool Maze::canMove(int X, int Y, int vector)
{
    int visited, mem, mem2, mem3, mem4;

    switch(vector)
    {
        case UP:

            visited = entities[player]->visited[Y - 1][X];
            mem = entities[player]->mem[Y - 1][X];

            if((visited == 0) && (mem != WALL))
            {
                if(Y - 2 >= 0)
                    mem2 = entities[player]->mem[Y - 2][X];
                else mem2 = WALL;

                mem3 = entities[player]->mem[Y - 1][X - 1];
                mem4 = entities[player]->mem[Y - 1][X + 1];

                if((mem2 == WALL)&&(mem3 == WALL)&&(mem4 == WALL)&&(squares[Y - 1][X]!=KEY)&&(squares[Y - 1][X]!=DOOR)) return false;

                else return true;
            }

            break;

        case DOWN:
            visited = entities[player]->visited[Y + 1][X];
            mem = entities[player]->mem[Y + 1][X];

            if((visited == 0) && (mem != WALL))
            {
                if(Y + 2 < size1)
                    mem2 = entities[player]->mem[Y + 2][X];
                else mem2 = WALL;

                mem3 = entities[player]->mem[Y + 1][X - 1];
                mem4 = entities[player]->mem[Y + 1][X + 1];

                if((mem2 == WALL)&&(mem3 == WALL)&&(mem4 == WALL)&&(squares[Y + 1][X]!=KEY)&&(squares[Y + 1][X]!=DOOR)) return false;

                else return true;
            }

            break;

        case LEFT:
            visited = entities[player]->visited[Y][X - 1];
            mem = entities[player]->mem[Y][X - 1];

            if((visited == 0) && (mem != WALL))
            {
                if(X - 2 >= 0)
                    mem2 = entities[player]->mem[Y][X - 2];
                else mem2 = WALL;

                mem3 = entities[player]->mem[Y - 1][X - 1];
                mem4 = entities[player]->mem[Y + 1][X - 1];

                if((mem2 == WALL)&&(mem3 == WALL)&&(mem4 == WALL)&&(squares[Y][X - 1]!=KEY)&&(squares[Y][X - 1]!=DOOR)) return false;

                else return true;
            }

            break;

        case RIGHT:
            visited = entities[player]->visited[Y][X + 1];
            mem = entities[player]->mem[Y][X + 1];

            if((visited == 0) && (mem != WALL))
            {
                if(X + 2 < size2)
                    mem2 = entities[player]->mem[Y][X + 2];
                else mem2 = WALL;

                mem3 = entities[player]->mem[Y - 1][X + 1];
                mem4 = entities[player]->mem[Y + 1][X + 1];

                if((mem2 == WALL)&&(mem3 == WALL)&&(mem4 == WALL)&&(squares[Y][X + 1]!=KEY)&&(squares[Y][X + 1]!=DOOR)) return false;

                else return true;
            }

            break;
    }

    return false;
}
