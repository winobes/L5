#!/usr/bin/env python

import amessage_pb2
import sys

# main
if len(sys.argv) != 2:
  print "Usage:", sys.argv[0], "AMESSAGE_FILE"
  sys.exit(-1)

amessage = amessage_pb2.AMessage()

f = open(sys.argv[1], 'rb')
amessage.ParseFromString(f.read())
f.close()

print amessage.a
print amessage.b
