Xephyr -br -ac -noreset -screen 800x600 :1 &
./build.sh
export DISPLAY=:1
gdb dwm
