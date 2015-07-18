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

        typedef int                                           vertex_descriptor;  
        typedef pair<vertex_descriptor, vertex_descriptor>    edge_descriptor;
        typedef vector<edge_descriptor>                       edge_vec;
        typedef pair<vertex_descriptor, edge_vec>             vertex_rep;
        typedef vector<vertex_rep>                            vertex_vec;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

        typedef typename edge_vec::iterator                   edge_iterator;

        // ---------------
        // vertex_iterator
        // ---------------

        class vertex_iterator : public vertex_vec::iterator {
            public:
                inline vertex_iterator(vertex_vec::iterator const &that)
                    : vertex_vec::iterator(that) {}
                vertex_descriptor operator * () {
                    const vertex_rep& v = vertex_vec::iterator::operator*();
                    return v.first;
                }
        };
/*
        // -------------
        // edge_iterator
        // -------------

        class edge_iterator : vertex_vec::iterator {
            public:
                inline edge_iterator(vertex_vec::iterator const &that)
                    : vertex_vec::iterator(that) {}
                vertex_descriptor operator * () {
                    const vertex_rep& v = vertex_vec::iterator::operator*();
                    return v.first;
                }
        };*/

        // ------------------
        // adjacency_iterator
        // ------------------

        class adjacency_iterator : public edge_vec::iterator {
            public:
                inline adjacency_iterator(edge_vec::iterator const &that)
                    : edge_vec::iterator(that) {}
                vertex_descriptor operator * () {
                    const edge_descriptor& e = edge_vec::iterator::operator*();
                    return e.second;
                }
        };

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
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor u, vertex_descriptor v, Graph&) {
            // <your code>
            edge_descriptor ed = edge_descriptor(u,v);
            bool            b  = true;
            return std::make_pair(ed, b);}

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

            g.adjacency.push_back(vertex_rep(v, edge_vec()));

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
            // <your code>
            edge_vec a(2);     // dummy data
            adjacency_iterator b = a.begin();
            adjacency_iterator e = a.end();
            return std::make_pair(b, e);}

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
            // <your code>
            edge_descriptor ed = edge_descriptor(0,0);
            bool            b  = true;
            return std::make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
         * @param g    a graph
         * @return     an iterator-range providing access to the edges in graph g
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
            // <your code>
            edge_vec a(2);     // dummy data
            edge_iterator b = a.begin();
            edge_iterator e = a.end();
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * @param g    a graph
         * @return     the number of edges in graph g
         */
        friend edges_size_type num_edges (const Graph& g) {
            // <your code>
            edges_size_type s = 1; // fix
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * @param g    a graph
         * @return     the number of vertices in graph g
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            vertices_size_type s = g.adjacency.size(); // fix
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
            // <your code>
            vertex_descriptor v = 0; // fix
            return v;}

        // ------
        // target
        // ------

        /**
         * @param e    an edge
         * @param g    a graph
         * @return     the target vertex of edge e in graph g
         */
        friend vertex_descriptor target (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v = 0; // fix
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
            vertex_descriptor vd = g.adjacency[n].first;
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * @param g    a graph
         * @return     an iterator-range providing access to the vertex set of graph g
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            // extract an iterable of vertices from graph
            vertex_vec vertices = g.adjacency;
            vertex_iterator b = vertices.begin();
            vertex_iterator e = vertices.end();
            return std::make_pair(b, e);}

    private:

        // ----
        // data
        // ----

        /*
         *  Adjacency List Representation
         *
         *  [
         *      ( vertex A, [ edge A->B, edge A->C ] )
         *      ( vertex B, [                      ] )
         *      ( vertex C, [ edge C->B            ] )
         *  ]
         *
         *      A ---
         *      |    \
         *      |     |
         *      V     V
         *      B <-- C
         */

        vertex_vec adjacency;
        vertex_descriptor next_vid;

        // -----
        // valid
        // -----

        /**
         * Check that the contained list is valid.
         */
        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * Default constructor. Creates an empty graph object with zero vertices and zero edges.
         */
        Graph () {
            adjacency = vector<pair<vertex_descriptor, vector<edge_descriptor>>>();
            next_vid = vertex_descriptor();
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h