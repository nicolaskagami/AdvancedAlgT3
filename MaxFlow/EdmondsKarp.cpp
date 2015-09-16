
#include "EdmondsKarp.h"

EdmondsKarp::EdmondsKarp(FSgraph * g)
{
    graph = g;
    src = g->source;
    tgt = g->target;
    parent = (unsigned *) malloc(g->numVerts);

    //Find path
    unsigned u,p;
    flow = 0;
    while(findPath())
    {
        unsigned pathFlow = getResidual(parent[tgt-1],tgt);
        for(p=tgt;p!=src;p=parent[p-1])
        {
            u = parent[p-1];
            if(getResidual(u,p)<pathFlow)
                pathFlow=getResidual(u,p);
        } 
        for(p=tgt;p!=src;p=parent[p-1])
        {
            u = parent[p-1];
            subResidual(u,p,pathFlow);
            addResidual(p,u,pathFlow);
        }
        flow+=pathFlow;
    }
}
unsigned EdmondsKarp::getResidual(unsigned u, unsigned v)
{ 
    unsigned i = graph->findEdge(u,v); 
    if(graph->edges[i].target == v)    
    {
        return graph->edges[i].residual;
    }
}
void EdmondsKarp::subResidual(unsigned u, unsigned v,unsigned subtraction)
{ 
    unsigned i = graph->findEdge(u,v); 
    if(graph->edges[i].target == v)    
    {
         graph->edges[i].residual-=subtraction;
    }
}
void EdmondsKarp::addResidual(unsigned u, unsigned v,unsigned addition)
{ 
    unsigned i = graph->findEdge(u,v); 
    if(graph->edges[i].target == v)    
    {
         graph->edges[i].residual+=addition;
    }
}
void EdmondsKarp::printPath()
{
    printf("Path:");
    for(unsigned p=tgt;p!=src;p=parent[p-1])
    {
        printf("%d,",p);
    }
    printf("\n");
}
bool EdmondsKarp::findPath()
{
    NHeap<unsigned> nh;
    nh.insert(src,0);

    bool * visited;
    visited = (bool *) calloc(graph->numVerts,sizeof(bool));
    unsigned * distances;
    distances = (unsigned *) calloc(graph->numVerts,sizeof(unsigned));
    distances[src-1]= 0;

    while(nh.occupation>0)
    {
        unsigned p = nh.getMin();
        unsigned value = nh.getMinValue();
        nh.deleteMin();
        visited[p-1] = true;
        if(p == tgt) 
        {
            return true;
        }
        for(unsigned b=graph->vertices[p-1].index,i=0;i<graph->vertices[p-1].edgeNum;i++)
        {
            unsigned neighbor = graph->edges[b+i].target;
            unsigned wht = graph->edges[b+i].residual;
            if(wht>0)
            {
                if(visited[neighbor-1])
                {
                    if((value+wht)<(distances[neighbor-1]))
                    {
                        visited[neighbor-1] = true;
                        distances[neighbor-1] = value+wht; 
                        parent[neighbor-1] = p;
                        nh.update(neighbor,value+wht);
                    }
                }
                else
                {
                    visited[neighbor-1] = true;
                    distances[neighbor-1] = value+wht; 
                    parent[neighbor-1] = p;
                    nh.insert(neighbor,value+wht);
                }
            }
        }
    }
    return false;
}
EdmondsKarp::~EdmondsKarp()
{
    free(parent);
}
int main(int argc, char ** argv)
{
    FSgraph gr(std::cin);
    EdmondsKarp EK(&gr);
    std::cout << EK.flow << std::endl;
    return 0;
}
