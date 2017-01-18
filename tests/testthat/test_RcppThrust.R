# test_RcppThrust.R

set.seed(1234)
x = sample(1:1e4, 1e3)
y = sort(x)
z = mysort(x)
expect_equal(y, z)

z = myfunctor(x)
expect_equal(y, -z)
