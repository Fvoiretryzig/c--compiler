#!/bin/bash
rm parser
make
#./parser test.cmm
./parser 3project_test/test1.cmm > test1.ir
./parser 3project_test/test2.cmm > test2.ir
./parser mytest/1-dimarray.cmm > 1-dimarray.ir
./parser mytest/gcd.cmm > gcd.ir
./parser mytest/goldbach.cmm > goldbach.ir
./parser mytest/is_prime.cmm > is_prime.ir
./parser mytest/optimize.cmm > optimize.ir
./parser mytest/readAndread.cmm > readAndread.ir
./parser mytest/simple.cmm > simple.ir
./parser mytest/writeread.cmm > writeread.ir

