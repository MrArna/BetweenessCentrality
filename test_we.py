import os
import subprocess
import sys

test_output = open("output_we.txt", "w")

#
# Delaunay_n14
#
test_output.write("delaunay_n14\n")

we = subprocess.Popen(['./we_parallel', 'delaunay_n14.mtx'], env={'OMP_NUM_THREADS' : '16'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo1"

we = subprocess.Popen(['./we_parallel', 'delaunay_n14.mtx'], env={'OMP_NUM_THREADS' : '8'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo2"

we = subprocess.Popen(['./we_parallel', 'delaunay_n14.mtx'], env={'OMP_NUM_THREADS' : '4'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo3"

we = subprocess.Popen(['./we_parallel', 'delaunay_n14.mtx'], env={'OMP_NUM_THREADS' : '2'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo4"

we = subprocess.Popen(['./we_parallel', 'delaunay_n14.mtx'], env={'OMP_NUM_THREADS' : '1'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo5"

#
# Delaunay_n16
#
test_output.write("delaunay_n16\n")


we = subprocess.Popen(['./we_parallel', 'delaunay_n16.mtx'], env={'OMP_NUM_THREADS' : '16'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo1"

we = subprocess.Popen(['./we_parallel', 'delaunay_n16.mtx'], env={'OMP_NUM_THREADS' : '8'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo2"

we = subprocess.Popen(['./we_parallel', 'delaunay_n16.mtx'], env={'OMP_NUM_THREADS' : '4'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo3"

we = subprocess.Popen(['./we_parallel', 'delaunay_n16.mtx'], env={'OMP_NUM_THREADS' : '2'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo4"

we = subprocess.Popen(['./we_parallel', 'delaunay_n16.mtx'], env={'OMP_NUM_THREADS' : '1'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo5"

#
# Luxembourg_osm
#

test_output.write("luxembourg_osm\n")


we = subprocess.Popen(['./we_parallel', 'luxembourg_osm.mtx'], env={'OMP_NUM_THREADS' : '16'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo1"

we = subprocess.Popen(['./we_parallel', 'luxembourg_osm.mtx'], env={'OMP_NUM_THREADS' : '8'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo2"

we = subprocess.Popen(['./we_parallel', 'luxembourg_osm.mtx'], env={'OMP_NUM_THREADS' : '4'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo3"

we = subprocess.Popen(['./we_parallel', 'luxembourg_osm.mtx'], env={'OMP_NUM_THREADS' : '2'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo4"

we = subprocess.Popen(['./we_parallel', 'luxembourg_osm.mtx'], env={'OMP_NUM_THREADS' : '1'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo5"


#
# fb-wosn-friends.edges
#

test_output.write("fb-wosn-friends.edges\n")


we = subprocess.Popen(['./we_parallel', 'fb-wosn-friends.edges'], env={'OMP_NUM_THREADS' : '16'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo1"

we = subprocess.Popen(['./we_parallel', 'fb-wosn-friends.edges'], env={'OMP_NUM_THREADS' : '8'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo2"

we = subprocess.Popen(['./we_parallel', 'fb-wosn-friends.edges'], env={'OMP_NUM_THREADS' : '4'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo3"

we = subprocess.Popen(['./we_parallel', 'fb-wosn-friends.edges'], env={'OMP_NUM_THREADS' : '2'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo4"

we = subprocess.Popen(['./we_parallel', 'fb-wosn-friends.edges'], env={'OMP_NUM_THREADS' : '1'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo5"


test_output.close()


#
#
# edge parallel
#
#

test_output = open("output_ep.txt", "w")

#
# Delaunay_n14
#
test_output.write("delaunay_n14\n")

we = subprocess.Popen(['./ep', 'delaunay_n14.mtx'], env={'OMP_NUM_THREADS' : '16'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo1"
test_output.flush()

we = subprocess.Popen(['./ep', 'delaunay_n14.mtx'], env={'OMP_NUM_THREADS' : '8'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo2"

we = subprocess.Popen(['./ep', 'delaunay_n14.mtx'], env={'OMP_NUM_THREADS' : '4'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo3"

we = subprocess.Popen(['./ep', 'delaunay_n14.mtx'], env={'OMP_NUM_THREADS' : '2'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo4"

we = subprocess.Popen(['./ep', 'delaunay_n14.mtx'], env={'OMP_NUM_THREADS' : '1'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo5"

#
# Delaunay_n16
#
test_output.write("delaunay_n16\n")


we = subprocess.Popen(['./ep', 'delaunay_n16.mtx'], env={'OMP_NUM_THREADS' : '16'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo1"

we = subprocess.Popen(['./ep', 'delaunay_n16.mtx'], env={'OMP_NUM_THREADS' : '8'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo2"

we = subprocess.Popen(['./ep', 'delaunay_n16.mtx'], env={'OMP_NUM_THREADS' : '4'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo3"

we = subprocess.Popen(['./ep', 'delaunay_n16.mtx'], env={'OMP_NUM_THREADS' : '2'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo4"

we = subprocess.Popen(['./ep', 'delaunay_n16.mtx'], env={'OMP_NUM_THREADS' : '1'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo5"

#
# Luxembourg_osm
#

test_output.write("luxembourg_osm\n")


we = subprocess.Popen(['./ep', 'luxembourg_osm.mtx'], env={'OMP_NUM_THREADS' : '16'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo1"

we = subprocess.Popen(['./ep', 'luxembourg_osm.mtx'], env={'OMP_NUM_THREADS' : '8'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo2"

we = subprocess.Popen(['./ep', 'luxembourg_osm.mtx'], env={'OMP_NUM_THREADS' : '4'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo3"

we = subprocess.Popen(['./ep', 'luxembourg_osm.mtx'], env={'OMP_NUM_THREADS' : '2'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo4"

we = subprocess.Popen(['./ep', 'luxembourg_osm.mtx'], env={'OMP_NUM_THREADS' : '1'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo5"


#
# fb-wosn-friends.edges
#

test_output.write("fb-wosn-friends.edges\n")


we = subprocess.Popen(['./ep', 'fb-wosn-friends.edges'], env={'OMP_NUM_THREADS' : '16'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo1"

we = subprocess.Popen(['./ep', 'fb-wosn-friends.edges'], env={'OMP_NUM_THREADS' : '8'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo2"

we = subprocess.Popen(['./ep', 'fb-wosn-friends.edges'], env={'OMP_NUM_THREADS' : '4'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo3"

we = subprocess.Popen(['./ep', 'fb-wosn-friends.edges'], env={'OMP_NUM_THREADS' : '2'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo4"

we = subprocess.Popen(['./ep', 'fb-wosn-friends.edges'], env={'OMP_NUM_THREADS' : '1'}, stderr=subprocess.PIPE)

for line in we.stderr:
	test_output.write(line)
	#print line
	if we.poll() != None:
		break
print "pippo5"


test_output.close()


