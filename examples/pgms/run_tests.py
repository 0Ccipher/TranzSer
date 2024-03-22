
import datetime
import subprocess
import sys
import tempfile
import os
import time
from termcolor import colored,cprint

curDir = os.getcwd()
LOGFILENAME = curDir + '/results.txt'
INPUTFILE = curDir + '/litmus.txt'
def runall():
    logfile=open(LOGFILENAME,'w')
    t0=time.time()
    tests = open(INPUTFILE)
    tracecount = 0
    n=0
    safe = 0
    unsafe = 0
    for tst in tests:
        t = 0
        res = 0
        n=n+1
        tst = tst.split("\n")
        cmd = f"nidhuggc -ccv -extfun-no-race=printf {tst[0]}"
        try:
            output=subprocess.check_output(cmd,shell = True).decode("utf-8")
        except Exception as e:
            output = str(e.output)
        print('{0:4}: '.format(n),end='')
        print(tst[0])
        if output.find("Error: Assertion violation at ") >= 0:
            text = colored('   CCV UNSAFE' , 'red')
            print(text)
            res = 0
            unsafe = unsafe + 1
            logfile.write(tst[0]+' Assertion Violation \n')
        else:
            parts_0=output.split(":=")
            trace = parts_0[-1].split("\n")
            text = colored('   CCV SAFE' , 'green')
            print(text + " ---> No of traces: " +trace[0])
            res = 1
            safe = safe + 1
            logfile.write(tst[0]+'----->No of traces = '+trace[0]+'\n')
        try:
            tracecount+=int(trace[0])
        except Exception as e:
            tracecount += 0
            t = -1
        timet = output.split("Total wall-clock time:")
        time_t = timet[-1].split("s")
        print('   Time taken :'+ time_t[0] +'s')
    print("No: of traces " + str(tracecount))
    print("Unsafe "+ str(unsafe) + " && " + "safe "+ str(safe))
    runtime=time.time()-t0
    logfile.write('# '+str(tracecount)+'\n')
    logfile.write('# Time: {0:.2f} s\n'.format(runtime))
    print('# Time: {0:.2f} s\n'.format(runtime))
    logfile.close()

runall()

