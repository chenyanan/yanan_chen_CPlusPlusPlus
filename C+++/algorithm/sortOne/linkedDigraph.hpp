////
////  linkedDigraph.hpp
////  C+++
////
////  Created by chenyanan on 2017/1/25.
////  Copyright © 2017年 chenyanan. All rights reserved.
////
//
//#ifndef linkedDigraph_hpp
//#define linkedDigraph_hpp
//
//#include "graph.hpp"
//#include "graphChain.hpp"
//#include "edge.hpp"
//#include "vertexIterator.hpp"
//#include "myException.hpp"
//#include "queue.hpp"
//
//class linkedDigraph : public graph<bool>
//{
//protected:
//    int n;
//    int e;
//    graphChain<int> *aList;
//    
//public:
//    linkedDigraph(int numberOfVertices = 0)
//    {
//        if (numberOfVertices < 0)
//            throw illegalParameterValue("number of vertices must be >= 0");
//        n = numberOfVertices;
//        e = 0;
//        aList = new graphChain<int> [n + 1];
//    }
//    
//    ~linkedDigraph() {delete [] aList;}
//    
//    int numberOfVertices() const {return n;}
//    
//    int numberOfEdges() const {return e;}
//    
//    bool directed() const {return true;}
//    
//    bool weighted() const {return false;}
//    
//    bool existsEdge(int i, int j) const
//    {
//        if (i < 1 || j < 1 || i > n || j > n
//            || aList[i].indexOf(j) == -1)
//            return false;
//        else
//            return true;
//    }
//    
//    void insertEdge(edge<bool> *theEdge)
//    {
//        int v1 = theEdge->vertex1();
//        int v2 = theEdge->vertex2();
//        if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
//        {
//            std::string s = "(" + std::string(1,v1) + "," + std::string(1,v2) + ") is not a permissible edge";
//            throw illegalParameterValue(s);
//        }
//        
//        if (aList[v1].indexOf(v2) == -1)
//        {
//            aList[v1].insert(0, v2);
//            e++;
//        }
//    }
//    
//    void insertEdgeNoCheck(edge<bool> *theEdge)
//    {
//        aList[theEdge->vertex1()].insert(0, theEdge->vertex2());
//        e++;
//    }
//    
//    
//    void eraseEdge(int i, int j)
//    {
//        if (i >= 1 && j >= 1 && i <= n && j <= n)
//        {
//            int *v = aList[i].eraseElement(j);
//            if (v != NULL)
//                e--;
//        }
//    }
//    
//    void checkVertex(int theVertex) const
//    {
//        if (theVertex < 1 || theVertex > n)
//        {
//            std::string s = "no vertex" + std::string(1,theVertex);
//            throw illegalParameterValue(s);
//        }
//    }
//    
//    int degree(int theVertex) const
//    {throw undefinedMethod("degree() undefined");}
//    
//    int outDegree(int theVertex) const
//    {
//        checkVertex(theVertex);
//        return aList[theVertex].size();
//    }
//    
//    int inDegree(int theVertex) const
//    {
//        checkVertex(theVertex);
//        
//        int sum = 0;
//        for (int j = 1; j <= n; j++)
//            if (aList[j].indexOf(theVertex) != -1)
//                sum++;
//        
//        return sum;
//    }
//    
//    class iterator : public vertexIterator<bool>
//    {
//    public:
//        iterator(chainNode<int> *theNode) {currentNode = theNode;}
//        
//        ~iterator() {}
//        
//        int next()
//        {
//            if (currentNode == NULL)
//                return 0;
//            int nextVertex = currentNode->element;
//            currentNode = currentNode->next;
//            return nextVertex;
//        }
//        
//        int next(bool& theWeight)
//        {
//            if (currentNode == NULL)
//                return 0;
//            int nextVertex = currentNode->element;
//            currentNode = currentNode->next;
//            theWeight = true;
//            return nextVertex;
//        }
//        
//    protected:
//        chainNode<int> *currentNode;
//    };
//    
//    iterator* iterator(int theVertex)
//    {
//        checkVertex(theVertex);
//        return new class iterator(aList[theVertex].firstNode);
//    }
//    
//    void bfs(int v, int reach[], int label)
//    {
//        arrayQueue<int> q(10);
//        reach[v] = label;
//        q.push(v);
//        while (!q.empty())
//        {
//            int w = q.front();
//            q.pop();
//            
//            for (chainNode<int>* u = aList[w].firstNode;
//                 u != NULL; u = u->next)
//                if (reach[u->element] == 0)
//                {
//                    q.push(u->element);
//                    reach[u->element] = label;
//                }
//        }
//    }
//};
//
//#endif /* linkedDigraph_hpp */
