#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

// Simple political orientation predictor based on survey responses
enum Party { UNKNOWN, DEMOCRAT, REPUBLICAN, LIBERTARIAN, GREEN };

// Convert Party enum to string for display
std::string partyToString(Party p) {
    switch (p) {
    case DEMOCRAT: return "Democrat";
    case REPUBLICAN: return "Republican";
    case LIBERTARIAN: return "Libertarian";
    case GREEN: return "Green";
    default: return "Unknown";
    }
}

// Question structure
struct Question {
    std::string text;
    std::vector<std::string> options;
    std::vector<std::map<Party, int>> optionScores;
};

// Predict party based on scores
Party predictParty(const std::map<Party, int>& scores) {
    Party bestGuess = UNKNOWN;
    int maxScore = -1;
    for (const auto& pair : scores) {
        if (pair.second > maxScore) {
            maxScore = pair.second;
            bestGuess = pair.first;
        }
    }
    return bestGuess;
}

// Display question and options
void displayQuestion(const Question& q, int index) {
    std::cout << "\nQuestion " << index + 1 << ": " << q.text << "\n";
    for (size_t i = 0; i < q.options.size(); ++i) {
        std::cout << i + 1 << ". " << q.options[i] << "\n";
    }
    std::cout << "Your choice (1-" << q.options.size() << "): ";
}

// Check if file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Save responses to CSV
void saveToCSV(const std::map<Party, int>& scores, Party prediction, Party userLabel, const std::string& filename) {
    bool exists = fileExists(filename);
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open or create CSV file.\n";
        return;
    }

	// Write header if file is new
    if (!exists) {
        file << "Democrat,Republican,Libertarian,Green,Prediction,UserLabel\n";
    }

	// Write scores and labels
    file << scores.at(DEMOCRAT) << ","
        << scores.at(REPUBLICAN) << ","
        << scores.at(LIBERTARIAN) << ","
        << scores.at(GREEN) << ","
        << partyToString(prediction) << ","
        << partyToString(userLabel) << "\n";

    file.close();
}

