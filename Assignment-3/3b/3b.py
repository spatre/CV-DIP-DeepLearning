import cv2
import matplotlib.pyplot as plt


ferrari1BGR = cv2.imread('ferrari1.jpg', cv2.IMREAD_COLOR)
ferrari1RGB = cv2.cvtColor(ferrari1BGR, cv2.COLOR_BGR2RGB)
ferrari1gray = cv2.cvtColor(ferrari1RGB, cv2.COLOR_BGR2GRAY)
plt.imshow(ferrari1RGB)
plt.show()

sift = cv2.xfeatures2d.SIFT_create()
keypoints_x_sift, featuredesc_x_sift = sift.detectAndCompute(ferrari1RGB, None)

ferrari1_RGB_keypoints = cv2.drawKeypoints(ferrari1RGB, keypoints_x_sift, ferrari1RGB.copy())
plt.imshow(ferrari1_RGB_keypoints)
plt.show()

surf = cv2.xfeatures2d.SURF_create()
keypoints_3_surf, featuredesc_3_surf = surf.detectAndCompute(ferrari1RGB, None)

ferrari1_RGB_keypoints_surf = cv2.drawKeypoints(ferrari1RGB, keypoints_3_surf, ferrari1RGB.copy())
plt.imshow(ferrari1_RGB_keypoints_surf)
plt.show()
surf = cv2.xfeatures2d.SURF_create(800)
keypoints_3_surf, featuredesc_3_surf = surf.detectAndCompute(ferrari1RGB, None)


ferrari1_RGB_keypoints_surf = cv2.drawKeypoints(ferrari1RGB, keypoints_3_surf, ferrari1RGB.copy())
plt.imshow(ferrari1_RGB_keypoints_surf)
plt.show()


image_list = ['bumblebee.jpg','Optimus_Prime.jpg','ferrari_2.jpg']

for img in image_list:

    vehicleBGR = cv2.imread(img, cv2.IMREAD_COLOR)
    vehicleRGB = cv2.cvtColor(vehicleBGR, cv2.COLOR_BGR2RGB)
    vehiclegray = cv2.cvtColor(vehicleRGB, cv2.COLOR_BGR2GRAY)
    plt.imshow(vehicleRGB)
    plt.show()

    #Computing and displaying SIFT features##

    keypoints_1_sift, featuredesc_1_sift = sift.detectAndCompute(vehicleRGB, None)
    #To Display the Features
    vehicleRGB_keypoints = cv2.drawKeypoints(vehicleRGB, keypoints_1_sift, vehicleRGB.copy())
    plt.imshow(vehicleRGB_keypoints)
    plt.show()

    #Plotting the features between Ferrari and vehicles using SIFT#

    bruteforce_sift = cv2.BFMatcher(cv2.NORM_L2, crossCheck=True)
    match_sift = bruteforce_sift.match(featuredesc_1_sift, featuredesc_x_sift)

    # Sorting the matches in accordance with their distance.
    match_sift = sorted(match_sift, key = lambda x:x.distance)

    # draw the top X matches
    XMATCH = 75
    siftmatch_TopX = cv2.drawMatches(vehicleRGB, keypoints_1_sift, ferrari1RGB, keypoints_x_sift, match_sift[:XMATCH], ferrari1RGB.copy(), flags=0)

    plt.figure(figsize=(12,6))
    plt.imshow(siftmatch_TopX)
    plt.show()

    #Displaying SURF features#


    keypoints_1_surf, featuredesc_1_surf = surf.detectAndCompute(vehicleRGB, None)


    vehicleRGB_surf_keypoints = cv2.drawKeypoints(vehicleRGB, keypoints_1_surf, vehicleRGB.copy())
    plt.imshow(vehicleRGB_surf_keypoints)
    plt.show()


    # Plotting features between Ferrari and vehicles using the SURF algorithms#


    bruteforce_surf = cv2.BFMatcher(cv2.NORM_L2, crossCheck=True)
    surf_match = bruteforce_surf.match(featuredesc_1_surf, featuredesc_3_surf)

    # Sorting the matches in accordance with their distance.
    surf_match = sorted(surf_match, key = lambda x:x.distance)

    # Top X matches#
    XMATCH = 75
    surfmatch_topX = cv2.drawMatches(vehicleRGB, keypoints_1_surf, ferrari1RGB, keypoints_3_surf, surf_match[:XMATCH], ferrari1RGB.copy(), flags=0)

    plt.figure(figsize=(12,6))
    plt.imshow(surfmatch_topX)
    plt.show()
