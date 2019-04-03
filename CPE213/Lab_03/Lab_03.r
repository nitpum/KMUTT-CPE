library('tidyverse')

data <- read.csv('bank-data.csv', sep=';')
# Init Graph Data
g1 <- data
g2 <- data
g3 <- data
g4 <- data

g1 <- g1 %>%
  filter(y == 'yes') %>% 
  ggplot() +
  geom_density(aes(x = age)) +
  xlim(c(15, 90))
  
g2 <- g2 %>% 
  ggplot() + 
  geom_bar(aes(x = campaign, fill = y), position = 'fill') +
  xlim(c(0,20)) +
  xlab('Contact Count') + ylab('Percent') +
  scale_fill_discrete(name = "Subscribe", labels = c('No','Yes'))
  
 
g3 <- g3 %>% 
  filter(y == 'yes') %>% 
  ggplot() +
  geom_boxplot(aes(x = job, y = age, fill = job))


g4 <- g4 %>% 
  group_by(job)# %>% 
  #summarise(yes = sum(filter(y == 'yes')))