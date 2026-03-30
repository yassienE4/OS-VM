#include <iostream>
#include <filesystem>
#include <map>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <directory> <bin_width>\n";
        return 1;
    }

    fs::path start_path = argv[1];
    size_t bin_width = stoull(argv[2]);
    string output_file = "output.csv";

    map<size_t, size_t> histogram;

    try {
        for (const auto& entry : fs::recursive_directory_iterator(start_path)) {
            if (entry.is_regular_file()) {
                size_t file_size = entry.file_size();
                size_t bin = file_size / bin_width;
                histogram[bin]++;
            }
        }
    } catch (const fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    ofstream out(output_file);
    if (!out) {
        cerr << "Failed to open output file\n";
        return 1;
    }

    // CSV header
    out << "lower_bound,upper_bound,count\n";

    for (const auto& [bin, count] : histogram) {
    size_t lower = bin * bin_width;
    size_t upper = lower + bin_width - 1;
    out << lower << "," << upper << "," << count << "\n";
    }

    out.close();
    cout << "Histogram data written to " << output_file << "\n";

    system("python plot.py");

    return 0;
}