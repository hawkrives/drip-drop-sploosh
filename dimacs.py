#!/usr/bin/env python3

import itertools
from operator import mod

numbers = []
for small in range( 5 ):
  for medium in range( 8 ):
    for large in range( 11 ):
      numbers.append( (small, medium, large) )

start = 'p edge'

def add_remainder(minimum, a, b):
  return a + b - min(minimum, a + b)

def find_possibilities( num_set ):
  col1, col2, col3 = num_set

  possibilities = []
  for possibility in num_set:
    # 2 -> 1
    possibilities.append(( min(4, col1 + col2), add_remainder(4, col1, col2 ), col3 ))

    # 1 -> 2
    possibilities.append(( add_remainder(7, col1, col2 ), min(7, col1 + col2), col3 ))

    # 1 -> 3
    possibilities.append(( add_remainder(10, col1, col3 ), col2, min(10, col1 + col3) ))

    # 2 -> 3
    possibilities.append(( col1, add_remainder(10, col2, col3 ), min(10, col2 + col3) ))

    # 3 -> 1
    possibilities.append(( min(4, col1 + col3), col2, add_remainder(4, col1, col3 ) ))

    # 3 -> 2
    possibilities.append(( col1, min(7, col2 + col3), add_remainder(7, col2, col3 ) ))


  return set(possibilities)

# print( numbers )
print(start, 4711, 1956)
for num_set in numbers:
  col1, col2, col3 = num_set
  f = str(col1) + str(col2) + str(col3)
  for p in find_possibilities(num_set):
    p1, p2, p3 = p
    t = str(p1) + str(p2) + str(p3)
    if f != t:
      print('e', f, t)
