import socket
import time

# Server's IP address and port
SERVER_IP = '192.168.1.1'
SERVER_PORT = 23

# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to the server
    client_socket.connect((SERVER_IP, SERVER_PORT))
    
    # Send data to the server
    message = "Hello, server!"
    client_socket.sendall(message.encode())
    time.sleep(5)

    # Receive data from the server
    # data = client_socket.recv(1024)
    # print("Received from server:", data.decode())

except ConnectionRefusedError:
    print("Connection refused. Make sure the server is running and the IP and port are correct.")
except Exception as e:
    print("An error occurred:", e)

finally:
    # Close the socket
    client_socket.close()
