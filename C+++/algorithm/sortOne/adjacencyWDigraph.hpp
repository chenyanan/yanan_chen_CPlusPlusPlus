//
//  adjacencyWDigraph.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/24.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef adjacencyWDigraph_hpp
#define adjacencyWDigraph_hpp

#include "graph.hpp"
#include "edge.hpp"
#include "vertexIterator.hpp"
#include "make2dArrayNoCatch.hpp"
#include "delete2dArray.hpp"
#include "myException.hpp"
#include "queue.hpp"
#include "graphChain.hpp"
#include "minHeap.hpp"

template<typename T>
class adjacencyWDigraph : public graph<T>
{
protected:
    int n;
    int e;
    T** a;
    T noEdge;
    
public:
    adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0)
    {
        if (numberOfVertices < 0)
            throw illegalParameterValue("number of vertices must be >= 0");
        n = numberOfVertices;
        e = 0;
        noEdge = theNoEdge;
        make2dArray(a, n + 1, n + 1);
        for (int i = 1; i <= n; ++i)
            std::fill(a[i], a[i] + n + 1, noEdge);
    }
    
    ~adjacencyWDigraph() {delete2dArray(a, n + 1);}
    
    int numberOfVertices() const {return n;}
    
    int numberOfEdges() const {return e;}
    
    bool directed() const {return true;}
    
    bool weighted() const {return true;}
    
    bool existedEdge(int i, int j) const
    {
        if (i < 1 || j < 1 || i > n || j > n || a[i][j] == noEdge)
            return false;
        else
            return true;
    }
    
    void insertEdge(edge<T>* theEdge)
    {
        int v1 = theEdge->vertex1();
        int v2 = theEdge->vertex2();
        if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
        {
            std::string s = "(" + std::string(1,v1) + "," + std::string(1,v2) + ") is not a permissible edge";
            throw illegalParameterValue(s);
        }
        
        if (a[v1][v2] == noEdge)
            e++;
        a[v1][v2] = theEdge->weight();
    }
    
    void eraseEdge(int i, int j)
    {
        if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
        {
            a[i][j] = noEdge;
            e--;
        }
    }
    
    void checkVertex(int theVertex) const
    {
        if (theVertex < 1 || theVertex > n)
        {
            std::string s = "no vertex " + std::string(1, theVertex);
            throw illegalParameterValue(s);
        }
    }
    
    int degree(int theVertex) const {throw undefinedMethod("degree() undefined");}
    
    int outDegree(int theVertex) const
    {
        checkVertex(theVertex);
        
        int sum = 0;
        for (int j = 1; j <= n; ++j)
            if (a[theVertex][j] != noEdge)
                sum++;
        
        return sum;
    }
    
    int inDegree(int theVertex) const
    {
        checkVertex(theVertex);
        
        int sum = 0;
        for (int j = 1; j <= n; ++j)
            if (a[j][theVertex] != noEdge)
                sum++;
        
        return sum;
    }
    
    class iterator : public vertexIterator<T>
    {
    public:
        iterator(T* theRow, T theNoEdge, int numberOfVertices)
        {
            row = theRow;
            noEdge = theNoEdge;
            n = numberOfVertices;
            currentVertex = 1;
        }
        
        ~iterator() {}
        
        int next()
        {
            for (int j = currentVertex; j <= n; ++j)
                if (row[j] != noEdge)
                {
                    currentVertex = j + 1;
                    return j;
                }
            currentVertex = n + 1;
            return 0;
        }
        
        int next(T& theWeight)
        {
            for (int j = currentVertex; j <= n; ++j)
            {
                currentVertex = j + 1;
                theWeight = row[j];
                return j;
            }
            currentVertex = n + 1;
            return 0;
        }
        
    protected:
        T* row;
        T noEdge;
        int n;
        int currentVertex;
    };
    
    iterator* iterator(int theVertex)
    {
        checkVertex(theVertex);
        return new class iterator(a[theVertex], noEdge, n);
    }
    
    void bfs(int v, int reach[], int label)
    {
        arrayQueue<int> q(10);
        reach[v] = label;
        q.push(v);
        while (!q.empty())
        {
            int w = q.front();
            q.pop();
            
            for (int u = 1; u <= n; ++u)
                if (a[w][u] != noEdge && reach[u] == 0)
                {
                    q.push(u);
                    reach[u] = label;
                }
        }
    }
    
    void shorttestPaths(int sourceVertex, T* distanceFromSource, int* predecessor)
    {
        if (sourceVertex < 1 || sourceVertex > n)
            throw illegalParameterValue("Invalid source vertex");
        
        if (!weighted())
            throw undefinedMethod("adjacencyWDigraph::shortestPaths() not defined for unweighted graphs");
        
        graphChain<int> newReachableVertices;
        
        for (int i = 1; i <= n; ++i)
        {
            distanceFromSource[i] = a[sourceVertex][i];
            if (distanceFromSource[i] == noEdge)
                predecessor[i] = -1;
            else
            {
                predecessor[i] = sourceVertex;
                newReachableVertices.insert(0,i);
            }
        }
        distanceFromSource[sourceVertex] = 0;
        predecessor[sourceVertex] = 0;
        
        while(!newReachableVertices.empty())
        {
            chain<int>::iterator iNewReachableVertices = newReachableVertices.begin();
            chain<int>::iterator theEnd = newReachableVertices.end();
            int v = *iNewReachableVertices;
            iNewReachableVertices++;
            while (iNewReachableVertices != theEnd)
            {
                int w = *iNewReachableVertices;
                iNewReachableVertices++;
                if (distanceFromSource[w] < distanceFromSource[v])
                    v = w;
            }
            
            newReachableVertices.eraseElement(v);
            for (int j = 1; j <= n; ++j)
            {
                if (a[v][j] != noEdge && (predecessor[j] == -1 || distanceFromSource[j] > distanceFromSource[v] + a[v][j]))
                {
                    distanceFromSource[j] = distanceFromSource[v] + a[v][j];
                    if (predecessor[j] == -1)
                        newReachableVertices.insert(0,j);
                    predecessor[j] = v;
                }
            }
        }
    }
    
    void allPairs(T** c, int** kay)
    {
        if (!weighted())
            throw undefinedMethod("adjacencyWDigraph::allpairs() not defined for unweighted graphs");
        
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
                c[i][j] = a[i][j];
                kay[i][j] = 0;
            }
        for (int i = 1; i <= n; ++i)
            c[i][i] = 0;
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    if (c[i][k] != noEdge && c[k][j] != noEdge && (c[i][j] == noEdge || c[i][j] > c[i][k] + c[k][j]))
                    {
                        c[i][j] = c[i][k] + c[k][j];
                        kay[i][j] = k;
                    }
    }
    
    T btSalesperson(int* bestTour)
    {
        if (!weighted())
            throw undefinedMethod("adjacencyWDigraph::btSalesperson() not defined for unweighted");
        
        partialTour = new int[n + 1];
        for (int i = 1; i <= n; ++i)
            partialTour[i] = i;
        
        costOfBestTourSoFar = noEdge;
        bestTourSoFar = bestTour;
        costOfPartialTour = 0;
        
        rTSP(2);
        
        return costOfBestTourSoFar;
    }
    
    struct heapNode
    {
        T lowerCost;
        T costOfPartialTour;
        T minAdditionalCost;
        int sizeOfPartialTour;
        int* partialTour;
        
        heapNode() {}
        
        heapNode(T lC, T cOPT, T mAC, int sOPT, int* pT)
        {
            lowerCost = lC;
            costOfPartialTour = cOPT;
            minAdditionalCost = mAC;
            sizeOfPartialTour = sOPT;
            partialTour = pT;
        }
        
        operator int() {return lowerCost;}
        
        bool operator>(const heapNode right) {return lowerCost > right.lowerCost;}
    };
    
    T leastCostBBSalesperson(int* bestTour)
    {
        if (!weighted())
            throw undefinedMethod("adjacencyWDigraph::leastCostBBSalesperson() not definedf for unweighted graphs");
        
        minHeap<heapNode> liveNodeMinHeap;
        
        T* costOfMinOutEdge = new T[n + 1];
        T sumOfMinCostOutEdges = 0;
        for (int i = 1; i <= n; ++i)
        {
            T minCost = noEdge;
            for (int j = 1; j <= n; ++j)
                if (a[i][j] != noEdge && (minCost == noEdge || minCost > a[i][j]))
                    minCost = a[i][j];
            
            if (minCost == noEdge) return noEdge;
            costOfMinOutEdge[i] = minCost;
            sumOfMinCostOutEdges += minCost;
        }
        
        heapNode eNode(0,0,sumOfMinCostOutEdges,0,new int[n]);
        for (int i = 0; i < n; ++i)
            eNode.partialTour[i] = i + 1;
        T costOfBestTourSoFar = noEdge;
        int* partialTour = eNode.partialTour;
        
        while (eNode.sizeOfPartialTour < n - 1)
        {
            partialTour = eNode.partialTour;
            if (eNode.sizeOfPartialTour == n - 1)
            {
                if (a[partialTour[n - 2]][partialTour[n - 1]] != noEdge && a[partialTour[n - 1]][1] != noEdge && (costOfBestTourSoFar == noEdge || eNode.costOfPartialTour + a[partialTour[n - 2]][partialTour[n - 1]] + a[partialTour[n - 1]][1]< costOfBestTourSoFar))
                {
                    costOfBestTourSoFar = eNode.costOfPartialTour
                    + a[partialTour[n - 2]][partialTour[n - 1]]
                    + a[partialTour[n - 1]][1];
                    eNode.costOfPartialTour = costOfBestTourSoFar;
                    eNode.lowerCost = costOfBestTourSoFar;
                    eNode.sizeOfPartialTour++;
                    liveNodeMinHeap.push(eNode);
                }
            }
            else
            {
                for (int i = eNode.sizeOfPartialTour + 1; i < n; i++)
                    if (a[partialTour[eNode.sizeOfPartialTour]]
                        [partialTour[i]] != noEdge)
                    {
                        T costOfPartialTour = eNode.costOfPartialTour
                        + a[partialTour[eNode.sizeOfPartialTour]]
                        [partialTour[i]];
                        T minAdditionalCost = eNode.minAdditionalCost
                        -  costOfMinOutEdge[partialTour
                                            [eNode.sizeOfPartialTour]];
                        T leastCostPossible = costOfPartialTour
                        + minAdditionalCost;
                        if (costOfBestTourSoFar == noEdge ||
                            leastCostPossible < costOfBestTourSoFar)
                        {
                            heapNode hNode(leastCostPossible,
                                           costOfPartialTour,
                                           minAdditionalCost,
                                           eNode.sizeOfPartialTour + 1,
                                           new int [n]);
                            for (int j = 0; j < n; j++)
                                hNode.partialTour[j] = partialTour[j];
                            hNode.partialTour[eNode.sizeOfPartialTour + 1] =
                            partialTour[i];
                            hNode.partialTour[i] =
                            partialTour[eNode.sizeOfPartialTour + 1];
                            liveNodeMinHeap.push(hNode);
                        }
                    }
            }
            
            delete [] eNode.partialTour;
            if (liveNodeMinHeap.empty()) break;
            eNode = liveNodeMinHeap.top();
            liveNodeMinHeap.pop();
        }
        
        if (costOfBestTourSoFar == noEdge)
            return NULL;
        
        for (int i = 0; i < n; i++)
            bestTour[i + 1] = partialTour[i];
        
        return costOfBestTourSoFar;
    }
    
