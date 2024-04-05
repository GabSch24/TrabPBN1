import cv2 as cv;

img = cv.imread("/home/gabrielschneider/Downloads/PBN/T1/Bugio8.ppm")
new_img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cv.imshow("a", new_img)
cv.waitKey(0)
