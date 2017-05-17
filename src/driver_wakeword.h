/*
 * Copyright 2016 <Admobilize>
 * MATRIX Labs  [http://creator.matrix.one]
 * This file is part of MATRIX Creator MALOS
 *
 * MATRIX Creator MALOS is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SRC_DRIVER_WAKEWORD_H_
#define SRC_DRIVER_WAKEWORD_H_

#include <cstdio>
#include <memory>
#include <thread>

#include "./src/driver.pb.h"
#include <matrix_malos/malos_base.h>

const char kWakeWordDriverName[] = "WakeWord";

namespace matrix_malos {

class WakeWordDriver : public MalosBase {
public:
  WakeWordDriver() : MalosBase(kWakeWordDriverName) {
    SetNeedsKeepalives(true);
    SetMandatoryConfiguration(true);
    SetNotesForHuman("WakeWord Driver v0.1.2");
  }

  // Read configuration from the outside workd.
  bool ProcessConfig(const DriverConfig &config) override;

private:
  // Thread that read events from pocketsphinx
  void PocketSphinxProcess();

  // Parameters loader
  void loadParameters(WakeWordParams wakeword_params);

  bool startPipe();

  bool stopPipe();

  void returnMatch(std::string match);

  // pipe handler for pocketsphinx
  FILE *sphinx_pipe_ = NULL;
  // config vars
  std::string wakeword;
  std::string lm_path;
  std::string dic_path;
  int16_t channel = 1;
  // enable pipe processing
  bool enable = false;
};

} // namespace matrix_malos

#endif // SRC_DRIVER_WAKEWORD_H_
