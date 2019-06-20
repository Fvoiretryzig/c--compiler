#!/bin/bash
rm parser
make
./parser test.cmm out1.s
