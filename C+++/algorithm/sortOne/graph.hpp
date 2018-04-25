//
//  graph.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/23.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include "edge.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "myException.hpp"
#include "arrayList.hpp"
#include "binNode.hpp"
#include "minHeap.hpp"
#include "fastUnionFind.hpp"
#include "vertexIterator.hpp"

template<typename T>
class graph
{
public:
    virtual ~graph() {}
    virtual int numberOfVertices() const = 0;
    virtual int numberOfEdges() const = 0;
    virtual bool existsEdge(int,int) const = 0;
    virtual void insertEdge(edge<T>*) = 0;
    virtual void eraseEdge(int,int) = 0;
    virtual int degree(int) const = 0;
    virtual int outDegree(int) const = 0;
    virtual bool directed() const = 0;
    virtual bool weighted() const = 0;
    virtual vertexIterator<T>* iterator(int) = 0;
    
    virtual void bfs(int v, int reach[], int label)
    {
        arrayQueue<int> q(10);
        reach[v] = label;
        q.push(v);
        while (!q.empty())
        {
            int w = q.front();
            q.pop();
            
            vertexIterator<T>* iw = iterator(w);
            int u;
            while ((u = iw->next()) != 0)
                if (reach[u] == 0)
                {
                    q.push(u);
                    reach[u] = label;
                }
            delete iw;
        }
    }
    
    void dfs(int v, int reach[], int label)
    {
        graph<T>::reach = reach;
        graph<T>::label = label;
        rDfs(v);
    }
    
    int* findPath(int theSource, int theDestination)
    {
        int n = numberOfVertices();
        path = new int [n + 1];
        path[1] = theSource;
        length = 1;
        destination = theDestination;
        reach = new int[n + 1];
        for (int i = 1; i <= n; ++i)
            reach[i] = 0;
        
        if (theSource == theDestination || rFindPath(theSource))
            path[0] = length - 1;
        else
        {
            delete[] path;
            path = NULL;
        }
        
        delete[] reach;
        return path;
    }
    
    bool connected()
    {
        if (directed())
            throw undefinedMethod("graph::connected() not defined for directed graphs");
        
        int n = numberOfVertices();
        
        reach = new int[n + 1];
        
        dfs(1, reach, 1);
        
        for (int i = 1; i <= n; ++i)
            if (reach[i] == 0)
                return false;
        return true;
    }
    
    int labelComponents(int c[])
    {
        if (directed())
            throw undefinedMethod("graph::labelComponents() not defined for directed graphs");
        
        int n = numberOfVertices();
        
        for (int i = 1; i <= n; ++i)
            c[i] = 0;
        
        label = 0;
        
        for (int i = 1; i <= n; ++i)
            if (c[i] == 0)
            {
                label++;
                bfs(i, c, label);
            }
        
        return label;
    }
    
    bool topologicalOrder(int *theOrder) {
        if (!directed())
            throw undefinedMethod("graph::topologicalOrder() not defined for undirected graphs");
        
        int n = numberOfVertices();
        
        int* inDegree = new int[n + 1];
        std::fill(inDegree + 1, inDegree + n + 1, 0);
        for (int i = 1; i <= n; ++i)
        {
            vertexIterator<T>* ii = iterator(i);
            int u;
            while ((u = ii->next()) != 0)
                inDegree[u]++;
        }
        
        arrayStack<int> stack;
        for (int i = i; i <= n; ++i)
            if (inDegree[i] == 0)
                stack.push(i);
        
        int j = 0;
        while (!stack.empty())
        {
            int nextVertex = stack.top();
            stack.pop();
            theOrder[j++] = nextVertex;
            vertexIterator<T>* iNextVertex = iterator(nextVertex);
            int u;
            while ((u = iNextVertex->next()) != 0)
            {
                inDegree[u]--;
                if (inDegree[u] == 0)
                    stack.push(u);
            }
        }
        return (j == n);
    }
    
    int bipartiteCover(int *theLabel, int *theCover) {
        int n = numberOfVertices();
        
        int sizeOfA = 0;
        for (int i = 1; i <= n; ++i)
            if (theLabel[i] == 1)
                sizeOfA++;
        int sizeOfB = n - sizeOfA;
        createBins(sizeOfB, n);
        int *newVerticesCovered = new int[n + 1];
        bool *changed = new bool[n + 1];
        std::fill(changed + 1, changed + n + 1, false);
        bool *covered = new bool[n + 1];
        std::fill(covered + 1, covered + n + 1, false);
        arrayStack<int> stack;
        
        for (int i = 1; i <= n; ++i)
            if (theLabel[i] == 1)
            {
                newVerticesCovered[i] = degree(i);
                insertBins(newVerticesCovered[i], i);
            }
        
        int numberCovered = 0, maxBin = sizeOfB;
        
        int coverSize = 0;
        
        while (maxBin > 0)
            if (bin[maxBin] != 0)
            {
                int v = bin[maxBin];
                theCover[coverSize++] = v;
                vertexIterator<T>* iv = iterator(v);
                int j;
                while ((j = iv->next()) != 0)
                {
                    if (!covered[j])
                    {
                        covered[j] = true;
                        numberCovered++;
                        vertexIterator<T>* ij = iterator(j);
                        int k;
                        while ((k = ij->next()) != 0)
                        {
                            newVerticesCovered[k]--;
                            if (!changed[k])
                            {
                                stack.push(k);
                                changed[k] = true;
                            }
                        }
                    }
                }
                
                while (!stack.empty())
                {
                    int k = stack.top();
                    stack.pop();
                    changed[k] = false;
                    moveBins(sizeOfB, newVerticesCovered[k], k);
                }
            }
            else
                maxBin--;
        
        return (numberCovered == sizeOfB) ? coverSize : -1;
    }
    
