/**
 * Copyright (c) 2019. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <fstream>
#include "SimulationConfig.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(SimulationConfig, "Log category for SimulationConfig");

namespace wrench {
    namespace workqueue {

        /**
         * @brief Load the simulation properties for configuring the simulation. It also creates and configures the
         *        HTCondorService object.
         *
         * @param simulation: pointer to simulation object
         * @param filename: File path for the properties file
         *
         * @throw std::invalid_argument
         */
        void SimulationConfig::loadProperties(wrench::Simulation &simulation, const std::string &filename) {

          std::ifstream file;
          nlohmann::json json_data;

          // handle the exceptions of opening the json file
          file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
          try {
            file.open(filename);
            file >> json_data;
          } catch (const std::ifstream::failure &e) {
            throw std::invalid_argument("SimulationConfig::loadProperties(): Invalid JSON file");
          }

        }
    }
}
