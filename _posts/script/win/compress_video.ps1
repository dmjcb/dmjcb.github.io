# 不使用硬件加速
# ffmpeg -i $args[0] -threads 16 -preset ultrafast -c:v libx265 -crf 28 $args[1]

ffmpeg -hwaccel cuvid -hwaccel_output_format cuda -i $args[0]  -c:v hevc_nvenc -map_metadata 0 -preset slow -cq 33 $args[1]