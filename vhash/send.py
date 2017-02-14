#!/usr/bin/env python
import urllib
import urllib2
opener = urllib2.build_opener()

auth = 'd80d05ec2d4e4f3a3e93358ff4c1534cb9e5bd45a274d42f70fc465867af6ae2615f00e5855ea9330593161ff116f7fd6ac5a6d2d6dfe682639999337c9229ae53203b1a74b53b844a3319ffa65ddf3144f2709e2a37085a2e6ee684344922d5069eaef0f58cf1e1b9795f5a6d84e5f8b3952812ff390fedd9f2b30d8c5c8cbc'

trailer = open('append-data').read().strip()
real = open('real-data').read().strip()

cookie = "auth=" + auth + "|" + urllib.quote_plus(real + trailer)
print cookie

opener.addheaders.append(('Cookie', cookie))
try:
 f = opener.open("http://thenewandlessbrokenvhash.ctf.bsidessf.net:9292/index.php")
 print f.read()
except Exception as e:
 print e
 print e.read()
