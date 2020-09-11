from PIL import Image

name = "result_14D.raw"
rawData = open(name,'rb').read()
imgsize = (600, 450)
img = Image.frombytes('L', imgsize, rawData, 'raw')
img.save("result_14D.jpg")

name = "result_3D.raw"
rawData = open(name,'rb').read()
imgsize = (600, 450)
img = Image.frombytes('L', imgsize, rawData, 'raw')
img.save("result_3D.jpg")

name = "comp.raw"
rawData = open(name,'rb').read()
imgsize = (600, 450)
img = Image.frombytes('L', imgsize, rawData, 'raw')
img.save("comp.jpg")
