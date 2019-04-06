library(tidyverse)

data <- read.csv('L8-demand.csv', sep = ';')

model1 <- lm(Target..Total.orders. ~ Non.urgent.order, data)
summary(model1) # 0.8711

model2 <- lm(Target..Total.orders. ~ Urgent.order, data)
summary(model2) # 0.5245

model3 <- lm(Target..Total.orders. ~ Non.urgent.order + Order.type.A, data)
summary(model3) #0.8707

model4 <- lm(Target..Total.orders. ~ Non.urgent.order + Order.type.B, data)
summary(model4) #0.9223

model5 <- lm(Target..Total.orders. ~ Non.urgent.order + Fiscal.sector.orders, data)
summary(model5) # 0.8689

model6 <- lm(Target..Total.orders. ~ Non.urgent.order + Banking.orders..1. + Order.type.B, data)
summary(model6) # 0.9263

model7 <- lm(Target..Total.orders. ~ Non.urgent.order + Banking.orders..2. + Order.type.B, data)
summary(model7) # 0.9248

model8 <- lm(Target..Total.orders. ~ Non.urgent.order + Banking.orders..3. + Order.type.B, data)
summary(model8) # 0.9209