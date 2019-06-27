/**
 * Copyright (c) 2019. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "WorkQueueService.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(WorkQueueService, "Log category for WorkQueueService");

namespace wrench {
    namespace workqueue {

        /**
         * @brief Constructor
         *
         * @param hostname: the name of the host on which the service will run
         */
        WorkQueueService::WorkQueueService(std::string &hostname, wrench::Workflow *workflow) :
                Service(hostname, "workqueue", "workqueue"), workflow(workflow) {}

        /**
         * @brief Destructor
         */
        WorkQueueService::~WorkQueueService() {
          this->completed_jobs.clear();
        }

        /**
         * @brief Get the service mailbox name
         *
         * @return mailbox name
         */
        const std::string WorkQueueService::getMailbox() {
          return this->mailbox_name;
        }

        /**
         * @brief Get a set of completed jobs
         *
         * @return set of completed jobs
         */
        std::set<WorkflowJob *> WorkQueueService::getCompletedJobs() {
          auto completed_jobs_set = this->completed_jobs;
          this->completed_jobs.clear();
          return completed_jobs_set;
        }

        /**
         * @brief Main method of the WorkQueue service daemon
         *
         * @return 0 on termination
         *
         * @throw std::runtime_error
         */
        int WorkQueueService::main() {
          TerminalOutput::setThisProcessLoggingColor(TerminalOutput::COLOR_GREEN);

          WRENCH_INFO("Starting WorkQueueService on host %s listening on mailbox_name %s",
                      S4U_Simulation::getHostName().c_str(), this->mailbox_name.c_str());

          // main loop
          while (this->processNextMessage()) {
            // no specific action
            WRENCH_INFO("Starting WorkQueueService on host %s listening on mailbox_name %s",
                        S4U_Simulation::getHostName().c_str(), this->mailbox_name.c_str());

          }

          WRENCH_INFO("WorkQueueService Daemon started on host %s terminating", S4U_Simulation::getHostName().c_str());
          return 0;
        }

        /**
         * @brief Wait for and react to any incoming message
         *
         * @return false if the daemon should terminate, true otherwise
         *
         * @throw std::runtime_error
         */
        bool WorkQueueService::processNextMessage() {
          // Wait for a workflow execution event
          std::unique_ptr<wrench::WorkflowExecutionEvent> event;
//          try {
//            event = this->workflow->waitForNextExecutionEvent();
//
//          } catch (wrench::WorkflowExecutionException &e) {
//            throw std::runtime_error("Error while getting and execution event: " + e.getCause()->toString());
//          }
//          switch (event->type) {
//            case wrench::WorkflowExecutionEvent::STANDARD_JOB_COMPLETION: {
//              StandardJob *job = (dynamic_cast<StandardJobCompletedEvent *>(event.get()))->standard_job;
//              this->processStandardJobCompletion(job);
//              break;
//            }
//            default: {
//              throw std::runtime_error("Unexpected workflow execution event: " + std::to_string((int) (event->type)));
//            }
//          }
          return true;
        }

        /**
         * @brief Process a standard job completion
         *
         * @param job: the job
         *
         * @throw std::runtime_error
         */
        void WorkQueueService::processStandardJobCompletion(StandardJob *job) {
          WRENCH_INFO("A standard job has completed job %s", job->getName().c_str());
          std::string callback_mailbox = job->popCallbackMailbox();
          for (auto task : job->getTasks()) {
            WRENCH_INFO("    Task completed: %s (%s)", task->getID().c_str(), callback_mailbox.c_str());
          }

          this->completed_jobs.insert(job);
        }
    }
}