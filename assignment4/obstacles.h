typedef struct Obstacle {
    short x;
    short y;
    short w;
    short h;
} Obstacle;
typedef struct Vertex {
    short x;
    short y;
    struct Neighbour *firstNeighbour;
    struct Neighbour *lastNeighbour;
    struct Obstacle *obstacle;
} Vertex;
typedef struct Neighbour {
    struct Vertex *vertex;
    struct Neighbour *next;
} Neighbour;
typedef struct Environment {
    struct Obstacle *obstacles;
    struct Vertex *vertices;
    int numObstacles;
    int numVertices;
} Environment;
