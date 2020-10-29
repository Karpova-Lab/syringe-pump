from moviepy.editor import *
from sys import argv

script,movieFile = argv

# clip = (VideoFileClip(movieFile)).fadeout(1,final_color=[255,255,255])
clip = (VideoFileClip(movieFile))
clip_resized = clip.resize(height=600) # make the height 360px ( According to moviePy documenation The width is then computed so that the width/height ratio is conserved.)
clip_resized.write_gif(movieFile[:-3]+"gif",fps = 20)
