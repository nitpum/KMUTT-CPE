library(tidyverse)
p <- ggplot(data = mpg) 
p <- p + geom_point(aes(x = cty, y = hwy, color = class))
