#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "CSVRow.h"
#include "parser.h"

/// @brief Return the most recent .csv file in the input folder.
/// @param folder_loc[in] Folder in which to look for the most recent .csv file.
/// @returns file (std::string) Filepath to most recent .csv file in folder_loc
std::string getInputCSV(std::string folder_loc = "src/input") {
    std::filesystem::path dir {std::filesystem::current_path() / folder_loc};
    auto dir_iter = std::filesystem::directory_iterator(dir);

    std::filesystem::path latest_file{};
    for (auto const& dir_entry : dir_iter) {
        const std::filesystem::path path{dir_entry.path()};
        if (path.extension() == ".csv") {

            if (latest_file == "") {
                latest_file = path;
            }
            
            auto time{dir_entry.last_write_time()};
            if (time > std::filesystem::last_write_time(latest_file)) {
                latest_file = path;
            }
        }
    }
    
    return latest_file;
}

/// @brief Builds a map for <merchant, payee> for categorizing rows in bank statement from .csv file
/// @return payee_map (std::unordered_map)
std::unordered_map<std::string, std::string> buildPayeeMap() {
    std::filesystem::path csv_loc {std::filesystem::current_path() / "src/payee_map.csv"};
    std::fstream file(csv_loc);
    std::string line;
    std::unordered_map<std::string, std::string> payee_map;

    while(getline(file, line)) {
        std::istringstream stream(line);
        std::string token;
        std::vector<std::string> row;

        while(getline(stream, token, ',')) {
            row.push_back(token);
        }
        payee_map[row[0]] = row[1];
    }
    return payee_map;
}

int main() {
    std::filesystem::path file_loc { getInputCSV() };
    std::unordered_map<std::string, std::string> payee_map { buildPayeeMap() };
    
    std::vector<CSVRow> rows;
    std::fstream file(file_loc);
    std::string line;

    while(getline(file, line)) {
        if (line[0] == '4') { // TODO: Fix this so April isn't hard coded
            // TODO: There's probably a more efficient way that doesn't involve creating a CSVRow object that is ultimately not used
            // May require SplitRow() to be a global function instead of a class method? 
            CSVRow row = CSVRow(line);
            
            // Not necessary to include Payment Received lines in calculation because
            // Those are payments already made and will confuse the totals
            if (row.getMerchant() != "Payment Received") {
                row.setPayee(payee_map);
                rows.push_back(row);
            }
        
        }
    }

    for (auto row : rows) {
        row.printRow();
    }

}