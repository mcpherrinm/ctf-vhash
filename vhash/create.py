#!/usr/bin/env python
import struct

# Pass in the length you'd be passing to vhash_final
def compute_trailer(length):
  # four uint32_t
  # f[0] = 0x8000_0000
  # f[1] = length
  # f[2] = 0
  # f[3] = 0xFFFF_FFFF

  finalblock = struct.pack('>IIII', 0x80000000, length, 0, 0xFFFFFFFF)

  bonus = '&username=administrator&'
  open('append-data', 'w').write(finalblock + bonus)
  open('bonus', 'w').write(bonus)
  print "wrote trailer to append-data"
  return finalblock + bonus

def gdb_restore_state(hmac):
  state = []
  for _ in xrange(8):
    for m in struct.unpack('>IIII', hmac[0:4*4]):
      state.append(m)
    hmac = hmac[4*4:]
  assert(len(hmac) == 0)
  for i, data in enumerate(state):
    print "set vctx->state[", i, "] = ", data

# take the content part of the cookie
def parse_up_cookie(cookie):
  auth, data = cookie.split("|")
  hmac = auth.split("=")[1].decode('hex')
  gdb_restore_state(hmac)
  return data

print "break vhash_init"
print "run < bonus"
print "finish" # Get back to main
print "step" # set size = 0
data = parse_up_cookie(open("real-cookie").read().strip())

print "set size = ", len(data)
print "p vctx"

print data
print "The data is length ", len(data)
append = compute_trailer(len(data))
open('real-data', 'w').write(data)
print "Wrote data to real-data"


