import cv2

im = cv2.imread("Models/Ground/ground.ppm")

im = cv2.resize(im,(1600,1600),interpolation = cv2.INTER_AREA)

cv2.imwrite("Models/Ground/ground.jpg",im)