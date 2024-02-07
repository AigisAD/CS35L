#!/bin/bash
RES=true
if test "$( ./randall 5| wc -c )" -eq "5" 
then 
    echo "1)We good"
else
    echo "1)Dang"
fi
if test "$( ./randall -i rdrand 5| wc -c )" -eq "5" 
then 
    echo "2)We good"
else
    echo "2)Dang"
fi
if test "$( ./randall -i rdrand 20 -o stdio| wc -c )" -eq "20" 
then 
    echo "3)We good"
else
    echo "3)Dang"
fi
if test "$( ./randall -i mrand48_r 20 -o stdio| wc -c )" -eq "20" 
then 
    echo "4)We good"
else
    echo "4)Dang"
fi
if test "$( ./randall -i /test.sh 20 | wc -c )" -eq "20" 
then 
    echo "5)We good"
else
    echo "5)Dang"
fi
if test "$( ./randall -i rdrand -o 5 21 | wc -c )" -eq "21" 
then 
    echo "6)We good"
else
    echo "6)Dang"
fi
