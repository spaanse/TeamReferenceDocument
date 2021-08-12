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

alphabet = list('0123456789aAbcdDeEfFGhHiIjJkLmMnNpqrRstTuvwxyYz')
def revhash(goal, prefix=None):
    if prefix == None:
        first = int(goal[0:1], base=16) ^ int(goal[1:2], base=16)
        prefix = "//{0:01x}".format(first)
    if len(prefix)==5:
        hash = hashlib.md5(prefix.encode('utf-8')).hexdigest()[0:2]
        if hash == goal:
            return prefix
    else:
        for letter in alphabet:
            res = revhash(goal,prefix+letter)
            if res != None:
                return res
    return None

for path, dirs, files in os.walk('./code'):
    for f in files:
        if (f.endswith(".cpp") or f.endswith('.java') or f.endswith('.sh')) and not f.endswith(".test.cpp"):
            p = os.path.join(path, f)
            q = os.path.join(".code", '/'.join(path.split('/')[2:]), f)

            try:
                os.makedirs(os.path.dirname(q))
            except:
                pass

            dat = [ line for line in open(p).read().splitlines() if not line.startswith('// vim: ') and not line.startswith('# vim: ') ]
            out = open(q, 'w')
            prevhash = "00"

            for line, (dat, hash) in enumerate(zip(dat, mkhash(dat))):
                dat = dat.replace('\t','  ')
                s = dat.lstrip(' ')
                if (s.startswith('//') and len(s) > 5):
                    print("//|"+s[2:], file=out)
                    continue
                elif (s.startswith('//') and len(s) <= 5 and hash != '00'):
                    print('Incorrect hash in %s on line %d: %s %s'%(p,line+1,hash,s))
                    print('Line should be %s'%(revhash(prevhash)))
                    # exit(1)
                add = len(dat) - len(s)
                if add > 0:
                    s = ' ' + s
                    add -= 1
                s = '-'*add + s
                if(len(s) > MARGIN):
                    print('WARNING: Code too wide in %s on line %d: %s' % (p,line+1,s))
                    # exit(1)
                print("@"+hash + "|@" + s.ljust(MARGIN, ' '), file=out)
                prevhash = hash
            print('finished processing file %s' % f)

