// Class for reading data from a CSV file
class Reader {
private:
    // File name to read data from
    string filename;

public:
    // Constructor to initialize the filename
    Reader(string filename) {
        this->filename = filename;
    }

    // Function to read data from the CSV file into vectors X and Y
    void read(vector<float>& X, vector<float>& Y) {
        // Open the file
        ifstream file(filename);

        // Check if the file is open
        if (!file.is_open()) {
            cerr << "Error opening the file." << endl;
            return;
        }

        // Flag to skip the header in the file
        bool isFirstLine = true;

        // Read each line from the file
        string line;
        while (getline(file, line)) {
            // Skip the header
            if (isFirstLine) {
                isFirstLine = false;
            } else {
                istringstream ss(line);
                string token;

                // Read each comma-separated value
                getline(ss, token, ',');
                try {
                    float exp = stof(token);
                    X.push_back(exp);
                } catch (const invalid_argument& e) {
                    cerr << "Error converting YearsExperience to float: " << token << endl;
                    // Handle the error or skip the line based on your requirements
                    continue;
                }

                getline(ss, token, ',');
                try {
                    float sal = stof(token);
                    Y.push_back(sal);
                } catch (const invalid_argument& e) {
                    cerr << "Error converting Salary to float: " << token << endl;
                    // Handle the error or skip the line based on your requirements
                    continue;
                }
            }
        }

        // Close the file
        file.close();
    }
};
