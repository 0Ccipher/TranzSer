#!/usr/bin/python3

# Copyright (C) 2022 Omkar
# Based on source code of Carl Leonardsson
# Run TOOL on all C tests.

import datetime
import subprocess
import sys
import tempfile
import os
import time
import argparse
import multiprocessing

curDir = os.getcwd()
LITMUSDIR = curDir + '/LineTran/Tran'
OUTPUTTFILE = curDir + '/testLineTran.results.txt'
LISTFILE = curDir + '/litmus_list.txt'
# FIX ME
transcBIN = 'genmc'
class bcolors:
    FAIL = '\033[91m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    ENDC = '\033[0m'


def get_expected(fname):
    f = open(fname,'r')
    l = []

    for ln in f:
        ln = ln.strip()
        if len(ln) and not(ln[0] == '#'):
            segments = ln.split()
            assert(segments[1] == 'Allow' or segments[1] == 'Forbid')
            l.append({'tstname' : segments[0],
                      'expect allow' : (segments[1] == 'Allow'),
                      })
    f.close()

    return l


def res_to_string(tst, res):
    s = tst['tstname']
    if 'allow' not in res:
        print(str(tst))
        print(res)
        return(s,False)
    s = s + ' ' + ('Allow' if res['allow'] else 'Forbid')

    return (s + bcolors.OKGREEN + ' OK ' + bcolors.ENDC + ' : ' + str(res['tracecount']), True)

    
def runalltransc(jobs, keep_going):
    logfile = open(OUTPUTTFILE, 'w')
    logfile.write('# The tests where executed using test-transc.py.\n')
    logfile.write('# Date: ' + datetime.datetime.now().strftime('%y%m%d-%H:%M')+'\n')
    logfile.write('\n')

    ret = 0
    totaltracecount = 0
    tests = get_expected(LISTFILE)
    initial_count = len(tests)
    t0 = time.time()

    q = multiprocessing.Queue()
    workers = []
    work = dict()

    def give_work(w, p):
        if len(tests) > 0:
            tst = tests.pop()
            n = initial_count - len(tests)
            p.send((n,tst))
            work[n] = (tst,w,p)
        else:
            p.send('die')
            w.join()

    for _ in range(min(len(tests), jobs)):
        (o, i) = multiprocessing.Pipe(False)
        p = multiprocessing.Process(target=slave, args=(q, o))
        p.start()
        workers.append((p, i))
        give_work(p, i)

    while len(work) > 0:
        (done_n, res) = q.get()
        (tst,w,p) = work.pop(done_n)
        totaltracecount += res['tracecount']
        print('{0:4}: '.format(done_n), end = '')
        (s, ok) = res_to_string(tst, res)
        print(s)
        logfile.write(s  + '\n')
        if not ok:
            if not keep_going: tests.clear()
            ret = 1
        give_work(w, p)

    runtime = time.time() - t0
    logfile.write('# Total number of traces: ' + str(totaltracecount) + '\n')
    logfile.write('# Total running time: {0:.2f} s\n'.format(runtime))
    logfile.close()

    return ret

def slave(q, p):
    while True:
        cmd = p.recv()
        if cmd == 'die': break
        (n,tst) = cmd
        res = run_test(tst)
        q.put((n, res))

def run_test(tst):
    res = dict()
    allow = False # Allow means "error found" (litmus test terminology)
    try:
        cmd = [transcBIN, '--mo', '--transc', '--check-consistency-type=full', '--check-consistency-point=step', '--schedule-policy=ltr', LITMUSDIR+tst['tstname']+'.c']
        # print(cmd)
        out = subprocess.check_output(cmd,stderr = subprocess.STDOUT)
    except subprocess.CalledProcessError as e:
        if e.returncode != 42:
            res['failure'] = transcBIN
            res['tracecount'] = -1
            return res
        allow = True
        out = e.output
    out = out.decode()
    lines = out.split("\n")
    res['tracecount'] = grep_count(lines, "Number of complete executions explored: ")
    res['allow'] = allow
    if (out.find('Assertion violation:') >= 0):
        print("Allow"+str(tst))
    assert((out.find('No errors were detected') >= 0) == (not allow))
    return res


def grep_count(lines, start):
    """
    Finds the first line that starts with `start` and returns the
    integer that follows. Otherwise, returns 0.
    """
    for line in lines:
        if line.startswith(start):
            return int(line[len(start):])
    return 0

def runall(keep_going):
    logfile = open(OUTPUTTFILE, 'w')
    logfile.write('# The tests where executed using test-transc.py.\n')
    logfile.write('# Date: ' + datetime.datetime.now().strftime('%y%m%d-%H:%M')+'\n')
    logfile.write('\n')

    ret = 0
    totaltracecount = 0
    tests = get_expected(LISTFILE)
    n = 0
    t0 = time.time()
    for tst in get_expected(LISTFILE):
        n += 1
        res = run_test(tst)
        (s, ok) = res_to_string(tst, res)
        print('{0:4}: '.format(n), end = '')
        totaltracecount += res['tracecount']
        print(s)
        logfile.write(s  + '\n')
        if not ok:
            if not keep_going: tests.clear()
            ret = 1

    runtime = time.time() - t0
    logfile.write('# Total number of traces: ' + str(totaltracecount) + '\n')
    logfile.write('# Total running time: {0:.2f} s\n'.format(runtime))
    logfile.close()
    return ret


def runonetransc(filename):
    for tst in get_expected(LISTFILE):
        if tst['tstname'] == filename:
            res = run_test(tst)
            (s, ok) = res_to_string(tst, res)
            print(s)
            return 0 if ok else 1

    print('Test case was not found!')
    return 2

####################################################

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    # How many threads we want (default, number of CPUs in the system)
    threads = os.getenv("THREADS", "")
    if threads == "":
        try:
            threads = str(multiprocessing.cpu_count())
        except:
            threads = "1"
    parser.add_argument('-j', dest='jobs', metavar='N', type=int,
                        default=int(threads), help='Number or parallel jobs')
    parser.add_argument('-k', '--keep-going', dest='keep_going',
                        action='store_true',
                        help='Run all tests, even if one fails')
    modes = parser.add_subparsers(metavar='mode',dest='mode')
    all_parser = modes.add_parser('all', help='Run all tests')
    one_parser = modes.add_parser('one', help='Run single test')
    one_parser.add_argument('test', help='testname(without_dot_c)')
    args = parser.parse_args()
    if (args.mode == "all"):
        ret = runalltransc(args.jobs,args.keep_going)
        sys.exit(ret)
    elif (args.mode == "one"):
        ret = runonetransc(args.test)
        sys.exit(ret)
    else:
        parser.print_help()
