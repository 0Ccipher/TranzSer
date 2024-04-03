import re
import sys
import datetime
import subprocess
import tempfile
import os

def get_expected(fname):
    f = open(fname,'r')
    l=[]
    for ln in f:
        ln = ln.strip()
        if len(ln) and not(ln[0] == '#'):
            #print(ln)
            [tst,exp] = ln.split()
            assert(exp == 'Allow' or exp == 'Forbid')
            l.append({'tstname':tst,'expect allow':(exp=='Allow')})
    f.close()
    return l

curDir = os.getcwd()

LOGFILENAME='generate-tran.log'
LITMUSDIR= curDir + '/C-tests'
EXPECTEDLISTFILE= curDir+'/test.results.txt'


start = '''void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() \n'''
logfile=open(LOGFILENAME,'w')
tests = get_expected(EXPECTEDLISTFILE)
n = 0
for tst in tests:
    input_file = tst['tstname']
    out = None
    with open(''+LITMUSDIR+'/'+input_file+'.c', 'r') as file:
        code = file.read()
        code = re.sub(r'(label_[^:]:;)', r'\1\n  begin;', code)
        out = re.sub(r'(return NULL;)', r'  end;\n\1', code)
        out = out.replace('''/* Copyright (C) 2018 Magnus Lång and Tuan Phong Ngo
 * This benchmark is part of SWSC */''' , '''/*Adopted From*/\n /*2018 Magnus Lång and Tuan Phong Ngo
 * This benchmark is part of SWSC */''')
        out = out.replace('''#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>''' , '''#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>\n\n'''+start)
        # out = out.replace("memory_order_acquire",'memory_order_seq_cst')
        # out = out.replace("memory_order_release",'memory_order_seq_cst')
        # out = out.replace("memory_order_acq_rel",'memory_order_seq_cst')
    if out:
        n += 1
        print(f"Transformed {input_file}")
        with open("Tran-litmus/Tran"+input_file+".c", 'w') as ofile:
            ofile.write(out)
print(f"Transformed {n} files\n")