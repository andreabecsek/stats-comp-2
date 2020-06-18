#!/bin/bash

#PBS -l nodes=1:ppn=1,walltime=00:10:00

# Define working directory 
export WORK_DIR=$HOME/books

# Define executable
export EXE=/bin/hostname

# Change into working directory 
cd $WORK_DIR

# Print job id and working directory

echo JOB ID: $PBS_JOBID

echo Working Directory: `pwd`

# Execute code 
$EXE
time most_used_words.sh 