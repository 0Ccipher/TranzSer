#!/usr/bin/python3

# Copyright (C) 2022 Omkar
# Based on source code of Carl Leonardsson

import re
import sys

varnumMap = {}

def parse_init(init):
    init=re.sub('([^;\\s])\\s*$','\\1;',init) # Add semi-colon at the end if missing
    inits = re.findall('([^=;\\s]*)\\s*=\\s*([^;\\s]*)\\s*;',init)
    vs = {}
    rs = {}
    crs= {}
    allvars = []
    for pr in inits:
##        print("pr\n");
##        print(pr);
        m = re.fullmatch('P?(\\d+):(.+)',pr[0])
##        print("m\n")
##        print(m)
        try:
            val = str(int(pr[1]))
        except ValueError:
            varName = 'var_'+pr[1]
            val = 'vars['+str(len(varnumMap))+']'
            if varName in varnumMap:
                val = 'vars['+str(varnumMap[varName])+']' # this is the index of the varialbe
            else:
                varnumMap[varName] = len(varnumMap)               
            allvars.append(varName)
        if m == None:
            m = re.fullmatch('(%.+)',pr[0])            
            if m == None:
                # Variable
                varName = 'var_'+pr[0]
                if pr[0].startswith('['):
                    assert(pr[0].endswith(']'))
                    varName='var_'+pr[0][1:-1] # Remove brackets [ ]
                var = 'vars['+str(varnumMap[varName])+']'    
                vs[var] = val
            else:
                # Register common to all threads
                reg=pr[0]
                crs[reg]=val
        else:
            # Register
            pid = int(m.group(1))
            reg = m.group(2)
            if not(pid in rs):
                rs[pid] = {}
            rs[pid][reg] = val
    for v in allvars:
        vv = 'vars['+str(varnumMap[v])+']'
        if not(vv in vs):
            vs[vv] = '0'
    return (vs,rs,crs)

def split_codes(code):
    codes = []
    lines = code.split(';')
    for ln in lines:
        ln = ln.strip()
        if len(ln) == 0: continue
        ins = ln.split('|')
        pid = 0
        for instr in ins:
            if len(codes) <= pid:
                codes.append([])
            instr = instr.strip()
            if len(instr) > 0:
                codes[pid].append(instr)
            pid = pid+1
    return codes

reg_counter = 0
def get_fresh_reg(r=''):
    #if len(r) and r[0]=='%':
    #    r=r[1:]
    global reg_counter
    reg_counter = reg_counter+1
    if len(r):
        return 'v'+str(reg_counter)+'_'+r
    else:
        return 'v'+str(reg_counter)

lbl_counter = 0
def get_fresh_label(l=''):
    global lbl_counter
    lbl_counter = lbl_counter+1
    if len(l):
        return 'label_'+str(lbl_counter)+'_'+l
    else:
        return 'label_'+str(lbl_counter)

def ppc_addi(reg_init,toks):
    tgt=get_fresh_reg(toks[1])
    if toks[2] in reg_init:
        left=reg_init[toks[2]]
    else:
        left='0'
    right=str(int(toks[3]))
    reg_init[toks[1]] = tgt
    return '  int '+tgt+' = '+left+' + '+right+';\n'

def ppc_mullw(reg_init,toks):
    tgt=get_fresh_reg(toks[1])
    if toks[2] in reg_init:
        left=reg_init[toks[2]]
    else:
        left='0'
    if toks[3] in reg_init:
        #right=reg_init[toks[3]][4:]
        right=reg_init[toks[3]]
    else:
        right='0'
    reg_init[toks[1]] = tgt
    return '  int '+tgt+' = '+left+' * '+right+';\n'

def ppc_divw(reg_init,toks):
    tgt=get_fresh_reg(toks[1])
    if toks[2] in reg_init:
        left=reg_init[toks[2]]
    else:
        left='0'
    if toks[3] in reg_init:
        right=reg_init[toks[3]]
    else:
        right='0'
    reg_init[toks[1]] = tgt
    return '  int '+tgt+' = '+left+' / '+right+';\n'

