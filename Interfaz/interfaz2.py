from skimage import io
import matplotlib.pyplot as plt
image = io.imread("Colombia.png")
plt.imshow(image,vmin=0,vmax=1)
