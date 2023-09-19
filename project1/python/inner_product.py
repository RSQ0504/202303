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
    w = param["w"].T
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
        #"data": np.zeros((n,k))
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
    #param_grad['b'] = np.zeros_like(param['b'])
    #param_grad['w'] = np.zeros_like(param['w'])
    #input_od = None

    last_diff = output["diff"]
    data = input_data["data"]
    batch_size = input_data["batch_size"]
    input_od = np.zeros_like(data)
    
    diff_b = np.ones((batch_size,1))
    diff_h = param["w"].T
    param_grad['b'] = np.matmul(last_diff,diff_b)

    for batch in range(batch_size):
        diff_w = np.tile(data[:,batch],(last_diff.shape[0],1)).T
        print(diff_w.shape)
        quit()
        # Done
        input_od[:,batch] = np.matmul(last_diff[:,batch],diff_h)

    return param_grad, input_od