from PIL import Image
import numpy as np
from pprint import pprint as pp

with open("test.csv",'r') as f:
    lines = f.readlines()
    

lines = [line.strip().split(',') for line in lines]
colors = []
for line in lines:
    colors.append([x.strip() for x in line])
colors = [colors] * 200
#pp(colors)
image = np.array(colors[:1700],dtype=np.uint8)
print(image.shape)
img = Image.fromarray(image,'RGB')
print(img.size)
img.save('test.bmp')
