#!/usr/bin/env python3

import time


class Info(object):
    def __init__(self, i):
        self.id = i
        self.name = str(i)
        self.order = 0
        self.size = 0
        self.unit = 0
        self.count = 0
        self.snaps = {}
        self.pool = 0
        self.kvs = {}

time.sleep(20)

data = {}

for i in range(4000000):
    data[i] = Info(i)

print('done')
data = None

time.sleep(1000)
