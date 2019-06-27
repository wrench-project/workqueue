/**
 * Copyright (c) 2019. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef WORKQUEUE_WORKQUEUEWMS_H
#define WORKQUEUE_WORKQUEUEWMS_H

#include <wrench-dev.h>
#include "WorkQueueService.h"

namespace wrench {
    namespace workqueue {

        /**
         *  @brief An implementation of the WorkQueue meta-scheduler
         */
        class WorkQueueWMS : public WMS {

        public:
            WorkQueueWMS(const std::string &hostname,
                         const std::shared_ptr<HTCondorComputeService> htcondor_service,
                         const std::shared_ptr<StorageService> storage_service,
                         std::shared_ptr<FileRegistryService> file_registry_service);

        protected:
            /***********************/
            /** \cond DEVELOPER    */
            /***********************/

            /***********************/
            /** \endcond           */
            /***********************/

        private:
            int main() override;

            /** @brief The job manager */
            std::shared_ptr<JobManager> job_manager;
            /** @brief */
            std::shared_ptr<WorkQueueService> workqueue_service;
        };

    }
}

#endif //WORKQUEUE_WORKQUEUEWMS_H
