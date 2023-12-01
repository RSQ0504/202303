import numpy as np

def get_camera_parameters(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    result = {}
    for line in lines:
        values = line.strip().split()

        img_name = values[0]

        K = np.array(values[1:10], dtype=float).reshape((3, 3))

        R = np.array(values[10:19], dtype=float).reshape((3, 3))

        t = np.array(values[19:22], dtype=float)

        result[img_name] = {
            'K': K,
            'R': R,
            't': t,
            'Rt': np.column_stack((R, t)),
            'P': np.dot(K,np.column_stack((R, t)))
        }

    return result
