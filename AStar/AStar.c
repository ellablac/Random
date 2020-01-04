#define TRUE 0
#define FALSE 1
#define numNODES 12

//int roomMap[3][4];
int offsX, offsY; // offset used in conversion from global to local

struct xy
{
    int x;
    int y;
};

int currCoord[2] = {3, 1}; //universal
struct xy obst [numNODES]; //obstacles' coordinates
int obstN[numNODES]; // obstacles as nodes
struct xy victs [numNODES]; //victims' coordinates
// victims as nodes
int victsN [numNODES] = {11,2, -1, -1, -1, -1, -1, -1, -1, -1}; 
int parent[12];
int goal;
int path[12][2]; 

char adjMx[12][12];
char adjMxT[12][12] =
{{1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
      {0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
      {1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
      {0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1},
      {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1},
      {1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
      {1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
      {1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0},
      {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1},
      {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0},
      {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1}};

//int adjMxB[12][12];
//int adjMxC[12][12];
//int adjMxD[12][12];

int hN[numNODES][numNODES] = //heuristic cost between every 2 nodes
{{0,5,10,5,7,11,10,11,14,15,15,18},
      {5,0,5,7,5,7,11,10,11,15,15,15},
      {10,5,0,11,7,5,14,11,10,18,15,15},
      {5,7,11,0,5,10,5,7,11,10,11,14},
      {7,5,7,5,0,5,7,5,7,11,10,11},
      {11,7,5,10,5,0,11,7,5,14,11,10},
      {10,11,14,5,7,11,0,5,10,5,7,11},
      {11,10,11,7,5,7,5,0,5,7,5,7},
      {14,11,10,11,7,5,10,5,0,11,7,5},
      {15,15,18,10,11,14,5,7,11,0,5,10},
      {15,15,15,11,10,11,7,5,7,5,0,5},
      {18,15,15,14,11,10,11,7,5,10,5,0}};

int gN[numNODES];
// 0 if in the list, 1 otherwise
char openList[12] =
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};
int bittest;


//converts an array of global x and y coordinates to local
void obstsGtoL()
{
    int i, j;
    
    if (obst[0].x < 5)
      offsX = 1;
    else
      offsX = 7;
    if (obst[0].y < 5)
      offsY = 1;
    else
      offsY = 6;
    
    
    j=0;
    for (i=0; i<numNODES; i++)
      {
        //check bounds
        if ((obst[i].x-offsX >=0) && (obst[i].x-offsX <=2) &&
            (obst[i].y-offsY >=0) && (obst[i].y-offsY <=3))
          {
            obst[j].x = obst[i].x-offsX;
            obst[j].y = obst[i].y-offsY;
            j++;
        }
    }
    for ( ; j<numNODES; j++)
      {
        obst[j].x = -1;
        obst[j].y = -1;
    }
    
}

void convertLtoG(struct xy arr[])
{
    int i;
    
    
    for (i=0; i<numNODES; i++)
      {
        arr[i].x += offsX;
        arr[i].y += offsY;
    }
}

// Given local x and y coordinates, returns index of the
// corresponding node
void xyToNode(struct xy coords[], int nodes[])
{
    int i=0;
    for (i=0; i<numNODES; i++)
      nodes[i] = -1;
    for (i=0; i<numNODES; i++)
      {
        if (coords[i].x == -1)
          break;
        nodes[i]=(3 * coords[i].y + coords[i].x);
    }
}

// given a node index, converts to local coordinates
void nodeToXY(int * x, int * y, int n)
{
    *x = (int)(n%3);
    *y = (int)(n/3);
    //printf("x: %d y: %d\n", *x, *y);
}

//===================================================//
//            Initialization functions               //
//===================================================//
void initIntMx(int arr[][], int fill, int size1, int size2)
{
    int i, j;
    for (i=0; i<size1; i++)
      for (j=0; j<size2; j++)
        arr[i][j] = fill;
}
void initIntArr(int arr[], int fill, int size)
{
    int i;
    for (i=0; i<size; i++)
      arr[i] = fill;
}

void initStrArr(struct xy arr[], int size, int fill)
{
    int i;
    for (i=0; i<size; i++)
      {
        arr[i].x = fill;
        arr[i].y = fill;
    }
}

void setObstAM()
{
    int i, y;
    i=0;
    while (obstN[i]!=-1)
      {
        for (y=0; y<numNODES; y++)
          {
            adjMx[obstN[i]][y] = FALSE;
            adjMx[y][obstN[i]] = FALSE;
        }
        i++;
    }
}


//for testing
void setObstaclesT()
{
    //obst[0].x = 2; obst[0].y = 2;
    //obst[1].x = 2; obst[1].y = 3;
    //obst[2].x = 3; obst[2].y = 2;
    
    
}
void setVictimsT(struct xy vics[])
{
    vics[0].x = 2; vics[0].y = 2;
    vics[0].x = 2; vics[0].y = 4;
    
}

int isObstacle(int n)
{
    int i;
    i=0;
    while (obstN[i] != -1)
      {
        if (obstN[i] == n)
          return TRUE;
        i++;
    }
    return FALSE;
}

// set adj. matrix edges to true or false, depending
// on the path and obstacles
void initAdjMx()
{
    int i,j;
    for (i = 0; i< numNODES; i++)
      for (j=i; j<numNODES; j++)
        adjMx[i][j] = FALSE;
    
    
    adjMx[0][1] = TRUE;
    adjMx[0][3] = TRUE;
    adjMx[0][4] = TRUE;
    adjMx[1][2] = TRUE;
    adjMx[1][3] = TRUE;
    adjMx[1][4] = TRUE;
    adjMx[1][5] = TRUE;
    adjMx[2][4] = TRUE;
    adjMx[2][5] = TRUE;
    adjMx[3][4] = TRUE;
    adjMx[3][6] = TRUE;
    adjMx[3][7] = TRUE;
    adjMx[4][5] = TRUE;
    adjMx[4][6] = TRUE;
    adjMx[4][7] = TRUE;
    adjMx[4][8] = TRUE; 
    adjMx[5][7] = TRUE;  
    adjMx[5][8] = TRUE;
    adjMx[6][7] = TRUE;
    adjMx[6][9] = TRUE;
    adjMx[6][10] = TRUE;
    adjMx[7][8] = TRUE;
    adjMx[7][9] = TRUE;
    adjMx[7][10] = TRUE;
    adjMx[7][11] = TRUE;
    adjMx[8][10] = TRUE;
    adjMx[8][11] = TRUE;
    adjMx[9][10] = TRUE;  
    adjMx[10][11] = TRUE;
    
    // symmetrical
    for (i = 0; i< numNODES; i++)
      for (j=i+1; j<numNODES; j++)
        adjMx[j][i] = adjMx[i][j];
    
}

void computeCost()
{
    int i, j, x1, x2, y1, y2, dX, dY;
    
    
    for(i=0; i<numNODES; i++)
      for (j=0; j<numNODES; j++)
        {
          nodeToXY(&x1, &y1, i);
          nodeToXY(&x2, &y2, j);
          dX = x1 - x2;
          dY = y1 - y2;
          //printf("\ndX:%d dY:%d", dX, dY);
          hN[i][j] = (int)((sqrt((float)(dX*dX+dY*dY)))*5.0);
      }
}
//===================================================//
//                 A* search algorithm               //
//===================================================//
// Input: AdjMx, hN, victs, currCoord
// Uses: openList, gN
// Output: path
//
int findMinFN()
// returns index of the node with the lowest f(n)
// in the openList
{
    int i, lVal, lNode;
    lVal = 255;
    for (i=0; i<numNODES; i++)
      if (openList[i] == TRUE)
        if ((gN[i] + hN[i][goal])<lVal)
          {
            lNode = i;
            lVal = gN[i] + hN[i][goal];
          }
                  
    return lNode;
}

void runSearch()
{
  while(42)
  {
    int i;
    //find node in the open list with the lowest f(n)
      int cNode = findMinFN();
      int newGN, cGN;
      if (cNode == goal)
        break;
    
    cGN = gN[cNode];
    //printf("cNode: %d\n", cNode);
    //remove from open list
    openList[cNode] = FALSE;
    for (i=0; i<numNODES; i++)
      {
        newGN = cGN+hN[cNode][i];
      if ((adjMx[cNode][i] == TRUE) && (gN[i] > newGN))
        {
          openList[i] = TRUE;
          parent[i] = cNode;
            //gN[i]=cGN+newGN;
            gN[i]=newGN;
        }
       }

  }  
    
}
void writePath(int c)
{
    int pathN[12];
    int pathNRev[12];
    int curr=goal;
    int i = 0, j=0;
    while (curr !=c)
      {
        pathN[i] = curr;
        curr = parent[curr];
        i++;
    }
      
    for (i=i-1, j=0; i>=0; i--, j++)
      pathNRev[j] = pathN[i];
      
    printf("Path:\n");
    for (i=0; i<j; i++)
      {
        nodeToXY(&path[i][0], &path[i][1], pathNRev[i]);
                printf("%d %d,", path[i][0], path[i][1]);
        
     }     
}

int AStar()
{
    int i, curr;
    int currXYLocal[2]; 
    currXYLocal[0]= currCoord[0]-offsX;
    currXYLocal[1]= currCoord[1]-offsY;
    if ((currXYLocal[0] <0) || (currXYLocal[1] <0))
      {
        printf("Curr coord out of bounds");
        return FALSE;
    }
    curr = (3 * currXYLocal[1] + currXYLocal[0]);//3y+x
    goal = victsN[0];
    // initialize f(n) cost to high value
    initIntArr(gN, 255, numNODES);
    initIntArr(parent, -1, numNODES);
    initIntMx(path, -1, numNODES, 2);
    openList[curr] = TRUE;
    gN[curr] = 0;
    runSearch();
    writePath(curr);
    printf("Parents:\n");
    for (i=0; i<numNODES; i++)
      printf("%d %d\n", i, parent[i]);
    
    return TRUE;
}
//===================================================//
//                     MAIN                          //
//===================================================//
void main()
{
    int i = 0, j=0;
    
    initStrArr(obst, numNODES, -1);
    setObstaclesT();
    //printf ("obstacles1:\n");
    /*i=0;
    while (obst[i].x != -1)
      {
        printf("%d %d\n",obst[i].x, obst[i].y);
        i++;
    }*/
    //setVictims(victs);
    obstsGtoL();
    /*printf ("obstacles2:\n");
    i=0;
    while (obst[i].x != -1)
      {
        printf("%d %d\n",obst[i].x, obst[i].y);
        i++;
    }*/
    xyToNode(obst, obstN);
    //printf ("obstacles3:\n");
    i=0;
    /*while (obstN[i] != -1)
      {
        printf("%d\n",obstN[i]);
        i++;
    }*/
    
    initAdjMx();
    setObstAM();
    printf("Matrix:\n");
    for (i=0; i<numNODES; i++)
      {
        for (j=0; j<numNODES; j++)
          {
            printf ("%d ", adjMx[i][j]);
        }
        printf ("\n");
    }
    
    computeCost();
    /*printf("Cost Matrix:\n");
    for (i=0; i<numNODES; i++)
      {
        for (j=0; j<numNODES; j++)
          {
            if (hN[i][j] > 9)
              printf (" %d", hN[i][j]);
            else
              printf ("  %d", hN[i][j]);
        }
        printf ("\n");
    }*/
    
    AStar();
    
}
