// --------------------------------
// projects/g++/graph/TestGraph.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

using namespace std;

using testing::Test;
using testing::Types;

// ---------
// TestGraph
// ---------

template <typename G>
struct TestGraph : Test {
    // --------
    // typedefs
    // --------

    typedef          G                     graph_type;
    typedef typename G::vertex_descriptor  vertex_descriptor;
    typedef typename G::edge_descriptor    edge_descriptor;
    typedef typename G::vertex_iterator    vertex_iterator;
    typedef typename G::edge_iterator      edge_iterator;
    typedef typename G::adjacency_iterator adjacency_iterator;
    typedef typename G::vertices_size_type vertices_size_type;
    typedef typename G::edges_size_type    edges_size_type;};

// directed, sparse, unweighted
// possibly connected
// possibly cyclic
typedef Types<
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
        graph_types;

TYPED_TEST_CASE(TestGraph, graph_types);

TYPED_TEST(TestGraph, add_vertex_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    for (int i=0; i<100; i++) {
        vertex_descriptor vdA = add_vertex(g);

        ASSERT_EQ(i, vdA);
    }
}

TYPED_TEST(TestGraph, num_vertex_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertices_size_type vertices_size_type;

    graph_type g;

    for (int i=0; i<100; i++) {
        add_vertex(g);
    }

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(100, vs);
}

TYPED_TEST(TestGraph, vertex_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    for (int i=0; i<100; i++) {
        add_vertex(g);
    }

    vertex_descriptor vd = vertex(55, g);
    ASSERT_EQ(55, vd);
}

TYPED_TEST(TestGraph, vertex_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::vertices_size_type vertices_size_type;

    graph_type g;

    for (int i=0; i<100; i++) {
        vertex_descriptor vdA = add_vertex(g);

        vertex_descriptor vd = vertex(i, g);
        ASSERT_EQ(vdA, vd);

        for (int j=0; j<i; j++) {
            vertex_descriptor vd = vertex(j, g);
            ASSERT_EQ(j, vd);
        }

        vertices_size_type vs = num_vertices(g);
        ASSERT_EQ(i+1, vs);
    }
}

TYPED_TEST(TestGraph, test_vertex) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::vertices_size_type vertices_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);
}

TYPED_TEST(TestGraph, vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    ASSERT_NE(b, e);
    ++b;
    ASSERT_EQ(b, e);
}

TYPED_TEST(TestGraph, vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    ASSERT_NE(b, e);
    vertex_descriptor vd = *b;
    ASSERT_EQ(vdA, vd);
}

TYPED_TEST(TestGraph, vertices_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    for (int i=0; i<100; i++) {
        add_vertex(g);
    }

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;

    vertex_descriptor vd = vertex(55, g);
    ASSERT_EQ(vd, *(b + 55));
}

TYPED_TEST(TestGraph, vertices_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    for (int i=0; i<100; i++) {
        add_vertex(g);
    }

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    
    for (int i=0; i<100; i++) {
        vertex_descriptor vd = vertex(i, g);
        ASSERT_EQ(vd, *(b + i));
        ASSERT_EQ(vd, *(e - (100 - i)));
    }
}

TYPED_TEST(TestGraph, vertices_5) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    for (int i=0; i<100; i++) {
        add_vertex(g);
    }

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    
    graph_type g2;

    for (int i=0; i<100; i++) {
        add_vertex(g2);
    }

    pair<vertex_iterator, vertex_iterator> p2 = vertices(g2);
    vertex_iterator                        b2 = p2.first;
    vertex_iterator                        e2 = p2.second;

    ASSERT_TRUE(equal(b, e, b2));
}

TYPED_TEST(TestGraph, test_vertices) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, add_edge_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<edge_descriptor, bool> pair_edAB = add_edge(vdA, vdB, g);
    edge_descriptor edAB = pair_edAB.first;
    bool success = pair_edAB.second;

    ASSERT_EQ(true, success);
}

TYPED_TEST(TestGraph, source_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<edge_descriptor, bool> pair_edAB = add_edge(vdA, vdB, g);
    edge_descriptor edAB = pair_edAB.first;

    ASSERT_EQ(vdA, source(edAB, g));
}

TYPED_TEST(TestGraph, source_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<edge_descriptor, bool> pair_edAB = add_edge(vdA, vdB, g);
    edge_descriptor edAB = pair_edAB.first;

    pair<edge_descriptor, bool> pair_edBA = add_edge(vdB, vdA, g);
    edge_descriptor edBA = pair_edBA.first;

    ASSERT_EQ(vdA, source(edAB, g));
    ASSERT_EQ(vdB, source(edBA, g));
}

TYPED_TEST(TestGraph, target_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<edge_descriptor, bool> pair_edAB = add_edge(vdA, vdB, g);
    edge_descriptor edAB = pair_edAB.first;

    ASSERT_EQ(vdA, source(edAB, g));
}

