import cv2

im = cv2.imread("Models/Hedge/hedge.ppm")

im = cv2.resize(im,(1600,1600),interpolation = cv2.INTER_AREA)

cv2.imwrite("Models/Hedge/hedge.jpg",im)