#include "vertice.h"

using namespace std;

struct Node* initNode(float x, float y, int type)
{
    struct Node *node = new struct Node;
    node->x    = x;
    node->y    = y;
    node->id   = 0;
    node->type = type;
    node->next = NULL;
    return node;
}

struct Segment* initSegment(Node *node1, Node *node2,int type)
{
    struct Segment *segment = new struct Segment;
    segment.node1 = node1;
    segment.node2 = node2;
    segment.type  = type;
    segment.id    = 0;
    segment.next  = NULL;

    return segment;
}
