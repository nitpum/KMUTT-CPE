
print = 20
cost = 30
price = 50
weeks <- c(1, 2, 4, 9, 10, 15, 16, 15, 12, 9, 4, 2, 1, 0)
demand <- c(13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26)
tab <- data.frame(
  rannum = c(0.4175, 0.8434, 0.5227, 0.1624, 0.0149, 0.0067, 0.0957, 0.6233, 0.9990, 0.0391, 0.2901, 0.0779)
)
d <- data.frame(
  demand,
  weeks,
  prob = weeks/sum(weeks),
  cum = cumsum(weeks/sum(weeks))
)

rawdata <- rep(demand, weeks)
tab$demand = ceiling(quantile(rawdata, tab$rannum))
tab$sold = ifelse(tab$demand <= print, tab$demand, print)
tab$thrown = ifelse(tab$demand > print, 0, print - tab$demand)
tab$revenue = tab$sold * price
tab$cost = print * cost
tab$profit = tab$revenue - tab$cost
