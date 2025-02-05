#ifndef FIXED_FREQUENCY_PROCESSOR_HPP
#define FIXED_FREQUENCY_PROCESSOR_HPP

#include <vector>
#include <functional>
#include <iostream>
#include "sbpt_generated_includes.hpp"

/**
 * @brief A class for processing IDs at a fixed frequency.
 */
class FixedFrequencyProcessor {
  private:
    std::vector<int> processed_ids;               ///< Vector of IDs that have been processed.
    std::vector<int> ids_to_process;              ///< Vector of IDs that need to be processed.
    std::function<void(int, double)> process_fun; ///< Function to process each ID.
    PeriodicSignal periodic_signal;

  public:
    bool processed_at_least_one_id = false;
    /**
     * @brief Constructs a FixedFrequencyProcessor.
     * @param frequency The number of times the process should happen per second.
     * @param fun Function to process each ID.
     */
    FixedFrequencyProcessor(int frequency, std::function<void(int, double)> process_fun);

    int get_last_processed_id() const;

    /**
     * @brief Adds an ID to the list of IDs to be processed.
     * @param id The ID to add.
     */
    void add_id(int id);

    /**
     * @brief Adds a list of IDs to the list of IDs to be processed.
     * @param ids A vector of IDs to add.
     */
    void add_ids(std::vector<int> ids);

    /**
     * @brief Attempts to process IDs if the accumulated time exceeds the processing interval.
     * @return true if processing was done; false otherwise.
     */
    bool attempt_to_process();

    /**
     * @brief Displays the list of processed IDs.
     */
    void display_processed_ids() const;
};

#endif // FIXED_FREQUENCY_PROCESSOR_HPP
