import numpy as np
import matplotlib.pyplot as plt
import cv2
import scipy.io as sio
from PIL import Image
from eightpoint import eightpoint
from epipolarCorrespondence import epipolarCorrespondence
from essentialMatrix import essentialMatrix
from camera2 import camera2
from triangulate import triangulate
from displayEpipolarF import displayEpipolarF
from epipolarMatchGUI import epipolarMatchGUI

# Load images and points
img1 = cv2.imread('../data/im1.png')
img2 = cv2.imread('../data/im2.png')
pts = np.load('../data/someCorresp.npy', allow_pickle=True).tolist()
pts1 = pts['pts1']
pts2 = pts['pts2']
M = pts['M']


# write your code here
R1, t1 = np.eye(3), np.zeros((3, 1))
R2, t2 = np.eye(3), np.zeros((3, 1))

F = eightpoint(pts1, pts2, M)
pts2 = epipolarCorrespondence(img1, img2, F, pts1)
intrinsics = np.load('../data/intrinsics.npy', allow_pickle=True).tolist()
k1 = intrinsics['K1']
k2 = intrinsics['K2']

E = essentialMatrix(F, k1, k2)
print(E)

# save extrinsic parameters for dense reconstruction
np.save('../results/extrinsics', {'R1': R1, 't1': t1, 'R2': R2, 't2': t2})
