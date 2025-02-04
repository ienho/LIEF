/* Copyright 2017 - 2021 R. Thomas
 * Copyright 2017 - 2021 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef LIEF_MACHO_MAIN_COMMAND_H_
#define LIEF_MACHO_MAIN_COMMAND_H_
#include <iostream>

#include "LIEF/visibility.h"

#include "LIEF/MachO/enums.hpp"
#include "LIEF/MachO/LoadCommand.hpp"

namespace LIEF {
namespace MachO {
struct entry_point_command;
class LIEF_API MainCommand : public LoadCommand {
  public:
  MainCommand();
  MainCommand(const entry_point_command *cmd);

  MainCommand& operator=(const MainCommand& copy);
  MainCommand(const MainCommand& copy);

  virtual MainCommand* clone() const override;

  virtual ~MainCommand();

  uint64_t entrypoint() const;
  uint64_t stack_size() const;

  void entrypoint(uint64_t entrypoint);
  void stack_size(uint64_t stacksize);

  bool operator==(const MainCommand& rhs) const;
  bool operator!=(const MainCommand& rhs) const;

  virtual std::ostream& print(std::ostream& os) const override;

  virtual void accept(Visitor& visitor) const override;

  private:
  uint64_t entrypoint_;
  uint64_t stackSize_;
};

}
}
#endif
