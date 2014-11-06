#include <iostream>

enum type {ORIGINAL, GENERATED};

struct Node
{
    float x;
    float y;
    int id;
    int type;
    struct Node *next;
};

struct Nodes
{
    int nb;
    struct Node *first;
};

struct Segment
{
    Node *node1;
    Node *node2;
    int id;
    int type;
    struct Node *next;
};

struct Segments
{
    int nb;
    struct Segment *first;
};

//nodes stuff
struct Nodes* initNodes();
struct Node* initNode(float x, float y, int type);
struct Node* getNode(struct Nodes *nodes, int id);
void addNode(struct Nodes *nodes, struct Node *node);

//segments stuff
struct Segments* initSegments();
struct Segment* initSegment(Node *node1, Node *node2,int type);
