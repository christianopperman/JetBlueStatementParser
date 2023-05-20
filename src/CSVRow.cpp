#include "CSVRow.h"
#include <iostream>
#include <regex>
#include <sstream>

// Constructor
CSVRow::CSVRow(std::string& unsplit_row, const char& delim) {
    std::vector<std::string> parsed_row = splitRow(unsplit_row, delim);
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

/// @brief 
/// @param payee_map 
void CSVRow::setPayee(std::unordered_map<std::string, std::string> payee_map) { 
    for ( const auto [key, value] : payee_map ) {
        if (std::regex_search(merchant, std::regex(key))) {
            payee = value;
        }
    }
    if (payee == "NONE") {
        payee = getPayeeFromUser();
    }
    }


void CSVRow::printRow() {
    std::cout << date << ", " << merchant << ", " << amount << ", " << payee << "\n";
}

/// @brief  
/// @return 
std::string CSVRow::outputRow() {
    std::string output_str {};

    for (std::string const& s : std::vector<std::string>{date, merchant, charge_type, amount, payee}) {
        output_str += s + ",";
    }

    output_str.pop_back();
    output_str += "\r";

    return output_str;
}

/// @brief Takes a CSV row and parses it into tokens. This algorithm handles fields with commas in them, provided they are delineated by quotes.
/// @param unsplit_row 
/// @param delim 
/// @return <std::vector<std::string>> row_tokens, a vector of strings representing the parsed tokens from the CSV row.
std::vector<std::string> CSVRow::splitRow(std::string& unsplit_row, const char& delim) {
    bool quote_flag = false;
    std::vector<std::string> row_tokens;
    std::string token = "";

    for ( std::string::iterator it=unsplit_row.begin(); it!=unsplit_row.end(); ++it) {
        if (*it == delim && !quote_flag) {
            row_tokens.push_back(token);
            token = "";
        } else if (*it == '\"' && !quote_flag) {
            quote_flag = true;
            token += *it;
        } else if (*it == '\"' && quote_flag) {
            quote_flag = false;
            token += *it;
        } else if (*it == '\r' || *it == '\n') {
            row_tokens.push_back(token);
            break;
        } else {
            token += *it;
        }
    }
    // Necessary to add the final token at the end of the file (as the file doesn't terminate with a carriage return or comma)
    row_tokens.push_back(token);

    return row_tokens;
}

/// @brief 
/// @return 
std::string CSVRow::getPayeeFromUser() {
    // Prompt the user to supply the payer for an unknown merchant
    std::string user_input;
    std::cout << "Please provide the payee for " << date << "/" << merchant << "/" << amount << ": ";
    // TODO: Add error handling into function to prevent non-valid values from being passed in by user
    std::cin >> user_input;
    return user_input;
}