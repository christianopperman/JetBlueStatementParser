#include "CSVRow.h"
#include <iostream>
#include <regex>
#include <sstream>

// Constructor
CSVRow::CSVRow(std::string& unsplit_row, const char& delim=',') {
    std::vector<std::string> parsed_row = SplitRow(unsplit_row, delim);
    date = parsed_row[0];
    merchant = parsed_row[1];
    charge_type = parsed_row[2];
    amount = parsed_row[3];
    payee = "NONE";
}

// Getter methods
std::string CSVRow::getDate() { return date; }
std::string CSVRow::getMerchant() { return merchant; }
std::string CSVRow::getChargeType() { return charge_type; }
std::string CSVRow::getAmount() { return amount; }
std::string CSVRow::getPayee() { return payee; }

// Setter methods
void CSVRow::setPayee(std::unordered_map<std::string, std::string> payee_map) { 
    for ( const auto [key, value] : payee_map ) {
        if (std::regex_search(merchant, std::regex(key))) {
            payee = value;
        }
    }
    if (payee == "NONE") {
        payee = GetPayee();
    }
    }
        
void CSVRow::printRow() {
    std::cout << date << ", " << merchant << ", " << amount << ", " << payee << "\n";
}

std::vector<std::string> CSVRow::SplitRow(std::string& unsplit_row, const char& delim) {
    // Remove any carriage returns from the row
    unsplit_row.erase(std::remove(unsplit_row.begin(), unsplit_row.end(), '\r'), unsplit_row.end());
    std::istringstream stream(unsplit_row);
    std::string token;

    std::vector<std::string> row;

    while(getline(stream, token, delim)) {
        row.push_back(token);
    }

    return row;
}

std::string CSVRow::GetPayee() {
    // Prompt the user to supply the payer for an unknown merchant
    std::string user_input;
    std::cout << "Please provide the payee for " << date << "/" << merchant << "/" << amount << ": ";
    std::cin >> user_input;
    return user_input;
}