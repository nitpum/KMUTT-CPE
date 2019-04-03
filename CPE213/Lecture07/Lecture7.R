library(tidyverse)
bankData <- read.csv('bank-data.csv', sep=';')

ggplot(bankData) +
  geom_histogram(aes(x=age, y = ..density..), 
                 color = 'white') +
  ylab('Probability')

age_avg = mean(bankData$age)
age_sd = sd(bankData$age)
hist(rnorm(1000,mean = age_avg, sd = age_sd))

x<- data.frame(A = rexp(10000,rate = 0.5), 
               B = rexp(10000, rate = 1), 
               C = rexp(10000, rate = 2))
ggplot(x) + 
  geom_density(aes(x=A), color='green') + 
  geom_density(aes(x=B),color='blue') + 
  geom_density(aes(x=C),color='red')

bankData %>% 
  group_by(y) %>% 
  summarise(n=n())

# n =40, p = 0.5
x <- NULL
for(i  in 1:1000) {
  x <- c(x,sum(ifelse(runif(40) > 0.5, 1, 0)))
}
ggplot(data.frame(x=x)) + geom_histogram(aes(x=x), bins = 80)

library(readxl)
sData <- read_xlsx('M2_Superstore.xlsx', sheet = 1)
sData %>% 
  group_by(`Order Date`) %>% 
  summarise(count = n())  -> orderByDate
ggplot(orderByDate) +
  geom_histogram(aes(x=count),bins = 30)
order_mean <- mean(orderByDate$count)
rpois(100, lambda = 8)

cdf <- ecdf(orderByDate$count)
plot(cdf)
cdf(2)



hist(quantile(orderByDate$count, runif(100000)))



table(bankData$marital)/nrow(bankData)

x <- runif(1000)
marital <- ifelse(x<0.115,'divorced',
                  ifelse(x<0.717,'married','single'))
