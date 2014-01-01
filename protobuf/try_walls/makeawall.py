#!/usr/bin/env python

import wall_pb2
import sys

PI = 3.141592653589793

# main
if len(sys.argv) != 2:
  print "Usage:", sys.argv[0], "WALL_FILE"
  sys.exit(-1)

awall = wall_pb2.Wall()

# prompt or just make one
awall.health = 5
awall.exists = True
awall.solid = True
awall.hot = False
awall.w = 160
awall.h = 20
awall.d = PI / 4
ext = awall.ext
ext.nverts = 4
vert = ext.vert.add()
vert.x = 299
vert.y = 0
vert1 = ext.vert.add()
vert1.x = 459
vert1.y = 0
vert2 = ext.vert.add()
vert2.x = 459
vert2.y = 20
vert3 = ext.vert.add()
vert3.x = 299
vert3.y = 20
awall.sprite_name = 'gfx/little1.png'

f = open(sys.argv[1], 'wb')
f.write(awall.SerializeToString())
f.close()
