#!/bin/env sh

echo "run the following in the frames/* directory you want to convert to video:"

echo "convert -delay 20 *ppm output.gif"

convert -delay 20 frames/*/*ppm frames/output.gif
