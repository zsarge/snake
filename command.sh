echo "run the following in the directory you want to convert to video:"

echo "ffmpeg -r 10 -i %d.ppm -vcodec libx264 -crf 25 -pix_fmt yuv420p out.mp4"

# ffmpeg -sws_flags neighbor -r 10 -s 70x70 -start_number 1 -i %d.ppm -vframes 1000 -vcodec libx264 -crf 0 -pix_fmt yuv420p test.mp4
