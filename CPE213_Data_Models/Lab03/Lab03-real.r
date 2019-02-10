library(tidyverse)
data <- read.csv('Google_Ad_Words.csv')

#data <- data %>%
 # mutate(CostConversion = as.numeric(gsub('[$,]', '', CostConversion))) %>% 
  #mutate(Cost = as.numeric(gsub('[$,]', '', Cost)))

p1 <- data %>% 
  group_by(Ad.Group) %>% 
  ggplot(aes(x  =Ad.Group, y = Clicks, fill = Ad.Group))+ geom_boxplot()
#  ggplot(aes(x = Cost, y = Conversions, color = Ad.Group)) +
#  geom_smooth(method = 'lm', se = FALSE)



#p2 <- p1 +
 # geom_smooth(aes(x = Cost, y = Conversions), method = 'lm')
  

#pos <- data %>% 
#  group_by(Ad.Group) %>% 
  

  #geom_boxplot(aes(x = Ad.Group,
                              #y = CostConversion))
                              #y = as.numeric(gsub('[$,]', '', CostConversion))))