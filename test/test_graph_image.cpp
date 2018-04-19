//
// Created by user on 4/2/18.
//

#include <boost/test/unit_test.hpp>

#include "higra/algo/graph_image.hpp"
#include "test_utils.hpp"

BOOST_AUTO_TEST_SUITE(graphImage);

    using namespace hg;
    using namespace std;


    BOOST_AUTO_TEST_CASE(test4AdjGraphExplicit) {

        auto g = get_4_adjacency_graph({2, 3});

        vector<vector<pair<ulong, ulong>>> outListsRef{{{0, 1}, {0, 3}},
                                                       {{1, 0}, {1, 2}, {1, 4}},
                                                       {{2, 1}, {2, 5}},
                                                       {{3, 0}, {3, 4}},
                                                       {{4, 1}, {4, 3}, {4, 5}},
                                                       {{5, 2}, {5, 4}}
        };
        vector<vector<pair<ulong, ulong>>> outListsTest;

        for (size_t v = 0; v < 6; v++) {
            outListsTest.push_back({});
            for (auto e: hg::out_edge_iterator(v, g))
                outListsTest[v].push_back({source(e, g), target(e, g)});
            BOOST_CHECK(vectorEqual(outListsRef[v], outListsTest[v]));
            BOOST_CHECK(out_degree(v, g) == outListsRef[v].size());

        }

    }

    BOOST_AUTO_TEST_CASE(test4AdjGraphImplicit) {

        auto g = get_4_adjacency_implicit_graph({2, 3});

        vector<vector<pair<ulong, ulong>>> outListsRef{{{0, 1}, {0, 3}},
                                                       {{1, 0}, {1, 2}, {1, 4}},
                                                       {{2, 1}, {2, 5}},
                                                       {{3, 0}, {3, 4}},
                                                       {{4, 1}, {4, 3}, {4, 5}},
                                                       {{5, 2}, {5, 4}}
        };
        vector<vector<pair<ulong, ulong>>> outListsTest;

        for (size_t v = 0; v < 6; v++) {
            outListsTest.push_back({});
            for (auto e: hg::out_edge_iterator(v, g))
                outListsTest[v].push_back({source(e, g), target(e, g)});
            BOOST_CHECK(vectorEqual(outListsRef[v], outListsTest[v]));
            BOOST_CHECK(out_degree(v, g) == outListsRef[v].size());

        }

    }

    BOOST_AUTO_TEST_CASE(test8AdjGraphExplicit) {

        auto g = get_8_adjacency_graph({2, 3});

        vector<vector<pair<ulong, ulong>>> outListsRef{{{0, 1}, {0, 3}, {0, 4}},
                                                       {{1, 0}, {1, 2}, {1, 3}, {1, 4}, {1, 5}},
                                                       {{2, 1}, {2, 4}, {2, 5}},
                                                       {{3, 0}, {3, 1}, {3, 4}},
                                                       {{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 5}},
                                                       {{5, 1}, {5, 2}, {5, 4}}
        };
        vector<vector<pair<ulong, ulong>>> outListsTest;

        for (size_t v = 0; v < 6; v++) {
            outListsTest.push_back({});
            for (auto e: hg::out_edge_iterator(v, g))
                outListsTest[v].push_back({source(e, g), target(e, g)});
            BOOST_CHECK(vectorEqual(outListsRef[v], outListsTest[v]));
            BOOST_CHECK(out_degree(v, g) == outListsRef[v].size());

        }

    }

    BOOST_AUTO_TEST_CASE(test8AdjGraphImplicit) {

        auto g = get_8_adjacency_implicit_graph({2, 3});

        vector<vector<pair<ulong, ulong>>> outListsRef{{{0, 1}, {0, 3}, {0, 4}},
                                                       {{1, 0}, {1, 2}, {1, 3}, {1, 4}, {1, 5}},
                                                       {{2, 1}, {2, 4}, {2, 5}},
                                                       {{3, 0}, {3, 1}, {3, 4}},
                                                       {{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 5}},
                                                       {{5, 1}, {5, 2}, {5, 4}}
        };
        vector<vector<pair<ulong, ulong>>> outListsTest;

        for (size_t v = 0; v < 6; v++) {
            outListsTest.push_back({});
            for (auto e: hg::out_edge_iterator(v, g))
                outListsTest[v].push_back({source(e, g), target(e, g)});
            BOOST_CHECK(vectorEqual(outListsRef[v], outListsTest[v]));
            BOOST_CHECK(out_degree(v, g) == outListsRef[v].size());

        }

    }


    BOOST_AUTO_TEST_CASE(graph2d2khalimsky) {


        auto g = get_4_adjacency_graph({4, 5});

        xt::xarray<int> data{0, 0, 1, 0, 2, 0, 3, 0, 0, 0, 0, 1, 0, 2, 0, 3, 0, 0, 0, 1, 1, 1, 2, 0, 3, 0, 0, 0, 0, 2,
                             3};

        xt::xarray<int> ref{{0, 0, 0, 1, 0, 2, 0, 3, 0},
                            {0, 0, 0, 1, 0, 2, 0, 3, 0},
                            {0, 0, 0, 1, 0, 2, 0, 3, 0},
                            {0, 0, 0, 1, 0, 2, 0, 3, 0},
                            {0, 0, 0, 1, 0, 2, 0, 3, 0},
                            {1, 1, 1, 1, 0, 2, 0, 3, 0},
                            {0, 0, 0, 0, 0, 2, 0, 3, 0}};
        auto r = contour2d_2_khalimsky(g, {4, 5}, data);
        BOOST_CHECK(xt::allclose(ref, r));

        xt::xarray<int> ref2{{0, 0, 0, 0, 1, 0, 2, 0, 3, 0, 0},
                             {0, 0, 0, 0, 1, 0, 2, 0, 3, 0, 0},
                             {0, 0, 0, 0, 1, 0, 2, 0, 3, 0, 0},
                             {0, 0, 0, 0, 1, 0, 2, 0, 3, 0, 0},
                             {0, 0, 0, 0, 1, 0, 2, 0, 3, 0, 0},
                             {0, 0, 0, 0, 1, 0, 2, 0, 3, 0, 0},
                             {1, 1, 1, 1, 1, 0, 2, 0, 3, 0, 0},
                             {0, 0, 0, 0, 0, 0, 2, 0, 3, 0, 0},
                             {0, 0, 0, 0, 0, 0, 2, 0, 3, 0, 0}};
        auto r2 = contour2d_2_khalimsky(g, {4, 5}, data, true);
        BOOST_CHECK(xt::allclose(ref2, r2));
    }



BOOST_AUTO_TEST_SUITE_END();