TYPED_TEST(TestGraph, target_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<edge_descriptor, bool> pair_edAB = add_edge(vdA, vdB, g);
    edge_descriptor edAB = pair_edAB.first;

    pair<edge_descriptor, bool> pair_edBA = add_edge(vdB, vdA, g);
    edge_descriptor edBA = pair_edBA.first;

    ASSERT_EQ(vdB, target(edAB, g));
    ASSERT_EQ(vdA, target(edBA, g));
}

TYPED_TEST(TestGraph, adjacent_vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    add_edge(vdA, vdB, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;

    vertex_descriptor vd = *b;
    ASSERT_EQ(vdB, vd);
}

TYPED_TEST(TestGraph, adjacent_vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    add_edge(vdA, vdB, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;

    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, adjacent_vertices_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;

    graph_type g;

    for (int i=0; i<100; i++) {
        for (int j=0; j<100; j++) {
            add_edge(i, j, g);
            add_edge(j, i, g);
        }
    }

    pair <vertex_iterator, vertex_iterator> v_iterA = vertices(g);
    vertex_iterator bA = v_iterA.first;
    vertex_iterator eA = v_iterA.second;

    for (int i=0; i<100; i++) {
        pair<adjacency_iterator, adjacency_iterator> adj_v = adjacent_vertices(i, g);
        adjacency_iterator bA = adj_v.first;
        adjacency_iterator eA = adj_v.second;
        for (int j=0; j<100; j++) {
            pair<edge_descriptor, bool> p = edge(i, j, g);
            ASSERT_TRUE(p.second);
            edge_descriptor edAB = p.first;
            vertex_descriptor vdB = target(edAB, g);

            ASSERT_NE(eA, find(bA, eA, vdB));
        }
    }
}

TYPED_TEST(TestGraph, test_adjacent_vertices) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, edge_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<edge_descriptor, bool> p0 = edge(vdA, vdB, g);
    ASSERT_EQ(false, p0.second);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);
}

TYPED_TEST(TestGraph, add_edge_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<edge_descriptor, bool> pair_edAB1 = add_edge(vdA, vdB, g);
    edge_descriptor edAB1 = pair_edAB1.first;
    bool success1 = pair_edAB1.second;

    pair<edge_descriptor, bool> pair_edAB2 = add_edge(vdA, vdB, g);
    edge_descriptor edAB2 = pair_edAB2.first;
    bool success2 = pair_edAB2.second;

    ASSERT_EQ(edAB1, edAB2);
    ASSERT_NE(success1, success2);
    ASSERT_EQ(false, success2);
}

TYPED_TEST(TestGraph, num_edges_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(0, es);

    add_edge(vdA, vdB, g);

    es = num_edges(g);
    ASSERT_EQ(1, es);
}

TYPED_TEST(TestGraph, edge_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    for (int i=0; i<100; i++)
        add_vertex(g);

    for (int i=0; i<100; i++) {
        vertex_descriptor vdA = vertex(i, g);

        for (int j=0; j<100; j++) {
            vertex_descriptor vdB = vertex(j, g);

            pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
            if (i > j)
                ASSERT_EQ(false, p1.second);
            else
                ASSERT_EQ(true, p1.second);

            pair<edge_descriptor, bool> p2 = add_edge(vdB, vdA, g);
            if (i >= j)
                ASSERT_EQ(false, p2.second);
            else
                ASSERT_EQ(true, p2.second);
        }
    }

    for (int i=0; i<100; i++) {
        vertex_descriptor vdA = vertex(i, g);
        for (int j=0; j<100; j++) {
            vertex_descriptor vdB = vertex(j, g);
            ASSERT_TRUE(edge(vdA, vdB, g).second);
            ASSERT_TRUE(edge(vdB, vdA, g).second);
        }
    }
}

TYPED_TEST(TestGraph, num_edges_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    for (int i=0; i<100; i++)
        vertex_descriptor vdA = add_vertex(g);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(0, es);

    for (int i=0; i<100; i++) {
        vertex_descriptor vdA = vertex(i, g);

        for (int j=0; j<100; j++) {
            vertex_descriptor vdB = vertex(j, g);

            pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
            if (i > j)
                ASSERT_EQ(false, p1.second);
            else
                ASSERT_EQ(true, p1.second);

            pair<edge_descriptor, bool> p2 = add_edge(vdB, vdA, g);
            if (i >= j)
                ASSERT_EQ(false, p2.second);
            else
                ASSERT_EQ(true, p2.second);
        }
    }

    es = num_edges(g);
    ASSERT_EQ(100*100, es);
}