def ppc_cmpw(reg_init,toks):
    if toks[1] in reg_init:
        left=reg_init[toks[1]]
    else:
        left='0'
    if toks[2] in reg_init:
        #right=reg_init[toks[2]][4:]
        right=reg_init[toks[2]]
    else:
        right='0'
    cmpr=get_fresh_reg('cmpeq')
    reg_init[('cmp','eq')] = cmpr
    return '  int '+cmpr+' = ('+left+' == '+right+');\n'

def ppc_cmpwi(reg_init,toks):
    if toks[1] in reg_init:
        left=reg_init[toks[1]]
    else:
        left='0'
    right=str(int(toks[2]))
    cmpr=get_fresh_reg('cmpeq')
    reg_init[('cmp','eq')] = cmpr
    return '  int '+cmpr+' = ('+left+' == '+right+');\n'

def ppc_beq(pc,reg_init,labels,toks):
    if not(('cmp','eq') in reg_init):
        raise Exception('Branching without preceding comparison!')
    lbl1='lbl_'+toks[1]
    assert((pc+1) in labels)
    lbl2=''+labels[pc+1]
    return '  if ('+reg_init[('cmp','eq')]+')  goto '+lbl1+'; else goto '+lbl2+';\n'

def ppc_bne(pc,reg_init,labels,toks):
    if not(('cmp','eq') in reg_init):
        raise Exception('Branching without preceding comparison!')
    lbl1='lbl_'+toks[1]
    assert((pc+1) in labels)
    lbl2=''+labels[pc+1]
    return '  if ('+reg_init[('cmp','eq')]+')  goto '+lbl2+'; else goto '+lbl1+';\n'

def ppc_li(reg_init,toks):
    reg_init[toks[1]] = toks[2]
    return ''

def ppc_mr(reg_init,toks):
    if toks[2] in reg_init:
        reg_init[toks[1]] = reg_init[toks[2]]
    else:
        reg_init[toks[1]] = '0'
    return ''

def ppc_xor(reg_init,toks):
    tgt_reg = get_fresh_reg(toks[1])
    if toks[2] in reg_init:
        op1=reg_init[toks[2]]
    else:
        op1='0'
    if toks[3] in reg_init:
        #op2=reg_init[toks[3]][4:] # remove type
        op2=reg_init[toks[3]]
    else:
        op2='0'
    reg_init[toks[1]] = tgt_reg
    return '  int '+tgt_reg+' = '+op1+' ^ '+op2+';\n'

def ppc_andi(reg_init,toks):
    tgt_reg = get_fresh_reg(toks[1])
    if toks[2] in reg_init:
        op1=reg_init[toks[2]]
    else:
        op1='0'
    op2=str(int(toks[3]))
    reg_init[toks[1]] = tgt_reg
    return '  int '+tgt_reg+' = '+op1+' & '+op2+';\n'

def ppc_stw(reg_init,toks):
    if toks[1] in reg_init:
        val = reg_init[toks[1]]
    else:
        val = '0'
    if val.startswith('vars['): # value is from a variable
        val =  'atomic_load_explicit(&'+val+', memory_order_seq_cst)'
    if toks[2] != '0':
        raise Exception('Non-zero offset in stw: {0}'.format(toks[2]))
    if toks[3] in reg_init:
        addr = reg_init[toks[3]]
    else:
        raise Exception('Uninitialized address used in stw: {0}'.format(toks[3]))
    if addr.startswith('vars['):
        return '  begin; atomic_store_explicit(&'+addr+', '+val+', memory_order_seq_cst); end;\n'
    else:
        raise Exception("The benchmark is containing some unsupported address operations.")

    
def ppc_stwx(reg_init,toks):
    if toks[1] in reg_init:
        val = reg_init[toks[1]]
    else:
        val = '0'
    if val.startswith('vars['): # value is from a variable
        val =  'atomic_load_explicit(&'+val+', memory_order_seq_cst)'
    if toks[2] in reg_init:
        offset=reg_init[toks[2]]
    else:
        offset='0'
    if toks[3] in reg_init:
        addr = reg_init[toks[3]]
