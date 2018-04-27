import time
import serial
print('before serial')
arduino = serial.Serial('/dev/ttyACM0', 9600)
arduino.flushInput()
from camera import takePicture
from vision import analyzeImage
from MailSend import SendMail

print('before main')
while 1: #main loop
    arduino.write('r')
    print('waiting for motion')
    while 1: #wait for PIR flag
	flag = arduino.readline()
	print(flag)
        if (flag == '5\r\n'):
	    print('motion detected')
            break
    takePicture()
 #   takePicture()
    takePicture()
    print('took picture')
    subjects = analyzeImage()
    if len(subjects) > 0:
	SendMail(subjects)
	print('sent email')
	arduino.write('p')
    else:
	print('did not send email')
        arduino.write('n')
    time.sleep(12);




    
    
        