TYPED_TEST(TestGraph, num_edges_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    for (int i=0; i<100; i++)
        vertex_descriptor vdA = add_vertex(g);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(0, es);

    for (int i=0; i<100; i++) {
        vertex_descriptor vdA = vertex(i, g);

        for (int j=0; j<100; j++) {
            vertex_descriptor vdB = vertex(j, g);

            pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
            if (i > j)
                ASSERT_EQ(false, p1.second);
            else
                ASSERT_EQ(true, p1.second);

            pair<edge_descriptor, bool> p2 = add_edge(vdB, vdA, g);
            if (i >= j)
                ASSERT_EQ(false, p2.second);
            else
                ASSERT_EQ(true, p2.second);
        }
    }

    for (int i=0; i<100; i++) {
        vertex_descriptor vdA = vertex(i, g);

        for (int j=0; j<100; j++) {
            vertex_descriptor vdB = vertex(j, g);
            add_edge(vdA, vdB, g);
            add_edge(vdB, vdA, g);
        }
    }

    es = num_edges(g);
    ASSERT_EQ(100*100, es);
}

TYPED_TEST(TestGraph, add_edge_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<edge_descriptor, bool> pair_edAB1 = add_edge(vdA, vdB, g);
    edge_descriptor edAB1 = pair_edAB1.first;
    bool success1 = pair_edAB1.second;

    pair<edge_descriptor, bool> pair_edAB2 = add_edge(vdA, vdB, g);
    edge_descriptor edAB2 = pair_edAB2.first;
    bool success2 = pair_edAB2.second;

    ASSERT_EQ(edAB1, edAB2);
    ASSERT_NE(success1, success2);
    ASSERT_EQ(false, success2);
}

TYPED_TEST(TestGraph, add_edge_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    pair<edge_descriptor, bool> pair_edAB = add_edge(8, 9, g);
    edge_descriptor edAB = pair_edAB.first;
    bool success = pair_edAB.second;

    ASSERT_EQ(10, num_vertices(g));
    ASSERT_EQ(1, num_edges(g));

    ASSERT_EQ(true, success);
}

TYPED_TEST(TestGraph, add_edge_5) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    pair<edge_descriptor, bool> pair_edAB = add_edge(8, 9, g);
    edge_descriptor edAB = pair_edAB.first;

    pair<edge_descriptor, bool> p2 = edge(8, 9, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);
}

TYPED_TEST(TestGraph, add_edge_6) {
    typedef typename TestFixture::graph_type         graph_type;

    graph_type g;

    add_edge(8, 9, g);

    for (int i=0; i<10; i++) {
        ASSERT_EQ(i, vertex(i, g));
    }
}

TYPED_TEST(TestGraph, edge_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    for (int i=0; i<100; i++) {
        for (int j=0; j<100; j++) {
            add_edge(i, j, g);
            add_edge(j, i, g);
        }
    }

    pair <vertex_iterator, vertex_iterator> v_iterA = vertices(g);
    vertex_iterator bA = v_iterA.first;
    vertex_iterator eA = v_iterA.second;

    for (int i=0; i<100; i++) {
        for (int j=0; j<100; j++) {
            pair<edge_descriptor, bool> p = edge(i, j, g);
            ASSERT_TRUE(p.second);
            edge_descriptor edAB = p.first;
            vertex_descriptor vdA = source(edAB, g);
            vertex_descriptor vdB = target(edAB, g);

            ASSERT_NE(eA, find(bA, eA, vdA));
            ASSERT_NE(eA, find(bA, eA, vdB));
        }
    }
}

TYPED_TEST(TestGraph, test_edge) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}

TYPED_TEST(TestGraph, edges_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::edge_iterator      edge_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                      b = p.first;
    edge_iterator                      e = p.second;

    ASSERT_NE(e, b);
    ASSERT_EQ(edAB, *b);
}

TYPED_TEST(TestGraph, edges_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::edge_iterator      edge_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                      b = p.first;
    edge_iterator                      e = p.second;

    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, edges_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;

    graph_type g;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                      b = p.first;
    edge_iterator                      e = p.second;

    ASSERT_EQ(b, e);

    for (int i=0; i<100; i++) {
        for (int j=0; j<100; j++) {
            add_edge(i, j, g);
            add_edge(j, i, g);
        }
    }

    pair <vertex_iterator, vertex_iterator> v_iterA = vertices(g);
    vertex_iterator bA = v_iterA.first;
    vertex_iterator eA = v_iterA.second;

    p = edges(g);
    b = p.first;
    e = p.second;

    for (; b != e; b++) {
        edge_descriptor edAB = (*b);
        vertex_descriptor vdA = source(edAB, g);
        vertex_descriptor vdB = target(edAB, g);

        ASSERT_NE(eA, find(bA, eA, vdA));
        ASSERT_NE(eA, find(bA, eA, vdB));
    }
}

TYPED_TEST(TestGraph, test_edges) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::edge_iterator      edge_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                      b = p.first;
    edge_iterator                      e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);}
    ++b;
    ASSERT_EQ(e, b);
}
