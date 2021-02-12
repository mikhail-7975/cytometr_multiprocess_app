import socket

sock = socket.socket()
sock.bind(('127.0.0.1', 9090))
print(sock.getsockname())
print("listen...")
sock.listen(1)
conn, addr = sock.accept()

print('connected:', addr)

while True:
    data = conn.recv(9090)
    if data != b'':
        print(data)
    conn.send(data.upper())

conn.close()