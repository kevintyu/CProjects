#include <stdio.h>
#include <stdlib.h>
#include "obstacles.h"
#include "display.h"

int hitsObject(short x1, short y1, short x2, short y2, short shapex1, short shapey1, short shapex2, short shapey2);
int inObject(short x, short y, short shapex1, short shapey1, short shapew1, short shapeh1);
Vertex* getVertexVert(Vertex* startV, Vertex* v, short newY);
Vertex* getVertexHor(Vertex* startV, Vertex* v, short newX);
Vertex* getVertex(Environment* env, short x, short y);
void upVertexNeighbours(Environment * env, Vertex *vTmp);
void rightVertexNeighbours(Environment * env, Vertex *vTmp);
void downVertexNeighbours(Environment * env, Vertex *vTmp);
void leftVertexNeighbours(Environment * env, Vertex *vTmp);
void freeVertexInNeighbour(Vertex *v, Neighbour* n);
// This is a helper function that determines whether or not line segment (v1---v2) intersects line segment (v3---v4)
unsigned char linesIntersect(short v1x, short v1y, short v2x, short v2y, short v3x, short v3y, short v4x, short v4y) {
  	float uA = ((v4x-v3x)*(v1y-v3y) - (v4y-v3y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));
  	float uB = ((v2x-v1x)*(v1y-v3y) - (v2y-v1y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));

  	// If uA and uB are between 0-1, there is an intersection
  	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
		return 1;

	return 0;
}

/*
for creating Edges
loop through every vertex in vertex list A
    loop through every vertex vertex list B
        check if B is left or right or top or bottom {
            create a neighbour pointer alloc NEIGHBOUR
            if first/last null ? let A.firstNeighbour = NEIGHBOUR A.lastNeighbour = NEIGHBOUR
            otherwise, A.lastNeighbour.next = NEIGHBOUR
        }
*/

// Create a grid of vertices with a horizontal and vertical gap between them of env->gridSize pixels
void createGrid(Environment *env) {
  Vertex *vList = (Vertex*) malloc(sizeof(Vertex));
  if (vList == NULL){
    printf("Memory allocation error\n");
    exit(-1);
  }
  vList->x=0;
  vList->y=0;

  env->firstVertex = vList;
  Vertex *vTmp = vList;
  for (int i = 0; i <= ENV_HEIGHT/env->gridSize; i++){
    for (int j = 0; j <= ENV_WIDTH/env->gridSize; j++){
      if (i != 0 || j!= 0){
        Vertex *vTmpTmp = (Vertex*)malloc(sizeof(Vertex));
        if (vTmpTmp == NULL){
          printf("Memory allocation error\n");
          exit(-1);
        }
        // vTmpTmp->firstNeighbour = nTmpOne;
        // vTmpTmp->lastNeighbour = nTmpOne;
        vTmpTmp->y = i*env->gridSize;
        vTmpTmp->x = j*env->gridSize;
        vTmp->nextVertex = vTmpTmp;
        vTmp = vTmp->nextVertex;
        // printf("%d %d\n", i, j);
      }
    }
      // printf("something wrong 8\n");
  }
  // printf("something wrong 6\n");
  vTmp = vList;
  if(vTmp->nextVertex == NULL){
    printf("over here\n" );
  }
  // getVertexAbove();
  // printf("%s\n", );
  rightVertexNeighbours(env, vTmp);

  vTmp = vList;
  if(vTmp->nextVertex == NULL){
    printf("over here\n" );
  }
  upVertexNeighbours(env, vTmp);

  vTmp = vList;
  leftVertexNeighbours(env,vTmp);

  vTmp = vList;
  downVertexNeighbours(env,vTmp);

  // (6, )

  printf("%d \n",linesIntersect(300, 250, 350, 300, 320,280,320+40,280));
  printf("%d \n",hitsObject(300, 250, 350, 300, 320,280,40,180));
  // printf("%d \n",linesIntersect(350, 300, 250, 300, ,280,320+40,280));
  // printf("%d \n",linesIntersect(300, 300, 350, 300, 320,280,320,280-120));

  return;

}


