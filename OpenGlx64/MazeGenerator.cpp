#include "MazeGenerator.h"

random_device rdev;
mt19937 rng(rdev());
uniform_int_distribution<mt19937::result_type> dist100(1, 100);


int Grid::index(int i, int j)
{
    if (i<0 || j<0 || i>COL - 1 || j > COL - 1)
    {
        return -1;
    }
    return j + i * COL;
}

Grid Grid::checkNeigbors(Grid* grid)
{
    {
        vector<Grid>neigbors;
        //neigbors.clear();

        int indexValue[4];
        indexValue[0] = index(i - 2, j);
        indexValue[1] = index(i, j + 2);
        indexValue[2] = index(i + 2, j);
        indexValue[3] = index(i, j - 2);

        for (int x = 0; x < 4; x++)
        {
            if (indexValue[x] != -1)
            {
                if (!grid[indexValue[x]].visited)
                {
                    neigbors.push_back(grid[indexValue[x]]);
                }
            }
        }
        if (neigbors.size() > 0)
        {
            int r = dist100(rng) % neigbors.size();
            hasNextGrid = true;
            return neigbors[r];
        }
        else
        {
            hasNextGrid = false;
        }
    }
}

void Maze::removeWalls(Grid* grid, Grid a, Grid b)
{
    int y = a.getI() - b.getI();
    if (y == 2)
    {
        grid[a.getJ() + (a.getI() - 1) * COL].setValue(0);
        grid[b.getJ() + (b.getI() + 1) * COL].setValue(0);
    }
    else if (y == -2)
    {
        grid[a.getJ() + (a.getI() + 1) * COL].setValue(0);
        grid[b.getJ() + (b.getI() - 1) * COL].setValue(0);
    }
    int x = a.getJ() - b.getJ();
    if (x == 2)
    {
        grid[(a.getJ() - 1) + a.getI() * COL].setValue(0);
        grid[(b.getJ() + 1) + b.getI() * COL].setValue(0);
    }
    else if (x == -2)
    {
        grid[(a.getJ() + 1) + a.getI() * COL].setValue(0);
        grid[(b.getJ() - 1) + b.getI() * COL].setValue(0);
    }
}

Maze::Maze()
{
    grid = new Grid[COL * COL];
    myMaze = new int[COL * COL];
}

Maze::~Maze()
{
    delete myMaze;
}

void Maze::generateMaze()
{
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (i % 2 == 0 || j % 2 == 0)
            {
                grid[j + i * COL].setValue(1);
            }
        }
    }

    int row = 1;

    grid[row * COL + 1].setVisited(true);
    grid[row * COL + 1].setValue(0);


    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            grid[j + i * COL].setI(i);
            grid[j + i * COL].setJ(j);
        }
    }

    stack<Grid>myStack;

    Grid current = grid[row * COL + 1];
    while (true)
    {
        Grid next = current.checkNeigbors(grid);
        if (current.getHasNextGrid())
        {
            //step 1
            next.setVisited(true);
            grid[next.getJ() + next.getI() * COL].setVisited(true);

            //step 2
            myStack.push(current);

            //step 3
            removeWalls(grid, current, next);

            //for visual site
            grid[next.getJ() + next.getI() * COL].setValue(3);
            grid[current.getJ() + current.getI() * COL].setValue(0);
            grid[next.getJ() + next.getI() * COL].setValue(0);

            //step 4
            current = next;
        }
        else if (myStack.size() != 0)
        {
            current = myStack.top();
            myStack.pop();
            grid[current.getJ() + current.getI() * COL].setValue(3);
            grid[current.getJ() + current.getI() * COL].setValue(0);
        }
        else
        {
            break;
        }
    }

    for (unsigned int i = 0; i < COL * COL; i++)
    {
        myMaze[i] = grid[i].getValue();
    }
    
    delete grid;
}

int* Maze::getMaze()
{
    return this->myMaze;
}

void Maze::manipulate(glm::vec3* enemyPositions)
{
    myMaze[17] = 0;
    myMaze[1073] = 0;

    
    int enemyPosIndex = 0;

    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            int indexY[] = { i - 1,i ,i ,i + 1 };
            int indexX[] = { j,j - 1,j + 1,j };
            if (isIndexValid(i,j) && myMaze[i * COL + j]==0)
            {
                int t = 0;
                vector<int>temp;
                temp.clear();
                for (unsigned int valueOfCheckingIndex = 0; valueOfCheckingIndex < 4; valueOfCheckingIndex++)
                {   
                    if (isIndexValid(indexY[valueOfCheckingIndex], indexX[valueOfCheckingIndex]) &&
                        myMaze[indexY[valueOfCheckingIndex] * COL + indexX[valueOfCheckingIndex]] == 1)
                    {
                        t++;
                        temp.push_back(valueOfCheckingIndex);
                    }
                }
                if (t == 3)
                {
                    t = 1;
                    myMaze[indexY[temp[t]] * COL + indexX[temp[t]]] = 0;
                    if (enemyPosIndex <= 2)
                    {
                        float x, y = 1.0, z;
                        x = (indexY[temp[t]] * COL + indexX[temp[t]]) % COL * 2.0;
                        z = (indexY[temp[t]] * COL + indexX[temp[t]]) / COL * 2.0;
                        enemyPositions[enemyPosIndex] = glm::vec3(x, -0.4f, z);
                        enemyPosIndex++;
                        cout << enemyPosIndex << endl;
                    }
                }
            }
        }
    }
}