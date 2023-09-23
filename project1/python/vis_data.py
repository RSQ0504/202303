import numpy as np
from utils import get_lenet
from load_mnist import load_mnist
from scipy.io import loadmat
from conv_net import convnet_forward
from init_convnet import init_convnet
import matplotlib.pyplot as plt

# Load the model architecture
layers = get_lenet()
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

# Load data
fullset = False
xtrain, ytrain, xvalidate, yvalidate, xtest, ytest = load_mnist(fullset)
m_train = xtrain.shape[1]

batch_size = 1
layers[0]['batch_size'] = batch_size

img = xtest[:,0]
img = np.reshape(img, (28, 28), order='F')
plt.imshow(img.T, cmap='gray')
plt.show()

output = convnet_forward(params, layers, xtest[:,0:1])
output_1 = np.reshape(output[0]['data'], (28,28), order='F')

##### Fill in your code here to plot the features ######
output_2 = np.reshape(output[1]['data'], (24,24,20), order='F')
features = [output_2[:, :, i].T for i in range(20)]

fig = plt.figure(figsize=(10, 8))

for i in range(1, 4 * 5 + 1):
    ax = fig.add_subplot(4, 5, i)
    ax.imshow(features[i - 1], cmap='gray')

plt.tight_layout()
plt.show()

output_3 = np.reshape(output[2]['data'], (24,24,20), order='F')
features = [output_3[:, :, i].T for i in range(20)]

fig = plt.figure(figsize=(10, 8))

for i in range(1, 4 * 5 + 1):
    ax = fig.add_subplot(4, 5, i)
    ax.imshow(features[i - 1], cmap='gray')

plt.tight_layout()
plt.show()