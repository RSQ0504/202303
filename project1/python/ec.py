import cv2
import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import loadmat

from conv_net import convnet_forward
from init_convnet import init_convnet
from utils import get_lenet

path = "../images/"
label = {
    "image1.JPG":[1,2,3,4,5,6,7,8,9,0],
    "image2.JPG":[1,2,3,4,5,6,7,8,9,0],
    "image3.png":[6,0,6,2,4],
    "image4.jpg":[7,2,1,0,4,1,4,9,5,9,
                    0,6,9,0,1,5,9,7,3,4,
                    9,6,4,5,4,0,7,4,0,1,
                    3,1,3,4,7,2,7,1,2,1,
                    1,7,4,2,3,5,1,2,4,4],
}
for file in os.listdir(path):
    if file.split('.')[-1] in  ["png","PNG","JPG","jpg"]:
        image = cv2.imread(os.path.join(path,file),cv2.IMREAD_GRAYSCALE)
        _, binary_image = cv2.threshold(image, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)
        num, label_image = cv2.connectedComponents(binary_image)
        
        list_info = []
        for index in range(1, num):
            x, y, w, h = cv2.boundingRect((label_image == index).astype(np.uint8))
            # Extract the digit region of interest (ROI)
            crop_image = image[y:y+h, x:x+w]
            resized_image = cv2.resize(crop_image, (28, 28), interpolation=cv2.INTER_LINEAR)
            cv2.normalize(resized_image, resized_image, 0, 1, cv2.NORM_MINMAX)
            list_info.append((resized_image, (x, y, w, h)))
        
        list_info = sorted(list_info, key=lambda x: x[1][0])
        
        classify_images = np.zeros((28*28,num-1))
        show_images = np.zeros((28,28,num-1))
        for index, info in enumerate(list_info):
            show_images[:,:,index] = info[0]
            classify_images[:,index] = info[0].reshape(-1,)
        
        h, w, batch_size = show_images.shape
    
        num_cols = int(np.ceil(np.sqrt(batch_size)))
        num_rows = int(np.ceil(batch_size / num_cols))
        fig, axes = plt.subplots(num_rows, num_cols, figsize=(8, 8))
        
        if num_rows == 1:
            axes = axes.reshape(1, -1)
        if num_cols == 1:
            axes = axes.reshape(-1, 1)

        for i in range(num_rows):
            for j in range(num_cols):
                index = i * num_cols + j
                if index < batch_size:
                    axes[i, j].imshow(show_images[:,:,index], cmap='gray')
                axes[i, j].axis('off')
        plt.show()
            
        layers = get_lenet(num-1)
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
        print(file)
        print(f"prediict: {predict}")
        print(f"label: {label[file]}")