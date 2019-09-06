library(tidyverse)
library(rpart)
library(rpart.plot)
library(caret)

data <- read.csv('HR-Employee-Attrition.csv')
data <- data %>% 
  select(-EmployeeCount,
         -EmployeeNumber,
         -StandardHours,
         -Over18)

set.seed(555)
test_ind <- sample(nrow(data), 0.3*nrow(data)) # Random data 30%
training_data <- data[-test_ind,] # No pick testing data
testing_data <- data[test_ind,] # Pick only testing data

# Check is testing data and training data is validate
summary(training_data)
summary(testing_data)

# Train model
tree <- rpart(Attrition ~ ., # Attrition is ouput, . the other is input
              data = training_data) 

pdf('tree.pdf') # Export pdf
rpart.plot(tree)
dev.off() #end export pdf

# View important rank
tree$variable.importance

res_p <- predict(tree, training_data)
res_class <- predict(tree,
                     testing_data,
                     type = 'class')

res <- factor(ifelse(res_p[, 'Yes'] > 0.3, 'Yes', 'No'),
  levels = c('No', 'Yes'))

confusionMatrix(res_class,
                testing_data$Attrition,
                positive = 'Yes',
                mode = 'prec_recall')
