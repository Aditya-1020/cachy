def trace(x):
    return [f"0x{i * 64:x}" for i in range(x)]

with open("tests/seq_trace.txt", 'w') as f:
    f.write('\n'.join(trace(1000)) + '\n')
