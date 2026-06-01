import serial

# Cambiar el puerto COMx en Windows o dev/ttyUSBx en Linux
ser = serial.Serial(port='/dev/ttyUSB0', baudrate=115200, timeout=.1)

def menu():
    print("Menu de control del led " )
    print("1. Encender" )
    print("2. Apagar" )
    print("3. Salir de la aplicacion" )

def luzON():
    ser.write(b'H')

def luzOFF():
    ser.write(b'L')


def main():
    print("CONTROL REMOTO DE LED")
    while True:
        menu()
        opc = input("Seleccione una opcion: ")
        if opc == '1':
            print("--> Encendiendo led\n")
            luzON()
        elif opc == '2':
            print("--> Apagando led\n")
            luzOFF()
        elif opc == '3':
            ser.close()
            print("--> Hasta luego\n")
            break
        else:
            print("--> OPCION INVALIDA\n")

if __name__ == "__main__":
    main()
