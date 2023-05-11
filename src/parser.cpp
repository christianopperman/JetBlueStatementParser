#include <iostream>
#include <filesystem>
// #include <print>
#include <sstream>
#include <fstream>
#include <chrono>

class CSVRow {
    public:
        // Constructor
        CSVRow(std::string& unsplit_row, const char& delim=',') {
            std::vector<std::string> parsed_row = SplitRow(unsplit_row, delim);
            date = parsed_row[0];
            merchant = parsed_row[1];
            charge_type = parsed_row[2];
            amount = parsed_row[3];
        }

        // Getter methods
        std::string getDate() { return date; }
        std::string getMerchant() { return merchant; }
        std::string getChargeType() { return charge_type; }
        std::string getAmount() { return amount; }
        std::string getPayee() { return payee; }

        // Setter methods
        void setPayee(std::string& p) { payee = p; }

        void printRow() {
            // std::string payee_string = payee == nullptr ? '' : payee;
            std::cout << date << " | " << merchant << " | " << charge_type << " | " << amount << "\n";
        }

    private:
        std::string date;
        std::string merchant;
        std::string charge_type;
        std::string amount;
        std::string payee;

        std::vector<std::string> SplitRow(std::string& unsplit_row, const char& delim) {
            std::istringstream stream(unsplit_row);
            std::string token;

            std::vector<std::string> row;

            while(getline(stream, token, delim)) {
                row.push_back(token);
            }

            return row;
        }
};

/// @brief Return the most recent .csv file in the input folder.
/// @param folder_loc[in] Folder in which to look for the most recent .csv file.
/// @returns file (std::string) Filepath to most recent .csv file in folder_loc
std::string getInputCSV(std::string folder_loc = "src/input") {
    std::filesystem::path dir = std::filesystem::current_path() / folder_loc;
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

int main() {
    std::filesystem::path file_loc { getInputCSV() };
    
    std::vector<CSVRow> rows;

    std::fstream file(file_loc);
    std::string line;
    while(getline(file, line)) {
        if (line[0] == '4') {
            CSVRow row = CSVRow(line);
            rows.push_back(row);
        }
    }

    for (CSVRow row : rows) {
        row.printRow();
        
    }
}