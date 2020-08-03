/*
 * linkedGraph.h
 *
 *  Created on: 2019年6月4日
 *      Author: Eichi
 */

#ifndef SRC_LINKEDGRAPH_H_
#define SRC_LINKEDGRAPH_H_
#include <algorithm>
#include <queue>
#include "graph.h"
#include "graphChain"
#include "vertexIterator.h"
//#include "adjacencyGraph.h"

//class adjacencyGraph;

class linkedGraph : public graph<bool>{
protected:
	int n;
	int e;
	graphChain<int> *aList;

public:
	linkedGraph(int numberOfVertices);
	//linkedGraph(adjacencyGraph &rGraph);
	 ~linkedGraph() {delete [] aList;}
	 int numberOfVertices() const {return n;}
	 int numberOfEdges() const {return e;}
	 bool existsEdge(int i, int j) const;
	 void insertEdge(edge<bool> *theEdge);
	 void insertEdgeNoCheck(edge<bool> *theEdge);
	 void eraseEdge(int i, int j);
	 bool directed() const {return true;}
	 bool weighted() const {return false;}
	 int degree(int theVertex) const{return 0;}
	 int outDegree(int theVertex) const{return 0;}
	 int inDegree(int theVertex) const{return 0;}
	 void output(std::ostream& out) const;

protected:
   void checkVertex(int theVertex) const;

public:
   class myIterator : public vertexIterator<bool>{
      public:
         myIterator(chainNode<int> *theNode) {currentNode = theNode;}

         ~myIterator() {}

         int next()
         {// Return next vertex if any. Return 0 if no next vertex.
            // find next adjacent vertex
            if (currentNode == NULL)
               return 0;
            int nextVertex = currentNode->element;
            currentNode = currentNode->next;
            return nextVertex;
         }
         int next(bool& theWeight)
         {// Return next vertex if any. Return 0 if no next vertex.
          // Set theWeight = edge weight.
            // find next adjacent vertex
            if (currentNode == NULL)
               return 0;
            int nextVertex = currentNode->element;
            currentNode = currentNode->next;
            theWeight = true;
            return nextVertex;
         }

      protected:
         chainNode<int> *currentNode;
   };
   myIterator* iterator(int theVertex){
       checkVertex(theVertex);
       return new myIterator(aList[theVertex].getFisrtNode());//firstNode是protected，需要声明为友元，或者调用函数
    }


};

linkedGraph::linkedGraph(int numberOfVertices) {
	if (numberOfVertices < 0)
          throw std::out_of_range("number of vertices must be >= 0");
	n = numberOfVertices;
    e = 0;
    aList = new graphChain<int> [n + 1];//不使用第0个元素
}

//linkedGraph::linkedGraph(adjacencyGraph &rGraph) {
//	n = rGraph.numberOfVertices();
//    e = rGraph.numberOfEdges();
//    aList = new graphChain<int> [n + 1];//不使用第0个元素
//    for(int i = 1;i<=n;i++){
//    	for(int j=1;j<=n;j++){
//    		if(rGraph.existsEdge(i,j))
//    			aList[i].insert(0,j);
//    	}
//    }
//}

void linkedGraph::checkVertex(int theVertex) const{
   if (theVertex < 1 || theVertex > n)
      throw std::out_of_range("no vertex");
}

bool linkedGraph::existsEdge(int i, int j) const{
    if (i < 1 || j < 1 || i > n || j > n || aList[i].indexOf(j) == -1)
       return false;
    else
       return true;
 }

void linkedGraph::insertEdge(edge<bool> *theEdge){// Insert an edge.
   int v1 = theEdge->vertex1();
   int v2 = theEdge->vertex2();
   if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
      throw std::out_of_range("not a permissible edge");

   if(aList[v1].indexOf(v2) == -1)aList[v1].insert(0, v2);
   if(aList[v2].indexOf(v1) == -1)aList[v2].insert(0,v1);
   ++e;
}
void linkedGraph::insertEdgeNoCheck(edge<bool> *theEdge){
	 // Insert an edge. No validation checks performed.
   aList[theEdge->vertex1()].insert(0, theEdge->vertex2());
   ++e;
}
void linkedGraph::eraseEdge(int i, int j){
   if (i >= 1 && j >= 1 && i <= n && j <= n)
   {
      int *v = aList[i].eraseElement(j);
      aList[j].eraseElement(i);
      if (v != NULL)  // edge (i,j) did exist
         --e;
   }
}
void linkedGraph::output(std::ostream& out) const
{// Output the adjacency matrix.
   for (int i = 1; i <= n; i++)
      out << i<<"==>"<<aList[i];
}


std::ostream& operator<<(std::ostream& out, const linkedGraph& x){
	 x.output(out);
	 return out;
}





#endif /* SRC_LINKEDGRAPH_H_ */
