# 1. default plot
g <- make_ring(10, directed = TRUE, mutual = TRUE)
V(g)$name <- LETTERS[1:10]
g <- g + edges(9,5, 7,1, 1,5)
plot(g, edge.arrow.size=0.1)

# 2. Layout
lo <- layout_in_circle(g)
head(lo, n = 4) # lo is a matrix of coornidates
plot(g, layout=lo, edge.arrow.size=0.1)

# 3. tree layout
gTree <- make_tree(15)
plot(gTree, layout=layout_as_tree(gTree, root = 1), edge.arrow.size=0.1)

# 4. grid layout
plot(g, layout=layout_on_grid(g), edge.arrow.size=0.1)

# 5. force layouts
plot(dolphin, layout=layout_with_fr(dolphin), edge.arrow.size=0.1)

# 6. vertex properties
vowel <- V(g)$name %in% c("A","E","I","O","U") + 1
plot(g, layout=lo, vertex.shape = c("circle","square")[vowel], edge.arrow.size=0.1)

# 7. vertex colors and sizes
plot(g, layout=lo, vertex.color=c("tomato2", "royalblue")[vowel], edge.arrow.size=0.1)

# 8. Properties using attributes
V(g)$shape <- "circle"
V(g)$size <- 15
V(g)$color <- "orange"
isVowel <- V(g)$name %in% c("A","E","I","O","U") 
V(g)[isVowel]$shape <- "square"
V(g)[isVowel]$color <- "royalblue"
V(g)[isVowel]$size <- 25
plot(g,layout=lo, edge.arrow.size=0.1)

# 9. Edge properties
E(g)$width = 1
E(g)[V(g)[isVowel] %--% V(g)[isVowel]]$width <- 4
plot(g, layout=lo, edge.arrow.size=0.1)

# 10. Curve edges
plot(g, layout=lo, edge.curved=0.3*which_mutual(g), edge.arrow.size=0.1)
                    
