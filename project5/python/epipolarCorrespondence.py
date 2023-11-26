import numpy as np
import cv2

def epipolarCorrespondence(im1, im2, F, pts1):
    """
    Args:
        im1:    Image 1
        im2:    Image 2
        F:      Fundamental Matrix from im1 to im2
        pts1:   coordinates of points in image 1
    Returns:
        pts2:   coordinates of points in image 2
    """
    window_size = 3
    pts2 = np.zeros_like(pts1)
    
    for i in range(pts1.shape[0]):
        point = np.array([pts1[i, 0], pts1[i, 1], 1])
        #print(point)
        epipolar_line = np.dot(F, point)
        best_score = float('inf')
        best_point = np.zeros(2, dtype=int)
        window = im1[int(pts1[i, 1]) - int(window_size / 2): int(pts1[i, 1]) + int(window_size / 2 + 1),
                    int(pts1[i, 0]) - int(window_size / 2):int(pts1[i, 0]) + int(window_size / 2 + 1)]

        for j in range(int(pts1[i, 1]) - int(window_size / 2), int(pts1[i, 1]) + int(window_size / 2 + 1)):
            x_candidate = int(((-epipolar_line[1] * j - epipolar_line[2]) / epipolar_line[0]))
            temp_window = im2[j - int(window_size / 2):j + int(window_size / 2) + 1, 
                                x_candidate - int(window_size / 2):x_candidate + int(window_size / 2) + 1]
            #print(window.shape,temp_window.shape)
            if window.shape == temp_window.shape:
                ssd_score = np.sum((window - temp_window) ** 2)
                #print(ssd_score)
                if ssd_score < best_score:
                    best_score = ssd_score
                    best_point = np.array([x_candidate, j])
                    #print(best_point)

        pts2[i, :] = best_point

    return pts2

if __name__ == "__main__":
    from eightpoint import eightpoint
    import cv2
    import os

    current_directory = os.path.dirname(os.path.abspath(__file__))
    relative_path = os.path.join('..', 'data', 'im1.png')
    image_path = os.path.abspath(os.path.join(current_directory, relative_path))

    im1 = cv2.imread(image_path)

    relative_path = os.path.join('..', 'data', 'im2.png')
    image_path = os.path.abspath(os.path.join(current_directory, relative_path))
    im2 = cv2.imread(image_path)

    correspondence = np.load('project5/data/someCorresp.npy', allow_pickle=True).item()

    pts1 = correspondence['pts1']
    pts2 = correspondence['pts2']

    M = max(im1.shape[0],im1.shape[1])
    F = eightpoint(pts1, pts2, M)

    pts2 = epipolarCorrespondence(im1, im2, F, pts1)
    print(pts2)