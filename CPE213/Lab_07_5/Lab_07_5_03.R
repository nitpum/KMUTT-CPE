library(readxl)
library(tidyverse)

data <- read_xlsx('M2_Superstore.xlsx', sheet = 1)

# 1
data %>% 
  group_by(`Order Date`) %>% 
  summarise(n = n()) %>% 
  ggplot() + geom_histogram(aes(x = n))

# 2
data %>% 
  mutate(ProcessingTime = as.Date(`Ship Date` ) - as.Date(`Order Date`)) %>%
  group_by(`Category`) %>% 
  summarise(AvgTime = mean(ProcessingTime)) %>% 
  ggplot() + geom_col(aes(x = Category, y = AvgTime))

# 3
data %>% 
  mutate(ProcessingTime = as.Date(`Ship Date` ) - as.Date(`Order Date`)) %>%
  select(ProcessingTime) %>% 
  ggplot() + geom_density(aes(x = ProcessingTime))
  
# 4
data %>% 
  mutate(ProcessingTime = as.Date(`Ship Date` ) - as.Date(`Order Date`)) %>%
  select(ProcessingTime) -> OrderTime
data %>% 
  group_by(`Order Date`) %>% 
  summarise(n = n()) -> OrderByDate
  # Sampling
  quantile(OrderByDate$n, runif(10)) -> x
  quantile(OrderTime$ProcessingTime, runif(10)) -> y
  mapply(c, x, y)
  mean(x)
  mean(y)
  

# 5
data %>% 
  group_by(`Order ID`) %>% 
  mutate(ProcessingTime = as.Date(`Ship Date` ) - as.Date(`Order Date`)) %>% 
  summarise(OrderSize = n(), ProcessingTime = sum(ProcessingTime)) %>% 
  group_by(OrderSize) %>% 
  summarise(AvgTime = mean(ProcessingTime)) %>% 
  ggplot() + geom_smooth(aes(x = OrderSize, y = AvgTime), method='lm')

# 6 
data %>%
  mutate(Day = format(as.Date(`Order Date`), format="%a")) %>% 
  group_by(Day) %>% 
  summarise(n = n(), Profit = sum(Profit)) %>% 
  filter(Day == 'Fri') -> rawFriday

data %>%
  mutate(Day = format(as.Date(`Order Date`), format="%a")) %>% 
  group_by(Day) %>%
  summarise(n = n(), Profit = sum(Profit)) %>% 
  mutate(n = ifelse(Day == 'Fri', n * 2, n)) %>% 
  mutate(Profit = ifelse(Day == 'Fri', Profit * 2, Profit)) %>% 
  filter(Day == 'Fri') %>% 
  mutate(Day = 'BoostedFri') -> boostedFriday -> boostedFriday

rbind(rawFriday, boostedFriday) %>% 
  ggplot() + geom_col(aes(x = Day, y = Profit, fill = Profit))
  