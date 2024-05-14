# Import required module 
from threading import *
import sys
import glob
from serial import Serial, SerialException

# Function to list serial ports
def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    for port in ports:
        try:
            s = Serial(port)
            s.close()
            return port
        except (OSError, SerialException):
            pass
    return None
  
# Serial Reader Thread class 
class SerialInterface(Thread): 
    def __init__(self, port, greenFunction, redFunction, baud_rate=115200, timeout=0.001):
        super().__init__()
        self.port = port
        self.baud_rate = baud_rate
        self.timeout = timeout
        self.greenFunction = greenFunction
        self.redFunction = redFunction
        
        self.ser = Serial(self.port, self.baud_rate, timeout=self.timeout)

    # Target function for thread 
    def run(self): 
        try:
            while True:
                data = self.ser.readline()
                data = data.decode('utf-8')
                if data:
                    if data[0] == 'g':
                        self.greenFunction(data)
                    elif data[0] == 'r':
                        self.redFunction(data)
        except KeyboardInterrupt:
            print("interrupted")
            return
        except Exception as ex:
            print(ex)
            return
        
    def close(self):
        self.ser.close()

    def sendMessage(self, message):
        try:
            self.ser.write(message.encode())
        except Exception as e:
            print(f"Error at port {self.port}: {e}")
  

def initialisePortInterfaces(greenFunction, redFunction):
    port = serial_ports()
    print(f"Serial port found: {port}")


    port = SerialInterface(port=port, greenFunction=greenFunction, redFunction=redFunction)

    port.start()
    
    return port
    
