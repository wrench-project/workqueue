/**
 * Copyright (c) 2019. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef WORKQUEUE_WORKQUEUESERVICE_H
#define WORKQUEUE_WORKQUEUESERVICE_H

#include <wrench-dev.h>

namespace wrench {
    namespace workqueue {

        /**
         * @brief A monitor for DAGMan
         */
        class WorkQueueService : public Service {
        public:
            WorkQueueService(std::string &hostname, Workflow *workflow);

            ~WorkQueueService() override;

            const std::string getMailbox();

            std::set<WorkflowJob *> getCompletedJobs();

        private:
            int main() override;

            bool processNextMessage();

            void processStandardJobCompletion(StandardJob *job);

            std::set<WorkflowJob *> completed_jobs;

            Workflow *workflow;
        };
    }
}

#endif //WORKQUEUE_WORKQUEUESERVICE_H
