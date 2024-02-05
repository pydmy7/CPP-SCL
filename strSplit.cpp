std::vector<std::string> strSplit(const std::string& str, const std::string& delims = " ") {
    std::vector<std::string> output;
    for (std::size_t first = 0; first < str.size();) {
        std::size_t second = str.find(delims, first);
        if (first != second) {
            output.emplace_back(str.substr(first, second - first));
        }
        if (second == std::string::npos) {
            break;
        }
        first = second + delims.size();
    }
    return output;
}