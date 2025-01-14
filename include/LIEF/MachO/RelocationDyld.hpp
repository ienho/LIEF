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
#ifndef LIEF_MACHO_RELOCATION_DYLD_COMMAND_H_
#define LIEF_MACHO_RELOCATION_DYLD_COMMAND_H_
#include <iostream>

#include "LIEF/visibility.h"
#include "LIEF/types.hpp"

#include "LIEF/MachO/Relocation.hpp"

namespace LIEF {
namespace MachO {

class BinaryParser;

class LIEF_API RelocationDyld : public Relocation {

  friend class BinaryParser;

  public:
  using Relocation::Relocation;
  RelocationDyld();

  RelocationDyld& operator=(const RelocationDyld&);
  RelocationDyld(const RelocationDyld&);

  virtual ~RelocationDyld();

  virtual Relocation* clone() const override;

  //! @brief Indicates whether the item containing the address to be
  //! relocated is part of a CPU instruction that uses PC-relative addressing.
  //!
  //! For addresses contained in PC-relative instructions, the CPU adds the address of
  //! the instruction to the address contained in the instruction.
  virtual bool is_pc_relative() const override;

  //! @brief Origin of the relocation
  virtual RELOCATION_ORIGINS origin() const override;


  virtual void pc_relative(bool val) override;

  bool operator==(const RelocationDyld& rhs) const;
  bool operator!=(const RelocationDyld& rhs) const;

  bool operator<(const RelocationDyld& rhs) const;
  bool operator>=(const RelocationDyld& rhs) const;

  bool operator>(const RelocationDyld& rhs) const;
  bool operator<=(const RelocationDyld& rhs) const;

  virtual void accept(Visitor& visitor) const override;

  virtual std::ostream& print(std::ostream& os) const override;
};

}
}
#endif
