library(tidyverse)
library(rpart)
library(rpart.plot)
library(caret)

data <- read.csv('bank-data.csv', sep = ';')

# Filter
data %>%
  select(-day,
         -month)

# Set seed
set.seed(555)

# Sample indexes for training and testing
test_indedx sample(nrow(data), 0.3*nrow(data)) # 30%
training_data <- data[-test_ind,] # No pick testing data
testing_data <- data[test_ind,] # Pick only testing data

# Training model
tree <- rpart(y ~ .,
              data = training_data)

#pdf('tree.pdf') # Print pdf
#rpart.plot(tree)
#dev.off() # End pdf
        
res_p <- predict(tree, training_data)  # res_p, p maybe is predict
res_class <- predict(tree, 
                    testing_data,
                    type = "class")
          

confusionMatrix(res_class,
              testing_data$y,
              positive = "yes",
              mode = "prec_recall")