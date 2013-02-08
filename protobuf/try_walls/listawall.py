#!/usr/bin/env python

import wall_pb2
import sys

# main
if len(sys.argv) != 2:
  print "Usage:", sys.argv[0], "WALL_FILE"
  sys.exit(-1)

awall = wall_pb2.Wall()

f = open(sys.argv[1], 'rb')
awall.ParseFromString(f.read())
f.close()

print awall.health
print awall.exists
print awall.solid
print awall.hot
print awall.w
print awall.h
print awall.d
ext = awall.ext
print ext.nverts
vert = ext.vert[0]
print vert.x
print vert.y
print awall.sprite_name
