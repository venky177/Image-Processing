import imgproc
from imgproc import *

# also import the maths module for the square root function
import math
import cv2
import numpy
# open a webcam to take pictures
#camera = Camera(160, 120)

# Open a viewer window to display images
#viewer = Viewer(160, 120, "The first step")

# grab a couple of frames, just to flush the camera
#camera.grabImage()
#camera.grabImage()

# take a picture from the camera
#img = camera.grabImage()

img=cv2.imread("xyy.jpg",1)
size=img.shape
width=size[0]
height=size[1]
#viewer.diplayImage(img)
#waitTime(5000)
# create an empty image to show the edges
#img_edge = Image(width, height)
#new_edge = Image(width, height)
img_edge=cv2.imread("xyy.jpg",1)
new_edge=cv2.imread("xyy.jpg",1)

# display the image in the viewer

i=0
# iterate over each pixel in the image
for x in range(1, 480 - 1):
	for y in range(1, 640 - 1):
                # initialise Gx to 0 and Gy to 0 for every pixel
                Gx = 0
                Gy = 0
		i=i+1
		print i

                # top left pixel
                r= img.item(x - 1, y - 1 ,0)
                g= img.item(x - 1, y - 1 ,1)
                b= img.item(x - 1, y - 1 ,2)
                # intensity ranges from 0 to 765 (255 * 3)
                intensity = (r + g + b)
                # accumulate the value into Gx, and Gy
                Gx += -intensity
                Gy += -intensity


                # now we do the same for the remaining pixels, left to right, top to bottom


                # remaining left column
                r= img.item(x - 1, y ,0)
                g= img.item(x - 1, y ,1)
                b= img.item(x - 1, y ,2)
                Gx += -2 * (r + g + b)

                r= img.item(x - 1, y + 1 ,0)
                g= img.item(x - 1, y + 1 ,1)
                b= img.item(x - 1, y + 1 ,2)
                Gx += -(r + g + b)
                Gy += (r + g + b)


                # middle pixels
                r= img.item(x, y - 1 ,0)
                g= img.item(x, y - 1 ,1)
                b= img.item(x, y - 1 ,2)
                Gy += -2 * (r + g + b)

                r= img.item(x, y + 1 ,0)
                g= img.item(x, y + 1 ,1)
                b= img.item(x, y + 1 ,2)
                Gy += 2 * (r + g + b)


                # right column
                r= img.item(x + 1, y - 1 ,0)
                g= img.item(x + 1, y - 1 ,1)
                b= img.item(x + 1, y - 1 ,2)
                Gx += (r + g + b)
                Gy += -(r + g + b)

                r= img.item(x + 1, y ,0)
                g= img.item(x + 1, y ,1)
                b= img.item(x + 1, y ,2)
                Gx += 2 * (r + g + b)

                r= img.item(x + 1, y + 1 ,0)
                g= img.item(x + 1, y + 1 ,1)
                b= img.item(x + 1, y + 1 ,2)
                Gx += (r + g + b)
                Gy += (r + g + b)



		# calculate the length of the gradient
		length = math.sqrt((Gx * Gx) + (Gy * Gy))

		# normalise the length of gradient to the range 0 to 255
		length = length / 4328 * 255

		# convert the length to an integer
		length = int(length)

		# draw the length in the edge image
                img_edge.itemset((x, y, 0),length)
                img_edge.itemset((x, y, 1),length)
                img_edge.itemset((x, y, 2),length)

#		img_edge.itemset[x, y] = length, length, length


# display the edge image
new_edge=img_edge
cv2.imwrite("lul.jpg", img_edge)
# delay for 5000 milliseconds to give us time to see the changes, then exi


# end of the script
