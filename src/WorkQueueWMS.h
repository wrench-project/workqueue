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
                         const HTCondorComputeService *htcondor_service,
                         const StorageService *storage_service,
                         FileRegistryService *file_registry_service);

        protected:
            /***********************/
            /** \cond DEVELOPER    */
            /***********************/

            /***********************/
            /** \endcond           */
            /***********************/

        private:
            int main() override;
        };

    }
}

#endif //WORKQUEUE_WORKQUEUEWMS_H
