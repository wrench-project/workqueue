/**
 * Copyright (c) 2019. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "WorkQueueScheduler.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(WorkQueueScheduler, "Log category for WorkQueue Scheduler Daemon");

namespace wrench {
    namespace workqueue {

        /**
         * @brief Constructor
         */
        WorkQueueScheduler::WorkQueueScheduler() {}


        /**
         * @brief Destructor
         */
        WorkQueueScheduler::~WorkQueueScheduler() {}

        /**
         * @brief Schedule and run a set of pilot jobs on available HTCondor resources
         *
         * @param compute_services: a set of compute services available to run jobs
         *
         * @throw std::runtime_error
         */
        void WorkQueueScheduler::schedulePilotJobs(
                const std::set<std::shared_ptr<wrench::ComputeService>> &compute_services) {

        }

        /**
         * @brief
         *
         * @param simulation: a pointer to the simulation object
         */
        void WorkQueueScheduler::setSimulation(Simulation *simulation) {
          this->simulation = simulation;
        }

        /**
         * @brief:
         *
         * @param service_callback_mailbox
         */
        void WorkQueueScheduler::setServiceCallbackMailbox(const std::string &service_callback_mailbox) {
          this->service_callback_mailbox = service_callback_mailbox;
        }
    }
}
