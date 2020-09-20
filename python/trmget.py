
import serial

fconfig = open('config.txt', 'r')
fresult = open('result.txt', 'w')

comconf = fconfig.readline().rstrip().split('\n')
comstr = ''.join(comconf)

baudrateconf = fconfig.readline().rstrip().split('\n')
baudratestr = ''.join(baudrateconf)

ser = serial.Serial(comstr, baudrate=int(baudratestr), timeout=1)

print(comstr)
print(baudratestr)

cnt=0

while cnt<20:
    cnt+=1

    rcv = ser.read(4)
    rcvstr=rcv.decode('utf-8')

    if rcvstr=='': continue

    cnt=0

    print(rcvstr)
    print(rcvstr, file=fresult)
    
    if rcvstr=='2000' or rcvstr=='2001' or rcvstr=='2002' or rcvstr=='2003': break
    
ser.close()
fresult.close()
fconfig.close()
