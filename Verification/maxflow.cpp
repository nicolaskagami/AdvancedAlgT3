/**
 * \file maxflow.cpp
 *   \author Marcus Ritt <mrpritt@inf.ufrgs.br>
 *   \version $Id: emacs 2872 2009-01-31 01:46:50Z ritt $
 *   \date Time-stamp: <2009-03-23 17:52:25 ritt>
 *
 * Read a maximum flow problem in DIMACS format and output the maximum flow.
 *
 */
#include <iostream>
#include <cstring>
using namespace std;
 
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/read_dimacs.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
using namespace boost;
 
// graph element descriptors
typedef adjacency_list_traits<vecS,vecS,directedS>::vertex_descriptor DiNode;
typedef adjacency_list_traits<vecS,vecS,directedS>::edge_descriptor Edge;
 
typedef unsigned Capacity;
struct VertexInformation {};
struct EdgeInformation {
  Capacity edge_capacity;
  Capacity edge_residual_capacity;
  Edge reverse_edge;
};
 
typedef adjacency_list<vecS,vecS,directedS,VertexInformation,EdgeInformation> DiGraph;
 
 
int main(int argc, char *argv[]) {
  // (0) read graph
 
  DiGraph g;
  DiNode s,t;
 
  read_dimacs_max_flow(g,
                       get(&EdgeInformation::edge_capacity,g),
                       get(&EdgeInformation::reverse_edge,g),
                       s, t);
 
  // (1) determine maximum flow
  cout << edmonds_karp_max_flow(g, s, t,
                                capacity_map(get(&EdgeInformation::edge_capacity,g)).
                                residual_capacity_map(get(&EdgeInformation::edge_residual_capacity,g)).
                                reverse_edge_map(get(&EdgeInformation::reverse_edge,g))) << endl;
}
