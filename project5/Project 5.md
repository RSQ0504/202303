# Project 5 

## Rongsheng Qian 301449387

## 3.1 Sparse reconstruction

### 3.1.1 Implement the eight point algorithm (2 pts)

In your write-up, please include your recovered F and the visualization of some epipolar lines like the figure below

```python
F =[[ 3.37554374e-09 -5.77488650e-08 -1.44640637e-05]
 [-1.29390178e-07 -1.48285427e-09  1.12458135e-03]
 [ 3.25298454e-05 -1.08034741e-03 -4.55969209e-03]]
```

![Screenshot 2023-12-04 at 9.35.30 AM](/Users/davidqian/Desktop/Cache/Screenshot 2023-12-04 at 9.35.30 AM.png)

### 3.1.2 Find epipolar correspondences (2 pts)

In your write-up, include a screenshot of epipolarMatchGui running with your implementation of epipolarCorrespondence (like the figure below). Mention the similarity metric you decided to use. Also comment on any cases where your matching algorithm consistently fails, and why you might think this is.

**The similarity metric you decided to use is NCC. It is robust to Lighting and Shading Variations and can find instances of a smaller template within a larger image. **

**However it is sensitive to noise in the data. In the following instance, the orange/red point on the pillar in image 1 is matched on the other pilllar in image 2. The details of the pillars are similar. In this case, the matching results are easily confused or affected by noise.**

![Screenshot 2023-12-04 at 9.42.16 AM](/Users/davidqian/Desktop/Cache/Screenshot 2023-12-04 at 9.42.16 AM.png)

### 3.1.3 Write a function to compute the essential matrix (2 pts)

In your write-up, write your estimated E matrix for the temple image pair we provided.

```python
E = [[ 0.00780296 -0.13397612 -0.04211513]
 [-0.30018241 -0.00345263  1.6557511 ]
 [ 0.00244448 -1.67570084 -0.00192676]]
```



### 3.1.4 Implement triangulation (2 pts)

In your write-up, describe how you determined which extrinsic matrices are correct. Report your re-projection error using pts1, pts2 from someCorresp.npy. If implemented correctly, the re-projection error should be less than 1 pixel.

**I determined which extrinsic matrices are correct by counting the 3D points which are in front of both cameras (positive depth) in each condition. I picked the one for which most of the 3D points are in front of both cameras (positive depth).**

```python
for i in range(P2_possible_e.shape[-1]):
    temp_p2_e = P2_possible_e[:,:,i]
    temp_P2 = np.dot(k2,temp_p2_e)
    points = triangulate(P1, pts1, temp_P2, pts2)
    front_count = 0
    for point in points:
        if point[-1]>0:
            front_count += 1
    if front_count > best:
        best = front_count
        P2 = temp_P2
        R2 = temp_p2_e[:,:-1]
        t2 = temp_p2_e[:,-1].reshape(-1,1)
        result_points = points
```

**re-projection error** 

```shell
img1:
re-projection error: 0.5527583965853167
img2:
re-projection error: 0.5536822966377606
mean error
re-projection error: 0.5532203466115386
```



### 3.1.5 Write a test script that uses templeCoords (2 pts)

In your write-up, include 3 images of your final reconstruction of the templeCoords points, from different angles. Like the figure below.

<img src="/Users/davidqian/Desktop/Cache/Screenshot 2023-12-04 at 9.54.58 AM.png" alt="Screenshot 2023-12-04 at 9.54.58 AM" style="zoom: 63%;" /><img src="/Users/davidqian/Desktop/Cache/Screenshot 2023-12-04 at 9.55.12 AM.png" alt="Screenshot 2023-12-04 at 9.55.12 AM" style="zoom:63%;" />

<img src="/Users/davidqian/Desktop/Cache/Screenshot 2023-12-04 at 9.56.47 AM.png" alt="Screenshot 2023-12-04 at 9.56.47 AM" style="zoom:67%;" />

## 3.2 Dense reconstruction

### 3.2.1 Image rectification (2 pts)