protected:
    void rTSP(int currentLevel)
    {
        using std::swap;
        if (currentLevel == n)
        {
            if (a[partialTour[n - 1]][partialTour[n]] != noEdge &&
                a[partialTour[n]][1] != noEdge &&
                (costOfBestTourSoFar == noEdge ||
                 costOfPartialTour + a[partialTour[n - 1]][partialTour[n]]
                 + a[partialTour[n]][1] < costOfBestTourSoFar))
            {
                copy(partialTour + 1, partialTour + n + 1, bestTourSoFar + 1);
                costOfBestTourSoFar = costOfPartialTour
                + a[partialTour[n - 1]][partialTour[n]]
                + a[partialTour[n]][1];
            }
        }
        else
        {
            for (int j = currentLevel; j <= n; j++)
                if (a[partialTour[currentLevel - 1]][partialTour[j]] != noEdge
                    && (costOfBestTourSoFar == noEdge ||
                        costOfPartialTour +
                        a[partialTour[currentLevel - 1]][partialTour[j]]
                        < costOfBestTourSoFar))
                {
                    swap(partialTour[currentLevel], partialTour[j]);
                    costOfPartialTour += a[partialTour[currentLevel - 1]]
                    [partialTour[currentLevel]];
                    rTSP(currentLevel + 1);
                    costOfPartialTour -= a[partialTour[currentLevel - 1]]
                    [partialTour[currentLevel]];
                    swap(partialTour[currentLevel], partialTour[j]);
                }
        }
    }
    
    static int *partialTour;
    static int *bestTourSoFar;
    static T costOfBestTourSoFar;
    static T costOfPartialTour;
};

#endif /* adjacencyWDigraph_hpp */
