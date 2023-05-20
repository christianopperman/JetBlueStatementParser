#pragma once
#include <string>
#include <vector>

class CSVRow {
    public:
        CSVRow(std::string& unsplit_row, const char& delim=',');
        std::string getDate();
        std::string getMerchant();
        std::string getChargeType();
        std::string getAmount();
        std::string getPayee();
        void setPayee(std::unordered_map<std::string, std::string> payee_map);
        void printRow();
        std::string outputRow();

    private:
        std::string date;
        std::string merchant;
        std::string charge_type;
        std::string amount;
        std::string payee;
        std::vector<std::string> splitRow(std::string& unsplit_row, const char& delim);
        std::string getPayeeFromUser();
};