##        print('addr\n')
##        print(addr)
    else:
        raise Exception('Uninitialized address used in stwx: {0}'.format(toks[3]))
    if addr.startswith('vars['):
        return '  begin; atomic_store_explicit(&'+addr[:-1]+'+'+offset+'], '+val+', memory_order_seq_cst); end;\n'
    else:
        raise Exception("The benchmark is containing some unsupported address operations.")

    
def ppc_isync(reg_init,toks):
    return '  atomic_fetch_add_explicit(&__fence_var, 0, memory_order_seq_cst);\n'

def ppc_eieio(reg_init,toks):
    return '  atomic_fetch_add_explicit(&__fence_var, 0, memory_order_seq_cst);\n'


def ppc_lwsync(reg_init,toks):
    return '  atomic_fetch_add_explicit(&__fence_var, 0, memory_order_seq_cst);\n'


def ppc_sync(reg_init,toks):
    return '  atomic_fetch_add_explicit(&__fence_var, 0, memory_order_seq_cst);\n'


def ppc_lwzx(reg_init,toks):
    r1=get_fresh_reg()
    r2=get_fresh_reg()
    tgt_reg = get_fresh_reg(toks[1])
    if toks[2] in reg_init:
        offset=reg_init[toks[2]]
    else:
        offset='0'
    if toks[3] in reg_init:
        addr = reg_init[toks[3]]
    else:
        raise Exception('Uninitialized address used in lwzx: {0}'.format(toks[3]))
    reg_init[toks[1]] = tgt_reg
    if addr.startswith('vars['):
        return '  begin; int '+tgt_reg+' = atomic_load_explicit(&'+addr[:-1]+'+'+offset+'], memory_order_seq_cst); end;\n'
    else:
        raise Exception("The benchmark is containing some unsupported address operations.")

def ppc_lwz(reg_init,toks):
    tmp_reg=get_fresh_reg()
    tgt_reg = get_fresh_reg(toks[1])
    if toks[2] != '0':
        raise Exception('Non-zero offset in lwz: {0}'.format(toks[2]))
    if toks[3] in reg_init:
        addr = reg_init[toks[3]]
    else:
        raise Exception('Uninitialized address used in lwz: {0}'.format(toks[3]))
    reg_init[toks[1]] = tgt_reg
    if addr.startswith('vars['): 
        return '  begin; int '+tgt_reg+' = atomic_load_explicit(&'+addr+', memory_order_seq_cst); end;\n'
    else:
        raise Exception("The benchmark is containing some unsupported address operations.")



