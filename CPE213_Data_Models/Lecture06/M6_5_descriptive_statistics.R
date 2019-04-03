# 1. Degree
degDol <- degree(dolphin)
head(degDol)
hist(degree(dolphin))

# 2. Clustering
g <- graph_from_literal(A--B, A--C, A--D, B--C, C--D, D--E)
transitivity(g, type="global")
transitivity(g, type="local")

# 3. Path
sp <- shortest_paths(dolphin, from="Beak", to="Whitetip")
sp$vpath
diameter(dolphin)

## 4. Centrality measures
# 4.1 Betweenness centrality
g <- make_full_graph(4) + vertex(1) + make_full_graph(4)
g <- g + edges(c(4,5, 5,6))
V(g)$name <- LETTERS[1:9]
plot(g, edge.arrow.size=0.1)
betweenness(g)

# 4.2 Eigenvector centrality
ec <- eigen_centrality(g)
ec$vector

# 4.3 PageRank centrality
pr <- page_rank(g)
pr$vector