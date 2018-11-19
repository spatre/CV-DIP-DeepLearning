import cv2
import matplotlib.pyplot as plt


image_list = ['bumblebee.jpg','Optimus_Prime.jpg']

for img in image_list:
    # SIFT and SURF Feature Calculation#
    vehicleclr = cv2.imread(img, cv2.IMREAD_COLOR)
    vehicle_gray = cv2.cvtColor(vehicleclr, cv2.COLOR_BGR2GRAY)

    vehicleRGB = cv2.cvtColor(vehicleclr, cv2.COLOR_BGR2RGB)
    plt.imshow(vehicleRGB)
    plt.show()

    #Computing SIFT Features from bumblebee Car and Optimus_Prime truck#

    sift = cv2.xfeatures2d.SIFT_create()
    keypoints_1_sift, featuredesc_1_sift = sift.detectAndCompute(vehicleRGB, None)

    vehicle = cv2.drawKeypoints(vehicleRGB, keypoints_1_sift, vehicleRGB.copy())
    plt.imshow(vehicle)
    plt.show()
    #SIFT Features Computation is complete#

    # Computing SURF Features from bumblebee Car and Optimus Prime truck#

    surf = cv2.xfeatures2d.SURF_create()
    keypoints_1_surf, featuredesc_1_surf = surf.detectAndCompute(vehicleRGB, None)

    vehicle = cv2.drawKeypoints(vehicleRGB, keypoints_1_surf, vehicleRGB.copy())
    plt.imshow(vehicle)
    plt.show()

    # SURF Features Computation is complete#