In your write-up, include a screenshot of the result of running testRectify.py on temple images. The results should show some epipolar lines that are perfectly horizontal, with corresponding points in both images lying on the same line.	

![Screenshot 2023-12-04 at 10.05.10 AM](/Users/davidqian/Desktop/Cache/Screenshot 2023-12-04 at 10.05.10 AM.png)

![Screenshot 2023-12-04 at 10.05.13 AM](/Users/davidqian/Desktop/Cache/Screenshot 2023-12-04 at 10.05.13 AM.png)

### 3.2.2 Dense window matching to find per pixel density (2 pts)

<img src="/Users/davidqian/Desktop/CMPT 412/412_Project/project5/results/disparity.png" alt="disparity" style="zoom: 45%;" />

### 3.2.3 Depth map (2 pts)

<img src="/Users/davidqian/Desktop/CMPT 412/412_Project/project5/results/disparity.png" alt="depth" style="zoom: 46%;" /><img src="/Users/davidqian/Desktop/CMPT 412/412_Project/project5/results/depth.png" alt="depth" style="zoom:45%;" />

## 3.3 Pose estimation

### 3.3.1 Estimate camera matrix P (2 pts)

```shell
Reprojected Error with clean 2D points is 0.0000
Pose Error with clean 2D points is 0.0000
------------------------------
Reprojected Error with noisy 2D points is 3.1531
Pose Error with noisy 2D points is 0.0135

Reprojected Error with clean 2D points is 0.0000
Pose Error with clean 2D points is 0.0000
------------------------------
Reprojected Error with noisy 2D points is 2.2296
Pose Error with noisy 2D points is 0.0208

Reprojected Error with clean 2D points is 0.0000
Pose Error with clean 2D points is 0.0000
------------------------------
Reprojected Error with noisy 2D points is 3.2137
Pose Error with noisy 2D points is 2.0240
```

### 3.3.2 Estimate intrinsic/extrinsic parameters (1 pts)

```shell
Intrinsic Error with clean 2D points is 0.0000
Rotation Error with clean 2D points is 0.0000
Translation Error with clean 2D points is 0.0000
------------------------------
Intrinsic Error with noisy 2D points is 0.6822
Rotation Error with noisy 2D points is 0.0755
Translation Error with noisy 2D points is 0.1660

Intrinsic Error with clean 2D points is 0.0000
Rotation Error with clean 2D points is 0.0000
Translation Error with clean 2D points is 0.0000
------------------------------
Intrinsic Error with noisy 2D points is 0.8108
Rotation Error with noisy 2D points is 0.0349
Translation Error with noisy 2D points is 0.3636

Intrinsic Error with clean 2D points is 0.0000
Rotation Error with clean 2D points is 0.0000
Translation Error with clean 2D points is 0.0000
------------------------------
Intrinsic Error with noisy 2D points is 0.6813
Rotation Error with noisy 2D points is 0.0531
Translation Error with noisy 2D points is 0.1008
```

## 3.4 Multi-view stereo

### 3.4.1 (1 pts)

![3_5_1](/Users/davidqian/Desktop/CMPT 412/412_Project/project5/results/3_5_1.png)

### 3.4.2 (1 pts)

### Here is my image[0] depthmap

![3_5(1)](/Users/davidqian/Desktop/CMPT 412/412_Project/project5/results/3_5(1).png)

### 3.4.3 (1 pts)

![Screenshot 2023-12-04 at 10.12.50 AM](/Users/davidqian/Desktop/Cache/Screenshot 2023-12-04 at 10.12.50 AM.png)

![Screenshot 2023-12-04 at 10.13.04 AM](/Users/davidqian/Desktop/Cache/Screenshot 2023-12-04 at 10.13.04 AM.png)

![Screenshot 2023-12-04 at 10.14.08 AM](/Users/davidqian/Desktop/Cache/Screenshot 2023-12-04 at 10.14.08 AM.png)

![Screenshot 2023-12-04 at 10.14.36 AM](/Users/davidqian/Desktop/Cache/Screenshot 2023-12-04 at 10.14.36 AM.png)