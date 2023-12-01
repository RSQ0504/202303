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

def Get3dCoord(q, I0, d):
    x, y = q

    q_new = np.array([d*x, d*y, d])

    P_inverse = np.linalg.pinv(I0["P"]) 
    p_3d = P_inverse @ (q_new - I0["P"][:,-1])

    return p_3d

def NormalizedCrossCorrelation(C0, C1):
    avg_red_C0 = np.mean(C0[:, 0])
    avg_green_C0 = np.mean(C0[:, 1])
    avg_blue_C0 = np.mean(C0[:, 2])

    C0 -= np.array([avg_red_C0, avg_green_C0, avg_blue_C0])

    l2_norm_C0 = np.linalg.norm(C0)

    C0 /= l2_norm_C0

    avg_red_C1 = np.mean(C1[:, 0])
    avg_green_C1 = np.mean(C1[:, 1])
    avg_blue_C1 = np.mean(C1[:, 2])

    C1 -= np.array([avg_red_C1, avg_green_C1, avg_blue_C1])
    
    l2_norm_C1 = np.linalg.norm(C1)
    
    C1 /= l2_norm_C1

    cross_correlation = np.dot(C0.flatten(), C1.flatten())

    return cross_correlation

def ComputeConsistency(I0, I1, X):
    num_points = X.shape[1]

    X = np.vstack((X, np.ones((1, num_points))))
    
    projected_coords_I0 = I0["P"] @ X

    C0 = np.zeros((num_points, 3))
    for i in range(num_points):
        x, y = projected_coords_I0[:2, i] / projected_coords_I0[2, i]
        C0[i] = I0["mat"][x,y]

    projected_coords_I1 = I1["P"] @ X

    C1 = np.zeros((num_points, 3))
    for i in range(num_points):
        x, y = projected_coords_I1[:2, i] / projected_coords_I1[2, i]
        C1[i] = I1["mat"][x,y]
        
    return NormalizedCrossCorrelation(C0, C1)