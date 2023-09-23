import cv2
import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import loadmat

from ..python.conv_net import convnet_forward
from ..python.init_convnet import init_convnet
from ..python.utils import get_lenet

path = "../images/"

for file in os.listdir(path):
    if file.split('.')[-1] in  ["png","PNG","JGP","jpg"]:
        image = cv2.imread(os.path.join(path,file),cv2.IMREAD_GRAYSCALE)
        _, binary_image = cv2.threshold(image, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)
        num, label_image = cv2.connectedComponents(binary_image)

        classify_images = np.zeros((28*28,num))
        for index in range(1, num):
            x, y, w, h = cv2.boundingRect((label_image == index).astype(np.uint8))
            # Extract the digit region of interest (ROI)
            crop_image = image[y:y+h, x:x+w]
            resized_image = cv2.resize(crop_image, (28, 28), interpolation=cv2.INTER_LINEAR)
            classify_images[:,index] = resized_image.reshape(-1,1)
            
        layers = get_lenet(num)
        params = init_convnet(layers)

        # Load the network
        data = loadmat('../results/lenet.mat')
        params_raw = data['params']
        for params_idx in range(len(params)):
            raw_w = params_raw[0,params_idx][0,0][0]
            raw_b = params_raw[0,params_idx][0,0][1]
            assert params[params_idx]['w'].shape == raw_w.shape, 'weights do not have the same shape'
            assert params[params_idx]['b'].shape == raw_b.shape, 'biases do not have the same shape'
            params[params_idx]['w'] = raw_w
            params[params_idx]['b'] = raw_b
            
        cptest, P = convnet_forward(params, layers, classify_images, test=True)
        predict = np.argmax(P,axis=0)