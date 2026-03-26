#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

std::vector<int> getHeightWidth(string WHstring) {
    std::vector<int> dimentions;
    stringstream ss(WHstring);
    string temp;
    char del = ' ';
    while (getline(ss, temp, del)) {
        int val = stoi(temp);
	dimentions.push_back(val);
    }
    return dimentions;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "usagage: "  << argv[0] << " file.ppm" << std::endl;
        return 1;
    }
    string filePath = argv[1];

    string L1Text; // either p3 or p6 - ignored
    string L2Text; // some comment - ignored
    string L3Text; // width heigh
    string L4Text; // max colour value - ignored

    ifstream file(filePath, ios::binary);
    getline(file, L1Text);
    getline(file, L2Text);
    getline(file, L3Text);
    getline(file, L4Text);

    std::vector<int> dimentions = getHeightWidth(L3Text);
    int height = dimentions[1];
    int width = dimentions[0];
    const char *title = "PV";

    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,height, 0);
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char redchr = file.get();
            char greenchr = file.get();
            char bluechr = file.get();
            Uint8 Red = redchr;
            Uint8 Blue = bluechr;
            Uint8 Green = greenchr;
            Uint32 colour = SDL_MapRGB(window_surface->format, Red, Blue, Green);
            SDL_Rect pixel = (SDL_Rect){x,y,1,1};
            SDL_FillRect(window_surface, &pixel, colour);
        }
    }
    SDL_UpdateWindowSurface(window);
    int appRunning = 1;
    while (appRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                appRunning = 0;
            }

        }
        SDL_Delay(100);
    }
    return 0;
}
 