// checks if neighbour, not itself and if is it not crossing an obstacle border
// if all yes then return 1

/* function takes in short x1, y1 which are coordinates of the first vertex
short x2, y2 which are coordinates of the second vertex
short shapex1, shapey1 which are coordinates a vertex for a shape
*/
int hitsObject(short x1, short y1, short x2, short y2, short shapex1, short shapey1, short shapew1, short shapeh1){

  // derive other 3 coordinates
  short toprightx, toprighty;
  short bottomleftx, bottomlefty;
  short bottomrightx, bottomrighty;

  toprightx = shapex1+shapew1;
  toprighty = shapey1;
  bottomleftx = shapex1;
  bottomlefty = shapey1-shapeh1;
  bottomrightx = toprightx;
  bottomrighty = bottomlefty;

  if(linesIntersect(x1, y1, x2, y2, shapex1, shapey1, toprightx, toprighty)){
    return 1;
  }
  // checking bottom side
  if(linesIntersect(x1, y1, x2, y2, bottomleftx, bottomlefty, bottomrightx, bottomrighty)){
    return 1;
  }
  if(linesIntersect(x1, y1, x2, y2, shapex1, shapey1, bottomleftx, bottomlefty)){
    return 1;
  }
  // checking right side
  if(linesIntersect(x1, y1, x2, y2, toprightx, toprighty, bottomrightx, bottomrighty)){
    return 1;
  }
  return 0;
}

int inObject(short x, short y, short shapex1, short shapey1, short shapew1, short shapeh1){

  // derive other 3 coordinates
  short toprightx, toprighty;
  short bottomleftx, bottomlefty;
  short bottomrightx, bottomrighty;

  toprightx = shapex1+shapew1;
  toprighty = shapey1;
  bottomleftx = shapex1;
  bottomlefty = shapey1-shapeh1;
  bottomrightx = toprightx;
  bottomrighty = bottomlefty;
  /**
  if x betweentop left x and top right x
    if y between top left y and bottom left y
      in object
    else not in object
  **/
  if (x >= shapex1 && x <= toprightx) {
    if(y <= shapey1 && y >= bottomlefty) {
      // printf("(%d, %d), %d, %d, %d, %d\n", x, y, shapex1, shapey1, shapew1, shapeh1);
      return 1;
    }
  }

  return 0;
}

//takes a vertex as input then iterates through the linked list of the vertex, and stop when the y is current vertex's + env->gridSize and same x
// do for all directions
Vertex* getVertexVert(Vertex* startV, Vertex* v, short newY){
  //print starting v
  // printf("%d, %d \n", v->x, v->y);
  short currentX = v->x;
  // loop through list until vertex with aboveY and currentX is found otherwise NULL
  // printf("%d\n", currentX);
  if (newY > 0) {
    while(v->nextVertex != NULL){
      v = v->nextVertex;
      if(currentX == v->x && v->y == newY) {
        // printf("returned true");
          return v;
      }
    }
  } else if (newY < 0) {
    while(startV->nextVertex != NULL) {
      startV = startV->nextVertex;
      if(currentX == startV->x && startV->y == newY) {
        // printf("returned true");
          return startV;
      }
    }
  }
  return NULL;
}

Vertex* getVertexHor(Vertex* startV, Vertex* v, short newX) {
  short currentY = v->y;
  if (newX > 0) {

    while(v->nextVertex != NULL){
      v = v->nextVertex;
      if(v->y == currentY && v->x == newX) {
        return v;
      }
    }
  } else {
    while(startV->nextVertex != NULL){
      startV = startV->nextVertex;
      if(startV->y == currentY && startV->x == newX) {
        return startV;
      }
    }
  }
  return NULL;
}

