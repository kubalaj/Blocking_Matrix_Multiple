##!/usr/bin/env python
import sys
import subprocess



def check_ps(text, filename):
	try:
		if text.startswith('<?xml'):
			cmd = 'psprocess ' + filename
			pid = subprocess.Popen(cmd, shell=True, 
									stdout=subprocess.PIPE,
									stderr=subprocess.PIPE)
			pid.wait()

			out, err = pid.communicate()
			return out
	except:
		print 'POINTS 0:     Could not run run psprocess on your file.'
		exit(1)

	return text

def get_value(text, tag):

	index_start = text.find(tag)

	if index_start >= 0:

		index_end = text.find('\n', index_start)
		val = text[index_end-15:index_end].replace(',','')
		print val
		return float(val)

def parse_text(text, test_name):

	points = 0
	with open(test_name+'.csv', 'w') as outfile:

		value = get_value(text,'Wall clock time')
		if value > 0:
			outfile.write('wallclock,'+str(value)+'\n')
			points += 1

		value = get_value(text,'Level 3 cache misses')
		if value >= 0:
			outfile.write('level_3,'+str(value)+'\n')
			points += 1

		value = get_value(text,'Level 2 cache misses')
		if value >= 0:
			outfile.write('level_2,'+str(value)+'\n')
			points += 1

		return points


filename = sys.argv[1]

test_name = 'psrun_' + filename.split('.')[1]

try:
	with open(filename,'r') as infile:
		text = infile.read()
		text = check_ps(text, filename)
		points = 2
		points += parse_text(text, test_name)
		for p in xrange(points):
			print 'A_POINTS:    1'

except IOError:
	print 'POINTS: 0     Could not file a file named ' + filename 


