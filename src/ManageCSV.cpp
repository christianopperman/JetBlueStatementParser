#include <iostream>
#include <filesystem>
#include <fstream>

#include "CSVRow.h"
#include "ManageCSV.h"


/// @brief Return the most recent .csv file in the input folder.
/// @param folder_loc[in] Folder in which to look for the most recent .csv file.
/// @returns file (std::string) Filepath to most recent .csv file in folder_loc
std::string getInputCSV(std::string folder_loc) {
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

 /// @brief 
 /// @param str 
 /// @param from 
 /// @param to 
 /// @return 
 bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos) {
        return false;
    }

    str.replace(start_pos, from.length(), to);
    return true;
 }

/// @brief 
/// @return 
std::string genOutputLoc() {
    std::string output_file = getInputCSV();
    replace(output_file, ".csv", "_Processed.csv");
    replace(output_file, "input", "output");
    return output_file;
}

/// @brief
/// @param rows 
/// @param filepath 
void outputCSV(std::vector<CSVRow> rows) {
    std::string filepath = genOutputLoc();
    std::ofstream output_file(filepath);

    // Header row
    output_file << "Date, Merchant, Chargetype, Amount, Payee\n";
    // Data rows
    for (CSVRow& row : rows) {
        output_file << row.outputRow();
    }
    output_file.close();

    std::cout << "Data written to file=" << filepath << "\n"; 
}