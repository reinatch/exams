# The comments are notes from mpeshko

import socket
import sys # A subject missed import for sys.exit

host = 'localhost'
port = 9999
address = (host, port)

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(address)
server_socket.listen(5)
print("Listening for client...")
conn, address = server_socket.accept()
while True:
    try:
        output = conn.recv(2048)
        if output:
            print("Message received from client:")
            print(output)
            # print(output.decode()) # Use 'print' and decode bytes to string for clean output
    except:
    #  except socket.error: # It's better to catch specific exceptions
        # conn.close() # Close the connection before exiting
        sys.exit(0)