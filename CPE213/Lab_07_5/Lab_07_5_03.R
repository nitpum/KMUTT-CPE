library(readxl)
library(tidyverse)

data <- read_xlsx('M2_Superstore.xlsx', sheet = 1)

#data %>% 
#  group_by(`Order Date`) %>% 
#  summarise(count = n()) %>% 
#  ggplot() + geom_histogram(aes(x = `Order Date`))

data %>% 
  group_by()