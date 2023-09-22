import cv2
import os
import numpy as np
from conv_net import convnet_forward
from init_convnet import init_convnet
from scipy.io import loadmat
from utils import get_lenet

if __name__ == "__main__":
    # Load the model architecture
    layers = get_lenet(1)
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

    path = "3.3image/"
    label = {
        "1.png":7,
        "2.png":4,
        "3.png":0,
        "4.png":2,
        "5.png":9
    }
    for file in os.listdir(path):
        if file.split('.')[-1] ==  "png":
            image = cv2.imread(os.path.join(path,file),cv2.IMREAD_GRAYSCALE)
            resized_image = cv2.resize(image, (28, 28))
            image_np = np.array(resized_image)
            image_np = image_np.reshape(-1,1)
            cptest, P = convnet_forward(params, layers, image_np, test=True)
            predict = np.argmax(P,axis=0)
            print(f"predict: {predict}; label: {label[file]}")