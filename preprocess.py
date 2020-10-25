#!/usr/bin/env python2
# -*- coding: utf-8 -*- 

import os
import hashlib
import re

MARGIN = 44


def mkhash(dat):
    h="00"
    for i in dat:
        s = re.sub('\s', '', i)
        nh = hashlib.md5(s.encode('utf-8')).hexdigest()[0:2]
        result = int(h, base=16) ^ int(nh, base=16)
        if (not s.startswith('//') or len(s)<=5):
            h= "{0:02x}".format(result)
        if (s.startswith('//') and len(s) > 5):
            yield "  "
        else:
            yield h

for path, dirs, files in os.walk('./code'):
    for f in files:
        if (f.endswith(".cpp") or f.endswith('.java') or f.endswith('.sh')) and not f.endswith(".test.cpp"):
            p = os.path.join(path, f)
            q = os.path.join("_code", '/'.join(path.split('/')[2:]), f)

            try:
                os.makedirs(os.path.dirname(q))
            except:
                pass

            dat = [ line for line in open(p).read().splitlines() if not line.startswith('// vim: ') and not line.startswith('# vim: ') ]
            out = open(q, 'w')

            lenthWarning = False
            for dat, hash in zip(dat, mkhash(dat)):
                dat = dat.replace('\t','  ')
                s = dat.lstrip(' ')
                if (s.startswith('//') and len(s) > 5):
                    print("/"+s, file=out)
                    continue
                elif (s.startswith('//') and len(s) <= 5 and hash != '00'):
                    print('WARNING: Incorrect hash in %s: %s %s'%(p,hash,s))
                add = len(dat) - len(s)
                if add > 0:
                    s = ' ' + s
                    add -= 1
                s = '-'*add + s
                if(len(s) > MARGIN):
                    lenthWarning = True
                print("@"+hash + "|@" + s.ljust(MARGIN, ' '), file=out)
            if lenthWarning:
                print('WARNING: Code too wide: %s' % p)
            print('finished processing file %s' % f)

