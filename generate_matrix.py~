#!/usr/bin/env python
import sys
import argparse
import numpy as np

def get_args(argv):
    parser = argparse.ArgumentParser()  
    parser.add_argument('-m', help='e.g. -m 100')
    parser.add_argument('-n', help='e.g. -n 10')
    parser.add_argument('-f', help='e.g. -f matrix.10x10' )
    return parser.parse_args(argv)

if __name__ == '__main__':

    args = get_args(sys.argv[1:])

    if not args.m or not args.n or not args.f:
        print 'please specify values -m, -n, and -f'
        sys.exit()

    print args.m, args.n 
    M = int(args.m)
    N = int(args.n)

    a = np.random.rand(M,N)
    
    with open(args.f,'w') as outfile:
        outfile.write(str(M)+' '+str(N)+'\n')
        np.savetxt(outfile, a, fmt='%.5f')


