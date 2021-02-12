import socket

sock = socket.socket()
sock.bind(('', 27015))
print(sock.getsockname())
print("listen...")
sock.listen(100)
conn, addr = sock.accept()

print('connected:', addr)

while True:
    data = conn.recv(27015)
    if not data:
        break
    conn.send(data.upper())

conn.close()