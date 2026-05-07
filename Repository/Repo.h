#pragma once
#include "massage.h"
#include <vector>
#include <fstream>

class Repo {
private:
    std::vector<Transmission> transmissions;
public:
    virtual void addTransmission(const Transmission& t) {
        transmissions.push_back(t);
    }

    const std::vector<Transmission>& getTransmissions() const {
        return transmissions;
    }
    void removeTransmission(int id) {
		int tp = findTransmissionById(id) ;
        if (tp == -1) {
            throw std::runtime_error("Transmission with the given ID not found.");

        }

     transmissions.erase(transmissions.begin() + tp);
            
       
	}
    int findTransmissionById(int id) {
        auto it = std::find_if(transmissions.begin(), transmissions.end(),
            [id](const Transmission& t) { return t.getId() == id; });
        if (it != transmissions.end()) {
            return std::distance(transmissions.begin(), it);
        }
        return -1; // Not found
    }


};
class FileTransmissionRepo : public Repo {
    void addTransmission(const Transmission& t) override {
		Repo::addTransmission(t);
        
        
    }
    void saveToFile(const std::string& filename) {
		std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Unable to open file for writing.");
        }
        for (const auto& t : getTransmissions()) {
            outFile << t << "\n";
        }
    }
};