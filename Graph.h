// --------------------------
// projects/c++/graph/Graph.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector

using namespace std;

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------


        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

        typedef vertices_size_type                            vertex_descriptor; 

        // ---------------
        // edge_descriptor
        // ---------------

        class edge_descriptor : public pair<vertex_descriptor, vertex_descriptor> {
        public:
            inline edge_descriptor(pair<vertex_descriptor, vertex_descriptor> const &that = make_pair(vertex_descriptor(),vertex_descriptor()))
                : pair<vertex_descriptor, vertex_descriptor>(that) {}
            operator vertex_descriptor() const { return second; }
        };

        // --------------
        // typedefs cont.
        // --------------

        typedef set<edge_descriptor>                       edge_set;

        // ----------
        // vertex_rep
        // ----------

        class vertex_rep : public pair<vertex_descriptor, edge_set> {
        public:
            inline vertex_rep(pair<vertex_descriptor, edge_set> const &that = make_pair(vertex_descriptor(), edge_set()))
                : pair<vertex_descriptor, edge_set>(that) {}
            operator vertex_descriptor() const { return first; }
        };

        // --------------
        // typedefs cont.
        // --------------

        typedef vector<vertex_rep>                            vertex_vec;

        typedef typename vertex_vec::iterator                 vertex_iterator;
        typedef typename edge_set::iterator                   edge_iterator;
        typedef typename edge_set::iterator                   adjacency_iterator;

    public:
        // --------
        // add_edge
        // --------

        /**
         * Adds edge (u,v) to the graph and returns the edge descriptor for the new edge.
         * @param u    source vertex of the new edge
         * @param v    target vertex of the new edge
         * @param g    graph in which to add new edge
         * @return     pair where first is new edge
         *                        second is true if edge was added, false if edge already existed 
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor u, vertex_descriptor v, Graph& g) {
            // call edge, if false add edge and make b true
            pair<edge_descriptor, bool> uv = edge(u, v, g);
            edge_descriptor             ed = uv.first;
            bool                        b  = uv.second;
            // if edge in adjacency list of u, b is true, so no adding
            if (b) {
                return make_pair(ed, false);
            }
            // add edge to edge set of u
            vertex_vec* vertices = &(g.adjacency);
            // TO DO LATER - if u or v > size of adjacency, add vertices until <
            while (num_vertices(g) <= u || num_vertices(g) <= v)
                add_vertex(g);
            vertex_rep& u_vertex = (*vertices)[u];
            edge_set&   u_edges  = u_vertex.second;
            u_edges.insert(ed);
            // insert new edge into set of all edges in g
            g.all_edges.insert(ed);
            assert(g.valid());
            return make_pair(ed, true);}

        // ----------
        // add_vertex
        // ----------

        /**
         * Adds a vertex to the graph and returns the vertex descriptor for the new vertex.
         * @param g    graph in which to add new vertex
         * @return     new vertex's descriptor
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            vertex_descriptor v = g.next_vid;
            g.next_vid++;

            g.adjacency.push_back(vertex_rep(make_pair(v, edge_set())));

            assert(g.valid());
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * @param u    a vertex
         * @param g    a graph
         * @return     an iterator-range providing access to the vertices adjacent to vertex u in graph g
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor u, const Graph& g) {
            // get edge vector from vertex u
            const vertex_vec* vertices = &(g.adjacency);
            // TO DO LATER - if u or v > size of adjacency, add vertices until <
            const vertex_rep* u_vertex = &(*vertices)[u];
            const edge_set*   u_edges  = &u_vertex->second;
            adjacency_iterator b = const_cast<edge_set*>(u_edges)->begin();
            adjacency_iterator e = const_cast<edge_set*>(u_edges)->end();
            return make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * @param u    a source vertex
         * @param v    a target vertex
         * @param g    a graph
         * @return     pair where first is edge
         *                        second is true if edge existed, false otherwise
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor u, vertex_descriptor v, const Graph& g) {
            edge_descriptor ed = make_pair(u,v);
            bool            b  = false;
            // if u or v is not in g, b is false
            if (num_vertices(g) <= u || num_vertices(g) <= v) {
                b = false;
            }
            else {
                // if u->v is in adjacent vertices to u, b is true
                pair<adjacency_iterator, adjacency_iterator> adj = adjacent_vertices(u, g);
                if (adj.second != find(adj.first, adj.second, ed))
                    b = true;
            }
            return make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
         * @param g    a graph
         * @return     an iterator-range providing access to the edges in graph g
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
            edge_iterator b = g.all_edges.cbegin();
            edge_iterator e = g.all_edges.cend();
            return make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * @param g    a graph
         * @return     the number of edges in graph g
         */
        friend edges_size_type num_edges (const Graph& g) {
            edges_size_type s = g.all_edges.size();
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * @param g    a graph
         * @return     the number of vertices in graph g
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            vertices_size_type s = g.adjacency.size();
            return s;}

        // ------
        // source
        // ------

        /**
         * @param e    an edge
         * @param g    a graph
         * @return     the source vertex of edge e in graph g
         */
        friend vertex_descriptor source (edge_descriptor e, const Graph& g) {
            vertex_descriptor v = e.first;
            return v;}

        // ------
        // target
        // ------

        /**
         * @param e    an edge
         * @param g    a graph
         * @return     the target vertex of edge e in graph g
         */
        friend vertex_descriptor target (edge_descriptor e, const Graph& g) {
            vertex_descriptor v = e.second;
            return v;}

        // ------
        // vertex
        // ------

        /**
         * @param n    an index
         * @param g    a graph
         * @return     the nth vertex in the graph's vertex list
         */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph& g) {
            vertex_descriptor vd = n;
            if (g.adjacency.size() > n)
                vd = g.adjacency[n].first;
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * @param g    a graph
         * @return     an iterator-range providing access to the vertex set of graph g
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            const vertex_vec* vertices = &(g.adjacency);
            vertex_iterator b = const_cast<vertex_vec*>(vertices)->begin();
            vertex_iterator e = const_cast<vertex_vec*>(vertices)->end();
            return std::make_pair(b, e);}

    private:

        // ----
        // data
        // ----

        /*
         *  Adjacency List Representation
         *
         *  [
         *      ( vertex A, [ edge A->B, edge A->C ] ),
         *      ( vertex B, [                      ] ),
         *      ( vertex C, [ edge C->B            ] )
         *  ]
         *
         *      A ---
         *      |    \
         *      |     |
         *      V     V
         *      B <-- C
         */

        vertex_vec        adjacency;
        vertex_descriptor next_vid;
        edge_set          all_edges;

        // -----
        // valid
        // -----

        /**
         * Check that the contained list is valid.
         */
        bool valid () const {
            //cout << "valid check" << endl;
/*            for (vertex_rep v : adjacency) {
                //cout << "check vid " << v.first << endl;
                // no vertex descriptors should be next vid or higher
                if (v.first >= next_vid) {
                    return false;
                }
                {
                    // each vertex descriptor should appear only once
                    pair<vertex_iterator, vertex_iterator> a = vertices(*this);
                    vertex_iterator b = a.first;
                    vertex_iterator e = a.second;
                    if (count(b, e, v.first) > 1) {
                        return false;
                    }
                }
                {
                    // each edge descriptor should have correct source and non-repeating target
                    for (edge_descriptor ed : v.second) {
                        //cout << "check eid " << ed.first << ", " << ed.second << endl;
                        if (source(ed, *this) != v.first) {
                            return false;
                        }
                        pair<adjacency_iterator, adjacency_iterator> a = adjacent_vertices(v.first, *this);
                        adjacency_iterator b = a.first;
                        adjacency_iterator e = a.second;
                        if (count(b, e, ed.second) > 1) {
                            return false;
                        }
                    }
                }
            }*/
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * Default constructor. Creates an empty graph object with zero vertices and zero edges.
         */
        Graph () {
            adjacency = vertex_vec();
            next_vid = vertex_descriptor();
            all_edges = edge_set();
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);

    };

#endif // Graph_h