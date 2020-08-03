/*
 * adjacencyGraph.h
 *
 *  Created on: 2019年6月5日
 *      Author: Eichi
*/
#ifndef SRC_ADJACENCYGRAPH_H_
#define SRC_ADJACENCYGRAPH_H_

#include <queue>
#include <iostream>

#include "graph.h"
#include "vertexIterator.h"
#include "unweightedEdge.h"
#include "linkedGraph.h"



void delete2dArray(int ** &theArray, int numberOfRows)
{// Delete the two-dimensional array theArray.

   // delete the memory for each row
   for (int i = 0; i < numberOfRows; i++)
      delete [] theArray[i];

   // delete the row pointers
   delete [] theArray;
   theArray = 0;
}

class adjacencyGraph : public graph<int>{
protected:
	int n;           // number of vertices
	int e;           // number of edges
    int **a;           // adjacency array
    int noEdge = 0;        // denotes absent edge
public:
   adjacencyGraph(int numberOfVertices,int theNoEdge);
   adjacencyGraph(linkedGraph &rGraph);
   ~adjacencyGraph();
   int numberOfVertices() const{return n;}
   int numberOfEdges() const {return e;}
   bool existsEdge(int, int) const;
   void insertEdge(edge<int>*);
   void insertEdge(edge<bool> *theEdge);
   void eraseEdge(int, int);
   int degree(int) const{throw std::invalid_argument("no degree");}
   int inDegree(int) const;
   int outDegree(int) const;
   bool directed() const {return true;}
   bool weighted() const {return true;}
   vertexIterator<int>* iterator(int) ;
   void output(std::ostream&) const ;
   void bfs(int v, int reach[], int label);
protected:
   bool make2dArray(int ** &x, int numberOfRows, int numberOfColumns);
   void checkVertex(int theVertex) const;

public:
   class myIterator : public vertexIterator<int>{
   public:
   	myIterator(int* theRow, int theNoEdge, int numberOfVertices);
   	myIterator* iterator(int theVertex);
   	int next();
   	int next(int& theWeight);

   protected:
   	int* row;           // row of adjacency matrix
       int noEdge;         // theRow[i] == noEdge iff no edge to i
       int n;            // number of vertices
       int currentVertex;
       void checkVertex(int theVertex) const;

   };

};



adjacencyGraph::adjacencyGraph(int numberOfVertices,int theNoEdge)
{// Constructor.
   // validate number of vertices
   if (numberOfVertices < 0)
      throw std::out_of_range("number of vertices must be >= 0");
   n = numberOfVertices;
   e = 0;
   noEdge = theNoEdge;
   make2dArray(a, n + 1, n + 1);
   for (int i = 1; i <= n; i++)
      // initialize adjacency matrix
      std::fill(a[i], a[i] + n + 1, noEdge);
}


//
adjacencyGraph::adjacencyGraph(linkedGraph &rGraph)
{
   n = rGraph.numberOfVertices();
   e = rGraph.numberOfEdges();

   make2dArray(a, n + 1, n + 1);
   for(int i = 1;i<=n;i++){
	   for(int j =1;j<=n;j++){
		   if(rGraph.existsEdge(i,j))
			   a[i][j] = 1;
		   else
			   a[i][j] = noEdge;
	   }
   }
}

adjacencyGraph::~adjacencyGraph()
{// Constructor.
   // validate number of vertices
	delete2dArray(a, n + 1);
}


bool adjacencyGraph::make2dArray(int ** &x, int numberOfRows, int numberOfColumns)
{// Create a two dimensional array.

   try {
          // create pointers for the rows
          x = new int * [numberOfRows];

          // get memory for each row
          for (int i = 0; i < numberOfRows; i++)
              x[i] = new int [numberOfColumns];
          return true;
       }
   catch (std::bad_alloc &e) {return false;}
}


bool adjacencyGraph::existsEdge(int i, int j) const
{// Return true iff (i,j) is an edge of the graph.
   if (i < 1 || j < 1 || i > n || j > n || a[i][j] == noEdge)
      return false;
   else
      return true;
}

void adjacencyGraph::eraseEdge(int i, int j)
{// Delete the edge (i,j).
   if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
   {
      a[i][j] = noEdge;
      a[j][i] = noEdge;
      --e;
   }
}