def instrs_to_c(reg_init,instrs,arch):
    # First find all defined labels
    labels={}
    pc=0
    while pc < len(instrs):
        if (instrs[pc].find(':') >= 0) and not(instrs[pc].endswith(':')):
            # Label and instruction on same line -> separate them
            i=instrs[pc].find(':')
            lbl=instrs[pc][:i]
            instr=instrs[pc][i+1:].strip()
            instrs[pc]=instr
            instrs.insert(pc,lbl+':')
        if instrs[pc].endswith(':'):
            # Label
            assert(not(pc in labels))
            lbl='lbl_'+instrs[pc][:-1]
            labels[pc]=lbl
            del instrs[pc]
        pc=pc+1
    # Then split the code into basic blocks
    if not(0 in labels):
        entry_lbl=get_fresh_label()
        labels[0]=entry_lbl
    BBs=[]
    fwd_incoming={}
    pc=0
    while pc <= len(instrs):
        if pc in labels:
            # New basic block
            lbl=labels[pc]
            incoming=[]
            if pc!=0:
                incoming.append(BBs[-1]['lbl'])
            if lbl in fwd_incoming:
                for ilbl in fwd_incoming[lbl]:
                    incoming.append(ilbl)
            BBs.append({'pc':pc,'lbl':lbl,'incoming':incoming})
        if pc==len(instrs): pc=pc+1; continue
        instr = instrs[pc].replace(',',' ').replace('(',' ').replace(')',' ')
        toks = instr.split()
        if toks[0] in ['beq','bne','b','B','bne','BNE','BEQ']:
            tgtlbl='lbl_'+toks[1]
            if not(tgtlbl in fwd_incoming):
                fwd_incoming[tgtlbl]=[]
            fwd_incoming[tgtlbl].append(BBs[-1]['lbl'])
            if not((pc+1) in labels):
                labels[pc+1]=get_fresh_label()
        pc=pc+1
    # Generate code
    src=''
    pc=0
    for i in range(len(BBs)):
        assert(BBs[i]['pc'] == pc)
        src=src+BBs[i]['lbl']+':;\n'
        # Setup registers, generate phi nodes
        regs={}
        if pc==0:
            for r in reg_init:
                regs[r]=reg_init[r]
        else:
            rns=[]
            iidxs=[]
            for j in range(len(BBs)):
                if BBs[j]['lbl'] in BBs[i]['incoming']:
                    iidxs.append(j)
                    for r in BBs[j]['regs']:
                        if not(r in rns):
                            rns.append(r)
            assert(len(iidxs)>0)
            if len(iidxs)>1:
                for r in rns:
                    if r==('cmp','eq'): continue
                    raise Exception('Unsupport phi node operations')
            else:
                for r in rns:
                    regs[r]=BBs[iidxs[0]]['regs'][r]
        BBs[i]['regs']=regs
        while (pc<len(instrs)) and ((i==len(BBs)-1) or (pc<BBs[i+1]['pc'])):
            instr = instrs[pc].replace(',',' ').replace('(',' ').replace(')',' ')
            instr = instr.replace('[',' ').replace(']',' ')
            toks = instr.split()
            did_branch=False
            if arch == 'PPC':
                if toks[0] == 'addi': src = src+ppc_addi(regs,toks)
                elif toks[0] == 'andi.': src = src+ppc_andi(regs,toks)
                elif toks[0] == 'beq': src = src+ppc_beq(pc,regs,labels,toks); did_branch=True
                elif toks[0] == 'bne': src = src+ppc_bne(pc,regs,labels,toks); did_branch=True
                elif toks[0] == 'cmpw': src = src+ppc_cmpw(regs,toks)
                elif toks[0] == 'cmpwi': src = src+ppc_cmpwi(regs,toks)
                elif toks[0] == 'divw': src = src+ppc_divw(regs,toks)
                elif toks[0] == 'eieio': src = src+ppc_eieio(regs,toks)
                elif toks[0] == 'isync': src = src+ppc_isync(regs,toks)
                elif toks[0] == 'li': src = src+ppc_li(regs,toks)
                elif toks[0] == 'lwsync': src = src+ppc_lwsync(regs,toks)
                elif toks[0] in ['lwz','ld']: src = src+ppc_lwz(regs,toks)
                elif toks[0] in ['lwzx','ldx']: src = src+ppc_lwzx(regs,toks)
                elif toks[0] == 'mr': src = src+ppc_mr(regs,toks)
                elif toks[0] == 'mullw': src = src+ppc_mullw(regs,toks)
                elif toks[0] in ['stw','std']: src = src+ppc_stw(regs,toks)
                elif toks[0] in ['stwx','stdx']: src = src+ppc_stwx(regs,toks)
                elif toks[0] == 'sync': src = src+ppc_sync(regs,toks)
                elif toks[0] == 'xor': src = src+ppc_xor(regs,toks)
                else:
                    raise Exception('Unknown assembly mnemonic: '+toks[0])
            pc=pc+1
        if not(did_branch) and (i+1<len(BBs)):
            src=src+'  goto label '+BBs[i+1]['lbl']+';\n'
    reg_init.clear()
    for r in BBs[-1]['regs']:
        reg_init[r]=BBs[-1]['regs'][r]
    return src

def parse_code(reg_init,common_reg_init,code,arch):
    codes = split_codes(code)
    c_codes = []
    pid=0
    for c in codes:
        if not(pid in reg_init):
            reg_init[pid]={}
        ri = reg_init[pid]
        for r in common_reg_init:
            ri[r] = common_reg_init[r]
        c_codes.append(instrs_to_c(ri,c,arch))
        pid=pid+1
    return c_codes

def get_atom_gvar(pid,reg,val):
    return 'atom_'+str(pid)+'_'+reg+'_'+val

