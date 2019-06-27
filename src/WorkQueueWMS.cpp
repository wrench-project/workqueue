/**
 * Copyright (c) 2019. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "WorkQueueWMS.h"
#include "WorkQueueScheduler.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(WorkQueueWMS, "Log category for DAGMan");

namespace wrench {
    namespace workqueue {

        /**
         * @brief Create a WorkQueue WMS with a workflow instance, a list of compute services
         *
         * @param hostname: the name of the host on which to start the WMS
         * @param htcondor_service: an HTCondor service available to run jobs
         * @param storage_service: a storage service available to the WMS
         * @param file_registry_service:
         */
        WorkQueueWMS::WorkQueueWMS(const std::string &hostname,
                                   const std::shared_ptr<wrench::HTCondorComputeService> htcondor_service,
                                   const std::shared_ptr<wrench::StorageService> storage_service,
                                   std::shared_ptr<FileRegistryService> file_registry_service) :
                WMS(nullptr, std::unique_ptr<PilotJobScheduler>(new WorkQueueScheduler()),
                    {htcondor_service}, {storage_service}, {},
                    file_registry_service, hostname, "workqueue_wms") {}

        /**
         * @brief main method of the WorkQueue WMS daemon
         *
         * @return 0 on completion
         *
         * @throw std::runtime_error
         */
        int WorkQueueWMS::main() {
          TerminalOutput::setThisProcessLoggingColor(TerminalOutput::COLOR_GREEN);

          // Check whether there is a deferred start time
          checkDeferredStart();

          WRENCH_INFO("Starting WorkQueue on host %s listening on mailbox_name %s",
                      S4U_Simulation::getHostName().c_str(),
                      this->mailbox_name.c_str());
          WRENCH_INFO("WorkQueue is about to execute a workflow with %lu tasks",
                      this->getWorkflow()->getNumberOfTasks());

          // starting WorkQueue service
          this->workqueue_service = std::make_shared<WorkQueueService>(this->hostname, this->getWorkflow());
          this->workqueue_service->simulation = this->simulation;
          this->workqueue_service->start(workqueue_service, true, true);

          // Create a job manager
          this->job_manager = this->createJobManager();
          auto data_movement_manager = this->createDataMovementManager();


        }

    }
}
