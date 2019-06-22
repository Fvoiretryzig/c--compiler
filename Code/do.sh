#!/bin/bash
rm parser
make
# ./parser test.cmm out1.s
./parser ./mytest/argtest.cmm ./gencode/arg.s
./parser ./mytest/arraytest.cmm ./gencode/array.s
./parser ./mytest/facttest.cmm ./gencode/fact.s
./parser ./mytest/fibtest.cmm ./gencode/fibtest.s
./parser ./mytest/gcdtest.cmm ./gencode/gcd.s
./parser ./mytest/is_prime.cmm ./gencode/prime.s
./parser ./mytest/iftest.cmm ./gencode/iftest.s
./parser ./mytest/mytest.cmm ./gencode/my.s
./parser ./mytest/nomaltest.cmm ./gencode/nomal.s
./parser ./mytest/readAndread.cmm ./gencode/readandread.s
./parser ./mytest/simple.cmm ./gencode/simple.s
./parser ./mytest/writeread.cmm ./gencode/writeread.s
