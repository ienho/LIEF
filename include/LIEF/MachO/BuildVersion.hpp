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
#ifndef LIEF_MACHO_BUILD_VERSION_COMMAND_H_
#define LIEF_MACHO_BUILD_VERSION_COMMAND_H_
#include <vector>
#include <iostream>
#include <array>

#include "LIEF/visibility.h"
#include "LIEF/types.hpp"

#include "LIEF/MachO/LoadCommand.hpp"

namespace LIEF {
namespace MachO {
struct build_tool_version;
struct build_version_command;

class LIEF_API BuildToolVersion : public LIEF::Object {
  public:
  //! @brief Version is an array of **3** integers
  using version_t = std::array<uint32_t, 3>;

  public:
  enum class TOOLS {
    UNKNOWN = 0,
    CLANG   = 1,
    SWIFT   = 2,
    LD      = 3,
  };

  public:
  BuildToolVersion();
  BuildToolVersion(const build_tool_version& tool);

  //! TOOL used
  TOOLS tool() const;

  //! Version associated with the tool
  version_t version() const;

  virtual ~BuildToolVersion();

  bool operator==(const BuildToolVersion& rhs) const;
  bool operator!=(const BuildToolVersion& rhs) const;

  virtual void accept(Visitor& visitor) const override;

  LIEF_API friend std::ostream& operator<<(std::ostream& os, const BuildToolVersion& tool);

  private:
  TOOLS tool_{TOOLS::UNKNOWN};
  version_t version_;
};

class LIEF_API BuildVersion : public LoadCommand {
  friend class BinaryParser;

  public:
  //! @brief Version is an array of **3** integers
  using version_t = std::array<uint32_t, 3>;

  using tools_list_t = std::vector<BuildToolVersion>;

  public:
  enum class PLATFORMS {
    UNKNOWN = 0,
    MACOS   = 1,
    IOS     = 2,
    TVOS    = 3,
    WATCHOS = 4,
  };

  public:
  BuildVersion();
  BuildVersion(const build_version_command *version_cmd);

  BuildVersion& operator=(const BuildVersion& copy);
  BuildVersion(const BuildVersion& copy);

  virtual BuildVersion* clone() const override;

  version_t minos() const;
  void minos(version_t version);

  version_t sdk() const;
  void sdk(version_t version);

  PLATFORMS platform() const;
  void platform(PLATFORMS plat);

  tools_list_t tools() const;

  virtual ~BuildVersion();

  bool operator==(const BuildVersion& rhs) const;
  bool operator!=(const BuildVersion& rhs) const;

  virtual void accept(Visitor& visitor) const override;

  virtual std::ostream& print(std::ostream& os) const override;

  private:
  PLATFORMS platform_{PLATFORMS::UNKNOWN};
  version_t minos_;
  version_t sdk_;
  tools_list_t tools_;
};

}
}
#endif
