#!/bin/bash
#PBS -l nodes=1:ppn=8
#PBS -l walltime=0:15:00
#PBS -N peeterj-ps9timeem-time

# Note: submit to queue with:
# 
# cd ; qsub physicsplay/phy1610-scientific-computing/ps9.sh
#------------------------
phy1610=$HOME/physicsplay/phy1610-scientific-computing
. $phy1610/ps9/setup

cd $SCRATCH || exit 5

outdir=timeem.batch.`date +%F-%T`
mkdir $outdir
cd $outdir || exit 7

$phy1610/ps9/timeem.pl 2>&1 | tee -a timeem.out
$phy1610/ps9/timeem.pl 2>&1 | tee -a timeem.out
$phy1610/ps9/timeem.pl 2>&1 | tee -a timeem.out
$phy1610/ps9/timeem.pl 2>&1 | tee -a timeem.out
#$phy1610/ps9/timeem.pl | tee -a timeem.out
#$phy1610/ps9/timeem.pl | tee -a timeem.out
#$phy1610/ps9/timeem.pl | tee -a timeem.out
#$phy1610/ps9/timeem.pl | tee -a timeem.out
