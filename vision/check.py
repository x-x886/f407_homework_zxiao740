import cv2
img = cv2.imread("test.png")
print("图片的高度是", img.shape[0])
print("图片的宽度是", img.shape[1])