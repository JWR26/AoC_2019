#include "day_08.h"

void day_08::print_answers() {
    std::cout << "\n--- Day 8: Space Image Format ---\n\n";

    const int LAYER_SIZE{ 150 };
    // read the file
    std::ifstream input("input\\day_08.txt");
    
    std::string layer(LAYER_SIZE, ' ');
    std::string image(LAYER_SIZE, '2');

    size_t zeros = layer.size();
    size_t part_1 = 0;

    while (input.read(layer.data(), LAYER_SIZE)) {
        // check for fewer zeros
        size_t layer_zeros = std::count(layer.begin(), layer.end(), '0');
        if (layer_zeros < zeros) {
            zeros = layer_zeros;
            part_1 = std::count(layer.begin(), layer.end(), '1') * std::count(layer.begin(), layer.end(), '2');;
        }

        for (size_t i = 0; i < image.size(); ++i) {
            if (image[i] == '2') {
                image[i] = layer[i];
            }
        }
    }


    std::cout << "Part 1: " << zeros << '\n';

    std::cout << "Part 2: " << '\n';

    for (size_t i = 0; i < image.size(); ++i) {
        std::cout << ((i % 25 == 0) ? '\n' : ' ') << (image[i] == '0' ? ' ' : '*');
    }

    std::cout << '\n';
}