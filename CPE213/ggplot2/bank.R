library(tidyverse)

bankData <- read.csv('bank-data.csv', sep = ';')
bankData %>%
  group_by(job) %>% 
  summarise(n = n())

bankData %>% 
  group_by(education, marital) %>% 
  summarise(n = n()) %>% 
  spread(marital, n)
  

ggplot(bankData, aes(x = job)) +
  geom_bar() + coord_flip()

brk <- c(0, 20, 40, 60, 80, 100)
h <- hist(bankData$age, breaks = brk, plot = F)
freq_table <- data.frame(bin = h$breaks[-1], counts = h$counts)


bankData %>% 
  mutate(age_bin = cut(age, breaks = brk)) %>% 
  group_by(age_bin) %>% 
  summarise(n = n())

bankData %>% 
  sample_frac(0.1) %>% 
  ggplot() +
  geom_histogram(aes(x = age), 
                 color = "white",
                 bins = 30)

bankData %>% 
  ggplot() + geom_boxplot(aes(x = education,
                              y = age,
                              fill = education))
    
