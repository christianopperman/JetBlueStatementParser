#pragma once

std::string getInputCSV(std::string folder_loc = "src/input");
bool replace(std::string& str, const std::string& from, const std::string& to);
std::string genOutputLoc();
void outputCSV(std::vector<CSVRow> rows);
