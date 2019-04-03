library(readxl)
library(tidyverse)

# Read data
data <- read_xlsx('M2_Superstore.xlsx', sheet=1)

data %>%
  filter(Sales < 6000) %>% 
  ggplot() + geom_histogram(aes(x = Quantity), bins = 12)

data %>% 
  group_by(Quantity) %>% 
  summarise(count = n()) -> sales

cdf <- ecdf(sales$count)
data %>% 
  ggplot(aes(x = Quantity)) + stat_ecdf() -> cdf2

# Sampling
quantile(data$Quantity, runif(10))


