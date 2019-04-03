library(tidyverse)
# Pi
err = c()
for (i in 1:8) {
  n <- 10 ** i
  x <- matrix(runif(n * 2), ncol=2)
  result <- mean(x[,1]**2 + x[,2]**2 < 1)*4
  err = c(err, abs(pi - result))
}
ggplot() + 
  geom_smooth(aes(x = 1:8, y = log10(err)), method='lm') + 
  geom_point(aes(x = 1:8, y = log10(err)))
