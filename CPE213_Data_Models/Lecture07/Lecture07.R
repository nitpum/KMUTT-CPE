library(tidyverse)

# Bernoulli PDF
x <- ifelse(runif(5000) < 0.883, 'N', 'Y')

# Binomial PDF
res <- NULL
for(i in 1:1000) {
  res <- c(res,
           # N = 40, P = 0.5
           sum(ifelse(runif(40) < 0.5, 1, 0)))
}



library(readxl)
sData <- read_xlsx('M2_Superstore.xlsx', )