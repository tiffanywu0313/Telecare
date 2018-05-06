import cv2
import numpy as np
from subprocess import Popen, PIPE
import struct

class VideoCaptureYUV:
    def __init__(self, f, size):
        self.f = f
    def read_raw(self):
        try:
            self.width = struct.unpack('<i', self.f.read(4))[0]
            self.height = struct.unpack('<i', self.f.read(4))[0]

            self.frame_len = self.width * self.height * 3 // 2
            self.shape = (int(self.height*1.5), self.width)

            raw = self.f.read(self.frame_len)
            yuv = np.frombuffer(raw, dtype=np.uint8)
            yuv = yuv.reshape(self.shape)
        except Exception as e:
            print (str(e))
            return False, None
        return True, yuv

    def read(self):
        ret, yuv = self.read_raw()
        if not ret:
            return ret, yuv
        bgr = cv2.cvtColor(yuv, cv2.COLOR_YUV420p2RGB)
        return ret, bgr


# if __name__ == "__main__":
#
#     output = Popen(['./sdlexample',
#         '-a', '46113352',
#         #'-s', '1_MX4xMDB-fjE1MjU1NTY4MDQ2MjF-WG9JblBDeDI2UFlIRlhyeWNwMjZCdHRxfn4',
#         '-t', '9b4dfb5f819424cf7c8924ee649e39a4ce97290c',
#         #'-d', 'client'
#         ], stdout=PIPE)
#
#     size = (480, 640)
#     cap = VideoCaptureYUV(output.stdout, size)
#
#     while 1:
#         ret, frame = cap.read()
#         if ret:
#             cv2.imshow("frame", frame)
#             cv2.waitKey(30)
#         else:
#             break
