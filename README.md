# Housing-Price-Predicition

IMPORTANT** Press "RAW"

A simple machine-learning algorithm, that takes the price, amount of bedrooms and bathrooms, square footage, and year that it was built of a house in an area, then predicts the price of a house based on the data inputted

When running this program, it must be in the format "./estimate train.txt data.txt"; because it must read train.txt first in order to function. The input format must
also be the same when changing "train" and "data".


 The user inputs the data of the houses in "train" that it would like the algorithm to take into account according to the format below:

train
4
(# of houses)
(# bedrooms) (# bathrooms) (sq. footage) (year built) (price)

Example:
train
4
7
3.000000 2.250000 2570.000000 1951.000000 538000.000000
2.000000 1.000000 770.000000 1933.000000 180000.000000
4.000000 3.000000 1960.000000 1965.000000 604000.000000
3.000000 2.000000 1680.000000 1987.000000 510000.000000
4.000000 4.500000 5420.000000 2001.000000 1230000.000000
3.000000 2.250000 1715.000000 1995.000000 257500.000000

The user inputs the data of the house's price it would like to predict in "data" according to the following format:

data
4
(# houses)
(# bedrooms) (# bathrooms) (sq. footage) (year built)

Example:
data
4
2
3.000000 2.500000 3560.000000 1965.000000
2.000000 1.000000 1160.000000 1942.000000