Vertex *getVertex(Environment* env, short x, short y) {
  Vertex *tmp = env->firstVertex;
  while(tmp != NULL) {
    if (tmp->x == x && tmp->y == y) {
      return tmp;
    }
    tmp = tmp->nextVertex;
  }
  return NULL;
}
void rightVertexNeighbours(Environment * env, Vertex *vTmp) {
  int rowCounter = 0;
  // printf("%d\n",(int)(ENV_WIDTH/env->gridSize));
  while (vTmp->nextVertex != NULL) {
    //if rowCounter is not right
      //skip
    if (rowCounter == (int)(ENV_WIDTH/env->gridSize)){
      rowCounter = 0;
      vTmp = vTmp->nextVertex;
      // printf("WHAT IS THIS NUMBER V");
      // printf("%d\n",(int)(rowCounter));
      continue;
    } else {
      rowCounter++;
    }
    int hitObject = 0;
    // Initialize a neighbour list
    // if helper returns true add neighbour to neighbour list
    Neighbour *neigh = (Neighbour*) malloc(sizeof(Neighbour));
    for (int i=0; i<env->numObstacles; i++) {
      // checks all horizontal lines
      if (hitsObject(vTmp->x, vTmp->y, vTmp->nextVertex->x, vTmp->nextVertex->y, env->obstacles[i].x, env->obstacles[i].y, env->obstacles[i].w, env->obstacles[i].h)){
        hitObject = 1;
        break;
      }
    }
    if (!hitObject) {
      if (vTmp->firstNeighbour == NULL && vTmp->lastNeighbour == NULL){
        neigh->vertex = vTmp->nextVertex;
        vTmp->firstNeighbour = neigh;
        vTmp->lastNeighbour = neigh;
      } else {
        neigh->vertex = vTmp->nextVertex;
        vTmp->lastNeighbour->next = neigh; // ensure next points to something
        vTmp->lastNeighbour = neigh; // actually sets the current neigh as last neighbour
      }
    }
    vTmp = vTmp->nextVertex;
  }
}

void leftVertexNeighbours(Environment * env, Vertex *vTmp) {
  int rowCounter = 0;
  // printf("%d\n",(int)(ENV_WIDTH/env->gridSize));
  while (vTmp->nextVertex != NULL) {
    // }
    int hitObject = 0;
    // Initialize a neighbour list
    // if helper returns true add neighbour to neighbour list
    Neighbour *neigh = (Neighbour*) malloc(sizeof(Neighbour));
    if (neigh == NULL){
      printf("MEMORY ALLOCATION ERROR\n" );
      exit(-1);
    }
    Vertex *vertexleft = getVertexHor(env->firstVertex, vTmp, (short)vTmp->x-env->gridSize);
    for (int i=0; i<env->numObstacles; i++) {
      // checks all horizontal lines
      if (vertexleft == NULL) {
        // printf("ALWAYS NULL\n");
        break;
      }
      if (hitsObject(vTmp->x, vTmp->y, vertexleft->x, vertexleft->y, env->obstacles[i].x, env->obstacles[i].y, env->obstacles[i].w, env->obstacles[i].h)){
        hitObject = 1;
        break;
      }
    }
    if (!hitObject) {

      if (vertexleft != NULL) {
        if (vTmp->firstNeighbour == NULL && vTmp->lastNeighbour == NULL){
          neigh->vertex = vertexleft;
          vTmp->firstNeighbour = neigh;
          vTmp->lastNeighbour = neigh;
        } else {
          neigh->vertex = vertexleft;
          vTmp->lastNeighbour->next = neigh; // ensure next points to something
          vTmp->lastNeighbour = neigh; // actually sets the current neigh as last neighbour
        }
      }
    }
    vTmp = vTmp->nextVertex;
  }
}
void upVertexNeighbours(Environment * env, Vertex *vTmp) {
  int rowCounter = 0;
  // printf("%d\n",(int)(ENV_WIDTH/env->gridSize));
  while (vTmp->nextVertex != NULL) {
    // }
    int hitObject = 0;
    // Initialize a neighbour list
    // if helper returns true add neighbour to neighbour list
    Neighbour *neigh = (Neighbour*) malloc(sizeof(Neighbour));
    Vertex *vertexAbove = getVertexVert(env->firstVertex, vTmp, (short)vTmp->y+env->gridSize);
    for (int i=0; i<env->numObstacles; i++) {
      // checks all horizontal lines
      if (vertexAbove == NULL) {
        // printf("ALWAYS NULL\n");
        break;
      }
      if (hitsObject(vTmp->x, vTmp->y, vertexAbove->x, vertexAbove->y, env->obstacles[i].x, env->obstacles[i].y, env->obstacles[i].w, env->obstacles[i].h)){
        hitObject = 1;
        break;
      }
    }
    if (!hitObject) {

      if (vertexAbove != NULL) {
        if (vTmp->firstNeighbour == NULL && vTmp->lastNeighbour == NULL){
          neigh->vertex = vertexAbove;
          vTmp->firstNeighbour = neigh;
          vTmp->lastNeighbour = neigh;
        } else {
          neigh->vertex = vertexAbove;
          vTmp->lastNeighbour->next = neigh; // ensure next points to something
          vTmp->lastNeighbour = neigh; // actually sets the current neigh as last neighbour
        }
      }
    }
    vTmp = vTmp->nextVertex;
  }
}