void adjacencyGraph::insertEdge(edge<int> *theEdge)
{// Insert edge theEdge into the digraph; if the edge is already
 // there, update its weight to theEdge.weight().
   int v1 = theEdge->vertex1();
   int v2 = theEdge->vertex2();
   if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
      throw std::out_of_range("invalid");

   if (a[v1][v2] == noEdge)  // new edge
      ++e;
   a[v1][v2] = theEdge->weight();
}


void adjacencyGraph::insertEdge(edge<bool> *theEdge)
{// Insert edge theEdge into the digraph; if the edge is already
 // there, update its weight to theEdge.weight().
   int v1 = theEdge->vertex1();
   int v2 = theEdge->vertex2();
   if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
      throw std::out_of_range("invalid");

   if (a[v1][v2] == noEdge)a[v1][v2] = 1;
   if (a[v2][v1] == noEdge)a[v2][v1] = 1;
      ++e;
}


void adjacencyGraph::checkVertex(int theVertex) const{
	// Verify that i is a valid vertex.
     if (theVertex < 1 || theVertex > n)
        throw std::out_of_range("no vertex");
}


int adjacencyGraph::outDegree(int theVertex) const
 {// Return out-degree of vertex theVertex.
    checkVertex(theVertex);

    // count out edges from vertex theVertex
    int sum = 0;
    for (int j = 1; j <= n; j++)
       if (a[theVertex][j] != noEdge)
          sum++;

    return sum;
 }


int adjacencyGraph::inDegree(int theVertex) const
 {// Return in-degree of vertex theVertex.
    checkVertex(theVertex);

    // count in edges at vertex theVertex
    int sum = 0;
    for (int j = 1; j <= n; j++)
       if (a[j][theVertex] != noEdge)
          sum++;

    return sum;
 }

void adjacencyGraph::output(std::ostream& out) const{
	// Output the adjacency matrix.
     for (int i = 1; i <= n; i++)
     {
        std::copy(a[i] + 1, a[i] + n + 1, std::ostream_iterator<int>(out, "  "));
        out << std::endl;
     }
  }

std::ostream& operator<<(std::ostream& out, const adjacencyGraph & x){
	x.output(out);
	return out;
}


vertexIterator<int>* adjacencyGraph::iterator(int theVertex){
   checkVertex(theVertex);
   return new adjacencyGraph::myIterator(a[theVertex], noEdge, n);
}


void adjacencyGraph::bfs(int v, int reach[], int label)
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
      for (int u = 1; u <= n; u++) //不使用迭代器
         // visit an adjacent vertex of w
         if (a[w][u] != noEdge && reach[u] == 0)
         {// u is an unreached vertex
            q.push(u);
            reach[u] = label; // mark reached
         }
   }
}


adjacencyGraph::myIterator::myIterator(int* theRow, int theNoEdge, int numberOfVertices)
 {
    row = theRow;
    noEdge = theNoEdge;
    n = numberOfVertices;
    currentVertex = 1;
 }


void adjacencyGraph::myIterator::checkVertex(int theVertex) const{
	// Verify that i is a valid vertex.
     if (theVertex < 1 || theVertex > n)
        throw std::out_of_range("no vertex");
}



int adjacencyGraph::myIterator::next()
{// Return next vertex if any. Return 0 if no next vertex.
   // find next adjacent vertex
   for (int j = currentVertex; j <= n; j++)
      if (row[j] != noEdge)
      {
         currentVertex = j + 1;
         return j;
      }
   // no next adjacent vertex
   currentVertex = n + 1;
   return 0;
}

int adjacencyGraph::myIterator::next(int& theWeight)
 {// Return next vertex if any. Return 0 if no next vertex.
  // Set theWeight = edge weight.
    // find next adjacent vertex
    for (int j = currentVertex; j <= n; j++)
       if (row[j] != noEdge)
       {
          currentVertex = j + 1;
          theWeight = row[j];
          return j;
       }
    // no next adjacent vertex
    currentVertex = n + 1;
    return 0;
 }





#endif /* SRC_ADJACENCYGRAPH_H_ */
