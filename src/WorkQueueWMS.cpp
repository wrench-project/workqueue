/**
 * Copyright (c) 2019. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "WorkQueueWMS.h"

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
                                   const wrench::HTCondorComputeService *htcondor_service,
                                   const wrench::StorageService *storage_service,
                                   wrench::FileRegistryService *file_registry_service) : WMS() {}

    }
}
