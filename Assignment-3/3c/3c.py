import cv2
from scipy.stats import chisquare as cs

#Ferrari_2 data#
ferrari2BGR = cv2.imread('ferrari_2.jpg', cv2.IMREAD_COLOR)
ferrari2RGB = cv2.cvtColor(ferrari2BGR, cv2.COLOR_BGR2RGB)
ferrari2GRAY = cv2.cvtColor(ferrari2RGB, cv2.COLOR_BGR2GRAY)


sift_ferrari2 = cv2.xfeatures2d.SIFT_create()

keypoints_ferrari2_sift, featuredesc_ferrari2_sift = sift_ferrari2.detectAndCompute(ferrari2RGB, None)

dicsize = 8
bowtrain = cv2.BOWKMeansTrainer(dicsize)

image_list = ['bumblebee.jpg','Optimus_Prime.jpg','ferrari1.jpg']

trainhist = []
for img in image_list:
    vehicleBGR = cv2.imread(img, cv2.IMREAD_COLOR)
    vehicleRGB = cv2.cvtColor(vehicleBGR, cv2.COLOR_BGR2RGB)
    vehicleGRAY = cv2.cvtColor(vehicleRGB, cv2.COLOR_BGR2GRAY)


    ## Computing and displaying SIFT features for the 3 input images


    keypoints_vehicle_sift, featuredesc_vehicle_sift = sift_ferrari2.detectAndCompute(vehicleRGB, None)
    ## Bag of Visual Words


    ## adding all the descriptors to BOW trainer
    bowtrain.add(featuredesc_vehicle_sift)

    ## clustering and creating vocabulary
    vocab = bowtrain.cluster()

    ## flann matcher for BOW extractor
    flann = dict(algorithm = 1, trees = 5)
    match = cv2.FlannBasedMatcher(flann, {})

    ## Used for computing descriptors and features during extraction and detection
    ext = cv2.xfeatures2d.SIFT_create()
    det = cv2.xfeatures2d.SIFT_create() ## 6

    ## BOVW feature extractor
    extbow = cv2.BOWImgDescriptorExtractor(ext, match)
    ## Setting up vocabulary
    extbow.setVocabulary(vocab)



    imag = vehicleGRAY
    histsift = cv2.xfeatures2d.SIFT_create()
    kp = histsift.detect(imag)
    vehiclehistvals = extbow.compute(imag, kp)
    trainhist.extend(vehiclehistvals)




## Test images Histogram values
testhist =[]
imag = ferrari2GRAY
histsift = cv2.xfeatures2d.SIFT_create()
kp = histsift.detect(imag)
ferrari2histvals =extbow.compute(imag, kp)
testhist.extend(ferrari2histvals)




BumbleBee = cs(testhist[0], trainhist[0])
OptimusPrime= cs(testhist[0], trainhist[1])
Ferrari1 = cs(testhist[0], trainhist[2])

#Printing the final output
print("The Chi-square distance of Ferrari2 with other Vehicles are as Follows:")
print("BumbleBee",BumbleBee)
print("OptimusPrime",OptimusPrime)
print("Ferrari1",Ferrari1)