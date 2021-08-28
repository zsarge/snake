echo "run the following in the directory you want to convert to video:"

echo "ffmpeg -r 10 -i %d.ppm -vcodec libx264 -crf 25 -pix_fmt yuv420p out.mp4"
