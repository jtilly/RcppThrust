library("RcppThrust")

set.seed(1)

x = runif(1e7)

system.time(y <- sort(x))
system.time(z <- mysort(x))

all.equal(y, z)
