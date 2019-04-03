library(igraph)
# 1. Trees
g <- make_tree(27, children = 3)
plot(g, edge.arrow.size=0.1)

# 2. Complete graphs
g <- make_full_graph(n = 6)
plot(g, edge.arrow.size=0.1)

# 3. Lattice
g <- make_lattice(dimvector = c(5,5),
                  circular = FALSE)
V(g)$label <- NA
plot(g, edge.arrow.size=0.1)

# 4. Star
g <- make_star(n=10, mode = "undirected")
plot(g, edge.arrow.size=0.1)

## 5. Networks from dataset
# 5.1 Import data
dolphinEdges <- read.csv("dolphin_edges.csv")
head(dolphinEdges, n=4)
dolphin <- graph_from_data_frame(dolphinEdges, directed = FALSE)
plot(dolphin, vertex.size=1, edge.arrow.size=0.1)


# 5.2 list vertex
dolphinVertices <- read.csv("dolphin_vertices.csv")
head(dolphinVertices, n = 4)
dolphin <- graph_from_data_frame(dolphinEdges, vertices = dolphinVertices, directed = FALSE)
plot(dolphin, vertex.size=1, edge.arrow.size=0.1)

# 5.3 write graph
write_graph(dolphin, "dolphin.graphml", format="graphml")
