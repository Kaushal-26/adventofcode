//https://adventofcode.com/2024/day/14

#include <bits/stdc++.h>
#include <png.h>


// By claude
class PNGImage {
public:
    PNGImage(int width, int height) : width(width), height(height) {
        // Allocate memory for pixel data
        pixels.resize(height);
        for (auto& row : pixels) {
            row.resize(width * 3);  // 3 channels (RGB)
        }
    }

    void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
        if (x < 0 || x >= width || y < 0 || y >= height) return;
        
        int index = x * 3;
        pixels[y][index] = r;
        pixels[y][index + 1] = g;
        pixels[y][index + 2] = b;
    }

    void saveToFile(const std::string& filename) {
        FILE* fp = fopen(filename.c_str(), "wb");
        if (!fp) {
            throw std::runtime_error("Cannot open file");
        }

        // Create PNG structures
        png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!png) {
            fclose(fp);
            throw std::runtime_error("Cannot create PNG write struct");
        }

        png_infop info = png_create_info_struct(png);
        if (!info) {
            png_destroy_write_struct(&png, nullptr);
            fclose(fp);
            throw std::runtime_error("Cannot create PNG info struct");
        }

        // Set up error handling
        if (setjmp(png_jmpbuf(png))) {
            png_destroy_write_struct(&png, &info);
            fclose(fp);
            throw std::runtime_error("PNG error");
        }

        // Initialize file for writing
        png_init_io(png, fp);

        // Write header
        png_set_IHDR(png, info, width, height, 8, 
                     PNG_COLOR_TYPE_RGB, 
                     PNG_COMPRESSION_TYPE_DEFAULT, 
                     PNG_FILTER_TYPE_DEFAULT, 
                     PNG_INTERLACE_NONE);

        // Allocate row pointers
        std::vector<png_bytep> rowPointers(height);
        for (int y = 0; y < height; y++) {
            rowPointers[y] = pixels[y].data();
        }

        // Write image data
        png_write_info(png, info);
        png_write_image(png, rowPointers.data());
        png_write_end(png, nullptr);

        // Clean up
        png_destroy_write_struct(&png, &info);
        fclose(fp);
    }

private:
    int width, height;
    std::vector<std::vector<uint8_t>> pixels;
};


// Time taken calculate
struct TimeCalculate {
        std::chrono::_V2::system_clock::time_point begin;
        TimeCalculate() {
                begin = std::chrono::high_resolution_clock::now();
        }
        void end() {
                auto end = std::chrono::high_resolution_clock::now();
                auto execution_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 1e-9;
                std::cout << std::fixed << std::setprecision(15) << "Execution Time: " << execution_time << "\n";
        }
};



std::string input;
std::istringstream oin;

void set_oin() {
        oin.clear(); oin.str(input);
}

void fix() {
        input.erase(input.find("p="), 2); input.erase(input.find("v="), 2);
        while (input.find(",") != std::string::npos) {
                input[input.find(",")] = ' ';
        }
}

std::string directory = "outputs/";

void solve() {
        // Command to run:
        // sudo apt-get install libpng-dev
        // g++-13 -std=c++23 -DKaushal_26 -Wall -g -H -O2 -fsanitize=address,undefined -D_GLIBCXX_DEBUG   -o go go.cpp -lpng
        // answer = image_7583.png

        std::queue<std::array<int, 4>> Q, TQ;

        int N = 0, M = 0;
        while (getline(std::cin, input)) {
                fix(); set_oin();
                int X, Y, Vx, Vy; oin >> Y >> X >> Vy >> Vx; Q.push({X, Y, Vx, Vy});
                N = std::max(N, X + 1); M = std::max(M, Y + 1);
        }

        for (int repetition = 0; repetition < 10000; ++repetition) {
                std::vector<std::vector<int>> x(N, std::vector<int>(M, 0));

                while (!TQ.empty()) TQ.pop();
                while (!Q.empty()) {
                        auto [X, Y, Vx, Vy] = Q.front(); Q.pop();
                        X += Vx; X += N; X %= N;
                        Y += Vy; Y += M; Y %= M;
                        TQ.push({X, Y, Vx, Vy});
                        x[X][Y] += 1;
                }

                std::swap(TQ, Q);

                PNGImage image(N * 5, M * 5);
                for (int i = 0; i < N * 5; i ++) {
                        for (int j = 0; j < M * 5; j ++) {
                                if (x[i / 5][j / 5]) {
                                        image.setPixel(i, j, 0, 255, 0);
                                } else {
                                        image.setPixel(i, j, 0, 0, 0);
                                }
                        }
                }
                std::string fileName = directory + "image_" + std::to_string(repetition) + ".png";
                image.saveToFile(fileName);
        }

}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        TimeCalculate timer;
        solve();
        timer.end();
        return 0;
}

// 1.77245
