#Lab 04 Matrix Multiply with Data Access Optimization


- Notebook on [understanding data access](http://nbviewer.ipython.org/6608757).
- Notebook on [using psrun](http://nbviewer.ipython.org/6612772)


__Due: October 1, 2013__

You will improve the runtime performance of your `matrix_multiply` from lab 03 by optimizing the way your program manages data.  Specifically, you will be finding the best loop order and block size for your matrix multiply.

You will need to read and write HDF5 files.  Please use the code from lab 03 if you'd like.  You many want to also read and write text files for testing and debugging, but this is not required for your grade.  Please see the lab 03 `io_hdf.cpp` file for help.

## Testing your code

Use the following module for building your code:

    module load HPSC_CLASS/lab04

We will run you code on several random files created with the `generate_matrix.py` tool from Lab 03.  You will be graded on the correctness and efficiency of your answers. We will run your code from the command line using a `Makefile`.  We should be able to type the
following:

    python ../lab-03/generate_matrix.py -m 100 -n 100 -f matrix.A -t h5
    python ../lab-03/generate_matrix.py -m 100 -n 100 -f matrix.B -t h5
    make run A=matrix.A B=matrix.B C=matrix.C

To help you, we have provided `compare.py`.  It checks the accuracy of your ouput, which
must be in HDF5 format, to that of `numpy` using the `pytables` module.  For example, if you type

    python compare.py -a matrix.A -b matrix.B

you will see the following output for the 100x100 matrix test previously generated:

    accuracy:   4.21103152348e-11
    your time:  0.0377509593964
    dot:        0.00611710548401

The accuracy should be small (maybe I should have called this the abs difference).  The times will not be close; We are just using `numpy` as a benchmark.

This is the script we will use to grade your homework.  Please use it for testing!

## Part A

We will run 5 different matrix multiplications on your code.  The correct answer is worth 5 points each.  Your accuracy values should be less than `1.0e-02`. With very little work, you should be able to take your __naive__ implementation and re-order the loops to obtain the following results.

    N, your_time, dot
    10,0.0166919231415,0.00525999069214
    100,0.0182418823242,0.00555014610291
    200,0.0272040367126,0.00766015052795
    400,0.155385971069,0.0220010280609
    800,0.985706090927,0.124357938766
    1600,10.4380290508,0.906809091568
    3200,84.9806330204,6.44653487206

If you have the correct answer and you are no more than 10% higher than these values, you will get another 5 points.  The correct block algorithm is worth another 5 points, for a total of 15*5 = 75 points.  Notice that you do not start to see the impact of blocking until you have relatively large values for N. 

    N, your_time, dot
    10,0.0220568180084,0.00521898269653
    100,0.0187680721283,0.00572991371155
    200,0.0284101963043,0.00781893730164
    400,0.100296974182,0.0223848819733
    800,1.05097198486,0.124593019485
    1600,7.25710391998,0.906764030457
    3200,56.4555110931,6.44543194771
    
__NOTE__: our test may not include square matrix files.    

## Part B

You will turn in the `psrun` output for each test listed above.  Please name the files exactly so that we can procees them.

    output.200.200
    output.400.400
    output.800.800
    output.1600.1600
    output.3200.3200

You will get 25 points for a correctly generated file.  


## What to turn in?

Please use the new [submission instructions](https://github.com/ResearchComputing/HPSC-Fall-2013/tree/master/lab/submission_instructions).  Your 
directory is located here:
        
        /curc/tools/grading/assignments/assignment-04/$USER


At the minimum, you should have a:
- Makefile
- At least one source file
- All 5 correctly named `psrun` output files.



