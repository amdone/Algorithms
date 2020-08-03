/*
 * graph.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */


#include "linkedDigraph.h"


using std::cout;
using std::endl;
//int main()
//{
//   adjacencyGraph g(4,0);
//
//   g.insertEdge(new unweightedEdge(2, 4));
//   g.insertEdge(new unweightedEdge(1, 3));
//   g.insertEdge(new unweightedEdge(2, 1));
//   g.insertEdge(new unweightedEdge(1, 4));
//   g.insertEdge(new unweightedEdge(4, 2));
//   cout << "The adjacency graph is" << endl;
//   cout << "Number of Vertices = " << g.numberOfVertices() << endl;
//   cout << "Number of Edges = " << g.numberOfEdges() << endl;
//   cout << g << endl;
//
//   g.eraseEdge(2,1);
//   cout << "The graph after deleting (2,1) is" << endl;
//   cout << "Number of Vertices = " << g.numberOfVertices() << endl;
//   cout << "Number of Edges = " << g.numberOfEdges() << endl;
//   cout << g << endl;
//
//   cout<<"converted into an linked graph:"<<endl;
//   linkedGraph lg = linkedGraph(g);
//   cout<<lg<<endl;
//
//}



//
//
//using std::cout;
//using std::endl;
//
//int main(void)
//{
//	linkedWDigraph<int> g(8);
////   cout << "Number of Vertices = " << g.numberOfVertices() << endl;
////   cout << "Number of Edges = " << g.numberOfEdges() << endl;
////   cout << endl;
//
//   g.insertEdge(new weightedEdge<int>(1,2,3));
//   g.insertEdge(new weightedEdge<int>(2,3,6));
//   g.insertEdge(new weightedEdge<int>(3, 4,8));
//   g.insertEdge(new weightedEdge<int>(3, 5,1));
//
////   g.insertEdge(new unweightedEdge(1, 5));
////   g.insertEdge(new unweightedEdge(2, 3));
////   g.insertEdge(new unweightedEdge(3, 4));
////   g.insertEdge(new unweightedEdge(3, 5));
//   g.insertEdge(new weightedEdge<int>(5,6,99));
//   g.insertEdge(new weightedEdge<int>(6, 4,3));
//   g.insertEdge(new weightedEdge<int>(7, 5,1));
//   g.insertEdge(new weightedEdge<int>(7, 8,8));
//   g.insertEdge(new weightedEdge<int>(8, 6,0));
//
//   cout << "The linked graph is" << endl;
//   cout << "Number of Vertices = " << g.numberOfVertices() << endl;
//   cout << "Number of Edges = " << g.numberOfEdges() << endl;
//   cout << g << endl;
//
//   g.eraseEdge(1,2);
//   cout << "The graph after deleting (1,5) is" << endl;
//   cout << "Number of Vertices = " << g.numberOfVertices() << endl;
//   cout << "Number of Edges = " << g.numberOfEdges() << endl;
//   cout << g << endl;
//
////
////   cout << "existsEdge(3,4) = " << g.existsEdge(3,4) << endl;
//////   cout << "inDegree(3) = " << g.inDegree(3) << endl;
//////   cout << "outDegree(1) = " << g.outDegree(1) << endl;
////   cout << "Number of Vertices = " << g.numberOfVertices() << endl;
////   cout << "Number of Edges = " << g.numberOfEdges() << endl;
////   cout << endl;
////
////   // test iterator
////   cout << "Vertices adjacenct to vertex 3" << endl;
////   vertexIterator<bool>* gi = g.iterator(3);
////   int i;
////   while((i = gi->next()) != 0)
////      cout << i << endl;
////   return 0;
//
//}
//
//
int main(){
	linkedDigraph a(8);
	a.insertEdge(new unweightedEdge(1, 3));
	a.insertEdge(new unweightedEdge(3, 4));
	a.insertEdge(new unweightedEdge(4, 5));
	a.insertEdge(new unweightedEdge(6, 5));
	a.insertEdge(new unweightedEdge(4, 7));
	a.insertEdge(new unweightedEdge(7, 6));
	a.insertEdge(new unweightedEdge(1, 7));
	a.insertEdge(new unweightedEdge(2, 7));
	a.insertEdge(new unweightedEdge(2, 8));
	a.insertEdge(new unweightedEdge(8, 6));
	cout<<a;
	int r[8];
	a.topologicalSort(r);
	for(int i=0;i<8;i++)cout<<r[i]<<" ";
	return 0;
}
