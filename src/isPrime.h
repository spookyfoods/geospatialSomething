#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <mdspan> // Ensure you have the header for mdspan

// Call this function right after your SAT calculation loop
void saveSATToCSV(const std::string& filename, 
                  std::mdspan<SatPixel, std::dextents<size_t, 2>> grid, 
                  int height, 
                  int width) {
    
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "[C++] Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    std::cout << "[C++] Dumping SAT to " << filename << "..." << std::endl;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Access the pixel at (row, col)
            // Assuming SatPixel struct has members r, g, b, a or subscript operator
            // Adjust members (.r, .g, .b, .a) based on your actual struct definition
            const auto& p = grid[i, j]; 
            
            // Format: R|G|B|A (using pipe separator within the cell to distinguish channels)
            file << p.r << "|" << p.g << "|" << p.b << "|" << p.a;

            // Add comma if it's not the last column
            if (j < width - 1) {
                file << ",";
            }
        }
        // New line at the end of the row
        file << "\n";
    }

    file.close();
    std::cout << "[C++] SAT dump complete." << std::endl;
}
