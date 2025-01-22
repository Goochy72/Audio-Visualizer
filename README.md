# Audio-Visualizer
Basic C Based Terminal Audio Visualizer
"INSTALLATION" FOR DEBIAN/UBUNTU
Run this command:
sudo apt install libpulse-dev libncurses5-dev build-essential pulseaudio
Navigate to the directory where you have the 'fftw.c' file
Run these commands:
gcc -o fftw fftw.c -lpulse-simple -lpulse -lncurses -lm
./fftw
Play audio and it should start working!!
For education only, this was just a little project I made for fun/learning more about C, the NCurses library and terminal GUI apps!!
I hope you find this at least a little bit cool because I sure do!
Thank you for checking out my basic C - based Terminal Audio Visualizer and my first github push!!!
