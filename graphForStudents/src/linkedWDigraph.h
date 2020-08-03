/*
 * linkedWDigraph.h
 *
 *  Created on: 2019年6月8日
 *      Author: Eichi
 */

#ifndef SRC_LINKEDWDIGRAPH_H_
#define SRC_LINKEDWDIGRAPH_H_

#include <algorithm>
#include <queue>
#include "graph.h"
#include "graphChain.h"
#include "vertexIterator.h"
#include "weightedEdge.h"

template<class T>
class linkedWDigraph : public graph<T>{
   protected:
      int n;                      // number of vertices
      int e;                      // number of edges
      graphChain<std::pair<int,T>> *aList;

   public:
      linkedWDigraph(int numberOfVertices);
      ~linkedWDigraph() {delete [] aList;}
      int numberOfVertices() const {return n;}
      int numberOfEdges() const {return e;}
      bool directed() const {return true;}
      bool weighted() const {return false;}
      bool existsEdge(int i, int j) const;
      int degree(int theVertex) const;
      int outDegree(int theVertex) const;
      int inDegree(int theVertex) const;
      void insertEdge(edge<T> *theEdge);
      void insertEdgeNoCheck(edge<T> *theEdge);
      void eraseEdge(int i, int j);
      void output(std::ostream& out) const;
      void bfs(int v, int reach[], int label);
      int indexOf(int &theIndex);



   protected:
      void checkVertex(int theVertex) const;

//   public:
//      class myIterator : public vertexIterator<T>{
//         public:
//            myIterator(chainNode<T> *theNode) {currentNode = theNode;}
//
//            ~myIterator() {}
//
//            int next()
//            {// Return next vertex if any. Return 0 if no next vertex.
//               // find next adjacent vertex
//               if (currentNode == NULL)
//                  return 0;
//               int nextVertex = currentNode->element;
//               currentNode = currentNode->next;
//               return nextVertex;
//            }
//            int next(bool& theWeight)
//            {// Return next vertex if any. Return 0 if no next vertex.
//             // Set theWeight = edge weight.
//               // find next adjacent vertex
//               if (currentNode == NULL)
//                  return 0;
//               int nextVertex = currentNode->element;
//               currentNode = currentNode->next;
//               theWeight = true;
//               return nextVertex;
//            }
//
//         protected:
//            chainNode<int> *currentNode;
//      };
//      myIterator* iterator(int theVertex){
//          checkVertex(theVertex);
//          return new myIterator(aList[theVertex].getFisrtNode());//firstNode是protected，需要声明为友元，或者调用函数
//       }
};

//std::ostream& operator<<(std::ostream& out, const linkedWdigraph& x);

template<class T>
linkedWDigraph<T>::linkedWDigraph(int numberOfVertices) {
	if (numberOfVertices < 0)
          throw std::out_of_range("number of vertices must be >= 0");
	n = numberOfVertices;
    e = 0;
    aList = new graphChain<std::pair<int,T>> [n + 1];
}

template<class T>
void linkedWDigraph<T>::checkVertex(int theVertex) const{
   if (theVertex < 1 || theVertex > n)
      throw std::out_of_range("no vertex");
}

template<class T>
bool linkedWDigraph<T>::existsEdge(int i, int j) const{

    if (i < 1 || j < 1 || i > n || j > n || aList[i].indexOf(j) == -1)
       return false;
    else
       return true;
 }

template<class T>
int linkedWDigraph<T>::degree(int theVertex) const{
	throw std::invalid_argument("degree() undefined");
}

template<class T>
 int linkedWDigraph<T>::outDegree(int theVertex) const{
    checkVertex(theVertex);
    return aList[theVertex].size();
 }

template<class T>
 int linkedWDigraph<T>::inDegree(int theVertex) const{
    checkVertex(theVertex);
    // count in-edges at vertex theVertex
    int sum = 0;
    for (int j = 1; j <= n; j++)
       if (aList[j].indexOf(theVertex) != -1) ++sum;
     return sum;
 }

template<class T>
 void linkedWDigraph<T>::insertEdge(edge<T> *theEdge){// Insert an edge.
    int v1 = theEdge->vertex1();
    int v2 = theEdge->vertex2();
    if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
       throw std::out_of_range("not a permissible edge");

    if (aList[v1].indexOf(v2) == -1){// new edge
       aList[v1].insert(0, std::pair<int,T>(v2,theEdge->weight()));
       ++e;
    }
 }

template<class T>
 void linkedWDigraph<T>::insertEdgeNoCheck(edge<T> *theEdge){
	 // Insert an edge. No validation checks performed.
    aList[theEdge->vertex1()].insert(0, std::pair<int,T>(theEdge->vertex1(),theEdge->weight()));
    ++e;
 }

template<class T>
void linkedWDigraph<T>::eraseEdge(int i, int j){
    if (i >= 1 && j >= 1 && i <= n && j <= n)
    {
    std::pair<int,T> *v = aList[i].eraseElement(j);
       if (v != NULL)  // edge (i,j) did exist
          --e;
    }
 }

template<class T>
 void linkedWDigraph<T>::output(std::ostream& out) const
 {// Output the adjacency matrix.
    for (int i = 1; i <= n; i++)
       out << i<<"==>"<<aList[i];
 }

template<class T>
 void linkedWDigraph<T>::bfs(int v, int reach[], int label)
 {// Breadth-first search. reach[i] is set to label for
  // all vertices reachable from vertex v.
    std::queue<int> q;
    reach[v] = label;
    q.push(v);
    while (!q.empty())
    {
       // remove a labeled vertex from the queue
       int w = q.front();
       q.pop();
       // mark all unreached vertices adjacent from w
       for (chainNode<int>* u = aList[w].firstNode;//不使用迭代器
                            u != NULL; u = u->next)
          // visit an adjacent vertex of w
          if (reach[u->element] == 0)
          {// u->element is an unreached vertex
             q.push(u->element);
             reach[u->element] = label; // mark reached
          }
    }
 }

template<class T>
std::ostream& operator<<(std::ostream& out, const linkedWDigraph<T>& x){
	 x.output(out);
	 return out;
 }

template<class T>
int linkedWDigraph<T>::indexOf(int &theIndex){
	  chainNode<T>* currentNode = this->aList[theIndex];
	   int index = 0;  // index of currentNode
	   while (currentNode != NULL && currentNode->element.first != theIndex){
	     currentNode = currentNode->next;
	      index++;
	   }
	  if (currentNode == NULL)
	      return -1;
	   else
	      return index;
}




#endif /* SRC_LINKEDWDIGRAPH_H_ */
