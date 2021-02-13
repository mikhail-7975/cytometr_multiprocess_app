import socket

sock = socket.socket()
sock.bind(('127.0.0.1', 9090))
print(sock.getsockname())
print("listen...")
sock.listen(1)
conn, addr = sock.accept()

print('connected:', addr)

while True:
    cmd = input()
    if cmd == "rcv":
        data = conn.recv(9090)
        print(data)
    if cmd == "snd":
        conn.send(b'test responce')
    if cmd == "cls":
        conn.close()
        break

print("connection closed")