def eval_cond(cond,atoms):
    cond = cond.strip()
    if len(cond) == 0: raise Exception('Failed to parse condition.')
    if cond[0] == '(':
        cond = cond[1:]
        (code,condreg,rest) = eval_cond(cond,atoms)
        rest = rest.strip()
        if (len(rest) == 0 or rest[0] != ')'):
            raise Exception('Failed to parse condition "{0}".'.format(rest))
        rest = rest[1:]
    else:
        m = re.match('^P?(\\d+):([^=\\s]+)\\s*=\\s*([^/\\)\\s]+)((?:.|\n)*)$',cond)
        if m != None: # Register
            pid=int(m.group(1))
            reg=m.group(2)
            val=m.group(3)
            rest = m.group(4)
            if not((pid,reg,val) in atoms):
                atoms.append((pid,reg,val))
            av = get_atom_gvar(pid,reg,val)
            condreg = get_fresh_reg()
            code = '  int '+condreg+' = atomic_load_explicit(&'+get_atom_gvar(pid,reg,val)+', memory_order_seq_cst);\n'
        else:
            m = re.match('\\[?([^=\\s\\]]+)\\]?\\s*=\\s*([^/\\)\\s]+)((?:.|\n)*)$',cond)
            varName='var_'+m.group(1)
            var = 'vars['+str(varnumMap[varName])+']'
            val=m.group(2)
            rest=m.group(3)
            actval = get_fresh_reg()
            condreg = get_fresh_reg()
            try:
                cmpval=str(int(val))
            except: # variable address
                raise Exception("The benchmark is containing some unsupported address operations.")
##                varName = 'var_'+val
##                cmpval = '  atomic_load_explicit(&vars['+str(varnumMap[varName])+'], memory_order_seq_cst)'
            code = '  begin; int '+actval+' = atomic_load_explicit(&'+var+', memory_order_seq_cst); end;\n'
            code = code+'  int '+condreg+' = (' + actval+' == '+cmpval+');\n'
    rest = rest.strip()
    if rest.startswith('/\\'):
        (code2,condreg2,rest) = eval_cond(rest[2:],atoms)
        condreg3 = get_fresh_reg('conj')
        code3 = code+code2+'  int '+condreg3+' = '+condreg+' & '+condreg2+';\n'
        return (code3,condreg3,rest)
    elif rest.startswith('\\/'):
        (code2,condreg2,rest) = eval_cond(rest[2:],atoms)
        condreg3 = get_fresh_reg('disj')
        code3 = code+code2+'  int '+condreg3+' = '+condreg+' | '+condreg2+';\n'
        return (code3,condreg3,rest)
    else:
        return (code,condreg,rest)

def parse_cond(quantifier,cond,reg_init):
    main_check=''
    sub_checks=[]
    atoms=[]

    (code,condreg,rest) = eval_cond(cond,atoms)
    main_check=code
    if quantifier=='exists':
        main_check=main_check+'  if ('+condreg+' == 1) res = 1;\n'
    else:
        assert(quantifier=='forall')
        main_check=main_check+'  if ('+condreg+' == 0) res = 1;\n'

    atom_gvars=[]
    for (pid,reg,val) in atoms:
        atom_gvars.append(get_atom_gvar(pid,reg,val))
        while len(sub_checks) <= pid: sub_checks.append('')
        if (pid in reg_init) and (reg in reg_init[pid]):
            actval = reg_init[pid][reg]
        else:
            actval=' 0'
    #    print('val\n')
 #       print(val)
        try:
            cmpval=str(int(val))
        except: # variable address
##            varName = 'var_'+val
##            cmpval = '  atomic_load_explicit(&vars['+str(varnumMap[varName])+'], memory_order_seq_cst)'
            raise Exception("The benchmark is containing some unsupported address operations.")
        tmp = get_fresh_reg()
        sub_checks[pid] = sub_checks[pid]+'  int '+tmp+' = ('+actval+' == '+cmpval+');\n'
        sub_checks[pid] = sub_checks[pid]+'  atomic_store_explicit(&'+get_atom_gvar(pid,reg,val)+', '+tmp+', memory_order_seq_cst);\n'

    return (main_check,sub_checks,atom_gvars)

