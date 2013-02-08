#!/usr/bin/env python

import amessage_pb2
import sys

# main
if len(sys.argv) != 2:
  print "Usage:", sys.argv[0], "AMESSAGE_FILE"
  sys.exit(-1)

amessage = amessage_pb2.AMessage()

# prompt or just make one
amessage.a = 1111
amessage.b = 2222

f = open(sys.argv[1], 'wb')
f.write(amessage.SerializeToString())
f.close()
