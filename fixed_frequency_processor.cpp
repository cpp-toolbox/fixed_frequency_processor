#include "fixed_frequency_processor.hpp"

FixedFrequencyProcessor::FixedFrequencyProcessor(int frequency, std::function<void(int, double)> process_fun)
    : process_fun(process_fun), periodic_signal(frequency, OperationMode::PERFECT_DELTAS) {}

void FixedFrequencyProcessor::add_id(int id) {
    std::cout << "FFP Adding ID: " << id << std::endl;
    ids_to_process.push_back(id);
}

void FixedFrequencyProcessor::add_ids(std::vector<int> ids) {
    for (const auto id : ids) {
        this->add_id(id);
    }
}

bool FixedFrequencyProcessor::attempt_to_process() {
    if (periodic_signal.process_and_get_signal()) {
        unsigned int count = 0;
        while (!ids_to_process.empty()) {
            int id = ids_to_process.front();
            ids_to_process.erase(ids_to_process.begin());
            process_fun(id, periodic_signal.get_last_delta_time());
            processed_ids.push_back(id);
            count++;
        }

        if (count >= 1 and ids_to_process.empty()) {
            std::cout << "FFP: All IDs processed." << std::endl;
            processed_at_least_one_id = true;
        }

        return true;
    }
    return false;
}
int FixedFrequencyProcessor::get_last_processed_id() const {
    if (processed_ids.empty()) {
        throw std::out_of_range("No IDs have been processed yet.");
    }
    return processed_ids.back(); // Returns the last element
}

void FixedFrequencyProcessor::display_processed_ids() const {
    std::cout << "FFP Processed IDs: ";
    for (const auto &id : processed_ids) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
}
