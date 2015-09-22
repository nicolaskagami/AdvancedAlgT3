//Author: Nicolas Silveira Kagami
//Slightly different than T1's 
//Adding findEdge and Reflexive edges with cost (which means capacity now) 0
#include "FSgraph.h"


FSgraph::FSgraph(unsigned vertNum, unsigned edgeNum)
{
    numEdges = edgeNum;
    numVerts = vertNum;
    currentEdge = 0;
    currentVert = 0;
    edges = (EDGE*) malloc(sizeof(EDGE)*edgeNum);
    vertices = (VERT*) malloc(sizeof(VERT)*vertNum);
}
FSgraph::FSgraph(std::istream& in)
{
    std::string line="", dummy;
    unsigned n,m;

    while (line.substr(0,5) != "p max")
    {
        getline(in,line);
    }
    std::stringstream linestr;
    linestr.str(line);
    linestr >> dummy >> dummy >> n >> m;

    //Init
    numVerts = n;
    numEdges = 2*m;
    currentEdge = 0;
    currentVert = 0;
    edges = (EDGE*) malloc(sizeof(EDGE)*numEdges);
    vertices = (VERT*) malloc(sizeof(VERT)*numVerts);
    unsigned i =0;
    for(i=0;i<numVerts;i++)
    {
        vertices[i].edgeNum=0;
        vertices[i].index=0;
    }
    source=0;
    target=0;

    std::stringstream buffer;
    buffer << in.rdbuf();
    i=0;
    while (i<m)
    {
        if(!std::getline(buffer, line))
        {
            printf("Parsing Error\n");
            exit(1);
        }
        if (line.substr(0,2) == "a ") 
        {
            std::stringstream arc(line);
            unsigned u,v,w;
            char ac;
            arc >> ac >> u >> v >> w;
            preallocate(u,v);
            preallocate(v,u);//Added for T3 Advanced algs
            i++;
        }
        if (line.substr(0,2) == "n ") 
        {
            std::stringstream arc(line);
            unsigned u;
            char ac,n;
            arc >> ac >> u >> n;
            if(n == 's')
                source = u;
            if(n == 't')
                target = u;
        }
    }
    indexify();
    buffer.seekg(0);
    i=0;
    while (i<m)
    {
        if(!std::getline(buffer, line))
        {
            printf("Parsing Error\n");
            exit(1);
        }
        if (line.substr(0,2) == "a ") 
        {
            std::stringstream arc(line);
            unsigned u,v,w;
            char ac;
            arc >> ac >> u >> v >> w;
            proposeEdge(u,v,w);
            proposeEdge(v,u,0);
            i++;
        }
    }

}
FSgraph::~FSgraph()
{
    free(edges);
    free(vertices);
}
void FSgraph::preallocate(unsigned vert, unsigned tgt)
{
    if(vert>numVerts)
    {
        printf("Invalid vertex\n");
        exit(1);
    }
    vertices[vert-1].edgeNum++;
}
void FSgraph::indexify()
{
    for(unsigned i = 0; i<(numVerts-1);i++)
    {
        vertices[i+1].index = vertices[i].index + vertices[i].edgeNum;
        vertices[i].edgeNum =0;
    }
    vertices[numVerts-1].edgeNum=0;
}
void FSgraph::addEdge(unsigned vert,unsigned tgt,unsigned wht)
{
    //printf("Adding Edge %d %d %d\n",vert, tgt, wht);
    if(vert>numVerts)
    {
        printf("Invalid vertex\n");
        exit(1);
    }
    unsigned ind = vertices[vert-1].index + vertices[vert-1].edgeNum;
    if(ind>numEdges)
    {
        printf("Invalid Edge\n");
        exit(1);
    }
    edges[ind].target = tgt;    
    edges[ind].weight = wht;
    edges[ind].residual = wht;

    vertices[vert-1].edgeNum++;
}
void FSgraph::proposeEdge(unsigned vert, unsigned tgt,unsigned wht)
{
   unsigned i,j;
   for(i=vertices[vert-1].index,j=0;j<vertices[vert-1].edgeNum;j++)
   {
        if(edges[i+j].target == tgt)
        {
            //It already exists, let the bigger prevail
            if(wht>edges[i+j].weight) 
            {
                edges[i+j].weight = wht;
                edges[i+j].residual = wht;
            }
            return;
        }
   }
   addEdge(vert,tgt,wht);
}
unsigned FSgraph::findEdge(unsigned u, unsigned v)
{
   unsigned i,j;
   for(i=vertices[u-1].index,j=0;j<vertices[u-1].edgeNum;j++)
   {
        if(edges[i+j].target == v)
            return i+j;
   }
   return 0;
}
void FSgraph::print()
{
    printf("Forward Star Graph\n");
    printf("Vertices: %d\n",numVerts);
    printf("Edges: %d\n",numEdges);
    for(unsigned i = 0;i<numVerts;i++)
    {
        printf("Vert %d",i+1);
        for(unsigned b = vertices[i].index,j=0;j<vertices[i].edgeNum;j++)
        {
            printf("\t %d %d/%d",edges[b+j].target,edges[b+j].residual,edges[b+j].weight);
        }
        printf("\n");
    }
}
