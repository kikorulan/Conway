#!/bin/bash

#======================================================
# Serial Solution
#======================================================

# Example 1
START_TIME=$(($(date +%s%N)/1000000))
./runConway Example1_dimensions.dat Example1_domain.dat
END_TIME=$(($(date +%s%N)/1000000))
ELAPSED_TIME=$(($END_TIME - $START_TIME))
echo "5000 $ELAPSED_TIME" > performance_serial.dat

# Example 2
START_TIME=$(($(date +%s%N)/1000000))
./runConway Example2_dimensions.dat Example2_domain.dat
END_TIME=$(($(date +%s%N)/1000000))
ELAPSED_TIME=$(($END_TIME - $START_TIME))
echo "10000 $ELAPSED_TIME" >> performance_serial.dat

# Example 3
START_TIME=$(($(date +%s%N)/1000000))
./runConway Example3_dimensions.dat Example3_domain.dat
END_TIME=$(($(date +%s%N)/1000000))
ELAPSED_TIME=$(($END_TIME - $START_TIME))
echo "20000 $ELAPSED_TIME" >> performance_serial.dat
# Example 4
START_TIME=$(($(date +%s%N)/1000000))
./runConway Example4_dimensions.dat Example4_domain.dat
END_TIME=$(($(date +%s%N)/1000000))
ELAPSED_TIME=$(($END_TIME - $START_TIME))
echo "40000 $ELAPSED_TIME" >> performance_serial.dat

# Example 5
START_TIME=$(($(date +%s%N)/1000000))
./runConway Example5_dimensions.dat Example5_domain.dat
END_TIME=$(($(date +%s%N)/1000000))
ELAPSED_TIME=$(($END_TIME - $START_TIME))
echo "80000 $ELAPSED_TIME" >> performance_serial.dat

#======================================================
# CUDA C
#======================================================

# Example 1
START_TIME=$(($(date +%s%N)/1000000))
./runConwayCUDA Example1_dimensions.dat Example1_domain.dat
END_TIME=$(($(date +%s%N)/1000000))
ELAPSED_TIME=$(($END_TIME - $START_TIME))
echo "5000 $ELAPSED_TIME" > performance_cuda.dat

# Example 2
START_TIME=$(($(date +%s%N)/1000000))
./runConwayCUDA Example2_dimensions.dat Example2_domain.dat
END_TIME=$(($(date +%s%N)/1000000))
ELAPSED_TIME=$(($END_TIME - $START_TIME))
echo "10000 $ELAPSED_TIME" >> performance_cuda.dat

# Example 3
START_TIME=$(($(date +%s%N)/1000000))
./runConwayCUDA Example3_dimensions.dat Example3_domain.dat
END_TIME=$(($(date +%s%N)/1000000))
ELAPSED_TIME=$(($END_TIME - $START_TIME))
echo "20000 $ELAPSED_TIME" >> performance_cuda.dat
# Example 4
START_TIME=$(($(date +%s%N)/1000000))
./runConwayCUDA Example4_dimensions.dat Example4_domain.dat
END_TIME=$(($(date +%s%N)/1000000))
ELAPSED_TIME=$(($END_TIME - $START_TIME))
echo "40000 $ELAPSED_TIME" >> performance_cuda.dat

# Example 5
START_TIME=$(($(date +%s%N)/1000000))
./runConwayCUDA Example5_dimensions.dat Example5_domain.dat
END_TIME=$(($(date +%s%N)/1000000))
ELAPSED_TIME=$(($END_TIME - $START_TIME))
echo "80000 $ELAPSED_TIME" >> performance_cuda.dat

#======================================================
# Gnuplot
#======================================================

gnuplot << EOF
set term pdf
set logscale xy
set format xy "%1.1e"
set ylabel "time (ms)"
set xlabel "n of pixels"
set key left
set output 'performanceCUDA.pdf'
set grid
plot 'performance_serial.dat' using 1:2 with lines linetype rgb "#00FFFF" title "Serial" , \
     'performance_cuda.dat'    using 1:2 with lines linetype rgb "#FF00FF" title "CUDA"
EOF
