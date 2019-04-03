library(igraphdata)
library(igraph)

dolphinVertices = read.csv("dolphin_vertices.csv")
dolphinEdges = read.csv("dolphin_edges.csv")
dolphinVertices <- read.csv("dolphin_vertices.csv")
dolphin <- graph_from_data_frame(dolphinVertices, directed = FALSE)
plot(dolphin, vertex.size=1, edge.arrow.size=0.1)
graph_attr(dolphin)

# 1.1
# Count Gender
male <- E(dolphin)[V(dolphin) %--% "Male"]
female <- E(dolphin)[V(dolphin) %--% "Female"]
unknown <- E(dolphin)[V(dolphin) %--% "Unknown"]
length(male)
length(female)
length(unknown)

# 1.2
# Weight
E(dolphin)$weight <- 1
E(dolphin)[[1:5]]


# 2 

data("USairports")
# 2.1
longhual <- E(USairports)$Distance > 1500
longtrip <- E(USairports)[[longhual]]

# 2.2
USAirGraph <- subgraph.edges(USairports, which(longhual))
plot(USAirGraph, vertex.size=1, edge.arrow.size=0.1)

# 2.3
t <- make_ego_graph(USairports, nodes = c("OAK"), order=1, mode ="out")[[1]]
V(t)


# 3.1
dolphin <- graph_from_data_frame(dolphinEdges, vertices = dolphinVertices, directed = FALSE)
degDol <- degree(dolphin)
head(degDol)
which.max(degDol)

# 3.2
localCoEff <- transitivity(dolphin, type = "local")
V(dolphin)$name[which.max(localCoEff)]
sp <- shortest.paths(dolphin, v = V(dolphin), to = TRUE)
hist(sp)