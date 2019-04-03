# 1. import data
install.packages("igraphdata")
library(igraphdahta)
data("USairports")
graph_attr(USairports)

# 2. vertext attributes
vertex_attr_names(USairports)
vertex_attr(USairports, "City")

# 3. edges attributes
edge_attr_names(USairports)
edge_attr(USairports, "Carrier")

# 4. sequence
V(USairports)[1:5] # subset by index
V(USairports)["JFK"] # subset by name
V(USairports)[["JFK"]] # access all attributes

# 5. adding attributes
V(USairports)[1:5]$City # access attributes
# add new attributes
V(USairports)$Group <- sample(c("A","B"), vcount(USairports), replace = TRUE)
V(USairports)[[1:5]]

# 6. edge selector
E(USairports)["JFK" %--% "BOS"] # edges in both direction
# all carriers from JFK to BOS
unique(E(USairports)["JFK" %--% "BOS"]$Carrier)

# 7. edges between groups
inCal <- grepl("CA$", V(USairports)$City)
inNy <- grepl("NY$", V(USairports)$City)
# Edges from CA to NY
E(USairports)[V(USairports)[inCal] %->% V(USairports)[inNy]]

# 8. Induced subgraph
calAirports <- induced_subgraph(USairports, inCal)
calAirports

# 9. Neighbourhoods
# neighbor within 2 vertices from JFK or LAX
d2Vertices <- ego(USairports, nodes = c("JFK","LAX"), order = 2)
# neighor as graphs
JFKNet <- make_ego_graph(USairports, nodes = "JFK", order = 2)[[1]]
plot(JFKNet, vertex.size=0, edge.arrow.size=0.1)

# 10. Adding
# a directed completely empty graph
g <- make_empty_graph(n = 0, directed = TRUE)
g <- g + vertices(c("A","B","C"))
g <- g + edges(c("A","C", "B","C"))
plot(g, edge.arrow.size=0.1)

# 11. Deleting
g <- g - V(g)["A"]
plot(g, edge.arrow.size=0.1)
