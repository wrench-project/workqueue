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

XBT_LOG_NEW_DEFAULT_CATEGORY(WorkQueue, "Log category for WorkQueue");

int main(int argc, char **argv) {

  // create and initialize the simulation
  wrench::Simulation simulation;
  simulation.init(&argc, argv);



  return 0;
}
