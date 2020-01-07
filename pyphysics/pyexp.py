import serial
import argparse

parser = argparse.ArgumentParser(description='Physics experiment runner')
parser.add_argument('--port', help='port to use', required=True)
parser.add_argument('--out', help='output results to file')
args = parser.parse_args()

def output(s):
    if args.out is not None:
        with open(args.out,'a') as f:
            f.write(s+'\n')

t=False
ser = serial.Serial(args.port)
while True:
    x=ser.readline().decode("utf-8").strip()
    if x[0]=='#':
        print(x)
    elif not t:
        fields=x
        print(fields)
        output(fields)
        fields=fields.split(',')
        t=True
    else:
        output(x)
        print(' '.join([(i+'='+j) for i, j in zip(fields, x.split(','))]),end='\r')