// Main function
int main() {
    std::vector<Question> survey = {
        {
            "Should we have universal healthcare?",
            {"Strongly support", "Somewhat support", "Neutral", "Oppose"},
            {
                {{DEMOCRAT, 2}, {GREEN, 2}},
                {{DEMOCRAT, 1}, {GREEN, 1}},
                {},
                {{REPUBLICAN, 2}, {LIBERTARIAN, 2}}
            }
        },
        {
            "What is gun ownership in your eyes?",
            {"Ban most guns", "Stricter regulations", "Keep laws as-is", "Loosen regulations"},
            {
                {{DEMOCRAT, 2}, {GREEN, 1}},
                {{DEMOCRAT, 1}},
                {{REPUBLICAN, 1}},
                {{REPUBLICAN, 2}, {LIBERTARIAN, 2}}
            }
        },
        {
            "How should taxes be handled?",
            {"Increase for wealthy", "Flat tax", "Lower taxes for all", "No taxes"},
            {
                {{DEMOCRAT, 2}, {GREEN, 1}},
                {{LIBERTARIAN, 1}},
                {{REPUBLICAN, 2}},
                {{LIBERTARIAN, 2}}
            }
        },
        {
            "What is your stance on climate change policy?",
            {"Aggressive action", "Moderate action", "Let market decide", "Climate change is exaggerated"},
            {
                {{GREEN, 3}, {DEMOCRAT, 2}},
                {{DEMOCRAT, 1}, {GREEN, 1}},
                {{LIBERTARIAN, 2}},
                {{REPUBLICAN, 2}}
            }
        },
        {
            "What does immigration look like for you?",
            {"Open borders", "Pathway to citizenship", "Strict enforcement", "Build a wall"},
            {
                {{GREEN, 2}, {DEMOCRAT, 2}},
                {{DEMOCRAT, 1}},
                {{REPUBLICAN, 1}},
                {{REPUBLICAN, 2}, {LIBERTARIAN, 1}}
            }
        },
        {
            "What is your opinion on student loan forgiveness?",
            {"Forgive all loans", "Forgive some loans", "No forgiveness", "Privatize education"},
            {
                {{DEMOCRAT, 2}, {GREEN, 2}},
                {{DEMOCRAT, 1}},
                {{REPUBLICAN, 2}},
                {{LIBERTARIAN, 2}}
            }
        },
        {
            "How do you feel about public education funding?",
            {"Increase funding", "Maintain current levels", "Reduce funding", "Privatize education"},
            {
                {{DEMOCRAT, 2}, {GREEN, 2}},
                {{DEMOCRAT, 1}},
                {{REPUBLICAN, 1}},
                {{LIBERTARIAN, 2}}
            }
        },
        {
            "What is your view on LGBTQ+ rights?",
            {"Full equality and protections", "Some protections", "Neutral", "Oppose LGBTQ+ rights"},
            {
                {{DEMOCRAT, 2}, {GREEN, 2}},
                {{DEMOCRAT, 1}},
                {},
                {{REPUBLICAN, 2}}
            }
        },
        {
            "What do you think about military spending?",
            {"Increase significantly", "Maintain current levels", "Reduce spending", "Abolish military"},
            {
                {{REPUBLICAN, 2}},
                {{REPUBLICAN, 1}},
                {{DEMOCRAT, 1}, {GREEN, 1}},
                {{GREEN, 2}, {LIBERTARIAN, 2}}
            }
        },
        {
            "How should corporations be regulated?",
            {"Strict regulations", "Moderate regulations", "Minimal regulations", "No regulations"},
            {
                {{DEMOCRAT, 2}, {GREEN, 2}},
                {{DEMOCRAT, 1}},
                {{REPUBLICAN, 1}},
                {{LIBERTARIAN, 2}}
            }
        }
    };

	// Initialize party scores
    std::map<Party, int> partyScores = {
        {DEMOCRAT, 0},
        {REPUBLICAN, 0},
        {LIBERTARIAN, 0},
        {GREEN, 0}
    };

	// Conduct survey
    for (size_t i = 0; i < survey.size(); ++i) {
        displayQuestion(survey[i], i);
        int choice;
        std::cin >> choice;

		// Validate input
        if (std::cin.fail() || choice < 1 || choice > static_cast<int>(survey[i].options.size())) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

	
        const auto& scores = survey[i].optionScores[choice - 1];
        for (const auto& pair : scores) {
            partyScores[pair.first] += pair.second;
        }

		// Intermediate prediction
        Party guess = predictParty(partyScores);
        std::cout << "Current guess: " << partyToString(guess) << "\n";
    }

	// Final prediction
    Party finalGuess = predictParty(partyScores);
    std::cout << "\nFinal prediction: " << partyToString(finalGuess) << "\n";

    // Ask user to label themselves
    std::cout << "\n**********This labeled response will serve as training data the model.**********";
    std::cout << "\nHow do you currently identify politically?\n";
    std::cout << "1. Democrat\n2. Republican\n3. Libertarian\n4. Green\n5. Other / Prefer not to say\n";
    std::cout << "Your choice (1-5): ";
    std::cout << "****************************************************************************************\n";
    int labelChoice;
    std::cin >> labelChoice;

	// Mapping user input to Party 
    Party userLabel = UNKNOWN;
    switch (labelChoice) {
    case 1: userLabel = DEMOCRAT; break;
    case 2: userLabel = REPUBLICAN; break;
    case 3: userLabel = LIBERTARIAN; break;
    case 4: userLabel = GREEN; break;
    default: userLabel = UNKNOWN; break;
    }

	// Save to CSV File
    saveToCSV(partyScores, finalGuess, userLabel, "responses.csv");

	// END of my program
    std::cout << "\nThank you! Your responses have been recorded in 'responses.csv'.\n";
    return 0;
}
