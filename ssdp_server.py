#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import socket
import random

HOST = '0.0.0.0'
PORT = 8080

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen(5)

print('server start at: %s:%s' % (HOST, PORT))
print('wait for connection...')

while True:
    conn, addr = s.accept()
    print('connected by ' + str(addr))

    while True:
        indata = conn.recv(4)
        indata = conn.recv(1024)
        if len(indata) == 0: # connection closed
            conn.close()
            print('client closed connection.')
            break
        
        msg = str(indata.decode())
        print('recv: ' + msg)

        #send response
        reply = "Recieve Instruction: " + msg + " success!";
        if msg.find('load') > 0:
            num = random.randint(100, 10000)
            reply = reply +   '@' + str(num)
        reply_len = len(reply)
        print('reply is' + reply)
        print('reply len is ' + str(reply_len))
        conn.send(reply_len.to_bytes(2, byteorder='big'))
        conn.send(reply.encode('utf-8'))

        