void downVertexNeighbours(Environment * env, Vertex *vTmp) {
  int rowCounter = 0;
  // printf("%d\n",(int)(ENV_WIDTH/env->gridSize));
  while (vTmp->nextVertex != NULL) {
    // }
    int hitObject = 0;
    // Initialize a neighbour list
    // if helper returns true add neighbour to neighbour list
    Neighbour *neigh = (Neighbour*) malloc(sizeof(Neighbour));
    Vertex *vertexBelow = getVertexVert(env->firstVertex, vTmp, (short)vTmp->y-env->gridSize);
    for (int i=0; i<env->numObstacles; i++) {
      // checks all horizontal lines
      if (vertexBelow == NULL) {
        // printf("ALWAYS NULL\n");
        break;
      }
      if (hitsObject(vTmp->x, vTmp->y, vertexBelow->x, vertexBelow->y, env->obstacles[i].x, env->obstacles[i].y, env->obstacles[i].w, env->obstacles[i].h)){
        hitObject = 1;
        break;
      }
    }
    if (!hitObject) {

      if (vertexBelow != NULL) {
        if (vTmp->firstNeighbour == NULL && vTmp->lastNeighbour == NULL){
          neigh->vertex = vertexBelow;
          vTmp->firstNeighbour = neigh;
          vTmp->lastNeighbour = neigh;
        } else {
          neigh->vertex = vertexBelow;
          vTmp->lastNeighbour->next = neigh; // ensure next points to something
          vTmp->lastNeighbour = neigh; // actually sets the current neigh as last neighbour
        }
      }
    }
    vTmp = vTmp->nextVertex;
  }
}
// This function removes all vertices that are invalid (i.e., inside an obstacle).
void removeInvalidVertices(Environment *env) {
  Vertex* v = env->firstVertex;
  Vertex* prev = v;
  int counter=0;
  while(v->nextVertex != NULL){
    int insideObject = 0;
    for (int i=0; i<env->numObstacles; i++) {
      if (inObject(v->x, v->y, env->obstacles[i].x, env->obstacles[i].y, env->obstacles[i].w, env->obstacles[i].h)){

        // printf("%d\n", counter);
        insideObject = 1;
        counter++;
        break;
      }
    }
    if (insideObject) {
      Vertex* next = v->nextVertex;
      // loop through neighbours
      Neighbour* curN = v->firstNeighbour;
      while(curN != NULL) {
        // free vertex in the neighbours of neighbours
        if (curN->vertex != NULL) {
          freeVertexInNeighbour(v, curN->vertex->firstNeighbour);
        }
        curN = curN->next;
      }
      free(v);
      if (prev == v) {
        env->firstVertex = v->nextVertex;
        v = v->nextVertex;
        prev = v;
      } else {
        v = v->nextVertex;
        prev->nextVertex = v;
      }
    } else {
      prev = v;
      v = v->nextVertex;
    }
  }
}

