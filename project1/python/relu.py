import numpy as np

def relu_forward(input_data):
    output = {
        'height': input_data['height'],
        'width': input_data['width'],
        'channel': input_data['channel'],
        'batch_size': input_data['batch_size'],
    }

    ###### Fill in the code here ######
    # Replace the following line with your implementation.
    output['data'] = input_data['data']
    output["data"][output["data"]<0]=0

    return output

def relu_backward(output, input_data, layer):
    ###### Fill in the code here ######
    # Replace the following line with your implementation.
    input_od = np.zeros_like(input_data['data'])

    return input_od

'''
if __name__=="__main__":
    input_data = {}
    input_data['data'] = np.array([-1, -4, 0, 2, 3, 4, 5, -6])
    input_data['width'] = 5
    input_data['height'] = 5
    input_data['channel'] = 3
    input_data['batch_size'] = 4
    relu_forward(input_data)
'''