from moviepy.editor import *
from sys import argv

script,xlsFile = argv

# clip = (VideoFileClip(xlsFile)).fadeout(1,final_color=[255,255,255])
clip = (VideoFileClip(xlsFile))
clip_resized = clip.resize(height=550) 
clip_resized.write_gif(xlsFile[:-3]+"gif",fps = 20)