def preprocess(s):
    s = re.sub('locations\\s*\\[[^]]*\\]','',s)
    while s.find('(*') != -1:
        start=s.find('(*')
        i=start+2
        depth=1
        while (i<len(s)-1) and (0<depth):
            if s[i:i+2] == '(*':
                depth = depth+1
                i=i+2
            elif s[i:i+2] == '*)':
                depth = depth-1
                i=i+2
            else:
                i=i+1
        if depth==0:
            s=s[:start]+s[i:]
        else:
            s=s[:start]
    s = re.sub('final\\s+([^;]+);\\s*with(?:.|\n)*$','exists \\1;',s)
    return s

def litc(fname):
    f = open(fname,'r')
    s=''
    for ln in f:
        s = s+ln
    s = preprocess(s)
    s = s.strip()
    if s.startswith('PPC'):
        arch='PPC'
    else:
        raise Exception("Failed to parse architecture. Should be 'PPC'.")
    m = re.fullmatch('[^{]*\\{([^}]*)\\}\\s*;?[^;]*;([^~]*)~?\\s*(exists|forall)((?:.|\n)*)',s)
    if m == None:
        raise Exception("Failed to parse litmus test.")
    init = m.group(1)
    code = m.group(2)
    quantifier = m.group(3)
    condition = m.group(4)
    (vs,rs,crs) = parse_init(init)
    c_codes = parse_code(rs,crs,code,arch)
    (main_cond_check,sub_cond_checks,atom_gvars) = parse_cond(quantifier,condition,rs)
    ir='/*TranZSER test*/'
    ir=ir+'#include <pthread.h>\n'
    ir=ir+'#include <stdatomic.h>\n'
    ir=ir+'#include <assert.h>\n\n'
    ir=ir+'void __VERIFIER_Transaction_begin();\n'
    ir=ir+'void __VERIFIER_Transaction_end();\n'
    ir=ir+'#define begin __VERIFIER_Transaction_begin()\n'
    ir=ir+'#define end __VERIFIER_Transaction_end()\n'
##    for v in vs:
##        ir = ir+'atomic_int '+v+'; \n';
    ir = ir+'atomic_int vars['+str(len(varnumMap))+']; \n';  
    for v in atom_gvars:
        ir = ir+'atomic_int '+v+'; \n'
    ir=ir+'\n'
    ir=ir+'atomic_int __fence_var;\n'
    ir=ir+'\n'
    
    pid=0
    for lc in c_codes:
        ir=ir+'void *t'+str(pid)+'(void *arg){\n'
        # ir=ir+' begin;\n'
        ir=ir+lc
        if pid < len(sub_cond_checks):
            ir=ir+sub_cond_checks[pid]       
        # ir=ir+'  end;\n' 
        ir=ir+'  return NULL;\n}\n\n'
        ir=ir+'\n\n\n'
        pid=pid+1
    ir=ir+'int main(int argc, char **argv){\n'
    pid=0
    tds=[]

    pid=0
    for _ in c_codes:
        ir=ir+'  pthread_t thr'+str(pid)+'; \n'
        pid=pid+1
    ir = ir + '\n'
    
    
    pid=0
    for _ in c_codes:
        ir=ir+'  pthread_create(&thr'+str(pid)+', NULL , t'+str(pid)+', NULL);\n'
        pid=pid+1
    ir = ir + '\n'
    
    pid=0
    for _ in c_codes:
        ir=ir+'  pthread_join(thr'+str(pid)+',NULL);\n'
        pid=pid+1
    ir = ir + '\n'
    
    ir = ir+'   int res = 0;\n'
    # ir=ir+' begin;\n'
    ir=ir+main_cond_check
    # ir=ir+'  end;\n'
    ir=ir+' if(res == 1) assert(0);\n'
    ir=ir+'  return 0;\n'
    ir=ir+'}'
    return ir

if (len(sys.argv) != 2):
    print("Usage: {0} <LITMUS TEST>".format(sys.argv[0]))
    exit(1)

print(litc(sys.argv[1]))