void freeVertexInNeighbour(Vertex *v, Neighbour* n) {
  Neighbour* prev = n;
  while (n != NULL) {
    if (n->vertex->x == v->x && n->vertex->y == v->y){
      Neighbour* tmp = n;
      n = n->next;
      prev->next = n;
      free(tmp);
      return;
    }
    prev = n;
    n = n->next;
  }
}
// Add diagonal edges to the graph, assuming that they don't intersect an obstacle
void addCrossEdges(Environment *env) {
  Vertex *curNode = env->firstVertex;
  while (curNode != NULL) {
    // top right node
    Vertex *topRight = getVertex(env, (short)curNode->x+env->gridSize, (short)curNode->y+env->gridSize);
    Vertex *topLeft = getVertex(env, (short)curNode->x-env->gridSize, (short)curNode->y+env->gridSize);
    // Vertex *vertex = getVertex(env, (short)300, (short)350);

    if (topRight != NULL) {
      int hitAnyObject = 0;
      for (int i=0; i<env->numObstacles; i++) {
        if(curNode->x == 300 && curNode->y == 250) {
          printf("reached");
        }
        if (hitsObject(curNode->x, curNode->y, topRight->x, topRight->y, env->obstacles[i].x, env->obstacles[i].y, env->obstacles[i].w, env->obstacles[i].h)){
          hitAnyObject++;
          break;
        }
      }
      if (hitAnyObject == 0) {
        Neighbour *neigh = (Neighbour*) malloc(sizeof(Neighbour));
        if (curNode->firstNeighbour == NULL && curNode->lastNeighbour == NULL){
          neigh->vertex = topRight;
          curNode->firstNeighbour = neigh;
          curNode->lastNeighbour = neigh;
        } else {
          neigh->vertex = topRight;
          curNode->lastNeighbour->next = neigh; // ensure next points to something
          curNode->lastNeighbour = neigh; // actually sets the current neigh as last neighbour
        }
        // displayEnvironment(env); getchar();
      }
    }
    if (topLeft != NULL) {
      int hitAnyObject = 0;
      for (int i=0; i<env->numObstacles; i++) {
        if (hitsObject(curNode->x, curNode->y, topLeft->x, topLeft->y, env->obstacles[i].x, env->obstacles[i].y, env->obstacles[i].w, env->obstacles[i].h)){
          hitAnyObject++;
          break;

          // displayEnvironment(env); getchar();
          // break;
        }
      }
      if (hitAnyObject == 0) {
        Neighbour *neigh = (Neighbour*) malloc(sizeof(Neighbour));
        if (curNode->firstNeighbour == NULL && curNode->lastNeighbour == NULL){
          neigh->vertex = topLeft;
          curNode->firstNeighbour = neigh;
          curNode->lastNeighbour = neigh;
        } else {
          neigh->vertex = topLeft;
          curNode->lastNeighbour->next = neigh; // ensure next points to something
          curNode->lastNeighbour = neigh; // actually sets the current neigh as last neighbour
        }
      }
    }
    curNode = curNode->nextVertex;
  }
}


// This procedure cleans up everything by creeing all alocated memory
void cleanupEverything(Environment *env) {
  Vertex* v = env->firstVertex;
  Vertex* prev = v;
  while (v != NULL) {
    Vertex* next = v->nextVertex;
    // loop through neighbours
    Neighbour* curN = v->firstNeighbour;
    while(curN != NULL) {
      // free vertex in the neighbours of neighbours
      if (curN->vertex != NULL) {
        freeVertexInNeighbour(v, curN->vertex->firstNeighbour);
      }
      curN = curN->next;
    }
    env->firstVertex = v->nextVertex;
    v = v->nextVertex;
    free(prev);
    prev = v;
  }
}
