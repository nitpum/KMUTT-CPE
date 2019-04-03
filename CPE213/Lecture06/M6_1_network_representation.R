# 1. Create a graph matrix
A <- rbind(c(0,1,0), c(1,0,1), c(1,0,0))
nodeNames <- c("A","B","C")
dimnames(A) <- list(nodeNames, nodeNames)
A

# 2. Matrix multiplication. Number of paths of length 2
A %*% A

# 3. Matrix multiplication. Number of paths of length 4
A %*% A %*% A %*% A

# 4. Graph as edge list representation
el <- rbind(c("A","B"), c("B","A"), c("B","C"), c("C","A"))
el

# 5. Representation with igraph
install.packages("igraph")
library(igraph)
g <- graph_from_literal(A--B, B-+C, C-+A)
g

# 6. Graph from edge list
g <- graph_from_edgelist(el, directed=TRUE)
g

# 7. Graph from data frame
df <- as.data.frame(el)
g <- graph_from_data_frame(df, directed=TRUE)
g

# 8. Graph from adjacency matrix
g <- graph_from_adjacency_matrix(A)
g

