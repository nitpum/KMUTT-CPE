library(igraph)

dolphinVertices = read.csv("dolphin_vertices.csv")
dolphin <- graph_from_data_frame(dolphinVertices, directed = FALSE)
plot(dolphin, vertex.size=1, edge.arrow.size=0.1)
graph_attr(dolphin)

# Count Gender
male <- E(dolphin)[V(dolphin) %--% "Male"]
female <- E(dolphin)[V(dolphin) %--% "Female"]
unknown <- E(dolphin)[V(dolphin) %--% "Unknown"]

# Weight
E(dolphin)$weight <- 1
E(dolphin)[[1:5]]


library(igraphdata)
USairports <- data("USairports")