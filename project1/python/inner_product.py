import numpy as np


def inner_product_forward(input, layer, param):
    """
    Forward pass of inner product layer.

    Parameters:
    - input (dict): Contains the input data.
    - layer (dict): Contains the configuration for the inner product layer.
    - param (dict): Contains the weights and biases for the inner product layer.
    """

    d, k = input["data"].shape
    n = param["w"].shape[1]
    
    ###### Fill in the code here ######
    b_row = param["b"].shape[1]
    w_row = param["w"].shape[0]
    
    assert n == d
    assert w_row == b_row
    
    w = param["w"]
    b = np.squeeze(param["b"])
    result = []
    for batch_id in range(k):
        x = input['data'][:,batch_id]
        Wx = np.matmul(w,x)
        y = Wx + b
        if result == []:
            result = y
        else:
            result = np.vstack((result,y))
    result = result.T
    # print(result.shape)
    # Initialize output data structure
    output = {
        "height": n,
        "width": 1,
        "channel": 1,
        "batch_size": k,
        "data": result # replace 'data' value with your implementation
    }

    return output


def inner_product_backward(output, input_data, layer, param):
    """
    Backward pass of inner product layer.

    Parameters:
    - output (dict): Contains the output data.
    - input_data (dict): Contains the input data.
    - layer (dict): Contains the configuration for the inner product layer.
    - param (dict): Contains the weights and biases for the inner product layer.
    """
    param_grad = {}
    ###### Fill in the code here ######
    # Replace the following lines with your implementation.
    param_grad['b'] = np.zeros_like(param['b'])
    param_grad['w'] = np.zeros_like(param['w'])
    input_od = None

    return param_grad, input_od