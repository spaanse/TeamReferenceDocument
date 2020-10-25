import string
import re
import hashlib

def mkhash(inp):
	s = re.sub('\s', '', inp)
	nh = int(hashlib.md5(s.decode('utf8')).hexdigest()[0:2],base=16)
	return "{0:02x}".format(nh)

alphabet = list('0123456789aAbcdDeEfFGhHiIjJkLmMnNpqrRstTuvwxyYz')
found = 0
depth = 0

def search(depth, prefix, goal):
	global found, result, alphabet
	if depth == 0:
		if mkhash(prefix) == goal:
			return prefix
	else:
		for letter in alphabet:
			res = search(depth-1, prefix+letter, goal)
			if res != "":
				return res
	return ""

for i in range(256):
	goal = "{0:02x}".format(i)
	result = ""
	depth = 2
	tmp = int(goal[0:1], base=16) ^ int(goal[1:2], base=16)
	xor = "{0:01x}".format(tmp)
	while result == "":
		result = search(depth,"//"+xor,goal)
		depth = depth+1
	print goal, result