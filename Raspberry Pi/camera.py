from subprocess import call

def takePicture():
    call(["fswebcam", "--greyscale", "--no-banner", "image.jpg"])
