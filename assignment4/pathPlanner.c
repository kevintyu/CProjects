#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "obstacles.h"

int createVertices(Environment *env){
    //create vertices not neighboburs
    //create edges -> make neighbours inside vertices
    //27 neighbours
    //loop through x and y pair of obstacles array
    //make space for one vertice
    //first vertice is malloc
    //otherwise use realloc
    //set a new vertice for each pair
    //return the number of vertices
  if(env->numVertices == 0){
    env->vertices = (Vertex *) malloc(sizeof(Vertex));

  }
  if (env->numVertices == NULL) {
    printf("Memory allocation error\n");
    exit(-1);
  }
  for(int i = 0; i<7; i++){
    env->numVertices+=1;
    env->vertices = (Vertex *) realloc(env->numVertices*sizeof(vertex)); // reallocate memory for each vertex
    env->vertices[i].x = env->obstacles[i].x; // x coordinate for vertex
    env->vertices[i].y = env->obstacles[i].y; // y coordinate for vertex
    env->vertices[i].obstacle = env->obstacles[i];

    env->vertices[i].firstNeighbour.vertex.x = env->obstacles[i].x; // grab the x coord for the first vertex
    env->vertices[i].firstNeighbour.vertex.y = env->obstacles[i].y; // grab the y coord for the first vertex
    env->vertices[i].firstNeighbour.next.x = env->obstacles[i].x + env->obstacles[i].w;
    env->vertices[i].firstNeighbour.next.y = env->obstacles[i].x + env->obstacles[i].h;

  }

  return env->numVertices
}
int createEdges(Environment *env){
  //loop through vertices array
  //add vertex to neighbour of this Vertex (linked list style)
  //do not add if the vertex is itself
  //return number of edges
  int edgeCounter = 0;
  return edgeCounter;
}
int createEdges(Environment *env){
  //loop through vertices array
  //add vertex to neighbour of this Vertex (linked list style)
  //do not add if the vertex is itself
  //return number of edges
  int edgeCounter = 0;
  return edgeCounter;
}
