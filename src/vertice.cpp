#include "vertice.h"

using namespace std;

struct Nodes* initNodes()
{
    struct Nodes *nodes = new struct Nodes;
    nodes->nb= 0;
    nodes->first = NULL;

    return nodes;
}

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



//generic method

void addNode(struct Nodes *nodes, struct Node *node)
{
    //find last node from nodes
    struct Node *node_ = nodes->first;

    if(nodes->first)
    {
        while(node_->next)
            node_ = node_->next;

        nodes->nb++;
        node->id = nodes->nb;
        node_->next = node;
    }
    //This is the first element of list
    else
    {
        nodes->nb++;
        node->id = nodes->nb;
        nodes->first = node;
    }

}

struct Node* getNode(struct Nodes *nodes, int id)
{
    struct Node *node = nodes->first;

    if(nodes->first)
    {
        while(node->next)
        {
            if(node->id == id)
                break;
            node = node->next;
        }
    }

    return node;
}
