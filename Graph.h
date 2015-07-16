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

        typedef int                                         vertex_descriptor;  // fix!
        typedef pair<vertex_descriptor, vertex_descriptor>  edge_descriptor;
        typedef vector<edge_descriptor>                     edge_vec;
        typedef pair<vertex_descriptor, edge_vec>           vertex;
        typedef vector<vertex>                              vertex_vec;


        typedef int*                                        vertex_iterator;    // fix!
        typedef typename vector<edge_descriptor>::iterator  edge_iterator;      // fix!
        typedef int*                                        adjacency_iterator; // fix!

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor, vertex_descriptor, Graph&) {
            // <your code>
            edge_descriptor ed = edge_descriptor(0,0);
            bool            b  = false;
            return std::make_pair(ed, b);}

        // ----------
        // add_vertex
        // ----------

        /**
         * <your documentation>
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            vertex_descriptor v = g.next_vid;
            g.next_vid++;

            g.adjacency.push_back(vertex(v, edge_vec()));

            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * <your documentation>
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor, const Graph&) {
            // <your code>
            static int a [] = {0, 0};     // dummy data
            adjacency_iterator b = a;
            adjacency_iterator e = a + 2;
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor, vertex_descriptor, const Graph&) {
            // <your code>
            edge_descriptor ed = edge_descriptor(0,0);
            bool            b  = true;
            return std::make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
         * <your documentation>
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph&) {
            // <your code>
            vector<edge_descriptor> a(2);     // dummy data
            edge_iterator b = a.begin();
            edge_iterator e = a.end();
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * <your documentation>
         */
        friend edges_size_type num_edges (const Graph&) {
            // <your code>
            edges_size_type s = 1; // fix
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation>
         */
        friend vertices_size_type num_vertices (const Graph&) {
            // <your code>
            vertices_size_type s = 1; // fix
            return s;}

        // ------
        // source
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor source (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v = 0; // fix
            return v;}

        // ------
        // target
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor target (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v = 0; // fix
            return v;}

        // ------
        // vertex
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor vertex (vertices_size_type i, const Graph& g) {
            // <your code>
            vertex_descriptor vd = g.adjacency[i].first;
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph&) {
            // <your code>
            static int a [] = {0, 0};     // dummy data
            vertex_iterator b = a;
            vertex_iterator e = a + 2;
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
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
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