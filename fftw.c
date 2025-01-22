#include <pulse/simple.h>
#include <pulse/error.h>
#include <ncurses.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SAMPLE_RATE 44100
#define CHANNELS 1
#define BUFFER_SIZE 64


void draw_visualizer(int *amplitudes, int size, int max_height) {
    clear();//clear terminal screen
    attron(A_STANDOUT);//Make the background visible
    for (int i = 0; i < size; i++) {//go through array of amplitudes and assign a height value based on it
        int height = amplitudes[i] * max_height / 100;
	for (int j = 0; j < height; j++) {//make bars
            mvprintw(max_height - j, i, " ");
        }
    }
    attroff(A_STANDOUT);//reset standout before next frame
    refresh();//duh
}

int main() {
    // PulseAudio setup
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = SAMPLE_RATE,
        .channels = CHANNELS
    };

    int error;
    pa_simple *pulse = pa_simple_new(NULL, "AudioVisualizer", PA_STREAM_RECORD, NULL, "audio", &ss, NULL, NULL, &error);
    if (!pulse) {//check for pulseaudio
        fprintf(stderr, "PulseAudio error: %s\n", pa_strerror(error));
        return 1;
    }

    // Ncurses setup
    initscr();//init screen
    noecho();//no command echo
    curs_set(FALSE);
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);//get terminal window size

    int amplitudes[max_x];//make max width the terminal size
    for (int i = 0; i < max_x; i++) amplitudes[i] = 0;//set all amp to 0

    // Main loop
    int16_t buffer[BUFFER_SIZE];
    while (1) {
        if (pa_simple_read(pulse, buffer, sizeof(buffer), &error) < 0) {//error
            fprintf(stderr, "PulseAudio error: %s\n", pa_strerror(error));
            break;
        }

        // Calculate amplitudes
        for (int i = 0; i < max_x; i++) {
            amplitudes[i] = abs(buffer[i % (BUFFER_SIZE / CHANNELS)]) / 256;
        }

        draw_visualizer(amplitudes, max_x, max_y - 1);//call to the draw
    }

    // Cleanup
    pa_simple_free(pulse);
    endwin();

    return 0;
}