    bool kruskal(weightedEdge<T>* spanningTreeEdges)
    {
        if (directed() || !weighted())
            throw undefinedMethod("graph::kruskal() not defined for unweighted and directed graphs");
        
        int n = numberOfVertices();
        
        int e = numberOfEdges();
        
        weightedEdge<T>* edge = new weightedEdge<T>[e + 1];
        int k = 0;
        for (int i = 1; i <= n; ++i)
        {
            vertexIterator<T>* ii = iterator(i);
            int j;
            T w;
            while ((j = ii->next(w)) != 0)
                if (i < j)
                    edge[++k] = weightedEdge<int>(i,j,w);
        }
        
        minHeap<weightedEdge<T>> heap(1);
        heap.initialize(edge, e);
        
        fastUnionFind uf(n);
        
        k = 0;
        while (e > 0 && k < n - 1)
        {
            weightedEdge<T> x = heap.top();
            heap.pop();
            e--;
            int a = uf.find(x.vertex1());
            int b = uf.find(x.vertex2());
            if (a != b)
            {
                spanningTreeEdges[k++] = x;
                uf.unite(a,b);
            }
        }
        return (k == n - 1);
    }
    
    void bellmanFord(int s, T *d, int *p) {
        if (!weighted())
            throw undefinedMethod("graph::bellmanFord() not defined for unweighted graphs");
        
        int n = numberOfVertices();
        if (s < 1 || s > n)
            throw illegalParameterValue("illegal source vertex");
        
        arrayList<int>* list1 = new arrayList<int>;
        arrayList<int>* list2 = new arrayList<int>;
        
        bool *inList2 = new bool[n + 1];
        
        std::fill(p + 1, p + n + 1, 0);
        std::fill(inList2 + 1, inList2 + n + 1, false);
        
        d[s] = 0;
        p[s] = s;
        
        list1->insert(0,s);
        
        for (int k = 1; k < n; ++k)
        {
            if (list1->empty())
                break;
            
            for (arrayList<int>::iterator iList1 = list1->begin(); iList1 != list1->end(); ++iList1)
            {
                int u = *iList1;
                vertexIterator<T>* iu = iterator(u);
                int v;
                T w;
                while((v = iu->next(w)) != 0)
                {
                    if (p[v] == 0 || d[u] + w < d[v])
                    {
                        d[v] = d[u] + w;
                        p[v] = u;
                        if (!inList2[v])
                        {
                            list2->insert(list2->size(), v);
                            inList2[v] = true;
                        }
                    }
                }
            }
            
            list1 = list2;
            list2 = new arrayList<int>;
            
            for (arrayList<int>::iterator iList1 = list1->begin(); iList1 != list1->end(); ++iList1)
                inList2[*iList1] = false;
        }
        p[s] = 0;
    }
    
protected:
    static int *reach;
    static int *path;
    static int label;
    static int length;
    static int destination;
    static int* bin;
    static binNode* node;
    
    void rDfs(int v)
    {
        reach[v] = label;
        vertexIterator<T>* iv = iterator(v);
        int u;
        while ((u = iv->next()) != 0)
            if (reach[u] == 0)
                rDfs(u);
        delete iv;
    }
    
    bool rFindPath(int s)
    {
        reach[s] = 1;
        vertexIterator<T>* is = iterator(s);
        int u;
        while ((u = is->next()) != 0)
        {
            if (reach[u] == 0)
            {
                path[++length] = u;
                if (u == destination || rFindPath(u))
                    return true;
                length--;
            }
        }
        delete is;
        return false;
    }
    
    void createBins(int b, int n)
    {
        bin = new int[b + 1];
        std::fill(bin, bin + b + 1, 0);
        node = new binNode[n + 1];
    }
    
    void insertBins(int b, int v)
    {
        if (b == 0)
            return ;
        
        node[v].left = b;
        if (bin[b] != 0)
            node[bin[b]].left = v;
        node[v].right = bin[b];
        bin[b] = v;
    }
    
    void moveBins(int bMax, int toBin, int v)
    {
        int l = node[v].left;
        int r = node[v].right;
        
        if (r != 0)
            node[r].left = node[v].left;
        if (l > bMax || bin[l] != v)
            node[l].right = r;
        else
            bin[l] = r;
        
        insertBins(toBin, v);
    }
};

template<> int* graph<bool>::reach;
template<> int graph<bool>::label;
template<> int* graph<bool>::path;
template<> int graph<bool>::length;
template<> int graph<bool>::destination;
template<> int* graph<bool>::bin;
template<> binNode* graph<bool>::node;
template<> int* graph<int>::reach;
template<> int graph<int>::label;
template<> int* graph<int>::path;
template<> int graph<int>::length;
template<> int graph<int>::destination;
template<> int* graph<int>::bin;
template<> binNode* graph<int>::node;
template<> int* graph<float>::reach;
template<> int graph<float>::label;
template<> int* graph<float>::path;
template<> int graph<float>::length;
template<> int graph<float>::destination;
template<> int* graph<float>::bin;
template<> binNode* graph<float>::node;
template<> int* graph<double>::reach;
template<> int graph<double>::label;
template<> int* graph<double>::path;
template<> int graph<double>::length;
template<> int graph<double>::destination;
template<> int* graph<double>::bin;
template<> binNode* graph<double>::node;

#endif /* graph_hpp */
