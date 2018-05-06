from lib.processors_noopenmdao import findFaceGetPulse
from lib.interface import plotXY, imshow, waitKey, destroyWindow
from cv2 import moveWindow
import cv2
import argparse
import numpy as np
import datetime
import socket
import sys
from subprocess import Popen, PIPE
import cv2
import struct
from video_listen import VideoCaptureYUV
from firebase import firebase
import threading
import time
import random

class getPulse(object):

    def __init__(self):

        self.firebase = firebase.FirebaseApplication('https://hackhealth-c0852.firebaseio.com', None)
        result = self.firebase.get('/Rooms/room2', None)
        sessionID = result['sessionID']
        tokenID = result['token']

        self.processor = findFaceGetPulse(bpm_limits = [50, 160],
                                          data_spike_limit = 2500.,
                                          face_detector_smoothness = 10.)
        self.bpm_plot = False
        self.plot_title = "Data display - raw signal (top) and PSD (bottom)"

        self.key_controls = {"s": self.toggle_search,
                             "d": self.toggle_display_plot,
                             "c": self.toggle_cam}
        # self.vidcap = cv2.VideoCapture(0)
        output = Popen(['./sdlexample',
                        '-a', '46113352',
                        '-s', sessionID,
                        '-t', tokenID,
                        '-d', 'patient'
                        ], stdout = PIPE)
        size = (480, 640)
        self.vidcap = VideoCaptureYUV(output.stdout, size)

    def toggle_cam(self):
        self.processor.find_faces = True
        self.bpm_plot = False

    def toggle_search(self):
        """
        Toggles a motion lock on the processor's face detection component.

        Locking the forehead location in place significantly improves
        data quality, once a forehead has been sucessfully isolated.
        """
        # state = self.processor.find_faces.toggle()
        state = self.processor.find_faces_toggle()
        print("face detection lock =", not state)

    def toggle_display_plot(self):
        """
        Toggles the data display.
        """
        if self.bpm_plot:
            print("bpm plot disabled")
            self.bpm_plot = False
            destroyWindow(self.plot_title)
        else:
            print("bpm plot enabled")
            if self.processor.find_faces:
                self.toggle_search()
            self.bpm_plot = True
            self.make_bpm_plot()
            moveWindow(self.plot_title, self.w, 0)

    def make_bpm_plot(self):
        """
        Creates and/or updates the data display
        """
        plotXY([[self.processor.times,
                 self.processor.samples],
                [self.processor.freqs,
                 self.processor.fft]],
               labels = [False, True],
               showmax = [False, "bpm"],
               label_ndigits = [0, 0],
               showmax_digits = [0, 1],
               skip = [3, 3],
               name = self.plot_title,
               bg = self.processor.slices[0])

    def key_handler(self):
        """
        Handle keystrokes, as set at the bottom of __init__()

        A plotting or camera frame window must have focus for keypresses to be
        detected.
        """

        self.pressed = waitKey(10) & 255  # wait for keypress for 10 ms
        if self.pressed == 27:  # exit program on 'esc'
            print("Exiting")
            self.vidcap.release()
            cv2.destroyAllWindows()
            sys.exit()

        for key in self.key_controls.keys():
            if chr(self.pressed) == key:
                self.key_controls[key]()

    def main_loop(self):
        """
        Single iteration of the application's main loop.
        """
        # Get current image frame from the camera
        ret, frame = self.vidcap.read()
        #self.h, self.w, _c = frame.shape
        self.h, self.w, _c = (480, 640, 3)

        # set current image frame to the processor's input
        self.processor.frame_in = frame
        # process the image frame to perform all needed analysis
        bpm = self.processor.run(self.vidcap)
        # collect the output frame for display
        output_frame = self.processor.frame_out

        # show the processed/annotated output frame
        imshow("Processed", output_frame)

        # create and/or update the raw data display if needed
        if self.bpm_plot:
            self.make_bpm_plot()

        # handle any key presses
        self.key_handler()

        return bpm

if __name__ == "__main__":

    App = getPulse()
    start_time = time.process_time()
    while True:
        bpm = App.main_loop()

        elapsed_time = time.process_time() - start_time

        if elapsed_time >= 3:
            start_time = time.process_time()
            firebase_application = firebase.FirebaseApplication('https://hackhealth-c0852.firebaseio.com', None)
            print(bpm)
            if bpm is not None:
                heartrateupdate = firebase_application.put('/Rooms/room2', 'heartRate', bpm)
                breathingrate = firebase_application.put('/Rooms/room2', 'breathingRate', random.randint(12,20))


            # cap = cv2.VideoCapture(0)
#
# while(True):
#     # Capture frame-by-frame
#     ret, frame = cap.read()
#
#     # Our operations on the frame come here
#     gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
#
#     # Display the resulting frame
#     cv2.imshow('frame',gray)
#     if cv2.waitKey(1) & 0xFF == ord('q'):
#         break
#
# # When everything done, release the capture
# cap.release()
# cv2.destroyAllWindows()