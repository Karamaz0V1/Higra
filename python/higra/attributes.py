############################################################################
# Copyright ESIEE Paris (2018)                                             #
#                                                                          #
# Contributor(s) : Benjamin Perret                                         #
#                                                                          #
# Distributed under the terms of the CECILL-B License.                     #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################


import numpy as np
import higra as hg


@hg.data_provider("vertex_area")
def attribute_vertex_area(graph):
    if hg.CptRegionAdjacencyGraph.validate(graph): # this is a rag like graph
        pre_graph = hg.CptRegionAdjacencyGraph.construct(graph)["pre_graph"]
        pre_graph_vertex_area = attribute_vertex_area(pre_graph)
        return hg.rag_accumulate_on_vertices(graph, hg.Accumulators.sum, vertex_weights=pre_graph_vertex_area)
    res = np.ones((graph.num_vertices(),), dtype=np.int64)
    hg.CptVertexWeightedGraph.link(res, graph)
    return res


@hg.data_provider("vertex_perimeter")
def attribute_vertex_perimeter(graph):
    vertices = np.arange(graph.num_vertices(), dtype=np.int64)
    res = graph.out_degree(vertices)
    hg.CptVertexWeightedGraph.link(res, graph)
    return res


@hg.data_provider("area")
@hg.argument_helper(hg.CptHierarchy, ("leaf_graph", "vertex_area"))
def attribute_area(tree, vertex_area):
    return hg.accumulate_sequential(tree, vertex_area, hg.Accumulators.sum)


@hg.data_provider("volume")
@hg.argument_helper(hg.CptValuedHierarchy, ("tree", "area"))
def attribute_volume(altitudes, tree, area):
    height = np.abs(altitudes[tree.parents()] - altitudes)
    height = height * area
    volume_leaves = height[:tree.num_leaves()]
    return hg.accumulate_and_add_sequential(tree, height, volume_leaves, hg.Accumulators.sum)


@hg.data_provider("lca_map")
@hg.argument_helper(hg.CptHierarchy)
def attribute_lca_map(tree, leaf_graph):
    lca = hg.LCAFast(tree)
    return lca.lca(leaf_graph)


@hg.data_provider("frontier_length")
@hg.argument_helper(("tree", "lca_map"))
def attribute_frontier_length(tree, lca_map):
    frontier_length = np.zeros((tree.num_vertices(),), dtype=np.int64)
    np.add.at(frontier_length, lca_map, 1)
    return frontier_length


@hg.data_provider("perimeter_length")
@hg.argument_helper(hg.CptHierarchy, ("leaf_graph", "vertex_perimeter"), ("tree", "frontier_length"))
def attribute_perimeter_length(tree, vertex_perimeter, frontier_length):
    return hg.accumulate_and_add_sequential(tree, -2 * frontier_length, vertex_perimeter, hg.Accumulators.sum)


@hg.data_provider("compactness")
@hg.argument_helper("area", "perimeter_length")
def attribute_compactness(tree, area, perimeter_length):
    compactness = area / (perimeter_length * perimeter_length)
    max_compactness = np.nanmax(compactness)
    return compactness / max_compactness


@hg.data_provider("mean_weights")
@hg.argument_helper(hg.CptHierarchy, "area", ("leaf_graph", hg.CptVertexWeightedGraph))
def attribute_mean_weights(tree, area, vertex_weights):
    return hg.accumulate_sequential(tree, vertex_weights.astype(np.float64), hg.Accumulators.sum) / area.reshape((-1, 1))