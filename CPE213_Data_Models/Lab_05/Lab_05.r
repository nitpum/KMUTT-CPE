library(tidyverse)
d <- read.csv('Google_Ad_Words.csv')

d <- d %>%
  mutate(CostConversion = as.numeric(gsub('[$,]', '', CostConversion))) %>% 
  mutate(Cost = as.numeric(gsub('[$,]', '', Cost)))

p1 <- d %>% 
  group_by(Ad.Group) %>% 
  sample_frac(0.1) %>% 
  ggplot(aes(x = Cost, y = Conversions, color = Ad.Group)) +
  geom_smooth(method = 'lm', se = FALSE)

cor(d$Cost, d$Conversions)