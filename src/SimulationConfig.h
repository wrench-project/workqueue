/**
 * Copyright (c) 2019. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef WORKQUEUE_SIMULATIONCONFIG_H
#define WORKQUEUE_SIMULATIONCONFIG_H

#include <nlohmann/json.hpp>
#include <wrench-dev.h>

namespace wrench {
    namespace workqueue {

        class SimulationConfig {

        public:
            void loadProperties(wrench::Simulation &simulation, const std::string &filename);
        };
    }
}

#endif //WORKQUEUE_SIMULATIONCONFIG_H
