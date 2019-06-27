/**
 * Copyright (c) 2019. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <iostream>
#include <vector>
#include <wrench-dev.h>
#include "SimulationConfig.h"
#include "WorkQueueWMS.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(WorkQueue, "Log category for WorkQueue");

int main(int argc, char **argv) {

  // create and initialize the simulation
  wrench::Simulation simulation;
  simulation.init(&argc, argv);

  // check to make sure there are the right number of arguments
  if (argc != 4) {
    std::cerr << "WRENCH WorkQueue Simulator" << std::endl;
    std::cerr << "Usage: " << argv[0]
              << " <xml platform file> <JSON or XML workflow file> <JSON simulation config file>"
              << std::endl;
    exit(1);
  }

  //create the platform file and dax file from command line args
  char *platform_file = argv[1];
  char *workflow_file = argv[2];
  char *properties_file = argv[3];

  // instantiating SimGrid platform
  WRENCH_INFO("Instantiating SimGrid platform from: %s", platform_file);
  simulation.instantiatePlatform(platform_file);

  // loading config file
  WRENCH_INFO("Loading simulation config from: %s", properties_file);
  wrench::workqueue::SimulationConfig config;
  config.loadProperties(simulation, properties_file);

  // loading the workflow from the JSON or XML file
  WRENCH_INFO("Loading workflow from: %s", workflow_file);
  std::istringstream ss(workflow_file);
  std::string token;
  std::vector<std::string> tokens;
  while (std::getline(ss, token, '.')) {
    tokens.push_back(token);
  }

  if (tokens.size() < 2) {
    std::cerr << "Invalid workflow file name " << workflow_file << " (should be *.xml or *.json)\n";
    exit(1);
  }
  wrench::Workflow workflow;
  if (tokens[tokens.size() - 1] == "xml") {
    workflow.loadFromDAX(workflow_file, "1f");
  } else if (tokens[tokens.size() - 1] == "json") {
    workflow.loadFromJSON(workflow_file, "1f");
  } else {
    std::cerr << "Invalid workflow file name " << workflow_file << " (should be *.xml or *.json)\n";
    exit(1);
  }

  WRENCH_INFO("The workflow has %ld tasks", workflow.getNumberOfTasks());

  // HTCondor service
  auto htcondor_service = config.getHTCondorComputeService();

  // file registry service
  WRENCH_INFO("Instantiating a FileRegistryService on: %s", config.getFileRegistryHostname().c_str());
  auto file_registry_service = simulation.add(new wrench::FileRegistryService(config.getFileRegistryHostname()));

  // storage services
  auto storage_services = config.getStorageServices();

  // create the wms
  auto wms = simulation.add(new wrench::workqueue::WorkQueueWMS(config.getSubmitHostname(),
                                                                {htcondor_service},
                                                                storage_services,
                                                                file_registry_service));
  wms->addWorkflow(&workflow);

  WRENCH_INFO("Staging input files");
  auto input_files = workflow.getInputFiles();
  try {
    simulation.stageFiles(input_files, htcondor_service->getLocalStorageService());
  } catch (std::runtime_error &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 0;
  }

  // simulation execution
  WRENCH_INFO("Launching the Simulation...");
  try {
    simulation.launch();
  } catch (std::runtime_error &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 0;
  }
  WRENCH_INFO("Simulation done!");

  return 0;
}
