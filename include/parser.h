#pragma once
#include "CSVRow.h"

std::unordered_map<std::string, std::string> buildPayeeMap();
void processTotals(std::vector<CSVRow> row);