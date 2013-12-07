#!/usr/bin/env python
import sys
import argparse
import time
import numpy as np
import tables as tb
import subprocess


def get_args(argv):
    parser = argparse.ArgumentParser()  
    parser.add_argument('-a', help='matrix.A')
    parser.add_argument('-b', help='matrix.B')
    return parser.parse_args(argv)

def read_h5(filename):
    filename = filename
    h5 = tb.openFile(filename, mode = "r")
    X = h5.root.x.read()
    h5.close()
    return X

def execute(fileA, fileB):

    if not fileA or not fileB:
        print 'please specify both -a and -b'
        exit()

    # Call python
    start = time.time()
    A = read_h5(fileA)
    B = read_h5(fileB)
    C = np.dot(A,B)
    python_time = time.time() - start

    #Call your code
    start = time.time()
    cmd = 'make run A=' + fileA + ' B=' + fileB + ' C=output'
    pid = subprocess.Popen(cmd, shell=True)
    pid.wait()
    your_time = time.time() - start

    #Check the accuracy
    D = read_h5('output')
    accuracy = np.sum(abs(C-D))

    return accuracy, your_time, python_time


if __name__ == '__main__':

    args = get_args(sys.argv[1:])

    values = execute(args.a, args.b)

    print "accuracy:  ", values[0]
    print "your time: ", values[1]
    print "dot:       ", values[2]



