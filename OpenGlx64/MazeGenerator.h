#ifndef MAZEGENERATOR
#define MAZEGENERATOR

#include <iostream>
#include <random>
#include <stack>

using namespace std;

const int COL = (16 * 2) + 1;

class Grid
{
private:
    int value = 2;
    bool visited = false;
    bool hasNextGrid = false;
    int i, j;

private:
    int index(int i, int j);

public:
    Grid(int value = 2, bool visited = false, bool hasNextGrid = false, int i = 0, int j = 0)
    {
        this->value = value;
        this->visited = visited;
        this->hasNextGrid = hasNextGrid;
        this->i = 0;
        this->j = 0;
    }
    ///For Maze Generator
    Grid checkNeigbors(Grid* grid);
    

    //set and get functions
public:
    void setValue(int val)
    {
        this->value = val;
    }
    int getValue() const
    {
        return this->value;
    }

    void setI(int val)
    {
        this->i = val;
    }
    int getI() const
    {
        return this->i;
    }
    void setJ(int val)
    {
        this->j = val;
    }
    int getJ() const
    {
        return this->j;
    }

    void setHasNextGrid(bool val)
    {
        this->hasNextGrid = val;
    }
    bool getHasNextGrid() const
    {
        return this->hasNextGrid;
    }

    void setVisited(bool val)
    {
        this->visited = val;
    }
    bool getVisited() const
    {
        return this->visited;
    }
};

class Maze
{
private:
    Grid* grid;
    int* myMaze;

private:
    void removeWalls(Grid* grid, Grid a, Grid b);
    
public:
    Maze();
    ~Maze();

    void generateMaze();
    int* getMaze();
    void manipulate();

    bool isIndexValid(int i, int j)
    {
        if (i<1 || j<1 || i>COL - 2 || j > COL - 2)
        {
            return false;
        }
        return true;
    }
};



#endif // !MAZEGENERATOR