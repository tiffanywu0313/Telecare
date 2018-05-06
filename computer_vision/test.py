from subprocess import Popen, PIPE
import cv2
import struct
from video_listen import VideoCaptureYUV
from firebase import firebase
import json

firebase = firebase.FirebaseApplication('https://hackhealth-c0852.firebaseio.com', None)
result = firebase.get('/Rooms/room1', None)
sessionID = result['sessionID']
tokenID = result['token']

result = firebase.get('/Rooms/room1', None)

output = Popen(['./sdlexample',
                '-a', '46113352',
                '-s', '2_MX40NjExMzM1Mn5-MTUyNTU5MTQ1MzU1NX50Z0UxVHA4QzJRc3hldEtXdHN5NjJaN1V-fg',
                '-t', 'T1==cGFydG5lcl9pZD00NjExMzM1MiZzaWc9YTExYWE1NGY2OGFlYWVjZTNlMWI3MTNjYjE0ZDMyMjJkOTM4Zjk3ZjpzZXNzaW9uX2lkPTJfTVg0ME5qRXhNek0xTW41LU1UVXlOVFU1TVRRMU16VTFOWDUwWjBVeFZIQTRRekpSYzNobGRFdFhkSE41TmpKYU4xVi1mZyZjcmVhdGVfdGltZT0xNTI1NTk2MDExJm5vbmNlPTAuOTI2ODAzODMyODY5MDQ1OCZyb2xlPXB1Ymxpc2hlciZleHBpcmVfdGltZT0xNTI1NjgyNDExJmNvbm5lY3Rpb25fZGF0YT1wYXRpZW50JmluaXRpYWxfbGF5b3V0X2NsYXNzX2xpc3Q9',
               # '-d', 'patient'
                ], stdout = PIPE)

size = (480, 640)
cap = VideoCaptureYUV(output.stdout, size)

while 1:
    ret, frame = cap.read()
    if ret:
        cv2.imshow("frame", frame)
        cv2.waitKey(30)
    else:
        break