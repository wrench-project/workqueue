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

          this->submit_hostname = getPropertyValue<std::string>("submit_host", json_data);
          this->file_registry_hostname = getPropertyValue<std::string>("file_registry_host", json_data);

          // storage resources
          std::vector<nlohmann::json> storage_resources = json_data.at("storage_hosts");
          for (auto &storage : storage_resources) {
            std::string storage_host = getPropertyValue<std::string>("hostname", storage);
            WRENCH_INFO("Instantiating a SimpleStorageService on: %s", storage_host.c_str());
            auto storage_service = simulation.add(
                    new SimpleStorageService(storage_host, getPropertyValue<double>("capacity", storage)));
            storage_service->setNetworkTimeoutValue(30);
            this->storage_services.insert(storage_service.get());
          }

          // compute resources
          std::vector<nlohmann::json> compute_resources = json_data.at("compute_services");
          for (auto &resource : compute_resources) {
            std::string type = getPropertyValue<std::string>("type", resource);

            if (type == "bare-metal" || type == "multicore") {
              throw std::invalid_argument("SimulationConfig::loadProperties(): Bare-Metal support not yet implemented");
            } else if (type == "cloud") {
              throw std::invalid_argument("SimulationConfig::loadProperties(): Cloud support not yet implemented");
            } else if (type == "batch") {
              instantiateBatch(resource.at("service_host"), resource.at("compute_hosts"));
            } else {
              throw std::invalid_argument("SimulationConfig::loadProperties(): Invalid compute service type");
            }
          }

          // build the HTCondorService
          this->htcondor_service = simulation.add(
                  new HTCondorComputeService(this->submit_hostname, "local", std::move(this->compute_services))).get();
        }

        /**
         * @brief Get the hostname for the submit host
         * @return The hostname for the submit host
         */
        std::string SimulationConfig::getSubmitHostname() {
          return this->submit_hostname;
        }

        /**
         * @brief Get the hostname for the file registry
         * @return The hostname for the file registry
         */
        std::string SimulationConfig::getFileRegistryHostname() {
          return this->file_registry_hostname;
        }

        /**
         * @brief Get a pointer to the HTCondorService
         * @return A pointer to the HTCondorService
         */
        HTCondorComputeService *SimulationConfig::getHTCondorComputeService() {
          return this->htcondor_service;
        }

        /**
         * @brief Get a set of pointers to wrench::StorageService available for the simulation
         * @return A set of storage services
         */
        std::set<StorageService *> SimulationConfig::getStorageServices() {
          return this->storage_services;
        }

        /**
         * @brief Instantiate wrench::BatchComputeService
         *
         * @param service_host: name of the host to run the batch service
         * @param hosts: vector of hosts to be instantiated
         */
        void SimulationConfig::instantiateBatch(std::string service_host, std::vector<std::string> hosts) {

          std::map<std::string, std::string> messagepayload_properties_list = {
                  {BatchComputeServiceMessagePayload::SUBMIT_STANDARD_JOB_REQUEST_MESSAGE_PAYLOAD, "122880000"},
                  {BatchComputeServiceMessagePayload::SUBMIT_STANDARD_JOB_ANSWER_MESSAGE_PAYLOAD,  "1024"},
                  {BatchComputeServiceMessagePayload::STANDARD_JOB_DONE_MESSAGE_PAYLOAD,           "512000000"},
          };

          this->compute_services.insert(new wrench::BatchComputeService(
                  service_host, hosts, 0, {{wrench::BareMetalComputeServiceProperty::SUPPORTS_PILOT_JOBS, "true"}},
                  {{wrench::BareMetalComputeServiceMessagePayload::STOP_DAEMON_MESSAGE_PAYLOAD, 1024}}));
        }
    }
}
