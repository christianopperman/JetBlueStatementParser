#pragma once

std::string getInputCSV(std::string folder_loc = "src/input");
std::unordered_map<std::string, std::string> buildPayeeMap();