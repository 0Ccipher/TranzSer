import re
import sys
pattern = r"(label_[^:]+:;)(.*)(return NULL;)"

if len(sys.argv) != 2:
    print("Usage: python3 getbench.py input_file")
    sys.exit(1)

input_file = sys.argv[1]

with open(input_file, 'r') as file:
    code = file.read()

code = re.sub(r'(label_[^:]:;)', r'\1\n  begin;', code)
out = re.sub(r'(return NULL;)', r'  end;\n\1', code)

start = '''void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() \n'''
with open("Tran/Tran"+input_file, 'w') as file:
    file.write(start)
    file.write(out)
