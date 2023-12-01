import numpy as np
import cv2
import tqdm
import os
import matplotlib.pyplot as plt

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

    P_inverse = np.linalg.inv(I0["P"][:,:-1]) 
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
    #print(I0["P"].shape,X.shape)
    projected_coords_I0 = I0["P"] @ X
    projected_coords_I1 = I1["P"] @ X
    #print(I0["mat"].shape)
    
    C0 = np.zeros((num_points, 3))
    C1 = np.zeros((num_points, 3))
    
    for i in range(num_points):
        x0, y0 = projected_coords_I0[:2, i] / projected_coords_I0[2, i]
        x1, y1 = projected_coords_I1[:2, i] / projected_coords_I1[2, i]
        try:
            C0[i] = I0["mat"][int(y0), int(x0)]
        except Exception as e:
            C0[i] = [0,0,0]
            # print(X[:,i])
            # print(projected_coords_I0[:, i])
            # print(y0,x0)
            
        try:
            C1[i] = I1["mat"][int(y1),int(x1)]
        except Exception as e:
            C1[i] = [0,0,0]
            # print(X[:,i])
            # print(projected_coords_I1[:, i])
            # print(y1,x1)
        
    return NormalizedCrossCorrelation(C0, C1)

def DepthmapAlgorithm(I0, I1, I2, I3, min_depth, max_depth, depth_step, S=5, consistency_threshold=0.7):
    height, width, _ = I0["mat"].shape
    best_depthmap = np.zeros((height, width))
    
    for y in tqdm.tqdm(range(height)):
        for x in range(width):
            if np.all(I0["mat"][y, x] < [30, 30, 30]):
                continue

            best_consistency_score = -np.inf
            best_depth = None

            for d in np.arange(min_depth, max_depth, depth_step):
                # Compute 3D coordinates using Get3dCoord
                X = [] 
                for qx in range(max(0, x - S//2),min(width, x + S//2 + 1)): 
                    for qy in range(max(0, y - S//2), min(height, y + S//2 + 1)):
                        #print(Get3dCoord((qx, qy), I0, d).shape)
                        #print(Get3dCoord((qx, qy), I0, d))
                        # print(qx,qy)
                        # print(Get3dCoord((qx, qy), I0, d))
                        if X == []:
                            X = Get3dCoord((qx, qy), I0, d)
                        else:
                            X = np.column_stack((X,Get3dCoord((qx, qy), I0, d)))

                score01 = ComputeConsistency(I0, I1, X)
                score02 = ComputeConsistency(I0, I2, X)
                score03 = ComputeConsistency(I0, I3, X)

                avg_consistency_score = np.mean([score01, score02, score03])

                # Update best depth if the consistency score is higher
                if avg_consistency_score > best_consistency_score:
                    best_consistency_score = avg_consistency_score
                    best_depth = d

            # Set the depth with the best consistency score for the pixel
            if best_consistency_score >= consistency_threshold:
                best_depthmap[y, x] = best_depth

    return best_depthmap

if __name__ == "__main__":
    result = get_camera_parameters("../data/templeR_par.txt")
    num_ims = len(result)
    images = []
    for index, img in enumerate(result):
        I = {}
        temp_img = cv2.imread(os.path.join("../data",img))
        I["mat"] = cv2.cvtColor(temp_img, cv2.COLOR_BGR2RGB)
        I["P"] = result[img]["P"]
        images.append(I)
    min_point = np.array([-0.023121, -0.038009, -0.091940])
    max_point = np.array([0.078626, 0.121636, -0.017395])

    corners_3d = np.array([
        [min_point[0], min_point[1], min_point[2]],
        [min_point[0], min_point[1], max_point[2]],
        [min_point[0], max_point[1], min_point[2]],
        [min_point[0], max_point[1], max_point[2]],
        [max_point[0], min_point[1], min_point[2]],
        [max_point[0], min_point[1], max_point[2]],
        [max_point[0], max_point[1], min_point[2]],
        [max_point[0], max_point[1], max_point[2]],
    ])

    projected_points = np.dot(images[0]["P"], np.column_stack((corners_3d, np.ones((8, 1)))).T)
    depth_values = projected_points[-1, :]
    projected = np.zeros((2,projected_points.shape[1]))
    for i in range(projected_points.shape[1]):
        projected[:,i] = projected_points[:2, i] / projected_points[2, i]
        print(projected[:,i])
        
    color = (255, 0, 0)
    radius = 5
    thickness = -1
    for i in range(projected.shape[1]):
        point_coordinates = (int(projected[0, i]), int(projected[1, i]))
        result_img = cv2.circle(images[0]["mat"], point_coordinates, radius, color, thickness)

    plt.imshow(result_img)
    plt.title('Image with Points')
    plt.show()

    min_depth = np.min(depth_values)
    max_depth = np.max(depth_values)

    depth_step = (max_depth-min_depth)/10
    d = DepthmapAlgorithm(images[0], images[1], images[2], images[3], min_depth, max_depth, depth_step, S=5, consistency_threshold=0.7)
    
    gray_image = cv2.cvtColor(images[0]["mat"] , cv2.COLOR_RGB2GRAY)
    plt.figure()
    plt.imshow(d * (gray_image > 40), cmap='gray')
    plt.axis('image')
    plt.title('Depth Map')
    plt.savefig('../results/3_5.png', dpi=300)