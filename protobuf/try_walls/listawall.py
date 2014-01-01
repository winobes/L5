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

print 'health: ', awall.health
print 'exists: ', awall.exists
print 'solid: ', awall.solid
print 'hot: ', awall.hot
print 'w: ', awall.w
print 'h: ', awall.h
print 'd: ', awall.d
ext = awall.ext
if ext:
  print 'ext: ~ True'
print 'ext.nverts: ', ext.nverts
for ind in xrange(0, ext.nverts):
  vert = ext.vert[ind]
  if vert:
    print 'vert[%d]: ~ True' % ind
  print 'x: ', vert.x
  print 'y: ', vert.y
print 'sprite: ', awall.sprite_name
