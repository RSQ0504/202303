import numpy as np

def triangulate(P1, pts1, P2, pts2):
    """
    Estimate the 3D positions of points from 2d correspondence
    Args:
        P1:     projection matrix with shape 3 x 4 for image 1
        pts1:   coordinates of points with shape N x 2 on image 1
        P2:     projection matrix with shape 3 x 4 for image 2
        pts2:   coordinates of points with shape N x 2 on image 2

    Returns:
        Pts3d:  coordinates of 3D points with shape N x 3
    """
    num_points = pts1.shape[0]
    pts3d = np.zeros((num_points, 3))

    for i in range(num_points):
        pt1 = np.array([pts1[i, 0], pts1[i, 1], 1])
        pt2 = np.array([pts2[i, 0], pts2[i, 1], 1])

        A = np.vstack((pt1[0] * P1[2] - P1[0],
                       pt1[1] * P1[2] - P1[1],
                       pt2[0] * P2[2] - P2[0],
                       pt2[1] * P2[2] - P2[1]))

        _, _, V = np.linalg.svd(A)

        X_homogeneous = V[-1, :4]
        X_homogeneous /= X_homogeneous[3]

        pts3d[i] = X_homogeneous[:3]
    return pts3d
